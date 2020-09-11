/*
 *
*@Copyright(C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-07
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#ifndef __IM_FPT_COMMON_H__
#define __IM_FPT_COMMON_H__


#include <klib.h>
#include "ddtop.h"
#include "driver_common.h"


#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus


#define IM_TYPE_FPT_COMMON				(im_fpt_common_get_type())
#define IM_FPT_COMMON	(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImFptCommon))
#define IM_IS_FPT_COMMON	(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_FPT_COMMON))

/*----------------------------------------------------------------------	*/
/* Compile option															*/
/*----------------------------------------------------------------------	*/
// #define CO_FPT_DISABLE_CLK_CTRL

/*----------------------------------------------------------------------	*/
/* Enumeration																*/
/*----------------------------------------------------------------------	*/

/*----------------------------------------------------------------------	*/
/* Definition																	*/
/*----------------------------------------------------------------------	*/
//---------------------------- driver section ----------------------------
#ifdef CO_ACT_CLOCK
#define ImFptCommon_CO_ACT_FPT_CLOCK
#endif	// CO_ACT_PCLOCK
#ifdef CO_ACT_HCLOCK
#define ImFptCommon_CO_ACT_FPT_HCLOCK
#endif	// CO_ACT_HCLOCK
#ifdef CO_ACT_PCLOCK
#define ImFptCommon_CO_ACT_FPT_PCLOCK
#endif	// CO_ACT_PCLOCK
#ifdef CO_ACT_ICLOCK
#define ImFptCommon_CO_ACT_FPT_ICLOCK
#endif	// CO_ACT_ICLOCK

// Version info.
#define ImFptCommon_D_IM_FPT_VERSION 						"FPT Driver Version V01L00\r\n"

#define ImFptCommon_D_IM_FPT0_CLK_REG_ADDR			(&DdToptwo_GET_CLKSTOP4())
#define ImFptCommon_D_IM_FPT0_HCLK_REG_ADDR		(&DdToptwo_GET_CLKSTOP4())
#define ImFptCommon_D_IM_FPT0_PCLK_REG_ADDR			(&DdToptwo_GET_CLKSTOP4())
#define ImFptCommon_D_IM_FPT0_ICLK_REG_ADDR			(&DdToptwo_GET_CLKSTOP4())

#define ImFptCommon_D_IM_FPT1_CLK_REG_ADDR			(&DdToptwo_GET_CLKSTOP4())
#define ImFptCommon_D_IM_FPT1_HCLK_REG_ADDR		(&DdToptwo_GET_CLKSTOP4())
#define ImFptCommon_D_IM_FPT1_PCLK_REG_ADDR			(&DdToptwo_GET_CLKSTOP4())
#define ImFptCommon_D_IM_FPT1_ICLK_REG_ADDR			(&DdToptwo_GET_CLKSTOP4())

#define ImFptCommon_D_IM_FPT0_CLK_REG_BIT				(DdTopone_FPT0CK_BIT)
#define ImFptCommon_D_IM_FPT0_PCLK_REG_BIT				(DdTopone_FPT0AP_BIT)
#define ImFptCommon_D_IM_FPT0_HCLK_REG_BIT				(DdTopone_FPT0AH_BIT)
#define ImFptCommon_D_IM_FPT0_ICLK_REG_BIT				(DdTopone_FPT0AX_BIT)

#define ImFptCommon_D_IM_FPT1_CLK_REG_BIT				(DdTopone_FPT1CK_BIT)
#define ImFptCommon_D_IM_FPT1_PCLK_REG_BIT				(DdTopone_FPT1AP_BIT)
#define ImFptCommon_D_IM_FPT1_HCLK_REG_BIT				(DdTopone_FPT1AH_BIT)
#define ImFptCommon_D_IM_FPT1_ICLK_REG_BIT				(DdTopone_FPT1AX_BIT)

// Clock Stop/Clear
#define ImFptCommon_D_IM_FPT_IM_FPT_CLK_ADDR_STOP		(0x18001134)
#define ImFptCommon_D_IM_FPT_IM_FPT_CLK_ADDR_CLEAR		(0x18001234)

// Clock Bit
// including FPTAX
#define ImFptCommon_D_IM_FPT_IM_FPTCLK						(0x00000090)
#define ImFptCommon_D_IM_FPT_PCLK								(0x00000020)
#define ImFptCommon_D_IM_FPT_HCLK								(0x00000040)

