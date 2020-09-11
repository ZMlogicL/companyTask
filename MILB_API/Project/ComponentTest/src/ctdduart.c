/**
 * @file		ct_dd_uart.c
 * @brief		This is ct code for ct_dd_uart
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
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

#ifdef CO_DEBUG_ON_PC
#define CtDdUart_D_UART_TEST_CMD_LEN		20
#endif	// CO_DEBUG_ON_PC


K_TYPE_DEFINE_WITH_PRIVATE(CtDdUart, ct_dd_uart);
#define CT_DD_UART_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdUartPrivate,CT_TYPE_DD_UART))

struct _CtDdUartPrivate
{

};

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// UART ring buffer
 kuchar gUartRBuff[256];
// UART channel
 kuchar gUARTCh = 0;

#ifdef CO_DEBUG_ON_PC
// UART send buffer

static char* S_GCMD_ARGV[25];
#endif	// CO_DEBUG_ON_PC

/*
DECLS
*/

#ifdef CO_DEBUG_ON_PC
static void ctUartSetCmd( int cmd_argc, char* cmd_argv );
static void ctUartRegDump(int ch);
#endif

static void ct_dd_uart_constructor(CtDdUart *self) 
{
//	CtDdUartPrivate *priv = CT_DD_UART_GET_PRIVATE(self);
}

static void ct_dd_uart_destructor(CtDdUart *self) 
{
//	CtDdUartPrivate *priv = CT_DD_UART_GET_PRIVATE(self);
	self = NULL;
}

/*
IMPL//todo
*/

#ifdef CO_DEBUG_ON_PC
static void ctUartSetCmd( int cmd_argc, char* cmd_argv ) 
{ 
	kint32 j;
	kint32 cmd_pos = 0;

	for( j = 0; j < cmd_argc; j++ ) { 
		S_GCMD_ARGV[ j ] = ( cmd_argv + ( cmd_pos * CtDdUart_D_UART_TEST_CMD_LEN ) ); 
		cmd_pos++;
	}
}

static void ctUartRegDump(int ch)
{
	Ddim_Print(("---- UART Register dump ----\n"));
	Ddim_Print(("UART%d.SMR   = 0x%02x\n", ch, IO_USIO.UART[ch].SMR.byte));
	Ddim_Print(("UART%d.SCR   = 0x%02x\n", ch, IO_USIO.UART[ch].SCR.byte));
	Ddim_Print(("UART%d.ESCR  = 0x%02x\n", ch, IO_USIO.UART[ch].ESCR.byte));
	Ddim_Print(("UART%d.SSR   = 0x%02x\n", ch, IO_USIO.UART[ch].SSR.byte));
	Ddim_Print(("UART%d.DR    = 0x%04x\n", ch, IO_USIO.UART[ch].DR.hword));
	Ddim_Print(("UART%d.BGR   = 0x%04x\n", ch, IO_USIO.UART[ch].BGR.hword));
	Ddim_Print(("UART%d.FCR   = 0x%04x\n", ch, IO_USIO.UART[ch].FCR.hword));
	Ddim_Print(("UART%d.FBYTE = 0x%04x\n", ch, IO_USIO.UART[ch].FBYTE.hword));
	Ddim_Print(("----------------------------\n"));
	
	return;
}
#endif	// CO_DEBUG_ON_PC

