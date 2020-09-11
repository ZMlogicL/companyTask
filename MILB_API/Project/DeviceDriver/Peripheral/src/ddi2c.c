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

#include "ddim_user_custom.h"
#include "driver_common.h"
#include "peripheral.h"
#include "dd_top.h"
#include "dd_arm.h"
#include "ddi2c.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdI2c, dd_i2c);
#define DD_I2C_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdI2cPrivate, DD_TYPE_I2C))

#define DdI2c_DONT_CARE				(0)

//#define DdI2c_DEBUG

struct _DdI2cPrivate
{
	DdI2cCtrl *i2cCtrl;
	volatile DdI2cState gDD_I2C_State[DdI2c_CH_MAX];
	volatile DdI2cEvent gDD_I2C_Next_Event[DdI2c_CH_MAX];
	volatile UINT32 gDD_I2C_Error[DdI2c_CH_MAX];
	volatile UINT32 gDD_I2C_Data_Count[DdI2c_CH_MAX];
	volatile UCHAR* gDD_I2C_Data[DdI2c_CH_MAX];
	volatile UINT32 gDD_I2C_Data_Num[DdI2c_CH_MAX];
	volatile UINT32 gDD_I2C_PEC_Byte_Num[DdI2c_CH_MAX];
};

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// I2C ST.MODE register code
typedef enum {
	E_DD_I2C_ST_MODE_IDLE		= 0x00,		// No mode Information Available
	E_DD_I2C_ST_MODE_STDONE		= 0x01,		// Start condition generated
	E_DD_I2C_ST_MODE_RSDONE		= 0x02,		// Repeated start condition generated
	E_DD_I2C_ST_MODE_IDLARL		= 0x03,		// Arbitrationlost, unaddressed slave mode entered
	E_DD_I2C_ST_MODE_MTADPA		= 0x04,		// Slave address sent, positive ACK
	E_DD_I2C_ST_MODE_MTADNA		= 0x05,		// Slave address sent, negative ACK
	E_DD_I2C_ST_MODE_MTDAPA		= 0x06,		// Data byte sent, positive ACK
	E_DD_I2C_ST_MODE_MTDANA		= 0x07,		// Data byte sent, negative ACK
	E_DD_I2C_ST_MODE_MRADPA		= 0x08,		// Slave address sent, positive ACK
	E_DD_I2C_ST_MODE_MRADNA		= 0x09,		// Slave address sent, negative ACK
	E_DD_I2C_ST_MODE_MRDAPA		= 0x0A,		// Data byte received, positive ACK
	E_DD_I2C_ST_MODE_MRDANA		= 0x0B,		// Data byte received, negative ACK
	E_DD_I2C_ST_MODE_SRADPA		= 0x10,		// Slave address received, positive ACK
	E_DD_I2C_ST_MODE_SRAAPA		= 0x11,		// Slave address received after arbitration loss, positive ACK
	E_DD_I2C_ST_MODE_SRDAPA		= 0x12,		// Data byte received, positive ACK
	E_DD_I2C_ST_MODE_SRDANA		= 0x13,		// Data byte received, negative ACK
	E_DD_I2C_ST_MODE_SSTOP		= 0x1C,		// Slave mode stop condition detected
	E_DD_I2C_ST_MODE_SGADPA		= 0x1D,		// Slave address received after arbitration loss, positive ACK
	E_DD_I2C_ST_MODE_SGAAPA		= 0x1E,		// Slave address received after arbitration loss, positive ACK
	E_DD_I2C_ST_MODE_BERROR		= 0x1F,		// Invalid start or stop condition detected
	E_DD_I2C_ST_MODE_STADPA		= 0x14,		// Slave address received, positive ACK
	E_DD_I2C_ST_MODE_STAAPA		= 0x15,		// Slave address received after arbitration loss, positive ACK
	E_DD_I2C_ST_MODE_STDAPA		= 0x16,		// Data byte received, positive ACK
	E_DD_I2C_ST_MODE_STDANA		= 0x17,		// Data byte received, negative ACK
	E_DD_I2C_ST_MODE_SATADP		= 0x18,		// Alart response address received, positive ACK
	E_DD_I2C_ST_MODE_SATAAP		= 0x19,		// Alart response address received after arbitration loss, positive ACK
	E_DD_I2C_ST_MODE_SATDAP		= 0x1A,		// Addressed With Alart response address, data byte send, positive ACK
	E_DD_I2C_ST_MODE_SATDAN		= 0x1B,		// Addressed With Alart response address, data byte send, negative ACK
#if 0	// Hs Mode
	E_DD_I2C_ST_MODE_MTMCER		= 0x0C,		// Master code transmitted error detected (pos. ACK)
	E_DD_I2C_ST_MODE_MTMCOK		= 0x21,		// Master code transmitted OK – switched to Hs mode
	E_DD_I2C_ST_MODE_HRSDONE	= 0x22,		// Repeated start condition generated
	E_DD_I2C_ST_MODE_HIDLARL	= 0x23,		// Arbitration lost, high-speed unaddressed slave mode enterd
	E_DD_I2C_ST_MODE_HMTADPA	= 0x24,		// Slave address sent, positive ACK
	E_DD_I2C_ST_MODE_HMTADNA	= 0x25,		// Slave address sent, negative ACK
	E_DD_I2C_ST_MODE_HMTDAPA	= 0x26,		// Data byte sent, positive ACK
	E_DD_I2C_ST_MODE_HMTDANA	= 0x27,		// Data byte sent, negative ACK
	E_DD_I2C_ST_MODE_HMRADPA	= 0x28,		// Slave address sent, positive ACK
	E_DD_I2C_ST_MODE_HMRADNA	= 0x29,		// Slave address sent, negative ACK
	E_DD_I2C_ST_MODE_HMRDAPA	= 0x2A,		// Data byte received, positive ACK
	E_DD_I2C_ST_MODE_HMRDANA	= 0x2B,		// Data byte received, negative ACK
	E_DD_I2C_ST_MODE_HSRADPA	= 0x30,		// Slave address received, positive ACK
	E_DD_I2C_ST_MODE_HSRDAPA	= 0x32,		// Data byte received, positive ACK
	E_DD_I2C_ST_MODE_HSRDANA	= 0x33,		// Data byte received, negative ACK
	E_DD_I2C_ST_MODE_HSTADTA	= 0x34,		// Slave address received, positive ACK
	E_DD_I2C_ST_MODE_HSTDAPA	= 0x36,		// Data byte send, positive ACK
	E_DD_I2C_ST_MODE_HSTDANA	= 0x37,		// Data byte send, negative ACK
#endif
} E_DD_I2C_ST_MODE;

