/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmMap3类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#ifndef __CT_IM_LTM_MAP_3_H__
#define __CT_IM_LTM_MAP_3_H__

#include "./../../../fj/glib/src/gobject.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_LTM_MAP_3                    	(ct_im_ltm_map3_get_type())
#define CT_IM_LTM_MAP_3(obj)                      	(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_LTM_MAP_3, CtImLtmMap3))
#define CT_IM_LTM_MAP_3_CALSS(klass)         	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_LTM_MAP_3, CtImLtmMap3Class))
#define CT_IS_IM_LTM_MAP_3(obj)                  	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_LTM_MAP_3))
#define CT_IS_IM_LTM_MAP_3_CLASS(klass)  		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_LTM_MAP_3))
#define CT_IM_LTM_MAP_3_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_LTM_MAP_3, CtImLtmMap3Class))


typedef struct _CtImLtmMap3               	CtImLtmMap3;
typedef struct _CtImLtmMap3Class      	CtImLtmMap3Class;
typedef struct _CtImLtmMap3Private 	CtImLtmMap3Private;


struct _CtImLtmMap3
{
	GObject    parent;
	 guchar 	pipeNo;
};

struct _CtImLtmMap3Class
{
	GObjectClass    parentClass;
};


GType     		 	 	ct_im_ltm_map3_get_type(void);
CtImLtmMap3*  ct_im_ltm_map3_new();

gint32 ct_im_ltm_map3_1_9( CtImLtmMap3 *self );
gint32 ct_im_ltm_map3_3_2( CtImLtmMap3 *self );
gint32 ct_im_ltm_map3_3_4( CtImLtmMap3 *self );
gint32 ct_im_ltm_map3_3_3( CtImLtmMap3 *self );
gint32 ct_im_ltm_map3_3_5( CtImLtmMap3 *self );
gint32 ct_im_ltm_map3_3_6( CtImLtmMap3 *self );
gint32 ct_im_ltm_map3_3_7( CtImLtmMap3 *self );
gint32 ct_im_ltm_map3_3_8( CtImLtmMap3 *self );
gint32 ct_im_ltm_map3_3_9( CtImLtmMap3 *self );
gint32 ct_im_ltm_map3_3_10( CtImLtmMap3 *self );
gint32 ct_im_ltm_map3_3_12( CtImLtmMap3 *self );
gint32 ct_im_ltm_map3_3_11( CtImLtmMap3 *self );

G_END_DECLS


#endif /* __CT_IM_LTM_MAP_3_H_ */

