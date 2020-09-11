/*
 *imdisp1group.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-08
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __IM_DISP1_GROUP_H__
#define __IM_DISP1_GROUP_H__

#include "imdisp1parent.h"

#define IM_TYPE_DISP1_GROUP				(im_disp1_group_get_type())
#define IM_DISP1_GROUP(obj)					(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp1Group))
#define IM_IS_DISP1_GROUP(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP1_GROUP)

typedef struct _ImDisp1Group 					ImDisp1Group;
typedef struct _ImDisp1GroupPrivate			ImDisp1GroupPrivate;

struct _ImDisp1Group{
	KObject parent;
	ImDisp1GroupPrivate *privImDisp1Group;
};

KConstType 			im_disp1_group_get_type(void);
ImDisp1Group *	im_disp1_group_new(kuchar *pclkCounter, kuchar *hclkCounter);

ImDisp1Parent *	im_disp1_group_get_pctest_instance(ImDisp1Group *self);
kuchar *				im_disp1_group_get_pclk_counter(ImDisp1Group *self);
kuchar *				im_disp1_group_get_hclk_counter(ImDisp1Group *self);
void 					im_disp1_group_ct_im_disp3_pclk_counter_on(ImDisp1Group *self);
void 					im_disp1_group_ct_im_disp3_pclk_counter_off(ImDisp1Group *self);

#endif /* __IM_DISP1_GROUP_H__ */
