/*
 *imdisp2group.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __IM_DISP2_GROUP_H__
#define __IM_DISP2_GROUP_H__

#include "imdisp2parent.h"

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define IM_TYPE_DISP2_GROUP					(im_disp2_group_get_type ())
#define IM_DISP2_GROUP(widget)				(G_TYPE_CHECK_INSTANCE_CAST((widget), \
				IM_TYPE_DISP2_GROUP, ImDisp2Group))
#define IM_DISP2_GROUP_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), \
		IM_TYPE_DISP2_GROUP, ImDisp2GroupClass))
#define IM_IS_DISP2_GROUP(widget)			(G_TYPE_CHECK_INSTANCE_TYPE((widget), IM_TYPE_DISP2_GROUP))
#define IM_IS_DISP2_GROUP_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), IM_TYPE_DISP2_GROUP))
#define IM_DISP2_GROUP_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), \
		IM_TYPE_DISP2_GROUP, ImDisp2GroupClass))

/*
 * 以下开始类结构体声明
 * */
typedef struct _ImDisp2Group 		ImDisp2Group;
typedef struct _ImDisp2GroupClass 	ImDisp2GroupClass;
typedef struct _ImDisp2GroupPrivate 	ImDisp2GroupPrivate;

typedef enum {
	ImDisp2Group_DO_IM_DISP_TEST = 1,
	ImDisp2Group_DO_IM_DISP_TEST_A,
	ImDisp2Group_DO_IM_DISP_TEST_B,
	ImDisp2Group_DO_IM_DISP_TEST_C,
	ImDisp2Group_DO_IM_DISP_TEST_D,
	ImDisp2Group_DO_IM_DISP_TEST_E,
	ImDisp2Group_DO_IM_DISP_TEST_F,
	ImDisp2Group_DO_IM_DISP_TEST_G,
	ImDisp2Group_DO_IM_DISP_TEST_H,
	ImDisp2Group_DO_IM_DISP_TEST_I,
	ImDisp2Group_DO_IM_DISP_TEST_J,
	ImDisp2Group_DO_IM_DISP_TEST_K,
	ImDisp2Group_DO_IM_DISP_TEST_L,
	ImDisp2Group_DO_IM_DISP_TEST_M,
	ImDisp2Group_DO_IM_DISP_TEST_N,
	ImDisp2Group_DO_IM_DISP_TEST_O,
	ImDisp2Group_DO_IM_DISP_TEST_END,
}ImDisp2GroupDoMainType;

typedef struct _Disp2bNewParams{
	gpointer pOutCtrlTrgLimit;
	gpointer pOutCtrl;
}Disp2bNewParams;

struct _ImDisp2Group
{
	GObject parent;
	/*public*/
	ImDisp2GroupPrivate *privImDisp2Group;
};

struct _ImDisp2GroupClass
{
	GObjectClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 											im_disp2_group_get_type(void) G_GNUC_CONST;
ImDisp2Group *							im_disp2_group_new(guchar *pclkCounter, guchar *hclkCounter);

ImDisp2Parent *							im_disp2_group_create_im_disp(ImDisp2Group *self,
															ImDisp2GroupDoMainType mainType, GData data);
GObject *										im_disp2_group_get_disp4(ImDisp2Group *self);
T_IM_DISP_CTRL_MAIN_TBL *		im_disp2_group_get_main_tbl(ImDisp2Group *self);
T_IM_DISP_CTRL_OUTPUT_TBL *	im_disp2_group_get_output_tbl(ImDisp2Group *self);
T_IM_DISP_CTRL_OUTPUT *			im_disp2_group_get_output_ctl(ImDisp2Group *self);
guchar *										im_disp2_group_get_pclk_counter(ImDisp2Group *self);
guchar *										im_disp2_group_get_hclk_counter(ImDisp2Group *self);
void 											im_disp2_group_set_disp3(ImDisp2Group *self, GObject *obj3);
GObject * 										im_disp2_group_get_disp3(ImDisp2Group *self);
void 											im_disp2_group_set_disp3a(ImDisp2Group *self, GObject *obj3a);
GObject * 										im_disp2_group_get_disp3a(ImDisp2Group *self);

G_END_DECLS

#endif /* __IM_DISP2_GROUP_H__ */
