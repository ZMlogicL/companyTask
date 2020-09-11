/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 杨文
*@brief : CtImIipAfn1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimiipafn.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImIipAfn1, ct_im_iip_afn1)
#define CT_IM_IIP_AFN1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIipAfn1Private, CT_TYPE_IM_IIP_AFN1))


struct _CtImIipAfn1Private
{
	int a;
};


/**
 * IMPL
 */
static void ct_im_iip_afn1_constructor(CtImIipAfn1 *self)
{
	CtImIipAfn1Private *priv = CT_IM_IIP_AFN1_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_iip_afn1_destructor(CtImIipAfn1 *self)
{
	CtImIipAfn1Private *priv = CT_IM_IIP_AFN1_GET_PRIVATE(self);

	priv->a = 0;
}


/**
 * PUBLIC
 */

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
// AFN Unit 3-1-1 YCC422 U8 VGA->VGA D-Zoom x1.0 (simple copy)
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_afn1_3_1_1: "
INT32 ct_im_iip_afn1_3_1_1( VOID )
{
	INT32						ercd;
	T_IM_IIP_PIXFMTTBL			pixfmtTbl0;		// AFN Unit input
	T_IM_IIP_PIXFMTTBL			pixfmtTbl1;		// SL Unit output
	T_IM_IIP_UNIT_CFG			afnCfg;
	T_IM_IIP_PARAM_AFN*			afnUnitInf = &g_ct_im_iip_unit_param_afn;
	T_IM_IIP_PARAM_AFN_OPCOL_0*	afnTbl = &g_ct_im_iip_afntbl;
	T_IM_IIP_PARAM_STS*			slUnitInf = &g_ct_im_iip_unit_param_sl0;
	T_IM_IIP_UNIT_CFG			slCfg;
	UINT32						waitFactorResult = 0;
	const UINT32				waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL5END;
	const UINT32				unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_AFN0 | D_IM_IIP_PARAM_PLDUNIT_SL5;
	const UINT32				pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID		srcUnitid = E_IM_IIP_UNIT_ID_AFN0;
	const E_IM_IIP_UNIT_ID		dstUnitid = E_IM_IIP_UNIT_ID_SL5;
	const E_IM_IIP_PARAM_PORTID	srcPortid = E_IM_IIP_PARAM_PORTID_AFN0;
	const E_IM_IIP_PARAM_PORTID	dstPortid = E_IM_IIP_PARAM_PORTID_SL5;
	const UINT32				srcPixid = 4;
	const UINT32				dstPixid = 5;
	const UINT32				openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;


	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
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
#ifdef CO_CT_IM_IIP_3_1_1_FILL_TEST
	pixfmtTbl0.pix_outside_img = D_IM_IIP_OUTSIDE_IMG_FIXED_VALUE;
	pixfmtTbl0.Y_G_val_outside_img = 1;
	pixfmtTbl0.Cb_B_val_outside_img = 255;
	pixfmtTbl0.Cr_R_val_outside_img = 128;
#endif // CO_CT_IM_IIP_3_1_1_FILL_TEST

	pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnTbl = 0x%x 0x%x\n", (UINT32)afnTbl, 
							sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) ));

	memset( afnTbl, '\0', sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
#ifdef CO_CT_IM_IIP_3_1_1_FILL_TEST
	afnTbl->STAXY0.bit.STAX = M_CT_IM_IIP_AFNTBL_CALC_POS(-D_IM_IIP_VGA_WIDTH -2);
	afnTbl->STAXY0.bit.STAY = M_CT_IM_IIP_AFNTBL_CALC_POS(-D_IM_IIP_VGA_LINES -2);
#else // CO_CT_IM_IIP_3_1_1_FILL_TEST
	afnTbl->STAXY0.bit.STAX = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
	afnTbl->STAXY0.bit.STAY = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
#endif // CO_CT_IM_IIP_3_1_1_FILL_TEST
	afnTbl->D_OUT_IN_0.bit.DXX = M_CT_IM_IIP_AFNTBL_CALC_POS(1.0F);	// X increment X=1.0
	afnTbl->D_OUT_IN_0.bit.DXY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// X increment Y=0.0
	afnTbl->D_OUT_IN_0.bit.DYX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// Y increment X=0.0
	afnTbl->D_OUT_IN_0.bit.DYY = M_CT_IM_IIP_AFNTBL_CALC_POS(1.0F);	// Y increment Y=1.0
	afnTbl->SZ.bit.AFNDHSZ = D_IM_IIP_VGA_WIDTH;
	afnTbl->SZ.bit.AFNDVSZ = D_IM_IIP_VGA_LINES;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnUnitInf = 0x%x 0x%x\n", (UINT32)afnUnitInf, 
							sizeof(T_IM_IIP_PARAM_AFN) ));
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "STAX=0x%x STAY=0x%x\n", (INT32)afnTbl->STAXY0.bit.STAX, 
							(INT32)afnTbl->STAXY0.bit.STAY ));

	memset( afnUnitInf, '\0', sizeof(*afnUnitInf) );
	*afnUnitInf = g_ct_im_iip_param_afn_base;
	afnUnitInf->AFNTOPCNF.bit.WAITCONF = dstPortid;
	afnUnitInf->PIXIDEF.bit.IPIXID = srcPixid;
	afnUnitInf->AFNPA.word = (ULONG)afnTbl;
