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
#include "dd_uart.h"
#include "dd_hdmac1.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "uart_csio.h"
#include "ctdduart.h"
#include "dd_tmr32.h"

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

	intid = E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT + ut_ch;
	dma_intid = E_DD_GIC_INTID_HDMAC1_CH0_INT + self->dma_ch;

	Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 0, D_DD_GIC_PRI30, 0x2);			/** UART interrupt disable */
	Dd_GIC_Ctrl((E_DD_GIC_INTID)dma_intid, 1, D_DD_GIC_PRI30, 0x2);		/** HDMAC1 interrupt enable */

	ret = Dd_UART_Put_Str_DMA(ut_ch, self->dma_ch);

	Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 1, D_DD_GIC_PRI30, 0x2);			/** UART interrupt enable */
	Dd_GIC_Ctrl((E_DD_GIC_INTID)dma_intid, 0, D_DD_GIC_PRI30, 0x2);		/** HDMAC1 interrupt disable */

	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Put_Str_DMA error=0x%x\n", ret) );
		return -1;
	}

	return 0;
}

static void ctUartRestartFifo( kuchar ut_ch )
{
	T_DD_UART_MNG		uart_mng;
	T_DD_UART_FIFO_CTRL	fifo_ctrl;

	memset( &uart_mng, 0, sizeof(T_DD_UART_MNG));
	memset( &fifo_ctrl, 0, sizeof(T_DD_UART_FIFO_CTRL));

	// Close
	Dd_UART_Close(ut_ch);

	// Set UART control data
	uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;		// Baud rate
	uart_mng.psend_callback		= NULL;								// Send callback function pointer
	uart_mng.preceive_callback	= ct_dd_uart_receive_callback_dma_cb;				// Receive callback function pointer
	uart_mng.receive_buff_addr	= &gUartRBuff[0];					// Receive buffer address
	uart_mng.receive_buff_size	= sizeof(gUartRBuff);				// Receive buffer size
	uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;			// Send_buff_addr
	uart_mng.send_buff_size		= D_UART_SRC_SIZE;					// Send buffer size
	uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_ON;			// Auto Echo
	uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;			// Save to the buffer
	uart_mng.mode				= E_DD_UART_MODE_NORMAL;			// UART Nomal Mode
	uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;		// Transferring Direction, LSB first or MSB first
	uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;				// Stop bit length
	uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;		// Parity bit type
	uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;			// Data Length
	uart_mng.ext_clk			= 0;								// Internal clock
	uart_mng.inv_nrz			= 0;								// NRZ

	fifo_ctrl.fsel				= 0;
	fifo_ctrl.fe1				= 1;
	fifo_ctrl.fe2				= 0;
	fifo_ctrl.flste				= 0;
	fifo_ctrl.fset				= 0;
	fifo_ctrl.fbyte_recv		= 0;
	uart_mng.fifo_ctrl			= &fifo_ctrl;						// FIFO Setting

	// Start UART
	Dd_UART_Open(ut_ch, D_DDIM_USER_SEM_WAIT_POL);
	Dd_UART_Ctrl(ut_ch, &uart_mng);
	Dd_UART_Start(ut_ch);

	return;
}

