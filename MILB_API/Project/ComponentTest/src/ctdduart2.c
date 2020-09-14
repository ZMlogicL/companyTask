/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtDdUart2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "stdlib.h"
#include "string.h"
// #include "dd_uart.h"
#include "../../Project/DeviceDriver/Peripheral/src/dduart.h"
#include "../../DeviceDriver/Peripheral/src/dduartcolabo.h"
#include "../../Project/DeviceDriver/Peripheral/src/dduartinterrupt.h"
#include "../../DeviceDriver/Peripheral/src/dduartbranch.h"

// #include "dd_hdmac1.h"
// #include "dd_gic.h"
// #include "dd_top.h"
#include "../../DeviceDriver/Peripheral/src/ddhdmac1.h"
#include "../../DeviceDriver/ARM/src/ddgic.h"
#include "../../DeviceDriver/LSITop/src/ddtop.h"
#include "uart_csio.h"
#include "ctdduart.h"
// #include "dd_tmr32.h"
#include "../../DeviceDriver/Peripheral/src/ddtmr32.h"


#include "ctdduart.h"

#include "ctdduart2.h"
#include "ctdduart1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdUart2, ct_dd_uart2);
#define CT_DD_UART2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdUart2Private,CT_TYPE_DD_UART2))

struct _CtDdUart2Private
{

};

/*
DECLS
*/

static kint32 		ctUartDmaSendProcess( kuchar ut_ch, CtDdUart2 *self );
static void 		ctUartRestartFifo( kuchar ut_ch );
static void 		ctUartRestartFifo2( kuchar ut_ch );
static kint32 		ctUartProcess( CtDdUart2 *self );
static kint32 		ctUartSimpleProcess( CtDdUart2 *self );
static kint32 		ctStartSendDmaNormal(CtDdUart2 *self, kuint32 cbflg);
static kint32 		ctStartRecvDmaNormal(CtDdUart2 *self, kuint32 cbflg);

static void ct_dd_uart2_constructor(CtDdUart2 *self) 
{
//	CtDdUart2Private *priv = CT_DD_UART2_GET_PRIVATE(self);
	self->tmout = D_DDIM_USER_SEM_WAIT_POL;
}

static void ct_dd_uart2_destructor(CtDdUart2 *self) 
{
//	CtDdUart2Private *priv = CT_DD_UART2_GET_PRIVATE(self);
	self = 	NULL;
}

/*
IMPL//todo
*/

// static kint32 ct_uart_dma_send_process( kuchar ut_ch, kuchar dma_ch )
static kint32 ctUartDmaSendProcess( kuchar ut_ch, CtDdUart2 *self )
{
	kint32 ret= 0;
	ULONG intid;
	ULONG dma_intid;

	intid = DdGic_INTID_UART_CH0_TRANSMISSION_INT + ut_ch;
	dma_intid = DdGic_INTID_HDMAC1_CH0_INT + self->dma_ch;

	dd_gic_ctrl((DdGicIntid)intid, 0, C_PRI30, 0x2);			/** UART interrupt disable */
	dd_gic_ctrl((DdGicIntid)dma_intid, 1, C_PRI30, 0x2);		/** HDMAC1 interrupt enable */

	ret = dd_uart_put_str_dma(ut_ch, self->dma_ch);

	dd_gic_ctrl((DdGicIntid)intid, 1, C_PRI30, 0x2);			/** UART interrupt enable */
	dd_gic_ctrl((DdGicIntid)dma_intid, 0, C_PRI30, 0x2);		/** HDMAC1 interrupt disable */

	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Put_Str_DMA error=0x%x\n", ret) );
		return -1;
	}

	return 0;
}

