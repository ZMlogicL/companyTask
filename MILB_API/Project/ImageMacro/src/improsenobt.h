/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-01
*@author              :杨金波
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __IMPRO_SENOBT_H__
#define __IMPRO_SENOBT_H__


#include <klib.h>
#include "improbase.h"
#include "improsentop.h"

#define IMPRO_TYPE_SENOBT        (impro_senobt_get_type())
#define IMPRO_SENOBT(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSenobt))
#define IMPRO_IS_SENOBT(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SENOBT))


/*宏定义区域*/
/** @addtogroup im_pro_sen_obt OBT*/
/**< Minimum setting of OBTV	*/
#define	ImproSenobt_D_IM_PRO_OBT_OBTV_MIN			(0)
/**< Maximum setting of OBTV	*/
#define	ImproSenobt_D_IM_PRO_OBT_OBTV_MAX			(8191)
/**< Minimum setting of OBTH	*/
#define	ImproSenobt_D_IM_PRO_OBT_OBTH_MIN			(0)
	/**< Maximum setting of OBTH	*/
#define	ImproSenobt_D_IM_PRO_OBT_OBTH_MAX			(12287)
	/**< Minimum setting of OBTVW	*/
#define	ImproSenobt_D_IM_PRO_OBT_OBTVW_MIN			(1)
/**< Maximum setting of OBTVW	*/
#define	ImproSenobt_D_IM_PRO_OBT_OBTVW_MAX			(127)
	/**< Minimum setting of OBTHW	*/
#define	ImproSenobt_D_IM_PRO_OBT_OBTHW_MIN			(1)
/**< Maximum setting of OBTHW	*/
#define	ImproSenobt_D_IM_PRO_OBT_OBTHW_MAX			(12288)
// im_pro_sen_obt

/*其他结构体或类型定义区域*/
/** PRO TOP OB Enable/Disable*/
typedef enum {
	/**< Disable	*/
	ImproSenobt_E_IM_PRO_OBT_DIS = 0,
	/**< Enable		*/
	ImproSenobt_E_IM_PRO_OBT_EN
} EimproObtEnable;

/** PRO TOP OB statistics select*/
typedef enum {
	/**< TOP OB common all pixel mode	*/
	ImproSenobt_E_IM_PRO_OBT_MODE_ALL = 0,
	/**< TOP OB each color mode			*/
	ImproSenobt_E_IM_PRO_OBT_MODE_COLOR
} EimproObtMode;

/** PRO TOP OB Correction select*/
typedef enum {
	/**< TOP OB correction fix value use		*/
	ImproSenobt_E_IM_PRO_OBT_SELECT_FIX = 0,
	/**< TOP OB correction evaluation value use	*/
	ImproSenobt_E_IM_PRO_OBT_SELECT_EVALUATION
} EimproObtSelect;

/** PRO TOP OB Intercommunication Enable/Disable*/
typedef enum {
	/**< Inter-OBT communication is disabled.		*/
	ImproSenobt_E_IM_PRO_OBT_INTERCOMM_DIS = 0,
	/**< OBT communication is enabled.				*/
	ImproSenobt_E_IM_PRO_OBT_INTERCOMM_EN
} EimproObtIntercommEnable;


/** TOP OB Control information*/
typedef struct {
	/**< OBT Correction enable target registor	:@@OBTEN remarks
	 * :Even if value set to 0(disable), OBT Detection performed. */
	EimproObtEnable						obtEnable;
	/**< TopOB Detection mode selection target registor	:@@OBTMD */
	EimproObtMode						mode;
	/**< Top OB Correction select target registor	:@@OBTSL */
	EimproObtSelect						sel;
	/**< OBT Intercommunication Enable/Disable target registor	:@@OBTCEN */
	EimproObtIntercommEnable	intercommEnable;
	/**< OB Input upper threshold value value range		:[0 - 16383] target registor	:@@OBTHTHBIT */
	USHORT										obMaxValue;
	/**< OB Input lower threshold value value range		:[0 - 16383] target registor	:@@OBTLTHBIT */
	USHORT										obMinValue;
} TimproObtCtrl;

