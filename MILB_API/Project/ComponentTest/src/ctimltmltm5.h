/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm5类
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#ifndef __CT_IM_LTM_LTM_5_H__
#define __CT_IM_LTM_LTM_5_H__

#include "./../../../fj/glib/src/gobject.h"
#include "ctimltmltm4.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_LTM_LTM_5             		(ct_im_ltm_ltm5_get_type())
#define CT_IM_LTM_LTM_5(obj)                 		(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_LTM_LTM_5, CtImLtmLtm5))
#define CT_IM_LTM_LTM_5_CALSS(klass)    	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_LTM_LTM_5, CtImLtmLtm5Class))
#define CT_IS_IM_LTM_LTM_5(obj)             	 	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_LTM_LTM_5))
#define CT_IS_IM_LTM_LTM_5_CLASS(klass) 	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_LTM_LTM_5))
#define CT_IM_LTM_LTM_5_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_LTM_LTM_5, CtImLtmLtm5Class))


typedef struct _CtImLtmLtm5           	CtImLtmLtm5;
typedef struct _CtImLtmLtm5Class  	CtImLtmLtm5Class;
typedef struct _CtImLtmLtm5Private	CtImLtmLtm5Private;


struct _CtImLtmLtm5
{
	GObject    parent;
};

struct _CtImLtmLtm5Class
{
	GObjectClass    parentClass;
};


GType     		  		ct_im_ltm_ltm5_get_type(void);
CtImLtmLtm5*   ct_im_ltm_ltm5_new();

gint32 	ct_im_ltm_ltm5_1_23(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_1_24(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_1_25(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_1(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_2(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_3(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_4(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_5(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_6(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_7(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_8(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_9(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_10(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_11(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_12(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_13(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_14(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_15(CtImLtmLtm5 *self);
gint32	ct_im_ltm_ltm5_2_16(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_17(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_18(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_19(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_20(CtImLtmLtm5 *self);
gint32 	ct_im_ltm_ltm5_2_21(CtImLtmLtm5 *self);
void 	ct_im_ltm_ltm5_set_ltm4(CtImLtmLtm5 *self,CtImLtmLtm4 *ltm4);


G_END_DECLS
#endif /* __CT_IM_LTM_LTM_5_H_ */

