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
#include "dd_arm.h"
#include "ddi2c.h"
#include "ddi2cctrl.h"



K_TYPE_DEFINE_WITH_PRIVATE(DdI2cCtrl, dd_i2c_ctrl);
#define DD_I2C_CTRL_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdI2cCtrlPrivate, DD_TYPE_I2C_CTRL))

#define DdI2c_10BIT_ADDRESS_FIX_BIT	(0xF0)


struct _DdI2cCtrlPrivate
{
	volatile DdI2cSide gDD_I2C_Ctrl_Side[DdI2c_CH_MAX];
	volatile DdI2cCtrlMaster gDD_I2C_Ctrl_Master[DdI2c_CH_MAX];
	volatile DdI2cSlaveAddr gDD_I2C_Slave_Addr[DdI2c_CH_MAX];
	volatile DdI2cCtrlSlave gDD_I2C_Ctrl_Slave[DdI2c_CH_MAX];
	volatile DdI2cStartInfo gDD_I2C_Start_Info[DdI2c_CH_MAX];
};


static void dd_i2c_ctrl_constructor(DdI2cCtrl *self)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdI2c_CH_MAX; i++)
	{
		priv->gDD_I2C_Ctrl_Side[i] = DdI2cCtrl_SIDE_MASTER;
	}
}

static void dd_i2c_ctrl_destructor(DdI2cCtrl *self)
{

}

// Init Timeout info
VOID dd_i2c_ctrl_init_timeout_info(DdI2cCtrl *self, UCHAR ch)
{
	IO_PERI.I2C[ch].CST.bit.TOCDIV	= 0;
	IO_PERI.I2C[ch].TOPR.bit.TOPR	= 0;
	IO_PERI.I2C[ch].CST.bit.TERR	= 0;
}

// Get SCL frequency
UCHAR dd_i2c_ctrl_get_scl_frequency(DdI2cCtrl *self, DdI2cBps bps)
{
	ULONG pclk;
	UCHAR sclfrq = DdI2c_SCLFRQ_MAX;		// fale safe

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

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
// Open I2C channel
INT32 dd_i2c_ctrl_open(DdI2cCtrl *self, UCHAR ch, INT32 timeout)
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_open() error. parameters is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	if(timeout == D_DDIM_USER_SEM_WAIT_POL) {
		ercd = DDIM_User_Pol_Sem(SID_DD_I2C(ch));
	}
	else{
		ercd = DDIM_User_Twai_Sem(SID_DD_I2C(ch), (DDIM_USER_TMO)timeout);
	}

	if(ercd != D_DDIM_USER_E_OK) {
		if(D_DDIM_USER_E_TMOUT == ercd) {
			return DdI2c_TIMEOUT;
		}
		return DdI2c_SEM_NG;
	}

	return D_DDIM_OK;
}

// Close I2C channel
INT32 dd_i2c_ctrl_close(DdI2cCtrl *self, UCHAR ch)
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_close() error. parameters is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	ercd = DDIM_User_Sig_Sem(SID_DD_I2C(ch));
	if(D_DDIM_USER_E_OK != ercd) {
		return DdI2c_SEM_NG;
	}

	return D_DDIM_OK;
}

