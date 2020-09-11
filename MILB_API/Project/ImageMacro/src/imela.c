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

#include <string.h>
#include "dd_top.h"
#include "imela.h"
#include "imelacore.h"
#include "imelareg.h"
#include "jdsela.h"
#include "dd_arm.h"
#include "ddim_user_custom.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImEla, im_ela);
#define IM_ELA_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImElaPrivate, IM_TYPE_ELA))

struct _ImElaPrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
static VOID imElaCtrlNoiseLimitRegister( const TImElaCtrlLimit* ctrl_noise_limit );

static void im_ela_constructor(ImEla *self)
{
}

static void im_ela_destructor(ImEla *self)
{
}

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/**
 * @brief		ELA core register setting
 * @param[in]	T_IM_ELA_CTRL_NOISE_LIMIT ctrl_noise_limit
 * @return		None
 * @note		None
 * @attention	None
 */
static VOID imElaCtrlNoiseLimitRegister( const TImElaCtrlLimit* ctrl_noise_limit )
{
	USHORT	plus_limit_work;
	USHORT	minus_limit_work;
	USHORT	limit_chk_val;
	ImEla *imEla  =  im_ela_get();
	TImElaCtrlCommon *gImElaCtrlCommonInfo = im_ela_get_g_im_ela_ctrl_common_info(imEla);

	plus_limit_work = ctrl_noise_limit->noisePlusLimit;
	minus_limit_work = ctrl_noise_limit->noiseMinusLimit;

	if( gImElaCtrlCommonInfo->noiseDataCompressEnable == ImEla_D_IM_ELA_DISABLE ){
		if( gImElaCtrlCommonInfo->noiseDataPrecision == ImEla_D_IM_ELA_NSLRES_PRECISION_1 ){
			limit_chk_val = 127;
		}
		else if( gImElaCtrlCommonInfo->noiseDataPrecision == ImEla_D_IM_ELA_NSLRES_PRECISION_2 ){
			limit_chk_val = 254;
		}
		else if( gImElaCtrlCommonInfo->noiseDataPrecision == ImEla_D_IM_ELA_NSLRES_PRECISION_3 ){
			limit_chk_val = 509;
		}
		else{
			limit_chk_val = 1019;
		}
	}
	else{
		if( gImElaCtrlCommonInfo->noiseDataPrecision == ImEla_D_IM_ELA_NSLRES_PRECISION_1 ){
			limit_chk_val = 315;
		}
		else if( gImElaCtrlCommonInfo->noiseDataPrecision == ImEla_D_IM_ELA_NSLRES_PRECISION_2 ){
			limit_chk_val = 631;
		}
		else{
			limit_chk_val = 1023;		// Don't Care (0x3FF)
		}
	}
	if( plus_limit_work > limit_chk_val ){
		plus_limit_work = limit_chk_val;
	}
	if( minus_limit_work > limit_chk_val ){
		minus_limit_work = limit_chk_val;
	}
	IO_ELA.NSLNGLMT.bit.NSLNGLMP = plus_limit_work;		// Noise element plus side limit
	IO_ELA.NSLNGLMT.bit.NSLNGLMM = minus_limit_work;	// Noise element minus side limit
}

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/**
 * @brief		EIRch register setting
 * @param[in]	TImElaCtrlEirch ctrlEirch
 * @return		None
 * @note		None
 * @attention	None
 */
VOID im_ela_ctrl_eirch_register( TImElaCtrlEirch ctrlEirch )
{
	USHORT	hSize;
	USHORT	vLine;
	ImEla *imEla  =  im_ela_get();
	TImElaBayerMng *gImElaBayer = im_ela_get_g_im_ela_bayer(imEla);

	const USHORT	hsize_max_cnt0	= 15360;
	const USHORT	hsize_min_cnt0	= 320;
	const USHORT	hsize_min		= 64;
	const USHORT	vline_max_cnt0	= 8960;
	const USHORT	vline_min_cnt0	= 240;
	const USHORT	vline_min		= 48;

	hSize = ctrlEirch.inBayerHsize;
	vLine = ctrlEirch.inBayerVline;
	IO_ELA.EIRA.word = ctrlEirch.inBayerTopAddr;				// Input bayer data top address
	IO_ELA.EIROFS.bit.EIROFS = ctrlEirch.inBayerTopOffset;		// Input bayer data Top area bit offset
	IO_ELA.EIRDEF.bit.EIRDEF = ctrlEirch.inBayerTotalHsize;		// Input bayer data total horizontal size

	if( imEla->gImElaStageCnt == 0 ){
		if( hSize > hsize_max_cnt0 ){
			hSize = hsize_max_cnt0;
		}
		else if( hSize < hsize_min_cnt0 ){
			hSize = hsize_min_cnt0;
		}
		else{
			;	// DO NOTHING
		}
		if( vLine > vline_max_cnt0 ){
			vLine = vline_max_cnt0;
		}
		else if( vLine < vline_min_cnt0 ){
			vLine = vline_min_cnt0;
		}
		else{
			;	// DO NOTHING
		}
	}
	else{
		if( hSize < hsize_min ){
			hSize = hsize_min;
		}
		if( vLine < vline_min ){
			vLine = vline_min;
		}
	}
	IO_ELA.EIRHSIZ.bit.EIRHSIZ = hSize;								// Input bayer data horizontal size
	IO_ELA.EIRVSIZ.bit.EIRVSIZ = vLine;								// Input bayer data horizontal size

	gImElaBayer->hSize = hSize;
	gImElaBayer->vLine = vLine;
}

/**
 * @brief		ELA core register setting
 * @param[in]	T_IM_ELA_CTRL_COMMON_NOISE ctrl_common_noise
 * @return		None
 * @note		None
 * @attention	None
 */
