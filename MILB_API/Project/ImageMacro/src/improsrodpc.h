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


#ifndef __IMPRO_SRODPC_H__
#define __IMPRO_SRODPC_H__


#include <klib.h>
#include "improbase.h"
#include "improsrotop.h"

#define IMPRO_TYPE_SRODPC        (impro_srodpc_get_type())
#define IMPRO_SRODPC(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSrodpc))
#define IMPRO_IS_SRODPC(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SRODPC))


/*宏定义区域*/
/** @addtogroup im_pro_sro_dpc DPC*/
/**< Minimum setting of DPCGV	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCGV_MIN			(0)
/**< Maximum setting of DPCGV	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCGV_MAX			(8960)
/**< Minimum setting of DPCGH	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCGH_MIN			(0)
/**< Minimum setting of DPCGVW	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCGVW_MIN			(10)
/**< Maximum setting of DPCGVW	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCGVW_MAX			(8960)
/**< Minimum setting of DPCGHW	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCGHW_MIN			(10)
/**< Minimum setting of DPCV	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCV_MIN			(0)
/**< Maximum setting of DPCV	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCV_MAX			(8950)
/**< Minimum setting of DPCH	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCH_MIN			(0)
/**< Minimum setting of DPCVW	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCVW_MIN			(10)
/**< Maximum setting of DPCVW	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCVW_MAX			(8960)
/**< Minimum setting of DPCHW	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCHW_MIN			(10)
	/**< Minimum setting of DPCBLWP/M	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCBLW_MIN			(0)
/**< Maximum setting of DPCBLWP/M	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCBLW_MAX			(15)

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**< Maximum setting of DPCGH	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCGH_MAX			(2496)
/**< Maximum setting of DPCGHW	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCGHW_MAX			(2496)
/**< Maximum setting of DPCH	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCH_MAX			(2486)
/**< Maximum setting of DPCHW	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCHW_MAX			(2496)
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**< Maximum setting of DPCGH	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCGH_MAX			(2900)
/**< Maximum setting of DPCGHW	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCGHW_MAX			(2900)
/**< Maximum setting of DPCH	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCH_MAX			(2890)
/**< Maximum setting of DPCHW	*/
#define	ImproSrodpc_D_IM_PRO_DPC_DPCHW_MAX			(2900)
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

/*	@}*/	// im_pro_sro_dpc

/*其他结构体或类型定义区域*/
/** Defect correction mode.<br>
	<table>
		<tr>
			<th>Mode</th>
			<th>Correction method of<br>dynamic detection pixel</th>
			<th>Correction method of<br>registration defective pixel</th>
			<th>Correction method of<br>registration defect and<br>dynamic detection pixel</th>
			<th>Recommended DPCRTZ setting</th>
		<tr>
			<td>0</td>
			<td>Correction OFF</td>
			<td>Correction OFF</td>
			<td>Correction OFF</td>
			<td>No effect</td></tr>

		<tr>
			<td>1</td>
			<td>alpha blend detect correction</td>
			<td>Correction OFF</td>
			<td>alpha blend detect correction</td>
			<td>0</td></tr>

		<tr>
			<td>2</td>
			<td>Correction OFF</td>
			<td>alpha blend detect correction</td>
			<td>alpha blend detect correction</td>
			<td>1</td></tr>

		<tr>
			<td>3</td>
			<td>alpha blend detect correction</td>
			<td>alpha blend detect correction</td>
			<td>alpha blend detect correction</td>
			<td>1</td></tr>

		<tr>
			<td>4</td>
			<td>alpha blend detect correction</td>
			<td>Edge storage defect correction</td>
			<td>Edge storage defect correction</td>
			<td>No effect</td></tr>

		<tr>
			<td>5</td>
			<td>alpha blend detect correction</td>
			<td>Edge storage defect correction</td>
			<td>alpha blend detect correction</td>
			<td>1</td></tr>
	</table>
*/
typedef enum {
	/**< Defect correction mode0.	*/
	ImproSrodpc_E_IM_PRO_DPC_MODE_0 = 0,
	/**< Defect correction mode1.	*/
	ImproSrodpc_E_IM_PRO_DPC_MODE_1,
	/**< Defect correction mode2.	*/
	ImproSrodpc_E_IM_PRO_DPC_MODE_2,
	/**< Defect correction mode3.	*/
	ImproSrodpc_E_IM_PRO_DPC_MODE_3,
	/**< Defect correction mode4.	*/
	ImproSrodpc_E_IM_PRO_DPC_MODE_4,
	/**< Defect correction mode5.	*/
	ImproSrodpc_E_IM_PRO_DPC_MODE_5,
} EimproDpcMode;

