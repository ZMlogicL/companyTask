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

#include "driver_common.h"
#include "peripheral.h"
#include "ddimusercustom.h"
#include "ddtop.h"
#include "ddarm.h"
#include "ddi2c.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdI2c, dd_i2c);
#define DD_I2C_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdI2cPrivate, DD_TYPE_I2C))

#define DdI2c_DONT_CARE				(0)

//#define DdI2c_DEBUG

struct _DdI2cPrivate
{
	DdI2cCtrl *i2cCtrl;
	volatile DdI2cState state[DdI2c_CH_MAX];
	volatile DdI2cEvent nextEvent[DdI2c_CH_MAX];
	volatile kuint32 error[DdI2c_CH_MAX];
	volatile kuint32 dataCount[DdI2c_CH_MAX];
	volatile kuchar* data[DdI2c_CH_MAX];
	volatile kuint32 dataNum[DdI2c_CH_MAX];
	volatile kuint32 pecByteNum[DdI2c_CH_MAX];
};

// I2C ST.MODE register code
typedef enum {
	DdI2c_ST_MODE_IDLE	 = 0x00,		// No mode Information Available
	DdI2c_ST_MODE_STDONE	 = 0x01,		// Start condition generated
	DdI2c_ST_MODE_RSDONE	 = 0x02,		// Repeated start condition generated
	DdI2c_ST_MODE_IDLARL	 = 0x03,		// Arbitrationlost, unaddressed slave mode entered
	DdI2c_ST_MODE_MTADPA	 = 0x04,		// Slave address sent, positive ACK
	DdI2c_ST_MODE_MTADNA	 = 0x05,		// Slave address sent, negative ACK
	DdI2c_ST_MODE_MTDAPA	 = 0x06,		// Data byte sent, positive ACK
	DdI2c_ST_MODE_MTDANA	 = 0x07,		// Data byte sent, negative ACK
	DdI2c_ST_MODE_MRADPA	 = 0x08,		// Slave address sent, positive ACK
	DdI2c_ST_MODE_MRADNA	 = 0x09,		// Slave address sent, negative ACK
	DdI2c_ST_MODE_MRDAPA	 = 0x0A,		// Data byte received, positive ACK
	DdI2c_ST_MODE_MRDANA	 = 0x0B,		// Data byte received, negative ACK
	DdI2c_ST_MODE_SRADPA	 = 0x10,		// Slave address received, positive ACK
	DdI2c_ST_MODE_SRAAPA	 = 0x11,		// Slave address received after arbitration loss, positive ACK
	DdI2c_ST_MODE_SRDAPA	 = 0x12,		// Data byte received, positive ACK
	DdI2c_ST_MODE_SRDANA	 = 0x13,		// Data byte received, negative ACK
	DdI2c_ST_MODE_SSTOP	 = 0x1C,		// Slave mode stop condition detected
	DdI2c_ST_MODE_SGADPA	 = 0x1D,		// Slave address received after arbitration loss, positive ACK
	DdI2c_ST_MODE_SGAAPA	 = 0x1E,		// Slave address received after arbitration loss, positive ACK
	DdI2c_ST_MODE_BERROR	 = 0x1F,		// Invalid start or stop condition detected
	DdI2c_ST_MODE_STADPA	 = 0x14,		// Slave address received, positive ACK
	DdI2c_ST_MODE_STAAPA	 = 0x15,		// Slave address received after arbitration loss, positive ACK
	DdI2c_ST_MODE_STDAPA	 = 0x16,		// Data byte received, positive ACK
	DdI2c_ST_MODE_STDANA	 = 0x17,		// Data byte received, negative ACK
	DdI2c_ST_MODE_SATADP	 = 0x18,		// Alart response address received, positive ACK
	DdI2c_ST_MODE_SATAAP	 = 0x19,		// Alart response address received after arbitration loss, positive ACK
	DdI2c_ST_MODE_SATDAP	 = 0x1A,		// Addressed With Alart response address, data byte send, positive ACK
	DdI2c_ST_MODE_SATDAN	 = 0x1B,		// Addressed With Alart response address, data byte send, negative ACK
#if 0	// Hs Mode
	DdI2c_ST_MODE_MTMCER	 = 0x0C,		// Master code transmitted error detected (pos. ACK)
	DdI2c_ST_MODE_MTMCOK	 = 0x21,		// Master code transmitted OK – switched to Hs mode
	DdI2c_ST_MODE_HRSDONE = 0x22,		// Repeated start condition generated
	DdI2c_ST_MODE_HIDLARL = 0x23,		// Arbitration lost, high-speed unaddressed slave mode enterd
	DdI2c_ST_MODE_HMTADPA = 0x24,		// Slave address sent, positive ACK
	DdI2c_ST_MODE_HMTADNA = 0x25,		// Slave address sent, negative ACK
	DdI2c_ST_MODE_HMTDAPA = 0x26,		// Data byte sent, positive ACK
	DdI2c_ST_MODE_HMTDANA = 0x27,		// Data byte sent, negative ACK
	DdI2c_ST_MODE_HMRADPA = 0x28,		// Slave address sent, positive ACK
	DdI2c_ST_MODE_HMRADNA = 0x29,		// Slave address sent, negative ACK
	DdI2c_ST_MODE_HMRDAPA = 0x2A,		// Data byte received, positive ACK
	DdI2c_ST_MODE_HMRDANA = 0x2B,		// Data byte received, negative ACK
	DdI2c_ST_MODE_HSRADPA = 0x30,		// Slave address received, positive ACK
	DdI2c_ST_MODE_HSRDAPA = 0x32,		// Data byte received, positive ACK
	DdI2c_ST_MODE_HSRDANA = 0x33,		// Data byte received, negative ACK
	DdI2c_ST_MODE_HSTADTA = 0x34,		// Slave address received, positive ACK
	DdI2c_ST_MODE_HSTDAPA = 0x36,		// Data byte send, positive ACK
	DdI2c_ST_MODE_HSTDANA = 0x37,		// Data byte send, negative ACK
#endif
} I2cStMode;

