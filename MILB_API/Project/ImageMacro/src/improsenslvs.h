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


#ifndef __IMPRO_SENSLVS_H__
#define __IMPRO_SENSLVS_H__


#include <klib.h>
#include "improbase.h"
#include "improsentop.h"

#define IMPRO_TYPE_SENSLVS        (impro_senslvs_get_type())
#define IMPRO_SENSLVS(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSenslvs))
#define IMPRO_IS_SENSLVS(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SENSLVS))


/*宏定义区域*/
/** PRO Return value of processing result
*/
/**< Error					*/
#define D_IM_PRO_NG					(D_IM_PRO | D_DDIM_NO_RECEIVE)
	/**< timeout				*/
#define	ImproSenslvs_D_IM_PRO_TIMEOUT			(D_IM_PRO | D_DDIM_TIMEOUT)
/**< System call error		*/
#define	ImproSenslvs_D_IM_PRO_SYSTEM_ERROR		(D_IM_PRO | D_DDIM_SYSTEM_ERROR)


/**< All wait flags of INTST	*/
#define	ImproSenslvs_D_IM_PRO_SLVS_INTST_ALL_WAITEND_FLG				(D_IM_PRO_SLVS_STREAM_A_INTST_FSI_WAITEND_FLG  | \
														 D_IM_PRO_SLVS_STREAM_A_INTST_FSO_WAITEND_FLG  | \
														 D_IM_PRO_SLVS_STREAM_A_INTST_FEI_WAITEND_FLG  | \
														 D_IM_PRO_SLVS_STREAM_A_INTST_FEO_WAITEND_FLG  | \
														 D_IM_PRO_SLVS_STREAM_A_INTST_RDY_WAITEND_FLG  | \
														 D_IM_PRO_SLVS_STREAM_A_INTST_STBY_WAITEND_FLG | \
														 D_IM_PRO_SLVS_STREAM_B_INTST_FSI_WAITEND_FLG  | \
														 D_IM_PRO_SLVS_STREAM_B_INTST_FSO_WAITEND_FLG  | \
														 D_IM_PRO_SLVS_STREAM_B_INTST_FEI_WAITEND_FLG  | \
														 D_IM_PRO_SLVS_STREAM_B_INTST_FEO_WAITEND_FLG  | \
														 D_IM_PRO_SLVS_STREAM_B_INTST_RDY_WAITEND_FLG  | \
														 D_IM_PRO_SLVS_STREAM_B_INTST_STBY_WAITEND_FLG	)

/*其他结构体或类型定义区域*/

/** SLVS input differential data value inversion setting.
*/
typedef enum {
	/**< Normal	*/
	ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL = 0,
	/**< Invert	*/
	ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_INVERT
} EimproSlvsInputDataInversion;


/** SLVS Multiplication factor control.
*/
typedef enum {
	/**< Reference Clock 72MHz Setting for (Data Rate 2.304Gbps)	*/
	ImproSenslvs_E_IM_PRO_SLVS_MULTIPLICATION_FACTOR_REF_CLK_72MHZ = 0,
	/**< Reserved	*/
	ImproSenslvs_E_IM_PRO_SLVS_MULTIPLICATION_FACTOR_RESERVED
} EimproSlvsMultiplicationFactor;

/** SLVS Power Down State select
*/
typedef enum {
	/**< Power Down state	*/
	ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_POWER_DOWN = 0,
	/**< power is being supplied state.	*/
	ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_NORMAL
} EimproSlvsPdState;

/** SLVS VDOUT control when frame stop is set
*/
typedef enum {
	/**< Next VDOUT after frame stop is set is not output.	*/
	ImproSenslvs_E_IM_PRO_SLVS_VDOUT_CTRL_NO_OUTPUT = 0,
	/**< Next VDOUT after frame stop is set is output.	*/
	ImproSenslvs_E_IM_PRO_SLVS_VDOUT_CTRL_OUTPUT,
} EimproSlvsVdoutCtrl;

/** SLVS ECC option / CRC Option of payload.
*/
typedef enum {
	/**< Without ECC/CRC.	*/
	ImproSenslvs_E_IM_PRO_SLVS_ECCCRC_OPT_WO_ECC_CRC = 0,
	/**< With CRC.	*/
	ImproSenslvs_E_IM_PRO_SLVS_ECCCRC_OPT_W_CRC,
	/**< With ECC(2byte parity).	*/
	ImproSenslvs_E_IM_PRO_SLVS_ECCCRC_OPT_W_ECC_2BYTE_PARITY,
	/**< With ECC(4byte parity).	*/
	ImproSenslvs_E_IM_PRO_SLVS_ECCCRC_OPT_W_ECC_4BYTE_PARITY,
	/**< ECC/CRC option select Max value	*/
	ImproSenslvs_E_IM_PRO_SLVS_ECCCRC_OPT_MAX,
} EimproSlvsEcccrcOpt;

