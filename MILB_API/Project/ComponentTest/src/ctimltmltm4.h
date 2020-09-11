/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm4类
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#ifndef __CT_IM_LTM_LTM_4_H__
#define __CT_IM_LTM_LTM_4_H__

#include "./../../../fj/glib/src/gobject.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_LTM_LTM_4                		(ct_im_ltm_ltm4_get_type())
#define CT_IM_LTM_LTM_4(obj)                    	(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_LTM_LTM_4, CtImLtmLtm4))
#define CT_IM_LTM_LTM_4_CALSS(klass)      	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_LTM_LTM_4, CtImLtmLtm4Class))
#define CT_IS_IM_LTM_LTM_4(obj)              	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_LTM_LTM_4))
#define CT_IS_IM_LTM_LTM_4_CLASS(klass) 	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_LTM_LTM_4))
#define CT_IM_LTM_LTM_4_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_LTM_LTM_4, CtImLtmLtm4Class))


typedef struct _CtImLtmLtm4       		CtImLtmLtm4;
typedef struct _CtImLtmLtm4Class   	CtImLtmLtm4Class;
typedef struct _CtImLtmLtm4Private	CtImLtmLtm4Private;


struct _CtImLtmLtm4
{
	GObject    parent;
	guchar 	pipeNo;
};

struct _CtImLtmLtm4Class
{
	GObjectClass    parentClass;
};


GType     		  		ct_im_ltm_ltm4_get_type(void);
CtImLtmLtm4*   ct_im_ltm_ltm4_new();

gint32 ct_im_ltm_ltm4_3_1(CtImLtmLtm4 *self);
gint32 ct_im_ltm_ltm4_3_2(CtImLtmLtm4 *self);
gint32 ct_im_ltm_ltm4_3_3(CtImLtmLtm4 *self);
gint32 ct_im_ltm_ltm4_3_4(CtImLtmLtm4 *self);
gint32 ct_im_ltm_ltm4_3_5(CtImLtmLtm4 *self);
gint32 ct_im_ltm_ltm4_3_6(CtImLtmLtm4 *self);
T_IM_LTM_LTM_CTRL_COMMON *			ct_im_ltm_ltm4_get1(CtImLtmLtm4 *self);
T_IM_LTM_LTM_CTRL_SDRAM_INPUT *		ct_im_ltm_ltm4_get2(CtImLtmLtm4 *self);
T_IM_LTM_INADDR_INFO *						ct_im_ltm_ltm4_get3(CtImLtmLtm4 *self);
T_IM_LTM_LTM_INDATA_INFO *				ct_im_ltm_ltm4_get4(CtImLtmLtm4 *self);
T_IM_LTM_LTM_OUTDATA_INFO *				ct_im_ltm_ltm4_get5(CtImLtmLtm4 *self);
T_IM_LTM_CTRL_YLOG *							ct_im_ltm_ltm4_get6(CtImLtmLtm4 *self);


G_END_DECLS
#endif /* __CT_IM_LTM_LTM_4_H_ */

