/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李昕
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

#ifndef _IM_ELA_H_
#define _IM_ELA_H_

#include <klib.h>
#include "imelareg.h"
#include "driver_common.h"

#define IM_TYPE_ELA		(im_ela_get_type())
#define IM_ELA(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImEla))
#define IM_IS_ELA(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_ELA))

#define im_ela_get_g_im_ela_stage_cnt(self)         (&(self->gImElaStageCnt))
#define im_ela_set_g_im_ela_stage_cnt(self,g)         {self->gImElaStageCnt = g;}
#define im_ela_get_g_im_ela_step_cnt(self)         (&(self->gImElaStepCnt))
#define im_elaeg_set_g_im_ela_step_cnt(self,g)         {self->gImElaStepCnt = g;}
#define im_ela_get_g_im_ela_next_ctrl_flag(self)         (&(self->gImElaNextCtrlFlag))
#define im_ela_set_g_im_ela_next_ctrl_flag(self,g)         {self->gImElaNextCtrlFlag = g;}
#define im_ela_get_g_im_ela_bayer(self)         (&(self->gImElaBayer))
#define im_elaeg_set_g_im_ela_bayer(self,g)         {self->gImElaBayer = g;}
#define im_ela_get_g_im_ela_ctrl_common_info(self)         (&(self->gImElaCtrlCommonInfo))
#define im_ela_set_g_im_ela_ctrl_common_info(self,g)         {self->gImElaCtrlCommonInfo = g;}
#define im_ela_get_g_im_ela_qelatmd_info(self)         (&(self->gImElaQelatmdInfo))
#define im_ela_set_g_im_ela_qelatmd_info(self,g)         {self->gImElaQelatmdInfo = g;}
#define im_ela_get_g_im_ela_multiple_exec_info(self)         (&(self->gImElaMultipleExecInfo))
#define im_ela_set_g_im_ela_multiple_exec_info(self,g)         {self->gImElaMultipleExecInfo = g;}
#define im_ela_get_g_im_ela_callback_func(self)         (&(self->gImElaCallbackFunc))
#define im_ela_set_g_im_ela_callback_func(self,g)         {self->gImElaCallbackFunc = g;}
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
// result
#define	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		(D_IM_ELA | D_DDIM_INPUT_PARAM_ERROR)	/**< Processing result code<br> Input parameter error			(0x0A000001) */
#define	ImEla_D_IM_ELA_MACRO_BUSY				(D_IM_ELA | D_DDIM_MACRO_BUSY_NG)		/**< Processing result code<br> Macro busy 						(0x0A000005) */
#define  ImEla_D_IM_ELA_SEM_NG					(D_IM_ELA | D_DDIM_SEM_NG)				/**< Processing result code<br> Semaphore acquisition NG		(0x0A000010) */
#define	ImEla_D_IM_ELA_SEM_TIMEOUT_ERR		(D_IM_ELA | D_DDIM_SEM_TIMEOUT)			/**< Processing result code<br> Semaphore acquisition Time Out	(0x0A000011) */
#define	ImEla_D_IM_ELA_TIMEOUT				(D_IM_ELA | D_DDIM_TIMEOUT)				/**< Processing result code<br> Time Out 						(0x0A000013) */
#define	ImEla_D_IM_ELA_NG						(D_IM_ELA | D_DDIM_SYSTEM_ERROR)		/**< Processing result code<br> Processing NG					(0x0A000099) */
#define	ImEla_D_IM_ELA_PROCESS_END			(D_IM_ELA | 0x000000FF)					/**< Processing result code<br> Process End 					(0x0A0000FF) */

/** Function Enable
*/
#define	ImEla_D_IM_ELA_DISABLE				(0)				/**< Disable						*/
#define	ImEla_D_IM_ELA_ENABLE					(1)				/**< Enable							*/

// ELA Register - NSLMD (Noise data mode )
/** Noise data mode
*/
#define	ImEla_D_IM_ELA_NSLMD_REDUCTION		0x00			/**< Noise data mode : Reduction mode 			*/
#define	ImEla_D_IM_ELA_NSLMD_SAME				0x01			/**< Noise data mode : Same magnification mode	*/
																/* @NSLMD.NSLMD					*/

/** Noise data precision
*/
#define	ImEla_D_IM_ELA_NSLRES_PRECISION_1		0x00			/**< Noise data precision : Precision 1	*/
#define	ImEla_D_IM_ELA_NSLRES_PRECISION_2		0x01			/**< Noise data precision : Precision 2	*/
#define	ImEla_D_IM_ELA_NSLRES_PRECISION_3		0x02			/**< Noise data precision : Precision 3	*/
#define	ImEla_D_IM_ELA_NSLRES_PRECISION_4		0x03			/**< Noise data precision : Precision 4	*/
																/* @NSLMD.NSLMD					*/

/** Bayer data start-pixel type
*/
#define	ImEla_D_IM_ELA_ORG_R					0x00			/**< Bayer data start-pixel type : R Pixel 		*/
#define	ImEla_D_IM_ELA_ORG_B					0x01			/**< Bayer data start-pixel type : B Pixel 		*/
#define	ImEla_D_IM_ELA_ORG_GR					0x02			/**< Bayer data start-pixel type : Gr Pixel 	*/
#define	ImEla_D_IM_ELA_ORG_GB					0x03			/**< Bayer data start-pixel type : Gb Pixel 	*/
																/* @BYRTYP.ORG					*/

/**	Bayer input/output data type
*/
#define	ImEla_D_IM_ELA_DATATYP_8BIT			0x00			/**< Bayer input/output data type : 8bits data	*/
#define	ImEla_D_IM_ELA_DATATYP_12BIT			0x02			/**< Bayer input/output data type : 12bits pack data	*/
#define	ImEla_D_IM_ELA_DATATYP_16BIT			0x03			/**< Bayer input/output data type : 16bits data	*/
																/* @ELABYR.EIRTYP, ELABYR.EIWTYP		*/