// The value of TRG bit.
#define ImFptCommon_D_IM_FPT_TRG_ABORT					(0)
#define ImFptCommon_D_IM_FPT_TRG_START						(1)
#define ImFptCommon_D_IM_FPT_TRG_STOPPED				(2)
#define ImFptCommon_D_IM_FPT_TRG_RUNNING				(3)

// Event-flag
#define ImFptCommon_D_IM_FPT_INTERRUPT_ERR				(ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR)
#define ImFptCommon_D_IM_FPT_ABORT_STOP					(0x00001000)
#define ImFptCommon_D_IM_FPT_USED_FLG_ALL				((ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | \
																										ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR | ImFptCommon_D_IM_FPT_ABORT_STOP))

// Mode Config
#define ImFptCommon_D_IM_FPT_IO_MODE_SDRAM				(0)
#define ImFptCommon_D_IM_FPT_IO_MODE_REGISTER			(1)
#define ImFptCommon_D_IM_FPT_PIPE_DISABLE					(0)
#define ImFptCommon_D_IM_FPT_PIPE_ENABLE						(1)
#define ImFptCommon_D_IM_FPT_NORMAL_MODE				(0)
#define ImFptCommon_D_IM_FPT_DEBUG_MODE					(1)

// LUT Config
#define ImFptCommon_D_IM_FPT_LUT_OFF								(0x00000000)
#define ImFptCommon_D_IM_FPT_LUT_ON								(0x00000001)
#define ImFptCommon_D_IM_FPT_LUT_BASE							(0x00000000)
#define ImFptCommon_D_IM_FPT_LUT_TARGET						(0x00000100)
#define ImFptCommon_D_IM_FPT_LUT_BASE_X__TARGET_Y	(0x00000200)
#define ImFptCommon_D_IM_FPT_LUT_LUT0							(0x00000000)
#define ImFptCommon_D_IM_FPT_LUT_LUT1							(0x00010000)

// Offset & Clip Config
#define ImFptCommon_D_IM_FPT_OFFSET_OFF						(0x0000)
#define ImFptCommon_D_IM_FPT_CLIP_MAX_OFF					(0xFF)
#define ImFptCommon_D_IM_FPT_CLIP_MIN_OFF					(0x00)

//---------------------------- driver section ----------------------------
#ifdef CO_FPT_DEBUG
#include <stdio.h>
#define ImFptCommon_IM_FPT_PRINTF(arg)							(printf arg)
#else
#define ImFptCommon_IM_FPT_PRINTF(arg)
#endif

#ifdef CO_ARM_V7_ARCH
#define ImFptCommon_IM_FPT_DUMMY_READ(ch)					{ ioFpt[ch].fptaxierr0.word; }
#else
#define ImFptCommon_IM_FPT_DUMMY_READ(ch)
#endif
/*----------------------------------------------------------------------	*/
/* Definition																	*/
/*----------------------------------------------------------------------	*/
//---------------------------- driver section ----------------------------
/**
 @weakgroup fpt_drv FPT driver API
 @{
 */
/**
 @name Returned value
 @{
 */
/**< Normal end*/
#define ImFptCommon_D_IM_FPT_RETVAL_OK										(0)
/**< Invalid argument error. The members of structure is not checked.	*/
#define ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR			(-1)
/**< System-call error*/
#define ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR			(-2)
/**< Error*/
#define ImFptCommon_D_IM_FPT_RETVAL_ERR									(-3)
/**< FPT Busy	*/
#define ImFptCommon_D_IM_FPT_RETVAL_BUSY_ERR						(-4)
/** @} */	// name
/** @} */// end of fpt_drv
/**< Sum Window 5x5*/
#define ImFptCommon_D_IM_FPT_WINDOW_5x5								(0)
/**< Sum Window 7x7*/
#define ImFptCommon_D_IM_FPT_WINDOW_7x7								(1)
/**< Min down-sampling 1/1 [No down-sampling]	*/
#define ImFptCommon_D_IM_FPT_DS_MIN											(0x0100)
/**< Max down-sampling 1/20	*/
#define ImFptCommon_D_IM_FPT_DS_MAX											(0x1400)
/**< Output coord only	*/
#define ImFptCommon_D_IM_FPT_OUT_COORD_ONLY						(0)
/**< Output coord and feature amount*/
#define ImFptCommon_D_IM_FPT_OUT_COORD_AND_FEATURE_AMOUNT	(1)
/**< Read target's coord from RAM.	*/
#define ImFptCommon_D_IM_FPT_READ_FROM_RAM							(0)
/**< Target coord is same as base coord.*/
#define ImFptCommon_D_IM_FPT_SAME_AS_BASE_COORD				(1)
/**< Interruption of FPT completion*/
#define ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE				(0x00000001)
/**< Interruption of AXI error*/
#define ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR						(0x00000010)
/**< Interruption of Parameter error*/
#define ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR				(0x00000100)


