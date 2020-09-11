/*
 *ctimdisp2l.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2L_H__
#define __CT_IM_DISP2L_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2L	(ct_im_disp2l_get_type())
#define CT_IM_DISP2L(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2l))
#define CT_IS_IM_DISP2L(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2L)

typedef struct _CtImDisp2l CtImDisp2l;
typedef struct _CtImDisp2lPrivate		CtImDisp2lPrivate;

struct _CtImDisp2l{
	ImDisp2Parent parent;
};

KConstType 			ct_im_disp2l_get_type(void);
CtImDisp2l *			ct_im_disp2l_new(void);

#endif /* __CT_IM_DISP2L_H__ */