/** Dynamic defect determination threshold zero conversion for registration defective pixel.<br>
*/
typedef enum {
	/**< Dynamic defect determination threshold is not converted to zero.	*/
	ImproSrodpc_E_IM_PRO_DPC_THRE_CONV_0_DIS = 0,
	/**< Dynamic defect determination threshold is converted to zero.	*/
	ImproSrodpc_E_IM_PRO_DPC_THRE_CONV_0_EN,
} EimproDpcThreConvToZero;

/** reference mode of gr/gb pixel in the defect dynamic detection and pixel value magnitude defect correction.
*/
typedef enum {
	/**< GrGb united.	*/
	ImproSrodpc_E_IM_PRO_DPC_DD_GRGB_UNITED = 0,
	/**< GrGb independent.	*/
	ImproSrodpc_E_IM_PRO_DPC_DD_GRGB_INDEPENDENT,
} EimproDpcDdGrgb;

/** dynamic detection mode of G pixel in the defect dynamic detection.
*/
typedef enum {
	/**< G pixel single defect support.	*/
	ImproSrodpc_E_IM_PRO_DPC_DD_MODE_G_SINGLE_DEFECT = 0,
	/**< G pixel 2-consecutive defects support.	*/
	ImproSrodpc_E_IM_PRO_DPC_DD_MODE_G_2_CONSECUTIVE_DEFECT,
} EimproDpcDdModeG;

/** dynamic detection mode of rr/bb pixel in the defect dynamic detection.
*/
typedef enum {
	/**< rr/bb pixel single defect support.	*/
	ImproSrodpc_E_IM_PRO_DPC_DD_MODE_RB_SINGLE_DEFECT = 0,
	/**< rr/bb pixel 2-consecutive defects support.	*/
	ImproSrodpc_E_IM_PRO_DPC_DD_MODE_RB_2_CONSECUTIVE_DEFECT,
} EimproDpcDdModeRb;

/** Use of mis-determination degree for correction.
*/
typedef enum {
	/**< Mis-determination degree for correction is not used.	*/
	ImproSrodpc_E_IM_PRO_DPC_DD_USE_MDD_DIS = 0,
	/**< Mis-determination degree for correction is used.	*/
	ImproSrodpc_E_IM_PRO_DPC_DD_USE_MDD_EN,
} EimproDpcDdUseMdd;

/** Mis-determination degree for correction  horizontal and vertical 2-concecutive defect support.
*/
typedef enum {
	/**< When mis-determination degree for correction is used, horizontal and
	 *  vertical 2-consecutive defect support is not included.	*/
	ImproSrodpc_E_IM_PRO_DPC_DD_MDD_2CONSECUTIVE_DEFECT_DIS = 0,
	/**< When mis-determination degree for correction is used, horizontal and
	 *  vertical 2-consecutive defect support is included.	*/
	ImproSrodpc_E_IM_PRO_DPC_DD_MDD_2CONSECUTIVE_DEFECT_EN,
} EimproDpcDdMdd2consecutiveDefect;

typedef enum {
	/**< Edge storage defect correction mode0.	*/
	ImproSrodpc_E_IM_PRO_DPC_ESD_MODE_0 = 0,
	/**< Edge storage defect correction mode1.	*/
	ImproSrodpc_E_IM_PRO_DPC_ESD_MODE_1,
	/**< Edge storage defect correction mode2.	*/
	ImproSrodpc_E_IM_PRO_DPC_ESD_MODE_2,
	/**< Edge storage defect correction mode3.	*/
	ImproSrodpc_E_IM_PRO_DPC_ESD_MODE_3,
} EimproDpcEsdMode;

/** Use of G pixel in RB judgment of edge storage defect correction.
*/
typedef enum {
	/**< G pixel is not used in RB judgment of edge storage defect correction.	*/
	ImproSrodpc_E_IM_PRO_DPC_ESD_USE_RB_JUDGE_DIS = 0,
	/**< G pixel is used in RB judgment of edge storage defect correction.	*/
	ImproSrodpc_E_IM_PRO_DPC_ESD_USE_RB_JUDGE_EN,
} EimproDpcEsdUseRbJudge;