/**	Bayer input/output bit shift mode
*/
#define	ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE	(0)			/**< Bayer input/output bit shift mode : No shift				*/
#define	ImEla_D_IM_ELA_BIT_SHIFT_MODE_R2		(1)			/**< Bayer input/output bit shift mode : 2bit right shift		*/
#define	ImEla_D_IM_ELA_BIT_SHIFT_MODE_R4		(2)			/**< Bayer input/output bit shift mode : 4bit right shift		*/
#define	ImEla_D_IM_ELA_BIT_SHIFT_MODE_L2		(3)			/**< Bayer input/output bit shift mode : 2bit shift to the left	*/
#define	ImEla_D_IM_ELA_BIT_SHIFT_MODE_L4		(4)			/**< Bayer input/output bit shift mode : 4bit shift to the left	*/

/**	Number of the output bayer data
*/
#define	ImEla_D_IM_ELA_EIWOUT_NONE			0x00			/**< Number of the output bayer data : none		*/
#define	ImEla_D_IM_ELA_EIWOUT_1				0x01			/**< Number of the output bayer data : 1		*/
#define	ImEla_D_IM_ELA_EIWOUT_4				0x02			/**< Number of the output bayer data : 4		*/
																/* @ELABYR.EIWOUT		*/

/**	Defect pixel correction mode
*/
#define	ImEla_D_IM_ELA_ELADCMD_OFF			0x00			/**< Defect pixel correction mode : Defect correction off						*/
#define	ImEla_D_IM_ELA_ELADCMD_WEAK			0x01			/**< Defect pixel correction mode : Defect tolerance on(comparatively weak)		*/
#define	ImEla_D_IM_ELA_ELADCMD_STRONG			0x03			/**< Defect pixel correction mode : Defect tolerance on(comparatively strong)	*/
																/* @BYRTYP.ELADCMD		*/

#define	ImEla_D_IM_ELA_EIWCH_ADDR_MAX			(4)				/**< The maximum values of output bayer data top address			*/
#define	ImEla_D_IM_ELA_ENRECH_ADDR_MAX		(16)			/**< The maximum values of input extraction noise data top address	*/
#define	ImEla_D_IM_ELA_EACH_DATA_MAX			(3)				/**< The maximum values of EAch data								*/
#define	ImEla_D_IM_ELA_DEKNEE_TBL_MAX			(256)			/**< The maximum values of Deknee table data						*/

// The kind of channel which the error generated
#define  ImEla_D_IM_ELA_NORMAL_END				(0x00)			/**< Normal end.<br> */
#define  ImEla_D_IM_ELA_AXI_ERR_CH_W			(0x01)			/**< The AXI error occurred by the write channel.<br> */
#define  ImEla_D_IM_ELA_AXI_ERR_CH_R			(0x02)			/**< The AXI error occurred by the read channel.<br> */
#define  ImEla_D_IM_ELA_AXI_ERR_CH_RW			(0x03)			/**< The AXI error occurred by the read channel and write channel.<br> */

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/**	ELF luminance threshold selection. */
typedef enum {
	ImEla_E_IM_ELA_ELFL_T1 = 0,				/**< ELF luminance threshold 1	*/
	ImEla_E_IM_ELA_ELFL_T2,					/**< ELF luminance threshold 2	*/
	ImEla_E_IM_ELA_ELFL_T3,					/**< ELF luminance threshold 3	*/
	ImEla_E_IM_ELA_ELFL_T4,					/**< ELF luminance threshold 4	*/
	ImEla_E_IM_ELA_ELFL_MAX					/**< Enumeration stopper */
} ImElaEImElaElfl;

/**	Noise characteristics selection. */
typedef enum {
	ImEla_E_IM_ELA_ANB_1 = 0,					/**< Noise characteristics number-1	*/
	ImEla_E_IM_ELA_ANB_2,						/**< Noise characteristics number-2	*/
	ImEla_E_IM_ELA_ANB_3,						/**< Noise characteristics number-3	*/
	ImEla_E_IM_ELA_ANB_4,						/**< Noise characteristics number-4	*/
	ImEla_E_IM_ELA_ANB_MAX					/**< Enumeration stopper */
} ImElaEImElaAnb;

/**	Edge degree threshold selection. */
typedef enum {
	ImEla_E_IM_ELA_ALNGE_1 = 0,				/**< Edge degree threshold number-1	*/
	ImEla_E_IM_ELA_ALNGE_2,					/**< Edge degree threshold number-2	*/
	ImEla_E_IM_ELA_ALNGE_3,					/**< Edge degree threshold number-3	*/
	ImEla_E_IM_ELA_ALNGE_MAX					/**< Enumeration stopper */
} ImElaEImElaAlnge;

/**	NR intensity selection. */
typedef enum {
	ImEla_E_IM_ELA_ALNG_L1E1N = 0,			/**< Luminance L1, Edge E1	*/
	ImEla_E_IM_ELA_ALNG_L1E2N,				/**< Luminance L1, Edge E2	*/
	ImEla_E_IM_ELA_ALNG_L1E3N,				/**< Luminance L1, Edge E3	*/
	ImEla_E_IM_ELA_ALNG_L2E1N,				/**< Luminance L2, Edge E1	*/
	ImEla_E_IM_ELA_ALNG_L2E2N,				/**< Luminance L2, Edge E2	*/
	ImEla_E_IM_ELA_ALNG_L2E3N,				/**< Luminance L2, Edge E3	*/
	ImEla_E_IM_ELA_ALNG_L3E1N,				/**< Luminance L3, Edge E1	*/
	ImEla_E_IM_ELA_ALNG_L3E2N,				/**< Luminance L3, Edge E2	*/
	ImEla_E_IM_ELA_ALNG_L3E3N,				/**< Luminance L3, Edge E3	*/
	ImEla_E_IM_ELA_ALNG_L4E1N,				/**< Luminance L4, Edge E1	*/
	ImEla_E_IM_ELA_ALNG_L4E2N,				/**< Luminance L4, Edge E2	*/
	ImEla_E_IM_ELA_ALNG_L4E3N,				/**< Luminance L4, Edge E3	*/
	ImEla_E_IM_ELA_ALNG_MAX					/**< Enumeration stopper */
} ImElaEImElaAlng;