static void ctUartRestartFifo2( kuchar ut_ch )
{
	T_DD_UART_MNG		uart_mng;
	T_DD_UART_FIFO_CTRL	fifo_ctrl;

	memset( &uart_mng, 0, sizeof(T_DD_UART_MNG));
	memset( &fifo_ctrl, 0, sizeof(T_DD_UART_FIFO_CTRL));

	// Close
	Dd_UART_Close(ut_ch);

	// Set UART control data
	uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;		// Baud rate
	uart_mng.psend_callback		= NULL;								// Send callback function pointer
	uart_mng.preceive_callback	= ct_dd_uart_receive_callback_dma_cb;				// Receive callback function pointer
	uart_mng.receive_buff_addr	= &gUartRBuff[0];					// Receive buffer address
	uart_mng.receive_buff_size	= sizeof(gUartRBuff);				// Receive buffer size
	uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;			// Send_buff_addr
	uart_mng.send_buff_size		= D_UART_SRC_SIZE;					// Send buffer size
	uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_ON;			// Auto Echo
	uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;			// Save to the buffer
	uart_mng.mode				= E_DD_UART_MODE_NORMAL;			// UART Nomal Mode
	uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;		// Transferring Direction, LSB first or MSB first
	uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;				// Stop bit length
	uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;		// Parity bit type
	uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;			// Data Length
	uart_mng.ext_clk			= 0;								// Internal clock
	uart_mng.inv_nrz			= 0;								// NRZ

	fifo_ctrl.fsel				= 0;
	fifo_ctrl.fe1				= 1;
	fifo_ctrl.fe2				= 1;
	fifo_ctrl.flste				= 0;
	fifo_ctrl.fset				= 0;
	fifo_ctrl.fbyte_recv		= 3;
	uart_mng.fifo_ctrl			= &fifo_ctrl;						// FIFO Setting

	// Start UART
	Dd_UART_Open(ut_ch, D_DDIM_USER_SEM_WAIT_POL);
	Dd_UART_Ctrl(ut_ch, &uart_mng);
	Dd_UART_Start(ut_ch);

	return;
}

// static kint32 ct_uart_process( kuchar auto_echo, kuchar save_buff, kuchar fifo, kuchar send_int )
static kint32 ctUartProcess( CtDdUart2 *self )
{
	kint32				ret;
	T_DD_UART_MNG		uart_mng;
	T_DD_UART_FIFO_CTRL fifo_ctrl;

	memset(&uart_mng, 0, sizeof(T_DD_UART_MNG));
	memset(&fifo_ctrl, 0, sizeof(T_DD_UART_FIFO_CTRL));

	/* Open */
	ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
		return ret;
	}
	/* Control */
	uart_mng.baud_rate = E_DD_UART_BAUD_RATE_115200;
	if(self->send_int == 1){
		uart_mng.psend_callback = ct_dd_uart_send_callback_cb;
	}
	else {
		uart_mng.psend_callback = NULL;
	}
	if( self->auto_echo == 0 ){
		uart_mng.preceive_callback = ct_dd_uart_receive_callback_cb;		// for auto echo on
	}
	else {
		uart_mng.preceive_callback = ct_dd_uart_receive_callback_echo_cb;// for auto echo off
	}
	uart_mng.receive_buff_addr			= &gUartRBuff[0];
	uart_mng.receive_buff_size			= sizeof(gUartRBuff);
	uart_mng.send_buff_addr				= (kuchar*)D_UART_SRC_ADDR;
	uart_mng.send_buff_size				= D_UART_SRC_SIZE;
	uart_mng.auto_echo					= (E_DD_UART_AUTO_ECHO)(self->auto_echo);
	uart_mng.save_buff					= (E_DD_UART_SAVE2BUFFER)(self->save_buff);
	uart_mng.mode						= E_DD_UART_MODE_NORMAL;
	uart_mng.bit_direction				= E_DD_UART_BIT_DIR_LSB_FIRST;
	uart_mng.stop_bit_length			= E_DD_UART_STOP_BIT_1;
	uart_mng.data_length				= E_DD_UART_DATA_LENGTH_8;
	uart_mng.parity_bit					= E_DD_UART_PARITY_BIT_NONE;

	if(self->fifo == 1){
		uart_mng.fifo_ctrl				= &fifo_ctrl;
		uart_mng.fifo_ctrl->fsel		= 0;
		uart_mng.fifo_ctrl->fe1			= 1;
		uart_mng.fifo_ctrl->fe2			= 0;
		uart_mng.fifo_ctrl->flste		= 0;
		uart_mng.fifo_ctrl->fset		= 0;
		uart_mng.fifo_ctrl->fbyte_recv	= 0;
	}
	else{
		uart_mng.fifo_ctrl = NULL;
	}

	ret = Dd_UART_Ctrl( gUARTCh, &uart_mng );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
		return ret;
	}

	/* Start */
	ret = Dd_UART_Start( gUARTCh );
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
	T_DD_UART_MNG_SIMPLE	uart_mng_simple;

	/* Open */
	ret = Dd_UART_Open( self->ch, D_DDIM_USER_SEM_WAIT_POL );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
		return ret;
	}
	/* Control */
	uart_mng_simple.baud_rate = E_DD_UART_BAUD_RATE_115200;
	if( self->auto_echo == E_DD_UART_AUTO_ECHO_ON ){
		uart_mng_simple.preceive_callback = ct_dd_uart_receive_callback_cb;		// for auto echo on
	}
	else {
		uart_mng_simple.preceive_callback = ct_dd_uart_receive_callback_echo_cb;// for auto echo off
	}
	uart_mng_simple.receive_buff_addr	= &gUartRBuff[0];
	uart_mng_simple.receive_buff_size	= sizeof(gUartRBuff);
	uart_mng_simple.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
	uart_mng_simple.send_buff_size		= D_UART_SRC_SIZE;
	uart_mng_simple.auto_echo			= (E_DD_UART_AUTO_ECHO)(self->auto_echo);
	uart_mng_simple.save_buff			= (E_DD_UART_SAVE2BUFFER)(self->save_buff);
	uart_mng_simple.stop_bit_length		= E_DD_UART_STOP_BIT_1;
	uart_mng_simple.data_length			= E_DD_UART_DATA_LENGTH_8;
	uart_mng_simple.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

	ret = Dd_UART_Initialize_Simple( self->ch, &uart_mng_simple );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Util_Set error=0x%x\n", ret) );
		return ret;
	}

	/* Start */
	ret = Dd_UART_Start( self->ch );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
		return ret;
	}

	return ret;
}

