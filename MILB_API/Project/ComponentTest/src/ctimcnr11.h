/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :王印斌
*@brief               :CtImCnr11类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_CNR11_H__
#define __CT_IM_CNR11_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR11				(ct_im_cnr11_get_type())
#define CT_IM_CNR11(obj)				(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImCnr11)) 
#define CT_IS_IM_CNR11(obj)				(G_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_CNR11))
#define CT_IM_CNR11_CLASS(kclass) 	 	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR11, CtImCnr11Class)) 
#define CT_IS_IM_CNR11_CLASS(obj)		(G_TYPE_CHECK_CLASS_TYPE((klass), CT_TYPE_IM_CNR11))
#define CT_IM_CNR11_GET_CLASS(kclass) 	(G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR11, CtImCnr11Class))  

typedef struct 	_CtImCnr11 			CtImCnr11;
typedef struct 	_CtImCnr11Private 	CtImCnr11Private;
typedef struct  _CtImCnr11Class  	CtImCnr11Class;

struct _CtImCnr11
{
	GObject parent;
	UCHAR ch11;
};

struct  _CtImCnr11Class {
	GObjectClass parentclass;
}

GType 	ct_im_cnr11_get_type(void) G_GNUC_CONST;
CtImCnr11* 	ct_im_cnr11_new(void);

INT32 ct_im_cnr_otf_3_45(CtImCnr11 *self);
INT32 ct_im_cnr_otf_3_46(CtImCnr11 *self);
INT32 ct_im_cnr_otf_3_47(CtImCnr11 *self);
INT32 ct_im_cnr_otf_3_48(CtImCnr11 *self);
INT32 ct_im_cnr_otf_3_49(CtImCnr11 *self);
INT32 ct_im_cnr_otf_3_50(CtImCnr11 *self);
INT32 ct_im_cnr_otf_3_51(CtImCnr11 *self);
INT32 ct_im_cnr_run_3(CtImCnr11 *self, const UINT32 ctNo2nd, CtImCnr6 *ctim6);

G_END_DECLS
#endif /* __CT_IM_CNR11_H_ */
