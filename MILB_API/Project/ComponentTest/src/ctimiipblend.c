/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 杨文
*@brief : CtImIipBlend
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
#include "ctimiipblend.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImIipBlend, ct_im_iip_blend)
#define CT_IM_IIP_BLEND_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIipBlendPrivate, CT_TYPE_IM_IIP_BLEND))


struct _CtImIipBlendPrivate
{
	int a;
};


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


/**
 * IMPL
 */
static void ct_im_iip_blend_constructor(CtImIipBlend *self)
{
	CtImIipBlendPrivate *priv = CT_IM_IIP_BLEND_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_iip_blend_destructor(CtImIipBlend *self)
{
	CtImIipBlendPrivate *priv = CT_IM_IIP_BLEND_GET_PRIVATE(self);

	priv->a = 0;
}


/**
 * PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/

// BLEND Unit 6-1-1 YCC422 U8 VGA[2]->VGA
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_blend_6_1_1: "
INT32 ct_im_iip_blend_6_1_1( VOID )
{
	INT32							ercd;
	T_IM_IIP_PIXFMTTBL				pixfmtTbl0[2];	// 1DL Unit input
	T_IM_IIP_PIXFMTTBL				pixfmtTbl1;		// SL Unit output
	T_IM_IIP_UNIT_CFG				onedCfg[2];
	T_IM_IIP_UNIT_CFG				blendCfg;
	T_IM_IIP_PARAM_1DL*				onedUnitInf[2] = { &g_ct_im_iip_unit_param_1dl0, &g_ct_im_iip_unit_param_1dl1 };
	T_IM_IIP_PARAM_BLEND*			blendUnitInf = &g_ct_im_iip_unit_param_blend;
	T_IM_IIP_PARAM_STS*				slUnitInf = &g_ct_im_iip_unit_param_sl0;
	T_IM_IIP_UNIT_CFG				slCfg;
	UINT32							waitFactorResult = 0;
	const UINT32					waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const UINT32					unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_LD2 | D_IM_IIP_PARAM_PLDUNIT_BLEND0 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const UINT32					pixidBitmask = E_IM_IIP_PIXID_3 | E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID			srcUnitid[2] = { E_IM_IIP_UNIT_ID_LD1, E_IM_IIP_UNIT_ID_LD2 };
	const E_IM_IIP_UNIT_ID			filterUnitid = E_IM_IIP_UNIT_ID_BLEND0;
	const E_IM_IIP_UNIT_ID			dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const E_IM_IIP_PARAM_PORTID		srcPortid[2] = { E_IM_IIP_PARAM_PORTID_LD1, E_IM_IIP_PARAM_PORTID_LD2 };
	const E_IM_IIP_PARAM_PORTID		filterPortid[2] = { E_IM_IIP_PARAM_PORTID_BLEND0_P0, E_IM_IIP_PARAM_PORTID_BLEND0_P1 };
	const E_IM_IIP_PARAM_PORTID		dstPortid = E_IM_IIP_PARAM_PORTID_SL2;
	const UINT32					srcPixid[2] = { 3, 4 };
	const UINT32					dstPixid = 5;
	const UINT32					openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if( ercd != D_IM_IIP_OK ) {
		return ercd;
	}

	pixfmtTbl0[0] = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl0[0].line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl0[0].line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0[0].line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0[0].line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmtTbl0[0].addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	pixfmtTbl0[0].addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmtTbl0[0].addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmtTbl0[0].addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A;

	pixfmtTbl0[1] = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl0[1].line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl0[1].line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0[1].line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0[1].line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmtTbl0[1].addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_Y;
	pixfmtTbl0[1].addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C;
	pixfmtTbl0[1].addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C;
	pixfmtTbl0[1].addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_A;

	pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "onedUnitInf[0] = 0x%x 0x%x\n", (UINT32)onedUnitInf[0], sizeof(T_IM_IIP_PARAM_1DL) ));

	memset( onedUnitInf[0], '\0', sizeof(*onedUnitInf[0]) );
	*onedUnitInf[0] = g_ct_im_iip_param_1dl_base;
	onedUnitInf[0]->LD_TOPCNF0.bit.WAITCONF = filterPortid[0];
	onedUnitInf[0]->PIXIDDEF.bit.IPIXID = srcPixid[0];

	onedCfg[0].unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg[0].chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg[0].unit_param_addr = (ULONG)onedUnitInf[0];
	onedCfg[0].load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "onedUnitInf[1] = 0x%x 0x%x\n", (UINT32)onedUnitInf[1], sizeof(T_IM_IIP_PARAM_1DL) ));

	memset( onedUnitInf[1], '\0', sizeof(*onedUnitInf[1]) );
	*onedUnitInf[1] = g_ct_im_iip_param_1dl_base;
	onedUnitInf[1]->LD_TOPCNF0.bit.WAITCONF = filterPortid[1];
	onedUnitInf[1]->PIXIDDEF.bit.IPIXID = srcPixid[1];

	onedCfg[1].unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg[1].chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg[1].unit_param_addr = (ULONG)onedUnitInf[1];
	onedCfg[1].load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "blendUnitInf = 0x%x 0x%x\n", (UINT32)blendUnitInf, sizeof(T_IM_IIP_PARAM_BLEND) ));

	*blendUnitInf = g_ct_im_iip_param_blend_base;
	blendUnitInf->BLENDTOPCNF0.bit.WAITCONF_0 = dstPortid;
	blendUnitInf->BLENDTOPCNF0.bit.DATACONF_0 = srcPortid[0];
	blendUnitInf->BLENDTOPCNF1.bit.DATACONF_1 = srcPortid[1];

	blendCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	blendCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	blendCfg.unit_param_addr = (ULONG)blendUnitInf;
	blendCfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (UINT32)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = g_ct_im_iip_param_sts_base;
	slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = filterPortid[0];
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;


	slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unit_param_addr = (ULONG)slUnitInf;
	slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)onedUnitInf[0], sizeof(T_IM_IIP_PARAM_1DL) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)onedUnitInf[1], sizeof(T_IM_IIP_PARAM_1DL) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)blendUnitInf, sizeof(T_IM_IIP_PARAM_BLEND) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	Palladium_Set_Out_Localstack( (ULONG)onedUnitInf[0], sizeof(T_IM_IIP_PARAM_1DL) );
	Palladium_Set_Out_Localstack( (ULONG)onedUnitInf[1], sizeof(T_IM_IIP_PARAM_1DL) );
	Palladium_Set_Out_Localstack( (ULONG)blendUnitInf, sizeof(T_IM_IIP_PARAM_BLEND) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid[0], &pixfmtTbl0[0] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid[1], &pixfmtTbl0[1] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid[0], &onedCfg[0] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid[1], &onedCfg[1] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( filterUnitid, &blendCfg );
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
	ercd = Im_IIP_Start_SWTRG( srcUnitid[0], D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start4\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid[1], D_IM_IIP_SWTRG_ON );
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
	Palladium_Set_Out_Localstack( (ULONG)onedUnitInf[0], sizeof(T_IM_IIP_PARAM_1DL) );
	Palladium_Set_Out_Localstack( (ULONG)onedUnitInf[1], sizeof(T_IM_IIP_PARAM_1DL) );
	Palladium_Set_Out_Localstack( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );
#endif

#if 0
	// dump UNITINF ONED[1]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( srcUnitid[0], g_get_unit_param, &param_bytes );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			Ddim_Print(( D_IM_IIP_FUNC_NAME "dump UNITINF ONED[1] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)g_get_unit_param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)g_get_unit_param, param_bytes );
		}
	}
#endif

#if 0
	// dump UNITINF ONED[2]
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( srcUnitid[1], g_get_unit_param, &param_bytes );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			Ddim_Print(( D_IM_IIP_FUNC_NAME "dump UNITINF ONED[2] %u\n", param_bytes ));
			ct_im_iip_clean_l1l2_dcache_addr( (ULONG)g_get_unit_param, param_bytes );
			Palladium_Set_Out_Localstack( (ULONG)g_get_unit_param, param_bytes );
		}
	}
#endif

#if 0
	// dump UNITINF BLEND
	{
		UINT32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM( filterUnitid, g_get_unit_param, &param_bytes );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes ));
		if( ercd == D_IM_IIP_OK ) {
			Ddim_Print(( D_IM_IIP_FUNC_NAME "dump UNITINF BLEND %u\n", param_bytes ));
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

// BLEND Unit 6-1-X
INT32 ct_im_iip_blend_run_6_1( const UINT32 ct_no_3rd )
{
	switch( ct_no_3rd ) {
		// Test-6-1-1
		case 1:
			return ct_im_iip_blend_6_1_1();

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

// BLEND Unit 6-2-1 YCC422 U14 VGA[2]->VGA
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_blend_6_2_1: "
INT32 ct_im_iip_blend_6_2_1( VOID )
{
	INT32							ercd;
	T_IM_IIP_PIXFMTTBL				pixfmtTbl0[2];	// 1DL Unit input
	T_IM_IIP_PIXFMTTBL				pixfmtTbl1;		// SL Unit output
	T_IM_IIP_UNIT_CFG				onedCfg[2];
	T_IM_IIP_UNIT_CFG				blendCfg;
	T_IM_IIP_PARAM_1DL*				onedUnitInf[2] = { &g_ct_im_iip_unit_param_1dl0, &g_ct_im_iip_unit_param_1dl1 };
	T_IM_IIP_PARAM_BLEND*			blendUnitInf = &g_ct_im_iip_unit_param_blend;
	T_IM_IIP_PARAM_STS*				slUnitInf = &g_ct_im_iip_unit_param_sl0;
	T_IM_IIP_UNIT_CFG				slCfg;
	UINT32							waitFactorResult = 0;
	const UINT32					waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL2END;
	const UINT32					unitidBitmask = D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_LD2 | D_IM_IIP_PARAM_PLDUNIT_BLEND0 | D_IM_IIP_PARAM_PLDUNIT_SL2;
	const UINT32					pixidBitmask = E_IM_IIP_PIXID_3 | E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID			srcUnitid[2] = { E_IM_IIP_UNIT_ID_LD1, E_IM_IIP_UNIT_ID_LD2 };
	const E_IM_IIP_UNIT_ID			filterUnitid = E_IM_IIP_UNIT_ID_BLEND0;
	const E_IM_IIP_UNIT_ID			dstUnitid = E_IM_IIP_UNIT_ID_SL2;
	const E_IM_IIP_PARAM_PORTID		srcPortid[2] = { E_IM_IIP_PARAM_PORTID_LD1, E_IM_IIP_PARAM_PORTID_LD2 };
	const E_IM_IIP_PARAM_PORTID		filterPortid[2] = { E_IM_IIP_PARAM_PORTID_BLEND0_P0, E_IM_IIP_PARAM_PORTID_BLEND0_P1 };
	const E_IM_IIP_PARAM_PORTID		dstPortid = E_IM_IIP_PARAM_PORTID_SL2;
	const UINT32					srcPixid[2] = { 3, 4 };
	const UINT32					dstPixid = 5;
	const UINT32					openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask, pixidBitmask, openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if( ercd != D_IM_IIP_OK ) {
		return ercd;
	}

	pixfmtTbl0[0] = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl0[0].line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH;
	pixfmtTbl0[0].line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	pixfmtTbl0[0].line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	pixfmtTbl0[0].line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH;
	pixfmtTbl0[0].addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_Y;
	pixfmtTbl0[0].addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C;
	pixfmtTbl0[0].addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_C;
	pixfmtTbl0[0].addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U16_A;
	pixfmtTbl0[0].pix_depth = D_IM_IIP_PDEPTH_16BITS;

	pixfmtTbl0[1] = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl0[1].line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH;
	pixfmtTbl0[1].line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	pixfmtTbl0[1].line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	pixfmtTbl0[1].line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH;
	pixfmtTbl0[1].addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_Y;
	pixfmtTbl0[1].addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_C;
	pixfmtTbl0[1].addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_C;
	pixfmtTbl0[1].addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U16_A;
	pixfmtTbl0[1].pix_depth = D_IM_IIP_PDEPTH_16BITS;

	pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U16_Y_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U16_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U16_A_GLOBAL_WIDTH;
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_Y;
	pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C;
	pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_C;
	pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U16_A;
	pixfmtTbl1.pix_depth = D_IM_IIP_PDEPTH_16BITS;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "onedUnitInf[0] = 0x%x 0x%x\n", (UINT32)onedUnitInf[0], sizeof(T_IM_IIP_PARAM_1DL) ));

	memset( onedUnitInf[0], '\0', sizeof(*onedUnitInf[0]) );
	*onedUnitInf[0] = g_ct_im_iip_param_1dl_base;
	onedUnitInf[0]->LD_TOPCNF0.bit.WAITCONF = filterPortid[0];
	onedUnitInf[0]->PIXIDDEF.bit.IPIXID = srcPixid[0];

	onedCfg[0].unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg[0].chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg[0].unit_param_addr = (ULONG)onedUnitInf[0];
	onedCfg[0].load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "onedUnitInf[1] = 0x%x 0x%x\n", (UINT32)onedUnitInf[1], sizeof(T_IM_IIP_PARAM_1DL) ));

	memset( onedUnitInf[1], '\0', sizeof(*onedUnitInf[1]) );
	*onedUnitInf[1] = g_ct_im_iip_param_1dl_base;
	onedUnitInf[1]->LD_TOPCNF0.bit.WAITCONF = filterPortid[1];
	onedUnitInf[1]->PIXIDDEF.bit.IPIXID = srcPixid[1];

	onedCfg[1].unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg[1].chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg[1].unit_param_addr = (ULONG)onedUnitInf[1];
	onedCfg[1].load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "blendUnitInf = 0x%x 0x%x\n", (UINT32)blendUnitInf, sizeof(T_IM_IIP_PARAM_BLEND) ));

	*blendUnitInf = g_ct_im_iip_param_blend_base;
	blendUnitInf->BLENDTOPCNF0.bit.WAITCONF_0 = dstPortid;
	blendUnitInf->BLENDTOPCNF0.bit.DATACONF_0 = srcPortid[0];
	blendUnitInf->BLENDTOPCNF1.bit.DATACONF_1 = srcPortid[1];

	blendCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	blendCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	blendCfg.unit_param_addr = (ULONG)blendUnitInf;
	blendCfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", (UINT32)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf, '\0', sizeof(*slUnitInf) );
	*slUnitInf = g_ct_im_iip_param_sts_base;
	slUnitInf->BASE.SL_TOPCNF0.bit.DATACONF = filterPortid[0];
	slUnitInf->BASE.PIXIDDEF.bit.OPIXID = dstPixid;


	slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unit_param_addr = (ULONG)slUnitInf;
	slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)onedUnitInf[0], sizeof(T_IM_IIP_PARAM_1DL) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)onedUnitInf[1], sizeof(T_IM_IIP_PARAM_1DL) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)blendUnitInf, sizeof(T_IM_IIP_PARAM_BLEND) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid[0], &pixfmtTbl0[0] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid[1], &pixfmtTbl0[1] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid, &pixfmtTbl1 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid[0], &onedCfg[0] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid[1], &onedCfg[1] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( filterUnitid, &blendCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid, &slCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, D_IM_IIP_ENABLE_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Dd_ARM_Dmb_Pou();

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid, D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( filterUnitid, D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start3\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid[0], D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start4\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid[1], D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != D_DDIM_OK ) {
		Ddim_Print(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// BLEND Unit 6-2-X
INT32 ct_im_iip_blend_run_6_2( const UINT32 ct_no_3rd )
{
	switch( ct_no_3rd ) {
		// Test-6-2-1
		case 1:
			return ct_im_iip_blend_6_2_1();

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

#endif //CO_CT_IM_IIP_DISABLE

CtImIipBlend* ct_im_iip_blend_new(void)
{
	CtImIipBlend* self = k_object_new_with_private(CT_TYPE_IM_IIP_BLEND, sizeof(CtImIipBlendPrivate));

	return self;
}