/*
PUBLIC//todo
*/

 void  ct_dd_uart_send_callback_cb()
{
//	Ddim_Print(("UART Send Callback\n"));
}

 void  ct_dd_uart_receive_callback_cb( void const *const r_result )
{
	kint32 result;
	CHAR  receive_data;

	result = (*(kint32*)r_result);
	if(result == D_DD_UART_INT_STATUS_RECV_CHAR){
		Dd_UART_Get_Char( gUARTCh, &receive_data);
		Ddim_Print(("UART Receive Callback(echo on). data=%d\n", receive_data));
	}
	else {
		Ddim_Print(("UART Receive Callback(echo on). err=0x%x\n", result));
	}
}

 void  ct_dd_uart_receive_callback_echo_cb( void const *const r_result )
{
	CHAR  receive_data;

	receive_data = (CHAR)(*(kint32*)r_result);
	printf("UART Receive Callback(echo off). data=%c\n", receive_data);
}

 void  ct_dd_uart_receive_callback_dma_cb( void const *const r_result )
{
	kint32 result;
	CHAR  receive_data;

	result = (*(kint32*)r_result);
	if(result == D_DDIM_OK){
		Dd_UART_Get_Char( gUARTCh, &receive_data);
	}
}

 void ct_dd_uart_send_dma_callback_cb(kint32 status)
{
	Ddim_Print(("ct_dd_uart_send_dma_callback_cb. status=0x%08X\n", status));
}

 void ct_dd_uart_recv_dma_callback_cb(kint32 status)
{
	Ddim_Print(("ct_dd_uart_recv_dma_callback_cb. status=0x%08X\n", status));
}


