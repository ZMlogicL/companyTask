/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月5日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */

#include "peripheral.h"
#include "ddimusercustom.h"
#include "ddarm.h"
#include "ddi2c.h"
#include "ddi2cctrl.h"



K_TYPE_DEFINE_WITH_PRIVATE(DdI2cCtrl, dd_i2c_ctrl);
#define DD_I2C_CTRL_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdI2cCtrlPrivate, DD_TYPE_I2C_CTRL))

#define DdI2cCtrl_10BIT_ADDRESS_FIX_BIT	(0xF0)


struct _DdI2cCtrlPrivate
{
	volatile DdI2cSide side[DdI2c_CH_MAX];
	volatile DdI2cCtrlMaster master[DdI2c_CH_MAX];
	volatile DdI2cSlaveAddr slaveAddr[DdI2c_CH_MAX];
	volatile DdI2cCtrlSlave slave[DdI2c_CH_MAX];
	volatile DdI2cStartInfo startInfo[DdI2c_CH_MAX];
};


static void dd_i2c_ctrl_constructor(DdI2cCtrl *self)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdI2c_CH_MAX; i++)
	{
		priv->side[i] = DdI2cCtrl_SIDE_MASTER;
	}
}

static void dd_i2c_ctrl_destructor(DdI2cCtrl *self)
{

}

// Init Timeout info
void dd_i2c_ctrl_init_timeout_info(DdI2cCtrl *self, kuchar ch)
{
	ioPeri.i2c[ch].cst.bit.tocdiv = 0;
	ioPeri.i2c[ch].topr.bit.topr = 0;
	ioPeri.i2c[ch].cst.bit.terr = 0;
}

// Get SCL frequency
kuchar dd_i2c_ctrl_get_scl_frequency(DdI2cCtrl *self, DdI2cBps bps)
{
	kulong pclk;
	kuchar sclfrq = DdI2c_SCLFRQ_MAX;		// fale safe

	pclk = Dd_Top_Get_PCLK();

	if(bps == DdI2cCtrl_BPS_400){
		switch(pclk){
			case DdI2c_PCLK_50_0:
				sclfrq = DdI2c_SCLFRQ_400K_50MHZ;
				break;
			case DdI2c_PCLK_25_0:
				sclfrq = DdI2c_SCLFRQ_400K_25MHZ;
				break;
			default:
				break;
		}
	}
	else {	// DdI2cCtrl_BPS_100
		switch(pclk){
			case DdI2c_PCLK_50_0:
				sclfrq = DdI2c_SCLFRQ_100K_50MHZ;
				break;
			case DdI2c_PCLK_25_0:
				sclfrq = DdI2c_SCLFRQ_100K_25MHZ;
				break;
			default:
				break;
		}
	}

	return sclfrq;
}

// Open I2C channel
kint32 dd_i2c_ctrl_open(DdI2cCtrl *self, kuchar ch, kint32 timeout)
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_open() error. parameters is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	if(timeout == DdimUserCustom_SEM_WAIT_POL) {
		ercd = DDIM_User_Pol_Sem(SID_DD_I2C(ch));
	}
	else{
		ercd = DDIM_User_Twai_Sem(SID_DD_I2C(ch), (DdimUserCustom_TMO)timeout);
	}

	if(ercd != DdimUserCustom_E_OK) {
		if(DdimUserCustom_E_TMOUT == ercd) {
			return DdI2c_TIMEOUT;
		}
		return DdI2c_SEM_NG;
	}

	return D_DDIM_OK;
}

// Close I2C channel
kint32 dd_i2c_ctrl_close(DdI2cCtrl *self, kuchar ch)
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_close() error. parameters is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	ercd = DDIM_User_Sig_Sem(SID_DD_I2C(ch));
	if(DdimUserCustom_E_OK != ercd) {
		return DdI2c_SEM_NG;
	}

	return D_DDIM_OK;
}

