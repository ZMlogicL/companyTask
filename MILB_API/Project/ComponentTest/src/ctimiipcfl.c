/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 杨文
*@brief : CtImIipCfl
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

// Memory barrier
#include "dd_arm.h"

// for memset
#include <string.h>
#include "ctimiipcfl.h"


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


K_TYPE_DEFINE_WITH_PRIVATE(CtImIipCfl, ct_im_iip_cfl)
#define CT_IM_IIP_CFL_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIipCflPrivate, CT_TYPE_IM_IIP_CFL))


struct _CtImIipCflPrivate
{
   int a;
};


/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
static const T_IM_IIP_PARAM_CFLOW S_G_CT_IM_IIP_PARAM_CFL_BASE = {
	.header0.bit.BeginningAddress = 0x0000,
	.header0.bit.WordLength = 9,
	.header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET,
//	.CFTOPCONF.bit.DATACONF_0 = ,		// set later
//	.CFTOPCONF.bit.DATACONF_1 = ,		// set later
	.DIFF_PREWAIT.bit.DIFF_PREWAIT = 8192,		// About. (ImgCache 32kByte /4)
	.DIFF_POSTWAIT.bit.DIFF_POSTWAIT = 64 * 8,	// About. (PHSZ1 x PVSZ1)
	.MAGPOW.bit.PREMAG = 0x10,
	.MAGPOW.bit.POSTMAG = 0x10,
	.CFMODE.bit.SPC_ON = 0,
};
#ifdef __GNUC__
// Needs 8bytes align
static T_IM_IIP_PARAM_CFLOW			S_G_CT_IM_IIP_UNIT_PARAM_CFL __attribute__((aligned(8)));	
#else
// Needs 8bytes align
static __align(8) T_IM_IIP_PARAM_CFLOW			S_G_CT_IM_IIP_UNIT_PARAM_CFL;	
#endif


/**
 * IMPL
 */
