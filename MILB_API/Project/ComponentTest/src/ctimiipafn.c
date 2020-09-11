/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 杨文
*@brief : CtImIipAfn
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimiipafn.h"


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Nothing Special

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


K_TYPE_DEFINE_WITH_PRIVATE(CtImIipAfn, ct_im_iip_afn)
#define CT_IM_IIP_AFN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIipAfnPrivate, CT_TYPE_IM_IIP_AFN))


struct _CtImIipAfnPrivate
{
	int a;
};


/**
 * IMPL
 */
static void ct_im_iip_afn_constructor(CtImIipAfn *self)
{
	CtImIipAfnPrivate *priv = CT_IM_IIP_AFN_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_iip_afn_destructor(CtImIipAfn *self)
{
	CtImIipAfnPrivate *priv = CT_IM_IIP_AFN_GET_PRIVATE(self);

	priv->a = 0;
}


/**
 * PUBLIC
 */
// /*----------------------------------------------------------------------*/
// /* Function																*/
// /*----------------------------------------------------------------------*/

// AFN Unit 3-2-1 YCC422 U8 FullHD->Ribery VGA D-Zoom x1.0 (Resize & format comvert)
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_afn_3_2_1: "
INT32 ct_im_iip_afn_3_2_1( VOID )
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
	pixfmtTbl0.line_bytes.Y_G = D_IM_IIP_FULLHD_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Cb_B = D_IM_IIP_FULLHD_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Cr_R = D_IM_IIP_FULLHD_YCC422_U8_C_GLOBAL_WIDTH;	// dummy
	pixfmtTbl0.line_bytes.Alpha = D_IM_IIP_FULLHD_YCC422_U8_A_GLOBAL_WIDTH;	// dummy
	pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_Y;
	pixfmtTbl0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_C;
	pixfmtTbl0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_C;	// dummy
	pixfmtTbl0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_A;	// dummy
	pixfmtTbl0.width = D_IM_IIP_FULLHD_WIDTH;
	pixfmtTbl0.lines = D_IM_IIP_FULLHD_LINES;

	pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_VGA_16_9_RIBERY_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_VGA_16_9_RIBERY_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_VGA_16_9_RIBERY_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Alpha = 0;	// dummy
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_VGA_16_9_RIBERY_U8_Y;
	pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_VGA_16_9_RIBERY_U8_C;
	pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_VGA_16_9_RIBERY_U8_C;	// dummy
	pixfmtTbl1.addr.Alpha = (ULONG)NULL;	// dummy
	pixfmtTbl1.width = D_IM_IIP_VGA_16_9_WIDTH;
	pixfmtTbl1.lines = D_IM_IIP_VGA_16_9_LINES;
	pixfmtTbl1.pix_format = E_IM_IIP_PFMT_VIDEO;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnTbl = 0x%x 0x%x\n", (UINT32)afnTbl, 
							sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) ));

	memset( afnTbl, '\0', sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	afnTbl->STAXY0.bit.STAX = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
	afnTbl->STAXY0.bit.STAY = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
	afnTbl->D_OUT_IN_0.bit.DXX = M_CT_IM_IIP_AFNTBL_CALC_PIT( pixfmtTbl1.width, pixfmtTbl0.width );
	afnTbl->D_OUT_IN_0.bit.DXY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// X increment Y=0.0
	afnTbl->D_OUT_IN_0.bit.DYX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// Y increment X=0.0
	afnTbl->D_OUT_IN_0.bit.DYY = M_CT_IM_IIP_AFNTBL_CALC_PIT( pixfmtTbl1.lines, pixfmtTbl0.lines );
	afnTbl->SZ.bit.AFNDHSZ = pixfmtTbl1.width;
	afnTbl->SZ.bit.AFNDVSZ = pixfmtTbl1.lines;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnUnitInf = 0x%x 0x%x\n", (UINT32)afnUnitInf, 
							sizeof(T_IM_IIP_PARAM_AFN) ));
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "STAX=0x%x STAY=0x%x\n", (INT32)afnTbl->STAXY0.bit.STAX, 
							(INT32)afnTbl->STAXY0.bit.STAY ));

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
	slUnitInf->BASE.SL_HSIZE.bit.HEND = pixfmtTbl1.width - 1;
	slUnitInf->BASE.SL_VSIZE.bit.VEND = pixfmtTbl1.lines - 1;

	slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unit_param_addr = (ULONG)slUnitInf;
	slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );

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


	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != D_DDIM_OK ) {
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// AFN Unit 3-2-2 YCC422 U8 FullHD->Ribery HD D-Zoom x1.0 (Resize & format comvert)
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_afn_3_2_2: "
INT32 ct_im_iip_afn_3_2_2( VOID )
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
	pixfmtTbl0.line_bytes.Y_G = D_IM_IIP_FULLHD_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Cb_B = D_IM_IIP_FULLHD_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Cr_R = D_IM_IIP_FULLHD_YCC422_U8_C_GLOBAL_WIDTH;	// dummy
	pixfmtTbl0.line_bytes.Alpha = D_IM_IIP_FULLHD_YCC422_U8_A_GLOBAL_WIDTH;	// dummy
	pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_Y;
	pixfmtTbl0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_C;
	pixfmtTbl0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_C;	// dummy
	pixfmtTbl0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_A;	// dummy
	pixfmtTbl0.width = D_IM_IIP_FULLHD_WIDTH;
	pixfmtTbl0.lines = D_IM_IIP_FULLHD_LINES;

	pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_HD_16_9_RIBERY_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_HD_16_9_RIBERY_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_HD_16_9_RIBERY_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Alpha = 0;	// dummy
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_HD_16_9_RIBERY_U8_Y;
	pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_HD_16_9_RIBERY_U8_C;
	pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_HD_16_9_RIBERY_U8_C;	// dummy
	pixfmtTbl1.addr.Alpha = (ULONG)NULL;	// dummy
	pixfmtTbl1.width = D_IM_IIP_HD_16_9_WIDTH;
	pixfmtTbl1.lines = D_IM_IIP_HD_16_9_LINES;
	pixfmtTbl1.pix_format = E_IM_IIP_PFMT_VIDEO;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnTbl = 0x%x 0x%x\n", (UINT32)afnTbl, 
							sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) ));

	memset( afnTbl, '\0', sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	afnTbl->STAXY0.bit.STAX = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
	afnTbl->STAXY0.bit.STAY = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
	afnTbl->D_OUT_IN_0.bit.DXX = M_CT_IM_IIP_AFNTBL_CALC_PIT( pixfmtTbl1.width, pixfmtTbl0.width );
	afnTbl->D_OUT_IN_0.bit.DXY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// X increment Y=0.0
	afnTbl->D_OUT_IN_0.bit.DYX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// Y increment X=0.0
	afnTbl->D_OUT_IN_0.bit.DYY = M_CT_IM_IIP_AFNTBL_CALC_PIT( pixfmtTbl1.lines, pixfmtTbl0.lines );
	afnTbl->SZ.bit.AFNDHSZ = pixfmtTbl1.width;
	afnTbl->SZ.bit.AFNDVSZ = pixfmtTbl1.lines;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnUnitInf = 0x%x 0x%x\n", (UINT32)afnUnitInf, 
							sizeof(T_IM_IIP_PARAM_AFN) ));
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "STAX=0x%x STAY=0x%x\n", (INT32)afnTbl->STAXY0.bit.STAX, 
							(INT32)afnTbl->STAXY0.bit.STAY ));

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
	slUnitInf->BASE.SL_HSIZE.bit.HEND = pixfmtTbl1.width - 1;
	slUnitInf->BASE.SL_VSIZE.bit.VEND = pixfmtTbl1.lines - 1;

	slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unit_param_addr = (ULONG)slUnitInf;
	slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );

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


	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != D_DDIM_OK ) {
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// AFN Unit 3-2-3 YCC422 U8 FullHD->Ribery HD D-Zoom x1.0 (Resize & format comvert)
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "ct_im_iip_afn_3_2_3: "
INT32 ct_im_iip_afn_3_2_3( VOID )
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
	pixfmtTbl0.line_bytes.Y_G = D_IM_IIP_FULLHD_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Cb_B = D_IM_IIP_FULLHD_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmtTbl0.line_bytes.Cr_R = D_IM_IIP_FULLHD_YCC422_U8_C_GLOBAL_WIDTH;	// dummy
	pixfmtTbl0.line_bytes.Alpha = D_IM_IIP_FULLHD_YCC422_U8_A_GLOBAL_WIDTH;	// dummy
	pixfmtTbl0.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_Y;
	pixfmtTbl0.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_C;
	pixfmtTbl0.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_C;	// dummy
	pixfmtTbl0.addr.Alpha = D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_A;	// dummy
	pixfmtTbl0.width = D_IM_IIP_FULLHD_WIDTH;
	pixfmtTbl0.lines = D_IM_IIP_FULLHD_LINES;

	pixfmtTbl1 = g_ct_im_iip_pixfmttbl_base;
	pixfmtTbl1.line_bytes.Y_G = D_IM_IIP_FULLHD_RIBERY_U8_Y_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cb_B = D_IM_IIP_FULLHD_RIBERY_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Cr_R = D_IM_IIP_FULLHD_RIBERY_U8_C_GLOBAL_WIDTH;
	pixfmtTbl1.line_bytes.Alpha = 0;	// dummy
	pixfmtTbl1.addr.Y_G = D_IM_IIP_IMG_MEM_ADDR_1_FULLHD_RIBERY_U8_Y;
	pixfmtTbl1.addr.Cb_B = D_IM_IIP_IMG_MEM_ADDR_1_FULLHD_RIBERY_U8_C;
	pixfmtTbl1.addr.Cr_R = D_IM_IIP_IMG_MEM_ADDR_1_FULLHD_RIBERY_U8_C;	// dummy
	pixfmtTbl1.addr.Alpha = (ULONG)NULL;	// dummy
	pixfmtTbl1.width = D_IM_IIP_FULLHD_WIDTH;
	pixfmtTbl1.lines = D_IM_IIP_FULLHD_LINES;
	pixfmtTbl1.pix_format = E_IM_IIP_PFMT_VIDEO;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnTbl = 0x%x 0x%x\n", (UINT32)afnTbl, 
							sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) ));

	memset( afnTbl, '\0', sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	afnTbl->STAXY0.bit.STAX = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
	afnTbl->STAXY0.bit.STAY = M_CT_IM_IIP_AFNTBL_CALC_POS(0);
	afnTbl->D_OUT_IN_0.bit.DXX = M_CT_IM_IIP_AFNTBL_CALC_PIT( pixfmtTbl1.width, pixfmtTbl0.width );
	afnTbl->D_OUT_IN_0.bit.DXY = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// X increment Y=0.0
	afnTbl->D_OUT_IN_0.bit.DYX = M_CT_IM_IIP_AFNTBL_CALC_POS(0.0F);	// Y increment X=0.0
	afnTbl->D_OUT_IN_0.bit.DYY = M_CT_IM_IIP_AFNTBL_CALC_PIT( pixfmtTbl1.lines, pixfmtTbl0.lines );
	afnTbl->SZ.bit.AFNDHSZ = pixfmtTbl1.width;
	afnTbl->SZ.bit.AFNDVSZ = pixfmtTbl1.lines;

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "afnUnitInf = 0x%x 0x%x\n", (UINT32)afnUnitInf, 
							sizeof(T_IM_IIP_PARAM_AFN) ));
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "STAX=0x%x STAY=0x%x\n", (INT32)afnTbl->STAXY0.bit.STAX, 
							(INT32)afnTbl->STAXY0.bit.STAY ));

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
	slUnitInf->BASE.SL_HSIZE.bit.HEND = pixfmtTbl1.width - 1;
	slUnitInf->BASE.SL_VSIZE.bit.VEND = pixfmtTbl1.lines - 1;

	slCfg.unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
	slCfg.chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	slCfg.unit_param_addr = (ULONG)slUnitInf;
	slCfg.load_unit_param_flag = unitidBitmask;

	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnTbl, sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)afnUnitInf, sizeof(T_IM_IIP_PARAM_AFN) );
	ct_im_iip_clean_l1l2_dcache_addr( (ULONG)slUnitInf, sizeof(T_IM_IIP_PARAM_STS) );

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


	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "WaitEnd\n" ));
	ercd = Im_IIP_Wait_End( &waitFactorResult, waitFactor, D_IM_IIP_OR_WAIT, 30 );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	if( ercd != D_DDIM_OK ) {
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Stop\n" ));
		ercd = Im_IIP_Stop( D_IM_IIP_ABORT );
		CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult ));
	}

	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n" ));
	ercd = Im_IIP_Close_SWTRG( unitidBitmask, pixidBitmask, openResBitmask );
	CtImIipAfn_DDIM_PRINT(( D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

// AFN Unit 3-2-X
INT32 ct_im_iip_afn_run_3_2( const UINT32 ctNo3rd )
{
	switch( ctNo3rd ) {
		// Test-3-2-1
		case 1:
			return ct_im_iip_afn_3_2_1();

		// Test-3-2-2
		case 2:
			return ct_im_iip_afn_3_2_2();

		// Test-3-2-3
		case 3:
			return ct_im_iip_afn_3_2_3();

		default:
			CtImIipAfn_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}


CtImIipAfn* ct_im_iip_afn_new(void)
{
	CtImIipAfn* self = k_object_new_with_private(CT_TYPE_IM_IIP_AFN, sizeof(CtImIipAfnPrivate));

	return self;
}

CtImIipAfn* ct_im_iip_afn_get(void)
{
	static CtImIipAfn* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_IIP_AFN, sizeof(CtImIipAfnPrivate));
	}

	return self;
}