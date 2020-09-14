/*
 *camera.h
 *
 *  Created on: 2020年6月2日
 *      Author: sns
 */

#ifndef __IM_MIPI_H__
#define __IM_MIPI_H__

#include "driver_common.h"
#include <klib.h>

#define IM_TYPE_MIPI	(im_mipi_get_type())
#define IM_MIPI(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImMipi))
#define IM_IS_MIPI(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, ImMipi))

#define ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR	(D_IM_MIPI | D_DDIM_INPUT_PARAM_ERROR)	/**< Input Parameter Error */
#define ImMipi_D_IM_MIPI_NO_RECEIVE		(D_IM_MIPI | D_DDIM_NO_RECEIVE)			/**< No receive */
#define ImMipi_D_IM_MIPI_TIMEOUT			(D_IM_MIPI | D_DDIM_TIMEOUT)			/**< Time out */
#define ImMipi_D_IM_MIPI_NG				(D_IM_MIPI | D_DDIM_SYSTEM_ERROR)		/**< System error */

// General-purpose definition of register value (Effectiveness selection)
#define ImMipi_D_IM_MIPI_ENABLE_OFF						(0)		/**< OFF	*/
#define ImMipi_D_IM_MIPI_ENABLE_ON							(1)		/**< ON		*/

// DPI color coding.
#define ImMipi_D_IM_MIPI_COLOR_CODING_16BIT_CONFIG1		(0)				/**< 16-bit configuration 1				*/
#define ImMipi_D_IM_MIPI_COLOR_CODING_16BIT_CONFIG2		(1)				/**< 16-bit configuration 2				*/
#define ImMipi_D_IM_MIPI_COLOR_CODING_16BIT_CONFIG3		(2)				/**< 16-bit configuration 3				*/
#define ImMipi_D_IM_MIPI_COLOR_CODING_18BIT_CONFIG1		(3)				/**< 18-bit configuration 1				*/
#define ImMipi_D_IM_MIPI_COLOR_CODING_18BIT_CONFIG2		(4)				/**< 18-bit configuration 2				*/
#define ImMipi_D_IM_MIPI_COLOR_CODING_24BIT				(5)				/**< 24-bit								*/
#define ImMipi_D_IM_MIPI_COLOR_CODING_20BIT_YCC422_LP		(6)				/**< 20-bit YCbCr4:2:2 loosely packed	*/
#define ImMipi_D_IM_MIPI_COLOR_CODING_24BIT_YCC422			(7)				/**< 24-bit YCbCr4:2:2					*/
#define ImMipi_D_IM_MIPI_COLOR_CODING_16BIT_YCC422			(8)				/**< 16-bit YCbCr4:2:2					*/
#define ImMipi_D_IM_MIPI_COLOR_CODING_30BIT				(9)				/**< 30-bit								*/
#define ImMipi_D_IM_MIPI_COLOR_CODING_36BIT				(10)			/**< 36-bit								*/
#define ImMipi_D_IM_MIPI_COLOR_CODING_12BIT_YCC420			(11)			/**< 12-bit YCbCr4:2:0					*/

// Video mode transmission type.
#define ImMipi_D_IM_MIPI_VID_MODE_TYPE_NON_BURST_SYNC_PULSES	(0)			/**< 00 : Non-Burst with sync pulses	*/
#define ImMipi_D_IM_MIPI_VID_MODE_TYPE_NON_BURST_SYNC_EVENTS	(1)			/**< 01 : Non-Burst with sync events	*/
#define ImMipi_D_IM_MIPI_VID_MODE_TYPE_BURST					(2)			/**< 10 or 11 : Burst mode				*/

// Number of Pakcets.
#define ImMipi_D_IM_MIPI_PACKET_NUM_MAX					(16)			/**< Max number							*/

/*----------------------------------------------------------------------*/
typedef struct _ImMipi ImMipi;

