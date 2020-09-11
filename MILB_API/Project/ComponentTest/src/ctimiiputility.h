/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipUtility类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_im_iip_utility.h
 * @brief		This is ct header for im_iip_utility.c.
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_IM_IIP_UTILITY_H__
#define __CT_IM_IIP_UTILITY_H__

#include <klib.h>
#include "ddim_typedef.h"

#define CT_TYPE_IM_IIP_UTILITY          (ct_im_iip_utility_get_type())
#define CT_IM_IIP_UTILITY(obj)          (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipUtility)) 
#define CT_IS_IM_IIP_UTILITY(obj)       (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_UTILITY)) 

typedef struct                          _CtImIipUtility CtImIipUtility;
typedef struct                          _CtImIipUtilityPrivate CtImIipUtilityPrivate;

struct _CtImIipUtility {
    KObject parent;
};

KConstType      ct_im_iip_utility_get_type(void);

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
/* Global Data															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */


/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// Utility
kint32           ct_im_iip_utility_14_1_1(CtImIipUtility *self);
kint32           ct_im_iip_utility_14_1_2(CtImIipUtility *self);
kint32           ct_im_iip_utility_14_1_3(CtImIipUtility *self);
kint32           ct_im_iip_utility_14_1_4(CtImIipUtility *self);
kint32           ct_im_iip_utility_14_1_5(CtImIipUtility *self);
kint32           ct_im_iip_utility_run_14_1(CtImIipUtility *self, const kuint32 ctNo3rd);

#ifdef __cplusplus
}
#endif	// __cplusplus

CtImIipUtility* ct_im_iip_utility_new(void);

#endif /* __CT_IM_IIP_UTILITY_H__ */