static void ct_im_iip_cfl_constructor(CtImIipCfl *self)
{
	CtImIipCflPrivate *priv = CT_IM_IIP_CFL_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_iip_cfl_destructor(CtImIipCfl *self)
{
	CtImIipCflPrivate *priv = CT_IM_IIP_CFL_GET_PRIVATE(self);

	priv->a = 0;
}


/**
 * PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/

// CFL Unit 12-1-1
// LD(YCC422)->SL(S)->LD->SL(S)
// +----+    +----+      +----+    +----+
// |LD0 |----|SL0 |------|LD1 |----|SL3 |
// +----+    +----+      +----+    +----+
//           D=LD0                 D=LD1
// W=SL0     W=CFL0_0    W=SL3     W=CFL0_1
// pix=3     pix=4       pix=4     pix=5
//              |                     |
//              |        +----+       |
//              +--------|CFL0|-------+
//                       +----+
//                    D0=SL0 D1=SL3
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_cfl_12_1_1: "
INT32 ct_im_iip_cfl_12_1_1( VOID )
{
	INT32							ercd;
	T_IM_IIP_PIXFMTTBL				pixfmtTbl0;	// 1DL0 Unit input
	T_IM_IIP_PIXFMTTBL				pixfmtTbl1;	// SL0 Unit output / 1DL1 Unit input
	T_IM_IIP_PIXFMTTBL				pixfmtTbl2;	// SL3 Unit output
	T_IM_IIP_UNIT_CFG				onedCfg[2];
	T_IM_IIP_UNIT_CFG				slCfg[2];
	T_IM_IIP_UNIT_CFG				cflCfg;
	T_IM_IIP_PARAM_1DL*				onedUnitInf[2] = { &g_ct_im_iip_unit_param_1dl0, &g_ct_im_iip_unit_param_1dl1 };
	T_IM_IIP_PARAM_STS*				slUnitInf[2] = { &g_ct_im_iip_unit_param_sl0, &g_ct_im_iip_unit_param_sl1 };
	T_IM_IIP_PARAM_CFLOW*			cflUnitInf = &S_G_CT_IM_IIP_UNIT_PARAM_CFL;
	UINT32							waitFactorResult = 0;
	const UINT32					waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL3END;
	const UINT32					pixidBitmask = E_IM_IIP_PIXID_3 | E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID			srcUnitid[2] = { E_IM_IIP_UNIT_ID_LD0, E_IM_IIP_UNIT_ID_LD1 };
	const E_IM_IIP_PARAM_PORTID		srcPortid[2] = { E_IM_IIP_PARAM_PORTID_LD0, E_IM_IIP_PARAM_PORTID_LD1 };
	const E_IM_IIP_UNIT_ID			cflUnitid    = E_IM_IIP_UNIT_ID_CFL0;
	const E_IM_IIP_PARAM_PORTID		cflPortid[2] = { E_IM_IIP_PARAM_PORTID_CFL0_P0, E_IM_IIP_PARAM_PORTID_CFL0_P1 };
	const E_IM_IIP_UNIT_ID			dstUnitid[2] = { E_IM_IIP_UNIT_ID_SL2, E_IM_IIP_UNIT_ID_SL3 };
	const E_IM_IIP_PARAM_PORTID		dstPortid[2] = { E_IM_IIP_PARAM_PORTID_SL2, E_IM_IIP_PARAM_PORTID_SL3 };
	const UINT32					unitidBitmask[2] = { D_IM_IIP_PARAM_PLDUNIT_LD0 | D_IM_IIP_PARAM_PLDUNIT_SL2,
														  D_IM_IIP_PARAM_PLDUNIT_LD1 | D_IM_IIP_PARAM_PLDUNIT_SL3 };
	const UINT32					srcPixid[2] = { 3, 4 };
	const UINT32					dstPixid[2] = { 4, 5 };
	const UINT32					openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask[0] | unitidBitmask[1] | D_IM_IIP_PARAM_PLDUNIT_CFL0, pixidBitmask,
							  openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
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
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_Y;
	pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_C;
	pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_C;
	pixfmtTbl1.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_2_YCC422_U8_A;

	pixfmtTbl2 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl2.line_bytes.Y_G = D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl2.line_bytes.Cb_B = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl2.line_bytes.Cr_R = D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl2.line_bytes.Alpha = D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmtTbl2.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	pixfmtTbl2.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl2.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	pixfmtTbl2.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "onedUnitInf[0] = 0x%x 0x%x\n", (UINT32)onedUnitInf[0], 
				 sizeof(T_IM_IIP_PARAM_1DL) ));

	memset( onedUnitInf[0], '\0', sizeof(*onedUnitInf[0]) );
	*onedUnitInf[0] = g_ct_im_iip_param_1dl_base;
	onedUnitInf[0]->LD_TOPCNF0.bit.WAITCONF = dstPortid[0];
	onedUnitInf[0]->PIXIDDEF.bit.IPIXID = srcPixid[0];
	onedUnitInf[0]->LD_CTL.bit.SLOW = E_IM_IIP_PARAM_SLOW_1PIX_CYC;


	onedCfg[0].unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg[0].chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg[0].unit_param_addr = (ULONG)onedUnitInf[0];
	onedCfg[0].load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "onedUnitInf[1] = 0x%x 0x%x\n", (UINT32)onedUnitInf[1],
				 sizeof(T_IM_IIP_PARAM_1DL) ));

	memset( onedUnitInf[1], '\0', sizeof(*onedUnitInf[1]) );
	*onedUnitInf[1] = g_ct_im_iip_param_1dl_base;
	onedUnitInf[1]->LD_TOPCNF0.bit.WAITCONF = dstPortid[1];
	onedUnitInf[1]->PIXIDDEF.bit.IPIXID = srcPixid[1];
	onedUnitInf[1]->LD_CTL.bit.SLOW = E_IM_IIP_PARAM_SLOW_1PIX_CYC;

	onedCfg[1].unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg[1].chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg[1].unit_param_addr = (ULONG)onedUnitInf[1];
	onedCfg[1].load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "cflUnitInf = 0x%x 0x%x\n", (UINT32)cflUnitInf, sizeof(T_IM_IIP_PARAM_CFLOW) ));

	memset( cflUnitInf, '\0', sizeof(*cflUnitInf) );
	*cflUnitInf = S_G_CT_IM_IIP_PARAM_CFL_BASE;
	cflUnitInf->CFTOPCONF.bit.DATACONF_0 = dstPortid[0];
	cflUnitInf->CFTOPCONF.bit.DATACONF_1 = dstPortid[1];

	cflCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	cflCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	cflCfg.unit_param_addr = (ULONG)cflUnitInf;
	cflCfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "slUnitInf[0] = 0x%x 0x%x\n", (UINT32)slUnitInf[0], sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf[0], '\0', sizeof(*slUnitInf[0]) );
	*slUnitInf[0] = g_ct_im_iip_param_sts_base;
	slUnitInf[0]->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid[0];
	slUnitInf[0]->BASE.SL_TOPCNF0.bit.WAITCONF = cflPortid[0];
	slUnitInf[0]->BASE.PIXIDDEF.bit.OPIXID = dstPixid[0];

	slCfg[0].unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg[0].chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg[0].unit_param_addr = (ULONG)slUnitInf[0];
	slCfg[0].load_unit_param_flag = unitidBitmask[0];

	Ddim_Print(( D_IM_IIP_FUNC_NAME "slUnitInf[1] = 0x%x 0x%x\n", (UINT32)slUnitInf[1], sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf[1], '\0', sizeof(*slUnitInf[1]) );
	*slUnitInf[1] = g_ct_im_iip_param_sts_base;
	slUnitInf[1]->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid[1];
	slUnitInf[1]->BASE.SL_TOPCNF0.bit.WAITCONF = cflPortid[1];
	slUnitInf[1]->BASE.PIXIDDEF.bit.OPIXID = dstPixid[1];

	slCfg[1].unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg[1].chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg[1].unit_param_addr = (ULONG)slUnitInf[1];
	slCfg[1].load_unit_param_flag = unitidBitmask[1];

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)onedUnitInf[0], sizeof(T_IM_IIP_PARAM_1DL) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)onedUnitInf[1], sizeof(T_IM_IIP_PARAM_1DL) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)cflUnitInf, sizeof(T_IM_IIP_PARAM_CFLOW) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf[0], sizeof(T_IM_IIP_PARAM_STS) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf[1], sizeof(T_IM_IIP_PARAM_STS) );

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid[0], &pixfmtTbl0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid[1], &pixfmtTbl1 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid[0], &pixfmtTbl1 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid[1], &pixfmtTbl2 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid[0], &onedCfg[0] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid[1], &onedCfg[1] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid[0], &slCfg[0] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid[1], &slCfg[1] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( cflUnitid, &cflCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, D_IM_IIP_ENABLE_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Dd_ARM_Dmb_Pou();

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( cflUnitid, D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid[0], D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start3\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid[1], D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start4\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid[0], D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start5\n" ));
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
	ercd = Im_IIP_Close_SWTRG( unitidBitmask[0] | unitidBitmask[1] | D_IM_IIP_PARAM_PLDUNIT_CFL0,
							   pixidBitmask, openResBitmask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// CFL Unit 12-1-2
// LD(YCC422)->SL(S)->LD->SL(S)
// +----+    +----+      +----+    +----+
// |LD2 |----|SL1 |------|FLT |----|SL4 |
// +----+    +----+      +----+    +----+
//           D=LD2                 D=FLT
// W=SL0     W=CFL0_0    W=SL4     W=CFL0_1
// pix=3     pix=4       pix=4     pix=5
//              |                     |
//              |        +----+       |
//              +--------|CFL0|-------+
//                       +----+
//                    D0=SL0 D1=SL3
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_cfl_12_1_2: "
INT32 ct_im_iip_cfl_12_1_2( VOID )
{
	INT32							ercd;
	T_IM_IIP_PIXFMTTBL				pixfmtTbl0;	// 1DL0 Unit input
	T_IM_IIP_PIXFMTTBL				pixfmtTbl1;	// SL0 Unit output / 1DL1 Unit input
	T_IM_IIP_PIXFMTTBL				pixfmtTbl2;	// SL3 Unit output
	T_IM_IIP_UNIT_CFG				onedCfg;
	T_IM_IIP_UNIT_CFG				slCfg[2];
	T_IM_IIP_UNIT_CFG				fltCfg;
	T_IM_IIP_UNIT_CFG				cflCfg;
	T_IM_IIP_PARAM_1DL*				onedUnitInf = &g_ct_im_iip_unit_param_1dl0;
	T_IM_IIP_PARAM_FLT*				fltUnitInf = &g_ct_im_iip_unit_param_flt;
	T_IM_IIP_PARAM_STS*				slUnitInf[2] = { &g_ct_im_iip_unit_param_sl0, &g_ct_im_iip_unit_param_sl1 };
	T_IM_IIP_PARAM_CFLOW*			cflUnitInf = &S_G_CT_IM_IIP_UNIT_PARAM_CFL;
	UINT32							waitFactorResult = 0;
	const UINT32					waitFactor = D_IM_IIP_INT_FACTOR_AXIERR | D_IM_IIP_INT_FACTOR_SL4END;
	const UINT32					pixidBitmask =   E_IM_IIP_PIXID_3 | E_IM_IIP_PIXID_4 | E_IM_IIP_PIXID_5;
	const E_IM_IIP_UNIT_ID			srcUnitid[2] = { E_IM_IIP_UNIT_ID_LD2, E_IM_IIP_UNIT_ID_FLT };
	const E_IM_IIP_PARAM_PORTID		srcPortid[2] = { E_IM_IIP_PARAM_PORTID_LD2, E_IM_IIP_PARAM_PORTID_FLT_P0 };
	const E_IM_IIP_UNIT_ID			cflUnitid    =   E_IM_IIP_UNIT_ID_CFL0;
	const E_IM_IIP_PARAM_PORTID		cflPortid[2] = { E_IM_IIP_PARAM_PORTID_CFL0_P0, E_IM_IIP_PARAM_PORTID_CFL0_P1 };
	const E_IM_IIP_UNIT_ID			dstUnitid[2] = { E_IM_IIP_UNIT_ID_SL2, E_IM_IIP_UNIT_ID_SL4 };
	const E_IM_IIP_PARAM_PORTID		dstPortid[2] = { E_IM_IIP_PARAM_PORTID_SL2, E_IM_IIP_PARAM_PORTID_SL4 };
	const UINT32					unitidBitmask[2] = { D_IM_IIP_PARAM_PLDUNIT_LD2 | D_IM_IIP_PARAM_PLDUNIT_SL2,
														 D_IM_IIP_PARAM_PLDUNIT_FLT | D_IM_IIP_PARAM_PLDUNIT_SL4 };
	const UINT32					srcPixid[2] = { 3, 4 };
	const UINT32					dstPixid[2] = { 4, 5 };
	const UINT32					openResBitmask = E_IM_IIP_OPEN_RES_CACHE0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unitidBitmask[0] | unitidBitmask[1] | D_IM_IIP_PARAM_PLDUNIT_CFL0, pixidBitmask,
							  openResBitmask, D_CT_IM_IIP_OPEN_TIMEOUT_MSEC );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));
	if( ercd != D_IM_IIP_OK ) {
		return ercd;
	}

	pixfmtTbl0 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl0.line_bytes.Y_G = 160;
	pixfmtTbl0.line_bytes.Cb_B = 0;	// dummy
	pixfmtTbl0.line_bytes.Cr_R = 0;	// dummy
	pixfmtTbl0.line_bytes.Alpha = 0;	// dummy
	pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_RGBA4444;
	pixfmtTbl0.addr.Cb_B = 0;		// dummy
	pixfmtTbl0.addr.Cr_R = 0;		// dummy
	pixfmtTbl0.addr.Alpha = 0;	// dummy
	pixfmtTbl0.pix_format = E_IM_IIP_PFMT_RGBA4444;
	pixfmtTbl0.width = 80;
	pixfmtTbl0.lines = 54;

	pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl1.pix_format = E_IM_IIP_PFMT_RGBA4444;
	pixfmtTbl1.width = 80;
	pixfmtTbl1.lines = 54;
	pixfmtTbl1.line_bytes.Y_G = 160;
	pixfmtTbl1.line_bytes.Cb_B = 0;	// dummy
	pixfmtTbl1.line_bytes.Cr_R = 0;	// dummy
	pixfmtTbl1.line_bytes.Alpha = 0;	// dummy
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_2_RGBA4444;
	pixfmtTbl1.addr.Cb_B = 0;		// dummy
	pixfmtTbl1.addr.Cr_R = 0;		// dummy
	pixfmtTbl1.addr.Alpha = 0;	// dummy

	pixfmtTbl2 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl2.line_bytes.Y_G = 160;
	pixfmtTbl2.line_bytes.Cb_B = 0;	// dummy
	pixfmtTbl2.line_bytes.Cr_R = 0;	// dummy
	pixfmtTbl2.line_bytes.Alpha = 0;	// dummy
	pixfmtTbl2.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_RGBA4444;
	pixfmtTbl2.addr.Cb_B = 0;		// dummy
	pixfmtTbl2.addr.Cr_R = 0;		// dummy
	pixfmtTbl2.addr.Alpha = 0;	// dummy
	pixfmtTbl2.pix_format = E_IM_IIP_PFMT_RGBA4444;
	pixfmtTbl2.width = 80;
	pixfmtTbl2.lines = 54;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", (UINT32)onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL) ));

	*onedUnitInf = g_ct_im_iip_param_1dl_base;
	onedUnitInf->LD_TOPCNF0.bit.WAITCONF = dstPortid[0];
	onedUnitInf->PIXIDDEF.bit.IPIXID = srcPixid[0];
	onedUnitInf->LD_CTL.bit.SLOW = E_IM_IIP_PARAM_SLOW_1PIX_CYC;
	onedUnitInf->LD_HSIZE.bit.HEND = 80 - 1;
	onedUnitInf->LD_VSIZE.bit.VEND = 54 - 1;

	onedCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	onedCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	onedCfg.unit_param_addr = (ULONG)onedUnitInf;
	onedCfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "cflUnitInf = 0x%x 0x%x\n", (UINT32)cflUnitInf, sizeof(T_IM_IIP_PARAM_CFLOW) ));

	memset( cflUnitInf, '\0', sizeof(*cflUnitInf) );
	*cflUnitInf = S_G_CT_IM_IIP_PARAM_CFL_BASE;
	cflUnitInf->CFTOPCONF.bit.DATACONF_0 = dstPortid[0];
	cflUnitInf->CFTOPCONF.bit.DATACONF_1 = dstPortid[1];
	cflUnitInf->DIFF_PREWAIT.bit.DIFF_PREWAIT = 8192;		// About. (ImgCache 32kByte /4)
	cflUnitInf->DIFF_POSTWAIT.bit.DIFF_POSTWAIT = 0;

	cflCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	cflCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	cflCfg.unit_param_addr = (ULONG)cflUnitInf;
	cflCfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "fltUnitInf = 0x%x 0x%x\n", (UINT32)fltUnitInf, sizeof(T_IM_IIP_PARAM_FLT) ));

	*fltUnitInf = g_ct_im_iip_param_flt_base;
	fltUnitInf->TDLTOPCNF.bit.DATACONF = E_IM_IIP_PARAM_PORTID_NONE;
	fltUnitInf->TDLTOPCNF.bit.WAITCONF_0 = dstPortid[1];
	fltUnitInf->TDLTOPCNF.bit.WAITCONF_1 = E_IM_IIP_PARAM_PORTID_NONE;
	fltUnitInf->PIXIDDEF.bit.IPIXID0 = srcPixid[1];
//	fltUnitInf->PIXIDDEF.bit.IPIXID1 = srcPixid[1];
	fltUnitInf->TDL_HSIZE.bit.HEND = 80 - 1;
	fltUnitInf->TDL_VSIZE.bit.VEND = 54 - 1;

	fltCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	fltCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	fltCfg.unit_param_addr = (ULONG)fltUnitInf;
	fltCfg.load_unit_param_flag = 0;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "slUnitInf[0] = 0x%x 0x%x\n", (UINT32)slUnitInf[0], sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf[0], '\0', sizeof(*slUnitInf[0]) );
	*slUnitInf[0] = g_ct_im_iip_param_sts_base;
	slUnitInf[0]->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid[0];
	slUnitInf[0]->BASE.SL_TOPCNF0.bit.WAITCONF = cflPortid[0];
	slUnitInf[0]->BASE.PIXIDDEF.bit.OPIXID = dstPixid[0];
	slUnitInf[0]->BASE.SL_HSIZE.bit.HEND = 80 - 1;
	slUnitInf[0]->BASE.SL_VSIZE.bit.VEND = 54 - 1;

	slCfg[0].unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg[0].chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg[0].unit_param_addr = (ULONG)slUnitInf[0];
	slCfg[0].load_unit_param_flag = unitidBitmask[0];

	Ddim_Print(( D_IM_IIP_FUNC_NAME "slUnitInf[1] = 0x%x 0x%x\n", (UINT32)slUnitInf[1], sizeof(T_IM_IIP_PARAM_STS) ));

	memset( slUnitInf[1], '\0', sizeof(*slUnitInf[1]) );
	*slUnitInf[1] = g_ct_im_iip_param_sts_base;
	slUnitInf[1]->BASE.SL_TOPCNF0.bit.DATACONF = srcPortid[1];
	slUnitInf[1]->BASE.SL_TOPCNF0.bit.WAITCONF = cflPortid[1];
	slUnitInf[1]->BASE.PIXIDDEF.bit.OPIXID = dstPixid[1];
	slUnitInf[1]->BASE.SL_HSIZE.bit.HEND = 80 - 1;
	slUnitInf[1]->BASE.SL_VSIZE.bit.VEND = 54 - 1;

	slCfg[1].unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg[1].chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg[1].unit_param_addr = (ULONG)slUnitInf[1];
	slCfg[1].load_unit_param_flag = unitidBitmask[1];

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)onedUnitInf, sizeof(T_IM_IIP_PARAM_1DL) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)fltUnitInf, sizeof(T_IM_IIP_PARAM_FLT) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)cflUnitInf, sizeof(T_IM_IIP_PARAM_CFLOW) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf[0], sizeof(T_IM_IIP_PARAM_STS) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf[1], sizeof(T_IM_IIP_PARAM_STS) );

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid[0], &pixfmtTbl0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( srcPixid[1], &pixfmtTbl1 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid[0], &pixfmtTbl1 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_PIXFMTTBL( dstPixid[1], &pixfmtTbl2 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid[0], &onedCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( srcUnitid[1], &fltCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid[0], &slCfg[0] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( dstUnitid[1], &slCfg[1] );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Ctrl_SWTRG_Unit( cflUnitid, &cflCfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	ercd = Im_IIP_Set_Interrupt( waitFactor, D_IM_IIP_ENABLE_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Dd_ARM_Dmb_Pou();

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start1\n" ));
	ercd = Im_IIP_Start_SWTRG( cflUnitid, D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start2\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid[0], D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start3\n" ));
	ercd = Im_IIP_Start_SWTRG( dstUnitid[1], D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start4\n" ));
	ercd = Im_IIP_Start_SWTRG( srcUnitid[0], D_IM_IIP_SWTRG_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	Ddim_Print(( D_IM_IIP_FUNC_NAME "Start5\n" ));
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
	ercd = Im_IIP_Close_SWTRG( unitidBitmask[0] | unitidBitmask[1] | D_IM_IIP_PARAM_PLDUNIT_CFL0, 
							   pixidBitmask, openResBitmask );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// CFL Unit 12-1-X
INT32 ct_im_iip_cfl_run_12_1( const UINT32 ctNo3rd )
{
	switch( ctNo3rd ) {
		// Test-12-1-1
		case 1:
			return ct_im_iip_cfl_12_1_1();

		// Test-12-1-2
		case 2:
			return ct_im_iip_cfl_12_1_2();

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

#endif //CO_CT_IM_IIP_DISABLE

CtImIipCfl* ct_im_iip_cfl_new(void)
{
	CtImIipCfl* self = k_object_new_with_private(CT_TYPE_IM_IIP_CFL, sizeof(CtImIipCflPrivate));

	return self;
}