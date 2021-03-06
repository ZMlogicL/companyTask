/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtImIipLut类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_im_iip_lut.c
 * @brief		IIP LUT unit ct code
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

// CT header
#include "ctimiip.h"

// ### REMOVE_RELEASE BEGIN
// PT header
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#endif //CO_PT_ENABLE

// ### REMOVE_RELEASE END
// im_iip header
#include "imiipdefine.h"

// MILB register header 
#include "jdsiip.h"

// for Memory barrier
#include "ddarm.h"

// for memset
#include <string.h>
#include "ctimiiplut.h"
#include "imiipunitparameter.h"

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif
#endif

K_TYPE_DEFINE_WITH_PRIVATE(CtImIipLut, ct_im_iip_lut);
#define CT_IM_IIP_LUT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImIipLutPrivate,CT_TYPE_IM_IIP_LUT))

struct _CtImIipLutPrivate {
    CtImIipLut *	ciIipLut;
	TImIipPixfmttbl	pixfmtTbl0;		// 1DL Unit input
	TImIipPixfmttbl	pixfmtTbl1;		// SL Unit output
	TImIipUnitCfg	onedCfg;
	TImIipUnitCfg	lutCfg;
	Tim1dl*			onedUnitInf;
#ifndef CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	TimLut*			lutUnitInf;
#endif //CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	TimSts*			slUnitInf;
	TImIipUnitCfg	slCfg;
};

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#undef Ddim_Print
#define CtImIipLut_DDIM_PRINT(arg)		{DDIM_User_Printf arg;}		/**< printf function inside DDIM */
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

#if !defined(CO_CT_IM_IIP_5_1_1_DISABLE_LUT) || !defined(CO_CT_IM_IIP_5_1_2_DISABLE_LUT)
static const TimLut S_G_CT_IM_IIP_PARAM_LUT_BASE = {
	.header0.bit.BeginningAddress = 0x0000,
	.header0.bit.WordLength = 57,
	.header0.bit.CtrlCode = ImIipParamEnum_E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET,
	.luttopcnf = {
//		[0] = {
//				.bit.waitconf,						// set later
//				.bit.dataconf,						// set later
//		},
		[1] = {
				.bit.waitconf = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE,
				.bit.dataconf = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE,
		},
		[2] = {
				.bit.waitconf = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE,
				.bit.dataconf = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE,
		},
		[3] = {
				.bit.waitconf = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE,
				.bit.dataconf = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_NONE,
		},
	},
	.lutunitctl.bit.porten = 3,		// D0=LUTA, D1=LUTB, D2=LUTC D3=through
	.lutunitctl.bit.port3seli = 0,
	.lutunitctl.bit.port3selo = 0,
	.lutunitctl.bit.branch = 0,
	.lutunitctl.bit.port2seli = 0,
	.lutunitctl.bit.port2selo = 0,
	.lutunitctl.bit.outmd0 = 0,
	.lutunitctl.bit.outmd1 = 0,
	.lutunitctl.bit.outmd2 = 0,
	.lutunitctl.bit.outmd3 = 0,
	.lutctlA.bit = {
		.lutbit = 8,
		.use 	= ImIipParamEnum_E_IM_IIP_PARAM_LUTUSE_LUT_OUT,
		.sgn 	= ImIipParamEnum_E_IM_IIP_PARAM_LUTSGN_UNSIGN,
		.splbit = 0,
	},
	.lutprecalA.bit = {
		.shift 	 = 0,
		.ofset 	 = 0,
		.clpmax  = 0x3fff,
		.thmax	 = 0x3fff,
		.clpmin  = 0x4000,
		.thmin 	 = 0x4000,
		.abs 	 = 1,
		.lutadrs = 0,
	},
	.lutctlB.bit = {
		.lutbit = 8,
		.use 	= ImIipParamEnum_E_IM_IIP_PARAM_LUTUSE_LUT_OUT,
		.sgn 	= ImIipParamEnum_E_IM_IIP_PARAM_LUTSGN_UNSIGN,
		.splbit = 0,
	},
	.lutprecalB.bit = {
		.shift	 = 0,
		.ofset	 = 0,
		.clpmax	 = 0x3fff,
		.thmax	 = 0x3fff,
		.clpmin	 = 0x4000,
		.thmin	 = 0x4000,
		.abs	 = 1,
		.lutadrs = 0,
	},
	.lutctlC.bit = {
		.lutbit = 8,
		.use 	= ImIipParamEnum_E_IM_IIP_PARAM_LUTUSE_LUT_OUT,
		.sgn 	= ImIipParamEnum_E_IM_IIP_PARAM_LUTSGN_UNSIGN,
		.splbit = 0,
	},
	.lutprecalC.bit = {
		.shift	 = 0,
		.ofset	 = 0,
		.clpmax	 = 0x3fff,
		.thmax	 = 0x3fff,
		.clpmin	 = 0x4000,
		.thmin	 = 0x4000,
		.abs	 = 1,
		.lutadrs = 0,
	},
	.lutctlD.bit = {
		.lutbit = 8,
		.use 	= ImIipParamEnum_E_IM_IIP_PARAM_LUTUSE_LUT_OUT,
		.sgn 	= ImIipParamEnum_E_IM_IIP_PARAM_LUTSGN_UNSIGN,
		.splbit = 0,
	},
	.lutprecalD.bit = {
		.shift	 = 0,
		.ofset	 = 0,
		.clpmax	 = 0x3fff,
		.thmax	 = 0x3fff,
		.clpmin	 = 0x4000,
		.thmin	 = 0x4000,
		.abs	 = 1,
		.lutadrs = 0,
	},
	.lutctlE.bit = {
		.lutbit = 8,
		.use	= ImIipParamEnum_E_IM_IIP_PARAM_LUTUSE_LUT_OUT,
		.sgn 	= ImIipParamEnum_E_IM_IIP_PARAM_LUTSGN_UNSIGN,
		.splbit = 0,
	},
	.lutprecalE.bit = {
		.shift	 = 0,
		.ofset	 = 0,
		.clpmax	 = 0x3fff,
		.thmax	 = 0x3fff,
		.clpmin	 = 0x4000,
		.thmin	 = 0x4000,
		.abs	 = 1,
		.lutadrs = 0,
	},
	.lutctlF.bit = {
		.lutbit = 8,
		.use	= ImIipParamEnum_E_IM_IIP_PARAM_LUTUSE_LUT_OUT,
		.sgn 	= ImIipParamEnum_E_IM_IIP_PARAM_LUTSGN_UNSIGN,
		.splbit = 0,
	},
	.lutprecalF.bit = {
		.shift	 = 0,
		.ofset	 = 0,
		.clpmax	 = 0x3fff,
		.thmax	 = 0x3fff,
		.clpmin	 = 0x4000,
		.thmin	 = 0x4000,
		.abs	 = 1,
		.lutadrs = 0,
	},
};
#endif //!CO_CT_IM_IIP_5_1_1_DISABLE_LUT && !CO_CT_IM_IIP_5_1_2_DISABLE_LUT