// I2C Communication Error information
typedef enum {
	E_DD_I2C_ERROR_NOT = 0,				// Error nothing
	E_DD_I2C_ERROR_BER ,				// Bus Error
	E_DD_I2C_ERROR_AL ,					// Arbitration lost
	E_DD_I2C_ERROR_COMM					// Communication error
} E_DD_I2C_ERROR;


static void dd_i2c_constructor(DdI2c *self)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdI2c_CH_MAX; i++)
	{
		priv->gDD_I2C_State[i] = DdI2c_STATE_IDLE;
		priv->gDD_I2C_Next_Event[i] = DdI2c_EVENT_START_WRITE;
		priv->gDD_I2C_Error[i] = D_DDIM_OK;
		priv->gDD_I2C_Data_Count[i] = 0;
		priv->gDD_I2C_Data[i] = NULL;
		priv->gDD_I2C_Data_Num[i] = 0;
		priv->gDD_I2C_PEC_Byte_Num[i] = 0;
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
static VOID dd_i2c_error_occur(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	DDIM_USER_ER ret = D_DDIM_USER_E_OK;
	priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_ERROR;

	// Clear ST.INT (release SCK)
	IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
	Dd_ARM_Dsb_Pou();

	if(dd_i2c_ctrl_get_side(priv->i2cCtrl, ch) == DdI2cCtrl_SIDE_MASTER){
		// Master
		IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;

		priv->gDD_I2C_State[ch] = DdI2c_STATE_ERROR;
		priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_END_RW;

		ret = DDIM_User_Set_Flg(FID_DD_I2C, dd_i2c_get_event_flg(self, ch));
		if(ret != D_DDIM_USER_E_OK){
			Ddim_Print(("Error DDIM_User_Set_Flg!! ret = 0x%x\n", ret));
		}
	}
	else {
		// Slave
		if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
			(*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, DdI2cCtrl_RECV_FROM_MASTER_ERROR, DdI2c_DONT_CARE);
		}
	}
}

// 0x03:Arbitrationlost, unaddressed slave mode entered
static VOID dd_i2c_st_mode_IDLARL_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_Error[ch] = DdI2c_ARBITRATION_LOST;

	Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));

	dd_i2c_error_occur(self, ch);
}

// 0x05:Slave address sent, negative ACK
static VOID dd_i2c_st_mode_MTADNA_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_Error[ch] = DdI2c_COMM_ERROR;

	/* Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__)); */

	dd_i2c_error_occur(self, ch);
}

// 0x09:Slave address sent, negative ACK
static VOID dd_i2c_st_mode_MRADNA_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_Error[ch] = DdI2c_COMM_ERROR;

	Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));

	dd_i2c_error_occur(self, ch);
}

// 0x07:Data byte sent, negative ACK
static VOID dd_i2c_st_mode_MTDANA_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_Error[ch] = DdI2c_COMM_ERROR;

	Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));

	dd_i2c_error_occur(self, ch);
}

// 0x1F:Invalid start or stop condition detected
static VOID dd_i2c_st_mode_BERROR_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_Error[ch] = DdI2c_BUS_ERROR;

	Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));

	dd_i2c_error_occur(self, ch);
}

// Timeout Error
static VOID dd_i2c_st_mode_TERR_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_Error[ch] = DdI2c_TIMEOUT;

	Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));

	dd_i2c_error_occur(self, ch);
}

//////////////////////////////////
///// Master Start condition /////
//////////////////////////////////
// 0x01:Start condition generated
static VOID dd_i2c_st_mode_STDONE_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->gDD_I2C_State[ch] == DdI2c_STATE_IDLE){
		switch(priv->gDD_I2C_Next_Event[ch]){
			case DdI2c_EVENT_START_READ:		// FALL THROUGH
			case DdI2c_EVENT_START_WRITE:
				// check START bit (Start condition send)
				if (IO_PERI.I2C[ch].CTL1.bit.START == 1) {
					priv->gDD_I2C_Error[ch] = DdI2c_COMM_ERROR;
					Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
					dd_i2c_error_occur(self, ch);
					break;
				}
				
				// Send slave address
				if(dd_i2c_ctrl_get_master_dest_slave_addr_len(priv->i2cCtrl, ch) == DdI2cCtrl_ADDR_LEN_7){
					// 7 bit address
					IO_PERI.I2C[ch].SDAT.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST);
					if(priv->gDD_I2C_Next_Event[ch] == DdI2c_EVENT_START_READ){
						// Read
						priv->gDD_I2C_State[ch] = DdI2c_STATE_RECEIVING_DATA;
						priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_RECEIVE;
					}
					else{
						// Write
						priv->gDD_I2C_State[ch] = DdI2c_STATE_SENDING_DATA;
						priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_SEND;
					}
				}
				else {	// DdI2cCtrl_ADDR_LEN_10
					// 10 bit upper address
					IO_PERI.I2C[ch].SDAT.word = (dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST) & 0xFE);
					priv->gDD_I2C_State[ch] = DdI2c_STATE_SENDING_ADDRESS;
				}

				// Clear ST.INT (release SCK)
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
				Dd_ARM_Dsb_Pou();
				break;
		}

	}
}