typedef enum{
	ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_1 = 0,					/**< One data lane    (lane 0)					*/
	ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_2,						/**< Two data lanes   (lanes 0 and 1)			*/
	ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_3,						/**< Three data lanes (lanes 0, 1, and 2)		*/
	ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_4						/**< Four data lanes  (lanes 0, 1, 2, and 3)	*/
} EImMipiActiveDataLane;

/** Interrupt type */
typedef enum{
	ImMipi_E_IM_MIPI_INT_TYPE_TO_HS_TX			= 0,			/**< Timeout.						*/
	ImMipi_E_IM_MIPI_INT_TYPE_DPI_PLD_WR_ERR,					/**< DPI payload write error.		*/
	ImMipi_E_IM_MIPI_INT_TYPE_GEN_CMD_WR_ERR,					/**< Generic command write error.	*/
	ImMipi_E_IM_MIPI_INT_TYPE_GEN_PLD_WR_ERR,					/**< Generic payload write error.	*/
	ImMipi_E_IM_MIPI_INT_TYPE_GEN_PLD_SEND_ERR,				/**< Generic payload send error.	*/
	ImMipi_E_IM_MIPI_INT_TYPE_MAX								/**< Interrupt type maximum value.	*/
} EImMipiIntType;

/** PHY_RSTZ Register - phy_shutdownz */
typedef enum{
	ImMipi_E_IM_MIPI_PHY_SHUTDOWNZ_POWER_DOWN = 0,				/**< Power-down state	*/
	ImMipi_E_IM_MIPI_PHY_SHUTDOWNZ_POWER_UP					/**< Power-up state		*/
} EImMipiPhyShutdownz;

/** PWR_UP Register - shutdownz */
typedef enum{
	ImMipi_E_IM_MIPI_SHUTDOWNZ_RESET = 0,						/**< Reset		*/
	ImMipi_E_IM_MIPI_SHUTDOWNZ_POWER_UP						/**< Power-up	*/
} EImMipiShutdownz;

/** modeCfg Register */
typedef enum{
	ImMipi_E_IM_MIPI_MODE_CFG_VIDEO = 0,						/**< Video mode		*/
	ImMipi_E_IM_MIPI_MODE_CFG_CMD,								/**< Command mode	*/
} EImMipiModeCfg;

/*----------------------------------------------------------------------*/
/* Structure  															*/
/*----------------------------------------------------------------------*/
/** clkmgrCfg Register structure */
typedef union {
	ULONG		word;				/**< All bits */
	struct {
		ULONG	txEscClkDivision	:8;		/**< The division factor for the TX Escape clock source.<br>
												 Value range : 0~255.<br>
												 The value 0 and 1 stop the TX_ESC clock generation.		*/
		ULONG	toClkDivision		:8;		/**< The division factor the Time Out clock.<br>
												 Value range : 0~255.										*/
		ULONG						:16;	/**< Reserve													*/
	} bit;	/**< Bit field */
} UImMipiClkmgrCfg;

/** DPI_CFG_POL Register structure */
typedef union {
	ULONG		word;				/**< All bits */
	struct {
		ULONG	dataenActiveLow	:1;		/**< Data enable pin.<br>
												 Value 1:active, 0:inactive		*/
		ULONG	vsyncActiveLow	:1;		/**< Vertical synchronism pin.<br>
												 Value 1:active, 0:inactive		*/
		ULONG	hsyncActiveLow	:1;		/**< Horizontal synchronism pin.<br>
												 Value 1:active, 0:inactive		*/
		ULONG	shutdActiveLow	:1;		/**< Shutdown pin.<br>
												 Value 1:active, 0:inactive		*/
		ULONG	colormAcviteLow	:1;		/**< Color mode pin.<br>
												 Value 1:active, 0:inactive		*/
		ULONG						:27;	/**< Reserve				*/
	} bit;	/**< Bit field */
} UImMipiDpiCfgPol;

