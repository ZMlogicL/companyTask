/*
 *imdisp2group.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-07
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#include "ctimdisp2.h"
#include "ctimdisp2a.h"
#include "ctimdisp2b.h"
#include "ctimdisp2c.h"
#include "ctimdisp2d.h"
#include "ctimdisp2e.h"
#include "ctimdisp2f.h"
#include "ctimdisp2g.h"
#include "ctimdisp2h.h"
#include "ctimdisp2i.h"
#include "ctimdisp2j.h"
#include "ctimdisp2k.h"
#include "ctimdisp2l.h"
#include "ctimdisp2m.h"
#include "ctimdisp2n.h"
#include "ctimdisp2o.h"

#include "ctimdisp.h"
#include "ctimdisp4.h"

#include "ct_im_disp_define.h"//CO_IO_DISP_DEFINE
#include "ct_im_disptbl_define.h"//DISP_TBL_REVERSE_GTBLB9

#include "im_disp.h"
#include "ctimdisp3.h"
#include "ctimdisp3a.h"
#include "imdisp2group.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImDisp2Group, im_disp2_group, K_TYPE_OBJECT)
#define IM_DISP2_GROUP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp2GroupPrivate, IM_TYPE_DISP2_GROUP))

struct _ImDisp2GroupPrivate
{
	kpointer qwertyu;
	CtImDisp4 *pCtimDisp4;
	T_IM_DISP_CTRL_MAIN_TBL gLcdDispTblMainTbl[CtImDisp4_LCD_DISP_SEL_END];
	T_IM_DISP_CTRL_OUTPUT_TBL gLcdDispTblOutputTbl[CtImDisp4_LCD_DISP_SEL_END];
	T_IM_DISP_CTRL_OUTPUT gLcdDispTblOutctrl[CtImDisp4_LCD_DISP_SEL_END];
	kuchar *pImDispPclkCounter;
	kuchar *pImDispHclkCounter;
	CtImDisp3 *ctImDisp3;
	CtImDisp3a *ctImDisp3a;
};

// Pointer of R data anti gamma table B.<br>
//	Please specify the address of the array of kushort[32].<br>
//	If NULL is specified, this setting is skipped.<br>
static kuint32 S_R_ANTI_TBL_B[32/2] = {
	DISP_TBL_REVERSE_IGTBLR0	,
	DISP_TBL_REVERSE_IGTBLR1	,
	DISP_TBL_REVERSE_IGTBLR2	,
	DISP_TBL_REVERSE_IGTBLR3	,
	DISP_TBL_REVERSE_IGTBLR4	,
	DISP_TBL_REVERSE_IGTBLR5	,
	DISP_TBL_REVERSE_IGTBLR6	,
	DISP_TBL_REVERSE_IGTBLR7	,
	DISP_TBL_REVERSE_IGTBLR8	,
	DISP_TBL_REVERSE_IGTBLR9	,
	DISP_TBL_REVERSE_IGTBLR10	,
	DISP_TBL_REVERSE_IGTBLR11	,
	DISP_TBL_REVERSE_IGTBLR12	,
	DISP_TBL_REVERSE_IGTBLR13	,
	DISP_TBL_REVERSE_IGTBLR14	,
	DISP_TBL_REVERSE_IGTBLR15
};

// Pointer of G data anti gamma table B.<br>
//	Please specify the address of the array of kushort[32].<br>
//	If NULL is specified, this setting is skipped.<br>
static kuint32 S_G_ANTI_TBL_B[32/2] = {
	DISP_TBL_REVERSE_IGTBLG0	,
	DISP_TBL_REVERSE_IGTBLG1	,
	DISP_TBL_REVERSE_IGTBLG2	,
	DISP_TBL_REVERSE_IGTBLG3	,
	DISP_TBL_REVERSE_IGTBLG4	,
	DISP_TBL_REVERSE_IGTBLG5	,
	DISP_TBL_REVERSE_IGTBLG6	,
	DISP_TBL_REVERSE_IGTBLG7	,
	DISP_TBL_REVERSE_IGTBLG8	,
	DISP_TBL_REVERSE_IGTBLG9	,
	DISP_TBL_REVERSE_IGTBLG10	,
	DISP_TBL_REVERSE_IGTBLG11	,
	DISP_TBL_REVERSE_IGTBLG12	,
	DISP_TBL_REVERSE_IGTBLG13	,
	DISP_TBL_REVERSE_IGTBLG14	,
	DISP_TBL_REVERSE_IGTBLG15
};

// Pointer of B data anti gamma table B.<br>
//	Please specify the address of the array of kushort[32].<br>
//	If NULL is specified, this setting is skipped.<br>
static kuint32 S_B_ANTI_TBL_B[32/2] = {
	DISP_TBL_REVERSE_IGTBLB0	,
	DISP_TBL_REVERSE_IGTBLB1	,
	DISP_TBL_REVERSE_IGTBLB2	,
	DISP_TBL_REVERSE_IGTBLB3	,
	DISP_TBL_REVERSE_IGTBLB4	,
	DISP_TBL_REVERSE_IGTBLB5	,
	DISP_TBL_REVERSE_IGTBLB6	,
	DISP_TBL_REVERSE_IGTBLB7	,
	DISP_TBL_REVERSE_IGTBLB8	,
	DISP_TBL_REVERSE_IGTBLB9	,
	DISP_TBL_REVERSE_IGTBLB10	,
	DISP_TBL_REVERSE_IGTBLB11	,
	DISP_TBL_REVERSE_IGTBLB12	,
	DISP_TBL_REVERSE_IGTBLB13	,
	DISP_TBL_REVERSE_IGTBLB14	,
	DISP_TBL_REVERSE_IGTBLB15
};

// Pointer of R data gamma table A.<br>
//	Please specify the address of the array of kushort[32].<br>
//	If NULL is specified, this setting is skipped.<br>
static kuint32 S_R_GAMMA_TBL_A[32/2] = {
	DISP_TBL_REVERSE_GTBLR0		,
	DISP_TBL_REVERSE_GTBLR1		,
	DISP_TBL_REVERSE_GTBLR2		,
	DISP_TBL_REVERSE_GTBLR3		,
	DISP_TBL_REVERSE_GTBLR4		,
	DISP_TBL_REVERSE_GTBLR5		,
	DISP_TBL_REVERSE_GTBLR6		,
	DISP_TBL_REVERSE_GTBLR7		,
	DISP_TBL_REVERSE_GTBLR8		,
	DISP_TBL_REVERSE_GTBLR9		,
	DISP_TBL_REVERSE_GTBLR10	,
	DISP_TBL_REVERSE_GTBLR11	,
	DISP_TBL_REVERSE_GTBLR12	,
	DISP_TBL_REVERSE_GTBLR13	,
	DISP_TBL_REVERSE_GTBLR14	,
	DISP_TBL_REVERSE_GTBLR15
};

// Pointer of G data gamma table A.<br>
//	Please specify the address of the array of kushort[32].<br>
//	If NULL is specified, this setting is skipped.<br>
static kuint32 S_G_GAMMA_TBL_A[32/2] = {
	DISP_TBL_REVERSE_GTBLG0		,
	DISP_TBL_REVERSE_GTBLG1		,
	DISP_TBL_REVERSE_GTBLG2		,
	DISP_TBL_REVERSE_GTBLG3		,
	DISP_TBL_REVERSE_GTBLG4		,
	DISP_TBL_REVERSE_GTBLG5		,
	DISP_TBL_REVERSE_GTBLG6		,
	DISP_TBL_REVERSE_GTBLG7		,
	DISP_TBL_REVERSE_GTBLG8		,
	DISP_TBL_REVERSE_GTBLG9		,
	DISP_TBL_REVERSE_GTBLG10	,
	DISP_TBL_REVERSE_GTBLG11	,
	DISP_TBL_REVERSE_GTBLG12	,
	DISP_TBL_REVERSE_GTBLG13	,
	DISP_TBL_REVERSE_GTBLG14	,
	DISP_TBL_REVERSE_GTBLG15
};

// Pointer of B data gamma table A.<br>
//	Please specify the address of the array of kushort[32].<br>
//	If NULL is specified, this setting is skipped.<br>
static kuint32 S_B_GAMMA_TBL_A[32/2] = {
	DISP_TBL_REVERSE_GTBLB0		,
	DISP_TBL_REVERSE_GTBLB1		,
	DISP_TBL_REVERSE_GTBLB2		,
	DISP_TBL_REVERSE_GTBLB3		,
	DISP_TBL_REVERSE_GTBLB4		,
	DISP_TBL_REVERSE_GTBLB5		,
	DISP_TBL_REVERSE_GTBLB6		,
	DISP_TBL_REVERSE_GTBLB7		,
	DISP_TBL_REVERSE_GTBLB8		,
	DISP_TBL_REVERSE_GTBLB9		,
	DISP_TBL_REVERSE_GTBLB10	,
	DISP_TBL_REVERSE_GTBLB11	,
	DISP_TBL_REVERSE_GTBLB12	,
	DISP_TBL_REVERSE_GTBLB13	,
	DISP_TBL_REVERSE_GTBLB14	,
	DISP_TBL_REVERSE_GTBLB15
};

// Pointer of R data anti gamma table B.<br>
//	Please specify the address of the array of kushort[32].<br>
//	If NULL is specified, this setting is skipped.<br>
static kuint32 S_R_GAMMA_TBL_B[32/2] = {
	DISP_TBL_REVERSE_IGTBLR0	,
	DISP_TBL_REVERSE_IGTBLR1	,
	DISP_TBL_REVERSE_IGTBLR2	,
	DISP_TBL_REVERSE_IGTBLR3	,
	DISP_TBL_REVERSE_IGTBLR4	,
	DISP_TBL_REVERSE_IGTBLR5	,
	DISP_TBL_REVERSE_IGTBLR6	,
	DISP_TBL_REVERSE_IGTBLR7	,
	DISP_TBL_REVERSE_IGTBLR8	,
	DISP_TBL_REVERSE_IGTBLR9	,
	DISP_TBL_REVERSE_IGTBLR10,
	DISP_TBL_REVERSE_IGTBLR11,
	DISP_TBL_REVERSE_IGTBLR12,
	DISP_TBL_REVERSE_IGTBLR13,
	DISP_TBL_REVERSE_IGTBLR14,
	DISP_TBL_REVERSE_IGTBLR15
};

// Pointer of G data anti gamma table B.<br>
//	Please specify the address of the array of kushort[32].<br>
//	If NULL is specified, this setting is skipped.<br>
static kuint32 S_G_GAMMA_TBL_B[32/2] = {
	DISP_TBL_REVERSE_IGTBLG0	,
	DISP_TBL_REVERSE_IGTBLG1	,
	DISP_TBL_REVERSE_IGTBLG2	,
	DISP_TBL_REVERSE_IGTBLG3	,
	DISP_TBL_REVERSE_IGTBLG4	,
	DISP_TBL_REVERSE_IGTBLG5	,
	DISP_TBL_REVERSE_IGTBLG6	,
	DISP_TBL_REVERSE_IGTBLG7	,
	DISP_TBL_REVERSE_IGTBLG8	,
	DISP_TBL_REVERSE_IGTBLG9	,
	DISP_TBL_REVERSE_IGTBLG10,
	DISP_TBL_REVERSE_IGTBLG11,
	DISP_TBL_REVERSE_IGTBLG12,
	DISP_TBL_REVERSE_IGTBLG13,
	DISP_TBL_REVERSE_IGTBLG14,
	DISP_TBL_REVERSE_IGTBLG15
};

// Pointer of B data anti gamma table B.<br>
//	Please specify the address of the array of kushort[32].<br>
//	If NULL is specified, this setting is skipped.<br>
static kuint32 S_B_GAMMA_TBL_B[32/2] = {
	DISP_TBL_REVERSE_IGTBLB0	,
	DISP_TBL_REVERSE_IGTBLB1	,
	DISP_TBL_REVERSE_IGTBLB2	,
	DISP_TBL_REVERSE_IGTBLB3	,
	DISP_TBL_REVERSE_IGTBLB4	,
	DISP_TBL_REVERSE_IGTBLB5	,
	DISP_TBL_REVERSE_IGTBLB6	,
	DISP_TBL_REVERSE_IGTBLB7	,
	DISP_TBL_REVERSE_IGTBLB8	,
	DISP_TBL_REVERSE_IGTBLB9	,
	DISP_TBL_REVERSE_IGTBLB10	,
	DISP_TBL_REVERSE_IGTBLB11	,
	DISP_TBL_REVERSE_IGTBLB12	,
	DISP_TBL_REVERSE_IGTBLB13	,
	DISP_TBL_REVERSE_IGTBLB14	,
	DISP_TBL_REVERSE_IGTBLB15
};

/*
 * DECLS
 * */