// Send start condition.
kint32 dd_i2c_ctrl_start_master(DdI2cCtrl *self, kuchar ch, const DdI2cStartInfo* const startInfo)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);
	DdI2c *ddI2c = dd_i2c_get();
	kint32 ret = D_DDIM_OK;
	DdimUserCustom_FLGPTN flgPtn;
	kint32 wait;

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (startInfo == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_start_master() error. startInfo is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	if(priv->side[ch] != DdI2cCtrl_SIDE_MASTER){
		// State error
		Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
		return DdI2c_STATUS_ABNORMAL;
	}

	if(dd_i2c_get_state(ddI2c, ch) == DdI2c_STATE_IDLE){
		if(ioPeri.i2c[ch].cst.bit.bb == 1){
			// Bus Busy error
			Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
			return DdI2c_STATUS_ABNORMAL;
		}
	}

	switch(dd_i2c_get_state(ddI2c, ch)){
		case DdI2c_STATE_IDLE:	// FALL THROUGH
		case DdI2c_STATE_END:
			priv->startInfo[ch] = *startInfo;

			// Set destination slave address
			priv->slaveAddr[ch].addrByte[DdI2cCtrl_ADDR_BYTE_1ST] = 0;
			priv->slaveAddr[ch].addrByte[DdI2cCtrl_ADDR_BYTE_2ND] = 0;
			if(priv->master[ch].destSlaveAddrLen == DdI2cCtrl_ADDR_LEN_7){
				priv->slaveAddr[ch].bit.addr = (kuchar)priv->master[ch].destSlaveAddr;
			}
			else {	// DdI2cCtrl_ADDR_LEN_10
				priv->slaveAddr[ch].bit.addr = ((priv->master[ch].destSlaveAddr >> 8) & 0x03);
				priv->slaveAddr[ch].addrByte[DdI2cCtrl_ADDR_BYTE_1ST] |= DdI2cCtrl_10BIT_ADDRESS_FIX_BIT;
				priv->slaveAddr[ch].addrByte[DdI2cCtrl_ADDR_BYTE_2ND] = (priv->master[ch].destSlaveAddr & 0xFF);
			}

			if(startInfo->rwMode == DdI2cCtrl_RW_MODE_READ){
				// read mode
				priv->slaveAddr[ch].bit.rw = 1;
				dd_i2c_set_data_num(ddI2c, ch, startInfo->rwDataLen + 1);
				dd_i2c_set_next_event(ddI2c, ch, DdI2c_EVENT_START_READ);
			}
			else {
				// write mode
				priv->slaveAddr[ch].bit.rw = 0;
				dd_i2c_set_data_num(ddI2c, ch, startInfo->rwDataLen);
				dd_i2c_set_next_event(ddI2c, ch, DdI2c_EVENT_START_WRITE);
			}

			dd_i2c_set_data(ddI2c, ch, startInfo->rwData);
			dd_i2c_set_data_count(ddI2c, ch, 0);
			dd_i2c_set_error(ddI2c, ch, D_DDIM_OK);

			// Init PEC-info and Timeout error
			dd_i2c_init_pec_info(ddI2c, ch);

			// Clear the waiting end process flag
			DDIM_User_Clr_Flg(FID_DD_I2C, ~(dd_i2c_get_event_flg(ddI2c, ch)));

			// Generate the Start Condition
			ioPeri.i2c[ch].ctl1.bit.start = 1;
			Dd_ARM_Dsb_Pou();

			if(dd_i2c_get_state(ddI2c, ch) == DdI2c_STATE_END){
				// Clear ST.INT (release SCK)
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;		// Clear interrupt for the Repeat Start Condition
				Dd_ARM_Dsb_Pou();
			}

			// wait START bit clear (Start condition send)
			for (wait = 0; wait < 1000; wait++){
				if(ioPeri.i2c[ch].ctl1.bit.start == 0){
					break;
				}
			}

			// Set Interrupt Enable
			ioPeri.i2c[ch].ctl1.bit.inten = 1;

			// Wait the start condition complete (STDONE)
			if(DDIM_User_Twai_Flg(FID_DD_I2C, dd_i2c_get_event_flg(ddI2c, ch), DdimUserCustom_TWF_ORW, &flgPtn, startInfo->timeout) != DdimUserCustom_E_OK){
				dd_i2c_set_state(ddI2c, ch, DdI2c_STATE_ERROR);
				dd_i2c_set_error(ddI2c, ch, DdI2c_TIMEOUT);
				Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
			}

			ioPeri.i2c[ch].ctl1.bit.inten = 0;

			// Check error state
			if(dd_i2c_get_state(ddI2c, ch) == DdI2c_STATE_ERROR){
				dd_i2c_set_state(ddI2c, ch, DdI2c_STATE_END);
				ret = dd_i2c_get_error(ddI2c, ch);

				// Stop
				ioPeri.i2c[ch].ctl1.bit.stop = 1;

				// Clear ST.INT (release SCK)
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;		// Clear interrupt for the Repeat Start Condition

				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
			}
			break;

		default:
			// State error
			ret = DdI2c_STATUS_ABNORMAL;
			Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
			break;
	}

	return ret;
}