/** dpiLpCmdTim Register structure */
typedef union {
	ULONG		word;				/**< All bits */
	struct {
		ULONG	invactLpcmdTime	:8;		/**< It defines the size of the largest packet(VACT).<br>
												 Value range : 0~255.											*/
		ULONG						:8;		/**< Reserve														*/
		ULONG	outvactLpcmdTime	:8;		/**< It defines the size of the largest packet(VSA,VBP,VFP).<br>
												 Value range : 0~255.											*/
		ULONG						:8;		/**< Reserve														*/
	} bit;	/**< Bit field */
} UImMipiDplLpCmdTim;

/** vidModeCfg Register structure */
typedef union {
	ULONG		word;				/**< All bits */
	struct {
		ULONG	vidModeType	:2;		/**< Video mode transmission type.<br>
											 <ul><li>@ref ImMipi_D_IM_MIPI_VID_MODE_TYPE_NON_BURST_SYNC_PULSES
												 <li>@ref ImMipi_D_IM_MIPI_VID_MODE_TYPE_NON_BURST_SYNC_EVENTS
												 <li>@ref ImMipi_D_IM_MIPI_VID_MODE_TYPE_BURST</ul>				*/
		ULONG					:6;		/**< Reserve														*/
		ULONG	lpVsaEn		:1;		/**< Return to low-power inside the VSA period.<br>
											 Value 1:enable, 0:disable										*/
		ULONG	lpVbpEn		:1;		/**< Return to low-power inside the VBP period.<br>
											 Value 1:enable, 0:disable										*/
		ULONG	lpVfpEn		:1;		/**< Return to low-power inside the VFP period.<br>
											 Value 1:enable, 0:disable										*/
		ULONG	lpVactEn		:1;		/**< Return to low-power inside the VACT period.<br>
											 Value 1:enable, 0:disable										*/
		ULONG	lpHbpEn		:1;		/**< Return to low-power inside the HBP period.<br>
											 Value 1:enable, 0:disable										*/
		ULONG	lpHfpEn		:1;		/**< Return to low-power inside the HFP period.<br>
											 Value 1:enable, 0:disable										*/
		ULONG					:1;		/**< Reserve														*/
		ULONG	lpCmdEn		:1;		/**< Command transmission only in low-power mode.<br>
											 Value 1:enable, 0:disable										*/
		ULONG	vpgEn			:1;		/**< Video mode pattern generator.<br>
											 Value 1:enable, 0:disable										*/
		ULONG					:3;		/**< Reserve														*/
		ULONG	vpgMode        :1;		/**< Pattern select.<br>
											 Value 1:BER pattern, 0:Color bar.								*/
		ULONG					:3;		/**< Reserve														*/
		ULONG	vpgOrientation :1;		/**< Color bar orientation.<br>
											 Value 1:Horizontal mode, 0:Vertical mode.						*/
		ULONG					:7;		/**< Reserve														*/
	} bit;	/**< Bit field */
} UImMipiVidModeCfg;

/** cmdModeCfg Register structure */
typedef union {
	ULONG		word;				/**< All bits */
	struct {
		ULONG					:8;		/**< Reserve																		*/
		ULONG	genSw0PTx    :1;		/**< the Generic short write packet zero paramter command transmission type.<br>
											 Value 1:Low-power, 0:High-speed												*/
		ULONG	genSw1PTx    :1;		/**< the Generic short write packet one paramter command transmission type.<br>
											 Value 1:Low-power, 0:High-speed												*/
		ULONG	genSw2PTx    :1;		/**< the Generic short write packet two paramter command transmission type.<br>
											 Value 1:Low-power, 0:High-speed												*/
		ULONG					:3;		/**< Reserve																		*/
		ULONG	genLwTx       :1;		/**< the Generic long write packet command transmission type.<br>
											 Value 1:Low-power, 0:High-speed												*/
		ULONG					:1;		/**< Reserve																		*/
		ULONG	dcsSw0PTx    :1;		/**< the DCS short write packet zero paramter command transmission type.<br>
											 Value 1:Low-power, 0:High-speed												*/
		ULONG	dcsSw1PTx    :1;		/**< the DCS short write packet one paramter command transmission type.<br>
											 Value 1:Low-power, 0:High-speed												*/
		ULONG					:1;		/**< Reserve																		*/
		ULONG	dcsLwTx       :1;		/**< the DCS long write packet command transmission type.<br>
											 Value 1:Low-power, 0:High-speed												*/
		ULONG					:12;	/**< Reserve																		*/
	} bit;	/**< Bit field */
} UImMipiCmdModeCfg;