static void initLcdDispTblMain(ImDisp2Group *self);
static void initLcdDispTblOutctrl(ImDisp2Group *self);

/*
 * IMPL
 * */
static void im_disp2_group_constructor(ImDisp2Group *self)
{
	ImDisp2GroupPrivate *priv = IM_DISP2_GROUP_GET_PRIVATE(self);
	CtImDisp4 *ctImDisp4 = ct_im_disp4_new();
	kint loopIndex = 0;
	priv->pCtimDisp4 = ctImDisp4;
	self->privImDisp2Group = priv;

	initLcdDispTblMain(self);//gLcdDispTblMainTbl
	initLcdDispTblOutctrl(self);//gLcdDispTblOutctrl

	for (loopIndex = 0; loopIndex < CtImDisp4_LCD_DISP_SEL_END; loopIndex++)
	{
		priv->gLcdDispTblOutputTbl[loopIndex].gamma_a.r_data =
				(kushort*) ct_im_disp4_get_r_gamma_out_tbla(ctImDisp4);
		priv->gLcdDispTblOutputTbl[loopIndex].gamma_a.g_data =
				(kushort*) ct_im_disp4_get_g_gamma_out_tbla(ctImDisp4);
		priv->gLcdDispTblOutputTbl[loopIndex].gamma_a.b_data =
				(kushort*) ct_im_disp4_get_b_gamma_out_tbla(ctImDisp4);
		priv->gLcdDispTblOutputTbl[loopIndex].gamma_b.r_data =
				(kushort*) ct_im_disp4_get_r_gamma_out_tblb(ctImDisp4);
		priv->gLcdDispTblOutputTbl[loopIndex].gamma_b.g_data =
				(kushort*) ct_im_disp4_get_g_gamma_out_tblb(ctImDisp4);
		priv->gLcdDispTblOutputTbl[loopIndex].gamma_b.b_data =
				(kushort*) ct_im_disp4_get_b_gamma_out_tblb(ctImDisp4);
		priv->gLcdDispTblOutputTbl[loopIndex].luminance_a =
				(kushort*) ct_im_disp4_get_luminance_tbla(ctImDisp4);
		priv->gLcdDispTblOutputTbl[loopIndex].chroma_a =
				(kushort*) ct_im_disp4_get_gain_tbla(ctImDisp4);
		priv->gLcdDispTblOutputTbl[loopIndex].luminance_b =
				(kushort*) ct_im_disp4_get_luminance_tblb(ctImDisp4);
		priv->gLcdDispTblOutputTbl[loopIndex].chroma_b =
				(kushort*) ct_im_disp4_get_gain_tblb(ctImDisp4);
	}
}

