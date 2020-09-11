/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmMap类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#ifndef __CT_IM_LTM_MAP_H__
#define __CT_IM_LTM_MAP_H__

#include "./../../../fj/glib/src/gobject.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_LTM_MAP                  		(ct_im_ltm_map_get_type())
#define CT_IM_LTM_MAP(obj)                   		(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_LTM_MAP, CtImLtmMap))
#define CT_IM_LTM_MAP_CALSS(klass)    		(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_LTM_MAP, CtImLtmMapClass))
#define CT_IS_IM_LTM_MAP(obj)                		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_LTM_MAP))
#define CT_IS_IM_LTM_MAP_CLASS(klass) 		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_LTM_MAP))
#define CT_IM_LTM_MAP_GET_CLASS(obj) 	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_LTM_MAP, CtImLtmMapClass))


typedef struct _CtImLtmMap            	CtImLtmMap;
typedef struct _CtImLtmMapClass   	CtImLtmMapClass;
typedef struct _CtImLtmMapPrivate 	CtImLtmMapPrivate;


struct _CtImLtmMap
{
	GObject    parent;
};

struct _CtImLtmMapClass
{
	GObjectClass    parentClass;
};


GType     		  		ct_im_ltm_map_get_type(void);
CtImLtmMap*  	ct_im_ltm_map_new();

void ct_im_ltm_map_run(CtImLtmMap *self,const guint32 ctIdx1st, const guint32 ctIdx2nd, const guint32 ctIdx3rd);
void ct_im_ltm_map_main(CtImLtmMap *self,gint32 argc, gchar** argv);


G_END_DECLS
#endif /* __CT_IM_LTM_MAP_H_ */

