/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm3类
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#ifndef __CT_IM_LTM_LTM_3_H__
#define __CT_IM_LTM_LTM_3_H__

#include "./../../../fj/glib/src/gobject.h"
#include "ctimltmltm4.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_LTM_LTM_3                 	(ct_im_ltm_ltm3_get_type())
#define CT_IM_LTM_LTM_3(obj)                  		(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_LTM_LTM_3, CtImLtmLtm3))
#define CT_IM_LTM_LTM_3_CALSS(klass)   		(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_LTM_LTM_3, CtImLtmLtm3Class))
#define CT_IS_IM_LTM_LTM_3(obj)                	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_LTM_LTM_3))
#define CT_IS_IM_LTM_LTM_3_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_LTM_LTM_3))
#define CT_IM_LTM_LTM_3_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_LTM_LTM_3, CtImLtmLtm3Class))


typedef struct _CtImLtmLtm3            	CtImLtmLtm3;
typedef struct _CtImLtmLtm3Class    	CtImLtmLtm3Class;
typedef struct _CtImLtmLtm3Private	CtImLtmLtm3Private;


struct _CtImLtmLtm3
{
	GObject    parent;
};

struct _CtImLtmLtm3Class
{
	GObjectClass    parentClass;
};


GType     		  		ct_im_ltm_ltm3_get_type(void);
CtImLtmLtm3*   ct_im_ltm_ltm3_new();

gint32 	ct_im_ltm_ltm3_1_1(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_2(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_3(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_4(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_5(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_6(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_11(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_14(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_15(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_16(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_17(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_18(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_19(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_20(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_21(CtImLtmLtm3 *self);
gint32 	ct_im_ltm_ltm3_1_22(CtImLtmLtm3 *self);
void 	ct_im_ltm_ltm3_set_ltm4(CtImLtmLtm3 *self,CtImLtmLtm4 *ltm4);


G_END_DECLS
#endif /* __CT_IM_LTM_LTM_3_H_ */

