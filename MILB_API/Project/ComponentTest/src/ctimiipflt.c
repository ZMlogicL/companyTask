/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-04
*@author            :吴雨莎
*@brief             :ctimiipflt
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*3、
*4、
*5、
*@version
*
*/

/**
 * @file		ct_im_iip_flt.c
 * @brief		IIP FLT unit ct code
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


// CT header
#include "ct_im_iip.h"
//#include "ct_im_iip_flt.h"
#include "ctimiipflt.h"

// im_iip header
#include "im_iip.h"

// MILB register header
#include "jdsiip.h"

// for Memory barrier
#include "dd_arm.h"

// for memset
#include <string.h>


K_TYPE_DEFINE_WITH_PRIVATE(CtImIipFlt, ct_im_iip_flt)
#define CT_IM_IIP_FLT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImIipFltPrivate, CT_TYPE_IM_IIP_FLT))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/

#ifndef CO_CT_IM_IIP_DISABLE

#if 1
#include <stdio.h>
#undef CtImIipFlt_DDIM_PRINT
#define CtImIipFlt_DDIM_PRINT(arg)		{DDIM_User_Printf arg;}		/**< printf function inside DDIM */
#endif

// FLT Unit SLINK 9-1-1 YCC422 U8 VGA->VGA not convert
#undef CtImIipFlt_D_IM_IIP_FUNC_NAME
#define CtImIipFlt_D_IM_IIP_FUNC_NAME "ct_im_iip_9_1_1: "

// FLT Unit SLINK 9-1-2 Bayer 12bit packed VGA->VGA not convert
#undef CtImIipFlt_D_IM_IIP_FUNC_NAME
#define CtImIipFlt_D_IM_IIP_FUNC_NAME "ct_im_iip_9_1_2: "

// FLT Unit DLINK 9-2-1
#undef CtImIipFlt_D_IM_IIP_FUNC_NAME
#define CtImIipFlt_D_IM_IIP_FUNC_NAME "ct_im_iip_9_2_1: "

// FLT Unit NORMAL 9-3-1
#undef CtImIipFlt_D_IM_IIP_FUNC_NAME
#define CtImIipFlt_D_IM_IIP_FUNC_NAME "ct_im_iip_9_3_1: "

#endif //CO_CT_IM_IIP_DISABLE


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
struct  _CtImIipFltPrivate
{

};


/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/


/*
 *IMPL
 */
static void ct_im_iip_flt_constructor(CtImIipFlt *self)
{
 //CtImIipFltPrivate *priv = CT_IM_IIP_FLT_GET_PRIVATE(self);
}

static void ct_im_iip_flt_destructor(CtImIipFlt *self)
{
}


#ifndef CO_CT_IM_IIP_DISABLE


/*
 * PUBLIC
 */
kint32 ct_im_iip_9_1_1( CtImIipFlt *self )
{
	kint32 ercd;
	TImIipPixfmttbl pixfmtTbl0;		// 1DL Unit input
	TImIipPixfmttbl pixfmtTbl1;		// SL Unit output
	ImIipUnitCfg onedCfg;
	ImIipUnitCfg cscCfg;
	ImIipUnitCfg spfCfg;
	ImIipParam1Dl* onedUnitInf = &gCtImIipUnitParam1Dl0;
	ImIipParamCsc* cscUnitInf = &gCtImIipUnitParamCsc;
	ImIipParamFlt* fltUnitInf = &gCtImIipUnitParamFlt;
	ImIipParamSts* slUnitInf = &gCtImIipUnitParamSl0;
	ImIipUnitCfg slCfg;
	kuint32 waitFactorResult = 0;
	const kuint32	 waitFactor = ImIip_D_IM_IIP_INT_FACTOR_AXIERR | ImIip_D_IM_IIP_INT_FACTOR_SL2END;
	const kuint32	 unitidBitmask = ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD1 | ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_CSC1 |
			ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_FLT | ImIip_D_IM_IIP_PARAM_PLDUNIT_SL2;
	const kuint32	 pixidBitmask = ImIip_E_IM_IIP_PIXID_4 | ImIip_E_IM_IIP_PIXID_5;
	const ImIipEImIipUnitId srcUnitid = ImIip_E_IM_IIP_UNIT_ID_LD1;
	const ImIipEImIipUnitId filter1Unitid = ImIip_E_IM_IIP_UNIT_ID_CSC1;
	const ImIipEImIipUnitId filter2Unitid = ImIip_E_IM_IIP_UNIT_ID_FLT;
	const ImIipEImIipUnitId dstUnitid = ImIip_E_IM_IIP_UNIT_ID_SL2;
	const ImIipParamEImIipParamPortid srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1;
	const ImIipParamEImIipParamPortid filter1Portid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_CSC1;
	const ImIipParamEImIipParamPortid filter2Portid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_FLT_P0;
	const ImIipParamEImIipParamPortid dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32 srcPixid = 4;
	const kuint32 dstPixid = 5;
	const kuint32 openResBitmask = ImIip_E_IM_IIP_OPEN_RES_CACHE0;


	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, CtImIip_D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if( ercd != ImIip_D_IM_IIP_OK ) {
		return ercd;
	}

	pixfmtTbl0 = gCtImIipPixfmttblBase;
	pixfmtTbl0.lineBytes.Y_G = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl0.lineBytes.Cb_B = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0.lineBytes.Cr_R = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmtTbl0.addr.Y_G = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	pixfmtTbl0.addr.Cb_B = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmtTbl0.addr.Cr_R = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmtTbl0.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A;

	pixfmtTbl1 = gCtImIipPixfmttblBase;
	pixfmtTbl1.lineBytes.Y_G = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl1.lineBytes.Cb_B = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.lineBytes.Cr_R = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmtTbl1.addr.Y_G = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	pixfmtTbl1.addr.Cb_B = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl1.addr.Cr_R = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl1.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", (kuint32)onedUnitInf,
			sizeof(ImIipParam1Dl) ));

	memset( onedUnitInf, '\0', sizeof(*onedUnitInf) );
	*onedUnitInf = gCtImIipParam1DlBase;
	onedUnitInf->ldTopcnf0.bit.WAITCONF = filter1Portid;
	onedUnitInf->PIXIDDEF.bit.IPIXID = srcPixid;
	onedUnitInf->LdTopcnf1.bit.linkUid = filter2Portid;
	onedUnitInf->ldCtl.bit.ldMode = ImIipParamEnum_E_IM_IIP_PARAM_LD_MODE_LINK;
	onedUnitInf->ldCtl.bit.SLOW = ImIipParamEnum_E_IM_IIP_PARAM_SLOW_1PIX_CYC;

	onedCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg.unitParamAddr = (ULONG)onedUnitInf;
	onedCfg.loadUnitParamFlag = 0;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "cscUnitInf = 0x%x 0x%x\n", (kuint32)cscUnitInf,
