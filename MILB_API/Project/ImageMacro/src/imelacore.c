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
#include "imelacore.h"
#include "imelareg.h"
#include "imela.h"
#include "jdsela.h"
#include "dd_arm.h"
#include "ddim_user_custom.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImElaCore, im_ela_core)
#define IM_ELA_CORE_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImElaCorePrivate,IM_TYPE_ELA_CORE))

struct _ImElaCorePrivate
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
volatile ULONG									S_G_IM_ELA_AXI_ERR = ImEla_D_IM_ELA_NORMAL_END;

#ifdef CO_ACT_ICLOCK
// ELACLK setting task counter (0~255)
volatile UCHAR S_G_IM_ELA_CLK_COUNTER	= 0;
// ICLK_ELA setting task counter (0~255)
volatile UCHAR S_G_IM_ELA_ICLK_COUNTER	= 0;
#endif //CO_ACT_ICLOCK
#ifdef CO_ACT_PCLOCK
// PCLK_ELA setting task counter (0~255)
volatile UCHAR S_G_IM_ELA_PCLK_COUNTER	= 0;
#endif //CO_ACT_PCLOCK

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
static VOID imElaOnIclk( VOID );
static VOID imElaOffIclk( VOID );
static VOID imElaOnClk( VOID );
static VOID imElaOffClk( VOID );
static INT32 imElaStartNext( VOID );

#ifdef CO_ELA_DEBUG_PRINT	// Debug
static VOID imElaQelatmdInfoPrint( VOID );
static VOID imElaCtrlRegPrint( VOID );
#endif

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

static void im_ela_core_constructor(ImElaCore *self)
{
//	ImElaCorePrivate *priv = IM_ELA_CORE_GET_PRIVATE(self);
}

static void im_ela_core_destructor(ImElaCore *self)
{
//	ImElaCorePrivate *priv = IM_ELA_CORE_GET_PRIVATE(self);
}

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
/**
 * @brief		ELA ICLK change to ON
 * @param[in]   None
 * @param[out]  None
 * @return		None
 * @note		None
 */
static VOID imElaOnIclk( VOID )
{
#ifdef CO_ACT_ICLOCK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_ELA_ICLK_COUNTER, &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_ELAAX_BIT );
#endif	// CO_ACT_ICLOCK
}

/**
 * @brief		ELA ICLK change to OFF
 * @param[in]   None
 * @param[out]  None
 * @return		None
 * @note		None
 */
static VOID imElaOffIclk( VOID )
{
#ifdef CO_ACT_ICLOCK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_ELA_ICLK_COUNTER, &Dd_Top_Get_CLKSTOP6(), D_DD_TOP_ELAAX_BIT );
#endif	// CO_ACT_ICLOCK
}

/**
 * @brief		ELA CLK change to ON
 * @param[in]   None
 * @param[out]  None
 * @return		None
 * @note		None
 */
static VOID imElaOnClk( VOID )
{
#ifdef CO_ACT_CLOCK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_ELA_CLK_COUNTER, &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_ELACK_BIT );
#endif	// CO_ACT_CLOCK
}

/**
 * @brief		ELA CLK change to OFF
 * @param[in]   None
 * @param[out]  None
 * @return		None
 * @note		None
 */
static VOID imElaOffClk( VOID )
{
#ifdef CO_ACT_CLOCK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_ELA_CLK_COUNTER, &Dd_Top_Get_CLKSTOP6(), D_DD_TOP_ELACK_BIT );
#endif	// CO_ACT_CLOCK
}

//---------------------------- driver section ----------------------------
/**
 * @brief		Start the next operaion of ELA
 * @param[in]	None
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_PROCESS_END
 * @note		None
 * @attention	None
 */
