/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
*@author              :董如利
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PARAMETER_H_
#define __CT_DD_PARAMETER_H_

#include <klib.h>

#define CT_TYPE_DD_PARAMETER						(ct_dd_parameter_get_type())
#define CT_DD_PARAMETER(obj)							(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdParameter))
#define CT_IS_DD_PARAMETER(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PARAMETER)) 

typedef struct 			_CtDdParameter CtDdParameter;
typedef struct 			_CtDdParameterPrivate CtDdParameterPrivate;

struct _CtDdParameter
{
	KObject parent;
    kint argc;
	kchar** argv;
};

KConstType 					ct_dd_parameter_get_type(void);
CtDdParameter* 			ct_dd_parameter_new(void);

void 								ct_dd_parameter_set_parameter(CtDdParameter* self,    kint argc,kchar** argv );

#endif /* __CT_DD_PARAMETER_H_ */
