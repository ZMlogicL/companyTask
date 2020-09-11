/*
 *ctimdisp2b.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2B_H__
#define __CT_IM_DISP2B_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2B	(ct_im_disp2b_get_type())
#define CT_IM_DISP2B(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2b))
#define CT_IS_IM_DISP2B(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2B)

typedef struct _CtImDisp2b CtImDisp2b;
typedef struct _CtImDisp2bPrivate		CtImDisp2bPrivate;
typedef struct _Disp2bNewParams Disp2bNewParams;

struct _CtImDisp2b{
	ImDisp2Parent parent;
	CtImDisp2bPrivate *privCtImDisp2b;
};

KConstType 			ct_im_disp2b_get_type(void);
CtImDisp2b *		ct_im_disp2b_new(Disp2bNewParams *disp2NewParams);

#endif /* __CT_IM_DISP2B_H__ */
