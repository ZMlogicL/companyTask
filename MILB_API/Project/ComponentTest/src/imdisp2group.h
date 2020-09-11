/*
 *imdisp2group.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-07
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

#define IM_TYPE_DISP2_GROUP	(im_disp2_group_get_type())
#define IM_DISP2_GROUP(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp2Group))
#define IM_IS_DISP2_GROUP(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP2_GROUP)

typedef struct _ImDisp2Group ImDisp2Group;
typedef struct _ImDisp2GroupPrivate		ImDisp2GroupPrivate;

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
	kpointer pOutCtrlTrgLimit;
	kpointer pOutCtrl;
}Disp2bNewParams;

struct _ImDisp2Group{
	KObject parent;
	ImDisp2GroupPrivate *privImDisp2Group;
};

KConstType 									im_disp2_group_get_type(void);
ImDisp2Group *							im_disp2_group_new(kuchar *pclkCounter, kuchar *hclkCounter);

ImDisp2Parent *							im_disp2_group_create_im_disp(ImDisp2Group *self,
															ImDisp2GroupDoMainType mainType, KData data);
KObject *										im_disp2_group_get_disp4(ImDisp2Group *self);
T_IM_DISP_CTRL_MAIN_TBL *		im_disp2_group_get_main_tbl(ImDisp2Group *self);
T_IM_DISP_CTRL_OUTPUT_TBL *	im_disp2_group_get_output_tbl(ImDisp2Group *self);
T_IM_DISP_CTRL_OUTPUT *			im_disp2_group_get_output_ctl(ImDisp2Group *self);
kuchar *										im_disp2_group_get_pclk_counter(ImDisp2Group *self);
kuchar *										im_disp2_group_get_hclk_counter(ImDisp2Group *self);
void 											im_disp2_group_set_disp3(ImDisp2Group *self, KObject *obj3);
KObject * 										im_disp2_group_get_disp3(ImDisp2Group *self);
void 											im_disp2_group_set_disp3a(ImDisp2Group *self, KObject *obj3a);
KObject * 										im_disp2_group_get_disp3a(ImDisp2Group *self);

#endif /* __IM_DISP2_GROUP_H__ */
