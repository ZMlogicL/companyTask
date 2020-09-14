/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipUtility1类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __CT_IM_IIP_UTILITY1_H__
#define __CT_IM_IIP_UTILITY1_H__

#include <klib.h>
#include "ddimtypedef.h"

#define CT_TYPE_IM_IIP_UTILITY1                 (ct_im_iip_utility1_get_type())
#define CT_IM_IIP_UTILITY1(obj)                 (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipUtility1)) 
#define CT_IS_IM_IIP_UTILITY1(obj)              (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_UTILITY1)) 

typedef struct                          _CtImIipUtility1 CtImIipUtility1;
typedef struct                          _CtImIipUtility1Private CtImIipUtility1Private;

struct _CtImIipUtility1 {
    KObject parent;
};

KConstType          ct_im_iip_utility1_get_type(void);

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
kint32               ct_im_iip_utility1_14_2_1(CtImIipUtility1 *self);
kint32               ct_im_iip_utility1_14_2_2(CtImIipUtility1 *self);
kint32               ct_im_iip_utility1_run_14_2(CtImIipUtility1 *self, const kuint32 ctNo3rd);

kint32               ct_im_iip_utility1_14_3_1(CtImIipUtility1 *self);
kint32               ct_im_iip_utility1_14_3_2(CtImIipUtility1 *self);
kint32               ct_im_iip_utility1_run_14_3(CtImIipUtility1 *self, const kuint32 ctNo3rd);

#ifdef __cplusplus
}
#endif	// __cplusplus

CtImIipUtility1*    ct_im_iip_utility1_new(void);

#endif /* __CT_IM_IIP_UTILITY1_H__ */
