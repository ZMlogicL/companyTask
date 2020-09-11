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

#ifndef __CT_CLOCK_CLKSTOP_END_H_
#define __CT_CLOCK_CLKSTOP_END_H_

#include "ctddparameter.h"

#define CT_TYPE_CLOCK_CLKSTOP_END						(ct_clock_clkstop_end_get_type())
#define CT_CLOCK_CLKSTOP_END(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtClockClkstopEnd))
#define CT_IS_CLOCK_CLKSTOP_END(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_CLOCK_CLKSTOP_END)) 

typedef struct 			_CtClockClkstopEnd CtClockClkstopEnd;
typedef struct 			_CtClockClkstopEndPrivate CtClockClkstopEndPrivate;

struct _CtClockClkstopEnd
{
	CtDdParameter parent;

};

KConstType 							ct_clock_clkstop_end_get_type(void);
CtClockClkstopEnd* 				ct_clock_clkstop_end_new(void);

void 										ct_clock_clkstop_end_set(CtClockClkstopEnd *self);
void 										ct_clock_clkstop_end_get(CtClockClkstopEnd *self);

#endif /* __CT_CLOCK_CLKSTOP_END_H_ */
