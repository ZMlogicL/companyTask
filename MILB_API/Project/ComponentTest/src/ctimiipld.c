/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipLd类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_im_iip_ld.c
 * @brief		IIP LD unit ct code
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

// CT header
#include "ctimiip.h"

// ### REMOVE_RELEASE BEGIN
// PT header
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

// im_iip header
#include "im_iip.h"

// MILB register header
#include "jdsiip.h"

// for Memory barrier
#include "ddarm.h"

// for memset
#include <string.h>
#include "ctimiipld.h"
#include "imiipunitparameter.h"
#include "imiipdefine.h"

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif
#endif

K_TYPE_DEFINE_WITH_PRIVATE(CtImIipLd, ct_im_iip_ld);
#define CT_IM_IIP_LD_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImIipLdPrivate,CT_TYPE_IM_IIP_LD))

struct _CtImIipLdPrivate {
	CtImIipLd *					ciIipLd;
	kint32						ercd;
	T_IM_IIP_PIXFMTTBL			pixfmtTbl0;		// 1DL Unit input
	T_IM_IIP_PIXFMTTBL			pixfmtTbl1;		// SL Unit output
	T_IM_IIP_UNIT_CFG			onedCfg;
	TImIipParam1dl*				onedUnitInf;
	TImIipParamSts*				slUnitInf;
	T_IM_IIP_UNIT_CFG			slCfg;
	kuint32						waitFactorResult;
};

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#undef Ddim_Print
#define CtImIipLd_DDIM_PRINT(arg)		{DDIM_User_Printf arg;}		/**< printf function inside DDIM */
#endif

static void ct_im_iip_ld_constructor(CtImIipLd *self) 
{
	CtImIipLdPrivate *priv 	= CT_IM_IIP_LD_GET_PRIVATE(self);
	priv->ciIipLd 			= ct_im_iip_ld_new();
	priv->onedUnitInf 		= &g_ct_im_iip_unit_param_1dl0;
	priv->slUnitInf 		= &g_ct_im_iip_unit_param_sl0;
	priv->waitFactorResult 	= 0;
}