VOID im_ela_ctrl_core_register( const TImElaCtrlCore* const ctrl_ela_core )
{
	// Optical zero level shift parameter
	ImElaReg_IM_ELA_SET_REG_SIGNED( IO_ELA.EZSFTA1, union io_ela_ezsfta1, EZSFTA1, ctrl_ela_core->opticalZeroLevelShift );

	/* NSLNGLMT register setting */
	imElaCtrlNoiseLimitRegister( &(ctrl_ela_core->limit) );

	IO_ELA.BYRTYP.bit.ELADCMD			= ctrl_ela_core->defectCorrectionMode;// Defect pixel correction mode
	IO_ELA.ELFZP.bit.ELFZP				= ctrl_ela_core->zeroPointLevel;		// Zero point level

	IO_ELA.ELFL.ELFL1.bit.ELFL_1		= ctrl_ela_core->elfLt[0];				// ELF luminance threshold 1
	IO_ELA.ELFL.ELFL1.bit.ELFL_2		= ctrl_ela_core->elfLt[1];				// ELF luminance threshold 2
	IO_ELA.ELFL.ELFL2.bit.ELFL_3		= ctrl_ela_core->elfLt[2];				// ELF luminance threshold 3
	IO_ELA.ELFL.ELFL2.bit.ELFL_4		= ctrl_ela_core->elfLt[3];				// ELF luminance threshold 4

	IO_ELA.ANBOR.ANBOR1.bit.ANBOR_0		= ctrl_ela_core->anbR.offset[0]; 	  	// Noise characteristics of the pixel R : Offset 0
	IO_ELA.ANBOR.ANBOR1.bit.ANBOR_1		= ctrl_ela_core->anbR.offset[1]; 	  	// Noise characteristics of the pixel R : Offset 1
	IO_ELA.ANBOR.ANBOR2.bit.ANBOR_2		= ctrl_ela_core->anbR.offset[2]; 	  	// Noise characteristics of the pixel R : Offset 2
	IO_ELA.ANBOR.ANBOR2.bit.ANBOR_3		= ctrl_ela_core->anbR.offset[3]; 	  	// Noise characteristics of the pixel R : Offset 3
	IO_ELA.ANBKR.ANBKR1.bit.ANBKR_0		= ctrl_ela_core->anbR.gain[0];		  	// Noise characteristics of the pixel R : Gain 0
	IO_ELA.ANBKR.ANBKR1.bit.ANBKR_1		= ctrl_ela_core->anbR.gain[1];		  	// Noise characteristics of the pixel R : Gain 1
	IO_ELA.ANBKR.ANBKR2.bit.ANBKR_2		= ctrl_ela_core->anbR.gain[2];		  	// Noise characteristics of the pixel R : Gain 2
	IO_ELA.ANBKR.ANBKR2.bit.ANBKR_3		= ctrl_ela_core->anbR.gain[3];		  	// Noise characteristics of the pixel R : Gain 3
	IO_ELA.ANBDR.ANBDR1.bit.ANBDR_0		= ctrl_ela_core->anbR.boundary[0];	  	// Noise characteristics of the pixel R : boundary 0
	IO_ELA.ANBDR.ANBDR1.bit.ANBDR_1		= ctrl_ela_core->anbR.boundary[1];	  	// Noise characteristics of the pixel R : boundary 1
	IO_ELA.ANBDR.ANBDR2.bit.ANBDR_2		= ctrl_ela_core->anbR.boundary[2];	  	// Noise characteristics of the pixel R : boundary 2
	IO_ELA.ANBDR.ANBDR2.bit.ANBDR_3		= ctrl_ela_core->anbR.boundary[3];	  	// Noise characteristics of the pixel R : boundary 3

	IO_ELA.ANBOG.ANBOG1.bit.ANBOG_0		= ctrl_ela_core->anbG.offset[0]; 	  	// Noise characteristics of the pixel G : Offset 0
	IO_ELA.ANBOG.ANBOG1.bit.ANBOG_1		= ctrl_ela_core->anbG.offset[1]; 	  	// Noise characteristics of the pixel G : Offset 1
	IO_ELA.ANBOG.ANBOG2.bit.ANBOG_2		= ctrl_ela_core->anbG.offset[2]; 	  	// Noise characteristics of the pixel G : Offset 2
	IO_ELA.ANBOG.ANBOG2.bit.ANBOG_3		= ctrl_ela_core->anbG.offset[3]; 	  	// Noise characteristics of the pixel G : Offset 3
	IO_ELA.ANBKG.ANBKG1.bit.ANBKG_0		= ctrl_ela_core->anbG.gain[0];		  	// Noise characteristics of the pixel G : Gain 0
	IO_ELA.ANBKG.ANBKG1.bit.ANBKG_1		= ctrl_ela_core->anbG.gain[1];		  	// Noise characteristics of the pixel G : Gain 1
	IO_ELA.ANBKG.ANBKG2.bit.ANBKG_2		= ctrl_ela_core->anbG.gain[2];		  	// Noise characteristics of the pixel G : Gain 2
	IO_ELA.ANBKG.ANBKG2.bit.ANBKG_3		= ctrl_ela_core->anbG.gain[3];		  	// Noise characteristics of the pixel G : Gain 3
	IO_ELA.ANBDG.ANBDG1.bit.ANBDG_0		= ctrl_ela_core->anbG.boundary[0];	  	// Noise characteristics of the pixel G : boundary 0
	IO_ELA.ANBDG.ANBDG1.bit.ANBDG_1		= ctrl_ela_core->anbG.boundary[1];	  	// Noise characteristics of the pixel G : boundary 1
	IO_ELA.ANBDG.ANBDG2.bit.ANBDG_2		= ctrl_ela_core->anbG.boundary[2];	  	// Noise characteristics of the pixel G : boundary 2
	IO_ELA.ANBDG.ANBDG2.bit.ANBDG_3		= ctrl_ela_core->anbG.boundary[3];	  	// Noise characteristics of the pixel G : boundary 3

	IO_ELA.ANBOB.ANBOB1.bit.ANBOB_0		= ctrl_ela_core->anbB.offset[0]; 	  	// Noise characteristics of the pixel B : Offset 0
	IO_ELA.ANBOB.ANBOB1.bit.ANBOB_1		= ctrl_ela_core->anbB.offset[1]; 	  	// Noise characteristics of the pixel B : Offset 1
	IO_ELA.ANBOB.ANBOB2.bit.ANBOB_2		= ctrl_ela_core->anbB.offset[2]; 	  	// Noise characteristics of the pixel B : Offset 2
	IO_ELA.ANBOB.ANBOB2.bit.ANBOB_3		= ctrl_ela_core->anbB.offset[3]; 	  	// Noise characteristics of the pixel B : Offset 3
	IO_ELA.ANBKB.ANBKB1.bit.ANBKB_0		= ctrl_ela_core->anbB.gain[0];		  	// Noise characteristics of the pixel B : Gain 0
	IO_ELA.ANBKB.ANBKB1.bit.ANBKB_1		= ctrl_ela_core->anbB.gain[1];		  	// Noise characteristics of the pixel B : Gain 1
	IO_ELA.ANBKB.ANBKB2.bit.ANBKB_2		= ctrl_ela_core->anbB.gain[2];		  	// Noise characteristics of the pixel B : Gain 2
	IO_ELA.ANBKB.ANBKB2.bit.ANBKB_3		= ctrl_ela_core->anbB.gain[3];		  	// Noise characteristics of the pixel B : Gain 3
	IO_ELA.ANBDB.ANBDB1.bit.ANBDB_0		= ctrl_ela_core->anbB.boundary[0];	  	// Noise characteristics of the pixel B : boundary 0
	IO_ELA.ANBDB.ANBDB1.bit.ANBDB_1		= ctrl_ela_core->anbB.boundary[1];	  	// Noise characteristics of the pixel B : boundary 1
	IO_ELA.ANBDB.ANBDB2.bit.ANBDB_2		= ctrl_ela_core->anbB.boundary[2];	  	// Noise characteristics of the pixel B : boundary 2
	IO_ELA.ANBDB.ANBDB2.bit.ANBDB_3		= ctrl_ela_core->anbB.boundary[3];	  	// Noise characteristics of the pixel B : boundary 3

	IO_ELA.LGTW.LGTW1.bit.LGTWR			= ctrl_ela_core->lumenGainR;			// R Gain for luminance
	IO_ELA.LGTW.LGTW1.bit.LGTWG			= ctrl_ela_core->lumenGainG;			// G Gain for luminance
	IO_ELA.LGTW.LGTW2.bit.LGTWB			= ctrl_ela_core->lumenGainB;			// B Gain for luminance

	IO_ELA.LGT.bit.LGTR					= ctrl_ela_core->lumenFactorR;		// R factor for the luminance
	IO_ELA.LGT.bit.LGTG					= ctrl_ela_core->lumenFactorG;		// G factor for the luminance
	IO_ELA.LGT.bit.LGTB					= ctrl_ela_core->lumenFactorB;		// B factor for the luminance
	IO_ELA.LGT.bit.LGTC					= ctrl_ela_core->lumenFactorC;		// C factor for the luminance

	IO_ELA.LGTE.bit.LGTER				= ctrl_ela_core->lumenEdgeR;			// R factor for the degree of weight edge
	IO_ELA.LGTE.bit.LGTEG				= ctrl_ela_core->lumenEdgeG;			// G factor for the degree of weight edge
	IO_ELA.LGTE.bit.LGTEB				= ctrl_ela_core->lumenEdgeB;			// B factor for the degree of weight edge

	IO_ELA.EDG2ANBA.bit.EDG2ANBA		= ctrl_ela_core->edgeAdjustA1;		// Set the degree adjustment factor-1 edge of A
	IO_ELA.EDGSCLA.bit.EDGSCLA			= ctrl_ela_core->edgeAdjustA2;		// Set the degree adjustment factor-2 edge of A
	IO_ELA.EDG2ANBB.bit.EDG2ANBB		= ctrl_ela_core->edgeAdjustB1;		// Set the degree adjustment factor-1 edge of B
	IO_ELA.EDGSCLB.bit.EDGSCLB			= ctrl_ela_core->edgeAdjustB2;		// Set the degree adjustment factor-2 edge of B

	IO_ELA.ALNGE.ALNGE1.bit.ALNGE_1		= ctrl_ela_core->edgeThreshold[0];		// Edge degree threshold 1
	IO_ELA.ALNGE.ALNGE1.bit.ALNGE_2		= ctrl_ela_core->edgeThreshold[1];		// Edge degree threshold 1
	IO_ELA.ALNGE.ALNGE2.bit.ALNGE_3		= ctrl_ela_core->edgeThreshold[2];		// Edge degree threshold 1

	IO_ELA.ALNG.ALNG1.bit.ALNGL1E1N		= ctrl_ela_core->nr[0];					// NR intensity :Luminance L1, Edge E1
	IO_ELA.ALNG.ALNG1.bit.ALNGL1E2N		= ctrl_ela_core->nr[1];					// NR intensity :Luminance L1, Edge E2
	IO_ELA.ALNG.ALNG2.bit.ALNGL1E3N		= ctrl_ela_core->nr[2];					// NR intensity :Luminance L1, Edge E3
	IO_ELA.ALNG.ALNG2.bit.ALNGL2E1N		= ctrl_ela_core->nr[3];					// NR intensity :Luminance L2, Edge E1
	IO_ELA.ALNG.ALNG3.bit.ALNGL2E2N		= ctrl_ela_core->nr[4];					// NR intensity :Luminance L2, Edge E2
	IO_ELA.ALNG.ALNG3.bit.ALNGL2E3N		= ctrl_ela_core->nr[5];					// NR intensity :Luminance L2, Edge E3
	IO_ELA.ALNG.ALNG4.bit.ALNGL3E1N		= ctrl_ela_core->nr[6];					// NR intensity :Luminance L3, Edge E1
	IO_ELA.ALNG.ALNG4.bit.ALNGL3E2N		= ctrl_ela_core->nr[7];					// NR intensity :Luminance L3, Edge E2
	IO_ELA.ALNG.ALNG5.bit.ALNGL3E3N		= ctrl_ela_core->nr[8];					// NR intensity :Luminance L3, Edge E3
	IO_ELA.ALNG.ALNG5.bit.ALNGL4E1N		= ctrl_ela_core->nr[9];					// NR intensity :Luminance L4, Edge E1
	IO_ELA.ALNG.ALNG6.bit.ALNGL4E2N		= ctrl_ela_core->nr[10];				// NR intensity :Luminance L4, Edge E2
	IO_ELA.ALNG.ALNG6.bit.ALNGL4E3N		= ctrl_ela_core->nr[11];				// NR intensity :Luminance L4, Edge E3

	IO_ELA.LFTH.bit.LFTH				= ctrl_ela_core->lNoise; 				// L extraction threshold noise
	IO_ELA.LCOME.bit.LCOME1				= ctrl_ela_core->lEdge[0];				// Edge applicable threshold contour L 1
	IO_ELA.LCOME.bit.LCOME2				= ctrl_ela_core->lEdge[1];				// Edge applicable threshold contour L 2
	IO_ELA.LCOMEN.bit.LCOME1N			= ctrl_ela_core->lIntense[0];			// Applied intensity L 1
	IO_ELA.LCOMEN.bit.LCOME2N			= ctrl_ela_core->lIntense[1];			// Applied intensity L 2
}

