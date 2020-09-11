/*
 *ctimdisp2k.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2K_H__
#define __CT_IM_DISP2K_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2K	(ct_im_disp2k_get_type())
#define CT_IM_DISP2K(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2k))
#define CT_IS_IM_DISP2K(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2K)

typedef struct _CtImDisp2k CtImDisp2k;
typedef struct _CtImDisp2kPrivate		CtImDisp2kPrivate;

struct _CtImDisp2k{
	ImDisp2Parent parent;
};

KConstType 			ct_im_disp2k_get_type(void);
CtImDisp2k *		ct_im_disp2k_new(void);

#endif /* __CT_IM_DISP2K_H__ */
