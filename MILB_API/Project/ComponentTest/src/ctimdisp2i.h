/*
 *ctimdisp2i.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2I_H__
#define __CT_IM_DISP2I_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2I	(ct_im_disp2i_get_type())
#define CT_IM_DISP2I(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2i))
#define CT_IS_IM_DISP2I(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2I)

typedef struct _CtImDisp2i CtImDisp2i;
typedef struct _CtImDisp2iPrivate		CtImDisp2iPrivate;

struct _CtImDisp2i{
	ImDisp2Parent parent;
};

KConstType 			ct_im_disp2i_get_type(void);
CtImDisp2i *			ct_im_disp2i_new(void);

#endif /* __CT_IM_DISP2I_H__ */
