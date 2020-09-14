/*
 * imr2yctrl4.h
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

#ifndef __IM_R2Y_CTRL4_H__
#define __IM_R2Y_CTRL4_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_CTRL4		(im_r2y_ctrl4_get_type())
#define IM_R2Y_CTRL4(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yCtrl4))
#define IM_IS_R2Y_CTRL4(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_CTRL4))

typedef struct 				_ImR2yCtrl4 ImR2yCtrl4;
typedef struct 				_ImR2yCtrl4Private ImR2yCtrl4Private;

struct _ImR2yCtrl4 {
	KObject parent;
};

KConstType 		    	im_r2y_ctrl4_get_type(void);
ImR2yCtrl4*		        im_r2y_ctrl4_new(void);

/**
Multi Axis Control
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_multi_axis		: pointer of Multi Axis control parameters.
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl4_multi_axis(ImR2yCtrl4 *self, kuint16 pipeNo, const CtrlMultiAxis* const r2y_ctrl_multi_axis );

#endif /* __IM_R2Y_CTRL4_H__ */