/** SLVS expected value when Line Number Error of the line next to the state the Line Number
 *  extracted from the packet header reaches the MAX value (13’h1FFF) is detected.
*/
typedef enum {
	/**< expected value when Line Number Error occurred is 0x0000.	*/
	ImproSenslvs_E_IM_PRO_SLVS_EXPECT_VAL_H_0000 = 0,
	/**< expected value when Line Number Error occurred is 0x1FFF.	*/
	ImproSenslvs_E_IM_PRO_SLVS_EXPECT_VAL_H_1FFF,
} EimproSlvsExpectVal;

/** SLVS symbol type
*/
typedef enum {
	/**< code type is Data.	*/
	ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_DATA = 0,
	/**< code type is K Code.	*/
	ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_K_CODE,
} EimproSlvsSymbolType;

/** SLVS number of bits per pixel
*/
typedef enum {
	/**< 8bit	*/
	ImproSenslvs_E_IM_PRO_SLVS_PIXEL_BIT_8BIT = 0,
	/**< 10bit	*/
	ImproSenslvs_E_IM_PRO_SLVS_PIXEL_BIT_10BIT,
	/**< 12bit	*/
	ImproSenslvs_E_IM_PRO_SLVS_PIXEL_BIT_12BIT,
	/**< 14bit	*/
	ImproSenslvs_E_IM_PRO_SLVS_PIXEL_BIT_14BIT,
	/**< 16bit	*/
	ImproSenslvs_E_IM_PRO_SLVS_PIXEL_BIT_16BIT,
	/**< number of bits per pixel Max value	*/
	ImproSenslvs_E_IM_PRO_SLVS_PIXEL_BIT_MAX
} EimproSlvsPixelBit;

