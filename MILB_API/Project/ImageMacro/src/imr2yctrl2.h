/*
 * imr2yctrl2.h
 *
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

#ifndef __IM_R2Y_CTRL2_H__
#define __IM_R2Y_CTRL2_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_CTRL2		(im_r2y_ctrl2_get_type())
#define IM_R2Y_CTRL2(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yCtrl2))
#define IM_IS_R2Y_CTRL2(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_CTRL2))

typedef struct 				_ImR2yCtrl2 ImR2yCtrl2;
typedef struct 				_ImR2yCtrl2Private ImR2yCtrl2Private;

struct _ImR2yCtrl2 {
	KObject parent;
};

KConstType 		    im_r2y_ctrl2_get_type(void);
ImR2yCtrl2*		        im_r2y_ctrl2_new(void);

/**
WB Gain control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		rgb_color				: pointer of WB gain parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_wb_gain(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_RGB_COLOR* const rgb_color );

/**
WB Clip Level control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_rgb_color			: pointer of WB clip level parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_wb_clip_level(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_RGB_COLOR* const r2y_rgb_color );

/**
CC0 Matrix Control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_cc				: pointer of CC0 Matrix parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_cc0_matrix(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_CC0* const r2y_ctrl_cc );

/**
Set CC0 Matrix coefficient
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		cc0k					: pointer of CC0 Matrix coefficient.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_cc0_matrix_coefficient(ImR2yCtrl2 *self, UCHAR pipe_no, const SHORT* const cc0k );

/**
RGB Offset before TC control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_btc_offset		: pointer of BTC rgb offset control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_before_tone_offset(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_TCOF* const r2y_ctrl_btc_offset );

/**
Luminance Evaluation before TC control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_btc_tct		: pointer of BTC tct control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_before_tone_tct(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_TCT* const r2y_ctrl_btc_tct );

/**
Histogram before TC control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_btc_hist		: pointer of BTC histogram control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_before_tone_tchs(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_TCHS* const r2y_ctrl_btc_hist );

/**
Set Luminance evaluation table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		tct_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(ImR2yCtrl2 *self, UCHAR pipe_no, UCHAR tct_enable, UCHAR wait_enable );

/**
Set BTC histogram table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		hist_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(ImR2yCtrl2 *self, UCHAR pipe_no, UCHAR hist_enable, UCHAR wait_enable );

/**
Gamma Correction control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_gamma			: pointer of Gamma Correction control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_gamma(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_GAMMA* const r2y_ctrl_gamma );

/**
Set Gamma table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		acc_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_gamma_tbl_access_enable(ImR2yCtrl2 *self, UCHAR pipe_no, UCHAR acc_enable, UCHAR wait_enable );

/**
Set Gamma Yb table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		acc_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(ImR2yCtrl2 *self, UCHAR pipe_no, UCHAR acc_enable, UCHAR wait_enable );

/** Is Gamma Control active
@param[in]		pipe_no	: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		active_status			: Gamma control status(active/inactive).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
 */
INT32 im_r2y_ctrl2_is_act_gamma(ImR2yCtrl2 *self, UCHAR pipe_no, UCHAR* const active_status );

/**
CC1 Matrix Control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_cc				: pointer of CC1 Matrix parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_cc1_matrix(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_CC1* const r2y_ctrl_cc );

/**
Set CC1 Matrix coefficient
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		cc1k					: pointer of CC1 Matrix coefficient.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_set_cc1_matrix_coefficient(ImR2yCtrl2 *self, UCHAR pipe_no, const SHORT* const cc1k );

/**
YC Convert control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_ycc			: pointer of YC Convert control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_yc_convert(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_YCC* const r2y_ctrl_ycc );

/**
Y(Luminance) Noise Reduction control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_ynr			: pointer of Y Noise Reduction control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_ctrl2_ynr(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_YNR* const r2y_ctrl_ynr );

#endif /* __IM_R2Y_CTRL2_H__ */
