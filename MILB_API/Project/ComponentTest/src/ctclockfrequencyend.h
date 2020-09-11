/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
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

#ifndef __CT_CLOCK_FREQUENCY_END_H_
#define __CT_CLOCK_FREQUENCY_END_H_

#include "ctddparameter.h"

#define CT_TYPE_CLOCK_FREQUENCY_END						(ct_clock_frequency_end_get_type())
#define CT_CLOCK_FREQUENCY_END(obj)							(K_TYPE_CHECK_INSTANCE_CAST (obj, CtClockFrequencyEnd))
#define CT_IS_CLOCK_FREQUENCY_END(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_CLOCK_FREQUENCY_END)) 

typedef struct 			_CtClockFrequencyEnd CtClockFrequencyEnd;
typedef struct 			_CtClockFrequencyEndPrivate CtClockFrequencyEndPrivate;

struct _CtClockFrequencyEnd
{
	CtDdParameter parent;
};

KConstType 									ct_clock_frequency_end_get_type(void);
CtClockFrequencyEnd* 					ct_clock_frequency_end_new(void);

void 												ct_clock_frequency_end_get_run(CtClockFrequencyEnd *self);

#endif /* __CT_CLOCK_FREQUENCY_END_H_ */
