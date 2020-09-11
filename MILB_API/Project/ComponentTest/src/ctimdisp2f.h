/*
 *ctimdisp2f.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2F_H__
#define __CT_IM_DISP2F_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2F	(ct_im_disp2f_get_type())
#define CT_IM_DISP2F(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2f))
#define CT_IS_IM_DISP2F(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2F)

typedef struct _CtImDisp2f CtImDisp2f;
typedef struct _CtImDisp2fPrivate		CtImDisp2fPrivate;

struct _CtImDisp2f{
	ImDisp2Parent parent;
};

KConstType 			ct_im_disp2f_get_type(void);
CtImDisp2f *			ct_im_disp2f_new(void);

#endif /* __CT_IM_DISP2F_H__ */
