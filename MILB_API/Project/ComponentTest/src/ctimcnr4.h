/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr4类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR4_H__
#define __CT_IM_CNR4_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR4					(ct_im_cnr4_get_type())
#define CT_IM_CNR4(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr4)) 
#define CT_IS_IM_CNR4(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR4))
#define CT_IM_CNR4_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR4, CtImCnr4Class)) 
#define CT_IS_IM_CNR4_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR4))
#define CT_IM_CNR4_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR4, CtImCnr4Class))  

typedef struct 	_CtImCnr4 			CtImCnr4;
typedef struct 	_CtImCnr4Private 	CtImCnr4Private;
typedef struct  _CtImCnr4Class  	CtImCnr4Class;

struct _CtImCnr4
{
	GObject parent;
	UCHAR ch4;

};

struct  _CtImCnr4Class {
	GObjectClass parentclass;
}

GType 		ct_im_cnr4_get_type(void) G_GNUC_CONST;
CtImCnr4* 	ct_im_cnr4_new(void);

INT32 ct_im_cnr_ofl_1_20(CtImCnr4 *self);
INT32 ct_im_cnr_ofl_1_25(CtImCnr4 *self);
INT32 ct_im_cnr_ofl_1_26(CtImCnr4 *self);
INT32 ct_im_cnr_ofl_1_35(CtImCnr4 *self);
INT32 ct_im_cnr_ofl_1_36(CtImCnr4 *self);
INT32 ct_im_cnr_6_3(CtImCnr4 *self);
INT32 ct_im_cnr_6_12(CtImCnr4 *self);
INT32 ct_im_cnr_6_13(CtImCnr4 *self);

G_END_DECLS
#endif /* __CT_IM_CNR4_H_ */
