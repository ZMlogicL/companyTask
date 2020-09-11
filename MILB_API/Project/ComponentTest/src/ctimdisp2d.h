/*
 *ctimdisp2d.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2D_H__
#define __CT_IM_DISP2D_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2D	(ct_im_disp2d_get_type())
#define CT_IM_DISP2D(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2d))
#define CT_IS_IM_DISP2D(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2D)

typedef struct _CtImDisp2d CtImDisp2d;
typedef struct _CtImDisp2dPrivate		CtImDisp2dPrivate;

struct _CtImDisp2d{
	ImDisp2Parent parent;
	CtImDisp2dPrivate *ctImDisp2dPrivate;
};

KConstType 			ct_im_disp2d_get_type(void);
CtImDisp2d *		ct_im_disp2d_new(void);

#endif /* __CT_IM_DISP2D_H__ */
