/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr3类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR3_H__
#define __CT_IM_CNR3_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR3					(ct_im_cnr3_get_type())
#define CT_IM_CNR3(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr3)) 
#define CT_IS_IM_CNR3(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR3))
#define CT_IM_CNR3_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR3, CtImCnr3Class)) 
#define CT_IS_IM_CNR3_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR3))
#define CT_IM_CNR3_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR3, CtImCnr3Class))  

typedef struct 	_CtImCnr3 			CtImCnr3;
typedef struct 	_CtImCnr3Private 	CtImCnr3Private;
typedef struct  _CtImCnr3Class  	CtImCnr3Class;

struct _CtImCnr3
{
	GObject parent;
	UCHAR ch3;

};

struct  _CtImCnr3Class {
	GObjectClass parentclass;
}

GType 		ct_im_cnr3_get_type(void) G_GNUC_CONST;
CtImCnr3* 	ct_im_cnr3_new(void);

INT32 ct_im_cnr_ofl_1_16(CtImCnr3 *self);
INT32 ct_im_cnr_ofl_1_18(CtImCnr3 *self);
INT32 ct_im_cnr_ofl_1_19(CtImCnr3 *self);
INT32 ct_im_cnr_ofl_1_21(CtImCnr3 *self);
INT32 ct_im_cnr_ofl_1_22(CtImCnr3 *self);
INT32 ct_im_cnr_ofl_1_33(CtImCnr3 *self);
INT32 ct_im_cnr_ofl_1_34(CtImCnr3 *self);
INT32 ct_im_cnr_ofl_1_55(CtImCnr3 *self);
INT32 ct_im_cnr_6_6(CtImCnr3 *self);
INT32 ct_im_cnr_6_8(CtImCnr3 *self);
INT32 ct_im_cnr_6_9(CtImCnr3 *self);

G_END_DECLS
#endif /* __CT_IM_CNR3_H_ */
