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

#ifndef __CT_CLOCK_FREQUENCY_MID_H_
#define __CT_CLOCK_FREQUENCY_MID_H_

#include "ctddparameter.h"

#define CT_TYPE_CLOCK_FREQUENCY_MID					(ct_clock_frequency_mid_get_type())
#define CT_CLOCK_FREQUENCY_MID(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtClockFrequencyMid)) 
#define CT_IS_CLOCK_FREQUENCY_MID(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_CLOCK_FREQUENCY_MID)) 

typedef struct 			_CtClockFrequencyMid CtClockFrequencyMid;
typedef struct 			_CtClockFrequencyMidPrivate CtClockFrequencyMidPrivate;

struct _CtClockFrequencyMid
{
	CtDdParameter parent;
};

KConstType 												ct_clock_frequency_mid_get_type(void);
CtClockFrequencyMid* 								ct_clock_frequency_mid_new(void);

void 															ct_clock_frequency_mid_get_run(CtClockFrequencyMid *self);

#endif /* __CT_CLOCK_FREQUENCY_MID_H_ */
