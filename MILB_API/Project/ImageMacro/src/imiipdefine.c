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
									  const UINT32 pixDepth,
									  const UCHAR sign )
{
	INT32 p;

	switch ( pixDepth ) {
		case ImIipDefine_D_IM_IIP_PDEPTH_8BITS:
			p = 8;
			break;
		case ImIipDefine_D_IM_IIP_PDEPTH_12BITS:
			p = 12;
			break;
//		case ImIipDefine_D_IM_IIP_PDEPTH_16BITS:
		default:
			p = 14;
			break;
	}

	if( ImIipDefine_D_IM_IIP_SIGNED_DATA == sign ) {
		*min_val = (UINT32)(-(1 << (p - 1)));
		*max_val = (UINT32)((1 << (p - 1)) - 1);
	}
	else {
		*min_val = 0x0000;
		*max_val = (UINT32)((1 << p) - 1);
	}
}

static void imIipSetAfnStructFlip( T_IM_IIP_PARAM_AFN_OPCOL_0* const afn_struct_param,
										 const TImIipUtilImg* const src,
										 const EImIipUtilRotate rotation,
										 const EImIipUtilFlip flip)
{
	U_IM_IIP_PARAM_AFN_STAXY	set_sta;
	INT32						wok;
	static const int sta_pos_tbl[ImIipStruct_E_IM_IIP_UTIL_ROTATE_MAX][ImIipStruct_E_IM_IIP_UTIL_FLIP_MAX] = {
		// off							mirror						reverse						mirror_reverse
		{ ImIipDefine_D_IM_IIP_UTIL_ORIGIN,			ImIipDefine_D_IM_IIP_UTIL_TOPRIGHT,		ImIipDefine_D_IM_IIP_UTIL_BOTTOMLEFT,	ImIipDefine_D_IM_IIP_UTIL_BOTTOMRIGHT	},	// 0
		{ ImIipDefine_D_IM_IIP_UTIL_BOTTOMLEFT,		ImIipDefine_D_IM_IIP_UTIL_ORIGIN,		ImIipDefine_D_IM_IIP_UTIL_BOTTOMRIGHT,	ImIipDefine_D_IM_IIP_UTIL_TOPRIGHT		},	// 90
		{ ImIipDefine_D_IM_IIP_UTIL_BOTTOMRIGHT,	ImIipDefine_D_IM_IIP_UTIL_BOTTOMLEFT,	ImIipDefine_D_IM_IIP_UTIL_TOPRIGHT,		ImIipDefine_D_IM_IIP_UTIL_ORIGIN		},	// 180
		{ ImIipDefine_D_IM_IIP_UTIL_TOPRIGHT,		ImIipDefine_D_IM_IIP_UTIL_BOTTOMRIGHT,	ImIipDefine_D_IM_IIP_UTIL_ORIGIN,		ImIipDefine_D_IM_IIP_UTIL_BOTTOMLEFT	},	// 270
	};

	switch (sta_pos_tbl[rotation][flip])
	{
	case ImIipDefine_D_IM_IIP_UTIL_TOPRIGHT:
		set_sta.bit.STAX = ImIipDefine_IM_IIP_FIXED_POINT(src->rect.left + src->rect.width - 1.0);
		set_sta.bit.STAY = ImIipDefine_IM_IIP_FIXED_POINT(src->rect.top);
		break;
	case ImIipDefine_D_IM_IIP_UTIL_BOTTOMLEFT:
		set_sta.bit.STAX = ImIipDefine_IM_IIP_FIXED_POINT(src->rect.left);
		set_sta.bit.STAY = ImIipDefine_IM_IIP_FIXED_POINT(src->rect.top + src->rect.lines - 1.0);
		break;
	case ImIipDefine_D_IM_IIP_UTIL_BOTTOMRIGHT:
		set_sta.bit.STAX = ImIipDefine_IM_IIP_FIXED_POINT(src->rect.left + src->rect.width - 1.0);
		set_sta.bit.STAY = ImIipDefine_IM_IIP_FIXED_POINT(src->rect.top  + src->rect.lines - 1.0);
		break;
	case ImIipDefine_D_IM_IIP_UTIL_ORIGIN:
		set_sta.bit.STAX = ImIipDefine_IM_IIP_FIXED_POINT(src->rect.left);
		set_sta.bit.STAY = ImIipDefine_IM_IIP_FIXED_POINT(src->rect.top);
		break;
	default:
		// Don't set paramter about Mirror/Reverse in cases of error.
		return;
	}

	if (flip == ImIipStruct_E_IM_IIP_UTIL_FLIP_REVERSE)
	{
		afn_struct_param->STAXY0.bit.STAX = set_sta.bit.STAX;
		afn_struct_param->STAXY0.bit.STAY = set_sta.bit.STAY;

		// make y-component negative to flip vertical
		// DYX = -DYX
		ImIipDefine_IM_IIP_GET_REG_SIGNED_A( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, -wok );

		// DYY = -DYY
		ImIipDefine_IM_IIP_GET_REG_SIGNED_A( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, -wok );
	}
	else if (flip == ImIipStruct_E_IM_IIP_UTIL_FLIP_MIRROR)
	{
		afn_struct_param->STAXY0.bit.STAX = set_sta.bit.STAX;
		afn_struct_param->STAXY0.bit.STAY = set_sta.bit.STAY;

		// make x-component negative to flip horizontal
		// DXY = -DXY
		ImIipDefine_IM_IIP_GET_REG_SIGNED_A( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, -wok );
		afn_struct_param->D_OUT_IN_0.bit.DXY = -(afn_struct_param->D_OUT_IN_0.bit.DXY);

		// DXX = -DXX
		ImIipDefine_IM_IIP_GET_REG_SIGNED_A( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, -wok );
	}
	else if (flip == ImIipStruct_E_IM_IIP_UTIL_FLIP_MIR_AND_REV)
	{
		afn_struct_param->STAXY0.bit.STAX = set_sta.bit.STAX;
		afn_struct_param->STAXY0.bit.STAY = set_sta.bit.STAY;

		// make x and y component negative to flip horizontal and vertical
		// DXY = -DXY
		ImIipDefine_IM_IIP_GET_REG_SIGNED_A( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, -wok );
		afn_struct_param->D_OUT_IN_0.bit.DXY = -(afn_struct_param->D_OUT_IN_0.bit.DXY);

		// DXX = -DXX
		ImIipDefine_IM_IIP_GET_REG_SIGNED_A( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, -wok );

		// DYX = -DYX
		ImIipDefine_IM_IIP_GET_REG_SIGNED_A( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, -wok );

		// DYY = -DYY
		ImIipDefine_IM_IIP_GET_REG_SIGNED_A( wok, afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, -wok );
	}
	else
	{
		afn_struct_param->STAXY0.bit.STAX = set_sta.bit.STAX;
		afn_struct_param->STAXY0.bit.STAY = set_sta.bit.STAY;
	}
}