typedef enum _EfptIoMode							EfptIoMode;
typedef enum _EfptPipeEn							EfptPipeEn;
typedef enum _EfptDebugMode					EfptDebugMode;
typedef enum _EfptLutset								EfptLutset;
typedef enum _EfptLutcfg								EfptLutcfg;

typedef struct _TfptMode0							TfptMode0;
typedef struct _TfptMode1							TfptMode1;
typedef struct _TfptSearchWindow				TfptSearchWindow;
typedef struct _TfptMode2							TfptMode2;
typedef struct _TfptMode3							TfptMode3;
typedef struct _TfptModeConfig					TfptModeConfig;
typedef struct _TfptBrcConfig						TfptBrcConfig;
typedef struct _TfptInterrupt						TfptInterrupt;

typedef struct _ImFptCommon 						ImFptCommon;
typedef struct _ImFptCommonPrivate 			ImFptCommonPrivate;


/*----------------------------------------------------------------------	*/
/* Enumeration																*/
/*----------------------------------------------------------------------	*/
/** The configuration of fptctl2.ioMode. */
enum _EfptIoMode
{
	/**< SDRAM mode : Read data from SDRAM and do the processing. Write the result to SDRAM.	*/
	ImFptCommon_E_IM_FPT_IO_MODE_SDRAM,
	/**< Register mode : Read data via AHB and do the processing. Read the result via AHB.	*/
	ImFptCommon_E_IM_FPT_IO_MODE_REGISTER
};

/** The configuration of fptctl2.pipeEn. */
enum _EfptPipeEn
{
	/**< Disable pipeline processing.	*/
	ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE,
	/**< Enable pipeline processing(fast method).	*/
	ImFptCommon_E_IM_FPT_PIPE_EN_ENABLE
};

/** The configuration of fptctl2.debugMode. */
enum _EfptDebugMode
{
	/**< Normal mode.	*/
	ImFptCommon_E_IM_FPT_DEBUG_MODE_NORMAL,
	/**< Debug mode.	*/
	ImFptCommon_E_IM_FPT_DEBUG_MODE_DEBUG
};

/** The selection of LUTRAM. */
enum _EfptLutset
{
	/**< LUT  is not used at all.	*/
	ImFptCommon_E_IM_FPT_LUTSEL_OFF,
	/**< LUT0 is used.	*/
	ImFptCommon_E_IM_FPT_LUTSEL_0,
	/**< LUT1 is used.	*/
	ImFptCommon_E_IM_FPT_LUTSEL_1
};

/** The configuration of LUTRAM. */
enum _EfptLutcfg
{
	/**< LUT  is not used at all.*/
	ImFptCommon_E_IM_FPT_LUTCFG_OFF,
	/**< LUT0 is used for Base   image. LUT1 is not used.*/
	ImFptCommon_E_IM_FPT_LUTCFG_BASE_0,
	/**< LUT0 is not used.              LUT1 is used for Target image.	*/
	ImFptCommon_E_IM_FPT_LUTCFG_TARGET_1,
	/**< LUT0 is used for Base   image. LUT1 is used for Target image.	*/
	ImFptCommon_E_IM_FPT_LUTCFG_BASE_0__TARGET_1,
	/**< LUT0 is used for Target image. LUT1 is used for Base   image.	*/
	ImFptCommon_E_IM_FPT_LUTCFG_BASE_1__TARGET_0
};

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

