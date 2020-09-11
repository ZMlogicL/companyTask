/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdTmr32类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_tmr32.h
 * @brief		This is ct header for dd_tmr32.c
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_DD_TMR32_H__
#define __CT_DD_TMR32_H__

#include <klib.h>
#include "driver_common.h"
#include "ddim_typedef.h"

#define CT_TYPE_DD_TMR32                  (ct_dd_tmr32_get_type())
#define CT_DD_TMR32(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdTmr32)) 
#define CT_IS_DD_TMR32(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_TMR32)) 

typedef struct                            _CtDdTmr32 CtDdTmr32;
typedef struct                            _CtDdTmr32Private CtDdTmr32Private;

struct _CtDdTmr32 {
    KObject parent;
    kulong	usec;
	kulong	num;
};

KConstType  ct_dd_tmr32_get_type(void);

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/************************************/
/* Size definition                  */
/************************************/

/************************************/
/* Address definition               */
/************************************/

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
void        ct_dd_tmr32_main(CtDdTmr32 *self, kint argc, KType* argv);

CtDdTmr32*  ct_dd_tmr32_new(void);

#endif /* __CT_DD_TMR32_H__ */