static void ct_im_iip_ld_destructor(CtImIipLd *self)
{
	CtImIipLdPrivate *priv = CT_IM_IIP_LD_GET_PRIVATE(self);
	if(priv->ciIipLd){
		k_object_unref(priv);
	}
	priv->ciIipLd = NULL;
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

// LD Unit 8-1-1 RGBA4444 VGA->VGA
#undef D_IM_IIP_FUNC_NAME
#define CtImIipLd_D_IM_IIP_FUNC_NAME "ct_im_iip_ld_8_1_1: "
kint32 ct_im_iip_ld_8_1_1(CtImIipLd *self)
{
	const kuint32				waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const kuint32				unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const kuint32				pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID		srcUnitid = E_IM_IIP_UNIT_ID_LD1;
	const E_IM_IIP_UNIT_ID		dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const EImIipParamPortid		srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1;
	const EImIipParamPortid		dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32				srcPixid = 4;
	const kuint32				dstPixid = 5;
	const kuint32				openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;
	CtImIipLdPrivate *			priv = CT_IM_IIP_LD_GET_PRIVATE(self);

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = Im_IIP_Open_SWTRG(unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));
	if(priv->ercd != D_IM_IIP_OK) {
		return priv->ercd;
	}

	priv->pixfmtTbl0 = g_ct_im_iip_pixfmttbl_base;
	priv->pixfmtTbl0.pix_format = E_IM_IIP_PFMT_RGBA4444;
	priv->pixfmtTbl0.line_bytes.Y_G = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;
	priv->pixfmtTbl0.line_bytes.Cb_B = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl0.line_bytes.Cr_R = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl0.line_bytes.Alpha = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_RGBA4444;
	priv->pixfmtTbl0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_RGBA4444;	// dummy
	priv->pixfmtTbl0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_RGBA4444;	// dummy
	priv->pixfmtTbl0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_RGBA4444;	// dummy
	priv->pixfmtTbl0.alpha = D_IM_IIP_ALPHA_TRUE;

	priv->pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	priv->pixfmtTbl1.pix_format = E_IM_IIP_PFMT_RGBA4444;
	priv->pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;
	priv->pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl1.line_bytes.Alpha = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_RGBA4444;
	priv->pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_RGBA4444;	// dummy
	priv->pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_RGBA4444;	// dummy
	priv->pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_RGBA4444;	// dummy
	priv->pixfmtTbl1.alpha = D_IM_IIP_ALPHA_TRUE;

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", 
		(kuint32)priv->onedUnitInf, sizeof(TImIipParam1dl)));

	memset(priv->onedUnitInf, '\0', sizeof(*priv->onedUnitInf));
	*priv->onedUnitInf = g_ct_im_iip_param_1dl_base;
	priv->onedUnitInf->LD_TOPCNF0.bit.WAITCONF = dstPortid;
	priv->onedUnitInf->PIXIDDEF.bit.IPIXID = srcPixid;
	priv->onedUnitInf->LD_PHSZ.bit.PHSZ1 = D_IM_IIP_VGA_WIDTH,
	priv->onedUnitInf->LD_PVSZ.bit.PVSZ1 = D_IM_IIP_VGA_LINES,
	priv->onedUnitInf->LD_PHSZ.bit.PHSZ0 = D_IM_IIP_VGA_WIDTH,
	priv->onedUnitInf->LD_PVSZ.bit.PVSZ0 = D_IM_IIP_VGA_LINES,

	priv->onedCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->onedCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->onedCfg.unit_param_addr = (kulong)priv->onedUnitInf;
	priv->onedCfg.load_unit_param_flag = 0;

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", 
		(kuint32)priv->slUnitInf, sizeof(TImIipParamSts)));

	memset(priv->slUnitInf, '\0', sizeof(*priv->slUnitInf));
	*priv->slUnitInf = g_cTImIipParamSts_base;
	priv->slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid;
	priv->slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;
	priv->slUnitInf->BASE.SL_PHSZ.bit.PHSZ1 =  D_IM_IIP_VGA_WIDTH;
	priv->slUnitInf->BASE.SL_PVSZ.bit.PVSZ1 =  D_IM_IIP_VGA_LINES;
	priv->slUnitInf->BASE.SL_PHSZ.bit.PHSZ0 = D_IM_IIP_VGA_WIDTH;
	priv->slUnitInf->BASE.SL_PVSZ.bit.PVSZ0 = D_IM_IIP_VGA_LINES;



	priv->slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->slCfg.unit_param_addr = (kulong)priv->slUnitInf;
	priv->slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->onedUnitInf, sizeof(TImIipParam1dl));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->slUnitInf, sizeof(TImIipParamSts));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	Palladium_Set_Out_Localstack((kulong)priv->onedUnitInf, sizeof(TImIipParam1dl));
	Palladium_Set_Out_Localstack((kulong)priv->slUnitInf, sizeof(TImIipParamSts));
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(srcPixid, &priv->pixfmtTbl0);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(dstPixid, &priv->pixfmtTbl1);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(srcUnitid, &priv->onedCfg);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(dstUnitid, &priv->slCfg);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Set_Interrupt(waitFactor, D_IM_IIP_ENABLE_ON);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	Im_IIP_On_Pclk();
	CtImIipLd_DDIM_PRINT(("ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.UNITINFTBL_LD1.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.UNITINFTBL_LD1.UNITINFTBL0.bit.HWEN));
	CtImIipLd_DDIM_PRINT(("SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Start1\n"));
	priv->ercd = Im_IIP_Start_SWTRG(dstUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Start2\n"));
	priv->ercd = Im_IIP_Start_SWTRG(srcUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

#if 0
	for(kuint32 loopcnt = 0; loopcnt < 10; loopcnt++) {
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					ioIip.IZACTL1.bit.SLALE,
					ioIip.INTIZ0.word,
					ioIip.INTIZ1.word));
		DDIM_User_Dly_Tsk(1);
	}
#endif

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "WaitEnd\n"));
	priv->ercd = Im_IIP_Wait_End(&priv->waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
		priv->ercd, priv->waitFactorResult));
	if(priv->ercd != D_DDIM_OK) {
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Stop\n"));
		priv->ercd = Im_IIP_Stop(D_IM_IIP_ABORT);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
			priv->ercd, priv->waitFactorResult));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 1
	// UnitINFダンプ
	Palladium_Set_Out_Localstack((kulong)priv->onedUnitInf, sizeof(TImIipParam1dl));
	Palladium_Set_Out_Localstack((kulong)priv->slUnitInf, sizeof(TImIipParamSts));
