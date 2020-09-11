/*
 *ctimdisp2n.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2N_H__
#define __CT_IM_DISP2N_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2N	(ct_im_disp2n_get_type())
#define CT_IM_DISP2N(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2n))
#define CT_IS_IM_DISP2N(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2N)

typedef struct _CtImDisp2n CtImDisp2n;
typedef struct _CtImDisp2nPrivate		CtImDisp2nPrivate;

struct _CtImDisp2n{
	ImDisp2Parent parent;
	CtImDisp2nPrivate *ctImDisp2nPrivate;
};

KConstType 			ct_im_disp2n_get_type(void);
CtImDisp2n *		ct_im_disp2n_new(void);

#endif /* __CT_IM_DISP2N_H__ */