static void im_disp2_group_destructor(ImDisp2Group *self)
{
}

static void initLcdDispTblMain(ImDisp2Group *self)
{
	ImDisp2GroupPrivate *priv = self->privImDisp2Group;
	CtImDisp4 *ctImDisp4 = priv->pCtimDisp4;

	T_IM_DISP_CTRL_MAIN_TBL tblMainTbl[CtImDisp4_LCD_DISP_SEL_END] = {
		{
			{
				(kushort*)ct_im_disp4_get_r_anti_tbla(ctImDisp4),
				(kushort*)ct_im_disp4_get_g_anti_tbla(ctImDisp4),
				(kushort*)ct_im_disp4_get_b_anti_tbla(ctImDisp4)
			},
			{
				(kushort*)S_R_ANTI_TBL_B,
				(kushort*)S_G_ANTI_TBL_B,
				(kushort*)S_B_ANTI_TBL_B
			},
			{
				(kushort*)S_R_GAMMA_TBL_A,
				(kushort*)S_G_GAMMA_TBL_A,
				(kushort*)S_B_GAMMA_TBL_A
			},
			{
				(kushort*)S_R_GAMMA_TBL_B,
				(kushort*)S_G_GAMMA_TBL_B,
				(kushort*)S_B_GAMMA_TBL_B
			},
		},
		{
			{
				(kushort*)ct_im_disp4_get_r_anti_tbla(ctImDisp4),
				(kushort*)ct_im_disp4_get_g_anti_tbla(ctImDisp4),
				(kushort*)ct_im_disp4_get_b_anti_tbla(ctImDisp4)
			},
			{
				(kushort*)S_R_ANTI_TBL_B,
				(kushort*)S_G_ANTI_TBL_B,
				(kushort*)S_B_ANTI_TBL_B
			},
			{
				(kushort*)S_R_GAMMA_TBL_A,
				(kushort*)S_G_GAMMA_TBL_A,
				(kushort*)S_B_GAMMA_TBL_A
			},
			{
				(kushort*)S_R_GAMMA_TBL_B,
				(kushort*)S_G_GAMMA_TBL_B,
				(kushort*)S_B_GAMMA_TBL_B
			},
		}
	};
	memcpy(priv->gLcdDispTblMainTbl, tblMainTbl, sizeof(tblMainTbl));
}

