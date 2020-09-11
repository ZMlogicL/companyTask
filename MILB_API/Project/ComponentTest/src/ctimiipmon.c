/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipMon类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_im_iip_mon.c
 * @brief		IIP MON unit ct code
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

// CT header
#include "ct_im_iip.h"
#include "ct_im_iip_mon.h"

// im_iip header
#include "im_iip.h"

// MILB register header
#include "jdsiip.h"

// for Memory barrier
#include "ddarm.h"

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#include "palladium_test_common.h"
#endif
// ### REMOVE_RELEASE END

// for memset
#include <string.h>
#include "ctimiipmon.h"
#include "imiipunitparameter.h"

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif
#endif

K_TYPE_DEFINE_WITH_PRIVATE(CtImIipMon, ct_im_iip_mon);
#define CT_IM_IIP_MON_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImIipMonPrivate,CT_TYPE_IM_IIP_MON))

struct _CtImIipMonPrivate {
    CtImIipMon *					ciIipMom;
	kint32							ercd;
	T_IM_IIP_PIXFMTTBL				pixfmtTbl0;		// 1DL Unit input
	T_IM_IIP_PIXFMTTBL				pixfmtTbl1;		// SL Unit output
	T_IM_IIP_UNIT_CFG				onedCfg;
	T_IM_IIP_PARAM_1DL*				onedUnitInf;
	T_IM_IIP_PARAM_STS*				slUnitInf;
	T_IM_IIP_UNIT_CFG				slCfg;
	T_IM_IIP_PARAM_MON*				monUnitInf;
	T_IM_IIP_UNIT_CFG				monCfg;
	kuint32							waitFactorResult;
};

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#undef Ddim_Print
#define CtImIipMon_DDIM_PRINT(arg)		{DDIM_User_Printf arg;}		/**< printf function inside DDIM */
#endif

static void ct_im_iip_mon_constructor(CtImIipMon *self) 
{
	CtImIipMonPrivate *priv = CT_IM_IIP_MON_GET_PRIVATE(self);
	priv->ciIipMom = ct_im_iip_mon_new();
	priv->onedUnitInf = &g_ct_im_iip_unit_param_1dl0;
	priv->slUnitInf = &g_ct_im_iip_unit_param_sl0;
	priv->monUnitInf = &g_ct_im_iip_unit_param_mon;
	priv->waitFactorResult = 0;
}

static void ct_im_iip_mon_destructor(CtImIipMon *self)
{
	CtImIipMonPrivate *priv = CT_IM_IIP_MON_GET_PRIVATE(self);
	if(priv->ciIipMom){
		k_object_unref(priv->ciIipMom);
	}
	priv->ciIipMom = NULL;
}

/*PUBLIC*/

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special


/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// Nothing Special


/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
// Nothing Special


/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/

// MON Unit 11-1-1 YUV422 VGA-> YUV422 VGA
#undef D_IM_IIP_FUNC_NAME
#define CtImIipMon_D_IM_IIP_FUNC_NAME "ct_im_iip_mon_11_1_1: "
kint32 ct_im_iip_mon_11_1_1(CtImIipMon *self)
{
	CtImIipMonPrivate *priv = CT_IM_IIP_MON_GET_PRIVATE(self);

	const kuint32					waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL4END;
	const kuint32					unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_SL4 
                                        | D_IM_IIP_PARAM_PLDUNIT_MON;
	const kuint32					pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID			srcUnitid = E_IM_IIP_UNIT_ID_LD1;
	const E_IM_IIP_UNIT_ID			dstUnitid = E_IM_IIP_UNIT_ID_SL4;
	const E_IM_IIP_UNIT_ID			mon_unitid = E_IM_IIP_UNIT_ID_MON;
	const E_IM_IIP_PARAM_PORTID		srcPortid = E_IM_IIP_PARAM_PORTID_LD1;
	const E_IM_IIP_PARAM_PORTID		dstPortid = E_IM_IIP_PARAM_PORTID_SL4;
	const kuint32					srcPixid = 4;
	const kuint32					dstPixid = 5;
	const kuint32					openResBitmask = E_IM_IIP_OPEN_RES_CACHE0 | E_IM_IIP_OPEN_RES_HIST_0 
                                        | E_IM_IIP_OPEN_RES_HIST_1 | E_IM_IIP_OPEN_RES_HIST_2;
	T_IM_IIP_MAXMON					maxmon;
	T_IM_IIP_MINMON					minmon;
	T_IM_IIP_ADDMON					addmon;
	kuint32							loopcnt;
#ifndef CO_CT_IM_IIP_11_1_2_DISABLE_HIST
	static kulong					bufferHistgram[D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)];
	UCHAR							histmax;