/*----------------------------------------------------------------------	*/
/* Structure																		*/
/*----------------------------------------------------------------------	*/
//---------------------------- driver section ----------------------------
/**
 Parameters of Im_FPT_Ctrl_Mode0().
*/
struct _TfptMode0
{
		/**<
		 The number of pixels of 1 line.<br>
		 It means line feed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptfqctl0.GHSIZE[14:0] register.<br>
		 */
		kushort globalWidth;
		kushort width;
		kushort lines;
		/**<
		 LUT control for input iamge.<br>
		 <ul>
		 <li> @ref ImFptCommon_E_IM_FPT_LUTSEL_OFF	[fptctl3.BRC_EN=0b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTSEL_0		[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=0b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTSEL_1		[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=1b]
		 </ul>
		 */
		EfptLutset lutsel;
		/**<
		 The size of sum window.<br>
		 <ul>
		 <li> @ref ImFptCommon_D_IM_FPT_WINDOW_5x5	[fptfqctl2.sumw=0b]
		 <li> @ref ImFptCommon_D_IM_FPT_WINDOW_7x7	[fptfqctl2.sumw=1b]
		 </ul>
		 */
		kuchar windowSize;
		/**<
		 Horizontal down-sampling.(downSampleX/256)<br>
		 value range  :[256 - 5120]<br>
		 The value is set to fptfqctl9.skipxFq[12:0] register.<br>
		 */
		kushort downSampleX;
		/**<
		 Vertical down-sampling.(downSampleY/256)<br>
		 value range  :[256 - 5120]<br>
		 The value is set to fptfqctl9.skipyFq[12:0] register.<br>
		 */
		kushort downSampleY;
		/**<
		 Beginning address of image to be processed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptfqctl3.SDAD_FQ_OF[31:0] register.<br>
		 */
		kuint32 imgAddr;
		/**<
		 Beginning address of feature amount data.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptfqctl4.SDAD_FQ_MP[31:0] register.<br>
		 */
		kuint32 featureAmountAddr;
		/**<
		 The number of bytes per feature amount data's line.<br>
		 featureAmountLineByte = [8-byte rounding up(((width/downSampleX)-(12+(windowSize*2)))*2)]<br>
		 Should be aligned on 8.<br>
		 The value is set to fptfqctl8.MAPGHSIZE[14:0] register.<br>
		 */
		kushort featureAmountLineByte;
		/**<
		 Beginning address of histgram data.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptfqctl5.SDAD_FQ_HI[31:0] register.<br>
		 */
		kuint32 histgramAddr;
};

/**
   Parameters of Im_FPT_Ctrl_Mode1().
 */
struct _TfptMode1
{
		/**<
		 The number of feature point to be re-calculated.[1~127].<br>
		 The value is set to fptfqctl2.fpmax[6:0] register.<br>
		 */
		kuchar numFeaturePoint;
		/**<
		 Control output data.
		 <ul>
		 <li>@ref ImFptCommon_D_IM_FPT_OUT_COORD_ONLY 				Output coord data only.
		 <li>@ref ImFptCommon_D_IM_FPT_OUT_COORD_AND_FEATURE_AMOUNT	Output coord and feature amount data.
		 </ul>
		 The value is set to fptfqctl2.outen register.<br>
		 */
		kuchar output;
		/**<
		 The number of pixels of 1 line.<br>
		 It means line feed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptfqctl0.GHSIZE[14:0] register.<br>
		 */
		kushort globalWidth;
		kushort width;
		kushort lines;
		/**<
		 LUT control for input iamge.<br>
		 <ul>
		 <li> @ref ImFptCommon_E_IM_FPT_LUTSEL_OFF	[fptctl3.BRC_EN=0b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTSEL_0		[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=0b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTSEL_1		[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=1b]
		 </ul>
		 */
		EfptLutset lutsel;
		/**<
		 The size of sum window.<br>
		 <ul>
		 <li> @ref ImFptCommon_D_IM_FPT_WINDOW_5x5	[fptfqctl2.sumw=0b]
		 <li> @ref ImFptCommon_D_IM_FPT_WINDOW_7x7	[fptfqctl2.sumw=1b]
		 </ul>
		 */
		kuchar windowSize;
		/**<
		 Horizontal down-sampling.(downSampleX/256)<br>
		 value range  :[256 - 5120]<br>
		 The value is set to fptfqctl9.skipxFq[12:0] register.<br>
		 */
		kushort downSampleX;
		/**<
		 Vertical down-sampling.(downSampleY/256)<br>
		 value range  :[256 - 5120]<br>
		 The value is set to fptfqctl9.skipyFq[12:0] register.<br>
		 */
		kushort downSampleY;
		/**<
		 Beginning address of image to be processed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptfqctl3.SDAD_FQ_OF[31:0] register.<br>
		 */
		kuint32 imgAddr;
		/**<
		 Beginning address of feature point coord data.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptfqctl6.SDAD_FQ_CXY[31:0] register.<br>
		 */
		kuint32 inputCoordAddr;
		/**<
		 Beginning address of output data.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptfqctl7.SDAD_FQ_RXY[31:0] register.<br>
		 */
		kuint32 outputAddr;
};