static void ctUartRestartFifo( kuchar ut_ch )
{
	DdUartMng		uart_mng;
	DdUartFifoCtrl	fifo_ctrl;

	memset( &uart_mng, 0, sizeof(DdUartMng));
	memset( &fifo_ctrl, 0, sizeof(DdUartFifoCtrl));

	// Close
	dd_uart_close(ut_ch);

	// Set UART control data
	uart_mng.baudRate			= DdUart_BAUD_RATE_115200;		// Baud rate
	uart_mng.psendCallback		= NULL;								// Send callback function pointer
	uart_mng.preceiveCallback	= ct_dd_uart_receive_callback_dma_cb;				// Receive callback function pointer
	uart_mng.receiveBuffAddr	= &gUartRBuff[0];					// Receive buffer address
	uart_mng.receiveBuffSize	= sizeof(gUartRBuff);				// Receive buffer size
	uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;			// Send_buff_addr
	uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;					// Send buffer size
	uart_mng.autoEcho			= DdUart_AUTO_ECHO_ON;			// Auto Echo
	uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;			// Save to the buffer
	uart_mng.mode				= DdUart_MODE_NORMAL;			// UART Nomal Mode
	uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;		// Transferring Direction, LSB first or MSB first
	uart_mng.stopBitLength	= DdUart_STOP_BIT_1;				// Stop bit length
	uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;		// Parity bit type
	uart_mng.dataLength		= DdUart_DATA_LENGTH_8;			// Data Length
	uart_mng.extClk			= 0;								// Internal clock
	uart_mng.invNrz			= 0;								// NRZ

	fifo_ctrl.fsel				= 0;
	fifo_ctrl.fe1				= 1;
	fifo_ctrl.fe2				= 0;
	fifo_ctrl.flste				= 0;
	fifo_ctrl.fset				= 0;
	fifo_ctrl.fbyteRecv		= 0;
	uart_mngfifoCtrl			= &fifo_ctrl;						// FIFO Setting

	// Start UART
	dd_uart_branch_open(ut_ch, D_DDIM_USER_SEM_WAIT_POL);
	dd_uart_ctrl(ut_ch, &uart_mng);
	dd_uart_branch_start(ut_ch);

	return;
}

static void ctUartRestartFifo2( kuchar ut_ch )
{
	DdUartMng		uart_mng;
	DdUartFifoCtrl	fifo_ctrl;

	memset( &uart_mng, 0, sizeof(DdUartMng));
	memset( &fifo_ctrl, 0, sizeof(DdUartFifoCtrl));

	// Close
	dd_uart_close(ut_ch);

	// Set UART control data
	uart_mng.baudRate			= DdUart_BAUD_RATE_115200;		// Baud rate
	uart_mng.psendCallback		= NULL;								// Send callback function pointer
	uart_mng.preceiveCallback	= ct_dd_uart_receive_callback_dma_cb;				// Receive callback function pointer
	uart_mng.receiveBuffAddr	= &gUartRBuff[0];					// Receive buffer address
	uart_mng.receiveBuffSize	= sizeof(gUartRBuff);				// Receive buffer size
	uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;			// Send_buff_addr
	uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;					// Send buffer size
	uart_mng.autoEcho			= DdUart_AUTO_ECHO_ON;			// Auto Echo
	uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;			// Save to the buffer
	uart_mng.mode				= DdUart_MODE_NORMAL;			// UART Nomal Mode
	uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;		// Transferring Direction, LSB first or MSB first
	uart_mng.stopBitLength	= DdUart_STOP_BIT_1;				// Stop bit length
	uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;		// Parity bit type
	uart_mng.dataLength		= DdUart_DATA_LENGTH_8;			// Data Length
	uart_mng.extClk			= 0;								// Internal clock
	uart_mng.invNrz			= 0;								// NRZ

	fifo_ctrl.fsel				= 0;
	fifo_ctrl.fe1				= 1;
	fifo_ctrl.fe2				= 1;
	fifo_ctrl.flste				= 0;
	fifo_ctrl.fset				= 0;
	fifo_ctrl.fbyteRecv		= 3;
	uart_mngfifoCtrl			= &fifo_ctrl;						// FIFO Setting

	// Start UART
	dd_uart_branch_open(ut_ch, D_DDIM_USER_SEM_WAIT_POL);
	dd_uart_ctrl(ut_ch, &uart_mng);
	dd_uart_branch_start(ut_ch);

	return;
}

