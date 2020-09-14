/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdMcc类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_mcc.h
 * @brief		dd_mcc Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_DD_MCC_H__
#define __CT_DD_MCC_H__

#include <klib.h>
#include "ddimtypedef.h"

#define CT_TYPE_DD_MCC                  (ct_dd_mcc_get_type())
#define CT_DD_MCC(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdMcc)) 
#define CT_IS_DD_MCC(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_MCC)) 

typedef struct                          _CtDdMcc CtDdMcc;
typedef struct                          _CtDdMccPrivate CtDdMccPrivate;

struct _CtDdMcc {
    KObject     parent;
    kint32      dat;
};

KConstType      ct_dd_mcc_get_type(void);

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
void	        ct_dd_mcc_main(CtDdMcc *self, kint argc, KType* argv);

CtDdMcc*        ct_dd_mcc_new(void);

#endif /* __CT_DD_MCC_H__ */
