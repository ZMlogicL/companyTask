/*
 *ctimdisp2a.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2A_H__
#define __CT_IM_DISP2A_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2A	(ct_im_disp2a_get_type())
#define CT_IM_DISP2A(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2a))
#define CT_IS_IM_DISP2A(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2A)

typedef struct _CtImDisp2a CtImDisp2a;
typedef struct _CtImDisp2aPrivate		CtImDisp2aPrivate;

struct _CtImDisp2a{
	ImDisp2Parent parent;
	CtImDisp2aPrivate *privCtImDisp2a;
};

KConstType 			ct_im_disp2a_get_type(void);
CtImDisp2a *		ct_im_disp2a_new(void);

#endif /* __CT_IM_DISP2A_H__ */