// Send start condition.
INT32 dd_i2c_ctrl_start_master(DdI2cCtrl *self, UCHAR ch, const DdI2cStartInfo* const start_info)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);
	DdI2c *ddI2c = dd_i2c_get();
	INT32 ret = D_DDIM_OK;
	DDIM_USER_FLGPTN flg_ptn;
	INT32 wait;

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (start_info == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_start_master() error. start_info is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	if(priv->gDD_I2C_Ctrl_Side[ch] != DdI2cCtrl_SIDE_MASTER){
		// State error
		Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
		return DdI2c_STATUS_ABNORMAL;
	}

	if(dd_i2c_get_state(ddI2c, ch) == DdI2c_STATE_IDLE){
		if(IO_PERI.I2C[ch].CST.bit.BB == 1){
			// Bus Busy error
			Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
			return DdI2c_STATUS_ABNORMAL;
		}
	}

	switch(dd_i2c_get_state(ddI2c, ch)){
		case DdI2c_STATE_IDLE:	// FALL THROUGH
		case DdI2c_STATE_END:
			priv->gDD_I2C_Start_Info[ch] = *start_info;

			// Set destination slave address
			priv->gDD_I2C_Slave_Addr[ch].addrByte[DdI2cCtrl_ADDR_BYTE_1ST] = 0;
			priv->gDD_I2C_Slave_Addr[ch].addrByte[DdI2cCtrl_ADDR_BYTE_2ND] = 0;
			if(priv->gDD_I2C_Ctrl_Master[ch].destSlaveAddrLen == DdI2cCtrl_ADDR_LEN_7){
				priv->gDD_I2C_Slave_Addr[ch].bit.addr = (UCHAR)priv->gDD_I2C_Ctrl_Master[ch].destSlaveAddr;
			}
			else {	// DdI2cCtrl_ADDR_LEN_10
				priv->gDD_I2C_Slave_Addr[ch].bit.addr = ((priv->gDD_I2C_Ctrl_Master[ch].destSlaveAddr >> 8) & 0x03);
				priv->gDD_I2C_Slave_Addr[ch].addrByte[DdI2cCtrl_ADDR_BYTE_1ST] |= DdI2c_10BIT_ADDRESS_FIX_BIT;
				priv->gDD_I2C_Slave_Addr[ch].addrByte[DdI2cCtrl_ADDR_BYTE_2ND] = (priv->gDD_I2C_Ctrl_Master[ch].destSlaveAddr & 0xFF);
			}

			if(start_info->rwMode == DdI2cCtrl_RW_MODE_READ){
				// read mode
				priv->gDD_I2C_Slave_Addr[ch].bit.rw	= 1;
				dd_i2c_set_data_num(ddI2c, ch, start_info->rwDataLen + 1);
				dd_i2c_set_next_event(ddI2c, ch, DdI2c_EVENT_START_READ);
			}
			else {
				// write mode
				priv->gDD_I2C_Slave_Addr[ch].bit.rw	= 0;
				dd_i2c_set_data_num(ddI2c, ch, start_info->rwDataLen);
				dd_i2c_set_next_event(ddI2c, ch, DdI2c_EVENT_START_WRITE);
			}

			dd_i2c_set_data(ddI2c, ch, start_info->rwData);
			dd_i2c_set_data_count(ddI2c, ch, 0);
			dd_i2c_set_error(ddI2c, ch, D_DDIM_OK);

			// Init PEC-info and Timeout error
			dd_i2c_init_pec_info(ddI2c, ch);

			// Clear the waiting end process flag
			DDIM_User_Clr_Flg(FID_DD_I2C, ~(dd_i2c_get_event_flg(ddI2c, ch)));

			// Generate the Start Condition
			IO_PERI.I2C[ch].CTL1.bit.START	= 1;
			Dd_ARM_Dsb_Pou();

			if(dd_i2c_get_state(ddI2c, ch) == DdI2c_STATE_END){
				// Clear ST.INT (release SCK)
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;		// Clear interrupt for the Repeat Start Condition
				Dd_ARM_Dsb_Pou();
			}

			// wait START bit clear (Start condition send)
			for (wait = 0; wait < 1000; wait++){
				if(IO_PERI.I2C[ch].CTL1.bit.START == 0){
					break;
				}
			}

			// Set Interrupt Enable
			IO_PERI.I2C[ch].CTL1.bit.INTEN	= 1;

			// Wait the start condition complete (STDONE)
			if(DDIM_User_Twai_Flg(FID_DD_I2C, dd_i2c_get_event_flg(ddI2c, ch), D_DDIM_USER_TWF_ORW, &flg_ptn, start_info->timeout) != D_DDIM_USER_E_OK){
				dd_i2c_set_state(ddI2c, ch, DdI2c_STATE_ERROR);
				dd_i2c_set_error(ddI2c, ch, DdI2c_TIMEOUT);
				Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
			}

			IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;

			// Check error state
			if(dd_i2c_get_state(ddI2c, ch) == DdI2c_STATE_ERROR){
				dd_i2c_set_state(ddI2c, ch, DdI2c_STATE_END);
				ret = dd_i2c_get_error(ddI2c, ch);

				// Stop
				IO_PERI.I2C[ch].CTL1.bit.STOP = 1;

				// Clear ST.INT (release SCK)
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;		// Clear interrupt for the Repeat Start Condition

				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
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
INT32 dd_i2c_ctrl_stop_master(DdI2cCtrl *self, UCHAR ch)
{
	DdI2c *ddI2c = dd_i2c_get();
	INT32 ret = D_DDIM_OK;
	INT32 wait;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_stop_master() error. ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	dd_i2c_set_state(ddI2c, ch, DdI2c_STATE_IDLE);

	// Generate the Stop Condition
	IO_PERI.I2C[ch].CTL1.bit.STOP = 1;

	// Clear ST.INT (release SCK)
	IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;

	// Set Interrupt Disable
	IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
	Dd_ARM_Dsb_Pou();

	for(wait = 0; wait < 1000; wait++){
		if(IO_PERI.I2C[ch].CST.bit.BB == 0){
			break;
		}
	}

	return ret;
}

// Start the communication waiting from the master.
INT32 dd_i2c_ctrl_start_slave(DdI2cCtrl *self, UCHAR ch)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);
	DdI2c *ddI2c = dd_i2c_get();
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_start_slave() error. ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	if(priv->gDD_I2C_Ctrl_Side[ch] != DdI2cCtrl_SIDE_SLAVE){
		// State error
		return DdI2c_STATUS_ABNORMAL;
	}

	dd_i2c_set_data_count(ddI2c, ch, 0);
	dd_i2c_set_error(ddI2c, ch, D_DDIM_OK);

	// Set Interrupt Enable
	IO_PERI.I2C[ch].CTL1.bit.INTEN	= 1;
	Dd_ARM_Dsb_Pou();

	return ret;
}

// Stop thje communication waiting from the master.
INT32 dd_i2c_ctrl_stop_slave(DdI2cCtrl *self, UCHAR ch)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("dd_i2c_ctrl_stop_slave() error. ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	// Set Interrupt Disable
	IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
	Dd_ARM_Dsb_Pou();

	return ret;
}

// Set I2C Master Control information
INT32 dd_i2c_ctrl_ctrl_master(DdI2cCtrl *self, UCHAR ch, const DdI2cCtrlMaster* const ctrl_master)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);
	DdI2c *ddI2c = dd_i2c_get();

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrl_master == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_ctrl_master() error. ctrl_master is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	priv->gDD_I2C_Ctrl_Master[ch] = *ctrl_master;

	// Enable I2C
	IO_PERI.I2C[ch].CTL2.bit.ENABLE = 1;

	// Set SCL Frequency
	IO_PERI.I2C[ch].CTL2.bit.SCLFRQ = dd_i2c_ctrl_get_scl_frequency(self, ctrl_master->bps);

	// Set Slave Address Enable
	IO_PERI.I2C[ch].ADDR.bit.SAEN = 0;

	// Set Global Call Match Enable
	IO_PERI.I2C[ch].CTL1.bit.GCMEN	= 0;

	// Set Alert Response Match Enable
	IO_PERI.I2C[ch].CTL1.bit.SMBARE	= 0;

	// Init PEC-info
	dd_i2c_init_pec_info(ddI2c, ch);

	// Init Timeout info
	dd_i2c_ctrl_init_timeout_info(self, ch);

	Dd_ARM_Dsb_Pou();

	priv->gDD_I2C_Ctrl_Side[ch] = DdI2cCtrl_SIDE_MASTER;
	dd_i2c_set_state(ddI2c, ch, DdI2c_STATE_IDLE);

	return D_DDIM_OK;
}

