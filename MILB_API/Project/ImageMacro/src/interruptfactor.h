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

#ifndef __INTERRUPT_FACTOR_H__
#define __INTERRUPT_FACTOR_H__

#include <klib.h>
#include "ddim_typedef.h"
#include "im_pro.h"
#include "interruptdefine.h"

#define INTERRUPT_TYPE_FACTOR		(interrupt_factor_get_type())
#define INTERRUPT_FACTOR(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, InterruptFactor))
#define INTERRUPT_IS_FACTOR(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, INTERRUPT_TYPE_FACTOR))

typedef struct 				_InterruptFactor InterruptFactor;
typedef struct 				_InterruptFactorPrivate InterruptFactorPrivate;

struct _InterruptFactor {
	KObject parent;
};

KConstType 		    interrupt_factor_get_type(void);
InterruptFactor*		        interrupt_factor_new(void);

VOID interrupt_factor_pwch_clear_int_factor( InterruptFactor*self,TimproPwchIntInfo* pwchInfo, ULONG* intFactor, UCHAR chCnt ); //私变公

VOID interrupt_factor_pwch_callback_int_factor( InterruptFactor*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_PWCH ch, ULONG* intFactor );//私变公

VOID interrupt_factor_prch_callback_int_factor( InterruptFactor*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_PRCH ch, ULONG* intFactor );//私变公

VOID interrupt_factor_prch_clear_int_factor( InterruptFactor*self,TimproPichIntInfo* prchInfo, ULONG* intFactor, UCHAR chCnt );//私变公

/**
CallBackFunction which Call to the interruption timing of PRch is registered
@param[in]	unitNo : Unit number.
@param[in]	blockType	 : PRO block type
@param[in]	ch : PRch channel
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_prch_set_int_handler( InterruptFactor*self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType,
		E_IM_PRO_PRCH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
CallBackFunction which Call to the interruption timing of PWch is registered
@param[in]	unitNo : Unit number.
@param[in]	blockType	 : PRO block type
@param[in]	ch			: PWch number
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_pwch_set_int_handler( InterruptFactor*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_PWCH ch,T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
B2B Macro Pipe1 Int handler.
*/
VOID interrupt_factor_b2btop_pipe1_int_handler( VOID );      //函数名作参数

/**
B2B Macro Pipe2 Int handler.
*/
VOID interrupt_factor_b2btop_pipe2_int_handler( VOID );      //函数名作参数

/**
PAS Macro Int handler.
*/
VOID interrupt_factor_pastop_int_handler( VOID );      //函数名作参数

/**
SENTOP macro interrupt delay setting
@param[in]	blockNum : SENCORE block number(0:SENCORE0, 1:SENCORE1, 2:SENCORE2, 3:SENCORE3)
@param[in]	ch : channel(0:HD/VD0, 1:HD/VD1, 2:HD/VD2, 3:HD/VD3)
@param[in]	delayCtrl : delay setting
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_sentop_set_vhd_delay( InterruptFactor*self,UCHAR blockNum, UCHAR ch, T_IM_PRO_INT_VHD_DELAY_CTRL* delayCtrl );

/**
SENTOP macro GYRO interrupt delay setting
@param[in]	blockNum : SENCORE block number(0:SENCORE0, 1:SENCORE1, 2:SENCORE2, 3:SENCORE3)
@param[in]	delayCtrl : delay setting
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_sentop_set_gyro_int_delay( InterruptFactor*self,UCHAR blockNum, T_IM_PRO_INT_VHD_DELAY_CTRL* delayCtrl );

/**
SROTOP macro interrupt delay setting
@param[in]	unitNo : Unit number.
@param[in]	ch : channel(0:HD/VD0, 1:HD/VD1)
@param[in]	delayCtrl : delay setting
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_srotop_set_vhd_delay( InterruptFactor*self,E_IM_PRO_UNIT_NUM unitNo, UCHAR ch, T_IM_PRO_INT_VHD_DELAY_CTRL* delayCtrl );

/** @addtogroup im_pro_handler_stat STAT Interrupt
@{
*/
/**
STATTOP Interrupt setting
@param[in]	intCtrl : STATTOP interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_factor_stattop_interrupt_ctrl( InterruptFactor*self,T_IM_PRO_INT_STATTOP_CTRL* intCtrl );

/**
B2BTOP macro interrupt delay setting
@param[in]	unitNo : Unit number.
@param[in]	ch : channel(0:HD/VD0, 1:HD/VD1)
@param[in]	delayCtrl : delay setting
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_b2btop_set_vhd_delay( InterruptFactor*self,
		E_IM_PRO_UNIT_NUM unitNo, UCHAR ch, T_IM_PRO_INT_VHD_DELAY_CTRL* delayCtrl );

/**
PASTOP macro interrupt delay setting
@param[in]	ch : channel(0:HD/VD0, 1:HD/VD1)
@param[in]	delayCtrl : delay setting
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_pastop_set_vhd_delay( InterruptFactor*self,UCHAR ch, T_IM_PRO_INT_VHD_DELAY_CTRL* delayCtrl );

/**
SEN block HD Int handler.
*/
VOID interrupt_factor_hd_int_handler( VOID );                  //函数名做参数

/**
SEN block HD Int handler setting.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_set_hd_int_handler( InterruptFactor*self,T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
SEN block SG HD Int handler setting.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_factor_set_sg_hd_int_handler( InterruptFactor*self,T_IM_PRO_CALLBACK_CFG* callbackCfg );

#endif /* __INTERRUPT_FACTOR_H__ */
