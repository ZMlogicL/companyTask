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

#ifndef __INTERRUPT_SEN_H__
#define __INTERRUPT_SEN_H__

#include <klib.h>
#include "ddim_typedef.h"
#include "im_pro.h"

#define INTERRUPT_TYPE_SEN		(interrupt_sen_get_type())
#define INTERRUPT_SEN(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, InterruptSen))
#define INTERRUPT_IS_SEN(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, INTERRUPT_TYPE_SEN))

typedef struct 				_InterruptSen InterruptSen;
typedef struct 				_InterruptSenPrivate InterruptSenPrivate;

struct _InterruptSen {
	KObject parent;
};

KConstType 		    interrupt_sen_get_type(void);
InterruptSen*		        interrupt_sen_new(void);

/**
SEN block VD Int handler setting.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_sen_set_vd_int_handler( InterruptSen*self,T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
SEN block VD Int handler.
*/
VOID interrupt_sen_vd_int_handler( VOID );              //函数名做为参数

/**
SEN block SG VD Int handler setting.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_sen_set_sg_vd_int_handler( InterruptSen*self,T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
SEN block Gyro Int handler setting.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_sen_set_gyro_int_handler( InterruptSen*self,T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
SLVS-EC Common Int handler setting.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_sen_slvs_set_common_int_handler( InterruptSen*self,T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
CallBackFunction which Call to the interruption timing of CMIPI is registered
@param[in]	ch : Channel No.
@param[in]	category : interrupt factor category.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_sen_cmipi_set_int_handler( InterruptSen*self,
		E_IM_PRO_CMIPI_CH ch, E_IM_PRO_CMIPI_INT_CATE category, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
SLVS-EC Int handler setting.
@param[in]	streamType : stream type of SLVS
@param[in]	intType : interrupt type of SLVS
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_sen_slvs_set_int_handler( InterruptSen*self,
		E_IM_PRO_SLVS_STREAM_TYPE streamType, E_IM_PRO_SLVS_INT_TYPE intType,T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
SEN block Sensor I/F 0 Int handler.
@remarks	This API uses DDIM_User_Set_Flg().
*/
VOID interrupt_sen_sensor_if_int_handler_0( VOID );        //函数名作参数了

/**
SEN block Sensor I/F 1 Int handler.
@remarks	This API uses DDIM_User_Set_Flg().
*/
VOID interrupt_sen_sensor_if_int_handler_1( VOID );        //函数名作参数了

/**
SEN block Sensor I/F 2 Int handler.
@remarks	This API uses DDIM_User_Set_Flg().
*/
VOID interrupt_sen_sensor_if_int_handler_2( VOID );        //函数名作参数了

/**
SEN block Sensor I/F 3 Int handler.
@remarks	This API uses DDIM_User_Set_Flg().
*/
VOID interrupt_sen_sensor_if_int_handler_3( VOID );        //函数名作参数了

/**
CallBackFunction which Call to the interruption timing of LVDS is registered
@param[in]	ch : Channel No.
@param[in]	outMode : select the callback index of Normal output mode or DOL1 or DOL2.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_sen_lvds_set_int_handler( InterruptSen*self,
		E_IM_PRO_LVDS_CH ch, E_IM_PRO_LVDS_OUTPUT_MODE outMode, T_IM_PRO_CALLBACK_CFG* callbackCfg );

/**
CallBackFunction which Call to the interruption timing of DMIPI is registered
@param[in]	ch : Channel No.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_sen_dmipi_set_int_handler( InterruptSen*self,E_IM_PRO_DMIPI_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg );

#endif /* __INTERRUPT_SEN_H__ */
