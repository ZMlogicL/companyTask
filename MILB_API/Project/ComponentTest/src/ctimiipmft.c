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
#include "imiipdefine.h"
#include "imiipstruct.h"

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
    CtImIipMft *	ciIipMft;
	kint32			ercd;
	TImIipPixfmttbl	pixfmtTbl0;		// 1DL Unit input
	TImIipPixfmttbl	pixfmtTbl1;		// SL Unit output
	TImIipUnitCfg	onedCfg;
	TImIipUnitCfg	mftCfg;
	Tim1dl*			onedUnitInf;
	TimMft*			mftUnitInf;
	TimSts*			slUnitInf;
	TImIipUnitCfg	slCfg;
	kuint32			waitFactorResult;
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

static const TimMft S_G_CT_IM_IIP_PARAM_MFT_BASE = {
	.header0.bit.BeginningAddress = 0x0000,
	.header0.bit.WordLength = 9,
	.header0.bit.CtrlCode = ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET,
//	.FTTOPCONF.bit.WAITCONF,	// set later
//	.FTTOPCONF.bit.DATACONF,	// set later
	.mftmd.bit.mftmd = ImIipParamEnum_E_IM_IIP_PARAM_MFTMD_MAX,
	.flttpsz.bit.flttpsz = 64,
//	.FLTOUTHSZ.bit.FLTOUTHSZ,	// set later
	.mftctld[0].bit = {
		.fix = 0,
		.val = 0,
	},
	.mftctld[1].bit = {
		.fix = 0,
		.val = 0,
	},
	.mftctld[2].bit = {
		.fix = 0,
		.val = 0,
	},
	.mftctld[3].bit = {
		.fix = 0,
		.val = 0,
	},
};

#ifdef __GNUC__
static TimMft	S_G_CT_IM_IIP_UNIT_PARAM_MFT __attribute__((aligned(8)));	// Needs 8bytes align
#else
static __align(8) TimMft	S_G_CT_IM_IIP_UNIT_PARAM_MFT;					// Needs 8bytes align
#endif