static INT32 imElaStartNext( VOID )
{
	static UCHAR stop_wait_cnt;
	ImEla *imEla  =  im_ela_get();
//	UCHAR *gImElaStageCnt = im_ela_get_g_im_ela_stage_cnt(imEla);
//	UCHAR *gImElaStepCnt = im_ela_get_g_im_ela_step_cnt(imEla);
//	UCHAR *gImElaNextCtrlFlag = im_ela_get_g_im_ela_next_ctrl_flag(imEla);
	TImElaQelatmd *gImElaQelatmdInfo = im_ela_get_g_im_ela_qelatmd_info(imEla);

	if( S_G_IM_ELA_AXI_ERR != ImEla_D_IM_ELA_NORMAL_END ){
		if( IO_ELA.ELATRG.bit.ELATRG == 0x3 ){
			/* ELA stop */
			IO_ELA.ELATRG.bit.ELATRG = 0;
		}
		Ddim_Print(("imElaStartNext() AXI error. ercd = %lu\n", S_G_IM_ELA_AXI_ERR));
		Ddim_Print(("RRESP[0] = %d\n", IO_ELA.EARAXSTS.bit.RRESP_0));
		Ddim_Print(("RRESP[1] = %d\n", IO_ELA.EARAXSTS.bit.RRESP_1));
		Ddim_Print(("RRESP[2] = %d\n", IO_ELA.EARAXSTS.bit.RRESP_2));
		Ddim_Print(("BRESP[0] = %d\n", IO_ELA.EAWAXSTS.bit.BRESP_0));
		Ddim_Print(("BRESP[1] = %d\n", IO_ELA.EAWAXSTS.bit.BRESP_1));
		Ddim_Print(("BRESP[2] = %d\n", IO_ELA.EAWAXSTS.bit.BRESP_2));

		return ImEla_D_IM_ELA_PROCESS_END;
	}
	else{
		stop_wait_cnt = 0;
		while( IO_ELA.ELATRG.bit.ELATRG == 3 ){
			DDIM_User_Dly_Tsk( 1 );

			stop_wait_cnt++;

			if( stop_wait_cnt > 100 ){
				Ddim_Print(("imElaStartNext() Time Out Error. ELATRG = %d\n", IO_ELA.ELATRG.bit.ELATRG ));
				return ImEla_D_IM_ELA_PROCESS_END;
			}
		}

		if( gImElaQelatmdInfo->elaElfLevel != ImEla_E_IM_ELA_ELF_LEVEL_1 ){
			if( imEla->gImElaStageCnt == 0 ){
				imEla->gImElaStageCnt++;
				imEla->gImElaStepCnt = 0;
			}
			else{
				if( imEla->gImElaStepCnt != ImElaReg_D_IM_ELA_STEP_S ){
					if( gImElaQelatmdInfo->elaDensityMode[ImElaReg_IM_ELA_CONV_STAGE_TO_LEVEL(imEla->gImElaStageCnt)] == ImEla_E_IM_ELA_DENSITY_MODE_2 ){
						if( imEla->gImElaStepCnt < 3 ){
							imEla->gImElaStepCnt++;
						}
						else if( imEla->gImElaStepCnt == 3 ){
							imEla->gImElaStepCnt = ImElaReg_D_IM_ELA_STEP_S;
						}
						else{
							imEla->gImElaStageCnt++;
							imEla->gImElaStepCnt = 0;
						}
					}
					else if( gImElaQelatmdInfo->elaDensityMode[ImElaReg_IM_ELA_CONV_STAGE_TO_LEVEL(imEla->gImElaStageCnt)] == ImEla_E_IM_ELA_DENSITY_MODE_3 ){
						if( imEla->gImElaStepCnt < 15 ){
							imEla->gImElaStepCnt++;
						}
						else if( imEla->gImElaStepCnt == 15 ){
							imEla->gImElaStepCnt = ImElaReg_D_IM_ELA_STEP_S;
						}
						else{
							imEla->gImElaStageCnt++;
							imEla->gImElaStepCnt = 0;
						}
					}
					else{
						imEla->gImElaStepCnt = ImElaReg_D_IM_ELA_STEP_S;
					}
				}
				else{
					imEla->gImElaStageCnt++;
					imEla->gImElaStepCnt = 0;
				}
			}
#ifdef CO_ELA_DEBUG_PRINT	// Debug
			Ddim_Print(("imElaStartNext() : Next Stage = %d, Next Step = %d\n", imEla->gImElaStageCnt, imEla->gImElaStepCnt));
#endif

			if( (ImElaReg_IM_ELA_CONV_STAGE_TO_LEVEL(imEla->gImElaStageCnt) > gImElaQelatmdInfo->elaElfLevel) ||
			   ((imEla->gImElaStepCnt == 0) && (imEla->gImElaNextCtrlFlag == ImEla_D_IM_ELA_ENABLE)) ){
				return ImEla_D_IM_ELA_PROCESS_END;
			}
			else{
				/* Common register & EIIch register & ENIch/ENOch register setting */
				im_ela_reg_ctrl_next_register(NULL);

#ifdef CO_ELA_DEBUG_PRINT	// Debug
				Ddim_Print(("imElaStartNext() : Start the next process\n"));
				imElaCtrlRegPrint();
#endif
				/* ELA start */
				IO_ELA.ELATRG.bit.ELATRG = 1;
			}
		}
		else{
#ifdef CO_ELA_DEBUG_PRINT	// Debug
			Ddim_Print(("imElaStartNext(): Process End.(ImEla_E_IM_ELA_ELF_LEVEL_1)\n"));
#endif
			return ImEla_D_IM_ELA_PROCESS_END;
		}
	}

	return D_DDIM_OK;
}