// static kint32 ct_uart_process( kuchar auto_echo, kuchar save_buff, kuchar fifo, kuchar send_int )
static kint32 ctUartProcess( CtDdUart2 *self )
{
	kint32				ret;
	DdUartMng		uart_mng;
	DdUartFifoCtrl fifo_ctrl;

	memset(&uart_mng, 0, sizeof(DdUartMng));
	memset(&fifo_ctrl, 0, sizeof(DdUartFifoCtrl));

	/* Open */
	ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
		return ret;
	}
	/* Control */
	uart_mng.baudRate = DdUart_BAUD_RATE_115200;
	if(self->send_int == 1){
		uart_mng.psendCallback = ct_dd_uart_send_callback_cb;
	}
	else {
		uart_mng.psendCallback = NULL;
	}
	if( self->auto_echo == 0 ){
		uart_mng.preceiveCallback = ct_dd_uart_receive_callback_cb;		// for auto echo on
	}
	else {
		uart_mng.preceiveCallback = ct_dd_uart_receive_callback_echo_cb;// for auto echo off
	}
	uart_mng.receiveBuffAddr			= &gUartRBuff[0];
	uart_mng.receiveBuffSize			= sizeof(gUartRBuff);
	uart_mng.sendBuffAddr				= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
	uart_mng.sendBuffSize				= CtDdUart_D_UART_SRC_SIZE;
	uart_mng.autoEcho					= (DdUart_AUTO_ECHO)(self->auto_echo);
	uart_mng.saveBuff					= (DdUart_SAVE2BUFFER)(self->save_buff);
	uart_mng.mode						= DdUart_MODE_NORMAL;
	uart_mng.bitDirection				= DdUart_BIT_DIR_LSB_FIRST;
	uart_mng.stopBitLength			= DdUart_STOP_BIT_1;
	uart_mng.dataLength				= DdUart_DATA_LENGTH_8;
	uart_mng.parityBit					= DdUart_PARITY_BIT_NONE;

	if(self->fifo == 1){
		uart_mngfifoCtrl				= &fifo_ctrl;
		uart_mngfifoCtrl->fsel		= 0;
		uart_mngfifoCtrl->fe1			= 1;
		uart_mngfifoCtrl->fe2			= 0;
		uart_mngfifoCtrl->flste		= 0;
		uart_mngfifoCtrl->fset		= 0;
		uart_mngfifoCtrl->fbyteRecv	= 0;
	}
	else{
		uart_mngfifoCtrl = NULL;
	}

	ret = dd_uart_ctrl( gUARTCh, &uart_mng );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
		return ret;
	}

	/* Start */
	ret = dd_uart_branch_start( gUARTCh );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
		return ret;
	}

	return ret;
}


// static kint32 ct_uart_simple_process( kuchar ch, kuchar auto_echo, kuchar save_buff )
static kint32 ctUartSimpleProcess( CtDdUart2 *self )
{
	kint32					ret ;
	DdUartMngSimple	uart_mng_simple;

	/* Open */
	ret = dd_uart_branch_open( self->ch, D_DDIM_USER_SEM_WAIT_POL );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
		return ret;
	}
	/* Control */
	uart_mng_simple.baudRate = DdUart_BAUD_RATE_115200;
	if( self->auto_echo == DdUart_AUTO_ECHO_ON ){
		uart_mng_simple.preceiveCallback = ct_dd_uart_receive_callback_cb;		// for auto echo on
	}
	else {
		uart_mng_simple.preceiveCallback = ct_dd_uart_receive_callback_echo_cb;// for auto echo off
	}
	uart_mng_simple.receiveBuffAddr	= &gUartRBuff[0];
	uart_mng_simple.receiveBuffSize	= sizeof(gUartRBuff);
	uart_mng_simple.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
	uart_mng_simple.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
	uart_mng_simple.autoEcho			= (DdUart_AUTO_ECHO)(self->auto_echo);
	uart_mng_simple.saveBuff			= (DdUart_SAVE2BUFFER)(self->save_buff);
	uart_mng_simple.stopBitLength		= DdUart_STOP_BIT_1;
	uart_mng_simple.dataLength			= DdUart_DATA_LENGTH_8;
	uart_mng_simple.parityBit			= DdUart_PARITY_BIT_NONE;

	ret = dd_uart_branch_initialize_simple( self->ch, &uart_mng_simple );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Util_Set error=0x%x\n", ret) );
		return ret;
	}

	/* Start */
	ret = dd_uart_branch_start( self->ch );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
		return ret;
	}

	return ret;
}

