/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdPmu类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_pmu.h
 * @brief		PMU driver Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2016 Socionext Inc.</I></B>
 */
#ifndef __CT_DD_PMU_H__
#define __CT_DD_PMU_H__

#include <klib.h>
#include "ddimtypedef.h"

#define CT_TYPE_DD_PMU                  (ct_dd_pmu_get_type())
#define CT_DD_PMU(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdPmu)) 
#define CT_IS_DD_PMU(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_PMU)) 

typedef struct                          _CtDdPmu CtDdPmu;
typedef struct                          _CtDdPmuPrivate CtDdPmuPrivate;

struct _CtDdPmu {
    KObject parent;
    kint	param2;
	kulong	value;
};

KConstType      ct_dd_pmu_get_type(void);
CtDdPmu*        ct_dd_pmu_new(void);

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
void	        ct_dd_pmu_main(CtDdPmu *self, kint argc, KType* argv);

CtDdPmu*        ct_dd_pmu_new(void);

#endif /* __CT_DD_PMU_H__ */
