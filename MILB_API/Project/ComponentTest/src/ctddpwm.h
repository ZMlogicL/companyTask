/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-03
*@author              	:杨升柄
*@brief               	:CtDdPwm类
*@rely                		:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PWM_H__
#define __CT_DD_PWM_H__

#include "driver_common.h"
#include <klib.h>

#define CT_TYPE_DD_PWM						(ct_dd_pwm_get_type())
#define CT_DD_PWM(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPwm))
#define CT_IS_DD_PWM(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PWM)) 

typedef struct 			_CtDdPwm CtDdPwm;
typedef struct 			_CtDdPwmPrivate CtDdPwmPrivate;

struct _CtDdPwm
{
	KObject 					parent;
	CtDdPwmPrivate* 	priv;
	kint32 						ret;
	/* Ch number */
	kuchar 					ch;
	kint32 						tmout;

};

KConstType 	ct_dd_pwm_get_type(void);
CtDdPwm* 		ct_dd_pwm_new(void);

void 				ct_dd_pwm_from_main(CtDdPwm* self, kint argc, kchar** argv);

#endif /* __CT_DD_PWM_H__ */
