/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR1_H__
#define __CT_IM_CNR1_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR1				 	(ct_im_cnr1_get_type())
#define CT_IM_CNR1(obj)				 	(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr1))
#define CT_IS_IM_CNR1(obj)			 	(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR1))
#define CT_IM_CNR1_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR1, CtImCnr1Class)) 
#define CT_IS_IM_CNR1_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR1))
#define CT_IM_CNR1_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR1, CtImCnr1Class)) 

typedef struct 	_CtImCnr1 			CtImCnr1;
typedef struct 	_CtImCnr1Private 	CtImCnr1Private;
typedef struct  _CtImCnr1Class  	CtImCnr1Class;

struct _CtImCnr1
{
	GObject parent;
	UCHAR ch1;

};

struct  _CtImCnr1Class {
	GObjectClass parentclass;
}

GType 		ct_im_cnr1_get_type(void) G_GNUC_CONST;
CtImCnr1* 	ct_im_cnr1_new(void);

INT32 ct_im_cnr_set_im_r2y_set(CtImCnr1 *self);
INT32 ct_im_cnr_set_im_r2y_start(CtImCnr1 *self);
INT32 ct_im_cnr_set_im_r2y_stop(CtImCnr1 *self);

INT32 ct_im_cnr_ofl_1_1(CtImCnr1 *self);
INT32 ct_im_cnr_ofl_1_2(CtImCnr1 *self);
INT32 ct_im_cnr_ofl_1_3(CtImCnr1 *self);
INT32 ct_im_cnr_ofl_1_4(CtImCnr1 *self);
INT32 ct_im_cnr_ofl_1_52(CtImCnr1 *self);
INT32 ct_im_cnr_ofl_1_53(CtImCnr1 *self);

G_END_DECLS
#endif /* __CT_IM_CNR1_H__ */