// I2C Communication Error information
typedef enum {
	DdI2c_ERROR_NOT = 0,				// Error nothing
	DdI2c_ERROR_BER ,				// Bus Error
	DdI2c_ERROR_AL ,					// Arbitration lost
	DdI2c_ERROR_COMM					// Communication error
} I2cError;


static void ddI2cErrorOccur(DdI2c *self, kuchar ch);
static void ddI2cStModeIDLARLProc(DdI2c *self, kuchar ch);
static void ddI2cStModeMTADNAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeMRADNAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeMTDANAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeBERRORProc(DdI2c *self, kuchar ch);
static void ddI2cStModeTERRProc(DdI2c *self, kuchar ch);
static void ddI2cStModeSTDONEProc(DdI2c *self, kuchar ch);
static void ddI2cStModeRSDONEProc(DdI2c *self, kuchar ch);
static void ddI2cSendDataToSlave(DdI2c *self, kuchar ch);
static void ddI2cStModeMTADPAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeMTDAPAProc(DdI2c *self, kuchar ch);
static void ddI2cReceiveDataFromSlave(DdI2c *self, kuchar ch);
static void ddI2cStModeMRADPAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeMRDAPAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeMRDANAProc(DdI2c *self, kuchar ch);
static void ddI2cNotifySlaveAddressSpecified(DdI2c *self, kuchar ch);
static void ddI2cStModeSRADPAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeSRAAPAProc(DdI2c *self, kuchar ch);
static void ddI2cReceiveDataFromMaster(DdI2c *self, kuchar ch);
static void ddI2cStModeSRDAPAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeSRDANAProc(kuchar ch);
static void ddI2cStModeSSTOPProc(kuchar ch);
static void ddI2cStModeSGADPAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeSGAAPAProc(DdI2c *self, kuchar ch);
static void ddI2cSendDataToMaster(DdI2c *self, kuchar ch);
static void ddI2cStModeSTADPAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeSTAAPAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeSTDAPAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeSTDANAProc(DdI2c *self, kuchar ch);
static void ddI2cStModeSATADPProc(DdI2c *self, kuchar ch);
static void ddI2cStModeSATAAPProc(DdI2c *self, kuchar ch);
static void ddI2cStModeSATDAPProc(DdI2c *self, kuchar ch);
static void ddI2cStModeSATDANProc(DdI2c *self, kuchar ch);


static void dd_i2c_constructor(DdI2c *self)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdI2c_CH_MAX; i++)
	{
		priv->state[i] = DdI2c_STATE_IDLE;
		priv->nextEvent[i] = DdI2c_EVENT_START_WRITE;
		priv->error[i] = D_DDIM_OK;
		priv->dataCount[i] = 0;
		priv->data[i] = NULL;
		priv->dataNum[i] = 0;
		priv->pecByteNum[i] = 0;
	}

	priv->i2cCtrl = dd_i2c_ctrl_new();

}

static void dd_i2c_destructor(DdI2c *self)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->i2cCtrl)
	{
		k_object_unref(priv->i2cCtrl);
	}
}

/////////////////
///// Error /////
/////////////////
// Error occur process
static void ddI2cErrorOccur(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	DdimUserCustom_ER ret = DdimUserCustom_E_OK;

	priv->nextEvent[ch] = DdI2c_EVENT_ERROR;

	// Clear ST.INT (release SCK)
	ioPeri.i2c[ch].ctl1.bit.clrst = 1;
	Dd_ARM_Dsb_Pou();

	if(dd_i2c_ctrl_get_side(priv->i2cCtrl, ch) == DdI2cCtrl_SIDE_MASTER){
		// Master
		ioPeri.i2c[ch].ctl1.bit.inten = 0;

		priv->state[ch] = DdI2c_STATE_ERROR;
		priv->nextEvent[ch] = DdI2c_EVENT_END_RW;

		ret = DDIM_User_Set_Flg(FID_DD_I2C, dd_i2c_get_event_flg(self, ch));
		if(ret != DdimUserCustom_E_OK){
			Ddim_Print(("Error DDIM_User_Set_Flg!! ret = 0x%x\n", ret));
		}
	}
	else {
		// Slave
		if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
			(*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch,
					DdI2cCtrl_RECV_FROM_MASTER_ERROR, DdI2c_DONT_CARE);
		}
	}
}

// 0x03:Arbitrationlost, unaddressed slave mode entered
static void ddI2cStModeIDLARLProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->error[ch] = DdI2c_ARBITRATION_LOST;

	Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));

	ddI2cErrorOccur(self, ch);
}

// 0x05:Slave address sent, negative ACK
static void ddI2cStModeMTADNAProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->error[ch] = DdI2c_COMM_ERROR;

	/* Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__)); */

	ddI2cErrorOccur(self, ch);
}

// 0x09:Slave address sent, negative ACK
static void ddI2cStModeMRADNAProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->error[ch] = DdI2c_COMM_ERROR;

	Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));

	ddI2cErrorOccur(self, ch);
}

// 0x07:Data byte sent, negative ACK
static void ddI2cStModeMTDANAProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->error[ch] = DdI2c_COMM_ERROR;

	Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));

	ddI2cErrorOccur(self, ch);
}

