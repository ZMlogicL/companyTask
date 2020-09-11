/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdTmr64类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_tmr64.h
 * @brief		This is ct header for dd_tmr64.c
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_DD_TMR64_H__
#define __CT_DD_TMR64_H__

#include <klib.h>
#include "driver_common.h"
#include "ddimusercustom.h"

#define CT_TYPE_DD_TMR64                  (ct_dd_tmr64_get_type())
#define CT_DD_TMR64(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdTmr64)) 
#define CT_IS_DD_TMR64(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_TMR64)) 

typedef struct                            _CtDdTmr64 CtDdTmr64;
typedef struct                            _CtDdTmr64Private CtDdTmr64Private;

struct _CtDdTmr64 {
    KObject 				parent;
	kint32					ret;
	DdimUserCustom_SYSTIM	systim;
};

KConstType  ct_dd_tmr64_get_type(void);

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
void        ct_dd_tmr64_main(CtDdTmr64 *self, kint argc, KType* argv);

CtDdTmr64*  ct_dd_tmr64_new(void);

#endif /* __CT_DD_TMR64_H__ */
