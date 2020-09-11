/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhangxinyue
*@brief               :CtImIipGpc1类
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
#include "ctimiipgpc.h"      
#include "ctimiipgpc1.h"
#include "ctimiipgpc2.h"

// im_iip header
#include "im_iip.h"

// MILB register header
#include "jdsiip.h"

// for Memory barrier
#include "dd_arm.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImIipGpc1, ct_im_iip_gpc1);
#define CT_IM_IIP_GPC1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImIipGpc1Private,CT_TYPE_IM_IIP_GPC1))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#undef CtImIipGpc1_Ddim_Print
#define CtImIipGpc1_Ddim_Print(arg)		{ddim_user_custom_printf arg;}		/**< printf function inside DDIM */
#endif    /*1*/
#endif  /*CO_CT_IM_IIP_DISABLE*/

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
#ifndef CO_CT_IM_IIP_DISABLE
// GPC Unit Parameter
typedef struct{
	TImIipParamGpcSeqCtrl					seq;
	TImIipParamGpcPrecal						precal[2];
	TImIipParamGpcCalc							calc;				// D0~D2
	TImIipParamGpcAlpha						alpha;			// D3(alpha)
	TImIipParamGpcInterCompCalc	interCompCalc;
} TImIzaParamGpcCongif;
#endif  /*CO_CT_IM_IIP_DISABLE*/

struct _CtImIipGpc1Private
{
#ifndef CO_CT_IM_IIP_DISABLE
	TImIipParamGpc ctImIip1ParamGpcBase;
#endif
};

#ifndef CO_CT_IM_IIP_DISABLE
#ifdef __GNUC__
static TImIipParamGpc S_G_CT_IM_IIP_UNIT_PARAM_GPC __attribute__((aligned(8)));	// Needs 8bytes align
#else
static __align(8) TImIipParamGpc S_G_CT_IM_IIP_UNIT_PARAM_GPC;								// Needs 8bytes align
#endif
#endif  /*CO_CT_IM_IIP_DISABLE*/

/*
 * DECLS
 */
// Nothing Special

static void ct_im_iip_gpc1_constructor(CtImIipGpc1 *self) 
{
	CtImIipGpc1Private *priv = CT_IM_IIP_GPC1_GET_PRIVATE(self);

	priv->ctImIip1ParamGpcBase.header0.bit.BeginningAddress = 0x0000;
	priv->ctImIip1ParamGpcBase.header0.bit.WordLength = 7;
	priv->ctImIip1ParamGpcBase.header0.bit.CtrlCode = ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET;
	priv->ctImIip1ParamGpcBase.GPCCONTROL.bit.COMMONPARA = ImIipParamEnum_E_IM_IIP_PARAM_COMMONPARA_D0_D0_D0;
	priv->ctImIip1ParamGpcBase.GPCCONTROL.bit.MD2DLK = 0;		// SLINK mode
	priv->ctImIip1ParamGpcBase.GPCCONTROL.bit.ALPEN0 = 0;			// No alpha plane
	priv->ctImIip1ParamGpcBase.GPCCONTROL.bit.ALPEN1 = 0;			// No alpha plane
	priv->ctImIip1ParamGpcBase.GPCCONTROL.bit.ATRB0 = ImIipParamEnum_E_IM_IIP_PARAM_ATRB_PORT0;
	priv->ctImIip1ParamGpcBase.GPCCONTROL.bit.ATRB1 = ImIipParamEnum_E_IM_IIP_PARAM_ATRB_PORT0;	
}

static void ct_im_iip_gpc1_destructor(CtImIipGpc1 *self) 
{
	// CtImIipGpc1Private *priv = CT_IM_IIP_GPC1_GET_PRIVATE(self);
}

/*
 * IMPL
 */