#ifdef CO_CT_IM_IIP_3_1_1_FILL_TEST
	afnUnitInf->CALMETHOD.bit.FILMD = 1;
	afnUnitInf->FILVAL0.bit.FILVALYG = 1;
	afnUnitInf->FILVAL0.bit.FILVALB = 255;
	afnUnitInf->FILVAL1.bit.FILVALR = 128;
#endif // CO_CT_IM_IIP_3_1_1_FILL_TEST

	afnCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	afnCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	afnCfg.unit_param_addr = (ULONG)afnUnitInf;
	afnCfg.load_unit_param_flag = 0;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (UINT32)slUnitInf, 
							sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = g_ct_im_iip_param_sts_base;
	slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid;
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;

	slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unit_param_addr = (ULONG)slUnitInf;
	slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	Palladium_Set_Out_Localstack( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	Palladium_Set_Out_Localstack( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid, &pixfmtTbl0 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid, &afnCfg );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, D_IM_IIP_ENABLE_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	CtImIipAfn_DDIM_PRINT(( "AFN[0]: PADRS=0x%x HWEN=%u\n",
				(UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipAfn_DDIM_PRINT(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO
			   ));
	Im_IIP_Off_Pclk();

	CT_Im_IIP_Print_Unitcfg_Byid( srcUnitid );
	CT_Im_IIP_Print_Unitcfg_Byid( dstUnitid );
	CT_Im_IIP_Print_Pixfmttbl_Detail( srcPixid );
	CT_Im_IIP_Print_Pixfmttbl_Detail( dstPixid );

	Dd_ARM_Dmb_Pou();

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, D_IM_IIP_SWTRG_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid, D_IM_IIP_SWTRG_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

#if 0
	for( UINT32 loopcnt = 0; loopcnt < 10; loopcnt++ ) {
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					IO_IIP.IZACTL1.bit.SLALE,
					IO_IIP.INTIZ0.word,
					IO_IIP.INTIZ1.word
				   ));
		DDIM_User_Dly_Tsk( 1 );
	}
#endif

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != D_DDIM_OK ) {
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	// UnitINF, AFNtblダンプ
	Palladium_Set_Out_Localstack( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	Palladium_Set_Out_Localstack( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif

#if 0
	// dump UNITINF AFN[0]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( srcUnitid, gCtImIIP_Get_Unit_Param, &param_bytes );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump UNITINF AFN[0] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
		}
	}
#endif

#if 0
	// dump UNITINF SL[2]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( dstUnitid, gCtImIIP_Get_Unit_Param, &param_bytes );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
		}
	}
#endif