#ifdef CO_ELA_DEBUG_PRINT	// Debug
static VOID imElaQelatmdInfoPrint( VOID )
{
	UINT32 i;
	ImEla *imEla  =  im_ela_get();
	TImElaQelatmd *gImElaQelatmdInfo = im_ela_get_g_im_ela_qelatmd_info(imEla);

	Ddim_Print(("<Im_ELA Qelatmd Info>\n"));
	Ddim_Print(("\t elaElfLevel = %d\n", gImElaQelatmdInfo->elaElfLevel));
	for( i = 0; i < ImEla_E_IM_ELA_ELF_LEVEL_MAX; i++ ){
		Ddim_Print(("\t elaDensityMode[%d] = %d\n", i, gImElaQelatmdInfo->elaDensityMode[i]));
	}
}

static VOID imElaCtrlRegPrint( VOID )
{
	UINT32 i;

#if 1
	Ddim_Print(( "(Core Reg)\n" ));
	Ddim_Print(( "\tELACNT = %d\n",			IO_ELA.ELACTL.bit.ELACNT ));
	Ddim_Print(( "\tELAACT = %d\n",			IO_ELA.ELACTL.bit.ELAACT ));
	Ddim_Print(( "\tELAMD  = %d\n",			IO_ELA.ELACTL.bit.ELAMD ));
	Ddim_Print(( "\tEIRTYP = %d\n",			IO_ELA.ELABYR.bit.EIRTYP ));
	Ddim_Print(( "\tEIRSFT = %d\n",			IO_ELA.ELABYR.bit.EIRSFT ));
	Ddim_Print(( "\tEIWTYP = %d\n",			IO_ELA.ELABYR.bit.EIWTYP ));
	Ddim_Print(( "\tEIWSFT = %d\n",			IO_ELA.ELABYR.bit.EIWSFT ));
	Ddim_Print(( "\tEIWOUT = %d\n",			IO_ELA.ELABYR.bit.EIWOUT ));
	Ddim_Print(( "\tNSLMD  = %d\n",			IO_ELA.NSLMD.bit.NSLMD ));

	Ddim_Print(( "(EIRch Reg)\n" ));
	Ddim_Print(( "\tEIRA    = 0x%08lx\n",	IO_ELA.EIRA.word ));
	Ddim_Print(( "\tEIROFS  = %d\n",		IO_ELA.EIROFS.bit.EIROFS ));
	Ddim_Print(( "\tEIRDEF  = %d\n",		IO_ELA.EIRDEF.bit.EIRDEF ));
	Ddim_Print(( "\tEIRHSIZ = %d\n",		IO_ELA.EIRHSIZ.bit.EIRHSIZ ));
	Ddim_Print(( "\tEIRVSIZ = %d\n",		IO_ELA.EIRVSIZ.bit.EIRVSIZ ));

	Ddim_Print(( "(EIWch Reg)\n" ));
	for( i = 0; i < 4; i++ ){
		Ddim_Print(( "\tEIWA[%d] = 0x%08lx\n",	i, IO_ELA.EIWA.word[i] ));
	}
	Ddim_Print(( "\tEIWDEF  = %d\n",		IO_ELA.EIWDEF.bit.EIWDEF ));

	Ddim_Print(( "(ENWch Reg)\n" ));
	Ddim_Print(( "\tENWA   = 0x%08lx\n",	IO_ELA.ENWA.word ));
	Ddim_Print(( "\tENWDEF = %d\n",			IO_ELA.ENWDEF.bit.ENWDEF ));

	Ddim_Print(( "(ENREch Reg)\n" ));
	for( i = 0; i < 16; i++ ){
		Ddim_Print(( "\tENRA[%d] = 0x%08lx\n",	i, IO_ELA.ENRA.word[i] ));
	}
	Ddim_Print(( "\tENRHSIZ  = %d\n",		IO_ELA.ENRHSIZ.bit.ENRHSIZ ));
	Ddim_Print(( "\tENRVSIZ  = %d\n",		IO_ELA.ENRVSIZ.bit.ENRVSIZ ));

	Ddim_Print(( "(ENRAch/ENWMch Reg)\n" ));
	Ddim_Print(( "\tENSA    = 0x%08lx\n",	IO_ELA.ENSA.word ));
	Ddim_Print(( "\tENSDEF  = %d\n",		IO_ELA.ENSDEF.bit.ENSDEF ));
	Ddim_Print(( "\tENSHSIZ = %d\n",		IO_ELA.ENSHSIZ.bit.ENSHSIZ ));
	Ddim_Print(( "\tENSVSIZ = %d\n",		IO_ELA.ENSVSIZ.bit.ENSVSIZ ));
#else
	Ddim_Print(( "\tELATRG = 0x%02x\n",		IO_ELA.ELATRG.bit.ELATRG ));

	Ddim_Print(( "\tELACTL = 0x%08lx\n",	IO_ELA.ELACTL.word ));

	Ddim_Print(( "\tELABYR = 0x%08lx\n",	IO_ELA.ELABYR.word ));

	Ddim_Print(( "\tNSLMD = 0x%08lx\n",		IO_ELA.NSLMD.word ));

	Ddim_Print(( "\tOBOF = 0x%016llx\n",	IO_ELA.OBOF.dword ));

	Ddim_Print(( "\tEZSFTA1 = 0x%04x\n",	IO_ELA.EZSFTA1.bit.EZSFTA1 ));

	Ddim_Print(( "\tNSLNGLMT = 0x%08lx\n",	IO_ELA.NSLNGLMT.word ));

	Ddim_Print(( "\tEIRA = 0x%08lx\n",		IO_ELA.EIRA.word ));
	Ddim_Print(( "\tEIROFS = 0x%02x\n",		IO_ELA.EIROFS.bit.EIROFS ));
	Ddim_Print(( "\tEIRDEF = 0x%04x\n",		IO_ELA.EIRDEF.bit.EIRDEF ));
	Ddim_Print(( "\tEIRHSIZ = 0x%04x\n",	IO_ELA.EIRHSIZ.bit.EIRHSIZ ));
	Ddim_Print(( "\tEIRVSIZ = 0x%04x\n",	IO_ELA.EIRVSIZ.bit.EIRVSIZ ));

	for( i = 0; i < 4; i++ ){
		Ddim_Print(( "\tEIWA[%d] = 0x%08lx\n",	i, IO_ELA.EIWA.word[i] ));
	}
	Ddim_Print(( "\tEIWDEF = 0x%04x\n",		IO_ELA.EIWDEF.bit.EIWDEF ));

	Ddim_Print(( "\tENWA = 0x%08lx\n",		IO_ELA.ENWA.word ));
	Ddim_Print(( "\tENWDEF = 0x%04x\n",		IO_ELA.ENWDEF.bit.ENWDEF ));

	for( i = 0; i < 16; i++ ){
		Ddim_Print(( "\tENRA[%d] = 0x%08lx\n",	i, IO_ELA.ENRA.word[i] ));
	}
	Ddim_Print(( "\tENRHSIZ = 0x%04x\n",	IO_ELA.ENRHSIZ.bit.ENRHSIZ ));
	Ddim_Print(( "\tENRVSIZ = 0x%04x\n",	IO_ELA.ENRVSIZ.bit.ENRVSIZ ));

	Ddim_Print(( "\tENSA = 0x%08lx\n",		IO_ELA.ENSA.word ));
	Ddim_Print(( "\tENSDEF = 0x%04x\n",		IO_ELA.ENSDEF.bit.ENSDEF ));
	Ddim_Print(( "\tENSHSIZ = 0x%04x\n",	IO_ELA.ENSHSIZ.bit.ENSHSIZ ));
	Ddim_Print(( "\tENSVSIZ = 0x%04x\n",	IO_ELA.ENSVSIZ.bit.ENSVSIZ ));
#endif
}