/** Use of G pixel in RB judgment of edge storage defect correction.
*/
typedef enum {
	/**< Over-correction degree for correction is not used in edge storage defect correction.	*/
	ImproSrodpc_E_IM_PRO_DPC_ESD_USE_OCD_DIS = 0,
	/**< Over-correction degree for correction is used in edge storage defect correction.	*/
	ImproSrodpc_E_IM_PRO_DPC_ESD_USE_OCD_EN,
} EimproDpcEsdUseOcd;

/** Use of over-correction degree for pixel value magnitude defect correction.
*/
typedef enum {
	/**< Over-correction degree for correction is not used in pixel value magnitude defect correction.	*/
	ImproSrodpc_E_IM_PRO_DPC_MDC_USE_OCD_DIS = 0,
	/**< Over-correction degree for correction is used in pixel value magnitude defect correction.	*/
	ImproSrodpc_E_IM_PRO_DPC_MDC_USE_OCD_EN,
} EimproDpcMdcUseOcd;


/** DPC Area information
*/
typedef struct {
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	/**< global Compensation horizontal direction start position value range		:[0 - 2496]
	 *  target registor	:@@DPCGH	*/
	USHORT	gPosX;
	/**< global Compensation vertical direction start position value range		:[0 - 8960]
	 * 2pixel boundary target registor	:@@DPCGV	*/
	USHORT	gPosY;
	/**< global horizontal size value range		:[10 - 2496]
	 *  2byte boundary target registor	:@@DPCGHW	*/
	USHORT	gWidth;
	/**< global vertical size value range		:[10 - 8960] 2pixel boundary target registor	:@@DPCGVW	*/
	USHORT	gLines;
	/**< Compensation horizontal direction start position value range		:[0 - 2486]
	 *  2pixel boundary target registor	:@@DPCH		*/
	USHORT	posX;
	/**< Compensation vertical direction start position value range		:[0 - 8950]
	 * 2pixel boundary target registor	:@@DPCV		*/
	USHORT	posY;
	/**< horizontal size value range		:[10 - 2496] 2byte boundary target registor	:@@DPCHW	*/
	USHORT	width;
	/**< vertical size value range		:[10 - 8960] 2pixel boundary target registor	:@@DPCVW	*/
	USHORT	lines;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	/**< global Compensation horizontal direction start position value range		:[0 - 2900]
	 *  target registor	:@@DPCGH	*/
	USHORT	gPosX;
	/**< global Compensation vertical direction start position value range		:[0 - 8960]
	 * 2pixel boundary target registor	:@@DPCGV	*/
	USHORT	gPosY;
	/**< global horizontal size value range		:[10 - 2900] 2byte boundary target registor	:@@DPCGHW	*/
	USHORT	gWidth;
	/**< global vertical size value range		:[10 - 8960] 2pixel boundary target registor	:@@DPCGVW	*/
	USHORT	gLines;
	/**< Compensation horizontal direction start position value range		:[0 - 2890]
	 *  2pixel boundary target registor	:@@DPCH		*/
	USHORT	posX;
	/**< Compensation vertical direction start position value range		:[0 - 8950]
	 * 2pixel boundary target registor	:@@DPCV		*/
	USHORT	posY;
	/**< horizontal size value range		:[10 - 2900] 2byte boundary target registor	:@@DPCHW	*/
	USHORT	width;
	/**< vertical size value range		:[10 - 8960] 2pixel boundary target registor	:@@DPCVW	*/
	USHORT	lines;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
} TimproDpcArea;

/** DPC Control information
*/
typedef struct {
	/**< Defect correction mode. target registor	:@@DPCMD */
	EimproDpcMode					dpcMode;
	/**< Dynamic defect determination threshold zero conversion for
	 * registration defective pixel. target registor	:@@DPCRTZ */
	EimproDpcThreConvToZero		threConv0;
} TimproDpcCtrl;