// 0x02:Repeated start condition generated
static VOID dd_i2c_st_mode_RSDONE_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->gDD_I2C_State[ch] == DdI2c_STATE_END){
		switch(priv->gDD_I2C_Next_Event[ch]){
			case DdI2c_EVENT_START_READ:		// FALL THROUGH
			case DdI2c_EVENT_START_WRITE:
				// check START bit (Start condition send)
				if (IO_PERI.I2C[ch].CTL1.bit.START == 1) {
					priv->gDD_I2C_Error[ch] = DdI2c_COMM_ERROR;
					Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
					dd_i2c_error_occur(self, ch);
					break;
				}
				
				IO_PERI.I2C[ch].SDAT.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST);

				if(dd_i2c_ctrl_get_master_dest_slave_addr_len(priv->i2cCtrl, ch) == DdI2cCtrl_ADDR_LEN_7){
					// 7 bit address
					if(priv->gDD_I2C_Next_Event[ch] == DdI2c_EVENT_START_READ){
						// Read
						priv->gDD_I2C_State[ch] = DdI2c_STATE_RECEIVING_DATA;
						priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_RECEIVE;
					}
					else {
						// Write
						priv->gDD_I2C_State[ch] = DdI2c_STATE_SENDING_DATA;
						priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_SEND;
					}
				}
				else {	// DdI2cCtrl_ADDR_LEN_10
					// 10 bit address
					if(priv->gDD_I2C_Next_Event[ch] == DdI2c_EVENT_START_READ){
						// Read
						priv->gDD_I2C_State[ch] = DdI2c_STATE_RECEIVING_DATA;
						priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_RECEIVE;
					}
					else {
						// Write
						priv->gDD_I2C_State[ch] = DdI2c_STATE_SENDING_ADDRESS;
					}
				}

				// Clear ST.INT (release SCK)
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
	else if(priv->gDD_I2C_State[ch] == DdI2c_STATE_SENDING_ADDRESS){
		switch(priv->gDD_I2C_Next_Event[ch]){
			case DdI2c_EVENT_RECEIVE:		// FALL THROUGH
				IO_PERI.I2C[ch].SDAT.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST);

				if(dd_i2c_ctrl_get_master_dest_slave_addr_len(priv->i2cCtrl, ch) == DdI2cCtrl_ADDR_LEN_10){
					// 10 bit address
					priv->gDD_I2C_State[ch] = DdI2c_STATE_RECEIVING_DATA;
					priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_RECEIVE;
				}

				// Clear ST.INT (release SCK)
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
	else if(priv->gDD_I2C_State[ch] == DdI2c_STATE_SENDING_DATA){
		switch(priv->gDD_I2C_Next_Event[ch]){
			case DdI2c_EVENT_SEND:
				IO_PERI.I2C[ch].SDAT.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST);

				if(dd_i2c_ctrl_get_master_dest_slave_addr_len(priv->i2cCtrl, ch) == DdI2cCtrl_ADDR_LEN_7){
						// Write
						priv->gDD_I2C_State[ch] = DdI2c_STATE_SENDING_DATA;
						priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_SEND;
				}
				// Clear ST.INT (release SCK)
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

////////////////////////////////
///// Master Transmit Mode /////
////////////////////////////////
// Send data to slave
static VOID dd_i2c_send_data_to_slave(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	UCHAR* sendData;
	UINT32 send_count;

	sendData = (UCHAR*)priv->gDD_I2C_Data[ch];
	send_count = priv->gDD_I2C_Data_Count[ch];

	if(send_count < priv->gDD_I2C_Data_Num[ch]){
		// Start send
		IO_PERI.I2C[ch].SDAT.word = sendData[send_count];
		send_count++;

		priv->gDD_I2C_Data_Count[ch] = send_count;

		// Check end of send
		if(send_count == priv->gDD_I2C_Data_Num[ch]){
			// Check PEC enable
			if((send_count + 1) == priv->gDD_I2C_PEC_Byte_Num[ch]){
				// Set PEC Next
				IO_PERI.I2C[ch].CST.bit.PECNEXT = 1;
				Dd_ARM_Dsb_Pou();

				// Sending PEC byte
				priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_SEND_PEC;
			}
			else {
				// End of send
				priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_END_RW;
			}
		}

		// Clear ST.INT (release SCK)
		IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
		Dd_ARM_Dsb_Pou();
	}
	else{
		// Clear ST.INT (release SCK)
//		IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;		// Not clear for the Repeat Start Condition or Stop Condition
//		Dd_ARM_Dsb_Pou();
	}
}

// 0x04:Slave address sent, positive ACK
static VOID dd_i2c_st_mode_MTADPA_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->gDD_I2C_State[ch] == DdI2c_STATE_SENDING_DATA){
		switch(priv->gDD_I2C_Next_Event[ch]){
			case DdI2c_EVENT_SEND:
				// Send Data
				dd_i2c_send_data_to_slave(self, ch);
				break;

			case DdI2c_EVENT_SEND_PEC:
				// End of send
				priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_END_RW;

				// Clear PEC Next
				IO_PERI.I2C[ch].CST.bit.PECNEXT = 0;

				// Clear ST.INT (release SCK)
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
	else if(priv->gDD_I2C_State[ch] == DdI2c_STATE_SENDING_ADDRESS){
		switch(priv->gDD_I2C_Next_Event[ch]){
			case DdI2c_EVENT_START_WRITE:
				// Send 10 bit lower address
				IO_PERI.I2C[ch].SDAT.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_2ND);
				Dd_ARM_Dsb_Pou();

				// Go to send data state
				priv->gDD_I2C_State[ch] = DdI2c_STATE_SENDING_DATA;
				priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_SEND;

				// Clear ST.INT (release SCK)
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				Dd_ARM_Dsb_Pou();
				break;

			case DdI2c_EVENT_START_READ:
				// Send 10 bit lower address
				IO_PERI.I2C[ch].SDAT.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_2ND);
				Dd_ARM_Dsb_Pou();

				// Keep state
				priv->gDD_I2C_Next_Event[ch] = DdI2c_EVENT_RECEIVE;

				// Clear ST.INT (release SCK)
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

// 0x06:Data byte sent, positive ACK
static VOID dd_i2c_st_mode_MTDAPA_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	DDIM_USER_ER ret = D_DDIM_USER_E_OK;

	if(priv->gDD_I2C_State[ch] == DdI2c_STATE_SENDING_DATA){
		switch(priv->gDD_I2C_Next_Event[ch]){
			case DdI2c_EVENT_SEND:
				// Send Data
				dd_i2c_send_data_to_slave(self, ch);
				break;

			case DdI2c_EVENT_END_RW:
				// End send
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;	// Pause interrupt because INT has not been cleared
				// Clear ST.INT (release SCK)
//				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;		// Not clear for the Repeat Start Condition or Stop Condition
				Dd_ARM_Dsb_Pou();

				priv->gDD_I2C_State[ch] = DdI2c_STATE_END;

				ret = DDIM_User_Set_Flg(FID_DD_I2C, dd_i2c_get_event_flg(self, ch));
				if(ret != D_DDIM_USER_E_OK){
					Ddim_Print(("Error DDIM_User_Set_Flg!! ret = 0x%x\n", ret));
				}
				break;

			default:
				// fail safe
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
	else if(priv->gDD_I2C_State[ch] == DdI2c_STATE_SENDING_ADDRESS){
		switch(priv->gDD_I2C_Next_Event[ch]){
			case DdI2c_EVENT_RECEIVE:
				// Resend 10 bit upper address and Read indicator
				IO_PERI.I2C[ch].SDAT.word = dd_i2c_ctrl_get_slave_addr_byte(priv->i2cCtrl, ch, DdI2cCtrl_ADDR_BYTE_1ST);
				Dd_ARM_Dsb_Pou();

				// Generate the Restart condition
				IO_PERI.I2C[ch].CTL1.bit.START	= 1;
				Dd_ARM_Dsb_Pou();

				// Clear ST.INT (release SCK)
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

///////////////////////////////
///// Master Receive Mode /////
///////////////////////////////
// Receive data from slave
static VOID dd_i2c_receive_data_from_slave(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	UCHAR* recv_data;
	UINT32 recv_count;
	DDIM_USER_ER ret = D_DDIM_USER_E_OK;

	recv_data = (UCHAR*)priv->gDD_I2C_Data[ch];
	recv_count = priv->gDD_I2C_Data_Count[ch];

	if(recv_count < priv->gDD_I2C_Data_Num[ch]){
		// Continue receive
		if(recv_count != 0){
			recv_data[recv_count-1] = (UCHAR)IO_PERI.I2C[ch].SDAT.word;		// ToDo
		}
		recv_count++;
		priv->gDD_I2C_Data_Count[ch] = recv_count;

		if(recv_count < priv->gDD_I2C_Data_Num[ch]){
			if((recv_count + 1) == priv->gDD_I2C_Data_Num[ch]){
				// next receive data is last. send no ack
				IO_PERI.I2C[ch].CTL1.bit.ACK = 1;

				// Check PEC enable
				if(recv_count == priv->gDD_I2C_PEC_Byte_Num[ch]){
					// Set PEC Next
					IO_PERI.I2C[ch].CST.bit.PECNEXT = 1;
					Dd_ARM_Dsb_Pou();
				}
			}
			else {
				// send ack
				IO_PERI.I2C[ch].CTL1.bit.ACK = 0;
			}

			// Clear ST.INT (release SCK)
			IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
			Dd_ARM_Dsb_Pou();
		}
		else {
			// End of receive
			if (priv->gDD_I2C_Data_Count[ch] == (priv->gDD_I2C_PEC_Byte_Num[ch] + 1)){
				// Check PEC Fault Error
				if(IO_PERI.I2C[ch].CST.bit.PECFAULT != 0){
					priv->gDD_I2C_Error[ch] = DdI2c_PEC_ERROR;
					Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
					dd_i2c_error_occur(self, ch);
				}
			}
			else {
				priv->gDD_I2C_Next_Event[ch]	= DdI2c_EVENT_END_RW;
				priv->gDD_I2C_State[ch]		= DdI2c_STATE_END;

				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;	// Pause interrupt because INT has not been cleared
//				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;		// Not clear for the Repeat Start Condition or Stop Condition
				Dd_ARM_Dsb_Pou();

				ret = DDIM_User_Set_Flg(FID_DD_I2C, dd_i2c_get_event_flg(self, ch));
				if(ret != D_DDIM_USER_E_OK){
					Ddim_Print(("Error DDIM_User_Set_Flg!! ret = 0x%x\n", ret));
				}
			}

			// Clear ST.INT (release SCK)
//			IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;		// Not clear for the Repeat Start Condition or Stop Condition
//			Dd_ARM_Dsb_Pou();
		}
	}
	else{
		// Clear ST.INT (release SCK)
//		IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;		// Not clear for the Repeat Start Condition or Stop Condition
//		Dd_ARM_Dsb_Pou();
	}
}

// 0x08:Slave address sent, positive ACK
static VOID dd_i2c_st_mode_MRADPA_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->gDD_I2C_State[ch] == DdI2c_STATE_RECEIVING_DATA){
		switch(priv->gDD_I2C_Next_Event[ch]){
			case DdI2c_EVENT_RECEIVE:
				// Receive Data
				dd_i2c_receive_data_from_slave(self, ch);
				break;

			default:
				// fail safe
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

// 0x0A:Data byte received, positive ACK
static VOID dd_i2c_st_mode_MRDAPA_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->gDD_I2C_State[ch] == DdI2c_STATE_RECEIVING_DATA){
		switch(priv->gDD_I2C_Next_Event[ch]){
			case DdI2c_EVENT_RECEIVE:
				// Receive Data
				dd_i2c_receive_data_from_slave(self, ch);
				break;

			default:
				// fail safe
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

// 0x0B:Data byte received, negative ACK
static VOID dd_i2c_st_mode_MRDANA_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(priv->gDD_I2C_State[ch] == DdI2c_STATE_RECEIVING_DATA){
		switch(priv->gDD_I2C_Next_Event[ch]){
			case DdI2c_EVENT_RECEIVE:
				// Receive Data
				dd_i2c_receive_data_from_slave(self, ch);
				break;

			case DdI2c_EVENT_END_RW:
				// End receive
				priv->gDD_I2C_State[ch] = DdI2c_STATE_END;

				// Clear ST.INT (release SCK)
//				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;		// Not clear for the Repeat Start Condition or Stop Condition
//				Dd_ARM_Dsb_Pou();
				break;

			default:
				// fail safe
				IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
				IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
				Dd_ARM_Dsb_Pou();
				break;
		}
	}
}

//////////////////////////////
///// Slave Receive Mode /////
//////////////////////////////
// Notify slave address specified
static VOID dd_i2c_notify_slave_address_specified(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
//	DdI2cSlaveAction action;

	if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
		// Notify slave address specified to Callback function
#if 0
		action = (*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, DdI2cCtrl_RECV_FROM_MASTER_ADDRESS, (UCHAR)IO_PERI.I2C[ch].SDAT.word);

		switch(action.actionMode){
			case DdI2c_SEND_ACK_MASTER:
				// send ack
				IO_PERI.I2C[ch].CTL1.bit.ACK = 0;
				break;
			case DdI2c_SEND_NO_ACK_MASTER:
				// send no ack
				IO_PERI.I2C[ch].CTL1.bit.ACK = 1;
				break;
			default:
				break;
		}
#else
		(*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, DdI2cCtrl_RECV_FROM_MASTER_ADDRESS, (UCHAR)IO_PERI.I2C[ch].SDAT.word);
#endif
	}

	// Clear ST.INT (release SCK)
	IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x10:Slave address received, positive ACK
static VOID dd_i2c_st_mode_SRADPA_proc(DdI2c *self, UCHAR ch)
{
	dd_i2c_notify_slave_address_specified(self, ch);
}

// 0x11:Slave address received after arbitration loss, positive ACK
static VOID dd_i2c_st_mode_SRAAPA_proc(DdI2c *self, UCHAR ch)
{
	dd_i2c_notify_slave_address_specified(self, ch);
}

static VOID dd_i2c_receive_data_from_master(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	DdI2cSlaveAction action;
	I2cRecvFromMaster receive_sig = DdI2cCtrl_RECV_FROM_MASTER_DATA;

	if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
		priv->gDD_I2C_Data_Count[ch]++;

		// Check PEC enable
		if(priv->gDD_I2C_Data_Count[ch] == priv->gDD_I2C_PEC_Byte_Num[ch]){
			// Set PEC Next
			IO_PERI.I2C[ch].CST.bit.PECNEXT = 1;
			Dd_ARM_Dsb_Pou();
		}
		else if (priv->gDD_I2C_Data_Count[ch] == (priv->gDD_I2C_PEC_Byte_Num[ch] + 1)){
			// Check PEC Fault Error
			if(IO_PERI.I2C[ch].CST.bit.PECFAULT != 0){
				receive_sig = DdI2cCtrl_RECV_FROM_MASTER_ERROR;
				priv->gDD_I2C_Error[ch] = DdI2c_PEC_ERROR;

				Ddim_Print(("DD_I2C ERR:ch=%d, line=%d\n", ch, __LINE__));
			}
		}

		// Receive data from master
		action = (*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, receive_sig, (UCHAR)IO_PERI.I2C[ch].SDAT.word);

		switch(action.actionMode){
			case DdI2c_SEND_ACK_MASTER:
				// Continue receive data
				IO_PERI.I2C[ch].CTL1.bit.ACK = 0;
				break;
			case DdI2c_SEND_NO_ACK_MASTER:
				// End receive data
				IO_PERI.I2C[ch].CTL1.bit.ACK = 1;
				break;
			default:
				break;
		}
	}

	// Clear ST.INT (release SCK)
	IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x12:Data byte received, positive ACK
static VOID dd_i2c_st_mode_SRDAPA_proc(DdI2c *self, UCHAR ch)
{
	dd_i2c_receive_data_from_master(self, ch);
}

// 0x13:Data byte received, negative ACK
static VOID dd_i2c_st_mode_SRDANA_proc(UCHAR ch)
{
	// Clear ST.INT (release SCK)
	IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x1C:Slave mode stop condition detected
static VOID dd_i2c_st_mode_SSTOP_proc(UCHAR ch)
{
	// Clear ST.INT (release SCK)
	IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x1D:Slave address received after arbitration loss, positive ACK
static VOID dd_i2c_st_mode_SGADPA_proc(DdI2c *self, UCHAR ch)
{
	dd_i2c_notify_slave_address_specified(self, ch);
}

// 0x1E:Slave address received after arbitration loss, positive ACK
static VOID dd_i2c_st_mode_SGAAPA_proc(DdI2c *self, UCHAR ch)
{
	dd_i2c_notify_slave_address_specified(self, ch);
}

///////////////////////////////
///// Slave Transmit Mode /////
///////////////////////////////
// Send data to master
static VOID dd_i2c_send_data_to_master(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);
	DdI2cSlaveAction action;

	if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
		// Detect ACK
		// Send data to master
		action = (*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, DdI2cCtrl_RECV_FROM_MASTER_ACK, DdI2c_DONT_CARE);

		if(action.actionMode == DdI2c_SEND_DATA_2_MASTER){
			// Send data
			IO_PERI.I2C[ch].SDAT.word = action.sendData;
			Dd_ARM_Dsb_Pou();

			priv->gDD_I2C_Data_Count[ch]++;

			if(priv->gDD_I2C_Data_Count[ch] == priv->gDD_I2C_PEC_Byte_Num[ch]){
				// Set PEC Next
				IO_PERI.I2C[ch].CST.bit.PECNEXT = 1;
				Dd_ARM_Dsb_Pou();
			}
		}
		else{
			// Error
			Ddim_Print(("I2C Slave Action Mode is invalid!! actionMode = %d\n", action.actionMode));
		}
	}

	// Clear ST.INT (release SCK)
	IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x14:Slave address received, positive ACK
static VOID dd_i2c_st_mode_STADPA_proc(DdI2c *self, UCHAR ch)
{
	dd_i2c_init_pec_info(self, ch);

	dd_i2c_send_data_to_master(self, ch);
}

// 0x15:Slave address received after arbitration loss, positive ACK
static VOID dd_i2c_st_mode_STAAPA_proc(DdI2c *self, UCHAR ch)
{
	dd_i2c_init_pec_info(self, ch);

	dd_i2c_send_data_to_master(self, ch);
}

// 0x16:Data byte received, positive ACK
static VOID dd_i2c_st_mode_STDAPA_proc(DdI2c *self, UCHAR ch)
{
	dd_i2c_send_data_to_master(self, ch);
}

// 0x17:Data byte received, negative ACK
static VOID dd_i2c_st_mode_STDANA_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
		// No detect ACK
		(*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, DdI2cCtrl_RECV_FROM_MASTER_NO_ACK, DdI2c_DONT_CARE);
	}

	// Clear ST.INT (release SCK)
	IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
	Dd_ARM_Dsb_Pou();
}

// 0x18:Alart response address received, positive ACK
static VOID dd_i2c_st_mode_SATADP_proc(DdI2c *self, UCHAR ch)
{
	dd_i2c_init_pec_info(self, ch);

	dd_i2c_send_data_to_master(self, ch);
}

// 0x19:Alart response address received after arbitration loss, positive ACK
static VOID dd_i2c_st_mode_SATAAP_proc(DdI2c *self, UCHAR ch)
{
	dd_i2c_init_pec_info(self, ch);

	dd_i2c_send_data_to_master(self, ch);
}

// 0x1A:Addressed With Alart response address, data byte send, positive ACK
static VOID dd_i2c_st_mode_SATDAP_proc(DdI2c *self, UCHAR ch)
{
	dd_i2c_send_data_to_master(self, ch);
}

// 0x1B:Addressed With Alart response address, data byte send, negative ACK
static VOID dd_i2c_st_mode_SATDAN_proc(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	if(dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch) != NULL){
		// No detect ACK
		(*dd_i2c_ctrl_get_slave_callback(priv->i2cCtrl, ch))(ch, DdI2cCtrl_RECV_FROM_MASTER_NO_ACK, DdI2c_DONT_CARE);
	}

	// Clear ST.INT (release SCK)
	IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
	Dd_ARM_Dsb_Pou();
}

// Get event flag of the ch specified
UINT32 dd_i2c_get_event_flg(DdI2c *self, UCHAR ch)
{
	UINT32 ret;

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
VOID dd_i2c_init_pec_info(DdI2c *self, UCHAR ch)
{
	// Init PEC info
	IO_PERI.I2C[ch].CST.bit.PECNEXT = 0;
}

// Terminate the I2C.
VOID dd_i2c_terminate(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_State[ch] = DdI2c_STATE_IDLE;

	// Clear EN
	IO_PERI.I2C[ch].CTL2.bit.ENABLE = 0;
	Dd_ARM_Dsb_Pou();
}

// Get Test SDA.
INT32 dd_i2c_get_test_sda(DdI2c *self, UCHAR ch, UCHAR* sda)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if((ch >= DdI2c_CH_MAX) || (sda == NULL)){
		Ddim_Assertion(("Dd_I2C_Get_Test_SDA() error. sda is NULL or ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	*sda = IO_PERI.I2C[ch].CST.bit.TSDA;

	return ret;
}

// Get Error Cause.
UINT32 dd_i2c_get_error_cause(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("Dd_I2C_Get_Error_Cause() error. ch is abnormal.\n"));
		return 0;
	}
#endif

	return priv->gDD_I2C_Error[ch];
}

// Set Toggle SCL.
INT32 dd_i2c_set_toggle_scl(DdI2c *self, UCHAR ch)
{
	INT32 ret = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("Dd_I2C_Set_Toggle_SCL() error. ch is abnormal.\n"));
		return DdI2c_INPUT_PARAM_ERROR;
	}
#endif

	IO_PERI.I2C[ch].CST.bit.TGSCL = 1;
	Dd_ARM_Dsb_Pou();

	return ret;
}

// Intterupt handler.
VOID dd_i2c_int_handler(DdI2c *self, UCHAR ch)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdI2c_CH_MAX){
		Ddim_Assertion(("Dd_I2C_Int_Handler() error. ch is abnormal.\n"));
		return ;
	}
#endif

#ifdef DdI2c_DEBUG
	printf("IN:I2C[%d].ST.MODE=0x%02X, priv->gDD_I2C_State=%d, priv->gDD_I2C_Next_Event=%d\n", ch, IO_PERI.I2C[ch].ST.bit.MODE, priv->gDD_I2C_State[ch], priv->gDD_I2C_Next_Event[ch]);
#endif

	if(IO_PERI.I2C[ch].CST.bit.TERR == 1){
		// Timeout Error
		dd_i2c_st_mode_TERR_proc(self, ch);
	}

	switch(IO_PERI.I2C[ch].ST.bit.MODE){
		//////////////////////////////////
		///// Master Start condition /////
		//////////////////////////////////
		case E_DD_I2C_ST_MODE_STDONE:		// 0x01:Start condition generated
			dd_i2c_st_mode_STDONE_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_RSDONE:		// 0x02:Repeated start condition generated
			dd_i2c_st_mode_RSDONE_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_IDLARL:		// 0x03:Arbitrationlost, unaddressed slave mode entered
			dd_i2c_st_mode_IDLARL_proc(self, ch);
			break;

		////////////////////////////////
		///// Master Transmit Mode /////
		////////////////////////////////
		case E_DD_I2C_ST_MODE_MTADPA:		// 0x04:Slave address sent, positive ACK
			dd_i2c_st_mode_MTADPA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_MTADNA:		// 0x05:Slave address sent, negative ACK
			dd_i2c_st_mode_MTADNA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_MTDAPA:		// 0x06:Data byte sent, positive ACK
			dd_i2c_st_mode_MTDAPA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_MTDANA:		// 0x07:Data byte sent, negative ACK
			dd_i2c_st_mode_MTDANA_proc(self, ch);
			break;

		///////////////////////////////
		///// Master Receive Mode /////
		///////////////////////////////
		case E_DD_I2C_ST_MODE_MRADPA:		// 0x08:Slave address sent, positive ACK
			dd_i2c_st_mode_MRADPA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_MRADNA:		// 0x09:Slave address sent, negative ACK
			dd_i2c_st_mode_MRADNA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_MRDAPA:		// 0x0A:Data byte received, positive ACK
			dd_i2c_st_mode_MRDAPA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_MRDANA:		// 0x0B:Data byte received, negative ACK
			dd_i2c_st_mode_MRDANA_proc(self, ch);
			break;

		//////////////////////////////
		///// Slave Receive Mode /////
		//////////////////////////////
		case E_DD_I2C_ST_MODE_SRADPA:		// 0x10:Slave address received, positive ACK
			dd_i2c_st_mode_SRADPA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_SRAAPA:		// 0x11:Slave address received after arbitration loss, positive ACK
			dd_i2c_st_mode_SRAAPA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_SRDAPA:		// 0x12:Data byte received, positive ACK
			dd_i2c_st_mode_SRDAPA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_SRDANA:		// 0x13:Data byte received, negative ACK
			dd_i2c_st_mode_SRDANA_proc(ch);
			break;
		case E_DD_I2C_ST_MODE_SSTOP:		// 0x1C:Slave mode stop condition detected
			dd_i2c_st_mode_SSTOP_proc(ch);
			break;
		case E_DD_I2C_ST_MODE_SGADPA:		// 0x1D:Slave address received after arbitration loss, positive ACK
			dd_i2c_st_mode_SGADPA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_SGAAPA:		// 0x1E:Slave address received after arbitration loss, positive ACK
			dd_i2c_st_mode_SGAAPA_proc(self, ch);
			break;

		///////////////////////////////
		///// Slave Transmit Mode /////
		///////////////////////////////
		case E_DD_I2C_ST_MODE_STADPA:		// 0x14:Slave address received, positive ACK
			dd_i2c_st_mode_STADPA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_STAAPA:		// 0x15:Slave address received after arbitration loss, positive ACK
			dd_i2c_st_mode_STAAPA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_STDAPA:		// 0x16:Data byte received, positive ACK
			dd_i2c_st_mode_STDAPA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_STDANA:		// 0x17:Data byte received, negative ACK
			dd_i2c_st_mode_STDANA_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_SATADP:		// 0x18:Alart response address received, positive ACK
			dd_i2c_st_mode_SATADP_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_SATAAP:		// 0x19:Alart response address received after arbitration loss, positive ACK
			dd_i2c_st_mode_SATAAP_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_SATDAP:		// 0x1A:Addressed With Alart response address, data byte send, positive ACK
			dd_i2c_st_mode_SATDAP_proc(self, ch);
			break;
		case E_DD_I2C_ST_MODE_SATDAN:		// 0x1B:Addressed With Alart response address, data byte send, negative ACK
			dd_i2c_st_mode_SATDAN_proc(self, ch);
			break;

		/////////////////
		///// Error /////
		/////////////////
		case E_DD_I2C_ST_MODE_BERROR:		// 0x1F:Invalid start or stop condition detected
			dd_i2c_st_mode_BERROR_proc(self, ch);
			break;
		default:
			// fail safe
			IO_PERI.I2C[ch].CTL1.bit.CLRST = 1;
			IO_PERI.I2C[ch].CTL1.bit.INTEN	= 0;
			Dd_ARM_Dsb_Pou();
			break;
	}
}

INT32 dd_i2c_open(DdI2c *self, UCHAR ch, INT32 timeout)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_open(priv->i2cCtrl, ch, timeout);
}

INT32 dd_i2c_close(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_close(priv->i2cCtrl, ch);
}

INT32 dd_i2c_start_master(DdI2c *self, UCHAR ch, const DdI2cStartInfo* const start_info)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_start_master(priv->i2cCtrl, ch, start_info);
}

INT32 dd_i2c_stop_master(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_stop_master(priv->i2cCtrl, ch);
}

INT32 dd_i2c_start_slave(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_start_slave(priv->i2cCtrl, ch);
}

INT32 dd_i2c_stop_slave(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_stop_slave(priv->i2cCtrl, ch);
}

INT32 dd_i2c_ctrl_master(DdI2c *self, UCHAR ch, const DdI2cCtrlMaster* const ctrl_master)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_ctrl_master(priv->i2cCtrl, ch, ctrl_master);
}

INT32 dd_i2c_get_ctrl_master(DdI2c *self, UCHAR ch, DdI2cCtrlMaster* const ctrl_master)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_get_ctrl_master(priv->i2cCtrl, ch, ctrl_master);
}

