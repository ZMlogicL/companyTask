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
#include "ctimiip.h"

// im_iip header
#include "imiipdefine.h"
#include "imiipstruct.h"
#include "imiipvoid.h"
#include "ddimusercustom.h"

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
    CtImIipMon *	ciIipMom;
	DdimUserCustom *ddimUserCus;
	kint32			ercd;
	TImIipPixfmttbl	pixfmtTbl0;		// 1DL Unit input
	TImIipPixfmttbl	pixfmtTbl1;		// SL Unit output
	TImIipUnitCfg	onedCfg;
	Tim1dl*			onedUnitInf;
	TimSts*			slUnitInf;
	TImIipUnitCfg	slCfg;
	TimMon*			monUnitInf;
	TImIipUnitCfg	monCfg;
	kuint32			waitFactorResult;
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
	priv->ciIipMom 			= ct_im_iip_mon_new();
	priv->ddimUserCus 		= ddim_user_custom_new();
	priv->onedUnitInf 		= &gCtImIipUnitParam1dl0;
	priv->slUnitInf 		= &gCtImIipUnitParamSl0;
	priv->monUnitInf 		= &gCtImIipUnitParamMon;
	priv->waitFactorResult 	= 0;
}

static void ct_im_iip_mon_destructor(CtImIipMon *self)
{
	CtImIipMonPrivate *priv = CT_IM_IIP_MON_GET_PRIVATE(self);
	if(priv->ciIipMom){
		k_object_unref(priv->ciIipMom);
	}
	priv->ciIipMom = NULL;

	if(priv->ddimUserCus){
		k_object_unref(priv->ddimUserCus);
	}
	priv->ddimUserCus = NULL;
}
/*
 *PUBLIC
 */
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
	CtImIipMonPrivate *	priv = CT_IM_IIP_MON_GET_PRIVATE(self);

	const kuint32		waitFactor = ImIipDefine_D_IM_IIP_INT_FACTOR_AXIERR | ImIipDefine_D_IM_IIP_INT_FACTOR_SL4END;
	const kuint32		unitidBitmask = ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD1 
							| ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL4 | ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_MON;
	const kuint32		pixidBitmask = ImIipStruct_E_IM_IIP_PIXID_4 | ImIipStruct_E_IM_IIP_PIXID_5;
	const EImIipUnitId	srcUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_LD1;
	const EImIipUnitId	dstUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL4;
	const EImIipUnitId	monUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_MON;
	const EimPortid		srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1;
	const EimPortid		dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL4;
	const kuint32		srcPixid = 4;
	const kuint32		dstPixid = 5;
	const kuint32		openResBitmask = ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0 | ImIipStruct_E_IM_IIP_OPEN_RES_HIST_0 
                            | ImIipStruct_E_IM_IIP_OPEN_RES_HIST_1 | ImIipStruct_E_IM_IIP_OPEN_RES_HIST_2;
	TImIipMaxmon		maxmon;
	TImIipMinmon		minmon;
	TImIipAddmon		addmon;
	kuint32				loopcnt;
#ifndef CO_CT_IM_IIP_11_1_2_DISABLE_HIST
	static kulong		bufferHistgram[ImIipDefine_D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)];
	kuchar				histmax;
