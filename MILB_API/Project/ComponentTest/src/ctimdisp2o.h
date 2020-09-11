/*
 *ctimdisp2o.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-09
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2O_H__
#define __CT_IM_DISP2O_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2O	(ct_im_disp2o_get_type())
#define CT_IM_DISP2O(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2o))
#define CT_IS_IM_DISP2O(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2O)

typedef struct _CtImDisp2o CtImDisp2o;
typedef struct _CtImDisp2oPrivate		CtImDisp2oPrivate;

struct _CtImDisp2o{
	ImDisp2Parent parent;
	kpointer privCtImDisp2o;
};

KConstType 			ct_im_disp2o_get_type(void);
CtImDisp2o *		ct_im_disp2o_new(void);

#endif /* __CT_IM_DISP2O_H__ */
