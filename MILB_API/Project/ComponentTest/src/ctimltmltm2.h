/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm2类
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#ifndef __CT_IM_LTM_LTM_2_H__
#define __CT_IM_LTM_LTM_2_H__

#include "./../../../fj/glib/src/gobject.h"
#include "ctimltmltm4.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_LTM_LTM_2               		(ct_im_ltm_ltm2_get_type())
#define CT_IM_LTM_LTM_2(obj)                   	(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_LTM_LTM_2, CtImLtmLtm2))
#define CT_IM_LTM_LTM_2_CALSS(klass)     	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_LTM_LTM_2, CtImLtmLtm2Class))
#define CT_IS_IM_LTM_LTM_2(obj)            		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_LTM_LTM_2))
#define CT_IS_IM_LTM_LTM_2_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_LTM_LTM_2))
#define CT_IM_LTM_LTM_2_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_LTM_LTM_2, CtImLtmLtm2Class))


typedef struct _CtImLtmLtm2           	CtImLtmLtm2;
typedef struct _CtImLtmLtm2Class   	CtImLtmLtm2Class;
typedef struct _CtImLtmLtm2Private	CtImLtmLtm2Private;


struct _CtImLtmLtm2
{
	GObject    parent;
    T_IM_LTM_LTM_CTRL_BLEND gctImLtmLtmCtrlBlend;
};

struct _CtImLtmLtm2Class
{
	GObjectClass    parentClass;
};


GType     		  		ct_im_ltm_ltm2_get_type(void);
CtImLtmLtm2*   ct_im_ltm_ltm2_new();

void ct_im_ltm_ltm2_print_ctrl_sdram_input_reg(void);
void ct_im_ltm_ltm2_print_all_reg(void);

gint32 	ct_im_ltm_ltm2_3_12(CtImLtmLtm2 *self);
gint32 	ct_im_ltm_ltm2_3_13(CtImLtmLtm2 *self);
gint32 	ct_im_ltm_ltm2_3_14(CtImLtmLtm2 *self);
gint32 	ct_im_ltm_ltm2_3_15(CtImLtmLtm2 *self);
void 	ct_im_ltm_ltm2_set_ltm4(CtImLtmLtm2 *self,CtImLtmLtm4 *ltm4);


G_END_DECLS
#endif /* __CT_IM_LTM_LTM_2_H_ */

