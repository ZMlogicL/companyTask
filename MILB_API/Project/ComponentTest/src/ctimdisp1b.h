/*
 *ctimdisp1b.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP1B_H__
#define __CT_IM_DISP1B_H__

#include "imdisp1parent.h"

#define CT_TYPE_IM_DISP1B	(ct_im_disp1b_get_type())
#define CT_IM_DISP1B(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp1b))
#define CT_IS_IM_DISP1B(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP1B)

typedef struct _CtImDisp1b CtImDisp1b;
typedef struct _CtImDisp1bPrivate		CtImDisp1bPrivate;

struct _CtImDisp1b{
	ImDisp1Parent parent;
};

KConstType 			ct_im_disp1b_get_type(void);
CtImDisp1b *		ct_im_disp1b_new();

#endif /* __CT_IM_DISP1B_H__ */