sizeof(ImIipParamCsc) ));

	memset( cscUnitInf, '\0', sizeof(*cscUnitInf) );
	*cscUnitInf = gCtImIipParamCscBase;
	cscUnitInf->CSCTOPCNF.bit.DATACONF = srcPortid;
	cscUnitInf->CSCTOPCNF.bit.WAITCONF = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE;

	cscCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	cscCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	cscCfg.unitParamAddr = (ULONG)cscUnitInf;
	cscCfg.loadUnitParamFlag = 0;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "fltUnitInf = 0x%x 0x%x\n", (kuint32)fltUnitInf,
sizeof(ImIipParamFlt) ));

	memset( fltUnitInf, '\0', sizeof(*fltUnitInf) );
	*fltUnitInf = gCtImIipParamFltBase;
	fltUnitInf->TDLTOPCNF.bit.DATACONF = filter1Portid;
	fltUnitInf->TDLTOPCNF.bit.waitconf0 = dstPortid;
	fltUnitInf->TDLTOPCNF.bit.waitconf1 = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE;
	fltUnitInf->PIXIDDEF.bit.IPIXID0 = srcPixid;
	fltUnitInf->PIXIDDEF.bit.IPIXID1 = srcPixid;
	fltUnitInf->tdlCtl.bit.inputMode = ImIipParamEnum_E_IM_IIP_PARAM_INPUT_MODE_SLINK;
	fltUnitInf->tdlPf.bit.pfOn = ImIipParamEnum_E_IM_IIP_PARAM_PF_ON_INVALID;

	spfCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	spfCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	spfCfg.unitParamAddr = (ULONG)fltUnitInf;
	spfCfg.loadUnitParamFlag = 0;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (kuint32)slUnitInf,