#ifdef __GNUC__
static TimLut	S_G_CT_IM_IIP_UNIT_PARAM_LUT __attribute__((aligned(8)));	// Needs 8bytes align
#else
static __align(8) TimLut	S_G_CT_IM_IIP_UNIT_PARAM_LUT;					// Needs 8bytes align
#endif

#if !defined(CO_CT_IM_IIP_5_1_1_DISABLE_LUT)
static const kushort S_G_CT_IM_IIP_LUTRAM[256] = {
		   0,    1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,	//    0
		  16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,	//   16
		  32,   33,   34,   35,   36,   37,   38,   39,   40,   41,   42,   43,   44,   45,   46,   47,	//   32
		  48,   49,   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,   61,   62,   63,	//   48
		  64,   65,   66,   67,   68,   69,   70,   71,   72,   73,   74,   75,   76,   77,   78,   79,	//   64
		  80,   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,   91,   92,   93,   94,   95,	//   80
		  96,   97,   98,   99,  100,  101,  102,  103,  104,  105,  106,  107,  108,  109,  110,  111,	//   96
		 112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,  126,  127,	//  112
		 128,  129,  130,  131,  132,  133,  134,  135,  136,  137,  138,  139,  140,  141,  142,  143,	//  128
		 144,  145,  146,  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,	//  144
		 160,  161,  162,  163,  164,  165,  166,  167,  168,  169,  170,  171,  172,  173,  174,  175,	//  160
		 176,  177,  178,  179,  180,  181,  182,  183,  184,  185,  186,  187,  188,  189,  190,  191,	//  176
		 192,  193,  194,  195,  196,  197,  198,  199,  200,  201,  202,  203,  204,  205,  206,  207,	//  192
		 208,  209,  210,  211,  212,  213,  214,  215,  216,  217,  218,  219,  220,  221,  222,  223,	//  208
		 224,  225,  226,  227,  228,  229,  230,  231,  232,  233,  234,  235,  236,  237,  238,  239,	//  224
		 240,  241,  242,  243,  244,  245,  246,  247,  248,  249,  250,  251,  252,  253,  254,  255,	//  240
};
#endif //!CO_CT_IM_IIP_5_1_1_DISABLE_LUT