static void initLcdDispTblOutctrl(ImDisp2Group *self)
{
	ImDisp2GroupPrivate *priv = self->privImDisp2Group;
	T_IM_DISP_CTRL_OUTPUT tblOutctrl[CtImDisp4_LCD_DISP_SEL_END] = {
		{
			(ULONG)DISP_HDMI_DATA_INTC,			// intc
			{ (ULONG)DISP_HDMI_DATA_INTE },		// inte
			(ULONG)DISP_HDMI_DATA_HABLK,		// hablk
			(ULONG)DISP_HDMI_DATA_FDOEN,		// fdoen
			{ (ULONG)DISP_HDMI_DATA_FODATA },	// fodata
			{									// blankdt
				{
					(kulong)DISP_HDMI_DATA_BLANKDT0,
					(kulong)DISP_HDMI_DATA_BLANKDT1
				}
			},
			DISP_HDMI_DATA_CLBHSIZE,			// clbhsize

			{									// clbdt[16]
				{ DISP_HDMI_DATA_CLBDT0 },
				{ DISP_HDMI_DATA_CLBDT1 },
				{ DISP_HDMI_DATA_CLBDT2 },
				{ DISP_HDMI_DATA_CLBDT3 },
				{ DISP_HDMI_DATA_CLBDT4 },
				{ DISP_HDMI_DATA_CLBDT5 },
				{ DISP_HDMI_DATA_CLBDT6 },
				{ DISP_HDMI_DATA_CLBDT7 },
				{ DISP_HDMI_DATA_CLBDT8 },
				{ DISP_HDMI_DATA_CLBDT9 },
				{ DISP_HDMI_DATA_CLBDT10 },
				{ DISP_HDMI_DATA_CLBDT11 },
				{ DISP_HDMI_DATA_CLBDT12 },
				{ DISP_HDMI_DATA_CLBDT13 },
				{ DISP_HDMI_DATA_CLBDT14 },
				{ DISP_HDMI_DATA_CLBDT15 }
			},
			{ DISP_HDMI_DATA_BLDCTL },				// bldctl
			{										// r2y[3]
				{ DISP_HDMI_DATA_R2Y0 },
				{ DISP_HDMI_DATA_R2Y1 },
				{ DISP_HDMI_DATA_R2Y2 }
			},
			{										// clipCal
				{ (ULONG)DISP_HDMI_DATA_YCAL,		(ULONG)DISP_HDMI_DATA_YCAL },		// y_cal
				{ (kushort)DISP_HDMI_DATA_YCLIP,		(kushort)DISP_HDMI_DATA_YCLIP },		// y_clip
				{ (SHORT)DISP_HDMI_DATA_CBCAL,		(SHORT)DISP_HDMI_DATA_CBCAL },		// cb_cal
				{ (kushort)DISP_HDMI_DATA_CBCLIP,	(kushort)DISP_HDMI_DATA_CBCLIP },	// cb_clip
				{ (SHORT)DISP_HDMI_DATA_CRCAL,		(SHORT)DISP_HDMI_DATA_CRCAL },		// cr_cal
				{ (kushort)DISP_HDMI_DATA_CRCLIP,	(kushort)DISP_HDMI_DATA_CRCLIP }		// cr_clip
			},
			{ (ULONG)DISP_HDMI_DATA_DOCTL0 },			// doctl0
			{ (ULONG)DISP_HDMI_DATA_DOCTL1 },			// doctl1
			{ (ULONG)DISP_HDMI_DATA_DOCTL2 },			// doctl2
			{											// trscode[2]
				{ (ULONG)DISP_HDMI_DATA_TRSCODE0 },
				{ (ULONG)DISP_HDMI_DATA_TRSCODE1 }
			},
			{											// y2r[3]
				{ (LLONG)DISP_HDMI_LY2R0_0 }, 			// [0]
				{ (LLONG)DISP_HDMI_LY2R1_0 },			// [1]
				{ (LLONG)DISP_HDMI_LY2R2_0 }			// [2]
			},
			(E_IM_DISP_CORRECT_PROC)DISP_HDMI_GMEN,		// tblaset_gmen
			(BYTE)DISP_HDMI_GMTSL,									// tblaset_gmtsl
			(E_IM_DISP_CORRECT_PROC)DISP_HDMI_YSATEN,	// tblaset_ysaten
			(BYTE)DISP_HDMI_YSATSL,						// tblaset_ysatsl
			{											// face
				{										// param[42]
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA0 },  { (ULONG)DISP_HDMI_DATA_FFSIZE0 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH0 },  { (ULONG)DISP_HDMI_DATA_FFCLR0 },  },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA1 },  { (ULONG)DISP_HDMI_DATA_FFSIZE1 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH1 },  { (ULONG)DISP_HDMI_DATA_FFCLR1 },  },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA2 },  { (ULONG)DISP_HDMI_DATA_FFSIZE2 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH2 },  { (ULONG)DISP_HDMI_DATA_FFCLR2 },  },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA3 },  { (ULONG)DISP_HDMI_DATA_FFSIZE3 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH3 },  { (ULONG)DISP_HDMI_DATA_FFCLR3 },  },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA4 },  { (ULONG)DISP_HDMI_DATA_FFSIZE4 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH4 },  { (ULONG)DISP_HDMI_DATA_FFCLR4 },  },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA5 },  { (ULONG)DISP_HDMI_DATA_FFSIZE5 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH5 },  { (ULONG)DISP_HDMI_DATA_FFCLR5 },  },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA6 },  { (ULONG)DISP_HDMI_DATA_FFSIZE6 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH6 },  { (ULONG)DISP_HDMI_DATA_FFCLR6 },  },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA7 },  { (ULONG)DISP_HDMI_DATA_FFSIZE7 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH7 },  { (ULONG)DISP_HDMI_DATA_FFCLR7 },  },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA8 },  { (ULONG)DISP_HDMI_DATA_FFSIZE8 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH8 },  { (ULONG)DISP_HDMI_DATA_FFCLR8 },  },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA9 },  { (ULONG)DISP_HDMI_DATA_FFSIZE9 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH9 },  { (ULONG)DISP_HDMI_DATA_FFCLR9 },  },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA10 }, { (ULONG)DISP_HDMI_DATA_FFSIZE10 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH10 }, { (ULONG)DISP_HDMI_DATA_FFCLR10 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA11 }, { (ULONG)DISP_HDMI_DATA_FFSIZE11 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH11 }, { (ULONG)DISP_HDMI_DATA_FFCLR11 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA12 }, { (ULONG)DISP_HDMI_DATA_FFSIZE12 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH12 }, { (ULONG)DISP_HDMI_DATA_FFCLR12 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA13 }, { (ULONG)DISP_HDMI_DATA_FFSIZE13 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH13 }, { (ULONG)DISP_HDMI_DATA_FFCLR13 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA14 }, { (ULONG)DISP_HDMI_DATA_FFSIZE14 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH14 }, { (ULONG)DISP_HDMI_DATA_FFCLR14 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA15 }, { (ULONG)DISP_HDMI_DATA_FFSIZE15 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH15 }, { (ULONG)DISP_HDMI_DATA_FFCLR15 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA16 }, { (ULONG)DISP_HDMI_DATA_FFSIZE16 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH16 }, { (ULONG)DISP_HDMI_DATA_FFCLR16 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA17 }, { (ULONG)DISP_HDMI_DATA_FFSIZE17 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH17 }, { (ULONG)DISP_HDMI_DATA_FFCLR17 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA18 }, { (ULONG)DISP_HDMI_DATA_FFSIZE18 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH18 }, { (ULONG)DISP_HDMI_DATA_FFCLR18 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA19 }, { (ULONG)DISP_HDMI_DATA_FFSIZE19 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH19 }, { (ULONG)DISP_HDMI_DATA_FFCLR19 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA20 }, { (ULONG)DISP_HDMI_DATA_FFSIZE20 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH20 }, { (ULONG)DISP_HDMI_DATA_FFCLR20 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA21 }, { (ULONG)DISP_HDMI_DATA_FFSIZE21 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH21 }, { (ULONG)DISP_HDMI_DATA_FFCLR21 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA22 }, { (ULONG)DISP_HDMI_DATA_FFSIZE22 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH22 }, { (ULONG)DISP_HDMI_DATA_FFCLR22 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA23 }, { (ULONG)DISP_HDMI_DATA_FFSIZE23 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH23 }, { (ULONG)DISP_HDMI_DATA_FFCLR23 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA24 }, { (ULONG)DISP_HDMI_DATA_FFSIZE24 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH24 }, { (ULONG)DISP_HDMI_DATA_FFCLR24 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA25 }, { (ULONG)DISP_HDMI_DATA_FFSIZE25 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH25 }, { (ULONG)DISP_HDMI_DATA_FFCLR25 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA26 }, { (ULONG)DISP_HDMI_DATA_FFSIZE26 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH26 }, { (ULONG)DISP_HDMI_DATA_FFCLR26 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA27 }, { (ULONG)DISP_HDMI_DATA_FFSIZE27 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH27 }, { (ULONG)DISP_HDMI_DATA_FFCLR27 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA28 }, { (ULONG)DISP_HDMI_DATA_FFSIZE28 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH28 }, { (ULONG)DISP_HDMI_DATA_FFCLR28 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA29 }, { (ULONG)DISP_HDMI_DATA_FFSIZE29 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH29 }, { (ULONG)DISP_HDMI_DATA_FFCLR29 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA30 }, { (ULONG)DISP_HDMI_DATA_FFSIZE30 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH30 }, { (ULONG)DISP_HDMI_DATA_FFCLR30 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA31 }, { (ULONG)DISP_HDMI_DATA_FFSIZE31 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH31 }, { (ULONG)DISP_HDMI_DATA_FFCLR31 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA32 }, { (ULONG)DISP_HDMI_DATA_FFSIZE32 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH32 }, { (ULONG)DISP_HDMI_DATA_FFCLR32 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA33 }, { (ULONG)DISP_HDMI_DATA_FFSIZE33 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH33 }, { (ULONG)DISP_HDMI_DATA_FFCLR33 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA34 }, { (ULONG)DISP_HDMI_DATA_FFSIZE34 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH34 }, { (ULONG)DISP_HDMI_DATA_FFCLR34 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA35 }, { (ULONG)DISP_HDMI_DATA_FFSIZE35 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH35 }, { (ULONG)DISP_HDMI_DATA_FFCLR35 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA36 }, { (ULONG)DISP_HDMI_DATA_FFSIZE36 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH36 }, { (ULONG)DISP_HDMI_DATA_FFCLR36 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA37 }, { (ULONG)DISP_HDMI_DATA_FFSIZE37 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH37 }, { (ULONG)DISP_HDMI_DATA_FFCLR37 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA38 }, { (ULONG)DISP_HDMI_DATA_FFSIZE38 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH38 }, { (ULONG)DISP_HDMI_DATA_FFCLR38 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA39 }, { (ULONG)DISP_HDMI_DATA_FFSIZE39 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH39 }, { (ULONG)DISP_HDMI_DATA_FFCLR39 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA40 }, { (ULONG)DISP_HDMI_DATA_FFSIZE40 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH40 }, { (ULONG)DISP_HDMI_DATA_FFCLR40 }, },
					{ { (ULONG)DISP_HDMI_DATA_FFDSTA41 }, { (ULONG)DISP_HDMI_DATA_FFSIZE41 },
							{ (ULONG)DISP_HDMI_DATA_FFWIDTH41 }, { (ULONG)DISP_HDMI_DATA_FFCLR41 }, }
				},
				(unsigned long long)DISP_HDMI_DATA_FFDISPEN,	// ffden
				(BYTE)DISP_HDMI_DATA_FFDO						// msff
			},
			{													// int_callback[12]
				ct_im_disp3_int_00_cb,
				ct_im_disp3_int_01_cb,
				ct_im_disp3_int_02_cb,
				ct_im_disp3_int_03_cb,
				ct_im_disp3_int_04_cb,
				ct_im_disp3_int_05_cb,
				ct_im_disp3_int_06_cb,
				ct_im_disp3_int_07_cb,
				ct_im_disp3_int_08_cb,
				ct_im_disp3_int_09_cb,
				ct_im_disp3_int_10_cb,
				ct_im_disp3_int_11_cb
			}
		},
		{
			DISP_LCD_DATA_INTC,						// intc
			{ DISP_LCD_DATA_INTE },					// inte
			(ULONG)DISP_LCD_DATA_HABLK,				// hablk
			(ULONG)DISP_LCD_DATA_FDOEN,				// fdoen
			{ (ULONG)DISP_LCD_DATA_FODATA },		// fodata
			{										// blankdt
				{
					(kulong)DISP_LCD_DATA_BLANKDT0,
					(kulong)DISP_LCD_DATA_BLANKDT1
				}
			},
			DISP_LCD_DATA_CLBHSIZE,					// clbhsize

			{										// clbdt[16]
				{ DISP_LCD_DATA_CLBDT0 },
				{ DISP_LCD_DATA_CLBDT1 },
				{ DISP_LCD_DATA_CLBDT2 },
				{ DISP_LCD_DATA_CLBDT3 },
				{ DISP_LCD_DATA_CLBDT4 },
				{ DISP_LCD_DATA_CLBDT5 },
				{ DISP_LCD_DATA_CLBDT6 },
				{ DISP_LCD_DATA_CLBDT7 },
				{ DISP_LCD_DATA_CLBDT8 },
				{ DISP_LCD_DATA_CLBDT9 },
				{ DISP_LCD_DATA_CLBDT10 },
				{ DISP_LCD_DATA_CLBDT11 },
				{ DISP_LCD_DATA_CLBDT12 },
				{ DISP_LCD_DATA_CLBDT13 },
				{ DISP_LCD_DATA_CLBDT14 },
				{ DISP_LCD_DATA_CLBDT15 }
			},
			{ DISP_LCD_DATA_BLDCTL },				// bldctl
			{										// r2y[3]
				{ DISP_LCD_DATA_R2Y0 },
				{ DISP_LCD_DATA_R2Y1 },
				{ DISP_LCD_DATA_R2Y2 }
			},
			{										// clipCal
				{ (ULONG)DISP_LCD_DATA_YCAL,	(ULONG)DISP_LCD_DATA_YCAL },
				{ (ULONG)DISP_LCD_DATA_YCLIP,	(ULONG)DISP_LCD_DATA_YCLIP },
				{ (ULONG)DISP_LCD_DATA_CBCAL,	(ULONG)DISP_LCD_DATA_CBCAL },
				{ (ULONG)DISP_LCD_DATA_CBCLIP,	(ULONG)DISP_LCD_DATA_CBCLIP },
				{ (ULONG)DISP_LCD_DATA_CRCAL,	(ULONG)DISP_LCD_DATA_CRCAL },
				{ (ULONG)DISP_LCD_DATA_CRCLIP,	(ULONG)DISP_LCD_DATA_CRCLIP }
			},
			{ (ULONG)DISP_LCD_DATA_DOCTL0 },		// doctl0
			{ (ULONG)DISP_LCD_DATA_DOCTL1 },		// doctl1
			{ (ULONG)DISP_LCD_DATA_DOCTL2 },		// doctl2
			{										// trscode[2]
				{ (ULONG)DISP_LCD_DATA_TRSCODE0 },
				{ (ULONG)DISP_LCD_DATA_TRSCODE1 }
			},
			{										// y2r[3]
				{ (LLONG)DISP_LCD_LY2R0_0 }, 		// [0]
				{ (LLONG)DISP_LCD_LY2R1_0 },		// [1]
				{ (LLONG)DISP_LCD_LY2R2_0 }			// [2]
			},
			(E_IM_DISP_CORRECT_PROC)DISP_LCD_GMEN,		// tblaset_gmen
			(BYTE)DISP_LCD_GMTSL,						// tblaset_gmtsl
			(E_IM_DISP_CORRECT_PROC)DISP_LCD_YSATEN,	// tblaset_ysaten
			(BYTE)DISP_LCD_YSATSL,						// tblaset_ysatsl
			{										// face
				{									// param[42]
					{ { (ULONG)DISP_LCD_DATA_FFDSTA0 },  { (ULONG)DISP_LCD_DATA_FFSIZE0 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH0 },   { (ULONG)DISP_LCD_DATA_FFCLR0 }  },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA1 },  { (ULONG)DISP_LCD_DATA_FFSIZE1 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH1 },   { (ULONG)DISP_LCD_DATA_FFCLR1 }  },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA2 },  { (ULONG)DISP_LCD_DATA_FFSIZE2 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH2 },   { (ULONG)DISP_LCD_DATA_FFCLR2 }  },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA3 },  { (ULONG)DISP_LCD_DATA_FFSIZE3 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH3 },   { (ULONG)DISP_LCD_DATA_FFCLR3 }  },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA4 },  { (ULONG)DISP_LCD_DATA_FFSIZE4 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH4 },   { (ULONG)DISP_LCD_DATA_FFCLR4 }  },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA5 },  { (ULONG)DISP_LCD_DATA_FFSIZE5 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH5 },   { (ULONG)DISP_LCD_DATA_FFCLR5 }  },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA6 },  { (ULONG)DISP_LCD_DATA_FFSIZE6 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH6 },   { (ULONG)DISP_LCD_DATA_FFCLR6 }  },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA7 },  { (ULONG)DISP_LCD_DATA_FFSIZE7 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH7 },   { (ULONG)DISP_LCD_DATA_FFCLR7 }  },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA8 },  { (ULONG)DISP_LCD_DATA_FFSIZE8 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH8 },   { (ULONG)DISP_LCD_DATA_FFCLR8 }  },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA9 },  { (ULONG)DISP_LCD_DATA_FFSIZE9 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH9 },   { (ULONG)DISP_LCD_DATA_FFCLR9 }  },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA10 }, { (ULONG)DISP_LCD_DATA_FFSIZE10 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH10 },  { (ULONG)DISP_LCD_DATA_FFCLR10 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA11 }, { (ULONG)DISP_LCD_DATA_FFSIZE11 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH11 },  { (ULONG)DISP_LCD_DATA_FFCLR11 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA12 }, { (ULONG)DISP_LCD_DATA_FFSIZE12 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH12 },  { (ULONG)DISP_LCD_DATA_FFCLR12 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA13 }, { (ULONG)DISP_LCD_DATA_FFSIZE13 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH13 },  { (ULONG)DISP_LCD_DATA_FFCLR13 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA14 }, { (ULONG)DISP_LCD_DATA_FFSIZE14 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH14 },  { (ULONG)DISP_LCD_DATA_FFCLR14 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA15 }, { (ULONG)DISP_LCD_DATA_FFSIZE15 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH15 },  { (ULONG)DISP_LCD_DATA_FFCLR15 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA16 }, { (ULONG)DISP_LCD_DATA_FFSIZE16 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH16 },  { (ULONG)DISP_LCD_DATA_FFCLR16 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA17 }, { (ULONG)DISP_LCD_DATA_FFSIZE17 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH17 },  { (ULONG)DISP_LCD_DATA_FFCLR17 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA18 }, { (ULONG)DISP_LCD_DATA_FFSIZE18 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH18 },  { (ULONG)DISP_LCD_DATA_FFCLR18 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA19 }, { (ULONG)DISP_LCD_DATA_FFSIZE19 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH19 },  { (ULONG)DISP_LCD_DATA_FFCLR19 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA20 }, { (ULONG)DISP_LCD_DATA_FFSIZE20 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH20 },  { (ULONG)DISP_LCD_DATA_FFCLR20 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA21 }, { (ULONG)DISP_LCD_DATA_FFSIZE21 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH21 },  { (ULONG)DISP_LCD_DATA_FFCLR21 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA22 }, { (ULONG)DISP_LCD_DATA_FFSIZE22 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH22 },  { (ULONG)DISP_LCD_DATA_FFCLR22 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA23 }, { (ULONG)DISP_LCD_DATA_FFSIZE23 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH23 },  { (ULONG)DISP_LCD_DATA_FFCLR23 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA24 }, { (ULONG)DISP_LCD_DATA_FFSIZE24 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH24 },  { (ULONG)DISP_LCD_DATA_FFCLR24 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA25 }, { (ULONG)DISP_LCD_DATA_FFSIZE25 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH25 },  { (ULONG)DISP_LCD_DATA_FFCLR25 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA26 }, { (ULONG)DISP_LCD_DATA_FFSIZE26 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH26 },  { (ULONG)DISP_LCD_DATA_FFCLR26 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA27 }, { (ULONG)DISP_LCD_DATA_FFSIZE27 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH27 },  { (ULONG)DISP_LCD_DATA_FFCLR27 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA28 }, { (ULONG)DISP_LCD_DATA_FFSIZE28 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH28 },  { (ULONG)DISP_LCD_DATA_FFCLR28 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA29 }, { (ULONG)DISP_LCD_DATA_FFSIZE29 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH29 },  { (ULONG)DISP_LCD_DATA_FFCLR29 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA30 }, { (ULONG)DISP_LCD_DATA_FFSIZE30 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH30 },  { (ULONG)DISP_LCD_DATA_FFCLR30 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA31 }, { (ULONG)DISP_LCD_DATA_FFSIZE31 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH31 },  { (ULONG)DISP_LCD_DATA_FFCLR31 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA32 }, { (ULONG)DISP_LCD_DATA_FFSIZE32 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH32 },  { (ULONG)DISP_LCD_DATA_FFCLR32 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA33 }, { (ULONG)DISP_LCD_DATA_FFSIZE33 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH33 },  { (ULONG)DISP_LCD_DATA_FFCLR33 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA34 }, { (ULONG)DISP_LCD_DATA_FFSIZE34 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH34 },  { (ULONG)DISP_LCD_DATA_FFCLR34 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA35 }, { (ULONG)DISP_LCD_DATA_FFSIZE35 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH35 },  { (ULONG)DISP_LCD_DATA_FFCLR35 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA36 }, { (ULONG)DISP_LCD_DATA_FFSIZE36 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH36 },  { (ULONG)DISP_LCD_DATA_FFCLR36 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA37 }, { (ULONG)DISP_LCD_DATA_FFSIZE37 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH37 },  { (ULONG)DISP_LCD_DATA_FFCLR37 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA38 }, { (ULONG)DISP_LCD_DATA_FFSIZE38 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH38 },  { (ULONG)DISP_LCD_DATA_FFCLR38 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA39 }, { (ULONG)DISP_LCD_DATA_FFSIZE39 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH39 },  { (ULONG)DISP_LCD_DATA_FFCLR39 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA40 }, { (ULONG)DISP_LCD_DATA_FFSIZE40 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH40 },  { (ULONG)DISP_LCD_DATA_FFCLR40 } },
					{ { (ULONG)DISP_LCD_DATA_FFDSTA41 }, { (ULONG)DISP_LCD_DATA_FFSIZE41 },
							{ (ULONG)DISP_LCD_DATA_FFWIDTH41 },  { (ULONG)DISP_LCD_DATA_FFCLR41 } }
				},
				(unsigned long long)DISP_LCD_DATA_FFDISPEN,	// ffden
				(BYTE)DISP_LCD_DATA_FFDO,					// msff
			},
			{												// int_callback[12]
				ct_im_disp3_int_00_cb,
				ct_im_disp3_int_01_cb,
				ct_im_disp3_int_02_cb,
				ct_im_disp3_int_03_cb,
				ct_im_disp3_int_04_cb,
				ct_im_disp3_int_05_cb,
				ct_im_disp3_int_06_cb,
				ct_im_disp3_int_07_cb,
				ct_im_disp3_int_08_cb,
				ct_im_disp3_int_09_cb,
				ct_im_disp3_int_10_cb,
				ct_im_disp3_int_11_cb
			}
		}
	};

	memcpy(priv->gLcdDispTblOutctrl, tblOutctrl, sizeof(tblOutctrl));
}

