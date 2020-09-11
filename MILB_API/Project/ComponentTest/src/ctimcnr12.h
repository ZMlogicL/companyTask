/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr12类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR12_H_
#define __CT_IM_CNR12_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR12				(ct_im_cnr12_get_type())
#define CT_IM_CNR12(obj)				(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr12)) 
#define CT_IS_IM_CNR12(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR12))
#define CT_IM_CNR12_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR12, CtImCnr12Class)) 
#define CT_IS_IM_CNR12_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR12))
#define CT_IM_CNR12_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR12, CtImCnr12Class))  

typedef struct 	_CtImCnr12 			CtImCnr12;
typedef struct 	_CtImCnr12Private 	CtImCnr12Private;
typedef struct  _CtImCnr12Class  	CtImCnr12Class;

struct _CtImCnr12
{
	GObject parent;
	UCHAR ch1;
	UCHAR ch2;
};

struct  _CtImCnr12Class {
	GObjectClass parentclass;
}

GType ct_im_cnr12_get_type(void) G_GNUC_CONST;
CtImCnr12* ct_im_cnr12_new(void);

INT32 ct_im_cnr_5_1(CtImCnr12 *self);
INT32 ct_im_cnr_5_2(CtImCnr12 *self);
INT32 ct_im_cnr_5_3(CtImCnr12 *self);
INT32 ct_im_cnr_5_4(CtImCnr12 *self);
INT32 ct_im_cnr_5_5(CtImCnr12 *self);
INT32 ct_im_cnr_5_6(CtImCnr12 *self);
INT32 ct_im_cnr_5_7(CtImCnr12 *self);
INT32 ct_im_cnr_5_8(CtImCnr12 *self);
INT32 ct_im_cnr_5_9(CtImCnr12 *self);
INT32 ct_im_cnr_5_10(CtImCnr12 *self);
INT32 ct_im_cnr_5_11(CtImCnr12 *self);
INT32 ct_im_cnr_5_12(CtImCnr12 *self);
INT32 ct_im_cnr_run_5(CtImCnr12 *self, const UINT32 ct_no_2nd);

G_END_DECLS
#endif /* __CT_IM_CNR12_H_ */