static VOID imIipSetAfnStructParam( T_IM_IIP_PARAM_AFN_OPCOL_0* const afn_struct_param,
										 const TImIipUtilImg* const src,
										 const TImIipUtilImgInt* const dst,
										 const EImIipUtilRotate rotation,
										 const EImIipUtilFlip flip )
{
	INT32	h_pit_fixed_point;
	INT32	v_pit_fixed_point;

	memset( afn_struct_param, '\0', sizeof(*afn_struct_param) );

	if( rotation == ImIipStruct_E_IM_IIP_UTIL_ROTATE_000 ) {
		h_pit_fixed_point = (((INT32)src->rect.width - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.width - 1);
		v_pit_fixed_point = (((INT32)src->rect.lines - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.lines - 1);

		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, h_pit_fixed_point );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY, 0x0 );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, 0x0 );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, v_pit_fixed_point );
	}
	else if( rotation == ImIipStruct_E_IM_IIP_UTIL_ROTATE_090 ) {
		h_pit_fixed_point = (((INT32)src->rect.width - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.lines - 1);
		v_pit_fixed_point = (((INT32)src->rect.lines - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.width - 1);

		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, 0x0 );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY, - v_pit_fixed_point );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, h_pit_fixed_point );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, 0x0 );
	}
	else if( rotation == ImIipStruct_E_IM_IIP_UTIL_ROTATE_270 ) {
		h_pit_fixed_point = (((INT32)src->rect.width - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.lines - 1);
		v_pit_fixed_point = (((INT32)src->rect.lines - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.width - 1);

		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, 0x0 );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY, v_pit_fixed_point );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, - h_pit_fixed_point );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, 0x0 );
	}
	else {
		// ImIipStruct_E_IM_IIP_UTIL_ROTATE_180
		h_pit_fixed_point = (((INT32)src->rect.width - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.width - 1);
		v_pit_fixed_point = (((INT32)src->rect.lines - 1) * D_IM_IIP_PARAM_AFN_VAL_1_0) / (dst->rect.lines - 1);

		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXX, - h_pit_fixed_point );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DXY, 0x0 );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYX, 0x0 );
		ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->D_OUT_IN_0, U_IM_IIP_PARAM_AFN_D_OUT_IN, DYY, - v_pit_fixed_point );
	}

	afn_struct_param->SZ.bit.AFNDVSZ = dst->rect.lines;
	afn_struct_param->SZ.bit.AFNDHSZ = dst->rect.width;

	imIipSetAfnStructFlip( afn_struct_param, src, rotation, flip );
}