static void ct_im_iip_mft_constructor(CtImIipMft *self) 
{
	CtImIipMftPrivate *priv = CT_IM_IIP_MFT_GET_PRIVATE(self);
	priv->ciIipMft 			= ct_im_iip_mft_new();
	priv->onedUnitInf 		= &gCtImIipUnitParam1dl0;
	priv->mftUnitInf 		= &S_G_CT_IM_IIP_UNIT_PARAM_MFT;
	priv->slUnitInf 		= &gCtImIipUnitParamSl0;
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
/*
 *PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/

// MFT Unit 15-1-1 YCC422 U8 VGA->VGA Max filter
#undef D_IM_IIP_FUNC_NAME
#define CtImIipMft_D_IM_IIP_FUNC_NAME "ct_im_iip_mft_15_1_1: "
kint32 ct_im_iip_mft_15_1_1(CtImIipMft *self)
{
	CtImIipMftPrivate *	priv = CT_IM_IIP_MFT_GET_PRIVATE(self);

	const kuint32		waitFactor = ImIipDefine_D_IM_IIP_INT_FACTOR_AXIERR | ImIipDefine_D_IM_IIP_INT_FACTOR_SL2END;
	const kulonglong	unitidBitmask = ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD1 
							| ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_MFT | ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL2;
	const kuint32		pixidBitmask = ImIipStruct_E_IM_IIP_PIXID_4 | ImIipStruct_E_IM_IIP_PIXID_5;
	const EImIipUnitId	srcUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_LD1;
	const EImIipUnitId	filter1Unitid = ImIipStruct_E_IM_IIP_UNIT_ID_MFT;
	const EImIipUnitId	dstUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL2;
	const EimPortid		srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1;
	const EimPortid		filter1Portid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_MFT;
	const EimPortid		dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32		srcPixid = 4;
	const kuint32		dstPixid = 5;
	const kuint32		openResBitmask = ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0;
	kulong				fltouthsz;


	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "\n"));

	priv->ercd = Im_IIP_Open_SWTRG(unitidBitmask, pixidBitmask, openResBitmask, 
		CtImIip_D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));
	if(priv->ercd != ImIipDefine_D_IM_IIP_OK) {
		return priv->ercd;
	}

	priv->pixfmtTbl0 = gCtImIipPixfmttblBase;
	priv->pixfmtTbl0.lineBytes.yG = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.cbB = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.crR = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	priv->pixfmtTbl0.addr.yG = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	priv->pixfmtTbl0.addr.cbB = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.crR = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A;

	priv->pixfmtTbl1 = gCtImIipPixfmttblBase;
	priv->pixfmtTbl1.lineBytes.yG = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.cbB = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.crR = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	priv->pixfmtTbl1.addr.yG = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	priv->pixfmtTbl1.addr.cbB = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.crR = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->onedUnitInf, sizeof(Tim1dl)));

	memset(priv->onedUnitInf, '\0', sizeof(*priv->onedUnitInf));
	*priv->onedUnitInf = gCtImIipParam1dlBase;
	priv->onedUnitInf->ldTopcnf0.bit.waitconf = filter1Portid;
	priv->onedUnitInf->pixiddef.bit.ipixid = srcPixid;
	priv->onedUnitInf->ldCtl.bit.saverd = ImIipParamEnum_E_IM_IIP_PARAM_SLOW_1PIX_CYC;


	priv->onedCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->onedCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->onedCfg.unitParamAddr = (kulong)priv->onedUnitInf;
	priv->onedCfg.loadUnitParamFlag = 0;


	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "mftUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->mftUnitInf, sizeof(TimMft)));

	memset(priv->mftUnitInf, '\0', sizeof(*priv->mftUnitInf));
	*priv->mftUnitInf = S_G_CT_IM_IIP_PARAM_MFT_BASE;
	priv->mftUnitInf->fttopconf.bit.dataconf = srcPortid;
	priv->mftUnitInf->fttopconf.bit.waitconf = dstPortid;

	priv->mftCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->mftCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->mftCfg.unitParamAddr = (kulong)priv->mftUnitInf;
	priv->mftCfg.loadUnitParamFlag = 0;

	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->slUnitInf, sizeof(TimSts)));

	memset(priv->slUnitInf, '\0', sizeof(*priv->slUnitInf));
	*priv->slUnitInf = gCtImIipParamStsBase;
	priv->slUnitInf->base.slTopcnf0.bit.dataconf = filter1Portid;
	priv->slUnitInf->base.pixiddef.bit.opixid = dstPixid;


	priv->slCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->slCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->slCfg.unitParamAddr = (kulong)priv->slUnitInf;
	priv->slCfg.loadUnitParamFlag = unitidBitmask;


	priv->onedUnitInf->ldPhsz.bit.phsz0 = priv->pixfmtTbl0.width;
	priv->onedUnitInf->ldPhsz.bit.phsz1 = priv->pixfmtTbl0.width;
	fltouthsz = priv->onedUnitInf->ldHsize.bit.hend
			  - priv->onedUnitInf->ldHsize.bit.hstart
			  + 1
			  - priv->mftUnitInf->flttpsz.bit.flttpsz;
	priv->mftUnitInf->fltouthsz.bit.fltouthsz = fltouthsz;
	priv->slUnitInf->base.slPhsz.bit.phsz0 = fltouthsz;
	priv->slUnitInf->base.slPhsz.bit.phsz1 = fltouthsz;
	priv->slUnitInf->base.slHsize.bit.hend = priv->mftUnitInf->fltouthsz.bit.fltouthsz -1;


	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->onedUnitInf, sizeof(Tim1dl));
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->mftUnitInf, sizeof(TimMft));
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->slUnitInf, sizeof(TimSts));


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

	im_iip_struct_on_pclk();
	CtImIipMft_DDIM_PRINT(("ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblLd1.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblLd1.unitinftbl0.bit.hwen));
	CtImIipMft_DDIM_PRINT(("MFT: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblMft.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblMft.unitinftbl0.bit.hwen));
	CtImIipMft_DDIM_PRINT(("SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.unitinftblSl2.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblSl2.unitinftbl0.bit.hwen,
				(kuint32)ioIip.unitinftblSl2.unitinftbl1.bit.pldunitHi,
				(kuint32)ioIip.unitinftblSl2.unitinftbl1.bit.pldunitLo));
	im_iip_struct_off_pclk();

	ct_im_iip_print_unitcfg_byid(srcUnitid);
	ct_im_iip_print_unitcfg_byid(filter1Unitid);
	ct_im_iip_print_unitcfg_byid(dstUnitid);
	ct_im_iip_print_pixfmttbl_detail(srcPixid);
	ct_im_iip_print_pixfmttbl_detail(dstPixid);

	DD_ARM_DMB_POU();

	// Need start sequence Store->MFT->1DL or Store->MFT->1DL
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "Start1\n"));
	priv->ercd = Im_IIP_Start_SWTRG(dstUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "Start2\n"));
	priv->ercd = Im_IIP_Start_SWTRG(filter1Unitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));

	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "Start3\n"));
	priv->ercd = Im_IIP_Start_SWTRG(srcUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", priv->ercd));


	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "WaitEnd\n"));
	priv->ercd = Im_IIP_Wait_End(&priv->waitFactorResult, waitFactor, ImIipDefine_D_IM_IIP_OR_WAIT, 30);
	CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
		priv->ercd, priv->waitFactorResult));
	if(priv->ercd != D_DDIM_OK) {
		CtImIipMft_DDIM_PRINT((CtImIipMft_D_IM_IIP_FUNC_NAME "Stop\n"));
		priv->ercd = im_iip_main_stop(ImIipDefine_D_IM_IIP_ABORT);
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