#endif

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
 * @brief		Start the operaion of ELA
 * @param[in]	ImElaReg_D_IM_ELA_SYNC, ImElaReg_D_IM_ELA_ASYNC
 * @return		INT32 D_DDIM_OK / ImEla_D_IM_ELA_TIMEOUT / ImEla_D_IM_ELA_NG / ImEla_D_IM_ELA_MACRO_BUSY
 * @note		None
 * @attention	None
 */
INT32 im_ela_core_start_core(ImElaCore*self, UINT32 sync )
{
	DDIM_USER_FLGPTN flg_ptn;
	DDIM_USER_ER ercd;
	INT32 ret = D_DDIM_OK;

	im_ela_core_on_pclk(NULL);

	if( IO_ELA.ELATRG.bit.ELATRG == 0x3 ){
		Ddim_Print(("im_ela_core_start_core() macro busy.\n"));

		im_ela_core_off_pclk(NULL);

		return ImEla_D_IM_ELA_MACRO_BUSY;
	}

	ercd = DDIM_User_Clr_Flg( FID_IM_ELA, ~ImElaReg_D_IM_ELA_FLG_ELA );
	if( ercd != D_DDIM_USER_E_OK ){
		Ddim_Print(("im_ela_core_start_core() system error. ercd = %d\n", ercd));

		im_ela_core_off_pclk(NULL);

		return ImEla_D_IM_ELA_NG;
	}

	imElaOnIclk();
	imElaOnClk();

	// Enable SRAM ACCESS
	IO_ELA.SRAMACT.bit.SRAMACT = 1;

	ImElaReg_IM_ELA_WAIT_USEC1( ImElaReg_D_IM_ELA_SRAM_WAIT_USEC );

	IO_ELA.ELATRG.bit.ELATRG = 1;

#ifdef CO_ELA_DEBUG_PRINT	// Debug
	imElaCtrlRegPrint();
#endif

	if( sync == ImElaReg_D_IM_ELA_SYNC ){
		/* ELA wait end */
		do{
			ercd = DDIM_User_Twai_Flg( FID_IM_ELA, ImElaReg_D_IM_ELA_FLG_ELA, D_DDIM_USER_TWF_ORW, &flg_ptn, ImElaReg_D_IM_ELA_WAIT_END_TIME );
			if( ercd == D_DDIM_USER_E_TMOUT ){
				Ddim_Print(("im_ela_core_start_core() time out. ercd = %d\n", ercd));
				ret = ImEla_D_IM_ELA_TIMEOUT;
				break;
			}
			else if( ercd != D_DDIM_USER_E_OK ){
				Ddim_Print(("im_ela_core_start_core() system error. ercd = %d\n", ercd));
				ret = ImEla_D_IM_ELA_NG;
				break;
			}
			else{
				(VOID)DDIM_User_Clr_Flg( FID_IM_ELA, ~ImElaReg_D_IM_ELA_FLG_ELA );
			}
		}
		while( imElaStartNext() != ImEla_D_IM_ELA_PROCESS_END );

#ifdef CO_ELA_DEBUG_PRINT	// Debug
		Ddim_Print(("im_ela_core_start_core() Normal End. ercd = %d\n", ercd));
#endif

		if( IO_ELA.ELATRG.bit.ELATRG == 0x3 ){
			/* ELA stop */
			IO_ELA.ELATRG.bit.ELATRG = 0;
		}

		// Disable SRAM ACCESS
		IO_ELA.SRAMACT.bit.SRAMACT = 0;

		im_ela_core_off_pclk(NULL);
		imElaOffIclk();
		imElaOffClk();
	}
	else{	// sync == ImElaReg_D_IM_ELA_ASYNC
		im_ela_core_off_pclk(NULL);
	}

	return ret;
}