/**
 * @brief  Command main function for uart test.
 * @param  kint32 argc	:The number of parameters
 *		   CGAR** argv	:The value of parameters
 *
 *	The meaning of parameters
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| P1                | P2 | P3          | P4        |  P5      |  P6       |Meaning                                 |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| open              | ch | tmout       |           |          |           |Dd_UART_Open()                          |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| close             | ch |             |           |          |           |Dd_UART_Close()                         |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| ctrl              | Refer to the following tables.          |           |Dd_UART_Ctrl()                          |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| ctrl_s            | Refer to the following tables.          |           |Dd_UART_Initialize_Simple()             |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| start             | ch |             |           |          |           |Dd_UART_Start()                         |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| stop              | ch |             |           |          |           |Dd_UART_Stop()                          |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| put               | ch | character   |           |          |           |Dd_UART_Put_Char() (one character)      |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| putbuf            | ch | strings     |           |          |           |Dd_UART_Set_Str() (strings)             |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| putover           | ch | character   | length    |          |           |Dd_UART_Set_Str() (Continuous character)|
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| get               | ch | strings     |           |          |           |Dd_UART_Get_Char()  (strings)           |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| send              | ch |             |           |          |           |Dd_UART_Put_Str() (no data)             |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| send_dma          | ch | dma_ch      |           |          |           |Dd_UART_Put_Str_DMA()  (strings)        |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| receive           | ch |             |           |          |           |Dd_UART_Get_Char() (no data)            |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| get_ctrl          | ch |             |           |          |           |Dd_UART_Get_Ctrl()                      |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| simple            | ch | echo        | save_buff |          |           |Simple communication test               |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| set_brate         | ch | baudrate    |           |          |           |Dd_UART_Set_Baudrate()                  |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| get_brate         | ch |             |           |          |           |Dd_UART_Get_Baudrate()                  |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| rst_brate         | ch |             |           |          |           |Dd_UART_Reset_Baudrate()                |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| set_fset          | ch | lost_detect |           |          |           |Dd_UART_Save_Send_FIFO_Pointer()        |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| set_fld           | ch |             |           |          |           |Dd_UART_Reload_Send_FIFO_Pointer()      |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| get_fld           | ch |             |           |          |           |Dd_UART_Get_Reload_Status()             |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| reset_fifo        | ch | fifo_num    |           |          |           |Dd_UART_Reset_FIFO()                    |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| set_slave         | ch | slave_addr  |           |          |           |Dd_UART_Set_Slave_Addr()                |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| send_slave_target | ch | slave_addr  |           |          |           |Dd_UART_Send_Target_Slave_Addr()        |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| get_s_write_pos   | ch |             |           |          |           |Dd_UART_Get_Send_Write_Pointer_Addr()   |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| start_test        | ch | echo        |  fifo     | send_int | save_buff |Test start                              |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| start_send_dma    | ch | dma_ch      | baudrate  | data_addr| data_num  | callback |Send DMA start               |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------+-----------------------------+
 *	| start_recv_dma    | ch | dma_ch      | baudrate  | data_addr| data_num  | callback |Receive DMA start            |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| set_test          | ch | num         |           |          |           |Continuous execution                    |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *	| err               | no |             |           |          |           |Parameter error test                    |
 *	+-------------------+----+-------------+-----------+----------+-----------+----------------------------------------+
 *
 *			ch			:	0-5
 *			fifo		:	0:fifo off, 1:fifo ofn
 *			echo		:	0:echo on, 1:echo off
 *			send_int	:	0:send interrupt off, 1:send interrupt on
 *			character	:	one character
 *			length		:	character length
 *			strings		:	character strings
 *
 *
 *	The meaning of "ctrl" command parameters
 *	+----+---- +------+---+--------+---+---+----+----+-----+----------+-----+----+---------+-----+------+----+----+--------+-------+----------------+
 *	| P1 | P2  | P3   | P4| P5     | P6| P7| P8 | P9 | P10 | P11      | P12 | P13| P14     | P15 | P16  | P17| P18| P19    | P20   | Meaning        |
 *	+----+---- +------+---+--------+---+---+----+----+-----+----------+-----+----+---------+-----+------+----+----+--------+-------+----------------+
 *	|ctrl| ch  |normal|lsb|[length]|sb1|pbn|ext0|inv0|echo0|[Baudrate]|fsel0|fe00|[fbyte_r]|fset0|flste0|scb0|rcb0|buff_en |hdf_en | Dd_UART_Ctrl() |
 *  |    |(0-5)|multi |msb| (5-8)  |sb2|pbe|ext1|inv1|echo1|(bps)     |fsel1|fe12|(num)    |fset1|flste1|scb0|rcb0|buff_dis|hdf_dis|                |
 *  |    |     |      |   |        |   |pbo|    |    |     |          |     |fe10|         |     |      |    |    |        |       |                |
 *  |    |     |      |   |        |   |   |    |    |     |          |     |fe02|         |     |      |    |    |        |       |                |
 *	+----+---- +------+---+--------+---+---+----+----+-----+----------+-----+----+---------+-----+------+----+----+--------+-------+----------------+
 *
 *
 *	The meaning of "ctrl_s" command parameters
 *	+------+---- +--------+---+---+-----+----------+----+--------+-----------------------------+
 *	| P1   | P2  | P3     | P4| P5| P6  | P7       | P8 | P9     | Meaning                     |
 *	+------+---- +--------+---+---+-----+----------+----+--------+-----------------------------+
 *	|ctrl_s| ch  |[length]|sb1|pbn|echo0|[Baudrate]|rcb0|buff_en | Dd_UART_Initialize_Simple() |
 *  |      |(0-5)| (5-8)  |sb2|pbe|echo1|(bps)     |rcb1|buff_dis|                             |
 *  |      |     |        |   |pbo|     |          |    |        |                             |
 *	+------+---- +--------+---+---+-----+----------+----+--------+-----------------------------+
 *
 * @return void
 */
void ct_dd_uart_main( int argc, char** argv )
{	
	CtDdUart2* ctDdUart2 = ct_dd_uart2_new();
	CtDdUart3* ctDdUart3 = ct_dd_uart3_new();

	ct_dd_uart3_set_ctdduart2(ctDdUart3,ctDdUart2);

	 ct_dd_uart3_main_a(ctDdUart3, argc, argv );
	 ct_dd_uart2_main_b(ctDdUart2, argc, argv );
	 ct_dd_uart3_main_c(ctDdUart3, argc, argv );
	
	k_object_unref(ctDdUart2);
	k_object_unref(ctDdUart3);
	return ;
}

/**
 * @brief	Uart PCSim Test.
 * @param	void
 * @return	void
 */
