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
#include "imelareg.h"
#include "imela.h"
#include "imelacore.h"
#include "jdsela.h"
#include "dd_arm.h"
#include "ddim_user_custom.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImElaReg, im_ela_reg)
#define IM_ELA_REG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImElaRegPrivate,IM_TYPE_ELA_REG))

struct _ImElaRegPrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
static volatile TImElaCurtailBayerData		S_G_IM_ELA_CURTAIL_BAYER[ImElaReg_D_IM_ELA_STAGE_MAX];
static volatile TImElaExtractNoiseData		S_G_IM_ELA_EXTRACT_NOISE[ImElaReg_D_IM_ELA_STAGE_MAX];

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
static VOID imElaCtrlNextEirchRegister( VOID );
static VOID imElaCtrlEnrechRegister( VOID );

static void im_ela_reg_constructor(ImElaReg *self)
{
}

static void im_ela_reg_destructor(ImElaReg *self)
{
}

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/**
 * @brief		EIRch register next setting
 * @param[in]	None
 * @return		None
 * @note		None
 * @attention	None
 */
static VOID imElaCtrlNextEirchRegister( VOID )
{
	TImElaCtrlEirch ctrlEirch;
	ImEla *imEla  =  im_ela_get();
//	UCHAR *gImElaStageCnt = im_ela_get_g_im_ela_stage_cnt(imEla);
//	UCHAR *gImElaStepCnt = im_ela_get_g_im_ela_step_cnt(imEla);

	// The EIRA is populated with EIWA data from the previous stage.
	ctrlEirch.inBayerTopOffset = 0;
	ctrlEirch.inBayerTotalHsize = S_G_IM_ELA_CURTAIL_BAYER[imEla->gImElaStageCnt - 1].glHbyte;
	ctrlEirch.inBayerHsize = S_G_IM_ELA_CURTAIL_BAYER[imEla->gImElaStageCnt - 1].hSize;
	ctrlEirch.inBayerVline = S_G_IM_ELA_CURTAIL_BAYER[imEla->gImElaStageCnt - 1].vLine;
	ctrlEirch.inBayerTopAddr = S_G_IM_ELA_CURTAIL_BAYER[imEla->gImElaStageCnt - 1].bayerAddr[imEla->gImElaStepCnt];

	im_ela_ctrl_eirch_register( ctrlEirch );
}

/**
 * @brief		ENREch register setting
 * @param[in]	None
 * @return		None
 * @note		None
 * @attention	None
 */
