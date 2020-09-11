/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

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
#include "imiipdefine.h"
#include"imiipstruct.h"
#include "imiipcounter.h"

#ifdef CO_DEBUG_ON_PC
#undef CO_IIP_DEBUG
#undef CO_DEBUG_PRINT_IM_IIP
#undef CO_IIP_DEBUG_PRINT_FUNC
#undef CO_IIP_REG_TYPE_CHECK
#undef CO_IIP_DEBUG_CLK_DISABLE
#endif

K_TYPE_DEFINE_WITH_PRIVATE(ImIipDefine, im_iip_define);
#define IM_IIP_DEFINE_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipDefinePrivate, IM_TYPE_IIP_DEFINE))

struct _ImIipDefinePrivate
{
	int a;
};

static void im_iip_define_constructor(ImIipDefine *self)
{
	ImIipDefinePrivate *priv = IM_IIP_DEFINE_GET_PRIVATE(self);
	priv-> a =  0;
}

static void im_iip_define_destructor(ImIipDefine *self)
{
	ImIipDefinePrivate *priv = IM_IIP_DEFINE_GET_PRIVATE(self);
	priv-> a =  0;
}

#ifdef CO_IM_IIP_ENABLE_UTILITY

#include "im_iip_param.h"

static VOID imIipGetMaxMinValue( UINT32* const max_val,
									  UINT32* const min_val,
									  const UINT32 pix_depth,
									  const UCHAR sign )
{
	INT32 p;

	switch ( pix_depth ) {
		case D_IM_IIP_PDEPTH_8BITS:
			p = 8;
			break;
		case D_IM_IIP_PDEPTH_12BITS:
			p = 12;
			break;
//		case D_IM_IIP_PDEPTH_16BITS:
		default:
			p = 14;
			break;
	}

	if( D_IM_IIP_SIGNED_DATA == sign ) {
		*min_val = (UINT32)(-(1 << (p - 1)));
		*max_val = (UINT32)((1 << (p - 1)) - 1);
	}
	else {
		*min_val = 0x0000;
		*max_val = (UINT32)((1 << p) - 1);
	}
}

static void imIipSetAfnStructFlip( T_IM_IIP_PARAM_AFN_OPCOL_0* const afn_struct_param,
										 const T_IM_IIP_UTIL_IMG* const src,
										 const E_IM_IIP_UTIL_ROTATE rotation,
										 const E_IM_IIP_UTIL_FLIP flip)
{
	U_IM_IIP_PARAM_AFN_STAXY	set_sta;
	INT32						wok;
	static const int sta_pos_tbl[E_IM_IIP_UTIL_ROTATE_MAX][E_IM_IIP_UTIL_FLIP_MAX] = {
		// off							mirror						reverse						mirror_reverse
		{ D_IM_IIP_UTIL_ORIGIN,			D_IM_IIP_UTIL_TOPRIGHT,		D_IM_IIP_UTIL_BOTTOMLEFT,	D_IM_IIP_UTIL_BOTTOMRIGHT	},	// 0
		{ D_IM_IIP_UTIL_BOTTOMLEFT,		D_IM_IIP_UTIL_ORIGIN,		D_IM_IIP_UTIL_BOTTOMRIGHT,	D_IM_IIP_UTIL_TOPRIGHT		},	// 90
		{ D_IM_IIP_UTIL_BOTTOMRIGHT,	D_IM_IIP_UTIL_BOTTOMLEFT,	D_IM_IIP_UTIL_TOPRIGHT,		D_IM_IIP_UTIL_ORIGIN		},	// 180
		{ D_IM_IIP_UTIL_TOPRIGHT,		D_IM_IIP_UTIL_BOTTOMRIGHT,	D_IM_IIP_UTIL_ORIGIN,		D_IM_IIP_UTIL_BOTTOMLEFT	},	// 270
	};

	switch (sta_pos_tbl[rotation][flip])
	{
	case D_IM_IIP_UTIL_TOPRIGHT:
		set_sta.bit.STAX = im_iip_get_fixed_point(src->rect.left + src->rect.width - 1.0);
		set_sta.bit.STAY = im_iip_get_fixed_point(src->rect.top);
		break;
	case D_IM_IIP_UTIL_BOTTOMLEFT:
		set_sta.bit.STAX = im_iip_get_fixed_point(src->rect.left);
		set_sta.bit.STAY = im_iip_get_fixed_point(src->rect.top + src->rect.lines - 1.0);
		break;
	case D_IM_IIP_UTIL_BOTTOMRIGHT:
		set_sta.bit.STAX = im_iip_get_fixed_point(src->rect.left + src->rect.width - 1.0);
		set_sta.bit.STAY = im_iip_get_fixed_point(src->rect.top  + src->rect.lines - 1.0);
		break;
	case D_IM_IIP_UTIL_ORIGIN:
		set_sta.bit.STAX = im_iip_get_fixed_point(src->rect.left);
		set_sta.bit.STAY = im_iip_get_fixed_point(src->rect.top);
		break;
	default:
		// Don't set paramter about Mirror/Reverse in cases of error.
		return;
	}

	if (flip == E_IM_IIP_UTIL_FLIP_REVERSE)
	{
		afn_struct_param->STAXY0.bit.STAX = set_sta.bit.STAX;
		afn_struct_param->STAXY0.bit.STAY = set_sta.bit.STAY;

		// make y-component negative to flip vertical
		// DYX = -DYX
		im_iip_get_reg_signed_a( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, -wok );

		// DYY = -DYY
		im_iip_get_reg_signed_a( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, -wok );
	}
	else if (flip == E_IM_IIP_UTIL_FLIP_MIRROR)
	{
		afn_struct_param->STAXY0.bit.STAX = set_sta.bit.STAX;
		afn_struct_param->STAXY0.bit.STAY = set_sta.bit.STAY;

		// make x-component negative to flip horizontal
		// DXY = -DXY
		im_iip_get_reg_signed_a( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, -wok );
		afn_struct_param->D_OUT_IN_0.bit.DXY = -(afn_struct_param->D_OUT_IN_0.bit.DXY);

		// DXX = -DXX
		im_iip_get_reg_signed_a( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, -wok );
	}
	else if (flip == E_IM_IIP_UTIL_FLIP_MIR_AND_REV)
	{
		afn_struct_param->STAXY0.bit.STAX = set_sta.bit.STAX;
		afn_struct_param->STAXY0.bit.STAY = set_sta.bit.STAY;

		// make x and y component negative to flip horizontal and vertical
		// DXY = -DXY
		im_iip_get_reg_signed_a( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, -wok );
		afn_struct_param->D_OUT_IN_0.bit.DXY = -(afn_struct_param->D_OUT_IN_0.bit.DXY);

		// DXX = -DXX
		im_iip_get_reg_signed_a( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, -wok );

		// DYX = -DYX
		im_iip_get_reg_signed_a( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, -wok );

		// DYY = -DYY
		im_iip_get_reg_signed_a( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, -wok );
	}
	else
	{
		afn_struct_param->STAXY0.bit.STAX = set_sta.bit.STAX;
		afn_struct_param->STAXY0.bit.STAY = set_sta.bit.STAY;
	}
}

