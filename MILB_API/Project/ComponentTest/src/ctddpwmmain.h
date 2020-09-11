/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-03
*@author              	:杨升柄
*@brief               	:CtDdPwmMain类
*@rely                		:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_PWM_MAIN_H__
#define __CT_DD_PWM_MAIN_H__

#include "driver_common.h"
#include <klib.h>

#define CT_TYPE_DD_PWM_MAIN					(ct_dd_pwm_main_get_type())
#define CT_DD_PWM_MAIN(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPwmMain))
#define CT_IS_DD_PWM_MAIN(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PWM_MAIN))

typedef struct 			_CtDdPwmMain CtDdPwmMain;
typedef struct 			_CtDdPwmMainPrivate CtDdPwmMainPrivate;

struct _CtDdPwmMain
{
	KObject parent;
	CtDdPwmMainPrivate *priv;
};

KConstType 			ct_dd_pwm_main_get_type(void);
CtDdPwmMain* 	ct_dd_pwm_main_new(void);

void 						ct_dd_pwm_main_test(CtDdPwmMain* self, kint argc, kchar** argv);

#endif /* __CT_DD_PWM_MAIN_H__ */
