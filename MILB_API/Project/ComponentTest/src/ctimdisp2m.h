/*
 *ctimdisp2m.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2M_H__
#define __CT_IM_DISP2M_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2M	(ct_im_disp2m_get_type())
#define CT_IM_DISP2M(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2m))
#define CT_IS_IM_DISP2M(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2M)

typedef struct _CtImDisp2m CtImDisp2m;
typedef struct _CtImDisp2mPrivate		CtImDisp2mPrivate;

struct _CtImDisp2m{
	ImDisp2Parent parent;
};

KConstType 			ct_im_disp2m_get_type(void);
CtImDisp2m *		ct_im_disp2m_new(void);

#endif /* __CT_IM_DISP2M_H__ */