#if 0
#ifndef CO_DEBUG_ON_PC
	// dump IO_IIP
	{
		ULONG regdump_addr = D_IM_IIP_REGDUMP_ADDR;
		ULONG regdump_bytes = sizeof(IO_IIP);
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump IO_IIP %u\n", regdump_bytes ));
		memcpy( (VOID*)regdump_addr, (VOID*)&IO_IIP, regdump_bytes );
		Palladium_Set_Out_Localstack( regdump_addr, regdump_bytes );
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// AFN Unit 3-1-2 YCC422 U8 VGA->VGA D-Zoom x2.0
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_afn1_3_1_2: "
INT32 ct_im_iip_afn1_3_1_2( VOID )
{
	INT32						ercd;
	T_IM_IIP_PIXFMTTBL			pixfmtTbl0;		// AFN Unit input
	T_IM_IIP_PIXFMTTBL			pixfmtTbl1;		// SL Unit output
	T_IM_IIP_UNIT_CFG			afnCfg;
	T_IM_IIP_PARAM_AFN*			afnUnitInf = &g_ct_im_iip_unit_param_afn;
	T_IM_IIP_PARAM_AFN_OPCOL_0*	afnTbl = &g_ct_im_iip_afntbl;
	T_IM_IIP_PARAM_STS*			slUnitInf = &g_ct_im_iip_unit_param_sl0;
	T_IM_IIP_UNIT_CFG			slCfg;
	UINT32						waitFactorResult = 0;
	const UINT32				waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const UINT32				unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_AFN0 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const UINT32				pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID		srcUnitid = E_IM_IIP_UNIT_ID_AFN0;
	const E_IM_IIP_UNIT_ID		dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const E_IM_IIP_PARAM_PORTID	srcPortid = E_IM_IIP_PARAM_PORTID_AFN0;
	const E_IM_IIP_PARAM_PORTID	dstPortid = E_IM_IIP_PARAM_PORTID_SL2;
	const UINT32				srcPixid = 4;
	const UINT32				dstPixid = 5;
	const UINT32				openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
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

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnTbl = 0x%x 0x%x\n", (UINT32)afnTbl, 
							sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) ));

	memset( afnTbl, '\0', sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	afnTbl->STAXY0.bit.STAX = M_CT_IM_IIP_AFNTBL_CALC_POS(D_IM_IIP_VGA_WIDTH /4);
	afnTbl->STAXY0.bit.STAY = M_CT_IM_IIP_AFNTBL_CALC_POS(D_IM_IIP_VGA_LINES /4);
	afnTbl->D_OUT_IN_0.bit.DXX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.5F);	// X increment X=0.5
	afnTbl->D_OUT_IN_0.bit.DXY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// X increment Y=0.0
	afnTbl->D_OUT_IN_0.bit.DYX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// Y increment X=0.0
	afnTbl->D_OUT_IN_0.bit.DYY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.5F);	// Y increment Y=0.5
	afnTbl->SZ.bit.AFNDHSZ = D_IM_IIP_VGA_WIDTH;
	afnTbl->SZ.bit.AFNDVSZ = D_IM_IIP_VGA_LINES;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnUnitInf = 0x%x 0x%x\n", (UINT32)afnUnitInf, 
							sizeof(T_IM_IIP_PARAM_AFN) ));

	memset( afnUnitInf, '\0', sizeof(*afnUnitInf) );
	*afnUnitInf = g_ct_im_iip_param_afn_base;
	afnUnitInf->AFNTOPCNF.bit.WAITCONF = dstPortid;
	afnUnitInf->PIXIDEF.bit.IPIXID = srcPixid;
	afnUnitInf->AFNPA.word = (ULONG)afnTbl;

	afnCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	afnCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	afnCfg.unit_param_addr = (ULONG)afnUnitInf;
	afnCfg.load_unit_param_flag = 0;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (UINT32)slUnitInf, 
							sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = g_ct_im_iip_param_sts_base;
	slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid;
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;


	slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unit_param_addr = (ULONG)slUnitInf;
	slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	Palladium_Set_Out_Localstack( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	Palladium_Set_Out_Localstack( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid, &pixfmtTbl0 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid, &afnCfg );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, D_IM_IIP_ENABLE_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	CtImIipAfn_DDIM_PRINT(( "AFN[0]: PADRS=0x%x HWEN=%u\n",
				(UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipAfn_DDIM_PRINT(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO
			   ));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, D_IM_IIP_SWTRG_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid, D_IM_IIP_SWTRG_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

#if 0
	for( UINT32 loopcnt = 0; loopcnt < 10; loopcnt++ ) {
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					IO_IIP.IZACTL1.bit.SLALE,
					IO_IIP.INTIZ0.word,
					IO_IIP.INTIZ1.word
				   ));
		DDIM_User_Dly_Tsk( 1 );
	}
#endif

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != D_DDIM_OK ) {
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	// UnitINF, AFNtblダンプ
	Palladium_Set_Out_Localstack( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	Palladium_Set_Out_Localstack( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif

#if 0
	// dump UNITINF AFN[0]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( srcUnitid, gCtImIIP_Get_Unit_Param, &param_bytes );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump UNITINF AFN[0] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
		}
	}
#endif

#if 0
	// dump UNITINF SL[2]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( dstUnitid, gCtImIIP_Get_Unit_Param, &param_bytes );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
		}
	}
