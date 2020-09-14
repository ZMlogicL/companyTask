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


#ifndef __IMPRO_SROTOP_H__
#define __IMPRO_SROTOP_H__


#include <klib.h>
#include "jdspro.h"
#include "improcommon.h"
#include "ddtop.h"

#define IMPRO_TYPE_SROTOP       	 (impro_srotop_get_type())
#define IMPRO_SROTOP(obj)      	 (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSrotop))
#define IMPRO_IS_SROTOP(obj)    	 (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SROTOP))


/*宏定义区域*/
/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
// PRO Channel/Macro start/stop status
/**< Minimum setting of GENV	*/
#define	ImproSrotop_D_IM_PRO_SROTOP_GENV_MIN				(2)
	/**< Maximum setting of GENV	*/
#define	ImproSrotop_D_IM_PRO_SROTOP_GENV_MAX			(16382)
/**< Minimum setting of GENH	*/
#define	ImproSrotop_D_IM_PRO_SROTOP_GENH_MIN			(2)
	/**< Maximum setting of GENH	*/
#define	ImproSrotop_D_IM_PRO_SROTOP_GENH_MAX			(16382)

/* SRO clock status ON	*/
#define ImproSrotop_IM_PRO_SRO_SET_START_STATUS(st, ch) 	(S_G_IM_SRO_START_Status[((st) >> 28) & 0xf]\
																											|=  (((st) & 0x0fffffff) << (ch)))
/* SRO clock status OFF	*/
#define ImproSrotop_IM_PRO_SRO_SET_STOP_STATUS(st, ch)		(S_G_IM_SRO_START_Status[((st) >> 28)\
                                                      		                         	 	 	 	 	 	 & 0xf] &= ~(((st) & 0x0fffffff) << (ch)))


/*其他结构体或类型定义区域*/
static	volatile	ULONG	S_G_IM_SRO_START_Status[3] = {0x00000000};

/** input mode of SRO unit.*/
typedef enum {
	/**< SEN direct connection mode	*/
	ImproSrotop_E_IM_PRO_SROTOP_INPUT_MODE_DIRECT = 0,
	/**< Bayer data re-input mode	*/
	ImproSrotop_E_IM_PRO_SROTOP_INPUT_MODE_REINPUT,
} EimproSrotopInputMode;

/** mode of SRO unit.*/
typedef enum {
	/**< FF0/1: valid   FSHDL0: valid   FSHDL1: invalid	*/
	ImproSrotop_E_IM_PRO_SROTOP_MODE0 = 0,
	/**< FF0/1: valid   FSHDL0: invalid FSHDL1: valid	*/
	ImproSrotop_E_IM_PRO_SROTOP_MODE1,
	/**< FF0/1: invalid FSHDL0: valid   FSHDL1: valid	*/
	ImproSrotop_E_IM_PRO_SROTOP_MODE2,
} EimproSrotopMode;

/** select in which unit FFC/CAG macro are used, SRO or B2B.*/
typedef enum {
	/**< FFC/CAG macro are used in SRO unit	*/
	ImproSrotop_E_IM_PRO_SROTOP_CAG_TARGET_BLOCK_SRO = 0,
	/**< FFC/CAG macro are used in B2B unit */
	ImproSrotop_E_IM_PRO_SROTOP_CAG_TARGET_BLOCK_B2B,
} EimproSrotopCagTargetBlock;

/** select a path for P2M0/1 and PWCH0/1 of SRO unit.*/
typedef enum {
	/**< Path without BayerResize	*/
	ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_BAY_OUT_WITHOUT_BR = 0,
	/**< Path with BayerResize */
	ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_BAY_OUT_WITH_BR,
	/**< Outputs of PG is inputted */
	ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_BAY_OUT_PG_OUT,
	/**< Outputs of CAG is inputted */
	ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_BAY_OUT_CAG_OUT,
} EimproSrotopPathSelBayOut;

/** select a path for B2B direct connection I/F.*/
typedef enum {
	/**< Path without BayerResize	*/
	ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_B2B_CONN_WITHOUT_BR = 0,
	/**< Path with BayerResize */
	ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_B2B_CONN_WITH_BR,
} EimproSrotopPathSelB2bConn;

/** select a path for LTM direct connection I/F.
*/
typedef enum {
	/**< Path without BayerResize	*/
	ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_LTM_CONN_WITHOUT_BR = 0,
	/**< Path with BayerResize */
	ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_LTM_CONN_WITH_BR,
} EimproSrotopPathSelLtmConn;

