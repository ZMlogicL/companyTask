/*
 *ctimdisp1d.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP1D_H__
#define __CT_IM_DISP1D_H__

#include "imdisp1parent.h"

#define CT_TYPE_IM_DISP1D	(ct_im_disp1d_get_type())
#define CT_IM_DISP1D(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp1d))
#define CT_IS_IM_DISP1D(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP1D)

typedef struct _CtImDisp1d CtImDisp1d;
typedef struct _CtImDisp1dPrivate		CtImDisp1dPrivate;

struct _CtImDisp1d{
	ImDisp1Parent parent;
};

KConstType 			ct_im_disp1d_get_type(void);
CtImDisp1d *		ct_im_disp1d_new();

#endif /* __CT_IM_DISP1D_H__ */