// static kint32 ct_start_send_dma_normal(kuchar ch, kuchar dma_ch, E_DD_UART_BAUD_RATE baud_rate, kuchar* data_addr, kuint32 data_num, kuint32 cbflg)
static kint32 ctStartSendDmaNormal(CtDdUart2 *self, kuint32 cbflg)
{
	kint32				ret = D_DDIM_OK;
	T_DD_UART_MNG		uart_mng;
	T_DD_UART_FIFO_CTRL	fifo_ctrl;
	ULONG				intid;

	Ddim_Print( ("ct_start_send_dma\n") );
	Ddim_Print( ("self->ch        = %d\n",		self->ch) );
	Ddim_Print( ("self->dma_ch    = %d\n",		self->dma_ch) );
	Ddim_Print( ("self->baud_rate = %d\n",		self->baud_rate) );
	Ddim_Print( ("data_addr = %p\n",		(kuchar*)&self->data_addr) );
	Ddim_Print( ("data_num  = 0x%x\n",		(kuint32)self->data_num) );

	memset(&uart_mng, 0, sizeof(T_DD_UART_MNG));
	memset(&fifo_ctrl, 0, sizeof(T_DD_UART_FIFO_CTRL));

	/* Control */
	uart_mng.baud_rate			= self->baud_rate;
	uart_mng.psend_callback		= NULL;
	uart_mng.preceive_callback	= NULL;
	uart_mng.receive_buff_addr	= NULL;
	uart_mng.receive_buff_size	= 0;
	uart_mng.send_buff_addr		= NULL;
	uart_mng.send_buff_size		= 0;
	uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
	uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_DIS;
	uart_mng.mode				= E_DD_UART_MODE_NORMAL;
	uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
	uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
	uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;
	uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

	fifo_ctrl.fsel				= 0;
	fifo_ctrl.fe1				= 1;
	fifo_ctrl.fe2				= 1;
	fifo_ctrl.flste				= 0;
	fifo_ctrl.fset				= 0;
//	fifo_ctrl.fbyte_recv		= 128;
	fifo_ctrl.fbyte_recv		= 64;
	uart_mng.fifo_ctrl			= &fifo_ctrl;

	if(cbflg != 0){
		uart_mng.send_dma_callback	= ct_dd_uart_send_dma_callback_cb;
		uart_mng.recv_dma_callback	= ct_dd_uart_recv_dma_callback_cb;
	}

	ret = Dd_UART_Ctrl( gUARTCh, &uart_mng );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
		return ret;
	}

	ret = Dd_UART_Set_Send_Data_DMA( self->ch, (kuchar*)self->data_addr, (kuint32)self->data_num );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Set_Send_Data_DMA error=0x%x\n", ret) );
		return ret;
	}

	intid = E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT + self->ch;
	Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 0, -1, 0x2);				/** UART interrupt disable */

	ret = Dd_UART_Start_Send_DMA( self->ch, self->dma_ch );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Start_Send_DMA error=0x%x\n", ret) );
		return ret;
	}

	return ret;
}

