/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-02
*@author              	:杨升柄
*@brief               	:CtDdExsMain类
*@rely                		:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_EXS_MAIN_H__
#define __CT_DD_EXS_MAIN_H__

#include <klib.h>

#define CT_TYPE_DD_EXS_MAIN						(ct_dd_exs_main_get_type())
#define CT_DD_EXS_MAIN(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdExsMain))
#define CT_IS_DD_EXS_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_EXS_MAIN)) 

typedef struct 			_CtDdExsMain CtDdExsMain;
typedef struct 			_CtDdExsMainPrivate CtDdExsMainPrivate;

struct _CtDdExsMain
{
	KObject parent;
	CtDdExsMainPrivate* priv;

};

KConstType 		ct_dd_exs_main_get_type(void);
CtDdExsMain*	ct_dd_exs_main_new(void);

void 					ct_dd_exs_main_test(CtDdExsMain *self, kint argc, kchar** argv);

#endif /* __CT_DD_EXS_MAIN_H__ */
