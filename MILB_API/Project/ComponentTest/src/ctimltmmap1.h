/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmMap1类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#ifndef __CT_IM_LTM_MAP_1_H__
#define __CT_IM_LTM_MAP_1_H__

#include "./../../../fj/glib/src/gobject.h"
#include "ctimltmmap3.h"

G_BEGIN_DECLS

#define CT_TYPE_IM_LTM_MAP_1                     	(ct_im_ltm_map1_get_type())
#define CT_IM_LTM_MAP_1(obj)                        	(G_TYPE_CHECK_INSTANCE_CAST ((obj), CT_TYPE_IM_LTM_MAP_1, CtImLtmMap1))
#define CT_IM_LTM_MAP_1_CALSS(klass)          	(G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_LTM_MAP_1, CtImLtmMap1Class))
#define CT_IS_IM_LTM_MAP_1(obj)                 	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_LTM_MAP_1))
#define CT_IS_IM_LTM_MAP_1_CLASS(klass) 		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_LTM_MAP_1))
#define CT_IM_LTM_MAP_1_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_LTM_MAP_1, CtImLtmMap1Class))

#define CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO1(a)		(((a)+1) & (D_IM_LTM_PIPE1+1))
#define CtImLtmMap1_CT_IM_LTM_MAP_CHECK_TARGET_PIPENO2(a)		(((a)+1) & (D_IM_LTM_PIPE2+1))

typedef struct _CtImLtmMap1          		CtImLtmMap1;
typedef struct _CtImLtmMap1Class      	CtImLtmMap1Class;
typedef struct _CtImLtmMap1Private		CtImLtmMap1Private;


struct _CtImLtmMap1
{
	GObject    parent;
};

struct _CtImLtmMap1Class
{
	GObjectClass    parentClass;
};


GType     		  		ct_im_ltm_map1_get_type(void);
CtImLtmMap1*  ct_im_ltm_map1_new();

void ct_im_ltm_map1_handler( guint32* result, guint32 userParam );
void ct_im_ltm_map1_print_ctrl_sdram_input_reg( void );
void ct_im_ltm_map1_print_all_reg( void );

gint32 ct_im_ltm_map1_1_21( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_3_1( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_1_7( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_1_8( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_1( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_2( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_3( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_4( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_5( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_6( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_7( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_8( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_9( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_10( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_11( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_12( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_13( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_14( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_15( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_16( CtImLtmMap1 *self );
gint32 ct_im_ltm_map1_2_17( CtImLtmMap1 *self );
void   ct_im_ltm_map1_set_map3(CtImLtmMap1* self, CtImLtmMap3* map3);


G_END_DECLS
#endif /* __CT_IM_LTM_MAP_1_H_ */

