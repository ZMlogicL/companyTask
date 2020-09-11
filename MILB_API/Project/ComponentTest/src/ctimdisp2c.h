/*
 *ctimdisp2c.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2C_H__
#define __CT_IM_DISP2C_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2C	(ct_im_disp2c_get_type())
#define CT_IM_DISP2C(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2c))
#define CT_IS_IM_DISP2C(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2C)

typedef struct _CtImDisp2c CtImDisp2c;
typedef struct _CtImDisp2cPrivate		CtImDisp2cPrivate;

struct _CtImDisp2c{
	ImDisp2Parent parent;
	CtImDisp2cPrivate *privCtImDisp2c;
};

KConstType 			ct_im_disp2c_get_type(void);
CtImDisp2c *		ct_im_disp2c_new(void);

#endif /* __CT_IM_DISP2C_H__ */
