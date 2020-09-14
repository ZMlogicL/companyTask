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
	if( result == DdUart_INT_STATUS_OVERRUN_ERROR || result == DdUart_INT_STATUS_FRAMING_ERROR ){
		Ddim_Print(("UART Receive Callback(error). result=0x%08x\n", result));
	}
	else if( result == DdUart_INT_STATUS_RECV_SLAVE_ADDR ){
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
		ret = dd_uart_colabo_stop(gUARTCh);
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
	DdUartMng		uart_mng;
	DdUartFifoCtrl	fifo_ctrl;
	ULONG				intid;

	CtDdUart1Private *priv = CT_DD_UART1_GET_PRIVATE(self);

	memset(&uart_mng, 0, sizeof(DdUartMng));
	memset(&fifo_ctrl, 0, sizeof(DdUartFifoCtrl));

	switch(priv->ctDdUart2->num){
		case 1:		// send address(CtDdUart_D_UART_SLAVE_ADDR_2) -> send data(FIFO not use)  bit_length:8bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_115200;
			uart_mng.psendCallback		= NULL;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_8;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			uart_mngfifoCtrl			= NULL;

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

			ret = dd_uart_send_target_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			dd_uart_branch_set_str( gUARTCh, 'U' );
			dd_uart_branch_set_str( gUARTCh, 'A' );
			dd_uart_branch_set_str( gUARTCh, 'R' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, ' ' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, 'E' );
			dd_uart_branch_set_str( gUARTCh, 'S' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, '1' );
			dd_uart_branch_set_str( gUARTCh, '\n' );

			dd_uart_branch_put_str( gUARTCh );

			break;

		case 2:		// send address(CtDdUart_D_UART_SLAVE_ADDR_3) -> send data(FIFO use)  bit_length:8bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_115200;
			uart_mng.psendCallback		= sendCallbackMulti_cb;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_8;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyteRecv		= 1;
			uart_mngfifoCtrl			= &fifo_ctrl;

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

			ret = dd_uart_send_target_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_3 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			dd_uart_branch_set_str( gUARTCh, 'U' );
			dd_uart_branch_set_str( gUARTCh, 'A' );
			dd_uart_branch_set_str( gUARTCh, 'R' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, ' ' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, 'E' );
			dd_uart_branch_set_str( gUARTCh, 'S' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, '2' );
			dd_uart_branch_set_str( gUARTCh, '\n' );

			dd_uart_branch_put_str( gUARTCh );

			break;

		case 3:		// send address(CtDdUart_D_UART_SLAVE_ADDR_2) -> send data(FIFO use)  bit_length:7bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_115200;
			uart_mng.psendCallback		= NULL;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_7;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyteRecv		= 1;
			uart_mngfifoCtrl			= &fifo_ctrl;

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

			ret = dd_uart_send_target_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			dd_uart_branch_set_str( gUARTCh, 'U' );
			dd_uart_branch_set_str( gUARTCh, 'A' );
			dd_uart_branch_set_str( gUARTCh, 'R' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, ' ' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, 'E' );
			dd_uart_branch_set_str( gUARTCh, 'S' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, '3' );
			dd_uart_branch_set_str( gUARTCh, '\n' );

			dd_uart_branch_put_str( gUARTCh );

			break;

		case 4:		// send address(CtDdUart_D_UART_SLAVE_ADDR_3) -> send data(FIFO not use)  bit_length:7bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_115200;
			uart_mng.psendCallback		= sendCallbackMulti_cb;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_7;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			uart_mngfifoCtrl			= NULL;

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
			ret = dd_uart_send_target_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_3 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			dd_uart_branch_set_str( gUARTCh, 'U' );
			dd_uart_branch_set_str( gUARTCh, 'A' );
			dd_uart_branch_set_str( gUARTCh, 'R' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, ' ' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, 'E' );
			dd_uart_branch_set_str( gUARTCh, 'S' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, '4' );
			dd_uart_branch_set_str( gUARTCh, '\n' );

			dd_uart_branch_put_str( gUARTCh );

			break;

		case 10:		// send data
			dd_uart_branch_set_str( gUARTCh, 'U' );
			dd_uart_branch_set_str( gUARTCh, 'A' );
			dd_uart_branch_set_str( gUARTCh, 'R' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, ' ' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, 'E' );
			dd_uart_branch_set_str( gUARTCh, 'S' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, 'A' );
			dd_uart_branch_set_str( gUARTCh, '\n' );
	
			dd_uart_branch_put_str( gUARTCh );
			break;

		case 20:		// receive data(FIFO not use)  bit_length:8bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_115200;
			uart_mng.psendCallback		= NULL;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_8;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			uart_mngfifoCtrl			= NULL;

			ret = dd_uart_ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			dd_uart_branch_set_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = dd_uart_branch_start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 21:		// receive data(FIFO use)  bit_length:8bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_115200;
			uart_mng.psendCallback		= NULL;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_8;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyteRecv		= 1;
			uart_mngfifoCtrl			= &fifo_ctrl;

			ret = dd_uart_ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			dd_uart_branch_set_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = dd_uart_branch_start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 22:		// receive data(FIFO use)  bit_length:7bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_115200;
			uart_mng.psendCallback		= NULL;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_7;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyteRecv		= 1;
			uart_mngfifoCtrl			= &fifo_ctrl;

			ret = dd_uart_ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			dd_uart_branch_set_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = dd_uart_branch_start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 23:		// receive data(FIFO not use)  bit_length:7bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_115200;
			uart_mng.psendCallback		= NULL;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_7;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			uart_mngfifoCtrl			= NULL;

			ret = dd_uart_ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			dd_uart_branch_set_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = dd_uart_branch_start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 30:		// send address(CtDdUart_D_UART_SLAVE_ADDR_1) -> send address(CtDdUart_D_UART_SLAVE_ADDR_2) -> timeout -> stop  bit_length:8bit
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_115200;
			uart_mng.psendCallback		= NULL;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_8;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			uart_mngfifoCtrl			= NULL;

			ret = dd_uart_ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			ret = dd_uart_branch_start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}

			ret = dd_uart_send_target_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_1 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			ret = dd_tmr32_open( CtDdUart1_D_UART_TIMER_CH, D_DDIM_USER_SEM_WAIT_POL );
			if (ret != D_DDIM_OK) {
				Ddim_Print(("timer open error : ret=%d \n", ret));
				return ret;
			}

			ret = dd_tmr32_set_timer( CtDdUart1_D_UART_TIMER_CH, 150*1000, ctUartTimerHandler_cb );
			if(ret != D_DDIM_OK) {
				dd_tmr32_stop(CtDdUart1_D_UART_TIMER_CH);
				dd_tmr32_close(CtDdUart1_D_UART_TIMER_CH);
				Ddim_Print(("timer set error : ret=%d \n", ret));
				return ret;
			}

			S_GSEND_FLG = 1;
			ret = dd_tmr32_start(CtDdUart1_D_UART_TIMER_CH);
			if(ret != D_DDIM_OK) {
				S_GSEND_FLG = 0;
				Ddim_Print(("timer start error : ret=%d \n", ret));
				return ret;
			}

			ret = dd_uart_send_target_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_2 );
			dd_tmr32_stop(CtDdUart1_D_UART_TIMER_CH);
			dd_tmr32_close(CtDdUart1_D_UART_TIMER_CH);
			S_GSEND_FLG = 0;
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			break;

		case 101:	// Slave Start
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_4000000;
			uart_mng.psendCallback		= NULL;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_DIS;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_8;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