#ifndef CO_CT_IM_IIP_5_1_2_DISABLE_LUT
static const kushort S_G_CT_IM_IIP_LUTRAM_INVERT[256] = {
		 255,  254,  253,  252,  251,  250,  249,  248,  247,  246,  245,  244,  243,  242,  241,  240,	//    0
		 239,  238,  237,  236,  235,  234,  233,  232,  231,  230,  229,  228,  227,  226,  225,  224,	//   16
		 223,  222,  221,  220,  219,  218,  217,  216,  215,  214,  213,  212,  211,  210,  209,  208,	//   32
		 207,  206,  205,  204,  203,  202,  201,  200,  199,  198,  197,  196,  195,  194,  193,  192,	//   48
		 191,  190,  189,  188,  187,  186,  185,  184,  183,  182,  181,  180,  179,  178,  177,  176,	//   64
		 175,  174,  173,  172,  171,  170,  169,  168,  167,  166,  165,  164,  163,  162,  161,  160,	//   80
		 159,  158,  157,  156,  155,  154,  153,  152,  151,  150,  149,  148,  147,  146,  145,  144,	//   96
		 143,  142,  141,  140,  139,  138,  137,  136,  135,  134,  133,  132,  131,  130,  129,  128,	//  112
		 127,  126,  125,  124,  123,  122,  121,  120,  119,  118,  117,  116,  115,  114,  113,  112,	//  128
		 111,  110,  109,  108,  107,  106,  105,  104,  103,  102,  101,  100,   99,   98,   97,   96,	//  144
		  95,   94,   93,   92,   91,   90,   89,   88,   87,   86,   85,   84,   83,   82,   81,   80,	//  160
		  79,   78,   77,   76,   75,   74,   73,   72,   71,   70,   69,   68,   67,   66,   65,   64,	//  176
		  63,   62,   61,   60,   59,   58,   57,   56,   55,   54,   53,   52,   51,   50,   49,   48,	//  192
		  47,   46,   45,   44,   43,   42,   41,   40,   39,   38,   37,   36,   35,   34,   33,   32,	//  208
		  31,   30,   29,   28,   27,   26,   25,   24,   23,   22,   21,   20,   19,   18,   17,   16,	//  224
		  15,   14,   13,   12,   11,   10,    9,    8,    7,    6,    5,    4,    3,    2,    1,    0,	//  240
};
#endif //!CO_CT_IM_IIP_5_1_2_DISABLE_LUT

static void ct_im_iip_lut_constructor(CtImIipLut *self) 
{
	CtImIipLutPrivate *priv = CT_IM_IIP_LUT_GET_PRIVATE(self);
	priv->ciIipLut = ct_im_iip_lut_new();
	priv->onedUnitInf = &gCtImIipUnitParam1dl0;
#ifndef CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	priv->lutUnitInf = &S_G_CT_IM_IIP_UNIT_PARAM_LUT;
#endif //CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	priv->slUnitInf = &gCtImIipUnitParamSl0;
}