// static kint32 ct_start_send_dma_normal(kuchar ch, kuchar dma_ch, DdUartBaudRate baud_rate, kuchar* data_addr, kuint32 data_num, kuint32 cbflg)
static kint32 ctStartSendDmaNormal(CtDdUart2 *self, kuint32 cbflg)
{
	kint32				ret = D_DDIM_OK;
	DdUartMng		uart_mng;
	DdUartFifoCtrl	fifo_ctrl;
	ULONG				intid;

	Ddim_Print( ("ct_start_send_dma\n") );
	Ddim_Print( ("self->ch        = %d\n",		self->ch) );
	Ddim_Print( ("self->dma_ch    = %d\n",		self->dma_ch) );
	Ddim_Print( ("self->baud_rate = %d\n",		self->baud_rate) );
	Ddim_Print( ("data_addr = %p\n",		(kuchar*)&self->data_addr) );
	Ddim_Print( ("data_num  = 0x%x\n",		(kuint32)self->data_num) );

	memset(&uart_mng, 0, sizeof(DdUartMng));
	memset(&fifo_ctrl, 0, sizeof(DdUartFifoCtrl));

	/* Control */
	uart_mng.baudRate			= self->baud_rate;
	uart_mng.psendCallback		= NULL;
	uart_mng.preceiveCallback	= NULL;
	uart_mng.receiveBuffAddr	= NULL;
	uart_mng.receiveBuffSize	= 0;
	uart_mng.sendBuffAddr		= NULL;
	uart_mng.sendBuffSize		= 0;
	uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
	uart_mng.saveBuff			= DdUart_SAVE2BUFFER_DIS;
	uart_mng.mode				= DdUart_MODE_NORMAL;
	uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
	uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
	uart_mng.dataLength		= DdUart_DATA_LENGTH_8;
	uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

	fifo_ctrl.fsel				= 0;
	fifo_ctrl.fe1				= 1;
	fifo_ctrl.fe2				= 1;
	fifo_ctrl.flste				= 0;
	fifo_ctrl.fset				= 0;
//	fifo_ctrl.fbyteRecv		= 128;
	fifo_ctrl.fbyteRecv		= 64;
	uart_mngfifoCtrl			= &fifo_ctrl;

	if(cbflg != 0){
		uart_mngsendDmaCallback	= ct_dd_uart_send_dma_callback_cb;
		uart_mngrecvDmaCallback	= ct_dd_uart_recv_dma_callback_cb;
	}

	ret = dd_uart_ctrl( gUARTCh, &uart_mng );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
		return ret;
	}

	ret = dd_uart_branch_set_send_data_dma( self->ch, (kuchar*)self->data_addr, (kuint32)self->data_num );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Set_Send_Data_DMA error=0x%x\n", ret) );
		return ret;
	}

	intid = DdGic_INTID_UART_CH0_TRANSMISSION_INT + self->ch;
	dd_gic_ctrl((DdGicIntid)intid, 0, -1, 0x2);				/** UART interrupt disable */

	ret = dd_uart_colabo_start_send_dma( self->ch, self->dma_ch );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Start_Send_DMA error=0x%x\n", ret) );
		return ret;
	}

	return ret;
}