/**
Tracking Search Window.<br>
Need to adjust search window on image boundary.<br>
*/
struct _TfptSearchWindow
{
		/**<
		 Left search range.<br>
		 4.8 fixed point value. [0x000~0x7FF]<br>
		 The value is set to fptftctl2.leftlimit register.<br>
		 */
		kushort left;
		/**<
		 Right search range.<br>
		 4.8 fixed point value. [0x000~0x7FF]<br>
		 The value is set to fptftctl2.rightlimit register.<br>
		 */
		kushort right;
		/**<
		 Top search range.<br>
		 4.8 fixed point value. [0x000~0x7FF]<br>
		 The value is set to fptftctl3.toplimit register.<br>
		 */
		kushort top;
		/**<
		 Bottom search range.<br>
		 4.8 fixed point value. [0x000~0x7FF]<br>
		 The value is set to fptftctl3.bottomlimit register.<br>
		 */
		kushort bottom;
};

/**
 Parameters of Im_FPT_Ctrl_Mode2().
*/
struct _TfptMode2
{
		/**<
		 The number of pixels of base image's 1 line.<br>
		 It means line feed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl0.ghbsize[14:0] register.<br>
		 */
		kushort baseGlobalWidth;
		/**<
		 The number of pixels of target image's 1 line.<br>
		 It means line feed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl0.ghtsize[14:0] register.<br>
		 */
		kushort targetGlobalWidth;
		/**<
		 The number of feature point to be tracked.[1~127].<br>
		 The value is set to fptftctl1.ftmax[6:0] register.<br>
		 */
		kuchar numFeaturePoint;
		/**<
		 Control the usage of target image's coord
		 <ul>
		 <li> @ref ImFptCommon_D_IM_FPT_READ_FROM_RAM      [fptftctl1.init0 = 0b]
		 <li> @ref ImFptCommon_D_IM_FPT_SAME_AS_BASE_COORD [fptftctl1.init0 = 1b]
		 </ul>
		 The value is set to fptftctl1.init0 register.<br>
		 */
		kuchar usageTargetCoord;
		/**<
		 Horizontal down-sampling.(downSampleX/256)<br>
		 value range  :[256 - 5120]<br>
		 The value is set to fptftctl10.skipxFt[12:0] register.<br>
		 */
		kushort downSampleX;
		/**<
		 Vertical down-sampling.(downSampleY/256)<br>
		 value range  :[256 - 5120]<br>
		 The value is set to fptftctl10.skipyFt[12:0] register.<br>
		 */
		kushort downSampleY;
		/**<
		 LUT control for input iamge.<br>
		 <ul>
		 <li> @ref ImFptCommon_E_IM_FPT_LUTCFG_OFF				[fptctl3.BRC_EN=0b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTCFG_BASE_0			[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=0b, fptctl3.BRC_MOD=00b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTCFG_TARGET_1			[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=1b, fptctl3.BRC_MOD=01b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTCFG_BASE_0__TARGET_1	[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=0b, fptctl3.BRC_MOD=10b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTCFG_BASE_1__TARGET_0	[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=1b, fptctl3.BRC_MOD=10b]
		 </ul>
		 */
		EfptLutcfg lutcfg;
		/**<Search window.<br>*/
		TfptSearchWindow searchWindow;
		/**<									Tracking convergence condition.<br>
		 4.8 fixed point value. [0x000~0x8FF].<br>
		 The value is set to fptftctl4.maxerr[11:0] register.<br>
		 */
		kushort trackingThreshold;
		/**<
		 The number of tracking iteration. [1~10]<br>
		 The value is set to fptftctl4.maxitr[3:0] register.<br>
		 */
		kushort numIteration;
		/**<
		 Beginning address of base image to be processed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl5.SDAD_BP_OF[31:0] register.<br>
		 */
		kuint32 baseImgAddr;
		/**<
		 Beginning address of target image to be processed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl6.SDAD_TP_OF[31:0] register.<br>
		 */
		kuint32 targetImgAddr;
		/**<
		 Beginning address of base image's feature point coord data.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl7.SDAD_FT_CXY[31:0] register.<br>
		 */
		kuint32 baseCoordAddr;
		/**<
		 Beginning address of target image's feature point coord data.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl8.SDAD_FT_BXY[31:0] register.<br>
		 */
		kuint32 targetCoordAddr;
		/**<
		 Beginning address of tracking output data, motion vectors. <br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl9.SDAD_FT_TXY[31:0] register.<br>
		 */
		kuint32 trackingResultAddr;
};

