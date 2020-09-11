/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr13类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR13_H_
#define __CT_IM_CNR13_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR13				(ct_im_cnr13_get_type())
#define CT_IM_CNR13(obj)				(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr13)) 
#define CT_IS_IM_CNR13(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR13))
#define CT_IM_CNR13_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR13, CtImCnr13Class)) 
#define CT_IS_IM_CNR13_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR13))
#define CT_IM_CNR13_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR13, CtImCnr13Class))  

typedef struct 	_CtImCnr13 			CtImCnr13;
typedef struct 	_CtImCnr13Private 	CtImCnr13Private;
typedef struct  _CtImCnr13Class  	CtImCnr13Class;

struct _CtImCnr13
{
	GObject parent;
	UCHAR ch13;
};

struct  _CtImCnr13Class {
	GObjectClass parentclass;
}

GType ct_im_cnr13_get_type(void) G_GNUC_CONST;
CtImCnr13* ct_im_cnr13_new(void);

INT32 ct_im_cnr_ofl_1_5(CtImCnr13 *self);
INT32 ct_im_cnr_ofl_1_6(CtImCnr13 *self);
INT32 ct_im_cnr_ofl_1_7(CtImCnr13 *self);
INT32 ct_im_cnr_ofl_1_8(CtImCnr13 *self);
INT32 ct_im_cnr_ofl_1_9(CtImCnr13 *self);
INT32 ct_im_cnr_ofl_1_10(CtImCnr13 *self);
INT32 ct_im_cnr_ofl_1_11(CtImCnr13 *self);
INT32 ct_im_cnr_ofl_1_12(CtImCnr13 *self);
INT32 ct_im_cnr_6_1(CtImCnr13 *self);

G_END_DECLS
#endif /* __CT_IM_CNR13_H_ */