INT32 dd_i2c_ctrl_slave(DdI2c *self, UCHAR ch, const DdI2cCtrlSlave* const ctrl_slave)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_ctrl_slave(priv->i2cCtrl, ch, ctrl_slave);
}

INT32 dd_i2c_get_ctrl_slave(DdI2c *self, UCHAR ch, DdI2cCtrlSlave* const ctrl_slave)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_get_ctrl_slave(priv->i2cCtrl, ch, ctrl_slave);
}

INT32 dd_i2c_ctrl_smbus(DdI2c *self, UCHAR ch, const DdI2cCtrlSmbus* const ctrl_smbus)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_ctrl_smbus(priv->i2cCtrl, ch, ctrl_smbus);
}

INT32 dd_i2c_get_ctrl_smbus(DdI2c *self, UCHAR ch, DdI2cCtrlSmbus* const ctrl_smbus)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_get_ctrl_smbus(priv->i2cCtrl, ch, ctrl_smbus);
}

#ifdef CO_DDIM_UTILITY_USE
INT32 dd_i2c_set_scl(DdI2c *self, UCHAR ch, UCHAR scl)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_set_scl(priv->i2cCtrl, ch, scl);
}

INT32 dd_i2c_get_scl(DdI2c *self, UCHAR ch, UCHAR* scl)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return dd_i2c_ctrl_get_scl(priv->i2cCtrl, ch, scl);
}

