/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr14类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR14_H_
#define __CT_IM_CNR14_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR14				(ct_im_cnr14_get_type())
#define CT_IM_CNR14(obj)				(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr14)) 
#define CT_IS_IM_CNR14(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR14))
#define CT_IM_CNR14_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR14, CtImCnr14Class)) 
#define CT_IS_IM_CNR14_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR14))
#define CT_IM_CNR14_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR14, CtImCnr14Class))  

typedef struct 	_CtImCnr14 			CtImCnr14;
typedef struct 	_CtImCnr14Private 	CtImCnr14Private;
typedef struct  _CtImCnr14Class  	CtImCnr14Class;

struct _CtImCnr14 {
	GObject parent;
	UCHAR ch14;
};

struct  _CtImCnr14Class {
	GObjectClass parentclass;
}

GType ct_im_cnr14_get_type(void) G_GNUC_CONST;
CtImCnr14* ct_im_cnr14_new(void);

INT32 ct_im_cnr_otf_4_1(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_2(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_3(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_4(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_5(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_6(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_7(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_8(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_9(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_10(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_11(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_12(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_13(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_14(CtImCnr14 *self);
INT32 ct_im_cnr_otf_4_15(CtImCnr14 *self);
INT32 ct_im_cnr_run_4(CtImCnr14 *self, const UINT32 ctNo2nd);

G_END_DECLS
#endif /* __CT_IM_CNR14_H_ */
