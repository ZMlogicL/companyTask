/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipMft类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_im_iip_mft.c
 * @brief		IIP MFT unit ct code
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

// CT header
#include "ctimiip.h"
#include "imiipparamenum.h"

// im_iip header
#include "im_iip.h"

// MILB register header
#include "jdsiip.h"

// for Memory barrier
#include "ddarm.h"

// for memset
#include <string.h>
#include "ctimiipmft.h"
#include "imiipunitparameter.h"

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif
#endif

K_TYPE_DEFINE_WITH_PRIVATE(CtImIipMft, ct_im_iip_mft);
#define CT_IM_IIP_MFT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImIipMftPrivate,CT_TYPE_IM_IIP_MFT))

struct _CtImIipMftPrivate {
    CtImIipMft *					ciIipMft;
	kint32							ercd;
	T_IM_IIP_PIXFMTTBL				pixfmtTbl0;		// 1DL Unit input
	T_IM_IIP_PIXFMTTBL				pixfmtTbl1;		// SL Unit output
	T_IM_IIP_UNIT_CFG				onedCfg;
	T_IM_IIP_UNIT_CFG				mftCfg;
	T_IM_IIP_PARAM_1DL*				onedUnitInf;
	T_IM_IIP_PARAM_MFT*				mftUnitInf;
	T_IM_IIP_PARAM_STS*				slUnitInf;
	T_IM_IIP_UNIT_CFG				slCfg;
	kuint32							waitFactorResult;
};

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/

#ifndef CO_CT_IM_IIP_DISABLE

#if 1
#undef Ddim_Print
#define CtImIipMft_DDIM_PRINT(arg)		{DDIM_User_Printf arg;}		/**< printf function inside DDIM */
#endif

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

static const T_IM_IIP_PARAM_MFT S_G_CT_IM_IIP_PARAM_MFT_BASE = {
	.header0.bit.BeginningAddress = 0x0000,
	.header0.bit.WordLength = 9,
	.header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET,
//	.FTTOPCONF.bit.WAITCONF,	// set later
//	.FTTOPCONF.bit.DATACONF,	// set later
	.MFTMD.bit.MFTMD = E_IM_IIP_PARAM_MFTMD_MAX,
	.FLTTPSZ.bit.FLTTPSZ = 64,
//	.FLTOUTHSZ.bit.FLTOUTHSZ,	// set later
	.MFTCTLD[0].bit = {
		.FIX = 0,
		.VAL = 0,
	},
	.MFTCTLD[1].bit = {
		.FIX = 0,
		.VAL = 0,
	},
	.MFTCTLD[2].bit = {
		.FIX = 0,
		.VAL = 0,
	},
	.MFTCTLD[3].bit = {
		.FIX = 0,
		.VAL = 0,
	},
};

#ifdef __GNUC__
static T_IM_IIP_PARAM_MFT	S_G_CT_IM_IIP_UNIT_PARAM_MFT __attribute__((aligned(8)));	// Needs 8bytes align
#else
static __align(8) T_IM_IIP_PARAM_MFT	S_G_CT_IM_IIP_UNIT_PARAM_MFT;					// Needs 8bytes align
#endif

static void ct_im_iip_mft_constructor(CtImIipMft *self) 
{
	CtImIipMftPrivate *priv = CT_IM_IIP_MFT_GET_PRIVATE(self);
	priv->ciIipMft 			= ct_im_iip_mft_new();
	priv->onedUnitInf 		= &g_ct_im_iip_unit_param_1dl0;
	priv->mftUnitInf 		= &S_G_CT_IM_IIP_UNIT_PARAM_MFT;
	priv->slUnitInf 		= &g_ct_im_iip_unit_param_sl0;
	priv->waitFactorResult 	= 0;
}

