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
#include "dd_uart.h"
#include "dd_hdmac1.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "uart_csio.h"
#include "ctdduart.h"
#include "dd_tmr32.h"

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

		priv->ctDdUart2->ret = Dd_UART_Open( gUARTCh, priv->ctDdUart2->tmout );
		if (priv->ctDdUart2->ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_UART_Open ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret) );
		}
	}
	else if( strcmp(argv[1], "close") == 0 ){
		/* ch number */
		gUARTCh = atoi( argv[2] );

		priv->ctDdUart2->ret = Dd_UART_Close( gUARTCh );
		if (priv->ctDdUart2->ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_UART_Close ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret) );
		}
	}
	else if( strcmp(argv[1], "ctrl") == 0 ){			// Set CTRL data
		T_DD_UART_MNG		uart_mng;
		T_DD_UART_FIFO_CTRL fifo_ctrl;

		uart_mng.fifo_ctrl = &fifo_ctrl;

		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		// Trasmit mode
		if( strcmp(argv[3], "normal") == 0 ){
			uart_mng.mode = E_DD_UART_MODE_NORMAL;
		}
		else if( strcmp(argv[3], "multi") == 0 ){
			uart_mng.mode = E_DD_UART_MODE_MULTI;
		}
		else{
			Ddim_Print(("please check 3rd parameter!!\n"));
			return;
		}

		// LSB first or MSB first
		if( strcmp(argv[4], "lsb") == 0 ){
			uart_mng.bit_direction = E_DD_UART_BIT_DIR_LSB_FIRST;
		}
		else if( strcmp(argv[4], "msb") == 0 ){
			uart_mng.bit_direction = E_DD_UART_BIT_DIR_MSB_FIRST;
		}
		else{
			Ddim_Print( ("please check 4th parameter!!\n" ) );
			return;
		}

		// Data bit length
		if( atoi(argv[5]) == 8 ){
			uart_mng.data_length = E_DD_UART_DATA_LENGTH_8;
		}
		else if( atoi(argv[5]) == 5 ){
			uart_mng.data_length = E_DD_UART_DATA_LENGTH_5;
		}
		else if( atoi(argv[5]) == 6 ){
			uart_mng.data_length = E_DD_UART_DATA_LENGTH_6;
		}
		else if( atoi(argv[5]) == 7 ){
			uart_mng.data_length = E_DD_UART_DATA_LENGTH_7;
		}
//		else if( atoi(argv[5]) == 9 ){
//			uart_mng.data_length = E_DD_UART_DATA_LENGTH_9;
//		}
		else{
			Ddim_Print( ("please check 5th parameter!!\n" ) );
			return;
		}

		// Stop bit length
		if( strcmp(argv[6], "sb1") == 0 ){
			uart_mng.stop_bit_length = E_DD_UART_STOP_BIT_1;
		}
		else if( strcmp(argv[6], "sb2") == 0 ){
			uart_mng.stop_bit_length = E_DD_UART_STOP_BIT_2;
		}
		else{
			Ddim_Print( ("please check 6th parameter!!\n" ) );
			return;
		}

		// Parity bit type
		if( strcmp(argv[7], "pbn") == 0 ){
			uart_mng.parity_bit = E_DD_UART_PARITY_BIT_NONE;
		}
		else if( strcmp(argv[7], "pbe") == 0 ){
			uart_mng.parity_bit = E_DD_UART_PARITY_BIT_EVEN;
		}
		else if( strcmp(argv[7], "pbo") == 0 ){
			uart_mng.parity_bit = E_DD_UART_PARITY_BIT_ODD;
		}
		else{
			Ddim_Print( ("please check 7th parameter!!\n" ) );
			return;
		}

		// External clock select
		if( strcmp(argv[8], "ext0") == 0 ){
			uart_mng.ext_clk = 0;
		}
		else if( strcmp(argv[8], "ext1") == 0 ){
			uart_mng.ext_clk = 1;
		}
		else{
			Ddim_Print( ("please check 8th parameter!!\n" ) );
			return;
		}

		// Inversion serial data format
		if( strcmp(argv[9], "inv0") == 0 ){
			uart_mng.inv_nrz = 0;
		}
		else if( strcmp(argv[9], "inv1") == 0 ){
			uart_mng.inv_nrz = 1;
		}
		else{
			Ddim_Print( ("please check 9th parameter!!\n" ) );
			return;
		}

		// Auto echo
		if( strcmp(argv[10], "echo0") == 0 ){
			uart_mng.auto_echo = E_DD_UART_AUTO_ECHO_OFF;
		}
		else if( strcmp(argv[10], "echo1") == 0 ){
			uart_mng.auto_echo = E_DD_UART_AUTO_ECHO_ON;
		}
		else{
			Ddim_Print( ("please check 10th parameter!!\n" ) );
			return;
		}


		// Baudrate (bps) 
		uart_mng.baud_rate = (E_DD_UART_BAUD_RATE)atol(argv[11]);


		// FIFO selection
		if( strcmp(argv[12], "fsel0") == 0 ){
			uart_mng.fifo_ctrl->fsel = 0;
		}
		else if( strcmp(argv[12], "fsel1") == 0 ){
			uart_mng.fifo_ctrl->fsel = 1;
		}
		else{
			Ddim_Print( ("please check 12th parameter!!\n" ) );
			return;
		}

		// FIFO 1/2 enable
		if( strcmp(argv[13], "fe00") == 0 ){
			uart_mng.fifo_ctrl->fe1 = 0;		// FIFO 1 enable			:Disable
			uart_mng.fifo_ctrl->fe2 = 0;		// FIFO 2 enable			:Disable
		}
		else if( strcmp(argv[13], "fe12") == 0 ){
			uart_mng.fifo_ctrl->fe1 = 1;		// FIFO 1 enable			:Enable
			uart_mng.fifo_ctrl->fe2 = 1;		// FIFO 2 enable			:Enable
		}
		else if( strcmp(argv[13], "fe10") == 0 ){
			uart_mng.fifo_ctrl->fe1 = 1;		// FIFO 1 enable			:Enable
			uart_mng.fifo_ctrl->fe2 = 0;		// FIFO 2 enable			:Disable
		}
		else if( strcmp(argv[13], "fe02") == 0 ){
			uart_mng.fifo_ctrl->fe1 = 0;		// FIFO 1 enable			:Disable
			uart_mng.fifo_ctrl->fe2 = 1;		// FIFO 2 enable			:Enable
		}
		else{
			Ddim_Print( ("please check 13th parameter!!\n" ) );
			return;
		}

		// FIFO receive data size
		uart_mng.fifo_ctrl->fbyte_recv = atoi(argv[14]);

		// FIFO reload pointer
		if( strcmp(argv[15], "fset0") == 0 ){
			uart_mng.fifo_ctrl->fset = 0;
		}
		else if( strcmp(argv[15], "fset1") == 0 ){
			uart_mng.fifo_ctrl->fset = 1;
		}
		else{
			Ddim_Print( ("please check 15th parameter!!\n" ) );
			return;
		}

		// FIFO Data-lost check
		if( strcmp(argv[16], "flste0") == 0 ){
			uart_mng.fifo_ctrl->flste = 0;
		}
		else if( strcmp(argv[16], "flste1") == 0 ){
			uart_mng.fifo_ctrl->flste = 1;
		}
		else{
			Ddim_Print( ("please check 16th parameter!!\n" ) );
			return;
		}


		// Send callback function
		if( strcmp(argv[17], "scb0") == 0 ){
			uart_mng.psend_callback = NULL;
		}
		else if( strcmp(argv[17], "scb1") == 0 ){
			uart_mng.psend_callback = ct_dd_uart_send_callback_cb;
		}
		else{
			Ddim_Print( ("please check 17th parameter!!\n" ) );
			return;
		}

		// Receive callback function
		if( strcmp(argv[18], "rcb0") == 0 ){
			uart_mng.preceive_callback = NULL;
		}
		else if( strcmp(argv[18], "rcb1") == 0 ){
			if( uart_mng.auto_echo == E_DD_UART_AUTO_ECHO_ON ){
				uart_mng.preceive_callback = ct_dd_uart_receive_callback_cb;		// for auto echo on
			}
			else {
				uart_mng.preceive_callback = ct_dd_uart_receive_callback_echo_cb;	// for auto echo off
			}
		}
		else{
			Ddim_Print( ("please check 18th parameter!!\n" ) );
			return;
		}

		// Save to the buffer
		if( strcmp(argv[19], "buff_en") == 0 ){
			uart_mng.save_buff = E_DD_UART_SAVE2BUFFER_EN;
		}
		else if( strcmp(argv[19], "buff_dis") == 0 ){
			uart_mng.save_buff = E_DD_UART_SAVE2BUFFER_DIS;
		}
		else{
			Ddim_Print( ("please check 19th parameter!!\n" ) );
			return;
		}
		
		// Hardware flow control enable
		if( strcmp(argv[20], "hdf_en") == 0 ){
			uart_mng.flow_enable = 1;
		}
		else if( strcmp(argv[20], "hdf_dis") == 0 ){
			uart_mng.flow_enable = 0;
		}
		else{
			Ddim_Print( ("please check 20th parameter!!\n" ) );
			return;
		}

		uart_mng.receive_buff_addr = &gUartRBuff[0];
		uart_mng.receive_buff_size = sizeof(gUartRBuff);
#ifndef CO_DEBUG_ON_PC
		uart_mng.send_buff_addr = (kuchar*)D_UART_SRC_ADDR;
		uart_mng.send_buff_size = D_UART_SRC_SIZE;
#else	// CO_DEBUG_ON_PC
		uart_mng.send_buff_addr = &S_GUART_S_BUFF[0];
		uart_mng.send_buff_size = sizeof(S_GUART_S_BUFF);
#endif	// CO_DEBUG_ON_PC

		// Call API
		priv->ctDdUart2->ret = Dd_UART_Ctrl(priv->ctDdUart2->ch, &uart_mng);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("UART Ctrl ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if( strcmp(argv[1], "ctrl_s") == 0 ){			// Set CTRL simple data
		T_DD_UART_MNG_SIMPLE		uart_mng_simple;

		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		// Data bit length
		if( atoi(argv[3]) == 8 ){
			uart_mng_simple.data_length = E_DD_UART_DATA_LENGTH_8;
		}
		else if( atoi(argv[3]) == 5 ){
			uart_mng_simple.data_length = E_DD_UART_DATA_LENGTH_5;
		}
		else if( atoi(argv[3]) == 6 ){
			uart_mng_simple.data_length = E_DD_UART_DATA_LENGTH_6;
		}
		else if( atoi(argv[3]) == 7 ){
			uart_mng_simple.data_length = E_DD_UART_DATA_LENGTH_7;
		}
//		else if( atoi(argv[3]) == 9 ){
//			uart_mng_simple.data_length = E_DD_UART_DATA_LENGTH_9;
//		}
		else{
			Ddim_Print( ("please check 3rd parameter!!\n" ) );
			return;
		}

		// Stop bit length
		if( strcmp(argv[4], "sb1") == 0 ){
			uart_mng_simple.stop_bit_length = E_DD_UART_STOP_BIT_1;
		}
		else if( strcmp(argv[4], "sb2") == 0 ){
			uart_mng_simple.stop_bit_length = E_DD_UART_STOP_BIT_2;
		}
		else{
			Ddim_Print( ("please check 4th parameter!!\n" ) );
			return;
		}

		// Parity bit type
		if( strcmp(argv[5], "pbn") == 0 ){
			uart_mng_simple.parity_bit = E_DD_UART_PARITY_BIT_NONE;
		}
		else if( strcmp(argv[5], "pbe") == 0 ){
			uart_mng_simple.parity_bit = E_DD_UART_PARITY_BIT_EVEN;
		}
		else if( strcmp(argv[5], "pbo") == 0 ){
			uart_mng_simple.parity_bit = E_DD_UART_PARITY_BIT_ODD;
		}
		else{
			Ddim_Print( ("please check 5th parameter!!\n" ) );
			return;
		}

		// Auto echo
		if( strcmp(argv[6], "echo0") == 0 ){
			uart_mng_simple.auto_echo = E_DD_UART_AUTO_ECHO_OFF;
		}
		else if( strcmp(argv[6], "echo1") == 0 ){
			uart_mng_simple.auto_echo = E_DD_UART_AUTO_ECHO_ON;
		}
		else{
			Ddim_Print( ("please check 6th parameter!!\n" ) );
			return;
		}


		// Baudrate (bps) 
		uart_mng_simple.baud_rate = (E_DD_UART_BAUD_RATE)atol(argv[7]);


		// Receive callback function
		if( strcmp(argv[8], "rcb0") == 0 ){
			uart_mng_simple.preceive_callback = NULL;
		}
		else if( strcmp(argv[8], "rcb1") == 0 ){
			if( uart_mng_simple.auto_echo == E_DD_UART_AUTO_ECHO_ON ){
				uart_mng_simple.preceive_callback = ct_dd_uart_receive_callback_cb;		// for auto echo on
			}
			else {
				uart_mng_simple.preceive_callback = ct_dd_uart_receive_callback_echo_cb;	// for auto echo off
			}
		}
		else{
			Ddim_Print( ("please check 8th parameter!!\n" ) );
			return;
		}

		// Save to the buffer
		if( strcmp(argv[9], "buff_en") == 0 ){
			uart_mng_simple.save_buff = E_DD_UART_SAVE2BUFFER_EN;
		}
		else if( strcmp(argv[9], "buff_dis") == 0 ){
			uart_mng_simple.save_buff = E_DD_UART_SAVE2BUFFER_DIS;
		}
		else{
			Ddim_Print( ("please check 9th parameter!!\n" ) );
			return;
		}

		uart_mng_simple.receive_buff_addr = &gUartRBuff[0];
		uart_mng_simple.receive_buff_size = sizeof(gUartRBuff);
		uart_mng_simple.send_buff_addr = (kuchar*)D_UART_SRC_ADDR;
		uart_mng_simple.send_buff_size = D_UART_SRC_SIZE;


		// Call API
		priv->ctDdUart2->ret = Dd_UART_Initialize_Simple(priv->ctDdUart2->ch, &uart_mng_simple);
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

		priv->ctDdUart2->ret = Dd_UART_Set_Baudrate(priv->ctDdUart2->ch, priv->ctDdUart2->baudrate);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Set_Baudrate ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "get_brate" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		priv->ctDdUart2->ret = Dd_UART_Get_Baudrate(priv->ctDdUart2->ch, &priv->ctDdUart2->baudrate);
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

		priv->ctDdUart2->ret = Dd_UART_Reset_Baudrate(priv->ctDdUart2->ch);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Reset_Baudrate ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "set_fset" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );
		/* lost_detect */
		priv->ctDdUart2->num = atoi( argv[3] );

		priv->ctDdUart2->ret = Dd_UART_Save_Send_FIFO_Pointer(priv->ctDdUart2->ch, priv->ctDdUart2->num);
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

		priv->ctDdUart2->ret = Dd_UART_Reload_Send_FIFO_Pointer(priv->ctDdUart2->ch);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Reload_Send_FIFO_Pointer ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "get_fld" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		priv->ctDdUart2->ret = Dd_UART_Get_Reload_Status(priv->ctDdUart2->ch);
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

		priv->ctDdUart2->ret = Dd_UART_Reset_FIFO(priv->ctDdUart2->ch, priv->ctDdUart2->num);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Reset_FIFO ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "set_slave" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );
		/* slave_addr */
		priv->ctDdUart2->slave_addr = atoi( argv[3] );

		priv->ctDdUart2->ret = Dd_UART_Set_Slave_Addr(priv->ctDdUart2->ch, priv->ctDdUart2->slave_addr);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Set_Slave_Addr ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "send_slave_target" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );
		/* slave_addr */
		priv->ctDdUart2->slave_addr = atoi( argv[3] );

		priv->ctDdUart2->ret = Dd_UART_Send_Target_Slave_Addr(priv->ctDdUart2->ch, priv->ctDdUart2->slave_addr);
		if (priv->ctDdUart2->ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_UART_Send_Target_Slave_Addr ERR. priv->ctDdUart2->ret=0x%x\n", priv->ctDdUart2->ret));
		}
	}
	else if ( strcmp( argv[1], "get_s_write_pos" ) == 0 ){
		/* ch number */
		priv->ctDdUart2->ch = atoi( argv[2] );

		priv->ctDdUart2->s_write_pos = Dd_UART_Get_Send_Write_Pointer_Addr(priv->ctDdUart2->ch);
		Ddim_Print(("Dd_UART_Get_Send_Write_Pointer_Addr: priv->ctDdUart2->s_write_pos=%lu\n", priv->ctDdUart2->s_write_pos));
	}
	else if (strcmp(argv[1], "err") == 0){
		T_DD_UART_MNG uart_mng;
		T_DD_UART_MNG_SIMPLE uart_mng_simple;

		switch(atoi(argv[2])){
			case 1:
				priv->ctDdUart2->ret = Dd_UART_Open( D_DD_USIO_CH_NUM_MAX, priv->ctDdUart2->tmout );
				Ddim_Print(("Dd_UART_Open(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 2:
				priv->ctDdUart2->ret = Dd_UART_Open( 0, -2 );
				Ddim_Print(("Dd_UART_Open(): priv->ctDdUart2->tmout value error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 3:
				priv->ctDdUart2->ret = Dd_UART_Close( D_DD_USIO_CH_NUM_MAX );
				Ddim_Print(("Dd_UART_Close(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 4:
				priv->ctDdUart2->ret = Dd_UART_Ctrl( D_DD_USIO_CH_NUM_MAX, &uart_mng );
				Ddim_Print(("Dd_UART_Ctrl(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 5:
				priv->ctDdUart2->ret = Dd_UART_Ctrl( 0, NULL );
				Ddim_Print(("Dd_UART_Ctrl(): uart_mng is NULL. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 6:
				priv->ctDdUart2->ret = Dd_UART_Get_Ctrl( D_DD_USIO_CH_NUM_MAX, &uart_mng );
				Ddim_Print(("Dd_UART_Get_Ctrl(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 7:
				priv->ctDdUart2->ret = Dd_UART_Get_Ctrl( 0, NULL );
				Ddim_Print(("Dd_UART_Get_Ctrl(): uart_mng is NULL. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 8:
				priv->ctDdUart2->ret = Dd_UART_Start( D_DD_USIO_CH_NUM_MAX );
				Ddim_Print(("Dd_UART_Start(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 9:
				Dd_UART_Put_Char( D_DD_USIO_CH_NUM_MAX, 'a' );
				Ddim_Print(("Dd_UART_Put_Char(): CH number error.\n"));
				break;

			case 10:
				priv->ctDdUart2->ret = Dd_UART_Set_Str( D_DD_USIO_CH_NUM_MAX, 'a' );
				Ddim_Print(("Dd_UART_Set_Str(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 11:
				Dd_UART_Put_Str( D_DD_USIO_CH_NUM_MAX );
				Ddim_Print(("Dd_UART_Put_Str(): CH number error.\n"));
				break;

			case 12:
				priv->ctDdUart2->ret = Dd_UART_Get_Char( D_DD_USIO_CH_NUM_MAX, &priv->ctDdUart2->data );
				Ddim_Print(("Dd_UART_Get_Char(): CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 13:
				priv->ctDdUart2->ret = Dd_UART_Get_Char( 0, NULL );
				Ddim_Print(("Dd_UART_Get_Char(): get_char is NULL. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 14:
				Dd_USIO_Int_Handler_Tx( D_DD_USIO_CH_NUM_MAX );
				Ddim_Print(("Dd_USIO_Int_Handler_Tx(): CH number error.\n"));
				break;

			case 15:
				Dd_USIO_Int_Handler_Rx( D_DD_USIO_CH_NUM_MAX );
				Ddim_Print(("Dd_USIO_Int_Handler_Rx(): CH number error.\n"));
				break;

			case 16:
				priv->ctDdUart2->ret = Dd_UART_Initialize_Simple( D_DD_USIO_CH_NUM_MAX, &uart_mng_simple );
				Ddim_Print(("Dd_UART_Initialize_Simple(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 17:
				priv->ctDdUart2->ret = Dd_UART_Initialize_Simple( 0, NULL );
				Ddim_Print(("Dd_UART_Initialize_Simple(): uart_mng_simple is NULL. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 18:
				priv->ctDdUart2->ret = Dd_UART_Put_Str_DMA( D_DD_USIO_CH_NUM_MAX, 5 );
				Ddim_Print(("Dd_UART_Put_Str_DMA(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 19:
				priv->ctDdUart2->ret = Dd_UART_Put_Str_DMA( 0, D_DD_HDMAC1_CH_NUM_MAX );
				Ddim_Print(("Dd_UART_Put_Str_DMA(): DMA CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 20:
				priv->ctDdUart2->ret = Dd_UART_Set_Baudrate(D_DD_USIO_CH_NUM_MAX, 10000);
				Ddim_Print(("Dd_UART_Set_Baudrate(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 21:
				priv->ctDdUart2->ret = Dd_UART_Get_Baudrate(D_DD_USIO_CH_NUM_MAX, &priv->ctDdUart2->baudrate);
				Ddim_Print(("Dd_UART_Get_Baudrate(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 22:
				priv->ctDdUart2->ret = Dd_UART_Get_Baudrate(0, NULL);
				Ddim_Print(("Dd_UART_Get_Baudrate(): baud_rate is NULL. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 23:
				priv->ctDdUart2->ret = Dd_UART_Reset_Baudrate(D_DD_USIO_CH_NUM_MAX);
				Ddim_Print(("Dd_UART_Reset_Baudrate(): DMA CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 24:
				priv->ctDdUart2->ret = Dd_UART_Save_Send_FIFO_Pointer(D_DD_USIO_CH_NUM_MAX, 0);
				Ddim_Print(("Dd_UART_Save_Send_FIFO_Pointer(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 25:
				priv->ctDdUart2->ret = Dd_UART_Save_Send_FIFO_Pointer(0, 2);
				Ddim_Print(("Dd_UART_Save_Send_FIFO_Pointer(): UART lost_detect error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 26:
				priv->ctDdUart2->ret = Dd_UART_Reload_Send_FIFO_Pointer(D_DD_USIO_CH_NUM_MAX);
				Ddim_Print(("Dd_UART_Reload_Send_FIFO_Pointer(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 27:
				priv->ctDdUart2->ret = Dd_UART_Get_Reload_Status(D_DD_USIO_CH_NUM_MAX);
				Ddim_Print(("Dd_UART_Get_Reload_Status(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 28:
				priv->ctDdUart2->ret = Dd_UART_Reset_FIFO(D_DD_USIO_CH_NUM_MAX, 0);
				Ddim_Print(("Dd_UART_Reset_FIFO(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 29:
				priv->ctDdUart2->ret = Dd_UART_Reset_FIFO(0, 0);
				Ddim_Print(("Dd_UART_Reset_FIFO(): fifo_num number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 30:
				priv->ctDdUart2->ret = Dd_UART_Stop( D_DD_USIO_CH_NUM_MAX );
				Ddim_Print(("Dd_UART_Stop(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 31:
				priv->ctDdUart2->ret = Dd_UART_Set_Slave_Addr( D_DD_USIO_CH_NUM_MAX, 0 );
				Ddim_Print(("Dd_UART_Set_Slave_Addr(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 32:
				priv->ctDdUart2->ret = Dd_UART_Send_Target_Slave_Addr( D_DD_USIO_CH_NUM_MAX, 0 );
				Ddim_Print(("Dd_UART_Set_Slave_Addr(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 33:
				uart_mng.mode = E_DD_UART_MODE_NORMAL;
				uart_mng.receive_buff_addr = &gUartRBuff[0];
				uart_mng.receive_buff_size = 1;
				uart_mng.send_buff_addr = (kuchar*)D_UART_SRC_ADDR;
				uart_mng.send_buff_size = 1;
				priv->ctDdUart2->ret = Dd_UART_Ctrl( 4, &uart_mng );
				priv->ctDdUart2->ret = Dd_UART_Send_Target_Slave_Addr( 0, 0 );
				Ddim_Print(("Dd_UART_Set_Slave_Addr(): UART mode unmatch. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 34:
				uart_mng.mode = E_DD_UART_MODE_MULTI;
				uart_mng.data_length = E_DD_UART_DATA_LENGTH_5;
				priv->ctDdUart2->ret = Dd_UART_Ctrl( 0, &uart_mng );
				Ddim_Print(("Dd_UART_Ctrl(): UART mode/data_length unmatch. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ));
				break;

			case 35:
				priv->ctDdUart2->ret = Dd_UART_Get_Send_Write_Pointer_Addr( D_DD_USIO_CH_NUM_MAX );
				Ddim_Print(("Dd_UART_Get_Send_Write_Pointer_Addr(): UART CH number error. priv->ctDdUart2->ret=%X\n", priv->ctDdUart2->ret ))
				break;

			case 36:
				Dd_UART_Set_Send_Data_DMA( D_DD_USIO_CH_NUM_MAX, 0, 0 );
				break;

			case 37:
				Dd_UART_Set_Send_Data_DMA( 0, 0, 0 );
				break;

			case 38:
				Dd_UART_Set_Send_Data_DMA( 0, (kuchar*)D_UART_SRC_ADDR, 0 );
				break;

			case 39:
				Dd_UART_Set_Recv_Data_DMA( D_DD_USIO_CH_NUM_MAX, 0, 0 );
				break;

			case 40:
				Dd_UART_Set_Recv_Data_DMA( 0, 0, 0 );
				break;

			case 41:
				Dd_UART_Set_Recv_Data_DMA( 0, (kuchar*)D_UART_SRC_ADDR, 0 );
				break;

			case 42:
				Dd_UART_Start_Send_DMA( D_DD_USIO_CH_NUM_MAX, 0 );
				break;

			case 43:
				Dd_UART_Start_Send_DMA( 0, D_DD_HDMAC1_CH_NUM_MAX );
				break;

			case 44:
				Dd_UART_Start_Recv_DMA( D_DD_USIO_CH_NUM_MAX, 0 );
				break;

			case 45:
				Dd_UART_Start_Recv_DMA( 0, D_DD_HDMAC1_CH_NUM_MAX );
				break;

			case 46:
				Dd_UART_Send_Recv_Disable( D_DD_USIO_CH_NUM_MAX );
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
