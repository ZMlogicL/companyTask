/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr9类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR9_H__
#define __CT_IM_CNR9_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR9					(ct_im_cnr9_get_type())
#define CT_IM_CNR9(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr9)) 
#define CT_IS_IM_CNR9(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR9)) 
#define CT_IM_CNR9_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR9, CtImCnr9Class)) 
#define CT_IS_IM_CNR9_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR9))
#define CT_IM_CNR9_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR9, CtImCnr9Class)) 

typedef struct 	_CtImCnr9 			CtImCnr9;
typedef struct 	_CtImCnr9Private 	CtImCnr9Private;
typedef struct  _CtImCnr9Class  	CtImCnr9Class;

struct _CtImCnr9
{
	GObject parent;
	UCHAR ch9;
};

struct  _CtImCnr9Class {
	GObjectClass parentclass;
}

GType 		ct_im_cnr9_get_type(void) G_GNUC_CONST;
CtImCnr9* 	ct_im_cnr9_new(void);

INT32 ct_im_cnr_otf_3_18(CtImCnr9 *self);
INT32 ct_im_cnr_otf_3_19(CtImCnr9 *self);
INT32 ct_im_cnr_otf_3_23(CtImCnr9 *self);
INT32 ct_im_cnr_otf_3_24(CtImCnr9 *self);
INT32 ct_im_cnr_6_20(CtImCnr9 *self);
INT32 ct_im_cnr_6_23(CtImCnr9 *self);
INT32 ct_im_cnr_6_24(CtImCnr9 *self);

G_END_DECLS
#endif /* __CT_IM_CNR9_H_ */
