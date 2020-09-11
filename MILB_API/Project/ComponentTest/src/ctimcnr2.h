/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr2类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR2_H__
#define __CT_IM_CNR2_H__

#include <klib.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR2					(ct_im_cnr2_get_type())
#define CT_IM_CNR2(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr2)) 
#define CT_IS_IM_CNR2(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR2))
#define CT_IM_CNR2_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR2, CtImCnr2Class)) 
#define CT_IS_IM_CNR2_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR2))
#define CT_IM_CNR2_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR2, CtImCnr2Class))  

typedef struct 	_CtImCnr2 			CtImCnr2;
typedef struct 	_CtImCnr2Private 	CtImCnr2Private;
typedef struct  _CtImCnr2Class  	CtImCnr2Class;

struct _CtImCnr2
{
	GObject parent;
	UCHAR ch2;

};

struct  _CtImCnr2Class {
	GObjectClass parentclass;
}

GType 		ct_im_cnr2_get_type(void) G_GNUC_CONST;
CtImCnr2* 	ct_im_cnr2_new(void);

INT32 ct_im_cnr_ofl_1_13(CtImCnr2 *self);
INT32 ct_im_cnr_ofl_1_14(CtImCnr2 *self);
INT32 ct_im_cnr_ofl_1_15(CtImCnr2 *self);
INT32 ct_im_cnr_ofl_1_17(CtImCnr2 *self);
INT32 ct_im_cnr_ofl_1_23(CtImCnr2 *self);
INT32 ct_im_cnr_ofl_1_24(CtImCnr2 *self);
INT32 ct_im_cnr_ofl_1_30(CtImCnr2 *self);
INT32 ct_im_cnr_ofl_1_32(CtImCnr2 *self);
INT32 ct_im_cnr_ofl_1_54(CtImCnr2 *self);
INT32 ct_im_cnr_6_2(CtImCnr2 *self);
INT32 ct_im_cnr_6_4(CtImCnr2 *self);
INT32 ct_im_cnr_6_5(CtImCnr2 *self);
INT32 ct_im_cnr_6_7(CtImCnr2 *self);

G_END_DECLS
#endif /* __CT_IM_CNR2_H_ */
