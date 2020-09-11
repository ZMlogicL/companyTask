/*
 * imr2yctrlsup.h
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
*@author              :gonghaotian
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __IM_R2Y_CTRL_SUP_H__
#define __IM_R2Y_CTRL_SUP_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_CTRL_SUP		(im_r2y_ctrl_sup_get_type())
#define IM_R2Y_CTRL_SUP(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yCtrlSup))
#define IM_IS_R2Y_CTRL_SUP(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_CTRL_SUP))

typedef struct 				_ImR2yCtrlSup ImR2yCtrlSup;
typedef struct 				_ImR2yCtrlSupPrivate ImR2yCtrlSupPrivate;

struct _ImR2yCtrlSup {
	KObject parent;
};

KConstType 		    		im_r2y_ctrl_sup_get_type(void);
ImR2yCtrlSup*		        im_r2y_ctrl_sup_new(void);

void im_r2y_ctrl_sup_multi_axis(ImR2yCtrlSup *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_MULTI_AXIS* const r2y_ctrl_multi_axis );

#ifdef CO_DDIM_UTILITY_USE
#ifdef CO_R2Y_RDMA_ON
VOID im_r2y_ctrl_sup_set_rdma_val_multi_axis(ImR2yCtrlSup *self, T_IM_R2Y_CTRL_RDMA_MCYC_VAL* mcyc_ctrl, UCHAR pipe_no, const T_IM_R2Y_CTRL_MULTI_AXIS* const r2y_ctrl_multi_axis );

#endif /* __IM_R2Y_CTRL_SUP_H__ */
#endif	// CO_DDIM_UTILITY_USE

#endif /* __IM_R2Y_CTRL_SUP_H__ */