// 0x1F:Invalid start or stop condition detected
static void ddI2cStModeBERRORProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->error[ch] = DdI2c_BUS_ERROR;

	Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));

	ddI2cErrorOccur(self, ch);
}

// Timeout Error
static void ddI2cStModeTERRProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->error[ch] = DdI2c_TIMEOUT;

	Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));

	ddI2cErrorOccur(self, ch);
}

//////////////////////////////////
///// Master Start condition /////
//////////////////////////////////
// 0x01:Start condition generated
static void ddI2cStModeSTDONEProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->state[ch] == DdI2c_STATE_IDLE){
		switch(priv->nextEvent[ch]){
			case DdI2c_EVENT_START_READ:		// FALL THROUGH
			case DdI2c_EVENT_START_WRITE:
				// check START bit (Start condition send)
				if (ioPeri.i2c[ch].ctl1.bit.start == 1) {
					priv->error[ch] = DdI2c_COMM_ERROR;
					Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
					ddI2cErrorOccur(self, ch);
					break;
				}
				
				// Send slave address
				if(dd_i2c_ctrl_get_master_dest_slave_addr_len(priv->i2cCtrl, ch) == DdI2cCtrl_ADDR_LEN_7){
					// 7 bit address
					ioPeri.i2c[ch].sdat.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST);
					if(priv->nextEvent[ch] == DdI2c_EVENT_START_READ){
						// Read
						priv->state[ch] = DdI2c_STATE_RECEIVING_DATA;
						priv->nextEvent[ch] = DdI2c_EVENT_RECEIVE;
					}
					else{
						// Write
						priv->state[ch] = DdI2c_STATE_SENDING_DATA;
						priv->nextEvent[ch] = DdI2c_EVENT_SEND;
					}
				}
				else {	// DdI2cCtrl_ADDR_LEN_10
					// 10 bit upper address
					ioPeri.i2c[ch].sdat.word = (dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST) & 0xFE);
					priv->state[ch] = DdI2c_STATE_SENDING_ADDRESS;
				}

				// Clear ST.INT (release SCK)
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
				break;
		}

	}
}

