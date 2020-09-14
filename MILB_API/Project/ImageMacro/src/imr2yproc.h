/*
 * imr2yproc.h
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

#ifndef __IM_R2Y_PROC_H__
#define __IM_R2Y_PROC_H__

#include <klib.h>
#include "imr2yutils.h"

#define IM_TYPE_R2Y_PROC		(im_r2y_proc_get_type())
#define IM_R2Y_PROC(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yProc))
#define IM_IS_R2Y_PROC(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_PROC))


#define	D_IM_R2Y_SYSTEM_ERROR					(D_IM_R2Y | D_DDIM_SYSTEM_ERROR)		/**< System call error		*/
#define	D_IM_R2Y_TIMEOUT						(D_IM_R2Y | D_DDIM_TIMEOUT)				/**< timeout				*/

// True/False (kuint16)
#define D_IM_R2Y_TRUE					((kuint16)1)
#define D_IM_R2Y_FALSE					((kuint16)0)

typedef struct 				_ImR2yProc ImR2yProc;
typedef struct 				_ImR2yProcPrivate ImR2yProcPrivate;

struct _ImR2yProc {
	KObject parent;
};

KConstType 		    	im_r2y_proc_get_type(void);
ImR2yProc*		        im_r2y_proc_new(void);

/**
Restart R2Y process when yywContinueStartEnable equal ImR2yCtrl_ENABLE_OFF.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_proc_constart(ImR2yProc *self,  kuint16 pipeNo );

/**
start R2Y process.
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_SYSTEM_ERROR	: systemcall error.
@retval			ImR2yUtils_MACRO_BUSY		: Macro busy error.
@remarks		This API uses DDIM_User_Clr_Flg().
*/
INT32 im_r2y_proc_start(ImR2yProc *self,  kuint16 pipeNo );

/**
Stop R2Y
@param[in]		pipeNo					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_SYSTEM_ERROR	: systemcall error.
*/
INT32 im_r2y_proc_stop(ImR2yProc *self,  kuint16 pipeNo );

/**
wait end of R2Y macro.
@param[in]		waiptn					: waiting end cause. (bit field)
										<ul><li>@ref ImR2yCtrl_INT_STATE_YYR_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYWALL_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYW0_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYW0A_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYW1_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYW2_END1
											<li>@ref ImR2yCtrl_INT_STATE_LINE0_END1
											<li>@ref ImR2yCtrl_INT_STATE_LINE1_END1
											<li>@ref ImR2yCtrl_INT_STATE_LINE2_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYR_ERR1
											<li>@ref ImR2yCtrl_INT_STATE_YYW_ERR1
											<li>@ref ImR2yCtrl_INT_STATE_AXR_ERR1
											<li>@ref ImR2yCtrl_INT_STATE_AXW_ERR1
											<li>@ref ImR2yCtrl_INT_STATE_YCFERR_ERR1
											<li>@ref ImR2yCtrl_INT_STATE_YYR_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYWALL_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYW0_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYW0A_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYW1_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYW2_END2
											<li>@ref ImR2yCtrl_INT_STATE_LINE0_END2
											<li>@ref ImR2yCtrl_INT_STATE_LINE1_END2
											<li>@ref ImR2yCtrl_INT_STATE_LINE2_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYR_ERR2
											<li>@ref ImR2yCtrl_INT_STATE_YYW_ERR2
											<li>@ref ImR2yCtrl_INT_STATE_AXR_ERR2
											<li>@ref ImR2yCtrl_INT_STATE_AXW_ERR2
											<li>@ref ImR2yCtrl_INT_STATE_YCFERR_ERR2</ul>
@param[in]		tmout					: timeout.
@param[out]		p_flgptn				: end cause. (bit field)
										<ul><li>@ref ImR2yCtrl_INT_STATE_YYR_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYWALL_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYW0_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYW0A_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYW1_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYW2_END1
											<li>@ref ImR2yCtrl_INT_STATE_LINE0_END1
											<li>@ref ImR2yCtrl_INT_STATE_LINE1_END1
											<li>@ref ImR2yCtrl_INT_STATE_LINE2_END1
											<li>@ref ImR2yCtrl_INT_STATE_YYR_ERR1
											<li>@ref ImR2yCtrl_INT_STATE_YYW_ERR1
											<li>@ref ImR2yCtrl_INT_STATE_AXR_ERR1
											<li>@ref ImR2yCtrl_INT_STATE_AXW_ERR1
											<li>@ref ImR2yCtrl_INT_STATE_YCFERR_ERR1
											<li>@ref ImR2yCtrl_INT_STATE_YYR_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYWALL_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYW0_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYW0A_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYW1_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYW2_END2
											<li>@ref ImR2yCtrl_INT_STATE_LINE0_END2
											<li>@ref ImR2yCtrl_INT_STATE_LINE1_END2
											<li>@ref ImR2yCtrl_INT_STATE_LINE2_END2
											<li>@ref ImR2yCtrl_INT_STATE_YYR_ERR2
											<li>@ref ImR2yCtrl_INT_STATE_YYW_ERR2
											<li>@ref ImR2yCtrl_INT_STATE_AXR_ERR2
											<li>@ref ImR2yCtrl_INT_STATE_AXW_ERR2
											<li>@ref ImR2yCtrl_INT_STATE_YCFERR_ERR2</ul>
@retval			D_DDIM_OK				: R2Y normal end. and set end cause to p_flgptn.
@retval			ImR2yUtils_PARAM_ERROR	: parameter error.
@retval			D_IM_R2Y_SYSTEM_ERROR	: system call error.
@retval			D_IM_R2Y_TIMEOUT		: wait timeout.
@remarks		This API uses DDIM_User_Clr_Flg().
@remarks		This API uses DDIM_User_Twai_Flg().
*/
INT32 im_r2y_proc_waitend(ImR2yProc *self,  DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout );

/**
Interrupt handler.
@param[in]		pipeNo	: Image pipe no(pipe1/pipe2).
@remarks		This API uses DDIM_User_Set_Flg().
*/
void im_r2y_proc_int_handler(ImR2yProc *self,  kuint16 pipeNo );

#endif /* __IM_R2Y_PROC_H__ */
