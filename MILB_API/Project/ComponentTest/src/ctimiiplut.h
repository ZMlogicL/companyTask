/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipLut类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_im_iip_lut.h
 * @brief		This is ct header for im_iip_lut.c.
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_IM_IIP_LUT_H__
#define __CT_IM_IIP_LUT_H__

#include <klib.h>
#include "ddim_typedef.h"

#define CT_TYPE_IM_IIP_LUT                  (ct_im_iip_lut_get_type())
#define CT_IM_IIP_LUT(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipLut)) 
#define CT_IS_IM_IIP_LUT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_LUT)) 

typedef struct                              _CtImIipLut CtImIipLut;
typedef struct                              _CtImIipLutPrivate CtImIipLutPrivate;

struct _CtImIipLut {
    KObject parent;
};

KConstType      ct_im_iip_lut_get_type(void);

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


// LUT Unit
kint32           ct_im_iip_lut_5_1_1(CtImIipLut *self);
kint32           ct_im_iip_lut_5_1_2(CtImIipLut *self);
kint32           ct_im_iip_lut_run_5_1(CtImIipLut *self, const kuint32 ctNo3rd);


#ifdef __cplusplus
}
#endif	// __cplusplus

CtImIipLut*     ct_im_iip_lut_new(void);

#endif /* __CT_IM_IIP_LUT_H__ */