static VOID imIipSetAfnStructParam( T_IM_IIP_PARAM_AFN_OPCOL_0* const afn_struct_param,
										 const T_IM_IIP_UTIL_IMG* const src,
										 const T_IM_IIP_UTIL_IMG_INT* const dst,
										 const E_IM_IIP_UTIL_ROTATE rotation,
										 const E_IM_IIP_UTIL_FLIP flip )
{
	INT32	h_pit_fixed_point;
	INT32	v_pit_fixed_point;

	memset( afn_struct_param, '\0', sizeof(*afn_struct_param) );

	if( rotation == E_IM_IIP_UTIL_ROTATE_000 ) {
		h_pit_fixed_point = (((INT32)src->rect.width - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.width - 1);
		v_pit_fixed_point = (((INT32)src->rect.lines - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.lines - 1);

		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, h_pit_fixed_point );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY, 0x0 );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, 0x0 );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, v_pit_fixed_point );
	}
	else if( rotation == E_IM_IIP_UTIL_ROTATE_090 ) {
		h_pit_fixed_point = (((INT32)src->rect.width - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.lines - 1);
		v_pit_fixed_point = (((INT32)src->rect.lines - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.width - 1);

		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, 0x0 );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY, - v_pit_fixed_point );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, h_pit_fixed_point );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, 0x0 );
	}
	else if( rotation == E_IM_IIP_UTIL_ROTATE_270 ) {
		h_pit_fixed_point = (((INT32)src->rect.width - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.lines - 1);
		v_pit_fixed_point = (((INT32)src->rect.lines - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.width - 1);

		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, 0x0 );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY, v_pit_fixed_point );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, - h_pit_fixed_point );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, 0x0 );
	}
	else {
		// E_IM_IIP_UTIL_ROTATE_180
		h_pit_fixed_point = (((INT32)src->rect.width - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.width - 1);
		v_pit_fixed_point = (((INT32)src->rect.lines - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.lines - 1);

		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, - h_pit_fixed_point );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY, 0x0 );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, 0x0 );
		im_iip_set_reg_signed_a( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, - v_pit_fixed_point );
	}

	afn_struct_param->SZ.bit.AFNDVSZ = dst->rect.lines;
	afn_struct_param->SZ.bit.AFNDHSZ = dst->rect.width;

	imIipSetAfnStructFlip( afn_struct_param, src, rotation, flip );
}