/** Alpha blend Control information
*/
typedef struct {
	/**< alpha blend transition width (plus side) value range		:[0 - 15] target registor	:@@DPCBLWP */
	UCHAR								alphaBlendTransitionWidthP;
	/**< alpha blend start position (plus side) value range		:[0 - 16383] target registor	:@@DPCBLSP */
	USHORT								alphaBlendStartPosP;
	/**< alpha blend transition width (minus side) value range		:[0 - 15] target registor	:@@DPCBLWM */
	UCHAR								alphaBlendTransitionWidthM;
	/**< alpha blend transition position (minus side) value range		:[0 - 16383] target registor	:@@DPCBLSM */
	USHORT								alphaBlendStartPosM;
} TimproDpcAbCtrl;

/** Defect Dynamic Detection Control information
*/
typedef struct {
	/**< reference mode of gr/gb pixel in the defect dynamic detection and pixel value magnitude
	 *  defect correction. target registor	:@@DFGRGB */
	EimproDpcDdGrgb						grgbIndependentSetting;
	/**< dynamic detection mode of G pixel in the defect dynamic detection. target registor	:@@DFMDG */
	EimproDpcDdModeG						gMode;
	/**< dynamic detection mode of rr/bb pixel in the defect dynamic detection. target registor	:@@DFMDRB */
	EimproDpcDdModeRb						rbMode;
	/**< limit value of the registration defective pixel existing in the surrounding of the focus pixel in the defect
	 * dynamic detection. value range		:[0 - 6] target registor	:@@DFDCNT */
	UCHAR										upperLimitLocalRegistration;
	/**< Use of mis-determination degree for correction. target registor	:@@DFRBUG */
	EimproDpcDdUseMdd						useMdd;
	/**< Mis-determination degree for correction  horizontal and vertical 2-concecutive defect
	 * support. target registor	:@@DFAGND */
	EimproDpcDdMdd2consecutiveDefect		support2concecutiveDefect;
	/**< value of the start position related to the dynamic defect determination threshold for each
	 * rr/G/bb pixel at the plus side. value range		:[0 - 16383] target registor	:@@DFSRP/GP/BP */
	USHORT										pThresholdStartPos[3];
	/**< value of the start position related to the dynamic defect determination threshold for each
	 *  rr/G/bb pixel at the minus side. value range		:[0 - 16383] target registor	:@@DFSRM/GM/BM */
	USHORT										mThresholdStartPos[3];
	/**< offset value related to the dynamic defect determination threshold for each rr/G/bb pixel
	 * at the plus side. value range		:[0 - 16383] target registor	:@@DFORP/GP/BP */
	USHORT										pThresholdStartOffset[3];
	/**< offset value related to the dynamic defect determination threshold for each rr/G/bb pixel
	 *  at the minus side. value range		:[0 - 16383] target registor	:@@DFORM/GM/BM */
	USHORT										mThresholdStartOffset[3];
	/**< gain value related to the dynamic defect determination threshold for each rr/G/bb pixel
	 *  at the plus side. value range		:[0 - 63(=3.9375)] target registor	:@@DFKRP/GP/BP */
	UCHAR										pThresholdGain[3];
	/**< gain value related to the dynamic defect determination threshold for each rr/G/bb pixel
	 * at the minus side. value range		:[0 - 63(=3.9375)] target registor	:@@DFKRM/GM/BM */
	UCHAR										mThresholdGain[3];
	/**< upper limit value of the dynamic defect determination threshold for each rr/G/bb pixel
	 *  at the plus side. value range		:[0 - 16383] target registor	:@@DFHRP/GP/BP */
	USHORT										pThresholdUpperLimit[3];
	/**< upper limit value of the dynamic defect determination threshold for each rr/G/bb pixel
	 *  at the minus side. value range		:[0 - 16383] target registor	:@@DFHRM/GM/BM */
	USHORT										mThresholdUpperLimit[3];
	/**<  plus side setting value of the threshold used to determine the 2-consecutive defect pixels
	 * . value range		:[0 - 63] target registor	:@@DFCSRP */
	UCHAR										pthreshold2consecutive;
	/**< minus side setting value of the threshold used to determine the 2-consecutive defect pixels
	 * . value range		:[0 - 63] target registor	:@@DFCSRM */
	UCHAR										mthreshold2consecutive;
	/**< setting values of the threshold used to determine the 2-consecutive bright spot pixels
	 * . value range		:[0 - 4095]< target registor	:@@DFLSTHR/G/bb */
	USHORT										threshold2consecutiveBrightPix[3];
} TimproDpcDddCtrl;

