/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip9
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


// CT header
// C Standard header
#include <string.h>
#include <stdlib.h>

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif
#endif //CO_CT_IM_IIP_DISABLE

#include "ct_im_iip.h"
#include "ct_im_iip_b2y_frect_afn.h"
#include "ct_im_iip_afn.h"
//#include "ct_im_iip_frect.h"
#include "ctimiipfrect.h"
#include "ct_im_iip_lut.h"
#include "ct_im_iip_blend.h"
#include "ct_im_iip_csc.h"
#include "ct_im_iip_ld.h"
#include "ct_im_iip_flt.h"
#include "ct_im_iip_sl.h"
#include "ct_im_iip_mon.h"
#include "ct_im_iip_cfl.h"
#include "ct_im_iip_gpc.h"
#include "ct_im_iip_utility.h"
#include "ct_im_iip_mft.h"
// im_iip header
#include "im_iip.h"

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#include "palladium_test_common.h"
#endif
// ### REMOVE_RELEASE END

// Driver common header
#include "driver_common.h"
#include "ddim_user_custom.h"

// Clock Control
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif

// Memory barrier
#include "dd_arm.h"
// MILB register header
#include "jdsiip.h"
#include "ctimiip.h"
#include "ctimiip9.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIip9, ct_im_iip_9)
//#define CT_IM_IIP_9_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIip9Private, CT_TYPE_IM_IIP_9))


struct _CtImIip9Private
{

};


/*
*DECLS
*/
#ifndef CO_CT_IM_IIP_DISABLE
static VOID ct_im_iip_print_pixfmttbl( const UINT32 pixid );
#endif //CO_CT_IM_IIP_DISABLE


/********
 * IMPL
 */
//static void ct_im_iip_9_constructor(CtImIip9 *self)
//{
//	CtImIip9Private *priv = CT_IM_IIP_9_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_9_destructor(CtImIip9 *self)
//{
//	CtImIip9Private *priv = CT_IM_IIP_9_GET_PRIVATE(self);
//}