#ifndef CO_CT_IM_IIP_DISABLE
#ifdef __GNUC__
static TImIzaParamGpcCongif		gCtImIipGpcConfig __attribute__((aligned(64))) = {		// Needs 64bytes align
#else
static __align(64) TImIzaParamGpcCongif		gCtImIipGpcConfig = {							// Needs 64bytes align
#endif
	.seq = {
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_SEQ_CTRL,
		.PARACNT.bit.SEQEN = 0,		// Sequence dont start.
		.PARACNT.bit.LPARA = 0,		// read next parameter.
		.SEQLOOP = 1,
		.SEQCTL.bit = {
			.STEPNUM = CtImIipGpc1_D_GPC_STEPNUM,

			.CNTEND_0 = 640 * 480,
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
	.precal[0] = {	// D0, D1
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P0_D0_1,
		.PARACNT.bit.SEQEN = 0,		// Sequence dont start.
		.PARACNT.bit.LPARA = 0,		// read next parameter.
		.PRECAL[0].bit = {	// D0
			.PREOFSET = 0,
			.PRECLIPMAX = 0x3fff,
			.PRECTHMAX = 0x3fff,
			.PRECLIPMIN = 0x4000,
			.PRECTHMIN = 0x4000,
			.PREAE = 0,
		},
		.PRECAL[1].bit = {	// D1
			.PREOFSET = 0,
			.PRECLIPMAX = 0xff,
			.PRECTHMAX = 0xff,
			.PRECLIPMIN = 0x100,
			.PRECTHMIN = 0x100,
			.PREAE = 0,
		},
	},
	.precal[1] = {	// D2, D3
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_PRECAL_P0_D2_3,
		.PARACNT.bit.SEQEN = 0,		// Sequence dont start.
		.PARACNT.bit.LPARA = 0,		// read next parameter.
		.PRECAL[0].bit = {	// D2
			.PREOFSET = 0,
			.PRECLIPMAX = 0xff,
			.PRECTHMAX = 0xff,
			.PRECLIPMIN = 0x100,
			.PRECTHMIN = 0x100,
			.PREAE = 0,
		},
		.PRECAL[1].bit = {	// D3
			.PREOFSET = 0,
			.PRECLIPMAX = 0xff,
			.PRECTHMAX = 0xff,
			.PRECLIPMIN = 0x100,
			.PRECTHMIN = 0x100,
			.PREAE = 0,
		},
	},
	.calc = {
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_CALC_D0_CFG0,
		.PARACNT.bit.SEQEN = 0,		// Sequence dont start.
		.PARACNT.bit.LPARA = 0,		// read next parameter.
		.GPC0PARA0.bit = {
			.GPC0SEL0 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P0D0,
			.GPC0SEL1 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG0,		// dummy
			.GPC0SEL2 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P1D0,
			.GPC0SEL3 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG1,		// dummy
			.G0MD0 = ImIipParamEnum_E_IM_IIP_PARAM_GMD_MUL_THROUGH,
			.G0MD1 = ImIipParamEnum_E_IM_IIP_PARAM_GMD_MUL_THROUGH,
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
			.GPC1SEL0 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P0D0,		// dummy
			.GPC1SEL1 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_P1D0,		// dummy
			.G1MD0 = ImIipParamEnum_E_IM_IIP_PARAM_GMD_MUL_THROUGH,	// dummy
			.GPC1SEL2 = ImIipParamEnum_E_IM_IIP_PARAM_GPCSEL_CFG1,		// dummy
			.G1MD1 = ImIipParamEnum_E_IM_IIP_PARAM_GMD_BIN_THROUGH,	// dummy
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
			.SESEL1 = ImIipParamEnum_E_IM_IIP_PARAM_SESEL0_INPUT_SELECTOR,
			.SEDLY2 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_0_STEP,
			.SEDLY3 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_0_STEP,
			.SEDLY4 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_0_STEP,
			.SEDLY5 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_0_STEP,
			.SEDLY6 = ImIipParamEnum_E_IM_IIP_PARAM_SEDLY_0_STEP,
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
			.CONFWEN0 = 0,
			.CONFWEN1 = 0,
			.CONFWEN2 = 0,
			.CONFWEN3 = 0,
			.CONFREGSEL0 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL1 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL2 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL3 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL4 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL5 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL6 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CALC0,		// Port1 output = calculator0 value
			.CONFREGSEL7 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL8 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,
			.CONFREGSEL9 = ImIipParamEnum_E_IM_IIP_PARAM_CONFREGSEL_CFG_n,		// Port0 output = fixed value
		},
		.CONFREG = {
			0,
			0,
			0,
			0,
		},
	},
	.alpha = {
		.PARACNT.bit.PARAAD = ImIipParamEnum_E_IM_IIP_PARAM_PARAAD_ALPHA,
		.PARACNT.bit.SEQEN = 0,		// Sequence dont start.
		.PARACNT.bit.LPARA = 0,		// read next parameter.
		.GPCALP = {
			[0].bit = {
				.GPCALPFIX = 0,
				.GPCALPSEL0 = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPSEL_P0D3,
				.GPCALPSEL1 = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPSEL_P1D3,
				.GPCALPMODE = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPMODE_THROUGH,
			},
			[1].bit = {
				.GPCALPFIX = 0,
				.GPCALPSEL0 = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPSEL_P0D3,
				.GPCALPSEL1 = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPSEL_P1D3,
				.GPCALPMODE = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPMODE_THROUGH,
			},
			[2].bit = {
				.GPCALPFIX = 0,
				.GPCALPSEL0 = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPSEL_P0D3,
				.GPCALPSEL1 = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPSEL_P1D3,
				.GPCALPMODE = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPMODE_THROUGH,
			},
			[3].bit = {
				.GPCALPFIX = 0,
				.GPCALPSEL0 = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPSEL_P0D3,
				.GPCALPSEL1 = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPSEL_P1D3,
				.GPCALPMODE = ImIipParamEnum_E_IM_IIP_PARAM_GPCALPMODE_THROUGH,
			},
		},
	},
	.interCompCalc = {
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
			[1].bit = {
				.ELESEL0 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D1_CFG9,
				.ELERD0 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT0 = 0,
				.ELESEL1 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D2_CFG9,
				.ELERD1 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT1 = 0,
				.ELESEL2 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D3_ALPHA,
				.ELERD2 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT2 = 0,
				.ELESEL3 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D0_CFG9,
				.ELERD3 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT3 = 0,
				.ELEMODE0 = ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_THROUGH,
				.ELEMODE1 = ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_THROUGH,
				.ELEMODE2 = ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_THROUGH,
				.ELERDO = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFTO = 0,
			},
			[2].bit = {
				.ELESEL0 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D2_CFG9,
				.ELERD0 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT0 = 0,
				.ELESEL1 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D3_ALPHA,
				.ELERD1 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT1 = 0,
				.ELESEL2 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D0_CFG9,
				.ELERD2 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT2 = 0,
				.ELESEL3 = ImIipParamEnum_E_IM_IIP_PARAM_ELESEL_D1_CFG9,
				.ELERD3 = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFT3 = 0,
				.ELEMODE0 = ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_THROUGH,
				.ELEMODE1 = ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_THROUGH,
				.ELEMODE2 = ImIipParamEnum_E_IM_IIP_PARAM_ELEMODE_THROUGH,
				.ELERDO = ImIipParamEnum_E_IM_IIP_PARAM_RND_ROUNDDOWN,
				.ELESHIFTO = 0,
			},
		},
	},
};
#endif  /*CO_CT_IM_IIP_DISABLE*/

/*
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
// GPC Unit 13-1-1
kint32 ct_im_iip_gpc_13_1_1(CtImIipGpc1* self)
{
	CtImIipGpc1Private *priv = CT_IM_IIP_GPC1_GET_PRIVATE(self);

	kint32									ercd;
	TImIipPixfmttbl			pixfmt_tbl_0[2];	// 1DL Unit input
	TImIipPixfmttbl			pixfmt_tbl_1;		// SL Unit output
	ImIipUnitCfg			oned_cfg[2];
	ImIipUnitCfg			gpc_cfg;
	ImIipParam1Dl*		oned_unit_inf[2] = { &gCtImIipUnitParam1Dl0, &g_ct_im_iip_unit_param_1dl1 };
	TImIipParamGpc*		gpc_unit_inf = &S_G_CT_IM_IIP_UNIT_PARAM_GPC;
	ImIipParamSts*		sl_unit_inf = &gCtImIipUnitParamSl0;
	ImIipUnitCfg			sl_cfg;
	kuint32								wait_factor_result = 0;
	const kuint32						wait_factor = ImIip_D_IM_IIP_INT_FACTOR_AXIERR | ImIip_D_IM_IIP_INT_FACTOR_SL2END;
	const kuint32						unitid_bitmask = ImIip_D_IM_IIP_PARAM_PLDUNIT_LD1 | ImIip_D_IM_IIP_PARAM_PLDUNIT_LD2  \
														| D_IM_IIP_PARAM_PLDUNIT_BLEND0 | ImIip_D_IM_IIP_PARAM_PLDUNIT_SL2;
	const kuint32						pixid_bitmask = E_IM_IIP_PIXID_3 | ImIip_E_IM_IIP_PIXID_4 | ImIip_E_IM_IIP_PIXID_5;
	const ImIipEImIipUnitId	src_unitid[2] = { ImIip_E_IM_IIP_UNIT_ID_LD1, ImIip_E_IM_IIP_UNIT_ID_LD2 };
	const ImIipEImIipUnitId	filter_unitid = E_IM_IIP_UNIT_ID_GPC;
	const ImIipEImIipUnitId	dst_unitid = ImIip_E_IM_IIP_UNIT_ID_SL2;
	const ImIipParamEImIipParamPortid		src_portid[2] = { ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1, ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD2 };
	const ImIipParamEImIipParamPortid		filter_portid[2] = { ImIipParamEnum_E_IM_IIP_PARAM_PORTID_GPC_P0, ImIipParamEnum_E_IM_IIP_PARAM_PORTID_GPC_P1 };
	const ImIipParamEImIipParamPortid		dst_portid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32						src_pixid[2] = { 3, 4 };
	const kuint32						dst_pixid = 5;
	const kuint32						open_res_bitmask = ImIip_E_IM_IIP_OPEN_RES_CACHE0;

	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "\n"));

	ercd = im_iip_open_swtrg(unitid_bitmask, pixid_bitmask, open_res_bitmask, CtImIip_D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));
	if(ercd != ImIip_D_IM_IIP_OK) {
		return ercd;
	}

	pixfmt_tbl_0[0] = 								gCtImIipPixfmttblBase;
	pixfmt_tbl_0[0].line_bytes.Y_G = 		CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmt_tbl_0[0].line_bytes.Cb_B = 		CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_0[0].line_bytes.Cr_R = 		CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_0[0].line_bytes.Alpha = 	CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmt_tbl_0[0].addr.Y_G = 				CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	pixfmt_tbl_0[0].addr.Cb_B = 				CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmt_tbl_0[0].addr.Cr_R = 				CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmt_tbl_0[0].addr.Alpha = 			CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A;

	pixfmt_tbl_0[1] = 								gCtImIipPixfmttblBase;
	pixfmt_tbl_0[1].line_bytes.Y_G = 		CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmt_tbl_0[1].line_bytes.Cb_B = 		CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_0[1].line_bytes.Cr_R = 		CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_0[1].line_bytes.Alpha = 	CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmt_tbl_0[1].addr.Y_G = 				CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_Y;
	pixfmt_tbl_0[1].addr.Cb_B = 				CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C;
	pixfmt_tbl_0[1].addr.Cr_R = 				CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C;
	pixfmt_tbl_0[1].addr.Alpha = 			CtImIip_D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_A;

	pixfmt_tbl_1 = 									gCtImIipPixfmttblBase;
	pixfmt_tbl_1.line_bytes.Y_G = 			CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Cb_B = 			CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Cr_R = 			CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	pixfmt_tbl_1.line_bytes.Alpha = 		CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	pixfmt_tbl_1.addr.Y_G = 					CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	pixfmt_tbl_1.addr.Cb_B = 					CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmt_tbl_1.addr.Cr_R = 					CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	pixfmt_tbl_1.addr.Alpha = 					CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "oned_unit_inf[0] = 0x%x 0x%x\n", (kuint32)oned_unit_inf[0], sizeof(ImIipParam1Dl)));

	memset(oned_unit_inf[0], '\0', sizeof(*oned_unit_inf[0]));
	*oned_unit_inf[0] = gCtImIipParam1DlBase;
	oned_unit_inf[0]->LD_TOPCNF0.bit.WAITCONF = filter_portid[0];
	oned_unit_inf[0]->PIXIDDEF.bit.IPIXID = src_pixid[0];
	oned_unit_inf[0]->LD_CTL.bit.SLOW = ImIipParamEnum_E_IM_IIP_PARAM_SLOW_1PIX_CYC;

	oned_cfg[0].unit_ctrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	oned_cfg[0].chain_enable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	oned_cfg[0].unit_param_addr = (ULONG)oned_unit_inf[0];
	oned_cfg[0].load_unit_param_flag = 0;

	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "oned_unit_inf[1] = 0x%x 0x%x\n", (kuint32)oned_unit_inf[1], sizeof(ImIipParam1Dl)));

	memset(oned_unit_inf[1], '\0', sizeof(*oned_unit_inf[1]));
	*oned_unit_inf[1] = gCtImIipParam1DlBase;
	oned_unit_inf[1]->LD_TOPCNF0.bit.WAITCONF = filter_portid[1];
	oned_unit_inf[1]->PIXIDDEF.bit.IPIXID = src_pixid[1];
	oned_unit_inf[1]->LD_CTL.bit.SLOW = ImIipParamEnum_E_IM_IIP_PARAM_SLOW_1PIX_CYC;

	oned_cfg[1].unit_ctrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	oned_cfg[1].chain_enable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	oned_cfg[1].unit_param_addr = (ULONG)oned_unit_inf[1];
	oned_cfg[1].load_unit_param_flag = 0;

	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "gpc_unit_inf = 0x%x 0x%x\n", (kuint32)gpc_unit_inf, sizeof(TImIipParamGpc)));

	memset(gpc_unit_inf, '\0', sizeof(*gpc_unit_inf));
	// *gpc_unit_inf = GCtImIipParamGpcBase;
	*gpc_unit_inf = priv->ctImIip1ParamGpcBase;
	gpc_unit_inf->GPCTOPCNF[0].bit.WAITCONF = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE;	// Port1 output
	gpc_unit_inf->GPCTOPCNF[0].bit.DATACONF = src_portid[0];
	gpc_unit_inf->GPCTOPCNF[1].bit.WAITCONF = dst_portid;					// Port1 output
	gpc_unit_inf->GPCTOPCNF[1].bit.DATACONF = src_portid[1];
	gpc_unit_inf->GPCCLOADADR.bit.CLOADADR = (ULONG)&gCtImIipGpcConfig;

	gpc_cfg.unit_ctrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	gpc_cfg.chain_enable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	gpc_cfg.unit_param_addr = (ULONG)gpc_unit_inf;
	gpc_cfg.load_unit_param_flag = 0;

	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "sl_unit_inf = 0x%x 0x%x\n", (kuint32)sl_unit_inf, sizeof(ImIipParamSts)));

	memset(sl_unit_inf, '\0', sizeof(*sl_unit_inf));
	*sl_unit_inf = gCtImIipParamStsBase;
	sl_unit_inf->BASE.SL_TOPCNF0.bit.DATACONF = filter_portid[1];				// Port1 output
	sl_unit_inf->BASE.PIXIDDEF.bit.OPIXID = dst_pixid;

	sl_cfg.unit_ctrl = ImIip_D_IM_IIP_HW_CTRL_SWTRG;
	sl_cfg.chain_enable = ImIip_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	sl_cfg.unit_param_addr = (ULONG)sl_unit_inf;
	sl_cfg.load_unit_param_flag = unitid_bitmask;

	ct_im_iip_clean_l1l2_dcache_addr((ULONG)oned_unit_inf[0], sizeof(ImIipParam1Dl));
	ct_im_iip_clean_l1l2_dcache_addr((ULONG)oned_unit_inf[1], sizeof(ImIipParam1Dl));
	ct_im_iip_clean_l1l2_dcache_addr((ULONG)gpc_unit_inf, sizeof(TImIipParamGpc));
	ct_im_iip_clean_l1l2_dcache_addr((ULONG)&gCtImIipGpcConfig, sizeof(TImIzaParamGpcCongif));
	ct_im_iip_clean_l1l2_dcache_addr((ULONG)sl_unit_inf, sizeof(ImIipParamSts));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	palladium_test_set_out_localstack((ULONG)oned_unit_inf[0], sizeof(ImIipParam1Dl));
	palladium_test_set_out_localstack((ULONG)oned_unit_inf[1], sizeof(ImIipParam1Dl));
	palladium_test_set_out_localstack((ULONG)gpc_unit_inf, sizeof(TImIipParamGpc));
	palladium_test_set_out_localstack((ULONG)sl_unit_inf, sizeof(ImIipParamSts));
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	ercd = im_iip_ctrl_pixfmttbl(src_pixid[0], &pixfmt_tbl_0[0]);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	ercd = im_iip_ctrl_pixfmttbl(src_pixid[1], &pixfmt_tbl_0[1]);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	ercd = im_iip_ctrl_pixfmttbl(dst_pixid, &pixfmt_tbl_1);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(src_unitid[0], &oned_cfg[0]);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(src_unitid[1], &oned_cfg[1]);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(filter_unitid, &gpc_cfg);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(dst_unitid, &sl_cfg);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Set_Interrupt(wait_factor, D_IM_IIP_ENABLE_ON);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	DdArm_Dd_ARM_Dmb_Pou();

	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "Start1\n"));
	ercd = im_iip_start_swteg(dst_unitid, D_IM_IIP_SWTRG_ON);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "Start2\n"));
	ercd = im_iip_start_swteg(filter_unitid, D_IM_IIP_SWTRG_ON);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "Start3\n"));
	ercd = im_iip_start_swteg(src_unitid[0], D_IM_IIP_SWTRG_ON);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "Start4\n"));
	ercd = im_iip_start_swteg(src_unitid[1], D_IM_IIP_SWTRG_ON);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

#if 0
	for(kuint32 loopcnt = 0; loopcnt < 10; loopcnt++) {
		CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					IO_IIP.IZACTL1.bit.SLALE,
					IO_IIP.INTIZ0.word,
					IO_IIP.INTIZ1.word
				  ));
		ddim_user_custom_dly_tsk(1);
	}
#endif

	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "WaitEnd\n"));
	ercd = im_iip_wait_end(&wait_factor_result, wait_factor, D_IM_IIP_OR_WAIT, 30);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x factor=0x%x\n", ercd, wait_factor_result));
	if(ercd != D_DDIM_OK) {
		CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "Stop\n"));
		ercd = im_iip_stop(D_IM_IIP_ABORT);
		CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x factor=0x%x\n", ercd, wait_factor_result));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	// UnitINFダンプ
	palladium_test_set_out_localstack((ULONG)oned_unit_inf[0], sizeof(ImIipParam1Dl));
	palladium_test_set_out_localstack((ULONG)oned_unit_inf[1], sizeof(ImIipParam1Dl));
	palladium_test_set_out_localstack((ULONG)gpc_unit_inf, sizeof(T_IM_IIP_PARAM_LUT));
	palladium_test_set_out_localstack((ULONG)sl_unit_inf, sizeof(ImIipParamSts));
#endif

#if 0
	// dump UNITINF ONED[1]
	{
		kuint32 param_bytes;
		ercd = im_iip_get_unit_param(src_unitid[0], g_get_unit_param, &param_bytes);
		CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = %d bytes = %u\n", ercd, param_bytes));
		if(ercd == ImIip_D_IM_IIP_OK) {
			CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "dump UNITINF ONED[1] %u\n", param_bytes));
			ct_im_iip_clean_l1l2_dcache_addr((ULONG)g_get_unit_param, param_bytes);
			palladium_test_set_out_localstack((ULONG)g_get_unit_param, param_bytes);
		}
	}
#endif

#if 0
	// dump UNITINF ONED[2]
	{
		kuint32 param_bytes;
		ercd = im_iip_get_unit_param(src_unitid[1], g_get_unit_param, &param_bytes);
		CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = %d bytes = %u\n", ercd, param_bytes));
		if(ercd == ImIip_D_IM_IIP_OK) {
			CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "dump UNITINF ONED[2] %u\n", param_bytes));
			ct_im_iip_clean_l1l2_dcache_addr((ULONG)g_get_unit_param, param_bytes);
			palladium_test_set_out_localstack((ULONG)g_get_unit_param, param_bytes);
		}
	}
#endif

#if 0
	// dump UNITINF gpc
	{
		kuint32 param_bytes;
		ercd = im_iip_get_unit_param(filter_unitid, g_get_unit_param, &param_bytes);
		CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = %d bytes = %u\n", ercd, param_bytes));
		if(ercd == ImIip_D_IM_IIP_OK) {
			CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "dump UNITINF gpc %u\n", param_bytes));
			ct_im_iip_clean_l1l2_dcache_addr((ULONG)g_get_unit_param, param_bytes);
			palladium_test_set_out_localstack((ULONG)g_get_unit_param, param_bytes);
		}
	}
#endif

#if 0
	// dump UNITINF SL[2]
	{
		kuint32 param_bytes;
		ercd = im_iip_get_unit_param(dst_unitid, g_get_unit_param, &param_bytes);
		CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = %d bytes = %u\n", ercd, param_bytes));
		if(ercd == ImIip_D_IM_IIP_OK) {
			CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "dump UNITINF SL[2] %u\n", param_bytes));
			ct_im_iip_clean_l1l2_dcache_addr((ULONG)g_get_unit_param, param_bytes);
			palladium_test_set_out_localstack((ULONG)g_get_unit_param, param_bytes);
		}
	}
#endif


#if 0
#ifndef CO_DEBUG_ON_PC
	// dump IO_IIP
	{
		ULONG regdump_addr = CtImIip_D_IM_IIP_REGDUMP_ADDR;
		ULONG regdump_bytes = sizeof(IO_IIP);
		CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "dump IO_IIP %u\n", regdump_bytes));
		memcpy((void*)regdump_addr, (void*)&IO_IIP, regdump_bytes);
		palladium_test_set_out_localstack(regdump_addr, regdump_bytes);
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "im_iip_close_swtrg\n"));
	ercd = im_iip_close_swtrg(unitid_bitmask, pixid_bitmask, open_res_bitmask);
	CtImIipGpc1_Ddim_Print(("CT_Im_IIP_13_1_1: " "ercd = 0x%x\n", ercd));

	return D_DDIM_OK;
}

TImIipParamGpc ct_im_iip1_gpc_get_param_gpc_base(CtImIipGpc1 *self)
{
	CtImIipGpc1Private *priv = CT_IM_IIP_GPC1_GET_PRIVATE(self);

	return priv->ctImIip1ParamGpcBase;
}
#endif  /*CO_CT_IM_IIP_DISABLE*/

CtImIipGpc1* ct_im_iip_gpc1_new(void) 
{
    CtImIipGpc1 *self = k_object_new_with_private(CT_TYPE_IM_IIP_GPC1, sizeof(CtImIipGpc1Private));
    return self;
}
