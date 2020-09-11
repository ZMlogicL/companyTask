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

#ifndef __CT_GPIO_MID_TEST_H_
#define __CT_GPIO_MID_TEST_H_

#include "ctddparameter.h"

#define CT_TYPE_GPIO_MID_TEST						(ct_gpio_mid_test_get_type())
#define CT_GPIO_MID_TEST(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtGpioMidTest))
#define CT_IS_GPIO_MID_TEST(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_GPIO_MID_TEST)) 

typedef struct 			_CtGpioMidTest CtGpioMidTest;
typedef struct 			_CtGpioMidTestPrivate CtGpioMidTestPrivate;

struct _CtGpioMidTest
{
	CtDdParameter parent;
};

KConstType 							ct_gpio_mid_test_get_type(void);
CtGpioMidTest* 						ct_gpio_mid_test_new(void);

void 										ct_gpio_mid_test(CtGpioMidTest *self);

#endif /* __CT_GPIO_MID_TEST_H_ */
