/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-04-20
*@author              :
*@brief               :snsnet网络协议栈
*@rely                :klib
*@function
*SNSNET，采用ETK-C语言编写
*设计的主要功能:
*@version
*1.0.0 2020年04月开始开发
*/

#ifndef __PALLADIUM_TEST_PWM_H__
#define __PALLADIUM_TEST_PWM_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_PWM	(palladium_test_pwm_get_type())
#define PALLADIUM_TEST_PWM(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestPwm)
#define PALLADIUM_IS_TEST_PWM(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_PWM)

typedef struct 				_PalladiumTestPwm PalladiumTestPwm;
typedef struct 				_PalladiumTestPwmPrivate PalladiumTestPwmPrivate;

struct _PalladiumTestPwm {
	KObject parent;
};

KConstType 						palladium_test_pwm_get_type(void);
PalladiumTestPwm* 		palladium_test_pwm_new(void);

VOID 									palladium_test_pwm_dd_pwm_main( VOID );

#endif /* __PALLADIUM_TEST_PWM_H__ */