static VOID imElaCtrlEnrechRegister( VOID )
{
	UINT32 i;
	ImEla *imEla  =  im_ela_get();
//	UCHAR *gImElaStageCnt = im_ela_get_g_im_ela_stage_cnt(imEla);

	for( i =0; i < ImEla_D_IM_ELA_ENRECH_ADDR_MAX; i++ ){
		IO_ELA.ENRA.word[i] = S_G_IM_ELA_EXTRACT_NOISE[imEla->gImElaStageCnt].noiseDataAddr[i];
	}
	IO_ELA.ENRHSIZ.bit.ENRHSIZ = S_G_IM_ELA_EXTRACT_NOISE[imEla->gImElaStageCnt].hSize;
	IO_ELA.ENRVSIZ.bit.ENRVSIZ = S_G_IM_ELA_EXTRACT_NOISE[imEla->gImElaStageCnt].vLine;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/**
 * @brief		Common register & EIRch register & ENWch/ENWch register setting
 * @param[in]	None
 * @return		None
 * @note		None
 * @attention	None
 */
VOID im_ela_reg_ctrl_next_register(ImElaReg*self)
{
	ImEla *imEla  =  im_ela_get();
//	UCHAR *gImElaStageCnt = im_ela_get_g_im_ela_stage_cnt(imEla);
	UCHAR *gImElaStepCnt = im_ela_get_g_im_ela_step_cnt(imEla);
	TImElaBayerMng *gImElaBayer = im_ela_get_g_im_ela_bayer(imEla);
	TImElaMultipleTimesInfo *gImElaMultipleExecInfo = im_ela_get_g_im_ela_multiple_exec_info(imEla);
	TImElaQelatmd *gImElaQelatmdInfo = im_ela_get_g_im_ela_qelatmd_info(imEla);

	/* common register setting */
	if( imEla->gImElaStepCnt == 0 ){
		IO_ELA.ELACTL.bit.ELACNT += 1;													// ELA count
	}
	IO_ELA.ELACTL.bit.ELAMD = gImElaQelatmdInfo->elaDensityMode[ImElaReg_IM_ELA_CONV_STAGE_TO_LEVEL(imEla->gImElaStageCnt)];	// ELA density mode

	if( imEla->gImElaStepCnt == ImElaReg_D_IM_ELA_STEP_S ){
		IO_ELA.ELACTL.bit.ELAACT = ImElaReg_D_IM_ELA_ELAACT_COMBINE;								// Synthesis mode
		imElaCtrlEnrechRegister();													// ENRAch/ENWMch register setting
		im_ela_reg_enrach_enwmch_register(NULL);
	}
	else{
		IO_ELA.ELACTL.bit.ELAACT = ImElaReg_D_IM_ELA_ELAACT_EXTRACT;								// Synthesis mode
		IO_ELA.ELABYR.bit.EIRTYP = gImElaBayer->eiwDtype;								// Input data type
		IO_ELA.ELABYR.bit.EIRSFT = gImElaBayer->eiwSft;								// Input bit shift mode

		if( gImElaQelatmdInfo->elaElfLevel == ImElaReg_IM_ELA_CONV_STAGE_TO_LEVEL(imEla->gImElaStageCnt) ){
			IO_ELA.ELABYR.bit.EIWOUT = ImEla_D_IM_ELA_EIWOUT_NONE;
		}
		else{
			switch( gImElaQelatmdInfo->elaDensityMode[ImElaReg_IM_ELA_CONV_STAGE_TO_LEVEL(imEla->gImElaStageCnt) + 1] ){
				case ImEla_E_IM_ELA_DENSITY_MODE_0:
				case ImEla_E_IM_ELA_DENSITY_MODE_1:
					if( gImElaStepCnt == 0 ){
						IO_ELA.ELABYR.bit.EIWOUT = ImEla_D_IM_ELA_EIWOUT_1;
					}
					else{
						IO_ELA.ELABYR.bit.EIWOUT = ImEla_D_IM_ELA_EIWOUT_NONE;
					}
					break;
				case ImEla_E_IM_ELA_DENSITY_MODE_2:
					if( gImElaStepCnt == 0 ){
						IO_ELA.ELABYR.bit.EIWOUT = ImEla_D_IM_ELA_EIWOUT_4;
					}
					else{
						IO_ELA.ELABYR.bit.EIWOUT = ImEla_D_IM_ELA_EIWOUT_NONE;
					}
					break;
//				case ImEla_E_IM_ELA_DENSITY_MODE_3:
				default:
					if( imEla->gImElaStepCnt < 4 ){
						IO_ELA.ELABYR.bit.EIWOUT = ImEla_D_IM_ELA_EIWOUT_4;
					}
					else{
						IO_ELA.ELABYR.bit.EIWOUT = ImEla_D_IM_ELA_EIWOUT_NONE;
					}
					break;
			}
		}

		IO_ELA.ELABYR.bit.DKNEN = 0;	// Deknee disable
		IO_ELA.ELABYR.bit.DKNACT = 0;
		IO_ELA.ELABYR.bit.EOBAEN = 0;	// "OB correction"/"Optical zero shift" disable

		/* for multiple times execution parameter */
		if( gImElaStepCnt == 0 ){
			if( gImElaMultipleExecInfo->core[imEla->gImElaStageCnt] != NULL ){
				im_ela_ctrl_core_register( gImElaMultipleExecInfo->core[imEla->gImElaStageCnt] );
			}
		}

		// EIRch register setting
		imElaCtrlNextEirchRegister();
		// EIWch register setting
		im_ela_reg_ctrl_eiwch_register(NULL);
		// ENWch register setting
		im_ela_reg_ctrl_enwch_register(NULL);
	}
}

/**
 * @brief		EIWch register setting
 * @param		None
 * @return		None
 * @note		None
 * @attention	None
 */
VOID im_ela_reg_ctrl_eiwch_register(ImElaReg*self)
{
	UINT32	loop_cnt;
	UINT32	loop_start;
	UINT32	loop_end;
	UINT32	glHbyte;
	ImEla *imEla  =  im_ela_get();
//	UCHAR *gImElaStageCnt = im_ela_get_g_im_ela_stage_cnt(imEla);
//	UCHAR *gImElaStepCnt = im_ela_get_g_im_ela_step_cnt(imEla);
	TImElaQelatmd *gImElaQelatmdInfo = im_ela_get_g_im_ela_qelatmd_info(imEla);

	if( gImElaQelatmdInfo->elaElfLevel == ImEla_E_IM_ELA_ELF_LEVEL_1 ||
	   gImElaQelatmdInfo->elaElfLevel == ImElaReg_IM_ELA_CONV_STAGE_TO_LEVEL(imEla->gImElaStageCnt) ){
		return;
	}
	if( imEla->gImElaStepCnt >= 4 ){
		return;
	}

	switch( gImElaQelatmdInfo->elaDensityMode[ImElaReg_IM_ELA_CONV_STAGE_TO_LEVEL(imEla->gImElaStageCnt) + 1] ){
		case ImEla_E_IM_ELA_DENSITY_MODE_0:
		case ImEla_E_IM_ELA_DENSITY_MODE_1:
			if( imEla->gImElaStepCnt >= 1 ){
				return;
			}
			loop_end = 1;
			break;
		case ImEla_E_IM_ELA_DENSITY_MODE_2:
			if( imEla->gImElaStepCnt >= 1 ){
				return;
			}
			loop_end = 4;
			break;
//		case ImEla_E_IM_ELA_DENSITY_MODE_3:
		default:
			if( imEla->gImElaStepCnt >= 4 ){
				return;
			}
			loop_end = 4;
			break;
	}
	loop_start = 4 * imEla->gImElaStepCnt;

	/* EIOch register setting */
	for( loop_cnt = 0; loop_cnt < loop_end; loop_cnt++ ){
		IO_ELA.EIWA.word[loop_cnt] = S_G_IM_ELA_CURTAIL_BAYER[imEla->gImElaStageCnt].bayerAddr[loop_start + loop_cnt];	// Output bayer data top address
	}

	/* calc. and set output bayer number of horizontal all bytes */
	/*
	 *  refer JDSELA1A section 5.5
	 */
	 glHbyte = S_G_IM_ELA_CURTAIL_BAYER[imEla->gImElaStageCnt].glHbyte;
#ifdef CO_IM_ELA_OUT_BAY_DEBUG
	if( gImElaBayer->eiwDtype == D_IM_ELA_EIODTYP_12PACK ){
		if( (glHbyte % 64) == 0 ){
			IO_ELA.EIWDEF.word = glHbyte;
		}
		else{
			// for display of dump bayer file easy on PC tool(for debug)
			IO_ELA.EIWDEF.word = ((glHbyte + 47) / (64 * 3)) * (64 * 3);
		}
	}
	else{
#endif //CO_IM_ELA_OUT_BAY_DEBUG
		if( (glHbyte % 64) == 0 ){
			IO_ELA.EIWDEF.word = glHbyte;
		}
		else{
			IO_ELA.EIWDEF.word = glHbyte + (64 - (glHbyte % 64));
		}
#ifdef CO_IM_ELA_OUT_BAY_DEBUG
	}
#endif //CO_IM_ELA_OUT_BAY_DEBUG
}

/**
 * @brief		ENWch register setting
 * @param[in]	None
 * @return		None
 * @note		None
 * @attention	None
 */
VOID im_ela_reg_ctrl_enwch_register(ImElaReg*self)
{
	ImEla *imEla  =  im_ela_get();
//	UCHAR *gImElaStageCnt = im_ela_get_g_im_ela_stage_cnt(imEla);
//	UCHAR *gImElaStepCnt = im_ela_get_g_im_ela_step_cnt(imEla);

	IO_ELA.ENWA.word = S_G_IM_ELA_EXTRACT_NOISE[imEla->gImElaStageCnt].noiseDataAddr[imEla->gImElaStepCnt];	// Output noise data data top address
	IO_ELA.ENWDEF.word = S_G_IM_ELA_EXTRACT_NOISE[imEla->gImElaStageCnt].glHbyte;							// Output noise data data total horizontal size
}

/**
 * @brief		ENRAch/ENWMch register setting
 * @param[in]	None
 * @return		None
 * @note		None
 * @attention	None
 */
VOID im_ela_reg_enrach_enwmch_register(ImElaReg*self)
{
	IO_ELA.ENSA.word = S_G_IM_ELA_EXTRACT_NOISE[0].noiseDataAddr[0];		// Input/Output synthetic noise data top address

	IO_ELA.ENSDEF.word = S_G_IM_ELA_EXTRACT_NOISE[0].glHbyte;				// Input/Output synthetic noise data total horizontal size
	IO_ELA.ENSHSIZ.word = S_G_IM_ELA_EXTRACT_NOISE[0].hSize;				// Input/Output synthetic noise data horizontal size
	IO_ELA.ENSVSIZ.word = S_G_IM_ELA_EXTRACT_NOISE[0].vLine;				// Input/Output synthetic noise data vertical line
}

/**
 * @brief		calculate curtail bayer data.
 * @param[in]	UINT32 outBayerAddr
 * @return		VOID
 * @note		None
 * @attention	None
 */
VOID im_ela_reg_calc_curtail_bayer_data(ImElaReg*self, UINT32 outBayerAddr )
{
	UCHAR	level = ImEla_E_IM_ELA_ELF_LEVEL_1;
	UCHAR	stage = 0;
	UCHAR	step;
	UCHAR	step_max;
	UCHAR	pd;
	UCHAR	ph;
	UCHAR	pv;
	USHORT	padding_hpixel;		// Number of padding horizontal pixels
	USHORT	padding_vline;		// Number of padding vertical pixels
	UINT32	padding_addr = 0;	// Padding bayer data address
	UINT32	calc_gl_hbyte;		// Calculate global horizontal size
	USHORT	type;
	ImEla *imEla  =  im_ela_get();
	TImElaBayerMng *gImElaBayer = im_ela_get_g_im_ela_bayer(imEla);
	TImElaQelatmd *gImElaQelatmdInfo = im_ela_get_g_im_ela_qelatmd_info(imEla);

	padding_hpixel	= gImElaBayer->hSize;
	padding_vline	= gImElaBayer->vLine;

	if( gImElaBayer->eiwDtype == ImEla_D_IM_ELA_DATATYP_8BIT ){
		type = 8;
	}
	else{
		type = 12;
	}

	for( level = ImEla_E_IM_ELA_ELF_LEVEL_1; level <= gImElaQelatmdInfo->elaElfLevel; level++ ){
		if( level == ImEla_E_IM_ELA_ELF_LEVEL_1 ){
			pd = 16;
		}
		else{
			pd = 8;
		}

		if( (padding_hpixel % 4) == 0 ){
			ph = 2;
		}
		else{
			ph = 6 - (padding_hpixel % 4);
		}

		if( (padding_vline % 4) == 0 ){
			pv = 2;
		}
		else{
			pv = 6 - (padding_vline % 4);
		}

		padding_hpixel	= (padding_hpixel + pd + ph - 2) / 2;
		padding_vline	= (padding_vline + pd + pv - 2) / 2;

		S_G_IM_ELA_CURTAIL_BAYER[stage].vLine = padding_vline;
		S_G_IM_ELA_CURTAIL_BAYER[stage].hSize = padding_hpixel;
		calc_gl_hbyte = padding_hpixel * type / 8;
#ifdef CO_IM_ELA_OUT_BAY_DEBUG
		if( gImElaBayer->eiwDtype == D_IM_ELA_EIODTYP_12PACK ){
			if( (calc_gl_hbyte % 64) != 0 ){
				// for display of dump bayer file easy on PC tool(for debug)
			 	calc_gl_hbyte = ((calc_gl_hbyte + 47) /(64*3)) *(64*3);
			}
		}
		else{
#endif //CO_IM_ELA_OUT_BAY_DEBUG
			if( (calc_gl_hbyte % 64) != 0 ){
			 	calc_gl_hbyte = calc_gl_hbyte + (64 - (calc_gl_hbyte % 64));
			}
#ifdef CO_IM_ELA_OUT_BAY_DEBUG
		}
#endif //CO_IM_ELA_OUT_BAY_DEBUG
	 	S_G_IM_ELA_CURTAIL_BAYER[stage].glHbyte = calc_gl_hbyte;

		if( level == gImElaQelatmdInfo->elaElfLevel ){
			break;
		}
		switch( gImElaQelatmdInfo->elaDensityMode[level + 1] ){
			case ImEla_E_IM_ELA_DENSITY_MODE_0:
			case ImEla_E_IM_ELA_DENSITY_MODE_1:
				step_max = 1;
				break;

			case ImEla_E_IM_ELA_DENSITY_MODE_2:
				step_max = 4;
				break;

//			case ImEla_E_IM_ELA_DENSITY_MODE_3:
			default:
				step_max = 16;
				break;
		}
		for( step = 0; step < step_max; step ++ ){
#ifdef ImElaReg_CO_ELA_OPTIMUM_MEM	//Memory consumption optimization
			if( (gImElaQelatmdInfo->elaElfLevel <= ImEla_E_IM_ELA_ELF_LEVEL_2) ||
			   (gImElaQelatmdInfo->elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_3] != ImEla_E_IM_ELA_DENSITY_MODE_3 ) ){
				if( ((level == ImEla_E_IM_ELA_ELF_LEVEL_1) && (step == 0)) ||
				   ((level == ImEla_E_IM_ELA_ELF_LEVEL_3) && (step == 0)) ){
					padding_addr = outBayerAddr;
				}
				else{
					if( step == 0 ){
						padding_addr += ((UINT32)S_G_IM_ELA_CURTAIL_BAYER[stage - 1].glHbyte * (UINT32)S_G_IM_ELA_CURTAIL_BAYER[stage - 1].vLine);
					}
					else{
						padding_addr += ((UINT32)calc_gl_hbyte * (UINT32)padding_vline);
					}
				}
			}
			else{
				if( ((level == ImEla_E_IM_ELA_ELF_LEVEL_1) && (step == 0)) ||
				   ((level == ImEla_E_IM_ELA_ELF_LEVEL_2) && (step == 0)) ||
				   ((level == ImEla_E_IM_ELA_ELF_LEVEL_4) && (step == 0)) ){
					padding_addr = outBayerAddr;
				}
				else{
					padding_addr += ((UINT32)calc_gl_hbyte * (UINT32)padding_vline);
				}
			}
#else
			if( (level == ImEla_E_IM_ELA_ELF_LEVEL_1) && (step == 0) ){
				padding_addr = outBayerAddr;
			}
			else{
				if( step == 0 ){
					padding_addr += ((UINT32)S_G_IM_ELA_CURTAIL_BAYER[stage - 1].glHbyte * (UINT32)S_G_IM_ELA_CURTAIL_BAYER[stage - 1].vLine);
				}
				else {
					padding_addr += ((UINT32)calc_gl_hbyte * (UINT32)padding_vline);
				}
			}
#endif
			if( (padding_addr % 64) == 0 ){
			 	S_G_IM_ELA_CURTAIL_BAYER[stage].bayerAddr[step] = padding_addr;
			}
			else{
			 	padding_addr = padding_addr + (64 - (padding_addr % 64));
			 	S_G_IM_ELA_CURTAIL_BAYER[stage].bayerAddr[step] = padding_addr;
			}
		}
		stage++;
	}
#ifdef ImElaReg_CO_ELA_OPTIMUM_MEM	// Memory consumption optimization.
	if( (gImElaQelatmdInfo->elaElfLevel <= ImEla_E_IM_ELA_ELF_LEVEL_2) ||
	   (gImElaQelatmdInfo->elaDensityMode[ImEla_E_IM_ELA_ELF_LEVEL_3] != ImEla_E_IM_ELA_DENSITY_MODE_3 ) ){
		// No processing.
	}
	else{
		padding_addr = (S_G_IM_ELA_CURTAIL_BAYER[1].bayerAddr[15] - S_G_IM_ELA_CURTAIL_BAYER[0].bayerAddr[3])
					   + ((UINT32)(S_G_IM_ELA_CURTAIL_BAYER[1].glHbyte) * (UINT32)(S_G_IM_ELA_CURTAIL_BAYER[1].vLine));
		for( step = 0; step < 4; step ++ ){
			S_G_IM_ELA_CURTAIL_BAYER[0].bayerAddr[step] += padding_addr;
		}
	}
#endif

}