#endif


#if 1
	// dump UNITINF ONED[1]
	{
		kuint32 paramBytes;
		priv->ercd = Im_IIP_Get_UNIT_PARAM(srcUnitid, gCtImIIP_Get_Unit_Param, &paramBytes);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", priv->ercd, paramBytes));
		if(priv->ercd == D_IM_IIP_OK) {
			CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "dump UNITINF ONED[1] %u\n", paramBytes));
			ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
		}
	}
#endif


#if 1
	// dump UNITINF SL[2]
	{
		kuint32 paramBytes;
		priv->ercd = Im_IIP_Get_UNIT_PARAM(dstUnitid, gCtImIIP_Get_Unit_Param, &paramBytes);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", priv->ercd, paramBytes));
		if(priv->ercd == D_IM_IIP_OK) {
			CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", paramBytes));
			ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
		}
	}
#endif


#if 0
#ifndef CO_DEBUG_ON_PC
	// dump ioIip
	{
		kulong regdump_addr = D_IM_IIP_REGDUMP_ADDR;
		kulong regdump_bytes = sizeof(ioIip);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "dump ioIip %u\n", regdump_bytes));
		memcpy((void*)regdump_addr, (void*)&ioIip, regdump_bytes);
		Palladium_Set_Out_Localstack(regdump_addr, regdump_bytes);
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n"));
	priv->ercd = Im_IIP_Close_SWTRG(unitidBitmask, pixidBitmask, openResBitmask);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}


