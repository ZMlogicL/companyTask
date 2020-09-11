/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr7类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR7_H__
#define __CT_IM_CNR7_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR7					(ct_im_cnr7_get_type())
#define CT_IM_CNR7(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr7)) 
#define CT_IS_IM_CNR7(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR7)) 
#define CT_IM_CNR7_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR7, CtImCnr7Class)) 
#define CT_IS_IM_CNR7_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR7))
#define CT_IM_CNR7_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR7, CtImCnr7Class)) 

typedef struct 	_CtImCnr7 			CtImCnr7;
typedef struct 	_CtImCnr7Private 	CtImCnr7Private;
typedef struct  _CtImCnr7Class  	CtImCnr7Class;

struct _CtImCnr7
{
	GObject parent;
	UCHAR ch7;

};

struct  _CtImCnr7Class {
	GObjectClass parentclass;
}

GType 		ct_im_cnr7_get_type(void) G_GNUC_CONST;
CtImCnr7* 	ct_im_cnr7_new(void);

INT32 ct_im_cnr_otf_3_9(CtImCnr7 *self);
INT32 ct_im_cnr_otf_3_10(CtImCnr7 *self);
INT32 ct_im_cnr_otf_3_11(CtImCnr7 *self);
INT32 ct_im_cnr_otf_3_12(CtImCnr7 *self);
INT32 ct_im_cnr_otf_3_13(CtImCnr7 *self);
INT32 ct_im_cnr_otf_3_20(CtImCnr7 *self);
INT32 ct_im_cnr_otf_3_26(CtImCnr7 *self);
INT32 ct_im_cnr_6_14(CtImCnr7 *self);
INT32 ct_im_cnr_6_15(CtImCnr7 *self);

G_END_DECLS
#endif /* __CT_IM_CNR7_H_ */