// Send stop condition.
kint32 dd_i2c_ctrl_stop_master(DdI2cCtrl *self, kuchar ch)
{
	DdI2c *ddI2c = dd_i2c_get();
	kint32 ret = D_DDIM_OK;
	kint32 wait;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_stop_master() error. ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	dd_i2c_set_state(ddI2c, ch, DdI2c_STATE_IDLE);

	// Generate the Stop Condition
	ioPeri.i2c[ch].ctl1.bit.stop = 1;

	// Clear ST.INT (release SCK)
	ioPeri.i2c[ch].ctl1.bit.clrst = 1;

	// Set Interrupt Disable
	ioPeri.i2c[ch].ctl1.bit.inten = 0;
	Dd_ARM_Dsb_Pou();

	for(wait = 0; wait < 1000; wait++){
		if(ioPeri.i2c[ch].cst.bit.bb == 0){
			break;
		}
	}

	return ret;
}

// Start the communication waiting from the master.
kint32 dd_i2c_ctrl_start_slave(DdI2cCtrl *self, kuchar ch)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);
	DdI2c *ddI2c = dd_i2c_get();
	kint32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_start_slave() error. ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	if(priv->side[ch] != DdI2cCtrl_SIDE_SLAVE){
		// State error
		return DdI2c_STATUS_ABNORMAL;
	}

	dd_i2c_set_data_count(ddI2c, ch, 0);
	dd_i2c_set_error(ddI2c, ch, D_DDIM_OK);

	// Set Interrupt Enable
	ioPeri.i2c[ch].ctl1.bit.inten = 1;
	Dd_ARM_Dsb_Pou();

	return ret;
}

// Stop thje communication waiting from the master.
kint32 dd_i2c_ctrl_stop_slave(DdI2cCtrl *self, kuchar ch)
{
	kint32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_stop_slave() error. ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	// Set Interrupt Disable
	ioPeri.i2c[ch].ctl1.bit.inten = 0;
	Dd_ARM_Dsb_Pou();

	return ret;
}

