/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtDdUart1类
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

K_TYPE_DEFINE_WITH_PRIVATE(CtDdUart1, ct_dd_uart1);
#define CT_DD_UART1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdUart1Private,CT_TYPE_DD_UART1))

#define CtDdUart1_D_UART_TIMER_CH			(7)

struct _CtDdUart1Private
{
	CtDdUart2* ctDdUart2;
};

static kuchar S_GSEND_FLG;

/*
DECLS
*/

static void  		sendCallbackMulti_cb();
static void  		receiveCallbackMulti_cb( void const *const r_result );
static void 		ctUartTimerHandler_cb( void );

static void ct_dd_uart1_constructor(CtDdUart1 *self) 
{
	CtDdUart1Private *priv = CT_DD_UART1_GET_PRIVATE(self);
	priv->ctDdUart2 = NULL;
}

static void ct_dd_uart1_destructor(CtDdUart1 *self) 
{
//	CtDdUart1Private *priv = CT_DD_UART1_GET_PRIVATE(self);
	self = NULL;
}

/*
IMPL//todo
*/

static void  sendCallbackMulti_cb()
{
//	Ddim_Print(("UART Send Callback(multi)\n"));
}

static void  receiveCallbackMulti_cb( void const *const r_result )
{
	kint32 result;
	CHAR  receive_data;

	result = (*(kint32*)r_result);
	if( result == D_DD_UART_INT_STATUS_OVERRUN_ERROR || result == D_DD_UART_INT_STATUS_FRAMING_ERROR ){
		Ddim_Print(("UART Receive Callback(error). result=0x%08x\n", result));
	}
	else if( result == D_DD_UART_INT_STATUS_RECV_SLAVE_ADDR ){
		Ddim_Print(("UART Receive Callback(addr). Receive_slave address\n"));
	}
	else{
		receive_data = (CHAR)(*(kint32*)r_result);
		Ddim_Print(("UART Receive Callback(data). result=%02x\n", receive_data));
	}
}

static void ctUartTimerHandler_cb( void )
{
	kint32 ret;

	if(S_GSEND_FLG == 1){
		ret = Dd_UART_Stop(gUARTCh);
		Ddim_Print(("UART Stop ERR. ret=0x%x\n", ret));
		S_GSEND_FLG = 0;
	}
}

/*
PUBLIC//todo
*/

