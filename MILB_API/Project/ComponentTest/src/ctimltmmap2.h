/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmMap2类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#ifndef __CT_IM_LTM_MAP_2_H__
#define __CT_IM_LTM_MAP_2_H__

#include "./../../../fj/glib/src/gobject.h"
#include "ctimltmmap3.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_LTM_MAP_2                  		(ct_im_ltm_map2_get_type())
#define CT_IM_LTM_MAP_2(obj)                    		(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_LTM_MAP_2, CtImLtmMap2))
#define CT_IM_LTM_MAP_2_CALSS(klass)       	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_LTM_MAP_2, CtImLtmMap2Class))
#define CT_IS_IM_LTM_MAP_2(obj)                 	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_LTM_MAP_2))
#define CT_IS_IM_LTM_MAP_2_CLASS(klass) 		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_LTM_MAP_2))
#define CT_IM_LTM_MAP_2_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_LTM_MAP_2, CtImLtmMap2Class))


typedef struct _CtImLtmMap2               	CtImLtmMap2;
typedef struct _CtImLtmMap2Class      	CtImLtmMap2Class;
typedef struct _CtImLtmMap2Private		CtImLtmMap2Private;


struct _CtImLtmMap2
{
	GObject    parent;
};

struct _CtImLtmMap2Class
{
	GObjectClass    parentClass;
};


GType     		  		ct_im_ltm_map2_get_type(void);
CtImLtmMap2*  ct_im_ltm_map2_new();

gint32 	ct_im_ltm_map2_1_1( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_2( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_3( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_4( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_5( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_6( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_10( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_11( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_12( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_13( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_14( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_15( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_16( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_17( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_18( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_19( CtImLtmMap2 *self );
gint32 	ct_im_ltm_map2_1_20( CtImLtmMap2 *self );
void 	ct_im_ltm_map2_set_map3(CtImLtmMap2* self, CtImLtmMap3* map3);


G_END_DECLS
#endif /* __CT_IM_LTM_MAP_2_H_ */