/**	Edge applicable threshold contour L selection. */
typedef enum {
	ImEla_E_IM_ELA_LCOME_1 = 0,				/**< Edge applicable threshold contour L number-1	*/
	ImEla_E_IM_ELA_LCOME_2,					/**< Edge applicable threshold contour L number-2	*/
	ImEla_E_IM_ELA_LCOME_MAX					/**< Enumeration stopper */
} ImElaEImElaLcome;

/**	Applied intensity L selection. */
typedef enum {
	ImEla_E_IM_ELA_LCOMEN_1 = 0,				/**< Applied intensity L number-1	*/
	ImEla_E_IM_ELA_LCOMEN_2,					/**< Applied intensity L number-2	*/
	ImEla_E_IM_ELA_LCOMEN_MAX					/**< Enumeration stopper */
} ImElaEImElaLcomen;

/**	Adjustment method parameter selection. */
typedef enum {
	ImEla_E_IM_ELA_ELF_LEVEL_0 = 0,			/**< Level 0 : Suppress the noise components of up to 9 pixels wavelength (Not used)	*/
	ImEla_E_IM_ELA_ELF_LEVEL_1,				/**< Level 1 : Suppress the noise components of up to 16 pixels wavelength	*/
	ImEla_E_IM_ELA_ELF_LEVEL_2,				/**< Level 2 : Suppress the noise components of up to 32 pixels wavelength	*/
	ImEla_E_IM_ELA_ELF_LEVEL_3,				/**< Level 3 : Suppress the noise components of up to 64 pixels wavelength	*/
	ImEla_E_IM_ELA_ELF_LEVEL_4,				/**< Level 4 : Suppress the noise components of up to 128 pixels wavelength	*/
	ImEla_E_IM_ELA_ELF_LEVEL_5,				/**< Level 5 : Suppress the noise components of up to 256 pixels wavelength	*/
	ImEla_E_IM_ELA_ELF_LEVEL_MAX				/**< Enumeration stopper */
} ImElaEImElaQelflvl;

/**	ELA density mode selection. */
typedef enum {
	ImEla_E_IM_ELA_DENSITY_MODE_0 = 0,		/**< ELA density mode 0<br>
											 Noise output data size : Reduction<br>
											 Number of noise data inputs : 1	*/
	ImEla_E_IM_ELA_DENSITY_MODE_1,			/**< ELA density mode 1<br>
											 Noise output data size : Same magnification<br>
											 Number of noise data inputs : 1	*/
	ImEla_E_IM_ELA_DENSITY_MODE_2,			/**< ELA density mode 2<br>
											 Noise output data size : Same magnification<br>
											 Number of noise data inputs : 4	*/
	ImEla_E_IM_ELA_DENSITY_MODE_3,			/**< ELA density mode 3<br>
											 Noise output data size : Same magnification<br>
											 Number of noise data inputs : 16	*/
	ImEla_E_IM_ELA_DENSITY_MODE_MAX			/**< Enumeration stopper */
} ImElaEImElaQelamd;

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
typedef VOID (*TImElaCallback)( ULONG interruptFlagMask );	/**< Callback function pointer	*/

/** ELA common control data */
typedef struct {
	UCHAR	noiseDataMode;							/**< NSLMD.NSLMD	: Noise data mode
														     <ul><li>@ref ImEla_D_IM_ELA_NSLMD_REDUCTION
																 <li>@ref ImEla_D_IM_ELA_NSLMD_SAME</ul>	*/
	UCHAR	noiseDataPrecision;						/**< NSLMD.NSLRES	: Noise data precision
														     <ul><li>@ref ImEla_D_IM_ELA_NSLRES_PRECISION_1
																 <li>@ref ImEla_D_IM_ELA_NSLRES_PRECISION_2
																 <li>@ref ImEla_D_IM_ELA_NSLRES_PRECISION_3
																 <li>@ref ImEla_D_IM_ELA_NSLRES_PRECISION_4</ul>
<pre>
	ImEla_D_IM_ELA_NSLRES_PRECISION_1 : High, Maximum amplitude : Small
	ImEla_D_IM_ELA_NSLRES_PRECISION_2 :  |  , Maximum amplitude :   |
	ImEla_D_IM_ELA_NSLRES_PRECISION_3 :  |  , Maximum amplitude :   |
	ImEla_D_IM_ELA_NSLRES_PRECISION_4 : Low , Maximum amplitude :  Wide
</pre>
																 	*/
	UCHAR	noiseDataCompressEnable;					/**< NSLMD.NSLKNE	: Noise data compression enable
														     <ul><li>@ref ImEla_D_IM_ELA_DISABLE
																 <li>@ref ImEla_D_IM_ELA_ENABLE</ul>	*/
	UCHAR	bayerStartPixelType;						/**< BYRTYP.ORG	: Bayer data start-pixel type
														     <ul><li>@ref ImEla_D_IM_ELA_ORG_R
																 <li>@ref ImEla_D_IM_ELA_ORG_B
																 <li>@ref ImEla_D_IM_ELA_ORG_GR
																 <li>@ref ImEla_D_IM_ELA_ORG_GB</ul>	*/
} TImElaCtrlCommon;