// LD Unit 8-1-2 RGBA4444 VGA->VGA
#undef CtImIipLd_D_IM_IIP_FUNC_NAME
#define CtImIipLd_D_IM_IIP_FUNC_NAME "ct_im_iip_ld_8_1_2: "
kint32 ct_im_iip_ld_8_1_2(CtImIipLd *self)
{
	const kuint32					waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const kuint32					unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const kuint32					pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID			srcUnitid = E_IM_IIP_UNIT_ID_LD1;
	const E_IM_IIP_UNIT_ID			dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const EImIipParamPortid		srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1;
	const EImIipParamPortid		dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32					srcPixid = 4;
	const kuint32					dstPixid = 5;
	const kuint32					openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;
	CtImIipLdPrivate *priv = CT_IM_IIP_LD_GET_PRIVATE(self);

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = Im_IIP_Open_SWTRG(unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));
	if(priv->ercd != D_IM_IIP_OK) {
		return priv->ercd;
	}

	priv->pixfmtTbl0 = g_ct_im_iip_pixfmttbl_base;
	priv->pixfmtTbl0.pix_format = E_IM_IIP_PFMT_RGBA4444;
	priv->pixfmtTbl0.line_bytes.Y_G = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;
	priv->pixfmtTbl0.line_bytes.Cb_B = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl0.line_bytes.Cr_R = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl0.line_bytes.Alpha = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_RGBA4444;
	priv->pixfmtTbl0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_RGBA4444;	// dummy
	priv->pixfmtTbl0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_RGBA4444;	// dummy
	priv->pixfmtTbl0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_RGBA4444;	// dummy
	priv->pixfmtTbl0.alpha = D_IM_IIP_ALPHA_TRUE;

	priv->pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	priv->pixfmtTbl1.pix_format = E_IM_IIP_PFMT_RGBA4444;
	priv->pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;
	priv->pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl1.line_bytes.Alpha = D_IM_IIP_VGA_RGBA4444_GLOBAL_WIDTH;	// dummy
	priv->pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_RGBA4444;
	priv->pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_RGBA4444;	// dummy
	priv->pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_RGBA4444;	// dummy
	priv->pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_RGBA4444;	// dummy
	priv->pixfmtTbl1.alpha = D_IM_IIP_ALPHA_TRUE;

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", 
		(kuint32)priv->onedUnitInf, sizeof(TImIipParam1dl)));

	memset(priv->onedUnitInf, '\0', sizeof(*priv->onedUnitInf));
	*priv->onedUnitInf = g_ct_im_iip_param_1dl_base;
	priv->onedUnitInf->LD_TOPCNF0.bit.WAITCONF = dstPortid;
	priv->onedUnitInf->PIXIDDEF.bit.IPIXID = srcPixid;

	priv->onedCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->onedCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->onedCfg.unit_param_addr = (kulong)priv->onedUnitInf;
	priv->onedCfg.load_unit_param_flag = 0;

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", 
		(kuint32)priv->slUnitInf, sizeof(TImIipParamSts)));

	memset(priv->slUnitInf, '\0', sizeof(*priv->slUnitInf));
	*priv->slUnitInf = g_cTImIipParamSts_base;
	priv->slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid;
	priv->slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;


	priv->slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->slCfg.unit_param_addr = (kulong)priv->slUnitInf;
	priv->slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->onedUnitInf, sizeof(TImIipParam1dl));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->slUnitInf, sizeof(TImIipParamSts));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	Palladium_Set_Out_Localstack((kulong)priv->onedUnitInf, sizeof(TImIipParam1dl));
	Palladium_Set_Out_Localstack((kulong)priv->slUnitInf, sizeof(TImIipParamSts));
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(srcPixid, &priv->pixfmtTbl0);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(dstPixid, &priv->pixfmtTbl1);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(srcUnitid, &priv->onedCfg);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(dstUnitid, &priv->slCfg);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Set_Interrupt(waitFactor, D_IM_IIP_ENABLE_ON);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	Im_IIP_On_Pclk();
	CtImIipLd_DDIM_PRINT(("ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.UNITINFTBL_LD1.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.UNITINFTBL_LD1.UNITINFTBL0.bit.HWEN));
	CtImIipLd_DDIM_PRINT(("SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Start1\n"));
	priv->ercd = Im_IIP_Start_SWTRG(dstUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Start2\n"));
	priv->ercd = Im_IIP_Start_SWTRG(srcUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

#if 0
	for(kuint32 loopcnt = 0; loopcnt < 10; loopcnt++) {
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					ioIip.IZACTL1.bit.SLALE,
					ioIip.INTIZ0.word,
					ioIip.INTIZ1.word));
		DDIM_User_Dly_Tsk(1);
	}
#endif

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "WaitEnd\n"));
	priv->ercd = Im_IIP_Wait_End(&priv->waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
		priv->ercd, priv->waitFactorResult));
	if(priv->ercd != D_DDIM_OK) {
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Stop\n"));
		priv->ercd = Im_IIP_Stop(D_IM_IIP_ABORT);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
			priv->ercd, priv->waitFactorResult));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 1
	// UnitINFダンプ
	Palladium_Set_Out_Localstack((kulong)priv->onedUnitInf, sizeof(TImIipParam1dl));
	Palladium_Set_Out_Localstack((kulong)priv->slUnitInf, sizeof(TImIipParamSts));
#endif


#if 1
	// dump UNITINF ONED[1]
	{
		kuint32 paramBytes;
		priv->ercd = Im_IIP_Get_UNIT_PARAM(srcUnitid, gCtImIIP_Get_Unit_Param, &paramBytes);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", priv->ercd, paramBytes));
		if(priv->ercd == D_IM_IIP_OK) {
			CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "dump UNITINF ONED[1] %u\n", paramBytes));
			ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
		}
	}
#endif


