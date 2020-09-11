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


#ifndef __IMPRO_SENCMIPI_H__
#define __IMPRO_SENCMIPI_H__


#include <klib.h>
#include "improbase.h"
#include "improsentop.h"

#define IMPRO_TYPE_SENCMIPI        (impro_sencmipi_get_type())
#define IMPRO_SENCMIPI(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSencmipi))
#define IMPRO_IS_SENCMIPI(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SENCMIPI))


/*宏定义区域*/


/*其他结构体或类型定义区域*/
/** Number of input lanes selection.*/
typedef enum {
	/**< 1-lane input */
	ImproSencmipi_E_IM_PRO_CMIPI_LANE_1 = 0,
	/**< 2-lane input */
	ImproSencmipi_E_IM_PRO_CMIPI_LANE_2,
	/**< 4-lane input */
	ImproSencmipi_E_IM_PRO_CMIPI_LANE_4 = 3,
} EimproCmipiLane;

/** select the Virtual Channel value for the packets output to the OUT0/1 side.*/
typedef enum {
	/**< Virtual Channel0 */
	ImproSencmipi_E_IM_PRO_CMIPI_VC_0 = 0,
	/**< Virtual Channel1 */
	ImproSencmipi_E_IM_PRO_CMIPI_VC_1,
	/**< Virtual Channel2 */
	ImproSencmipi_E_IM_PRO_CMIPI_VC_2,
	/**< Virtual Channel3 */
	ImproSencmipi_E_IM_PRO_CMIPI_VC_3,
	/**< Virtual Channel invalid ( All output ) */
	ImproSencmipi_E_IM_PRO_CMIPI_VC_INVALID,
} EimproCmipiVc;

/** select the input data mode.*/
typedef enum {
	/**< RAW 8-bit mode */
	ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_8BIT = 0,
	/**< RAW 10-bit mode */
	ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_10BIT,
	/**< RAW 12-bit mode */
	ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_12BIT,
	/**< RAW 14-bit mode */
	ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_14BIT,
	/**< Legacy YUV420 8-bit  */
	ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_LEGACY_YUV420,
	/**< YUV422 8-bit */
	ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_YUV422,
	/**< User Defined/Embedded Data */
	ImproSencmipi_E_IM_PRO_CMIPI_IN_DATA_MODE_USER_DEF,
} EimproCmipiInDataMode;

/** Output data mode selection.*/
typedef enum {
	/**< No output */
	ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_NO_OUTPUT = 0,
	/**< 1-line output mode */
	ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_1LINE = 2,
	/**< 2-point output mode */
	ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_2POINT,
	/**< 4-point output mode */
	ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_4POINT,
	/**< 8-point output mode */
	ImproSencmipi_E_IM_PRO_CMIPI_OUT_MODE_8POINT,
} EimproCmipiOutMode;

/** select the DataType mode for the packets output.*/
typedef enum {
	/**< DT selection mode is off */
	ImproSencmipi_E_IM_PRO_CMIPI_DT_OUT_DIS = 0,
	/**< DT selection mode is on */
	ImproSencmipi_E_IM_PRO_CMIPI_DT_OUT_EN,
} EimproCmipiDtOut;

/**  select the cycle between horizontal detect pulse and output pixel data.*/
typedef enum {
	/**< The cycle between HDP and pixel data is 0 cycle. */
	ImproSencmipi_E_IM_PRO_CMIPI_SEL_CYCLE_0 = 0,
	/**< The cycle between HDP and pixel data is 2 cycle. */
	ImproSencmipi_E_IM_PRO_CMIPI_SEL_CYCLE_2,
} EimproCmipiSelCycle;

/** RxEnable value setting.*/
typedef enum {
	/**< All RxEnable0~3 signals output "0". */
	ImproSencmipi_E_IM_PRO_CMIPI_RXENABLE_ALL_OUT0 = 0,
	/**< The corresponding RxEnable signal outputs "1". */
	ImproSencmipi_E_IM_PRO_CMIPI_RXENABLE_OUT1,
} EimproCmipiRxenable;

/** MIPI-CPHY Status Information.*/
typedef struct {
	/**< RxStopstate_L0 signal status.	target registor	:@@SSL0				*/
	UCHAR							rxstopstateL0;
	/**< RxStopstate_L1 signal status.	target registor	:@@SSL1				*/
	UCHAR							rxstopstateL1;
	/**< RxStopstate_L2 signal status.	target registor	:@@SSL2				*/
	UCHAR							rxstopstateL2;
	/**< Lane0 status.					target registor	:@@RLR_LSTATUS0		*/
	UCHAR							lstatus0;
	/**< Lane1 status.					target registor	:@@RLR_LSTATUS1		*/
	UCHAR							lstatus1;
	/**< Lane2 status.					target registor	:@@RLR_LSTATUS2		*/
	UCHAR							lstatus2;
	/**< Lane0 Word error count.		target registor	:@@RLR_WERRCNT0		*/
	UCHAR							werrcnt0;
	/**< Lane1 Word error count.		target registor	:@@RLR_WERRCNT1		*/
	UCHAR							werrcnt1;
	/**< Lane2 Word error count.		target registor	:@@RLR_WERRCNT2		*/
	UCHAR							werrcnt2;
	/**< Lane0 Word count.				target registor	:@@RLR_WCNT0		*/
	ULLONG						wcnt0;
	/**< Lane1 Word count.				target registor	:@@RLR_WCNT1		*/
	ULLONG						wcnt1;
	/**< Lane2 Word count.				target registor	:@@RLR_WCNT2		*/
	ULLONG						wcnt2;
	/**< Lane0 Symbol error count.		target registor	:@@RLR_SYERRCNT0	*/
	UCHAR							syerrcnt0;
	/**< Lane1 Symbol error count.		target registor	:@@RLR_SYERRCNT1	*/
	UCHAR							syerrcnt1;
	/**< Lane2 Symbol error count.		target registor	:@@RLR_SYERRCNT2	*/
	UCHAR							syerrcnt2;
	/**< Lane0 error location.			target registor	:@@RLR_SYERRLOC0	*/
	ULLONG						syerrloc0;
	/**< Lane1 error location.			target registor	:@@RLR_SYERRLOC1	*/
	ULLONG						syerrloc1;
	/**< Lane2 error location.			target registor	:@@RLR_SYERRLOC2	*/
	ULLONG						syerrloc2;
} TimproCmipiStatus;