/**
 Parameters of Im_FPT_Ctrl_Mode3().
*/
struct _TfptMode3
{
		kushort width;
		kushort lines;
		/**<
		 The size of sum window.<br>
		 <ul>
		 <li> @ref ImFptCommon_D_IM_FPT_WINDOW_5x5	[fptfqctl2.sumw=0b]
		 <li> @ref ImFptCommon_D_IM_FPT_WINDOW_7x7	[fptfqctl2.sumw=1b]
		 </ul>
		 */
		kuchar windowSize;
		/**<
		 Beginning address of output data.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptfqctl7.SDAD_FQ_RXY[31:0] register.<br>
		 */
		kuint32 outputAddr;
		/**<
		 The number of pixels of base image's 1 line.<br>
		 It means line feed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl0.ghbsize[14:0] register.<br>
		 */
		kushort baseGlobalWidth;
		/**<
		 The number of pixels of target image's 1 line.<br>
		 It means line feed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl0.ghtsize[14:0] register.<br>
		 */
		kushort targetGlobalWidth;
		/**<
		 The number of feature point to be tracked.[1~127].<br>
		 The value is set to fptftctl1.ftmax[6:0] register.<br>
		 */
		kuchar numFeaturePoint;
		/**<
		 Control the usage of target image's coord
		 <ul>
		 <li> @ref ImFptCommon_D_IM_FPT_READ_FROM_RAM      [fptftctl1.init0 = 0b]
		 <li> @ref ImFptCommon_D_IM_FPT_SAME_AS_BASE_COORD [fptftctl1.init0 = 1b]
		 </ul>
		 The value is set to fptftctl1.init0 register.<br>
		 */
		kuchar usageTargetCoord;
		/**<
		 Horizontal down-sampling for tracking.(downSampleX/256)<br>
		 value range  :[256 - 5120]<br>
		 The value is set to fptftctl10.skipxFt[12:0] register.<br>

		 */
		kushort downSampleX;
		/**<
		 Vertical down-sampling for tracking.(downSampleY/256)<br>
		 value range  :[256 - 5120]<br>
		 The value is set to fptftctl10.skipyFt[12:0] register.<br>
		 */
		kushort downSampleY;
		/**<
		 LUT control for input iamge.<br>
		 <ul>
		 <li> @ref ImFptCommon_E_IM_FPT_LUTCFG_OFF				[fptctl3.BRC_EN=0b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTCFG_BASE_0			[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=0b, fptctl3.BRC_MOD=00b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTCFG_TARGET_1			[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=1b, fptctl3.BRC_MOD=01b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTCFG_BASE_0__TARGET_1	[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=0b, fptctl3.BRC_MOD=10b]
		 <li> @ref ImFptCommon_E_IM_FPT_LUTCFG_BASE_1__TARGET_0	[fptctl3.BRC_EN=1b, fptctl3.LUT_SEL=1b, fptctl3.BRC_MOD=10b]
		 </ul>
		 */
		EfptLutcfg lutcfg;
		/**< Search window.<br> */
		TfptSearchWindow searchWindow;
		/**<
		 Tracking convergence condition.<br>
		 4.8 fixed point value. [0x000~0x8FF].<br>
		 The value is set to fptftctl4.maxerr[11:0] register.<br>
		 */
		kushort trackingThreshold;
		/**<
		 The number of tracking iteration. [1~10]<br>
		 The value is set to fptftctl4.maxitr[3:0] register.<br>
		 */
		kushort numIteration;
		/**<
		 Beginning address of base image to be processed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl5.SDAD_BP_OF[31:0] register.<br>
		 */
		kuint32 baseImgAddr;
		/**<
		 Beginning address of target image to be processed.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl6.SDAD_TP_OF[31:0] register.<br>
		 */
		kuint32 targetImgAddr;
		/**<
		 Beginning address of base image's feature point coord data.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl7.SDAD_FT_CXY[31:0] register.<br>
		 */
		kuint32 baseCoordAddr;
		/**<
		 Beginning address of target image's feature point coord data.<br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl8.SDAD_FT_BXY[31:0] register.<br>
		 */
		kuint32 targetCoordAddr;
		/**<
		 Beginning address of tracking output data, motion vectors. <br>
		 Should be aligned on 8.<br>
		 The value is set to fptftctl9.SDAD_FT_TXY[31:0] register.<br>*/
		kuint32 trackingResultAddr;
};

/**
   Parameters of im_fpt_ctrl_mode_config().
 */