// Set I2C Master Control information
kint32 dd_i2c_ctrl_ctrl_master(DdI2cCtrl *self, kuchar ch, const DdI2cCtrlMaster* const ctrlMaster)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);
	DdI2c *ddI2c = dd_i2c_get();

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrlMaster == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_ctrl_master() error. ctrlMaster is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	priv->master[ch] = *ctrlMaster;

	// Enable I2C
	ioPeri.i2c[ch].ctl2.bit.enable = 1;

	// Set SCL Frequency
	ioPeri.i2c[ch].ctl2.bit.sclfrq = dd_i2c_ctrl_get_scl_frequency(self, ctrlMaster->bps);

	// Set Slave Address Enable
	ioPeri.i2c[ch].addr.bit.saen = 0;

	// Set Global Call Match Enable
	ioPeri.i2c[ch].ctl1.bit.gcmen = 0;

	// Set Alert Response Match Enable
	ioPeri.i2c[ch].ctl1.bit.smbare = 0;

	// Init PEC-info
	dd_i2c_init_pec_info(ddI2c, ch);

	// Init Timeout info
	dd_i2c_ctrl_init_timeout_info(self, ch);

	Dd_ARM_Dsb_Pou();

	priv->side[ch] = DdI2cCtrl_SIDE_MASTER;
	dd_i2c_set_state(ddI2c, ch, DdI2c_STATE_IDLE);

	return D_DDIM_OK;
}

// Get I2C Master Control information
kint32 dd_i2c_ctrl_get_ctrl_master(DdI2cCtrl *self, kuchar ch, DdI2cCtrlMaster* const ctrlMaster)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrlMaster == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_get_ctrl_master() error. ctrlMaster is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	*ctrlMaster = priv->master[ch];

	return D_DDIM_OK;
}