void ct_dd_uart_pcsim_test( void )
{
#ifdef CO_DEBUG_ON_PC
	int cmd_cnt = 0;
	
	// UART Test command data
	char uart_test_argv1[][CtDdUart_D_UART_TEST_CMD_LEN] = { "dduart", "open", "1", "0" };
	char uart_test_argv2[][CtDdUart_D_UART_TEST_CMD_LEN] = { "dduart", "ctrl", "1", "normal", "lsb",
													"8", "sb1", "pbn", "ext0", "inv0",
													"echo0", "1200", "fsel0", "fe00", "1",
													"fset0", "flste0", "scb0", "rcb0", "buff_en",
													"hdf_en" };
	char uart_test_argv3[][CtDdUart_D_UART_TEST_CMD_LEN] = { "dduart", "get_ctrl", "1" };
	char uart_test_argv4[][CtDdUart_D_UART_TEST_CMD_LEN] = { "dduart", "ctrl", "1", "normal", "lsb",
													"8", "sb1", "pbn", "ext0", "inv0",
													"echo0", "9600", "fsel0", "fe00", "1",
													"fset0", "flste0", "scb0", "rcb0", "buff_en",
													"hdf_en" };
	char uart_test_argv5[][CtDdUart_D_UART_TEST_CMD_LEN] = { "dduart", "rst_brate", "1" };
	
	// Test UART
	
	Ddim_Print(("\n======== UART ========\n"));
	Ddim_Print((">> Test 1-1-1 ~ 1-1-6\n"));
	// Dd_UART_Open
	cmd_cnt = 4;
	ctUartSetCmd(cmd_cnt, (char*)uart_test_argv1);
	ct_dd_uart_main(cmd_cnt, S_GCMD_ARGV);
	
	// Dd_UART_Ctrl
	cmd_cnt = 21;
	ctUartSetCmd(cmd_cnt, (char*)uart_test_argv2);
	ct_dd_uart_main(cmd_cnt, S_GCMD_ARGV);
	
	// check register
	ctUartRegDump(1);
	
	Ddim_Print(("\n>> Test 1-2-1 ~ 1-2-6\n"));
	// Dd_UART_Get_Ctrl
	cmd_cnt = 3;
	ctUartSetCmd(cmd_cnt, (char*)uart_test_argv3);
	ct_dd_uart_main(cmd_cnt, S_GCMD_ARGV);
	
	Ddim_Print(("\n>> Test 1-3-1\n"));
	
	// Get HCLK
	ULONG hclk = Dd_Top_Get_HCLK();
	ULONG baudrate = (hclk / 1200) - 1;
	Ddim_Print(("HCLK           = %lu\n", hclk));
	Ddim_Print(("baudrate value = %lu\n", baudrate));
	// Dd_UART_Reset_Baudrate
	cmd_cnt = 21;
	ctUartSetCmd(cmd_cnt, (char*)uart_test_argv4);
	ct_dd_uart_main(cmd_cnt, S_GCMD_ARGV);
	
	// check register
	ctUartRegDump(1);
	
	Ddim_Print(("\n>> Test 1-3-2\n"));
	// Dd_UART_Reset_Baudrate
	cmd_cnt = 3;
	ctUartSetCmd(cmd_cnt, (char*)uart_test_argv5);
	ct_dd_uart_main(cmd_cnt, S_GCMD_ARGV);
	
	// check register
	ctUartRegDump(1);
	
	Ddim_Print(("\n>> Test 2-1-1\n"));
	// Dd_UART_Open (same ch)
	cmd_cnt = 4;
	ctUartSetCmd(cmd_cnt, (char*)uart_test_argv1);
	ct_dd_uart_main(cmd_cnt, S_GCMD_ARGV);
#endif	// CO_DEBUG_ON_PC
}

CtDdUart* ct_dd_uart_new(void) 
{
    CtDdUart *self = k_object_new_with_private(CT_TYPE_DD_UART, sizeof(CtDdUartPrivate));
    return self;
}