/**
 * @brief		ELA PCLK change to ON
 * @param[in]   None
 * @param[out]  None
 * @return		None
 * @note		None
 */
VOID im_ela_core_on_pclk(ImElaCore*self)
{
#ifdef CO_ACT_PCLOCK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_ELA_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_ELAAP_BIT );
#endif	// CO_ACT_PCLOCK
}

/**
 * @brief		ELA PCLK change to OFF
 * @param[in]   None
 * @param[out]  None
 * @return		None
 * @note		None
 */
VOID im_ela_core_off_pclk(ImElaCore*self)
{
#ifdef CO_ACT_PCLOCK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_ELA_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP6(), D_DD_TOP_ELAAP_BIT );
#endif	// CO_ACT_PCLOCK
}

/**
 * @brief		The register is set for the ELA macro processing since the second times.
 * @param[in]	None
 * @return		INT32 D_DDIM_OK
 * @note		None
 * @attention	None
 */
UINT32 im_ela_core_ctrl_next(ImElaCore*self)
{
	im_ela_core_on_pclk(NULL);

	/* Common register & EIIch register & ENIch/ENOch register setting */
	im_ela_reg_ctrl_next_register(NULL);

	im_ela_core_off_pclk(NULL);
	ImElaReg_IM_ELA_DSB();

	return D_DDIM_OK;
}

