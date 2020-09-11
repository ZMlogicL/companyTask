/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhangxinyue
*@brief               :CtImIipGpc类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif   /*1*/
#endif  /*CO_CT_IM_IIP_DISABLE*/

// for memcpy
#include <string.h>

// CT header
#include "ct_im_iip.h"
#include <target/cpu_tkernel/basefw/MILB_API/Project/ImageMacro/src/imiipparamenum.h>
#include "ctimiipgpc.h"      
#include "ctimiipgpc1.h"
#include "ctimiipgpc2.h"

// im_iip header
#include "im_iip.h"

// MILB register header
#include "jdsiip.h"

// for Memory barrier
#include "dd_arm.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImIipGpc, ct_im_iip_gpc);
#define CT_IM_IIP_GPC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImIipGpcPrivate,CT_TYPE_IM_IIP_GPC))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#undef CtImIipGpc_Ddim_Print
#define CtImIipGpc_Ddim_Print(arg)		{ddim_user_custom_printf arg;}		/**< printf function inside DDIM */
#endif

#define CtImIipGpc_D_GPC_STEPNUM_13_1_3		(10)
#endif /*CO_CT_IM_IIP_DISABLE*/

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
#ifndef CO_CT_IM_IIP_DISABLE
typedef struct{
	TImIipParamGpcSeqCtrl					seq;
	TImIipParamGpcPrecal						precalP0D0D1;	// Input port0 D0-D1
	TImIipParamGpcPrecal						precalP0D2D3;	// Input port0 D2-D3
	TImIipParamGpcPrecal						precalP1D0D1;	// Input port1 D0-D1
	TImIipParamGpcPrecal						precalP1D2D3;	// Input port1 D2-D3
	TImIipParamGpcCalc							calc;							// D0~D2
	TImIipParamGpcInterCompCalc	interCompCalc;
} TImIzaParamGpcConfig13_1_3;

typedef struct {
	E_IM_IIP_PFMT	pfmt;
	E_IM_IIP_FTYPE	ffmt;
	kushort				gWidth;
	kushort				width;
	kushort				lines;
	kulong					addrY;
	kulong					addrC;
} TCtIipGpcImg;
#endif /*CO_CT_IM_IIP_DISABLE*/

struct _CtImIipGpcPrivate
{
#ifndef CO_CT_IM_IIP_DISABLE
	kushort				staX;
	kushort				staY;
	TCtIipGpcImg		srcA;
	TCtIipGpcImg		srcB;
	TCtIipGpcImg		dst;
	kulong					alphaAddr;
#endif

	CtImIipGpc1* gpc1;
	CtImIipGpc2* gpc2;
};

#ifndef CO_CT_IM_IIP_DISABLE
#ifdef __GNUC__
static TImIipParamGpc	 S_G_CT_IM_IIP_UNIT_PARAM_GPC __attribute__((aligned(8)));	// Needs 8bytes align
#else
static __align(8) TImIipParamGpc S_G_CT_IM_IIP_UNIT_PARAM_GPC;									// Needs 8bytes align
#endif
#endif /*CO_CT_IM_IIP_DISABLE*/

/*
 * DECLS
 */
#ifndef CO_CT_IM_IIP_DISABLE
static kulong 		ctImIipGpcSetPnsz0(CtImIipGpc *self, kulong sta, kulong pnsz1);
static kint32 		ctImIipGpcSetBlend(CtImIipGpc *self, KType funcNm);
#endif /*CO_CT_IM_IIP_DISABLE*/

static void ct_im_iip_gpc_constructor(CtImIipGpc *self) 
{
	CtImIipGpcPrivate *priv = CT_IM_IIP_GPC_GET_PRIVATE(self);

	priv->gpc1 = ct_im_iip_gpc1_new();
	priv->gpc2 = ct_im_iip_gpc2_new();
}

static void ct_im_iip_gpc_destructor(CtImIipGpc *self) 
{
	CtImIipGpcPrivate *priv = CT_IM_IIP_GPC_GET_PRIVATE(self);
	if(priv->gpc1){
		k_object_unref(priv->gpc1);
		priv->gpc1 = NULL;
	}
	if(priv->gpc2){
		k_object_unref(priv->gpc2);
		priv->gpc2 = NULL;
	}
}

/*
 * IMPL
 */
