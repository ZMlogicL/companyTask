/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-05
*@author              :jianghaodong
*@brief               :CtDdI2c类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include <stdlib.h>
#include <string.h>
#include "dd_top.h"
#include "driver_common.h"
#include "dd_i2c.h"
#include "ct_dd_i2c.h"
#include "dd_gic.h"
#include "ddim_user_custom.h"
#include "peripheral.h"

#include "ctddi2c.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdI2c, ct_dd_i2c);
#define CT_DD_I2C_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdI2cPrivate,CT_TYPE_DD_I2C))

#define CtDdI2c_D_CT_DD_I2C_SLAVE_ADDRESS_7				(0x60)			//7 bit Slave address
#define CtDdI2c_D_CT_DD_I2C_SLAVE_ADDRESS_10			(0x362)			//10 bit Slave address
#define CtDdI2c_D_CT_DD_I2C_SLAVE_ADDRESS_7_ERR_TEST	(0x65)			//7 bit Slave address slave error test

#define CtDdI2c_D_CT_DD_I2C_MAX_BUFFER_SIZE				(0x200)			//Master send address
#define CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN				(100)			//Max length of data
#define CtDdI2c_D_CT_DD_I2C_MAX_DATA_NUM				(10)			//Max number of data
#define CtDdI2c_D_CT_DD_I2C_TEST_DATA_NUM				(2)				//Number of test data

#define CtDdI2c_D_CT_DD_I2C_MASTER_SEND_ADDRESS			(0xA7000000)	//Master send address
#define CtDdI2c_D_CT_DD_I2C_MASTER_SEND_END_ADDRESS	\
(CtDdI2c_D_CT_DD_I2C_MASTER_SEND_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_BUFFER_SIZE)//Master send address end

#define CtDdI2c_D_CT_DD_I2C_MASTER_RECEIVE_ADDRESS (CtDdI2c_D_CT_DD_I2C_MASTER_SEND_END_ADDRESS)
//Master send address
#define CtDdI2c_D_CT_DD_I2C_MASTER_RECEIVE_END_ADDRESS	\
(CtDdI2c_D_CT_DD_I2C_MASTER_RECEIVE_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_BUFFER_SIZE)//Master send address

#define CtDdI2c_D_CT_DD_I2C_SLAVE_SEND_ADDRESS	\
(CtDdI2c_D_CT_DD_I2C_MASTER_RECEIVE_END_ADDRESS)//slave send address
#define CtDdI2c_D_CT_DD_I2C_SLAVE_SEND_END_ADDRESS	\
(CtDdI2c_D_CT_DD_I2C_SLAVE_SEND_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_BUFFER_SIZE)//slave send address end

#define CtDdI2c_D_CT_DD_I2C_SLAVE_RECEIVE_ADDRESS	\
(CtDdI2c_D_CT_DD_I2C_SLAVE_SEND_END_ADDRESS)//slave receive address
#define CtDdI2c_D_CT_DD_I2C_SLAVE_RECEIVE_END_ADDRESS	\
(CtDdI2c_D_CT_DD_I2C_SLAVE_RECEIVE_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_BUFFER_SIZE)//slave receive address end

#define CtDdI2c_D_DD_CT_I2C_WAIT_TIME	(3000)

struct _CtDdI2cPrivate
{

};

