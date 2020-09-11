/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr6类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR6_H__
#define __CT_IM_CNR6_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR6					(ct_im_cnr6_get_type())
#define CT_IM_CNR6(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr6)) 
#define CT_IS_IM_CNR6(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR6))
#define CT_IM_CNR6_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR6, CtImCnr6Class)) 
#define CT_IS_IM_CNR6_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR6))
#define CT_IM_CNR6_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR6, CtImCnr6Class))  

typedef struct 	_CtImCnr6 			CtImCnr6;
typedef struct 	_CtImCnr6Private 	CtImCnr6Private;
typedef struct  _CtImCnr6Class  	CtImCnr6Class;

struct _CtImCnr6
{
	GObject parent;
	UCHAR ch6;
};

struct  _CtImCnr6Class {
	GObjectClass parentclass;
}

GType 		ct_im_cnr6_get_type(void) G_GNUC_CONST;
CtImCnr6* 	ct_im_cnr6_new(void);

INT32 ct_im_cnr_ofl_2_1(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_2(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_3(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_4(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_5(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_6(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_7(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_8(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_9(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_10(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_11(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_12(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_13(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_14(CtImCnr6 *self);
INT32 ct_im_cnr_ofl_2_15(CtImCnr6 *self);
INT32 ct_im_cnr_otf_3_1(CtImCnr6 *self);
INT32 ct_im_cnr_otf_3_2(CtImCnr6 *self);
INT32 ct_im_cnr_otf_3_3(CtImCnr6 *self);
INT32 ct_im_cnr_otf_3_4(CtImCnr6 *self);
INT32 ct_im_cnr_otf_3_5(CtImCnr6 *self);
INT32 ct_im_cnr_otf_3_6(CtImCnr6 *self);
INT32 ct_im_cnr_otf_3_7(CtImCnr6 *self);
INT32 ct_im_cnr_otf_3_8(CtImCnr6 *self);
INT32 ct_im_cnr_run_2(CtImCnr6 *self, const UINT32 ctNo2nd);

G_END_DECLS
#endif /* __CT_IM_CNR6_H_ */
