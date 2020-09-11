/*
*@Copyright (C) 2050-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*5、
*2、
*@version
*5.0.0 2020年06月开始开发
*/
#include "imiipdefine.h"

#include "im_iip_param.h"
#include "driver_common.h"
#include <klib.h>
//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
//#endif
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include "jdsiip.h"
// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END
#include <string.h>
#include "imiipvoid.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImIipVoid, im_iip_void);
#define IM_IIP_VOID_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipVoidPrivate, IM_TYPE_IIP_VOID))

struct _ImIipVoidPrivate
{
	int a;
};

static void im_iip_void_constructor(ImIipVoid *self)
{
	ImIipVoidPrivate *priv = IM_IIP_VOID_GET_PRIVATE(self);
	priv-> a =  0;
}

static void im_iip_void_destructor(ImIipVoid *self)
{
	ImIipVoidPrivate *priv = IM_IIP_VOID_GET_PRIVATE(self);
	priv-> a =  0;
}

INT32 Im_IIP_Ctrl_PIXFMTTBL( const UINT32 pixid, const T_IM_IIP_PIXFMTTBL* const tbl )
{
	volatile struct io_iip_pixfmttbl*	pPIXFMTTBL;
	UINT32								irq_mask;

#ifdef CO_PARAM_CHECK
	if( pixid >= D_IM_IIP_MAX_PIXID ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_PIXFMTTBL INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
	if( tbl == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_PIXFMTTBL INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif	// CO_PARAM_CHECK

	pPIXFMTTBL = &IO_IIP.PIXFMTTBL[pixid];

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

#ifdef CO_DEBUG_PRINT_IM_IIP
	Ddim_Print(( "Im_IIP_Ctrl_PIXFMTTBL pixid=%u\n", pixid ));
#endif

	irq_mask = im_iip_irq_disable();

	im_iip_wait_pftflg();

	pPIXFMTTBL->PIXFMTTBL_0.bit.PFMT = tbl->pix_format;
	pPIXFMTTBL->PIXFMTTBL_0.bit.PDEPTH = tbl->pix_depth;
	pPIXFMTTBL->PIXFMTTBL_0.bit.ALPHA = tbl->alpha;
	pPIXFMTTBL->PIXFMTTBL_0.bit.ADEPTH = tbl->alpha_depth;
	pPIXFMTTBL->PIXFMTTBL_0.bit.CHKYORDR = ((0x3 & tbl->chunky_color.component3) << 6) |
										   ((0x3 & tbl->chunky_color.component2) << 4) |
										   ((0x3 & tbl->chunky_color.component1) << 2) |
										   ((0x3 & tbl->chunky_color.component0) << 0);

	pPIXFMTTBL->PIXFMTTBL_1.bit.SGYG = tbl->sign_Y_G;
	pPIXFMTTBL->PIXFMTTBL_1.bit.SGB = tbl->sign_Cb_B;
	pPIXFMTTBL->PIXFMTTBL_1.bit.SGR = tbl->sign_Cr_R;
	pPIXFMTTBL->PIXFMTTBL_1.bit.SGA = tbl->sign_D3;
	pPIXFMTTBL->PIXFMTTBL_1.bit.ASUBSPL = tbl->alpha_subsampling;
	pPIXFMTTBL->PIXFMTTBL_1.bit.OARBHV = tbl->pix_outside_img;

	pPIXFMTTBL->PIXFMTTBL_8.bit.PICHSZ = tbl->width;
	pPIXFMTTBL->PIXFMTTBL_8.bit.PICVSZ = tbl->lines;

	pPIXFMTTBL->PIXFMTTBL_2.bit.OARVALYG = tbl->Y_G_val_outside_img;
	pPIXFMTTBL->PIXFMTTBL_2.bit.OARVALB = tbl->Cb_B_val_outside_img;
	pPIXFMTTBL->PIXFMTTBL_3.bit.OARVALR = tbl->Cr_R_val_outside_img;
	pPIXFMTTBL->PIXFMTTBL_3.bit.OARVALA = tbl->Alpha_val_outside_img;

	pPIXFMTTBL->PIXFMTTBL_0.bit.FTYPE = tbl->frame_type;

	pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFYG = tbl->masterIF_Y_G;
	pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFB = tbl->masterIF_Cb_B;
	pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFR = tbl->masterIF_Cr_R;
	pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFA = tbl->masterIF_Alpha;

	pPIXFMTTBL->PIXFMTTBL_4.bit.GHSZYG = tbl->line_bytes.Y_G;
	pPIXFMTTBL->PIXFMTTBL_5.bit.GHSZB = tbl->line_bytes.Cb_B;
	pPIXFMTTBL->PIXFMTTBL_6.bit.GHSZR = tbl->line_bytes.Cr_R;
	pPIXFMTTBL->PIXFMTTBL_7.bit.GHSZA = tbl->line_bytes.Alpha;

	pPIXFMTTBL->PIXFMTTBL_9.bit.ADRSYG = tbl->addr.Y_G;
	pPIXFMTTBL->PIXFMTTBL_10.bit.ADRSB = tbl->addr.Cb_B;
	pPIXFMTTBL->PIXFMTTBL_11.bit.ADRSR = tbl->addr.Cr_R;
	pPIXFMTTBL->PIXFMTTBL_12.bit.ADRSA = tbl->addr.Alpha;

	im_iip_update_pixfmttbl( pixid );

	im_iip_irq_enable( irq_mask );

#ifdef CO_DEBUG_PRINT_IM_IIP
	Ddim_Print(( "PFMT = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_0.bit.PFMT ));
	Ddim_Print(( "PDEPTH = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_0.bit.PDEPTH ));
	Ddim_Print(( "ALPHA = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_0.bit.ALPHA ));
	Ddim_Print(( "ADEPTH = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_0.bit.ADEPTH ));
	Ddim_Print(( "CHKYORDR = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_0.bit.CHKYORDR ));

	Ddim_Print(( "SGYG = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_1.bit.SGYG ));
	Ddim_Print(( "SGB = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_1.bit.SGB ));
	Ddim_Print(( "SGR = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_1.bit.SGR ));
	Ddim_Print(( "SGA = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_1.bit.SGA ));
	Ddim_Print(( "ASUBPL = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_1.bit.ASUBSPL ));
	Ddim_Print(( "OARBHV = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_1.bit.OARBHV ));

	Ddim_Print(( "PICHSZ = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_8.bit.PICHSZ ));
	Ddim_Print(( "PICVSZ = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_8.bit.PICVSZ ));

	Ddim_Print(( "OARVALYG = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_2.bit.OARVALYG ));
	Ddim_Print(( "OARVALB = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_2.bit.OARVALB ));
	Ddim_Print(( "OARVALR = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_3.bit.OARVALR ));
	Ddim_Print(( "OARVALA = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_3.bit.OARVALA ));

	Ddim_Print(( "MTIFYG = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFYG ));
	Ddim_Print(( "MTIFB = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFB ));
	Ddim_Print(( "MTIFR = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFR ));
	Ddim_Print(( "MTIFA = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_1.bit.MTIFA ));

	Ddim_Print(( "FTYPE = 0x%x\n", (UINT32)pPIXFMTTBL->PIXFMTTBL_0.bit.FTYPE ));

	Ddim_Print(( "GHSZYG = 0x%x\n", (INT32)pPIXFMTTBL->PIXFMTTBL_4.bit.GHSZYG ));
	Ddim_Print(( "GHSZB = 0x%x\n", (INT32)pPIXFMTTBL->PIXFMTTBL_5.bit.GHSZB ));
	Ddim_Print(( "GHSZR = 0x%x\n", (INT32)pPIXFMTTBL->PIXFMTTBL_6.bit.GHSZR ));
	Ddim_Print(( "GHSZA = 0x%x\n", (INT32)pPIXFMTTBL->PIXFMTTBL_7.bit.GHSZA ));

	Ddim_Print(( "ADRSYG = 0x%lx\n", pPIXFMTTBL->PIXFMTTBL_9.bit.ADRSYG ));
	Ddim_Print(( "ADRSB = 0x%lx\n", pPIXFMTTBL->PIXFMTTBL_10.bit.ADRSB ));
	Ddim_Print(( "ADRSR = 0x%lx\n", pPIXFMTTBL->PIXFMTTBL_11.bit.ADRSR ));
	Ddim_Print(( "ADRSA = 0x%lx\n", pPIXFMTTBL->PIXFMTTBL_12.bit.ADRSA ));
#endif //CO_DEBUG_PRINT_IM_IIP

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

/**
*	Set UNITINFTBL
*/
INT32 Im_IIP_Ctrl_UNITINFTBL( const T_IM_IIP_UNITINFTBL* const tbl )
{
#ifdef CO_PARAM_CHECK
	if( tbl == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_UNITINFTBL INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif	// CO_PARAM_CHECK

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	im_iip_set_UNITINFTBL( tbl->pLD[0], &IO_IIP.UNITINFTBL_LD0 );
	im_iip_set_UNITINFTBL( tbl->pLD[1], &IO_IIP.UNITINFTBL_LD1 );
	im_iip_set_UNITINFTBL( tbl->pLD[2], &IO_IIP.UNITINFTBL_LD2 );
	im_iip_set_UNITINFTBL( tbl->pLD[3], &IO_IIP.UNITINFTBL_LD3 );
	im_iip_set_UNITINFTBL( tbl->pLD[4], &IO_IIP.UNITINFTBL_LD4 );
	im_iip_set_UNITINFTBL( tbl->pLD[5], &IO_IIP.UNITINFTBL_LD5 );
	im_iip_set_UNITINFTBL( tbl->pLD[6], &IO_IIP.UNITINFTBL_LD6 );
	im_iip_set_UNITINFTBL( tbl->pLD[7], &IO_IIP.UNITINFTBL_LD7 );

	im_iip_set_UNITINFTBL( tbl->pFLT, &IO_IIP.UNITINFTBL_FLT );

	im_iip_set_UNITINFTBL( tbl->pAFN[0], &IO_IIP.UNITINFTBL_AFN0 );
	im_iip_set_UNITINFTBL( tbl->pAFN[1], &IO_IIP.UNITINFTBL_AFN1 );
	im_iip_set_UNITINFTBL( tbl->pAFN[2], &IO_IIP.UNITINFTBL_AFN2 );
	im_iip_set_UNITINFTBL( tbl->pAFN[3], &IO_IIP.UNITINFTBL_AFN3 );

	im_iip_set_UNITINFTBL( tbl->pFRECT[0], &IO_IIP.UNITINFTBL_FRC0 );
	im_iip_set_UNITINFTBL( tbl->pFRECT[1], &IO_IIP.UNITINFTBL_FRC1 );

	im_iip_set_UNITINFTBL( tbl->pMON, &IO_IIP.UNITINFTBL_MON );

	im_iip_set_UNITINFTBL_SL( tbl->pSL[0], &IO_IIP.UNITINFTBL_SL0 );
	im_iip_set_UNITINFTBL_SL( tbl->pSL[1], &IO_IIP.UNITINFTBL_SL1 );
	im_iip_set_UNITINFTBL_SL( tbl->pSL[2], &IO_IIP.UNITINFTBL_SL2 );
	im_iip_set_UNITINFTBL_SL( tbl->pSL[3], &IO_IIP.UNITINFTBL_SL3 );
	im_iip_set_UNITINFTBL_SL( tbl->pSL[4], &IO_IIP.UNITINFTBL_SL4 );
	im_iip_set_UNITINFTBL_SL( tbl->pSL[5], &IO_IIP.UNITINFTBL_SL5 );
	im_iip_set_UNITINFTBL_SL( tbl->pSL[6], &IO_IIP.UNITINFTBL_SL6 );
	im_iip_set_UNITINFTBL_SL( tbl->pSL[7], &IO_IIP.UNITINFTBL_SL7 );
	im_iip_set_UNITINFTBL_SL( tbl->pSL[8], &IO_IIP.UNITINFTBL_SL8 );

	im_iip_set_UNITINFTBL( tbl->pCSC[0], &IO_IIP.UNITINFTBL_CSC0 );
	im_iip_set_UNITINFTBL( tbl->pCSC[1], &IO_IIP.UNITINFTBL_CSC1 );
	im_iip_set_UNITINFTBL( tbl->pCSC[2], &IO_IIP.UNITINFTBL_CSC2 );
	im_iip_set_UNITINFTBL( tbl->pCSC[3], &IO_IIP.UNITINFTBL_CSC3 );

	im_iip_set_UNITINFTBL( tbl->pLUT, &IO_IIP.UNITINFTBL_LUT );

	im_iip_set_UNITINFTBL( tbl->pGPC, &IO_IIP.UNITINFTBL_GPC );

	im_iip_set_UNITINFTBL( tbl->pBLEND[0], &IO_IIP.UNITINFTBL_BLD0 );
	im_iip_set_UNITINFTBL( tbl->pBLEND[1], &IO_IIP.UNITINFTBL_BLD1 );

	im_iip_set_UNITINFTBL( tbl->pCFL, &IO_IIP.UNITINFTBL_CFL0 );

	im_iip_set_UNITINFTBL( tbl->pMFT, &IO_IIP.UNITINFTBL_MFT );

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

/**
*	Set LUTRAM
*/
INT32 Im_IIP_Ctrl_LUT( const T_IM_IIP_LUT* const lut )
{
	ULONG			lutramst = 0;
	ULONG			lutram_ofst = 0;
	INT32			retval = D_IM_IIP_OK;
	volatile ULONG*	dst;
	const USHORT*	src;

#ifdef CO_PARAM_CHECK
	if( lut == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_LUT INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
	if( lut->buffer_bytes > (D_IM_IIP_MAX_LUTRAM_RESOL * sizeof(lut->buffer_addr[0])) ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_LUT INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
	if( lut->lutram_type >= E_IM_IIP_LUTRAM_TYPE_MAX ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_LUT INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif	// CO_PARAM_CHECK

	DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.

	Im_IIP_On_Hclk();
	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	while( 1 ) {
		switch( lut->lutram_type ) {
			case E_IM_IIP_LUTRAM_TYPE_A:
				lutramst = IO_IIP.AHBSTS.bit.LUTAST;
				lutram_ofst = 1024 * 0;
				break;
			case E_IM_IIP_LUTRAM_TYPE_B:
				lutramst = IO_IIP.AHBSTS.bit.LUTBST;
				lutram_ofst = 1024 * 2;
				break;
			case E_IM_IIP_LUTRAM_TYPE_C:
				lutramst = IO_IIP.AHBSTS.bit.LUTCST;
				lutram_ofst = 1024 * 4;
				break;
			case E_IM_IIP_LUTRAM_TYPE_D:
				lutramst = IO_IIP.AHBSTS.bit.LUTDST;
				lutram_ofst = 1024 * 1;
				break;
			case E_IM_IIP_LUTRAM_TYPE_E:
				lutramst = IO_IIP.AHBSTS.bit.LUTEST;
				lutram_ofst = 1024 * 3;
				break;
			case E_IM_IIP_LUTRAM_TYPE_F:
				lutramst = IO_IIP.AHBSTS.bit.LUTFST;
				lutram_ofst = 1024 * 5;
				break;
			default:
				retval = D_IM_IIP_INVALID_ARG_ERR;
		}
		if( lutramst != 0 ) {
			retval = D_IM_IIP_ERR;
		}

		if( retval != D_IM_IIP_OK ) {
			break;
		}


		dst = &IO_IIP_TBL.LUTRAM.LUTRAM.word[0][0] + lutram_ofst;
		src = lut->buffer_addr;

		im_iip_wait_usec( 1 );

		im_iip_copy_short_to_word( dst, src, lut->buffer_bytes );

		break;
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Off_Hclk();
	Im_IIP_Dsb();

	DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.

	return retval;
}

INT32 Im_IIP_Set_Interrupt( const ULONG interrupt_bitmask, const UCHAR permission_flg )
{
	ULONG			inten0;
	ULONG			inten1;
//	ULONG			inten2;
	ULONG			intiz0;
	ULONG			intiz1;
//	ULONG			intiz2;
	UINT32			irq_mask;

	inten0 = 0;
	intiz0 = 0;
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_IZAEND ) {
		inten0 |= D_IM_IIP_IZAEN_BIT;
		intiz0 |= D_IM_IIP_IZAFLG_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_AXIERR ) {
		inten0 |= D_IM_IIP_AXEEN_BIT;
		intiz0 |= D_IM_IIP_AXEFLG_BIT;
	}

	inten1 = 0;
	intiz1 = 0;
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL0END ) {
		inten1 |= D_IM_IIP_SL0FEN_BIT;
		intiz1 |= D_IM_IIP_SL0FF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL1END ) {
		inten1 |= D_IM_IIP_SL1FEN_BIT;
		intiz1 |= D_IM_IIP_SL1FF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL2END ) {
		inten1 |= D_IM_IIP_SL2FEN_BIT;
		intiz1 |= D_IM_IIP_SL2FF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL3END ) {
		inten1 |= D_IM_IIP_SL3FEN_BIT;
		intiz1 |= D_IM_IIP_SL3FF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL4END ) {
		inten1 |= D_IM_IIP_SL4FEN_BIT;
		intiz1 |= D_IM_IIP_SL4FF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL5END ) {
		inten1 |= D_IM_IIP_SL5FEN_BIT;
		intiz1 |= D_IM_IIP_SL5FF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL6END ) {
		inten1 |= D_IM_IIP_SL6FEN_BIT;
		intiz1 |= D_IM_IIP_SL6FF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL7END ) {
		inten1 |= D_IM_IIP_SL7FEN_BIT;
		intiz1 |= D_IM_IIP_SL7FF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL8END ) {
		inten1 |= D_IM_IIP_SL8FEN_BIT;
		intiz1 |= D_IM_IIP_SL8FF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL0_LINEEND ) {
		inten1 |= D_IM_IIP_SL0MEN_BIT;
		intiz1 |= D_IM_IIP_SL0MF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL1_LINEEND ) {
		inten1 |= D_IM_IIP_SL1MEN_BIT;
		intiz1 |= D_IM_IIP_SL1MF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL2_LINEEND ) {
		inten1 |= D_IM_IIP_SL2MEN_BIT;
		intiz1 |= D_IM_IIP_SL2MF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL3_LINEEND ) {
		inten1 |= D_IM_IIP_SL3MEN_BIT;
		intiz1 |= D_IM_IIP_SL3MF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL4_LINEEND ) {
		inten1 |= D_IM_IIP_SL4MEN_BIT;
		intiz1 |= D_IM_IIP_SL4MF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL5_LINEEND ) {
		inten1 |= D_IM_IIP_SL5MEN_BIT;
		intiz1 |= D_IM_IIP_SL5MF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL6_LINEEND ) {
		inten1 |= D_IM_IIP_SL6MEN_BIT;
		intiz1 |= D_IM_IIP_SL6MF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL7_LINEEND ) {
		inten1 |= D_IM_IIP_SL7MEN_BIT;
		intiz1 |= D_IM_IIP_SL7MF_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL8_LINEEND ) {
		inten1 |= D_IM_IIP_SL8MEN_BIT;
		intiz1 |= D_IM_IIP_SL8MF_BIT;
	}

#if 0	// INTIZ2/INTEN2 delete
	inten2 = 0;
	intiz2 = 0;
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_RINGFULL_AFN0 ) {
		inten2 |= D_IM_IIP_REAF0E_BIT;
		intiz2 |= D_IM_IIP_REAF0F_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_RINGFULL_AFN1 ) {
		inten2 |= D_IM_IIP_REAF1E_BIT;
		intiz2 |= D_IM_IIP_REAF1F_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_RINGFULL_AFN2 ) {
		inten2 |= D_IM_IIP_REAF2E_BIT;
		intiz2 |= D_IM_IIP_REAF2F_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_RINGFULL_AFN3 ) {
		inten2 |= D_IM_IIP_REAF3E_BIT;
		intiz2 |= D_IM_IIP_REAF3F_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_RINGFULL_FRECT0 ) {
		inten2 |= D_IM_IIP_REFR0E_BIT;
		intiz2 |= D_IM_IIP_REFR0F_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_RINGFULL_FRECT1 ) {
		inten2 |= D_IM_IIP_REFR1E_BIT;
		intiz2 |= D_IM_IIP_REFR1F_BIT;
	}
	if( interrupt_bitmask & D_IM_IIP_INT_FACTOR_RINGFULL_FLT ) {
		inten2 |= D_IM_IIP_REFLTE_BIT;
		intiz2 |= D_IM_IIP_REFLTF_BIT;
	}
#endif	// INTIZ2/INTEN2 delete

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	irq_mask = im_iip_irq_disable();

	if( permission_flg == D_IM_IIP_ENABLE_OFF ) {
		// disable interrupt
		IO_IIP.INTEN0.word &= ~inten0;
		IO_IIP.INTEN1.word &= ~inten1;
//		IO_IIP.INTEN2.word &= ~inten2;

		// clear interrupt
		IO_IIP.INTIZ0.word = intiz0;
		IO_IIP.INTIZ1.word = intiz1;
//		IO_IIP.INTIZ2.word = intiz2;
	}
	else {
		// clear interrupt
		IO_IIP.INTIZ0.word = intiz0;
		IO_IIP.INTIZ1.word = intiz1;
//		IO_IIP.INTIZ2.word = intiz2;

		// enable interrupt
		IO_IIP.INTEN0.word |= inten0;
		IO_IIP.INTEN1.word |= inten1;
//		IO_IIP.INTEN2.word |= inten2;
	}

	im_iip_irq_enable( irq_mask );

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();


	return D_IM_IIP_OK;
}

INT32 Im_IIP_Set_SLIntLines( const ULONG interrupt_bitmask, const UINT32 trans_lines )
{
	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	if( (interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL0_LINEEND) != 0 ) {
		IO_IIP.LINE_VAL_INT_SL0.bit.LINE_VAL_INT_SL = trans_lines;
	}
	if( (interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL1_LINEEND) != 0 ) {
		IO_IIP.LINE_VAL_INT_SL1.bit.LINE_VAL_INT_SL = trans_lines;
	}
	if( (interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL2_LINEEND) != 0 ) {
		IO_IIP.LINE_VAL_INT_SL2.bit.LINE_VAL_INT_SL = trans_lines;
	}
	if( (interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL3_LINEEND) != 0 ) {
		IO_IIP.LINE_VAL_INT_SL3.bit.LINE_VAL_INT_SL = trans_lines;
	}
	if( (interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL4_LINEEND) != 0 ) {
		IO_IIP.LINE_VAL_INT_SL4.bit.LINE_VAL_INT_SL = trans_lines;
	}
	if( (interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL5_LINEEND) != 0 ) {
		IO_IIP.LINE_VAL_INT_SL5.bit.LINE_VAL_INT_SL = trans_lines;
	}
	if( (interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL6_LINEEND) != 0 ) {
		IO_IIP.LINE_VAL_INT_SL6.bit.LINE_VAL_INT_SL = trans_lines;
	}
	if( (interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL7_LINEEND) != 0 ) {
		IO_IIP.LINE_VAL_INT_SL7.bit.LINE_VAL_INT_SL = trans_lines;
	}
	if( (interrupt_bitmask & D_IM_IIP_INT_FACTOR_SL8_LINEEND) != 0 ) {
		IO_IIP.LINE_VAL_INT_SL8.bit.LINE_VAL_INT_SL = trans_lines;
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

ImIipVoid *im_iip_void_new(void)
{
	ImIipVoid* self = k_object_new_with_private(IM_TYPE_IIP_VOID,sizeof(ImIipVoidPrivate));
	return self;
}