// 0x02:Repeated start condition generated
static void ddI2cStModeRSDONEProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->state[ch] == DdI2c_STATE_END){
		switch(priv->nextEvent[ch]){
			case DdI2c_EVENT_START_READ:		// FALL THROUGH
			case DdI2c_EVENT_START_WRITE:
				// check START bit (Start condition send)
				if (ioPeri.i2c[ch].ctl1.bit.start == 1) {
					priv->error[ch] = DdI2c_COMM_ERROR;
					Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
					ddI2cErrorOccur(self, ch);
					break;
				}
				
				ioPeri.i2c[ch].sdat.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST);

				if(dd_i2c_ctrl_get_master_dest_slave_addr_len(priv->i2cCtrl, ch) == DdI2cCtrl_ADDR_LEN_7){
					// 7 bit address
					if(priv->nextEvent[ch] == DdI2c_EVENT_START_READ){
						// Read
						priv->state[ch] = DdI2c_STATE_RECEIVING_DATA;
						priv->nextEvent[ch] = DdI2c_EVENT_RECEIVE;
					}
					else {
						// Write
						priv->state[ch] = DdI2c_STATE_SENDING_DATA;
						priv->nextEvent[ch] = DdI2c_EVENT_SEND;
					}
				}
				else {	// DdI2cCtrl_ADDR_LEN_10
					// 10 bit address
					if(priv->nextEvent[ch] == DdI2c_EVENT_START_READ){
						// Read
						priv->state[ch] = DdI2c_STATE_RECEIVING_DATA;
						priv->nextEvent[ch] = DdI2c_EVENT_RECEIVE;
					}
					else {
						// Write
						priv->state[ch] = DdI2c_STATE_SENDING_ADDRESS;
					}
				}

				// Clear ST.INT (release SCK)
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
	else if(priv->state[ch] == DdI2c_STATE_SENDING_ADDRESS){
		switch(priv->nextEvent[ch]){
			case DdI2c_EVENT_RECEIVE:		// FALL THROUGH
				ioPeri.i2c[ch].sdat.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST);

				if(dd_i2c_ctrl_get_master_dest_slave_addr_len(priv->i2cCtrl, ch) == DdI2cCtrl_ADDR_LEN_10){
					// 10 bit address
					priv->state[ch] = DdI2c_STATE_RECEIVING_DATA;
					priv->nextEvent[ch] = DdI2c_EVENT_RECEIVE;
				}

				// Clear ST.INT (release SCK)
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
	else if(priv->state[ch] == DdI2c_STATE_SENDING_DATA){
		switch(priv->nextEvent[ch]){
			case DdI2c_EVENT_SEND:
				ioPeri.i2c[ch].sdat.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST);

				if(dd_i2c_ctrl_get_master_dest_slave_addr_len(priv->i2cCtrl, ch) == DdI2cCtrl_ADDR_LEN_7){
						// Write
						priv->state[ch] = DdI2c_STATE_SENDING_DATA;
						priv->nextEvent[ch] = DdI2c_EVENT_SEND;
				}
				// Clear ST.INT (release SCK)
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

////////////////////////////////
///// Master Transmit Mode /////
////////////////////////////////
// Send data to slave
static void ddI2cSendDataToSlave(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	kuchar* sendData;
	kuint32 sendCount;

	sendData = (kuchar*)priv->data[ch];
	sendCount = priv->dataCount[ch];

	if(sendCount < priv->dataNum[ch]){
		// Start send
		ioPeri.i2c[ch].sdat.word = sendData[sendCount];
		sendCount++;

		priv->dataCount[ch] = sendCount;

		// Check end of send
		if(sendCount == priv->dataNum[ch]){
			// Check PEC enable
			if((sendCount + 1) == priv->pecByteNum[ch]){
				// Set PEC Next
				ioPeri.i2c[ch].cst.bit.pecnext = 1;
				Dd_ARM_Dsb_Pou();

				// Sending PEC byte
				priv->nextEvent[ch] = DdI2c_EVENT_SEND_PEC;
			}
			else {
				// End of send
				priv->nextEvent[ch] = DdI2c_EVENT_END_RW;
			}
		}

		// Clear ST.INT (release SCK)
		ioPeri.i2c[ch].ctl1.bit.clrst = 1;
		Dd_ARM_Dsb_Pou();
	}
	else{
		// Clear ST.INT (release SCK)
//		ioPeri.i2c[ch].ctl1.bit.clrst = 1;		// Not clear for the Repeat Start Condition or Stop Condition
//		Dd_ARM_Dsb_Pou();
	}
}

// 0x04:Slave address sent, positive ACK
static void ddI2cStModeMTADPAProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->state[ch] == DdI2c_STATE_SENDING_DATA){
		switch(priv->nextEvent[ch]){
			case DdI2c_EVENT_SEND:
				// Send Data
				ddI2cSendDataToSlave(self, ch);
				break;

			case DdI2c_EVENT_SEND_PEC:
				// End of send
				priv->nextEvent[ch] = DdI2c_EVENT_END_RW;

				// Clear PEC Next
				ioPeri.i2c[ch].cst.bit.pecnext = 0;

				// Clear ST.INT (release SCK)
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
	else if(priv->state[ch] == DdI2c_STATE_SENDING_ADDRESS){
		switch(priv->nextEvent[ch]){
			case DdI2c_EVENT_START_WRITE:
				// Send 10 bit lower address
				ioPeri.i2c[ch].sdat.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_2ND);
				Dd_ARM_Dsb_Pou();

				// Go to send data state
				priv->state[ch] = DdI2c_STATE_SENDING_DATA;
				priv->nextEvent[ch] = DdI2c_EVENT_SEND;

				// Clear ST.INT (release SCK)
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				Dd_ARM_Dsb_Pou();
				break;

			case DdI2c_EVENT_START_READ:
				// Send 10 bit lower address
				ioPeri.i2c[ch].sdat.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_2ND);
				Dd_ARM_Dsb_Pou();

				// Keep state
				priv->nextEvent[ch] = DdI2c_EVENT_RECEIVE;

				// Clear ST.INT (release SCK)
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

// 0x06:Data byte sent, positive ACK
static void ddI2cStModeMTDAPAProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	DdimUserCustom_ER ret = DdimUserCustom_E_OK;

	if(priv->state[ch] == DdI2c_STATE_SENDING_DATA){
		switch(priv->nextEvent[ch]){
			case DdI2c_EVENT_SEND:
				// Send Data
				ddI2cSendDataToSlave(self, ch);
				break;

			case DdI2c_EVENT_END_RW:
				// End send
				ioPeri.i2c[ch].ctl1.bit.inten = 0;	// Pause interrupt because INT has not been cleared
				// Clear ST.INT (release SCK)
//				ioPeri.i2c[ch].ctl1.bit.clrst = 1;		// Not clear for the Repeat Start Condition or Stop Condition
				Dd_ARM_Dsb_Pou();

				priv->state[ch] = DdI2c_STATE_END;

				ret = DDIM_User_Set_Flg(FID_DD_I2C, dd_i2c_get_event_flg(self, ch));
				if(ret != DdimUserCustom_E_OK){
					Ddim_Print(("Error DDIM_User_Set_Flg!! ret = 0x%x\n", ret));
				}
				break;

			default:
				// fail safe
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
	else if(priv->state[ch] == DdI2c_STATE_SENDING_ADDRESS){
		switch(priv->nextEvent[ch]){
			case DdI2c_EVENT_RECEIVE:
				// Resend 10 bit upper address and Read indicator
				ioPeri.i2c[ch].sdat.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST);
				Dd_ARM_Dsb_Pou();

				// Generate the Restart condition
				ioPeri.i2c[ch].ctl1.bit.start = 1;
				Dd_ARM_Dsb_Pou();

				// Clear ST.INT (release SCK)
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

///////////////////////////////
///// Master Receive Mode /////
///////////////////////////////
// Receive data from slave
static void ddI2cReceiveDataFromSlave(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	kuchar* recvData;
	kuint32 recvCount;
	DdimUserCustom_ER ret = DdimUserCustom_E_OK;

	recvData = (kuchar*)priv->data[ch];
	recvCount = priv->dataCount[ch];

	if(recvCount < priv->dataNum[ch]){
		// Continue receive
		if(recvCount != 0){
			recvData[recvCount-1] = (kuchar)ioPeri.i2c[ch].sdat.word;
		}
		recvCount++;
		priv->dataCount[ch] = recvCount;

		if(recvCount < priv->dataNum[ch]){
			if((recvCount + 1) == priv->dataNum[ch]){
				// next receive data is last. send no ack
				ioPeri.i2c[ch].ctl1.bit.ack = 1;

				// Check PEC enable
				if(recvCount == priv->pecByteNum[ch]){
					// Set PEC Next
					ioPeri.i2c[ch].cst.bit.pecnext = 1;
					Dd_ARM_Dsb_Pou();
				}
			}
			else {
				// send ack
				ioPeri.i2c[ch].ctl1.bit.ack = 0;
			}

			// Clear ST.INT (release SCK)
			ioPeri.i2c[ch].ctl1.bit.clrst = 1;
			Dd_ARM_Dsb_Pou();
		}
		else {
			// End of receive
			if (priv->dataCount[ch] == (priv->pecByteNum[ch] + 1)){
				// Check PEC Fault Error
				if(ioPeri.i2c[ch].cst.bit.pecfault != 0){
					priv->error[ch] = DdI2c_PEC_ERROR;
					Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
					ddI2cErrorOccur(self, ch);
				}
			}
			else {
				priv->nextEvent[ch] = DdI2c_EVENT_END_RW;
				priv->state[ch]	 = DdI2c_STATE_END;

				ioPeri.i2c[ch].ctl1.bit.inten = 0;	// Pause interrupt because INT has not been cleared
//				ioPeri.i2c[ch].ctl1.bit.clrst = 1;		// Not clear for the Repeat Start Condition or Stop Condition
				Dd_ARM_Dsb_Pou();

				ret = DDIM_User_Set_Flg(FID_DD_I2C, dd_i2c_get_event_flg(self, ch));
				if(ret != DdimUserCustom_E_OK){
					Ddim_Print(("Error DDIM_User_Set_Flg!! ret = 0x%x\n", ret));
				}
			}

			// Clear ST.INT (release SCK)
//			ioPeri.i2c[ch].ctl1.bit.clrst = 1;		// Not clear for the Repeat Start Condition or Stop Condition
//			Dd_ARM_Dsb_Pou();
		}
	}
	else{
		// Clear ST.INT (release SCK)
//		ioPeri.i2c[ch].ctl1.bit.clrst = 1;		// Not clear for the Repeat Start Condition or Stop Condition
//		Dd_ARM_Dsb_Pou();
	}
}

// 0x08:Slave address sent, positive ACK
static void ddI2cStModeMRADPAProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->state[ch] == DdI2c_STATE_RECEIVING_DATA){
		switch(priv->nextEvent[ch]){
			case DdI2c_EVENT_RECEIVE:
				// Receive Data
				ddI2cReceiveDataFromSlave(self, ch);
				break;

			default:
				// fail safe
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

// 0x0A:Data byte received, positive ACK
static void ddI2cStModeMRDAPAProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->state[ch] == DdI2c_STATE_RECEIVING_DATA){
		switch(priv->nextEvent[ch]){
			case DdI2c_EVENT_RECEIVE:
				// Receive Data
				ddI2cReceiveDataFromSlave(self, ch);
				break;

			default:
				// fail safe
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

// 0x0B:Data byte received, negative ACK
static void ddI2cStModeMRDANAProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->state[ch] == DdI2c_STATE_RECEIVING_DATA){
		switch(priv->nextEvent[ch]){
			case DdI2c_EVENT_RECEIVE:
				// Receive Data
				ddI2cReceiveDataFromSlave(self, ch);
				break;

			case DdI2c_EVENT_END_RW:
				// End receive
				priv->state[ch] = DdI2c_STATE_END;

				// Clear ST.INT (release SCK)
//				ioPeri.i2c[ch].ctl1.bit.clrst = 1;		// Not clear for the Repeat Start Condition or Stop Condition
//				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				ioPeri.i2c[ch].ctl1.bit.clrst = 1;
				ioPeri.i2c[ch].ctl1.bit.inten = 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

//////////////////////////////
///// Slave Receive Mode /////
//////////////////////////////
// Notify slave address specified
static void ddI2cNotifySlaveAddressSpecified(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
//	DdI2cSlaveAction action;

	if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
		// Notify slave address specified to Callback function
#if 0
		action = (*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, DdI2cCtrl_RECV_FROM_MASTER_ADDRESS,
				(kuchar)ioPeri.i2c[ch].sdat.word);

		switch(action.actionMode){
			case DdI2c_SEND_ACK_MASTER:
				// send ack
				ioPeri.i2c[ch].ctl1.bit.ack = 0;
				break;
			case DdI2c_SEND_NO_ACK_MASTER:
				// send no ack
				ioPeri.i2c[ch].ctl1.bit.ack = 1;
				break;
			default:
				break;
		}
#else
		(*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, DdI2cCtrl_RECV_FROM_MASTER_ADDRESS,
				(kuchar)ioPeri.i2c[ch].sdat.word);
#endif
	}

	// Clear ST.INT (release SCK)
	ioPeri.i2c[ch].ctl1.bit.clrst = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x10:Slave address received, positive ACK
static void ddI2cStModeSRADPAProc(DdI2c *self, kuchar ch)
{
	ddI2cNotifySlaveAddressSpecified(self, ch);
}

// 0x11:Slave address received after arbitration loss, positive ACK
static void ddI2cStModeSRAAPAProc(DdI2c *self, kuchar ch)
{
	ddI2cNotifySlaveAddressSpecified(self, ch);
}

static void ddI2cReceiveDataFromMaster(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	DdI2cSlaveAction action;
	I2cRecvFromMaster receiveSig = DdI2cCtrl_RECV_FROM_MASTER_DATA;

	if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
		priv->dataCount[ch]++;

		// Check PEC enable
		if(priv->dataCount[ch] == priv->pecByteNum[ch]){
			// Set PEC Next
			ioPeri.i2c[ch].cst.bit.pecnext = 1;
			Dd_ARM_Dsb_Pou();
		}
		else if (priv->dataCount[ch] == (priv->pecByteNum[ch] + 1)){
			// Check PEC Fault Error
			if(ioPeri.i2c[ch].cst.bit.pecfault != 0){
				receiveSig = DdI2cCtrl_RECV_FROM_MASTER_ERROR;
				priv->error[ch] = DdI2c_PEC_ERROR;

				Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
			}
		}

		// Receive data from master
		action = (*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, receiveSig,
				(kuchar)ioPeri.i2c[ch].sdat.word);

		switch(action.actionMode){
			case DdI2c_SEND_ACK_MASTER:
				// Continue receive data
				ioPeri.i2c[ch].ctl1.bit.ack = 0;
				break;
			case DdI2c_SEND_NO_ACK_MASTER:
				// End receive data
				ioPeri.i2c[ch].ctl1.bit.ack = 1;
				break;
			default:
				break;
		}
	}

	// Clear ST.INT (release SCK)
	ioPeri.i2c[ch].ctl1.bit.clrst = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x12:Data byte received, positive ACK
static void ddI2cStModeSRDAPAProc(DdI2c *self, kuchar ch)
{
	ddI2cReceiveDataFromMaster(self, ch);
}

// 0x13:Data byte received, negative ACK
static void ddI2cStModeSRDANAProc(kuchar ch)
{
	// Clear ST.INT (release SCK)
	ioPeri.i2c[ch].ctl1.bit.clrst = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x1C:Slave mode stop condition detected
static void ddI2cStModeSSTOPProc(kuchar ch)
{
	// Clear ST.INT (release SCK)
	ioPeri.i2c[ch].ctl1.bit.clrst = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x1D:Slave address received after arbitration loss, positive ACK
static void ddI2cStModeSGADPAProc(DdI2c *self, kuchar ch)
{
	ddI2cNotifySlaveAddressSpecified(self, ch);
}

// 0x1E:Slave address received after arbitration loss, positive ACK
static void ddI2cStModeSGAAPAProc(DdI2c *self, kuchar ch)
{
	ddI2cNotifySlaveAddressSpecified(self, ch);
}

///////////////////////////////
///// Slave Transmit Mode /////
///////////////////////////////
// Send data to master
static void ddI2cSendDataToMaster(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	DdI2cSlaveAction action;

	if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
		// Detect ACK
		// Send data to master
		action = (*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch,
				DdI2cCtrl_RECV_FROM_MASTER_ACK, DdI2c_DONT_CARE);

		if(action.actionMode == DdI2c_SEND_DATA_2_MASTER){
			// Send data
			ioPeri.i2c[ch].sdat.word = action.sendData;
			Dd_ARM_Dsb_Pou();

			priv->dataCount[ch]++;

			if(priv->dataCount[ch] == priv->pecByteNum[ch]){
				// Set PEC Next
				ioPeri.i2c[ch].cst.bit.pecnext = 1;
				Dd_ARM_Dsb_Pou();
			}
		}
		else{
			// Error
			Ddim_Print(("I2C Slave Action Mode is invalid!! actionMode = %d\n", action.actionMode));
		}
	}

	// Clear ST.INT (release SCK)
	ioPeri.i2c[ch].ctl1.bit.clrst = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x14:Slave address received, positive ACK
static void ddI2cStModeSTADPAProc(DdI2c *self, kuchar ch)
{
	dd_i2c_init_pec_info(self, ch);

	ddI2cSendDataToMaster(self, ch);
}

// 0x15:Slave address received after arbitration loss, positive ACK
static void ddI2cStModeSTAAPAProc(DdI2c *self, kuchar ch)
{
	dd_i2c_init_pec_info(self, ch);

	ddI2cSendDataToMaster(self, ch);
}

// 0x16:Data byte received, positive ACK
static void ddI2cStModeSTDAPAProc(DdI2c *self, kuchar ch)
{
	ddI2cSendDataToMaster(self, ch);
}

// 0x17:Data byte received, negative ACK
static void ddI2cStModeSTDANAProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
		// No detect ACK
		(*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, DdI2cCtrl_RECV_FROM_MASTER_NO_ACK, DdI2c_DONT_CARE);
	}

	// Clear ST.INT (release SCK)
	ioPeri.i2c[ch].ctl1.bit.clrst = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x18:Alart response address received, positive ACK
static void ddI2cStModeSATADPProc(DdI2c *self, kuchar ch)
{
	dd_i2c_init_pec_info(self, ch);

	ddI2cSendDataToMaster(self, ch);
}

// 0x19:Alart response address received after arbitration loss, positive ACK
static void ddI2cStModeSATAAPProc(DdI2c *self, kuchar ch)
{
	dd_i2c_init_pec_info(self, ch);

	ddI2cSendDataToMaster(self, ch);
}

// 0x1A:Addressed With Alart response address, data byte send, positive ACK
static void ddI2cStModeSATDAPProc(DdI2c *self, kuchar ch)
{
	ddI2cSendDataToMaster(self, ch);
}

// 0x1B:Addressed With Alart response address, data byte send, negative ACK
static void ddI2cStModeSATDANProc(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
		// No detect ACK
		(*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, DdI2cCtrl_RECV_FROM_MASTER_NO_ACK, DdI2c_DONT_CARE);
	}

	// Clear ST.INT (release SCK)
	ioPeri.i2c[ch].ctl1.bit.clrst = 1;
	Dd_ARM_Dsb_Pou();
}

// Get event flag of the ch specified
kuint32 dd_i2c_get_event_flg(DdI2c *self, kuchar ch)
{
	kuint32 ret;

	if(ch == DdI2c_CH_00) {
		ret = DdI2c_FLG_0;
	}
	else if(ch == DdI2c_CH_01) {
		ret = DdI2c_FLG_1;
	}
	else{
		ret = DdI2c_FLG_2;
	}
	return ret;
}

// Init PEC-info and Timeout error
void dd_i2c_init_pec_info(DdI2c *self, kuchar ch)
{
	// Init PEC info
	ioPeri.i2c[ch].cst.bit.pecnext = 0;
}

// Terminate the I2C.
void dd_i2c_terminate(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->state[ch] = DdI2c_STATE_IDLE;

	// Clear EN
	ioPeri.i2c[ch].ctl2.bit.enable = 0;
	Dd_ARM_Dsb_Pou();
}

// Get Test SDA.
kint32 dd_i2c_get_test_sda(DdI2c *self, kuchar ch, kuchar* sda)
{
	kint32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (sda == NULL)){
		Ddim_Assertion(("Dd_I2C_Get_Test_SDA() error. sda is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	*sda = ioPeri.i2c[ch].cst.bit.tsda;

	return ret;
}

// Get Error Cause.
kuint32 dd_i2c_get_error_cause(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("Dd_I2C_Get_Error_Cause() error. ch is abnormal.\n"));
		return 0;
	}
#endif

	return priv->error[ch];
}

// Set Toggle SCL.
kint32 dd_i2c_set_toggle_scl(DdI2c *self, kuchar ch)
{
	kint32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("Dd_I2C_Set_Toggle_SCL() error. ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	ioPeri.i2c[ch].cst.bit.tgscl = 1;
	Dd_ARM_Dsb_Pou();

	return ret;
}

// Intterupt handler.
void dd_i2c_int_handler(DdI2c *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("Dd_I2C_Int_Handler() error. ch is abnormal.\n"));
		return ;
	}
#endif

#ifdef DdI2c_DEBUG
	printf("IN:I2C[%d].ST.MODE=0x%02X, priv->state=%d, priv->nextEvent=%d\n", ch, ioPeri.i2c[ch].st.bit.mode, priv->state[ch], priv->nextEvent[ch]);
#endif

	if(ioPeri.i2c[ch].cst.bit.terr == 1){
		// Timeout Error
		ddI2cStModeTERRProc(self, ch);
	}

	switch(ioPeri.i2c[ch].st.bit.mode){
		//////////////////////////////////
		///// Master Start condition /////
		//////////////////////////////////
		case DdI2c_ST_MODE_STDONE:		// 0x01:Start condition generated
			ddI2cStModeSTDONEProc(self, ch);
			break;
		case DdI2c_ST_MODE_RSDONE:		// 0x02:Repeated start condition generated
			ddI2cStModeRSDONEProc(self, ch);
			break;
		case DdI2c_ST_MODE_IDLARL:		// 0x03:Arbitrationlost, unaddressed slave mode entered
			ddI2cStModeIDLARLProc(self, ch);
			break;

		////////////////////////////////
		///// Master Transmit Mode /////
		////////////////////////////////
		case DdI2c_ST_MODE_MTADPA:		// 0x04:Slave address sent, positive ACK
			ddI2cStModeMTADPAProc(self, ch);
			break;
		case DdI2c_ST_MODE_MTADNA:		// 0x05:Slave address sent, negative ACK
			ddI2cStModeMTADNAProc(self, ch);
			break;
		case DdI2c_ST_MODE_MTDAPA:		// 0x06:Data byte sent, positive ACK
			ddI2cStModeMTDAPAProc(self, ch);
			break;
		case DdI2c_ST_MODE_MTDANA:		// 0x07:Data byte sent, negative ACK
			ddI2cStModeMTDANAProc(self, ch);
			break;

		///////////////////////////////
		///// Master Receive Mode /////
		///////////////////////////////
		case DdI2c_ST_MODE_MRADPA:		// 0x08:Slave address sent, positive ACK
			ddI2cStModeMRADPAProc(self, ch);
			break;
		case DdI2c_ST_MODE_MRADNA:		// 0x09:Slave address sent, negative ACK
			ddI2cStModeMRADNAProc(self, ch);
			break;
		case DdI2c_ST_MODE_MRDAPA:		// 0x0A:Data byte received, positive ACK
			ddI2cStModeMRDAPAProc(self, ch);
			break;
		case DdI2c_ST_MODE_MRDANA:		// 0x0B:Data byte received, negative ACK
			ddI2cStModeMRDANAProc(self, ch);
			break;

		//////////////////////////////
		///// Slave Receive Mode /////
		//////////////////////////////
		case DdI2c_ST_MODE_SRADPA:		// 0x10:Slave address received, positive ACK
			ddI2cStModeSRADPAProc(self, ch);
			break;
		case DdI2c_ST_MODE_SRAAPA:		// 0x11:Slave address received after arbitration loss, positive ACK
			ddI2cStModeSRAAPAProc(self, ch);
			break;
		case DdI2c_ST_MODE_SRDAPA:		// 0x12:Data byte received, positive ACK
			ddI2cStModeSRDAPAProc(self, ch);
			break;
		case DdI2c_ST_MODE_SRDANA:		// 0x13:Data byte received, negative ACK
			ddI2cStModeSRDANAProc(ch);
			break;
		case DdI2c_ST_MODE_SSTOP:		// 0x1C:Slave mode stop condition detected
			ddI2cStModeSSTOPProc(ch);
			break;
		case DdI2c_ST_MODE_SGADPA:		// 0x1D:Slave address received after arbitration loss, positive ACK
			ddI2cStModeSGADPAProc(self, ch);
			break;
		case DdI2c_ST_MODE_SGAAPA:		// 0x1E:Slave address received after arbitration loss, positive ACK
			ddI2cStModeSGAAPAProc(self, ch);
			break;

		///////////////////////////////
		///// Slave Transmit Mode /////
		///////////////////////////////
		case DdI2c_ST_MODE_STADPA:		// 0x14:Slave address received, positive ACK
			ddI2cStModeSTADPAProc(self, ch);
			break;
		case DdI2c_ST_MODE_STAAPA:		// 0x15:Slave address received after arbitration loss, positive ACK
			ddI2cStModeSTAAPAProc(self, ch);
			break;
		case DdI2c_ST_MODE_STDAPA:		// 0x16:Data byte received, positive ACK
			ddI2cStModeSTDAPAProc(self, ch);
			break;
		case DdI2c_ST_MODE_STDANA:		// 0x17:Data byte received, negative ACK
			ddI2cStModeSTDANAProc(self, ch);
			break;
		case DdI2c_ST_MODE_SATADP:		// 0x18:Alart response address received, positive ACK
			ddI2cStModeSATADPProc(self, ch);
			break;
		case DdI2c_ST_MODE_SATAAP:		// 0x19:Alart response address received after arbitration loss, positive ACK
			ddI2cStModeSATAAPProc(self, ch);
			break;
		case DdI2c_ST_MODE_SATDAP:		// 0x1A:Addressed With Alart response address, data byte send, positive ACK
			ddI2cStModeSATDAPProc(self, ch);
			break;
		case DdI2c_ST_MODE_SATDAN:		// 0x1B:Addressed With Alart response address, data byte send, negative ACK
			ddI2cStModeSATDANProc(self, ch);
			break;

		/////////////////
		///// Error /////
		/////////////////
		case DdI2c_ST_MODE_BERROR:		// 0x1F:Invalid start or stop condition detected
			ddI2cStModeBERRORProc(self, ch);
			break;
		default:
			// fail safe
			ioPeri.i2c[ch].ctl1.bit.clrst = 1;
			ioPeri.i2c[ch].ctl1.bit.inten = 0;
			Dd_ARM_Dsb_Pou();
			break;
	}
}

kint32 dd_i2c_open(DdI2c *self, kuchar ch, kint32 timeout)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_open(priv->i2cCtrl, ch, timeout);
}

kint32 dd_i2c_close(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_close(priv->i2cCtrl, ch);
}

kint32 dd_i2c_start_master(DdI2c *self, kuchar ch, const DdI2cStartInfo* const startInfo)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_start_master(priv->i2cCtrl, ch, startInfo);
}

kint32 dd_i2c_stop_master(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_stop_master(priv->i2cCtrl, ch);
}

kint32 dd_i2c_start_slave(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_start_slave(priv->i2cCtrl, ch);
}

kint32 dd_i2c_stop_slave(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_stop_slave(priv->i2cCtrl, ch);
}

kint32 dd_i2c_ctrl_master(DdI2c *self, kuchar ch, const DdI2cCtrlMaster* const ctrlMaster)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_ctrl_master(priv->i2cCtrl, ch, ctrlMaster);
}

kint32 dd_i2c_get_ctrl_master(DdI2c *self, kuchar ch, DdI2cCtrlMaster* const ctrlMaster)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_get_ctrl_master(priv->i2cCtrl, ch, ctrlMaster);
}

kint32 dd_i2c_ctrl_slave(DdI2c *self, kuchar ch, const DdI2cCtrlSlave* const ctrlSlave)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_ctrl_slave(priv->i2cCtrl, ch, ctrlSlave);
}

kint32 dd_i2c_get_ctrl_slave(DdI2c *self, kuchar ch, DdI2cCtrlSlave* const ctrlSlave)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_get_ctrl_slave(priv->i2cCtrl, ch, ctrlSlave);
}

kint32 dd_i2c_ctrl_smbus(DdI2c *self, kuchar ch, const DdI2cCtrlSmbus* const ctrlSmbus)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_ctrl_smbus(priv->i2cCtrl, ch, ctrlSmbus);
}

kint32 dd_i2c_get_ctrl_smbus(DdI2c *self, kuchar ch, DdI2cCtrlSmbus* const ctrlSmbus)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_get_ctrl_smbus(priv->i2cCtrl, ch, ctrlSmbus);
}

#ifdef CO_DDIM_UTILITY_USE
kint32 dd_i2c_set_scl(DdI2c *self, kuchar ch, kuchar scl)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_set_scl(priv->i2cCtrl, ch, scl);
}

