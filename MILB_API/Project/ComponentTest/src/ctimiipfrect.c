/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-04
*@author            :吴雨莎
*@brief             :ctimiipfrect
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
 * @file		ct_im_iip_frect.c
 * @brief		IIP FRECT unit ct code
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


// CT header
#include "ct_im_iip.h"
//#include "ct_im_iip_frect.h"
#include "ctimiipfrect.h"

// im_iip header
#include "im_iip.h"

// MILB register header
#include "jdsiip.h"

// for Memory barrier
#include "dd_arm.h"

// for memset
#include <string.h>


K_TYPE_DEFINE_WITH_PRIVATE(CtImIipFrect, ct_im_iip_frect)
#define CT_IM_IIP_FRECT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImIipFrectPrivate, CT_TYPE_IM_IIP_FRECT))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/

#ifndef CO_CT_IM_IIP_DISABLE

#if 1
#include <stdio.h>
#undef CtImIipFrect_DDIM_PRINT
#define CtImIipFrect_DDIM_PRINT(arg)		{DDIM_User_Printf arg;}		/**< printf function inside DDIM */
#endif

// FRECT table size (for VGA 640x480)
#define CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_X_SZ	(64)
#define CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_Y_SZ	(8)
// FRECT table number (for VGA 640x480)
#define CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_X_NUM	(10)		// (640 / 64)
#define CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_Y_NUM	(60)		// (480 / 8)
#define CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_NUM	\
	(CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_X_NUM * CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_Y_NUM)

// FRECT Unit 4-1-1 YCC422 U8 VGA->VGA
#undef CtImIipFrect_D_IM_IIP_FUNC_NAME
#define CtImIipFrect_D_IM_IIP_FUNC_NAME "ct_im_iip_frect_4_1_1: "

#endif //CO_CT_IM_IIP_DISABLE


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
struct  _CtImIipFrectPrivate
{

};


/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
#ifndef CO_CT_IM_IIP_DISABLE
#ifdef __GNUC__
static IipParamFrectOpcol0	S_G_CT_IM_IIP_FRECTTBL[CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_NUM]
                             	                       __attribute__((aligned(8)));	// Needs 8bytes align
#else
static __align(8) IipParamFrectOpcol0	S_G_CT_IM_IIP_FRECTTBL[CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_NUM];
													// Needs 8bytes align
#endif
#endif //CO_CT_IM_IIP_DISABLE

/*
 *IMPL
 */
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
static void ct_im_iip_frect_constructor(CtImIipFrect *self)
{
 //CtImIipFrectPrivate *priv = CT_IM_IIP_FRECT_GET_PRIVATE(self);
}

static void ct_im_iip_frect_destructor(CtImIipFrect *self)
{
}