static VOID imIipSetAfnUnitParam( T_IM_IIP_PARAM_AFN* const afn,
									   const ULONG afn_struct_param_addr,
									   const T_IM_IIP_UTIL_RR* const cfg )
{
	const T_IM_IIP_UTIL_RECT_INT* dst_rect = &cfg->dst.rect;
	UINT32 max_val;
	UINT32 min_val;

	memset( afn, '\0', sizeof(*afn) );

	afn->header0.bit.BeginningAddress = 0x0000;
	afn->header0.bit.WordLength = 29;
	afn->header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET;
	afn->AFNTOPCNF.bit.DATACONF = 0;
//	afn->AFNTOPCNF.bit.WAITCONF;	// set later
	afn->AFNLDCNF.bit.DTHD = E_IM_IIP_PARAM_DTHD_NORMAL;
	afn->AFNLDCNF.bit.CBC = E_IM_IIP_PARAM_CBC_DISABLE;
	afn->AFNCTL.bit.LPLVL = E_IM_IIP_PARAM_LPLVL_H_LEVEL;
	afn->AFNCTL.bit.HDBL = E_IM_IIP_PARAM_HDBL_SAME_AS_PICHSZ;
	afn->AFNCTL.bit.VDBL = E_IM_IIP_PARAM_VDBL_SAME_AS_PICVSZ;
	afn->AFNCTL.bit.GHSZ = E_IM_IIP_PARAM_GHSZ_32PIX;
	afn->AFNCTL.bit.GVSZ = ( dst_rect->lines >=   8 ) ? E_IM_IIP_PARAM_GVSZ_8PIX   :
		                   ( dst_rect->lines >=   4 ) ? E_IM_IIP_PARAM_GVSZ_4PIX   :
		                                                E_IM_IIP_PARAM_GVSZ_2PIX;
	afn->AFNCTL.bit.HSMD = E_IM_IIP_PARAM_HSMD_NORMAL;
	afn->PFCTL.bit.PFEXTMC = 4;
	afn->PFCTL.bit.PFEXTADC = 64;
	if( (E_IM_IIP_UTIL_ROTATE_090 == cfg->rotation) ||
		 (E_IM_IIP_UTIL_ROTATE_270 == cfg->rotation) ) {
		afn->PFCTL.bit.PFSP1 = E_IM_IIP_PARAM_PFSP_1;
		afn->PFCTL.bit.PFSP2 = E_IM_IIP_PARAM_PFSP_1;
	}
	else {
		afn->PFCTL.bit.PFSP1 = E_IM_IIP_PARAM_PFSP_1;
		afn->PFCTL.bit.PFSP2 = E_IM_IIP_PARAM_PFSP_16;
	}
	afn->PFCTL.bit.PFVSP = E_IM_IIP_PARAM_PFVSP_VERTICAL_0;
	afn->PFCTL.bit.PFOFF = E_IM_IIP_PARAM_PFOFF_RUN;
//	afn->PIXIDEF.bit.IPIXID;		// set later
	afn->PIXIDEF.bit.EXA = E_IM_IIP_PARAM_EXA_NO_ALPHA_TO_NEXT_UNIT;
	afn->PIXIDEF.bit.CSEL = cfg->afn_cache_select;
	afn->CALMETHOD.bit.OPCOL = 0;
	afn->CALMETHOD.bit.ITMD = cfg->resize_mode;
	afn->CALMETHOD.bit.ARA = E_IM_IIP_PARAM_ARA_ITMD;
	afn->CALMETHOD.bit.FILMD = 0;
	if( cfg->resize_mode == E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR ) {
		afn->CALMETHOD.bit.DANTI = 1;
		afn->CALMETHOD.bit.AANTI = 1;
	}
	else {
		afn->CALMETHOD.bit.DANTI = 0;
		afn->CALMETHOD.bit.AANTI = 0;
	}
	switch( cfg->afn_unitid ) {
		case E_IM_IIP_UNIT_ID_AFN0:
			afn->CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN0;
			break;
		case E_IM_IIP_UNIT_ID_AFN1:
			afn->CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN1;
			break;
		case E_IM_IIP_UNIT_ID_AFN2:
			afn->CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN2;
			break;
		case E_IM_IIP_UNIT_ID_AFN3:
			afn->CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN3;
			break;
		default:
			afn->CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN0;	// Failsafe
			break;
	}
	afn->CALMETHOD.bit.SCUB = cfg->bi_cubic_unitid;
	afn->FILVAL0.bit.FILVALYG = 0x0;
	afn->FILVAL0.bit.FILVALB = 0x0;
	afn->FILVAL1.bit.FILVALR = 0x0;
	afn->FILVAL1.bit.FILVALA = 0x0;
	afn->OPMD.bit.OPMD0 = E_IM_IIP_PARAM_OPMD_ADD;
	afn->OPY.bit.OPBY = 0;
	afn->OPY.bit.OPAY = 0x10;	// 1.0
	afn->OPB.bit.OPBB = 0;
	afn->OPB.bit.OPAB = 0x10;	// 1.0
	afn->OPR.bit.OPBR = 0;
	afn->OPR.bit.OPAR = 0x10;	// 1.0
	afn->OPA.bit.OPBA = 0;
	afn->OPA.bit.OPAA = 0x10;	// 1.0
	imIipGetMaxMinValue( &max_val, &min_val, cfg->pix_depth, cfg->src.gbl.sign_Y_G );
	afn->CLIPLVLY.bit.CLIPLVLYH = max_val;
	afn->CLIPLVLY.bit.CLIPLVLYL = min_val;
	imIipGetMaxMinValue( &max_val, &min_val, cfg->pix_depth, cfg->src.gbl.sign_Cb_B );
	afn->CLIPLVLB.bit.CLIPLVLBH = max_val;
	afn->CLIPLVLB.bit.CLIPLVLBL = min_val;
	imIipGetMaxMinValue( &max_val, &min_val, cfg->pix_depth, cfg->src.gbl.sign_Cr_R );
	afn->CLIPLVLR.bit.CLIPLVLRH = max_val;
	afn->CLIPLVLR.bit.CLIPLVLRL = min_val;
	imIipGetMaxMinValue( &max_val, &min_val, cfg->pix_depth, cfg->src.gbl.sign_D3 );
	afn->CLIPLVLA.bit.CLIPLVLAH = max_val;
	afn->CLIPLVLA.bit.CLIPLVLAL = min_val;
	afn->AFNPCNT.bit.AFNPHCNT = 1;
	afn->AFNPCNT.bit.AFNPVCNT = 1;
	afn->AFNPA.word = afn_struct_param_addr;
	afn->OUTSIZE.bit.OUTHSZ = 0;
	afn->OUTSIZE.bit.OUTVSZ = 0;
	afn->OUTSTARTPOS.bit.STARTX = 0;
	afn->OUTSTARTPOS.bit.STARTY = 0;
	afn->UPLK_TARGET.bit.UPSU0 = E_IM_IIP_PARAM_UPSU_NONE;
	afn->UPLK_TARGET.bit.UPSU1 = E_IM_IIP_PARAM_UPSU_NONE;
	afn->UPLK_TARGET.bit.UPSU2 = 0;
	afn->DWLK_TARGET.bit.DWSU0 = E_IM_IIP_PARAM_DWSU_NONE;
	afn->DWLK_TARGET.bit.DWSU1 = E_IM_IIP_PARAM_DWSU_NONE;
	afn->DWLK_TARGET.bit.DWSU2 = 0;
	afn->LKNUM.bit.UPNUM = E_IM_IIP_PARAM_UPNUM_NONE;
	afn->LKNUM.bit.DWNUM = E_IM_IIP_PARAM_DWNUM_NONE;
	afn->RING.bit.URINGSIZE = 0;
	afn->RING.bit.UMARGINIYSZ = 0;
	afn->RING.bit.DRINGSIZE = 0;
}

