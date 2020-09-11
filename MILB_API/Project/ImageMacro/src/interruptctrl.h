/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :王睿
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

#ifndef __INTERRUPT_CTRL_H__
#define __INTERRUPT_CTRL_H__

#include <klib.h>
#include "ddim_typedef.h"
#include "im_pro.h"

#define INTERRUPT_TYPE_CTRL		(interrupt_ctrl_get_type())
#define INTERRUPT_CTRL(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, InterruptCtrl))
#define INTERRUPT_IS_CTRL(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, INTERRUPT_TYPE_CTRL))

typedef struct 				_InterruptCtrl InterruptCtrl;
typedef struct 				_InterruptCtrlPrivate InterruptCtrlPrivate;

struct _InterruptCtrl {
	KObject parent;
};

KConstType 		    interrupt_ctrl_get_type(void);
InterruptCtrl*		        interrupt_ctrl_new(void);

/**
SEN block Int handler except VD, HD, and Sensor I/F interrupts.
*/
VOID interrupt_ctrl_sen_int_handler( VOID );                 //函数名作参数

/**
CallBackFunction which Call to the interruption timing of LDIV is registered
@param[in]	ch : Channel No.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_ctrl_ldiv_set_int_handler( InterruptCtrl*self,E_IM_PRO_LDIV_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
CallBackFunction which Call to the interruption timing of OB is registered
@param[in]	ch : Channel No.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_ctrl_obd_set_int_handler( InterruptCtrl*self,E_IM_PRO_OBD_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
CallBackFunction which Call to the interruption timing of OBT is registered
@param[in]	ch : Channel No.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_ctrl_obt_set_int_handler( InterruptCtrl*self,E_IM_PRO_OBT_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
SRO pipe VD Int handler setting.
@param[in]	unitNo : Unit number.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_ctrl_srotop_pipe_set_vd_int_handler( InterruptCtrl*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
SRO Macro Pipe1 VD Int handler.
*/
VOID interrupt_ctrl_srotop_pipe1_vd_int_handler( VOID );    //函数名作参数

/**
SRO Macro Pipe2 VD Int handler.
*/
VOID interrupt_ctrl_srotop_pipe2_vd_int_handler( VOID );    //函数名作参数

/**
SRO pipe HD Int handler setting.
@param[in]	unitNo : Unit number.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_ctrl_srotop_pipe_set_hd_int_handler( InterruptCtrl*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
SRO Macro Pipe1 HD Int handler.
*/
VOID interrupt_ctrl_srotop_pipe1_hd_int_handler( VOID );    //函数名作参数

/**
SRO Macro Pipe2 HD Int handler.
*/
VOID interrupt_ctrl_srotop_pipe2_hd_int_handler( VOID );    //函数名作参数

/**
B2B pipe VD Int handler setting.
@param[in]	unitNo : Unit number.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_ctrl_b2btop_pipe_set_vd_int_handler( InterruptCtrl*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
B2B Macro Pipe1 VD Int handler.
*/
VOID interrupt_ctrl_b2btop_pipe1_vd_int_handler( VOID );    //函数名作参数

/**
B2B Macro Pipe2 VD Int handler.
*/
VOID interrupt_ctrl_b2btop_pipe2_vd_int_handler( VOID );    //函数名作参数

/**
B2B pipe HD Int handler setting.
@param[in]	unitNo : Unit number.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_ctrl_b2btop_pipe_set_hd_int_handler( InterruptCtrl*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
B2B Macro Pipe1 HD Int handler.
*/
VOID interrupt_ctrl_b2btop_pipe1_hd_int_handler( VOID );    //函数名作参数

/**
B2B Macro Pipe2 HD Int handler.
*/
VOID interrupt_ctrl_b2btop_pipe2_hd_int_handler( VOID );    //函数名作参数

#endif /* __INTERRUPT_CTRL_H__ */