/** Calculation of mis-determination degree for correction Control information
*/
typedef struct {
	/**< parameter of the plus side related to the calculation of mis-determination degree effect for
	 * correction. value range		:[0 - 7] target registor	:@@DFAGEFP */
	UCHAR										pMddEffect;
	/**< parameter of the minus side related to the calculation of mis-determination degree effect for
	 *  correction. value range		:[0 - 7] target registor	:@@DFAGEFM */
	UCHAR										mMddEffect;
	/**< parameter of the plus side related to the calculation of mis-determination degree effect2 for
	 * correction. value range		:[0 - 3] target registor	:@@DFAGEFP2 */
	UCHAR										pMddEffect2;
	/**< parameter of the minus side related to the calculation of mis-determination degree effect2 for
	 * correction. value range		:[0 - 3] target registor	:@@DFAGEFM2 */
	UCHAR										mMddEffect2;
	/**< offset value of the plus side related to the mis-determination degree threshold for correction.
	 *  value range		:[0 - 1023] target registor	:@@DFAGTHP */
	USHORT										pThresholdOffset;
	/**< offset value of the minus side related to the mis-determination degree threshold for correction.
	 *  value range		:[0 - 1023] target registor	:@@DFAGTHM */
	USHORT										mThresholdOffset;
	/**< gain value of the plus side related to the mis-determination degree threshold for correction.
	 * value range		:[0 - 63(=0.984375)] target registor	:@@DFAGTHKP */
	UCHAR										pThresholdGain;
	/**< gain value of the minus side related to the mis-determination degree threshold for correction.
	 *  value range		:[0 - 63(=0.984375)] target registor	:@@DFAGTHKM */
	UCHAR										mThresholdGain;
} TimproDpcMddCtrl;

/** Edge strage defect correction Control information
*/
typedef struct {
	/**< reference mode of gr/gb pixel in the edge storage defect correction. target registor	:@@DEGRGB */
	EimproDpcEsdMode						esdMode;
	/**< Use of G pixel in RB judgment of edge storage defect correction. target registor	:@@DERBUG */
	EimproDpcEsdUseRbJudge				useRbJdge;
	/**< Use of G pixel in RB judgment of edge storage defect correction. target registor	:@@DEGUG */
	EimproDpcEsdUseOcd					useOcd;
	/**< start position related to the noise determination threshold of the edge storage defect correction.
	 *  value range		:[0 - 16383] target registor	:@@DENSS */
	USHORT										thresholdStartPos;
	/**< offset related to the noise determination threshold of the edge storage defect correction.
	 * value range		:[0 - 16383] target registor	:@@DENSO */
	USHORT										thresholdOffset;
	/**< gain related to the noise determination threshold of the edge storage defect correction.
	 *  value range		:[0 - 255(=3.984375)] target registor	:@@DENSK */
	UCHAR										thresholdGain;
	/**< upper limit value related to the noise determination threshold of the edge storage defect correction.
	 *  value range		:[0 - 16383] target registor	:@@DENSH */
	USHORT										thresholdUpperLimit;
	/**< value related to the noise tolerance of the edge storage defect correction.
	 * value range		:[1 - 5] target registor	:@@DENSMGN */
	UCHAR										noiseTolerance;
	/**< threshold used to calculate the correction value in the edge storage defect correction.
	 * value range		:[0 - 16383] target registor	:@@DENDCTH */
	USHORT										thresholdCalculation;
	/**< correction level (the degree to soften the correction) based on the over-correction
	 * degree(plus side) for correction in the edge storage defect correction. value range
	 * 	:[0 - 63(=3.9375)] target registor	:@@DEAGKP */
	UCHAR										pCorrectionLevelOnOcd;
	/**< correction level (the degree to soften the correction) based on the over-correction
	 *  degree(minus side) for correction in the edge storage defect correction. value range
	 *  	:[0 - 63(=3.9375)] target registor	:@@DEAGKM */
	UCHAR										mCorrectionLevelOnOcd;
} TimproDpcEsdcCtrl;

