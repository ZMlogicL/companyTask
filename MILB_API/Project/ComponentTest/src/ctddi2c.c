/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
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
#include "ddi2c.h"
#include "ct_dd_i2c.h"
#include "ddgic.h"
#include "ddim_user_custom.h"
#include "peripheral.h"

#include "ctddi2c.h"


G_DEFINE_TYPE(CtDdI2c, ct_dd_i2c, G_TYPE_OBJECT);
#define CT_DD_I2C_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_DD_I2C, CtDdI2cPrivate))

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
	DdI2c *ddI2c;
	DdGic *ddGic;
};

static guchar* S_GCT_DD_I2C_MASTER_SEND_ADDRESS = (guchar*)CtDdI2c_D_CT_DD_I2C_MASTER_SEND_ADDRESS;
static guchar* S_GCT_DD_I2C_MASTER_RECEIVE_ADDRESS = (guchar*)CtDdI2c_D_CT_DD_I2C_MASTER_RECEIVE_ADDRESS;
static guchar* S_GCT_DD_I2C_SLAVE_SEND_ADDRESS = (guchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_SEND_ADDRESS;
static guchar* S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS = (guchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_RECEIVE_ADDRESS;

static gint32 S_GCT_DD_I2C_RECV_COUNTER = 0;
static gint32 S_GCT_DD_I2C_SEND_COUNTER = 0;

static DdI2cCtrlMaster	 S_GCT_DD_I2C_CTRL_MASTER;
static DdI2cCtrlSlave		 S_GCT_DD_I2C_CTRL_SLAVE;

/*
*DECLS
*/
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
#ifdef D_DD_I2C_PC_DEBUG
static void 	ctI2cRegisterDump( guchar ch );
#endif
static void 	ctI2cCtrlMasterDump( const DdI2cCtrlMaster* ctrlMaster );
static void 	ctI2cCtrlSlaveDump( const DdI2cCtrlSlave* ctrlSlave );
static void 	ctI2cCtrlSmbusDump( const DdI2cCtrlSmbus* ctrlSmbus );
#ifdef D_DD_I2C_PC_DEBUG
static void 	ctI2cStartInfoDump( const DdI2cStartInfo* startInfo );
#endif
static void 	ctDdI2cSetWriteTestData( guint32 dataLen, guchar* data[], guint32 dataNum );
static void 	ctDdI2cSetReadTestData( guint32 dataLen, guchar* data[], guint32 dataNum );
static gint32 	ctDdI2cMasterStart( guchar ch, DdI2cStartInfo* const startInfo, guchar* data[], guint32 dataNum );
static void 	ctDdI2cDataPrint( I2cRwMode mode, guint32 dataNum, guint32 dataLength, guchar* data[] );
static void 	ctDdI2cMasterWriteTest( guchar ch );
static void 	ctDdI2cMasterReadTest( guchar ch );
static DdI2cSlaveAction
						ctDdI2c_cb( guchar ch, I2cRecvFromMaster receiveSig, guchar data );
/*
*IMPL
*/

static void ct_dd_i2c_class_init(CtDdI2cClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtDdI2cPrivate));
}

static void ct_dd_i2c_init(CtDdI2c *self)
{
	CtDdI2cPrivate *priv = CT_DD_I2C_GET_PRIVATE(self);
	priv->ddI2c=dd_i2c_get();
	priv->ddGic=dd_gic_new();
}

