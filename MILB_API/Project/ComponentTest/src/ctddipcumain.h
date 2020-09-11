/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-03
*@author              	:杨升柄
*@brief               	:CtDdIpcuMain类
*@rely                		:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_IPCU_MAIN_H__
#define __CT_DD_IPCU_MAIN_H__

#include <klib.h>

#define CT_TYPE_DD_IPCU_MAIN					(ct_dd_ipcu_main_get_type())
#define CT_DD_IPCU_MAIN(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdIpcuMain))
#define CT_IS_DD_IPCU_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_IPCU_MAIN)) 

typedef struct 			_CtDdIpcuMain CtDdIpcuMain;
typedef struct 			_CtDdIpcuMainPrivate CtDdIpcuMainPrivate;

struct _CtDdIpcuMain
{
	KObject parent;
	CtDdIpcuMainPrivate* priv;

};

KConstType 		ct_dd_ipcu_main_get_type(void);
CtDdIpcuMain* 	ct_dd_ipcu_main_new(void);

//原.h只声明了main函数；
void 					ct_dd_ipcu_main_test(CtDdIpcuMain* self, kint argc, kchar** argv);


#endif /* __CT_DD_IPCU_MAIN_H__ */