struct _TfptModeConfig
{
		/**<The settings for the input and output method of feature point coordinates and the processing result.<br> */
		EfptIoMode imIoMode;
		/**<
		 At the time of the feature point tracking, the settings of whether reading pixel data from the
		 SDRAM and the internal processing executed with pipeline processing.<br>
		 Please set "ImFptCommon_E_IM_FPT_PIPE_EN_DISABLE".*/
		EfptPipeEn imPipeEn;
		/**<The setting of debug mode.<br>*/
		EfptDebugMode imDebugMode;
};

/**
   Parameters of Im_FPT_Ctrl_BRC_Config_Base() and Im_FPT_Ctrl_BRC_Config_Target().
 */
struct _TfptBrcConfig
{
		/**< Offset values for the brightness correction of the base and target image.<br>
		 This value is signed.<br>
		 The value is set to fptctl4.offsetB[24:16], fptctl5.offsetT[24:16] register.<br>
		 */
		kushort imgOffset;
		/**< Upper limit clip value after the offset for the brightness correction of the base and target image.<br>
		 The value is set to fptctl4.clpmaxB[15:8], fptctl5.clpmaxT[15:8] register.<br>
		 */
		kuchar imClipMax;
		/**< Lower limit clip value after the offset for the brightness correction of the base and target image.<br>
		 The value is set to fptctl4.clpminB[7:0], fptctl5.clpminT[7:0] register.<br>
		 */
		kuchar imgClipMin;
};

/**
   Parameters of im_fpt_ctrl_interrupt().
 */
struct _TfptInterrupt
{
		kuint32 flag;
		void(*callback)(kuint32 intFactor, kuchar ch);
};

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section -------------------------
// Nothing Special
#endif

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section -------------------------
// Nothing Special
#endif


struct _ImFptCommon
{
	KObject parent;
};


KConstType 		    			im_fpt_common_get_type(void);
ImFptCommon*		        im_fpt_common_new(void);
/**
 Configure the mode.<br>
 @param[in]	ch :Channel number(0/1)
 @param[in]	param : parameter. Please refer to @ref TfptModeConfig.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 */
extern kint32 im_fpt_ctrl_mode_config(ImFptCommon*self, kuchar ch, const TfptModeConfig* const param);

/**
 Configure BRC(BRightness Correction) of the base image.<br>
 @param[in]	ch :Channel number(0/1)
 @param[in]	param : parameter. Please refer to @ref TfptBrcConfig.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 */
extern kint32 im_fpt_ctrl_brc_config_base_img(ImFptCommon*self, kuchar ch, const TfptBrcConfig* const param);

/**
 Configure BRC(BRightness Correction) of the target image.<br>

 @param[in]	ch :Channel number(0/1)
 @param[in]	param : parameter. Please refer to @ref TfptBrcConfig.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 */
extern kint32 im_fpt_ctrl_brc_config_target_img(ImFptCommon*self, kuchar ch, const TfptBrcConfig* const param);

/**
 Configure Interrupt.<br>
 @param[in]	ch :Channel number(0/1)
 @param[in]	param : parameter. Please refer to @ref TfptInterrupt.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 */
extern kint32 im_fpt_ctrl_interrupt(ImFptCommon*self, kuchar ch, const TfptInterrupt* const param);

/**
 Configure LUTRAM.<br>
 <br>
 In LUT function, FPT process the value of input pixel as follows:<br>
 lut[ the value of input pixel ]<br>
 @param[in]	ch :Channel number(0/1)
 @param[in]	lutSel : fptlut0 or fptlut1<br>
 <ul>
 <li>0  : fptlut0 is used.
 <li>1  : fptlut1 is used.
 </ul>
 @param[in]	lut : Beginning address of LUTRAM buffer [256Bytes].<br>
 These value is copied on the LUTRAM.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 */
extern kint32 im_fpt_ctrl_lutram(ImFptCommon*self, kuchar ch, kint32 lutSel, const kuchar* lut);

/**
 Set REGRAM.<br>
 This area is used to store the input coordinates and the operation result register.<br>
 @param[in]	ch :Channel number(0/1)
 @param[in]	regSel : fptreg0 or fptreg1<br>
 <ul>
 <li>0  : fptreg0 is used.
 <li>1  : fptreg1 is used.
 </ul>
 @param[in]	reg : Beginning address of REGRAM buffer [512Bytes].<br>
 These value is copied on the REGRAM.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 */
extern kint32 im_fpt_set_regram(ImFptCommon*self, kuchar ch, kint32 regSel, const kuchar* reg);