//  kint32 ct_uart_process_multi(kuchar ch, kuchar num)
 kint32 ct_dd_uart1_process_multi(CtDdUart1 *self)
{
	kint32				ret = D_DDIM_OK;
	T_DD_UART_MNG		uart_mng;
	T_DD_UART_FIFO_CTRL	fifo_ctrl;
	ULONG				intid;

	CtDdUart1Private *priv = CT_DD_UART1_GET_PRIVATE(self);

	memset(&uart_mng, 0, sizeof(T_DD_UART_MNG));
	memset(&fifo_ctrl, 0, sizeof(T_DD_UART_FIFO_CTRL));

	switch(priv->ctDdUart2->num){
		case 1:		// send address(D_UART_SLAVE_ADDR_2) -> send data(FIFO not use)  bit_length:8bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;
			uart_mng.psend_callback		= NULL;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			uart_mng.fifo_ctrl			= NULL;

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

			ret = Dd_UART_Send_Target_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			Dd_UART_Set_Str( gUARTCh, 'U' );
			Dd_UART_Set_Str( gUARTCh, 'A' );
			Dd_UART_Set_Str( gUARTCh, 'R' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, ' ' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, 'E' );
			Dd_UART_Set_Str( gUARTCh, 'S' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, '1' );
			Dd_UART_Set_Str( gUARTCh, '\n' );

			Dd_UART_Put_Str( gUARTCh );

			break;

		case 2:		// send address(D_UART_SLAVE_ADDR_3) -> send data(FIFO use)  bit_length:8bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;
			uart_mng.psend_callback		= sendCallbackMulti_cb;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyte_recv		= 1;
			uart_mng.fifo_ctrl			= &fifo_ctrl;

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

			ret = Dd_UART_Send_Target_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_3 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			Dd_UART_Set_Str( gUARTCh, 'U' );
			Dd_UART_Set_Str( gUARTCh, 'A' );
			Dd_UART_Set_Str( gUARTCh, 'R' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, ' ' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, 'E' );
			Dd_UART_Set_Str( gUARTCh, 'S' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, '2' );
			Dd_UART_Set_Str( gUARTCh, '\n' );

			Dd_UART_Put_Str( gUARTCh );

			break;

		case 3:		// send address(D_UART_SLAVE_ADDR_2) -> send data(FIFO use)  bit_length:7bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;
			uart_mng.psend_callback		= NULL;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_7;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyte_recv		= 1;
			uart_mng.fifo_ctrl			= &fifo_ctrl;

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

			ret = Dd_UART_Send_Target_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			Dd_UART_Set_Str( gUARTCh, 'U' );
			Dd_UART_Set_Str( gUARTCh, 'A' );
			Dd_UART_Set_Str( gUARTCh, 'R' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, ' ' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, 'E' );
			Dd_UART_Set_Str( gUARTCh, 'S' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, '3' );
			Dd_UART_Set_Str( gUARTCh, '\n' );

			Dd_UART_Put_Str( gUARTCh );

			break;

		case 4:		// send address(D_UART_SLAVE_ADDR_3) -> send data(FIFO not use)  bit_length:7bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;
			uart_mng.psend_callback		= sendCallbackMulti_cb;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_7;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			uart_mng.fifo_ctrl			= NULL;

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
			ret = Dd_UART_Send_Target_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_3 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			Dd_UART_Set_Str( gUARTCh, 'U' );
			Dd_UART_Set_Str( gUARTCh, 'A' );
			Dd_UART_Set_Str( gUARTCh, 'R' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, ' ' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, 'E' );
			Dd_UART_Set_Str( gUARTCh, 'S' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, '4' );
			Dd_UART_Set_Str( gUARTCh, '\n' );

			Dd_UART_Put_Str( gUARTCh );

			break;

		case 10:		// send data
			Dd_UART_Set_Str( gUARTCh, 'U' );
			Dd_UART_Set_Str( gUARTCh, 'A' );
			Dd_UART_Set_Str( gUARTCh, 'R' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, ' ' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, 'E' );
			Dd_UART_Set_Str( gUARTCh, 'S' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, 'A' );
			Dd_UART_Set_Str( gUARTCh, '\n' );
	
			Dd_UART_Put_Str( gUARTCh );
			break;

		case 20:		// receive data(FIFO not use)  bit_length:8bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;
			uart_mng.psend_callback		= NULL;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			uart_mng.fifo_ctrl			= NULL;

			ret = Dd_UART_Ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			Dd_UART_Set_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = Dd_UART_Start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 21:		// receive data(FIFO use)  bit_length:8bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;
			uart_mng.psend_callback		= NULL;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyte_recv		= 1;
			uart_mng.fifo_ctrl			= &fifo_ctrl;

			ret = Dd_UART_Ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			Dd_UART_Set_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = Dd_UART_Start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 22:		// receive data(FIFO use)  bit_length:7bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;
			uart_mng.psend_callback		= NULL;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_7;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyte_recv		= 1;
			uart_mng.fifo_ctrl			= &fifo_ctrl;

			ret = Dd_UART_Ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			Dd_UART_Set_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = Dd_UART_Start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 23:		// receive data(FIFO not use)  bit_length:7bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;
			uart_mng.psend_callback		= NULL;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_7;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			uart_mng.fifo_ctrl			= NULL;

			ret = Dd_UART_Ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			Dd_UART_Set_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = Dd_UART_Start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 30:		// send address(D_UART_SLAVE_ADDR_1) -> send address(D_UART_SLAVE_ADDR_2) -> timeout -> stop  bit_length:8bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;
			uart_mng.psend_callback		= NULL;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			uart_mng.fifo_ctrl			= NULL;

			ret = Dd_UART_Ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			ret = Dd_UART_Start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}

			ret = Dd_UART_Send_Target_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_1 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			ret = Dd_TMR32_Open( CtDdUart1_D_UART_TIMER_CH, D_DDIM_USER_SEM_WAIT_POL );
			if (ret != D_DDIM_OK) {
				Ddim_Print(("timer open error : ret=%d \n", ret));
				return ret;
			}

			ret = Dd_TMR32_SetTimer( CtDdUart1_D_UART_TIMER_CH, 150*1000, ctUartTimerHandler_cb );
			if(ret != D_DDIM_OK) {
				Dd_TMR32_Stop(CtDdUart1_D_UART_TIMER_CH);
				Dd_TMR32_Close(CtDdUart1_D_UART_TIMER_CH);
				Ddim_Print(("timer set error : ret=%d \n", ret));
				return ret;
			}

			S_GSEND_FLG = 1;
			ret = Dd_TMR32_Start(CtDdUart1_D_UART_TIMER_CH);
			if(ret != D_DDIM_OK) {
				S_GSEND_FLG = 0;
				Ddim_Print(("timer start error : ret=%d \n", ret));
				return ret;
			}

			ret = Dd_UART_Send_Target_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_2 );
			Dd_TMR32_Stop(CtDdUart1_D_UART_TIMER_CH);
			Dd_TMR32_Close(CtDdUart1_D_UART_TIMER_CH);
			S_GSEND_FLG = 0;
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			break;

		case 101:	// Slave Start
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_4000000;
			uart_mng.psend_callback		= NULL;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_DIS;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