/**
 * @brief		The register at the ELA parameters is set
 * @param[in]	TImElaCtrl* ctrl_ela
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_ctrl(ImEla*self,  const TImElaCtrl* const ctrl_ela )
{
	UINT32 loop_cnt;
	ImEla *imEla  =  im_ela_get();
	TImElaBayerMng *gImElaBayer = im_ela_get_g_im_ela_bayer(imEla);
	TImElaCtrlCommon *gImElaCtrlCommonInfo = im_ela_get_g_im_ela_ctrl_common_info(imEla);
	TImElaQelatmd *gImElaQelatmdInfo = im_ela_get_g_im_ela_qelatmd_info(imEla);

#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( ctrl_ela == NULL ){
		Ddim_Assertion(("im_ela_ctrl( ) error. ctrl_ela = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}

	/* check on input elf level */
	if( ctrl_ela->elaElfLevel == ImEla_E_IM_ELA_ELF_LEVEL_MAX ){
		Ddim_Assertion(("im_ela_ctrl( ) error. elaElfLevel = %d\n", ctrl_ela->elaElfLevel));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}

	/* check on input ELA density mode */
	for( loop_cnt = 1; loop_cnt <= ctrl_ela->elaElfLevel; loop_cnt++ ){
		if( ctrl_ela->elaDensityMode[loop_cnt] > (ctrl_ela->elaDensityMode[loop_cnt - 1] + 1) ){
			Ddim_Assertion(("im_ela_ctrl( ) error. elaDensityMode[%d] = %d (elaDensityMode[%d] = %d)\n",
																						loop_cnt,
																						ctrl_ela->elaDensityMode[loop_cnt],
																						(loop_cnt - 1),
																						ctrl_ela->elaDensityMode[loop_cnt - 1]));
			return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
		}
	}
	if( ctrl_ela->ctrlCommon.noiseDataCompressEnable == ImEla_D_IM_ELA_ENABLE ){
		if( (ctrl_ela->ctrlCommon.noiseDataPrecision == ImEla_D_IM_ELA_NSLRES_PRECISION_3) ||
		   (ctrl_ela->ctrlCommon.noiseDataPrecision == ImEla_D_IM_ELA_NSLRES_PRECISION_4) ){
			Ddim_Assertion(("im_ela_ctrl( ) error. noiseDataCompressEnable = %d, noiseDataPrecision = %d)\n",
																						ctrl_ela->ctrlCommon.noiseDataCompressEnable,
																						ctrl_ela->ctrlCommon.noiseDataPrecision));
			return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
		}
	}
#endif // CO_PARAM_CHECK

	memset( (TImElaBayerMng*)&imEla->gImElaBayer, 0, sizeof(TImElaBayerMng) );
#ifdef CO_ELA_DEBUG_PRINT	// Debug
	Ddim_Print(("im_ela_ctrl( ) : gImElaBayer clear END\n"));
#endif

	im_ela_core_on_pclk(NULL);

	// Wait ELA Stop
	while( IO_ELA.ELATRG.bit.ELATRG == 3 ){
		DDIM_User_Dly_Tsk(1);
		Ddim_Print(("im_ela_ctrl( ) : ELA Processing\n"));
	}

	imEla->gImElaNextCtrlFlag = ctrl_ela->nextCtrlFlag;

