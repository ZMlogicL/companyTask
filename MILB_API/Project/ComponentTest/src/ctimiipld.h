/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipLd类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_im_iip_ld.h
 * @brief		This is ct header for im_iip_ld.c.
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_IM_IIP_LD_H__
#define __CT_IM_IIP_LD_H__

#include <klib.h>
#include "ddimtypedef.h"

#define CT_TYPE_IM_IIP_LD                  (ct_im_iip_ld_get_type())
#define CT_IM_IIP_LD(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipLd)) 
#define CT_IS_IM_IIP_LD(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_LD)) 

typedef struct                             _CtImIipLd CtImIipLd;
typedef struct                             _CtImIipLdPrivate CtImIipLdPrivate;

struct _CtImIipLd {
    KObject parent;
};

KConstType  ct_im_iip_ld_get_type(void);

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


// LD Unit
kint32       ct_im_iip_ld_8_1_1(CtImIipLd *self);
kint32       ct_im_iip_ld_8_1_2(CtImIipLd *self);
kint32       ct_im_iip_ld_8_1_3(CtImIipLd *self);
kint32       ct_im_iip_ld_run_8_1(CtImIipLd *self, const kuint32 ctNo3rd);


#ifdef __cplusplus
}
#endif	// __cplusplus

CtImIipLd*  ct_im_iip_ld_new(void);

#endif /* __CT_IM_IIP_LD_H__ */