/** SLVS number of valid Lanes
*/
typedef enum {
	/**< 1Lane	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_NUM_1LANE = 0,
	/**< 2Lane	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_NUM_2LANE,
	/**< 4Lane	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_NUM_4LANE,
	/**< 6Lane	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_NUM_6LANE,
	/**< 8Lane	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_NUM_8LANE,
	/**< number of valid Lanes Max value	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_NUM_MAX
} EimproSlvsLaneNum;

/** SLVS Lane Enable/Disable
*/
typedef enum {
	/**< Disable	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_DIS = 0,
	/**< Enable		*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_EN
} EimproSlvsLaneEnable;


/** SLVS output format of the image data interface.
*/
typedef enum {
	/**< 1-point output	*/
	ImproSenslvs_E_IM_PRO_SLVS_OUT_FORMAT_1POINT = 0,
	/**< 2-point output	*/
	ImproSenslvs_E_IM_PRO_SLVS_OUT_FORMAT_2POINT,
	/**< 4-point output	*/
	ImproSenslvs_E_IM_PRO_SLVS_OUT_FORMAT_4POINT,
	/**< 8-point output	*/
	ImproSenslvs_E_IM_PRO_SLVS_OUT_FORMAT_8POINT,
	/**< output format Max value	*/
	ImproSenslvs_E_IM_PRO_SLVS_OUT_FORMAT_MAX
} EimproSlvsOutFormat;

/** SLVS input port select for Lane swap.
*/
typedef enum {
	/**< L0IN	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_0 = 0,
	/**< L1IN	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_1,
	/**< L2IN	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_2,
	/**< L3IN	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_3,
	/**< L4IN	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_4,
	/**< L5IN	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_5,
	/**< L6IN	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_6,
	/**< L7IN	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_7,
	/**< input port select Max value	*/
	ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_MAX
} EimproSlvsLaneSwapInputPortSel;

/** SLVS trimming Enable/Disable
*/
typedef enum {
	/**< Disable	*/
	ImproSenslvs_E_IM_PRO_SLVS_TRIM_DIS = 0,
	/**< Enable		*/
	ImproSenslvs_E_IM_PRO_SLVS_TRIM_EN
} EimproSlvsTrimEnable;

/** SLVS status of indicate whether Embedded Data is detected in the frame.
*/
typedef enum {
	/**< no Embedded Data.	*/
	ImproSenslvs_E_IM_PRO_SLVS_STATUS_EBD_NO_EBD = 0,
	/**< Embedded Data is detected.	*/
	ImproSenslvs_E_IM_PRO_SLVS_STATUS_EBD_DETECTED,
} EimproSlvsStatusEbd;

/** Input differential data value inversion setting. */
typedef struct {
	/**< Lane0 */
	EimproSlvsInputDataInversion		lane0:1;
	/**< Lane1 */
	EimproSlvsInputDataInversion		lane1:1;
	/**< Lane2 */
	EimproSlvsInputDataInversion		lane2:1;
	/**< Lane3 */
	EimproSlvsInputDataInversion		lane3:1;
	/**< Lane4 */
	EimproSlvsInputDataInversion		lane4:1;
	/**< Lane5 */
	EimproSlvsInputDataInversion		lane5:1;
	/**< Lane6 */
	EimproSlvsInputDataInversion		lane6:1;
	/**< Lane7 */
	EimproSlvsInputDataInversion		lane7:1;
} TimproSlvsInputDataInversionSel;


/** Control the ICPCODE port of PMA macro (common to each PMA)
 * and the REFSEL port of the termination resistor adjustment circuit.<br>
	*Caution* Changing the setting value in normal use is prohibited. */
typedef struct {
	/**< Optional parameter setting enabled.[0: disabled  other: enabled]<br>
	If this parameter set disabled, H/W initial value applied to PHYCR0@@REFSEL and PHYCR0@@ICPCODE. */
	UCHAR				enabled;
	/**< Termination resistor adjustment circuit mode select. PHYCR0@@REFSEL */
	UCHAR				refsel;
	/**< Charge pump control code PHYCR0@@ICPCODE */
	UCHAR				icpcode;
} TimproSlvsPmaInitOpt;


/** Physical Media Attachment initialization setting. */
typedef struct {
	/**< input differential data value inversion setting. PHYCR1@@INVDATA */
	TimproSlvsInputDataInversionSel	invertSel;
	/**< Multiplication factor control setting. PHYCR1@@IFVDCNT */
	EimproSlvsMultiplicationFactor		multiplicationFactor;
	/**< Optional setting parameter for PMA macro. */
	TimproSlvsPmaInitOpt						optInitParam;
} TimproSlvsPmaInit;

/** Physical Media Attachment Power Down parameters
*/
typedef struct {
	/**< Lane0 Power Down state. PHYCR2@@IRXPDX0	*/
	EimproSlvsPdState			lane0PdState;
	/**< Lane1 Power Down state. PHYCR2@@IRXPDX1	*/
	EimproSlvsPdState			lane1PdState;
	/**< Lane2 Power Down state. PHYCR2@@IRXPDX2	*/
	EimproSlvsPdState			lane2PdState;
	/**< Lane3 Power Down state. PHYCR2@@IRXPDX3	*/
	EimproSlvsPdState			lane3PdState;
	/**< Lane4 Power Down state. PHYCR2@@IRXPDX4	*/
	EimproSlvsPdState			lane4PdState;
	/**< Lane5 Power Down state. PHYCR2@@IRXPDX5	*/
	EimproSlvsPdState			lane5PdState;
	/**< Lane6 Power Down state. PHYCR2@@IRXPDX6	*/
	EimproSlvsPdState			lane6PdState;
	/**< Lane7 Power Down state. PHYCR2@@IRXPDX7	*/
	EimproSlvsPdState			lane7PdState;
} TimproSlvsPmaPd;

/** SLVS-EC Control Information
*/
typedef struct {
	/**< External RAM(Line Buffer) Power Down state.  RAMPD@@RAMPDX	*/
	EimproSlvsPdState			ramPdState;
	/**< Control the VDOUT output when frame stop is set. TRGR@@VDEN	*/
	EimproSlvsVdoutCtrl		vdoutCtrl;
	/**< ECC option / CRC Option of payload. CFGR0@@ECCCRC	*/
	EimproSlvsEcccrcOpt		ecccrcOpt;
	/**< Expected value when Line Number Error occurred. MMODE@@LNMAXCLP	*/
	EimproSlvsExpectVal		expectVal;
} TimproSlvsCtrl;

/** SLVS-EC Common Configuration parameters
*/
typedef struct {
	/**< transfer count of Standby Code in Standby Sequence in the range of 18~255. */
	UCHAR									StandbyLength;
	/**< Symbol code type (D/K) following Comma Symbol inside the Standby Code. */
	EimproSlvsSymbolType		StandbySymbolType;
	/**< Symbol following Comma Symbol inside the Standby Code. */
	UCHAR									StandbySymbol;
	/**< Deskew Interval (Idle Code continuous transfer count between
	 *  Deskew Code in Training Sequence) in the range of 20~255. */
	UCHAR									DeskewInterval;
	/**< Deskew Length (transfer count of Deskew Code in Training Sequence) in the range of 3~255. */
	UCHAR									DeskewLength;
	/**< Code type (D/K) of the Symbol following Comma Symbol inside the Deskew Code. */
	EimproSlvsSymbolType		DeskewSymbolType;
	/**< Symbol following Comma Symbol inside the Deskew Code. */
	UCHAR									DeskewSymbol;
	/**< Code type (D/K) of the Symbol(2nd) of the Idle Code. */
	EimproSlvsSymbolType		IdleSymbolType1;
	/**< Symbol(2nd) of idle code.  */
	UCHAR									IdleSymbol1;
	/**< Code type (D/K) of the Symbol(1st) of the Idle Code. */
	EimproSlvsSymbolType		IdleSymbolType0;
	/**< Symbol(1st) of Idle Code */
	UCHAR									IdleSymbol0;
	/**< Code type (D/K) of the Symbol (4th) of the Idle Code. */
	EimproSlvsSymbolType		IdleSymbolType3;
	/**< Symbol(4th) of idle code. */
	UCHAR									IdleSymbol3;
	/**< Code type (D/K) of the Symbol (3rd) of the Idle Code. */
	EimproSlvsSymbolType		IdleSymbolType2;
	/**< Symbol (3rd) of Idle Code */
	UCHAR									IdleSymbol2;
} TimproSlvsCommonCfg;

/** Valid Lane select information */
typedef struct {
	/**< Lane0 */
	EimproSlvsLaneEnable		lane0:1;
	/**< Lane1 */
	EimproSlvsLaneEnable		lane1:1;
	/**< Lane2 */
	EimproSlvsLaneEnable		lane2:1;
	/**< Lane3 */
	EimproSlvsLaneEnable		lane3:1;
	/**< Lane4 */
	EimproSlvsLaneEnable		lane4:1;
	/**< Lane5 */
	EimproSlvsLaneEnable		lane5:1;
	/**< Lane6 */
	EimproSlvsLaneEnable		lane6:1;
	/**< Lane7 */
	EimproSlvsLaneEnable		lane7:1;
	/**< Not used */
	ULONG								dummy:24;
} TimproSlvsValidLaneSel;

/** Mode Configuration parameters
*/
typedef struct {
	/**< SLVS number of bits per pixel. CFGR0@@PixelBit */
	EimproSlvsPixelBit								pixelbit;
	/**< SLVS number of valid Lanes. CFGR0@@LaneNum */
	EimproSlvsLaneNum							lanenum;
	/**< SLVS number of bits per pixel(4 pixel boundary). CFGR1@@LineLength */
	USHORT												linelength;
	/**< SLVS output format of the image data interface. OUTMD@@OUTMD */
	EimproSlvsOutFormat						outputFormat;
	/**< SLVS swap lane configuration. LSWAP@@LxOUT@image html im_pro_slvs_swap.png	*/
	EimproSlvsLaneSwapInputPortSel	swapLane[ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_MAX	];
	/**< SLVS valid Lane select. VLANE@@LANEx */
	TimproSlvsValidLaneSel					valid_lane;

} TimproSlvsModeCfg;

/** SLVS-EC Mode Trimming parameters
*/
typedef struct {
	/**< SLVS trimming mode enabled. OUTMD@@TRMG */
	EimproSlvsTrimEnable		enabled;
	/**< SLVS trimming start X position(16 pixel boundary). HSADD@@HSADD */
	USHORT								startX;
	/**< SLVS trimming width(16 pixel boundary). HSIZE@@HSIZE */
	USHORT								width;
} TimproSlvsTrimCfg;

/** SLVS-EC status
*/
typedef struct {
	/**< indicate whether Embedded Data is detected in the frame. EBDST@@EBD */
	EimproSlvsStatusEbd			embeddedDataDetect;
	/**< indicate the number of lines in which Embedded Data is stored. EBDST@@LNUM */
	USHORT								ebdStoredLineNum;
	/**< indicate the expected value of the number of lines in which discontinuity is detected. LNEST@@EXPLN */
	USHORT								expectValueDiscontinuity;
	/**< indicate the number of lines in which discontinuity is detected. LNEST@@DETLN */
	USHORT								lineNumDiscontinuity;
} TimproSlvsStatus;

/*类型定义区域*/
typedef struct _ImproSenslvs							ImproSenslvs;
typedef struct _ImproSenslvsPrivate				ImproSenslvsPrivate;


/*对象结构体区域*/
struct _ImproSenslvs
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_senslvs_get_type(void);
ImproSenslvs*		impro_senslvs_new();
/**
Software reset of SLVS-EC RX macro(excluding PMA, termination resistor adjustment circuit and CNT block).
@param[in]	streamType : stream type of SLVS
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_senslvs_sr( E_IM_PRO_SLVS_STREAM_TYPE streamType );
/**
Update of the SLVS-EC configuration parameters.
@param[in]	streamType : stream type of SLVS
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_senslvs_update_cfg( E_IM_PRO_SLVS_STREAM_TYPE streamType );
/**
Software reset release of SLVS-EC.
@param[in]	streamType : stream type of SLVS
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_senslvs_sr_rlease( E_IM_PRO_SLVS_STREAM_TYPE streamType );
/**
Physical Media Attachment initialization.
@param[in]	pmaInit : PMA initialization parameters.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
extern	INT32			impro_senslvs_pma_init( TimproSlvsPmaInit* pmaInit );
/**
Physical Media Attachment Power Down control.
@param[in]	pmaPd : PMA Power Down control parameters.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
extern	INT32			impro_senslvs_pma_power_down( TimproSlvsPmaPd* pmaPd );
/**
Physical Media Attachment PLL Power Down control.
@param[in]	pdState : PMA PLL Power Down control parameters.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
extern	INT32			impro_senslvs_pma_pll_power_down( EimproSlvsPdState pdState );
/**
SLVS-EC Common Configuration.
@param[in]	commonCfg : Common configuration parameters.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
extern	INT32			impro_senslvs_common_cfg( TimproSlvsCommonCfg* commonCfg );
/**
SLVS-EC Configuration.
@param[in]	streamType : stream type of SLVS
@param[in]	slvsCtrl : configuration parameters for each stream.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
extern	INT32			impro_senslvs_ctrl( E_IM_PRO_SLVS_STREAM_TYPE streamType, TimproSlvsCtrl* slvsCtrl );
/**
SLVS-EC Mode Configuration.
@param[in]	streamType : stream type of SLVS
@param[in]	modeCtrl : mode configuration parameters for each stream.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
extern	INT32			impro_senslvs_mode_cfg( E_IM_PRO_SLVS_STREAM_TYPE streamType, TimproSlvsModeCfg* modeCtrl );
/**
SLVS-EC Trimming Configuration.
@param[in]	streamType : stream type of SLVS
@param[in]	trimCtrl : trimming configuration parameters for each stream.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_NG					: Processing NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
extern	INT32			impro_senslvs_trim_cfg( E_IM_PRO_SLVS_STREAM_TYPE streamType, TimproSlvsTrimCfg* trimCtrl );
/**
Get SLVS-EC status.
@param[in]	streamType : stream type of SLVS
@param[out]	status : status parameter pointer.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
extern	INT32			impro_senslvs_get_status( E_IM_PRO_SLVS_STREAM_TYPE streamType, TimproSlvsStatus* status );
/**
SLVS-EC macro start.
@param[in]	streamType : stream type of SLVS
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
extern	INT32			impro_senslvs_status( E_IM_PRO_SLVS_STREAM_TYPE streamType );
/**
Stop SLVS-EC information
@param[in]	streamType : stream type of SLVS
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Parameter invalid
*/
extern	INT32			impro_senslvs_stop( E_IM_PRO_SLVS_STREAM_TYPE streamType, UCHAR force );
/**
wait end of SLVS-EC macro.
@param[in]		waiptn   : waiting end cause. (bit field)
						<ul><li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_FSI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_FSO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_FEI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_FEO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_RDY_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_STBY_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_FSI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_FSO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_FEI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_FEO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_RDY_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_STBY_WAITEND_FLG</ul>
@param[in]		tmout    : timeout.
@param[out]		p_flgptn : end cause. (bit field)
						<ul><li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_FSI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_FSO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_FEI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_FEO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_RDY_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_A_INTST_STBY_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_FSI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_FSO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_FEI_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_FEO_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_RDY_WAITEND_FLG
							<li>@ref D_IM_PRO_SLVS_STREAM_B_INTST_STBY_WAITEND_FLG</ul>
@retval			D_DDIM_OK                  : SLVS-EC normal end. and set end cause to p_flgptn.
@retval			D_IM_PRO_INPUT_PARAM_ERROR : parameter error.
@retval			ImproSenslvs_D_IM_PRO_TIMEOUT     : wait timeout.
@remarks		This API uses DDIM_User_Clr_Flg().
@remarks		This API uses DDIM_User_Twai_Flg().
*/
extern	INT32			impro_senslvs_wait_end( DDIM_USER_FLGPTN* const p_flgptn, const DDIM_USER_FLGPTN waiptn, const DDIM_USER_TMO tmout );










#endif /* __IMPRO_SENSLVS_H__ */