/** ELA bayer data control data */
typedef struct {
	UCHAR	inDataType;						/**< ELABYR.EIRTYP	: Input data type
												     <ul><li>@ref ImEla_D_IM_ELA_DATATYP_8BIT
														 <li>@ref ImEla_D_IM_ELA_DATATYP_12BIT
														 <li>@ref ImEla_D_IM_ELA_DATATYP_16BIT</ul>	*/
	UCHAR	inDataShiftMode;					/**< ELABYR.EIRSFT	: Input bit shift mode
												     <ul><li>@ref ImEla_D_IM_ELA_BIT_SHIFT_MODE_R2
														 <li>@ref ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE
														 <li>@ref ImEla_D_IM_ELA_BIT_SHIFT_MODE_L2 (Some saturation compensation)
														 <li>@ref ImEla_D_IM_ELA_BIT_SHIFT_MODE_L4 (Some saturation compensation)</ul>	*/
	UCHAR	outDataType;						/**< ELABYR.EIWTYP	: Output data type
												     <ul><li>@ref ImEla_D_IM_ELA_DATATYP_8BIT
														 <li>@ref ImEla_D_IM_ELA_DATATYP_12BIT</ul>	*/
	UCHAR	outDataShiftMode;				/**< ELABYR.EIWSFT	: Output bit shift mode
												     <ul><li>@ref ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE
														 <li>@ref ImEla_D_IM_ELA_BIT_SHIFT_MODE_R2
														 <li>@ref ImEla_D_IM_ELA_BIT_SHIFT_MODE_R4</ul>	*/
	UCHAR	dekneeEnable;						/**< ELABYR.DKNEN	: Enabling the Deknee processing for bayer data entry
												     <ul><li>@ref ImEla_D_IM_ELA_DISABLE
														 <li>@ref ImEla_D_IM_ELA_ENABLE</ul>	*/
	UCHAR	obZsfEnable;						/**< ELABYR.EOBAEN	: Enabling the "OB correction"/"Optical zero shift" processing for bayer data entry
												     <ul><li>@ref ImEla_D_IM_ELA_DISABLE
														 <li>@ref ImEla_D_IM_ELA_ENABLE</ul>	*/
} TImElaCtrlByr;

/** Noise characteristics element */
typedef struct {
	USHORT	offset[ImEla_E_IM_ELA_ANB_MAX];		/**< ANBOR, ANBOG, ANBOB	: Offset noise characteristics (12bits)	*/
	USHORT	gain[ImEla_E_IM_ELA_ANB_MAX];			/**< ANBKR, ANBKG, ANBKB	: Gain noise characteristics (12bits)	*/
	USHORT	boundary[ImEla_E_IM_ELA_ANB_MAX];		/**< ANBDR, ANBDG, ANBDB	: Region boundary noise characteristics (12bits)	*/
} TImElaCtrlCoreAnb;

/** Noise extraction limit data control */
typedef struct {
	USHORT	noisePlusLimit;				/**< NSLNGLMT.NSLNGLMP	: Noise element plus side limit (10bits)		*/
	USHORT	noiseMinusLimit;				/**< NSLNGLMT.NSLNGLMM	: Noise element minus side limit (10bits)		*/
} TImElaCtrlLimit;

/** ELA core control data */
typedef struct {
	SHORT	opticalZeroLevelShift;			/**< EZSFTA1	: Optical zero level shift parameter (11bits signed)	*/
	TImElaCtrlLimit	limit;					/**< Noise extraction limit data control parameter				*/
	UCHAR	defectCorrectionMode;				/**< BYRTYP.ELADCMD	: Defect pixel correction mode
											     <ul><li>@ref ImEla_D_IM_ELA_ELADCMD_OFF
													 <li>@ref ImEla_D_IM_ELA_ELADCMD_WEAK
													 <li>@ref ImEla_D_IM_ELA_ELADCMD_STRONG</ul>									*/
	USHORT	zeroPointLevel;					/**< ELFZP	: Zero point level (12bits)											*/
	USHORT	elfLt[ImEla_E_IM_ELA_ELFL_MAX];			/**< ELFL	: ELF luminance threshold (12bits)<br>
													Please set up so that "elfLt[ImEla_E_IM_ELA_ELFL_T1] <= elfLt[ImEla_E_IM_ELA_ELFL_T2] <= elfLt[ImEla_E_IM_ELA_ELFL_T3] <= elfLt[ImEla_E_IM_ELA_ELFL_T4]" Always.	*/
	TImElaCtrlCoreAnb	anbR;				/**< Noise characteristics of the pixel R						 				*/
	TImElaCtrlCoreAnb	anbG;				/**< Noise characteristics of the pixel G						 				*/
	TImElaCtrlCoreAnb	anbB;				/**< Noise characteristics of the pixel B						 				*/
	USHORT	lumenGainR;						/**< LGTW.LGTWR	: R Gain for luminance (10bits)	<br>
													value range: [0 - 1023(=0/256 - 1023/256)]									*/
	USHORT	lumenGainG;						/**< LGTW.LGTWG	: G Gain for luminance (10bits)	<br>
													value range: [0 - 1023(=0/256 - 1023/256)]									*/
	USHORT	lumenGainB;						/**< LGTW.LGTWB	: B Gain for luminance (10bits)	<br>
													value range: [0 - 1023(=0/256 - 1023/256)]									*/
	USHORT	lumenFactorR;						/**< LGT.LGTR	: R factor for the luminance (5bits)	<br>
													value range: [0 - 31(=0/16 - 31/16)]										*/
	USHORT	lumenFactorG;						/**< LGT.LGTG	: G factor for the luminance (5bits)	<br>
													value range: [0 - 31(=0/16 - 31/16)]										*/
	USHORT	lumenFactorB;						/**< LGT.LGTB	: B factor for the luminance (5bits)	<br>
													value range: [0 - 31(=0/16 - 31/16)]										*/
	USHORT	lumenFactorC;						/**< LGT.LGTC	: Color difference parameter for the luminance (5bits)	<br>
													value range: [0 - 31(=0/16 - 31/16)]										*/
	USHORT	lumenEdgeR;						/**< LGTE.LGTER	: R factor for the degree of weight edge (5bits)	<br>
													value range: [0 - 31(=0/16 - 31/16)]										*/
	USHORT	lumenEdgeG;						/**< LGTE.LGTEG	: G factor for the degree of weight edge (5bits)	<br>
													value range: [0 - 31(=0/16 - 31/16)]										*/
	USHORT	lumenEdgeB;						/**< LGTE.LGTEB	: B factor for the degree of weight edge (5bits)	<br>
													value range: [0 - 31(=0/16 - 31/16)]										*/
	USHORT	edgeAdjustA1;						/**< EDG2ANBA.EDG2ANBA	: Set the degree adjustment factor-1 edge of A (8bits)	<br>
													value range: [0 - 255(=0/64 - 255/64)]										*/
	USHORT	edgeAdjustA2;						/**< EDGSCLA.EDGSCLA	: Set the degree adjustment factor-2 edge of A (10bits)	*/
	USHORT	edgeAdjustB1;						/**< EDG2ANBB.EDG2ANBB	: Set the degree adjustment factor-1 edge of B (10bits)	<br>
													value range: [0 - 1023(=0/64 - 1023/64)]										*/
	USHORT	edgeAdjustB2;						/**< EDGSCLB.EDGSCLB	: Set the degree adjustment factor-2 edge of B (10bits)	*/
	USHORT	edgeThreshold[ImEla_E_IM_ELA_ALNGE_MAX];	/**< ALNGE	: Edge degree threshold (12bits)<br>
													Please set up so that "edgeThreshold[ImEla_E_IM_ELA_ALNGE_1] <= edgeThreshold[ImEla_E_IM_ELA_ALNGE_2] <= edgeThreshold[ImEla_E_IM_ELA_ALNGE_3]" Always.	*/
	USHORT	nr[ImEla_E_IM_ELA_ALNG_MAX];				/**< ALNG	: NR intensity (9bits)<br>
													Set each degree the NR intensity in luminance(Lm), edge(En). (m=1~4, n=1~3)<br>
													Please set in the range of 0.0 to 1.0.	*/
	USHORT	lNoise;							/**< LFTH	: L extraction threshold noise (12bits)								*/
	USHORT	lEdge[ImEla_E_IM_ELA_LCOME_MAX];			/**< LCOME	: Edge applicable threshold contour L (12bits)<br>
													Please set up so that "lEdge[ImEla_E_IM_ELA_LCOMEN_1] <= lEdge[ImEla_E_IM_ELA_LCOME_2]" Always.	*/
	USHORT	lIntense[ImEla_E_IM_ELA_LCOMEN_MAX];		/**< LCOMEN	: Applied intensity L (9bits)<br>
													Please set in the range of 0.0 to 1.0.	*/
} TImElaCtrlCore;