#endif

DdI2cState dd_i2c_get_state(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return priv->gDD_I2C_State[ch];
}

void dd_i2c_set_state(DdI2c *self, UCHAR ch, DdI2cState state)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_State[ch] = state;
}

void dd_i2c_set_next_event(DdI2c *self, UCHAR ch, DdI2cEvent nextEvent)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_Next_Event[ch] = nextEvent;
}

UINT32 dd_i2c_get_error(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return priv->gDD_I2C_Error[ch];
}

void dd_i2c_set_error(DdI2c *self, UCHAR ch, UINT32 err)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_Error[ch] = err;
}

void dd_i2c_set_data_count(DdI2c *self, UCHAR ch, UINT32 dataCount)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_Data_Count[ch] = dataCount;
}

void dd_i2c_set_data(DdI2c *self, UCHAR ch, UCHAR* data)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_Data[ch] = data;
}

void dd_i2c_set_data_num(DdI2c *self, UCHAR ch, UINT32 dataNum)

{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_Data_Num[ch] = dataNum;
}

UINT32 dd_i2c_get_pec_byte_num(DdI2c *self, UCHAR ch)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	return priv->gDD_I2C_PEC_Byte_Num[ch];
}

void dd_i2c_set_pec_byte_num(DdI2c *self, UCHAR ch, UINT32 pecByteNum)
{
	DdI2cPrivate *priv = DD_I2C_GET_PRIVATE(self);

	priv->gDD_I2C_PEC_Byte_Num[ch] = pecByteNum;
}

DdI2c* dd_i2c_get(void)
{
	static DdI2c* self = NULL;

	if(!self)
		self = k_object_new_with_private(DD_TYPE_I2C, sizeof(DdI2cPrivate));

	return self;
}