/** MIPI-CPHY Information.detail of this setting value, please refer to C-PHY macro specifications.*/
typedef struct {
	/**< RxEnable value setting.				target registor	:@@CPEN	*/
	EimproCmipiRxenable			rxenable;
	/**< Settle count setting.					target registor	:@@CP_HS_SETTLECNT	*/
	UCHAR										hsSettlecnt;
	/**< Stop count setting.					target registor	:@@CP_HS_STOPCNT	*/
	UCHAR										hsStopcnt;
	/**< Sync detection mode setting.			target registor	:@@CP_HS_SYNCMODE	*/
	UCHAR										hsSyncmode;
	/**< Lane configuration.					target registor	:@@CP_RLR_LCONFIG	*/
	UCHAR										rlrLconfig;
	/**< Test pattern select.					target registor	:@@CP_RLR_TPSEL		*/
	UCHAR										rlrTpsel;
	/**< PRBS seed value.						target registor	:@@CP_RLR_PRBSSP	*/
	UCHAR										rlrPrbssp;
	/**< Preamble configuration sequence value.	target registor	:@@CP_TGR_PROGSEQ	*/
	ULLONG									tgrProgseq;
	/**< ForceRxmode(lane2) value.				target registor	:@@CP_FORCERXMODE2	*/
	UCHAR										forcerxmode2;
	/**< ForceRxmode(lane1) value.				target registor	:@@CP_FORCERXMODE1	*/
	UCHAR										forcerxmode1;
	/**< ForceRxmode(lane0) value.				target registor	:@@CP_FORCERXMODE0	*/
	UCHAR										forcerxmode0;
} TimproCmipiPhyCtrl;

/** MIPI-CPHY Configuration.*/
typedef struct {
	/**< Number of input lanes selection.target registor	:@@LANE	*/
	EimproCmipiLane					laneSel;
	/**< select the Virtual Channel value for the packets output to the OUT0/1 side.<br>
	target registor	:@@VCOUT0/1	*/
	EimproCmipiVc						vcModeSel[2];
	/**< select the input data mode target registor	:@@DTMD0/1	*/
	EimproCmipiInDataMode		inputDataMode[2];
	/**< Output data mode selection.target registor	:@@OUTMD0/1	*/
	EimproCmipiOutMode			outputDataMode[2];
	/**< Output DT selection modetarget registor	:@@DTCOMD0/1	*/
	EimproCmipiDtOut				outputDtSel[2];
	/**< DataType value for the packets output to the OUT0/1 side.target registor	:@@DTCO0/1	*/
	UCHAR										outputDtSetting[2];
	/**< Setting the cycle for OUT0/1 side.target registor	:@@HDPDSEL0/1	*/
	EimproCmipiSelCycle			outCycle[2];
	/**< MIPI C-PHY control. */
	TimproCmipiPhyCtrl				phyCtrl;
} TimproCmipiCtrl;



/*类型定义区域*/
typedef struct _ImproSencmipi							ImproSencmipi;
typedef struct _ImproSencmipiPrivate				ImproSencmipiPrivate;


/*对象结构体区域*/
struct _ImproSencmipi
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_sencmipi_get_type(void);
ImproSencmipi*	impro_sencmipi_new();
/**
MIPI-CPHY initialize
@param[in]	ch : MIPI-CPHY channel
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sencmipi_init( E_IM_PRO_CMIPI_CH ch );
/**
Software reset of MIPI-CPHY
@param[in]	ch : MIPI-CPHY channel
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sencmipi_sr( E_IM_PRO_CMIPI_CH ch );
/**
MIPI-CPHY macro start.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Macro Start OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: D-MIPI has not stopped NG
*/
extern	INT32			impro_sencmipi_start( E_IM_PRO_CMIPI_CH ch );
/**
MIPI-CPHY macro stop.
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Macro Stop OK
@retval		D_IM_PRO_NG					: Macro Stop NG
*/
extern	INT32			impro_sencmipi_stop( E_IM_PRO_CMIPI_CH ch, UCHAR force );
/**
The control parameter of MIPI-CPHY is set.
@param[in]	ch : Channel No.
@param[in]	cmipiCtrl : MIPI-CPHY control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_sencmipi_ctrl( E_IM_PRO_CMIPI_CH ch, TimproCmipiCtrl* cmipiCtrl );
/**
A setup of enable access to the built-in RAM of MIPI-CPHY.
@param[in]	ch : Channel No.
@param[in]	paen0Trg : RAM0 access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@param[in]	paen1Trg : RAM1 access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_sencmipi_set_pean( E_IM_PRO_CMIPI_CH ch, UCHAR paen0Trg, UCHAR paen1Trg );
/**
Get MIPI C-PHY status..
@param[in]	ch : Channel No.
@param[out]	status : MIPI-CPHY status information
@retval		D_DDIM_OK					: Getting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Getting NG
*/
extern	INT32			impro_sencmipi_get_status( E_IM_PRO_CMIPI_CH ch, TimproCmipiStatus* status );



#endif /* __IMPRO_SENCMIPI_H__ */

