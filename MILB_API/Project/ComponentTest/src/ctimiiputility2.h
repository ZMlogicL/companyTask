/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipUtility2类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __CT_IM_IIP_UTILITY2_H__
#define __CT_IM_IIP_UTILITY2_H__

#include <klib.h>
#include "ddimtypedef.h"

#define CT_TYPE_IM_IIP_UTILITY2                 (ct_im_iip_utility2_get_type())
#define CT_IM_IIP_UTILITY2(obj)                 (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipUtility2)) 
#define CT_IS_IM_IIP_UTILITY2(obj)              (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_UTILITY2)) 

typedef struct                          _CtImIipUtility2 CtImIipUtility2;
typedef struct                          _CtImIipUtility2Private CtImIipUtility2Private;

struct _CtImIipUtility2 {
    KObject parent;
};

KConstType          ct_im_iip_utility2_get_type(void);

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
kint32               ct_im_iip_utility2_14_4_1(CtImIipUtility2 *self);
kint32               ct_im_iip_utility2_14_4_2(CtImIipUtility2 *self);
kint32               ct_im_iip_utility2_14_4_3(CtImIipUtility2 *self);
kint32               ct_im_iip_utility2_14_4_4(CtImIipUtility2 *self);
kint32               ct_im_iip_utility2_run_14_4(CtImIipUtility2 *self, const kuint32 ctNo3rd);

#ifdef __cplusplus
}
#endif	// __cplusplus

CtImIipUtility2*    ct_im_iip_utility2_new(void);

#endif /* __CT_IM_IIP_UTILITY2_H__ */