static void dispose_od(GObject *object)
{
	CtDdI2c *self = (CtDdI2c*)object;
	CtDdI2cPrivate *priv = CT_DD_I2C_GET_PRIVATE(self);
	if(priv->ddI2c){
		g_object_unref(priv->ddI2c);
		priv->ddI2c=NULL;
	}
	if(priv->ddGic){
		g_object_unref(priv->ddGic);
		priv->ddGic=NULL;
	}
	G_OBJECT_CLASS(ct_dd_i2c_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtDdI2c *self = (CtDdI2c*)object;
//	CtDdI2cPrivate *priv = CT_DD_I2C_GET_PRIVATE(self);
}

#ifdef D_DD_I2C_PC_DEBUG
static void ctI2cRegisterDump( guchar ch )
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

static void ctI2cCtrlMasterDump( const DdI2cCtrlMaster* ctrlMaster )
{
	Ddim_Print(("DdI2cCtrlMaster\n"));
	Ddim_Print((" ctrlMaster.bps                 = %d\n", (DdI2cBps)ctrlMaster->bps ));
	Ddim_Print((" ctrlMaster.destSlaveAddrLen = %d\n", (DdI2cAddrLen)ctrlMaster->destSlaveAddrLen ));
	Ddim_Print((" ctrlMaster.destSlaveAddr     = 0x%04X\n", ctrlMaster->destSlaveAddr ));
}

static void ctI2cCtrlSlaveDump( const DdI2cCtrlSlave* ctrlSlave )
{
	Ddim_Print(("DdI2cCtrlSlave\n"));
	Ddim_Print((" ctrlSlave.ownSlaveAddrLen = %d\n", (DdI2cAddrLen)ctrlSlave->ownSlaveAddrLen ));
	Ddim_Print((" ctrlSlave.ownSlaveAddr     = 0x%04X\n", ctrlSlave->ownSlaveAddr ));
	Ddim_Print((" ctrlSlave.globalCallEn     = %d\n", ctrlSlave->globalCallEn ));
	Ddim_Print((" ctrlSlave.callback           = 0x%08lX\n", (gulong)ctrlSlave->callback ));
}

static void ctI2cCtrlSmbusDump( const DdI2cCtrlSmbus* ctrlSmbus )
{
	Ddim_Print(("DdI2cCtrlSmbus\n"));
	Ddim_Print((" ctrlSmbus.alertRespEn = %d\n", ctrlSmbus->alertRespEn ));
	Ddim_Print((" ctrlSmbus.pecNum       = %d\n", ctrlSmbus->pecNum ));
	Ddim_Print((" ctrlSmbus.timeoutDiv   = %d\n", (DdI2cToDiv)ctrlSmbus->timeoutDiv ));
	Ddim_Print((" ctrlSmbus.timeoutPresc = %d\n", ctrlSmbus->timeoutPresc ));
}

#ifdef D_DD_I2C_PC_DEBUG
static void ctI2cStartInfoDump( const DdI2cStartInfo* startInfo )
{
	Ddim_Print(("DdI2cStartInfo\n"));
	Ddim_Print((" startInfo.rwMode     = %d\n", startInfo->rwMode ));
	Ddim_Print((" startInfo.rwDataLen = %d\n", startInfo->rwDataLen ));
	Ddim_Print((" startInfo.rwData     = %d\n", startInfo->rwData ));
	Ddim_Print((" startInfo.timeout     = %d\n", startInfo->timeout ));
}
#endif

static void ctDdI2cSetWriteTestData( guint32 dataLen, guchar* data[], guint32 dataNum )
{
	gint32	num, i;

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

static void ctDdI2cSetReadTestData( guint32 dataLen, guchar* data[], guint32 dataNum )
{
	gint32	num, i;

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

static gint32 ctDdI2cMasterStart( guchar ch, DdI2cStartInfo* const startInfo, guchar* data[], guint32 dataNum )
{
	gint32 i;
	gint32 ret = DriverCommon_D_DDIM_OK;

	for( i = 0; i < dataNum; i++ ){
		// receive counter clear.
		S_GCT_DD_I2C_RECV_COUNTER = 0;
		// send counter clear.
		S_GCT_DD_I2C_SEND_COUNTER = 0;
		// Set RW data pointer
		startInfo->rwData = data[i];
#ifdef D_DD_I2C_PC_DEBUG
		ctI2cStartInfoDump( startInfo );
#endif
		// Start Master
		Ddim_Print(("Dd_I2C_Start_Master: Start.\n"));
		ret = dd_i2c_start_master(priv->ddI2c, ch, startInfo );
		if( ret != DriverCommon_D_DDIM_OK){
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

static void ctDdI2cDataPrint( I2cRwMode mode, guint32 dataNum, guint32 dataLength, guchar* data[] )
{
	gint32 i, j;

	//Print send data to slave
	for( i = 0; i < dataNum; i++ ){
		if( mode == DdI2cCtrl_RW_MODE_WRITE ){
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
static void ctDdI2cMasterWriteTest( guchar ch )
{
	DdI2cStartInfo	startInfo;
	guchar*				data[CtDdI2c_D_CT_DD_I2C_TEST_DATA_NUM];
	guint32				dataNum = CtDdI2c_D_CT_DD_I2C_TEST_DATA_NUM;
	gint32				ret;

	// Set start info
	startInfo.rwMode		= DdI2cCtrl_RW_MODE_WRITE;
	startInfo.rwDataLen	= CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;
	startInfo.timeout		= 500;

	// Reset receive data pointer
	S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS = (guchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_RECEIVE_ADDRESS;

	// Set send data pointer
	data[0] = S_GCT_DD_I2C_MASTER_SEND_ADDRESS;
	data[1] = S_GCT_DD_I2C_MASTER_SEND_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;

	// Set send test data
	ctDdI2cSetWriteTestData( startInfo.rwDataLen, data, dataNum );

	// Start Master
	ret = ctDdI2cMasterStart( ch, &startInfo, data, dataNum );

	if( ret == DriverCommon_D_DDIM_OK ){
		// Print send data
		ctDdI2cDataPrint( DdI2cCtrl_RW_MODE_WRITE, dataNum, startInfo.rwDataLen, data );

		// Reset receive buffer pointer
		S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS = (guchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_RECEIVE_ADDRESS;

		// Print receive data
		data[0] = S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS;
		data[1] = S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;
		ctDdI2cDataPrint( DdI2cCtrl_RW_MODE_READ, dataNum, startInfo.rwDataLen, data );

		Ddim_Print(("Compare Result = %d\n", memcmp((void*)S_GCT_DD_I2C_MASTER_SEND_ADDRESS, (void*)S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS, CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN*dataNum)));
	}
}

// Master <---Read--- Slave
static void ctDdI2cMasterReadTest( guchar ch )
{
	DdI2cStartInfo	startInfo;
	guchar*				data[CtDdI2c_D_CT_DD_I2C_TEST_DATA_NUM];
	guchar*				sendData[CtDdI2c_D_CT_DD_I2C_TEST_DATA_NUM];
	guint32				dataNum = CtDdI2c_D_CT_DD_I2C_TEST_DATA_NUM;
	gint32				ret;

	// Set start info
	startInfo.rwMode		= DdI2cCtrl_RW_MODE_READ;
	startInfo.rwDataLen	= CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;
	startInfo.timeout		= 500;

	// Reset send data pointer
	S_GCT_DD_I2C_SLAVE_SEND_ADDRESS = (guchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_SEND_ADDRESS;

	// Set send data pointer
	sendData[0] = S_GCT_DD_I2C_SLAVE_SEND_ADDRESS;
	sendData[1] = S_GCT_DD_I2C_SLAVE_SEND_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;

	// Set send test data
	ctDdI2cSetReadTestData( startInfo.rwDataLen, sendData, dataNum );

	// Set receive data pointer
	data[0] = S_GCT_DD_I2C_MASTER_RECEIVE_ADDRESS;
	data[1] = S_GCT_DD_I2C_MASTER_RECEIVE_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;

	// Start Master
	ret = ctDdI2cMasterStart( ch, &startInfo, data, dataNum );

	if( ret == DriverCommon_D_DDIM_OK ){
		// Print receive data
		ctDdI2cDataPrint( DdI2cCtrl_RW_MODE_READ, dataNum, startInfo.rwDataLen, data );

		// Reset receive buffer pointer
		S_GCT_DD_I2C_SLAVE_SEND_ADDRESS = (guchar*)CtDdI2c_D_CT_DD_I2C_SLAVE_SEND_ADDRESS;

		// Print send data
		data[0] = S_GCT_DD_I2C_SLAVE_SEND_ADDRESS;
		data[1] = S_GCT_DD_I2C_SLAVE_SEND_ADDRESS + CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN;
		ctDdI2cDataPrint( DdI2cCtrl_RW_MODE_WRITE, dataNum, startInfo.rwDataLen, data );

		Ddim_Print(("Compare Result = %d\n", memcmp((void*)S_GCT_DD_I2C_SLAVE_SEND_ADDRESS, (void*)S_GCT_DD_I2C_MASTER_RECEIVE_ADDRESS, CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN*dataNum)));
	}
}

//Call back function for slave
static DdI2cSlaveAction ctDdI2c_cb( guchar ch, I2cRecvFromMaster receiveSig, guchar data )
{
	DdI2cSlaveAction retAct = { DdI2c_SEND_NO_ACK_MASTER, 0 };

	switch( receiveSig ){
		case DdI2cCtrl_RECV_FROM_MASTER_ADDRESS:
			// Receive slave address
			S_GCT_DD_I2C_RECV_COUNTER = 0;
			S_GCT_DD_I2C_SEND_COUNTER = 0;

			Ddim_Print(("Received Slave address = 0x%04X\n",data));
			break;
		case DdI2cCtrl_RECV_FROM_MASTER_DATA:

			if( S_GCT_DD_I2C_RECV_COUNTER < CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN ){
				// Replay ACK to master
				retAct.actionMode = DdI2c_SEND_DATA_2_MASTER;
				retAct.sendData = D_DD_I2C_SEND_ACK_MASTER;

				// Get receive data
				*S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS = data;
				S_GCT_DD_I2C_SLAVE_RECEIVE_ADDRESS++;
				S_GCT_DD_I2C_RECV_COUNTER++;
			}
			else {
				// Replay NOACK to master
				retAct.actionMode = DdI2c_SEND_NO_ACK_MASTER;
			}
			break;

		case E_DD_I2C_RECV_FROM_MASTER_ACK:
			if( S_GCT_DD_I2C_SEND_COUNTER < CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN ){
				// Replay ACK to master
				retAct.actionMode = DdI2c_SEND_DATA_2_MASTER;

				// Set send data
				retAct.sendData = *S_GCT_DD_I2C_SLAVE_SEND_ADDRESS;
				S_GCT_DD_I2C_SLAVE_SEND_ADDRESS++;
				S_GCT_DD_I2C_SEND_COUNTER++;
			}
			else if (S_GCT_DD_I2C_SEND_COUNTER == CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN) {
				retAct.actionMode = DdI2c_SEND_DATA_2_MASTER;
				retAct.sendData = 0x00;
			}
			break;

		case E_DD_I2C_RECV_FROM_MASTER_ERROR:
			// Receive error
			retAct.actionMode = DdI2c_SEND_NO_ACK_MASTER;

			Ddim_Print(("Received Error occur. Cause = 0x%08X\n", dd_i2c_get_error_cause(priv->ddI2c, ch )));
			break;

		default:
			break;
	}

	return retAct;
}

/*
*PUBLIC
*/
void ct_dd_i2c_main_main(CtDdI2c* self, gint argc, gchar** argv)
{
	gulong val;
	guchar ch;
	gchar* endstr;
	gint32 ret = DriverCommon_D_DDIM_OK;
	CtDdI2cPrivate *priv = CT_DD_I2C_GET_PRIVATE(self);

	if( strcmp(argv[1], "init") == 0 ){
		val = Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PC1L, 1 );	// IS0CL(ch0)
		if ( val != DriverCommon_D_DDIM_OK ) {
			Ddim_Print(("Dd_Top_Set_Gpio_Function error [IS0CL(ch0)]\n"));
		}
		val = Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PC0L, 1 );	// IS0DA(ch0)
		if ( val != DriverCommon_D_DDIM_OK ) {
			Ddim_Print(("Dd_Top_Set_Gpio_Function error [IS0DA(ch0)]\n"));
		}
		val = Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PC3L, 1 );	// IS1CL(ch1)
		if ( val != DriverCommon_D_DDIM_OK ) {
			Ddim_Print(("Dd_Top_Set_Gpio_Function error [IS1CL(ch1)]\n"));
		}
		val = Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PC2L, 1 );	// IS1DA(ch1)
		if ( val != DriverCommon_D_DDIM_OK ) {
			Ddim_Print(("Dd_Top_Set_Gpio_Function error [IS1DA(ch1)]\n"));
		}
		val = Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PC5L, 1 );	// IS2CL(ch2)
		if ( val != DriverCommon_D_DDIM_OK ) {
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

		dd_gic_ctrl(priv->ddGic, E_DD_GIC_INTID_I2C_CH0_INT, 1, D_DD_GIC_PRI14, 1);
		dd_gic_ctrl(priv->ddGic, E_DD_GIC_INTID_I2C_CH1_INT, 1, D_DD_GIC_PRI14, 1);
		dd_gic_ctrl(priv->ddGic, E_DD_GIC_INTID_I2C_CH2_INT, 1, D_DD_GIC_PRI14, 1);
	}
	else if( strcmp(argv[1], "open") == 0){
		// i2c stop_master P1
		//   P1 : Channel No.
		//   P2 : wait time
		ch = atoi( argv[2] );

		gint32 wait_time = CtDdI2c_D_DD_CT_I2C_WAIT_TIME;
		if( argc > 3 ){
			wait_time = atoi(argv[3]);
		}
		if( Dd_I2C_Open( ch,wait_time ) == DriverCommon_D_DDIM_OK ){
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
		if( Dd_I2C_Close( ch ) == DriverCommon_D_DDIM_OK ){
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
			S_GCT_DD_I2C_CTRL_MASTER.bps					= (DdI2cBps)atoi( argv[3] );
			S_GCT_DD_I2C_CTRL_MASTER.destSlaveAddrLen	= (DdI2cAddrLen)atoi( argv[4] );
			S_GCT_DD_I2C_CTRL_MASTER.destSlaveAddr		= strtoul( argv[5], &endstr, 16 );
#ifdef D_DD_I2C_PC_DEBUG
			ctI2cCtrlMasterDump( &S_GCT_DD_I2C_CTRL_MASTER );
#endif

			ret = Dd_I2C_Ctrl_Master( ch, &S_GCT_DD_I2C_CTRL_MASTER );
			if( ret == DriverCommon_D_DDIM_OK ){
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
		DdI2cCtrlMaster	ctrlMaster;

		ch	= atoi( argv[2] );

		ret = Dd_I2C_Get_Ctrl_Master( ch, &ctrlMaster );
		if( ret == DriverCommon_D_DDIM_OK ){
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
			S_GCT_DD_I2C_CTRL_SLAVE.ownSlaveAddrLen	= (DdI2cAddrLen)atoi( argv[3] );
			S_GCT_DD_I2C_CTRL_SLAVE.ownSlaveAddr		= strtoul( argv[4], &endstr, 16 );
			S_GCT_DD_I2C_CTRL_SLAVE.globalCallEn		= atoi( argv[5] );
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
			if( ret == DriverCommon_D_DDIM_OK ){
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
		DdI2cCtrlSlave	ctrlSlave;

		ch	= atoi( argv[2] );

		ret = Dd_I2C_Get_Ctrl_Slave( ch, &ctrlSlave );
		if( ret == DriverCommon_D_DDIM_OK ){
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
			DdI2cCtrlSmbus	ctrlSmbus;

			ch	= atoi( argv[2] );
			ctrlSmbus.alertRespEn	= atoi( argv[3] );
			ctrlSmbus.pecNum			= atoi( argv[4] );
			ctrlSmbus.timeoutDiv		= (DdI2cToDiv)atoi( argv[5] );
			ctrlSmbus.timeoutPresc	= atoi( argv[6] );
#ifdef D_DD_I2C_PC_DEBUG
			ctI2cCtrlSmbusDump( &ctrlSmbus );
#endif

			ret = Dd_I2C_Ctrl_SMBus( ch, &ctrlSmbus );
			if( ret == DriverCommon_D_DDIM_OK ){
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
		DdI2cCtrlSmbus	ctrlSmbus;

		ch	= atoi( argv[2] );

		ret = Dd_I2C_Get_Ctrl_SMBus( ch, &ctrlSmbus );
		if( ret == DriverCommon_D_DDIM_OK ){
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
			DdI2cStartInfo	startInfo;
			guint32				dataNum;
			gint32				i;
			guchar*				data[CtDdI2c_D_CT_DD_I2C_MAX_DATA_NUM];

			ch						= atoi( argv[2] );
			startInfo.rwMode		= (I2cRwMode)atoi( argv[3] );
			data[0]					= (guchar*)strtoul(argv[4], &endstr, 16);
			startInfo.rwDataLen	= atoi( argv[5] );
			dataNum				= atoi(argv[6]);
			startInfo.timeout		= 500;

			// Check test data size
			if( startInfo.rwDataLen > CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN ){
				Ddim_Print(("rwDataLen is over test size(%d)\n", CtDdI2c_D_CT_DD_I2C_MAX_DATA_LEN));
				return;
			}
			if( dataNum > CtDdI2c_D_CT_DD_I2C_MAX_DATA_NUM ){
				Ddim_Print(("dataNum is over test size(%d)\n", CtDdI2c_D_CT_DD_I2C_MAX_DATA_NUM));
				return;
			}

			// Set data address
			for( i = 1; i < dataNum; i++ ){
				data[i] = data[i-1] + startInfo.rwDataLen;
			}

			if( startInfo.rwMode == DdI2cCtrl_RW_MODE_WRITE ){
				// Set send test data
				ctDdI2cSetWriteTestData( startInfo.rwDataLen, data, dataNum );
			}

			// Start Master
			ret = ctDdI2cMasterStart( ch, &startInfo, data, dataNum );
			if( ret == DriverCommon_D_DDIM_OK ){
				// Start OK
				Ddim_Print(("Dd_I2C_Start_Master: OK\n"));
				// Print result
				ctDdI2cDataPrint( startInfo.rwMode, dataNum, startInfo.rwDataLen, data );
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
		ch = atoi( argv[2] );

		ret = Dd_I2C_Stop_Master( ch );
		if( ret == DriverCommon_D_DDIM_OK ){
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
		if( argc == 3 ){
			ch = atoi( argv[2] );

			ret = Dd_I2C_Start_Slave( ch );
			if( ret == DriverCommon_D_DDIM_OK ){
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
		ch = atoi( argv[2] );

		ret = Dd_I2C_Stop_Slave( ch );
		if( ret == DriverCommon_D_DDIM_OK ){
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
			ch = atoi(argv[3]);

			Dd_I2C_Set_Toggle_SCL( ch );
			Ddim_Print((" IO_PERI.I2C[%d].CST.bit.TGSCL = %d\n", ch, IO_PERI.I2C[ch].CST.bit.TGSCL ));
		}
		else if( strcmp(argv[2], "scl") == 0 ){
			guchar scl = atoi(argv[4]);
			ch = atoi(argv[3]);

			Dd_I2C_Set_SCL( ch, scl );
			Ddim_Print((" IO_PERI.I2C[%d].CTL2.bit.SCLFRQ = %d\n", ch, IO_PERI.I2C[ch].CTL2.bit.SCLFRQ ));
		}
	}
	else if( strcmp(argv[1], "get") == 0 ){
		if( strcmp(argv[2], "tsda") == 0 ){
			guchar tsda;
			ch = atoi(argv[3]);
#ifdef D_DD_I2C_PC_DEBUG
			IO_PERI.I2C[ch].CST.bit.TSDA = 1;
#endif
			Dd_I2C_Get_Test_SDA( ch, &tsda );
			Ddim_Print((" IO_PERI.I2C[%d].CST.bit.TSDA = %d\n", ch, tsda ));
		}
		else if( strcmp(argv[2], "scl") == 0 ){
			guchar scl;
			ch = atoi(argv[3]);

			Dd_I2C_Get_SCL( ch, &scl );
			Ddim_Print((" IO_PERI.I2C[%d].CTL2.bit.SCLFRQ = %d\n", ch, scl ));
		}
		else if( strcmp(argv[2], "cause") == 0 ){
			ch = atoi(argv[3]);
			Ddim_Print((" Error Cause[%d] = 0x%08X\n", ch, dd_i2c_get_error_cause(priv->ddI2c, ch ) ));
		}
	}
	else if( strcmp(argv[1], "inthdr") == 0 ){
		guchar ch = atoi(argv[2]);

#ifdef D_DD_I2C_PC_DEBUG
		guchar mode = strtoul( argv[3], &endstr, 16 );;

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
		gint32 ret;
		DdI2cCtrlMaster ctrlMaster;
		DdI2cCtrlSlave ctrlSlave;
		DdI2cCtrlSmbus ctrlSmbus;
		DdI2cStartInfo startInfo;
		guchar val;

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

		ret = dd_i2c_start_master(priv->ddI2c, 3, &startInfo );
		Ddim_Print(("Dd_I2C_Start_Master: CH NG(%d)\n", ret));

		ret = dd_i2c_start_master(priv->ddI2c, 2, NULL );
		Ddim_Print(("Dd_I2C_Start_Master: Pointer NG(%d)\n", ret));

		ret = Dd_I2C_Ctrl_Slave( 2, &ctrlSlave );
		ret = dd_i2c_start_master(priv->ddI2c, 2, &startInfo );
		Ddim_Print(("Dd_I2C_Start_Master: SIDE NG(%d)\n", ret));

		ret = dd_i2c_start_master(priv->ddI2c, 2, &startInfo );
		ret = dd_i2c_start_master(priv->ddI2c, 2, &startInfo );
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

CtDdI2c *ct_dd_i2c_new(void) 
{
    CtDdI2c *self = g_object_new(CT_TYPE_DD_I2C, NULL);
    return self;
}
