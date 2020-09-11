/*
 * imr2yedge.h
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

#ifndef __IM_R2Y_EDGE_H__
#define __IM_R2Y_EDGE_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_EDGE		(im_r2y_edge_get_type())
#define IM_R2Y_EDGE(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yEdge))
#define IM_IS_R2Y_EDGE(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_EDGE))

typedef struct 				_ImR2yEdge ImR2yEdge;
typedef struct 				_ImR2yEdgePrivate ImR2yEdgePrivate;

struct _ImR2yEdge {
	KObject parent;
};

KConstType 		    im_r2y_edge_get_type(void);
ImR2yEdge*		        im_r2y_edge_new(void);

/**
High/Medium frequency edge enhancement common control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_edge_cmn		: pointer of Edge noise reduction control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_noise_reduction(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_CMN* const r2y_ctrl_edge_cmn );

/**
High frequency Edge enhancement control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_hedge			: pointer of Edge enhancement control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_high_edge(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_HEDGE* const r2y_ctrl_hedge );

/**
Set High Edge scale table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		scl_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_set_high_edge_scl_tbl_access_enable(ImR2yEdge *self, UCHAR pipe_no, UCHAR scl_enable, UCHAR wait_enable );

/**
Set High Edge step table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		step_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_set_high_edge_step_tbl_access_enable(ImR2yEdge *self, UCHAR pipe_no, UCHAR step_enable, UCHAR wait_enable );

/**
Medium frequency Edge enhancement control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_medge			: pointer of Edge enhancement control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_medium_edge(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_MEDGE* const r2y_ctrl_medge );

/**
Set Medium Edge scale table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		scl_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_set_medium_edge_scl_tbl_access_enable(ImR2yEdge *self, UCHAR pipe_no, UCHAR scl_enable, UCHAR wait_enable );

/**
Set Medium Edge step table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		step_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_set_medium_edge_step_tbl_access_enable(ImR2yEdge *self, UCHAR pipe_no, UCHAR step_enable, UCHAR wait_enable );

/**
Low frequency Edge enhancement control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_ledge			: pointer of Edge enhancement control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_ctrl_low_edge(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_LEDGE* const r2y_ctrl_ledge );

/**
Set Low Edge scale table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		scl_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_set_low_edge_scl_tbl_access_enable(ImR2yEdge *self, UCHAR pipe_no, UCHAR scl_enable, UCHAR wait_enable );

/**
Set Low Edge step table access enable
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		step_enable				: 0 : access disable / 1 : access enable
@param[in]		wait_enable				: D_IM_R2Y_WAIT_OFF : Turn off wait. / D_IM_R2Y_WAIT_ON : Wait 1usec if needed.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_set_low_edge_step_tbl_access_enable(ImR2yEdge *self, UCHAR pipe_no, UCHAR step_enable, UCHAR wait_enable );

/** Is Post filter active
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[out]		active_status			: Post filter control status(active/inactive).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
 */
INT32 im_r2y_edge_is_act_post_filter(ImR2yEdge *self, UCHAR pipe_no, UCHAR* const active_status );

/**
Edge dot noise control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_edge_dot		: pointer of Edge dot noise control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_ctrl_dot_noise(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_DOT_NOISE* const r2y_ctrl_edge_dot );

/**
Edge enhancement blend control
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@param[in]		r2y_ctrl_edge_blend		: pointer of Edge enhancement blend control parameters.
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_edge_ctrl_blend(ImR2yEdge *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_EDGE_BLEND* const r2y_ctrl_edge_blend );

#endif /* __IM_R2Y_EDGE_H__ */