// static kint32 ct_start_recv_dma_normal(kuchar ch, kuchar dma_ch, DdUartBaudRate baud_rate, kuchar* data_addr, kuint32 data_num, kuint32 cbflg)
static kint32 ctStartRecvDmaNormal(CtDdUart2 *self, kuint32 cbflg)
{
	kint32				ret = D_DDIM_OK;
	DdUartMng		uart_mng;
	DdUartFifoCtrl	fifo_ctrl;
	ULONG				intid;

	Ddim_Print( ("ct_start_recv_dma\n") );
	Ddim_Print( ("self->ch        = %d\n",		self->ch) );
	Ddim_Print( ("self->dma_ch    = %d\n",		self->dma_ch) );
	Ddim_Print( ("self->baud_rate = %d\n",		self->baud_rate) );
	Ddim_Print( ("data_addr = %p\n",		(kuchar*)self->data_addr) );
	Ddim_Print( ("data_num  = 0x%x\n",		(kuint32)self->data_num) );

	memset(&uart_mng, 0, sizeof(DdUartMng));
	memset(&fifo_ctrl, 0, sizeof(DdUartFifoCtrl));

	/* Control */
	uart_mng.baudRate			= self->baud_rate;
	uart_mng.psendCallback		= NULL;
	uart_mng.preceiveCallback	= NULL;
	uart_mng.receiveBuffAddr	= NULL;
	uart_mng.receiveBuffSize	= 0;
	uart_mng.sendBuffAddr		= NULL;
	uart_mng.sendBuffSize		= 0;
	uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
	uart_mng.saveBuff			= DdUart_SAVE2BUFFER_DIS;
	uart_mng.mode				= DdUart_MODE_NORMAL;
	uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
	uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
	uart_mng.dataLength		= DdUart_DATA_LENGTH_8;
	uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

	fifo_ctrl.fsel				= 0;
	fifo_ctrl.fe1				= 1;
	fifo_ctrl.fe2				= 1;
	fifo_ctrl.flste				= 0;
	fifo_ctrl.fset				= 0;
//	fifo_ctrl.fbyteRecv		= 128;
	fifo_ctrl.fbyteRecv		= 64;
	uart_mngfifoCtrl			= &fifo_ctrl;

	if(cbflg != 0){
		uart_mngsendDmaCallback	= ct_dd_uart_send_dma_callback_cb;
		uart_mngrecvDmaCallback	= ct_dd_uart_recv_dma_callback_cb;
	}

	ret = dd_uart_ctrl( gUARTCh, &uart_mng );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
		return ret;
	}

	ret = dd_uart_colabo_set_recv_data_dma( self->ch, (kuchar*)self->data_addr, (kuint32)self->data_num );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Set_Recv_Data_DMA error=0x%x\n", ret) );
		return ret;
	}

	intid = DdGic_INTID_UART_CH0_RECEPTION_INT + self->ch;
	dd_gic_ctrl((DdGicIntid)intid, 0, -1, 0x2);				/** UART interrupt disable */

	ret = dd_uart_colabo_start_recv_dma( self->ch, self->dma_ch );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Start_Recv_DMA error=0x%x\n", ret) );
		return ret;
	}

	return D_DDIM_OK;
}

/*
PUBLIC//todo
*/