/** OB Correction control */
typedef struct {
	SHORT	obRr;							/**< OBOF.EOBRR		: OB Correction R Pixel (11bits)					*/
	SHORT	obBb;							/**< OBOF.EOBBB		: OB Correction B Pixel (11bits)					*/
	SHORT	obGr;							/**< OBOF.EOBGR		: OB Correction Gr Pixel (11bits)					*/
	SHORT	obGb;							/**< OBOF.EOBGB		: OB Correction Gb Pixel (11bits)					*/
} TImElaCtrlObCorrection;

/** EIRch control */
typedef struct {
	ULONG	inBayerTopAddr;				/**< EIRA		: Input bayer data top address (32bits)<br>
													Set the address that contains the LSB bits of the first pixel.<br>
													When 16-bit, please set to be an even address this.	*/
	UCHAR	inBayerTopOffset;			/**< EIROFS		: Set LSB bit (bit number) of the beginning of the input pixel Bayer data. (3bits)<br>
													When the data type of 8/16 bit, please set the "000b" Always.<br>
													Only when the 12-bit pack data type, please select the settings for "000b" or "100b".	*/
	USHORT	inBayerTotalHsize;			/**< EIRDEF		: Input bayer data total horizontal size (15bits, Unit 16 byte, 16~32752)		*/
	USHORT	inBayerHsize;					/**< EIRHSIZ	: Input bayer data horizontal size (14bits, Unit 2 pixels, 320~15360)			*/
	USHORT	inBayerVline;					/**< EIRVSIZ	: Input bayer data vertical line (14bits, Unit 2 pixels, 240~8960)				*/
} TImElaCtrlEirch;

/** EIWch control */
typedef struct {
	UINT32	outBayerTopAddr[ImEla_D_IM_ELA_EIWCH_ADDR_MAX];	/**< EIWA	: Output bayer data top address (32bits, Unit 64 byte)	*/
	USHORT	outBayerTotalHsize;							/**< EIWDEF	: Output bayer data total horizontal size (14bits, Unit 64 byte, 64~16368)	*/
} TImElaCtrlEiwch;

/** ENWch control */
typedef struct {
	UINT32	outExtractNoiseTopAddr;		/**< ENWA	: Output extraction noise data top address (32bits, Unit 64 byte)	*/
	USHORT	outExtractNoiseTotalHsize;	/**< ENWDEF	: Output extraction noise data total horizontal size(14bits, Unit 64 byte)	*/
} TImElaCtrlEnwch;

/** ENREch control */
typedef struct {
	UINT32	inExtractNoiseTopAddr[ImEla_D_IM_ELA_ENRECH_ADDR_MAX];	/**< ENRA		: Input extraction noise data top address (32bits, Unit 64 byte)	*/
	USHORT	inExtractNoiseHsize;									/**< ENRHSIZ	: Input extraction noise data horizontal size(14bits, Unit 2 pixels)	*/
	USHORT	inExtractNoiseVline;									/**< ENRVSIZ	: Input extraction noise data vertical line(14bits, Unit 2 pixels)	*/
} TImElaCtrlEnrech;

/** ENRAch/ENWMch control */
typedef struct {
	UINT32	syntheticNoiseTopAddr;		/**< ENSA		: Input/Output synthetic noise data top address (32bits, Unit 64 byte)	*/
	USHORT	syntheticNoiseTotalHsize;	/**< ENSDEF		: Input/Output synthetic noise data total horizontal size(14bits, Unit 64 byte)	*/
	USHORT	syntheticNoiseHsize;			/**< ENSHSIZ	: Input/Output synthetic noise data horizontal size(14bits, Unit 2 pixels)	*/
	USHORT	syntheticNoiseVline;			/**< ENSVSIZ	: Input/Output synthetic noise data vertical line(14bits, Unit 2 pixels)	*/
} TImElaCtrlEnrachEnwmch;