/*
 * PUBLIC
 * */
ImDisp2Parent *im_disp2_group_create_im_disp(ImDisp2Group *self,
		ImDisp2GroupDoMainType mainType, KData data)
{
	ImDisp2Parent *imDisp2Parent = NULL;
//	CtImDisp *ctImDisp = (CtImDisp *)data;

	switch(mainType)
	{
		case ImDisp2Group_DO_IM_DISP_TEST:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2_new();
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_A:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2a_new();
//			ct_im_disp2a_set_group((CtImDisp2a *)imDisp2Parent, (KObject *)self);//im_disp2_parent_set_group
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_B:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2b_new((Disp2bNewParams *)data);
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_C:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2c_new();
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_D:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2d_new();
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_E:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2e_new();
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_F:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2f_new();
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_G:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2g_new();
			break;

		case ImDisp2Group_DO_IM_DISP_TEST_H:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2h_new();
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_I:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2i_new();
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_J:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2j_new();
			break;

		case ImDisp2Group_DO_IM_DISP_TEST_K:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2k_new();
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_L:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2l_new();
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_M:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2m_new();
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_N:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2n_new();
			break;
		case ImDisp2Group_DO_IM_DISP_TEST_O:
			imDisp2Parent = (ImDisp2Parent *)ct_im_disp2o_new();
			break;
		default:
			break;
	}

	if(imDisp2Parent)
	{
		im_disp2_parent_set_group(imDisp2Parent, (KObject *)self);
	}
	return imDisp2Parent;
}