// Set I2C Slave Control information
kint32 dd_i2c_ctrl_ctrl_slave(DdI2cCtrl *self, kuchar ch, const DdI2cCtrlSlave* const ctrlSlave)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);
	DdI2c *ddI2c = dd_i2c_get();

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrlSlave == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_ctrl_slave() error. ctrlSlave is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
	if(ctrlSlave->callback == NULL){
		// Call back function not specified error
		Ddim_Assertion(("dd_i2c_ctrl_ctrl_slave() error. callback is NULL.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	priv->slave[ch] = *ctrlSlave;

	// Enable I2C
	ioPeri.i2c[ch].ctl2.bit.enable = 1;

	// Set Own Slave Address
	if(ctrlSlave->ownSlaveAddrLen == DdI2cCtrl_ADDR_LEN_7){
		ioPeri.i2c[ch].ctl3.bit.s10en = 0;
		ioPeri.i2c[ch].addr.bit.addr = ctrlSlave->ownSlaveAddr;
	}
	else {	// DdI2cCtrl_ADDR_LEN_10
		ioPeri.i2c[ch].ctl3.bit.s10en = 1;
		ioPeri.i2c[ch].addr.bit.addr = ctrlSlave->ownSlaveAddr & 0x7F;
		ioPeri.i2c[ch].ctl3.bit.s10adr = (ctrlSlave->ownSlaveAddr >>  7) & 0x07;
	}

	// Set Slave Address Enable
	ioPeri.i2c[ch].addr.bit.saen = 1;

	// Set Global Call Match Enable
	ioPeri.i2c[ch].ctl1.bit.gcmen = ctrlSlave->globalCallEn;

	// Set Alert Response Match Enable
	ioPeri.i2c[ch].ctl1.bit.smbare = 0;

	// Init PEC-info and Timeout error
	dd_i2c_init_pec_info(ddI2c, ch);

	// Init Timeout info
	dd_i2c_ctrl_init_timeout_info(self, ch);

	Dd_ARM_Dsb_Pou();

	priv->side[ch] = DdI2cCtrl_SIDE_SLAVE;

	return D_DDIM_OK;
}

// Get I2C Slave Control information
kint32 dd_i2c_ctrl_get_ctrl_slave(DdI2cCtrl *self, kuchar ch, DdI2cCtrlSlave* const ctrlSlave)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrlSlave == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_get_ctrl_slave() error. ctrlSlave is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	*ctrlSlave = priv->slave[ch];

	return D_DDIM_OK;
}

// Set Control information for SMBus.
kint32 dd_i2c_ctrl_ctrl_smbus(DdI2cCtrl *self, kuchar ch, const DdI2cCtrlSmbus* const ctrlSmbus)
{
	DdI2c *ddI2c = dd_i2c_get();

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrlSmbus == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_ctrl_smbus() error. ctrlSmbus is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	if(ioPeri.i2c[ch].ctl2.bit.enable != 1){
		// State error
		return DdI2c_STATUS_ABNORMAL;
	}

	// Set Alert Response Match Enable (Slave only)
	ioPeri.i2c[ch].ctl1.bit.smbare = ctrlSmbus->alertRespEn;

	// Set PEC(Packet Error Checking) number of bytes.
	dd_i2c_set_pec_byte_num(ddI2c, ch, ctrlSmbus->pecNum);

	// Set Timeout Divider & Prescaler
	ioPeri.i2c[ch].cst.bit.tocdiv = ctrlSmbus->timeoutDiv;
	ioPeri.i2c[ch].topr.bit.topr = ctrlSmbus->timeoutPresc;
	ioPeri.i2c[ch].cst.bit.terr = 0;

	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

// Get Control information for SMBus.
kint32 dd_i2c_ctrl_get_ctrl_smbus(DdI2cCtrl *self, kuchar ch, DdI2cCtrlSmbus* const ctrlSmbus)
{
	DdI2c *ddI2c = dd_i2c_get();

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrlSmbus == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_get_ctrl_smbus() error. ctrlSmbus is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	if(ioPeri.i2c[ch].ctl2.bit.enable != 1){
		// State error
		return DdI2c_STATUS_ABNORMAL;
	}

	// Get Alert Response Match Enable (Slave only)
	ctrlSmbus->alertRespEn = ioPeri.i2c[ch].ctl1.bit.smbare;

	// Get PEC(Packet Error Checking) number of bytes.

	ctrlSmbus->pecNum = dd_i2c_get_pec_byte_num(ddI2c, ch);

	// Get Timeout Divider & Prescaler
	ctrlSmbus->timeoutDiv = (DdI2cToDiv)ioPeri.i2c[ch].cst.bit.tocdiv;
	ctrlSmbus->timeoutPresc = ioPeri.i2c[ch].topr.bit.topr;

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Set SCL Frequency
kint32 dd_i2c_ctrl_set_scl(DdI2cCtrl *self, kuchar ch, kuchar scl)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_set_scl() error.  ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
	if(scl > DdI2c_SCLFRQ_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_set_scl() error.  scl is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	// Set SCL Frequency
	ioPeri.i2c[ch].ctl2.bit.sclfrq = scl;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

// Get SCL Frequency
kint32 dd_i2c_ctrl_get_scl(DdI2cCtrl *self, kuchar ch, kuchar* scl)
{
#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (scl == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_get_scl() error. scl is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	// Get SCL Frequency
	*scl = ioPeri.i2c[ch].ctl2.bit.sclfrq;

	return D_DDIM_OK;
}
#endif

DdI2cSide dd_i2c_ctrl_get_side(DdI2cCtrl *self, kuchar ch)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

	return priv->side[ch];
}

DdI2cAddrLen dd_i2c_ctrl_get_master_dest_slave_addr_len(DdI2cCtrl *self, kuchar ch)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

	return priv->master[ch].destSlaveAddrLen;
}

kuchar dd_i2c_ctrl_get_slave_addr_byte(DdI2cCtrl *self, kuchar ch, DdI2cAddrCnt cnt)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

	return priv->slaveAddr[ch].addrByte[cnt];
}

DdI2cCtrlFunc dd_i2c_ctrl_get_slave_callback(DdI2cCtrl *self, kuchar ch)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

	return priv->slave[ch].callback;
}

DdI2cCtrl* dd_i2c_ctrl_new(void)
{
	DdI2cCtrl* self = k_object_new_with_private(DD_TYPE_I2C_CTRL, sizeof(DdI2cCtrlPrivate));

	return self;
}
