/*
 * imr2yclk.h
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
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

#ifndef __IM_R2Y_CLK_H__
#define __IM_R2Y_CLK_H__

#include <klib.h>
#include "driver_common.h"

#define IM_TYPE_R2Y_CLK		(im_r2y_clk_get_type())
#define IM_R2Y_CLK(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yClk))
#define IM_IS_R2Y_CLK(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_CLK))

#define im_r2y_check_target_pipe_no_1(a)		(((a) + 1) & (ImR2yCtrl_PIPE1 + 1))
#define im_r2y_check_target_pipe_no_2(a)		(((a) + 1) & (ImR2yCtrl_PIPE2 + 1))



typedef struct 				_ImR2yClk ImR2yClk;
typedef struct 				_ImR2yClkPrivate ImR2yClkPrivate;

struct _ImR2yClk {
	KObject parent;
};

KConstType 		    im_r2y_clk_get_type(void);
ImR2yClk*		        im_r2y_clk_new(void);


void im_r2y_clk_manager_init(ImR2yClk *self, kuint16 pipeNo, kuint16 size_coef);

void im_r2y_clk_ddim_print(ImR2yClk *self);

INT32 im_r2y_clk_on_pclk(ImR2yClk *self, kuint16 pipeNo );

/**
Disable PCLK for R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 im_r2y_clk_off_pclk(ImR2yClk *self, kuint16 pipeNo );

/**
Force disable PCLK for R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 im_r2y_clk_force_off_pclk(ImR2yClk *self, kuint16 pipeNo );

/**
Enable HCLK for R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 im_r2y_clk_on_hclk(ImR2yClk *self, kuint16 pipeNo );

/**
Disable HCLK for R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 im_r2y_clk_off_hclk(ImR2yClk *self, kuint16 pipeNo );

/**
Force disable HCLK for R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 im_r2y_clk_force_off_hclk(ImR2yClk *self, kuint16 pipeNo );

/**
Enable ICLK for R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 im_r2y_clk_on_iclk(ImR2yClk *self, kuint16 pipeNo );

/**
Disable ICLK for R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 im_r2y_clk_off_iclk(ImR2yClk *self, kuint16 pipeNo );

/**
Force disable ICLK for R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 im_r2y_clk_force_off_iclk(ImR2yClk *self, kuint16 pipeNo );

/**
Enable R2YCLK for R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 im_r2y_clk_on_clk(ImR2yClk *self, kuint16 pipeNo );

/**
Disable R2YCLK for R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 im_r2y_clk_off_clk(ImR2yClk *self, kuint16 pipeNo );

/**
Force disable R2YCLK for R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 im_r2y_clk_force_off_clk(ImR2yClk *self, kuint16 pipeNo );

#endif /* __IM_R2Y_CLK_H__ */