/** GEN_HDR Register structure */
typedef union {
	ULONG		word;				/**< All bits */
	struct {
		ULONG	genDt				:6;		/**< Packet data type. Value range : 0~63.		*/
		ULONG	genVc				:2;		/**< Virtual channel ID. Value range : 0~3.		*/
		ULONG	genWcLsbyte		:8;		/**< header packet's word count(LSB).<br>
												 Value range : 0~255.						*/
		ULONG	genWcMsbyte		:8;		/**< header packet's word count(MSB).<br>
												 Value range : 0~255.						*/
		ULONG						:8;		/**< Reserve									*/
	} bit;	/**< Bit field */
} UImMipiGenHdr;

/** phyTmrLpclkCfg Register structure */
typedef union {
	ULONG		word;				/**< All bits */
	struct {
		ULONG	phyClkhs2lpTime	:8;		/**< Time to switch from low-power to high-speed consumption.<br>
												 Value range : 0~255.											*/
		ULONG						:8;		/**< Reserve														*/
		ULONG	phyClklp2hsTime	:8;		/**< Time to switch from high-speed to low-power consumption.<br>
												 Value range : 0~255.											*/
		ULONG						:8;		/**< Reserve														*/
	} bit;	/**< Bit field */
} UImMipiPhyTmrLpclkCfg;

/** phyTmrCfg Register structure */
typedef union {
	ULONG		word;				/**< All bits */
	struct {
		ULONG						:16;	/**< Reserve														*/
		ULONG	phyLp2hsTime		:8;		/**< Time to switch from high-speed to low-power consumption.<br>
												 Value range : 0~255.											*/
		ULONG	phyHs2lpTime		:8;		/**< Time to switch from low-power to high-speed consumption.<br>
												 Value range : 0~255.											*/
	} bit;	/**< Bit field */
} UImMipiPhyTmrCfg;

/** INT_MSK1 Register structure */
typedef union {
	ULONG		word;				/**< All bits */
	struct {
		ULONG	toHsTx			:1;		/**< Timeout.<br>
												 Value 0:Unmask, 1:Mask.			*/
		ULONG						:6;		/**< Reserve							*/
		ULONG	dpiPldWrErr		:1;		/**< DPI payload write error.<br>
												 Value 0:Unmask, 1:Mask.			*/
		ULONG	genCmdWrErr		:1;		/**< Generic command write error.<br>
												 Value 0:Unmask, 1:Mask.			*/
		ULONG	genPldWrErr		:1;		/**< Generic payload write error.<br>
												 Value 0:Unmask, 1:Mask.			*/
		ULONG	genPldSendErr	:1;		/**< Generic payload send error.<br>
												 Value 0:Unmask, 1:Mask.			*/
		ULONG						:21;	/**< Reserve							*/
	} bit;	/**< Bit field */
} UImMipiIntMsk1;

/** PHY_SETUP_CL/PHY_SETUP_DL Register structure */
typedef union {
	ULONG		word;				/**< All bits */
	struct {
		ULONG	sapTlpx			:8;		/**< TLPX Setup(Clock Lane) / TLPX Setup(Data Lane).<br>
												 Value range : 0~255.												*/
		ULONG	sapHs0				:8;		/**< Tclk-ZERO Setup(Clock Lane) / THS-ZERO Setup(Data Lane).<br>
												 Value range : 0~255.												*/
		ULONG	sapTrAIL			:8;		/**< TCLK-TRAIL Setup(Clock Lane) / THS-TRAIL Setup(Data Lane).<br>
												 Value range : 0~255.												*/
		ULONG	sapPre				:8;		/**< TCLK-PREPARE Setup(Clock Lane) / THS-PREPARE Setup(Data Lane).<br>
												 Value range : 0~255.												*/
	} bit;	/**< Bit field */
} UImMipiPhySetup;

