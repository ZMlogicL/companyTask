/*
 *ctimdisp2.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-02
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2_H__
#define __CT_IM_DISP2_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2	(ct_im_disp2_get_type())
#define CT_IM_DISP2(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2))
#define CT_IS_IM_DISP2(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2)

typedef struct _CtImDisp2 CtImDisp2;
typedef struct _CtImDisp2Private		CtImDisp2Private;

struct _CtImDisp2{
	ImDisp2Parent parent;
	CtImDisp2Private *privCtImDisp2;
};

KConstType 			ct_im_disp2_get_type(void);
CtImDisp2 *			ct_im_disp2_new(void);

#endif /* __CT_IM_DISP2_H__ */
