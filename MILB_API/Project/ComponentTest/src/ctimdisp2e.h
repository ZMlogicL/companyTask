/*
 *ctimdisp2e.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2E_H__
#define __CT_IM_DISP2E_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2E	(ct_im_disp2e_get_type())
#define CT_IM_DISP2E(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2e))
#define CT_IS_IM_DISP2E(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2E)

typedef struct _CtImDisp2e CtImDisp2e;
typedef struct _CtImDisp2ePrivate		CtImDisp2ePrivate;

struct _CtImDisp2e{
	ImDisp2Parent parent;
};

KConstType 			ct_im_disp2e_get_type(void);
CtImDisp2e *		ct_im_disp2e_new(void);

#endif /* __CT_IM_DISP2E_H__ */
