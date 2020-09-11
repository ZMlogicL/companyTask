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

#ifndef __CT_CLOCK_CLKSTOP_H_
#define __CT_CLOCK_CLKSTOP_H_

#include "ctddparameter.h"

#define CT_TYPE_CLOCK_CLKSTOP						(ct_clock_clkstop_get_type())
#define CT_CLOCK_CLKSTOP(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtClockClkstop))
#define CT_IS_CLOCK_CLKSTOP(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_CLOCK_CLKSTOP)) 

typedef struct 			_CtClockClkstop CtClockClkstop;
typedef struct 			_CtClockClkstopPrivate CtClockClkstopPrivate;

struct _CtClockClkstop
{
	CtDdParameter parent;
};

KConstType 					ct_clock_clkstop_get_type(void);
CtClockClkstop* 				ct_clock_clkstop_new(void);

void 								ct_clock_clkstop_set(CtClockClkstop *self);
void 								ct_clock_clkstop_get(CtClockClkstop *self);

#endif /* __CT_CLOCK_CLKSTOP_H_ */
