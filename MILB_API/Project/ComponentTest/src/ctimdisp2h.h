/*
 *ctimdisp2h.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2H_H__
#define __CT_IM_DISP2H_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2H	(ct_im_disp2h_get_type())
#define CT_IM_DISP2H(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2h))
#define CT_IS_IM_DISP2H(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2H)

typedef struct _CtImDisp2h CtImDisp2h;
typedef struct _CtImDisp2hPrivate		CtImDisp2hPrivate;

struct _CtImDisp2h{
	ImDisp2Parent parent;
};

KConstType 			ct_im_disp2h_get_type(void);
CtImDisp2h *		ct_im_disp2h_new(void);

#endif /* __CT_IM_DISP2H_H__ */
