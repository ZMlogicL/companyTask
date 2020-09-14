/*
*@Copyright (C) 2070-2020 上海网用软件有限公司

*@date                :2020-08-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*7、
*2、
*@version
*7.0.0 2020年06月开始开发
*/

#ifndef __IM_LTM_COMMON_H__
#define __IM_LTM_COMMON_H__

#include <klib.h>

#define IM_TYPE_LTM_COMMON	(im_ltm_common_get_type())
#define IM_LTM_COMMON(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImLtmCommon))
#define IM_IS_LTM_COMMON(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, ImLtmCommon))


#define	D_IM_LTM_PIPE1						(0)						/**< Pipe1.							*/
#define	D_IM_LTM_PIPE2						(1)						/**< Pipe2.							*/
#define	D_IM_LTM_PIPE12						(2)						/**< Pipe1&2.						*/
#define	D_IM_LTM_PIPE_MAX
#define	D_IM_LTM_PARAM_ERROR				(D_IM_LTM | D_DDIM_INPUT_PARAM_ERROR)	/**< parameter error		*/

typedef struct _ImLtmCommon ImLtmCommon;
struct _ImLtmCommon {
	KObject parent;
};

KConstType 		    				im_ltm_common_get_type(void);
ImLtmCommon*		          	im_ltm_common_new(void);

/**
Enable PCLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 										im_ltm_common_on_pclk( UCHAR pipe_no );

/**
Disable PCLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 										im_ltm_common_off_pclk( UCHAR pipe_no );

/**
Force disable PCLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32 										im_ltm_common_force_off_pclk( UCHAR pipe_no );

/**
Enable HCLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
INT32	 									im_ltm_common_on_hclk( UCHAR pipe_no );

/**
Disable HCLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
 INT32 										im_ltm_common_off_hclk( UCHAR pipe_no );

/**
Force disable HCLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
 INT32 										im_ltm_common_force_off_hclk( UCHAR pipe_no );

/**
Enable ACLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
 INT32 										im_ltm_common_on_aclk( UCHAR pipe_no );

/**
Disable ACLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
 INT32						 				im_ltm_common_off_aclk( UCHAR pipe_no );

/**
Force disable ACLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
 INT32 										im_ltm_common_force_off_aclk( UCHAR pipe_no );

/**
Enable LTMCLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
 INT32 										im_ltm_common_on_clk( UCHAR pipe_no );

/**
Disable LTMCLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
 INT32 										im_ltm_common_off_clk( UCHAR pipe_no );

/**
Force disable LTMCLK for LTM
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
 INT32	 									im_ltm_common_force_off_clk( UCHAR pipe_no );

/**
Enable LTMRBKCLK for LTMRBK/LTMMAP
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
 INT32 										im_ltm_common_on_rbkclk( UCHAR pipe_no );

/**
Disable LTMRBKCLK for LTMRBK/LTMMAP
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
 INT32 										im_ltm_common_off_rbkclk( UCHAR pipe_no );

/**
Force disable LTMRBKCLK for LTMRBK/LTMMAP
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@remarks		For debugging use only (for register dump on debugger)
*/
 INT32 										im_ltm_common_force_off_rbkclk( UCHAR pipe_no );

/**
LTM All block(RBK/MAP/LTM) Initialize
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
*/
 INT32 										im_ltm_common_init_all_block( UCHAR pipe_no );

/**
LTM All block(RBK/MAP/LTM) SW reset
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
@retval			D_IM_LTM_MACRO_BUSY		: Macro busy error.
*/
 INT32 										im_ltm_common_sw_reset_all_block( UCHAR pipe_no );

/**
Stop LTM(All block)
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2/pipe12).
@retval			D_DDIM_OK				: success.
@retval			D_IM_LTM_PARAM_ERROR	: parameter error.
*/
 INT32 										im_ltm_common_stop_all_block( UCHAR pipe_no );

/**
Interrupt handler.
@param[in]		pipe_no					: Image pipe no(pipe1/pipe2).
*/
 VOID 										im_ltm_common_int_handler( UCHAR pipe_no );

VOID 											im_ltm_common_print_clockstatus( VOID );

#endif /* __IM_LTM_COMMON_H__ */