/**
Lane data.<br>
*/
typedef struct {
	UImMipiPhySetup				clockLane;			/**< PHY_SETUP_CL : D-PHY setup register for Clock Lane.			*/
	UImMipiPhySetup				dataLane;			/**< PHY_SETUP_DL : D-PHY setup register for Data Lane.				*/
	UCHAR							tclkpPost;			/**< PHY_TCLKPOST.TCLK_POST : D-PHY setup register for Tclkp-post.<br>
															 Value range : 0~63.											*/
} TImMipiDpiLaneInfo;

/**
DPI Resolution data.<br>
*/
typedef struct {
	EImMipiActiveDataLane		lane;				/**< PHY_IF_CFG : data lane.<br>
															 <ul><li>@ref ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_1
																 <li>@ref ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_2
																 <li>@ref ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_3
																 <li>@ref ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_4</ul>					*/
	UCHAR							vcid;				/**< DPI_VCID : virtual channel.<br>
															 Value range:0~3<br>											*/
	UCHAR							colorCoding;		/**< DPI_COLOR_CODING.dpi_color_coding : color coding.<br>
															 <ul><li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_16BIT_CONFIG1
																 <li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_16BIT_CONFIG2
																 <li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_16BIT_CONFIG3
																 <li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_18BIT_CONFIG1
																 <li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_18BIT_CONFIG2
																 <li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_24BIT
																 <li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_20BIT_YCC422_LP
																 <li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_24BIT_YCC422
																 <li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_16BIT_YCC422
																 <li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_30BIT
																 <li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_36BIT
																 <li>@ref ImMipi_D_IM_MIPI_COLOR_CODING_12BIT_YCC420</ul>			*/
	BOOL							loosely18En;		/**< DPI_COLOR_CODING.loosely18En : loosely enable.<br>
															 Value 1:activate, 0:inactive									*/
	UImMipiDpiCfgPol			cfgPol;			/**< DPI_CFG_POL : Polarity of the DPI signals.						*/
	EImMipiModeCfg				modeCfg;			/**< modeCfg : the mode of operation.<br>
															 <ul><li>@ref ImMipi_E_IM_MIPI_MODE_CFG_VIDEO
																 <li>@ref ImMipi_E_IM_MIPI_MODE_CFG_CMD</ul>						*/
	UImMipiVidModeCfg			vidModeCfg;		/**< vidModeCfg : Several aspects of the Video mode operation		*/
	USHORT							vidPktSize;		/**< vidPktSize : Video packet size.<br>
															 Value range:1~16383.											*/
	USHORT							vidNumChunks;		/**< vidNumChunks : Number of chunks to use.<br>
															 Value range:0~16383.											*/
	USHORT							vidNullSize;		/**< vidNullSize : Size of null packets.<br>
															 Value range:0~16383.											*/
	USHORT							vidHlineTime;		/**< vidHlineTime : Overall time for each video line.<br>
															 Value range:1~32767.											*/
    USHORT							vidHsaTime;		/**< vidHsaTime : Video HSA time.<br>
															 Value range:1~4095.											*/
	USHORT							vidHbpTime;		/**< vidHbpTime : Video HBP time.<br>
															 Value range:1~4095.											*/
	USHORT							vidVsaLines;		/**< vidVsaLines : VSA period.<br>
															 Value range:1~1023.											*/
    USHORT							vidVbpLines;		/**< vidVbpLines : VBP period.<br>
															 Value range:1~1023.											*/
	USHORT							vidVfpLines;		/**< vidVfpLines : VFP period.<br>
															 Value range:1~1023.											*/
	USHORT							vidVactiveLines;	/**< vidVactiveLines : Vertical resolution of the video.<br>
															 Value range:1~16383.											*/
	UImMipiCmdModeCfg			cmdModeCfg;		/**< cmdModeCfg : Several aspects of the command mode operation	*/
} TImMipiDplResolution;

