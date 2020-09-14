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


#ifndef __IMPRO_SENDMIPI_H__
#define __IMPRO_SENDMIPI_H__


#include <klib.h>
#include "improbase.h"
#include "improsentop.h"

#define IMPRO_TYPE_SENDMIPI        (impro_sendmipi_get_type())
#define IMPRO_SENDMIPI(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSendmipi))
#define IMPRO_IS_SENDMIPI(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SENDMIPI))


/*宏定义区域*/


/*其他结构体或类型定义区域*/
/** Number of input lanes selection.*/
typedef enum {
	/**< 1-lane input */
	ImproSendmipi_E_IM_PRO_DMIPI_LANE_1 = 0,
	/**< 2-lane input */
	ImproSendmipi_E_IM_PRO_DMIPI_LANE_2,
	/**< 4-lane input */
	ImproSendmipi_E_IM_PRO_DMIPI_LANE_4 = 3,
} EimproDmipiLane;

/** select the Virtual Channel value for the packets output to the OUT0/1 side.*/
typedef enum {
	/**< Virtual Channel0 */
	ImproSendmipi_E_IM_PRO_DMIPI_VC_0 = 0,
	/**< Virtual Channel1 */
	ImproSendmipi_E_IM_PRO_DMIPI_VC_1,
	/**< Virtual Channel2 */
	ImproSendmipi_E_IM_PRO_DMIPI_VC_2,
	/**< Virtual Channel3 */
	ImproSendmipi_E_IM_PRO_DMIPI_VC_3,
} EimproDmipiVc;

/** select the input data mode.*/
typedef enum {
	/**< RAW 8-bit mode */
	ImproSendmipi_E_IM_PRO_DMIPI_IN_DATA_MODE_8BIT = 0,
	/**< RAW 10-bit mode */
	ImproSendmipi_E_IM_PRO_DMIPI_IN_DATA_MODE_10BIT,
	/**< RAW 12-bit mode */
	ImproSendmipi_E_IM_PRO_DMIPI_IN_DATA_MODE_12BIT,
	/**< RAW 14-bit mode */
	ImproSendmipi_E_IM_PRO_DMIPI_IN_DATA_MODE_14BIT,
	/**< Legacy YUV420 8-bit  */
	ImproSendmipi_E_IM_PRO_DMIPI_IN_DATA_MODE_LEGACY_YUV420,
	/**< YUV422 8-bit */
	ImproSendmipi_E_IM_PRO_DMIPI_IN_DATA_MODE_YUV422,
	/**< User Defined/Embedded Data */
	ImproSendmipi_E_IM_PRO_DMIPI_IN_DATA_MODE_USER_DEF,
} EimproDmipiInDataMode;

/** Output data mode selection.*/
typedef enum {
	/**< No output */
	ImproSendmipi_E_IM_PRO_DMIPI_OUT_MODE_NO_OUTPUT = 0,
	/**< 1-line output mode */
	ImproSendmipi_E_IM_PRO_DMIPI_OUT_MODE_1LINE = 2,
	/**< 2-point output mode */
	ImproSendmipi_E_IM_PRO_DMIPI_OUT_MODE_2POINT,
	/**< 4-point output mode */
	ImproSendmipi_E_IM_PRO_DMIPI_OUT_MODE_4POINT,
	/**< 8-point output mode */
	ImproSendmipi_E_IM_PRO_DMIPI_OUT_MODE_8POINT,
} EimproDmipiOutMode;

/** select the DataType mode for the packets output.*/
typedef enum {
	/**< DT selection mode is off */
	ImproSendmipi_E_IM_PRO_DMIPI_DT_OUT_DIS = 0,
	/**< DT selection mode is on */
	ImproSendmipi_E_IM_PRO_DMIPI_DT_OUT_EN,
} EimproDmipiDtOut;


/**  select the cycle between horizontal detect pulse and output pixel data.*/
typedef enum {
	/**< The cycle between HDP and pixel data is 0 cycle. */
	ImproSendmipi_E_IM_PRO_DMIPI_SEL_CYCLE_0 = 0,
	/**< The cycle between HDP and pixel data is 2 cycle. */
	ImproSendmipi_E_IM_PRO_DMIPI_SEL_CYCLE_2,
} EimproDmipiSelCycle;

/** RxSyncMode value setting.*/
typedef enum {
	/**< Only perfectly-matched sync code is allowed. */
	ImproSendmipi_E_IM_PRO_DMIPI_RXSYNCMODE_PERFECTLY_MATCHED = 0,
	/**< One bit of discrepancy between sync codes is allowed. */
	ImproSendmipi_E_IM_PRO_DMIPI_RXSYNCMODE_1BIT_DISCREPANCY,
} EimproDmipiRxsyncmode;