/*
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
kint32 ct_im_iip_frect_4_1_1( CtImIipFrect *self )
{
	kint32 ercd;
	TImIipPixfmttbl pixfmtTbl0;		// FRECT Unit input
	TImIipPixfmttbl pixfmtTbl1;		// SL Unit output
	ImIipUnitCfg frectCfg;
	ImIipParamFrect* frectUnitInf = &gCtImIipUnitParamFrect0;
	IipParamFrectOpcol0* frectTbl = S_G_CT_IM_IIP_FRECTTBL;
	ImIipParamSts* slUnitInf = &gCtImIipUnitParamSl0;
	ImIipUnitCfg slCfg;
	kuint32 waitFactorResult = 0;
	const kuint32	 waitFactor = ImIip_D_IM_IIP_INT_FACTOR_AXIERR | ImIip_D_IM_IIP_INT_FACTOR_SL2END;
	const kuint32 unitidBitmask = ImIip_D_IM_IIP_PARAM_PLDUNIT_FRECT0 | ImIip_D_IM_IIP_PARAM_PLDUNIT_SL2;
	const kuint32	 pixidBitmask = ImIip_E_IM_IIP_PIXID_4 | ImIip_E_IM_IIP_PIXID_5;
	const ImIipEImIipUnitId srcUnitid = ImIip_E_IM_IIP_UNIT_ID_FRECT0;
	const ImIipEImIipUnitId dstUnitid = ImIip_E_IM_IIP_UNIT_ID_SL2;
	const ImIipParamEImIipParamPortid srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_FRECT0;
	const ImIipParamEImIipParamPortid dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32	 srcPixid = 4;
	const kuint32	 dstPixid = 5;
	const kuint32	 openResBitmask = ImIip_E_IM_IIP_OPEN_RES_CACHE0;
	kuint32 loopcnt;
	kuint32 loopcnt2;
	kuint32 loopcnt3;

	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, CtImIip_D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
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

	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "frectTbl = 0x%x 0x%x\n", (kuint32)frectTbl,
			sizeof(IipParamFrectOpcol0) ));

	memset( frectTbl, '\0', sizeof(IipParamFrectOpcol0) * CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_NUM );
	loopcnt3 = 0;
	for( loopcnt2 = 0; loopcnt2 < CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_Y_NUM; loopcnt2++ ) {
		for( loopcnt = 0; loopcnt < CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_X_NUM; loopcnt++ ) {
			frectTbl[loopcnt3].XY0.bit.AX = loopcnt * CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_X_SZ
					*ImIipParam_D_IM_IIP_PARAM_FRECT_VAL_1_0;
			frectTbl[loopcnt3].XY0.bit.AY = loopcnt2 * CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_Y_SZ
					*ImIipParam_D_IM_IIP_PARAM_FRECT_VAL_1_0;
			frectTbl[loopcnt3].XY0.bit.BX = (loopcnt +1) * CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_X_SZ
					*ImIipParam_D_IM_IIP_PARAM_FRECT_VAL_1_0;
			frectTbl[loopcnt3].XY0.bit.BY = loopcnt2 * CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_Y_SZ
					*ImIipParam_D_IM_IIP_PARAM_FRECT_VAL_1_0;
			frectTbl[loopcnt3].XY0.bit.CX = loopcnt * CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_X_SZ
					*ImIipParam_D_IM_IIP_PARAM_FRECT_VAL_1_0;
			frectTbl[loopcnt3].XY0.bit.CY = (loopcnt2 +1) * CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_Y_SZ
					*ImIipParam_D_IM_IIP_PARAM_FRECT_VAL_1_0;
			frectTbl[loopcnt3].XY0.bit.DX = (loopcnt +1) * CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_X_SZ
					*ImIipParam_D_IM_IIP_PARAM_FRECT_VAL_1_0;
			frectTbl[loopcnt3].XY0.bit.DY = (loopcnt2 +1) * CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_Y_SZ
					*ImIipParam_D_IM_IIP_PARAM_FRECT_VAL_1_0;
			frectTbl[loopcnt3].SZ.bit.SZPOWH = ImIipParamEnum_E_IM_IIP_PARAM_SZPOWH_64;
			frectTbl[loopcnt3].SZ.bit.SZPOWV = ImIipParamEnum_E_IM_IIP_PARAM_SZPOWV_8;
			loopcnt3++;
		}
	}

	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "frectUnitInf = 0x%x 0x%x\n", (kuint32)frectUnitInf,
			sizeof(ImIipParamFrect) ));

	memset( frectUnitInf, '\0', sizeof(*frectUnitInf) );
	*frectUnitInf = gCtImIipParamFrectBase;
	frectUnitInf->FRTOPCNF.bit.WAITCONF = dstPortid;
	frectUnitInf->PIXIDEF.bit.IPIXID = srcPixid;
	frectUnitInf->PADRS.word = (ULONG)frectTbl;
	frectUnitInf->FRPCNT.bit.FRPHCNT = CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_X_NUM;
	frectUnitInf->FRPCNT.bit.FRPVCNT = CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_Y_NUM;

	frectCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	frectCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	frectCfg.unitParamAddr = (ULONG)frectUnitInf;
	frectCfg.loadUnitParamFlag = 0;

	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (kuint32)slUnitInf,
			sizeof(ImIipParamSts) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = gCtImIipParamStsBase;
	slUnitInf->BASE.slTopcnf0.bit.DATACONF = srcPortid;
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;
	slUnitInf->BASE.slPhsz.bit.PHSZ1 = CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_X_SZ;
	slUnitInf->BASE.slPvsz.bit.PVSZ1 = CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_Y_SZ;
	slUnitInf->BASE.slPhsz.bit.PHSZ0 = CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_X_SZ;
	slUnitInf->BASE.slPvsz.bit.PVSZ0 = CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_Y_SZ;

	slCfg.unitCtrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chainEnable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unitParamAddr = (ULONG)slUnitInf;
	slCfg.loadUnitParamFlag = unitidBitmask;

	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)frectTbl, sizeof(IipParamFrectOpcol0) *
			CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_NUM );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)frectUnitInf, sizeof(ImIipParamFrect) );
	CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)slUnitInf, sizeof(ImIipParamSts) );

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	palladium_test_set_out_localstack( (ULONG)frectTbl, sizeof(IipParamFrectOpcol0) *
			CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_NUM );
	palladium_test_set_out_localstack( (ULONG)frectUnitInf, sizeof(ImIipParamFrect) );
	palladium_test_set_out_localstack( (ULONG)slUnitInf, sizeof(ImIipParamSts) );
#endif /*0*/
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid, &pixfmtTbl0 );
	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid, &frectCfg );
	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, ImIipDefine_D_IM_IIP_ENABLE_ON );
	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	im_iip_struct_on_pclk();
	CtImIipFrect_DDIM_PRINT(( "FRECT[0]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.UNITINFTBL_FRC0.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.UNITINFTBL_FRC0.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipFrect_DDIM_PRINT(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL2.bit.PADRS,
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL0.bit.HWEN,
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL1.bit.PLDUNIT_HI,
				(kuint32)ioIip.unitinftblSl2.UNITINFTBL1.bit.PLDUNIT_LO
			   ));
	im_iip_struct_off_pclk();

	DdArm_Dd_ARM_Dmb_Pou();

	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