// static kint32 ct_start_recv_dma_normal(kuchar ch, kuchar dma_ch, E_DD_UART_BAUD_RATE baud_rate, kuchar* data_addr, kuint32 data_num, kuint32 cbflg)
static kint32 ctStartRecvDmaNormal(CtDdUart2 *self, kuint32 cbflg)
{
	kint32				ret = D_DDIM_OK;
	T_DD_UART_MNG		uart_mng;
	T_DD_UART_FIFO_CTRL	fifo_ctrl;
	ULONG				intid;

	Ddim_Print( ("ct_start_recv_dma\n") );
	Ddim_Print( ("self->ch        = %d\n",		self->ch) );
	Ddim_Print( ("self->dma_ch    = %d\n",		self->dma_ch) );
	Ddim_Print( ("self->baud_rate = %d\n",		self->baud_rate) );
	Ddim_Print( ("data_addr = %p\n",		(kuchar*)self->data_addr) );
	Ddim_Print( ("data_num  = 0x%x\n",		(kuint32)self->data_num) );

	memset(&uart_mng, 0, sizeof(T_DD_UART_MNG));
	memset(&fifo_ctrl, 0, sizeof(T_DD_UART_FIFO_CTRL));

	/* Control */
	uart_mng.baud_rate			= self->baud_rate;
	uart_mng.psend_callback		= NULL;
	uart_mng.preceive_callback	= NULL;
	uart_mng.receive_buff_addr	= NULL;
	uart_mng.receive_buff_size	= 0;
	uart_mng.send_buff_addr		= NULL;
	uart_mng.send_buff_size		= 0;
	uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
	uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_DIS;
	uart_mng.mode				= E_DD_UART_MODE_NORMAL;
	uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
	uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
	uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;
	uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

	fifo_ctrl.fsel				= 0;
	fifo_ctrl.fe1				= 1;
	fifo_ctrl.fe2				= 1;
	fifo_ctrl.flste				= 0;
	fifo_ctrl.fset				= 0;
//	fifo_ctrl.fbyte_recv		= 128;
	fifo_ctrl.fbyte_recv		= 64;
	uart_mng.fifo_ctrl			= &fifo_ctrl;

	if(cbflg != 0){
		uart_mng.send_dma_callback	= ct_dd_uart_send_dma_callback_cb;
		uart_mng.recv_dma_callback	= ct_dd_uart_recv_dma_callback_cb;
	}

	ret = Dd_UART_Ctrl( gUARTCh, &uart_mng );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
		return ret;
	}

	ret = Dd_UART_Set_Recv_Data_DMA( self->ch, (kuchar*)self->data_addr, (kuint32)self->data_num );
	if( ret != D_DDIM_OK ){
		Ddim_Print( ("Dd_UART_Set_Recv_Data_DMA error=0x%x\n", ret) );
		return ret;
	}

	intid = E_DD_GIC_INTID_UART_CH0_RECEPTION_INT + self->ch;
	Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 0, -1, 0x2);				/** UART interrupt disable */

	ret = Dd_UART_Start_Recv_DMA( self->ch, self->dma_ch );
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
	T_DD_UART_MNG		uart_mng;
	E_DD_UART_BAUD_RATE	baud_rate;
	ULONG				data_addr;
	ULONG				data_num;*/
    if( strcmp(argv[1], "start") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = Dd_UART_Start( gUARTCh );
		if (self->ret !=D_DDIM_OK) {
			Ddim_Print(("UART Start ERR. self->ret=0x%x\n", self->ret));
		}
	}
	else if( strcmp(argv[1], "stop") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = Dd_UART_Stop( gUARTCh );
		if (self->ret !=D_DDIM_OK) {
			Ddim_Print(("UART Stop ERR. self->ret=0x%x\n", self->ret));
		}
	}
	else if( strcmp(argv[1], "start_test") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = Dd_UART_Close( gUARTCh );
		if (self->ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_UART_Close ERR. self->ret=0x%x\n", self->ret) );
		}

		self->auto_echo = (E_DD_UART_AUTO_ECHO)( atoi(argv[3]) );
		self->fifo = (E_DD_UART_AUTO_ECHO)( atoi(argv[4]) );
		self->send_int = (E_DD_UART_AUTO_ECHO)( atoi(argv[5]) );
		self->save_buff = (E_DD_UART_SAVE2BUFFER)( atoi(argv[6]) );
		ctUartProcess( self );
	}
	else if( strcmp(argv[1], "start_send_dma") == 0 ){
		gUARTCh = atoi( argv[2] );
		self->dma_ch = atoi( argv[3] );
		self->baud_rate = (E_DD_UART_BAUD_RATE)atoi( argv[4] );
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
		self->baud_rate = (E_DD_UART_BAUD_RATE)atoi( argv[4] );
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

		self->ret = Dd_UART_Put_Char( gUARTCh, argv[3][0] );
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

		memset( (kint32*)D_UART_SRC_ADDR, '\0', D_UART_SRC_SIZE);

		// restart
		ctUartRestartFifo2(gUARTCh);

		Dd_UART_Set_Str( gUARTCh, 'U' );
		Dd_UART_Set_Str( gUARTCh, 'A' );
		Dd_UART_Set_Str( gUARTCh, 'R' );
		Dd_UART_Set_Str( gUARTCh, 'T' );
		Dd_UART_Set_Str( gUARTCh, ' ' );
		Dd_UART_Set_Str( gUARTCh, 'P' );
		Dd_UART_Set_Str( gUARTCh, 'U' );
		Dd_UART_Set_Str( gUARTCh, 'T' );
		Dd_UART_Set_Str( gUARTCh, ' ' );
		Dd_UART_Set_Str( gUARTCh, 'D' );
		Dd_UART_Set_Str( gUARTCh, 'M' );
		Dd_UART_Set_Str( gUARTCh, 'A' );
		Dd_UART_Set_Str( gUARTCh, ' ' );
		Dd_UART_Set_Str( gUARTCh, 'T' );
		Dd_UART_Set_Str( gUARTCh, 'E' );
		Dd_UART_Set_Str( gUARTCh, 'S' );
		Dd_UART_Set_Str( gUARTCh, 'T' );
		Dd_UART_Set_Str( gUARTCh, '\n' );

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}
	}
	else if( strcmp(argv[1], "putdma_max_1") == 0 ){

		/* channel */
		gUARTCh = atoi( argv[2] );
		self->dma_ch = atoi( argv[3] );

		memset( (kint32*)D_UART_SRC_ADDR, '\0', D_UART_SRC_SIZE);

		// restart
		ctUartRestartFifo(gUARTCh);

		for(self->count = 0; self->count < 4095; (self->count)++) {
			if (self->count == 4094) {
				Dd_UART_Set_Str( gUARTCh, 'E' );
			}
			else {
				Dd_UART_Set_Str( gUARTCh, 'A' );
			}
		}

		Dd_UART_Set_Str( gUARTCh, '\n' );

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}

		Dd_UART_Set_Str( gUARTCh, 'B' );

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}

		Dd_UART_Set_Str( gUARTCh, '\n' );
		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}
	}
	else if( strcmp(argv[1], "putdma_1_max") == 0 ){

		/* channel */
		gUARTCh = atoi( argv[2] );
		self->dma_ch = atoi( argv[3] );

		memset( (kint32*)D_UART_SRC_ADDR, '\0', D_UART_SRC_SIZE);

		// restart
		ctUartRestartFifo(gUARTCh);

		Dd_UART_Set_Str( gUARTCh, 'B' );

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}

		for(self->count = 0; self->count < 4095; (self->count)++) {
			if (self->count == 4094) {
				Dd_UART_Set_Str( gUARTCh, 'E' );
			}
			else {
				Dd_UART_Set_Str( gUARTCh, 'A' );
			}
		}
		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}

		Dd_UART_Set_Str( gUARTCh, '\n' );
		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}
	}
	else if( strcmp(argv[1], "putdma_rw_0") == 0 ){

		/* channel */
		gUARTCh = atoi( argv[2] );
		self->dma_ch = atoi( argv[3] );

		memset( (kint32*)D_UART_SRC_ADDR, '\0', D_UART_SRC_SIZE);

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

		memset( (kint32*)D_UART_SRC_ADDR, '\0', D_UART_SRC_SIZE);

		// restart
		ctUartRestartFifo2(gUARTCh);

		for(self->count = 0; self->count < 3000; (self->count)++) {
			Dd_UART_Set_Str( gUARTCh, 'A' );
			if (self->count == 2999) {
				Dd_UART_Set_Str( gUARTCh, ' ' );
				Dd_UART_Set_Str( gUARTCh, 'E' );
				Dd_UART_Set_Str( gUARTCh, 'N' );
				Dd_UART_Set_Str( gUARTCh, 'D' );
				Dd_UART_Set_Str( gUARTCh, '\n' );
			}
		}

		self->ret = ctUartDmaSendProcess( gUARTCh, self );
		if( self->ret != D_DDIM_OK ){
			return ;
		}

		for(self->count = 0; self->count < 3000; (self->count)++) {
			Dd_UART_Set_Str( gUARTCh, 'B' );
			if (self->count == 2999) {
				Dd_UART_Set_Str( gUARTCh, ' ' );
				Dd_UART_Set_Str( gUARTCh, 'E' );
				Dd_UART_Set_Str( gUARTCh, 'N' );
				Dd_UART_Set_Str( gUARTCh, 'D' );
				Dd_UART_Set_Str( gUARTCh, '\n' );
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
			self->ret = Dd_UART_Set_Str( gUARTCh, argv[3][0] );
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

		self->ret = Dd_UART_Put_Str( gUARTCh );
		self->ret = Dd_UART_Put_Str( gUARTCh );
		if( self->ret != D_DDIM_OK ){
			Ddim_Print( ("Dd_UART_Put_Str error=0x%x\n", self->ret) );
			return ;
		}
	}
	else if( strcmp(argv[1], "receive") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = Dd_UART_Get_Char( gUARTCh, &self->data );
		if( self->ret != D_DDIM_OK ){
			Ddim_Print( ("Dd_UART_Get_Char error=0x%x\n", self->ret) );
			return ;
		}
	}
	else if ( strcmp(argv[1], "get_ctrl") == 0 ){
		T_DD_UART_FIFO_CTRL fifo_ctrl;

		self->uart_mng.fifo_ctrl = &fifo_ctrl;

		/* ch number */
		self->ch = atoi( argv[2] );

		self->ret = Dd_UART_Get_Ctrl(self->ch, &self->uart_mng);
		if( self->ret != D_DDIM_OK ){
			Ddim_Print( ("Dd_UART_Get_Ctrl error=0x%x\n", self->ret) );
			return ;
		}

		Ddim_Print(("UART Ctrl_Get OK.\n"));
		Ddim_Print(("UART baud_rate             =%d\n", self->uart_mng.baud_rate));
		Ddim_Print(("UART psend_callback        =%p\n", self->uart_mng.psend_callback));
		Ddim_Print(("UART preceive_callback     =%p\n", self->uart_mng.preceive_callback));
		Ddim_Print(("UART receive_buff_addr     =%p\n", self->uart_mng.receive_buff_addr));
		Ddim_Print(("UART receive_buff_size     =%d\n", self->uart_mng.receive_buff_size));
		Ddim_Print(("UART send_buff_addr        =%p\n", self->uart_mng.send_buff_addr));
		Ddim_Print(("UART send_buff_size        =%d\n", self->uart_mng.send_buff_size));
		Ddim_Print(("UART auto_echo             =%d\n", self->uart_mng.auto_echo));
		Ddim_Print(("UART save_buff             =%d\n", self->uart_mng.save_buff));
		Ddim_Print(("UART mode                  =%d\n", self->uart_mng.mode));
		Ddim_Print(("UART bit_direction         =%d\n", self->uart_mng.bit_direction));
		Ddim_Print(("UART stop_bit_length       =%d\n", self->uart_mng.stop_bit_length));
		Ddim_Print(("UART data_length           =%d\n", self->uart_mng.data_length));
		Ddim_Print(("UART parity_bit            =%d\n", self->uart_mng.parity_bit));
		Ddim_Print(("UART ext_clk               =%d\n", self->uart_mng.ext_clk));
		Ddim_Print(("UART inv_nrz               =%d\n", self->uart_mng.inv_nrz));
		Ddim_Print(("UART flow_enable           =%d\n", self->uart_mng.flow_enable));
		Ddim_Print(("UART fifo_ctrl->fsel       =%d\n", self->uart_mng.fifo_ctrl->fsel));
		Ddim_Print(("UART fifo_ctrl->flste      =%d\n", self->uart_mng.fifo_ctrl->flste));
		Ddim_Print(("UART fifo_ctrl->fset       =%d\n", self->uart_mng.fifo_ctrl->fset));
		Ddim_Print(("UART fifo_ctrl->fe2        =%d\n", self->uart_mng.fifo_ctrl->fe2));
		Ddim_Print(("UART fifo_ctrl->fe1        =%d\n", self->uart_mng.fifo_ctrl->fe1));
		Ddim_Print(("UART fifo_ctrl->fbyte_recv =%d\n", self->uart_mng.fifo_ctrl->fbyte_recv));
		Ddim_Print(("UART send_dma_callback     =%p\n", self->uart_mng.send_dma_callback));
		Ddim_Print(("UART recv_dma_callback     =%p\n", self->uart_mng.recv_dma_callback));
	}
	else if ( strcmp(argv[1], "simple") == 0 ){
		/* channel */
		gUARTCh = atoi( argv[2] );

		self->ret = Dd_UART_Close( gUARTCh );
		if (self->ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_UART_Close ERR. self->ret=0x%x\n", self->ret) );
		}

		self->auto_echo = (E_DD_UART_AUTO_ECHO)( atoi(argv[3]) );
		self->save_buff = (E_DD_UART_SAVE2BUFFER)( atoi(argv[4]) );
		self->ch = gUARTCh;
		ctUartSimpleProcess( self );
	}
}

CtDdUart2* ct_dd_uart2_new(void) 
{
    CtDdUart2 *self = k_object_new_with_private(CT_TYPE_DD_UART2, sizeof(CtDdUart2Private));
    return self;
}
