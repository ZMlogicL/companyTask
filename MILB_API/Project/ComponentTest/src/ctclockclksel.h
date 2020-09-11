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

#ifndef __CT_CLOCK_CLKSEL_H_
#define __CT_CLOCK_CLKSEL_H_

#include "ctddparameter.h"

#define CT_TYPE_CLOCK_CLKSEL						(ct_clock_clksel_get_type())
#define CT_CLOCK_CLKSEL(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtClockClksel))
#define CT_IS_CLOCK_CLKSEL(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_CLOCK_CLKSEL)) 

typedef struct 			_CtClockClksel CtClockClksel;
typedef struct 			_CtClockClkselPrivate CtClockClkselPrivate;

struct _CtClockClksel
{
	CtDdParameter parent;
};

KConstType 			ct_clock_clksel_get_type(void);
CtClockClksel* 		ct_clock_clksel_new(void);

void 						ct_clock_clksel_set(CtClockClksel *self);
void 						ct_clock_clksel_get(CtClockClksel *self);

#endif /* __CT_CLOCK_CLKSEL_H_ */
