/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :杨升柄
*@brief               :CtDdExs类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_EXS_H__
#define __CT_DD_EXS_H__

#include "ddim_typedef.h"
#include <klib.h>

#define CT_TYPE_DD_EXS					(ct_dd_exs_get_type())
#define CT_DD_EXS(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdExs)) 
#define CT_IS_DD_EXS(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_EXS))

typedef struct 			_CtDdExs CtDdExs;
typedef struct 			_CtDdExsPrivate CtDdExsPrivate;

struct _CtDdExs
{
	KObject 				parent;
	CtDdExsPrivate* priv;

};

KConstType 	ct_dd_exs_get_type(void);
CtDdExs* 		ct_dd_exs_new(void);

//拆分出来的函数，从main函数里面
void 				ct_dd_exs_from_main(CtDdExs* self, kint argc, kchar** argv);

#endif /* __CT_DD_EXS_H__ */