#ifndef CO_CT_IM_IIP_DISABLE
#ifdef __GNUC__
static TImIzaParamGpcConfig13_1_3 gCtImIipGpcConfig_13_1_3 __attribute__((aligned(64))) = { // Needs 64bytes align
#else
static __align(64) TImIzaParamGpcConfig13_1_3 gCtImIipGpcConfig_13_1_3 = {					// Needs 64bytes align
#endif
	.seq = {
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_SEQ_CTRL,
		.PARACNT.bit.SEQEN = 0,		// Sequence dont start.
		.PARACNT.bit.LPARA = 0,		// read next parameter.
		.SEQLOOP = CtImIip_D_IM_IIP_VGA_LINES,
		.SEQCTL.bit = {
			.STEPNUM = CtImIipGpc_D_GPC_STEPNUM_13_1_3,

			.CNTEND_0 	= CtImIip_D_IM_IIP_VGA_WIDTH,
			.SEQCONF_0 = 0,	// Use parameter 0.
			.CNFOUT_0 = 1,		// Enable output

			.CNTEND_1 = 0,		// dummy(invalid)
			.SEQCONF_1 = 0,	// dummy(invalid)
			.CNFOUT_1 = 0,		// Disable output

			.CNTEND_2 = 0,		// dummy(invalid)
			.SEQCONF_2 = 0,	// dummy(invalid)
			.CNFOUT_2 = 0,		// Disable output

			.CNTEND_3 = 0,		// dummy(invalid)
			.SEQCONF_3 = 0,	// dummy(invalid)
			.CNFOUT_3 = 0,		// Disable output
		},
	},
	.precalP0D0D1 = {		// Through
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P0_D0_1,
		.PARACNT.bit.SEQEN = 0,		// Sequence dont start.
		.PARACNT.bit.LPARA = 0,		// read next parameter.
		.PRECAL[0].bit = {	// D0
			.PREOFSET = 0,
			.PRECLIPMAX = 0x3FFF,
			.PRECTHMAX = 0x3FFF,
			.PRECLIPMIN = 0x4000,
			.PRECTHMIN = 0x4000,
			.PREAE = 0,
		},
		.PRECAL[1].bit = {	// D1
			.PREOFSET = 0,
			.PRECLIPMAX = 0xFF,
			.PRECTHMAX = 0xFF,
			.PRECLIPMIN = 0x100,
			.PRECTHMIN = 0x100,
			.PREAE = 0,
		},
	},
	.precalP0D2D3 = {		// Through
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P0_D2_3,
		.PARACNT.bit.SEQEN = 0,		// Sequence dont start.
		.PARACNT.bit.LPARA = 0,		// read next parameter.
		.PRECAL[0].bit = {	// D2
			.PREOFSET = 0,
			.PRECLIPMAX = 0xFF,
			.PRECTHMAX = 0xFF,
			.PRECLIPMIN = 0x100,
			.PRECTHMIN = 0x100,
			.PREAE = 0,
		},
		.PRECAL[1].bit = {	// D3
			.PREOFSET = 0,
			.PRECLIPMAX = 0xFF,
			.PRECTHMAX = 0xFF,
			.PRECLIPMIN = 0x100,
			.PRECTHMIN = 0x100,
			.PREAE = 0,
		},
	},
	.precalP1D0D1 = {		// Through
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P0_D0_1,
		.PARACNT.bit.SEQEN = 0,		// Sequence dont start.
		.PARACNT.bit.LPARA = 0,		// read next parameter.
		.PRECAL[0].bit = {	// D0
			.PREOFSET = 0,
			.PRECLIPMAX = 0x3FFF,
			.PRECTHMAX = 0x3FFF,
			.PRECLIPMIN = 0x4000,
			.PRECTHMIN = 0x4000,
			.PREAE = 0,
		},
		.PRECAL[1].bit = {	// D1
			.PREOFSET = 0,
			.PRECLIPMAX = 0xFF,
			.PRECTHMAX = 0xFF,
			.PRECLIPMIN = 0x100,
			.PRECTHMIN = 0x100,
			.PREAE = 0,
		},
	},
	.precalP1D2D3 = {		// Through
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P0_D2_3,
		.PARACNT.bit.SEQEN = 0,		// Sequence dont start.
		.PARACNT.bit.LPARA = 0,		// read next parameter.
		.PRECAL[0].bit = {	// D2
			.PREOFSET = 0,
			.PRECLIPMAX = 0xFF,
			.PRECTHMAX = 0xFF,
			.PRECLIPMIN = 0x100,
			.PRECTHMIN = 0x100,
			.PREAE = 0,
		},
		.PRECAL[1].bit = {	// D3
			.PREOFSET = 0,
			.PRECLIPMAX = 0x1,
			.PRECTHMAX = 0x1,
			.PRECLIPMIN = 0x100,
			.PRECTHMIN = 0x100,
			.PREAE = 0,
		},
	},
	.calc = {	// Blend
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D0_CFG0,	// 0x200
		.PARACNT.bit.SEQEN = 0,		// Sequence dont start.
		.PARACNT.bit.LPARA = 0,		// read next parameter.
		.GPC0PARA0.bit = {
			.GPC0SEL0 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG2,
			.GPC0SEL1 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG3,
			.GPC0SEL2 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG4,
			.GPC0SEL3 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG1,
			.G0MD0 = ImIipParamEnum_E_IM_IIP_PARAM_GMD_MUL_MUL,
			.G0MD1 = ImIipParamEnum_E_IM_IIP_PARAM_GMD_MUL_MUL,
			.G0MD2 = ImIipParamEnum_E_IM_IIP_PARAM_GMD_BIN_ADD,
		},
		.GPC0PARA1.bit = {
			.G0RND_0 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G0SFT_0 = 0,
			.G0RND_1 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G0SFT_1 = 0,
			.G0RND_2 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G0SFT_2 = 0,
			.G0RND_3 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G0SFT_3 = 0,
			.G0RND_4 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G0SFT_4 = 0,
			.G0RND_5 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G0SFT_5 = 0,
			.G0RND_6 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G0SFT_6 = 0,
		},
		.GPC1PARA0.bit = {
			.GPC1SEL0 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG0,
			.GPC1SEL1 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P1D3,
			.G1MD0 = ImIipParamEnum_E_IM_IIP_PARAM_GMD_MUL_THROUGH,
			.GPC1SEL2 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG1,
			.G1MD1 = ImIipParamEnum_E_IM_IIP_PARAM_GMD_BIN_SUB,
		},
		.GPC1PARA1.bit = {
			.G1RND_0 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G1SFT_0 = 0,
			.G1RND_1 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G1SFT_1 = 0,
			.G1RND_2 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G1SFT_2 = 0,
			.G1RND_3 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G1SFT_3 = 0,
			.G1RND_4 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.G1SFT_4 = 0,
		},
		.SERPASS.bit = {
			.SEDLY0 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_0_STEP,
			.SESEL0 = ImIipParamEnum_E_IM_IIP_PARAM_SESEL0_INPUT_SELECTOR,
			.SEDLY1 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_0_STEP,
			.SESEL1 = ImIipParamEnum_E_IM_IIP_PARAM_SESEL1_INPUT_SELECTOR,
			.SEDLY2 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_0_STEP,
			.SEDLY3 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_0_STEP,
			.SEDLY4 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_4_STEP,
			.SEDLY5 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_4_STEP,
			.SEDLY6 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_4_STEP,
			.SEDLY7 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_0_STEP,
		},
		.COMPSEL.bit = {
			.COMPSEL = ImIipParamEnum_E_IM_IIP_PARAM_COMPSEL_CFG0,
			.CMPRND = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.CMPSFT = 0,
			.CORPEN = 0,
			.CORMEN = 0,
			.CLPPEN = 0,
			.CLPMEN = 0,
		},
		.CONFCNT.bit = {
			.CONFWEN0 = 1,	// Enable
			.CONFWEN1 = 0,
			.CONFWEN2 = 0,
			.CONFWEN3 = 0,
			.CONFREGSEL0 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL1 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CALC1,
			.CONFREGSEL2 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_P0D0,
			.CONFREGSEL3 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_P1D3,
			.CONFREGSEL4 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_P1D0,
			.CONFREGSEL5 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL6 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CALC0,		// Port1 output enable
			.CONFREGSEL7 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL8 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL9 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
		},
		.CONFREG = {
			0x1,
			0,
			0,
			0,
		},
	},
	.interCompCalc = {	// Port0 D.C.   Port1 Through
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_INTER_COMP_CALC,
		.PARACNT.bit.SEQEN = 1,		// Sequence start.
		.PARACNT.bit.LPARA = 1,		// this parameter is last.
		.P1OUTMD.bit = {
			.P1RNDO_0 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.P1SFTO_0 = 0,
			.P1SELO_0 = ImIipParamEnum_E_IM_IIP_PARAM_P1SELO_CONF6_D0,
			.P1RNDO_1 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.P1SFTO_1 = 0,
			.P1SELO_1 = ImIipParamEnum_E_IM_IIP_PARAM_P1SELO_CONF6_D1,
			.P1RNDO_2 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.P1SFTO_2 = 0,
			.P1SELO_2 = ImIipParamEnum_E_IM_IIP_PARAM_P1SELO_CONF6_D2,
			.P1RNDO_3 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.P1SFTO_3 = 0,
			.P1SELO_3 = ImIipParamEnum_E_IM_IIP_PARAM_P1SELO_ALPHA,
		},
		.P0OUTMD_D3.bit = {
			.P0RNDO_D3 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
			.P0SFTO_D3 = 0,
			.P0SELO_D3 = ImIipParamEnum_E_IM_IIP_PARAM_P0SELO_ALPHA,
		},
		.ELECAL = {
			[0].bit = {
				.ELESEL0 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D0_CFG9,
				.ELERD0 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT0 = 0,
				.ELESEL1 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D1_CFG9,
				.ELERD1 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT1 = 0,
				.ELESEL2 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D2_CFG9,
				.ELERD2 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT2 = 0,
				.ELESEL3 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D3_ALPHA,
				.ELERD3 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT3 = 0,
				.ELEMODE0 = ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_THROUGH,
				.ELEMODE1 = ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_THROUGH,
				.ELEMODE2 = ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_THROUGH,
				.ELERDO = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFTO = 0,
			},
			// [1].bit
			// [2].bit
		},
	},
};

static kulong ctImIipGpcSetPnsz0(CtImIipGpc *self, kulong sta, kulong pnsz1)
{
	kulong pnsz0;

	if(sta != 0) {
		pnsz0 = pnsz1 - (sta % pnsz1);
		if(pnsz0 == 0) {
			pnsz0 = pnsz1;
		}
	}
	else {
		pnsz0 = pnsz1;
	}

	return pnsz0;
}

static kint32 ctImIipGpcSetBlend(CtImIipGpc *self, KType funcNm)
{
	CtImIipGpcPrivate *priv = CT_IM_IIP_GPC_GET_PRIVATE(self);
	kint32	ercd;

	TImIipPixfmttbl pixfmt_tbl_0[2];	// 1DL Unit input
	TImIipPixfmttbl pixfmt_tbl_1;		// SL Unit output
	ImIipUnitCfg oned_cfg[2];
	ImIipUnitCfg gpc_cfg;
	ImIipParam1Dl *oned_unit_inf[2] = { &gCtImIipUnitParam1Dl0, &g_ct_im_iip_unit_param_1dl1 };
	TImIipParamGpc *gpc_unit_inf = &S_G_CT_IM_IIP_UNIT_PARAM_GPC;
	ImIipParamSts *sl_unit_inf = &gCtImIipUnitParamSl0;
	ImIipUnitCfg sl_cfg;
	kuint32 wait_factor_result = 0;
	const kuint32	wait_factor = ImIip_D_IM_IIP_INT_FACTOR_AXIERR | ImIip_D_IM_IIP_INT_FACTOR_SL2END;
	const kuint32	unitid_bitmask = ImIip_D_IM_IIP_PARAM_PLDUNIT_LD1 | ImIip_D_IM_IIP_PARAM_PLDUNIT_LD2   \
				| D_IM_IIP_PARAM_PLDUNIT_GPC | ImIip_D_IM_IIP_PARAM_PLDUNIT_SL2;
	const kuint32 pixid_bitmask = E_IM_IIP_PIXID_3 | ImIip_E_IM_IIP_PIXID_4 | ImIip_E_IM_IIP_PIXID_5;
	const ImIipEImIipUnitId src_unitid[2] = { ImIip_E_IM_IIP_UNIT_ID_LD1, ImIip_E_IM_IIP_UNIT_ID_LD2 };
	const ImIipEImIipUnitId filter_unitid = E_IM_IIP_UNIT_ID_GPC;
	const ImIipEImIipUnitId dst_unitid = ImIip_E_IM_IIP_UNIT_ID_SL2;
	const ImIipParamEImIipParamPortid src_portid[2] = { ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1, ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD2 };
	const ImIipParamEImIipParamPortid filter_portid[2] = { ImIipParamEnum_E_IM_IIP_PARAM_PORTID_GPC_P0, ImIipParamEnum_E_IM_IIP_PARAM_PORTID_GPC_P1 };
	const ImIipParamEImIipParamPortid dst_portid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32 src_pixid[2] = { 3, 4 };
	const kuint32 dst_pixid = 5;
	const kuint32 open_res_bitmask = ImIip_E_IM_IIP_OPEN_RES_CACHE0;

	CtImIipGpc_Ddim_Print(("%s \n", funcNm));

	ercd = im_iip_open_swtrg(unitid_bitmask, pixid_bitmask, open_res_bitmask, CtImIip_D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	if(ercd != ImIip_D_IM_IIP_OK) {
		return ercd;
	}

	// A
	pixfmt_tbl_0[0] = gCtImIipPixfmttblBase;
	pixfmt_tbl_0[0].frame_type = priv->srcA.ffmt;
	pixfmt_tbl_0[0].pix_format	 = priv->srcA.pfmt;
	pixfmt_tbl_0[0].width = priv->srcA.width;
	pixfmt_tbl_0[0].lines = priv->srcA.lines;
	pixfmt_tbl_0[0].line_bytes.Y_G = priv->srcA.gWidth;
	pixfmt_tbl_0[0].line_bytes.Cb_B = priv->srcA.gWidth;	// Y_PACKED_CBCR
	pixfmt_tbl_0[0].line_bytes.Cr_R = priv->srcA.gWidth;	// Y_PACKED_CBCR
	pixfmt_tbl_0[0].line_bytes.Alpha = priv->srcA.gWidth;
	pixfmt_tbl_0[0].addr.Y_G = priv->srcA.addrY;
	pixfmt_tbl_0[0].addr.Cb_B = priv->srcA.addrC;
	pixfmt_tbl_0[0].addr.Cr_R = 0;	// not used
	pixfmt_tbl_0[0].addr.Alpha = 0;	// not used

	// B
	pixfmt_tbl_0[1] = gCtImIipPixfmttblBase;
	pixfmt_tbl_0[1].alpha = D_IM_IIP_ALPHA_TRUE;		// alpha lane enable
	pixfmt_tbl_0[1].frame_type = priv->srcB.ffmt;
	pixfmt_tbl_0[1].pix_format	 = priv->srcB.pfmt;
	pixfmt_tbl_0[1].width = priv->srcB.width;
	pixfmt_tbl_0[1].lines = priv->srcB.lines;
	pixfmt_tbl_0[1].line_bytes.Y_G = priv->srcB.gWidth;
	pixfmt_tbl_0[1].line_bytes.Cb_B	= priv->srcB.gWidth;	// Y_PACKED_CBCR
	pixfmt_tbl_0[1].line_bytes.Cr_R = priv->srcB.gWidth;	// Y_PACKED_CBCR
	pixfmt_tbl_0[1].line_bytes.Alpha = priv->srcB.gWidth;
	pixfmt_tbl_0[1].addr.Y_G = priv->srcB.addrY;
	pixfmt_tbl_0[1].addr.Cb_B	= priv->srcB.addrC;
	pixfmt_tbl_0[1].addr.Cr_R = 0;	// not used
	pixfmt_tbl_0[1].addr.Alpha = priv->alphaAddr;

	pixfmt_tbl_1 = gCtImIipPixfmttblBase;
	pixfmt_tbl_1.frame_type = priv->dst.ffmt;
	pixfmt_tbl_1.pix_format = priv->dst.pfmt;
	pixfmt_tbl_1.width = priv->dst.width;
	pixfmt_tbl_1.lines = priv->dst.lines;
	pixfmt_tbl_1.line_bytes.Y_G = priv->dst.gWidth;
	pixfmt_tbl_1.line_bytes.Cb_B = priv->dst.gWidth;	// Y_PACKED_CBCR
	pixfmt_tbl_1.line_bytes.Cr_R = priv->dst.gWidth;	// Y_PACKED_CBCR
	pixfmt_tbl_1.line_bytes.Alpha = priv->dst.gWidth;
	pixfmt_tbl_1.addr.Y_G = priv->dst.addrY;
	pixfmt_tbl_1.addr.Cb_B = priv->dst.addrC;
	pixfmt_tbl_1.addr.Cr_R = 0;	// not used
	pixfmt_tbl_1.addr.Alpha = 0;

	CtImIipGpc_Ddim_Print(("%s oned_unit_inf[0] = 0x%x 0x%x\n", funcNm, (kuint32)oned_unit_inf[0], sizeof(ImIipParam1Dl)));

	memset(oned_unit_inf[0], '\0', sizeof(*oned_unit_inf[0]));
	*oned_unit_inf[0] = gCtImIipParam1DlBase;
	oned_unit_inf[0]->LD_TOPCNF0.bit.WAITCONF = filter_portid[0];
	oned_unit_inf[0]->PIXIDDEF.bit.IPIXID = src_pixid[0];
	oned_unit_inf[0]->LD_CTL.bit.SLOW = ImIipParamEnum_E_IM_IIP_PARAM_PF_PDIST_64PIX;
	oned_unit_inf[0]->LD_PREFETCH.bit.PF_PDIST = ImIipParamEnum_E_IM_IIP_PARAM_PF_PDIST_64PIX;
	oned_unit_inf[0]->LD_HSIZE.bit.HSTART = priv->staX;
	oned_unit_inf[0]->LD_HSIZE.bit.HEND = (priv->staX + priv->srcB.width) - 1;
	oned_unit_inf[0]->LD_VSIZE.bit.VSTART = priv->staY;
	oned_unit_inf[0]->LD_VSIZE.bit.VEND = (priv->staY + priv->srcB.lines) - 1;
	oned_unit_inf[0]->LD_PHSZ.bit.PHSZ1 = 64;
	oned_unit_inf[0]->LD_PVSZ.bit.PVSZ1 = 8;
	oned_unit_inf[0]->LD_PHSZ.bit.PHSZ0 = ctImIipGpcSetPnsz0(self, oned_unit_inf[0]->LD_HSIZE.bit.HSTART, oned_unit_inf[0]->LD_PHSZ.bit.PHSZ1);
	oned_unit_inf[0]->LD_PVSZ.bit.PVSZ0 = ctImIipGpcSetPnsz0(self, oned_unit_inf[0]->LD_VSIZE.bit.VSTART, oned_unit_inf[0]->LD_PVSZ.bit.PVSZ1);

	oned_cfg[0].unit_ctrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	oned_cfg[0].chain_enable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	oned_cfg[0].unit_param_addr = (kulong)oned_unit_inf[0];
	oned_cfg[0].load_unit_param_flag = 0;

	CtImIipGpc_Ddim_Print(("%s oned_unit_inf[1] = 0x%x 0x%x\n", funcNm, (kuint32)oned_unit_inf[1], sizeof(ImIipParam1Dl)));

	memset(oned_unit_inf[1], '\0', sizeof(*oned_unit_inf[1]));
	*oned_unit_inf[1] = gCtImIipParam1DlBase;
	oned_unit_inf[1]->LD_TOPCNF0.bit.WAITCONF = filter_portid[1];
	oned_unit_inf[1]->PIXIDDEF.bit.IPIXID = src_pixid[1];
	oned_unit_inf[1]->LD_CTL.bit.SLOW = ImIipParamEnum_E_IM_IIP_PARAM_PF_PDIST_64PIX;
	oned_unit_inf[1]->LD_PREFETCH.bit.PF_PDIST = ImIipParamEnum_E_IM_IIP_PARAM_PF_PDIST_64PIX;
	oned_unit_inf[1]->LD_HSIZE.bit.HSTART = 0;
	oned_unit_inf[1]->LD_HSIZE.bit.HEND = priv->srcB.width - 1;
	oned_unit_inf[1]->LD_VSIZE.bit.VSTART = 0;
	oned_unit_inf[1]->LD_VSIZE.bit.VEND = priv->srcB.lines - 1;
	oned_unit_inf[1]->LD_PHSZ.bit.PHSZ1 = 64;
	oned_unit_inf[1]->LD_PVSZ.bit.PVSZ1 = 8;
	oned_unit_inf[1]->LD_PHSZ.bit.PHSZ0 = ctImIipGpcSetPnsz0(self, oned_unit_inf[1]->LD_HSIZE.bit.HSTART, oned_unit_inf[1]->LD_PHSZ.bit.PHSZ1);
	oned_unit_inf[1]->LD_PVSZ.bit.PVSZ0 = ctImIipGpcSetPnsz0(self, oned_unit_inf[1]->LD_VSIZE.bit.VSTART, oned_unit_inf[1]->LD_PVSZ.bit.PVSZ1);

	oned_cfg[1].unit_ctrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	oned_cfg[1].chain_enable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	oned_cfg[1].unit_param_addr = (kulong)oned_unit_inf[1];
	oned_cfg[1].load_unit_param_flag = 0;

	CtImIipGpc_Ddim_Print(("%s gpc_unit_inf = 0x%x 0x%x\n", funcNm, (kuint32)gpc_unit_inf, sizeof(TImIipParamGpc)));

	memset(gpc_unit_inf, '\0', sizeof(*gpc_unit_inf));
	gCtImIipGpcConfig_13_1_3.seq.SEQLOOP = priv->srcA.width;
	gCtImIipGpcConfig_13_1_3.seq.SEQCTL.bit.CNTEND_0 = priv->srcA.lines;

	*gpc_unit_inf = ct_im_iip1_gpc_get_param_gpc_base(priv->gpc1);
	gpc_unit_inf->GPCTOPCNF[0].bit.WAITCONF = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE;	// Port1 output
	gpc_unit_inf->GPCTOPCNF[0].bit.DATACONF = src_portid[0];
	gpc_unit_inf->GPCTOPCNF[1].bit.WAITCONF = dst_portid;					// Port1 output
	gpc_unit_inf->GPCTOPCNF[1].bit.DATACONF = src_portid[1];
	gpc_unit_inf->GPCCONTROL.bit.COMMONPARA = ImIipParamEnum_E_IM_IIP_PARAM_COMMONPARA_D0_D0_D0;	// used common parameter
	gpc_unit_inf->GPCCLOADADR.bit.CLOADADR = (kulong)&gCtImIipGpcConfig_13_1_3;

	gpc_cfg.unit_ctrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	gpc_cfg.chain_enable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	gpc_cfg.unit_param_addr = (kulong)gpc_unit_inf;
	gpc_cfg.load_unit_param_flag = 0;

	CtImIipGpc_Ddim_Print(("%s sl_unit_inf = 0x%x 0x%x\n", funcNm, (kuint32)sl_unit_inf, sizeof(ImIipParamSts)));

	memset(sl_unit_inf, '\0', sizeof(*sl_unit_inf));
	*sl_unit_inf = gCtImIipParamStsBase;
	sl_unit_inf->BASE.SL_TOPCNF0.bit.DATACONF = filter_portid[1];				// Port1 output
	sl_unit_inf->BASE.PIXIDDEF.bit.OPIXID = dst_pixid;
	sl_unit_inf->BASE.CLPTH_U_0.bit.CLPTH_U = 0xFF;
	sl_unit_inf->BASE.CLPVAL_U_0.bit.CLPVAL_U = 0xFF;

	sl_unit_inf->BASE.SL_HSIZE.bit.HSTART = priv->staX;
	sl_unit_inf->BASE.SL_HSIZE.bit.HEND = (priv->staX + priv->srcB.width) - 1;
	sl_unit_inf->BASE.SL_VSIZE.bit.VSTART = priv->staY;
	sl_unit_inf->BASE.SL_VSIZE.bit.VEND = (priv->staY + priv->srcB.lines) - 1;
	sl_unit_inf->BASE.SL_PHSZ.bit.PHSZ1 =  64;
	sl_unit_inf->BASE.SL_PVSZ.bit.PVSZ1 =  8;
	sl_unit_inf->BASE.SL_PHSZ.bit.PHSZ0 = ctImIipGpcSetPnsz0(self, sl_unit_inf->BASE.SL_HSIZE.bit.HSTART, sl_unit_inf->BASE.SL_PHSZ.bit.PHSZ1);
	sl_unit_inf->BASE.SL_PVSZ.bit.PVSZ0  = ctImIipGpcSetPnsz0(self, sl_unit_inf->BASE.SL_VSIZE.bit.VSTART, sl_unit_inf->BASE.SL_PVSZ.bit.PVSZ1);

	sl_cfg.unit_ctrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	sl_cfg.chain_enable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	sl_cfg.unit_param_addr = (kulong)sl_unit_inf;
	sl_cfg.load_unit_param_flag = unitid_bitmask;

	ct_im_iip_clean_l1l2_dcache_addr((kulong)oned_unit_inf[0], sizeof(ImIipParam1Dl));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)oned_unit_inf[1], sizeof(ImIipParam1Dl));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)gpc_unit_inf, sizeof(TImIipParamGpc));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)&gCtImIipGpcConfig_13_1_3, sizeof(TImIzaParamGpcConfig13_1_3));
	ct_im_iip_clean_l1l2_dcache_addr((kulong)sl_unit_inf, sizeof(ImIipParamSts));

	ercd = im_iip_ctrl_pixfmttbl(src_pixid[0], &pixfmt_tbl_0[0]);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	ercd = im_iip_ctrl_pixfmttbl(src_pixid[1], &pixfmt_tbl_0[1]);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	ercd = im_iip_ctrl_pixfmttbl(dst_pixid, &pixfmt_tbl_1);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(src_unitid[0], &oned_cfg[0]);//TODO:吴雨莎还未修改名字
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(src_unitid[1], &oned_cfg[1]);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(filter_unitid, &gpc_cfg);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(dst_unitid, &sl_cfg);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	ercd = Im_IIP_Set_Interrupt(wait_factor, D_IM_IIP_ENABLE_ON);//TODO:吴雨莎还未修改名字
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	DdArm_Dd_ARM_Dmb_Pou();

	CtImIipGpc_Ddim_Print(("%s Start1\n", funcNm));
	ercd = im_iip_start_swteg(dst_unitid, D_IM_IIP_SWTRG_ON);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	CtImIipGpc_Ddim_Print(("%s Start2\n", funcNm));
	ercd = im_iip_start_swteg(filter_unitid, D_IM_IIP_SWTRG_ON);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	CtImIipGpc_Ddim_Print(("%s Start3\n", funcNm));
	ercd = im_iip_start_swteg(src_unitid[0], D_IM_IIP_SWTRG_ON);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	CtImIipGpc_Ddim_Print(("%s Start4\n", funcNm));
	ercd = im_iip_start_swteg(src_unitid[1], D_IM_IIP_SWTRG_ON);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	CtImIipGpc_Ddim_Print(("%s WaitEnd\n", funcNm));
	ercd = im_iip_wait_end(&wait_factor_result, wait_factor, D_IM_IIP_OR_WAIT, 30);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x factor=0x%x\n", funcNm, ercd, wait_factor_result));
	if(ercd != D_DDIM_OK) {
		CtImIipGpc_Ddim_Print(("%s Stop\n", funcNm));
		ercd = im_iip_stop(D_IM_IIP_ABORT);
		CtImIipGpc_Ddim_Print(("%s ercd = 0x%x factor=0x%x\n", funcNm, ercd, wait_factor_result));
	}

	CtImIipGpc_Ddim_Print(("%s im_iip_close_swtrg\n", funcNm));
	ercd = im_iip_close_swtrg(unitid_bitmask, pixid_bitmask, open_res_bitmask);
	CtImIipGpc_Ddim_Print(("%s ercd = 0x%x\n", funcNm, ercd));

	return D_DDIM_OK;
}
#endif /*CO_CT_IM_IIP_DISABLE*/

