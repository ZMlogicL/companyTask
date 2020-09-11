/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr8类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR8_H__
#define __CT_IM_CNR8_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR8					(ct_im_cnr8_get_type())
#define CT_IM_CNR8(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr8)) 
#define CT_IS_IM_CNR8(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR8))
#define CT_IM_CNR8_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR8, CtImCnr8Class)) 
#define CT_IS_IM_CNR8_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR8))
#define CT_IM_CNR8_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR8, CtImCnr8Class))  

typedef struct 	_CtImCnr8 			CtImCnr8;
typedef struct 	_CtImCnr8Private 	CtImCnr8Private;
typedef struct  _CtImCnr8Class  	CtImCnr8Class;

struct _CtImCnr8
{
	GObject parent;
	UCHAR ch8;
};

struct  _CtImCnr8Class {
	GObjectClass parentclass;
}

GType 		ct_im_cnr8_get_type(void) G_GNUC_CONST;
CtImCnr8* 	ct_im_cnr8_new(void);

INT32 ct_im_cnr_otf_3_14(CtImCnr8 *self);
INT32 ct_im_cnr_otf_3_15(CtImCnr8 *self);
INT32 ct_im_cnr_otf_3_16(CtImCnr8 *self);
INT32 ct_im_cnr_otf_3_17(CtImCnr8 *self);
INT32 ct_im_cnr_otf_3_21(CtImCnr8 *self);
INT32 ct_im_cnr_otf_3_22(CtImCnr8 *self);
INT32 ct_im_cnr_6_16(CtImCnr8 *self);
INT32 ct_im_cnr_6_17(CtImCnr8 *self);
INT32 ct_im_cnr_6_18(CtImCnr8 *self);
INT32 ct_im_cnr_6_19(CtImCnr8 *self);

G_END_DECLS
#endif /* __CT_IM_CNR8_H_ */
