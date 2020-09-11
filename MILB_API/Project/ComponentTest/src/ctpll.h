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

#ifndef __CT_PLL_H_
#define __CT_PLL_H_

#include "ctddparameter.h"

#define CT_TYPE_PLL					(ct_pll_get_type())
#define CT_PLL(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtPll))
#define CT_IS_PLL(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_PLL)) 

typedef struct 			_CtPll CtPll;
typedef struct 			_CtPllPrivate CtPllPrivate;

struct _CtPll
{
	CtDdParameter parent;
};

KConstType 						ct_pll_get_type(void);
CtPll* 									ct_pll_new(void);

void 									ct_pll_control(CtPll *self);

#endif /* __CT_PLL_H_ */