/** ELA data control */
typedef struct {
	UCHAR	nextCtrlFlag;											/**< Please set "ImEla_D_IM_ELA_ENABLE" when using Im_ELA_Ctrl_Next function.<br>
																	     <ul><li>@ref ImEla_D_IM_ELA_DISABLE
																			 <li>@ref ImEla_D_IM_ELA_ENABLE</ul>	*/
	ImElaEImElaQelflvl	elaElfLevel;								/**< ELF level
																     <ul><li>@ref ImEla_E_IM_ELA_ELF_LEVEL_1
																		 <li>@ref ImEla_E_IM_ELA_ELF_LEVEL_2
																		 <li>@ref ImEla_E_IM_ELA_ELF_LEVEL_3
																		 <li>@ref ImEla_E_IM_ELA_ELF_LEVEL_4
																		 <li>@ref ImEla_E_IM_ELA_ELF_LEVEL_5</ul>				*/
	ImElaEImElaQelamd		elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_MAX];	/**< ELA density mode
																     <ul><li>@ref ImEla_E_IM_ELA_DENSITY_MODE_0
																		 <li>@ref ImEla_E_IM_ELA_DENSITY_MODE_1
																		 <li>@ref ImEla_E_IM_ELA_DENSITY_MODE_2
																		 <li>@ref ImEla_E_IM_ELA_DENSITY_MODE_3</ul>				*/
	TImElaCtrlCommon		ctrlCommon;				/**< ELA common control parameter								*/
	TImElaCtrlByr			ctrlByr;					/**< ELA bayer data control parameter							*/
	TImElaCtrlObCorrection	obCorrection;				/**< OB Correction control parameter							*/
	TImElaCtrlEirch			ctrlEirch;					/**< EIRch control parameter									*/
	UINT32	outBayerAddr;									/**< EIWch control<br>
																 tput bayer data top address (32bits, Unit 64 byte)			*/
	UINT32	extractNoiseAddr;								/**< ENWch/ENREch control<br>
																 Input/Output extraction noise data top address (32bits, Unit 64 byte)	*/
	UINT32	noiseSuppressAddr;							/**< ENRAch/ENWMch control<br>
																 Noise suppression data address (32bits, Unit 64 byte)	*/
	TImElaCallback	pCallBack;							/**< callback function	*/
} TImElaCtrl;

/** ELA multiple times execution parameter */
typedef struct {
	TImElaCtrlCore	*core[ImElaReg_D_IM_ELA_STAGE_MAX];	/**< ELA core control parameter										*/
} TImElaMultipleTimesInfo;

/** Noise data mode data */
typedef struct {
	UCHAR	noiseDataMode;							/**< NSLMD.NSLMD	: Noise data mode
														     <ul><li>@ref ImEla_D_IM_ELA_NSLMD_REDUCTION
																 <li>@ref ImEla_D_IM_ELA_NSLMD_SAME</ul>	*/
	UCHAR	noiseDataPrecision;						/**< NSLMD.NSLRES	: Noise data precision
														     <ul><li>@ref ImEla_D_IM_ELA_NSLRES_PRECISION_1	Data precision 1 : High, Maximum amplitude : Small
																 <li>@ref ImEla_D_IM_ELA_NSLRES_PRECISION_2	Data precision 2 :  |  , Maximum amplitude :   |
																 <li>@ref ImEla_D_IM_ELA_NSLRES_PRECISION_3	Data precision 3 :  |  , Maximum amplitude :   |
																 <li>@ref ImEla_D_IM_ELA_NSLRES_PRECISION_4	Data precision 4 : Low , Maximum amplitude : Wide	</ul>	*/
	UCHAR	noiseDataCompressEnable;					/**< NSLMD.NSLKNE	: Noise data compression enable
														     <ul><li>@ref ImEla_D_IM_ELA_DISABLE
																 <li>@ref ImEla_D_IM_ELA_ENABLE</ul>	*/
} TImElaCtrlNslmd;

/** EAch control */
typedef struct {
	UCHAR	cacheTypeR[ImEla_D_IM_ELA_EACH_DATA_MAX];		/**< EARCACHE	: Setting of read channel cache type (4bit)		*/
	UCHAR	cacheTypeW[ImEla_D_IM_ELA_EACH_DATA_MAX];		/**< EAWCACHE	: Setting of write channel cache type (4bit)	*/
	UCHAR	protectTypeR[ImEla_D_IM_ELA_EACH_DATA_MAX];		/**< EARPROT	: Setting of read channel protect type (3bit)	*/
	UCHAR	protectTypeW[ImEla_D_IM_ELA_EACH_DATA_MAX];		/**< EAWPROT	: Setting of write channel protect type (3bit)	*/
	USHORT	reqMaskR[ImEla_D_IM_ELA_EACH_DATA_MAX];			/**< EARREQMSK	: Setting of read channel request mask (12bit)	*/
	USHORT	reqMaskW[ImEla_D_IM_ELA_EACH_DATA_MAX];			/**< EAWREQMSK	: Setting of write channel request mask (12bit)	*/
} TImElaCtrlEach;

/** EAch AXI status */
typedef struct {
	UCHAR	axiReplyR[ImEla_D_IM_ELA_EACH_DATA_MAX];		/**< EARAXSTS	: Setting of read channel cache type (2bit)		*/
	UCHAR	axiReplyW[ImEla_D_IM_ELA_EACH_DATA_MAX];		/**< EAWAXSTS	: Setting of write channel cache type (2bit)	*/
} TImElaEachAxi;

typedef struct {
	UCHAR	eiwDtype;			/* EIWTYP	: EIWch data type								@ELABYR	 */
	UCHAR	eiwSft;			/* EIWSFT	: EIWch data type								@ELABYR	 */
	USHORT	vLine;				/* EIILINE	: Input bayer data vertical line			 	@EIILINE */
	USHORT	hSize;				/* EIIHSIZ	: Input bayer data horizontal size			 	@EIIHSIZ */
} TImElaBayerMng;

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

// Parameter adjustment method table
typedef struct {
	ImElaEImElaQelflvl	elaElfLevel;
	ImElaEImElaQelamd		elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_MAX];
} TImElaQelatmd;

typedef struct 				_ImEla ImEla;
typedef struct 				_ImElaPrivate ImElaPrivate;

struct _ImEla {
	KObject parent;
	ImEla *imEla;
	UCHAR							gImElaStageCnt;
	UCHAR							gImElaStepCnt;
	UCHAR							gImElaNextCtrlFlag;
    TImElaBayerMng				gImElaBayer;
	TImElaCtrlCommon			gImElaCtrlCommonInfo;
	TImElaQelatmd				gImElaQelatmdInfo;
	TImElaMultipleTimesInfo			gImElaMultipleExecInfo;
	TImElaCallback				gImElaCallbackFunc;
};

