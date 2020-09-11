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

#ifndef __CT_DD_UART1_H_
#define __CT_DD_UART1_H_

#include <klib.h>
#include "ctdduart2.h"

#define CT_TYPE_DD_UART1					(ct_dd_uart1_get_type())
#define CT_DD_UART1(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdUart1)) 
#define CT_IS_DD_UART1(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_UART1)) 

typedef struct 			_CtDdUart1 CtDdUart1;
typedef struct 			_CtDdUart1Private CtDdUart1Private;

struct _CtDdUart1
{
	KObject parent;

};

KConstType 			ct_dd_uart1_get_type(void);
CtDdUart1* 			ct_dd_uart1_new(void);

// kint32 ct_uart_process_multi(kuchar ch, kuchar num);
kint32 				ct_dd_uart1_process_multi(CtDdUart1 *self);
void 				ct_dd_uart1_set_ctdduart2(CtDdUart1 *self,CtDdUart2 *ctDdUart2);


#endif /* __CT_DD_UART1_H_ */
