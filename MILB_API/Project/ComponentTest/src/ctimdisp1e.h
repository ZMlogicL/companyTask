/*
 *ctimdisp1e.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP1E_H__
#define __CT_IM_DISP1E_H__

#include "imdisp1parent.h"

#define CT_TYPE_IM_DISP1E	(ct_im_disp1e_get_type())
#define CT_IM_DISP1E(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp1e))
#define CT_IS_IM_DISP1E(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP1E)

typedef struct _CtImDisp1e CtImDisp1e;
typedef struct _CtImDisp1ePrivate		CtImDisp1ePrivate;

struct _CtImDisp1e{
	ImDisp1Parent parent;
//	kpointer privCtImDisp1e;
};

KConstType 		ct_im_disp1e_get_type(void);
CtImDisp1e *	ct_im_disp1e_new(void);

#endif /* __CT_IM_DISP1E_H__ */
