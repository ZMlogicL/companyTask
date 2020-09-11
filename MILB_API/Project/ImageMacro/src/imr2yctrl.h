/*
 * imr2yctrl.h
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
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

#ifndef __IM_R2Y_CTRL_H__
#define __IM_R2Y_CTRL_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_CTRL			(im_r2y_ctrl_get_type())
#define IM_R2Y_CTRL(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yCtrl))
#define IM_IS_R2Y_CTRL(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_CTRL))

typedef struct 				_ImR2yCtrl ImR2yCtrl;
typedef struct 				_ImR2yCtrlPrivate ImR2yCtrlPrivate;

struct _ImR2yCtrl {
	KObject parent;
};

KConstType 		   	 	im_r2y_ctrl_get_type(void);
ImR2yCtrl*		        im_r2y_ctrl_new(void);

/**
Post-resize edge enhancement0 control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_post_resize	: pointer of Post resize edge enhancement control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl_post_resize_edge0(ImR2yCtrl *self, UCHAR pipe_no, const T_IM_R2Y_POST_RESIZE0_PARAM* const r2y_ctrl_post_resize );

/**
Post-resize edge enhancement1 control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_post_resize	: pointer of Post resize edge enhancement control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl_post_resize_edge1(ImR2yCtrl *self, UCHAR pipe_no, const T_IM_R2Y_POST_RESIZE1_PARAM* const r2y_ctrl_post_resize );

/**
Offset Control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		ofs						: pointer of offset parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_set_offset(ImR2yCtrl *self, UCHAR pipe_no, const T_IM_R2Y_OFS* const ofs );

/**
Tone Control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_tone			: pointer of Tone control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl_tone(ImR2yCtrl *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_TONE* const r2y_ctrl_tone );

/**
Set Tone control table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		tc_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_set_tone_control_tbl_access_enable(ImR2yCtrl *self, UCHAR pipe_no, UCHAR tc_enable, UCHAR wait_enable );

/**
Is Tone Control active
@param[in]		pipe_no	: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		active_status			: Tone control status(active/inactive).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_is_act_tone(ImR2yCtrl *self, UCHAR pipe_no, UCHAR* const active_status );

#endif /* __IM_R2Y_CTRL_H__ */