#endif

#if 0
#ifndef CO_DEBUG_ON_PC
	// dump IO_IIP
	{
		ULONG regdump_addr = D_IM_IIP_REGDUMP_ADDR;
		ULONG regdump_bytes = sizeof(IO_IIP);
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump IO_IIP %u\n", regdump_bytes ));
		memcpy( (VOID*)regdump_addr, (VOID*)&IO_IIP, regdump_bytes );
		Palladium_Set_Out_Localstack( regdump_addr, regdump_bytes );
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// AFN Unit 3-1-3 Plane U16(valid 14bit) VGA->VGA D-Zoom x2.0
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_afn1_3_1_3: "
INT32 ct_im_iip_afn1_3_1_3( VOID )
{
	INT32						ercd;
	T_IM_IIP_PIXFMTTBL			pixfmtTbl0;		// AFN Unit input
	T_IM_IIP_PIXFMTTBL			pixfmtTbl1;		// SL Unit output
	T_IM_IIP_UNIT_CFG			afnCfg;
	T_IM_IIP_PARAM_AFN*			afnUnitInf = &g_ct_im_iip_unit_param_afn;
	T_IM_IIP_PARAM_AFN_OPCOL_0*	afnTbl = &g_ct_im_iip_afntbl;
	T_IM_IIP_PARAM_STS*			slUnitInf = &g_ct_im_iip_unit_param_sl0;
	T_IM_IIP_UNIT_CFG			slCfg;
	UINT32						waitFactorResult = 0;
	const UINT32				waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const UINT32				unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_AFN0 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const UINT32				pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID		srcUnitid = E_IM_IIP_UNIT_ID_AFN0;
	const E_IM_IIP_UNIT_ID		dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const E_IM_IIP_PARAM_PORTID	srcPortid = E_IM_IIP_PARAM_PORTID_AFN0;
	const E_IM_IIP_PARAM_PORTID	dstPortid = E_IM_IIP_PARAM_PORTID_SL2;
	const UINT32				srcPixid = 4;
	const UINT32				dstPixid = 5;
	const UINT32				openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if( ercd != D_IM_IIP_OK ) {
		return ercd;
	}

	pixfmtTbl0 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl0.line_bytes.Y_G = D_IM_IIP_VGA_PLANE14BIT_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Cb_B = D_IM_IIP_VGA_PLANE14BIT_GLOBAL_WIDTH;	// dummy
	pixfmtTbl0.line_bytes.Cr_R = D_IM_IIP_VGA_PLANE14BIT_GLOBAL_WIDTH;	// dummy
	pixfmtTbl0.line_bytes.Alpha = D_IM_IIP_VGA_PLANE14BIT_GLOBAL_WIDTH;	// dummy
	pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_PLANE14BIT;
	pixfmtTbl0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_PLANE14BIT;			// dummy
	pixfmtTbl0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_PLANE14BIT;			// dummy
	pixfmtTbl0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_PLANE14BIT;			// dummy
	pixfmtTbl0.pix_format = E_IM_IIP_PFMT_PLANE;
	pixfmtTbl0.pix_depth = D_IM_IIP_PDEPTH_16BITS;

	pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_PLANE14BIT_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_PLANE14BIT_GLOBAL_WIDTH;	// dummy
	pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_PLANE14BIT_GLOBAL_WIDTH;	// dummy
	pixfmtTbl1.line_bytes.Alpha = D_IM_IIP_VGA_PLANE14BIT_GLOBAL_WIDTH;	// dummy
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_PLANE14BIT;
	pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_PLANE14BIT;			// dummy
	pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_PLANE14BIT;			// dummy
	pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_PLANE14BIT;			// dummy
	pixfmtTbl1.pix_format = E_IM_IIP_PFMT_PLANE;
	pixfmtTbl1.pix_depth = D_IM_IIP_PDEPTH_16BITS;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnTbl = 0x%x 0x%x\n", (UINT32)afnTbl, 
							sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) ));

	memset( afnTbl, '\0', sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	afnTbl->STAXY0.bit.STAX = M_CT_IM_IIP_AFNTBL_CALC_POS(D_IM_IIP_VGA_WIDTH /4);
	afnTbl->STAXY0.bit.STAY = M_CT_IM_IIP_AFNTBL_CALC_POS(D_IM_IIP_VGA_LINES /4);
	afnTbl->D_OUT_IN_0.bit.DXX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.5F);	// X increment X=0.5
	afnTbl->D_OUT_IN_0.bit.DXY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// X increment Y=0.0
	afnTbl->D_OUT_IN_0.bit.DYX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// Y increment X=0.0
	afnTbl->D_OUT_IN_0.bit.DYY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.5F);	// Y increment Y=0.5
	afnTbl->SZ.bit.AFNDHSZ = D_IM_IIP_VGA_WIDTH;
	afnTbl->SZ.bit.AFNDVSZ = D_IM_IIP_VGA_LINES;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnUnitInf = 0x%x 0x%x\n", (UINT32)afnUnitInf, 
							sizeof(T_IM_IIP_PARAM_AFN) ));

	memset( afnUnitInf, '\0', sizeof(*afnUnitInf) );
	*afnUnitInf = g_ct_im_iip_param_afn_base;
	afnUnitInf->AFNTOPCNF.bit.WAITCONF = dstPortid;
	afnUnitInf->PIXIDEF.bit.IPIXID = srcPixid;
	afnUnitInf->AFNPA.word = (ULONG)afnTbl;

	afnCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	afnCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	afnCfg.unit_param_addr = (ULONG)afnUnitInf;
	afnCfg.load_unit_param_flag = 0;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (UINT32)slUnitInf, 
							sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = g_ct_im_iip_param_sts_base;
	slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid;
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;


	slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unit_param_addr = (ULONG)slUnitInf;
	slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	Palladium_Set_Out_Localstack( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	Palladium_Set_Out_Localstack( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid, &pixfmtTbl0 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid, &afnCfg );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, D_IM_IIP_ENABLE_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	CtImIipAfn_DDIM_PRINT(( "AFN[0]: PADRS=0x%x HWEN=%u\n",
				(UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipAfn_DDIM_PRINT(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO
			   ));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, D_IM_IIP_SWTRG_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid, D_IM_IIP_SWTRG_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

#if 0
	for( UINT32 loopcnt = 0; loopcnt < 10; loopcnt++ ) {
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					IO_IIP.IZACTL1.bit.SLALE,
					IO_IIP.INTIZ0.word,
					IO_IIP.INTIZ1.word
				   ));
		DDIM_User_Dly_Tsk( 1 );
	}
#endif

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != D_DDIM_OK ) {
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	// UnitINF, AFNtblダンプ
	Palladium_Set_Out_Localstack( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	Palladium_Set_Out_Localstack( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif

#if 0
	// dump UNITINF AFN[0]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( srcUnitid, gCtImIIP_Get_Unit_Param, &param_bytes );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump UNITINF AFN[0] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
		}
	}
#endif

#if 0
	// dump UNITINF SL[2]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( dstUnitid, gCtImIIP_Get_Unit_Param, &param_bytes );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
		}
	}