/**
 * @brief		ELA Initialize
 * @param[in]	None
 * @return		None
 * @note		None
 * @attention	None
 */
VOID im_ela_core_init(ImElaCore*self )
{
	union io_ela_elaintf elaintf;

	S_G_IM_ELA_AXI_ERR = ImEla_D_IM_ELA_NORMAL_END;

	im_ela_core_on_pclk(NULL);

	/* Interrupt setting */
	IO_ELA.ELAINTE.bit.ENWE = 1;		// int enable
	IO_ELA.ELAINTE.bit.AXRERE = 1;		// int enable
	IO_ELA.ELAINTE.bit.AXWERE = 1;		// int enable

	// flag clear
	elaintf.word = 0;
	elaintf.bit.__ENWF = 1;
	elaintf.bit.__AXRERF = 1;
	elaintf.bit.__AXWERF = 1;

	IO_ELA.ELAINTF.word = elaintf.word;

	im_ela_core_off_pclk(NULL);
}

/**
 * @brief		The processing of ELA stop
 * @param		None
 * @return		None
 * @note		None
 * @attention	None
 */
VOID im_ela_core_stop(ImElaCore*self )
{
	DDIM_USER_ER ercd;

	im_ela_core_on_pclk(NULL);

	/* ELA stop */
	if( IO_ELA.ELATRG.bit.ELATRG == 0x3 ){
		/* ELA stop */
		IO_ELA.ELATRG.bit.ELATRG = 0;
	}

	// Disable SRAM ACCESS
	IO_ELA.SRAMACT.bit.SRAMACT = 0;

	im_ela_core_off_pclk(NULL);
	imElaOffIclk();
	imElaOffClk();

	ercd = DDIM_User_Clr_Flg( FID_IM_ELA, ~ImElaReg_D_IM_ELA_FLG_ELA );
	if( ercd != D_DDIM_USER_E_OK ){
		Ddim_Print(("im_ela_core_stop(NULL) system error. ercd = %d\n", ercd));
	}
}

/**
 * @brief		It is an interrupt handler that starts when the processing of ELA ends
 * @param		None
 * @return		None
 * @note		None
 * @attention	None
 */
