/*
 *ctimdisp1a.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP1A_H__
#define __CT_IM_DISP1A_H__

#include "imdisp1parent.h"

#define CT_TYPE_IM_DISP1A	(ct_im_disp1a_get_type())
#define CT_IM_DISP1A(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp1a))
#define CT_IS_IM_DISP1A(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP1A)

typedef struct _CtImDisp1a CtImDisp1a;
typedef struct _CtImDisp1aPrivate		CtImDisp1aPrivate;

struct _CtImDisp1a{
	ImDisp1Parent parent;
};

KConstType 			ct_im_disp1a_get_type(void);
CtImDisp1a *		ct_im_disp1a_new();

#endif /* __CT_IM_DISP1A_H__ */
