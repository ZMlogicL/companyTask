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

#ifndef __INTERRUPT_CLEAR1_H__
#define __INTERRUPT_CLEAR1_H__

#include <klib.h>
#include "im_pro.h"

#define INTERRUPT_TYPE_CLEAR1		(interrupt_clear1_get_type())
#define INTERRUPT_CLEAR1(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, InterruptClear1))
#define INTERRUPT_IS_CLEAR1(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, INTERRUPT_TYPE_CLEAR1))

typedef struct 				_InterruptClear1 InterruptClear1;
typedef struct 				_InterruptClear1Private InterruptClear1Private;

struct _InterruptClear1 {
	KObject parent;
};

KConstType 		    interrupt_clear1_get_type(void);
InterruptClear1*		        interrupt_clear1_new(void);

/**
SENTOP Interrupt setting
@param[in]	intCtrl : SENTOP interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear1_sentop_interrupt_ctrl( InterruptClear1*self,T_IM_PRO_INT_SENTOP_CTRL* intCtrl );

/**
SG Interrupt setting
@param[in]	sgIntCtrl : SG interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear1_sentop_sg_interrupt_ctrl( InterruptClear1*self,T_IM_PRO_INT_SG_CTRL* sgIntCtrl );

/**
GYRO Interrupt setting
@param[in]	gyroIntCtrl : GYRO interrupt control information structure
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_clear1_sentop_gyro_interrupt_ctrl( InterruptClear1*self,T_IM_PRO_INT_GYRO_CTRL* gyroIntCtrl );

/**
Set SLVS-EC Common Interrupt flg
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@code
	//
	//sample code
	//

	T_IM_PRO_INT_CFG intCfg;

	// for Lane0~3 error interrupt enabled setting
	intCfg.interrupt_bit	= ( D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE0 | D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE1 |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE2 | D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE3 |
								D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE0 | D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE1 |
								D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE2 | D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE3 |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE0  | D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE1  |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE2  | D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE3 );
	intCfg.permission_flg	= 1;	// interrupt enabled

	interrupt_clear1_slvs_set_interrupt( interrupt_clear1_new(),&intCfg );


	// for Lane0~3 error interrupt disabled setting
	intCfg.interrupt_bit	= ( D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE0 | D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE1 |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE2 | D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE3 |
								D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE0 | D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE1 |
								D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE2 | D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE3 |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE0  | D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE1  |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE2  | D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE3 );
	intCfg.permission_flg	= 0;	// interrupt disabled

	interrupt_clear1_slvs_set_interrupt( interrupt_clear1_new(),&intCfg );

@endcode
*/
INT32 interrupt_clear1_slvs_set_common_interrupt( InterruptClear1*self,T_IM_PRO_INT_CFG* intCfg );

/**
Set SLVS-EC Interrupt flg
@param[in]	streamType : stream type of SLVS
@param[in]	intType : interrupt type of SLVS
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@code
	//
	//sample code
	//

	T_IM_PRO_INT_CFG intCfg;

	// INTn_O (Normal operation) interrupt enabled setting.
	intCfg.interrupt_bit	= ( D_IM_PRO_SLVS_INTEN_FSI_BIT | D_IM_PRO_SLVS_INTEN_FSO_BIT |
								D_IM_PRO_SLVS_INTEN_FEI_BIT | D_IM_PRO_SLVS_INTEN_FEO_BIT |
								D_IM_PRO_SLVS_INTEN_RDY_BIT | D_IM_PRO_SLVS_INTEN_STBY_BIT );
	intCfg.permission_flg	= 1;	// interrupt enabled

	interrupt_clear1_slvs_set_interrupt( interrupt_clear1_new(),E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_INTN_O, &intCfg );

	// EINTn_O (PCS Error related) interrupt enabled setting.
	intCfg.interrupt_bit	= ( D_IM_PRO_SLVS_LEINTEN_LBOVF_BIT | D_IM_PRO_SLVS_LEINTEN_LNE_BIT |
								D_IM_PRO_SLVS_LEINTEN_ECCE_BIT | D_IM_PRO_SLVS_LEINTEN_PCRCE_BIT | D_IM_PRO_SLVS_LEINTEN_LLE_BIT );
	intCfg.permission_flg	= 1;	// interrupt enabled

	interrupt_clear1_slvs_set_interrupt( interrupt_clear1_new(),E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_PCS_ERR, &intCfg );


	// INTn_O (Normal operation) interrupt disabled setting.
	intCfg.interrupt_bit	= ( D_IM_PRO_SLVS_INTEN_FSI_BIT | D_IM_PRO_SLVS_INTEN_FSO_BIT |
								D_IM_PRO_SLVS_INTEN_FEI_BIT | D_IM_PRO_SLVS_INTEN_FEO_BIT |
								D_IM_PRO_SLVS_INTEN_RDY_BIT | D_IM_PRO_SLVS_INTEN_STBY_BIT );
	intCfg.permission_flg	= 0;	// interrupt disabled

	interrupt_clear1_slvs_set_interrupt( interrupt_clear1_new(),E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_INTN_O, &intCfg );

	// EINTn_O (PCS Error related) interrupt disabled setting.
	intCfg.interrupt_bit	= ( D_IM_PRO_SLVS_LEINTEN_LBOVF_BIT | D_IM_PRO_SLVS_LEINTEN_LNE_BIT |
								D_IM_PRO_SLVS_LEINTEN_ECCE_BIT | D_IM_PRO_SLVS_LEINTEN_PCRCE_BIT | D_IM_PRO_SLVS_LEINTEN_LLE_BIT );
	intCfg.permission_flg	= 0;	// interrupt disabled

	interrupt_clear1_slvs_set_interrupt( interrupt_clear1_new(),E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_PCS_ERR, &intCfg );

@endcode
*/
INT32 interrupt_clear1_slvs_set_interrupt( InterruptClear1*self,
		E_IM_PRO_SLVS_STREAM_TYPE streamType, E_IM_PRO_SLVS_INT_TYPE intType, T_IM_PRO_INT_CFG* intCfg );

/**
LVDS Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@code
	//sample code
	USHORT interrupt_bit;

	interrupt_bit = (D_IM_PRO_LVDSINTENB_EOLE0|D_IM_PRO_LVDSINTENB_SOLE0|D_IM_PRO_LVDSINTENB_EOFE0|D_IM_PRO_LVDSINTENB_SOFE0);

	interrupt_clear1_lvds_set_interrupt( InterruptClear1*self,interrupt_bit, 1 );
@endcode
*/
INT32 interrupt_clear1_lvds_set_interrupt( InterruptClear1*self,E_IM_PRO_LVDS_CH ch, T_IM_PRO_INT_LVDS_CTRL* intCfg );

/**
DMIPI Macro interrupt permission set
@param[in]	ch : Channel No.
@param[in]	intCfg : interrupt configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@code
	//sample code
	USHORT interrupt_bit;

	interrupt_bit = (D_IM_PRO_DMIPIINTENB_EOLE|D_IM_PRO_DMIPIINTENB_SOLE|D_IM_PRO_DMIPIINTENB_EOFE|D_IM_PRO_DMIPIINTENB_SOFE);

	interrupt_clear1_dmipi_set_interrupt( InterruptClear1*self,interrupt_bit, 1 );
@endcode
*/
INT32 interrupt_clear1_dmipi_set_interrupt( InterruptClear1*self,E_IM_PRO_DMIPI_CH ch, T_IM_PRO_INT_CFG* intCfg );


#endif /* __INTERRUPT_CLEAR1_H__ */
