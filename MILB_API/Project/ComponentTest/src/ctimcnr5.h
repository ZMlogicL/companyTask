/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr5类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR5_H__
#define __CT_IM_CNR5_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR5					(ct_im_cnr5_get_type())
#define CT_IM_CNR5(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr5)) 
#define CT_IS_IM_CNR5(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR5))
#define CT_IM_CNR5_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR5, CtImCnr5Class)) 
#define CT_IS_IM_CNR5_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR5))
#define CT_IM_CNR5_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR5, CtImCnr5Class))  

typedef struct 	_CtImCnr5 			CtImCnr5;
typedef struct 	_CtImCnr5Private 	CtImCnr5Private;
typedef struct  _CtImCnr5Class  	CtImCnr5Class;

struct _CtImCnr5
{
	GObject parent;
	UCHAR ch5;
};

struct  _CtImCnr5Class {
	GObjectClass parentclass;
}

GType 		ct_im_cnr5_get_type(void) G_GNUC_CONST;
CtImCnr5* 	ct_im_cnr5_new(void);

INT32 ct_im_cnr_ofl_1_27(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_31(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_37(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_38(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_39(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_40(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_41(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_42(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_43(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_44(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_45(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_46(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_47(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_48(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_49(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_50(CtImCnr5* self);
INT32 ct_im_cnr_ofl_1_51(CtImCnr5* self);
INT32 ct_im_cnr_6_11(CtImCnr5* self);

G_END_DECLS
#endif /* __CT_IM_CNR5_H_ */