#if 1
	// dump UNITINF SL[2]
	{
		kuint32 paramBytes;
		priv->ercd = Im_IIP_Get_UNIT_PARAM(dstUnitid, gCtImIIP_Get_Unit_Param, &paramBytes);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", priv->ercd, paramBytes));
		if(priv->ercd == D_IM_IIP_OK) {
			CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", paramBytes));
			ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
		}
	}
#endif


#if 0
#ifndef CO_DEBUG_ON_PC
	// dump ioIip
	{
		kulong regdump_addr = D_IM_IIP_REGDUMP_ADDR;
		kulong regdump_bytes = sizeof(ioIip);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "dump ioIip %u\n", regdump_bytes));
		memcpy((void*)regdump_addr, (void*)&ioIip, regdump_bytes);
		Palladium_Set_Out_Localstack(regdump_addr, regdump_bytes);
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n"));
	priv->ercd = Im_IIP_Close_SWTRG(unitidBitmask, pixidBitmask, openResBitmask);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}


// LD Unit 8-1-3 YUV422Planar VGA-> YUV422Interleaved VGA
#undef CtImIipLd_D_IM_IIP_FUNC_NAME
#define CtImIipLd_D_IM_IIP_FUNC_NAME "ct_im_iip_ld_8_1_3: "
kint32 ct_im_iip_ld_8_1_3(CtImIipLd *self)
{
	const kuint32					waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const kuint32					unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const kuint32					pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID			srcUnitid = E_IM_IIP_UNIT_ID_LD1;
	const E_IM_IIP_UNIT_ID			dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const EImIipParamPortid		srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1;
	const EImIipParamPortid		dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32					srcPixid = 4;
	const kuint32					dstPixid = 5;
	const kuint32					openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;
	CtImIipLdPrivate *priv = CT_IM_IIP_LD_GET_PRIVATE(self);

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = Im_IIP_Open_SWTRG(unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));
	if(priv->ercd != D_IM_IIP_OK) {
		return priv->ercd;
	}

	priv->pixfmtTbl0 = g_ct_im_iip_pixfmttbl_base;
	priv->pixfmtTbl0.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl0.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	priv->pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	priv->pixfmtTbl0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A;

	priv->pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	priv->pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	priv->pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	priv->pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", 
		(kuint32)priv->onedUnitInf, sizeof(TImIipParam1dl)));

	memset(priv->onedUnitInf, '\0', sizeof(*priv->onedUnitInf));
	*priv->onedUnitInf = g_ct_im_iip_param_1dl_base;
	priv->onedUnitInf->LD_TOPCNF0.bit.WAITCONF = dstPortid;
	priv->onedUnitInf->PIXIDDEF.bit.IPIXID = srcPixid;

	priv->onedCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->onedCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->onedCfg.unit_param_addr = (kulong)priv->onedUnitInf;
	priv->onedCfg.load_unit_param_flag = 0;

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", 
		(kuint32)priv->slUnitInf, sizeof(TImIipParamSts)));

	memset(priv->slUnitInf, '\0', sizeof(*priv->slUnitInf));
	*priv->slUnitInf = g_cTImIipParamSts_base;
	priv->slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid;
	priv->slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;


	priv->slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->slCfg.unit_param_addr = (kulong)priv->slUnitInf;
	priv->slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->onedUnitInf, sizeof(TImIipParam1dl));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->slUnitInf, sizeof(TImIipParamSts));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	Palladium_Set_Out_Localstack((kulong)priv->onedUnitInf, sizeof(TImIipParam1dl));
	Palladium_Set_Out_Localstack((kulong)priv->slUnitInf, sizeof(TImIipParamSts));
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(srcPixid, &priv->pixfmtTbl0);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(dstPixid, &priv->pixfmtTbl1);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(srcUnitid, &priv->onedCfg);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(dstUnitid, &priv->slCfg);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Set_Interrupt(waitFactor, D_IM_IIP_ENABLE_ON);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	Im_IIP_On_Pclk();
	CtImIipLd_DDIM_PRINT(("ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.UNITINFTBL_LD1.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.UNITINFTBL_LD1.UNITINFTBL0.bit.HWEN));
	CtImIipLd_DDIM_PRINT(("SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(kuint32)ioIip.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Start1\n"));
	priv->ercd = Im_IIP_Start_SWTRG(dstUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Start2\n"));
	priv->ercd = Im_IIP_Start_SWTRG(srcUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

#if 0
	for(kuint32 loopcnt = 0; loopcnt < 10; loopcnt++) {
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					ioIip.IZACTL1.bit.SLALE,
					ioIip.INTIZ0.word,
					ioIip.INTIZ1.word));
		DDIM_User_Dly_Tsk(1);
	}
#endif

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "WaitEnd\n"));
	priv->ercd = Im_IIP_Wait_End(&priv->waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
		priv->ercd, priv->waitFactorResult));
	if(priv->ercd != D_DDIM_OK) {
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Abort\n"));
		priv->ercd = Im_IIP_Stop(D_IM_IIP_ABORT);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
			priv->ercd, priv->waitFactorResult));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	// UnitINFダンプ
	Palladium_Set_Out_Localstack((kulong)priv->onedUnitInf, sizeof(TImIipParam1dl));
	Palladium_Set_Out_Localstack((kulong)priv->slUnitInf, sizeof(TImIipParamSts));
