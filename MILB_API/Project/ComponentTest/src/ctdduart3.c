/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-07
*@author              :liudong
*@brief               :CtDdUart3类
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
#include "ctdduart1.h"
#include "ctdduart2.h"

#include "ctdduart3.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdUart3, ct_dd_uart3);
#define CT_DD_UART3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdUart3Private,CT_TYPE_DD_UART3))

struct _CtDdUart3Private
{
    CtDdUart2* ctDdUart2;
};

#ifdef CO_DEBUG_ON_PC
// UART send buffer
static kuchar S_GUART_S_BUFF[256];

#endif	// CO_DEBUG_ON_PC

/*
DECLS
*/

static void ct_dd_uart3_constructor(CtDdUart3 *self) 
{
	CtDdUart3Private *priv = CT_DD_UART3_GET_PRIVATE(self);
    priv->ctDdUart2 = NULL;

}

static void ct_dd_uart3_destructor(CtDdUart3 *self) 
{
	// CtDdUart3Private *priv = CT_DD_UART3_GET_PRIVATE(self);
    self =  NULL;
}

/*
IMPL//todo
*/

/*
PUBLIC//todo
*/

void ct_dd_uart3_main_a(CtDdUart3 *self, int argc, char** argv )
{
    /*kint32				ret;
	// kuint32				length;
	kuchar				ch;
	// kuchar				dma_ch;
	// kuchar				num;
	// CHAR				data;
	// kuint32				count;
	// kuchar				auto_echo;
	// kuchar				save_buff;
	// kuchar				fifo;
	// kuchar				send_int;
	kint32				tmout = D_DDIM_USER_SEM_WAIT_POL;
	// USHORT				baudrate;
	// kuchar				slave_addr;
	// ULONG				s_write_pos;
	// T_DD_UART_MNG		uart_mng;
	// E_DD_UART_BAUD_RATE	baud_rate;
	// ULONG				data_addr;
	// ULONG				data_num;*/

    CtDdUart3Private *priv = CT_DD_UART3_GET_PRIVATE(self);

	if( strcmp(argv[1], "open") == 0 ){
		/* ch number */
		gUARTCh = atoi( argv[2] );
		priv->ctDdUart2->tmout = atoi(argv[3]);

		priv->ctDdUart2->ret = dd_uart_branch_open( gUARTCh, priv->ctDdUart2->tmout );
		if (priv->ctDdUart2->ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_UART_Open ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret) );
		}
	}
	else if( strcmp(argv[1], "close") == 0 ){
		/* ch number */
		gUARTCh = atoi( argv[2] );

		priv->ctDdUart2->ret = dd_uart_close( gUARTCh );
		if (priv->ctDdUart2->ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_UART_Close ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret) );
		}
	}
	else if( strcmp(argv[1], "ctrl") == 0 ){			// Set CTRL data
		DdUartMng		uart_mng;
		DdUartFifoCtrl fifo_ctrl;

		uart_mngfifoCtrl = &fifo_ctrl;

		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		// Trasmit mode
		if( strcmp(argv[3], "normal") == 0 ){
			uart_mng.mode = DdUart_MODE_NORMAL;
		}
		else if( strcmp(argv[3], "multi") == 0 ){
			uart_mng.mode = DdUart_MODE_MULTI;
		}
		else{
			Ddim_Print(("please check 3rd parameter!!\n"));
			return;
		}

		// LSB first or MSB first
		if( strcmp(argv[4], "lsb") == 0 ){
			uart_mng.bitDirection = DdUart_BIT_DIR_LSB_FIRST;
		}
		else if( strcmp(argv[4], "msb") == 0 ){
			uart_mng.bitDirection = DdUart_BIT_DIR_MSB_FIRST;
		}
		else{
			Ddim_Print( ("please check 4th parameter!!\n" ) );
			return;
		}

		// Data bit length
		if( atoi(argv[5]) == 8 ){
			uart_mng.dataLength = DdUart_DATA_LENGTH_8;
		}
		else if( atoi(argv[5]) == 5 ){
			uart_mng.dataLength = DdUart_DATA_LENGTH_5;
		}
		else if( atoi(argv[5]) == 6 ){
			uart_mng.dataLength = DdUart_DATA_LENGTH_6;
		}
		else if( atoi(argv[5]) == 7 ){
			uart_mng.dataLength = DdUart_DATA_LENGTH_7;
		}
//		else if( atoi(argv[5]) == 9 ){
//			uart_mng.dataLength = E_DD_UART_DATA_LENGTH_9;
//		}
		else{
			Ddim_Print( ("please check 5th parameter!!\n" ) );
			return;
		}

		// Stop bit length
		if( strcmp(argv[6], "sb1") == 0 ){
			uart_mng.stopBitLength = DdUart_STOP_BIT_1;
		}
		else if( strcmp(argv[6], "sb2") == 0 ){
			uart_mng.stopBitLength = DdUart_STOP_BIT_2;
		}
		else{
			Ddim_Print( ("please check 6th parameter!!\n" ) );
			return;
		}

		// Parity bit type
		if( strcmp(argv[7], "pbn") == 0 ){
			uart_mng.parityBit = DdUart_PARITY_BIT_NONE;
		}
		else if( strcmp(argv[7], "pbe") == 0 ){
			uart_mng.parityBit = DdUart_PARITY_BIT_EVEN;
		}
		else if( strcmp(argv[7], "pbo") == 0 ){
			uart_mng.parityBit = DdUart_PARITY_BIT_ODD;
		}
		else{
			Ddim_Print( ("please check 7th parameter!!\n" ) );
			return;
		}

		// External clock select
		if( strcmp(argv[8], "ext0") == 0 ){
			uart_mng.extClk = 0;
		}
		else if( strcmp(argv[8], "ext1") == 0 ){
			uart_mng.extClk = 1;
		}
		else{
			Ddim_Print( ("please check 8th parameter!!\n" ) );
			return;
		}

		// Inversion serial data format
		if( strcmp(argv[9], "inv0") == 0 ){
			uart_mng.invNrz = 0;
		}
		else if( strcmp(argv[9], "inv1") == 0 ){
			uart_mng.invNrz = 1;
		}
		else{
			Ddim_Print( ("please check 9th parameter!!\n" ) );
			return;
		}

		// Auto echo
		if( strcmp(argv[10], "echo0") == 0 ){
			uart_mng.autoEcho = DdUart_AUTO_ECHO_OFF;
		}
		else if( strcmp(argv[10], "echo1") == 0 ){
			uart_mng.autoEcho = DdUart_AUTO_ECHO_ON;
		}
		else{
			Ddim_Print( ("please check 10th parameter!!\n" ) );
			return;
		}


		// Baudrate (bps) 
		uart_mng.baudRate = (DdUartBaudRate)atol(argv[11]);


		// FIFO selection
		if( strcmp(argv[12], "fsel0") == 0 ){
			uart_mngfifoCtrl->fsel = 0;
		}
		else if( strcmp(argv[12], "fsel1") == 0 ){
			uart_mngfifoCtrl->fsel = 1;
		}
		else{
			Ddim_Print( ("please check 12th parameter!!\n" ) );
			return;
		}

		// FIFO 1/2 enable
		if( strcmp(argv[13], "fe00") == 0 ){
			uart_mngfifoCtrl->fe1 = 0;		// FIFO 1 enable			:Disable
			uart_mngfifoCtrl->fe2 = 0;		// FIFO 2 enable			:Disable
		}
		else if( strcmp(argv[13], "fe12") == 0 ){
			uart_mngfifoCtrl->fe1 = 1;		// FIFO 1 enable			:Enable
			uart_mngfifoCtrl->fe2 = 1;		// FIFO 2 enable			:Enable
		}
		else if( strcmp(argv[13], "fe10") == 0 ){
			uart_mngfifoCtrl->fe1 = 1;		// FIFO 1 enable			:Enable
			uart_mngfifoCtrl->fe2 = 0;		// FIFO 2 enable			:Disable
		}
		else if( strcmp(argv[13], "fe02") == 0 ){
			uart_mngfifoCtrl->fe1 = 0;		// FIFO 1 enable			:Disable
			uart_mngfifoCtrl->fe2 = 1;		// FIFO 2 enable			:Enable
		}
		else{
			Ddim_Print( ("please check 13th parameter!!\n" ) );
			return;
		}

		// FIFO receive data size
		uart_mngfifoCtrl->fbyteRecv = atoi(argv[14]);

		// FIFO reload pointer
		if( strcmp(argv[15], "fset0") == 0 ){
			uart_mngfifoCtrl->fset = 0;
		}
		else if( strcmp(argv[15], "fset1") == 0 ){
			uart_mngfifoCtrl->fset = 1;
		}
		else{
			Ddim_Print( ("please check 15th parameter!!\n" ) );
			return;
		}

		// FIFO Data-lost check
		if( strcmp(argv[16], "flste0") == 0 ){
			uart_mngfifoCtrl->flste = 0;
		}
		else if( strcmp(argv[16], "flste1") == 0 ){
			uart_mngfifoCtrl->flste = 1;
		}
		else{
			Ddim_Print( ("please check 16th parameter!!\n" ) );
			return;
		}


		// Send callback function
		if( strcmp(argv[17], "scb0") == 0 ){
			uart_mng.psendCallback = NULL;
		}
		else if( strcmp(argv[17], "scb1") == 0 ){
			uart_mng.psendCallback = ct_dd_uart_send_callback_cb;
		}
		else{
			Ddim_Print( ("please check 17th parameter!!\n" ) );
			return;
		}

		// Receive callback function
		if( strcmp(argv[18], "rcb0") == 0 ){
			uart_mng.preceiveCallback = NULL;
		}
		else if( strcmp(argv[18], "rcb1") == 0 ){
			if( uart_mng.autoEcho == DdUart_AUTO_ECHO_ON ){
				uart_mng.preceiveCallback = ct_dd_uart_receive_callback_cb;		// for auto echo on
			}
			else {
				uart_mng.preceiveCallback = ct_dd_uart_receive_callback_echo_cb;	// for auto echo off
			}
		}
		else{
			Ddim_Print( ("please check 18th parameter!!\n" ) );
			return;
		}

		// Save to the buffer
		if( strcmp(argv[19], "buff_en") == 0 ){
			uart_mng.saveBuff = DdUart_SAVE2BUFFER_EN;
		}
		else if( strcmp(argv[19], "buff_dis") == 0 ){
			uart_mng.saveBuff = DdUart_SAVE2BUFFER_DIS;
		}
		else{
			Ddim_Print( ("please check 19th parameter!!\n" ) );
			return;
		}
		
		// Hardware flow control enable
		if( strcmp(argv[20], "hdf_en") == 0 ){
			uart_mng.flowEnable = 1;
		}
		else if( strcmp(argv[20], "hdf_dis") == 0 ){
			uart_mng.flowEnable = 0;
		}
		else{
			Ddim_Print( ("please check 20th parameter!!\n" ) );
			return;
		}

		uart_mng.receiveBuffAddr = &gUartRBuff[0];
		uart_mng.receiveBuffSize = sizeof(gUartRBuff);
#ifndef CO_DEBUG_ON_PC
		uart_mng.sendBuffAddr = (kuchar*)CtDdUart_D_UART_SRC_ADDR;
		uart_mng.sendBuffSize = CtDdUart_D_UART_SRC_SIZE;
#else	// CO_DEBUG_ON_PC
		uart_mng.sendBuffAddr = &S_GUART_S_BUFF[0];
		uart_mng.sendBuffSize = sizeof(S_GUART_S_BUFF);
#endif	// CO_DEBUG_ON_PC

		// Call API
		priv->ctDdUart2->ret = dd_uart_ctrl(priv->ctDdUart2->ch, &uart_mng);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("UART Ctrl ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if( strcmp(argv[1], "ctrl_s") == 0 ){			// Set CTRL simple data
		DdUartMngSimple		uart_mng_simple;

		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		// Data bit length
		if( atoi(argv[3]) == 8 ){
			uart_mng_simple.dataLength = DdUart_DATA_LENGTH_8;
		}
		else if( atoi(argv[3]) == 5 ){
			uart_mng_simple.dataLength = DdUart_DATA_LENGTH_5;
		}
		else if( atoi(argv[3]) == 6 ){
			uart_mng_simple.dataLength = DdUart_DATA_LENGTH_6;
		}
		else if( atoi(argv[3]) == 7 ){
			uart_mng_simple.dataLength = DdUart_DATA_LENGTH_7;
		}
//		else if( atoi(argv[3]) == 9 ){
//			uart_mng_simple.dataLength = DdUart_DATA_LENGTH_9;
//		}
		else{
			Ddim_Print( ("please check 3rd parameter!!\n" ) );
			return;
		}

		// Stop bit length
		if( strcmp(argv[4], "sb1") == 0 ){
			uart_mng_simple.stopBitLength = DdUart_STOP_BIT_1;
		}
		else if( strcmp(argv[4], "sb2") == 0 ){
			uart_mng_simple.stopBitLength = DdUart_STOP_BIT_2;
		}
		else{
			Ddim_Print( ("please check 4th parameter!!\n" ) );
			return;
		}

		// Parity bit type
		if( strcmp(argv[5], "pbn") == 0 ){
			uart_mng_simple.parityBit = DdUart_PARITY_BIT_NONE;
		}
		else if( strcmp(argv[5], "pbe") == 0 ){
			uart_mng_simple.parityBit = DdUart_PARITY_BIT_EVEN;
		}
		else if( strcmp(argv[5], "pbo") == 0 ){
			uart_mng_simple.parityBit = DdUart_PARITY_BIT_ODD;
		}
		else{
			Ddim_Print( ("please check 5th parameter!!\n" ) );
			return;
		}

		// Auto echo
		if( strcmp(argv[6], "echo0") == 0 ){
			uart_mng_simple.autoEcho = DdUart_AUTO_ECHO_OFF;
		}
		else if( strcmp(argv[6], "echo1") == 0 ){
			uart_mng_simple.autoEcho = DdUart_AUTO_ECHO_ON;
		}
		else{
			Ddim_Print( ("please check 6th parameter!!\n" ) );
			return;
		}


		// Baudrate (bps) 
		uart_mng_simple.baudRate = (DdUartBaudRate)atol(argv[7]);


		// Receive callback function
		if( strcmp(argv[8], "rcb0") == 0 ){
			uart_mng_simple.preceiveCallback = NULL;
		}
		else if( strcmp(argv[8], "rcb1") == 0 ){
			if( uart_mng_simple.autoEcho == DdUart_AUTO_ECHO_ON ){
				uart_mng_simple.preceiveCallback = ct_dd_uart_receive_callback_cb;		// for auto echo on
			}
			else {
				uart_mng_simple.preceiveCallback = ct_dd_uart_receive_callback_echo_cb;	// for auto echo off
			}
		}
		else{
			Ddim_Print( ("please check 8th parameter!!\n" ) );
			return;
		}

		// Save to the buffer
		if( strcmp(argv[9], "buff_en") == 0 ){
			uart_mng_simple.saveBuff = DdUart_SAVE2BUFFER_EN;
		}
		else if( strcmp(argv[9], "buff_dis") == 0 ){
			uart_mng_simple.saveBuff = DdUart_SAVE2BUFFER_DIS;
		}
		else{
			Ddim_Print( ("please check 9th parameter!!\n" ) );
			return;
		}

		uart_mng_simple.receiveBuffAddr = &gUartRBuff[0];
		uart_mng_simple.receiveBuffSize = sizeof(gUartRBuff);
		uart_mng_simple.sendBuffAddr = (kuchar*)CtDdUart_D_UART_SRC_ADDR;
		uart_mng_simple.sendBuffSize = CtDdUart_D_UART_SRC_SIZE;


		// Call API
		priv->ctDdUart2->ret = dd_uart_branch_initialize_simple(priv->ctDdUart2->ch, &uart_mng_simple);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("UART Initialize_Simple ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
}


void ct_dd_uart3_main_c(CtDdUart3 *self, int argc, char** argv )
{
    /*kint32				ret;
	// kuint32				length;
	kuchar				ch;
	// kuchar				dma_ch;
	kuchar				num;
	CHAR				data;
	// kuint32				count;
	// kuchar				auto_echo;
	// kuchar				save_buff;
	// kuchar				fifo;
	// kuchar				send_int;
	kint32				tmout = D_DDIM_USER_SEM_WAIT_POL;
	USHORT				baudrate;
	kuchar				slave_addr;
	ULONG				s_write_pos;
	// T_DD_UART_MNG		uart_mng;
	// E_DD_UART_BAUD_RATE	baud_rate;
	// ULONG				data_addr;
	// ULONG				data_num;*/

    CtDdUart3Private *priv = CT_DD_UART3_GET_PRIVATE(self);

    if ( strcmp( argv[1], "set_brate" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );
		/* baudrate */
		priv->ctDdUart2->baudrate = atoi( argv[3] );

		priv->ctDdUart2->ret = dd_uart_branch_set_baudrate(priv->ctDdUart2->ch, priv->ctDdUart2->baudrate);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Set_Baudrate ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "get_brate" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		priv->ctDdUart2->ret = dd_uart_branch_get_baudrate(priv->ctDdUart2->ch, &priv->ctDdUart2->baudrate);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Get_Baudrate ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
		else {
			Ddim_Print(("Dd_UART_Get_Baudrate: Baudrate=%d\n", priv->ctDdUart2->baudrate));
		}
	}
	else if ( strcmp( argv[1], "rst_brate" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		priv->ctDdUart2->ret = dd_uart_branch_reset_baudrate(priv->ctDdUart2->ch);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Reset_Baudrate ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "set_fset" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );
		/* lost_detect */
		priv->ctDdUart2->num = atoi( argv[3] );

		priv->ctDdUart2->ret = dd_uart_branch_save_send_fifo_pointer(priv->ctDdUart2->ch, priv->ctDdUart2->num);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Save_Send_FIFO_Pointer ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}

		if ( strlen(argv[4]) != 0 ) {
			Ddim_Print( ("PUT=%s\n", argv[4]) );
		}
	}
	else if ( strcmp( argv[1], "set_fld" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		priv->ctDdUart2->ret = dd_uart_branch_reload_send_fifo_pointer(priv->ctDdUart2->ch);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Reload_Send_FIFO_Pointer ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "get_fld" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		priv->ctDdUart2->ret = dd_uart_branch_get_reload_status(priv->ctDdUart2->ch);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Get_Reload_Status ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
		else {
			Ddim_Print(("Dd_UART_Get_Reload_Status: FLD = 0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "reset_fifo" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );
		/* fifo_num */
		priv->ctDdUart2->num = atoi( argv[3] );

		priv->ctDdUart2->ret = dd_uart_branch_reset_fifo(priv->ctDdUart2->ch, priv->ctDdUart2->num);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Reset_FIFO ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "set_slave" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );
		/* slave_addr */
		priv->ctDdUart2->slave_addr = atoi( argv[3] );

		priv->ctDdUart2->ret = dd_uart_branch_set_slave_addr(priv->ctDdUart2->ch, priv->ctDdUart2->slave_addr);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Set_Slave_Addr ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "send_slave_target" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );
		/* slave_addr */
		priv->ctDdUart2->slave_addr = atoi( argv[3] );

		priv->ctDdUart2->ret = dd_uart_send_target_slave_addr(priv->ctDdUart2->ch, priv->ctDdUart2->slave_addr);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Send_Target_Slave_Addr ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "get_s_write_pos" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		priv->ctDdUart2->s_write_pos = dd_uart_branch_get_send_write_pointer_addr(priv->ctDdUart2->ch);
		Ddim_Print(("Dd_UART_Get_Send_Write_Pointer_Addr: priv->ctDdUart2->s_write_pos=%lu\n", priv->ctDdUart2->s_write_pos));
	}
	else if (strcmp(argv[1], "err") == 0){
		DdUartMng uart_mng;
		DdUartMngSimple uart_mng_simple;

		switch(atoi(argv[2])){
			case 1:
				priv->ctDdUart2->ret = dd_uart_branch_open( DdUart_CH_NUM_MAX, priv->ctDdUart2->tmout );
				Ddim_Print(("dd_uart_branch_open(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 2:
				priv->ctDdUart2->ret = dd_uart_branch_open( 0, -2 );
				Ddim_Print(("dd_uart_branch_open(): priv->ctDdUart2->tmout value error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 3:
				priv->ctDdUart2->ret = dd_uart_close( DdUart_CH_NUM_MAX );
				Ddim_Print(("dd_uart_close(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 4:
				priv->ctDdUart2->ret = dd_uart_ctrl( DdUart_CH_NUM_MAX, &uart_mng );
				Ddim_Print(("dd_uart_ctrl(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 5:
				priv->ctDdUart2->ret = dd_uart_ctrl( 0, NULL );
				Ddim_Print(("dd_uart_ctrl(): uart_mng is NULL. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 6:
				priv->ctDdUart2->ret = dd_uart_branch_get_ctrl( DdUart_CH_NUM_MAX, &uart_mng );
				Ddim_Print(("dd_uart_branch_get_ctrl(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 7:
				priv->ctDdUart2->ret = dd_uart_branch_get_ctrl( 0, NULL );
				Ddim_Print(("dd_uart_branch_get_ctrl(): uart_mng is NULL. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 8:
				priv->ctDdUart2->ret = dd_uart_branch_start( DdUart_CH_NUM_MAX );
				Ddim_Print(("dd_uart_branch_start(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 9:
				dd_uart_put_char( DdUart_CH_NUM_MAX, 'a' );
				Ddim_Print(("dd_uart_put_char(): CH number error.\n"));
				break;

			case 10:
				priv->ctDdUart2->ret = dd_uart_branch_set_str( DdUart_CH_NUM_MAX, 'a' );
				Ddim_Print(("dd_uart_branch_set_str(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 11:
				dd_uart_branch_put_str( DdUart_CH_NUM_MAX );
				Ddim_Print(("dd_uart_branch_put_str(): CH number error.\n"));
				break;

			case 12:
				priv->ctDdUart2->ret = dd_uart_branch_get_char( DdUart_CH_NUM_MAX, &priv->ctDdUart2->data );
				Ddim_Print(("dd_uart_branch_get_char(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 13:
				priv->ctDdUart2->ret = dd_uart_branch_get_char( 0, NULL );
				Ddim_Print(("dd_uart_branch_get_char(): get_char is NULL. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 14:
				dd_uart_interrupt_int_handler_tx( DdUart_CH_NUM_MAX );
				Ddim_Print(("dd_uart_interrupt_int_handler_tx(): CH number error.\n"));
				break;

			case 15:
				dd_uart_interrupt_int_handler_rx( DdUart_CH_NUM_MAX );
				Ddim_Print(("dd_uart_interrupt_int_handler_rx(): CH number error.\n"));
				break;

			case 16:
				priv->ctDdUart2->ret = dd_uart_branch_initialize_simple( DdUart_CH_NUM_MAX, &uart_mng_simple );
				Ddim_Print(("dd_uart_branch_initialize_simple(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 17:
				priv->ctDdUart2->ret = dd_uart_branch_initialize_simple( 0, NULL );
				Ddim_Print(("dd_uart_branch_initialize_simple(): uart_mng_simple is NULL. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 18:
				priv->ctDdUart2->ret = dd_uart_put_str_dma( DdUart_CH_NUM_MAX, 5 );
				Ddim_Print(("dd_uart_put_str_dma(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 19:
				priv->ctDdUart2->ret = dd_uart_put_str_dma( 0, DdHdmac1_CH_NUM_MAX );
				Ddim_Print(("dd_uart_put_str_dma(): DMA CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 20:
				priv->ctDdUart2->ret = dd_uart_branch_set_baudrate(DdUart_CH_NUM_MAX, 10000);
				Ddim_Print(("dd_uart_branch_set_baudrate(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 21:
				priv->ctDdUart2->ret = dd_uart_branch_get_baudrate(DdUart_CH_NUM_MAX, &priv->ctDdUart2->baudrate);
				Ddim_Print(("dd_uart_branch_get_baudrate(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 22:
				priv->ctDdUart2->ret = dd_uart_branch_get_baudrate(0, NULL);
				Ddim_Print(("dd_uart_branch_get_baudrate(): baud_rate is NULL. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 23:
				priv->ctDdUart2->ret = dd_uart_branch_reset_baudrate(DdUart_CH_NUM_MAX);
				Ddim_Print(("dd_uart_branch_reset_baudrate(): DMA CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 24:
				priv->ctDdUart2->ret = dd_uart_branch_save_send_fifo_pointer(DdUart_CH_NUM_MAX, 0);
				Ddim_Print(("dd_uart_branch_save_send_fifo_pointer(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 25:
				priv->ctDdUart2->ret = dd_uart_branch_save_send_fifo_pointer(0, 2);
				Ddim_Print(("dd_uart_branch_save_send_fifo_pointer(): UART lost_detect error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 26:
				priv->ctDdUart2->ret = dd_uart_branch_reload_send_fifo_pointer(DdUart_CH_NUM_MAX);
				Ddim_Print(("dd_uart_branch_reload_send_fifo_pointer(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 27:
				priv->ctDdUart2->ret = dd_uart_branch_get_reload_status(DdUart_CH_NUM_MAX);
				Ddim_Print(("dd_uart_branch_get_reload_status(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 28:
				priv->ctDdUart2->ret = dd_uart_branch_reset_fifo(DdUart_CH_NUM_MAX, 0);
				Ddim_Print(("dd_uart_branch_reset_fifo(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 29:
				priv->ctDdUart2->ret = dd_uart_branch_reset_fifo(0, 0);
				Ddim_Print(("dd_uart_branch_reset_fifo(): fifo_num number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 30:
				priv->ctDdUart2->ret = dd_uart_colabo_stop( DdUart_CH_NUM_MAX );
				Ddim_Print(("dd_uart_colabo_stop(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 31:
				priv->ctDdUart2->ret = dd_uart_branch_set_slave_addr( DdUart_CH_NUM_MAX, 0 );
				Ddim_Print(("dd_uart_branch_set_slave_addr(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 32:
				priv->ctDdUart2->ret = dd_uart_send_target_slave_addr( DdUart_CH_NUM_MAX, 0 );
				Ddim_Print(("dd_uart_branch_set_slave_addr(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 33:
				uart_mng.mode = DdUart_MODE_NORMAL;
				uart_mng.receiveBuffAddr = &gUartRBuff[0];
				uart_mng.receiveBuffSize = 1;
				uart_mng.sendBuffAddr = (kuchar*)CtDdUart_D_UART_SRC_ADDR;
				uart_mng.sendBuffSize = 1;
				priv->ctDdUart2->ret = dd_uart_ctrl( 4, &uart_mng );
				priv->ctDdUart2->ret = dd_uart_send_target_slave_addr( 0, 0 );
				Ddim_Print(("dd_uart_branch_set_slave_addr(): UART mode unmatch. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 34:
				uart_mng.mode = DdUart_MODE_MULTI;
				uart_mng.dataLength = DdUart_DATA_LENGTH_5;
				priv->ctDdUart2->ret = dd_uart_ctrl( 0, &uart_mng );
				Ddim_Print(("dd_uart_ctrl(): UART mode/dataLength unmatch. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 35:
				priv->ctDdUart2->ret = dd_uart_branch_get_send_write_pointer_addr( DdUart_CH_NUM_MAX );
				Ddim_Print(("dd_uart_branch_get_send_write_pointer_addr(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ))
				break;

			case 36:
				dd_uart_branch_set_send_data_dma( DdUart_CH_NUM_MAX, 0, 0 );
				break;

			case 37:
				dd_uart_branch_set_send_data_dma( 0, 0, 0 );
				break;

			case 38:
				dd_uart_branch_set_send_data_dma( 0, (kuchar*)CtDdUart_D_UART_SRC_ADDR, 0 );
				break;

			case 39:
				dd_uart_colabo_set_recv_data_dma( DdUart_CH_NUM_MAX, 0, 0 );
				break;

			case 40:
				dd_uart_colabo_set_recv_data_dma( 0, 0, 0 );
				break;

			case 41:
				dd_uart_colabo_set_recv_data_dma( 0, (kuchar*)CtDdUart_D_UART_SRC_ADDR, 0 );
				break;

			case 42:
				dd_uart_colabo_start_send_dma( DdUart_CH_NUM_MAX, 0 );
				break;

			case 43:
				dd_uart_colabo_start_send_dma( 0, DdHdmac1_CH_NUM_MAX );
				break;

			case 44:
				dd_uart_colabo_start_recv_dma( DdUart_CH_NUM_MAX, 0 );
				break;

			case 45:
				dd_uart_colabo_start_recv_dma( 0, DdHdmac1_CH_NUM_MAX );
				break;

			case 46:
				dd_uart_colabo_send_recv_disable( DdUart_CH_NUM_MAX );
				break;

			default:
				Ddim_Print( ("please check 2nd parameter!!\n" ) );
		}

	}
	else{
		Ddim_Print( ("please check 1st parameter!!\n" ) );
	}
}

void ct_dd_uart3_set_ctdduart2(CtDdUart3 *self,CtDdUart2 *ctDdUart2)
{
	CtDdUart3Private *priv = CT_DD_UART3_GET_PRIVATE(self);
	priv->ctDdUart2 = ctDdUart2;
}

CtDdUart3* ct_dd_uart3_new(void) 
{
    CtDdUart3 *self = k_object_new_with_private(CT_TYPE_DD_UART3, sizeof(CtDdUart3Private));
    return self;
}