//	imEla->gImElaStageCnt = 0;								// ELA macro stage count
//	gImElaStepCnt = 0;								// ELA macro step count

	gImElaQelatmdInfo->elaElfLevel = ctrl_ela->elaElfLevel;
	for( loop_cnt = 0; loop_cnt <= ctrl_ela->elaElfLevel; loop_cnt++ ){
		gImElaQelatmdInfo->elaDensityMode[loop_cnt] = ctrl_ela->elaDensityMode[loop_cnt];
	}

	/* common register setting */
	IO_ELA.ELACTL.bit.ELACNT = 0;												// ELA count
	IO_ELA.ELACTL.bit.ELAACT = ImElaReg_D_IM_ELA_ELAACT_EXTRACT;							// Operation mode
	IO_ELA.ELACTL.bit.ELAMD = ctrl_ela->elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_1];	// ELA density mode

	IO_ELA.ELABYR.bit.EIRTYP = ctrl_ela->ctrlByr.inDataType;					// Input data type
	// Input bit shift mode
	switch( ctrl_ela->ctrlByr.inDataShiftMode ){
		case ImEla_D_IM_ELA_BIT_SHIFT_MODE_R2:
			IO_ELA.ELABYR.bit.EIRSFT = 0x00;
			break;
		case ImEla_D_IM_ELA_BIT_SHIFT_MODE_L2:
			IO_ELA.ELABYR.bit.EIRSFT = 0x02;
			break;
		case ImEla_D_IM_ELA_BIT_SHIFT_MODE_L4:
			IO_ELA.ELABYR.bit.EIRSFT = 0x03;
			break;
		default:
			// Not Bit Shift
			IO_ELA.ELABYR.bit.EIRSFT = 0x01;
			break;
	}
	IO_ELA.ELABYR.bit.EIWTYP = ctrl_ela->ctrlByr.outDataType;				// Output data type
	// Output bit shift mode
	switch( ctrl_ela->ctrlByr.outDataShiftMode ){
		case ImEla_D_IM_ELA_BIT_SHIFT_MODE_R2:
			IO_ELA.ELABYR.bit.EIWSFT = 0x02;
			gImElaBayer->eiwSft = 0x02;
			break;
		case ImEla_D_IM_ELA_BIT_SHIFT_MODE_R4:
			IO_ELA.ELABYR.bit.EIWSFT = 0x03;
			gImElaBayer->eiwSft = 0x03;
			break;
		default:
			// Not Bit Shift
			IO_ELA.ELABYR.bit.EIWSFT = 0x01;
			gImElaBayer->eiwSft = 0x01;
			break;
	}
	// Output data num
	if( ctrl_ela->elaElfLevel == ImEla_E_IM_ELA_ELF_LEVEL_1 ){
		IO_ELA.ELABYR.bit.EIWOUT = ImEla_D_IM_ELA_EIWOUT_NONE;
	}
	else{
		switch( ctrl_ela->elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_2] ){
			case ImEla_E_IM_ELA_DENSITY_MODE_0:
			case ImEla_E_IM_ELA_DENSITY_MODE_1:
				IO_ELA.ELABYR.bit.EIWOUT = ImEla_D_IM_ELA_EIWOUT_1;
				break;
//			case ImEla_E_IM_ELA_DENSITY_MODE_2:
//			case ImEla_E_IM_ELA_DENSITY_MODE_3:
			default:
				IO_ELA.ELABYR.bit.EIWOUT = ImEla_D_IM_ELA_EIWOUT_4;
				break;
		}
	}

	gImElaBayer->eiwDtype = ctrl_ela->ctrlByr.outDataType;

	// First set only
	if( ctrl_ela->ctrlByr.dekneeEnable == ImEla_D_IM_ELA_ENABLE ){
		// Enabling the Deknee processing for bayer data entry
		IO_ELA.ELABYR.bit.DKNEN = ctrl_ela->ctrlByr.dekneeEnable;
		IO_ELA.ELABYR.bit.DKNACT = 1;
	}

	// Enabling the "OB correction"/"Optical zero shift" processing for bayer data entry
	IO_ELA.ELABYR.bit.EOBAEN = ctrl_ela->ctrlByr.obZsfEnable;

	IO_ELA.NSLMD.bit.NSLMD = ctrl_ela->ctrlCommon.noiseDataMode;				// Noise data mode
	IO_ELA.NSLMD.bit.NSLRES = ctrl_ela->ctrlCommon.noiseDataPrecision;		// Noise data precision
	IO_ELA.NSLMD.bit.NSLKNE = ctrl_ela->ctrlCommon.noiseDataCompressEnable;	// Noise data compression enable
	IO_ELA.BYRTYP.bit.ORG = ctrl_ela->ctrlCommon.bayerStartPixelType;		// Bayer data start-pixel type
	memcpy( (TImElaCtrlCommon*)&gImElaCtrlCommonInfo, &(ctrl_ela->ctrlCommon), sizeof(TImElaCtrlCommon) );
#ifdef CO_ELA_DEBUG_PRINT	// Debug
	Ddim_Print(("im_ela_ctrl( ) : TImElaCtrlCommon Copy END\n"));
#endif

	if( ctrl_ela->ctrlByr.obZsfEnable == ImEla_D_IM_ELA_ENABLE ){
		// OB Correction R Pixel
		ImElaReg_IM_ELA_SET_REG_SIGNED( IO_ELA.OBOF.OBOF1, union io_ela_obof_1, EOBRR, ctrl_ela->obCorrection.obRr );

		// OB Correction B Pixel
		ImElaReg_IM_ELA_SET_REG_SIGNED( IO_ELA.OBOF.OBOF1, union io_ela_obof_1, EOBBB, ctrl_ela->obCorrection.obBb );

		// OB Correction Gr Pixel
		ImElaReg_IM_ELA_SET_REG_SIGNED( IO_ELA.OBOF.OBOF2, union io_ela_obof_2, EOBGR, ctrl_ela->obCorrection.obGr );

		// OB Correction Gb Pixel
		ImElaReg_IM_ELA_SET_REG_SIGNED( IO_ELA.OBOF.OBOF2, union io_ela_obof_2, EOBGB, ctrl_ela->obCorrection.obGb );
	}

	/* EIRch register setting */
	im_ela_ctrl_eirch_register( ctrl_ela->ctrlEirch );
#ifdef CO_ELA_DEBUG_PRINT	// Debug
	Ddim_Print(("im_ela_ctrl( ) : EIRch register setting END\n"));
#endif

	/* calculate curtail bayer data */
	im_ela_reg_calc_curtail_bayer_data(NULL, ctrl_ela->outBayerAddr );
#ifdef CO_ELA_DEBUG_PRINT	// Debug
	Ddim_Print(("im_ela_ctrl( ) : calculate curtail bayer data END\n"));
#endif

	/* calculate extraction noise data */
	im_ela_reg_calc_extract_noise_data(NULL, ctrl_ela->extractNoiseAddr, ctrl_ela->noiseSuppressAddr );
#ifdef CO_ELA_DEBUG_PRINT	// Debug
	Ddim_Print(("im_ela_ctrl( ) : calculate extraction noise data END\n"));
#endif

	/* EIWch register setting */
	im_ela_reg_ctrl_eiwch_register(NULL);
