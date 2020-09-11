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


typedef struct 				_ImR2yProc ImR2yProc;
typedef struct 				_ImR2yProcPrivate ImR2yProcPrivate;

struct _ImR2yProc {
	KObject parent;
};

KConstType 		    	im_r2y_proc_get_type(void);
ImR2yProc*		        im_r2y_proc_new(void);

/**
Restart R2Y process when yyw_continue_start_enable equal D_IM_R2Y_ENABLE_OFF.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
*/
INT32 im_r2y_proc_constart(ImR2yProc *self,  UCHAR pipe_no );

/**
start R2Y process.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_SYSTEM_ERROR	: systemcall error.
@retval			D_IM_R2Y_MACRO_BUSY		: Macro busy error.
@remarks		This API uses DDIM_User_Clr_Flg().
*/
INT32 im_r2y_proc_start(ImR2yProc *self,  UCHAR pipe_no );

/**
Stop R2Y
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_R2Y_SYSTEM_ERROR	: systemcall error.
*/
INT32 im_r2y_proc_stop(ImR2yProc *self,  UCHAR pipe_no );

/**
wait end of R2Y macro.
@param[in]		waiptn					: waiting end cause. (bit field)
										<ul><li>@ref D_IM_R2Y1_INT_STATE_YYR_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYWALL_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYW0_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYW0A_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYW1_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYW2_END
											<li>@ref D_IM_R2Y1_INT_STATE_LINE0_END
											<li>@ref D_IM_R2Y1_INT_STATE_LINE1_END
											<li>@ref D_IM_R2Y1_INT_STATE_LINE2_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYR_ERR
											<li>@ref D_IM_R2Y1_INT_STATE_YYW_ERR
											<li>@ref D_IM_R2Y1_INT_STATE_AXR_ERR
											<li>@ref D_IM_R2Y1_INT_STATE_AXW_ERR
											<li>@ref D_IM_R2Y1_INT_STATE_YCFERR_ERR
											<li>@ref D_IM_R2Y2_INT_STATE_YYR_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYWALL_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYW0_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYW0A_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYW1_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYW2_END
											<li>@ref D_IM_R2Y2_INT_STATE_LINE0_END
											<li>@ref D_IM_R2Y2_INT_STATE_LINE1_END
											<li>@ref D_IM_R2Y2_INT_STATE_LINE2_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYR_ERR
											<li>@ref D_IM_R2Y2_INT_STATE_YYW_ERR
											<li>@ref D_IM_R2Y2_INT_STATE_AXR_ERR
											<li>@ref D_IM_R2Y2_INT_STATE_AXW_ERR
											<li>@ref D_IM_R2Y2_INT_STATE_YCFERR_ERR</ul>
@param[in]		tmout					: timeout.
@param[out]		p_flgptn				: end cause. (bit field)
										<ul><li>@ref D_IM_R2Y1_INT_STATE_YYR_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYWALL_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYW0_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYW0A_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYW1_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYW2_END
											<li>@ref D_IM_R2Y1_INT_STATE_LINE0_END
											<li>@ref D_IM_R2Y1_INT_STATE_LINE1_END
											<li>@ref D_IM_R2Y1_INT_STATE_LINE2_END
											<li>@ref D_IM_R2Y1_INT_STATE_YYR_ERR
											<li>@ref D_IM_R2Y1_INT_STATE_YYW_ERR
											<li>@ref D_IM_R2Y1_INT_STATE_AXR_ERR
											<li>@ref D_IM_R2Y1_INT_STATE_AXW_ERR
											<li>@ref D_IM_R2Y1_INT_STATE_YCFERR_ERR
											<li>@ref D_IM_R2Y2_INT_STATE_YYR_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYWALL_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYW0_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYW0A_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYW1_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYW2_END
											<li>@ref D_IM_R2Y2_INT_STATE_LINE0_END
											<li>@ref D_IM_R2Y2_INT_STATE_LINE1_END
											<li>@ref D_IM_R2Y2_INT_STATE_LINE2_END
											<li>@ref D_IM_R2Y2_INT_STATE_YYR_ERR
											<li>@ref D_IM_R2Y2_INT_STATE_YYW_ERR
											<li>@ref D_IM_R2Y2_INT_STATE_AXR_ERR
											<li>@ref D_IM_R2Y2_INT_STATE_AXW_ERR
											<li>@ref D_IM_R2Y2_INT_STATE_YCFERR_ERR</ul>
@retval			D_DDIM_OK				: R2Y normal end. and set end cause to p_flgptn.
@retval			D_IM_R2Y_PARAM_ERROR	: parameter error.
@retval			D_IM_R2Y_SYSTEM_ERROR	: system call error.
@retval			D_IM_R2Y_TIMEOUT		: wait timeout.
@remarks		This API uses DDIM_User_Clr_Flg().
@remarks		This API uses DDIM_User_Twai_Flg().
*/
INT32 im_r2y_proc_waitend(ImR2yProc *self,  DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout );

/**
Interrupt handler.
@param[in]		pipe_no	: Image pipe no(pipe1/pipe2).
@remarks		This API uses DDIM_User_Set_Flg().
*/
VOID im_r2y_proc_int_handler(ImR2yProc *self,  UCHAR pipe_no );

#endif /* __IM_R2Y_PROC_H__ */
