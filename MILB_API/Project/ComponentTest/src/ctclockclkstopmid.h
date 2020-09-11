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

#ifndef __CT_CLOCK_CLKSTOP_MID_H_
#define __CT_CLOCK_CLKSTOP_MID_H_

#include "ctddparameter.h"

#define CT_TYPE_CLOCK_CLKSTOP_MID						(ct_clock_clkstop_mid_get_type())
#define CT_CLOCK_CLKSTOP_MID(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtClockClkstopMid))
#define CT_IS_CLOCK_CLKSTOP_MID(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_CLOCK_CLKSTOP_MID)) 

typedef struct 			_CtClockClkstopMid CtClockClkstopMid;
typedef struct 			_CtClockClkstopMidPrivate CtClockClkstopMidPrivate;

struct _CtClockClkstopMid
{
	CtDdParameter parent;

};

KConstType 						ct_clock_clkstop_mid_get_type(void);
CtClockClkstopMid* 			ct_clock_clkstop_mid_new(void);

void 									ct_clock_clkstop_mid_set(CtClockClkstopMid *self);
void 									ct_clock_clkstop_mid_get(CtClockClkstopMid *self);

#endif /* __CT_CLOCK_CLKSTOP_MID_H_ */