/**
 * @brief		calculate curtail bayer data.
 * @param[in]	UINT32 outBayerAddr
 * @param[in]	UINT32 noiseSuppressAddr
 * @return		VOID
 * @note		None
 * @attention	None
 */
VOID im_ela_reg_calc_extract_noise_data(ImElaReg*self, UINT32 extractNoiseAddr, UINT32 noiseSuppressAddr )
{
	UCHAR	level = ImEla_E_IM_ELA_ELF_LEVEL_1;
	UCHAR	stage = 0;
	UCHAR 	step;
	UCHAR 	step_max;
	UCHAR 	pd;
	UCHAR 	rd;
	UCHAR 	ph;
	UCHAR 	pv;
	USHORT	padding_hpixel;		// Number of padding horizontal pixels
	USHORT	padding_vline;		// Number of padding vertical pixels
	UINT32	padding_addr;		// Padding bayer data address
	UINT32	calc_gl_hbyte;		// Calculate global horizontal size
	USHORT	in_bayer_hpixel;	// Number of input bayer horizontal pixels
	USHORT	inBayerVline;		// Number of input bayer vertical pixels
	ImEla *imEla  =  im_ela_get();
	TImElaBayerMng *gImElaBayer = im_ela_get_g_im_ela_bayer(imEla);
	TImElaQelatmd *gImElaQelatmdInfo = im_ela_get_g_im_ela_qelatmd_info(imEla);

	padding_addr = extractNoiseAddr;

	for( level = ImEla_E_IM_ELA_ELF_LEVEL_1; level <= gImElaQelatmdInfo->elaElfLevel; level++ ){
		if( level == ImEla_E_IM_ELA_ELF_LEVEL_1 ){
			in_bayer_hpixel = gImElaBayer->hSize;
			inBayerVline = gImElaBayer->vLine;
		}
		else{
			in_bayer_hpixel = S_G_IM_ELA_CURTAIL_BAYER[stage - 1].hSize;
			inBayerVline = S_G_IM_ELA_CURTAIL_BAYER[stage - 1].vLine;
		}

		if( level == ImEla_E_IM_ELA_ELF_LEVEL_1 ){
			pd = 16;
		}
		else{
			pd = 8;
		}
		if( gImElaQelatmdInfo->elaDensityMode[level] == ImEla_E_IM_ELA_DENSITY_MODE_0 ){
			rd = 2;
		}
		else{
			rd = 1;
		}

		if( (in_bayer_hpixel % 4) == 0 ){
			ph = 2;
		}
		else{
			ph = 6 - (in_bayer_hpixel % 4);
		}

		if( (inBayerVline % 4) == 0 ){
			pv = 2;
		}
		else{
			pv = 6 - (inBayerVline % 4);
		}

		padding_hpixel = (in_bayer_hpixel + pd + ph - 14) / rd;
		padding_vline  = (inBayerVline + pd + pv - 14) / rd;
		S_G_IM_ELA_EXTRACT_NOISE[stage].hSize = padding_hpixel;
		S_G_IM_ELA_EXTRACT_NOISE[stage].vLine = padding_vline;
		if( (padding_hpixel % 64) != 0 ){
		 	calc_gl_hbyte = padding_hpixel + (64 - (padding_hpixel % 64));
		}
		else{
			calc_gl_hbyte = padding_hpixel;
		}
	 	S_G_IM_ELA_EXTRACT_NOISE[stage].glHbyte = calc_gl_hbyte;

		switch( gImElaQelatmdInfo->elaDensityMode[level] ){
			case ImEla_E_IM_ELA_DENSITY_MODE_0:
			case ImEla_E_IM_ELA_DENSITY_MODE_1:
				step_max = 1;
				break;

			case ImEla_E_IM_ELA_DENSITY_MODE_2:
				step_max = 4;
				break;

//			case ImEla_E_IM_ELA_DENSITY_MODE_3:
			default:
				step_max = 16;
				break;
		}
		for( step = 0; step < step_max; step ++ ){
#ifdef ImElaReg_CO_ELA_OPTIMUM_MEM	// Memory consumption optimization.
			if( step == 0 && level == ImEla_E_IM_ELA_ELF_LEVEL_1 ){
				padding_addr = noiseSuppressAddr;
			}
			else if( step == 0 && level >= ImEla_E_IM_ELA_ELF_LEVEL_2 ){
				padding_addr = extractNoiseAddr;
			}
			else{
				padding_addr += (calc_gl_hbyte * padding_vline * 8 / 8);
			}
#else
			if( step == 0 && level == ImEla_E_IM_ELA_ELF_LEVEL_1 ){
				padding_addr = noiseSuppressAddr;
			}
			else if( step == 0 && level == ImEla_E_IM_ELA_ELF_LEVEL_2 ){
				padding_addr = extractNoiseAddr;
			}
			else{
				padding_addr += (calc_gl_hbyte * padding_vline * 8 / 8);
			}
#endif
			if( (padding_addr % 64) == 0 ){
			 	S_G_IM_ELA_EXTRACT_NOISE[stage].noiseDataAddr[step] = padding_addr;
			}
			else {
			 	padding_addr = padding_addr + (64 - (padding_addr % 64));
			 	S_G_IM_ELA_EXTRACT_NOISE[stage].noiseDataAddr[step] = padding_addr;
			}
		}
		stage++;
	}
}

