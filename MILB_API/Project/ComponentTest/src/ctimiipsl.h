/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :王印斌
*@brief               :CtImIipSl类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_IIP_SL_H_
#define __CT_IM_IIP_SL_H_

#include "ddim_typedef.h"
#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_IIP_SL				(ct_im_iip_sl_get_type())
#define CT_IM_IIP_SL(obj)				(G_TYPE_CHECK_INSTANCE_CAST(obj, CtImIipSl))
#define CT_IM_IIP_SL_CLASS(kclass)  	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_IIP_SL, CtImIipSlClass))
#define CT_IS_IM_IIP_SL(obj)			(G_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_IIP_SL))
#define CT_IS_IM_IIP_SL_CLASS(kclass) 	(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_IIP_SL))
#define CT_IM_IIP_SL_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_IIP_SL, CtImIipSlClass))

typedef struct 	_CtImIipSl 			CtImIipSl;
typedef struct 	_CtImIipSlPrivate 	CtImIipSlPrivate;
typedef struct  _CtImIipSlClass		CtImIipSlClass;

struct _CtImIipSl {
	GObject parent;
	UINT32 ctNo;

};

struct _CtImIipSlClass {
	GObjectClass parentclass;
}

GType 		ct_im_iip_sl_get_type(void) G_GNUC_CONST;
CtImIipSl* 	ct_im_iip_sl_new(void);

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

// SL Unit
INT32 ct_im_iip_10_1_1(void);
INT32 ct_im_iip_10_1_2(void);
INT32 ct_im_iip_run_10_1(CtImIipSl *self);

#ifdef __cplusplus
}
#endif	// __cplusplus

G_END_DECLS

#endif /* __CT_IM_IIP_SL_H_ */
