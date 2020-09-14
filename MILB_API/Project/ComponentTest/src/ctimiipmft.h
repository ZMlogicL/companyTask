/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipMft类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_im_iip_mft.h
 * @brief		This is ct header for im_iip_mft.c.
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_IM_IIP_MFT_H__
#define __CT_IM_IIP_MFT_H__

#include <klib.h>
#include "ddimtypedef.h"

#define CT_TYPE_IM_IIP_MFT                  (ct_im_iip_mft_get_type())
#define CT_IM_IIP_MFT(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipMft)) 
#define CT_IS_IM_IIP_MFT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_MFT)) 

typedef struct                              _CtImIipMft CtImIipMft;
typedef struct                              _CtImIipMftPrivate CtImIipMftPrivate;

struct _CtImIipMft {
    KObject parent;
};

KConstType          ct_im_iip_mft_get_type(void);

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


// FLT Unit
kint32               ct_im_iip_mft_15_1_1(CtImIipMft *self);
kint32               ct_im_iip_mft_run_15_1(CtImIipMft *self, const kuint32 ctNo3rd);


#ifdef __cplusplus
}
#endif	// __cplusplus

CtImIipMft*         ct_im_iip_mft_new(void);

#endif /* __CT_IM_IIP_MFT_H__ */