/** Calculation of over-correction degree for correction Control information
*/
typedef struct {
	/**< parameters related to the calculation of over-correction degree(plus side) for correction.
	 * They are used both in the pixel value magnitude defect correction and the edge storage
	 *  defect correction. value range		:[0 - 7] target registor	:@@DCAGEFP */
	UCHAR										pOcdEffect;
	/**< parameters related to the calculation of over-correction degree(minus side) for correction.
	 * <br>They are used both in the pixel value magnitude defect correction and the edge storage
	 * defect correction. value range		:[0 - 7] target registor	:@@DCAGEFM */
	UCHAR										mOcdEffect;
	/**< threshold for over-correction degree(plus side) for correction. They are used both in the
	 * pixel value magnitude defect correction and the edge storage defect correction.value range
	 * 	:[0 - 16383] target registor	:@@DCAGTHP */
	USHORT										pThreshold;
	/**< threshold for over-correction degree(minus side) for correction. They are used both in the
	 *  pixel value magnitude defect correction and the edge storage defect correction.value range
	 *  	:[0 - 16383] target registor	:@@DCAGTHM */
	USHORT										mThreshold;
} TimproDpcOcdCtrl;

/** Pixel value magnitude defect correction Control information
*/
typedef struct {
	/**< Use of over-correction degree for pixel value magnitude defect correction. target registor	:@@DMGUG */
	EimproDpcMdcUseOcd					useOcd;
	/**< amount to soften the correction in single defective pixel correction of pixel value(plus side) magnitude
	 *  defect correction. value range		:[0 - 1023] target registor	:@@DMWKSP */
	USHORT										pManualAdjValSingle;
	/**< amount to soften the correction in single defective pixel correction of pixel value(minus side)
	 * magnitude defect correction. value range		:[0 - 1023] target registor	:@@DMWKSM */
	USHORT										mManualAdjValSingle;
	/**< amount to soften the correction in 2-concecutive defective pixel correction of pixel value(plus side)
	 *  magnitude defect correction. value range		:[0 - 1023] target registor	:@@DMWKDP */
	USHORT										pManualAdjVal2consecutive;
	/**< amount to soften the correction in 2-concecutive defective pixel correction of pixel value(minus side)
	 *  magnitude defect correction. value range		:[0 - 1023] target registor	:@@DMWKDM */
	USHORT										mManualAdjVal2consecutive;
	/**< correction level (the degree to soften the correction) based on the over-correction degree for
	 *  correction in the pixel value(plus side) magnitude defect correction. value range
	 *  	:[0 - 63(=3.9375)] target registor	:@@DMAGKP */
	UCHAR										pCorrectionLevelOnOcd;
	/**< correction level (the degree to soften the correction) based on the over-correction degree for
	 *  correction in the pixel value(minus side) magnitude defect correction. value range
	 *  	:[0 - 63(=3.9375)] target registor	:@@DMAGKM */
	UCHAR										mCorrectionLevelOnOcd;
} TimproDpcMdcCtrl;