#endif


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = Im_IIP_Open_SWTRG(unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));
	if(priv->ercd != D_IM_IIP_OK) {
		return priv->ercd;
	}

	priv->pixfmtTbl0 = g_ct_im_iip_pixfmttbl_base;
	priv->pixfmtTbl0.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl0.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;	// Input Y frame.
	priv->pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	priv->pixfmtTbl0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;	// Input Y frame.
	priv->pixfmtTbl0.alpha = D_IM_IIP_ALPHA_TRUE;

	priv->pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	priv->pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	priv->pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	priv->pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL)));

	memset(priv->onedUnitInf, '\0', sizeof(*priv->onedUnitInf));
	*priv->onedUnitInf = g_ct_im_iip_param_1dl_base;
	priv->onedUnitInf->LD_TOPCNF0.bit.WAITCONF = dstPortid;
	priv->onedUnitInf->PIXIDDEF.bit.IPIXID = srcPixid;

	priv->onedCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->onedCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->onedCfg.unit_param_addr = (kulong)priv->onedUnitInf;
	priv->onedCfg.load_unit_param_flag = 0;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->slUnitInf, sizeof(T_IM_IIP_PARAM_STS)));

	memset(priv->slUnitInf, '\0', sizeof(*priv->slUnitInf));
	*priv->slUnitInf = g_ct_im_iip_param_sts_base;
	priv->slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid;
	priv->slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;


	priv->slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->slCfg.unit_param_addr = (kulong)priv->slUnitInf;
	priv->slCfg.load_unit_param_flag = unitidBitmask;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "monUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->monUnitInf, sizeof(T_IM_IIP_PARAM_MON)));

	memset(priv->monUnitInf, '\0', sizeof(*priv->monUnitInf));
	*priv->monUnitInf = g_ct_im_iip_param_mon_base;
	priv->monUnitInf->MONDSEL.bit.DSEL = E_IM_IIP_PARAM_DSEL_SL4;
	priv->monUnitInf->HISTCTL[0].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0;
	priv->monUnitInf->HISTCTL[1].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0;
	priv->monUnitInf->HISTCTL[2].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0;
	priv->monUnitInf->HISTCTL[3].bit.BITSEL = E_IM_IIP_PARAM_BITSEL_7_0;


	priv->monCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->monCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->monCfg.unit_param_addr = (kulong)priv->monUnitInf;
	priv->monCfg.load_unit_param_flag = 0;

	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->slUnitInf, sizeof(T_IM_IIP_PARAM_STS));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->monUnitInf, sizeof(T_IM_IIP_PARAM_MON));


	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(srcPixid, &priv->pixfmtTbl0);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(dstPixid, &priv->pixfmtTbl1);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(srcUnitid, &priv->onedCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(mon_unitid, &priv->monCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(dstUnitid, &priv->slCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Set_Interrupt(waitFactor, D_IM_IIP_ENABLE_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Clear_HISTGRAM(1, 1, 1, 1);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	Im_IIP_On_Pclk();
	CtImIipMon_DDIM_PRINT(("ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL2.bit.PADRS,
				(kuint32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL0.bit.HWEN));
	CtImIipMon_DDIM_PRINT(("SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO));
	Im_IIP_Off_Pclk();

	CT_Im_IIP_Print_Unitcfg_Byid(srcUnitid);
	CT_Im_IIP_Print_Unitcfg_Byid(mon_unitid);
	CT_Im_IIP_Print_Unitcfg_Byid(dstUnitid);
	CT_Im_IIP_Print_Pixfmttbl_Detail(srcPixid);
	CT_Im_IIP_Print_Pixfmttbl_Detail(dstPixid);

	Dd_ARM_Dmb_Pou();

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start1\n"));
	priv->ercd = Im_IIP_Start_SWTRG(dstUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start2\n"));
	priv->ercd = Im_IIP_Start_SWTRG(mon_unitid, D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start3\n"));
	priv->ercd = Im_IIP_Start_SWTRG(srcUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "WaitEnd\n"));
	priv->ercd = Im_IIP_Wait_End(&priv->waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
		priv->ercd, priv->waitFactorResult));
	if(priv->ercd != D_DDIM_OK) {
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Abort\n"));
		priv->ercd = Im_IIP_Stop(D_IM_IIP_ABORT);
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
            priv->ercd, priv->waitFactorResult));
	}

#ifndef CO_CT_IM_IIP_11_1_2_DISABLE_HIST
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "** hist_a\n"));
	priv->ercd = Im_IIP_Get_HISTGRAM(bufferHistgram, NULL, NULL, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_HISTMAX(&histmax, NULL, NULL, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	Palladium_Set_Out_Localstack((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 70;
	bufferHistgram[histmax] = 3000;
#endif
	CT_Im_IIP_Plot_Hist(bufferHistgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
	DDIM_User_Dly_Tsk(500);		// Wait for UART output.
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "** hist_b\n"));
	priv->ercd = Im_IIP_Get_HISTGRAM(NULL, bufferHistgram, NULL, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_HISTMAX(NULL, &histmax, NULL, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	Palladium_Set_Out_Localstack((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 70;
	bufferHistgram[histmax] = 3000;
#endif
	CT_Im_IIP_Plot_Hist(bufferHistgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
	DDIM_User_Dly_Tsk(500);		// Wait for UART output.
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "** hist_c\n"));
	priv->ercd = Im_IIP_Get_HISTGRAM(NULL, NULL, bufferHistgram, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_HISTMAX(NULL, NULL, &histmax, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	Palladium_Set_Out_Localstack((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 70;
	bufferHistgram[histmax] = 3000;
#endif
	CT_Im_IIP_Plot_Hist(bufferHistgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "** hist_d\n"));
	priv->ercd = Im_IIP_Get_HISTGRAM(NULL, NULL, NULL, bufferHistgram);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_HISTMAX(NULL, NULL, NULL, &histmax);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	Palladium_Set_Out_Localstack((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 70;
	bufferHistgram[histmax] = 3000;
#endif
	CT_Im_IIP_Plot_Hist(bufferHistgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END
#endif

	priv->ercd = Im_IIP_Get_MAXMON(&maxmon);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_MINMON(&minmon);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_ADDMON(&addmon);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	for(loopcnt = 0; loopcnt < 4; loopcnt++) {
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "max_mon[%u]:x=%u y=%u V=%d\n",
					loopcnt,
					maxmon.max[loopcnt].pos_x,
					maxmon.max[loopcnt].pos_y,
					maxmon.max[loopcnt].value
					));
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "min_mon[%u]:x=%u y=%u V=%d\n",
					loopcnt,
					minmon.min[loopcnt].pos_x,
					minmon.min[loopcnt].pos_y,
					minmon.min[loopcnt].value
					));
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "add_mon[%u]:x=%u y=%u V=%d\n",
					loopcnt,
					addmon.add[loopcnt].pos_x,
					addmon.add[loopcnt].pos_y,
					addmon.add[loopcnt].value
					));
	}

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n"));
	priv->ercd = Im_IIP_Close_SWTRG(unitidBitmask, pixidBitmask, openResBitmask);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}


// MON Unit 11-1-2 YUV422 VGA-> YUV422 VGA
#undef CtImIipMon_D_IM_IIP_FUNC_NAME
#define CtImIipMon_D_IM_IIP_FUNC_NAME "ct_im_iip_mon_11_1_2: "
kint32 ct_im_iip_mon_11_1_2(CtImIipMon *self)
{
	CtImIipMonPrivate *priv = CT_IM_IIP_MON_GET_PRIVATE(self);

	const kuint32					waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const kuint32					unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_SL2 
                                        | D_IM_IIP_PARAM_PLDUNIT_MON;
	const kuint32					pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID			srcUnitid = E_IM_IIP_UNIT_ID_LD1;
	const E_IM_IIP_UNIT_ID			dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const E_IM_IIP_UNIT_ID			mon_unitid = E_IM_IIP_UNIT_ID_MON;
	const E_IM_IIP_PARAM_PORTID		srcPortid = E_IM_IIP_PARAM_PORTID_LD1;
	const E_IM_IIP_PARAM_PORTID		dstPortid = E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32					srcPixid = 4;
	const kuint32					dstPixid = 5;
	const kuint32					openResBitmask = E_IM_IIP_OPEN_RES_CACHE0 | E_IM_IIP_OPEN_RES_HIST_0  
                                        | E_IM_IIP_OPEN_RES_HIST_1 | E_IM_IIP_OPEN_RES_HIST_2;
	T_IM_IIP_MAXMON					maxmon;
	T_IM_IIP_MINMON					minmon;
	T_IM_IIP_ADDMON					addmon;
	kuint32							loopcnt;
#ifndef CO_CT_IM_IIP_11_1_2_DISABLE_HIST
	static kulong					bufferHistgram[D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)];
	UCHAR							histmax;
#endif


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = Im_IIP_Open_SWTRG(unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));
	if(priv->ercd != D_IM_IIP_OK) {
		return priv->ercd;
	}

	priv->pixfmtTbl0 = g_ct_im_iip_pixfmttbl_base;
	priv->pixfmtTbl0.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl0.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH;
	priv->pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_Y;
	priv->pixfmtTbl0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C;
	priv->pixfmtTbl0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C;
	priv->pixfmtTbl0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_A;
	priv->pixfmtTbl0.pix_depth = D_IM_IIP_PDEPTH_16BITS;

	priv->pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	priv->pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH;
	priv->pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_Y;
	priv->pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C;
	priv->pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C;
	priv->pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_A;
	priv->pixfmtTbl1.pix_depth = D_IM_IIP_PDEPTH_16BITS;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL)));

	memset(priv->onedUnitInf, '\0', sizeof(*priv->onedUnitInf));
	*priv->onedUnitInf = g_ct_im_iip_param_1dl_base;
	priv->onedUnitInf->LD_TOPCNF0.bit.WAITCONF = dstPortid;
	priv->onedUnitInf->PIXIDDEF.bit.IPIXID = srcPixid;

	priv->onedCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->onedCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->onedCfg.unit_param_addr = (kulong)priv->onedUnitInf;
	priv->onedCfg.load_unit_param_flag = 0;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->slUnitInf, sizeof(T_IM_IIP_PARAM_STS)));

	memset(priv->slUnitInf, '\0', sizeof(*priv->slUnitInf));
	*priv->slUnitInf = g_ct_im_iip_param_sts_base;
	priv->slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid;
	priv->slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;


	priv->slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->slCfg.unit_param_addr = (kulong)priv->slUnitInf;
	priv->slCfg.load_unit_param_flag = unitidBitmask;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "monUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->monUnitInf, sizeof(T_IM_IIP_PARAM_MON)));

	memset(priv->monUnitInf, '\0', sizeof(*priv->monUnitInf));
	*priv->monUnitInf = g_ct_im_iip_param_mon_base;
	priv->monUnitInf->MONDSEL.bit.DSEL = E_IM_IIP_PARAM_DSEL_SL2;
	priv->monUnitInf->HISTCTL[0].bit.BITSEL = 3;
	priv->monUnitInf->HISTCTL[1].bit.BITSEL = 3;
	priv->monUnitInf->HISTCTL[2].bit.BITSEL = 3;

	priv->monCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->monCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->monCfg.unit_param_addr = (kulong)priv->monUnitInf;
	priv->monCfg.load_unit_param_flag = 0;

	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->slUnitInf, sizeof(T_IM_IIP_PARAM_STS));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->monUnitInf, sizeof(T_IM_IIP_PARAM_MON));


	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(srcPixid, &priv->pixfmtTbl0);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(dstPixid, &priv->pixfmtTbl1);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(srcUnitid, &priv->onedCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(mon_unitid, &priv->monCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(dstUnitid, &priv->slCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Set_Interrupt(waitFactor, D_IM_IIP_ENABLE_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Clear_HISTGRAM(1, 1, 1, 1);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	Im_IIP_On_Pclk();
	CtImIipMon_DDIM_PRINT(("ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL2.bit.PADRS,
				(kuint32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL0.bit.HWEN));
	CtImIipMon_DDIM_PRINT(("SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start1\n"));
	priv->ercd = Im_IIP_Start_SWTRG(dstUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start2\n"));
	priv->ercd = Im_IIP_Start_SWTRG(mon_unitid, D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start3\n"));
	priv->ercd = Im_IIP_Start_SWTRG(srcUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "WaitEnd\n"));
	priv->ercd = Im_IIP_Wait_End(&priv->waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
		priv->ercd, priv->waitFactorResult));
	if(priv->ercd != D_DDIM_OK) {
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Abort\n"));
		priv->ercd = Im_IIP_Stop(D_IM_IIP_ABORT);
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
			priv->ercd, priv->waitFactorResult));
	}

#ifndef CO_CT_IM_IIP_11_1_2_DISABLE_HIST
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "** hist_a\n"));
	priv->ercd = Im_IIP_Get_HISTGRAM(bufferHistgram, NULL, NULL, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_HISTMAX(&histmax, NULL, NULL, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	Palladium_Set_Out_Localstack((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 70;
	bufferHistgram[histmax] = 3000;
#endif
	CT_Im_IIP_Plot_Hist(bufferHistgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
	DDIM_User_Dly_Tsk(500);		// Wait for UART output.
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "** hist_b\n"));
	priv->ercd = Im_IIP_Get_HISTGRAM(NULL, bufferHistgram, NULL, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_HISTMAX(NULL, &histmax, NULL, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	Palladium_Set_Out_Localstack((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 255;
	bufferHistgram[histmax] = 3000;
#endif
	CT_Im_IIP_Plot_Hist(bufferHistgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
	DDIM_User_Dly_Tsk(500);		// Wait for UART output.
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "** hist_c\n"));
	priv->ercd = Im_IIP_Get_HISTGRAM(NULL, NULL, bufferHistgram, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_HISTMAX(NULL, NULL, &histmax, NULL);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	Palladium_Set_Out_Localstack((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 255;
	bufferHistgram[histmax] = 3000;
#endif
	CT_Im_IIP_Plot_Hist(bufferHistgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "** hist_d\n"));
	priv->ercd = Im_IIP_Get_HISTGRAM(NULL, NULL, NULL, bufferHistgram);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_HISTMAX(NULL, NULL, NULL, &histmax);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
	ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	Palladium_Set_Out_Localstack((kulong)bufferHistgram, D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 255;
	bufferHistgram[histmax] = 3000;
#endif
	CT_Im_IIP_Plot_Hist(bufferHistgram, (D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
// ### REMOVE_RELEASE BEGIN
#endif
// ### REMOVE_RELEASE END
#endif

	priv->ercd = Im_IIP_Get_MAXMON(&maxmon);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_MINMON(&minmon);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Get_ADDMON(&addmon);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	for(loopcnt = 0; loopcnt < 4; loopcnt++) {
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "max_mon[%u]:x=%u y=%u V=%d\n",
					loopcnt,
					maxmon.max[loopcnt].pos_x,
					maxmon.max[loopcnt].pos_y,
					maxmon.max[loopcnt].value
					));
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "min_mon[%u]:x=%u y=%u V=%d\n",
					loopcnt,
					minmon.min[loopcnt].pos_x,
					minmon.min[loopcnt].pos_y,
					minmon.min[loopcnt].value
					));
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "add_mon[%u]:x=%u y=%u V=%d\n",
					loopcnt,
					addmon.add[loopcnt].pos_x,
					addmon.add[loopcnt].pos_y,
					addmon.add[loopcnt].value
					));
	}

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n"));
	priv->ercd = Im_IIP_Close_SWTRG(unitidBitmask, pixidBitmask, openResBitmask);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}


// MON Unit 11-1-X
kint32 ct_im_iip_mon_run_11_1(CtImIipMon *self, const kuint32 ctNo3rd)
{
	CtImIipMonPrivate *priv = CT_IM_IIP_MON_GET_PRIVATE(self);

	switch(ctNo3rd) {
		// Test-11-1-1
		case 1:
			return ct_im_iip_mon_11_1_1(priv->ciIipMom);

		// Test-11-1-2
		case 2:
			return ct_im_iip_mon_11_1_2(priv->ciIipMom);

		default:
			CtImIipMon_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

#endif //CO_CT_IM_IIP_DISABLE

CtImIipMon *ct_im_iip_mon_new(void)
{
    CtImIipMon *self = k_object_new_with_private(CT_TYPE_IM_IIP_MON, sizeof(CtImIipMonPrivate));
    return self;
}