KObject *im_disp2_group_get_disp4(ImDisp2Group *self)
{
	ImDisp2GroupPrivate *priv = self->privImDisp2Group;
	return (KObject *)priv->pCtimDisp4;
}

T_IM_DISP_CTRL_MAIN_TBL *im_disp2_group_get_main_tbl(ImDisp2Group *self)
{
	ImDisp2GroupPrivate *priv = self->privImDisp2Group;
	return priv->gLcdDispTblMainTbl;
}

T_IM_DISP_CTRL_OUTPUT_TBL *im_disp2_group_get_output_tbl(ImDisp2Group *self)
{
	ImDisp2GroupPrivate *priv = self->privImDisp2Group;
	return priv->gLcdDispTblOutputTbl;
}

T_IM_DISP_CTRL_OUTPUT *im_disp2_group_get_output_ctl(ImDisp2Group *self)
{
	ImDisp2GroupPrivate *priv = self->privImDisp2Group;
	return priv->gLcdDispTblOutctrl;
}

kuchar *im_disp2_group_get_pclk_counter(ImDisp2Group *self)
{
	if (IM_IS_DISP2_GROUP(self))
	{
		ImDisp2GroupPrivate *priv = self->privImDisp2Group;
		return priv->pImDispPclkCounter;
	}
	return NULL;
}

