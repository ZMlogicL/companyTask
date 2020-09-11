/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr10类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR10_H__
#define __CT_IM_CNR10_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR10				(ct_im_cnr10_get_type())
#define CT_IM_CNR10(obj)				(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr10)) 
#define CT_IS_IM_CNR10(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR10))
#define CT_IM_CNR10_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR10, CtImCnr10Class)) 
#define CT_IS_IM_CNR10_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR10))
#define CT_IM_CNR10_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR10, CtImCnr10Class))  

typedef struct 	_CtImCnr10 			CtImCnr10;
typedef struct 	_CtImCnr10Private 	CtImCnr10Private;
typedef struct  _CtImCnr10Class  	CtImCnr10Class;

struct _CtImCnr10
{
	GObject parent;
	UCHAR ch10;
};

struct  _CtImCnr10Class {
	GObjectClass parentclass;
}

GType 	ct_im_cnr10_get_type(void) G_GNUC_CONST;
CtImCnr10* 	ct_im_cnr10_new(void);

INT32 ct_im_cnr_otf_3_25(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_30(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_31(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_32(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_33(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_34(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_35(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_36(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_37(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_38(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_39(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_40(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_41(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_42(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_43(CtImCnr10 *self);
INT32 ct_im_cnr_otf_3_44(CtImCnr10 *self);
INT32 ct_im_cnr_6_22(CtImCnr10 *self);

G_END_DECLS
#endif /* __CT_IM_CNR10_H_ */