static VOID imIipUtilSetAfnRawInputUnit( T_IM_IIP_PARAM_AFN* const afn, T_IM_IIP_PARAM_AFN_OPCOL_0* const afn_struct_param, T_IM_IIP_PARAM_STS* const sl )
{
	INT32 wok;

	im_iip_get_reg_signed_a( wok, afn_struct_param->STAXY0, U_IM_IIP_PARAM_AFN_STAXY, STAX );
	wok /= 2;
	im_iip_set_reg_signed_a( afn_struct_param->STAXY0, U_IM_IIP_PARAM_AFN_STAXY, STAX, wok );
	im_iip_get_reg_signed_a( wok, afn_struct_param->STAXY0, U_IM_IIP_PARAM_AFN_STAXY, STAY );
	wok /= 2;
	im_iip_set_reg_signed_a( afn_struct_param->STAXY0, U_IM_IIP_PARAM_AFN_STAXY, STAY, wok );

	afn->OUTSIZE.bit.OUTHSZ /= 2;
	afn->OUTSIZE.bit.OUTVSZ /= 2;
	afn->OUTSTARTPOS.bit.STARTX = 0 /2;
	afn->OUTSTARTPOS.bit.STARTY = 0 /2;
	afn->CALMETHOD.bit.FILMD = 1;
	afn->CALMETHOD.bit.DANTI = 0;
	afn->CALMETHOD.bit.AANTI = 0;

	sl->BASE.SL_PHSZ.bit.PHSZ0 *= 2;
	sl->BASE.SL_PHSZ.bit.PHSZ1 *= 2;
	sl->BASE.SL_PVSZ.bit.PVSZ0 *= 2;
	sl->BASE.SL_PVSZ.bit.PVSZ1 *= 2;
}

static VOID imIipUtilSetAfnRawInputPixfmttbl( T_IM_IIP_PIXFMTTBL* const in_pixfmttbl )
{
	in_pixfmttbl->line_bytes.Y_G *= 2;
	in_pixfmttbl->line_bytes.Cb_B *= 2;
	in_pixfmttbl->line_bytes.Cr_R *= 2;
	in_pixfmttbl->width *= 2;
	in_pixfmttbl->lines *= 2;
}

static INT32 imIipUtilSetParamResizerotate( T_IM_IIP_UTIL_PARAM_RESIZE_ROTATE* const rr_param, const T_IM_IIP_UTIL_RR* const cfg )
{
	T_IM_IIP_PARAM_AFN*			afn;
	T_IM_IIP_PARAM_AFN_OPCOL_0*	afn_struct_param;
	T_IM_IIP_PARAM_STS*			sl;
	T_IM_IIP_UTIL_PHVSZ			phvsz;
	UINT32						mod_sz;

	/// Set Pointer of SDRAM parameter

	afn_struct_param = (T_IM_IIP_PARAM_AFN_OPCOL_0*)rr_param->param_buffer_addr;
	rr_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );

	afn = (T_IM_IIP_PARAM_AFN*)rr_param->param_buffer_addr;
	rr_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_AFN) );

	sl = (T_IM_IIP_PARAM_STS*)rr_param->param_buffer_addr;
	rr_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_STS) );


//	printf( "SIZE: %u, %u\n", im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) ) + im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_AFN) ) + im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_STS) ), D_IM_IIP_UTIL_RR_BUF_BYTES );

	/// Set SDRAM paramter

	imIipSetAfnStructParam( afn_struct_param, &cfg->src, &cfg->dst, cfg->rotation, cfg->flip );

	imIipSetAfnUnitParam( afn, (UINT32)afn_struct_param, cfg );

	phvsz.PHSZ1 = ( E_IM_IIP_PARAM_GHSZ_64PIX == afn->AFNCTL.bit.GHSZ ) ? 64 : 32;
	switch( afn->AFNCTL.bit.GVSZ ) {
		case E_IM_IIP_PARAM_GVSZ_SAME_AS_VERTICAL_PIX:
			 phvsz.PVSZ1 = afn_struct_param->SZ.bit.AFNDVSZ;
			 break;
		case E_IM_IIP_PARAM_GVSZ_256PIX:
			phvsz.PVSZ1 = 256;
			break;
		case E_IM_IIP_PARAM_GVSZ_128PIX:
			phvsz.PVSZ1 = 128;
			break;
		case E_IM_IIP_PARAM_GVSZ_64PIX:
			phvsz.PVSZ1 = 64;
			break;
		case E_IM_IIP_PARAM_GVSZ_32PIX:
			phvsz.PVSZ1 = 32;
			break;
		case E_IM_IIP_PARAM_GVSZ_16PIX:
			phvsz.PVSZ1 = 16;
			break;
		case E_IM_IIP_PARAM_GVSZ_8PIX:
			phvsz.PVSZ1 = 8;
			break;
		case E_IM_IIP_PARAM_GVSZ_4PIX:
			phvsz.PVSZ1 = 4;
			break;
		case E_IM_IIP_PARAM_GVSZ_2PIX:
			phvsz.PVSZ1 = 2;
			break;
		default:
			return D_IM_IIP_INVALID_ARG_ERR;
	}
	if( (afn->OUTSIZE.bit.OUTHSZ == 0) && (afn->OUTSIZE.bit.OUTVSZ == 0) ) {
		phvsz.PHSZ0 = phvsz.PHSZ1;
		phvsz.PVSZ0 = phvsz.PVSZ1;
	}
	else {
		mod_sz = afn->OUTSTARTPOS.bit.STARTX % phvsz.PHSZ1;
		phvsz.PHSZ0 = (mod_sz == 0) ? phvsz.PHSZ1 : (phvsz.PHSZ1 - mod_sz);
		mod_sz = afn->OUTSTARTPOS.bit.STARTY % phvsz.PVSZ1;
		phvsz.PVSZ0 = (mod_sz == 0) ? phvsz.PVSZ1 : (phvsz.PVSZ1 - mod_sz);
	}

	im_iip_set_sl_unit_param( sl, &phvsz, &cfg->dst.rect, &cfg->dst.gbl, cfg->pix_depth );

	afn->PIXIDEF.bit.IPIXID = rr_param->pixid[0];
	afn->AFNTOPCNF.bit.WAITCONF = im_iip_util_conv_portid( cfg->sl_unitid );

	sl->BASE.PIXIDDEF.bit.OPIXID = rr_param->pixid[1];
	sl->BASE.SL_TOPCNF0.bit.DATACONF = im_iip_util_conv_portid( cfg->afn_unitid );


	if( cfg->src.gbl.pix_format == E_IM_IIP_PFMT_BAYER ) {
		imIipUtilSetAfnRawInputUnit( afn, afn_struct_param, sl );
	}


	rr_param->p_param_afn = afn;
	rr_param->p_afn_struct_param = afn_struct_param;
	rr_param->p_param_sl = sl;

	im_iip_set_unitinftbl_param( &rr_param->unit_cfg_afn, cfg->afn_unitid, afn, 0ULL );
	im_iip_set_unitinftbl_param( &rr_param->unit_cfg_sl, cfg->sl_unitid, sl, rr_param->open_param.unitid_bitmask );

	return D_IM_IIP_OK;
}