#if 0
	for( kuint32 loopcnt = 0; loopcnt < 10; loopcnt++ ) {
		CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					ioIip.IZACTL1.bit.SLALE,
					ioIip.INTIZ0.word,
					ioIip.INTIZ1.word
				   ));
		DDIM_User_Dly_Tsk( 1 );
	}
#endif /*0*/

	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, ImIipDefine_D_IM_IIP_OR_WAIT, 30 );
	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != DriverCommon_D_DDIM_OK ) {
		CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = im_iip_main_stop( ImIip_D_IM_IIP_ABORT );
		CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd,
				waitFactorResult ));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	// UnitINF, FRECTtblダンプ
	palladium_test_set_out_localstack( (ULONG)frectTbl, sizeof(IipParamFrectOpcol0) *
			CtImIipFrect_D_CT_IM_IIP_FRECT_TBL_NUM );
	palladium_test_set_out_localstack( (ULONG)frectUnitInf, sizeof(ImIipParamFrect) );
	palladium_test_set_out_localstack( (ULONG)slUnitInf, sizeof(ImIipParamSts) );
#endif /*0*/

#if 0
	// dump UNITINF FRECT0
	{
		kuint32 paramBytes;
		ercd = im_iip_static_get_unit_param( srcUnitid, gGetUnitParam, &paramBytes );
		CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, paramBytes ));
		if( ercd == ImIip_D_IM_IIP_OK ) {
			CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "dump UNITINF FRECT[0] %u\n", paramBytes ));
			CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)gGetUnitParam, paramBytes );
			palladium_test_set_out_localstack( (ULONG)gGetUnitParam, paramBytes );
		}
	}
#endif /*0*/

#if 0
	// dump UNITINF SL[2]
	{
		kuint32 paramBytes;
		ercd = im_iip_static_get_unit_param( dstUnitid, gGetUnitParam, &paramBytes );
		CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, paramBytes ));
		if( ercd == ImIip_D_IM_IIP_OK ) {
			CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", paramBytes ));
			CtImIip_CT_IM_IIP_CLEAN_L1L2_DCACHE_ADDR( (ULONG)gGetUnitParam, paramBytes );
			palladium_test_set_out_localstack( (ULONG)gGetUnitParam, paramBytes );
		}
	}
#endif /*0*/

#if 0
#ifndef CO_DEBUG_ON_PC
	// dump ioIip
	{
		ULONG regdumpAddr = CtImIip_D_IM_IIP_REGDUMP_ADDR;
		ULONG regdumpBytes = sizeof(ioIip);
		CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "dump ioIip %u\n", regdumpBytes ));
		memcpy( (void*)regdumpAddr, (void*)&ioIip, regdumpBytes );
		palladium_test_set_out_localstack( regdumpAddr, regdumpBytes );
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipFrect_DDIM_PRINT(( CtImIipFrect_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return DriverCommon_D_DDIM_OK;
}

// FRECT Unit 4-1-X
kint32 ct_im_iip_frect_run_4_1( CtImIipFrect *self, const kuint32 ctNo3rd )
{
	switch( ctNo3rd ) {
		// Test-4-1-1
		case 1:
			return ct_im_iip_frect_4_1_1( NULL );

		default:
			CtImIipFrect_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}

	return DriverCommon_D_DDIM_INPUT_PARAM_ERROR;
}

#endif //CO_CT_IM_IIP_DISABLE

CtImIipFrect *ct_im_iip_frect_new(void)
{
	CtImIipFrect *self = k_object_new_with_private(CT_TYPE_IM_IIP_FRECT, sizeof( CtImIipFrectPrivate));
	return self;
}
