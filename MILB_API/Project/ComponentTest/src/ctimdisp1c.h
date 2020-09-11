/*
 *ctimdisp1c.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP1C_H__
#define __CT_IM_DISP1C_H__

#include "imdisp1parent.h"

#define CT_TYPE_IM_DISP1C	(ct_im_disp1c_get_type())
#define CT_IM_DISP1C(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp1c))
#define CT_IS_IM_DISP1C(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP1C)

typedef struct _CtImDisp1c CtImDisp1c;
typedef struct _CtImDisp1cPrivate		CtImDisp1cPrivate;

struct _CtImDisp1c{
	ImDisp1Parent parent;
};

KConstType 			ct_im_disp1c_get_type(void);
CtImDisp1c *		ct_im_disp1c_new();

#endif /* __CT_IM_DISP1C_H__ */