sizeof(ImIipParamSts) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = gCtImIipParamStsBase;
	slUnitInf->BASE.slTopcnf0.bit.DATACONF = filter2Portid;
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;

	slCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unitParamAddr = (ULONG)slUnitInf;
	slCfg.loadUnitParamFlag = unitidBitmask;

	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)onedUnitInf, sizeof(ImIipParam1Dl) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)cscUnitInf, sizeof(ImIipParamCsc) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)fltUnitInf, sizeof(ImIipParamFlt) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)slUnitInf, sizeof(ImIipParamSts) );

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid, &pixfmtTbl0 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid, &onedCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( filter1Unitid, &cscCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( filter2Unitid, &spfCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, ImIipDefine_D_IM_IIP_ENABLE_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	im_iip_struct_on_pclk();
	CtImIipFlt_DDIM_PRINT(( "ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblLd1.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblLd1.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFlt_DDIM_PRINT(( "CSC1: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblCsc1.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblCsc1.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFlt_DDIM_PRINT(( "FLT: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblFlt.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblFlt.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFlt_DDIM_PRINT(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL0.bit.HWEN,
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL1.bit.PLDUNIT_HI,
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL1.bit.PLDUNIT_LO
			   ));
	im_iip_struct_off_pclk();

	DdArm_Dd_ARM_Dmb_Pou();

	// Need start sequence Store->CSC->1DL->FLT or Store->1DL->CSC->FLT
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( filter1Unitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start3\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start4\n" ));
	ercd = Im_IIP_Start_SWTRG( filter2Unitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, ImIipDefine_D_IM_IIP_OR_WAIT, 30 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != DriverCommon_D_DDIM_OK ) {
		CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = im_iip_main_stop( ImIip_D_IM_IIP_ABORT );
		CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return DriverCommon_D_DDIM_OK;
}

kint32 ct_im_iip_9_1_2( CtImIipFlt *self )
{
	kint32 ercd;
	TImIipPixfmttbl pixfmtTbl0;		// 1DL Unit input
	TImIipPixfmttbl pixfmtTbl1;		// SL Unit output
	ImIipUnitCfg onedCfg;
	ImIipUnitCfg cscCfg;
	ImIipUnitCfg spfCfg;
	ImIipParam1Dl* onedUnitInf = &gCtImIipUnitParam1Dl0;
	ImIipParamCsc* cscUnitInf = &gCtImIipUnitParamCsc;
	ImIipParamFlt* fltUnitInf = &gCtImIipUnitParamFlt;
	ImIipParamSts* slUnitInf = &gCtImIipUnitParamSl0;
	ImIipUnitCfg slCfg;
	kuint32 waitFactorResult = 0;
	const kuint32	 waitFactor = ImIip_D_IM_IIP_INT_FACTOR_AXIERR | ImIipDefine_D_IM_IIP_INT_FACTOR_SL6END;
	const kuint32	 unitidBitmask = ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD1 | ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_CSC2 |
			ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_FLT | ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL6;
	const kuint32	 pixidBitmask = ImIip_E_IM_IIP_PIXID_10 | ImIip_E_IM_IIP_PIXID_11;
	const ImIipEImIipUnitId srcUnitid = ImIip_E_IM_IIP_UNIT_ID_LD1;
	const ImIipEImIipUnitId filter1Unitid = ImIip_E_IM_IIP_UNIT_ID_CSC2;
	const ImIipEImIipUnitId filter2Unitid = ImIip_E_IM_IIP_UNIT_ID_FLT;
	const ImIipEImIipUnitId dstUnitid = ImIip_E_IM_IIP_UNIT_ID_SL6;
	const ImIipParamEImIipParamPortid srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1;
	const ImIipParamEImIipParamPortid filter1Portid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_CSC2;
	const ImIipParamEImIipParamPortid filter2Portid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_FLT_P0;
	const ImIipParamEImIipParamPortid dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL6;
	const kuint32	 srcPixid = 10;
	const kuint32 dstPixid = 11;
	const kuint32	 openResBitmask = ImIip_E_IM_IIP_OPEN_RES_CACHE1;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, CtImIip_D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if( ercd != ImIip_D_IM_IIP_OK ) {
		return ercd;
	}

	pixfmtTbl0 = gCtImIipPixfmttblBase;
	pixfmtTbl0.lineBytes.Y_G = D_IM_IIP_VGA_RAW12BIT_GLOBAL_WIDTH;
	pixfmtTbl0.lineBytes.Cb_B = 0;	// dummy
	pixfmtTbl0.lineBytes.Cr_R = 0;	// dummy
	pixfmtTbl0.lineBytes.Alpha = 0;	// dummy
	pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_RAW12BIT;
	pixfmtTbl0.addr.Cb_B = 0;		// dummy
	pixfmtTbl0.addr.Cr_R = 0;		// dummy
	pixfmtTbl0.addr.Alpha = 0;	// dummy
	pixfmtTbl0.masterIfYG = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.masterIfCbB = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.masterIfCrR = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.masterIfAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.pixFormat = ImIip_E_IM_IIP_PFMT_BAYER;
	pixfmtTbl0.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_12BITS;

	pixfmtTbl1 = gCtImIipPixfmttblBase;
	pixfmtTbl1.lineBytes.Y_G = D_IM_IIP_VGA_RAW12BIT_GLOBAL_WIDTH;
	pixfmtTbl1.lineBytes.Cb_B = 0;	// dummy
	pixfmtTbl1.lineBytes.Cr_R = 0;	// dummy
	pixfmtTbl1.lineBytes.Alpha = 0;	// dummy
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_RAW12BIT;
	pixfmtTbl1.addr.Cb_B = 0;		// dummy
	pixfmtTbl1.addr.Cr_R = 0;		// dummy
	pixfmtTbl1.addr.Alpha = 0;	// dummy
	pixfmtTbl1.masterIfYG = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.masterIfCbB = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.masterIfCrR = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.masterIfAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.pixFormat = ImIip_E_IM_IIP_PFMT_BAYER;
	pixfmtTbl1.pixDepth = ImIipDefine_D_IM_IIP_PDEPTH_12BITS;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", (kuint32)onedUnitInf,
			sizeof(ImIipParam1Dl) ));

	memset( onedUnitInf, '\0', sizeof(*onedUnitInf) );
	*onedUnitInf = gCtImIipParam1DlBase;
	onedUnitInf->ldTopcnf0.bit.WAITCONF = filter1Portid;
	onedUnitInf->PIXIDDEF.bit.IPIXID = srcPixid;
	onedUnitInf->LdTopcnf1.bit.linkUid = filter2Portid;
	onedUnitInf->ldCtl.bit.ldMode = ImIipParamEnum_E_IM_IIP_PARAM_LD_MODE_LINK;
	onedUnitInf->ldCtl.bit.SLOW = ImIipParamEnum_E_IM_IIP_PARAM_SLOW_1PIX_CYC;
	onedUnitInf->ldCtl.bit.CSEL = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_1;

	onedCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg.unitParamAddr = (ULONG)onedUnitInf;
	onedCfg.loadUnitParamFlag = 0;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "cscUnitInf = 0x%x 0x%x\n", (kuint32)cscUnitInf,
			sizeof(ImIipParamCsc) ));

	memset( cscUnitInf, '\0', sizeof(*cscUnitInf) );
	*cscUnitInf = gCtImIipParamCscBase;
	cscUnitInf->CSCTOPCNF.bit.DATACONF = srcPortid;
	cscUnitInf->CSCTOPCNF.bit.WAITCONF = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE;

	cscCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	cscCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	cscCfg.unitParamAddr = (ULONG)cscUnitInf;
	cscCfg.loadUnitParamFlag = 0;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "fltUnitInf = 0x%x 0x%x\n", (kuint32)fltUnitInf,
			sizeof(ImIipParamFlt) ));

	memset( fltUnitInf, '\0', sizeof(*fltUnitInf) );
	*fltUnitInf = gCtImIipParamFltBase;
	fltUnitInf->TDLTOPCNF.bit.DATACONF = filter1Portid;
	fltUnitInf->TDLTOPCNF.bit.waitconf0 = dstPortid;
	fltUnitInf->TDLTOPCNF.bit.waitconf1 = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE;
	fltUnitInf->PIXIDDEF.bit.IPIXID0 = srcPixid;
	fltUnitInf->PIXIDDEF.bit.IPIXID1 = srcPixid;
	fltUnitInf->tdlCtl.bit.inputMode = ImIipParamEnum_E_IM_IIP_PARAM_INPUT_MODE_SLINK;
	fltUnitInf->tdlPf.bit.pfOn = ImIipParamEnum_E_IM_IIP_PARAM_PF_ON_INVALID;
	fltUnitInf->tdlCtl.bit.CSEL = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_1;
	fltUnitInf->unitOut.bit.unitOutAD0 = ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_ISO;			// port 0
	fltUnitInf->unitOut.bit.unitOutAD1 = ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_DISABLE;		// port 0
	fltUnitInf->unitOut.bit.unitOutAD2 = ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_DISABLE;		// port 0
	fltUnitInf->ISO_TH_D[0].bit.isoUthD = 10;
	fltUnitInf->ISO_TH_D[0].bit.isoLthD = 10;
	fltUnitInf->ISO_TH_D[1].bit.isoUthD = 10;
	fltUnitInf->ISO_TH_D[1].bit.isoLthD = 10;
	fltUnitInf->ISO_TH_D[2].bit.isoUthD = 10;
	fltUnitInf->ISO_TH_D[2].bit.isoLthD = 10;
	fltUnitInf->ISO_TH_D[3].bit.isoUthD = 10;
	fltUnitInf->ISO_TH_D[3].bit.isoLthD = 10;

	spfCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	spfCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	spfCfg.unitParamAddr = (ULONG)fltUnitInf;
	spfCfg.loadUnitParamFlag = 0;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (kuint32)slUnitInf,
			sizeof(ImIipParamSts) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = gCtImIipParamStsBase;
	slUnitInf->BASE.slTopcnf0.bit.DATACONF = filter2Portid;
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;

	slCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unitParamAddr = (ULONG)slUnitInf;
	slCfg.loadUnitParamFlag = unitidBitmask;

	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)onedUnitInf, sizeof(ImIipParam1Dl) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)cscUnitInf, sizeof(ImIipParamCsc) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)fltUnitInf, sizeof(ImIipParamFlt) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)slUnitInf, sizeof(ImIipParamSts) );

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid, &pixfmtTbl0 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid, &onedCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( filter1Unitid, &cscCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( filter2Unitid, &spfCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, ImIipDefine_D_IM_IIP_ENABLE_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	im_iip_struct_on_pclk();
	CtImIipFlt_DDIM_PRINT(( "ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblLd1.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblLd1.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFlt_DDIM_PRINT(( "CSC1: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblCsc1.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblCsc1.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFlt_DDIM_PRINT(( "FLT: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblFlt.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblFlt.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFlt_DDIM_PRINT(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL0.bit.HWEN,
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL1.bit.PLDUNIT_HI,
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL1.bit.PLDUNIT_LO
			   ));
	im_iip_struct_off_pclk();

	DdArm_Dd_ARM_Dmb_Pou();

	// Need start sequence Store->CSC->1DL->FLT or Store->1DL->CSC->FLT
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( filter1Unitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start3\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start4\n" ));
	ercd = Im_IIP_Start_SWTRG( filter2Unitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, ImIipDefine_D_IM_IIP_OR_WAIT, 30 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != DriverCommon_D_DDIM_OK ) {
		CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = im_iip_main_stop( ImIip_D_IM_IIP_ABORT );
		CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return DriverCommon_D_DDIM_OK;
}

// FLT Unit SLINK 9-1-X
kint32 ct_im_iip_run_9_1( CtImIipFlt *self, const kuint32 ctNo3rd )
{
	switch( ctNo3rd ) {
		// Test-9-1-1
		case 1:
			return ct_im_iip_9_1_1( NULL );

		// Test-9-1-2
		case 2:
			return ct_im_iip_9_1_2( NULL );

		default:
			CtImIipFlt_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}

	return DriverCommon_D_DDIM_INPUT_PARAM_ERROR;
}

kint32 ct_im_iip_9_2_1( CtImIipFlt *self )
{
	kint32 ercd;
	TImIipPixfmttbl pixfmtTbl0;		// 1DL Unit input
	TImIipPixfmttbl pixfmtTbl1;		// 1DL Unit input
	TImIipPixfmttbl pixfmtTbl2;		// SL Unit output
	ImIipUnitCfg onedCfg[2];
	ImIipUnitCfg blendCfg;
	ImIipUnitCfg spfCfg;
	ImIipParam1Dl* onedUnitInf[2] = { &gCtImIipUnitParam1Dl0, &g_ct_im_iip_unit_param_1dl1 };
	ImIipParamBlend* blendUnitInf = &gCtImIipUnitParamBlend;
	ImIipParamFlt* fltUnitInf = &gCtImIipUnitParamFlt;
	ImIipParamSts* slUnitInf = &gCtImIipUnitParamSl0;
	ImIipUnitCfg slCfg;
	kuint32 waitFactorResult = 0;
	const kuint32	 waitFactor = ImIip_D_IM_IIP_INT_FACTOR_AXIERR | ImIipDefine_D_IM_IIP_INT_FACTOR_SL6END;
	const kuint32 unitidBitmask = ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD1 | ImIip_D_IM_IIP_PARAM_PLDUNIT_LD2 |
			ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_BLEND0 | ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_FLT | ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL6;
	const kuint32 pixidBitmask = ImIip_E_IM_IIP_PIXID_9 | ImIip_E_IM_IIP_PIXID_10 | ImIip_E_IM_IIP_PIXID_11;
	const ImIipEImIipUnitId srcUnitid[2] = { ImIip_E_IM_IIP_UNIT_ID_LD1, ImIip_E_IM_IIP_UNIT_ID_LD2 };
	const ImIipEImIipUnitId filter1Unitid = ImIip_E_IM_IIP_UNIT_ID_BLEND0;
	const ImIipEImIipUnitId filter2Unitid = ImIip_E_IM_IIP_UNIT_ID_FLT;
	const ImIipEImIipUnitId dstUnitid = ImIip_E_IM_IIP_UNIT_ID_SL6;
	const ImIipParamEImIipParamPortid srcPortid[2] = { ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1,
			ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD2 };
	const ImIipParamEImIipParamPortid filter1Portid[2] = { ImIipParamEnum_E_IM_IIP_PARAM_PORTID_BLEND0_P0,
			ImIipParamEnum_E_IM_IIP_PARAM_PORTID_BLEND0_P1 };
	const ImIipParamEImIipParamPortid filter2Portid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_FLT_P0;
	const ImIipParamEImIipParamPortid dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL6;
	const kuint32	 srcPixid[2] = { 9, 10 };
	const kuint32 dstPixid = 11;
	const kuint32 openResBitmask = ImIip_E_IM_IIP_OPEN_RES_CACHE1;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, CtImIip_D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if( ercd != ImIip_D_IM_IIP_OK ) {
		return ercd;
	}

	pixfmtTbl0 = gCtImIipPixfmttblBase;
	pixfmtTbl0.lineBytes.Y_G = CtImIip_D_IM_IIP_VGA_RGBA8888_GLOBAL_WIDTH;
	pixfmtTbl0.lineBytes.Cb_B = 0;	// dummy
	pixfmtTbl0.lineBytes.Cr_R = 0;	// dummy
	pixfmtTbl0.lineBytes.Alpha = 0;	// dummy
	pixfmtTbl0.addr.Y_G = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_RGBA8888;
	pixfmtTbl0.addr.Cb_B = 0;		// dummy
	pixfmtTbl0.addr.Cr_R = 0;		// dummy
	pixfmtTbl0.addr.Alpha = 0;	// dummy
	pixfmtTbl0.masterIfYG = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.masterIfCbB = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.masterIfCrR = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.masterIfAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.frameType = ImIip_E_IM_IIP_FTYPE_CHUNKY;	// RGBA8888
	pixfmtTbl0.pixFormat = ImIip_E_IM_IIP_PFMT_YCC444;		// RGBA8888
	pixfmtTbl0.alphaDepth = ImIip_E_IM_IIP_ADEPTH_8BITS;	// RGBA8888
	pixfmtTbl0.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE;			// RGBA8888

	pixfmtTbl1 = gCtImIipPixfmttblBase;
	pixfmtTbl1.lineBytes.Y_G = CtImIip_D_IM_IIP_VGA_RGBA8888_GLOBAL_WIDTH;
	pixfmtTbl1.lineBytes.Cb_B = 0;	// dummy
	pixfmtTbl1.lineBytes.Cr_R = 0;	// dummy
	pixfmtTbl1.lineBytes.Alpha = 0;	// dummy
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_4_RGBA8888;
	pixfmtTbl1.addr.Cb_B = 0;		// dummy
	pixfmtTbl1.addr.Cr_R = 0;		// dummy
	pixfmtTbl1.addr.Alpha = 0;	// dummy
	pixfmtTbl1.masterIfYG = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.masterIfCbB = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.masterIfCrR = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.masterIfAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.frameType = ImIip_E_IM_IIP_FTYPE_CHUNKY;	// RGBA8888
	pixfmtTbl1.pixFormat = ImIip_E_IM_IIP_PFMT_YCC444;		// RGBA8888
	pixfmtTbl1.alphaDepth = ImIip_E_IM_IIP_ADEPTH_8BITS;	// RGBA8888
	pixfmtTbl1.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE;			// RGBA8888

	pixfmtTbl2 = gCtImIipPixfmttblBase;
	pixfmtTbl2.lineBytes.Y_G = CtImIip_D_IM_IIP_VGA_RGBA8888_GLOBAL_WIDTH;
	pixfmtTbl2.lineBytes.Cb_B = 0;	// dummy
	pixfmtTbl2.lineBytes.Cr_R = 0;	// dummy
	pixfmtTbl2.lineBytes.Alpha = 0;	// dummy
	pixfmtTbl2.addr.Y_G = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_RGBA8888;
	pixfmtTbl2.addr.Cb_B = 0;		// dummy
	pixfmtTbl2.addr.Cr_R = 0;		// dummy
	pixfmtTbl2.addr.Alpha = 0;	// dummy
	pixfmtTbl2.masterIfYG = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl2.masterIfCbB = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl2.masterIfCrR = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl2.masterIfAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl2.frameType = ImIip_E_IM_IIP_FTYPE_CHUNKY;	// RGBA8888
	pixfmtTbl2.pixFormat = ImIip_E_IM_IIP_PFMT_YCC444;		// RGBA8888
	pixfmtTbl2.alphaDepth = ImIip_E_IM_IIP_ADEPTH_8BITS;	// RGBA8888
	pixfmtTbl2.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE;			// RGBA8888

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "onedUnitInf[0] = 0x%x 0x%x\n", (kuint32)onedUnitInf[0],
			sizeof(ImIipParam1Dl) ));

	memset( onedUnitInf[0], '\0', sizeof(*onedUnitInf[0]) );
	*onedUnitInf[0] = gCtImIipParam1DlBase;
	onedUnitInf[0]->ldTopcnf0.bit.WAITCONF = filter1Portid[0];
	onedUnitInf[0]->PIXIDDEF.bit.IPIXID = srcPixid[0];
	onedUnitInf[0]->LdTopcnf1.bit.linkUid = filter2Portid;
	onedUnitInf[0]->ldCtl.bit.ldMode = ImIipParamEnum_E_IM_IIP_PARAM_LD_MODE_LINK;
	onedUnitInf[0]->ldCtl.bit.SLOW = ImIipParamEnum_E_IM_IIP_PARAM_SLOW_1PIX_CYC;
	onedUnitInf[0]->ldCtl.bit.CSEL = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_1;

	onedCfg[0].unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg[0].chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg[0].unitParamAddr = (ULONG)onedUnitInf[0];
	onedCfg[0].loadUnitParamFlag = 0;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "onedUnitInf[1] = 0x%x 0x%x\n", (kuint32)onedUnitInf[1],
			sizeof(ImIipParam1Dl) ));

	memset( onedUnitInf[1], '\0', sizeof(*onedUnitInf[1]) );
	*onedUnitInf[1] = gCtImIipParam1DlBase;
	onedUnitInf[1]->ldTopcnf0.bit.WAITCONF = filter1Portid[1];
	onedUnitInf[1]->PIXIDDEF.bit.IPIXID = srcPixid[1];
	onedUnitInf[1]->LdTopcnf1.bit.linkUid = filter2Portid;
	onedUnitInf[1]->ldCtl.bit.ldMode = ImIipParamEnum_E_IM_IIP_PARAM_LD_MODE_LINK;
	onedUnitInf[1]->ldCtl.bit.SLOW = ImIipParamEnum_E_IM_IIP_PARAM_SLOW_1PIX_CYC;
	onedUnitInf[1]->ldCtl.bit.CSEL = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_1;

	onedCfg[1].unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg[1].chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg[1].unitParamAddr = (ULONG)onedUnitInf[1];
	onedCfg[1].loadUnitParamFlag = 0;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "blendUnitInf = 0x%x 0x%x\n", (kuint32)blendUnitInf,
			sizeof(ImIipParamBlend) ));

	memset( blendUnitInf, '\0', sizeof(*blendUnitInf) );
	*blendUnitInf = gCtImIipParamBlendBase;
	blendUnitInf->BLENDTOPCNF0.bit.waitconf0 = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE;
	blendUnitInf->BLENDTOPCNF0.bit.DATACONF_0 = srcPortid[0];
	blendUnitInf->BLENDTOPCNF1.bit.DATACONF_1 = srcPortid[1];
	blendUnitInf->BLENDCTL.bit.ALPHA_OUT = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_OUT_P0_ALPHA;
	blendUnitInf->ALPHACTL0.bit.ALPHA_SEL = ImIipParamEnum_E_IM_IIP_PARAM_ALPHA_SEL_P0_ALPHA;

	blendCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	blendCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	blendCfg.unitParamAddr = (ULONG)blendUnitInf;
	blendCfg.loadUnitParamFlag = 0;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "fltUnitInf = 0x%x 0x%x\n", (kuint32)fltUnitInf,
			sizeof(ImIipParamFlt) ));

	memset( fltUnitInf, '\0', sizeof(*fltUnitInf) );
	*fltUnitInf = gCtImIipParamFltBase;
	fltUnitInf->TDLTOPCNF.bit.DATACONF = filter1Portid[0];
	fltUnitInf->TDLTOPCNF.bit.waitconf0 = dstPortid;
	fltUnitInf->TDLTOPCNF.bit.waitconf1 = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE;
	fltUnitInf->PIXIDDEF.bit.IPIXID0 = srcPixid[0];
	fltUnitInf->PIXIDDEF.bit.IPIXID1 = srcPixid[1];
	fltUnitInf->tdlCtl.bit.inputMode = ImIipParamEnum_E_IM_IIP_PARAM_INPUT_MODE_DLINK;
	fltUnitInf->tdlPf.bit.pfOn = ImIipParamEnum_E_IM_IIP_PARAM_PF_ON_INVALID;
	fltUnitInf->tdlCtl.bit.CSEL = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_1;
	fltUnitInf->unitOut.bit.unitOutAD0 = ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_EP,		// port 0
	fltUnitInf->unitOut.bit.unitOutAD1 = ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_EP,		// port 0
	fltUnitInf->unitOut.bit.unitOutAD2 = ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_EP,		// port 0

	spfCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	spfCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	spfCfg.unitParamAddr = (ULONG)fltUnitInf;
	spfCfg.loadUnitParamFlag = 0;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (kuint32)slUnitInf,
			sizeof(ImIipParamSts) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = gCtImIipParamStsBase;
	slUnitInf->BASE.slTopcnf0.bit.DATACONF = filter2Portid;
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;

	slCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unitParamAddr = (ULONG)slUnitInf;
	slCfg.loadUnitParamFlag = unitidBitmask;

	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)onedUnitInf[0], sizeof(ImIipParam1Dl) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)onedUnitInf[1], sizeof(ImIipParam1Dl) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)blendUnitInf, sizeof(ImIipParamBlend) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)fltUnitInf, sizeof(ImIipParamFlt) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)slUnitInf, sizeof(ImIipParamSts) );

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid[0], &pixfmtTbl0 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid[1], &pixfmtTbl1 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl2 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid[0], &onedCfg[0] );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid[1], &onedCfg[1] );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( filter1Unitid, &blendCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( filter2Unitid, &spfCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, ImIipDefine_D_IM_IIP_ENABLE_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	im_iip_struct_on_pclk();
	CtImIipFlt_DDIM_PRINT(( "ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblLd1.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblLd1.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFlt_DDIM_PRINT(( "ONED[2]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.UNITINFTBL_LD2.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.UNITINFTBL_LD2.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFlt_DDIM_PRINT(( "BLEND[0]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.UNITINFTBL_BLD0.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.UNITINFTBL_BLD0.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFlt_DDIM_PRINT(( "FLT: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblFlt.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblFlt.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFlt_DDIM_PRINT(( "SL[6]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.UNITINFTBL_SL6.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.UNITINFTBL_SL6.UNITINFTBL0.bit.HWEN,
				(kuint32)ioIip.UNITINFTBL_SL6.UNITINFTBL1.bit.PLDUNIT_HI,
				(kuint32)ioIip.UNITINFTBL_SL6.UNITINFTBL1.bit.PLDUNIT_LO
			   ));
	im_iip_struct_off_pclk();

	DdArm_Dd_ARM_Dmb_Pou();

	// Need start sequence Store->CSC->1DL->FLT or Store->1DL->CSC->FLT
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( filter1Unitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start3\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid[0], ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start4\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid[1], ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start5\n" ));
	ercd = Im_IIP_Start_SWTRG( filter2Unitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, ImIipDefine_D_IM_IIP_OR_WAIT, 30 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != DriverCommon_D_DDIM_OK ) {
		CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = im_iip_main_stop( ImIip_D_IM_IIP_ABORT );
		CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return DriverCommon_D_DDIM_OK;
}

// FLT Unit DLINK 9-2-X
kint32 ct_im_iip_run_9_2( CtImIipFlt *self, const kuint32 ctNo3rd )
{
	switch( ctNo3rd ) {
		// Test-9-2-1
		case 1:
			return ct_im_iip_9_2_1( NULL );

		default:
			CtImIipFlt_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}
	return DriverCommon_D_DDIM_INPUT_PARAM_ERROR;
}

kint32 ct_im_iip_9_3_1( CtImIipFlt *self )
{
	kint32 ercd;
	TImIipPixfmttbl pixfmtTbl0;		// FLT Unit input
	TImIipPixfmttbl pixfmtTbl1;		// SL Unit input
	ImIipUnitCfg spfCfg;
	ImIipParamFlt* fltUnitInf = &gCtImIipUnitParamFlt;
	ImIipParamSts* slUnitInf = &gCtImIipUnitParamSl0;
	ImIipUnitCfg slCfg;
	kuint32 waitFactorResult = 0;
	const kuint32	 waitFactor = ImIip_D_IM_IIP_INT_FACTOR_AXIERR | ImIipDefine_D_IM_IIP_INT_FACTOR_SL6END;
	const kuint32	 unitidBitmask = ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_FLT | ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL6;
	const kuint32	 pixidBitmask = ImIip_E_IM_IIP_PIXID_10 | ImIip_E_IM_IIP_PIXID_11;
	const ImIipEImIipUnitId srcUnitid = ImIip_E_IM_IIP_UNIT_ID_FLT;
	const ImIipEImIipUnitId dstUnitid = ImIip_E_IM_IIP_UNIT_ID_SL6;
	const ImIipParamEImIipParamPortid srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_FLT_P0;
	const ImIipParamEImIipParamPortid dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL6;
	const kuint32 srcPixid = 10;
	const kuint32	 dstPixid = 11;
	const kuint32	 openResBitmask = ImIip_E_IM_IIP_OPEN_RES_CACHE1;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, CtImIip_D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if( ercd != ImIip_D_IM_IIP_OK ) {
		return ercd;
	}

	pixfmtTbl0 = gCtImIipPixfmttblBase;
	pixfmtTbl0.lineBytes.Y_G = CtImIip_D_IM_IIP_VGA_RGBA5551_GLOBAL_WIDTH;
	pixfmtTbl0.lineBytes.Cb_B = 0;	// dummy
	pixfmtTbl0.lineBytes.Cr_R = 0;	// dummy
	pixfmtTbl0.lineBytes.Alpha = 0;	// dummy
	pixfmtTbl0.addr.Y_G = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_RGBA5551;
	pixfmtTbl0.addr.Cb_B = 0;		// dummy
	pixfmtTbl0.addr.Cr_R = 0;		// dummy
	pixfmtTbl0.addr.Alpha = 0;	// dummy
	pixfmtTbl0.masterIfYG = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.masterIfCbB = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.masterIfCrR = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.masterIfAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl0.pixFormat = ImIip_E_IM_IIP_PFMT_RGBA5551;
	pixfmtTbl0.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE;

	pixfmtTbl1 = gCtImIipPixfmttblBase;
	pixfmtTbl1.lineBytes.Y_G = CtImIip_D_IM_IIP_VGA_RGBA5551_GLOBAL_WIDTH;
	pixfmtTbl1.lineBytes.Cb_B = 0;	// dummy
	pixfmtTbl1.lineBytes.Cr_R = 0;	// dummy
	pixfmtTbl1.lineBytes.Alpha = 0;	// dummy
	pixfmtTbl1.addr.Y_G = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_RGBA5551;
	pixfmtTbl1.addr.Cb_B = 0;		// dummy
	pixfmtTbl1.addr.Cr_R = 0;		// dummy
	pixfmtTbl1.addr.Alpha = 0;	// dummy
	pixfmtTbl1.masterIfYG = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.masterIfCbB = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.masterIfCrR = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.masterIfAlpha = ImIipDefine_D_IM_IIP_MASTER_IF1;
	pixfmtTbl1.pixFormat = ImIip_E_IM_IIP_PFMT_RGBA5551;
	pixfmtTbl1.alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "fltUnitInf = 0x%x 0x%x\n", (kuint32)fltUnitInf,
			sizeof(ImIipParamFlt) ));

	memset( fltUnitInf, '\0', sizeof(*fltUnitInf) );
	*fltUnitInf = gCtImIipParamFltBase;
	fltUnitInf->TDLTOPCNF.bit.DATACONF = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE;
	fltUnitInf->TDLTOPCNF.bit.waitconf0 = dstPortid;
	fltUnitInf->TDLTOPCNF.bit.waitconf1 = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE;
	fltUnitInf->PIXIDDEF.bit.IPIXID0 = srcPixid;
	fltUnitInf->PIXIDDEF.bit.IPIXID1 = srcPixid;
	fltUnitInf->tdlCtl.bit.CSEL = ImIipParamEnum_E_IM_IIP_PARAM_CSEL_1;
	fltUnitInf->unitOut.bit.unitOutAD0 = ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_EP,		// port 0
	fltUnitInf->unitOut.bit.unitOutAD1 = ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_EP,		// port 0
	fltUnitInf->unitOut.bit.unitOutAD2 = ImIipParamEnum_E_IM_IIP_PARAM_UNIT_OUT_EP,		// port 0

	spfCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	spfCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	spfCfg.unitParamAddr = (ULONG)fltUnitInf;
	spfCfg.loadUnitParamFlag = 0;

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (kuint32)slUnitInf,
			sizeof(ImIipParamSts) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = gCtImIipParamStsBase;
	slUnitInf->BASE.slTopcnf0.bit.DATACONF = srcPortid;
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;

	slCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unitParamAddr = (ULONG)slUnitInf;
	slCfg.loadUnitParamFlag = unitidBitmask;

	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)fltUnitInf, sizeof(ImIipParamFlt) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)slUnitInf, sizeof(ImIipParamSts) );

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid, &pixfmtTbl0 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid, &spfCfg );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, ImIipDefine_D_IM_IIP_ENABLE_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	im_iip_struct_on_pclk();
	CtImIipFlt_DDIM_PRINT(( "FLT: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblFlt.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblFlt.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFlt_DDIM_PRINT(( "SL[6]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.UNITINFTBL_SL6.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.UNITINFTBL_SL6.UNITINFTBL0.bit.HWEN,
				(kuint32)ioIip.UNITINFTBL_SL6.UNITINFTBL1.bit.PLDUNIT_HI,
				(kuint32)ioIip.UNITINFTBL_SL6.UNITINFTBL1.bit.PLDUNIT_LO
			   ));
	im_iip_struct_off_pclk();

	CT_Im_IIP_Print_Unitcfg_Byid( srcUnitid );
	CT_Im_IIP_Print_Unitcfg_Byid( dstUnitid );
	CT_Im_IIP_Print_Pixfmttbl_Detail( srcPixid );
	CT_Im_IIP_Print_Pixfmttbl_Detail( dstPixid );

	DdArm_Dd_ARM_Dmb_Pou();

	// Need start sequence Store->CSC->1DL->FLT or Store->1DL->CSC->FLT
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, ImIipDefine_D_IM_IIP_OR_WAIT, 30 );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != DriverCommon_D_DDIM_OK ) {
		CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = im_iip_main_stop( ImIip_D_IM_IIP_ABORT );
		CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipFlt_DDIM_PRINT(( CtImIipFlt_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return DriverCommon_D_DDIM_OK;
}

// FLT Unit NORMAL 9-3-X
kint32 ct_im_iip_run_9_3( CtImIipFlt *self, const kuint32 ctNo3rd )
{
	switch( ctNo3rd ) {
		// Test-9-3-1
		case 1:
			return ct_im_iip_9_3_1( NULL );

		default:
			CtImIipFlt_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}
	return DriverCommon_D_DDIM_INPUT_PARAM_ERROR;
}

#endif //CO_CT_IM_IIP_DISABLE

CtImIipFlt *ct_im_iip_flt_new(void)
{
	CtImIipFlt *self = k_object_new_with_private(CT_TYPE_IM_IIP_FLT, sizeof( CtImIipFltPrivate));
	return self;
}