// Get I2C Master Control information
INT32 dd_i2c_ctrl_get_ctrl_master(DdI2cCtrl *self, UCHAR ch, DdI2cCtrlMaster* const ctrl_master)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrl_master == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_get_ctrl_master() error. ctrl_master is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	*ctrl_master = priv->gDD_I2C_Ctrl_Master[ch];

	return D_DDIM_OK;
}

// Set I2C Slave Control information
INT32 dd_i2c_ctrl_ctrl_slave(DdI2cCtrl *self, UCHAR ch, const DdI2cCtrlSlave* const ctrl_slave)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);
	DdI2c *ddI2c = dd_i2c_get();

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrl_slave == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_ctrl_slave() error. ctrl_slave is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
	if(ctrl_slave->callback == NULL){
		// Call back function not specified error
		Ddim_Assertion(("dd_i2c_ctrl_ctrl_slave() error. callback is NULL.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	priv->gDD_I2C_Ctrl_Slave[ch] = *ctrl_slave;

	// Enable I2C
	IO_PERI.I2C[ch].CTL2.bit.ENABLE = 1;

	// Set Own Slave Address
	if(ctrl_slave->ownSlaveAddrLen == DdI2cCtrl_ADDR_LEN_7){
		IO_PERI.I2C[ch].CTL3.bit.S10EN	= 0;
		IO_PERI.I2C[ch].ADDR.bit.ADDR	= ctrl_slave->ownSlaveAddr;
	}
	else {	// DdI2cCtrl_ADDR_LEN_10
		IO_PERI.I2C[ch].CTL3.bit.S10EN	= 1;
		IO_PERI.I2C[ch].ADDR.bit.ADDR	= ctrl_slave->ownSlaveAddr & 0x7F;
		IO_PERI.I2C[ch].CTL3.bit.S10ADR	= (ctrl_slave->ownSlaveAddr >>  7) & 0x07;
	}

	// Set Slave Address Enable
	IO_PERI.I2C[ch].ADDR.bit.SAEN = 1;

	// Set Global Call Match Enable
	IO_PERI.I2C[ch].CTL1.bit.GCMEN	= ctrl_slave->globalCallEn;

	// Set Alert Response Match Enable
	IO_PERI.I2C[ch].CTL1.bit.SMBARE	= 0;

	// Init PEC-info and Timeout error
	dd_i2c_init_pec_info(ddI2c, ch);

	// Init Timeout info
	dd_i2c_ctrl_init_timeout_info(self, ch);

	Dd_ARM_Dsb_Pou();

	priv->gDD_I2C_Ctrl_Side[ch] = DdI2cCtrl_SIDE_SLAVE;

	return D_DDIM_OK;
}

// Get I2C Slave Control information
INT32 dd_i2c_ctrl_get_ctrl_slave(DdI2cCtrl *self, UCHAR ch, DdI2cCtrlSlave* const ctrl_slave)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrl_slave == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_get_ctrl_slave() error. ctrl_slave is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	*ctrl_slave = priv->gDD_I2C_Ctrl_Slave[ch];

	return D_DDIM_OK;
}

// Set Control information for SMBus.
INT32 dd_i2c_ctrl_ctrl_smbus(DdI2cCtrl *self, UCHAR ch, const DdI2cCtrlSmbus* const ctrl_smbus)
{
	DdI2c *ddI2c = dd_i2c_get();

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrl_smbus == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_ctrl_smbus() error. ctrl_smbus is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	if(IO_PERI.I2C[ch].CTL2.bit.ENABLE != 1){
		// State error
		return DdI2c_STATUS_ABNORMAL;
	}

	// Set Alert Response Match Enable (Slave only)
	IO_PERI.I2C[ch].CTL1.bit.SMBARE	= ctrl_smbus->alertRespEn;

	// Set PEC(Packet Error Checking) number of bytes.
	dd_i2c_set_pec_byte_num(ddI2c, ch, ctrl_smbus->pecNum);

	// Set Timeout Divider & Prescaler
	IO_PERI.I2C[ch].CST.bit.TOCDIV	= ctrl_smbus->timeoutDiv;
	IO_PERI.I2C[ch].TOPR.bit.TOPR	= ctrl_smbus->timeoutPresc;
	IO_PERI.I2C[ch].CST.bit.TERR	= 0;

	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

// Get Control information for SMBus.
INT32 dd_i2c_ctrl_get_ctrl_smbus(DdI2cCtrl *self, UCHAR ch, DdI2cCtrlSmbus* const ctrl_smbus)
{
	DdI2c *ddI2c = dd_i2c_get();

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (ctrl_smbus == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_get_ctrl_smbus() error. ctrl_smbus is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	if(IO_PERI.I2C[ch].CTL2.bit.ENABLE != 1){
		// State error
		return DdI2c_STATUS_ABNORMAL;
	}

	// Get Alert Response Match Enable (Slave only)
	ctrl_smbus->alertRespEn	= IO_PERI.I2C[ch].CTL1.bit.SMBARE;

	// Get PEC(Packet Error Checking) number of bytes.

	ctrl_smbus->pecNum			= dd_i2c_get_pec_byte_num(ddI2c, ch);

	// Get Timeout Divider & Prescaler
	ctrl_smbus->timeoutDiv		= (DdI2cToDiv)IO_PERI.I2C[ch].CST.bit.TOCDIV;
	ctrl_smbus->timeoutPresc	= IO_PERI.I2C[ch].TOPR.bit.TOPR;

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Set SCL Frequency
INT32 dd_i2c_ctrl_set_scl(DdI2cCtrl *self, UCHAR ch, UCHAR scl)
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
	IO_PERI.I2C[ch].CTL2.bit.SCLFRQ = scl;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

// Get SCL Frequency
INT32 dd_i2c_ctrl_get_scl(DdI2cCtrl *self, UCHAR ch, UCHAR* scl)
{
#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (scl == NULL)){
		Ddim_Assertion(("dd_i2c_ctrl_get_scl() error. scl is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	// Get SCL Frequency
	*scl = IO_PERI.I2C[ch].CTL2.bit.SCLFRQ;

	return D_DDIM_OK;
}
#endif

DdI2cSide dd_i2c_ctrl_get_side(DdI2cCtrl *self, UCHAR ch)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

	return priv->gDD_I2C_Ctrl_Side[ch];
}

DdI2cAddrLen dd_i2c_ctrl_get_master_dest_slave_addr_len(DdI2cCtrl *self, UCHAR ch)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

	return priv->gDD_I2C_Ctrl_Master[ch].destSlaveAddrLen;
}

UCHAR dd_i2c_ctrl_get_slave_addr_byte(DdI2cCtrl *self, UCHAR ch, DdI2cAddrCnt cnt)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

	return priv->gDD_I2C_Slave_Addr[ch].addrByte[cnt];
}

DdI2cCtrlFunc dd_i2c_ctrl_get_slave_callback(DdI2cCtrl *self, UCHAR ch)
{
	DdI2cCtrlPrivate *priv = DD_I2C_CTRL_GET_PRIVATE(self);

	return priv->gDD_I2C_Ctrl_Slave[ch].callback;
}

DdI2cCtrl* dd_i2c_ctrl_new(void)
{
	DdI2cCtrl* self = k_object_new_with_private(DD_TYPE_I2C_CTRL, sizeof(DdI2cCtrlPrivate));

	return self;
}
