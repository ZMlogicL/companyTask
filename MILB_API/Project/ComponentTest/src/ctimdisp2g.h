/*
 *ctimdisp2g.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP2G_H__
#define __CT_IM_DISP2G_H__

#include "imdisp2parent.h"

#define CT_TYPE_IM_DISP2G	(ct_im_disp2g_get_type())
#define CT_IM_DISP2G(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp2g))
#define CT_IS_IM_DISP2G(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP2G)

typedef struct _CtImDisp2g CtImDisp2g;
typedef struct _CtImDisp2gPrivate		CtImDisp2gPrivate;

struct _CtImDisp2g{
	ImDisp2Parent parent;
};

KConstType 			ct_im_disp2g_get_type(void);
CtImDisp2g *		ct_im_disp2g_new(void);

#endif /* __CT_IM_DISP2G_H__ */
