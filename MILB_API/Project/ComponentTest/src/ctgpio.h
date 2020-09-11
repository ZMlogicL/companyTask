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

#ifndef __CT_GPIO_H_
#define __CT_GPIO_H_

#include "ctddparameter.h"

#define CT_TYPE_GPIO						(ct_gpio_get_type())
#define CT_GPIO(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtGpio))
#define CT_IS_GPIO(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_GPIO)) 

typedef struct 			_CtGpio CtGpio;
typedef struct 			_CtGpioPrivate CtGpioPrivate;

struct _CtGpio
{
	CtDdParameter parent;
};

KConstType 						ct_gpio_get_type(void);
CtGpio* 								ct_gpio_new(void);

void 									ct_gpio_get_ctrl(CtGpio*self,kchar *reg, kchar *port);
void 									ct_gpio_set_ctrl(CtGpio*self,kchar *reg, kchar *port, kuchar val);
void 									ct_gpio_control(CtGpio *self);

#endif /* __CT_GPIO_H_ */