#ifndef CO_CT_IM_IIP_DISABLE
static VOID ct_im_iip_print_pixfmttbl( const UINT32 pixid )
{
	volatile struct io_iip_pixfmttbl*	pPIXFMTTBL;

	pPIXFMTTBL = &IO_IIP.PIXFMTTBL[pixid];

	Im_IIP_On_Pclk();

	Ddim_Print(( "[%u] PIXFMTTBL_0 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_0.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_1 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_1.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_2 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_2.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_3 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_3.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_4 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_4.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_5 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_5.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_6 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_6.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_7 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_7.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_8 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_8.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_9 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_9.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_10 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_10.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_11 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_11.word ));
	Ddim_Print(( "[%u] PIXFMTTBL_12 = 0x%08lx\n", pixid, pPIXFMTTBL->PIXFMTTBL_12.word ));

	Im_IIP_Off_Pclk();
}
#endif //CO_CT_IM_IIP_DISABLE


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
INT32 CT_Im_IIP_1_1_4( VOID )
{
	INT32 ercd;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	// check: result = 0x0
	ercd = Im_IIP_Open( 100 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check: result = 0x0C000013
	ercd = Im_IIP_Open( 100 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check: result = 0x0
	ercd = Im_IIP_Close();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check: result = 0x0C000099
	ercd = Im_IIP_Close();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check: result = 0x0
	ercd = Im_IIP_Open( 100 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

#ifdef CO_DEBUG_ON_PC
	// check: HWEN = 1
	ct_im_iip_set_hwen_auto_all();
	ct_im_iip_print_hwen_all();
#endif // CO_DEBUG_ON_PC

	// check: result = 0x0
	ercd = Im_IIP_Close();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

#ifdef CO_DEBUG_ON_PC
	// check: HWEN = 0
	ct_im_iip_print_hwen_all();
#endif // CO_DEBUG_ON_PC

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_5( VOID )
{
	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	CT_Im_IIP_1_1_4();

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_6( VOID )
{
	T_IM_IIP_PIXFMTTBL pixfmttbl_min = {
		.pix_depth = 0,
		.alpha = 0,
		.frame_type = (E_IM_IIP_FTYPE)0,
		.pix_format = (E_IM_IIP_PFMT)0,
		.alpha_depth = (E_IM_IIP_ADEPTH)0,
		.chunky_color = {
			0, 0, 0, 0,
		},
		.sign_Y_G = 0,
		.sign_Cb_B = 0,
		.sign_Cr_R = 0,
		.sign_D3 = 0,
		.masterIF_Y_G = 0,
		.masterIF_Cb_B = 0,
		.masterIF_Cr_R = 0,
		.masterIF_Alpha = 0,
		.alpha_subsampling = 0,
		.pix_outside_img = 0,
		.Y_G_val_outside_img = 0,
		.Cb_B_val_outside_img = 0,
		.Cr_R_val_outside_img = 0,
		.Alpha_val_outside_img = 0,
		.width = 0,
		.lines = 0,
		.line_bytes = {
			0, 0, 0, 0,
		},
		.addr = {
			0, 0, 0, 0,
		},
	};
	T_IM_IIP_PIXFMTTBL pixfmttbl_max = {
		.pix_depth = 3,
		.alpha = 7,
		.frame_type = (E_IM_IIP_FTYPE)3,
		.pix_format = (E_IM_IIP_PFMT)0xf,
		.alpha_depth = (E_IM_IIP_ADEPTH)3,
		.chunky_color = {
			0x3, 0x3, 0x3, 0x3,
		},
		.sign_Y_G = 1,
		.sign_Cb_B = 1,
		.sign_Cr_R = 1,
		.sign_D3 = 1,
		.masterIF_Y_G = 1,
		.masterIF_Cb_B = 1,
		.masterIF_Cr_R = 1,
		.masterIF_Alpha = 1,
		.alpha_subsampling = 3,
		.pix_outside_img = 1,
		.Y_G_val_outside_img = 0xffff,
		.Cb_B_val_outside_img = 0xffff,
		.Cr_R_val_outside_img = 0xffff,
		.Alpha_val_outside_img = 0xffff,
		.width = 0x7fff,
		.lines = 0x3fff,
		.line_bytes = {
			0x3ffff, 0x3ffff, 0x3ffff, 0x3ffff,
		},
		.addr = {
			0xffffffffUL, 0xffffffffUL, 0xffffffffUL, 0xffffffffUL,
		},
	};
	INT32 ercd;
	UINT32 pixid;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	// check: result = 0x0
	ercd = Im_IIP_Open( 100 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	for( pixid = 0; pixid < D_IM_IIP_PIXID_MAXNUM; pixid++ ) {
		Ddim_Print(( "** %u\n", (UINT32)pixid ));

		// check: Assertion
		// check: result = 0xc000001
		ercd = Im_IIP_Ctrl_PIXFMTTBL( pixid, NULL );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		// check: All valid bit is '1'
		ercd = Im_IIP_Ctrl_PIXFMTTBL( pixid, &pixfmttbl_max );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_pixfmttbl( pixid );

		// check: All valid bit is '0'
		ercd = Im_IIP_Ctrl_PIXFMTTBL( pixid, &pixfmttbl_min );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_pixfmttbl( pixid );
	}

	// check: Assertion
	ercd = Im_IIP_Ctrl_PIXFMTTBL( D_IM_IIP_PIXID_MAXNUM, NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check: result = 0x0
	ercd = Im_IIP_Close();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_7( VOID )
{
	T_IM_IIP_UNIT_CFG unitcfg_min = {
		.unit_ctrl = 0,
		.chain_enable = 0,
		.unit_param_addr = 0,
		.load_unit_param_flag = 0,
	};
	T_IM_IIP_UNIT_CFG unitcfg_max = {
		.unit_ctrl = 1,
		.chain_enable = 1,
		.unit_param_addr = 0xffffffffUL,
		.load_unit_param_flag = 0xffffffffffffffffULL,
	};
	T_IM_IIP_UNITINFTBL unitinftbl_min = {
		.pLD[0] = &unitcfg_min,
		.pLD[1] = &unitcfg_min,
		.pLD[2] = &unitcfg_min,
		.pLD[3] = &unitcfg_min,
		.pLD[4] = &unitcfg_min,
		.pLD[5] = &unitcfg_min,
		.pLD[6] = &unitcfg_min,
		.pLD[7] = &unitcfg_min,
		.pFLT = &unitcfg_min,
		.pAFN[0] = &unitcfg_min,
		.pAFN[1] = &unitcfg_min,
		.pAFN[2] = &unitcfg_min,
		.pAFN[3] = &unitcfg_min,
		.pFRECT[0] = &unitcfg_min,
		.pFRECT[1] = &unitcfg_min,
		.pMON = &unitcfg_min,
		.pSL[0] = &unitcfg_min,
		.pSL[1] = &unitcfg_min,
		.pSL[2] = &unitcfg_min,
		.pSL[3] = &unitcfg_min,
		.pSL[4] = &unitcfg_min,
		.pSL[5] = &unitcfg_min,
		.pSL[6] = &unitcfg_min,
		.pSL[7] = &unitcfg_min,
		.pSL[8] = &unitcfg_min,
		.pCSC[0] = &unitcfg_min,
		.pCSC[1] = &unitcfg_min,
		.pCSC[2] = &unitcfg_min,
		.pCSC[3] = &unitcfg_min,
		.pLUT = &unitcfg_min,
		.pGPC = &unitcfg_min,
		.pBLEND[0] = &unitcfg_min,
		.pBLEND[1] = &unitcfg_min,
		.pCFL = &unitcfg_min,
		.pMFT = &unitcfg_min,
	};
	T_IM_IIP_UNITINFTBL unitinftbl_max = {
		.pLD[0] = &unitcfg_max,
		.pLD[1] = &unitcfg_max,
		.pLD[2] = &unitcfg_max,
		.pLD[3] = &unitcfg_max,
		.pLD[4] = &unitcfg_max,
		.pLD[5] = &unitcfg_max,
		.pLD[6] = &unitcfg_max,
		.pLD[7] = &unitcfg_max,
		.pFLT = &unitcfg_max,
		.pAFN[0] = &unitcfg_max,
		.pAFN[1] = &unitcfg_max,
		.pAFN[2] = &unitcfg_max,
		.pAFN[3] = &unitcfg_max,
		.pFRECT[0] = &unitcfg_max,
		.pFRECT[1] = &unitcfg_max,
		.pMON = &unitcfg_max,
		.pSL[0] = &unitcfg_max,
		.pSL[1] = &unitcfg_max,
		.pSL[2] = &unitcfg_max,
		.pSL[3] = &unitcfg_max,
		.pSL[4] = &unitcfg_max,
		.pSL[5] = &unitcfg_max,
		.pSL[6] = &unitcfg_max,
		.pSL[7] = &unitcfg_max,
		.pSL[8] = &unitcfg_max,
		.pCSC[0] = &unitcfg_max,
		.pCSC[1] = &unitcfg_max,
		.pCSC[2] = &unitcfg_max,
		.pCSC[3] = &unitcfg_max,
		.pLUT = &unitcfg_max,
		.pGPC = &unitcfg_max,
		.pBLEND[0] = &unitcfg_max,
		.pBLEND[1] = &unitcfg_max,
		.pCFL = &unitcfg_max,
		.pMFT = &unitcfg_max,
	};
	T_IM_IIP_UNITINFTBL unitinftbl_null = {
		.pLD[0] = NULL,
		.pLD[1] = NULL,
		.pLD[2] = NULL,
		.pLD[3] = NULL,
		.pLD[4] = NULL,
		.pLD[5] = NULL,
		.pLD[6] = NULL,
		.pLD[7] = NULL,
		.pFLT = NULL,
		.pAFN[0] = NULL,
		.pAFN[1] = NULL,
		.pAFN[2] = NULL,
		.pAFN[3] = NULL,
		.pFRECT[0] = NULL,
		.pFRECT[1] = NULL,
		.pMON = NULL,
		.pSL[0] = NULL,
		.pSL[1] = NULL,
		.pSL[2] = NULL,
		.pSL[3] = NULL,
		.pSL[4] = NULL,
		.pSL[5] = NULL,
		.pSL[6] = NULL,
		.pSL[7] = NULL,
		.pSL[8] = NULL,
		.pCSC[0] = NULL,
		.pCSC[1] = NULL,
		.pCSC[2] = NULL,
		.pCSC[3] = NULL,
		.pLUT = NULL,
		.pGPC = NULL,
		.pBLEND[1] = NULL,
		.pBLEND[0] = NULL,
		.pCFL = NULL,
		.pMFT = NULL,
	};

	INT32 ercd;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	// check: result = 0x0
	ercd = Im_IIP_Open( 100 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check: Assertion
	// check: result = 0xc000001
	ercd = Im_IIP_Ctrl_UNITINFTBL( NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check: result = 0x0
	// check: All valid bit is '1'
	ercd = Im_IIP_Ctrl_UNITINFTBL( &unitinftbl_max );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	ct_im_iip_print_unitcfg_all();

	// check: result = 0x0
	// check: HWEN = 0
	ercd = Im_IIP_Ctrl_UNITINFTBL( &unitinftbl_null );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	ct_im_iip_print_unitcfg_all();

	// check: result = 0x0
	// check: All valid bit is '0'
	ercd = Im_IIP_Ctrl_UNITINFTBL( &unitinftbl_min );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	ct_im_iip_print_unitcfg_all();

	// check: result = 0x0
	ercd = Im_IIP_Close();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_CT_IM_IIP_DISABLE

CtImIip9* ct_im_iip_9_get(void)
{
	static CtImIip9* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_9, sizeof(CtImIip9Private));
	}

	return self;
}