static void ct_im_iip_mft_destructor(CtImIipMft *self)
{
	CtImIipMftPrivate *priv = CT_IM_IIP_MFT_GET_PRIVATE(self);
	if(priv->ciIipMft){
		k_object_unref(priv->ciIipMft);
	}
	priv->ciIipMft = NULL;
}

/*PUBLIC*/

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/

// MFT Unit 15-1-1 YCC422 U8 VGA->VGA Max filter
#undef D_IM_IIP_FUNC_NAME
#define CtImIipMft_D_IM_IIP_FUNC_NAME "ct_im_iip_mft_15_1_1: "
kint32 ct_im_iip_mft_15_1_1(CtImIipMft *self)
{
	CtImIipMftPrivate *priv = CT_IM_IIP_MFT_GET_PRIVATE(self);

	const kuint32					waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const kulonglong				unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_MFT 
                                        | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const kuint32					pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID			srcUnitid = E_IM_IIP_UNIT_ID_LD1;
	const E_IM_IIP_UNIT_ID			filter1Unitid = E_IM_IIP_UNIT_ID_MFT;
	const E_IM_IIP_UNIT_ID			dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const EImIipParamPortid			srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1;
	const EImIipParamPortid			filter1Portid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_MFT;
	const EImIipParamPortid			dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32					srcPixid = 4;
	const kuint32					dstPixid = 5;
	const kuint32					openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;
	kulong							fltouthsz;


	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = Im_IIP_Open_SWTRG(unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));
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

	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL)));

	memset(priv->onedUnitInf, '\0', sizeof(*priv->onedUnitInf));
	*priv->onedUnitInf = g_ct_im_iip_param_1dl_base;
	priv->onedUnitInf->ldTopcnf0.bit.WAITCONF = filter1Portid;
	priv->onedUnitInf->pixiddef.bit.IPIXID = srcPixid;
	priv->onedUnitInf->ldCtl.bit.SLOW = E_IM_IIP_PARAM_SLOW_1PIX_CYC;


	priv->onedCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->onedCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->onedCfg.unit_param_addr = (kulong)priv->onedUnitInf;
	priv->onedCfg.load_unit_param_flag = 0;


	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "mftUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->mftUnitInf, sizeof(T_IM_IIP_PARAM_MFT)));

	memset(priv->mftUnitInf, '\0', sizeof(*priv->mftUnitInf));
	*priv->mftUnitInf = S_G_CT_IM_IIP_PARAM_MFT_BASE;
	priv->mftUnitInf->fttopconf.bit.DATACONF = srcPortid;
	priv->mftUnitInf->fttopconf.bit.WAITCONF = dstPortid;

	priv->mftCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->mftCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->mftCfg.unit_param_addr = (kulong)priv->mftUnitInf;
	priv->mftCfg.load_unit_param_flag = 0;

	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->slUnitInf, sizeof(T_IM_IIP_PARAM_STS)));

	memset(priv->slUnitInf, '\0', sizeof(*priv->slUnitInf));
	*priv->slUnitInf = g_ct_im_iip_param_sts_base;
	priv->slUnitInf->BASE.slTopcnf0.bit.DATACONF = filter1Portid;
	priv->slUnitInf->BASE.pixiddef.bit.OPIXID = dstPixid;


	priv->slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	priv->slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->slCfg.unit_param_addr = (kulong)priv->slUnitInf;
	priv->slCfg.load_unit_param_flag = unitidBitmask;


	priv->onedUnitInf->ldPhsz.bit.PHSZ0 = priv->pixfmtTbl0.width;
	priv->onedUnitInf->ldPhsz.bit.PHSZ1 = priv->pixfmtTbl0.width;
	fltouthsz = priv->onedUnitInf->ldHsize.bit.HEND
			  - priv->onedUnitInf->ldHsize.bit.HSTART
			  + 1
			  - priv->mftUnitInf->flttpsz.bit.FLTTPSZ;
	priv->mftUnitInf->fltouthsz.bit.FLTOUTHSZ = fltouthsz;
	priv->slUnitInf->BASE.slPhsz.bit.PHSZ0 = fltouthsz;
	priv->slUnitInf->BASE.slPhsz.bit.PHSZ1 = fltouthsz;
	priv->slUnitInf->BASE.slHsize.bit.HEND = priv->mftUnitInf->fltouthsz.bit.FLTOUTHSZ -1;


	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->mftUnitInf, sizeof(T_IM_IIP_PARAM_MFT));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->slUnitInf, sizeof(T_IM_IIP_PARAM_STS));


	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(srcPixid, &priv->pixfmtTbl0);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_PIXFMTTBL(dstPixid, &priv->pixfmtTbl1);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(srcUnitid, &priv->onedCfg);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(filter1Unitid, &priv->mftCfg);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Ctrl_SWTRG_Unit(dstUnitid, &priv->slCfg);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	priv->ercd = Im_IIP_Set_Interrupt(waitFactor, D_IM_IIP_ENABLE_ON);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	Im_IIP_On_Pclk();
	CtImIipMft_DDIM_PRINT(("ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL2.bit.PADRS,
				(kuint32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL0.bit.HWEN));
	CtImIipMft_DDIM_PRINT(("MFT: PADRS=0x%x HWEN=%u\n",
				(kuint32)IO_IIP.UNITINFTBL_MFT.UNITINFTBL2.bit.PADRS,
				(kuint32)IO_IIP.UNITINFTBL_MFT.UNITINFTBL0.bit.HWEN));
	CtImIipMft_DDIM_PRINT(("SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(kuint32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO));
	Im_IIP_Off_Pclk();

	CT_Im_IIP_Print_Unitcfg_Byid(srcUnitid);
	CT_Im_IIP_Print_Unitcfg_Byid(filter1Unitid);
	CT_Im_IIP_Print_Unitcfg_Byid(dstUnitid);
	CT_Im_IIP_Print_Pixfmttbl_Detail(srcPixid);
	CT_Im_IIP_Print_Pixfmttbl_Detail(dstPixid);

	Dd_ARM_Dmb_Pou();

	// Need start sequence Store->MFT->1DL or Store->MFT->1DL
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "Start1\n"));
	priv->ercd = Im_IIP_Start_SWTRG(dstUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "Start2\n"));
	priv->ercd = Im_IIP_Start_SWTRG(filter1Unitid, D_IM_IIP_SWTRG_ON);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "Start3\n"));
	priv->ercd = Im_IIP_Start_SWTRG(srcUnitid, D_IM_IIP_SWTRG_ON);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));


	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "WaitEnd\n"));
	priv->ercd = Im_IIP_Wait_End(&priv->waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
		priv->ercd, priv->waitFactorResult));
	if(priv->ercd != D_DDIM_OK) {
		CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "Stop\n"));
		priv->ercd = Im_IIP_Stop(D_IM_IIP_ABORT);
		CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
			priv->ercd, priv->waitFactorResult));
	}


	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n"));
	priv->ercd = Im_IIP_Close_SWTRG(unitidBitmask, pixidBitmask, openResBitmask);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	return D_DDIM_OK;
}

// MFT Unit 15-1-X
kint32 ct_im_iip_mft_run_15_1(CtImIipMft *self, const kuint32 ctNo3rd)
{
	CtImIipMftPrivate *priv = CT_IM_IIP_MFT_GET_PRIVATE(self);

	switch(ctNo3rd) {
		// Test-15-1-1
		case 1:
			return ct_im_iip_mft_15_1_1(priv->ciIipMft);

		default:
			CtImIipMft_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

#endif //CO_CT_IM_IIP_DISABLE

CtImIipMft *ct_im_iip_mft_new(void)
{
    CtImIipMft *self = k_object_new_with_private(CT_TYPE_IM_IIP_MFT, sizeof(CtImIipMftPrivate));
    return self;
}