/** WEITGEN Enable/Disable*/
typedef enum {
	/**< Disable	*/
	ImproSrotop_E_IM_PRO_WEITGEN_DIS = 0,
	/**< Enable		*/
	ImproSrotop_E_IM_PRO_WEITGEN_EN
} EimproWeitgenEnable;

typedef enum {
	/**< SROCLK		*/
	ImproSrotop_E_IM_PRO_SROTOP_CLK_TYPE_SROCLK = 0,
	/**< SROCLK2	*/
	ImproSrotop_E_IM_PRO_SROTOP_CLK_TYPE_SROCLK2,
} EimproSrotopClkType;

/** WEITGEN channel number.
*/
typedef enum {
	/**< ch0		*/
	ImproSrotop_E_IM_PRO_WEITGEN_CH0 = 0,
	/**< ch1		*/
	ImproSrotop_E_IM_PRO_WEITGEN_CH1,
} EimproWeitgenCh;

/** SROTOP Macro Control Information*/
typedef struct {
	/**< Select the input mode of SRO unit. SROTOPCTL1@@SROISW */
	EimproSrotopInputMode			inputMode;
	/**< Select an mode of SRO unit. SROTOPCTL1@@SROMD */
	EimproSrotopMode				sroModeSel;
	/**< Select in which unit FFC/CAG macro are used, SRO or B2B. SROTOPCTL1@@CAGSL */
	EimproSrotopCagTargetBlock	cagTargetSel;
	/**< Select a path for P2M0/1 and PWCH0/1 of SRO unit. SROTOPCTL1@@BRPSW0 */
	EimproSrotopPathSelBayOut	bayOutPathSel;
	/**< Select a path for B2B direct connection I/F. SROTOPCTL1@@BRPSW1 */
	EimproSrotopPathSelB2bConn	b2bConnectPathSel;
	/**< Select a path for LTM direct connection I/F. SROTOPCTL1@@BRPSW2 */
	EimproSrotopPathSelLtmConn	ltmConnectPathSel;
	/**< Select an Bayer first pixel for each PAT block input SROTOPCTL2@@ORG0-@@ORG1 */
	EimproOrg						firstPixel[2];
} TimproSrotopCtrl;

/** WEITGEN Macro Control Information*/
typedef struct {
	/**< vertical position of WAIT signal occurs during vertical blanking. @@GENVx  value range  :[2 - 16382] */
	USHORT								vWaitSignalPos;
	/**< horizontal position of WAIT signal occurs during horizontal blanking. @@GENHx   value range  :[2 - 16382] */
	USHORT								hWaitSignalPos;
} TimproSrotopWeitgenCtrl;





/*类型定义区域*/
typedef struct _ImproSrotop					ImproSrotop;
typedef struct _ImproSrotopPrivate				ImproSrotopPrivate;


/*对象结构体区域*/
struct _ImproSrotop
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_srotop_get_type(void);
ImproSrotop*			impro_srotop_new();
/**
SROTOP Macro initialize
@param[in]	unitNo : Unit number.
@remarks	Please Call at the time of system starting.
*/
extern	VOID			impro_srotop_init( E_IM_PRO_UNIT_NUM unitNo );
/**
SROTOP Macro software reset
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: All macro not stopped NG
*/
extern	INT32			impro_srotop_sw_reset( E_IM_PRO_UNIT_NUM unitNo );
/**
SROTOP Macro clock control
@param[in]	unitNo : Unit number.
@param[in]	clkType	: SROTOP Macro clock type
@param[in]	onOff		: 0:clock on 1:clock off
@param[in]	waitSkip	: 0:non wait 1:wait 1ms. for wait PROCLK/CDK 5 cycle.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srotop_control_clock( E_IM_PRO_UNIT_NUM unitNo, EimproSrotopClkType clkType,
									UCHAR onOff, UCHAR waitSkip );
/**
SROTOP macro control data setting
@param[in]	unitNo : Unit number.
@param[in]	ctrl : SROTOP macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srotop_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproSrotopCtrl* ctrl );
/**
WEITGEN macro control data setting
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	weitgenCtrl : WEITGEN macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srotop_weitgen_ctrl( E_IM_PRO_UNIT_NUM unitNo, EimproWeitgenCh ch,
									TimproSrotopWeitgenCtrl* weitgenCtrl );
/**
setup of enable to WEITGEN macro.
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	enabled : setup of enable to WEITGEN macro.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srotop_weitgen_enable( E_IM_PRO_UNIT_NUM unitNo, EimproWeitgenCh ch,
									EimproWeitgenEnable enabled );








#endif /* __IMPRO_SROTOP_H__ */