static VOID imIipSetCscUnitParam( T_IM_IIP_PARAM_CSC* const csc,
									   const T_IM_IIP_UTIL_CSC* const cfg )
{
	INT32	loopcnt;

	memset( csc, '\0', sizeof(*csc) );

	csc->header0.bit.BeginningAddress = 0x0000;
	csc->header0.bit.WordLength = 25;
	csc->header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET;
//	csc->CSCTOPCNF.bit.DATACONF;	// set later
//	csc->CSCTOPCNF.bit.WAITCONF;	// set later

	for ( loopcnt = 0; loopcnt < 4; loopcnt++ ) {
		csc->CSCK[loopcnt].bit.CSCK_0 = cfg->csck[loopcnt][0];
		csc->CSCK[loopcnt].bit.CSCK_1 = cfg->csck[loopcnt][1];
		csc->CSCK[loopcnt].bit.CSCK_2 = cfg->csck[loopcnt][2];
		csc->CSCK[loopcnt].bit.CSCK_3 = cfg->csck[loopcnt][3];
	}

	csc->MDSEL.bit.MDSEL = cfg->csck_mode_sel;
	csc->ALPSEL.bit.ALPSEL = cfg->alpha_in_sel;
	csc->ALPSEL.bit.ALOSEL = cfg->alpha_out_sel;
	csc->ALPVAL.bit.ALPVAL = cfg->alpha_val;
	csc->MAXMIN.bit.MAXMIN0 = E_IM_IIP_PARAM_MAXMIN_THROUGH;
	csc->MAXMIN.bit.MAXMIN1 = E_IM_IIP_PARAM_MAXMIN_THROUGH;
	csc->MAXMIN.bit.MAXMIN2 = E_IM_IIP_PARAM_MAXMIN_THROUGH;
	csc->MAXMIN.bit.MAXMIN3 = E_IM_IIP_PARAM_MAXMIN_THROUGH;
	csc->OUTCLIP.bit.CLPMAX0 = 0x3FFF;
	csc->OUTCLIP.bit.CLPMIN0 = -0x4000;
	csc->OUTCLIP.bit.CLPMAX1 = 0x3FFF;
	csc->OUTCLIP.bit.CLPMIN1 = -0x4000;
	csc->OUTCLIP.bit.CLPMAX2 = 0x3FFF;
	csc->OUTCLIP.bit.CLPMIN2 = -0x4000;
	csc->OUTCLIP.bit.CLPMAX3 = 0xFF;
	csc->OUTCLIP.bit.CLPMIN3 = -0x100;
}

static VOID imIipUtilSetParamCsc( T_IM_IIP_UTIL_PARAM_CSC* const csc_param, const T_IM_IIP_UTIL_CSC* const cfg )
{
	T_IM_IIP_PARAM_1DL*			oned;
	T_IM_IIP_PARAM_CSC*			csc;
	T_IM_IIP_PARAM_STS*			sl;
	T_IM_IIP_UTIL_PHVSZ			phvsz;

	/// Set Pointer of SDRAM parameter

	oned = (T_IM_IIP_PARAM_1DL*)csc_param->param_buffer_addr;
	csc_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_1DL) );

	csc = (T_IM_IIP_PARAM_CSC*)csc_param->param_buffer_addr;
	csc_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_CSC) );

	sl = (T_IM_IIP_PARAM_STS*)csc_param->param_buffer_addr;
	csc_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_STS) );


	/// Set SDRAM paramter
	im_iip_set_phvsz_1d_sl( &phvsz, &cfg->dst );

	im_iip_set_1d_unit_param( oned, &phvsz, &cfg->src, cfg->pix_depth, cfg->ld_cache_select );

	imIipSetCscUnitParam( csc, cfg );

	im_iip_set_sl_unit_param( sl, &phvsz, &cfg->dst.rect, &cfg->dst.gbl, cfg->pix_depth );

	//Set Shift bit
	sl->BASE.SFT_0.bit.SFTVAL = cfg->sl_sftval;

	oned->PIXIDDEF.bit.IPIXID = csc_param->pixid[0];
	oned->LD_TOPCNF0.bit.WAITCONF = im_iip_util_conv_portid( cfg->csc_unitid );

	csc->CSCTOPCNF.bit.DATACONF = im_iip_util_conv_portid( cfg->ld_unitid );
	csc->CSCTOPCNF.bit.WAITCONF = im_iip_util_conv_portid( cfg->sl_unitid );

	sl->BASE.PIXIDDEF.bit.OPIXID = csc_param->pixid[1];
	sl->BASE.SL_TOPCNF0.bit.DATACONF = im_iip_util_conv_portid( cfg->csc_unitid );

	csc_param->p_param_1d = oned;
	csc_param->p_param_csc = csc;
	csc_param->p_param_sl = sl;

	im_iip_set_unitinftbl_param( &csc_param->unit_cfg_1d, cfg->ld_unitid, oned, 0ULL );
	im_iip_set_unitinftbl_param( &csc_param->unit_cfg_csc, cfg->csc_unitid, csc, 0ULL );
	im_iip_set_unitinftbl_param( &csc_param->unit_cfg_sl, cfg->sl_unitid, sl, csc_param->open_param.unitid_bitmask );
}