/**
 Get REGRAM.<br>
 This area is used to store the input coordinates and the operation result register.<br>
 @param[in]	ch :Channel number(0/1)
 @param[in]	regSel : fptreg0 or fptreg1<br>
 <ul>
 <li>0  : fptreg0 is used.
 <li>1  : fptreg1 is used.
 </ul>
 @param[in]	bufAddr : Beginning address of the buffer [512Bytes].<br>
 These value is copied from the REGRAM.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 @remarks	This API uses DDIM_User_Clr_Flg().
 */
extern kint32 im_fpt_get_regram(ImFptCommon*self, kuchar ch, kint32 regSel, kulong* bufAddr);

/**
 Start FPT.<br>
 @param[in]	ch :Channel number(0/1)
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_ERR : @ref ImFptCommon_D_IM_FPT_RETVAL_ERR(FPT is running.)
 @remarks	It should be called when FPT is not running.
 */
extern kint32 im_fpt_start(ImFptCommon*self, kuchar ch);

/**
 Force stop FPT.<br>
 @param[in]	ch :Channel number(0/1)
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR : @ref ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR
 @retval		ImFptCommon_D_IM_FPT_RETVAL_ERR : @ref ImFptCommon_D_IM_FPT_RETVAL_ERR(FPT is running.)
 @remarks	It should be called when FPT is running.
 @remarks	This API uses DDIM_User_Set_Flg().
 */
extern kint32 im_fpt_stop(ImFptCommon*self, kuchar ch);

/**
 Wait process until FPT interrupt occurs.<br>
 @param[in]	ch :Channel number(0/1)
 @param[out]	status : Status.<br>
 <ul>
 <li>bit0  : If bit0  is set to 1, FPT completion interrupt has occured.
 <li>bit4  : If bit4  is set to 1, AXI error interrupt has occured.
 <li>bit8  : If bit8  is set to 1, parameter error interrupt has occured.
 <li>bit12 : If bit12 is set to 1, force stop has occured. It means that im_fpt_stop() is called while im_fpt_waitend().
 </ul>
 @param[in]	waitTime : Wait time [msec]. The valid range is -1, 0, ... .
 If this parameter is set to -1, driver waits permanently unless system-call sets event-flag.
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 @retval		ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR : @ref ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR
 @remarks	This API uses DDIM_User_Clr_Flg().
 @remarks	This API uses DDIM_User_Twai_Flg().
 */
extern kint32 im_fpt_waitend(ImFptCommon*self, kuchar ch, kuint32* status, kint32 waitTime);

/**
 Interrupt Handler.<br>
 @param[in]	ch :Channel number(0/1)
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR : @ref ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR
 @remarks	This API should be called when interrupt of INTID 104 has occured.<br>
 @remarks	If the address of callback funtion is set to TfptInterrupt::callback, this api calls callback function.
 @remarks	This API uses DDIM_User_Set_Flg().
 */
extern kint32 im_fpt_int_handler(ImFptCommon*self, kuchar ch);

/**
 Get AXI response.<br>
 @param[in]	ch :Channel number(0/1)
 @param[out]	readResponse  : The value of fptaxierr0.rresp register.<br>.
 It means that read response signal, rresp.<br>
 @param[out]	writeResponse : The value of fptaxierr0.wresp register.<br>.
 It means that write response signal, BRESP.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 @remarks	This API should be used only for the purpose of debug.<br>
 @remarks	This API should be used right after AXI Error interrupt has occured.<br>
 */
extern kint32 im_fpt_get_axi_response(ImFptCommon*self, kuchar ch, kuchar* readResponse, kuchar* writeResponse);

/**
 Dump the value of all FPT's register.<br>
 @param[in]	ch :Channel number(0/1)
 @param[in]	buf0_addr : Beginning address of buffer [256Bytes].<br>
 The value of APB registers is copied on the buffer.<br>
 Should be aligned on 4.<br>
 @param[in]	buf1_addr : Beginning address of buffer [256Bytes x2 = 512Bytes].<br>
 The value of AHB registers is copied on the buffer.<br>
 Should be aligned on 4.<br>
 @remarks	This API should be used only for the purpose of debug.<br>
 */
extern void im_fpt_debugdump_all_registers(ImFptCommon*self, kuchar ch, kuint32 buf0_addr, kuint32 buf1_addr);

/**
 Get version info.<br>
 @code
 kchar *str;
 im_fpt_get_version( &str );
 printf("%s\n", str);
 @endcode
 @param[out]	str : The pointer of version string.<br>
 @remarks	This API should be used only for the purpose of debug.<br>
 */
extern void im_fpt_get_version(ImFptCommon*self, kchar** str);
#ifdef CO_DDIM_UTILITY_USE


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif /* __IM_FPT_COMMON_H__ */