KConstType 		    im_ela_get_type(void);
ImEla*		        im_ela_get(void);

/*----------------------------------------------------------------------*/
/* Function  															*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus
//---------------------------- driver section ----------------------------
VOID im_ela_ctrl_eirch_register(ImEla*self, TImElaCtrlEirch ctrlEirch );
VOID im_ela_ctrl_core_register(ImEla*self, const TImElaCtrlCore* const ctrl_ela_core);

/**
The register is set for ELA.<br>
@param [in] ctrl_ela	Setting of ELA parameters<br> See @ref TImElaCtrl.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
UINT32 im_ela_ctrl(ImEla*self,  const TImElaCtrl* const ctrl_ela);

/**
The register setting of ELA common is acquired. <br>
@param [out] ctrl_ela_common	Setting of ELA common parameters.<br> See @ref TImElaCtrlCommon.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_get_ctrl_common(ImEla*self, TImElaCtrlCommon* const ctrl_ela_common );

/**
The register setting of EIRch is acquired. <br>
@param [out] ctrl_ela_eirch	Setting of EIRch control parameters.<br> See @ref TImElaCtrlEirch.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_get_ctrl_eirch(ImEla*self, TImElaCtrlEirch* const ctrl_ela_eirch );

/**
The register setting of EIWch is acquired. <br>
@param [out] ctrl_ela_eiwch	Setting of EIWch control parameters.<br> See @ref TImElaCtrlEiwch.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_get_ctrl_eiwch(ImEla*self, TImElaCtrlEiwch* const ctrl_ela_eiwch );

/**
The register setting of ENWch is acquired. <br>
@param [out] ctrl_ela_enwch	Setting of ENWch control parameters.<br> See @ref TImElaCtrlEnwch.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_get_ctrl_enwch(ImEla*self, TImElaCtrlEnwch* const ctrl_ela_enwch );

/**
The register setting of ENREch is acquired. <br>
@param [out] ctrl_ela_enrech	Setting of ENREch control parameters.<br> See @ref TImElaCtrlEnrech.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_get_ctrl_enrech(ImEla*self, TImElaCtrlEnrech* const ctrl_ela_enrech );

/**
The register setting of ENRAch/ENWMch is acquired. <br>
@param [out] ctrl_ela_enrach_enwmch	Setting of ENRAch/ENWMch control parameters.<br> See @ref TImElaCtrlEnrachEnwmch.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_get_ctrl_enrach_enwmch(ImEla*self, TImElaCtrlEnrachEnwmch* const ctrl_ela_enrach_enwmch );

/**
The register setting of core information is acquired. <br>
@param [out] ctrl_ela_core	Setting of cire information.<br> See @ref TImElaCtrlCore.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_get_ctrl_core(ImEla*self, TImElaCtrlCore* const ctrl_ela_core );

/**
The register setting of OB Correction control is acquired. <br>
@param [out]	ctrl_ela_ob		pointer of OB Correction control parameters.<br> See @ref TImElaCtrlObCorrection.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_get_ctrl_ob_correction(ImEla*self, TImElaCtrlObCorrection* const ctrl_ela_ob ) ;

/**
Set address of parameter for multiple times execution.<br>
@param [in]	multiple_exec_info		pointer of multiple times execution information data address.<br> See @ref TImElaMultipleTimesInfo.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
@remarks	This API uses DDIM_User_Clr_Flg().
*/
UINT32 im_ela_set_multiple_exec_info(ImEla*self, const TImElaMultipleTimesInfo* const multiple_exec_info );