VOID im_iip_set_1d_unit_param( T_IM_IIP_PARAM_1DL* const p1D,
									  const T_IM_IIP_UTIL_PHVSZ* const phvsz,
									  const T_IM_IIP_UTIL_IMG_INT* const src,
									  const UINT32 pix_depth,
									  const E_IM_IIP_PARAM_CSEL cache_select )
{
	const T_IM_IIP_UTIL_RECT_INT* src_rect = &src->rect;

	memset( p1D, '\0', sizeof(*p1D) );

	p1D->header0.bit.BeginningAddress = 0x4;
	p1D->header0.bit.WordLength = 16;
	p1D->header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET;
//	p1D->LD_TOPCNF0.bit.WAITCONF;		// set later
	p1D->LD_TOPCNF1.bit.LINK_UID = 0x4; // dummy. initial value

//	p1D->PIXIDDEF.bit.IPIXID;	// set later
	p1D->LD_CTL.bit.LD_MODE = E_IM_IIP_PARAM_LD_MODE_NORMAL_LOAD;
	p1D->LD_CTL.bit.LD_OUT = 0;
	p1D->LD_CTL.bit.SLOW = E_IM_IIP_PARAM_SLOW_2PIX_CYC;
	p1D->LD_CTL.bit.SAVERD = 0;
	p1D->LD_CTL.bit.CSEL = cache_select;
	p1D->LD_PREFETCH.bit.PFOFF = E_IM_IIP_PARAM_PFOFF_RUN;
	p1D->LD_PREFETCH.bit.PF_PDIST = im_iip_get_PF_PDIST( pix_depth,
														 src->gbl.frame_type,
														 src->gbl.pix_format,
														 src->gbl.alpha );
	p1D->LD_PREFETCH.bit.PF_1ST = E_IM_IIP_PARAM_PF_1ST_ACCESS_BEFORE_PF;
	p1D->LD_PREFETCH.bit.PFB_NUM = 0;
	p1D->LD_PREFETCH.bit.PF_ADD = 0;

	p1D->LD_HSIZE.bit.HSTART = src_rect->left;
	p1D->LD_HSIZE.bit.HEND = src_rect->left + src_rect->width - 1;
	p1D->LD_VSIZE.bit.VSTART = src_rect->top;
	p1D->LD_VSIZE.bit.VEND = src_rect->top  + src_rect->lines - 1;

	p1D->LD_PHSZ.bit.PHSZ0 = phvsz->PHSZ0;
	p1D->LD_PHSZ.bit.PHSZ1 = phvsz->PHSZ1;
	p1D->LD_PVSZ.bit.PVSZ0 = phvsz->PVSZ0;
	p1D->LD_PVSZ.bit.PVSZ1 = phvsz->PVSZ1;
	p1D->UPLK_TARGET.bit.UPSU0 = E_IM_IIP_PARAM_UPSU_NONE;
	p1D->UPLK_TARGET.bit.UPSU1 = E_IM_IIP_PARAM_UPSU_NONE;
	p1D->UPLK_TARGET.bit.UPSU2 = 0;
	p1D->DWLK_TARGET.bit.DWSU0 = E_IM_IIP_PARAM_DWSU_NONE;
	p1D->DWLK_TARGET.bit.DWSU1 = E_IM_IIP_PARAM_DWSU_NONE;
	p1D->DWLK_TARGET.bit.DWSU2 = 0;
	p1D->LKNUM.bit.UPNUM = E_IM_IIP_PARAM_UPNUM_NONE;
	p1D->LKNUM.bit.DWNUM = E_IM_IIP_PARAM_DWNUM_NONE;
	p1D->RING.bit.URINGSIZE = 0;
	p1D->RING.bit.UMARGINIYSZ = 0;
	p1D->RING.bit.DRINGSIZE = 0;
}

