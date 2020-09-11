/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#ifndef __CT_IM_LTM_LTM_H__
#define __CT_IM_LTM_LTM_H__

#include "./../../../fj/glib/src/gobject.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_LTM_LTM                	(ct_im_ltm_ltm_get_type())
#define CT_IM_LTM_LTM(obj)                   	(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_LTM_LTM, CtImLtmLtm))
#define CT_IM_LTM_LTM_CALSS(klass)    	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_LTM_LTM, CtImLtmLtmClass))
#define CT_IS_IM_LTM_LTM(obj)                	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_LTM_LTM))
#define CT_IS_IM_LTM_LTM_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_LTM_LTM))
#define CT_IM_LTM_LTM_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_LTM_LTM, CtImLtmLtmClass))

#define CtImLtmLtm_CHECK_TARGET_PIPE_NO1(a)		(((a)+1) & (D_IM_LTM_PIPE1+1))
#define CtImLtmLtm_CHECK_TARGET_PIPE_NO2(a)		(((a)+1) & (D_IM_LTM_PIPE2+1))

typedef struct _CtImLtmLtm        		CtImLtmLtm;
typedef struct _CtImLtmLtmClass    	CtImLtmLtmClass;
typedef struct _CtImLtmLtmPrivate 	CtImLtmLtmPrivate;


struct _CtImLtmLtm
{
	GObject    parent;
};

struct _CtImLtmLtmClass
{
	GObjectClass    parentClass;
};


GType     		  		ct_im_ltm_ltm_get_type(void);
CtImLtmLtm*    	ct_im_ltm_ltm_new();

void ct_im_ltm_ltm_run(CtImLtmLtm *self,const guint32 ctIdx1st, const guint32 ctIdx2nd, const guint32 ctIdx3rd);
void ct_im_ltm_ltm_main(CtImLtmLtm *self,gint32 argc, gchar** argv);


G_END_DECLS

#endif /* __CT_IM_LTM_LTM_H_ */