static void ct_im_iip_lut_destructor(CtImIipLut *self)
{
	CtImIipLutPrivate *priv = CT_IM_IIP_LUT_GET_PRIVATE(self);
	if(priv->ciIipLut){
		k_object_unref(priv);
	}
	priv->ciIipLut = NULL;
}
/*
 *PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/

// LUT Unit 5-1-1 YCC422 U8 VGA->VGA
#undef D_IM_IIP_FUNC_NAME
#define CtImIipLut_D_IM_IIP_FUNC_NAME "ct_im_iip_lut_5_1_1: "
kint32 ct_im_iip_lut_5_1_1(CtImIipLut *self)
{
	CtImIipLutPrivate *	priv = CT_IM_IIP_LUT_GET_PRIVATE(self);

	kint32				ercd;
#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	TImIipLut			lutCtrl;
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	kuint32				waitFactorResult = 0;
	const kuint32		waitFactor = ImIipDefine_D_IM_IIP_INT_FACTOR_AXIERR 
							| ImIipDefine_D_IM_IIP_INT_FACTOR_SL2END;
#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	const kuint32		unitidBitmask = ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD1 
							| ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LUT | ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL2;
#else //CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	const kuint32		unitidBitmask = ImIipParamEnum_D_IM_IIP_PARAM_PLDUNIT_LD1 | 
							ImIipParamEnum_D_IM_IIP_PARAM_PLDUNIT_SL2;
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	const kuint32		pixidBitmask = ImIipStruct_E_IM_IIP_PIXID_4 | ImIipStruct_E_IM_IIP_PIXID_5;
	const EImIipUnitId	srcUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_LD1;
#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	const EImIipUnitId	filterUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_LUT;
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	const EImIipUnitId	dstUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL2;
	const EimPortid		srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1;
#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	const EimPortid		filterPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LUT_P0;
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	const EimPortid		dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
	const kuint32		srcPixid = 4;
	const kuint32		dstPixid = 5;
#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	const kuint32		openResBitmask = ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0 | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_A 
                        	| ImIipStruct_E_IM_IIP_OPEN_RES_LUT_B | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_C 
							| ImIipStruct_E_IM_IIP_OPEN_RES_LUT_D | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_E 
							| ImIipStruct_E_IM_IIP_OPEN_RES_LUT_F;
#else //CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	const kuint32		openResBitmask = ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0;
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT


	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "\n"));

	ercd = Im_IIP_Open_SWTRG(unitidBitmask, pixidBitmask, openResBitmask, 
		CtImIip_D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));
	if(ercd != ImIipDefine_D_IM_IIP_OK) {
		return ercd;
	}

	priv->pixfmtTbl0 = gCtImIipPixfmttblBase;
	priv->pixfmtTbl0.lineBytes.yG = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.cbB = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.crR = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	priv->pixfmtTbl0.addr.yG = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	priv->pixfmtTbl0.addr.cbB = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.crR = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A;

	priv->pixfmtTbl1 = gCtImIipPixfmttblBase;
	priv->pixfmtTbl1.lineBytes.yG = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.cbB = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.crR = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	priv->pixfmtTbl1.addr.yG = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	priv->pixfmtTbl1.addr.cbB = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.crR = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "lutram = 0x%x 0x%x\n", 
        (kuint32)S_G_CT_IM_IIP_LUTRAM, sizeof(S_G_CT_IM_IIP_LUTRAM)));

	lutCtrl.bufferBytes = sizeof(S_G_CT_IM_IIP_LUTRAM);
	lutCtrl.bufferAddr = S_G_CT_IM_IIP_LUTRAM;
	lutCtrl.lutramType = ImIipStruct_E_IM_IIP_LUTRAM_TYPE_A;
	ercd = Im_IIP_Ctrl_LUT(&lutCtrl);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x lutram_type=%u\n", 
		ercd, lutCtrl.lutramType));
	lutCtrl.lutram_type = ImIipStruct_E_IM_IIP_LUTRAM_TYPE_B;
	ercd = Im_IIP_Ctrl_LUT(&lutCtrl);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x lutram_type=%u\n", 
		ercd, lutCtrl.lutramType));
	lutCtrl.lutram_type = ImIipStruct_E_IM_IIP_LUTRAM_TYPE_C;
	ercd = Im_IIP_Ctrl_LUT(&lutCtrl);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x lutram_type=%u\n", 
		ercd, lutCtrl.lutramType));
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n",  
        (kuint32)priv->onedUnitInf, sizeof(Tim1dl)));

	memset(priv->onedUnitInf, '\0', sizeof(*priv->onedUnitInf));
	*priv->onedUnitInf = gCtImIipParam1dlBase;
#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	priv->onedUnitInf->ldTopcnf0.bit.waitconf = filterPortid;
#else //CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	priv->onedUnitInf->ldTopcnf0.bit.waitconf = dstPortid;
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	priv->onedUnitInf->pixiddef.bit.ipixid = srcPixid;

	priv->onedCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->onedCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->onedCfg.unitParamAddr = (kulong)priv->onedUnitInf;
	priv->onedCfg.loadUnitParamFlag = 0;

#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "lutUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->lutUnitInf, sizeof(TimLut)));

	memset(priv->lutUnitInf, '\0', sizeof(*priv->lutUnitInf));
	*priv->lutUnitInf = S_G_CT_IM_IIP_PARAM_LUT_BASE;
	priv->lutUnitInf->luttopcnf[0].bit.dataconf = srcPortid;
	priv->lutUnitInf->luttopcnf[0].bit.waitconf = dstPortid;

	priv->lutCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->lutCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->lutCfg.unitParamAddr = (kulong)priv->lutUnitInf;
	priv->lutCfg.loadUnitParamFlag = 0;
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->slUnitInf, sizeof(TimSts)));

	memset(priv->slUnitInf, '\0', sizeof(*priv->slUnitInf));
	*priv->slUnitInf = gCtImIipParamStsBase;
#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	priv->slUnitInf->base.slTopcnf0.bit.dataconf = filterPortid;
#else //CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	priv->slUnitInf->base.slTopcnf0.bit.dataconf = srcPortid;
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	priv->slUnitInf->base.pixiddef.bit.opixid = dstPixid;


	priv->slCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->slCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->slCfg.unitParamAddr = (kulong)priv->slUnitInf;
	priv->slCfg.loadUnitParamFlag = unitidBitmask;

	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->onedUnitInf, sizeof(Tim1dl));
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->lutUnitInf, sizeof(TimLut));
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->slUnitInf, sizeof(TimSts));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	Palladium_Set_Out_Localstack((kulong)priv->onedUnitInf, sizeof(Tim1dl));
	Palladium_Set_Out_Localstack((kulong)priv->lutUnitInf, sizeof(TimLut));
	Palladium_Set_Out_Localstack((kulong)priv->slUnitInf, sizeof(TimSts));
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	ercd = Im_IIP_Ctrl_PIXFMTTBL(srcPixid, &priv->pixfmtTbl0);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Ctrl_PIXFMTTBL(dstPixid, &priv->pixfmtTbl1);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(srcUnitid, &priv->onedCfg);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	ercd = Im_IIP_Ctrl_SWTRG_Unit(filterUnitid, &priv->lutCfg);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT

	ercd = Im_IIP_Ctrl_SWTRG_Unit(dstUnitid, &priv->slCfg);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Set_Interrupt(waitFactor, ImIipDefine_D_IM_IIP_ENABLE_ON);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	im_iip_struct_on_pclk();
	CtImIipLut_DDIM_PRINT(("ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblLd1.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblLd1.unitinftbl0.bit.hwen));
#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	CtImIipLut_DDIM_PRINT(("LUT: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblLut.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblLut.unitinftbl0.bit.hwen));
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	CtImIipLut_DDIM_PRINT(("SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.unitinftblSl2.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblSl2.unitinftbl0.bit.hwen,
				(kuint32)ioIip.unitinftblSl2.unitinftbl1.bit.pldunitHi,
				(kuint32)ioIip.unitinftblSl2.unitinftbl1.bit.pldunitLo));
	im_iip_struct_off_pclk();

	DD_ARM_DMB_POU();

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "Start1\n"));
	ercd = Im_IIP_Start_SWTRG(dstUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

#ifndef CO_CT_IM_IIP_5_1_1_DISABLE_LUT
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "Start2\n"));
	ercd = Im_IIP_Start_SWTRG(filterUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));
#endif //CO_CT_IM_IIP_5_1_1_DISABLE_LUT

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "Start3\n"));
	ercd = Im_IIP_Start_SWTRG(srcUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

#if 0
	for(kuint32 loopcnt = 0; loopcnt < 10; loopcnt++) {
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					ioIip.IZACTL1.bit.SLALE,
					ioIip.INTIZ0.word,
					ioIip.INTIZ1.word));
		DDIM_User_Dly_Tsk(1);
	}
#endif

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "WaitEnd\n"));
	ercd = Im_IIP_Wait_End(&waitFactorResult, waitFactor, ImIipDefine_D_IM_IIP_OR_WAIT, 30);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
		ercd, waitFactorResult));
	if(ercd != D_DDIM_OK) {
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "Stop\n"));
		ercd = im_iip_main_stop(ImIipDefine_D_IM_IIP_ABORT);
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", 
			ercd, waitFactorResult));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 1
	// UnitINFダンプ
	Palladium_Set_Out_Localstack((kulong)priv->onedUnitInf, sizeof(Tim1dl));
	Palladium_Set_Out_Localstack((kulong)priv->lutUnitInf, sizeof(TimLut));
	Palladium_Set_Out_Localstack((kulong)priv->slUnitInf, sizeof(TimSts));
#endif


#if 1
	// dump UNITINF ONED[1]
	{
		kuint32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM(srcUnitid, gCtImIIP_Get_Unit_Param, &param_bytes);
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes));
		if(ercd == ImIipDefine_D_IM_IIP_OK) {
			CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "dump UNITINF ONED[1] %u\n", param_bytes));
			CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
		}
	}
#endif


#if 0
	// dump UNITINF LUT
	{
		kuint32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM(filterUnitid, gCtImIIP_Get_Unit_Param, &param_bytes);
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes));
		if(ercd == ImIipDefine_D_IM_IIP_OK) {
			CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "dump UNITINF LUT %u\n", param_bytes));
			CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
		}
	}
#endif


#if 1
	// dump UNITINF SL[2]
	{
		kuint32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM(dstUnitid, gCtImIIP_Get_Unit_Param, &param_bytes);
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes));
		if(ercd == ImIipDefine_D_IM_IIP_OK) {
			CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", param_bytes));
			CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
		}
	}
#endif


#if 0
#ifndef CO_DEBUG_ON_PC
	// dump ioIip
	{
		kulong regdump_addr = D_IM_IIP_REGDUMP_ADDR;
		kulong regdump_bytes = sizeof(ioIip);
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "dump ioIip %u\n", regdump_bytes));
		memcpy((void*)regdump_addr, (void*)&ioIip, regdump_bytes);
		Palladium_Set_Out_Localstack(regdump_addr, regdump_bytes);
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n"));
	ercd = Im_IIP_Close_SWTRG(unitidBitmask, pixidBitmask, openResBitmask);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	return D_DDIM_OK;
}


// LUT Unit 5-1-2 YCC422 U8 VGA->VGA pixval is inverting
#undef CtImIipLut_D_IM_IIP_FUNC_NAME
#define CtImIipLut_D_IM_IIP_FUNC_NAME "ct_im_iip_lut_5_1_2: "
kint32 ct_im_iip_lut_5_1_2(CtImIipLut *self)
{
	CtImIipLutPrivate *	priv = CT_IM_IIP_LUT_GET_PRIVATE(self);

	kint32				ercd;
#ifndef CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	TImIipLut			lutCtrl;
#endif //CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	kuint32				waitFactorResult = 0;
	const kuint32		waitFactor = ImIipDefine_D_IM_IIP_INT_FACTOR_AXIERR | ImIipDefine_D_IM_IIP_INT_FACTOR_SL2END;
	const kuint32		unitidBitmask = ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LD1 
							| ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_LUT | ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL2;
	const kuint32		pixidBitmask = ImIipStruct_E_IM_IIP_PIXID_4 | ImIipStruct_E_IM_IIP_PIXID_5;
	const EImIipUnitId	srcUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_LD1;
	const EImIipUnitId	filterUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_LUT;
	const EImIipUnitId	dstUnitid = ImIipStruct_E_IM_IIP_UNIT_ID_SL2;
	const EimPortid		filterPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LUT_P0;
#ifndef CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	const EimPortid		srcPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_LD1;
	const EimPortid		dstPortid = ImIipParamEnum_E_IM_IIP_PARAM_PORTID_SL2;
#endif //CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	const kuint32		srcPixid = 4;
	const kuint32		dstPixid = 5;
	const kuint32		openResBitmask = ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0 | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_A 
                            | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_B | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_C;


	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "\n"));

	ercd = Im_IIP_Open_SWTRG(unitidBitmask, pixidBitmask, openResBitmask, CtImIip_D_CT_IM_IIP_OPEN_TIMEOUT_MSEC);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));
	if(ercd != ImIipDefine_D_IM_IIP_OK) {
		return ercd;
	}

	priv->pixfmtTbl0 = gCtImIipPixfmttblBase;
	priv->pixfmtTbl0.lineBytes.yG = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.cbB = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.crR = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl0.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	priv->pixfmtTbl0.addr.yG = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_Y;
	priv->pixfmtTbl0.addr.cbB = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.crR = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_C;
	priv->pixfmtTbl0.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_0_YCC422_U8_A;

	priv->pixfmtTbl1 = gCtImIipPixfmttblBase;
	priv->pixfmtTbl1.lineBytes.yG = CtImIip_D_IM_IIP_VGA_YCC422_U8_Y_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.cbB = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.crR = CtImIip_D_IM_IIP_VGA_YCC422_U8_C_GLOBAL_WIDTH;
	priv->pixfmtTbl1.lineBytes.Alpha = CtImIip_D_IM_IIP_VGA_YCC422_U8_A_GLOBAL_WIDTH;
	priv->pixfmtTbl1.addr.yG = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_Y;
	priv->pixfmtTbl1.addr.cbB = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.crR = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_C;
	priv->pixfmtTbl1.addr.Alpha = CtImIip_D_IM_IIP_IMG_MEM_ADDR_1_YCC422_U8_A;

#ifndef CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "lutram = 0x%x 0x%x\n", 
		(kuint32)S_G_CT_IM_IIP_LUTRAM_INVERT, sizeof(S_G_CT_IM_IIP_LUTRAM_INVERT)));

	lutCtrl.bufferBytes = sizeof(S_G_CT_IM_IIP_LUTRAM_INVERT);
	lutCtrl.bufferAddr = S_G_CT_IM_IIP_LUTRAM_INVERT;
	lutCtrl.lutramType = ImIipStruct_E_IM_IIP_LUTRAM_TYPE_A;
	ercd = Im_IIP_Ctrl_LUT(&lutCtrl);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x lutram_type=%u\n", ercd, lutCtrl.lutramType));
	lutCtrl.lutram_type = ImIipStruct_E_IM_IIP_LUTRAM_TYPE_B;
	ercd = Im_IIP_Ctrl_LUT(&lutCtrl);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x lutram_type=%u\n", ercd, lutCtrl.lutramType));
	lutCtrl.lutram_type = ImIipStruct_E_IM_IIP_LUTRAM_TYPE_C;
	ercd = Im_IIP_Ctrl_LUT(&lutCtrl);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x lutram_type=%u\n", ercd, lutCtrl.lutramType));
#endif //CO_CT_IM_IIP_5_1_2_DISABLE_LUT

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "onedUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->onedUnitInf, sizeof(Tim1dl)));

	memset(priv->onedUnitInf, '\0', sizeof(*priv->onedUnitInf));
	*priv->onedUnitInf = gCtImIipParam1dlBase;
	priv->onedUnitInf->ldTopcnf0.bit.waitconf = filterPortid;
	priv->onedUnitInf->pixiddef.bit.ipixid = srcPixid;

	priv->onedCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->onedCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->onedCfg.unitParamAddr = (kulong)priv->onedUnitInf;
	priv->onedCfg.loadUnitParamFlag = 0;

#ifndef CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "lutUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->lutUnitInf, sizeof(TimLut)));

	memset(priv->lutUnitInf, '\0', sizeof(*priv->lutUnitInf));
	*priv->lutUnitInf = S_G_CT_IM_IIP_PARAM_LUT_BASE;
	priv->lutUnitInf->luttopcnf[0].bit.dataconf = srcPortid;
	priv->lutUnitInf->luttopcnf[0].bit.waitconf = dstPortid;

	priv->lutCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->lutCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->lutCfg.unitParamAddr = (kulong)priv->lutUnitInf;
	priv->lutCfg.loadUnitParamFlag = 0;
#endif //CO_CT_IM_IIP_5_1_2_DISABLE_LUT

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "slUnitInf = 0x%x 0x%x\n", 
        (kuint32)priv->slUnitInf, sizeof(TimSts)));

	memset(priv->slUnitInf, '\0', sizeof(*priv->slUnitInf));
	*priv->slUnitInf = gCtImIipParamStsBase;
	priv->slUnitInf->base.slTopcnf0.bit.dataconf = filterPortid;
	priv->slUnitInf->base.pixiddef.bit.opixid = dstPixid;


	priv->slCfg.unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	priv->slCfg.chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
	priv->slCfg.unitParamAddr = (kulong)priv->slUnitInf;
	priv->slCfg.loadUnitParamFlag = unitidBitmask;

	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->onedUnitInf, sizeof(Tim1dl));
#ifndef CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->lutUnitInf, sizeof(TimLut));
#endif //CO_CT_IM_IIP_5_1_2_DISABLE_LUT
	CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)priv->slUnitInf, sizeof(TimSts));

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	Palladium_Set_Out_Localstack((kulong)priv->onedUnitInf, sizeof(Tim1dl));
	Palladium_Set_Out_Localstack((kulong)priv->lutUnitInf, sizeof(TimLut));
	Palladium_Set_Out_Localstack((kulong)priv->slUnitInf, sizeof(TimSts));
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	ercd = Im_IIP_Ctrl_PIXFMTTBL(srcPixid, &priv->pixfmtTbl0);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Ctrl_PIXFMTTBL(dstPixid, &priv->pixfmtTbl1);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(srcUnitid, &priv->onedCfg);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(filterUnitid, &priv->lutCfg);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Ctrl_SWTRG_Unit(dstUnitid, &priv->slCfg);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	ercd = Im_IIP_Set_Interrupt(waitFactor, ImIipDefine_D_IM_IIP_ENABLE_ON);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	im_iip_struct_on_pclk();
	CtImIipLut_DDIM_PRINT(("ONED[1]: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblLd1.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblLd1.unitinftbl0.bit.hwen));
	CtImIipLut_DDIM_PRINT(("LUT: PADRS=0x%x HWEN=%u\n",
				(kuint32)ioIip.unitinftblLut.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblLut.unitinftbl0.bit.hwen));
	CtImIipLut_DDIM_PRINT(("SL[2]: PADRS=0x%x HWEN=%u PLDUNIT=0x%08x%08x\n",
				(kuint32)ioIip.unitinftblSl2.unitinftbl2.bit.padrs,
				(kuint32)ioIip.unitinftblSl2.unitinftbl0.bit.hwen,
				(kuint32)ioIip.unitinftblSl2.unitinftbl1.bit.pldunitHi,
				(kuint32)ioIip.unitinftblSl2.unitinftbl1.bit.pldunitLo));
	im_iip_struct_off_pclk();

	DD_ARM_DMB_POU();

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "Start1\n"));
	ercd = Im_IIP_Start_SWTRG(dstUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "Start2\n"));
	ercd = Im_IIP_Start_SWTRG(filterUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "Start3\n"));
	ercd = Im_IIP_Start_SWTRG(srcUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

#if 0
	for(kuint32 loopcnt = 0; loopcnt < 10; loopcnt++) {
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME " SLALE=%u INTIZ0=0x%lx INTIZ1=0x%lx\n",
					ioIip.IZACTL1.bit.SLALE,
					ioIip.INTIZ0.word,
					ioIip.INTIZ1.word));
		DDIM_User_Dly_Tsk(1);
	}
#endif

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "WaitEnd\n"));
	ercd = Im_IIP_Wait_End(&waitFactorResult, waitFactor, ImIipDefine_D_IM_IIP_OR_WAIT, 30);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult));
	if(ercd != D_DDIM_OK) {
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "Stop\n"));
		ercd = im_iip_main_stop(ImIipDefine_D_IM_IIP_ABORT);
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x factor=0x%x\n", ercd, waitFactorResult));
	}

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#if 0
	// UnitINFダンプ
	Palladium_Set_Out_Localstack((kulong)priv->onedUnitInf, sizeof(Tim1dl));
	Palladium_Set_Out_Localstack((kulong)priv->lutUnitInf, sizeof(TimLut));
	Palladium_Set_Out_Localstack((kulong)priv->slUnitInf, sizeof(TimSts));
#endif


#if 0
	// dump UNITINF ONED[1]
	{
		kuint32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM(srcUnitid, gCtImIIP_Get_Unit_Param, &param_bytes);
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes));
		if(ercd == ImIipDefine_D_IM_IIP_OK) {
			CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "dump UNITINF ONED[1] %u\n", param_bytes));
			CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
		}
	}
#endif


#if 0
	// dump UNITINF LUT
	{
		kuint32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM(filterUnitid, gCtImIIP_Get_Unit_Param, &param_bytes);
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes));
		if(ercd == ImIipDefine_D_IM_IIP_OK) {
			CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "dump UNITINF ONED[1] %u\n", param_bytes));
			CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
		}
	}
#endif


#if 0
	// dump UNITINF SL[2]
	{
		kuint32 param_bytes;
		ercd = Im_IIP_Get_UNIT_PARAM(dstUnitid, gCtImIIP_Get_Unit_Param, &param_bytes);
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = %d bytes = %u\n", ercd, param_bytes));
		if(ercd == ImIipDefine_D_IM_IIP_OK) {
			CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "dump UNITINF SL[2] %u\n", param_bytes));
			CtImIip_ct_im_iip_clean_l1l2_dcache_addr((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
			Palladium_Set_Out_Localstack((kulong)gCtImIIP_Get_Unit_Param, param_bytes);
		}
	}
#endif


#if 0
#ifndef CO_DEBUG_ON_PC
	// dump ioIip
	{
		kulong regdump_addr = D_IM_IIP_REGDUMP_ADDR;
		kulong regdump_bytes = sizeof(ioIip);
		CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "dump ioIip %u\n", regdump_bytes));
		memcpy((void*)regdump_addr, (void*)&ioIip, regdump_bytes);
		Palladium_Set_Out_Localstack(regdump_addr, regdump_bytes);
	}
#endif //!CO_DEBUG_ON_PC
#endif
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END

	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "Im_IIP_Close_SWTRG\n"));
	ercd = Im_IIP_Close_SWTRG(unitidBitmask, pixidBitmask, openResBitmask);
	CtImIipLut_DDIM_PRINT((CtImIipLut_D_IM_IIP_FUNC_NAME "ercd = 0x%x\n", ercd));

	return D_DDIM_OK;
}


// LUT Unit 5-1-X
kint32 ct_im_iip_lut_run_5_1(CtImIipLut *self, const kuint32 ctNo3rd)
{
	CtImIipLutPrivate *priv = CT_IM_IIP_LUT_GET_PRIVATE(self);

	switch(ctNo3rd) {
		// Test-5-1-1
		case 1:
			return ct_im_iip_lut_5_1_1(priv->ciIipLut);

		// Test-5-1-2
		case 2:
			return ct_im_iip_lut_5_1_2(priv->ciIipLut);

		default:
			CtImIipLut_DDIM_PRINT(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

#endif //CO_CT_IM_IIP_DISABLE

CtImIipLut *ct_im_iip_lut_new(void)
{
    CtImIipLut *self = k_object_new_with_private(CT_TYPE_IM_IIP_LUT, sizeof(CtImIipLutPrivate));
    return self;
}
