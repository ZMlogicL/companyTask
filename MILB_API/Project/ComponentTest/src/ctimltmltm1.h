/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm1类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#ifndef __CT_IM_LTM_LTM_1_H__
#define __CT_IM_LTM_LTM_1_H__

#include "./../../../fj/glib/src/gobject.h"
#include "ctimltmltm4.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_LTM_LTM_1               		(ct_im_ltm_ltm1_get_type())
#define CT_IM_LTM_LTM_1(obj)                  		(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_LTM_LTM_1, CtImLtmLtm1))
#define CT_IM_LTM_LTM_1_CALSS(klass)      	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_LTM_LTM_1, CtImLtmLtm1Class))
#define CT_IS_IM_LTM_LTM_1(obj)                	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_LTM_LTM_1))
#define CT_IS_IM_LTM_LTM_1_CLASS(klass) 	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_LTM_LTM_1))
#define CT_IM_LTM_LTM_1_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_LTM_LTM_1, CtImLtmLtm1Class))


typedef struct _CtImLtmLtm1        		CtImLtmLtm1;
typedef struct _CtImLtmLtm1Class  	CtImLtmLtm1Class;
typedef struct _CtImLtmLtm1Private	CtImLtmLtm1Private;


struct _CtImLtmLtm1
{
	GObject    parent;
};

struct _CtImLtmLtm1Class
{
	GObjectClass    parentClass;
};


GType     		  		ct_im_ltm_ltm1_get_type(void);
CtImLtmLtm1*   ct_im_ltm_ltm1_new();

gint32 					ct_im_ltm_ltm1_1_7(CtImLtmLtm1 *self);
gint32 					ct_im_ltm_ltm1_1_8(CtImLtmLtm1 *self);
gint32 					ct_im_ltm_ltm1_1_12(CtImLtmLtm1 *self);
gint32 					ct_im_ltm_ltm1_3_7(CtImLtmLtm1 *self);
gint32 					ct_im_ltm_ltm1_3_8(CtImLtmLtm1 *self);
gint32 					ct_im_ltm_ltm1_3_9(CtImLtmLtm1 *self);
gint32 					ct_im_ltm_ltm1_3_10(CtImLtmLtm1 *self);
gint32 					ct_im_ltm_ltm1_3_11(CtImLtmLtm1 *self);
gint32 					ct_im_ltm_ltm1_1_9(CtImLtmLtm1 *self);
gint32 					ct_im_ltm_ltm1_1_10(CtImLtmLtm1 *self);
gint32 					ct_im_ltm_ltm1_1_13(CtImLtmLtm1 *self);
void 					ct_im_ltm_ltm1_set_ltm4(CtImLtmLtm1 *self,CtImLtmLtm4 *ltm4);
guchar 				ct_im_ltm_ltm1_get_self1(CtImLtmLtm1 *self);


G_END_DECLS
#endif /* __CT_IM_LTM_LTM_1_H_ */

