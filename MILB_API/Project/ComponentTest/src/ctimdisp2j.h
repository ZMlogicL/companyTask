/*
 *ctimdisp2j.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2J_H__
#define __CT_IM_DISP2J_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2J	(ct_im_disp2j_get_type())
#define CT_IM_DISP2J(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2j))
#define CT_IS_IM_DISP2J(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2J)

typedef struct _CtImDisp2j CtImDisp2j;
typedef struct _CtImDisp2jPrivate		CtImDisp2jPrivate;

struct _CtImDisp2j{
	ImDisp2Parent parent;
};

KConstType 			ct_im_disp2j_get_type(void);
CtImDisp2j *			ct_im_disp2j_new(void);

#endif /* __CT_IM_DISP2J_H__ */