kint32 dd_i2c_get_scl(DdI2c *self, kuchar ch, kuchar* scl)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_get_scl(priv->i2cCtrl, ch, scl);
}

#endif

DdI2cState dd_i2c_get_state(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return priv->state[ch];
}

void dd_i2c_set_state(DdI2c *self, kuchar ch, DdI2cState state)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->state[ch] = state;
}

void dd_i2c_set_next_event(DdI2c *self, kuchar ch, DdI2cEvent nextEvent)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->nextEvent[ch] = nextEvent;
}

kuint32 dd_i2c_get_error(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return priv->error[ch];
}

void dd_i2c_set_error(DdI2c *self, kuchar ch, kuint32 err)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->error[ch] = err;
}

void dd_i2c_set_data_count(DdI2c *self, kuchar ch, kuint32 dataCount)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->dataCount[ch] = dataCount;
}

void dd_i2c_set_data(DdI2c *self, kuchar ch, kuchar* data)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->data[ch] = data;
}

void dd_i2c_set_data_num(DdI2c *self, kuchar ch, kuint32 dataNum)

{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->dataNum[ch] = dataNum;
}

kuint32 dd_i2c_get_pec_byte_num(DdI2c *self, kuchar ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return priv->pecByteNum[ch];
}

void dd_i2c_set_pec_byte_num(DdI2c *self, kuchar ch, kuint32 pecByteNum)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->pecByteNum[ch] = pecByteNum;
}

DdI2c* dd_i2c_get(void)
{
	static DdI2c* self = NULL;

	if(!self)
		self = k_object_new_with_private(DD_TYPE_I2C, sizeof(DdI2cPrivate));

	return self;
}