/**
 * @brief		The ela channel is exclusively controlled.
 * @param[in]	INT32 tmout
 * @return		INT32 D_DDIM_OK/ImEla_D_IM_ELA_SEM_NG/ImEla_D_IM_ELA_INPUT_PARAM_ERROR/ImEla_D_IM_ELA_SEM_TIMEOUT_ERR
 * @note		None
 * @attention	None
 */
INT32 im_ela_reg_open(ImElaReg*self, const INT32 tmout )
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if( tmout < D_DDIM_USER_SEM_WAIT_FEVR ){
		Ddim_Assertion(("im_ela_reg_open() error. input param error. tmout = %x\n", tmout));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if( D_DDIM_USER_SEM_WAIT_POL == tmout ){
		ercd = DDIM_User_Pol_Sem( SID_IM_ELA );							// pol_sem()
	}
	else{
		ercd = DDIM_User_Twai_Sem( SID_IM_ELA, (DDIM_USER_TMO)tmout );	// twai_sem()
	}

	if( D_DDIM_USER_E_TMOUT == ercd ){
		// A semaphore acquisition processing time out
		Ddim_Print(("im_ela_reg_open() error : Semaphore Get Time Out\n"));
		return ImEla_D_IM_ELA_SEM_TIMEOUT_ERR;
	}

	if( D_DDIM_USER_E_OK != ercd ){
		// Ela processing error
		Ddim_Print(("im_ela_reg_open() error : Semaphore Get Error\n"));
		return ImEla_D_IM_ELA_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief 		The exclusive control of control Channel it is released.
 * @param[in]	None
 * @return 		INT32 D_DDIM_OK/ImEla_D_IM_ELA_SEM_NG
 * @note		None
 * @attention	None
 */
INT32 im_ela_reg_close(ImElaReg*self)
{
	DDIM_USER_ER ercd;

	ercd = DDIM_User_Sig_Sem( SID_IM_ELA );				// sig_sem()
	if( D_DDIM_USER_E_OK != ercd ){
		// SPR processing error
		Ddim_Print(("im_ela_reg_close(NULL) Error.\n"));
		return ImEla_D_IM_ELA_SEM_NG;
	}
	return D_DDIM_OK;
}

/**
 * @brief		Get ELA executing count
 * @param[in]	None
 * @return		ELA executing count.(0~4)
 * @note		None
 * @attention	None
 */
UCHAR im_ela_reg_get_exe_cnt(ImElaReg*self)
{
	UCHAR ela_count;

	im_ela_core_on_pclk(NULL);

	ela_count = ( IO_ELA.ELACTL.bit.ELACNT );

	im_ela_core_off_pclk(NULL);

	return ela_count;
}

/**
 * @brief		Get Optical zero level shift parameter
 * @param[in]	None
 * @return		Optical zero level shift parameter.(Two's complement)
 * @note		None
 * @attention	None
 */
USHORT im_ela_reg_get_optical_zero_level_shift(ImElaReg*self)
{
	USHORT Optical_Zero_Level_Shift;

	im_ela_core_on_pclk(NULL);

	ImElaReg_IM_ELA_GET_REG_SIGNED(Optical_Zero_Level_Shift, IO_ELA.EZSFTA1, union io_ela_ezsfta1, EZSFTA1);

	im_ela_core_off_pclk(NULL);

	return Optical_Zero_Level_Shift;
}


/**
 * @brief		Start the operation of ELA's sync
 * @param[in]	None
 * @return		D_DDIM_OK / ImEla_D_IM_ELA_TIMEOUT / ImEla_D_IM_ELA_NG / ImEla_D_IM_ELA_MACRO_BUSY
 * @note		None
 * @attention	None
 */
INT32 im_ela_reg_start_sync(ImElaReg*self)
{
	INT32 ret;

	ret = im_ela_core_start_core(NULL, ImElaReg_D_IM_ELA_SYNC );

	return ret;
}

/**
 * @brief		Start the operation of ELA's async
 * @param[in]	None
 * @return		D_DDIM_OK / ImEla_D_IM_ELA_MACRO_BUSY
 * @note		None
 * @attention	None
 */
INT32 im_ela_reg_start_async(ImElaReg*self)
{
	INT32 ret;

	ret = im_ela_core_start_core(NULL, ImElaReg_D_IM_ELA_ASYNC );

	return ret;
}

/**
 * @brief		Wait that the asynchronization processing ends
 * @param[in]	None
 * @return		D_DDIM_OK / ImEla_D_IM_ELA_TIMEOUT / ImEla_D_IM_ELA_NG
 * @note		When the executed asynchronization processing ends, it is a return.
 * @attention	None
 */
INT32 im_ela_reg_wait_end(ImElaReg*self )
{
	DDIM_USER_FLGPTN flg_ptn;
	DDIM_USER_ER ercd;
	INT32 ret = D_DDIM_OK;

	ercd = DDIM_User_Twai_Flg( FID_IM_ELA, ImElaReg_D_IM_ELA_FLG_ELA, D_DDIM_USER_TWF_ORW, &flg_ptn, ImElaReg_D_IM_ELA_WAIT_END_TIME );
	if( ercd == D_DDIM_USER_E_TMOUT ){
		Ddim_Print(("im_ela_core_start_core() time out. ercd = %d\n", ercd));
		ret = ImEla_D_IM_ELA_TIMEOUT;
	}
	else if( ercd != D_DDIM_USER_E_OK ){
		Ddim_Print(("im_ela_core_start_core() system error. ercd = %d\n", ercd));
		ret = ImEla_D_IM_ELA_NG;
	}
	else{
		(VOID)DDIM_User_Clr_Flg( FID_IM_ELA, ~ImElaReg_D_IM_ELA_FLG_ELA );
	}

	return ret;
}

/**
 * @brief		Cancel the LUT sleep for Deknee.
 * @param[in]	UCHAR dekneeEnable
 * @return		None
 * @note		None
 * @attention	None
 */
VOID im_ela_reg_set_deknee_lut_sleep(ImElaReg*self, UCHAR dekneeEnable )
{
#ifdef CO_PARAM_CHECK
	if( dekneeEnable > ImEla_D_IM_ELA_ENABLE ){
		Ddim_Assertion(("im_ela_reg_set_deknee_lut_sleep() error. input dekneeEnable error : %d\n", dekneeEnable));
		return ;
	}
#endif // CO_PARAM_CHECK

	im_ela_core_on_pclk(NULL);

	if( dekneeEnable == ImEla_D_IM_ELA_ENABLE ){
		IO_ELA.ELABYR.bit.DKNACT = 1;
	}
	else{
		IO_ELA.ELABYR.bit.DKNACT = 0;
	}

	im_ela_core_off_pclk(NULL);
}

/**
 * @brief		Set Deknee table.
 * @param[in]	USHORT* const src_tbl
 * @param[in]	USHORT write_ofs_num
 * @param[in]	USHORT array_num
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR / ImEla_D_IM_ELA_MACRO_BUSY
 * @note		None
 * @attention	None
 */
UINT32 im_ela_reg_set_deknee_tbl(ImElaReg*self, const USHORT* const src_tbl, USHORT write_ofs_num, USHORT array_num )
{
	UINT32 loop_cnt;
	ULONG deknee_tbl[ImEla_D_IM_ELA_DEKNEE_TBL_MAX / 2];

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( src_tbl == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_ELA_Set_Deknee_Tbl error. src_tbl = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
	if( (write_ofs_num + array_num) > ImEla_D_IM_ELA_DEKNEE_TBL_MAX ) {
		// Parameter setting error
		Ddim_Assertion(("I:Im_ELA_Set_Deknee_Tbl error. write_ofs_num + array_num > MAX\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_ela_core_on_pclk(NULL);
	IO_ELA.ELABYR.bit.DKNACT = 1;

	if( IO_ELA.ELATRG.bit.ELATRG == 0x3 ){
		return ImEla_D_IM_ELA_MACRO_BUSY;
	}

	for( loop_cnt = 0; loop_cnt < (ImEla_D_IM_ELA_DEKNEE_TBL_MAX / 2); loop_cnt++ ){
		deknee_tbl[loop_cnt] = IO_ELA.DKNTBL.word[loop_cnt];
	}

	for( loop_cnt = write_ofs_num; loop_cnt < array_num; loop_cnt++ ){
		if( (loop_cnt % 2) == 0 ){
			deknee_tbl[loop_cnt / 2] &= 0xFFFF0000;
			deknee_tbl[loop_cnt / 2] |= src_tbl[loop_cnt];
		}
		else{
			deknee_tbl[loop_cnt / 2] &= 0x0000FFFF;
			deknee_tbl[loop_cnt / 2] |= src_tbl[loop_cnt] << 16;
		}
	}

	for( loop_cnt = 0; loop_cnt < (ImEla_D_IM_ELA_DEKNEE_TBL_MAX / 2); loop_cnt++ ){
		IO_ELA.DKNTBL.word[loop_cnt] = deknee_tbl[loop_cnt];
	}

	IO_ELA.ELABYR.bit.DKNACT = 0;
	im_ela_core_off_pclk(NULL);

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
/**
 * @brief		Set curtail bayer data table
 * @param[in]	curtail_bayer[ImElaReg_D_IM_ELA_STAGE_MAX]	Pointer of Table data (Type of TImElaCurtailBayerData)
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_reg_set_curtail_bayer_data_tbl(ImElaReg*self, const TImElaCurtailBayerData curtail_bayer[ImElaReg_D_IM_ELA_STAGE_MAX] )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( curtail_bayer == NULL ){
		Ddim_Assertion(("im_ela_reg_set_curtail_bayer_data_tbl() error. curtail_bayer = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	memcpy( &S_G_IM_ELA_CURTAIL_BAYER, curtail_bayer, (sizeof(TImElaCurtailBayerData) * ImElaReg_D_IM_ELA_STAGE_MAX) );
	return D_DDIM_OK;
}

/**
 * @brief		Get curtail bayer data table
 * @param[out]	curtail_bayer[ImElaReg_D_IM_ELA_STAGE_MAX]	Pointer of Table data (Type of TImElaCurtailBayerData)
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_reg_get_curtail_bayer_data_tbl(ImElaReg*self, TImElaCurtailBayerData curtail_bayer[ImElaReg_D_IM_ELA_STAGE_MAX] )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( curtail_bayer == NULL ){
		Ddim_Assertion(("im_ela_reg_get_curtail_bayer_data_tbl() error. curtail_bayer = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	memcpy( curtail_bayer, &S_G_IM_ELA_CURTAIL_BAYER, (sizeof(TImElaCurtailBayerData) * ImElaReg_D_IM_ELA_STAGE_MAX) );
	return D_DDIM_OK;
}

/**
 * @brief		Set extraction noise data table
 * @param[in]	extract_noise[ImElaReg_D_IM_ELA_STAGE_MAX]	Pointer of Table data (Type of TImElaExtractNoiseData)
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_reg_set_extract_noise_data_tbl(ImElaReg*self, const TImElaExtractNoiseData extract_noise[ImElaReg_D_IM_ELA_STAGE_MAX] )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( extract_noise == NULL ){
		Ddim_Assertion(("im_ela_reg_set_extract_noise_data_tbl() error. extract_noise = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	memcpy( &S_G_IM_ELA_EXTRACT_NOISE, extract_noise, (sizeof(TImElaExtractNoiseData) * ImElaReg_D_IM_ELA_STAGE_MAX) );
	return D_DDIM_OK;
}

/**
 * @brief		Get extraction noise data table
 * @param[out]	extract_noise[ImElaReg_D_IM_ELA_STAGE_MAX]	Pointer of Table data (Type of TImElaExtractNoiseData)
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_INPUT_PARAM_ERROR
 * @note		None
 * @attention	None
 */
UINT32 im_ela_reg_get_extract_noise_data_tbl(ImElaReg*self, TImElaExtractNoiseData extract_noise[ImElaReg_D_IM_ELA_STAGE_MAX] )
{
#ifdef CO_PARAM_CHECK
	/* check on input pointer */
	if( extract_noise == NULL ){
		Ddim_Assertion(("im_ela_reg_get_extract_noise_data_tbl() error. extract_noise = NULL\n"));
		return ImEla_D_IM_ELA_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	memcpy( extract_noise, &S_G_IM_ELA_EXTRACT_NOISE, (sizeof(TImElaExtractNoiseData) * ImElaReg_D_IM_ELA_STAGE_MAX) );
	return D_DDIM_OK;
}

//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

ImElaReg *im_ela_reg_new(void)
{
	ImElaReg* self = k_object_new_with_private(IM_TYPE_ELA_REG,sizeof(ImElaRegPrivate));
	return self;
}
