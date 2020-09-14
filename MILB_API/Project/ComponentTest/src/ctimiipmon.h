/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipMon类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_im_iip_mon.h
 * @brief		This is ct header for im_iip_mon.c.
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef __CT_IM_IIP_MON_H__
#define __CT_IM_IIP_MON_H__

#include <klib.h>
#include "ddimtypedef.h"

#define CT_TYPE_IM_IIP_MON                  (ct_im_iip_mon_get_type())
#define CT_IM_IIP_MON(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipMon)) 
#define CT_IS_IM_IIP_MON(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_MON)) 

typedef struct                              _CtImIipMon CtImIipMon;
typedef struct                              _CtImIipMonPrivate CtImIipMonPrivate;

struct _CtImIipMon {
    KObject parent;
};

KConstType      ct_im_iip_mon_get_type(void);

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


// MON Unit
kint32           ct_im_iip_mon_11_1_1(CtImIipMon *self);
kint32           ct_im_iip_mon_11_1_2(CtImIipMon *self);
kint32           ct_im_iip_mon_run_11_1(CtImIipMon *self, const kuint32 ctNo3rd);


#ifdef __cplusplus
}
#endif	// __cplusplus

CtImIipMon*     ct_im_iip_mon_new(void);

#endif /* __CT_IM_IIP_MON_H__ */
