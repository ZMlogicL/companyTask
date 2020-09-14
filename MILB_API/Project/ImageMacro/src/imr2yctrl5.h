/*
 * imr2yctrl5.h
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
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

#ifndef __IM_R2Y_CTRL5_H__
#define __IM_R2Y_CTRL5_H__

#include <klib.h>

#define IM_TYPE_R2Y_CTRL5		(im_r2y_ctrl5_get_type())
#define IM_R2Y_CTRL5(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yCtrl5))
#define IM_IS_R2Y_CTRL5(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_CTRL5))

typedef struct 				_ImR2yCtrl5 ImR2yCtrl5;
typedef struct 				_ImR2yCtrl5Private ImR2yCtrl5Private;

struct _ImR2yCtrl5 {
	KObject parent;
};

KConstType 		    im_r2y_ctrl5_get_type(void);
ImR2yCtrl5*		        im_r2y_ctrl5_new(void);

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON

void im_r2y_ctrl5_set_rdma_val_multi_axis( kuint16 pipeNo, const CtrlMultiAxis* const r2y_ctrl_multi_axis );
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


#endif /* __IM_R2Y_CTRL5_H__ */