/** RDMA I/F DPC register address information
*/
typedef struct {
	/**< 2840_(9118 - 911Bh) */
	ULONG	dpcmd;
	/**< 2840_(911C - 911Fh) */
	ULONG	dpcblp;
	/**< 2840_(9120 - 9123h) */
	ULONG	dpcblm;
	/**< 2840_(9124 - 9127h) */
	ULONG	dfctl;
	/**< 2840_(9130 - 9133h) */
	ULONG	dfs1;
	/**< 2840_(9134 - 9137h) */
	ULONG	dfs2;
	/**< 2840_(9138 - 913Bh) */
	ULONG	dfs3;
	/**< 2840_(9140 - 9143h) */
	ULONG	dfo1;
	/**< 2840_(9144 - 9147h) */
	ULONG	dfo2;
	/**< 2840_(9148 - 914Bh) */
	ULONG	dfo3;
	/**< 2840_(9150 - 9153h) */
	ULONG	dfk1;
	/**< 2840_(9154 - 9157h) */
	ULONG	dfk2;
	/**< 2840_(9158 - 915Bh) */
	ULONG	dfk3;
	/**< 2840_(9160 - 9163h) */
	ULONG	dfh1;
	/**< 2840_(9164 - 9167h) */
	ULONG	dfh2;
	/**< 2840_(9168 - 916Bh) */
	ULONG	dfh3;
	/**< 2840_(9170 - 9173h) */
	ULONG	dfcsr;
	/**< 2840_(9178 - 917Bh) */
	ULONG	dflsth1;
	/**< 2840_(917C - 917Fh) */
	ULONG	dflsth2;
	/**< 2840_(9180 - 9183h) */
	ULONG	dfagef;
	/**< 2840_(9184 - 9187h) */
	ULONG	dfagef2;
	/**< 2840_(9188 - 918Bh) */
	ULONG	dfagth;
	/**< 2840_(918C - 918Fh) */
	ULONG	dfagthk;
	/**< 2840_(9190 - 9193h) */
	ULONG	dmctl;
	/**< 2840_(9194 - 9197h) */
	ULONG	dmwks;
	/**< 2840_(9198 - 919Bh) */
	ULONG	dmwkd;
	/**< 2840_(919C - 919Fh) */
	ULONG	dmagk;
	/**< 2840_(91A0 - 91A3h) */
	ULONG	dectl;
	/**< 2840_(91A4 - 91A7h) */
	ULONG	denss;
	/**< 2840_(91A8 - 91ABh) */
	ULONG	denso;
	/**< 2840_(91AC - 91AFh) */
	ULONG	densk;
	/**< 2840_(91B0 - 91B3h) */
	ULONG	densh;
	/**< 2840_(91B4 - 91B7h) */
	ULONG	densmgn;
	/**< 2840_(91B8 - 91BBh) */
	ULONG	dendcth;
	/**< 2840_(91BC - 91BFh) */
	ULONG	deagk;
	/**< 2840_(91C0 - 91C3h) */
	ULONG	dcagef;
	/**< 2840_(91C4 - 91C7h) */
	ULONG	dcagth;
} TimproRdmaDpcAddr;

/*类型定义区域*/
typedef struct _ImproSrodpc							ImproSrodpc;
typedef struct _ImproSrodpcPrivate				ImproSrodpcPrivate;


/*对象结构体区域*/
struct _ImproSrodpc
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_srodpc_get_type(void);
ImproSrodpc*		impro_srodpc_new();
/**
Compensation mode start
@param[in]	unitNo : Unit number.
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_srodpc_start( E_IM_PRO_UNIT_NUM unitNo );
/**
Compensation mode stop
@param[in]	unitNo : Unit number.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_srodpc_stop( E_IM_PRO_UNIT_NUM unitNo, UCHAR force );
/**
DPC control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcCtrl : DPC control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srodpc_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcCtrl* dpcCtrl );
/**
A setup of enable access to the built-in RAM of DPC.
@param[in]	unitNo : Unit number.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_srodpc_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg );
/**
DPC control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcArea : DPC control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srodpc_set_area( E_IM_PRO_UNIT_NUM unitNo, TimproDpcArea* dpcArea );
/**
Alpha blend control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcAbCtrl : Alpha blend Control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srodpc_alpha_blend_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcAbCtrl* dpcAbCtrl );
/**
Defect Dynamic Detection control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcDddCtrl : Defect Dynamic Detection Control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srodpc_dynamic_detect_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcDddCtrl* dpcDddCtrl );
/**
Calculation of mis-determination degree control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcMddCtrl : Calculation of mis-determination degree for correction Control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srodpc_mis_determination_calc_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcMddCtrl* dpcMddCtrl );
/**
Pixel value magnitude defect correction control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcMdcCtrl : Pixel value magnitude defect correction control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srodpc_magnitude_defect_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcMdcCtrl* dpcMdcCtrl );
/**
Edge storage defect correction control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcEsdcCtrl : Edge storage defect correction Control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srodpc_edge_storage_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcEsdcCtrl* dpcEsdcCtrl );
/**
Calculation of over-correction degree for correction control setup
@param[in]	unitNo : Unit number.
@param[in]	dpcOcdCtrl : Calculation of over-correction degree for correction control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srodpc_over_correction_detect_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproDpcOcdCtrl* dpcOcdCtrl );
/**
Get the top address of the address array of DPC control.
@param[in]		unitNo : Unit number.
@param[out]		addr					: Top address of the address array of SDC control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
extern	INT32			impro_srodpc_get_rdma_addr_dpc_cntl( E_IM_PRO_UNIT_NUM unitNo, const TimproRdmaDpcAddr** addr );




#endif /* __IMPRO_SRODPC_H__ */