//			fifo_ctrl.fbyteRecv		= 128;
			fifo_ctrl.fbyteRecv		= 64;
			uart_mngfifoCtrl			= &fifo_ctrl;

			uart_mngsendDmaCallback	= ct_dd_uart_send_dma_callback_cb;
			uart_mngrecvDmaCallback	= ct_dd_uart_recv_dma_callback_cb;

			ret = dd_uart_ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			dd_uart_branch_set_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = dd_uart_branch_start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 102:	// Master Start
			gUARTCh = priv->ctDdUart2->ch;

			/* Open */
			ret = dd_uart_branch_open( gUARTCh, D_DDIM_USER_SEM_WAIT_POL );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Open error=0x%x\n", ret) );
				return ret;
			}

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_4000000;
			uart_mng.psendCallback		= NULL;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_DIS;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_8;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
//			fifo_ctrl.fbyteRecv		= 128;
			fifo_ctrl.fbyteRecv		= 64;
			uart_mngfifoCtrl			= &fifo_ctrl;

			uart_mngsendDmaCallback	= ct_dd_uart_send_dma_callback_cb;
			uart_mngrecvDmaCallback	= ct_dd_uart_recv_dma_callback_cb;

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

			ret = dd_uart_send_target_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			break;

		case 103:	// interrupt disable
			dd_uart_colabo_send_recv_disable(gUARTCh);
			break;

		case 104:	// Send DMA		data_size = 0x80
			ret = dd_uart_branch_set_send_data_dma( gUARTCh, (kuchar*)0x51000000, 0x80 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Send_Data_DMA error=0x%x\n", ret) );
				return ret;
			}

			intid = DdGic_INTID_UART_CH0_TRANSMISSION_INT + gUARTCh;
			dd_gic_ctrl((DdGicIntid)intid, 0, -1, 0x2);			/** UART send interrupt disable */

			ret = dd_uart_colabo_start_send_dma( gUARTCh, 0 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start_Send_DMA error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 105:	// Send DMA		data_size = 0x3FC000
			ret = dd_uart_branch_set_send_data_dma( gUARTCh, (kuchar*)0x51000000, 0x3FC000 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Send_Data_DMA error=0x%x\n", ret) );
				return ret;
			}

			intid = DdGic_INTID_UART_CH0_TRANSMISSION_INT + gUARTCh;
			dd_gic_ctrl((DdGicIntid)intid, 0, -1, 0x2);			/** UART send interrupt disable */

			ret = dd_uart_colabo_start_send_dma( gUARTCh, 0 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start_Send_DMA error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 106:	// Recv DMA		data_size = 0x80
			ret = dd_uart_colabo_set_recv_data_dma( gUARTCh, (kuchar*)0x51000000, 0x80 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Recv_Data_DMA error=0x%x\n", ret) );
				return ret;
			}

			intid = DdGic_INTID_UART_CH0_RECEPTION_INT + gUARTCh;
			dd_gic_ctrl((DdGicIntid)intid, 0, -1, 0x2);			/** UART receive interrupt disable */

			ret = dd_uart_colabo_start_recv_dma( gUARTCh, 0 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start_Recv_DMA error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 107:	// Recv DMA		data_size = 0x3FC000
			ret = dd_uart_colabo_set_recv_data_dma( gUARTCh, (kuchar*)0x51000000, 0x3FC000 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Recv_Data_DMA error=0x%x\n", ret) );
				return ret;
			}

			intid = DdGic_INTID_UART_CH0_RECEPTION_INT + gUARTCh;
			dd_gic_ctrl((DdGicIntid)intid, 0, -1, 0x2);			/** UART receive interrupt disable */

			ret = dd_uart_colabo_start_recv_dma( gUARTCh, 0 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start_Recv_DMA error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 108:
			gUARTCh = priv->ctDdUart2->ch;

			intid = DdGic_INTID_UART_CH0_TRANSMISSION_INT + gUARTCh;
			dd_gic_ctrl((DdGicIntid)intid, 1, -1, 0x2);			/** UART send interrupt disable */

			intid = DdGic_INTID_UART_CH0_RECEPTION_INT + gUARTCh;
			dd_gic_ctrl((DdGicIntid)intid, 1, -1, 0x2);			/** UART send interrupt disable */

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_115200;
			uart_mng.psendCallback		= NULL;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_8;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyteRecv		= 1;
			uart_mngfifoCtrl			= &fifo_ctrl;

			ret = dd_uart_ctrl( gUARTCh, &uart_mng );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Ctrl error=0x%x\n", ret) );
				return ret;
			}

			dd_uart_branch_set_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Set_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			/* Start */
			ret = dd_uart_branch_start( gUARTCh );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Start error=0x%x\n", ret) );
				return ret;
			}
			break;

		case 109:
			gUARTCh = priv->ctDdUart2->ch;

			intid = DdGic_INTID_UART_CH0_TRANSMISSION_INT + gUARTCh;
			dd_gic_ctrl((DdGicIntid)intid, 1, -1, 0x2);			/** UART send interrupt enable */

			intid = DdGic_INTID_UART_CH0_RECEPTION_INT + gUARTCh;
			dd_gic_ctrl((DdGicIntid)intid, 1, -1, 0x2);			/** UART receive interrupt enable */

			/* Control */
			uart_mng.baudRate			= DdUart_BAUD_RATE_115200;
			uart_mng.psendCallback		= NULL;
			uart_mng.preceiveCallback	= receiveCallbackMulti_cb;
			uart_mng.receiveBuffAddr	= &gUartRBuff[0];
			uart_mng.receiveBuffSize	= sizeof(gUartRBuff);
			uart_mng.sendBuffAddr		= (kuchar*)CtDdUart_D_UART_SRC_ADDR;
			uart_mng.sendBuffSize		= CtDdUart_D_UART_SRC_SIZE;
			uart_mng.autoEcho			= DdUart_AUTO_ECHO_OFF;
			uart_mng.saveBuff			= DdUart_SAVE2BUFFER_EN;
			uart_mng.mode				= DdUart_MODE_MULTI;
			uart_mng.bitDirection		= DdUart_BIT_DIR_LSB_FIRST;
			uart_mng.stopBitLength	= DdUart_STOP_BIT_1;
			uart_mng.dataLength		= DdUart_DATA_LENGTH_8;
			uart_mng.parityBit			= DdUart_PARITY_BIT_NONE;

			fifo_ctrl.fsel				= 0;
			fifo_ctrl.fe1				= 1;
			fifo_ctrl.fe2				= 1;
			fifo_ctrl.flste				= 0;
			fifo_ctrl.fset				= 0;
			fifo_ctrl.fbyteRecv		= 1;
			uart_mngfifoCtrl			= &fifo_ctrl;

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

			ret = dd_uart_send_target_slave_addr( gUARTCh, CtDdUart_D_UART_SLAVE_ADDR_2 );
			if( ret != D_DDIM_OK ){
				Ddim_Print( ("Dd_UART_Send_Target_Slave_Addr error=0x%x\n", ret) );
				return ret;
			}

			dd_uart_branch_set_str( gUARTCh, 'U' );
			dd_uart_branch_set_str( gUARTCh, 'A' );
			dd_uart_branch_set_str( gUARTCh, 'R' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, ' ' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, 'E' );
			dd_uart_branch_set_str( gUARTCh, 'S' );
			dd_uart_branch_set_str( gUARTCh, 'T' );
			dd_uart_branch_set_str( gUARTCh, '3' );
			dd_uart_branch_set_str( gUARTCh, '\n' );

			dd_uart_branch_put_str( gUARTCh );
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
    CtDdUart1 *self = k_object_new_with_private(CT_TYPDdUart1, sizeof(CtDdUart1Private));
    return self;
}
