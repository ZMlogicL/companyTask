/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
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

#ifndef __CT_RESET_H_
#define __CT_RESET_H_

#include "ctddparameter.h"

#define CT_TYPE_RESET						(ct_reset_get_type())
#define CT_RESET(obj)							(K_TYPE_CHECK_INSTANCE_CAST (obj, CtReset))
#define CT_IS_RESET(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_RESET)) 

typedef struct 			_CtReset CtReset;
typedef struct 			_CtResetPrivate CtResetPrivate;

struct _CtReset
{
	CtDdParameter parent;
};

KConstType 					ct_reset_get_type(void);
CtReset* 							ct_reset_new(void);

void 								ct_reset_control(CtReset *self);

#endif /* __CT_RESET_H_ */
