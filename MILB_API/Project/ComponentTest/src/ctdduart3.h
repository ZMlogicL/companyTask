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

#ifndef __CT_DD_UART3_H_
#define __CT_DD_UART3_H_

#include <klib.h>
#include "ctdduart2.h"

#define CT_TYPE_DD_UART3					(ct_dd_uart3_get_type())
#define CT_DD_UART3(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdUart3)) 
#define CT_IS_DD_UART3(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_UART3)) 

typedef struct 			_CtDdUart3 CtDdUart3;
typedef struct 			_CtDdUart3Private CtDdUart3Private;

struct _CtDdUart3
{
	KObject parent;

};

KConstType 		ct_dd_uart3_get_type(void);
CtDdUart3* 		ct_dd_uart3_new(void);


void 			ct_dd_uart3_main_a(CtDdUart3 *self, int argc, char** argv );
void 			ct_dd_uart3_main_c(CtDdUart3 *self, int argc, char** argv );
void 			ct_dd_uart3_set_ctdduart2(CtDdUart3 *self,CtDdUart2 *ctDdUart2);

#endif /* __CT_DD_UART3_H_ */