/**
Transmission configuration data.<br>
*/
typedef struct {
	UImMipiClkmgrCfg			clkmgrCfg;			/**< clkmgrCfg : Polarity of the DPI signals.					*/
	UImMipiDplLpCmdTim		dpiLpCmdTim;		/**< dpiLpCmdTim : Several aspects of the Video mode operation	*/
	USHORT							timerCount;		/**< TO_CNT_CFG.hstx_to_cnt : Timer counter.<br>
															 Value range:0~65535.										*/
	UImMipiPhyTmrLpclkCfg		phyTmrLpclkCfg;	/**< phyTmrLpclkCfg : High-speed and low-power consumption to switch time.		*/
	UImMipiPhyTmrCfg			phyTmrCfg;		/**< phyTmrCfg : High-speed and low-power consumption to switch time.		*/
} TImMipiTransConfig;

struct _ImMipi {
	KObject parent;
};

#ifdef __cplusplus
extern "C" {
#endif

KConstType 		    im_mipi_get_type(void);
ImMipi*		           im_mipi_new(void);

VOID im_mipi_init(ImMipi*self,EImMipiActiveDataLane lane);

/**
 * @brief	LPCLK control.
 * @param[in]	lpclk		LPCLK control state.<br>
 * @retval	VOID.
 */
VOID im_mipi_lpclk_ctrl(ImMipi*self,UCHAR lpclk);

/**
 * @brief	Power-up/down control.
 * @param[in]	power		Power-up/down state.<br>
 * 							<ul><li>@ref ImMipi_E_IM_MIPI_PHY_SHUTDOWNZ_POWER_DOWN
 * 								<li>@ref ImMipi_E_IM_MIPI_PHY_SHUTDOWNZ_POWER_UP</ul>
 * @param[in]	reset		Reset/Power-up.<br>
 * 							<ul><li>@ref ImMipi_E_IM_MIPI_SHUTDOWNZ_RESET
 * 								<li>@ref ImMipi_E_IM_MIPI_SHUTDOWNZ_POWER_UP</ul>
 * @retval	VOID.
 */
VOID im_mipi_power_ctrl(ImMipi*self,EImMipiPhyShutdownz power, EImMipiShutdownz reset);

/**
 * @brief	Enter ULPS on both clock lane and data lane.
 * @retval	D_DDIM_OK		success.
 * @retval	ImMipi_D_IM_MIPI_NG	status NG.
 * @remarks	This API uses DDIM_User_Dly_Tsk().
 */
INT32 im_mipi_enter_ulps(ImMipi*self);

/**
 * @brief	Exit ULPS on both clock lane and data lane.
 * @retval	D_DDIM_OK		success.
 * @retval	ImMipi_D_IM_MIPI_NG	status NG.
 * @remarks	This API uses DDIM_User_Dly_Tsk().
 */
INT32 im_mipi_exit_ulps(ImMipi*self);

/**
 * @brief	Set clock lane / data lane / TCLK POST.
 * @param[in]	lane_info		Configure the lane.
 * @retval	D_DDIM_OK					success.
 * @retval	ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR	Input parameter error.
 */
INT32 im_mipi_set_lane_info(TImMipiDpiLaneInfo const *const lane_info);

/**
 * @brief	Get clock lane / data lane / TCLK POST.
 * @param[out]	lane_info		Configure the lane.
 * @retval	D_DDIM_OK					success.
 * @retval	ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR	Input parameter error.
 */
INT32 im_mipi_get_lane_info(TImMipiDpiLaneInfo *const lane_info);

/**
 * @brief	Set DPI Resolution data.
 * @param[in]	dpi			DPI Resolution data.
 * @retval	D_DDIM_OK					success.
 * @retval	ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
INT32 im_mipi_set_dpi_resolution(TImMipiDplResolution const *const dpi);

/**
 * @brief	Get DPI Resolution data.
 * @param[out]	dpi			TDPI Resolution data.
 * @retval	D_DDIM_OK					success.
 * @retval	ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
INT32 im_mipi_get_dpi_resolution(TImMipiDplResolution *const dpi);

/**
 * @brief	Updating the DPI Configuration.
 * @retval	D_DDIM_OK			success.
 * @retval	ImMipi_D_IM_MIPI_NG		NG.
 */
INT32 im_mipi_update_dpi(VOID);

/**
 * @brief	Set Transmission Configuration.
 * @param[in]	config			Transmission configuration data.
 * @retval	D_DDIM_OK					success.
 * @retval	ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
INT32 im_mipi_set_transmission_configutation(TImMipiTransConfig const *const config);

/**
 * @brief	Get Transmission Configuration.
 * @param[out]	config			Transmission configuration data.
 * @retval	D_DDIM_OK					success.
 * @retval	ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
INT32 im_mipi_get_transmission_configutation(TImMipiTransConfig *const config);

/**
 * @brief	Paket Transmission.
 * @param[in]	header_num		header  Number. Value range : 1~16.
 * @param[in]	payload_num		payload Number. Value range : 1~14.
 * @param[in]	header			Packet header.
 * @param[in]	payload			Payload Data.<br>
 * 								Value range : 0x00000000~0xFFFFFFFF.
 * @retval	D_DDIM_OK					success.
 * @retval	ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
INT32 im_mipi_packet_transmission(UCHAR header_num, UCHAR payload_num, const UImMipiGenHdr header[ImMipi_D_IM_MIPI_PACKET_NUM_MAX], const ULONG payload[ImMipi_D_IM_MIPI_PACKET_NUM_MAX]);

/**
 * @brief	Set Timeer count.
 * @param[in]	count			Timeer count. Value range : 0~255.
 * @retval	VOID.
 */
VOID im_mipi_set_timer_count(ImMipi*self,UCHAR count);

/**
 * @brief	Set Interrupt mask.
 * @param[in]	int_msk1		Interrupt mask Register.
 * @retval	VOID.
 */
VOID im_mipi_set_int_mask(ImMipi*self,UImMipiIntMsk1 int_msk1);

/**
 * @brief	Get Interrupt mask.
 * @param[out]	int_msk1		Interrupt mask Register.
 * @retval	D_DDIM_OK					success.
 * @retval	ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
INT32 im_mipi_get_int_mask(UImMipiIntMsk1* int_msk1);

/**
 * @brief	Set interrupt callback function.
 * @param[in]	interrupt_type	Interrupt type.<br>
 * 								<ul><li>@ref ImMipi_E_IM_MIPI_INT_TYPE_TO_HS_TX
 * 									<li>@ref ImMipi_E_IM_MIPI_INT_TYPE_DPI_PLD_WR_ERR
 * 									<li>@ref ImMipi_E_IM_MIPI_INT_TYPE_GEN_CMD_WR_ERR
 * 									<li>@ref ImMipi_E_IM_MIPI_INT_TYPE_GEN_PLD_WR_ERR
 * 									<li>@ref ImMipi_E_IM_MIPI_INT_TYPE_GEN_PLD_SEND_ERR
 * 									<li>@ref ImMipi_E_IM_MIPI_INT_TYPE_GEN_PLD_SEND_ERR</ul>
 * @param[in]	vp_callback		callback funcion pointer.
 * @retval	D_DDIM_OK					success.
 * @retval	ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
INT32 im_mipi_set_int_callback(EImMipiIntType interrupt_type, VP_CALLBACK vp_callback);

/**
 * @brief	Interrupt handler.
 * @retval	VOID.
 */
VOID im_mipi_int_handler(VOID);

#ifdef __cplusplus
}
#endif

#endif /* __IM_MIPI_H__ */