VOID im_iip_set_sl_unit_param( T_IM_IIP_PARAM_STS* const sl,
									  const T_IM_IIP_UTIL_PHVSZ* const phvsz,
									  const T_IM_IIP_UTIL_RECT_INT* const dst_rect,
									  const T_IM_IIP_UTIL_IMG_GBL* const dst_gbl,
									  const UINT32 pix_depth )
{
	UINT32 max_val, min_val;

	memset( sl, '\0', sizeof(*sl) );

	sl->header0.bit.BeginningAddress = 0x0000;
	sl->header0.bit.WordLength = 26;
	sl->header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_LOAD_ONLY;
	sl->BASE.SL_TOPCNF0.bit.WAITCONF = E_IM_IIP_PARAM_PORTID_NONE;
//	sl->BASE.SL_TOPCNF0.bit.DATACONF;		// set later
//	sl->BASE.PIXIDDEF.bit.OPIXID;			// set later
	sl->BASE.PIXIDDEF.bit.CSEL = E_IM_IIP_PARAM_CSEL_0;	// dummy
	sl->BASE.PIXIDDEF.bit.DIV1ST = E_IM_IIP_PARAM_DIV1ST_1ST;
	sl->BASE.PIXIDDEF.bit.LKDIV = 0;

	sl->BASE.PLDUNIT_SL.bit.PLDUNIT_SL_LO = 0;
	sl->BASE.PLDUNIT_SL.bit.PLDUNIT_SL_HI = 0;

	sl->BASE.SL_CTL.bit.SL_MODE = 0;
	sl->BASE.SL_CTL.bit.LOADMD = 0;
	sl->BASE.SL_CTL.bit.MASKEN = E_IM_IIP_PARAM_MASKEN_NO_MASK;

	sl->BASE.OUTCOL.bit.OUTCOL = 0;

	sl->BASE.SL_HSIZE.bit.HSTART = dst_rect->left;
	sl->BASE.SL_HSIZE.bit.HEND = dst_rect->left + dst_rect->width - 1;
	sl->BASE.SL_VSIZE.bit.VSTART = dst_rect->top;
	sl->BASE.SL_VSIZE.bit.VEND = dst_rect->top  + dst_rect->lines - 1;
	sl->BASE.SL_PHSZ.bit.PHSZ0 = phvsz->PHSZ0;
	sl->BASE.SL_PHSZ.bit.PHSZ1 = phvsz->PHSZ1;
	sl->BASE.SL_PVSZ.bit.PVSZ0 = phvsz->PVSZ0;
	sl->BASE.SL_PVSZ.bit.PVSZ1 = phvsz->PVSZ1;

	sl->BASE.SEL_OPARA.bit.SEL_OPARA = 0;

	sl->BASE.OFSET_0.bit.OFSET = 0;
	imIipGetMaxMinValue( &max_val, &min_val, pix_depth, dst_gbl->sign_Y_G );
	sl->BASE.CLPTH_U_0.bit.CLPTH_U = max_val;
	sl->BASE.CLPTH_L_0.bit.CLPTH_L = min_val;
	sl->BASE.CLPVAL_U_0.bit.CLPVAL_U = sl->BASE.CLPTH_U_0.bit.CLPTH_U;
	sl->BASE.CLPVAL_L_0.bit.CLPVAL_L = sl->BASE.CLPTH_L_0.bit.CLPTH_L;
	sl->BASE.SFT_0.bit.SFTVAL = 0;
	sl->BASE.SFT_0.bit.SFTM = 0;
	sl->BASE.W14MD_0.bit.W14LSFT = 0;
	sl->BASE.W14MD_0.bit.W14SAT = 0;

	sl->header1.bit.BeginningAddress = 0x0200;
	sl->header1.bit.WordLength = 2;
	sl->header1.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET;
	sl->FILL_EN.bit.FILL_EN0 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN1 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN2 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN3 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN4 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN5 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN6 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN7 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN8 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN9 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN10 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN11 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN12 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN13 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN14 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN15 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN16 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN17 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN18 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
	sl->FILL_EN.bit.FILL_EN19 = E_IM_IIP_PARAM_FILL_EN_DISABLE;
}