#endif

#if 0
#ifndef CO_DEBUG_ON_PC
	// dump IO_IIP
	{
		ULONG regdump_addr = D_IM_IIP_REGDUMP_ADDR;
		ULONG regdump_bytes = sizeof(IO_IIP);
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump IO_IIP %u\n", regdump_bytes ));
		memcpy( (VOID*)regdump_addr, (VOID*)&IO_IIP, regdump_bytes );
		Palladium_Set_Out_Localstack( regdump_addr, regdump_bytes );
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// AFN Unit 3-1-4 YCC422 U8 VGA->VGA D-Zoom x2.0 BI-Cubic
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_afn1_3_1_4: "
INT32 ct_im_iip_afn1_3_1_4( VOID )
{
	INT32						ercd;
	T_IM_IIP_PIXFMTTBL			pixfmtTbl0;		// AFN Unit input
	T_IM_IIP_PIXFMTTBL			pixfmtTbl1;		// SL Unit output
	T_IM_IIP_UNIT_CFG			afnCfg;
	T_IM_IIP_PARAM_AFN*			afnUnitInf = &g_ct_im_iip_unit_param_afn;
	T_IM_IIP_PARAM_AFN_OPCOL_0*	afnTbl = &g_ct_im_iip_afntbl;
	T_IM_IIP_PARAM_STS*			slUnitInf = &g_ct_im_iip_unit_param_sl0;
	T_IM_IIP_UNIT_CFG			slCfg;
	UINT32						waitFactorResult = 0;
	const UINT32				waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const UINT32				unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_AFN0 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const UINT32				pixidBitmask = E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID		srcUnitid = E_IM_IIP_UNIT_ID_AFN0;
	const E_IM_IIP_UNIT_ID		dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const E_IM_IIP_PARAM_PORTID	srcPortid = E_IM_IIP_PARAM_PORTID_AFN0;
	const E_IM_IIP_PARAM_PORTID	dstPortid = E_IM_IIP_PARAM_PORTID_SL2;
	const UINT32				srcPixid = 4;
	const UINT32				dstPixid = 5;
	const UINT32				openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
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

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnTbl = 0x%x 0x%x\n", (UINT32)afnTbl, 
							sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) ));

	memset( afnTbl, '\0', sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	afnTbl->STAXY0.bit.STAX = M_CT_IM_IIP_AFNTBL_CALC_POS(D_IM_IIP_VGA_WIDTH /4);
	afnTbl->STAXY0.bit.STAY = M_CT_IM_IIP_AFNTBL_CALC_POS(D_IM_IIP_VGA_LINES /4);
	afnTbl->D_OUT_IN_0.bit.DXX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.5F);	// X increment X=0.5
	afnTbl->D_OUT_IN_0.bit.DXY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// X increment Y=0.0
	afnTbl->D_OUT_IN_0.bit.DYX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// Y increment X=0.0
	afnTbl->D_OUT_IN_0.bit.DYY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.5F);	// Y increment Y=0.5
	afnTbl->SZ.bit.AFNDHSZ = D_IM_IIP_VGA_WIDTH;
	afnTbl->SZ.bit.AFNDVSZ = D_IM_IIP_VGA_LINES;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnUnitInf = 0x%x 0x%x\n", (UINT32)afnUnitInf, 
							sizeof(T_IM_IIP_PARAM_AFN) ));

	memset( afnUnitInf, '\0', sizeof(*afnUnitInf) );
	*afnUnitInf = g_ct_im_iip_param_afn_base;
	afnUnitInf->AFNTOPCNF.bit.WAITCONF = dstPortid;
	afnUnitInf->PIXIDEF.bit.IPIXID = srcPixid;
	afnUnitInf->AFNPA.word = (ULONG)afnTbl;

	// Enable BI-Cubic
	afnUnitInf->CALMETHOD.bit.ITMD = E_IM_IIP_PARAM_ITMD_BI_CUBIC;
	afnUnitInf->CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN0;
	afnUnitInf->CALMETHOD.bit.SCUB = E_IM_IIP_PARAM_SCUB_0;
	// Enable Clipping (0~255)
	afnUnitInf->OPMD.bit.OPMD0 = E_IM_IIP_PARAM_OPMD_ADD;
	afnUnitInf->OPY.bit.OPBY = 0;		// +0
	afnUnitInf->OPY.bit.OPAY = 0x10;	// x1.0
	afnUnitInf->OPB.bit.OPBB = 0;		// +0
	afnUnitInf->OPB.bit.OPAB = 0x10;	// x1.0
	afnUnitInf->OPR.bit.OPBR = 0;		// +0
	afnUnitInf->OPR.bit.OPAR = 0x10;	// x1.0
	afnUnitInf->OPA.bit.OPBA = 0;		// +0
	afnUnitInf->OPA.bit.OPAA = 0x10;	// x1.0
	afnUnitInf->CLIPLVLY.bit.CLIPLVLYH = 0xFF;
	afnUnitInf->CLIPLVLY.bit.CLIPLVLYL = 0;
	afnUnitInf->CLIPLVLB.bit.CLIPLVLBH = 0xFF;
	afnUnitInf->CLIPLVLB.bit.CLIPLVLBL = 0;
	afnUnitInf->CLIPLVLR.bit.CLIPLVLRH = 0xFF;
	afnUnitInf->CLIPLVLR.bit.CLIPLVLRL = 0;
	afnUnitInf->CLIPLVLA.bit.CLIPLVLAH = 0xFF;
	afnUnitInf->CLIPLVLA.bit.CLIPLVLAL = 0;

	afnCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	afnCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	afnCfg.unit_param_addr = (ULONG)afnUnitInf;
	afnCfg.load_unit_param_flag = 0;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (UINT32)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = g_ct_im_iip_param_sts_base;
	slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid;
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;


	slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unit_param_addr = (ULONG)slUnitInf;
	slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 1
	Palladium_Set_Out_Localstack( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	Palladium_Set_Out_Localstack( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid, &pixfmtTbl0 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid, &afnCfg );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, D_IM_IIP_ENABLE_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	CtImIipAfn_DDIM_PRINT(( "AFN[0]: PADRS=0x%x HWEN=%u\n",
				(UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_AFN0.UNITINFTBL0.bit.HWEN
			   ));
	CtImIipAfn_DDIM_PRINT(( "SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL2.bit.PADRS,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.HWEN,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_HI,
				(UINT32)IO_IIP.UNITINFTBL_SL2.UNITINFTBL1.bit.PLDUNIT_LO
			   ));
	Im_IIP_Off_Pclk();

	Dd_ARM_Dmb_Pou();

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, D_IM_IIP_SWTRG_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid, D_IM_IIP_SWTRG_ON );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

#if 0
	for( UINT32 loopcnt = 0; loopcnt < 10; loopcnt++ ) {
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					IO_IIP.IZACTL1.bit.SLALE,
					IO_IIP.INTIZ0.word,
					IO_IIP.INTIZ1.word
				   ));
		DDIM_User_Dly_Tsk( 1 );
	}