static kuchar* S_GCT_DD_I2C_MASTER_SEND_ADDRESS = (kuchar*)CtDdI2c_D_CT_DD_I2C_MASTER_SEND_ADDRESS;
static kuchar* S_GCT_DD_I2C_MASTER_RECEIVE_ADDRESS = (kuchar*)CtDdI2c_D_CT_DD_I2C_MASTER_RECEIVE_ADDRESS;
static kuchar* S_GCT_DD_I2C_SLAVE_SEND_ADDRESS = (kuchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_SEND_ADDRESS;
static kuchar* S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS = (kuchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_RECEIVE_ADDRESS;

static kint32 S_GCT_DD_I2C_RECV_COUNTER = 0;
static kint32 S_GCT_DD_I2C_SEND_COUNTER = 0;

static T_DD_I2C_CTRL_MASTER	 S_GCT_DD_I2C_CTRL_MASTER;
static T_DD_I2C_CTRL_SLAVE	S_GCT_DD_I2C_CTRL_SLAVE;

/*
*DECLS
*/
#ifdef D_DD_I2C_PC_DEBUG
static void ctI2cRegisterDump( kuchar ch );
#endif

static void ctI2cCtrlMasterDump( const T_DD_I2C_CTRL_MASTER* ctrlMaster );
static void ctI2cCtrlSlaveDump( const T_DD_I2C_CTRL_SLAVE* ctrlSlave );
static void ctI2cCtrlSmbusDump( const T_DD_I2C_CTRL_SMBUS* ctrlSmbus );
#ifdef D_DD_I2C_PC_DEBUG
static void ctI2cStartInfoDump( const T_DD_I2C_START_INFO* startInfo );
#endif

static void ctDdI2cSetWriteTestData( kuint32 dataLen, kuchar* data[], kuint32 dataNum );
static void ctDdI2cSetReadTestData( kuint32 dataLen, kuchar* data[], kuint32 dataNum );
static kint32 ctDdI2cMasterStart( kuchar ch, T_DD_I2C_START_INFO* const startInfo, kuchar* data[], kuint32 dataNum );
static void ctDdI2cDataPrint( E_DD_I2C_RW_MODE mode, kuint32 dataNum, kuint32 dataLength, kuchar* data[] );
static void ctDdI2cMasterWriteTest( kuchar ch );
static void ctDdI2cMasterReadTest( kuchar ch );
static T_DD_I2C_SLAVE_ACTION ctDdI2c_cb( kuchar ch, E_DD_I2C_RECV_FROM_MASTER receiveSig, kuchar data );

/*
*IMPL
*/
static void ct_dd_i2c_constructor(CtDdI2c *self) 
{
}

static void ct_dd_i2c_destructor(CtDdI2c *self) 
{
}

#ifdef D_DD_I2C_PC_DEBUG
static void ctI2cRegisterDump( kuchar ch )
{
	Ddim_Print(("REGISTER WORD\n"));
	Ddim_Print((" IO_PERI.I2C[%d].SDAT.word = %08lX\n", ch, IO_PERI.I2C[ch].SDAT.word ));
	Ddim_Print((" IO_PERI.I2C[%d].ST.word   = %08lX\n", ch, IO_PERI.I2C[ch].ST.word   ));
	Ddim_Print((" IO_PERI.I2C[%d].CST.word  = %08lX\n", ch, IO_PERI.I2C[ch].CST.word  ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL1.word = %08lX\n", ch, IO_PERI.I2C[ch].CTL1.word ));
	Ddim_Print((" IO_PERI.I2C[%d].ADDR.word = %08lX\n", ch, IO_PERI.I2C[ch].ADDR.word ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL2.word = %08lX\n", ch, IO_PERI.I2C[ch].CTL2.word ));
	Ddim_Print((" IO_PERI.I2C[%d].TOPR.word = %08lX\n", ch, IO_PERI.I2C[ch].TOPR.word ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL3.word = %08lX\n", ch, IO_PERI.I2C[ch].CTL3.word ));
	Ddim_Print(("REGISTER BIT [SDAT]\n"));
	Ddim_Print((" IO_PERI.I2C[%d].SDAT.bit.DATA   = 0x%02lX\n", ch, IO_PERI.I2C[ch].SDAT.bit.DATA ));
	Ddim_Print(("REGISTER BIT [ST]\n"));
	Ddim_Print((" IO_PERI.I2C[%d].ST.bit.MODE     = 0x%02lX\n", ch, IO_PERI.I2C[ch].ST.bit.MODE ));
	Ddim_Print((" IO_PERI.I2C[%d].ST.bit.INT      = %d\n", ch, IO_PERI.I2C[ch].ST.bit.INT ));
	Ddim_Print(("REGISTER BIT [CST]\n"));
	Ddim_Print((" IO_PERI.I2C[%d].CST.bit.BB	  = %d\n", ch, IO_PERI.I2C[ch].CST.bit.BB      ));
	Ddim_Print((" IO_PERI.I2C[%d].CST.bit.TOCDIV  = %d\n", ch, IO_PERI.I2C[ch].CST.bit.TOCDIV  ));
	Ddim_Print((" IO_PERI.I2C[%d].CST.bit.TERR    = %d\n", ch, IO_PERI.I2C[ch].CST.bit.TERR    ));
	Ddim_Print((" IO_PERI.I2C[%d].CST.bit.TSDA    = %d\n", ch, IO_PERI.I2C[ch].CST.bit.TSDA    ));
	Ddim_Print((" IO_PERI.I2C[%d].CST.bit.TGSCL   = %d\n", ch, IO_PERI.I2C[ch].CST.bit.TGSCL   ));
	Ddim_Print((" IO_PERI.I2C[%d].CST.bit.PECNEXT = %d\n", ch, IO_PERI.I2C[ch].CST.bit.PECNEXT ));
	Ddim_Print((" IO_PERI.I2C[%d].CST.bit.PECFAULT = %d\n", ch, IO_PERI.I2C[ch].CST.bit.PECFAULT ));
	Ddim_Print(("REGISTER BIT [CTL1]\n"));
	Ddim_Print((" IO_PERI.I2C[%d].CTL1.bit.START  = %d\n", ch, IO_PERI.I2C[ch].CTL1.bit.START  ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL1.bit.STOP   = %d\n", ch, IO_PERI.I2C[ch].CTL1.bit.STOP   ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL1.bit.INTEN  = %d\n", ch, IO_PERI.I2C[ch].CTL1.bit.INTEN  ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL1.bit.ACK    = %d\n", ch, IO_PERI.I2C[ch].CTL1.bit.ACK    ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL1.bit.GCMEN  = %d\n", ch, IO_PERI.I2C[ch].CTL1.bit.GCMEN  ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL1.bit.SMBARE = %d\n", ch, IO_PERI.I2C[ch].CTL1.bit.SMBARE ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL1.bit.CLRST  = %d\n", ch, IO_PERI.I2C[ch].CTL1.bit.CLRST  ));
	Ddim_Print(("REGISTER BIT [ADDR]\n"));
	Ddim_Print((" IO_PERI.I2C[%d].ADDR.bit.ADDR	  = 0x%02lX\n", ch, IO_PERI.I2C[ch].ADDR.bit.ADDR ));
	Ddim_Print((" IO_PERI.I2C[%d].ADDR.bit.SAEN   = %d\n", ch, IO_PERI.I2C[ch].ADDR.bit.SAEN ));
	Ddim_Print(("REGISTER BIT [CTL2]\n"));
	Ddim_Print((" IO_PERI.I2C[%d].CTL2.bit.ENABLE = %d\n", ch, IO_PERI.I2C[ch].CTL2.bit.ENABLE ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL2.bit.SCLFRQ = %d\n", ch, IO_PERI.I2C[ch].CTL2.bit.SCLFRQ ));
	Ddim_Print(("REGISTER BIT [TOPR]\n"));
	Ddim_Print((" IO_PERI.I2C[%d].TOPR.bit.TOPR	  = %d\n", ch, IO_PERI.I2C[ch].TOPR.bit.TOPR ));
	Ddim_Print(("REGISTER BIT [CTL3]\n"));
	Ddim_Print((" IO_PERI.I2C[%d].CTL3.bit.S10ADR = 0x%02lX\n", ch, IO_PERI.I2C[ch].CTL3.bit.S10ADR ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL3.bit.S10EN  = %d\n", ch, IO_PERI.I2C[ch].CTL3.bit.S10EN  ));
	Ddim_Print((" IO_PERI.I2C[%d].CTL3.bit.HSCDIV = %d\n", ch, IO_PERI.I2C[ch].CTL3.bit.HSCDIV ));
}
#endif

static void ctI2cCtrlMasterDump( const T_DD_I2C_CTRL_MASTER* ctrlMaster )
{
	Ddim_Print(("T_DD_I2C_CTRL_MASTER\n"));
	Ddim_Print((" ctrlMaster.bps                 = %d\n", (E_DD_I2C_BPS)ctrlMaster->bps ));
	Ddim_Print((" ctrlMaster.dest_slave_addr_len = %d\n", (E_DD_I2C_ADDR_LEN)ctrlMaster->dest_slave_addr_len ));
	Ddim_Print((" ctrlMaster.dest_slave_addr     = 0x%04X\n", ctrlMaster->dest_slave_addr ));
}

static void ctI2cCtrlSlaveDump( const T_DD_I2C_CTRL_SLAVE* ctrlSlave )
{
	Ddim_Print(("T_DD_I2C_CTRL_SLAVE\n"));
	Ddim_Print((" ctrlSlave.own_slave_addr_len = %d\n", (E_DD_I2C_ADDR_LEN)ctrlSlave->own_slave_addr_len ));
	Ddim_Print((" ctrlSlave.own_slave_addr     = 0x%04X\n", ctrlSlave->own_slave_addr ));
	Ddim_Print((" ctrlSlave.global_call_en     = %d\n", ctrlSlave->global_call_en ));
	Ddim_Print((" ctrlSlave.callback           = 0x%08lX\n", (kulong)ctrlSlave->callback ));
}

static void ctI2cCtrlSmbusDump( const T_DD_I2C_CTRL_SMBUS* ctrlSmbus )
{
	Ddim_Print(("T_DD_I2C_CTRL_SMBUS\n"));
	Ddim_Print((" ctrlSmbus.alert_resp_en = %d\n", ctrlSmbus->alert_resp_en ));
	Ddim_Print((" ctrlSmbus.pec_num       = %d\n", ctrlSmbus->pec_num ));
	Ddim_Print((" ctrlSmbus.timeout_div   = %d\n", (E_DD_I2C_TO_DIV)ctrlSmbus->timeout_div ));
	Ddim_Print((" ctrlSmbus.timeout_presc = %d\n", ctrlSmbus->timeout_presc ));
}

#ifdef D_DD_I2C_PC_DEBUG
static void ctI2cStartInfoDump( const T_DD_I2C_START_INFO* startInfo )
{
	Ddim_Print(("T_DD_I2C_START_INFO\n"));
	Ddim_Print((" startInfo.rw_mode     = %d\n", startInfo->rw_mode ));
	Ddim_Print((" startInfo.rw_data_len = %d\n", startInfo->rw_data_len ));
	Ddim_Print((" startInfo.rw_data     = %d\n", startInfo->rw_data ));
	Ddim_Print((" startInfo.timeout     = %d\n", startInfo->timeout ));
}
#endif

static void ctDdI2cSetWriteTestData( kuint32 dataLen, kuchar* data[], kuint32 dataNum )
{
	kint32	num, i;

	// Set write data
	for( num = 0; num < dataNum; num++ ){
		if( num % 2 == 0 ){
			for( i = 0; i < dataLen; i++ ){
				*(data[num] + i) = (i + 1);
			}
		}
		else {
			for( i = 0; i < dataLen; i++ ){
				*(data[num] + i) = (dataLen - i);
			}
		}
	}
}

static void ctDdI2cSetReadTestData( kuint32 dataLen, kuchar* data[], kuint32 dataNum )
{
	kint32	num, i;

	// Set read data
	for( num = 0; num < dataNum; num++ ){
		if( num % 2 == 0 ){
			for( i = 0; i < dataLen; i++ ){
				*(data[num] + i) = (0xFF - i);
			}
		}
		else {
			for( i = 0; i < dataLen; i++ ){
				*(data[num] + i) = (0xFF - dataLen + i + 1);
			}
		}
	}
}

static kint32 ctDdI2cMasterStart( kuchar ch, T_DD_I2C_START_INFO* const startInfo, kuchar* data[], kuint32 dataNum )
{
	kint32 i;
	kint32 ret = D_DDIM_OK;

	for( i = 0; i < dataNum; i++ ){
		// receive counter clear.
		S_GCT_DD_I2C_RECV_COUNTER = 0;
		// send counter clear.
		S_GCT_DD_I2C_SEND_COUNTER = 0;
		// Set RW data pointer
		startInfo->rw_data = data[i];
#ifdef D_DD_I2C_PC_DEBUG
		ctI2cStartInfoDump( startInfo );
#endif
		// Start Master
		Ddim_Print(("Dd_I2C_Start_Master: Start.\n"));
		ret = Dd_I2C_Start_Master( ch, startInfo );
		if( ret != D_DDIM_OK){
			// Master start error
			Ddim_Print(("Dd_I2C_Start_Master: Error. ret=0x%08X\n", ret));
		}
		else {
			// Master start OK
			Ddim_Print(("Dd_I2C_Start_Master: OK.\n"));
		}
//		DDIM_User_Tslp_Tsk(1000);
	}

	return ret;
}

static void ctDdI2cDataPrint( E_DD_I2C_RW_MODE mode, kuint32 dataNum, kuint32 dataLength, kuchar* data[] )
{
	kint32 i, j;

	//Print send data to slave
	for( i = 0; i < dataNum; i++ ){
		if( mode == E_DD_I2C_RW_MODE_WRITE ){
			Ddim_Print(("Send Data[%d]\n",i));
		}
		else {
			Ddim_Print(("Receive Data[%d]\n",i));
		}
		for( j = 0; j < dataLength; j += 10 ){
			Ddim_Print(("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
			*( data[i] + j ), *( data[i] +j+1 ),*( data[i] +j+2 ),*( data[i] +j+3 ),
			*( data[i] + j+4 ), *( data[i] +j+5 ),*( data[i] +j+6 ),*( data[i] +j+7 ),
			*( data[i] + j+8 ), *( data[i] +j+9 ) ));
		}
	}
}

// Master ---Write---> Slave
static void ctDdI2cMasterWriteTest( kuchar ch )
{
	T_DD_I2C_START_INFO	startInfo;
	kuchar*				data[CtDdI2c_D_CT_DD_I2C_TEST_DATA_NUM];
	kuint32				dataNum = CtDdI2c_D_CT_DD_I2C_TEST_DATA_NUM;
	kint32				ret;

	// Set start info
	startInfo.rw_mode		= E_DD_I2C_RW_MODE_WRITE;
	startInfo.rw_data_len	= CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;
	startInfo.timeout		= 500;

	// Reset receive data pointer
	S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS = (kuchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_RECEIVE_ADDRESS;

	// Set send data pointer
	data[0] = S_GCT_DD_I2C_MASTER_SEND_ADDRESS;
	data[1] = S_GCT_DD_I2C_MASTER_SEND_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;

	// Set send test data
	ctDdI2cSetWriteTestData( startInfo.rw_data_len, data, dataNum );

	// Start Master
	ret = ctDdI2cMasterStart( ch, &startInfo, data, dataNum );

	if( ret == D_DDIM_OK ){
		// Print send data
		ctDdI2cDataPrint( E_DD_I2C_RW_MODE_WRITE, dataNum, startInfo.rw_data_len, data );

		// Reset receive buffer pointer
		S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS = (kuchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_RECEIVE_ADDRESS;

		// Print receive data
		data[0] = S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS;
		data[1] = S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;
		ctDdI2cDataPrint( E_DD_I2C_RW_MODE_READ, dataNum, startInfo.rw_data_len, data );

		Ddim_Print(("Compare Result = %d\n", memcmp((void*)S_GCT_DD_I2C_MASTER_SEND_ADDRESS, (void*)S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS, CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN*dataNum)));
	}
}

// Master <---Read--- Slave
static void ctDdI2cMasterReadTest( kuchar ch )
{
	T_DD_I2C_START_INFO	startInfo;
	kuchar*				data[CtDdI2c_D_CT_DD_I2C_TEST_DATA_NUM];
	kuchar*				send_data[CtDdI2c_D_CT_DD_I2C_TEST_DATA_NUM];
	kuint32				dataNum = CtDdI2c_D_CT_DD_I2C_TEST_DATA_NUM;
	kint32				ret;

	// Set start info
	startInfo.rw_mode		= E_DD_I2C_RW_MODE_READ;
	startInfo.rw_data_len	= CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;
	startInfo.timeout		= 500;

	// Reset send data pointer
	S_GCT_DD_I2C_SLAVE_SEND_ADDRESS = (kuchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_SEND_ADDRESS;

	// Set send data pointer
	send_data[0] = S_GCT_DD_I2C_SLAVE_SEND_ADDRESS;
	send_data[1] = S_GCT_DD_I2C_SLAVE_SEND_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;

	// Set send test data
	ctDdI2cSetReadTestData( startInfo.rw_data_len, send_data, dataNum );

	// Set receive data pointer
	data[0] = S_GCT_DD_I2C_MASTER_RECEIVE_ADDRESS;
	data[1] = S_GCT_DD_I2C_MASTER_RECEIVE_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;

	// Start Master
	ret = ctDdI2cMasterStart( ch, &startInfo, data, dataNum );

	if( ret == D_DDIM_OK ){
		// Print receive data
		ctDdI2cDataPrint( E_DD_I2C_RW_MODE_READ, dataNum, startInfo.rw_data_len, data );

		// Reset receive buffer pointer
		S_GCT_DD_I2C_SLAVE_SEND_ADDRESS = (kuchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_SEND_ADDRESS;

		// Print send data
		data[0] = S_GCT_DD_I2C_SLAVE_SEND_ADDRESS;
		data[1] = S_GCT_DD_I2C_SLAVE_SEND_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;
		ctDdI2cDataPrint( E_DD_I2C_RW_MODE_WRITE, dataNum, startInfo.rw_data_len, data );

		Ddim_Print(("Compare Result = %d\n", memcmp((void*)S_GCT_DD_I2C_SLAVE_SEND_ADDRESS, (void*)S_GCT_DD_I2C_MASTER_RECEIVE_ADDRESS, CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN*dataNum)));
	}
}

//Call back function for slave
static T_DD_I2C_SLAVE_ACTION ctDdI2c_cb( kuchar ch, E_DD_I2C_RECV_FROM_MASTER receiveSig, kuchar data )
{
	T_DD_I2C_SLAVE_ACTION ret_act = { D_DD_I2C_SEND_NO_ACK_MASTER, 0 };

	switch( receiveSig ){
		case E_DD_I2C_RECV_FROM_MASTER_ADDRESS:
			// Receive slave address
			S_GCT_DD_I2C_RECV_COUNTER = 0;
			S_GCT_DD_I2C_SEND_COUNTER = 0;

			Ddim_Print(("Received Slave address = 0x%04X\n",data));
			break;
		case E_DD_I2C_RECV_FROM_MASTER_DATA:

			if( S_GCT_DD_I2C_RECV_COUNTER < CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN ){
				// Replay ACK to master
				ret_act.action_mode = D_DD_I2C_SEND_DATA_2_MASTER;
				ret_act.send_data = D_DD_I2C_SEND_ACK_MASTER;

				// Get receive data
				*S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS = data;
				S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS++;
				S_GCT_DD_I2C_RECV_COUNTER++;
			}
			else {
				// Replay NOACK to master
				ret_act.action_mode = D_DD_I2C_SEND_NO_ACK_MASTER;
			}
			break;

		case E_DD_I2C_RECV_FROM_MASTER_ACK:
			if( S_GCT_DD_I2C_SEND_COUNTER < CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN ){
				// Replay ACK to master
				ret_act.action_mode = D_DD_I2C_SEND_DATA_2_MASTER;

				// Set send data
				ret_act.send_data = *S_GCT_DD_I2C_SLAVE_SEND_ADDRESS;
				S_GCT_DD_I2C_SLAVE_SEND_ADDRESS++;
				S_GCT_DD_I2C_SEND_COUNTER++;
			}
			else if (S_GCT_DD_I2C_SEND_COUNTER == CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN) {
				ret_act.action_mode = D_DD_I2C_SEND_DATA_2_MASTER;
				ret_act.send_data = 0x00;
			}
			break;

		case E_DD_I2C_RECV_FROM_MASTER_ERROR:
			// Receive error
			ret_act.action_mode = D_DD_I2C_SEND_NO_ACK_MASTER;

			Ddim_Print(("Received Error occur. Cause = 0x%08X\n", Dd_I2C_Get_Error_Cause( ch )));
			break;

		default:
			break;
	}

	return ret_act;
}

/*
*PUBLIC
*/
void ct_dd_i2c_main_main(CtDdI2c* self, kint argc, kchar** argv)
{
	kulong val;
	kuchar ch;
	kchar* endstr;
	kint32 ret = D_DDIM_OK;

	if( strcmp(argv[1], "init") == 0 ){
		val = Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PC1L, 1 );	// IS0CL(ch0)
		if ( val != D_DDIM_OK ) {
			Ddim_Print(("Dd_Top_Set_Gpio_Function error [IS0CL(ch0)]\n"));
		}
		val = Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PC0L, 1 );	// IS0DA(ch0)
		if ( val != D_DDIM_OK ) {
			Ddim_Print(("Dd_Top_Set_Gpio_Function error [IS0DA(ch0)]\n"));
		}
		val = Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PC3L, 1 );	// IS1CL(ch1)
		if ( val != D_DDIM_OK ) {
			Ddim_Print(("Dd_Top_Set_Gpio_Function error [IS1CL(ch1)]\n"));
		}
		val = Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PC2L, 1 );	// IS1DA(ch1)
		if ( val != D_DDIM_OK ) {
			Ddim_Print(("Dd_Top_Set_Gpio_Function error [IS1DA(ch1)]\n"));
		}
		val = Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PC5L, 1 );	// IS2CL(ch2)
		if ( val != D_DDIM_OK ) {
			Ddim_Print(("Dd_Top_Set_Gpio_Function error [IS2CL(ch2)]\n"));
		}
		val = Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PC4L, 1 );	// IS2DA(ch2)
		if ( val != D_DDIM_USER_E_OK ) {
			Ddim_Print(("Dd_Top_Set_Gpio_Function error [IS2DA(ch2)]\n"));
		}

		memset(S_GCT_DD_I2C_MASTER_SEND_ADDRESS, 0, CtDdI2c_D_CT_DD_I2C_MAX_BUFFER_SIZE);
		memset(S_GCT_DD_I2C_MASTER_RECEIVE_ADDRESS, 0, CtDdI2c_D_CT_DD_I2C_MAX_BUFFER_SIZE);
		memset(S_GCT_DD_I2C_SLAVE_SEND_ADDRESS, 0, CtDdI2c_D_CT_DD_I2C_MAX_BUFFER_SIZE);
		memset(S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS, 0, CtDdI2c_D_CT_DD_I2C_MAX_BUFFER_SIZE);

		Dd_GIC_Ctrl(E_DD_GIC_INTID_I2C_CH0_INT, 1, D_DD_GIC_PRI14, 1);
		Dd_GIC_Ctrl(E_DD_GIC_INTID_I2C_CH1_INT, 1, D_DD_GIC_PRI14, 1);
		Dd_GIC_Ctrl(E_DD_GIC_INTID_I2C_CH2_INT, 1, D_DD_GIC_PRI14, 1);
	}
	else if( strcmp(argv[1], "open") == 0){
		// i2c stop_master P1
		//   P1 : Channel No.
		//   P2 : wait time
		ch = atoi( argv[2] );

		kint32 wait_time = CtDdI2c_D_DD_CT_I2C_WAIT_TIME;
		if( argc > 3 ){
			wait_time = atoi(argv[3]);
		}
		if( Dd_I2C_Open( ch,wait_time ) == D_DDIM_OK ){
			Ddim_Print(("Dd_I2C_Open: OK\n"));
		}
		else{
			Ddim_Print(("Dd_I2C_Open: open error\n"));
		}
#ifdef D_DD_I2C_PC_DEBUG
		ctI2cRegisterDump(ch);
#endif
	}
	else if( strcmp(argv[1], "close") == 0 ){
		// i2c stop_master P1
		//   P1 : Channel No.
		ch = atoi( argv[2] );

#ifdef CO_DEBUG_ON_PC
		Dd_I2C_Open( ch, 1 );
#endif
		if( Dd_I2C_Close( ch ) == D_DDIM_OK ){
			Ddim_Print(("Dd_I2C_Close: OK\n"));
		}
		else{
			Ddim_Print(("Dd_I2C_Close: close error\n"));
		}
#ifdef D_DD_I2C_PC_DEBUG
		ctI2cRegisterDump(ch);
#endif
	}
	else if( strcmp(argv[1], "ctrlMaster") == 0 ){
		// i2c ctrlMaster P1 P2 P3 P4
		//  P1: Channel No P2: BPS
		//  P3: Destination slave address length. 0=7 bits 1=10 bits
		//  P4: Destination slave address
		if( argc == 6 ){
			ch	= atoi( argv[2] );
			S_GCT_DD_I2C_CTRL_MASTER.bps					= (E_DD_I2C_BPS)atoi( argv[3] );
			S_GCT_DD_I2C_CTRL_MASTER.dest_slave_addr_len	= (E_DD_I2C_ADDR_LEN)atoi( argv[4] );
			S_GCT_DD_I2C_CTRL_MASTER.dest_slave_addr		= strtoul( argv[5], &endstr, 16 );
#ifdef D_DD_I2C_PC_DEBUG
			ctI2cCtrlMasterDump( &S_GCT_DD_I2C_CTRL_MASTER );
#endif

			ret = Dd_I2C_Ctrl_Master( ch, &S_GCT_DD_I2C_CTRL_MASTER );
			if( ret == D_DDIM_OK ){
				Ddim_Print(("Dd_I2C_Ctrl_Master: OK\n"));
			}
			else{
				Ddim_Print(("Dd_I2C_Ctrl_Master: Error. ret=0x%08X)\n", ret));
			}
#ifdef D_DD_I2C_PC_DEBUG
			ctI2cRegisterDump( ch );
#endif
		}
		else{
			Ddim_Print(("Parameter should be 6\n"));
		}
	}
	else if( strcmp(argv[1], "get_ctrl_master") == 0 ){
		T_DD_I2C_CTRL_MASTER	ctrlMaster;

		ch	= atoi( argv[2] );

		ret = Dd_I2C_Get_Ctrl_Master( ch, &ctrlMaster );
		if( ret == D_DDIM_OK ){
			Ddim_Print(("Dd_I2C_Get_Ctrl_Master: OK\n"));
			ctI2cCtrlMasterDump( &ctrlMaster );
		}
		else{
			Ddim_Print(("Dd_I2C_Get_Ctrl_Master: Error. ret=0x%08X)\n", ret));
		}
	}
	else if( strcmp(argv[1], "ctrlSlave") == 0 ){
		// i2c ctrlSlave P1 P2 P3 P4 P5
		//  P1: Channel No P2: Own slave address length. 0=7 bits 1=10 bits P3: Own slave address
		//  P4: Global call address enable
		//  P5: Callback enable
		if( argc == 7 ){
			ch	= atoi( argv[2] );
			S_GCT_DD_I2C_CTRL_SLAVE.own_slave_addr_len	= (E_DD_I2C_ADDR_LEN)atoi( argv[3] );
			S_GCT_DD_I2C_CTRL_SLAVE.own_slave_addr		= strtoul( argv[4], &endstr, 16 );
			S_GCT_DD_I2C_CTRL_SLAVE.global_call_en		= atoi( argv[5] );
			if( atoi( argv[6] ) == 0 ){
				S_GCT_DD_I2C_CTRL_SLAVE.callback			= NULL;
			}
			else {
				S_GCT_DD_I2C_CTRL_SLAVE.callback			= (VP_I2C_CALLBACK)ctDdI2c_cb;
			}
#ifdef D_DD_I2C_PC_DEBUG
			ctI2cCtrlSlaveDump( &S_GCT_DD_I2C_CTRL_SLAVE );
#endif

			ret = Dd_I2C_Ctrl_Slave( ch, &S_GCT_DD_I2C_CTRL_SLAVE );
			if( ret == D_DDIM_OK ){
				Ddim_Print(("Dd_I2C_Ctrl_Slave: OK\n"));
			}
			else{
				Ddim_Print(("Dd_I2C_Ctrl_Slave: Error. ret=0x%08X\n", ret));
			}
#ifdef D_DD_I2C_PC_DEBUG
			ctI2cRegisterDump( ch );
#endif
		}
		else{
			Ddim_Print(("Parameter should be 7\n"));
		}
	}
	else if( strcmp(argv[1], "get_ctrl_slave") == 0 ){
		T_DD_I2C_CTRL_SLAVE	ctrlSlave;

		ch	= atoi( argv[2] );

		ret = Dd_I2C_Get_Ctrl_Slave( ch, &ctrlSlave );
		if( ret == D_DDIM_OK ){
			Ddim_Print(("Dd_I2C_Get_Ctrl_Slave: OK\n"));
			ctI2cCtrlSlaveDump( &ctrlSlave );
		}
		else{
			Ddim_Print(("Dd_I2C_Get_Ctrl_Slave: Error. ret=0x%08X\n", ret));
		}
	}
	else if( strcmp(argv[1], "ctrlSmbus") == 0 ){
		// i2c ctrlSmbus P1 P2 P3 P4 P5
		//  P1: Channel No P2: Alert Response Match Enable P3: PEC number of byte P4: Timeout Divider
		//  P5: Timeout Prescaler
		if( argc == 7 ){
			T_DD_I2C_CTRL_SMBUS	ctrlSmbus;

			ch	= atoi( argv[2] );
			ctrlSmbus.alert_resp_en	= atoi( argv[3] );
			ctrlSmbus.pec_num			= atoi( argv[4] );
			ctrlSmbus.timeout_div		= (E_DD_I2C_TO_DIV)atoi( argv[5] );
			ctrlSmbus.timeout_presc	= atoi( argv[6] );
#ifdef D_DD_I2C_PC_DEBUG
			ctI2cCtrlSmbusDump( &ctrlSmbus );
#endif

			ret = Dd_I2C_Ctrl_SMBus( ch, &ctrlSmbus );
			if( ret == D_DDIM_OK ){
				Ddim_Print(("Dd_I2C_Ctrl_SMBus: OK\n"));
			}
			else{
				Ddim_Print(("Dd_I2C_Ctrl_SMBus: Error. ret=0x%08X)\n", ret));
			}
#ifdef D_DD_I2C_PC_DEBUG
			ctI2cRegisterDump( ch );
#endif
		}
		else{
			Ddim_Print(("Parameter should be 7\n"));
		}
	}
	else if( strcmp(argv[1], "get_ctrl_smbus") == 0 ){
		T_DD_I2C_CTRL_SMBUS	ctrlSmbus;

		ch	= atoi( argv[2] );

		ret = Dd_I2C_Get_Ctrl_SMBus( ch, &ctrlSmbus );
		if( ret == D_DDIM_OK ){
			Ddim_Print(("Dd_I2C_Get_Ctrl_SMBus: OK\n"));
			ctI2cCtrlSmbusDump( &ctrlSmbus );
		}
		else{
			Ddim_Print(("Dd_I2C_Get_Ctrl_SMBus: Error. ret=0x%08X)\n", ret));
		}
	}
	else if( strcmp( argv[1], "start_master") == 0 ) {
		// i2c start_master P1 P2 P3 P4 P5
		//  P1: Channel No. P2: Read(0) or Write(1) P3: Data address P4: Data length P5: Number of data
		if( argc == 8 ){
			T_DD_I2C_START_INFO	startInfo;
			kuint32				dataNum;
			kint32				i;
			kuchar*				data[CtDdI2c_D_CT_DD_I2C_MAX_DATA_NUM];

			ch						= atoi( argv[2] );
			startInfo.rw_mode		= (E_DD_I2C_RW_MODE)atoi( argv[3] );
			data[0]					= (kuchar*)strtoul(argv[4], &endstr, 16);
			startInfo.rw_data_len	= atoi( argv[5] );
			dataNum				= atoi(argv[6]);
			startInfo.timeout		= 500;

			// Check test data size
			if( startInfo.rw_data_len > CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN ){
				Ddim_Print(("rw_data_len is over test size(%d)\n", CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN));
				return;
			}
			if( dataNum > CtDdI2c_D_CT_DD_I2C_MAX_DATA_NUM ){
				Ddim_Print(("dataNum is over test size(%d)\n", CtDdI2c_D_CT_DD_I2C_MAX_DATA_NUM));
				return;
			}

			// Set data address
			for( i = 1; i < dataNum; i++ ){
				data[i] = data[i-1] + startInfo.rw_data_len;
			}

			if( startInfo.rw_mode == E_DD_I2C_RW_MODE_WRITE ){
				// Set send test data
				ctDdI2cSetWriteTestData( startInfo.rw_data_len, data, dataNum );
			}

			// Start Master
			ret = ctDdI2cMasterStart( ch, &startInfo, data, dataNum );
			if( ret == D_DDIM_OK ){
				// Start OK
				Ddim_Print(("Dd_I2C_Start_Master: OK\n"));
				// Print result
				ctDdI2cDataPrint( startInfo.rw_mode, dataNum, startInfo.rw_data_len, data );
			}
#ifdef D_DD_I2C_PC_DEBUG
			ctI2cRegisterDump( ch );
#endif
		}
		else{
			Ddim_Print(("Parameter should be 7\n"));
		}
	}
	else if( strcmp(argv[1], "stop_master") == 0 ){
		// i2c stop_master P1
		//  P1 : Channel No.
		ch = atoi( argv[2] );

		ret = Dd_I2C_Stop_Master( ch );
		if( ret == D_DDIM_OK ){
			// Stop OK
			Ddim_Print(("Dd_I2C_Stop_Master OK\n"));
		}
		else{
			// Stop NG
			Ddim_Print(("Dd_I2C_Stop_Master NG\n"));
		}
#ifdef D_DD_I2C_PC_DEBUG
		ctI2cRegisterDump(ch);
#endif
	}
	else if( strcmp( argv[1], "start_slave") == 0 ) {
		// i2c start_slave P1
		//  P1: Channel No.
		if( argc == 3 ){
			ch = atoi( argv[2] );

			ret = Dd_I2C_Start_Slave( ch );
			if( ret == D_DDIM_OK ){
				// Start OK
				Ddim_Print(("Dd_I2C_Start_Slave OK\n"));
			}
			else{
				//Start NG
				Ddim_Print(("Dd_I2C_Start_Slave NG\n"));
			}
#ifdef D_DD_I2C_PC_DEBUG
			ctI2cRegisterDump(ch);
#endif
		}
		else{
			Ddim_Print(("Parameter should be 3\n"));
		}
	}
	else if( strcmp(argv[1], "stop_slave") == 0 ){
		// i2c stop_slave P1
		//  P1 : Channel No.
		ch = atoi( argv[2] );

		ret = Dd_I2C_Stop_Slave( ch );
		if( ret == D_DDIM_OK ){
			// Stop OK
			Ddim_Print(("Dd_I2C_Stop_Slave OK\n"));
		}
		else{
			// Stop NG
			Ddim_Print(("Dd_I2C_Stop_Slave NG\n"));
		}
#ifdef D_DD_I2C_PC_DEBUG
		ctI2cRegisterDump(ch);
#endif
	}
	else if( strcmp(argv[1], "set") == 0 ){
		if( strcmp(argv[2], "tgscl") == 0 ){
			// Set Toggle SCL
			// i2c set tgscl P1
			//  P1 : Channel No.
			ch = atoi(argv[3]);

			Dd_I2C_Set_Toggle_SCL( ch );
			Ddim_Print((" IO_PERI.I2C[%d].CST.bit.TGSCL = %d\n", ch, IO_PERI.I2C[ch].CST.bit.TGSCL ));
		}
		else if( strcmp(argv[2], "scl") == 0 ){
			// Set SCL frequency
			// i2c set scl P1 P2
			//  P1 : Channel No.
			//  P2 : SCL frequency
			kuchar scl = atoi(argv[4]);
			ch = atoi(argv[3]);

			Dd_I2C_Set_SCL( ch, scl );
			Ddim_Print((" IO_PERI.I2C[%d].CTL2.bit.SCLFRQ = %d\n", ch, IO_PERI.I2C[ch].CTL2.bit.SCLFRQ ));
		}
	}
	else if( strcmp(argv[1], "get") == 0 ){
		if( strcmp(argv[2], "tsda") == 0 ){
			// Get Test SDA
			// i2c get tsda P1
			//  P1 : Channel No.
			kuchar tsda;
			ch = atoi(argv[3]);
#ifdef D_DD_I2C_PC_DEBUG
			IO_PERI.I2C[ch].CST.bit.TSDA = 1;
#endif
			Dd_I2C_Get_Test_SDA( ch, &tsda );
			Ddim_Print((" IO_PERI.I2C[%d].CST.bit.TSDA = %d\n", ch, tsda ));
		}
		else if( strcmp(argv[2], "scl") == 0 ){
			// Get SCL frequency
			// i2c get scl P1
			//  P1 : Channel No.
			kuchar scl;
			ch = atoi(argv[3]);

			Dd_I2C_Get_SCL( ch, &scl );
			Ddim_Print((" IO_PERI.I2C[%d].CTL2.bit.SCLFRQ = %d\n", ch, scl ));
		}
		else if( strcmp(argv[2], "cause") == 0 ){
			// Get Error Cause
			// i2c get cause P1
			//  P1 : Channel No.
			ch = atoi(argv[3]);
			Ddim_Print((" Error Cause[%d] = 0x%08X\n", ch, Dd_I2C_Get_Error_Cause( ch ) ));
		}
	}
	else if( strcmp(argv[1], "inthdr") == 0 ){
		// Interrupt handler
		// i2c inthdr P1 P2
		//  P1 : Channel No.
		//  P2 : ST.MODE
		kuchar ch = atoi(argv[2]);

#ifdef D_DD_I2C_PC_DEBUG
		kuchar mode = strtoul( argv[3], &endstr, 16 );;

		if( mode == 0x40 ){
			IO_PERI.I2C[ch].CST.bit.TERR = 1;
		}
		else {
			IO_PERI.I2C[ch].ST.bit.MODE = mode;
		}
#endif

		Dd_I2C_Int_Handler( ch );

#ifdef D_DD_I2C_PC_DEBUG
		ctI2cRegisterDump(ch);
#endif
	}
	else if( strcmp(argv[1], "start_w") == 0 ){
		// Master ---Write---> Slave
		// i2c start_w P1
		//  P1 : Channel No.
		ch = atoi( argv[2] );

		ctDdI2cMasterWriteTest( ch );
#ifdef D_DD_I2C_PC_DEBUG
		ctI2cRegisterDump( ch );
		ctI2cRegisterDump( ch );
#endif
	}
	else if( strcmp(argv[1], "start_r") == 0 ){
		// Master <---Read--- Slave
		// i2c start_w P1
		//  P1 : Channel No.
		ch = atoi( argv[2] );
		ctDdI2cMasterReadTest( ch );
#ifdef D_DD_I2C_PC_DEBUG
		ctI2cRegisterDump( ch );
		ctI2cRegisterDump( ch );
#endif
	}
	else if( strcmp(argv[1], "err") == 0 ){
		kint32 ret;
		T_DD_I2C_CTRL_MASTER ctrlMaster;
		T_DD_I2C_CTRL_SLAVE ctrlSlave;
		T_DD_I2C_CTRL_SMBUS ctrlSmbus;
		T_DD_I2C_START_INFO startInfo;
		kuchar val;

		ret = Dd_I2C_Open( 3,1 );
		Ddim_Print(("Dd_I2C_Open: CH NG(%d)\n", ret));

		ret = Dd_I2C_Open( 2,1 );
		Ddim_Print(("Dd_I2C_Open: SEM NG(%d)\n", ret));

		ret = Dd_I2C_Close( 3 );
		Ddim_Print(("Dd_I2C_Close: CH NG(%d)\n", ret));

		ret = Dd_I2C_Close( 2 );
		ret = Dd_I2C_Close( 2 );
		Ddim_Print(("Dd_I2C_Close: SEM NG(%d)\n", ret));

		ret = Dd_I2C_Ctrl_Master( 3, &ctrlMaster );
		Ddim_Print(("Dd_I2C_Ctrl_Master: CH NG(%d)\n", ret));

		ret = Dd_I2C_Ctrl_Master( 2, NULL );
		Ddim_Print(("Dd_I2C_Ctrl_Master: Pointer NG(%d)\n", ret));

		ret = Dd_I2C_Get_Ctrl_Master( 3, &ctrlMaster );
		Ddim_Print(("Dd_I2C_Get_Ctrl_Master: CH NG(%d)\n", ret));

		ret = Dd_I2C_Get_Ctrl_Master( 2, NULL );
		Ddim_Print(("Dd_I2C_Get_Ctrl_Master: Pointer NG(%d)\n", ret));

		ctrlSlave.callback = ctDdI2c_cb;
		ret = Dd_I2C_Ctrl_Slave( 3, &ctrlSlave );
		Ddim_Print(("Dd_I2C_Ctrl_Slave: CH NG(%d)\n", ret));

		ret = Dd_I2C_Ctrl_Slave( 2, NULL );
		Ddim_Print(("Dd_I2C_Ctrl_Slave: Pointer NG(%d)\n", ret));

		ctrlSlave.callback = NULL;
		ret = Dd_I2C_Ctrl_Slave( 2, &ctrlSlave );
		Ddim_Print(("Dd_I2C_Ctrl_Slave: Callback NG(%d)\n", ret));

		ret = Dd_I2C_Get_Ctrl_Slave( 3, &ctrlSlave );
		Ddim_Print(("Dd_I2C_Get_Ctrl_Slave: CH NG(%d)\n", ret));

		ret = Dd_I2C_Get_Ctrl_Slave( 2, NULL );
		Ddim_Print(("Dd_I2C_Get_Ctrl_Slave: Pointer NG(%d)\n", ret));

		ret = Dd_I2C_Ctrl_SMBus( 3, &ctrlSmbus );
		Ddim_Print(("Dd_I2C_Ctrl_SMBus: CH NG(%d)\n", ret));

		ret = Dd_I2C_Ctrl_SMBus( 2, NULL );
		Ddim_Print(("Dd_I2C_Ctrl_SMBus: Pointer NG(%d)\n", ret));

		ret = Dd_I2C_Close( 2 );
		ret = Dd_I2C_Ctrl_SMBus( 2, &ctrlSmbus );
		Ddim_Print(("Dd_I2C_Ctrl_SMBus: ENABLE NG(%d)\n", ret));
		ret = Dd_I2C_Open( 2,1 );

		ret = Dd_I2C_Get_Ctrl_SMBus( 3, &ctrlSmbus );
		Ddim_Print(("Dd_I2C_Get_Ctrl_SMBus: CH NG(%d)\n", ret));

		ret = Dd_I2C_Get_Ctrl_SMBus( 2, NULL );
		Ddim_Print(("Dd_I2C_Get_Ctrl_SMBus: Pointer NG(%d)\n", ret));

		ret = Dd_I2C_Get_Ctrl_SMBus( 2, &ctrlSmbus );
		Ddim_Print(("Dd_I2C_Get_Ctrl_SMBus: ENABLE NG(%d)\n", ret));

		ret = Dd_I2C_Start_Master( 3, &startInfo );
		Ddim_Print(("Dd_I2C_Start_Master: CH NG(%d)\n", ret));

		ret = Dd_I2C_Start_Master( 2, NULL );
		Ddim_Print(("Dd_I2C_Start_Master: Pointer NG(%d)\n", ret));

		ret = Dd_I2C_Ctrl_Slave( 2, &ctrlSlave );
		ret = Dd_I2C_Start_Master( 2, &startInfo );
		Ddim_Print(("Dd_I2C_Start_Master: SIDE NG(%d)\n", ret));

		ret = Dd_I2C_Start_Master( 2, &startInfo );
		ret = Dd_I2C_Start_Master( 2, &startInfo );
		Ddim_Print(("Dd_I2C_Start_Master: BB NG(%d)\n", ret));

		ret = Dd_I2C_Stop_Master( 3 );
		Ddim_Print(("Dd_I2C_Stop_Master: CH NG(%d)\n", ret));

		ret = Dd_I2C_Start_Slave( 3 );
		Ddim_Print(("Dd_I2C_Start_Slave: CH NG(%d)\n", ret));

		ret = Dd_I2C_Stop_Slave( 3 );
		Ddim_Print(("Dd_I2C_Stop_Slave: CH NG(%d)\n", ret));

		ret = Dd_I2C_Set_Toggle_SCL( 3 );
		Ddim_Print(("Dd_I2C_Set_Toggle_SCL: CH NG(%d)\n", ret));

		ret = Dd_I2C_Get_Test_SDA( 3, &val );
		Ddim_Print(("Dd_I2C_Get_Test_SDA: CH NG(%d)\n", ret));

		ret = Dd_I2C_Get_Test_SDA( 2, NULL );
		Ddim_Print(("Dd_I2C_Get_Test_SDA: Pointer NG(%d)\n", ret));

		Dd_I2C_Int_Handler( 3 );
		Ddim_Print(("Dd_I2C_Int_Handler: CH NG\n"));

		val = 127;
		ret = Dd_I2C_Set_SCL( 3, val );
		Ddim_Print(("Dd_I2C_Set_SCL: CH NG(%d)\n", ret));

		val = 128;
		ret = Dd_I2C_Set_SCL( 2, val );
		Ddim_Print(("Dd_I2C_Set_SCL: SCL NG(%d)\n", ret));

		ret = Dd_I2C_Get_SCL( 3, &val );
		Ddim_Print(("Dd_I2C_Get_SCL: CH NG(%d)\n", ret));

		ret = Dd_I2C_Get_SCL( 2, NULL );
		Ddim_Print(("Dd_I2C_Get_SCL: Pointer NG(%d)\n", ret));
	}
	else{
		Ddim_Print(("Error: Unknown command.\n"));
	}

	return;
}

CtDdI2c* ct_dd_i2c_new(void) 
{
    CtDdI2c *self = k_object_new_with_private(CT_TYPE_DD_I2C, sizeof(CtDdI2cPrivate));
    return self;
}