/*
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
// GPC Unit 13-1-3
kint32 ct_im_iip_13_1_3(CtImIipGpc *self)
{
	CtImIipGpcPrivate *priv = CT_IM_IIP_GPC_GET_PRIVATE(self);

	// VGA all area
	priv->staX = 0;
	priv->staY = 0;

	priv->srcA.pfmt = E_IM_IIP_PFMT_YCC422;
	priv->srcA.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcA.gWidth = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->srcA.width = CtImIip_D_IM_IIP_VGA_WIDTH;
	priv->srcA.lines = CtImIip_D_IM_IIP_VGA_LINES;
	priv->srcA.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	priv->srcA.addrC = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;

	priv->srcB.pfmt = E_IM_IIP_PFMT_YCC420;
	priv->srcB.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcB.gWidth = CtImIip_D_IM_IIP_VGA_YCC420_U8_Y_GLOBAL_WIDTH;
	priv->srcB.width = CtImIip_D_IM_IIP_VGA_WIDTH;
	priv->srcB.lines = CtImIip_D_IM_IIP_VGA_LINES;
	priv->srcB.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC420_U8_Y;
	priv->srcB.addrC	 = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC420_U8_C;
	priv->alphaAddr = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC420_U8_A;

	priv->dst.pfmt = E_IM_IIP_PFMT_YCC422;
	priv->dst.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->dst.gWidth = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->dst.width = CtImIip_D_IM_IIP_VGA_WIDTH;
	priv->dst.lines = CtImIip_D_IM_IIP_VGA_LINES;
	priv->dst.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	priv->dst.addrC = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;

	return ctImIipGpcSetBlend(self, "ct_im_iip_13_1_3: ");
}

// GPC Unit 13-1-4
kint32 ct_im_iip_13_1_4(CtImIipGpc *self)
{
	CtImIipGpcPrivate *priv = CT_IM_IIP_GPC_GET_PRIVATE(self);

	// VGA 10%
	priv->staX = ((CtImIip_D_IM_IIP_VGA_WIDTH - CtImIip_D_IM_IIP_VGA_1_10_WIDTH) >> 1) & 0xFFC0;
	priv->staY = ((CtImIip_D_IM_IIP_VGA_LINES - CtImIip_D_IM_IIP_VGA_1_10_LINES) >> 1) & 0xFFF0;

	priv->srcA.pfmt = E_IM_IIP_PFMT_YCC422;
	priv->srcA.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcA.gWidth = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->srcA.width = CtImIip_D_IM_IIP_VGA_WIDTH;
	priv->srcA.lines = CtImIip_D_IM_IIP_VGA_LINES;
	priv->srcA.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	priv->srcA.addrC = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;

	priv->srcB.pfmt = E_IM_IIP_PFMT_YCC420;
	priv->srcB.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcB.gWidth = CtImIip_D_IM_IIP_VGA_1_10_YCC420_U8_Y_GLOBAL_WIDTH;
	priv->srcB.width = CtImIip_D_IM_IIP_VGA_1_10_WIDTH;
	priv->srcB.lines = CtImIip_D_IM_IIP_VGA_1_10_LINES;
	priv->srcB.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_VGA_1_10_YCC420_U8_Y;
	priv->srcB.addrC = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_VGA_1_10_YCC420_U8_C;
	priv->alphaAddr = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_VGA_1_10_YCC420_U8_A;
	priv->dst = priv->srcA;			// The same settings as the srcA

	return ctImIipGpcSetBlend(self, "ct_im_iip_13_1_4: ");
}

// GPC Unit 13-1-5
kint32 ct_im_iip_13_1_5(CtImIipGpc *self)
{
	CtImIipGpcPrivate *priv = CT_IM_IIP_GPC_GET_PRIVATE(self);

	// Rebery VGA all area
	priv->staX = 0;
	priv->staY = 0;

	priv->srcA.pfmt = E_IM_IIP_PFMT_VIDEO;
	priv->srcA.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcA.gWidth = CtImIip_D_IM_IIP_VGA_RIBERY_U8_Y_GLOBAL_WIDTH;
	priv->srcA.width = CtImIip_D_IM_IIP_VGA_WIDTH;
	priv->srcA.lines = CtImIip_D_IM_IIP_VGA_LINES;
	priv->srcA.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_VGA_RIBERY_U8_Y;
	priv->srcA.addrC = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_VGA_RIBERY_U8_C;

	priv->srcB.pfmt = E_IM_IIP_PFMT_YCC420;
	priv->srcB.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcB.gWidth = CtImIip_D_IM_IIP_VGA_YCC420_U8_Y_GLOBAL_WIDTH;
	priv->srcB.width = CtImIip_D_IM_IIP_VGA_WIDTH;
	priv->srcB.lines = CtImIip_D_IM_IIP_VGA_LINES;
	priv->srcB.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC420_U8_Y;
	priv->srcB.addrC	 = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC420_U8_C;
	priv->alphaAddr = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC420_U8_A;

	priv->dst.pfmt = E_IM_IIP_PFMT_VIDEO;
	priv->dst.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->dst.gWidth = CtImIip_D_IM_IIP_VGA_RIBERY_U8_Y_GLOBAL_WIDTH;
	priv->dst.width = CtImIip_D_IM_IIP_VGA_WIDTH;
	priv->dst.lines = CtImIip_D_IM_IIP_VGA_LINES;
	priv->dst.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_VGA_RIBERY_U8_Y;
	priv->dst.addrC = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_VGA_RIBERY_U8_C;

	return ctImIipGpcSetBlend(self, "ct_im_iip_13_1_5: ");
}

// GPC Unit 13-1-6
kint32 ct_im_iip_13_1_6(CtImIipGpc *self)
{
	CtImIipGpcPrivate *priv = CT_IM_IIP_GPC_GET_PRIVATE(self);

	// VGA 10%
	priv->staX = ((CtImIip_D_IM_IIP_VGA_WIDTH - CtImIip_D_IM_IIP_VGA_1_10_WIDTH) >> 1) & 0xFFC0;
	priv->staY = ((CtImIip_D_IM_IIP_VGA_LINES - CtImIip_D_IM_IIP_VGA_1_10_LINES) >> 1) & 0xFFF0;
	priv->srcA.pfmt = E_IM_IIP_PFMT_VIDEO;
	priv->srcA.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcA.gWidth = CtImIip_D_IM_IIP_VGA_RIBERY_U8_Y_GLOBAL_WIDTH;
	priv->srcA.width = CtImIip_D_IM_IIP_VGA_WIDTH;
	priv->srcA.lines = CtImIip_D_IM_IIP_VGA_LINES;
	priv->srcA.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_VGA_RIBERY_U8_Y;
	priv->srcA.addrC = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_VGA_RIBERY_U8_C;

	priv->srcB.pfmt = E_IM_IIP_PFMT_YCC420;
	priv->srcB.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcB.gWidth = CtImIip_D_IM_IIP_VGA_1_10_YCC420_U8_Y_GLOBAL_WIDTH;
	priv->srcB.width = CtImIip_D_IM_IIP_VGA_1_10_WIDTH;
	priv->srcB.lines = CtImIip_D_IM_IIP_VGA_1_10_LINES;
	priv->srcB.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_VGA_1_10_YCC420_U8_Y;
	priv->srcB.addrC	 = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_VGA_1_10_YCC420_U8_C;
	priv->alphaAddr = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_VGA_1_10_YCC420_U8_A;
	priv->dst = priv->srcA;	// The same settings as the srcA

	return ctImIipGpcSetBlend(self, "ct_im_iip_13_1_6: ");
}

// GPC Unit 13-1-7
kint32 ct_im_iip_13_1_7(CtImIipGpc *self)
{
	CtImIipGpcPrivate *priv = CT_IM_IIP_GPC_GET_PRIVATE(self);

	// FullHD 10%
	priv->staX = ((CtImIip_D_IM_IIP_FULLHD_WIDTH - CtImIip_D_IM_IIP_FULLHD_1_10_WIDTH) >> 1) & 0xFFC0;
	priv->staY = ((CtImIip_D_IM_IIP_FULLHD_LINES - CtImIip_D_IM_IIP_FULLHD_1_10_LINES) >> 1) & 0xFFF0;
	priv->srcA.pfmt = E_IM_IIP_PFMT_YCC422;
	priv->srcA.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcA.gWidth = CtImIip_D_IM_IIP_FULLHD_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->srcA.width = CtImIip_D_IM_IIP_FULLHD_WIDTH;
	priv->srcA.lines = CtImIip_D_IM_IIP_FULLHD_LINES;
	priv->srcA.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_Y;
	priv->srcA.addrC = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_YCC422_U8_C;

	priv->srcB.pfmt = E_IM_IIP_PFMT_YCC420;
	priv->srcB.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcB.gWidth = CtImIip_D_IM_IIP_FULLHD_1_10_YCC420_U8_Y_GLOBAL_WIDTH;
	priv->srcB.width = CtImIip_D_IM_IIP_FULLHD_1_10_WIDTH;
	priv->srcB.lines = CtImIip_D_IM_IIP_FULLHD_1_10_LINES;
	priv->srcB.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_FULLHD_1_10_YCC420_U8_Y;
	priv->srcB.addrC	 = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_FULLHD_1_10_YCC420_U8_C;
	priv->alphaAddr = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_FULLHD_1_10_YCC420_U8_A;
	priv->dst = priv->srcA;			// The same settings as the srcA

	return ctImIipGpcSetBlend(self, "ct_im_iip_13_1_7: ");
}

// GPC Unit 13-1-8
kint32 ct_im_iip_13_1_8(CtImIipGpc *self)
{
	CtImIipGpcPrivate *priv = CT_IM_IIP_GPC_GET_PRIVATE(self);

	// FullHD 10%
	priv->staX = ((CtImIip_D_IM_IIP_FULLHD_WIDTH - CtImIip_D_IM_IIP_FULLHD_1_10_WIDTH) >> 1) & 0xFFC0;
	priv->staY = ((CtImIip_D_IM_IIP_FULLHD_LINES - CtImIip_D_IM_IIP_FULLHD_1_10_LINES) >> 1) & 0xFFF0;
	priv->srcA.pfmt = E_IM_IIP_PFMT_VIDEO;
	priv->srcA.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcA.gWidth = CtImIip_D_IM_IIP_FULLHD_RIBERY_U8_Y_GLOBAL_WIDTH;
	priv->srcA.width = CtImIip_D_IM_IIP_FULLHD_WIDTH;
	priv->srcA.lines = CtImIip_D_IM_IIP_FULLHD_LINES;
	priv->srcA.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_RIBERY_U8_Y;
	priv->srcA.addrC = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_FULLHD_RIBERY_U8_C;

	priv->srcB.pfmt = E_IM_IIP_PFMT_YCC420;
	priv->srcB.ffmt = E_IM_IIP_FTYPE_Y_PACKED_CBCR;
	priv->srcB.gWidth = CtImIip_D_IM_IIP_FULLHD_1_10_YCC420_U8_Y_GLOBAL_WIDTH;
	priv->srcB.width = CtImIip_D_IM_IIP_FULLHD_1_10_WIDTH;
	priv->srcB.lines = CtImIip_D_IM_IIP_FULLHD_1_10_LINES;
	priv->srcB.addrY = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_FULLHD_1_10_YCC420_U8_Y;
	priv->srcB.addrC = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_FULLHD_1_10_YCC420_U8_C;
	priv->alphaAddr = CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_FULLHD_1_10_YCC420_U8_A;
	priv->dst = priv->srcA;			// The same settings as the srcA

	return ctImIipGpcSetBlend(self, "ct_im_iip_13_1_8: ");
}

// GPC Unit 13-1-X
kint32 ct_im_iip_gpc_run_13_1(CtImIipGpc *self, const kuint32 ct_no_3rd)
{
	CtImIipGpcPrivate *priv = CT_IM_IIP_GPC_GET_PRIVATE(self);

	switch(ct_no_3rd) {
		// Test-13-1-1
		case 1:
			return ct_im_iip_gpc_13_1_1(priv->gpc1);

		// Test-13-1-2
		case 2:
			return ct_im_iip_gpc_13_1_2(priv->gpc2);

		// Test-13-1-3
		case 3:
			return ct_im_iip_13_1_3(self);

		// Test-13-1-4
		case 4:
			return ct_im_iip_13_1_4(self);

		// Test-13-1-5
		case 5:
			return ct_im_iip_13_1_5(self);

		// Test-13-1-6
		case 6:
			return ct_im_iip_13_1_6(self);

		// Test-13-1-7
		case 7:
			return ct_im_iip_13_1_7(self);

		// Test-13-1-8
		case 8:
			return ct_im_iip_13_1_8(self);

		default:
			CtImIipGpc_Ddim_Print(("Error: Unknown command.\n"));
			break;
	}
	return D_DDIM_INPUT_PARAM_ERROR;
}
#endif /*CO_CT_IM_IIP_DISABLE*/

CtImIipGpc *ct_im_iip_gpc_new(void) 
{
    CtImIipGpc *self = k_object_new_with_private(CT_TYPE_IM_IIP_GPC, sizeof(CtImIipGpcPrivate));
    return self;
}
