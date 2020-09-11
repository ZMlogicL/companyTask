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

#ifndef __CT_DD_UART2_H_
#define __CT_DD_UART2_H_

#include <klib.h>

#define CT_TYPE_DD_UART2					(ct_dd_uart2_get_type())
#define CT_DD_UART2(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdUart2)) 
#define CT_IS_DD_UART2(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_UART2)) 

typedef struct 			_CtDdUart2 CtDdUart2;
typedef struct 			_CtDdUart2Private CtDdUart2Private;

struct _CtDdUart2
{
	KObject parent;
	kint32				ret;
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
	kint32				tmout;
	USHORT				baudrate;
	kuchar				slave_addr;
	ULONG				s_write_pos;
	T_DD_UART_MNG		uart_mng;
	E_DD_UART_BAUD_RATE	baud_rate;
	ULONG				data_addr;
	ULONG				data_num;

};

KConstType 		ct_dd_uart2_get_type(void);
CtDdUart2* 		ct_dd_uart2_new(void);

// void Ct_Dd_Uart_Main_b( int argc, char** argv );
void 			ct_dd_uart2_main_b( CtDdUart2 *self,int argc, char** argv );


#endif /* __CT_DD_UART2_H_ */