#endif


#if 1
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Stop\n"));
		priv->ercd = Im_IIP_Stop(D_IM_IIP_STOP);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));
#endif


#if 1
	// dump UNITINF ONED[1]
	{
		kuint32 paramBytes;
		priv->ercd = Im_IIP_Get_UNIT_PARAM(srcUnitid, gCtImIIP_Get_Unit_Param, &paramBytes);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", priv->ercd, paramBytes));
		if(priv->ercd == D_IM_IIP_OK) {
			CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "dump UNITINF ONED[1] %u\n", paramBytes));
			ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
		}
	}
#endif


#if 1
	// dump UNITINF SL[2]
	{
		kuint32 paramBytes;
		priv->ercd = Im_IIP_Get_UNIT_PARAM(dstUnitid, gCtImIIP_Get_Unit_Param, &paramBytes);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", priv->ercd, paramBytes));
		if(priv->ercd == D_IM_IIP_OK) {
			CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", paramBytes));
			ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, paramBytes);
		}
	}
#endif


#if 0
#ifndef CO_DEBUG_ON_PC
	// dump ioIip
	{
		kulong regdump_addr = D_IM_IIP_REGDUMP_ADDR;
		kulong regdump_bytes = sizeof(ioIip);
		CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "dump ioIip %u\n", regdump_bytes));
		memcpy((void*)regdump_addr, (void*)&ioIip, regdump_bytes);
		Palladium_Set_Out_Localstack(regdump_addr, regdump_bytes);
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n"));
	priv->ercd = Im_IIP_Close_SWTRG(unitidBitmask, pixidBitmask, openResBitmask);
	CtImIipLd_DDIM_PRINT((CtImIipLd_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}


// LD Unit 8-1-X
kint32 ct_im_iip_ld_run_8_1(CtImIipLd *self, const kuint32 ctNo3rd)
{
	CtImIipLdPrivate *priv = CT_IM_IIP_LD_GET_PRIVATE(self);

	switch(ctNo3rd) {
		// Test-8-1-1
		case 1:
			return ct_im_iip_ld_8_1_1(priv->ciIipLd);

		// Test-8-1-2
		case 2:
			return ct_im_iip_ld_8_1_2(priv->ciIipLd);

		// Test-8-1-3
		case 3:
			return ct_im_iip_ld_8_1_3(priv->ciIipLd);

		default:
			CtImIipLd_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}


#endif //CO_CT_IM_IIP_DISABLE

CtImIipLd *ct_im_iip_ld_new(void)
{
    CtImIipLd *self = k_object_new_with_private(CT_TYPE_IM_IIP_LD, sizeof(CtImIipLdPrivate));
    return self;
}
