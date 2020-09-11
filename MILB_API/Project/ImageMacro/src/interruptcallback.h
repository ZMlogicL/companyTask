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

#ifndef __INTERRUPT_CALLBACK_H__
#define __INTERRUPT_CALLBACK_H__

#include <klib.h>
#include "ddim_typedef.h"
#include "im_pro.h"
#include "interruptdefine.h"

#define INTERRUPT_TYPE_CALLBACK		(interrupt_callback_get_type())
#define INTERRUPT_CALLBACK(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, InterruptCallback))
#define INTERRUPT_IS_CALLBACK(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, INTERRUPT_TYPE_CALLBACK))

typedef struct 				_InterruptCallback InterruptCallback;
typedef struct 				_InterruptCallbackPrivate InterruptCallbackPrivate;

struct _InterruptCallback {
	KObject parent;
};

KConstType 		    interrupt_callback_get_type(void);
InterruptCallback*		        interrupt_callback_new(void);

/**
new func   处理gim_pro_inttbl_moni_int和gIM_PRO_MONI_CallBack_Func并平衡代码。
*/
VOID interrupt_callback_monifunc( InterruptCallback*self,
		UINT32	loopcnt,TimproSencoreIntFactor* intFactor,ULONG	callbackResult,T_CALLBACK_ID	*cbId,UCHAR sencoreCh);

/**
STAT Macro Int handler.
*/
VOID interrupt_callback_stat_int_handler( VOID );          //函数名作参数

/**
CallBackFunction which Call to the interruption timing of AEAWB is registered
@param[in]	ch : channel
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_callback_aeawb_set_int_handler( InterruptCallback*self,E_IM_PRO_AEAWB_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
CallBackFunction which Call to the interruption timing of AF is registered
@param[in]	ch : channel
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_af_set_int_handler( InterruptCallback*self,E_IM_PRO_AF_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
CallBackFunction which Call to the interruption timing of HIST is registered
@param[in]	ch : channel
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_hist_set_int_handler( InterruptCallback*self, E_IM_PRO_HIST_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
PAS block VD Int handler setting.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_pastop_set_vd_int_handler( InterruptCallback*self, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
PAS Macro VD Int handler.
*/
VOID interrupt_callback_pastop_vd_int_handler( VOID );          //函数名作参数

/**
PAS block HD Int handler setting.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_pastop_set_hd_int_handler( InterruptCallback*self, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
PAS Macro HD Int handler.
*/
VOID interrupt_callback_pastop_hd_int_handler( VOID );          //函数名作参数

/**
CallBackFunction which Call to the interruption timing of SDC is registered
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel<br>
	 			 value range:[0 - 1]<br>
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NCH_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_sdc_set_int_handler( InterruptCallback*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
CallBackFunction which Call to the interruption timing of MONI is registered
@param[in]	unitNo : Unit number.
@param[in]	blockType	 : PRO block type
@param[in]	ch			: channel
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_callback_moni_set_int_handler( InterruptCallback*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_MONI_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
SRO Macro Pipe1 Int handler.
*/
VOID interrupt_callback_srotop_pipe1_int_handler( VOID );          //函数名作参数

/**
SRO Macro Pipe2 Int handler.
*/
VOID interrupt_callback_srotop_pipe2_int_handler( VOID );          //函数名作参数

#endif /* __INTERRUPT_CALLBACK_H__ */