void ct_dd_uart2_main_b( CtDdUart2 *self,int argc, char** argv )
{
    /*kint32				ret;
	kuint32				length;
	kuchar				ch;
	kuchar				dma_ch;
	kuchar				num;
	CHAR				data;
	kuint32				count;
	kuchar				auto_echo;
	kuchar				save_buff;
	kuchar				fifo;
	kuchar				send_int;
	// kint32				tmout = D_DDIM_USER_SEM_WAIT_POL;
	// USHORT				baudrate;
	// kuchar				slave_addr;
	// ULONG				s_write_pos;
	DdUartMng		uart_mng;
	DdUartBaudRate	baud_rate;
	ULONG				data_addr;
	ULONG				data_num;*/
    if( strcmp(argv[1], "start") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = dd_uart_branch_start( gUARTCh );
		if (self->ret !=D_DDIM_OK) {
			Ddim_Print(("UART Start ERR. self->ret=0x%x\n", self->ret));
		}
	}
	else if( strcmp(argv[1], "stop") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = dd_uart_colabo_stop( gUARTCh );
		if (self->ret !=D_DDIM_OK) {
			Ddim_Print(("UART Stop ERR. self->ret=0x%x\n", self->ret));
		}
	}
	else if( strcmp(argv[1], "start_test") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = dd_uart_close( gUARTCh );
		if (self->ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_UART_Close ERR. self->ret=0x%x\n", self->ret) );
		}

		self->auto_echo = (DdUart_AUTO_ECHO)( atoi(argv[3]) );
		self->fifo = (DdUart_AUTO_ECHO)( atoi(argv[4]) );
		self->send_int = (DdUart_AUTO_ECHO)( atoi(argv[5]) );
		self->save_buff = (DdUart_SAVE2BUFFER)( atoi(argv[6]) );
		ctUartProcess( self );
	}
	else if( strcmp(argv[1], "start_send_dma") == 0 ){
		gUARTCh = atoi( argv[2] );
		self->dma_ch = atoi( argv[3] );
		self->baud_rate = (DdUartBaudRate)atoi( argv[4] );
		sscanf(argv[5], "%lx", (ULONG*)&(self->data_addr));
		sscanf(argv[6], "%lx", (ULONG*)&(self->data_num));
		self->ch = gUARTCh;
		// ret = ct_start_send_dma_normal( gUARTCh, dma_ch, baud_rate, (kuchar*)data_addr, data_num, atoi(argv[7]) );
		self->ret = ctStartSendDmaNormal( self, atoi(argv[7]) );
		Ddim_Print( ("start_send_dma end. self->ret=0x%x\n", self->ret) );
	}
	else if( strcmp(argv[1], "start_recv_dma") == 0 ){
		gUARTCh = atoi( argv[2] );
		self->dma_ch = atoi( argv[3] );
		self->baud_rate = (DdUartBaudRate)atoi( argv[4] );
		sscanf(argv[5], "%lx", (ULONG*)&(self->data_addr));
		sscanf(argv[6], "%lx", (ULONG*)&(self->data_num));
		self->ch = gUARTCh;
		// ret = ct_start_recv_dma_normal( gUARTCh, dma_ch, baud_rate, (kuchar*)data_addr, data_num, atoi(argv[7]) );
		self->ret = ctStartRecvDmaNormal( self, atoi(argv[7]) );
		Ddim_Print( ("start_recv_dma end. self->ret=0x%x\n", self->ret) );
	}
	else if( strcmp(argv[1], "set_test") == 0 ){
		/* channel */
		self->ch = atoi( argv[2] );

		/* Test number */
		self->num = atoi( argv[3] );
		
		CtDdUart1* ctDdUart1 = ct_dd_uart1_new();
		ct_dd_uart1_set_ctdduart2(ctDdUart1,self);
		self->ret = ct_dd_uart1_process_multi( ctDdUart1 );
		k_object_unref(ctDdUart1);
		if (self->ret != D_DDIM_OK) {
			Ddim_Print( ("ctUartProcess ERR. self->ret=0x%x\n", self->ret) );
		}
	}
	else if( strcmp(argv[1], "put") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = dd_uart_put_char( gUARTCh, argv[3][0] );
		if (self->ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_UART_Put_Char ERR. self->ret=0x%x\n", self->ret) );
		}
	}
	else if( strcmp(argv[1], "putbuf") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		Ddim_Print( ("UART PUT TEST=%s\n", argv[3]) );
	}
	else if( strcmp(argv[1], "putdma_rw") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );
		self->dma_ch = atoi( argv[3] );

		memset( (kint32*)CtDdUart_D_UART_SRC_ADDR, '\0', CtDdUart_D_UART_SRC_SIZE);

		// restart
		ctUartRestartFifo2(gUARTCh);

		dd_uart_branch_set_str( gUARTCh, 'U' );
		dd_uart_branch_set_str( gUARTCh, 'A' );
		dd_uart_branch_set_str( gUARTCh, 'R' );
		dd_uart_branch_set_str( gUARTCh, 'T' );
		dd_uart_branch_set_str( gUARTCh, ' ' );
		dd_uart_branch_set_str( gUARTCh, 'P' );
		dd_uart_branch_set_str( gUARTCh, 'U' );
		dd_uart_branch_set_str( gUARTCh, 'T' );
		dd_uart_branch_set_str( gUARTCh, ' ' );
		dd_uart_branch_set_str( gUARTCh, 'D' );
		dd_uart_branch_set_str( gUARTCh, 'M' );
		dd_uart_branch_set_str( gUARTCh, 'A' );
		dd_uart_branch_set_str( gUARTCh, ' ' );
		dd_uart_branch_set_str( gUARTCh, 'T' );
		dd_uart_branch_set_str( gUARTCh, 'E' );
		dd_uart_branch_set_str( gUARTCh, 'S' );
		dd_uart_branch_set_str( gUARTCh, 'T' );
		dd_uart_branch_set_str( gUARTCh, '\n' );

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}
	}
	else if( strcmp(argv[1], "putdma_max_1") == 0 ){

		/* channel */
		gUARTCh = atoi( argv[2] );
		self->dma_ch = atoi( argv[3] );

		memset( (kint32*)CtDdUart_D_UART_SRC_ADDR, '\0', CtDdUart_D_UART_SRC_SIZE);

		// restart
		ctUartRestartFifo(gUARTCh);

		for(self->count = 0; self->count < 4095; (self->count)++) {
			if (self->count == 4094) {
				dd_uart_branch_set_str( gUARTCh, 'E' );
			}
			else {
				dd_uart_branch_set_str( gUARTCh, 'A' );
			}
		}

		dd_uart_branch_set_str( gUARTCh, '\n' );

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}

		dd_uart_branch_set_str( gUARTCh, 'B' );

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}

		dd_uart_branch_set_str( gUARTCh, '\n' );
		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}
	}
	else if( strcmp(argv[1], "putdma_1_max") == 0 ){

		/* channel */
		gUARTCh = atoi( argv[2] );
		self->dma_ch = atoi( argv[3] );

		memset( (kint32*)CtDdUart_D_UART_SRC_ADDR, '\0', CtDdUart_D_UART_SRC_SIZE);

		// restart
		ctUartRestartFifo(gUARTCh);

		dd_uart_branch_set_str( gUARTCh, 'B' );

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}

		for(self->count = 0; self->count < 4095; (self->count)++) {
			if (self->count == 4094) {
				dd_uart_branch_set_str( gUARTCh, 'E' );
			}
			else {
				dd_uart_branch_set_str( gUARTCh, 'A' );
			}
		}
		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}

		dd_uart_branch_set_str( gUARTCh, '\n' );
		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}
	}
	else if( strcmp(argv[1], "putdma_rw_0") == 0 ){

		/* channel */
		gUARTCh = atoi( argv[2] );
		self->dma_ch = atoi( argv[3] );

		memset( (kint32*)CtDdUart_D_UART_SRC_ADDR, '\0', CtDdUart_D_UART_SRC_SIZE);

		// restart
		ctUartRestartFifo(gUARTCh);

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}
	}
	else if( strcmp(argv[1], "putdma_wr") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );
		self->dma_ch = atoi( argv[3] );

		memset( (kint32*)CtDdUart_D_UART_SRC_ADDR, '\0', CtDdUart_D_UART_SRC_SIZE);

		// restart
		ctUartRestartFifo2(gUARTCh);

		for(self->count = 0; self->count < 3000; (self->count)++) {
			dd_uart_branch_set_str( gUARTCh, 'A' );
			if (self->count == 2999) {
				dd_uart_branch_set_str( gUARTCh, ' ' );
				dd_uart_branch_set_str( gUARTCh, 'E' );
				dd_uart_branch_set_str( gUARTCh, 'N' );
				dd_uart_branch_set_str( gUARTCh, 'D' );
				dd_uart_branch_set_str( gUARTCh, '\n' );
			}
		}

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}

		for(self->count = 0; self->count < 3000; (self->count)++) {
			dd_uart_branch_set_str( gUARTCh, 'B' );
			if (self->count == 2999) {
				dd_uart_branch_set_str( gUARTCh, ' ' );
				dd_uart_branch_set_str( gUARTCh, 'E' );
				dd_uart_branch_set_str( gUARTCh, 'N' );
				dd_uart_branch_set_str( gUARTCh, 'D' );
				dd_uart_branch_set_str( gUARTCh, '\n' );
			}
		}

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}
	}
	else if( strcmp(argv[1], "putover") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );
		self->length = atoi( argv[4] );

		for(self->count = 0; self->count < self->length; (self->count)++) {
			self->ret = dd_uart_branch_set_str( gUARTCh, argv[3][0] );
			if( self->ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Str error=0x%x\n", self->ret) );
				return ;
			}
		}
	}
	else if( strcmp(argv[1], "get") == 0 ){
		/* channel */
		self->ch = atoi( argv[2] );

		Ddim_Print( ("UART GET TEST=%s\n", argv[3]) );
	}
	else if( strcmp(argv[1], "send") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = dd_uart_branch_put_str( gUARTCh );
		self->ret = dd_uart_branch_put_str( gUARTCh );
		if( self->ret != D_DDIM_OK ){
			Ddim_Print( ("Dd_UART_Put_Str error=0x%x\n", self->ret) );
			return ;
		}
	}
	else if( strcmp(argv[1], "receive") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = dd_uart_branch_get_char( gUARTCh, &self->data );
		if( self->ret != D_DDIM_OK ){
			Ddim_Print( ("Dd_UART_Get_Char error=0x%x\n", self->ret) );
			return ;
		}
	}
	else if ( strcmp(argv[1], "get_ctrl") == 0 ){
		DdUartFifoCtrl fifo_ctrl;

		self->uart_mngfifoCtrl = &fifo_ctrl;

		/* ch number */
		self->ch = atoi( argv[2] );

		self->ret = dd_uart_branch_get_ctrl(self->ch, &self->uart_mng);
		if( self->ret != D_DDIM_OK ){
			Ddim_Print( ("Dd_UART_Get_Ctrl error=0x%x\n", self->ret) );
			return ;
		}

		Ddim_Print(("UART Ctrl_Get OK.\n"));
		Ddim_Print(("UART baud_rate             =%d\n", self->uart_mng.baudRate));
		Ddim_Print(("UART psendCallback        =%p\n", self->uart_mng.psendCallback));
		Ddim_Print(("UART preceiveCallback     =%p\n", self->uart_mng.preceiveCallback));
		Ddim_Print(("UART receiveBuffAddr     =%p\n", self->uart_mng.receiveBuffAddr));
		Ddim_Print(("UART receiveBuffSize     =%d\n", self->uart_mng.receiveBuffSize));
		Ddim_Print(("UART sendBuffAddr        =%p\n", self->uart_mng.sendBuffAddr));
		Ddim_Print(("UART sendBuffSize        =%d\n", self->uart_mng.sendBuffSize));
		Ddim_Print(("UART autoEcho             =%d\n", self->uart_mng.autoEcho));
		Ddim_Print(("UART saveBuff             =%d\n", self->uart_mng.saveBuff));
		Ddim_Print(("UART mode                  =%d\n", self->uart_mng.mode));
		Ddim_Print(("UART bitDirection         =%d\n", self->uart_mng.bitDirection));
		Ddim_Print(("UART stopBitLength       =%d\n", self->uart_mng.stopBitLength));
		Ddim_Print(("UART dataLength           =%d\n", self->uart_mng.dataLength));
		Ddim_Print(("UART parityBit            =%d\n", self->uart_mng.parityBit));
		Ddim_Print(("UART extClk               =%d\n", self->uart_mng.extClk));
		Ddim_Print(("UART invNrz               =%d\n", self->uart_mng.invNrz));
		Ddim_Print(("UART flowEnable           =%d\n", self->uart_mng.flowEnable));
		Ddim_Print(("UART fifo_ctrl->fsel       =%d\n", self->uart_mngfifoCtrl->fsel));
		Ddim_Print(("UART fifo_ctrl->flste      =%d\n", self->uart_mngfifoCtrl->flste));
		Ddim_Print(("UART fifo_ctrl->fset       =%d\n", self->uart_mngfifoCtrl->fset));
		Ddim_Print(("UART fifo_ctrl->fe2        =%d\n", self->uart_mngfifoCtrl->fe2));
		Ddim_Print(("UART fifo_ctrl->fe1        =%d\n", self->uart_mngfifoCtrl->fe1));
		Ddim_Print(("UART fifo_ctrl->fbyteRecv =%d\n", self->uart_mngfifoCtrl->fbyteRecv));
		Ddim_Print(("UART send_dma_callback     =%p\n", self->uart_mngsendDmaCallback));
		Ddim_Print(("UART recv_dma_callback     =%p\n", self->uart_mngrecvDmaCallback));
	}
	else if ( strcmp(argv[1], "simple") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = dd_uart_close( gUARTCh );
		if (self->ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_UART_Close ERR. self->ret=0x%x\n", self->ret) );
		}

		self->auto_echo = (DdUart_AUTO_ECHO)( atoi(argv[3]) );
		self->save_buff = (DdUart_SAVE2BUFFER)( atoi(argv[4]) );
		self->ch = gUARTCh;
		ctUartSimpleProcess( self );
	}
}

CtDdUart2* ct_dd_uart2_new(void) 
{
    CtDdUart2 *self = k_object_new_with_private(CT_TYPE_DD_UART2, sizeof(CtDdUart2Private));
    return self;
}