/**
The register setting of NSLMD is acquired. <br>
@param [out]	nslmd		pointer of NSLMD parameters.<br> See @ref TImElaCtrlNslmd.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_get_nslmd(ImEla*self, TImElaCtrlNslmd* const nslmd ) ;

/**
The register is set for EAch.<br>
@param [in] ctrl_each	Setting of EAch parameters<br> See @ref TImElaCtrlEach.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_set_each(ImEla*self, const TImElaCtrlEach* const ctrl_each );

/**
The register setting of EAch is acquired. <br>
@param [out]	ctrl_each	pointer of EAch parameters<br> See @ref TImElaCtrlEach.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_get_each(ImEla*self, TImElaCtrlEach* const ctrl_each );

/**
The register setting of AXI status is acquired. <br>
@param [out]	each_axi	pointer of AXI status parameters<br> See @ref TImElaEachAxi.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_get_axi_status(ImEla*self, TImElaEachAxi* const each_axi );

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// _IM_ELA_H_

/*@}*/
/**
@weakgroup im_ela
@{

@section im_ela_sample_section1	Sample of ELA
The example of executing synchronous processing is as follows.<br>
@code

    INT32 result;
    int cnt;
    TImElaCtrl ctrl_ela;
    TImElaMultipleTimesInfo ela_ctrl_multiple_exec;

    memset(&ela_ctrl_multiple_exec, 0, sizeof(TImElaMultipleTimesInfo)); // Set the noise data obtained from IQ is in practice.

    ctrl_ela.nextCtrlFlag = ImEla_D_IM_ELA_DISABLE;

    ctrl_ela.elaElfLevel = ImEla_E_IM_ELA_ELF_LEVEL_5;
    ctrl_ela.elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
    ctrl_ela.elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_2;
    ctrl_ela.elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_3;
    ctrl_ela.elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_3;
    ctrl_ela.elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_5] = ImEla_E_IM_ELA_DENSITY_MODE_3;

    ctrl_ela.ctrlCommon.noiseDataMode            = ImEla_D_IM_ELA_NSLMD_SAME;
    ctrl_ela.ctrlCommon.noiseDataPrecision       = ImEla_D_IM_ELA_NSLRES_PRECISION_2;
    ctrl_ela.ctrlCommon.noiseDataCompressEnable = ImEla_D_IM_ELA_ENABLE;
    ctrl_ela.ctrlCommon.bayerStartPixelType     = ImEla_D_IM_ELA_ORG_R;

    ctrl_ela.ctrlByr.inDataType        = ImEla_D_IM_ELA_DATATYP_12BIT;
    ctrl_ela.ctrlByr.inDataShiftMode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
    ctrl_ela.ctrlByr.outDataType       = ImEla_D_IM_ELA_DATATYP_12BIT;
    ctrl_ela.ctrlByr.outDataShiftMode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
    ctrl_ela.ctrlByr.dekneeEnable       = ImEla_D_IM_ELA_ENABLE;
    ctrl_ela.ctrlByr.obZsfEnable       = ImEla_D_IM_ELA_ENABLE;

    //OB Correction control
    ctrl_ela.obCorrection.obRr = 0;
    ctrl_ela.obCorrection.obBb = 0;
    ctrl_ela.obCorrection.obGr = 0;
    ctrl_ela.obCorrection.obGb = 0;

    ctrl_ela.ctrlEirch.inBayerTopAddr = 0x2000000;
    ctrl_ela.ctrlEirch.inBayerTopOffset = 0;
    ctrl_ela.ctrlEirch.inBayerTotalHsize = 6912;
    ctrl_ela.ctrlEirch.inBayerHsize = 4608;
    ctrl_ela.ctrlEirch.inBayerVline = 3456;

    ctrl_ela.outBayerAddr     = 0x3000000;
    ctrl_ela.extractNoiseAddr = 0x4000000;

    ctrl_ela.pCallBack = NULL;

    // Setting of ELA control parameter
    result = im_ela_ctrl(NULL, &ctrl_ela);
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

    result = im_ela_set_multiple_exec_info(NULL, NULL,&ela_ctrl_multiple_exec);
    if( result != D_DDIM_OK ) {
        // Error processing
        return;
    }

    // Processing is started synchronously
    result = im_ela_reg_start_sync(im_ela_reg_new());
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

@endcode
<br><br>

@section im_ela_sample_section2	Sample of ELA using Im_ELA_Ctrl_Next function
The example of executing synchronous processing is as follows.<br>
@code

    INT32 result;
    int cnt;
    TImElaCtrl ctrl_ela;
    TImElaMultipleTimesInfo ela_ctrl_multiple_exec;

    memset(&ela_ctrl_multiple_exec, 0, sizeof(TImElaMultipleTimesInfo)); // Set the noise data obtained from IQ is in practice.

    ctrl_ela.nextCtrlFlag = ImEla_D_IM_ELA_ENABLE;

    ctrl_ela.elaElfLevel = ImEla_E_IM_ELA_ELF_LEVEL_5;
    ctrl_ela.elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
    ctrl_ela.elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_2;
    ctrl_ela.elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_3;
    ctrl_ela.elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_3;
    ctrl_ela.elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_5] = ImEla_E_IM_ELA_DENSITY_MODE_3;

    ctrl_ela.ctrlCommon.noiseDataMode            = ImEla_D_IM_ELA_NSLMD_SAME;
    ctrl_ela.ctrlCommon.noiseDataPrecision       = ImEla_D_IM_ELA_NSLRES_PRECISION_2;
    ctrl_ela.ctrlCommon.noiseDataCompressEnable = ImEla_D_IM_ELA_ENABLE;
    ctrl_ela.ctrlCommon.bayerStartPixelType     = ImEla_D_IM_ELA_ORG_R;

    ctrl_ela.ctrlByr.inDataType        = ImEla_D_IM_ELA_DATATYP_12BIT;
    ctrl_ela.ctrlByr.inDataShiftMode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
    ctrl_ela.ctrlByr.outDataType       = ImEla_D_IM_ELA_DATATYP_12BIT;
    ctrl_ela.ctrlByr.outDataShiftMode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
    ctrl_ela.ctrlByr.dekneeEnable       = ImEla_D_IM_ELA_ENABLE;
    ctrl_ela.ctrlByr.obZsfEnable       = ImEla_D_IM_ELA_ENABLE;

    //OB Correction control
    ctrl_ela.obCorrection.obRr = 0;
    ctrl_ela.obCorrection.obBb = 0;
    ctrl_ela.obCorrection.obGr = 0;
    ctrl_ela.obCorrection.obGb = 0;

    ctrl_ela.ctrlEirch.inBayerTopAddr = 0x2000000;
    ctrl_ela.ctrlEirch.inBayerTopOffset = 0;
    ctrl_ela.ctrlEirch.inBayerTotalHsize = 6912;
    ctrl_ela.ctrlEirch.inBayerHsize = 4608;
    ctrl_ela.ctrlEirch.inBayerVline = 3456;

    ctrl_ela.outBayerAddr     = 0x3000000;
    ctrl_ela.extractNoiseAddr = 0x4000000;

	ctrl_ela.pCallBack = NULL;

    // Setting of ELA control parameter
    result = im_ela_ctrl(NULL, &ctrl_ela);
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

    result = im_ela_set_multiple_exec_info(NULL, NULL,&ela_ctrl_multiple_exec);
    if( result != D_DDIM_OK ) {
        // Error processing
        return;
    }

    // Processing is started synchronously
    result = im_ela_reg_start_sync(im_ela_reg_new());
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

    // Setting of ELA control parameter
    // ELA macro processing of the second times
    result = im_ela_core_ctrl_next(NULLNULL);
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

    // Processing is started synchronously
    result = im_ela_reg_start_sync(im_ela_reg_new());
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

    // Setting of ELA control parameter
    // The last ELA macro processing
    result = im_ela_core_ctrl_next(NULLNULL);
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

    // Processing is started synchronously
    result = im_ela_reg_start_sync(im_ela_reg_new());
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

    // Setting of ELA control parameter
    // The last ELA macro processing
    result = im_ela_core_ctrl_next(NULLNULL);
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

    // Processing is started synchronously
    result = im_ela_reg_start_sync(im_ela_reg_new());
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

    // Setting of ELA control parameter
    // The last ELA macro processing
    result = im_ela_core_ctrl_next(NULLNULL);
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

    // Processing is started synchronously
    result = im_ela_reg_start_sync(im_ela_reg_new());
    if(result != D_DDIM_OK) {
        // Error processing
        return;
    }

@endcode

*/

/*@}*/
