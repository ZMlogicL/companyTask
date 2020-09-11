/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 杨文
*@brief : CtImIipCsc
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


// CT header
#include "ct_im_iip.h"

// im_iip header
#include "im_iip.h"
// MILB register header
#include "jdsiip.h"
// for Memory barrier
#include "dd_arm.h"
// for memset
#include <string.h>
#include "ctimiipcsc.h"


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#ifndef CO_CT_IM_IIP_DISABLE

#if 1
#include <stdio.h>
#undef Ddim_Print
#define Ddim_Print(arg)		{DDIM_User_Printf arg;}		/**< printf function inside DDIM */
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
// Nothing Special


K_TYPE_DEFINE_WITH_PRIVATE(CtImIipCsc, ct_im_iip_csc)
#define CT_IM_IIP_CSC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIipCscPrivate, CT_TYPE_IM_IIP_CSC))

struct _CtImIipCscPrivate
{
	int a;
};


/**
 * IMPL
 */
static void ct_im_iip_csc_constructor(CtImIipCsc *self)
{
	CtImIipCscPrivate *priv = CT_IM_IIP_CSC_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_iip_csc_destructor(CtImIipCsc *self)
{
	CtImIipCscPrivate *priv = CT_IM_IIP_CSC_GET_PRIVATE(self);

	priv->a = 0;
}


/**
 * PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/

// CSC Unit 7-1-1 YCC422 U8 VGA->VGA not convert
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_csc_7_1_1: "
INT32 ct_im_iip_csc_7_1_1( VOID )
{
	INT32							ercd;
	T_IM_IIP_PIXFMTTBL				pixfmtTbl0;		// 1DL Unit input
	T_IM_IIP_PIXFMTTBL				pixfmtTbl1;		// SL Unit output
	T_IM_IIP_UNIT_CFG				onedCfg;
	T_IM_IIP_UNIT_CFG				cscCfg;
	T_IM_IIP_PARAM_1DL*				onedUnitInf = &g_ct_im_iip_unit_param_1dl0;
	T_IM_IIP_PARAM_CSC*				cscUnitInf = &g_ct_im_iip_unit_param_csc;
	T_IM_IIP_PARAM_STS*				slUnitInf = &g_ct_im_iip_unit_param_sl0;
	T_IM_IIP_UNIT_CFG				slCfg;
	UINT32							waitFactorResult = 0;
	const UINT32					waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const UINT32					unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_CSC0 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const UINT32					pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID			srcUnitid = E_IM_IIP_UNIT_ID_LD1;
	const E_IM_IIP_UNIT_ID			filterUnitid = E_IM_IIP_UNIT_ID_CSC0;
	const E_IM_IIP_UNIT_ID			dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const E_IM_IIP_PARAM_PORTID		filterPortid = E_IM_IIP_PARAM_PORTID_CSC0;
	const E_IM_IIP_PARAM_PORTID		srcPortid = E_IM_IIP_PARAM_PORTID_LD1;
	const E_IM_IIP_PARAM_PORTID		dstPortid = E_IM_IIP_PARAM_PORTID_SL2;
	const UINT32					srcPixid = 4;
	const UINT32					dstPixid = 5;
	const UINT32					openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if( ercd != D_IM_IIP_OK ) {
		return ercd;
	}

	pixfmtTbl0 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl0.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	pixfmtTbl0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmtTbl0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmtTbl0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A;

	pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", (UINT32)onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL) ));

	memset( onedUnitInf, '\0', sizeof(*onedUnitInf) );
	*onedUnitInf = g_ct_im_iip_param_1dl_base;
	onedUnitInf->LD_TOPCNF0.bit.WAITCONF = filterPortid;
	onedUnitInf->PIXIDDEF.bit.IPIXID = srcPixid;

	onedCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg.unit_param_addr = (ULONG)onedUnitInf;
	onedCfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "cscUnitInf = 0x%x 0x%x\n", (UINT32)cscUnitInf, sizeof(T_IM_IIP_PARAM_CSC) ));

	memset( cscUnitInf, '\0', sizeof(*cscUnitInf) );
	*cscUnitInf = g_ct_im_iip_param_csc_base;
	cscUnitInf->CSCTOPCNF.bit.DATACONF = srcPortid;
	cscUnitInf->CSCTOPCNF.bit.WAITCONF = dstPortid;

	cscCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	cscCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	cscCfg.unit_param_addr = (ULONG)cscUnitInf;
	cscCfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (UINT32)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = g_ct_im_iip_param_sts_base;
	slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = filterPortid;
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;

	slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unit_param_addr = (ULONG)slUnitInf;
	slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)cscUnitInf, sizeof(T_IM_IIP_PARAM_CSC) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	Palladium_Set_Out_Localstack( (ULONG)onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL) );
	Palladium_Set_Out_Localstack( (ULONG)cscUnitInf, sizeof(T_IM_IIP_PARAM_CSC) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid, &pixfmtTbl0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid, &onedCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( filterUnitid, &cscCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, D_IM_IIP_ENABLE_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	Ddim_Print(( "ONED[1]: PADRS=0x%x HWEN=%u\n",
				(UINT32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL0.bit.HWEN
			   ));
	Ddim_Print(( "CSC0: PADRS=0x%x HWEN=%u\n",
				(UINT32)IO_IIP.UNITINFTBL_CSC0.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_CSC0.UNITINFTBL0.bit.HWEN
			   ));
	Ddim_Print(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO
			   ));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( filterUnitid, D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start3\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid, D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

#if 0
	for( UINT32 loopcnt = 0; loopcnt < 10; loopcnt++ ) {
		Ddim_Print(( D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					IO_IIP.IZACTL1.bit.SLALE,
					IO_IIP.INTIZ0.word,
					IO_IIP.INTIZ1.word
				   ));
		DDIM_User_Dly_Tsk( 1 );
	}
#endif

	Ddim_Print(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	// UnitINFダンプ
	Palladium_Set_Out_Localstack( (ULONG)onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL) );
	Palladium_Set_Out_Localstack( (ULONG)cscUnitInf, sizeof(T_IM_IIP_PARAM_CSC) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif

#if 0
	// dump UNITINF ONED[1]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( srcUnitid, g_get_unit_param, &param_bytes );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			Ddim_Print(( D_IM_IIP_FUNC_NAME "dump UNITINF ONED[1] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)g_get_unit_param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)g_get_unit_param, param_bytes );
		}
	}
#endif

#if 0
	// dump UNITINF CSC
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( filterUnitid, g_get_unit_param, &param_bytes );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			Ddim_Print(( D_IM_IIP_FUNC_NAME "dump UNITINF ONED[1] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)g_get_unit_param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)g_get_unit_param, param_bytes );
		}
	}
#endif

#if 0
	// dump UNITINF SL[2]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( dstUnitid, g_get_unit_param, &param_bytes );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			Ddim_Print(( D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)g_get_unit_param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)g_get_unit_param, param_bytes );
		}
	}
#endif

#if 0
#ifndef CO_DEBUG_ON_PC
	// dump IO_IIP
	{
		ULONG regdump_addr = D_IM_IIP_REGDUMP_ADDR;
		ULONG regdump_bytes = sizeof(IO_IIP);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "dump IO_IIP %u\n", regdump_bytes ));
		memcpy( (VOID*)regdump_addr, (VOID*)&IO_IIP, regdump_bytes );
		Palladium_Set_Out_Localstack( regdump_addr, regdump_bytes );
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// CSC Unit 7-1-2 YCC422 U8 VGA->VGA Y->Cb, Cb->Cr, Cr->Y
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_csc_7_1_2: "
INT32 ct_im_iip_csc_7_1_2( VOID )
{
	INT32							ercd;
	T_IM_IIP_PIXFMTTBL				pixfmtTbl0;		// 1DL Unit input
	T_IM_IIP_PIXFMTTBL				pixfmtTbl1;		// SL Unit output
	T_IM_IIP_UNIT_CFG				onedCfg;
	T_IM_IIP_UNIT_CFG				cscCfg;
	T_IM_IIP_PARAM_1DL*				onedUnitInf = &g_ct_im_iip_unit_param_1dl0;
	T_IM_IIP_PARAM_CSC*				cscUnitInf = &g_ct_im_iip_unit_param_csc;
	T_IM_IIP_PARAM_STS*				slUnitInf = &g_ct_im_iip_unit_param_sl0;
	T_IM_IIP_UNIT_CFG				slCfg;
	UINT32							waitFactorResult = 0;
	const UINT32					waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const UINT32					unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_CSC0 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const UINT32					pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID			srcUnitid = E_IM_IIP_UNIT_ID_LD1;
	const E_IM_IIP_UNIT_ID			filterUnitid = E_IM_IIP_UNIT_ID_CSC0;
	const E_IM_IIP_UNIT_ID			dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const E_IM_IIP_PARAM_PORTID		filterPortid = E_IM_IIP_PARAM_PORTID_CSC0;
	const E_IM_IIP_PARAM_PORTID		srcPortid = E_IM_IIP_PARAM_PORTID_LD1;
	const E_IM_IIP_PARAM_PORTID		dstPortid = E_IM_IIP_PARAM_PORTID_SL2;
	const UINT32					srcPixid = 4;
	const UINT32					dstPixid = 5;
	const UINT32					openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if( ercd != D_IM_IIP_OK ) {
		return ercd;
	}

	pixfmtTbl0 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl0.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	pixfmtTbl0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmtTbl0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmtTbl0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A;

	pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", (UINT32)onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL) ));

	memset( onedUnitInf, '\0', sizeof(*onedUnitInf) );
	*onedUnitInf = g_ct_im_iip_param_1dl_base;
	onedUnitInf->LD_TOPCNF0.bit.WAITCONF = filterPortid;
	onedUnitInf->PIXIDDEF.bit.IPIXID = srcPixid;

	onedCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg.unit_param_addr = (ULONG)onedUnitInf;
	onedCfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "cscUnitInf = 0x%x 0x%x\n", (UINT32)cscUnitInf, sizeof(T_IM_IIP_PARAM_CSC) ));

	memset( cscUnitInf, '\0', sizeof(*cscUnitInf) );
	*cscUnitInf = g_ct_im_iip_param_csc_base;
	cscUnitInf->CSCTOPCNF.bit.DATACONF = srcPortid;
	cscUnitInf->CSCTOPCNF.bit.WAITCONF = dstPortid;
	cscUnitInf->CSCK[0].bit.CSCK_0 = 0;
	cscUnitInf->CSCK[0].bit.CSCK_1 = 0;
	cscUnitInf->CSCK[0].bit.CSCK_2 = (LONG)(1.0F * 0x1000);
	cscUnitInf->CSCK[0].bit.CSCK_3 = 0;
	cscUnitInf->CSCK[1].bit.CSCK_0 = (LONG)(1.0F * 0x1000);
	cscUnitInf->CSCK[1].bit.CSCK_1 = 0;
	cscUnitInf->CSCK[1].bit.CSCK_2 = 0;
	cscUnitInf->CSCK[1].bit.CSCK_3 = 0;
	cscUnitInf->CSCK[2].bit.CSCK_0 = 0;
	cscUnitInf->CSCK[2].bit.CSCK_1 = (LONG)(1.0F * 0x1000);
	cscUnitInf->CSCK[2].bit.CSCK_2 = 0;
	cscUnitInf->CSCK[2].bit.CSCK_3 = 0;
	cscUnitInf->CSCK[3].bit.CSCK_0 = 0;
	cscUnitInf->CSCK[3].bit.CSCK_1 = 0;
	cscUnitInf->CSCK[3].bit.CSCK_2 = 0;
	cscUnitInf->CSCK[3].bit.CSCK_3 = 0;

	cscCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	cscCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	cscCfg.unit_param_addr = (ULONG)cscUnitInf;
	cscCfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (UINT32)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = g_ct_im_iip_param_sts_base;
	slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = filterPortid;
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;

	slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unit_param_addr = (ULONG)slUnitInf;
	slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)cscUnitInf, sizeof(T_IM_IIP_PARAM_CSC) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	Palladium_Set_Out_Localstack( (ULONG)onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL) );
	Palladium_Set_Out_Localstack( (ULONG)cscUnitInf, sizeof(T_IM_IIP_PARAM_CSC) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid, &pixfmtTbl0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid, &onedCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( filterUnitid, &cscCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, D_IM_IIP_ENABLE_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	Ddim_Print(( "ONED[1]: PADRS=0x%x HWEN=%u\n",
				(UINT32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_LD1.UNITINFTBL0.bit.HWEN
			   ));
	Ddim_Print(( "CSC0: PADRS=0x%x HWEN=%u\n",
				(UINT32)IO_IIP.UNITINFTBL_CSC0.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_CSC0.UNITINFTBL0.bit.HWEN
			   ));
	Ddim_Print(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO
			   ));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( filterUnitid, D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start3\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid, D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

#if 0
	for( UINT32 loopcnt = 0; loopcnt < 10; loopcnt++ ) {
		Ddim_Print(( D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					IO_IIP.IZACTL1.bit.SLALE,
					IO_IIP.INTIZ0.word,
					IO_IIP.INTIZ1.word
				   ));
		DDIM_User_Dly_Tsk( 1 );
	}
#endif

	Ddim_Print(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	// UnitINFダンプ
	Palladium_Set_Out_Localstack( (ULONG)onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL) );
	Palladium_Set_Out_Localstack( (ULONG)cscUnitInf, sizeof(T_IM_IIP_PARAM_CSC) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif

#if 0
	// dump UNITINF ONED[1]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( srcUnitid, g_get_unit_param, &param_bytes );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			Ddim_Print(( D_IM_IIP_FUNC_NAME "dump UNITINF ONED[1] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)g_get_unit_param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)g_get_unit_param, param_bytes );
		}
	}
#endif

#if 0
	// dump UNITINF CSC
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( filterUnitid, g_get_unit_param, &param_bytes );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			Ddim_Print(( D_IM_IIP_FUNC_NAME "dump UNITINF ONED[1] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)g_get_unit_param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)g_get_unit_param, param_bytes );
		}
	}
#endif

#if 0
	// dump UNITINF SL[2]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( dstUnitid, g_get_unit_param, &param_bytes );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			Ddim_Print(( D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)g_get_unit_param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)g_get_unit_param, param_bytes );
		}
	}
#endif

#if 0
#ifndef CO_DEBUG_ON_PC
	// dump IO_IIP
	{
		ULONG regdump_addr = D_IM_IIP_REGDUMP_ADDR;
		ULONG regdump_bytes = sizeof(IO_IIP);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "dump IO_IIP %u\n", regdump_bytes ));
		memcpy( (VOID*)regdump_addr, (VOID*)&IO_IIP, regdump_bytes );
		Palladium_Set_Out_Localstack( regdump_addr, regdump_bytes );
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// CSC Unit 7-1-X
INT32 ct_im_iip_csc_run_7_1( const UINT32 ctNo3rd )
{
	switch( ctNo3rd ) {
		// Test-7-1-1
		case 1:
			return ct_im_iip_csc_7_1_1();

		// Test-7-1-2
		case 2:
			return ct_im_iip_csc_7_1_2();

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}
#endif //CO_CT_IM_IIP_DISABLE

CtImIipCsc* ct_im_iip_csc_new(void)
{
	CtImIipCsc* self = k_object_new_with_private(CT_TYPE_IM_IIP_CSC, sizeof(CtImIipCscPrivate));

	return self;
}