VOID im_ela_core_int_handler( VOID )
{
	union io_ela_elainte elainte;
	union io_ela_elaintf elaintf;
	ImEla *imEla  =  im_ela_get();
//	UCHAR *gImElaStageCnt = im_ela_get_g_im_ela_stage_cnt(imEla);
//	UCHAR *gImElaStepCnt = im_ela_get_g_im_ela_step_cnt(imEla);
//	UCHAR *gImElaNextCtrlFlag = im_ela_get_g_im_ela_next_ctrl_flag(imEla);
//	TImElaCallback *gImElaCallbackFunc = im_ela_get_g_im_ela_callback_func(imEla);

	S_G_IM_ELA_AXI_ERR = ImEla_D_IM_ELA_NORMAL_END;

	im_ela_core_on_pclk(NULL);
	ImElaReg_IM_ELA_DSB();

#ifdef CO_ELA_DEBUG_PRINT	// Debug
	Ddim_Print(("im_ela_core_int_handler() : Stage=%d, Step=%d\n", imEla->gImElaStageCnt, imEla->gImElaStepCnt));
	Ddim_Print(("im_ela_core_int_handler() : imEla->gImElaNextCtrlFlag = %d\n", imEla->gImElaNextCtrlFlag));
	Ddim_Print(( "\tELACNT = %d\n",			IO_ELA.ELACTL.bit.ELACNT ));
	Ddim_Print(( "\tELAMD  = %d\n",			IO_ELA.ELACTL.bit.ELAMD ));
	Ddim_Print(( "\tELAACT = %d\n",			IO_ELA.ELACTL.bit.ELAACT ));
	Ddim_Print(( "\tEIWOUT = %d\n",			IO_ELA.ELABYR.bit.EIWOUT ));
	Ddim_Print(( "\tEIRA    = 0x%08lx\n",	IO_ELA.EIRA.word ));
	{
		UINT32 i;
		for( i = 0; i < 4; i++ ){
			Ddim_Print(( "\tEIWA[%d] = 0x%08lx\n",	i, IO_ELA.EIWA.word[i] ));
		}
		Ddim_Print(( "\tENWA   = 0x%08lx\n",		IO_ELA.ENWA.word ));
		for( i = 0; i < 16; i++ ){
			Ddim_Print(( "\tENRA[%d] = 0x%08lx\n",	i, IO_ELA.ENRA.word[i] ));
		}
	}
	Ddim_Print(( "\tENSA    = 0x%08lx\n",			IO_ELA.ENSA.word ));

	imElaQelatmdInfoPrint();
#endif
	elainte.word = IO_ELA.ELAINTE.word;
	elaintf.word = IO_ELA.ELAINTF.word;

	/* interrupt AXI Write Ch */
	if( (elainte.bit.AXWERE == 1) && (elaintf.bit.__AXWERF == 1) ){		/* pgr0872 */
		IO_ELA.ELAINTF.word = ImElaReg_D_IM_ELA_ELAINTF_AXWERF;	// flag clear
		S_G_IM_ELA_AXI_ERR |= ImEla_D_IM_ELA_AXI_ERR_CH_W;
	}

	/* interrupt AXI Read Ch */
	if( (elainte.bit.AXRERE == 1) && (elaintf.bit.__AXRERF == 1) ){		/* pgr0872 */
		IO_ELA.ELAINTF.word = ImElaReg_D_IM_ELA_ELAINTF_AXRERF;	// flag clear
		S_G_IM_ELA_AXI_ERR |= ImEla_D_IM_ELA_AXI_ERR_CH_R;
	}

	/* interrupt Process completed */
	if( (elainte.bit.ENWE == 1) && (elaintf.bit.__ENWF == 1) ){			/* pgr0872 */
		IO_ELA.ELAINTF.word = ImElaReg_D_IM_ELA_ELAINTF_ENWF;	// flag clear
	}

	(VOID)DDIM_User_Set_Flg( FID_IM_ELA, ImElaReg_D_IM_ELA_FLG_ELA );

	// User Function Check
	if( imEla->gImElaCallbackFunc != NULL ){
		imEla->gImElaCallbackFunc( S_G_IM_ELA_AXI_ERR );
	}

	im_ela_core_off_pclk(NULL);
	ImElaReg_IM_ELA_DSB();
}

ImElaCore *im_ela_core_new(void)
{
	ImElaCore* self = k_object_new_with_private(IM_TYPE_ELA_CORE,sizeof(ImElaCorePrivate));
	return self;
}