#endif

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = Im_IIP_Open_SWTRG(unitidBitmask, pixidBitmask, openResBitmask, 
		CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));
	if(priv->ercd != ImIipDefine_D_IM_IIP_OK) {
		return priv->ercd;
	}

	priv->pixfmtTbl0 = gCtImIipPixfmttblBase;
	priv->pixfmtTbl0.lineBytes.yG = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.cbB = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.crR = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;	// Input Y frame.
	priv->pixfmtTbl0.addr.yG = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	priv->pixfmtTbl0.addr.cbB = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.crR = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;	// Input Y frame.
	priv->pixfmtTbl0.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE;

	priv->pixfmtTbl1 = gCtImIipPixfmttblBase;
	priv->pixfmtTbl1.lineBytes.yG = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.cbB = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.crR = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	priv->pixfmtTbl1.addr.yG = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	priv->pixfmtTbl1.addr.cbB = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.crR = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->onedUnitInf, sizeof(Tim1dl)));

	memset(priv->onedUnitInf, '\0', sizeof(*priv->onedUnitInf));
	*priv->onedUnitInf = gCtImIipParam1dlBase;
	priv->onedUnitInf->ldTopcnf0.bit.waitconf = dstPortid;
	priv->onedUnitInf->pixiddef.bit.ipixid = srcPixid;

	priv->onedCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->onedCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->onedCfg.unitParamAddr = (kulong)priv->onedUnitInf;
	priv->onedCfg.loadUnitParamFlag = 0;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->slUnitInf, sizeof(TimSts)));

	memset(priv->slUnitInf, '\0', sizeof(*priv->slUnitInf));
	*priv->slUnitInf = gCtImIipParamStsBase;
	priv->slUnitInf->base.slTopcnf0.bit.dataconf = srcPortid;
	priv->slUnitInf->base.pixiddef.bit.opixid = dstPixid;


	priv->slCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->slCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->slCfg.unitParamAddr = (kulong)priv->slUnitInf;
	priv->slCfg.loadUnitParamFlag = unitidBitmask;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "monUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->monUnitInf, sizeof(TimMon)));

	memset(priv->monUnitInf, '\0', sizeof(*priv->monUnitInf));
	*priv->monUnitInf = gCtImIipParamMonBase;
	priv->monUnitInf->mondsel.bit.dsel = ImIipParamEnum_E_IM_IIP_PARAM_DSEL_SL4;
	priv->monUnitInf->histctl[0].bit.bitsel = ImIipParamEnum_E_IM_IIP_PARAM_BITSEL_7_0;
	priv->monUnitInf->histctl[1].bit.bitsel = ImIipParamEnum_E_IM_IIP_PARAM_BITSEL_7_0;
	priv->monUnitInf->histctl[2].bit.bitsel = ImIipParamEnum_E_IM_IIP_PARAM_BITSEL_7_0;
	priv->monUnitInf->histctl[3].bit.bitsel = ImIipParamEnum_E_IM_IIP_PARAM_BITSEL_7_0;


	priv->monCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->monCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->monCfg.unitParamAddr = (kulong)priv->monUnitInf;
	priv->monCfg.loadUnitParamFlag = 0;

	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->onedUnitInf, sizeof(Tim1dl));
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->slUnitInf, sizeof(TimSts));
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->monUnitInf, sizeof(TimMon));


	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(srcPixid, &priv->pixfmtTbl0);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(dstPixid, &priv->pixfmtTbl1);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(srcUnitid, &priv->onedCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(monUnitid, &priv->monCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(dstUnitid, &priv->slCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Set_Interrupt(waitFactor, ImIipDefine_D_IM_IIP_ENABLE_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Clear_HISTGRAM(1, 1, 1, 1);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	im_iip_struct_on_pclk();
	CtImIipMon_DDIM_PRINT(("ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblLd1.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblLd1.unitinftbl0.bit.hwen));
	CtImIipMon_DDIM_PRINT(("SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.unitinftblSl2.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblSl2.unitinftbl0.bit.hwen,
				(kuint32)ioIip.unitinftblSl2.unitinftbl1.bit.pldunitHi,
				(kuint32)ioIip.unitinftblSl2.unitinftbl1.bit.pldunitLo));
	im_iip_struct_off_pclk();

	ct_im_iip_print_unitcfg_byid(srcUnitid);
	ct_im_iip_print_unitcfg_byid(monUnitid);
	ct_im_iip_print_unitcfg_byid(dstUnitid);
	ct_im_iip_print_pixfmttbl_detail(srcPixid);
	ct_im_iip_print_pixfmttbl_detail(dstPixid);

	DD_ARM_DMB_POU();

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start1\n"));
	priv->ercd = Im_IIP_Start_SWTRG(dstUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start2\n"));
	priv->ercd = Im_IIP_Start_SWTRG(monUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start3\n"));
	priv->ercd = Im_IIP_Start_SWTRG(srcUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "WaitEnd\n"));
	priv->ercd = Im_IIP_Wait_End(&priv->waitFactorResult, waitFactor, ImIipDefine_D_IM_IIP_OR_WAIT, 30);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
		priv->ercd, priv->waitFactorResult));
	if(priv->ercd != D_DDIM_OK) {
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Abort\n"));
		priv->ercd = im_iip_main_stop(ImIipDefine_D_IM_IIP_ABORT);
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
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	palladium_test_set_out_localstack((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 70;
	bufferHistgram[histmax] = 3000;
#endif
	ct_im_iip_plot_hist(bufferHistgram, (ImIipDefine_D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
	ddim_user_custom_dly_tsk(priv->ddimUserCus, 500);		// Wait for UART output.
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
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	palladium_test_set_out_localstack((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 70;
	bufferHistgram[histmax] = 3000;
#endif
	ct_im_iip_plot_hist(bufferHistgram, (ImIipDefine_D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
	ddim_user_custom_dly_tsk(priv->ddimUserCus, 500);		// Wait for UART output.
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
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	palladium_test_set_out_localstack((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 70;
	bufferHistgram[histmax] = 3000;
#endif
	ct_im_iip_plot_hist(bufferHistgram, (ImIipDefine_D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
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
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	palladium_test_set_out_localstack((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 70;
	bufferHistgram[histmax] = 3000;
#endif
	ct_im_iip_plot_hist(bufferHistgram, (ImIipDefine_D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
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
					maxmon.max[loopcnt].posX,
					maxmon.max[loopcnt].posY,
					maxmon.max[loopcnt].value
					));
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "min_mon[%u]:x=%u y=%u V=%d\n",
					loopcnt,
					minmon.min[loopcnt].posX,
					minmon.min[loopcnt].posY,
					minmon.min[loopcnt].value
					));
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "add_mon[%u]:x=%u y=%u V=%d\n",
					loopcnt,
					addmon.add[loopcnt].posX,
					addmon.add[loopcnt].posY,
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
	CtImIipMonPrivate *	priv = CT_IM_IIP_MON_GET_PRIVATE(self);

	const kuint32		waitFactor = ImIipDefine_D_IM_IIP_INT_FACTOR_AXIERR | ImIipDefine_D_IM_IIP_INT_FACTOR_SL2END;
	const kuint32		unitidBitmask = ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD1 
							| ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL2 | ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_MON;
	const kuint32		pixidBitmask = ImIipStruct_E_IM_IIP_PIXID_4 | ImIipStruct_E_IM_IIP_PIXID_5;
	const EImIipUnitId	srcUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_LD1;
	const EImIipUnitId	dstUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL2;
	const EImIipUnitId	monUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_MON;
	const EimPortid		srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1;
	const EimPortid		dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32		srcPixid = 4;
	const kuint32		dstPixid = 5;
	const kuint32		openResBitmask = ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0 | ImIipStruct_E_IM_IIP_OPEN_RES_HIST_0  
                            | ImIipStruct_E_IM_IIP_OPEN_RES_HIST_1 | ImIipStruct_E_IM_IIP_OPEN_RES_HIST_2;
	TImIipMaxmon		maxmon;
	TImIipMinmon		minmon;
	TImIipAddmon		addmon;
	kuint32				loopcnt;
#ifndef CO_CT_IM_IIP_11_1_2_DISABLE_HIST
	static kulong		bufferHistgram[ImIipDefine_D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)];
	kuchar				histmax;
#endif

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = Im_IIP_Open_SWTRG(unitidBitmask, pixidBitmask, openResBitmask, 
		CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));
	if(priv->ercd != ImIipDefine_D_IM_IIP_OK) {
		return priv->ercd;
	}

	priv->pixfmtTbl0 = gCtImIipPixfmttblBase;
	priv->pixfmtTbl0.lineBytes.yG = CtImIip_D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.cbB = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.crR = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH;
	priv->pixfmtTbl0.addr.yG = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_Y;
	priv->pixfmtTbl0.addr.cbB = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C;
	priv->pixfmtTbl0.addr.crR = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C;
	priv->pixfmtTbl0.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_A;
	priv->pixfmtTbl0.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_16BITS;

	priv->pixfmtTbl1 = gCtImIipPixfmttblBase;
	priv->pixfmtTbl1.lineBytes.yG = CtImIip_D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.cbB = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.crR = CtImIip_D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH;
	priv->pixfmtTbl1.addr.yG = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_Y;
	priv->pixfmtTbl1.addr.cbB = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C;
	priv->pixfmtTbl1.addr.crR = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C;
	priv->pixfmtTbl1.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_A;
	priv->pixfmtTbl1.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_16BITS;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->onedUnitInf, sizeof(Tim1dl)));

	memset(priv->onedUnitInf, '\0', sizeof(*priv->onedUnitInf));
	*priv->onedUnitInf = gCtImIipParam1dlBase;
	priv->onedUnitInf->ldTopcnf0.bit.waitconf = dstPortid;
	priv->onedUnitInf->pixiddef.bit.ipixid = srcPixid;

	priv->onedCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->onedCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->onedCfg.unitParamAddr = (kulong)priv->onedUnitInf;
	priv->onedCfg.loadUnitParamFlag = 0;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->slUnitInf, sizeof(TimSts)));

	memset(priv->slUnitInf, '\0', sizeof(*priv->slUnitInf));
	*priv->slUnitInf = gCtImIipParamStsBase;
	priv->slUnitInf->base.slTopcnf0.bit.dataconf = srcPortid;
	priv->slUnitInf->base.pixiddef.bit.opixid = dstPixid;


	priv->slCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->slCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->slCfg.unitParamAddr = (kulong)priv->slUnitInf;
	priv->slCfg.loadUnitParamFlag = unitidBitmask;

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "monUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->monUnitInf, sizeof(TimMon)));

	memset(priv->monUnitInf, '\0', sizeof(*priv->monUnitInf));
	*priv->monUnitInf = gCtImIipParamMonBase;
	priv->monUnitInf->mondsel.bit.dsel = ImIipParamEnum_E_IM_IIP_PARAM_DSEL_SL2;
	priv->monUnitInf->histctl[0].bit.bitsel = 3;
	priv->monUnitInf->histctl[1].bit.bitsel = 3;
	priv->monUnitInf->histctl[2].bit.bitsel = 3;

	priv->monCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->monCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->monCfg.unitParamAddr = (kulong)priv->monUnitInf;
	priv->monCfg.loadUnitParamFlag = 0;

	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->onedUnitInf, sizeof(Tim1dl));
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->slUnitInf, sizeof(TimSts));
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->monUnitInf, sizeof(TimMon));


	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(srcPixid, &priv->pixfmtTbl0);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(dstPixid, &priv->pixfmtTbl1);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(srcUnitid, &priv->onedCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(monUnitid, &priv->monCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(dstUnitid, &priv->slCfg);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Set_Interrupt(waitFactor, ImIipDefine_D_IM_IIP_ENABLE_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Clear_HISTGRAM(1, 1, 1, 1);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	im_iip_struct_on_pclk();
	CtImIipMon_DDIM_PRINT(("ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblLd1.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblLd1.unitinftbl0.bit.hwen));
	CtImIipMon_DDIM_PRINT(("SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.unitinftblSl2.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblSl2.unitinftbl0.bit.hwen,
				(kuint32)ioIip.unitinftblSl2.unitinftbl1.bit.pldunitHi,
				(kuint32)ioIip.unitinftblSl2.unitinftbl1.bit.pldunitLo));
	im_iip_struct_off_pclk();

	DD_ARM_DMB_POU();

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start1\n"));
	priv->ercd = Im_IIP_Start_SWTRG(dstUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start2\n"));
	priv->ercd = Im_IIP_Start_SWTRG(monUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Start3\n"));
	priv->ercd = Im_IIP_Start_SWTRG(srcUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));


	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "WaitEnd\n"));
	priv->ercd = Im_IIP_Wait_End(&priv->waitFactorResult, waitFactor, ImIipDefine_D_IM_IIP_OR_WAIT, 30);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
		priv->ercd, priv->waitFactorResult));
	if(priv->ercd != D_DDIM_OK) {
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "Abort\n"));
		priv->ercd = im_iip_main_stop(ImIipDefine_D_IM_IIP_ABORT);
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
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	palladium_test_set_out_localstack((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 70;
	bufferHistgram[histmax] = 3000;
#endif
	ct_im_iip_plot_hist(bufferHistgram, (ImIipDefine_D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
	ddim_user_custom_dly_tsk(priv->ddimUserCus, 500);		// Wait for UART output.
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
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	palladium_test_set_out_localstack((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 255;
	bufferHistgram[histmax] = 3000;
#endif
	ct_im_iip_plot_hist(bufferHistgram, (ImIipDefine_D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
	ddim_user_custom_dly_tsk(priv->ddimUserCus, 500);		// Wait for UART output.
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
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	palladium_test_set_out_localstack((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 255;
	bufferHistgram[histmax] = 3000;
#endif
	ct_im_iip_plot_hist(bufferHistgram, (ImIipDefine_D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
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
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	palladium_test_set_out_localstack((kulong)bufferHistgram, ImIipDefine_D_IM_IIP_HIST_MAXBYTES);
	CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "histmax = %u\n", histmax));
#else
// ### REMOVE_RELEASE END
#ifdef CO_DEBUG_ON_PC
	histmax = 255;
	bufferHistgram[histmax] = 3000;
#endif
	ct_im_iip_plot_hist(bufferHistgram, (ImIipDefine_D_IM_IIP_HIST_MAXBYTES / sizeof(kulong)), histmax);
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
					maxmon.max[loopcnt].posX,
					maxmon.max[loopcnt].posY,
					maxmon.max[loopcnt].value
					));
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "min_mon[%u]:x=%u y=%u V=%d\n",
					loopcnt,
					minmon.min[loopcnt].posX,
					minmon.min[loopcnt].posY,
					minmon.min[loopcnt].value
					));
		CtImIipMon_DDIM_PRINT((CtImIipMon_D_IM_IIP_FUNC_NAME "add_mon[%u]:x=%u y=%u V=%d\n",
					loopcnt,
					addmon.add[loopcnt].posX,
					addmon.add[loopcnt].posY,
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
