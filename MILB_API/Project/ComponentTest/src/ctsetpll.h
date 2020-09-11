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

#ifndef __CT_SET_PLL_H_
#define __CT_SET_PLL_H_

#include "ctddparameter.h"

#define CT_TYPE_SET_PLL					(ct_set_pll_get_type())
#define CT_SET_PLL(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtSetPll))
#define CT_IS_SET_PLL(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_SET_PLL)) 

typedef struct 			_CtSetPll CtSetPll;
typedef struct 			_CtSetPllPrivate CtSetPllPrivate;

struct _CtSetPll
{
	CtDdParameter parent;
};

KConstType 						ct_set_pll_get_type(void);
CtSetPll* 								ct_set_pll_new(void);

void 									ct_set_pll_control(CtSetPll *self);

#endif /* __CT_SET_PLL_H_ */