#ifdef CO_ELA_DEBUG_PRINT	// Debug
	Ddim_Print(("im_ela_ctrl( ) : EIWch register setting END\n"));
#endif

	/* ENWch register setting */
	im_ela_reg_ctrl_enwch_register(NULL);
#ifdef CO_ELA_DEBUG_PRINT	// Debug
	Ddim_Print(("im_ela_ctrl( ) : ENWch register setting END\n"));
#endif

	/* ENWMch register setting */
	im_ela_reg_enrach_enwmch_register(NULL);
#ifdef CO_ELA_DEBUG_PRINT	// Debug
	Ddim_Print(("im_ela_ctrl( ) : ENWMch register setting END\n"));
#endif

	imEla->gImElaCallbackFunc = ctrl_ela->pCallBack;
	im_ela_core_off_pclk(NULL);
	ImElaReg_IM_ELA_DSB();

	return D_DDIM_OK;
}

/**
 * @brief		The register at the ELA common parameters is get
 * @param[out]	TImElaCtrlCommon* ctrl_ela_common
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_get_ctrl_common(ImEla*self, TImElaCtrlCommon* ctrl_ela_common )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( ctrl_ela_common == NULL ){
		Ddim_Assertion(("im_ela_get_ctrl_common( ) error. ctrl_ela_common = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_ela_core_on_pclk(NULL);

	ctrl_ela_common->noiseDataMode			= IO_ELA.NSLMD.bit.NSLMD;		// Noise data mode
	ctrl_ela_common->noiseDataPrecision		= IO_ELA.NSLMD.bit.NSLRES;		// Noise data precision
	ctrl_ela_common->noiseDataCompressEnable	= IO_ELA.NSLMD.bit.NSLKNE;		// Noise data compression enable
	ctrl_ela_common->bayerStartPixelType		= IO_ELA.BYRTYP.bit.ORG;		// Bayer data start-pixel type

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		The register at the EIRch is get
 * @param[out]	TImElaCtrlEirch* ctrl_ela_eirch
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_get_ctrl_eirch(ImEla*self, TImElaCtrlEirch* const ctrl_ela_eirch )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( ctrl_ela_eirch == NULL ){
		Ddim_Assertion(("im_ela_get_ctrl_eirch( ) error. ctrl_ela_eirch = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_ela_core_on_pclk(NULL);

	ctrl_ela_eirch->inBayerTopAddr = IO_ELA.EIRA.word;			// Input bayer data top address

	ctrl_ela_eirch->inBayerTopOffset =IO_ELA.EIROFS.bit.EIROFS;	// Input bayer data Top area bit offset

	ctrl_ela_eirch->inBayerTotalHsize = IO_ELA.EIRDEF.word;		// Input bayer data total horizontal size
	ctrl_ela_eirch->inBayerHsize = IO_ELA.EIRHSIZ.word;			// Input bayer data horizontal size
	ctrl_ela_eirch->inBayerVline = IO_ELA.EIRVSIZ.word;			// Input bayer data vertical line

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		The register at the EIWch is get
 * @param[out]	TImElaCtrlEiwch* ctrl_ela_eiwch
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_get_ctrl_eiwch(ImEla*self, TImElaCtrlEiwch* const ctrl_ela_eiwch )
{
	UINT32	i;
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( ctrl_ela_eiwch == NULL ){
		Ddim_Assertion(("im_ela_get_ctrl_eiwch( ) error. ctrl_ela_eiwch = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_ela_core_on_pclk(NULL);

	for( i =0; i < ImEla_D_IM_ELA_EIWCH_ADDR_MAX; i++ ){
		ctrl_ela_eiwch->outBayerTopAddr[i] = IO_ELA.EIWA.word[i];	// Output bayer data top address
	}
	ctrl_ela_eiwch->outBayerTotalHsize = IO_ELA.EIWDEF.word;			// Output bayer data total horizontal size

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		The register at the ENWch is get
 * @param[out]	TImElaCtrlEnwch* ctrl_ela_enwch
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_get_ctrl_enwch(ImEla*self, TImElaCtrlEnwch* const ctrl_ela_enwch )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( ctrl_ela_enwch == NULL ){
		Ddim_Assertion(("im_ela_get_ctrl_enwch( ) error. ctrl_ela_enwch = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_ela_core_on_pclk(NULL);

	ctrl_ela_enwch->outExtractNoiseTopAddr = IO_ELA.ENWA.word;		// Output extraction noise data top address
	ctrl_ela_enwch->outExtractNoiseTotalHsize = IO_ELA.ENWDEF.word;	// Output extraction noise data total horizontal size

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		The register at the ENREch is get
 * @param[out]	TImElaCtrlEnrech* ctrl_ela_enrech
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_get_ctrl_enrech(ImEla*self, TImElaCtrlEnrech* const ctrl_ela_enrech )
{
	UINT32	i;
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( ctrl_ela_enrech == NULL ){
		Ddim_Assertion(("im_ela_get_ctrl_enrech( ) error. ctrl_ela_enrech = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_ela_core_on_pclk(NULL);

	for( i =0; i < ImEla_D_IM_ELA_ENRECH_ADDR_MAX; i++ ){
		ctrl_ela_enrech->inExtractNoiseTopAddr[i] = IO_ELA.ENRA.word[i];	// Input extraction noise data top address
	}
	ctrl_ela_enrech->inExtractNoiseHsize = IO_ELA.ENRHSIZ.word;		// Input extraction noise data horizontal size
	ctrl_ela_enrech->inExtractNoiseVline = IO_ELA.ENRVSIZ.word;	// Input extraction noise data vertical line

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		The register at the ENRAch/ENWMch is get
 * @param[out]	TImElaCtrlEnrachEnwmch* ctrl_ela_enrach_enwmch
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_get_ctrl_enrach_enwmch(ImEla*self,  TImElaCtrlEnrachEnwmch* const ctrl_ela_enrach_enwmch )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( ctrl_ela_enrach_enwmch == NULL ){
		Ddim_Assertion(("im_ela_get_ctrl_enrach_enwmch( ) error. ctrl_ela_enrach_enwmch = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_ela_core_on_pclk(NULL);

	ctrl_ela_enrach_enwmch->syntheticNoiseTopAddr = IO_ELA.ENSA.word;		// Input/Output synthetic noise data top address
	ctrl_ela_enrach_enwmch->syntheticNoiseTotalHsize = IO_ELA.ENSDEF.word;	// Input/Output synthetic noise data total horizontal size
	ctrl_ela_enrach_enwmch->syntheticNoiseHsize = IO_ELA.ENSHSIZ.word;		// Input/Output synthetic noise data horizontal size
	ctrl_ela_enrach_enwmch->syntheticNoiseVline = IO_ELA.ENSVSIZ.word;		// Input/Output synthetic noise data vertical line

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		The register at the core information is get
 * @param[out]	TImElaCtrlCore* ctrl_ela_core
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_get_ctrl_core(ImEla*self, TImElaCtrlCore* const ctrl_ela_core )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( ctrl_ela_core == NULL ){
		Ddim_Assertion(("im_ela_get_ctrl_core( ) error. ctrl_ela_core = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_ela_core_on_pclk(NULL);

	ctrl_ela_core->defectCorrectionMode = IO_ELA.BYRTYP.bit.ELADCMD;		// Defect pixel correction mode
	ctrl_ela_core->zeroPointLevel = IO_ELA.ELFZP.bit.ELFZP;				// Zero point level

	ctrl_ela_core->elfLt[0] = IO_ELA.ELFL.ELFL1.bit.ELFL_1;					// ELF luminance threshold 1
	ctrl_ela_core->elfLt[1] = IO_ELA.ELFL.ELFL1.bit.ELFL_2;					// ELF luminance threshold 2
	ctrl_ela_core->elfLt[2] = IO_ELA.ELFL.ELFL2.bit.ELFL_3;					// ELF luminance threshold 3
	ctrl_ela_core->elfLt[3] = IO_ELA.ELFL.ELFL2.bit.ELFL_4;					// ELF luminance threshold 4

	ctrl_ela_core->anbR.offset[0] = IO_ELA.ANBOR.ANBOR1.bit.ANBOR_0;		// Noise characteristics of the pixel R : Offset 0
	ctrl_ela_core->anbR.offset[1] = IO_ELA.ANBOR.ANBOR1.bit.ANBOR_1;		// Noise characteristics of the pixel R : Offset 1
	ctrl_ela_core->anbR.offset[2] = IO_ELA.ANBOR.ANBOR2.bit.ANBOR_2;		// Noise characteristics of the pixel R : Offset 2
	ctrl_ela_core->anbR.offset[3] = IO_ELA.ANBOR.ANBOR2.bit.ANBOR_3;		// Noise characteristics of the pixel R : Offset 3
	ctrl_ela_core->anbR.gain[0] = IO_ELA.ANBKR.ANBKR1.bit.ANBKR_0;			// Noise characteristics of the pixel R : Gain 0
	ctrl_ela_core->anbR.gain[1] = IO_ELA.ANBKR.ANBKR1.bit.ANBKR_1;			// Noise characteristics of the pixel R : Gain 1
	ctrl_ela_core->anbR.gain[2] = IO_ELA.ANBKR.ANBKR2.bit.ANBKR_2;			// Noise characteristics of the pixel R : Gain 2
	ctrl_ela_core->anbR.gain[3] = IO_ELA.ANBKR.ANBKR2.bit.ANBKR_3;			// Noise characteristics of the pixel R : Gain 3
	ctrl_ela_core->anbR.boundary[0] = IO_ELA.ANBDR.ANBDR1.bit.ANBDR_0;		// Noise characteristics of the pixel R : boundary 0
	ctrl_ela_core->anbR.boundary[1] = IO_ELA.ANBDR.ANBDR1.bit.ANBDR_1;		// Noise characteristics of the pixel R : boundary 1
	ctrl_ela_core->anbR.boundary[2] = IO_ELA.ANBDR.ANBDR2.bit.ANBDR_2;		// Noise characteristics of the pixel R : boundary 2
	ctrl_ela_core->anbR.boundary[3] = IO_ELA.ANBDR.ANBDR2.bit.ANBDR_3;		// Noise characteristics of the pixel R : boundary 3

	ctrl_ela_core->anbG.offset[0] = IO_ELA.ANBOG.ANBOG1.bit.ANBOG_0;		// Noise characteristics of the pixel G : Offset 0
	ctrl_ela_core->anbG.offset[1] = IO_ELA.ANBOG.ANBOG1.bit.ANBOG_1;		// Noise characteristics of the pixel G : Offset 1
	ctrl_ela_core->anbG.offset[2] = IO_ELA.ANBOG.ANBOG2.bit.ANBOG_2;		// Noise characteristics of the pixel G : Offset 2
	ctrl_ela_core->anbG.offset[3] = IO_ELA.ANBOG.ANBOG2.bit.ANBOG_3;		// Noise characteristics of the pixel G : Offset 3
	ctrl_ela_core->anbG.gain[0] = IO_ELA.ANBKG.ANBKG1.bit.ANBKG_0;			// Noise characteristics of the pixel G : Gain 0
	ctrl_ela_core->anbG.gain[1] = IO_ELA.ANBKG.ANBKG1.bit.ANBKG_1;			// Noise characteristics of the pixel G : Gain 1
	ctrl_ela_core->anbG.gain[2] = IO_ELA.ANBKG.ANBKG2.bit.ANBKG_2;			// Noise characteristics of the pixel G : Gain 2
	ctrl_ela_core->anbG.gain[3] = IO_ELA.ANBKG.ANBKG2.bit.ANBKG_3;			// Noise characteristics of the pixel G : Gain 3
	ctrl_ela_core->anbG.boundary[0] = IO_ELA.ANBDG.ANBDG1.bit.ANBDG_0;		// Noise characteristics of the pixel G : boundary 0
	ctrl_ela_core->anbG.boundary[1] = IO_ELA.ANBDG.ANBDG1.bit.ANBDG_1;		// Noise characteristics of the pixel G : boundary 1
	ctrl_ela_core->anbG.boundary[2] = IO_ELA.ANBDG.ANBDG2.bit.ANBDG_2;		// Noise characteristics of the pixel G : boundary 2
	ctrl_ela_core->anbG.boundary[3] = IO_ELA.ANBDG.ANBDG2.bit.ANBDG_3;		// Noise characteristics of the pixel G : boundary 3

	ctrl_ela_core->anbB.offset[0] = IO_ELA.ANBOB.ANBOB1.bit.ANBOB_0;		// Noise characteristics of the pixel B : Offset 0
	ctrl_ela_core->anbB.offset[1] = IO_ELA.ANBOB.ANBOB1.bit.ANBOB_1;		// Noise characteristics of the pixel B : Offset 1
	ctrl_ela_core->anbB.offset[2] = IO_ELA.ANBOB.ANBOB2.bit.ANBOB_2;		// Noise characteristics of the pixel B : Offset 2
	ctrl_ela_core->anbB.offset[3] = IO_ELA.ANBOB.ANBOB2.bit.ANBOB_3;		// Noise characteristics of the pixel B : Offset 3
	ctrl_ela_core->anbB.gain[0] = IO_ELA.ANBKB.ANBKB1.bit.ANBKB_0;			// Noise characteristics of the pixel B : Gain 0
	ctrl_ela_core->anbB.gain[1] = IO_ELA.ANBKB.ANBKB1.bit.ANBKB_1;			// Noise characteristics of the pixel B : Gain 1
	ctrl_ela_core->anbB.gain[2] = IO_ELA.ANBKB.ANBKB2.bit.ANBKB_2;			// Noise characteristics of the pixel B : Gain 2
	ctrl_ela_core->anbB.gain[3] = IO_ELA.ANBKB.ANBKB2.bit.ANBKB_3;			// Noise characteristics of the pixel B : Gain 3
	ctrl_ela_core->anbB.boundary[0] = IO_ELA.ANBDB.ANBDB1.bit.ANBDB_0;		// Noise characteristics of the pixel B : boundary 0
	ctrl_ela_core->anbB.boundary[1] = IO_ELA.ANBDB.ANBDB1.bit.ANBDB_1;		// Noise characteristics of the pixel B : boundary 1
	ctrl_ela_core->anbB.boundary[2] = IO_ELA.ANBDB.ANBDB2.bit.ANBDB_2;		// Noise characteristics of the pixel B : boundary 2
	ctrl_ela_core->anbB.boundary[3] = IO_ELA.ANBDB.ANBDB2.bit.ANBDB_3;		// Noise characteristics of the pixel B : boundary 3

	ctrl_ela_core->lumenGainR = IO_ELA.LGTW.LGTW1.bit.LGTWR;				// R Gain for luminance
	ctrl_ela_core->lumenGainG = IO_ELA.LGTW.LGTW1.bit.LGTWG;				// G Gain for luminance
	ctrl_ela_core->lumenGainB = IO_ELA.LGTW.LGTW2.bit.LGTWB;				// B Gain for luminance

	ctrl_ela_core->lumenFactorR = IO_ELA.LGT.bit.LGTR;					// R factor for the luminance
	ctrl_ela_core->lumenFactorG = IO_ELA.LGT.bit.LGTG;					// G factor for the luminance
	ctrl_ela_core->lumenFactorB = IO_ELA.LGT.bit.LGTB;					// B factor for the luminance
	ctrl_ela_core->lumenFactorC = IO_ELA.LGT.bit.LGTC;					// C factor for the luminance

	ctrl_ela_core->lumenEdgeR = IO_ELA.LGTE.bit.LGTER;					// R factor for the degree of weight edge
	ctrl_ela_core->lumenEdgeG = IO_ELA.LGTE.bit.LGTEG;					// G factor for the degree of weight edge
	ctrl_ela_core->lumenEdgeB = IO_ELA.LGTE.bit.LGTEB;					// B factor for the degree of weight edge

	ctrl_ela_core->edgeAdjustA1 = IO_ELA.EDG2ANBA.bit.EDG2ANBA;			// Set the degree adjustment factor-1 edge of A
	ctrl_ela_core->edgeAdjustA2 = IO_ELA.EDGSCLA.bit.EDGSCLA;				// Set the degree adjustment factor-2 edge of A
	ctrl_ela_core->edgeAdjustB1 = IO_ELA.EDG2ANBB.bit.EDG2ANBB;			// Set the degree adjustment factor-1 edge of B
	ctrl_ela_core->edgeAdjustB2 = IO_ELA.EDGSCLB.bit.EDGSCLB;				// Set the degree adjustment factor-2 edge of B

	ctrl_ela_core->edgeThreshold[0] = IO_ELA.ALNGE.ALNGE1.bit.ALNGE_1;		// Edge degree threshold 1
	ctrl_ela_core->edgeThreshold[1] = IO_ELA.ALNGE.ALNGE1.bit.ALNGE_2;		// Edge degree threshold 1
	ctrl_ela_core->edgeThreshold[2] = IO_ELA.ALNGE.ALNGE2.bit.ALNGE_3;		// Edge degree threshold 1

	ctrl_ela_core->nr[0]  = IO_ELA.ALNG.ALNG1.bit.ALNGL1E1N;				// NR intensity :Luminance L1, Edge E1
	ctrl_ela_core->nr[1]  = IO_ELA.ALNG.ALNG1.bit.ALNGL1E2N;				// NR intensity :Luminance L1, Edge E2
	ctrl_ela_core->nr[2]  = IO_ELA.ALNG.ALNG2.bit.ALNGL1E3N;				// NR intensity :Luminance L1, Edge E3
	ctrl_ela_core->nr[3]  = IO_ELA.ALNG.ALNG2.bit.ALNGL2E1N;				// NR intensity :Luminance L2, Edge E1
	ctrl_ela_core->nr[4]  = IO_ELA.ALNG.ALNG3.bit.ALNGL2E2N;				// NR intensity :Luminance L2, Edge E2
	ctrl_ela_core->nr[5]  = IO_ELA.ALNG.ALNG3.bit.ALNGL2E3N;				// NR intensity :Luminance L2, Edge E3
	ctrl_ela_core->nr[6]  = IO_ELA.ALNG.ALNG4.bit.ALNGL3E1N;				// NR intensity :Luminance L3, Edge E1
	ctrl_ela_core->nr[7]  = IO_ELA.ALNG.ALNG4.bit.ALNGL3E2N;				// NR intensity :Luminance L3, Edge E2
	ctrl_ela_core->nr[8]  = IO_ELA.ALNG.ALNG5.bit.ALNGL3E3N;				// NR intensity :Luminance L3, Edge E3
	ctrl_ela_core->nr[9]  = IO_ELA.ALNG.ALNG5.bit.ALNGL4E1N;				// NR intensity :Luminance L4, Edge E1
	ctrl_ela_core->nr[10] = IO_ELA.ALNG.ALNG6.bit.ALNGL4E2N;				// NR intensity :Luminance L4, Edge E2
	ctrl_ela_core->nr[11] = IO_ELA.ALNG.ALNG6.bit.ALNGL4E3N;				// NR intensity :Luminance L4, Edge E3

	ctrl_ela_core->lNoise = IO_ELA.LFTH.bit.LFTH;							// L extraction threshold noise
	ctrl_ela_core->lEdge[0] = IO_ELA.LCOME.bit.LCOME1;						// Edge applicable threshold contour L 1
	ctrl_ela_core->lEdge[1] = IO_ELA.LCOME.bit.LCOME2;						// Edge applicable threshold contour L 2
	ctrl_ela_core->lIntense[0] = IO_ELA.LCOMEN.bit.LCOME1N;				// Applied intensity L 1
	ctrl_ela_core->lIntense[1] = IO_ELA.LCOMEN.bit.LCOME2N;				// Applied intensity L 2

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		The register at OB Correction control is get
 * @param[out]	TImElaCtrlObCorrection* ctrl_ela_ob
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_get_ctrl_ob_correction(ImEla*self, TImElaCtrlObCorrection* const ctrl_ela_ob )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( ctrl_ela_ob == NULL ){
		Ddim_Assertion(("im_ela_get_ctrl_ob_correction( ) error. ctrl_ela_ob = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_ela_core_on_pclk(NULL);
	// OB Correction R Pixel
	ImElaReg_IM_ELA_GET_REG_SIGNED(ctrl_ela_ob->obRr, IO_ELA.OBOF.OBOF1, union io_ela_obof_1, EOBRR);
	// OB Correction B Pixel
	ImElaReg_IM_ELA_GET_REG_SIGNED(ctrl_ela_ob->obBb, IO_ELA.OBOF.OBOF1, union io_ela_obof_1, EOBBB);
	// OB Correction Gr Pixel
	ImElaReg_IM_ELA_GET_REG_SIGNED(ctrl_ela_ob->obGr, IO_ELA.OBOF.OBOF2, union io_ela_obof_2, EOBGR);
	// OB Correction Gb Pixel
	ImElaReg_IM_ELA_GET_REG_SIGNED(ctrl_ela_ob->obGb, IO_ELA.OBOF.OBOF2, union io_ela_obof_2, EOBGB);

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		Set address of parameter for multiple times execution
 * @param[in]	TImElaMultipleTimesInfo* multiple_exec_info
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	This API calls before Im_ELA_Start() or im_ela_reg_start_async(NULL).
 */