/** RxEnable value setting.*/
typedef enum {
	/**< All RxEnable0~3 signals output "0". */
	ImproSendmipi_E_IM_PRO_DMIPI_RXENABLE_ALL_OUT0 = 0,
	/**< The corresponding RxEnable signal outputs "1". */
	ImproSendmipi_E_IM_PRO_DMIPI_RXENABLE_OUT1,
} EimproDmipiRxenable;

/** MIPI-DPHY Information.*/
typedef struct {
	/**< RxSyncMode value setting.target registor	:@@DPSM	*/
	EimproDmipiRxsyncmode		rxsyncmode;
	/**< value of output data RxSMT_D. Set DPSMTD to 4'h7RxSMT_D is an output signal
	 *  for setting the same phase input mask in the data lane of D-PHYarget registor	:@@DPSMTD	*/
	UCHAR										rxsmtDVal;
	/**< value of output data RxSMT_C. Set DPSMTD to 4'hERxSMT_C is an output signal for
	 * setting the same phase input mask in the clock lane of D-PHY.target registor	:@@DPSMTC	*/
	UCHAR										rxsmtCVal;
	/**< RxEnable value setting.target registor	:@@DPEN	*/
	EimproDmipiRxenable			rxenable;
} TimproDmipiPhyCtrl;

/** MIPI-DPHY Configuration.*/
typedef struct {
	/**< Number of input lanes selection.target registor	:@@LANE	*/
	EimproDmipiLane					laneSel;
	/**< select the Virtual Channel value for the packets output to the OUT0/1 side.target registor	:@@VCOUT0/1	*/
	EimproDmipiVc						vcModeSel[2];
	/**< select the input data mode.target registor	:@@DTMD0/1	*/
	EimproDmipiInDataMode		inputDataMode[2];
	/**< Output data mode selection.target registor	:@@OUTMD0/1	*/
	EimproDmipiOutMode			outputDataMode[2];
	/**< Output DT selection mode.target registor	:@@DTCOMD0/1	*/
	EimproDmipiDtOut				outputDtSel[2];
	/**< DataType value for the packets output to the OUT0/1 side target registor	:@@DTCO0/1	*/
	UCHAR										outputDtSetting[2];
	/**< MIPI D-PHY control. */
	TimproDmipiPhyCtrl				phyCtrl;
	/**< Setting the cycle for OUT0/1 side.target registor	:@@HDPDSEL0/1	*/
	EimproDmipiSelCycle			outCycle[2];
} TimproDmipiCtrl;

/** MIPI-DPHY Status Information.*/
typedef struct {
	/**< status of the signals input to D-PHY.target registor	:@@MPIDPVR	*/
	ULONG							inputSignalStatus;
	/**< status of the skew calibration to D-PHY.target registor	:@@MPISCS	*/
	ULONG							skewCalibrationStatus;
} TimproDmipiStatus;


/*类型定义区域*/
typedef struct _ImproSendmipi							ImproSendmipi;
typedef struct _ImproSendmipiPrivate				ImproSendmipiPrivate;


/*对象结构体区域*/
struct _ImproSendmipi
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_sendmipi_get_type(void);
ImproSendmipi*	impro_sendmipi_new();
/**
MIPI-DPHY initialize
@param[in]	ch : MIPI-DPHY channel
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sendmipi_init( EimproDmipiCh ch );
/**
Software reset of MIPI-DPHY
@param[in]	ch : MIPI-DPHY channel
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sendmipi_sr( EimproDmipiCh ch );
/**
MIPI-DPHY macro start.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Macro Start OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: D-MIPI has not stopped NG
*/
extern	INT32			impro_sendmipi_start( EimproDmipiCh ch );
/**
MIPI-DPHY macro stop.
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Macro Stop OK
@retval		D_IM_PRO_NG					: Macro Stop NG
*/
extern	INT32			impro_sendmipi_stop( EimproDmipiCh ch, UCHAR force );
/**
The control parameter of MIPI-DPHY is set.
@param[in]	ch : Channel No.
@param[in]	dmipiCtrl : MIPI-DPHY control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_sendmipi_ctrl( EimproDmipiCh ch, TimproDmipiCtrl* dmipiCtrl );
/**
A setup of enable access to the built-in RAM of MIPI-DPHY.
@param[in]	ch : Channel No.
@param[in]	paen0Trg : RAM0 access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@param[in]	paen1Trg : RAM1 access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_sendmipi_set_paen( EimproDmipiCh ch, UCHAR paen0Trg, UCHAR paen1Trg );
/**
Get MIPI D-PHY status..
@param[in]	ch : Channel No.
@param[out]	status : MIPI-DPHY status information
@retval		D_DDIM_OK					: Getting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Getting NG
*/
extern	INT32			impro_sendmipi_get_status( EimproDmipiCh ch, TimproDmipiStatus* status );


#endif /* __IMPRO_SENDMIPI_H__ */