INT32 Im_IIP_Get_MAXMON( T_IM_IIP_MAXMON* const mon )
{
	UINT32 loopcnt;

#ifdef CO_PARAM_CHECK
	if( mon == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_MAXMON INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	for( loopcnt = 0; loopcnt < 4; loopcnt++ ) {
		mon->max[loopcnt].value = IO_IIP.MAXMON[loopcnt].bit.MAXVAL;
		mon->max[loopcnt].pos_x = IO_IIP.MAXMON[loopcnt].bit.HPOINTMAX;
		mon->max[loopcnt].pos_y = IO_IIP.MAXMON[loopcnt].bit.VPOINTMAX;
		im_iip_get_reg_signed_a( mon->max[loopcnt].value, IO_IIP.MAXMON[loopcnt], union io_iip_maxmon, MAXVAL );
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

INT32 im_iip_util_resizerotate_main( T_IM_IIP_UTIL_PARAM_RESIZE_ROTATE* const rr_param, const T_IM_IIP_UTIL_RR* const cfg )
{
	INT32	retval;

	rr_param->open_param.unitid_bitmask = im_iip_util_conv_unitid_to_pldunit(cfg->afn_unitid)
										| im_iip_util_conv_unitid_to_pldunit(cfg->sl_unitid);
	rr_param->open_param.pixid_bitmask = cfg->src_pixid | cfg->dst_pixid;
	rr_param->open_param.open_res_bitmask = E_IM_IIP_OPEN_RES_NONE;

	if( cfg->resize_mode == E_IM_IIP_UTIL_RESIZE_MODE_BICUBIC ) {
		switch( cfg->bi_cubic_unitid ) {
			case E_IM_IIP_PARAM_SCUB_0:
				rr_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_BICUBIC0;
				break;
			case E_IM_IIP_PARAM_SCUB_1:
				rr_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_BICUBIC1;
				break;
			default:
				return D_IM_IIP_INVALID_ARG_ERR;
		}
	}
	switch( cfg->afn_cache_select ) {
		case E_IM_IIP_PARAM_CSEL_0:
			rr_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE0;
			break;
		case E_IM_IIP_PARAM_CSEL_1:
			rr_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE1;
			break;
		case E_IM_IIP_PARAM_CSEL_2:
			rr_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE2;
			break;
		default:
			return D_IM_IIP_INVALID_ARG_ERR;
	}

	rr_param->pixid[0] = im_iip_util_conv_pixid( cfg->src_pixid );
	if( rr_param->pixid[0] == E_IM_IIP_PIXID_INVALID ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}
	rr_param->pixid[1] = im_iip_util_conv_pixid( cfg->dst_pixid );
	if( rr_param->pixid[1] == E_IM_IIP_PIXID_INVALID ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}

	retval = Im_IIP_Open_SWTRG( rr_param->open_param.unitid_bitmask, rr_param->open_param.pixid_bitmask, rr_param->open_param.open_res_bitmask, rr_param->wait_param.wait_time );
	if( retval != D_IM_IIP_OK ) {
		return retval;
	}


	while( 1 ) {
		/// Set SDRAM parameter and UNITINFTBL parameter
		imIipUtilSetParamResizerotate( rr_param, cfg );

		/// Set IIP driver parameter
		im_iip_set_pixfmttbl_param( &rr_param->pixfmttbl[0], &cfg->src.gbl, cfg->pix_depth, NULL );
		im_iip_set_pixfmttbl_param( &rr_param->pixfmttbl[1], &cfg->dst.gbl, cfg->pix_depth, NULL );

		if( cfg->src.gbl.pix_format == E_IM_IIP_PFMT_BAYER ) {
			imIipUtilSetAfnRawInputPixfmttbl( &rr_param->pixfmttbl[0] );
		}

		im_iip_set_axi_param( cfg->afn_unitid, &rr_param->axi_id_afn, &rr_param->axi_cfg_afn, rr_param->param_master_IF );

		im_iip_set_axi_param( cfg->sl_unitid, &rr_param->axi_id_sl, &rr_param->axi_cfg_sl, rr_param->param_master_IF );

		/// Execute IIP
		retval = im_iip_util_exec_rotate( rr_param, cfg );
		if( retval != D_IM_IIP_OK ) {
			break;
		}

		// Unit start successful
		return retval;
	}

	// Error route
	(VOID)Im_IIP_Close_SWTRG( rr_param->open_param.unitid_bitmask, rr_param->open_param.pixid_bitmask, rr_param->open_param.open_res_bitmask );

	return retval;
}

INT32 im_iip_util_csc_main( T_IM_IIP_UTIL_PARAM_CSC* const csc_param, const T_IM_IIP_UTIL_CSC* const cfg, const INT32 wait_time )
{
	INT32	retval;
	T_IM_IIP_UTIL_ALPHA_INFO	alpha_info;

	csc_param->open_param.unitid_bitmask = im_iip_util_conv_unitid_to_pldunit(cfg->ld_unitid)
										 | im_iip_util_conv_unitid_to_pldunit(cfg->csc_unitid)
										 | im_iip_util_conv_unitid_to_pldunit(cfg->sl_unitid);
	csc_param->open_param.pixid_bitmask = cfg->src_pixid | cfg->dst_pixid;
	csc_param->open_param.open_res_bitmask = E_IM_IIP_OPEN_RES_NONE;

	switch( cfg->ld_cache_select ) {
		case E_IM_IIP_PARAM_CSEL_0:
			csc_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE0;
			break;
		case E_IM_IIP_PARAM_CSEL_1:
			csc_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE1;
			break;
		case E_IM_IIP_PARAM_CSEL_2:
			csc_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE2;
			break;
		default:
			return D_IM_IIP_INVALID_ARG_ERR;
	}

	csc_param->pixid[0] = im_iip_util_conv_pixid( cfg->src_pixid );
	if( csc_param->pixid[0] == E_IM_IIP_PIXID_INVALID ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}
	csc_param->pixid[1] = im_iip_util_conv_pixid( cfg->dst_pixid );
	if( csc_param->pixid[1] == E_IM_IIP_PIXID_INVALID ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}

	retval = Im_IIP_Open_SWTRG( csc_param->open_param.unitid_bitmask, csc_param->open_param.pixid_bitmask, csc_param->open_param.open_res_bitmask, csc_param->wait_param.wait_time );
	if( retval != D_IM_IIP_OK ) {
		return retval;
	}


	while( 1 ) {
		/// Set SDRAM parameter and UNITINFTBL parameter
		imIipUtilSetParamCsc( csc_param, cfg );

		/// Set IIP driver parameter
		alpha_info.alpha_depth = cfg->alpha_depth;
		alpha_info.alpha_subsampling = cfg->alpha_subsampling;
		im_iip_set_pixfmttbl_param( &csc_param->pixfmttbl[0], &cfg->src.gbl, cfg->pix_depth, &alpha_info );
		im_iip_set_pixfmttbl_param( &csc_param->pixfmttbl[1], &cfg->dst.gbl, cfg->pix_depth, &alpha_info );

		im_iip_set_axi_param( cfg->ld_unitid, &csc_param->axi_id_ld, &csc_param->axi_cfg_1d, csc_param->param_master_IF );

		im_iip_set_axi_param( cfg->sl_unitid, &csc_param->axi_id_sl, &csc_param->axi_cfg_sl, csc_param->param_master_IF );

		/// Execute IIP
		retval = im_iip_util_exec_csc( csc_param, cfg );
		if( retval != D_IM_IIP_OK ) {
			break;
		}

		// Unit start successful
		return retval;
	}

	// Error route
	(VOID)Im_IIP_Close_SWTRG( csc_param->open_param.unitid_bitmask, csc_param->open_param.pixid_bitmask, csc_param->open_param.open_res_bitmask );

	return retval;
}

ImIipDefine *im_iip_define_get(void)
{
 	 static ImIipDefine* self = NULL;
 	 if(!self){
 		self = k_object_new(IM_TYPE_IIP_DEFINE);
 		self->gimIipCallback = NULL;
 	 }
 	 else{
 		 k_object_ref(self);
 	 }
 	return self;
}


#endif	// CO_IM_IIP_ENABLE_UTILITY