static VOID imIipSetAfnUnitParam( T_IM_IIP_PARAM_AFN* const afn,
									   const ULONG afn_struct_param_addr,
									   const TImIipUtilRr* const cfg )
{
	const TImIipUtilRectInt* dst_rect = &cfg->dst.rect;
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
	if( (ImIipStruct_E_IM_IIP_UTIL_ROTATE_090 == cfg->rotation) ||
		 (ImIipStruct_E_IM_IIP_UTIL_ROTATE_270 == cfg->rotation) ) {
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
	afn->PIXIDEF.bit.CSEL = cfg->afnCacheSelect;
	afn->CALMETHOD.bit.OPCOL = 0;
	afn->CALMETHOD.bit.ITMD = cfg->resizeMode;
	afn->CALMETHOD.bit.ARA = E_IM_IIP_PARAM_ARA_ITMD;
	afn->CALMETHOD.bit.FILMD = 0;
	if( cfg->resizeMode == ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BILINEAR ) {
		afn->CALMETHOD.bit.DANTI = 1;
		afn->CALMETHOD.bit.AANTI = 1;
	}
	else {
		afn->CALMETHOD.bit.DANTI = 0;
		afn->CALMETHOD.bit.AANTI = 0;
	}
	switch( cfg->afnUnitid ) {
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN0:
			afn->CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN0;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN1:
			afn->CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN1;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN2:
			afn->CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN2;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN3:
			afn->CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN3;
			break;
		default:
			afn->CALMETHOD.bit.CUBSEL = E_IM_IIP_PARAM_CUBSEL_AFN0;	// Failsafe
			break;
	}
	afn->CALMETHOD.bit.SCUB = cfg->biCubicUnitid;
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
	imIipGetMaxMinValue( &max_val, &min_val, cfg->pixDepth, cfg->src.gbl.signYG );
	afn->CLIPLVLY.bit.CLIPLVLYH = max_val;
	afn->CLIPLVLY.bit.CLIPLVLYL = min_val;
	imIipGetMaxMinValue( &max_val, &min_val, cfg->pixDepth, cfg->src.gbl.signCbB );
	afn->CLIPLVLB.bit.CLIPLVLBH = max_val;
	afn->CLIPLVLB.bit.CLIPLVLBL = min_val;
	imIipGetMaxMinValue( &max_val, &min_val, cfg->pixDepth, cfg->src.gbl.signCrR );
	afn->CLIPLVLR.bit.CLIPLVLRH = max_val;
	afn->CLIPLVLR.bit.CLIPLVLRL = min_val;
	imIipGetMaxMinValue( &max_val, &min_val, cfg->pixDepth, cfg->src.gbl.signD3 );
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

	ImIipDefine_IM_IIP_GET_REG_SIGNED_A( wok, afn_struct_param->STAXY0, U_IM_IIP_PARAM_AFN_STAXY, STAX );
	wok /= 2;
	ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->STAXY0, U_IM_IIP_PARAM_AFN_STAXY, STAX, wok );
	ImIipDefine_IM_IIP_GET_REG_SIGNED_A( wok, afn_struct_param->STAXY0, U_IM_IIP_PARAM_AFN_STAXY, STAY );
	wok /= 2;
	ImIipDefine_IM_IIP_SET_REG_SIGNED_A( afn_struct_param->STAXY0, U_IM_IIP_PARAM_AFN_STAXY, STAY, wok );

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

static VOID imIipUtilSetAfnRawInputPixfmttbl( TImIipPixfmttbl* const in_pixfmttbl )
{
	in_pixfmttbl->lineBytes.yG *= 2;
	in_pixfmttbl->lineBytes.cbB *= 2;
	in_pixfmttbl->lineBytes.crR *= 2;
	in_pixfmttbl->width *= 2;
	in_pixfmttbl->lines *= 2;
}

static INT32 imIipUtilSetParamResizerotate( TImIipUtilParamResizeRotate* const rr_param, const TImIipUtilRr* const cfg )
{
	T_IM_IIP_PARAM_AFN*			afn;
	T_IM_IIP_PARAM_AFN_OPCOL_0*	afn_struct_param;
	T_IM_IIP_PARAM_STS*			sl;
	TImIipUtilPhvsz			phvsz;
	UINT32						mod_sz;

	/// Set Pointer of SDRAM parameter

	afn_struct_param = (T_IM_IIP_PARAM_AFN_OPCOL_0*)rr_param->paramBufferAddr;
	rr_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) );

	afn = (T_IM_IIP_PARAM_AFN*)rr_param->paramBufferAddr;
	rr_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_AFN) );

	sl = (T_IM_IIP_PARAM_STS*)rr_param->paramBufferAddr;
	rr_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_STS) );