//			fifo_ctrl.fbyte_recv		= 128;
			fifo_ctrl.fbyte_recv		= 64;
			uart_mng.fifo_ctrl			= &fifo_ctrl;

			uart_mng.send_dma_callback	= ct_dd_uart_send_dma_callback_cb;
			uart_mng.recv_dma_callback	= ct_dd_uart_recv_dma_callback_cb;

			ret = Dd_UART_Ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			Dd_UART_Set_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = Dd_UART_Start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 102:	// Master Start
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = Dd_UART_Open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_4000000;
			uart_mng.psend_callback		= NULL;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_DIS;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
//			fifo_ctrl.fbyte_recv		= 128;
			fifo_ctrl.fbyte_recv		= 64;
			uart_mng.fifo_ctrl			= &fifo_ctrl;

			uart_mng.send_dma_callback	= ct_dd_uart_send_dma_callback_cb;
			uart_mng.recv_dma_callback	= ct_dd_uart_recv_dma_callback_cb;

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

			ret = Dd_UART_Send_Target_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			break;

		case 103:	// interrupt disable
			Dd_UART_Send_Recv_Disable(gUARTCh);
			break;

		case 104:	// Send DMA		data_size = 0x80
			ret = Dd_UART_Set_Send_Data_DMA( gUARTCh, (kuchar*)0x51000000, 0x80 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Send_Data_DMA error=0x%x\n", ret) );
				return ret;
			}

			intid = E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT + gUARTCh;
			Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 0, -1, 0x2);			/** UART send interrupt disable */

			ret = Dd_UART_Start_Send_DMA( gUARTCh, 0 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start_Send_DMA error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 105:	// Send DMA		data_size = 0x3FC000
			ret = Dd_UART_Set_Send_Data_DMA( gUARTCh, (kuchar*)0x51000000, 0x3FC000 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Send_Data_DMA error=0x%x\n", ret) );
				return ret;
			}

			intid = E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT + gUARTCh;
			Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 0, -1, 0x2);			/** UART send interrupt disable */

			ret = Dd_UART_Start_Send_DMA( gUARTCh, 0 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start_Send_DMA error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 106:	// Recv DMA		data_size = 0x80
			ret = Dd_UART_Set_Recv_Data_DMA( gUARTCh, (kuchar*)0x51000000, 0x80 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Recv_Data_DMA error=0x%x\n", ret) );
				return ret;
			}

			intid = E_DD_GIC_INTID_UART_CH0_RECEPTION_INT + gUARTCh;
			Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 0, -1, 0x2);			/** UART receive interrupt disable */

			ret = Dd_UART_Start_Recv_DMA( gUARTCh, 0 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start_Recv_DMA error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 107:	// Recv DMA		data_size = 0x3FC000
			ret = Dd_UART_Set_Recv_Data_DMA( gUARTCh, (kuchar*)0x51000000, 0x3FC000 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Recv_Data_DMA error=0x%x\n", ret) );
				return ret;
			}

			intid = E_DD_GIC_INTID_UART_CH0_RECEPTION_INT + gUARTCh;
			Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 0, -1, 0x2);			/** UART receive interrupt disable */

			ret = Dd_UART_Start_Recv_DMA( gUARTCh, 0 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start_Recv_DMA error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 108:
			gUARTCh = priv->ctDdUart2->ch;

			intid = E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT + gUARTCh;
			Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 1, -1, 0x2);			/** UART send interrupt disable */

			intid = E_DD_GIC_INTID_UART_CH0_RECEPTION_INT + gUARTCh;
			Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 1, -1, 0x2);			/** UART send interrupt disable */

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;
			uart_mng.psend_callback		= NULL;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyte_recv		= 1;
			uart_mng.fifo_ctrl			= &fifo_ctrl;

			ret = Dd_UART_Ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			Dd_UART_Set_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = Dd_UART_Start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 109:
			gUARTCh = priv->ctDdUart2->ch;

			intid = E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT + gUARTCh;
			Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 1, -1, 0x2);			/** UART send interrupt enable */

			intid = E_DD_GIC_INTID_UART_CH0_RECEPTION_INT + gUARTCh;
			Dd_GIC_Ctrl((E_DD_GIC_INTID)intid, 1, -1, 0x2);			/** UART receive interrupt enable */

			/* Control */
			uart_mng.baud_rate			= E_DD_UART_BAUD_RATE_115200;
			uart_mng.psend_callback		= NULL;
			uart_mng.preceive_callback	= receiveCallbackMulti_cb;
			uart_mng.receive_buff_addr	= &gUartRBuff[0];
			uart_mng.receive_buff_size	= sizeof(gUartRBuff);
			uart_mng.send_buff_addr		= (kuchar*)D_UART_SRC_ADDR;
			uart_mng.send_buff_size		= D_UART_SRC_SIZE;
			uart_mng.auto_echo			= E_DD_UART_AUTO_ECHO_OFF;
			uart_mng.save_buff			= E_DD_UART_SAVE2BUFFER_EN;
			uart_mng.mode				= E_DD_UART_MODE_MULTI;
			uart_mng.bit_direction		= E_DD_UART_BIT_DIR_LSB_FIRST;
			uart_mng.stop_bit_length	= E_DD_UART_STOP_BIT_1;
			uart_mng.data_length		= E_DD_UART_DATA_LENGTH_8;
			uart_mng.parity_bit			= E_DD_UART_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyte_recv		= 1;
			uart_mng.fifo_ctrl			= &fifo_ctrl;

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

			ret = Dd_UART_Send_Target_Slave_Addr( gUARTCh, D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			Dd_UART_Set_Str( gUARTCh, 'U' );
			Dd_UART_Set_Str( gUARTCh, 'A' );
			Dd_UART_Set_Str( gUARTCh, 'R' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, ' ' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, 'E' );
			Dd_UART_Set_Str( gUARTCh, 'S' );
			Dd_UART_Set_Str( gUARTCh, 'T' );
			Dd_UART_Set_Str( gUARTCh, '3' );
			Dd_UART_Set_Str( gUARTCh, '\n' );

			Dd_UART_Put_Str( gUARTCh );
			break;

		default:
			break;
	}
	return ret;
}

void ct_dd_uart1_set_ctdduart2(CtDdUart1 *self,CtDdUart2 *ctDdUart2)
{
	CtDdUart1Private *priv = CT_DD_UART1_GET_PRIVATE(self);
	priv->ctDdUart2 = ctDdUart2;

}

CtDdUart1* ct_dd_uart1_new(void) 
{
    CtDdUart1 *self = k_object_new_with_private(CT_TYPE_DD_UART1, sizeof(CtDdUart1Private));
    return self;
}