#endif

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != D_DDIM_OK ) {
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	// UnitINF, AFNtblダンプ
	Palladium_Set_Out_Localstack( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	Palladium_Set_Out_Localstack( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif

#if 0
	// dump UNITINF AFN[0]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( srcUnitid, gCtImIIP_Get_Unit_Param, &param_bytes );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump UNITINF AFN[0] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
		}
	}
#endif

#if 0
	// dump UNITINF SL[2]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( dstUnitid, gCtImIIP_Get_Unit_Param, &param_bytes );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)gCtImIIP_Get_Unit_Param, param_bytes );
		}
	}
#endif

#if 0
#ifndef CO_DEBUG_ON_PC
	// dump IO_IIP
	{
		ULONG regdump_addr = D_IM_IIP_REGDUMP_ADDR;
		ULONG regdump_bytes = sizeof(IO_IIP);
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "dump IO_IIP %u\n", regdump_bytes ));
		memcpy( (VOID*)regdump_addr, (VOID*)&IO_IIP, regdump_bytes );
		Palladium_Set_Out_Localstack( regdump_addr, regdump_bytes );
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// AFN Unit 3-1-X
INT32 ct_im_iip_afn1_run_3_1( const UINT32 ctNo3rd )
{
	switch( ctNo3rd ) {
		// Test-3-1-1
		case 1:
			return ct_im_iip_afn1_3_1_1();

		// Test-3-1-2
		case 2:
			return ct_im_iip_afn1_3_1_2();

		// Test-3-1-3
		case 3:
			return ct_im_iip_afn1_3_1_3();

		// Test-3-1-4
		case 4:
			return ct_im_iip_afn1_3_1_4();

		default:
			CtImIipAfn_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

CtImIipAfn1* ct_im_iip_afn1_new(void)
{
	CtImIipAfn1* self = k_object_new_with_private(CT_TYPE_IM_IIP_AFN1, sizeof(CtImIipAfn1Private));

	return self;
}

CtImIipAfn1* ct_im_iip_afn1_get(void)
{
	static CtImIipAfn1* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_IIP_AFN1, sizeof(CtImIipAfn1Private));
	}

	return self;
}