UINT32 im_ela_set_multiple_exec_info(ImEla*self, const TImElaMultipleTimesInfo* const multiple_exec_info )
{
	ImEla *imEla  =  im_ela_get();
	TImElaMultipleTimesInfo *gImElaMultipleExecInfo = im_ela_get_g_im_ela_multiple_exec_info(imEla);

#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( multiple_exec_info == NULL ){
		Ddim_Assertion(("im_ela_set_multiple_exec_info( ) error. multiple_exec_info = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_ela_core_on_pclk(NULL);

	memcpy( (TImElaMultipleTimesInfo*)&imEla->gImElaMultipleExecInfo, multiple_exec_info, sizeof(TImElaMultipleTimesInfo) );

	/* multiple times execution parameter for 1st time*/
	if( gImElaMultipleExecInfo->core[0] != NULL ){
		im_ela_ctrl_core_register( gImElaMultipleExecInfo->core[0] );
	}

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		The register setting of NSLMD is acquired.
 * @param[out]	TImElaCtrlNslmd* const nslmd
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32  im_ela_get_nslmd(ImEla*self, TImElaCtrlNslmd* const nslmd )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( nslmd == NULL ){
		Ddim_Assertion(("im_ela_get_nslmd( ) error. nslmd = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK
	im_ela_core_on_pclk(NULL);

	nslmd->noiseDataMode				= IO_ELA.NSLMD.bit.NSLMD;
	nslmd->noiseDataPrecision			= IO_ELA.NSLMD.bit.NSLRES;
	nslmd->noiseDataCompressEnable	= IO_ELA.NSLMD.bit.NSLKNE;

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		The register is set for EAch.
 * @param[in]	TImElaCtrlEach* const ctrl_each
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_set_each(ImEla*self, const TImElaCtrlEach* const ctrl_each )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( ctrl_each == NULL ){
		Ddim_Assertion(("im_ela_set_each() error. ctrl_each = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK
	im_ela_core_on_pclk(NULL);

	IO_ELA.EARCACHE.bit.EARCACHE_0		= ctrl_each->cacheTypeR[0];
	IO_ELA.EARCACHE.bit.EARCACHE_1		= ctrl_each->cacheTypeR[1];
	IO_ELA.EARCACHE.bit.EARCACHE_2		= ctrl_each->cacheTypeR[2];

	IO_ELA.EAWCACHE.bit.EAWCACHE_0		= ctrl_each->cacheTypeW[0];
	IO_ELA.EAWCACHE.bit.EAWCACHE_1		= ctrl_each->cacheTypeW[1];
	IO_ELA.EAWCACHE.bit.EAWCACHE_2		= ctrl_each->cacheTypeW[2];

	IO_ELA.EARPROT.bit.EARPROT_0		= ctrl_each->protectTypeR[0];
	IO_ELA.EARPROT.bit.EARPROT_1		= ctrl_each->protectTypeR[1];
	IO_ELA.EARPROT.bit.EARPROT_2		= ctrl_each->protectTypeR[2];

	IO_ELA.EAWPROT.bit.EAWPROT_0		= ctrl_each->protectTypeW[0];
	IO_ELA.EAWPROT.bit.EAWPROT_1		= ctrl_each->protectTypeW[1];
	IO_ELA.EAWPROT.bit.EAWPROT_2		= ctrl_each->protectTypeW[2];

	IO_ELA.EARREQMSK.EARREQMSK1.bit.EARREQMSK_0	= ctrl_each->reqMaskR[0];
	IO_ELA.EARREQMSK.EARREQMSK1.bit.EARREQMSK_1	= ctrl_each->reqMaskR[1];
	IO_ELA.EARREQMSK.EARREQMSK2.bit.EARREQMSK_2	= ctrl_each->reqMaskR[2];

	IO_ELA.EAWREQMSK.EAWREQMSK1.bit.EAWREQMSK_0	= ctrl_each->reqMaskW[0];
	IO_ELA.EAWREQMSK.EAWREQMSK1.bit.EAWREQMSK_1	= ctrl_each->reqMaskW[1];
	IO_ELA.EAWREQMSK.EAWREQMSK2.bit.EAWREQMSK_2	= ctrl_each->reqMaskW[2];

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		The register setting of EAch is acquired.
 * @param[out]	TImElaCtrlEach* const ctrl_each
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_get_each(ImEla*self, TImElaCtrlEach* const ctrl_each )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( ctrl_each == NULL ){
		Ddim_Assertion(("im_ela_get_each() error. ctrl_each = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK
	im_ela_core_on_pclk(NULL);

	ctrl_each->cacheTypeR[0]		= IO_ELA.EARCACHE.bit.EARCACHE_0;
	ctrl_each->cacheTypeR[1]		= IO_ELA.EARCACHE.bit.EARCACHE_1;
	ctrl_each->cacheTypeR[2]		= IO_ELA.EARCACHE.bit.EARCACHE_2;

	ctrl_each->cacheTypeW[0]		= IO_ELA.EAWCACHE.bit.EAWCACHE_0;
	ctrl_each->cacheTypeW[1]		= IO_ELA.EAWCACHE.bit.EAWCACHE_1;
	ctrl_each->cacheTypeW[2]		= IO_ELA.EAWCACHE.bit.EAWCACHE_2;

	ctrl_each->protectTypeR[0]	= IO_ELA.EARPROT.bit.EARPROT_0;
	ctrl_each->protectTypeR[1]	= IO_ELA.EARPROT.bit.EARPROT_1;
	ctrl_each->protectTypeR[2]	= IO_ELA.EARPROT.bit.EARPROT_2;

	ctrl_each->protectTypeW[0]	= IO_ELA.EAWPROT.bit.EAWPROT_0;
	ctrl_each->protectTypeW[1]	= IO_ELA.EAWPROT.bit.EAWPROT_1;
	ctrl_each->protectTypeW[2]	= IO_ELA.EAWPROT.bit.EAWPROT_2;

	ctrl_each->reqMaskR[0]		= IO_ELA.EARREQMSK.EARREQMSK1.bit.EARREQMSK_0;
	ctrl_each->reqMaskR[1]		= IO_ELA.EARREQMSK.EARREQMSK1.bit.EARREQMSK_1;
	ctrl_each->reqMaskR[2]		= IO_ELA.EARREQMSK.EARREQMSK2.bit.EARREQMSK_2;

	ctrl_each->reqMaskW[0]		= IO_ELA.EAWREQMSK.EAWREQMSK1.bit.EAWREQMSK_0;
	ctrl_each->reqMaskW[1]		= IO_ELA.EAWREQMSK.EAWREQMSK1.bit.EAWREQMSK_1;
	ctrl_each->reqMaskW[2]		= IO_ELA.EAWREQMSK.EAWREQMSK2.bit.EAWREQMSK_2;

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

/**
 * @brief		The register setting of AXI status is acquired.
 * @param[out]	TImElaEachAxi* const each_axi
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_get_axi_status(ImEla*self, TImElaEachAxi* const each_axi )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( each_axi == NULL ){
		Ddim_Assertion(("im_ela_get_axi_status() error. each_axi = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK
	im_ela_core_on_pclk(NULL);

	each_axi->axiReplyR[0]	= IO_ELA.EARAXSTS.bit.RRESP_0;
	each_axi->axiReplyR[1]	= IO_ELA.EARAXSTS.bit.RRESP_1;
	each_axi->axiReplyR[2]	= IO_ELA.EARAXSTS.bit.RRESP_2;

	each_axi->axiReplyW[0]	= IO_ELA.EAWAXSTS.bit.BRESP_0;
	each_axi->axiReplyW[1]	= IO_ELA.EAWAXSTS.bit.BRESP_1;
	each_axi->axiReplyW[2]	= IO_ELA.EAWAXSTS.bit.BRESP_2;

	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

ImEla *im_ela_get(void)
{
	static ImEla *imEla = NULL;
	if(!imEla)
		imEla = k_object_new_with_private(IM_TYPE_ELA,sizeof(ImElaPrivate));
	    imEla->gImElaStageCnt = 0;
	    imEla->gImElaStepCnt = 0;
	    imEla->gImElaNextCtrlFlag = 0;
	    imEla->gImElaCallbackFunc= NULL;
	return imEla;
}