//	printf( "SIZE: %u, %u\n", ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_AFN_OPCOL_0) ) + ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_AFN) ) + ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_STS) ), ImIipDefine_D_IM_IIP_UTIL_RR_BUF_BYTES );

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
			return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
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

	im_iip_define_set_sl_unit_param(NULL, sl, &phvsz, &cfg->dst.rect, &cfg->dst.gbl, cfg->pixDepth );

	afn->PIXIDEF.bit.IPIXID = rr_param->pixid[0];
	afn->AFNTOPCNF.bit.WAITCONF = im_iip_sub_util_conv_portid( cfg->slUnitid );

	sl->BASE.PIXIDDEF.bit.OPIXID = rr_param->pixid[1];
	sl->BASE.SL_TOPCNF0.bit.DATACONF = im_iip_sub_util_conv_portid( cfg->afnUnitid );


	if( cfg->src.gbl.pixFormat == ImIipStruct_E_IM_IIP_PFMT_BAYER ) {
		imIipUtilSetAfnRawInputUnit( afn, afn_struct_param, sl );
	}


	rr_param->pParamAfn = afn;
	rr_param->pAfnStructParam = afn_struct_param;
	rr_param->pParamSl = sl;

	im_iip_sub_set_unitinftbl_param(NULL,&rr_param->unitCfgAfn, cfg->afnUnitid, afn, 0ULL );
	im_iip_sub_set_unitinftbl_param( NULL,&rr_param->unitCfgSl, cfg->slUnitid, sl, rr_param->openParam.unitidBitmask );

	return ImIipDefine_D_IM_IIP_OK;
}

