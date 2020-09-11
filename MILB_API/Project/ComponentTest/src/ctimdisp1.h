/*
 *ctimdisp1.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-02
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP1_H__
#define __CT_IM_DISP1_H__

#include "imdisp1parent.h"

#define CT_TYPE_IM_DISP1	(ct_im_disp1_get_type())
#define CT_IM_DISP1(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp1))
#define CT_IS_IM_DISP1(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP1)

typedef struct _CtImDisp1 CtImDisp1;
typedef struct _CtImDisp1Private		CtImDisp1Private;

struct _CtImDisp1{
	ImDisp1Parent parent;
};

KConstType 		ct_im_disp1_get_type(void);
CtImDisp1 *		ct_im_disp1_new();

#endif /* __CT_IM_DISP1_H__ */
