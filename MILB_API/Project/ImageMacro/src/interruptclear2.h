/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
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

#ifndef __INTERRUPT_CLEAR2_H__
#define __INTERRUPT_CLEAR2_H__

#include <klib.h>
#include "im_pro.h"

#define INTERRUPT_TYPE_CLEAR2		(interrupt_clear2_get_type())
#define INTERRUPT_CLEAR2(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, InterruptClear2))
#define INTERRUPT_IS_CLEAR2(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, INTERRUPT_TYPE_CLEAR2))

typedef struct 				_InterruptClear2 InterruptClear2;
typedef struct 				_InterruptClear2Private InterruptClear2Private;

struct _InterruptClear2 {
	KObject parent;
};

KConstType 		    interrupt_clear2_get_type(void);
InterruptClear2*		        interrupt_clear2_new(void);

/**
CMIPI Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	cmipiIntCtrl : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@code
	//sample code
	T_IM_PRO_INT_CMIPI_CTRL cmipiIntCtrl;

	cmipiIntCtrl.cmipi_int1_enable.interrupt_bit	= (D_IM_PRO_MPIINTF_FEO0|D_IM_PRO_MPIINTF_FEI0);
	cmipiIntCtrl.cmipi_int1_enable.permission_flg	= 1;
	cmipiIntCtrl.cmipi_int2_enable.interrupt_bit	= (D_IM_PRO_MPICINTE2_CICHSE0|D_IM_PRO_MPICINTF2_CICHSF1|D_IM_PRO_MPICINTF2_CICHSF2|D_IM_PRO_MPICINTF2_PHCRCAEF);
	cmipiIntCtrl.cmipi_int2_enable.permission_flg	= 1;

	interrupt_clear2_cmipi_set_interrupt( interrupt_clear2_new(),E_IM_PRO_CMIPI_CH0, &cmipiIntCtrl );
@endcode
*/
INT32 interrupt_clear2_cmipi_set_interrupt( InterruptClear2*self,E_IM_PRO_CMIPI_CH ch, T_IM_PRO_INT_CMIPI_CTRL* cmipiIntCtrl );

/**
MONI Macro interrupt permission set
@param[in]	unitNo : Unit number.
@param[in]	blockType	 : PRO block type
@param[in]	ch			: channel
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_moni_set_interrupt( InterruptClear2*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_MONI_CH ch, T_IM_PRO_INT_CFG* intCfg );

/**
LDIV Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_ldiv_set_interrupt( InterruptClear2*self,E_IM_PRO_LDIV_CH ch, T_IM_PRO_INT_CFG* intCfg );

/**
OBT Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_obt_set_interrupt( InterruptClear2*self,E_IM_PRO_OBT_CH ch, T_IM_PRO_INT_CFG* intCfg );

/**
OBD Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_obd_set_interrupt( InterruptClear2*self,E_IM_PRO_OBD_CH ch, T_IM_PRO_INT_CFG* intCfg );

/**
SROTOP Interrupt setting
@param[in]	unitNo : Unit number.
@param[in]	intCtrl : SROTOP interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear2_srotop_interrupt_ctrl( InterruptClear2*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_INT_SROTOP_CTRL* intCtrl );

/**
Set SDC Interrupt flg
@param[in]	unitNo : Unit number.
@param[in]	ch : SDC channel<br>
	 			 value range:[0 - 1]<br>
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK				:setting ok
@retval		D_IM_PRO_PARAM_ERROR	:setting ng
*/
INT32 interrupt_clear2_sdc_set_interrupt( InterruptClear2*self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, T_IM_PRO_INT_CFG* intCfg );

/**
B2BTOP Interrupt setting
@param[in]	unitNo : Unit number.
@param[in]	intCtrl : B2BTOP interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear2_b2btop_interrupt_ctrl( InterruptClear2*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_INT_B2BTOP_CTRL* intCtrl );

/**
AEAWB Macro interrupt permission set
@param[in]	ch : channel
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_aeawb_set_interrupt( InterruptClear2*self,E_IM_PRO_AEAWB_CH ch, T_IM_PRO_INT_CFG* intCfg );

/**
AF Macro interrupt permission set
@param[in]	ch : channel
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_af_set_interrupt( InterruptClear2*self,E_IM_PRO_AF_CH ch, T_IM_PRO_INT_CFG* intCfg );

/**
HIST Macro interrupt permission set
@param[in]	ch : channel
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_hist_set_interrupt( InterruptClear2*self,E_IM_PRO_HIST_CH ch, T_IM_PRO_INT_CFG* intCfg );

/**
PASTOP Interrupt setting
@param[in]	intCtrl : PASTOP interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear2_pastop_interrupt_ctrl( InterruptClear2*self,T_IM_PRO_INT_PASTOP_CTRL* intCtrl );

/**
PWch Macro interrupt permission set
@param[in]	unitNo : Unit number.
@param[in]	blockType	 : PRO block type
@param[in]	ch			: PWch number
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_pwch_set_interrupt( InterruptClear2*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_PWCH ch, T_IM_PRO_INT_CFG* intCfg );

/**
The permission setting of the PRch interrupt control is done.
@param[in]	unitNo : Unit number.
@param[in]	blockType	 : PRO block type
@param[in]	ch : PRch channel
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_clear2_prch_set_interrupt( InterruptClear2*self,
		E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, E_IM_PRO_PRCH ch, T_IM_PRO_INT_CFG* intCfg );

#endif /* __INTERRUPT_CLEAR2_H__ */