static VOID imIipSetCscUnitParam( T_IM_IIP_PARAM_CSC* const csc,
									   const TImIipUtilCsc* const cfg )
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

	csc->MDSEL.bit.MDSEL = cfg->csckModeSel;
	csc->ALPSEL.bit.ALPSEL = cfg->alphaInSel;
	csc->ALPSEL.bit.ALOSEL = cfg->alphaOutSel;
	csc->ALPVAL.bit.ALPVAL = cfg->alphaVal;
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

static VOID imIipUtilSetParamCsc( TImIipUtilParamCsc* const csc_param, const TImIipUtilCsc* const cfg )
{
	T_IM_IIP_PARAM_1DL*			oned;
	T_IM_IIP_PARAM_CSC*			csc;
	T_IM_IIP_PARAM_STS*			sl;
	TImIipUtilPhvsz			phvsz;

	/// Set Pointer of SDRAM parameter

	oned = (T_IM_IIP_PARAM_1DL*)csc_param->paramBufferAddr;
	csc_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_1DL) );

	csc = (T_IM_IIP_PARAM_CSC*)csc_param->paramBufferAddr;
	csc_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_CSC) );

	sl = (T_IM_IIP_PARAM_STS*)csc_param->paramBufferAddr;
	csc_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_STS) );


	/// Set SDRAM paramter
	im_iip_sub_set_phvsz_1d_sl( NULL,&phvsz, &cfg->dst );

	im_iip_define_set_1d_unit_param(NULL, oned, &phvsz, &cfg->src, cfg->pixDepth, cfg->ldCacheSelect );

	imIipSetCscUnitParam( csc, cfg );

	im_iip_define_set_sl_unit_param(NULL, sl, &phvsz, &cfg->dst.rect, &cfg->dst.gbl, cfg->pixDepth );

	//Set Shift bit
	sl->BASE.SFT_0.bit.SFTVAL = cfg->slSftval;

	oned->PIXIDDEF.bit.IPIXID = csc_param->pixid[0];
	oned->LD_TOPCNF0.bit.WAITCONF = im_iip_sub_util_conv_portid( cfg->cscUnitid );

	csc->CSCTOPCNF.bit.DATACONF = im_iip_sub_util_conv_portid( cfg->ldUnitid );
	csc->CSCTOPCNF.bit.WAITCONF = im_iip_sub_util_conv_portid( cfg->slUnitid );

	sl->BASE.PIXIDDEF.bit.OPIXID = csc_param->pixid[1];
	sl->BASE.SL_TOPCNF0.bit.DATACONF = im_iip_sub_util_conv_portid( cfg->cscUnitid );

	csc_param->pParam1D = oned;
	csc_param->pParamCsc = csc;
	csc_param->pParamSl = sl;

	im_iip_sub_set_unitinftbl_param(NULL,  &csc_param->unitCfg1D, cfg->ldUnitid, oned, 0ULL );
	im_iip_sub_set_unitinftbl_param( NULL, &csc_param->unitCfgCsc, cfg->cscUnitid, csc, 0ULL );
	im_iip_sub_set_unitinftbl_param( NULL, &csc_param->unitCfgSl, cfg->slUnitid, sl, csc_param->openParam.unitidBitmask );
}

