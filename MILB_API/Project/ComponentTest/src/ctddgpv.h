/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :杨升柄
*@brief               :CtDdGpv类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_GPV_H__
#define __CT_DD_GPV_H__

#include <klib.h>

#define CT_TYPE_DD_GPV					(ct_dd_gpv_get_type())
#define CT_DD_GPV(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdGpv))
#define CT_IS_DD_GPV(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_GPV)) 

typedef struct 			_CtDdGpv CtDdGpv;
typedef struct 			_CtDdGpvPrivate CtDdGpvPrivate;

struct _CtDdGpv
{
	KObject 	parent;

	kint 			input;
	kint32 		ret;

};

KConstType 		ct_dd_gpv_get_type(void);
CtDdGpv* 			ct_dd_gpv_new(void);

//新增加的方法
void 					ct_dd_gpv_from_main(CtDdGpv* self, kint argc, kchar** argv);


#endif /* __CT_DD_GPV_H__ */