typedef struct {
	/**< 2800_(B8C0 - B8C3h) */
	ULONG				obtctl;
	/**< 2800_(B8D4 - B8D7h) */
	ULONG				obtthbit;
	/**< 2800_(B8E8 - B8EBh) */
	ULONG				obtofsr;
	/**< 2800_(B8EC - B8EFh) */
	ULONG				obtofsgr;
	/**< 2800_(B8F0 - B8F3h) */
	ULONG				obtofsgb;
	/**< 2800_(B8F4 - B8F7h) */
	ULONG				obtofsb;
} TimproRdmaObtAddr;

/*类型定义区域*/
typedef struct _ImproSenobt							ImproSenobt;
typedef struct _ImproSenobtPrivate				ImproSenobtPrivate;


/*对象结构体区域*/
struct _ImproSenobt
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_senobt_get_type(void);
ImproSenobt*		impro_senobt_new();
/**
Start TOP OB macro.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Processing OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_senobt_start( EimproObtCh ch );
/**
Stop TOP OB macro.
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_senobt_stop( EimproObtCh ch, UCHAR force );
/**
The control parameter of TOP OB compensation is set.
@param[in]	ch : Channel No.
@param[in]	obtCtrl	:	TOP OB Control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_senobt_ctrl( EimproObtCh ch, TimproObtCtrl* obtCtrl );
/**
The area for Top OB detection is set up.
@param[in]	ch : Channel No.
@param[in]	obtArea	:The area for Top OB detection. See @ref TimproAreaInfo<br>
							value range  :posX[0 - 12287]<br>
							target registor  :@@OBTH<br>
							value range  :posY[0 - 8191]<br>
							target registor  :@@OBTV<br>
							value range  :width[1 - 12288]	1pixel boundary(OBTMD=0)<br>
															2pixel boundary(OBTMD=1)<br>
							target registor  :@@OBTHW<br>
							value range  :lines[1 - 127]	1pixel boundary(OBTMD=0)<br>
															2pixel boundary(OBTMD=1)<br>
							target registor  :@@OBTVW
@retval		D_DDIM_OK						: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
extern	INT32			impro_senobt_set_area( EimproObtCh ch, TimproAreaInfo* obtArea );
/**
Set TOP OB offset
@param[in]	ch : Channel No.<br>
				 value range:[0 - 1]<br>
@param[in]	offset : TOP OB offset<br>
					 value range : rr :[0x4000(=-16384) - 0x3FFF(=+16383)]<br>
					 target registor :@@obtOfsr<br>
					 value range : gr :[0x4000(=-16384) - 0x3FFF(=+16383)]<br>
					 target registor :@@obtOfsgr<br>
					 value range : gb :[0x4000(=-16384) - 0x3FFF(=+16383)]<br>
					 target registor :@@obtOfsgb<br>
					 value range : bb :[0x4000(=-16384) - 0x3FFF(=+16383)]<br>
					 target registor :@@obtOfsb
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@remarks	Please set up a minus value by a complement. bit15 is sign bit
*/
extern	INT32			impro_senobt_set_offset( EimproObtCh ch, TimproARgb2* offset );
/**
Get TOP OB detection data
@param[in]	ch : Channel No.<br>
				 value range:[0 - 1]<br>
@param[out]	obtdata : OBTDATA
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_senobt_get_bot_data( EimproObtCh ch, TimproARgb2* obtdata );
/**
Get the top address of the address array of OBT control.
@param[in]		ch : Channel No.
@param[out]		addr					: Top address of the address array of OBT control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
extern	INT32			impro_senobt_get_rdma_addr_obt_cntl( EimproObtCh ch, const TimproRdmaObtAddr** addr );




#endif /* __IMPRO_SENOBT_H__ */