VOID im_iip_define_set_1d_unit_param( ImIipDefine* self, T_IM_IIP_PARAM_1DL* const p1D,
									  const TImIipUtilPhvsz* const phvsz,
									  const TImIipUtilImgInt* const src,
									  const UINT32 pixDepth,
									  const E_IM_IIP_PARAM_CSEL cache_select )
{
	const TImIipUtilRectInt* src_rect = &src->rect;

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
	p1D->LD_PREFETCH.bit.PF_PDIST = im_iip_sub_get_pf_pdist( pixDepth,
														 src->gbl.frameType,
														 src->gbl.pixFormat,
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

VOID im_iip_define_set_sl_unit_param(ImIipDefine* self, T_IM_IIP_PARAM_STS* const sl,
									  const TImIipUtilPhvsz* const phvsz,
									  const TImIipUtilRectInt* const dst_rect,
									  const TImIipUtilImgGbl* const dst_gbl,
									  const UINT32 pixDepth )
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
	imIipGetMaxMinValue( &max_val, &min_val, pixDepth, dst_gbl->signYG );
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

INT32 Im_IIP_Get_MAXMON( TImIipMaxmon* const mon )
{
	UINT32 loopcnt;

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( mon == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Get_MAXMON INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	for( loopcnt = 0; loopcnt < 4; loopcnt++ ) {
		mon->max[loopcnt].value = IO_IIP.MAXMON[loopcnt].bit.MAXVAL;
		mon->max[loopcnt].posX = IO_IIP.MAXMON[loopcnt].bit.HPOINTMAX;
		mon->max[loopcnt].posY = IO_IIP.MAXMON[loopcnt].bit.VPOINTMAX;
		ImIipDefine_IM_IIP_GET_REG_SIGNED_A( mon->max[loopcnt].value, IO_IIP.MAXMON[loopcnt], union io_iip_maxmon, MAXVAL );
	}

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

INT32 im_iip_define_util_resizerotate_main( TImIipUtilParamResizeRotate* const rr_param, const TImIipUtilRr* const cfg )
{
	INT32	retval;

	rr_param->openParam.unitidBitmask = ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->afnUnitid)
										| ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->slUnitid);
	rr_param->openParam.pixidBitmask = cfg->srcPixid | cfg->dstPixid;
	rr_param->openParam.openResBitmask = ImIipStruct_E_IM_IIP_OPEN_RES_NONE;

	if( cfg->resizeMode == ImIipStruct_E_IM_IIP_UTIL_RESIZE_MODE_BICUBIC ) {
		switch( cfg->biCubicUnitid ) {
			case E_IM_IIP_PARAM_SCUB_0:
				rr_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_BICUBIC0;
				break;
			case E_IM_IIP_PARAM_SCUB_1:
				rr_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_BICUBIC1;
				break;
			default:
				return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
		}
	}
	switch( cfg->afnCacheSelect ) {
		case E_IM_IIP_PARAM_CSEL_0:
			rr_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0;
			break;
		case E_IM_IIP_PARAM_CSEL_1:
			rr_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE1;
			break;
		case E_IM_IIP_PARAM_CSEL_2:
			rr_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE2;
			break;
		default:
			return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	rr_param->pixid[0] = im_iip_sub_util_conv_pixid( cfg->srcPixid );
	if( rr_param->pixid[0] == ImIipStruct_E_IM_IIP_PIXID_INVALID ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
	rr_param->pixid[1] = im_iip_sub_util_conv_pixid( cfg->dstPixid );
	if( rr_param->pixid[1] == ImIipStruct_E_IM_IIP_PIXID_INVALID ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	retval = Im_IIP_Open_SWTRG( rr_param->openParam.unitidBitmask, rr_param->openParam.pixidBitmask, rr_param->openParam.openResBitmask, rr_param->waitParam.waitTime );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
		return retval;
	}


	while( 1 ) {
		/// Set SDRAM parameter and UNITINFTBL parameter
		imIipUtilSetParamResizerotate( rr_param, cfg );

		/// Set IIP driver parameter
		im_iip_sub_set_pixfmttbl_param(NULL, &rr_param->pixfmttbl[0], &cfg->src.gbl, cfg->pixDepth, NULL );
		im_iip_sub_set_pixfmttbl_param(NULL, &rr_param->pixfmttbl[1], &cfg->dst.gbl, cfg->pixDepth, NULL );

		if( cfg->src.gbl.pixFormat == ImIipStruct_E_IM_IIP_PFMT_BAYER ) {
			imIipUtilSetAfnRawInputPixfmttbl( &rr_param->pixfmttbl[0] );
		}

		im_iip_new_set_axi_param( NULL,cfg->afnUnitid, &rr_param->axiIdAfn, &rr_param->axiCfgAfn, rr_param->paramMasterIf );

		im_iip_new_set_axi_param(  NULL,cfg->slUnitid, &rr_param->axiIdSl, &rr_param->axiCfgSl, rr_param->paramMasterIf );

		/// Execute IIP
		retval = im_iip_new_util_exec_rotate( rr_param, cfg );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			break;
		}

		// Unit start successful
		return retval;
	}

	// Error route
	(VOID)Im_IIP_Close_SWTRG( rr_param->openParam.unitidBitmask, rr_param->openParam.pixidBitmask, rr_param->openParam.openResBitmask );

	return retval;
}

INT32 im_iip_define_util_csc_main(TImIipUtilParamCsc* const csc_param, const TImIipUtilCsc* const cfg, const INT32 waitTime )
{
	INT32	retval;
	TImIipUtilAlphaInfo	alpha_info;

	csc_param->openParam.unitidBitmask = ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->ldUnitid)
										 | ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->cscUnitid)
										 | ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->slUnitid);
	csc_param->openParam.pixidBitmask = cfg->srcPixid | cfg->dstPixid;
	csc_param->openParam.openResBitmask = ImIipStruct_E_IM_IIP_OPEN_RES_NONE;

	switch( cfg->ldCacheSelect ) {
		case E_IM_IIP_PARAM_CSEL_0:
			csc_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0;
			break;
		case E_IM_IIP_PARAM_CSEL_1:
			csc_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE1;
			break;
		case E_IM_IIP_PARAM_CSEL_2:
			csc_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE2;
			break;
		default:
			return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	csc_param->pixid[0] = im_iip_sub_util_conv_pixid( cfg->srcPixid );
	if( csc_param->pixid[0] == ImIipStruct_E_IM_IIP_PIXID_INVALID ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
	csc_param->pixid[1] = im_iip_sub_util_conv_pixid( cfg->dstPixid );
	if( csc_param->pixid[1] == ImIipStruct_E_IM_IIP_PIXID_INVALID ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	retval = Im_IIP_Open_SWTRG( csc_param->openParam.unitidBitmask, csc_param->openParam.pixidBitmask, csc_param->openParam.openResBitmask, csc_param->waitParam.waitTime );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
		return retval;
	}


	while( 1 ) {
		/// Set SDRAM parameter and UNITINFTBL parameter
		imIipUtilSetParamCsc( csc_param, cfg );

		/// Set IIP driver parameter
		alpha_info.alphaDepth = cfg->alphaDepth;
		alpha_info.alphaSubsampling = cfg->alphaSubsampling;
		im_iip_sub_set_pixfmttbl_param(NULL, &csc_param->pixfmttbl[0], &cfg->src.gbl, cfg->pixDepth, &alpha_info );
		im_iip_sub_set_pixfmttbl_param(NULL, &csc_param->pixfmttbl[1], &cfg->dst.gbl, cfg->pixDepth, &alpha_info );

		im_iip_new_set_axi_param(  NULL,cfg->ldUnitid, &csc_param->axiIdLd, &csc_param->axiCfg1D, csc_param->paramMasterIf );

		im_iip_new_set_axi_param(  NULL,cfg->slUnitid, &csc_param->axiIdSl, &csc_param->axiCfgSl, csc_param->paramMasterIf );

		/// Execute IIP
		retval = im_iip_new_util_exec_csc( csc_param, cfg );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			break;
		}

		// Unit start successful
		return retval;
	}

	// Error route
	(VOID)Im_IIP_Close_SWTRG( csc_param->openParam.unitidBitmask, csc_param->openParam.pixidBitmask, csc_param->openParam.openResBitmask );

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