kuchar *im_disp2_group_get_hclk_counter(ImDisp2Group *self)
{
	if (IM_IS_DISP2_GROUP(self))
	{
		ImDisp2GroupPrivate *priv = self->privImDisp2Group;
		return priv->pImDispHclkCounter;
	}
	return NULL;
}

void im_disp2_group_set_disp3(ImDisp2Group *self, KObject *obj3)
{
	if (IM_IS_DISP2_GROUP(self))
	{
		ImDisp2GroupPrivate *priv = self->privImDisp2Group;
		priv->ctImDisp3 = (CtImDisp3 *)k_object_ref(obj3);
	}
}

KObject * im_disp2_group_get_disp3(ImDisp2Group *self)
{
	if (IM_IS_DISP2_GROUP(self))
	{
		ImDisp2GroupPrivate *priv = self->privImDisp2Group;
		return (KObject *)priv->ctImDisp3;
	}
	return NULL;
}

void im_disp2_group_set_disp3a(ImDisp2Group *self, KObject *obj3a)
{
	if (IM_IS_DISP2_GROUP(self))
	{
		ImDisp2GroupPrivate *priv = self->privImDisp2Group;
		priv->ctImDisp3a = (CtImDisp3a *)k_object_ref(obj3a);
	}
}

KObject * im_disp2_group_get_disp3a(ImDisp2Group *self)
{
	if (IM_IS_DISP2_GROUP(self))
	{
		ImDisp2GroupPrivate *priv = self->privImDisp2Group;
		return (KObject *)priv->ctImDisp3a;
	}
	return NULL;
}

ImDisp2Group *im_disp2_group_new(kuchar *pclkCounter, kuchar *hclkCounter)
{
	ImDisp2Group *self = (ImDisp2Group *) k_object_new_with_private(IM_TYPE_DISP2_GROUP,
			sizeof(ImDisp2GroupPrivate));
	ImDisp2GroupPrivate *priv = self->privImDisp2Group;
	priv->pImDispPclkCounter = pclkCounter;
	priv->pImDispHclkCounter = hclkCounter;
	return self;
}
