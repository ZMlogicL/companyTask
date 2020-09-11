/*
 *ctimdisp3a.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-04
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#include <stdlib.h>
#include <string.h>
#include "im_disp.h"
#include "jdsdisp3a.h"
#include "ctimdisp.h"//already define CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING CtImDisp_CO_DEBUG_DISP
#include "ct_im_disp_define.h"
#include "ctimdisp3.h"
#include "ctimdisp3a.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp3a, ct_im_disp3a, K_TYPE_OBJECT)
#define CT_IM_DISP3A_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp3aPrivate, CT_TYPE_IM_DISP3A))

struct _CtImDisp3aPrivate
{
	kpointer qwertyu;
	kuchar *pImDispPclkCounter;
	kuchar *pImDispHclkCounter;
};

/*
 * DECLS
 * */
static void dumpRegLch(CtImDisp3a *self, E_IM_DISP_SEL block);
static void dumpRegDcore(CtImDisp3a *self, E_IM_DISP_SEL block);
static void dumpRegGrch(CtImDisp3a *self, E_IM_DISP_SEL block, kint32 i);
static void outputByte9LccTable(U_IM_DISP_LCC table[3]);
static void outputShortTable(kushort table[], kint32 size);

/*
 * IMPL
 * */
static void ct_im_disp3a_constructor(CtImDisp3a *self)
{
	//CtImDisp3aPrivate *priv = CT_IM_DISP3A_GET_PRIVATE(self);
}

static void ct_im_disp3a_destructor(CtImDisp3a *self)
{
}

static void dumpRegLch(CtImDisp3a *self, E_IM_DISP_SEL block)
{
	CtImDisp3aPrivate *priv = self->privCtImDisp3a;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RPGEN   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.RPGEN.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LRST      = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LRST.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LTRG      = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LTRG.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LRPGCTL   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LRPGCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIDT0     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LIDT0.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIDT1     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LIDT1.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LISIZE    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LISIZE.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYSA      = \n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].LCH.LYSA[0].word), 4);
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LCSA      = \n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].LCH.LCSA[0].word), 4);
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHGA     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYHGA.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LCHGA     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LCHGA.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIBCTL    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LIBCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LRSZ0     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LRSZ0.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LRSZ1     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LRSZ1.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LRSZ2     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LRSZ2.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LRSZ3     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LRSZ3.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHLPCTL  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYHLPCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHLPK0   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYHLPK0.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHLPK1   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYHLPK1.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHLPOL   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYHLPOL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHLPCLR  = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].LCH.LYHLPCLR.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYWCTL    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYWCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW0TH    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYW0TH.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW1TH    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYW1TH.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW0ST    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYW0ST.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW0CA    = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].LCH.LYW0CA.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW0CB    = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].LCH.LYW0CB.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW1ST    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYW1ST.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW1CA    = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].LCH.LYW1CA.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW1CB    = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].LCH.LYW1CB.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LBLTMR    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LBLTMR.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LBOST     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LBOST.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LZBWID    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LZBWID.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LZBV      = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LZBV.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LZBPT     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LZBPT.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LY2R      = \n", block));
	ct_im_disp3a_output_dword_table((LLONG*)(&IO_DISP.MAIN[block].LCH.LY2R[0].dword), 3);
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LTBLASET  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LTBLASET.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LCC       = \n", block));
	ct_im_disp3a_output_dword_table((LLONG*)(&IO_DISP.MAIN[block].LCH.LCC[0].dword), 3);
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LGMMD     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LGMMD.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LALP      = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LALP.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LDSTA     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LDSTA.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LREVDISP  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LREVDISP.word));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

static void dumpRegDcore(CtImDisp3a *self, E_IM_DISP_SEL block)
{
	CtImDisp3aPrivate *priv = self->privCtImDisp3a;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RESET    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.RESET.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.IFS      = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.IFS.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRG      = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.TRG.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TGKST    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.TGKST.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TOCTL    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.TOCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTC     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.INTC.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTE     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.INTE.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.INTF     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.INTF.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.AXISTS   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.AXISTS.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RPGCTL   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.RPGCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RPGEN    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.RPGEN.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.POLSEL   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.POLSEL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TSL      = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.TSL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.VCYC     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.VCYC.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.HCYC     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.HCYC.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.OVPW     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.OVPW.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.HPW      = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.HPW.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.VBLK     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.VBLK.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.HBLK     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.HBLK.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.VDLY     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.VDLY.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.HDLY     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.HDLY.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.OVSIZE   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.OVSIZE.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.OHSIZE   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.OHSIZE.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.VRFCTL   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.VRFCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.HRFCTL   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.HRFCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.HABLK    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.HABLK.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.DOMD     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.DOMD.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FDOEN    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.FDOEN.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FODATA   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.FODATA.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.BLANKDT1  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.BLANKDT.BLANKDT1.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.BLANKDT2  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.BLANKDT.BLANKDT2.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CLBHSIZE = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.CLBHSIZE.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CLBDT      = \n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].DCORE.CLBDT[0]), 16);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.BLDCTL   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.BLDCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.R2Y      = \n", block));
	ct_im_disp3a_output_dword_table((LLONG*)(&IO_DISP.MAIN[block].DCORE.R2Y[0]), 3);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.YCAL     = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].DCORE.YCAL.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.YCLIP    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.YCLIP.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CBCAL    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.CBCAL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CBCLIP   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.CBCLIP.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CRCAL    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.CRCAL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CRCLIP   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.CRCLIP.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.DOCTL0   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.DOCTL0.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.DOCTL1   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.DOCTL1.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.DOCTL2   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.DOCTL2.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRSCODE0 = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.TRSCODE0.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TRSCODE1 = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.TRSCODE1.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.Y2R      = \n", block));
	ct_im_disp3a_output_dword_table((LLONG*)(&IO_DISP.MAIN[block].DCORE.Y2R[0]), 3);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.TBLASET  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.TBLASET.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GHDSTA   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GHDSTA.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GVDSTA   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GVDSTA.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GLENGTH  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GLENGTH.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GWIDTH   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GWIDTH.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GITVL    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GITVL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GNUM     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GNUM.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GDCTL    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GDCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GDISPEN  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GDISPEN.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDSTA   = \n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].DCORE.FFDSTA[0]), 42);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFSIZE   = \n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].DCORE.FFSIZE[0]), 42);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFWIDTH  = \n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].DCORE.FFWIDTH[0]), 42);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFCLR    = \n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].DCORE.FFCLR[0].word), 42);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDISPEN = %016llX\n",
			block, (LLONG)IO_DISP.MAIN[block].DCORE.FFDISPEN.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDO     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.FFDO.word));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

static void dumpRegGrch(CtImDisp3a *self, E_IM_DISP_SEL block, kint32 i)
{
	CtImDisp3aPrivate *priv = self->privCtImDisp3a;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRRST      = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRRST.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRTRG      = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRTRG.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRRPGCTL   = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRRPGCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRIDT      = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRIDT.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRTISIZE   = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRTISIZE.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRTDSTA    = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRTDSTA.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRIPO      = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRIPO.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRSCCTL    = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRSCCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRISIZE    =", block, i));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRISIZE[0]), 10);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRSA0    =", block, i));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRSA0[0]), 4);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRSA     =", block, i));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRSA[0]), 9);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRASA    =", block, i));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRASA[0]), 10);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRHGA    =", block, i));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRHGA[0]), 10);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRAHGA   =", block, i));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRAHGA[0]), 10);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRDSTA   =", block, i));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRDSTA[0]), 10);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRAREN   = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRAREN.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRBSL    = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRBSL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRBLINK  =", block, i));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRBLINK.word[0]), 5);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRBINIT  = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRBINIT.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRBITRG  = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRBITRG.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRRSZ0   = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRRSZ0.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRRSZ1   = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRRSZ1.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRRSZ2   = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRRSZ2.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRRSZ3   = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRRSZ3.word));
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRY2R    =", block, i));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRY2R[0]), 3);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRALP    = %08X\n",
			block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRALP.word));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

static void outputByte9LccTable(U_IM_DISP_LCC table[3])
{
	kint32 i;
	for(i = 0; i < 3; i++) {
		Ddim_Print(("%llX\n",
			(LLONG)table[i].dword
			));
	}
}

static void outputShortTable(kushort table[], kint32 size)
{
	kint32 i;
	kint32 j;
	for(i = 0, j = 1; i < size; i++, j++) {
		Ddim_Print((" %04X", table[i]));
		if(j == 8){
			Ddim_Print(("\n"));
			j = 0;
		}
	}
	if(j != 1){
		Ddim_Print(("\n"));
	}
}

/*
 * PUBLIC
 * */
#ifdef CtImDisp_CO_DEBUG_DISP

void ct_im_disp3a_dump_reg_p2m_pwch(CtImDisp3a *self, E_IM_DISP_WC_NUM number)
{
	CtImDisp3aPrivate *priv = self->privCtImDisp3a;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("----- P2M -----\n"));
	Ddim_Print(("IO_DISP.P2M[%d].P2MTRG.     = %08lu\n",		number, IO_DISP.P2M[number].P2MTRG.word));
	Ddim_Print(("IO_DISP.P2M[%d].P2MPAEN     = %08lu\n",		number, IO_DISP.P2M[number].P2MPAEN.word));
	Ddim_Print(("IO_DISP.P2M[%d].P2M2PMD     = %08lu\n",		number, IO_DISP.P2M[number].P2M2PMD.word));
	Ddim_Print(("IO_DISP.P2M[%d].P2MCTL      = %08lu\n",		number, IO_DISP.P2M[number].P2MCTL.word));
	Ddim_Print(("IO_DISP.P2M[%d].P2MOFS      = %08lu\n",		number, IO_DISP.P2M[number].P2MOFS.word));
	Ddim_Print(("IO_DISP.P2M[%d].PBSFT       = %08lu\n",		number, IO_DISP.P2M[number].PBSFT.word));
	Ddim_Print(("IO_DISP.P2M[%d].PCLPH       = %08lu\n",		number, IO_DISP.P2M[number].PCLPH.word));
	Ddim_Print(("IO_DISP.P2M[%d].PTRMV       = %08lu\n",		number, IO_DISP.P2M[number].PTRMV.word));
	Ddim_Print(("IO_DISP.P2M[%d].PTRMH       = %08lu\n",		number, IO_DISP.P2M[number].PTRMH.word));
	Ddim_Print(("IO_DISP.P2M[%d].PTRMVW      = %08lu\n",		number, IO_DISP.P2M[number].PTRMVW.word));
	Ddim_Print(("IO_DISP.P2M[%d].PTRMHW      = %08lu\n",		number, IO_DISP.P2M[number].PTRMHW.word));
	Ddim_Print(("IO_DISP.P2M[%d].PTRMXVCYC   = %08lu\n",		number, IO_DISP.P2M[number].PTRMXVCYC.word));
	Ddim_Print(("IO_DISP.P2M[%d].PTRMXHCYC   = %08lu\n",		number, IO_DISP.P2M[number].PTRMXHCYC.word));
	Ddim_Print(("IO_DISP.P2M[%d].PTRMXVEN    = %016llu\n",	number, IO_DISP.P2M[number].PTRMXVEN.dword));
	Ddim_Print(("IO_DISP.P2M[%d].PTRMXHEN    = %016llu\n",	number, IO_DISP.P2M[number].PTRMXHEN.dword));
	Ddim_Print(("IO_DISP.P2M[%d].P2MMIR      = %08lu\n",		number, IO_DISP.P2M[number].P2MMIR.word));
	Ddim_Print(("----- PWCH -----\n"));
	Ddim_Print(("IO_DISP.PWCH[%d].PWCHTRG    = %08lu\n",		number, IO_DISP.PWCH[number].PWCHTRG.word));
	Ddim_Print(("IO_DISP.PWCH[%d].PWAXCTL    = %08lu\n",		number, IO_DISP.PWCH[number].PWAXCTL.word));
	Ddim_Print(("IO_DISP.PWCH[%d].PWS        = %08lu\n",		number, IO_DISP.PWCH[number].PWS.word));
	Ddim_Print(("IO_DISP.PWCH[%d].PWCHCTL    = %08lu\n",		number, IO_DISP.PWCH[number].PWCHCTL.word));
	Ddim_Print(("IO_DISP.PWCH[%d].PWCHINTENB = %08lu\n",		number, IO_DISP.PWCH[number].PWCHINTENB.word));
	Ddim_Print(("IO_DISP.PWCH[%d].PWSA       = %08lu\n",		number, IO_DISP.PWCH[number].PWSA.word));
	Ddim_Print(("IO_DISP.PWCH[%d].PWLSIZE    = %08lu\n",		number, IO_DISP.PWCH[number].PWLSIZE.word));
	Ddim_Print(("IO_DISP.PWCH[%d].PWVFM      = %08lu\n",		number, IO_DISP.PWCH[number].PWVFM.word));
	Ddim_Print(("IO_DISP.PWCH[%d].PWDW       = %08lu\n",		number, IO_DISP.PWCH[number].PWDW.word));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3a_clear_reg_lch(CtImDisp3a *self, E_IM_DISP_SEL block)
{
	CtImDisp3aPrivate *priv = self->privCtImDisp3a;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	IO_DISP.MAIN[block].LCH.LRST.word = 0;
	IO_DISP.MAIN[block].LCH.LRPGCTL.word = 0;
	IO_DISP.MAIN[block].LCH.LIDT0.word = 0;
	IO_DISP.MAIN[block].LCH.LIDT1.word = 0;
	IO_DISP.MAIN[block].LCH.LISIZE.word = 0;
	IO_DISP.MAIN[block].LCH.LYSA[0].word = 0;
	IO_DISP.MAIN[block].LCH.LYSA[1].word = 0;
	IO_DISP.MAIN[block].LCH.LYSA[2].word = 0;
	IO_DISP.MAIN[block].LCH.LYSA[3].word = 0;
	IO_DISP.MAIN[block].LCH.LCSA[0].word = 0;
	IO_DISP.MAIN[block].LCH.LCSA[1].word = 0;
	IO_DISP.MAIN[block].LCH.LCSA[2].word = 0;
	IO_DISP.MAIN[block].LCH.LCSA[3].word = 0;
	IO_DISP.MAIN[block].LCH.LYHGA.word = 0;
	IO_DISP.MAIN[block].LCH.LCHGA.word = 0;
	IO_DISP.MAIN[block].LCH.LIBCTL.word = 0;
	IO_DISP.MAIN[block].LCH.LRSZ0.word = 0;
	IO_DISP.MAIN[block].LCH.LRSZ1.word = 0;
	IO_DISP.MAIN[block].LCH.LRSZ2.word = 0;
	IO_DISP.MAIN[block].LCH.LRSZ3.word = 0;
	IO_DISP.MAIN[block].LCH.LYHLPCTL.word = 0;
	IO_DISP.MAIN[block].LCH.LYHLPK0.word = 0;
	IO_DISP.MAIN[block].LCH.LYHLPK1.word = 0;
	IO_DISP.MAIN[block].LCH.LYHLPOL.word = 0;
	IO_DISP.MAIN[block].LCH.LYHLPCLR.dword = 0;
	IO_DISP.MAIN[block].LCH.LYWCTL.word = 0;
	IO_DISP.MAIN[block].LCH.LYW0TH.word = 0;
	IO_DISP.MAIN[block].LCH.LYW1TH.word = 0;
	IO_DISP.MAIN[block].LCH.LYW0ST.word = 0;
	IO_DISP.MAIN[block].LCH.LYW0CA.dword = 0;
	IO_DISP.MAIN[block].LCH.LYW0CB.dword = 0;
	IO_DISP.MAIN[block].LCH.LYW1ST.word = 0;
	IO_DISP.MAIN[block].LCH.LYW1CA.dword = 0;
	IO_DISP.MAIN[block].LCH.LYW1CB.dword = 0;
	IO_DISP.MAIN[block].LCH.LBLTMR.word = 0;
	IO_DISP.MAIN[block].LCH.LBOST.word = 0;
	IO_DISP.MAIN[block].LCH.LZBWID.word = 0;
	IO_DISP.MAIN[block].LCH.LZBV.word = 0;
	IO_DISP.MAIN[block].LCH.LZBPT.word = 0;
	IO_DISP.MAIN[block].LCH.LY2R[0].dword = 0;
	IO_DISP.MAIN[block].LCH.LY2R[1].dword = 0;
	IO_DISP.MAIN[block].LCH.LY2R[2].dword = 0;
	IO_DISP.MAIN[block].LCH.LTBLASET.word = 0;
	IO_DISP.MAIN[block].LCH.LCC[0].dword = 0;
	IO_DISP.MAIN[block].LCH.LCC[1].dword = 0;
	IO_DISP.MAIN[block].LCH.LCC[2].dword = 0;
	IO_DISP.MAIN[block].LCH.LGMMD.word = 0;
	IO_DISP.MAIN[block].LCH.LALP.word = 0;
	IO_DISP.MAIN[block].LCH.LDSTA.word = 0;
	IO_DISP.MAIN[block].LCH.LREVDISP.word = 0;
	IO_DISP.MAIN[block].LCH.LTBLASET.word = 0;
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3a_dump_reg_grid(CtImDisp3a *self, E_IM_DISP_SEL block)
{
	CtImDisp3aPrivate *priv = self->privCtImDisp3a;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.RPGEN   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.RPGEN.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GHDSTA  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GHDSTA.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GVDSTA  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GVDSTA.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GLENGTH = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GLENGTH.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GWIDTH  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GWIDTH.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GITVL   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GITVL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GNUM    = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GNUM.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GDCTL   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GDCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GDISPEN = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.GDISPEN.word));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3a_dump_reg_trg(CtImDisp3a *self)
{
	CtImDisp3aPrivate *priv = self->privCtImDisp3a;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("--- Block:0 ---\n"));
	Ddim_Print(("IO_DISP.MAIN[0].LCH.LTRG.word       = %08X\n", (kuint32)IO_DISP.MAIN[0].LCH.LTRG.word));
	Ddim_Print(("IO_DISP.MAIN[0].DCORE.TRG.bit.TRG   = %08X\n", (kuint32)IO_DISP.MAIN[0].DCORE.TRG.bit.TRG));
	Ddim_Print(("IO_DISP.MAIN[0].GRCH[0].GRTRG.word  = %08X\n", (kuint32)IO_DISP.MAIN[0].GRCH[0].GRTRG.word));
	Ddim_Print(("IO_DISP.MAIN[0].GRCH[1].GRTRG.word  = %08X\n", (kuint32)IO_DISP.MAIN[0].GRCH[1].GRTRG.word));
	Ddim_Print(("--- Block:1 ---\n"));
	Ddim_Print(("IO_DISP.MAIN[1].LCH.LTRG.word       = %08X\n", (kuint32)IO_DISP.MAIN[1].LCH.LTRG.word));
	Ddim_Print(("IO_DISP.MAIN[1].DCORE.TRG.bit.TRG   = %08X\n", (kuint32)IO_DISP.MAIN[1].DCORE.TRG.bit.TRG));
	Ddim_Print(("IO_DISP.MAIN[1].GRCH[0].GRTRG.word  = %08X\n", (kuint32)IO_DISP.MAIN[1].GRCH[0].GRTRG.word));
	Ddim_Print(("IO_DISP.MAIN[1].GRCH[1].GRTRG.word  = %08X\n", (kuint32)IO_DISP.MAIN[1].GRCH[1].GRTRG.word));
	Ddim_Print(("--- CH:1 ---\n"));
	Ddim_Print(("IO_DISP.PWCH[0].PWCHTRG.bit.PWCHTRG = %08X\n", (kuint32)IO_DISP.PWCH[0].PWCHTRG.bit.PWCHTRG));
	Ddim_Print(("IO_DISP.P2M[0].P2MTRG.bit.P2MTRG    = %08X\n", (kuint32)IO_DISP.P2M[0].P2MTRG.bit.P2MTRG));
	Ddim_Print(("--- CH:2 ---\n"));
	Ddim_Print(("IO_DISP.PWCH[1].PWCHTRG.bit.PWCHTRG = %08X\n", (kuint32)IO_DISP.PWCH[1].PWCHTRG.bit.PWCHTRG));
	Ddim_Print(("IO_DISP.P2M[1].P2MTRG.bit.P2MTRG    = %08X\n\n", (kuint32)IO_DISP.P2M[1].P2MTRG.bit.P2MTRG));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3a_dump_regiser(CtImDisp3a *self, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_SEL block)
{
	Ddim_Print(("Layer:%d\n", layer));

	switch (layer) {
		case E_IM_DISP_SEL_LAYER_DCORE:
			dumpRegDcore(self, block);
			break;
		case E_IM_DISP_SEL_LAYER_OSD_0:
			dumpRegGrch(self, block, 0);
			break;
		case E_IM_DISP_SEL_LAYER_OSD_1:
			dumpRegGrch(self, block, 1);
			break;
		default: // E_IM_DISP_SEL_LAYER_MAIN
			dumpRegLch(self, block);
			break;
	}
}

void ct_im_disp3a_dump_reg_dcore_gamma(CtImDisp3a *self, E_IM_DISP_SEL block)
{
	CtImDisp3aPrivate *priv = self->privCtImDisp3a;
	ct_im_disp3_pclk_counter_on(priv->pImDispHclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GTBLA.GTBLR      = \n", block));
	outputShortTable((kushort*)(&IO_DISP_TBL.MAIN[block].DCORE.GTBLA.GTBLR), 33);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GTBLA.GTBLB      = \n", block));
	outputShortTable((kushort*)(&IO_DISP_TBL.MAIN[block].DCORE.GTBLA.GTBLG), 33);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GTBLA.GTBLB      = \n", block));
	outputShortTable((kushort*)(&IO_DISP_TBL.MAIN[block].DCORE.GTBLA.GTBLB), 33);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GTBLB.GTBLR      = \n", block));
	outputShortTable((kushort*)(&IO_DISP_TBL.MAIN[block].DCORE.GTBLB.GTBLR), 33);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GTBLB.GTBLG      = \n", block));
	outputShortTable((kushort*)(&IO_DISP_TBL.MAIN[block].DCORE.GTBLB.GTBLG), 33);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.GTBLB.GTBLB      = \n", block));
	outputShortTable((kushort*)(&IO_DISP_TBL.MAIN[block].DCORE.GTBLB.GTBLB), 33);
	ct_im_disp3_pclk_counter_off(priv->pImDispHclkCounter);
}

void ct_im_disp3a_output_dword_table(LLONG table[], kint32 size)
{
	kint32 i;
	kint32 j;
	for(i = 0, j = 1; i < size; i++, j++) {
		Ddim_Print((" %016llX", table[i]));
		if(j == 4){
			Ddim_Print(("\n"));
			j = 0;
		}
	}
	if(j != 1){
		Ddim_Print(("\n"));
	}
}

void ct_im_disp3a_print_ctrl_output_tbl(T_IM_DISP_CTRL_OUTPUT_TBL ctrlTbl)
{
	Ddim_Print(("[T_IM_DISP_CTRL_OUTPUT_TBL]\n"));
	Ddim_Print(("--- gamma_a.r_data ---\n"));
	ct_im_disp3a_output_ushort_33_table(ctrlTbl.gamma_a.r_data);
	Ddim_Print(("--- gamma_a.g_data ---\n"));
	ct_im_disp3a_output_ushort_33_table(ctrlTbl.gamma_a.g_data);
	Ddim_Print(("--- gamma_a.b_data ---\n"));
	ct_im_disp3a_output_ushort_33_table(ctrlTbl.gamma_a.b_data);
	Ddim_Print(("--- gamma_b.r_data ---\n"));
	ct_im_disp3a_output_ushort_33_table(ctrlTbl.gamma_b.r_data);
	Ddim_Print(("--- gamma_b.g_data ---\n"));
	ct_im_disp3a_output_ushort_33_table(ctrlTbl.gamma_b.g_data);
	Ddim_Print(("--- gamma_b.b_data ---\n"));
	ct_im_disp3a_output_ushort_33_table(ctrlTbl.gamma_b.b_data);
	Ddim_Print(("--- luminance_a ---\n"));
	ct_im_disp3a_output_ushort_33_table(ctrlTbl.luminance_a);
	Ddim_Print(("--- chroma_a ---\n"));
	ct_im_disp3a_output_ushort_33_table(ctrlTbl.chroma_a);
	Ddim_Print(("--- luminance_b ---\n"));
	ct_im_disp3a_output_ushort_33_table(ctrlTbl.luminance_b);
	Ddim_Print(("--- chroma_b ---\n"));
	ct_im_disp3a_output_ushort_33_table(ctrlTbl.chroma_b);
}

void ct_im_disp3a_output_p2m_pwch(T_IM_DISP_CTRL_P2M *p2m, T_IM_DISP_CTRL_PWCH pwch)
{
	Ddim_Print(("----- P2M parameter -----\n"));
	Ddim_Print(("p2mpaen       = 0x%08lu\n", p2m->p2mpaen));
	Ddim_Print(("p2mctl_plpf   = 0x%08X\n", p2m->p2mctl_plpf));
	Ddim_Print(("p2mctl_p2mtyp = 0x%08X\n", p2m->p2mctl_p2mtyp));
	Ddim_Print(("p2mofs        = 0x%04X\n", p2m->p2mofs));
	Ddim_Print(("pbsft         = 0x%02X\n", p2m->pbsft));
	Ddim_Print(("pclph         = 0x%04X\n", p2m->pclph));
	Ddim_Print(("ptrmv         = 0x%04X\n", p2m->ptrmv));
	Ddim_Print(("ptrmh         = 0x%04X\n", p2m->ptrmh));
	Ddim_Print(("ptrmvw        = 0x%04X\n", p2m->ptrmvw));
	Ddim_Print(("ptrmhw        = 0x%08lu\n", p2m->ptrmhw));
	Ddim_Print(("ptrmxvcyc     = 0x%02X\n", p2m->ptrmxvcyc));
	Ddim_Print(("ptrmxhcyc     = 0x%02X\n", p2m->ptrmxhcyc));
	Ddim_Print(("ptrmxven      = 0x%016llu\n", p2m->ptrmxven));
	Ddim_Print(("ptrmxhen      = 0x%016llu\n", p2m->ptrmxhen));
	Ddim_Print(("p2mmir        = 0x%02X\n", p2m->p2mmir));
	Ddim_Print(("p2m2pmd       = 0x%08X\n", p2m->p2m2pmd));
	Ddim_Print(("----- PWCH parameter -----\n"));
	Ddim_Print(("pwaxctl       = 0x%08X\n", (kuint32)pwch.pwaxctl.word));
	Ddim_Print(("pwmw          = 0x%02X\n", pwch.pwmw));
	Ddim_Print(("pwchintenb    = 0x%08X\n", (kuint32)pwch.pwchintenb.word));
	Ddim_Print(("pwsa          = 0x%08X\n", (kuint32)pwch.pwsa));
	Ddim_Print(("pwlsize       = 0x%08X\n", (kuint32)pwch.pwlsize));
	Ddim_Print(("pwvfm         = 0x%02d\n", pwch.pwvfm));
}

void ct_im_disp3a_print_param_grch(T_IM_DISP_CTRL_OSD_LAYER ctrl)
{
	kint32 loop = 0;
	Ddim_Print(("[T_IM_DISP_CTRL_OSD_LAYER]\n"));
	Ddim_Print(("ctrl.gridt          = %08X\n", (kuint32)ctrl.gridt.word));
	Ddim_Print(("ctrl.grtisize       = %08X\n", (kuint32)ctrl.grtisize.word));
	Ddim_Print(("ctrl.grtdsta        = %08X\n", (kuint32)ctrl.grtdsta.word));
	Ddim_Print(("ctrl.gripo          = %08X\n", (kuint32)ctrl.gripo.word));
	Ddim_Print(("ctrl.grscctl_idset  = %08X\n", (kuint32)ctrl.grscctl_idset));
	for(loop = D_IM_DISP_OSD_DISPLAY_AREA_COUNT - 1; loop >= 0; loop--) {
		Ddim_Print(("ctrl.grisize[%d]    = %08X\n", loop, (kuint32)ctrl.grisize[loop].word));
		Ddim_Print(("ctrl.grhga[%d]      = %08X\n", loop, (kuint32)ctrl.grhga[loop]));
		Ddim_Print(("ctrl.grahga[%d]     = %08X\n", loop, (kuint32)ctrl.grahga[loop]));
		Ddim_Print(("ctrl.grdsta[%d]     = %08X\n", loop, (kuint32)ctrl.grdsta[loop].word));
	}
	for(loop = D_IM_DISP_OSD_ADDR_0_BANK_SIZE - 1; loop >= 0; loop--) {
		Ddim_Print(("ctrl.grsa0[%d]      = %08X\n", loop, (kuint32)ctrl.grsa0[loop]));
	}
	for(loop = D_IM_DISP_OSD_ADDR_BANK_SIZE - 1; loop >= 0; loop--) {
		Ddim_Print(("ctrl.grsa[%d]       = %08X\n", loop, (kuint32)ctrl.grsa[loop]));
	}
	for(loop = D_IM_DISP_OSD_DISPLAY_AREA_COUNT - 1; loop >= 0; loop--) {
		Ddim_Print(("ctrl.grasa[%d]      = %08X\n", loop, (kuint32)ctrl.grasa[loop]));
	}
	Ddim_Print(("ctrl.graren         = %08X\n", (kuint32)ctrl.graren));
	Ddim_Print(("ctrl.grbsl          = %08X\n", (kuint32)ctrl.grbsl));
	for(loop = 5 - 1; loop >= 0; loop--) {
		Ddim_Print(("ctrl.grblink[%d]        = %08X\n", loop, (kuint32)ctrl.grblink.word[loop]));
	}
	Ddim_Print(("ctrl.grbinit        = %08X\n", (kuint32)ctrl.grbinit));
	Ddim_Print(("ctrl.grbitrg        = %08X\n", (kuint32)ctrl.grbitrg));
	Ddim_Print(("ctrl.grrsz0         = %08X\n", (kuint32)ctrl.grrsz0));
	Ddim_Print(("ctrl.grrsz1         = %08X\n", (kuint32)ctrl.grrsz1.word));
	Ddim_Print(("ctrl.grrsz2         = %08X\n", (kuint32)ctrl.grrsz2.word));
	Ddim_Print(("ctrl.grrsz3         = %08X\n", (kuint32)ctrl.grrsz3.word));
	for(loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
		Ddim_Print(("ctrl.gry2r[%d]      = %08X\n", loop, (kint32)ctrl.gry2r[loop].word));
	}
	Ddim_Print(("ctrl.gralp          = %08X\n", (kuint32)ctrl.gralp));
}

void ct_im_disp3a_print_param_ctrl_grid(T_IM_DISP_CTRL_GRID_LAYER ctrl)
{
	Ddim_Print(("[T_IM_DISP_CTRL_GRID_LAYER]\n"));
	Ddim_Print(("grid.ghdsta  DSH:%d, DSV:%d\n", ctrl.grid.ghdsta.bit.DSH, ctrl.grid.ghdsta.bit.DSV));
	Ddim_Print(("grid.gvdsta  DSH:%d, DSV:%d\n", ctrl.grid.gvdsta.bit.DSH, ctrl.grid.gvdsta.bit.DSV));
	Ddim_Print(("grid.glength GHLEN:%d, GVLEN:%d\n", ctrl.grid.glength.bit.GHLEN, ctrl.grid.glength.bit.GVLEN));
	Ddim_Print(("grid.gwidth  GHWID:%d, GVWID:%d\n", ctrl.grid.gwidth.bit.GHWID, ctrl.grid.gwidth.bit.GVWID));
	Ddim_Print(("grid.gitvl   GHITV:%d, GVITV:%d\n", ctrl.grid.gitvl.bit.GHITV, ctrl.grid.gitvl.bit.GVITV));
	Ddim_Print(("grid.gnum    GHNUM:%d, GVNUM:%d\n", ctrl.grid.gnum.bit.GHNUM, ctrl.grid.gnum.bit.GVNUM));
	Ddim_Print(("grid.gdctl   GCLRR:%d, GCLRG:%d, GCLRB:%d, GALP:%d\n",
			ctrl.grid.gdctl.bit.GCLRR, ctrl.grid.gdctl.bit.GCLRG,
			ctrl.grid.gdctl.bit.GCLRB, ctrl.grid.gdctl.bit.GALP));
	Ddim_Print(("gdispen:%d\n", ctrl.gdispen));
}

void ct_im_disp3a_print_param_grid(T_IM_DISP_GRID grid)
{
	Ddim_Print(("[T_IM_DISP_GRID]\n"));
	Ddim_Print(("ghdsta  DSH:%d, DSV:%d\n", grid.ghdsta.bit.DSH, grid.ghdsta.bit.DSV));
	Ddim_Print(("gvdsta  DSH:%d, DSV:%d\n", grid.gvdsta.bit.DSH, grid.gvdsta.bit.DSV));
	Ddim_Print(("glength GHLEN:%d, GVLEN:%d\n", grid.glength.bit.GHLEN, grid.glength.bit.GVLEN));
	Ddim_Print(("gwidth  GHWID:%d, GVWID:%d\n", grid.gwidth.bit.GHWID, grid.gwidth.bit.GVWID));
	Ddim_Print(("gitvl   GHITV:%d, GVITV:%d\n", grid.gitvl.bit.GHITV, grid.gitvl.bit.GVITV));
	Ddim_Print(("gnum    GHNUM:%d, GVNUM:%d\n", grid.gnum.bit.GHNUM, grid.gnum.bit.GVNUM));
	Ddim_Print(("gdctl   GCLRR:%d, GCLRG:%d, GCLRB:%d, GALP:%d\n",
			grid.gdctl.bit.GCLRR, grid.gdctl.bit.GCLRG, grid.gdctl.bit.GCLRB, grid.gdctl.bit.GALP));
}

void ct_im_disp3a_print_param_ctrl_osd_layer(T_IM_DISP_CTRL_OSD_LAYER osd)
{
	Ddim_Print(("[T_IM_DISP_CTRL_OSD_LAYER]\n"));
	Ddim_Print(("gridt  IFBTMU:%d\n",	osd.gridt.bit.IFBTMU));
	Ddim_Print(("       ASLVSL:%d\n",	osd.gridt.bit.ASLVSL));
	Ddim_Print(("       SLVSL :%d\n",	osd.gridt.bit.SLVSL));
	Ddim_Print(("       PROT  :%d\n",		osd.gridt.bit.PROT));
	Ddim_Print(("       CACHE :%d\n",	osd.gridt.bit.CACHE));
	Ddim_Print(("       NBT   :%d\n",		osd.gridt.bit.NBT));
	Ddim_Print(("       IFMT  :%d\n",		osd.gridt.bit.IFMT));
	Ddim_Print(("grtisize lines:0x%04X, width:0x%04X\n",
			osd.grtisize.size.lines,	osd.grtisize.size.width));
	Ddim_Print(("grtdsta  lines:0x%04X, width:0x%04X\n",	osd.grtdsta.bit.DSV, osd.grtdsta.bit.DSH));
	Ddim_Print(("gripo    IPO4:%d,  IPO3:%d,  IPO2:%d,  IPO1:%d\n",
			osd.gripo.bit.IPO4, osd.gripo.bit.IPO3, osd.gripo.bit.IPO2, osd.gripo.bit.IPO1));
	Ddim_Print(("grscctl_idset:%d\n",	osd.grscctl_idset));
	Ddim_Print(("grisize:0x%08X,  0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grisize[0].word, (kuint32)osd.grisize[1].word,
			(kuint32)osd.grisize[2].word, (kuint32)osd.grisize[3].word,
			(kuint32)osd.grisize[4].word));
	Ddim_Print(("       :0x%08X,  0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grisize[5].word, (kuint32)osd.grisize[6].word,
			(kuint32)osd.grisize[7].word, (kuint32)osd.grisize[8].word, (kuint32)osd.grisize[9].word));
	Ddim_Print(("grsa0  :0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grsa0[0],	(kuint32)osd.grsa0[1], 	(kuint32)osd.grsa0[2], (kuint32)osd.grsa0[3]));
	Ddim_Print(("grsa   :0x%08X,  0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grsa[0], (kuint32)osd.grsa[1], (kuint32)osd.grsa[2],
			(kuint32)osd.grsa[3], (kuint32)osd.grsa[4]));
	Ddim_Print(("       :0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grsa[5], (kuint32)osd.grsa[6], (kuint32)osd.grsa[7], (kuint32)osd.grsa[8]));
	Ddim_Print(("grhga  :0x%08X,  0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grhga[0], (kuint32)osd.grhga[1], (kuint32)osd.grhga[2],
			(kuint32)osd.grhga[3], (kuint32)osd.grhga[4]));
	Ddim_Print(("       :0x%08X,  0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grhga[5], (kuint32)osd.grhga[6], (kuint32)osd.grhga[7],
			(kuint32)osd.grhga[8], (kuint32)osd.grhga[9]));
	Ddim_Print(("grahga :0x%08X,  0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grahga[0], (kuint32)osd.grahga[1], (kuint32)osd.grahga[2],
			(kuint32)osd.grahga[3], (kuint32)osd.grahga[4]));
	Ddim_Print(("       :0x%08X,  0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grahga[5], (kuint32)osd.grahga[6], (kuint32)osd.grahga[7],
			(kuint32)osd.grahga[8], (kuint32)osd.grahga[9]));
	Ddim_Print(("grdsta :0x%08X,  0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grdsta[0].word, (kuint32)osd.grdsta[1].word,
			(kuint32)osd.grdsta[2].word, (kuint32)osd.grdsta[3].word, (kuint32)osd.grdsta[4].word));
	Ddim_Print(("       :0x%08X,  0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grdsta[5].word, (kuint32)osd.grdsta[6].word,
			(kuint32)osd.grdsta[7].word, (kuint32)osd.grdsta[8].word, (kuint32)osd.grdsta[9].word));
	Ddim_Print(("graren :0x%08X\n",	(kuint32)osd.graren));
	Ddim_Print(("grbsl  :0x%08X\n",	(kuint32)osd.grbsl));
	Ddim_Print(("grblink:0x%08X,  0x%08X,  0x%08X,  0x%08X,  0x%08X\n",
			(kuint32)osd.grblink.word[0], (kuint32)osd.grblink.word[1],
			(kuint32)osd.grblink.word[2], (kuint32)osd.grblink.word[3], (kuint32)osd.grblink.word[4]));
	Ddim_Print(("grbinit:0x%08X\n", (kuint32)osd.grbinit));
	Ddim_Print(("grbitrg:0x%08X\n", (kuint32)osd.grbitrg));
	Ddim_Print(("grrsz0 :0x%08X\n",	(kuint32)osd.grrsz0));
	Ddim_Print(("grrsz1 :0x%08X\n",	(kuint32)osd.grrsz1.word));
	Ddim_Print(("grrsz2 :0x%08X\n",	(kuint32)osd.grrsz2.word));
	Ddim_Print(("grrsz3 :0x%08X\n",	(kuint32)osd.grrsz3.word));
	Ddim_Print(("gry2r  :0x%08X,  0x%08X,  0x%08X\n",
			(kint32)osd.gry2r[0].word, (kint32)osd.gry2r[1].word, (kint32)osd.gry2r[2].word));
	Ddim_Print(("gralp  :0x%08X\n",	(kuint32)osd.gralp));
}

void ct_im_disp3a_output_byte_9_table(U_IM_DISP_YR_MATRIX_COEFFICIENT table[3])
{
	kint32 i;
	for(i = 0; i < 3; i++) {
		Ddim_Print(("%llX\n",
			(LLONG)table[i].dword
			));
	}
}

void ct_im_disp3a_output_ushort_32_table(volatile kushort table[32])
{
	kint32 i;
	for(i = 0; i < 32; i += 8) {
		Ddim_Print(("%04X %04X %04X %04X %04X %04X %04X %04X\n",
			table[i],
			table[i+1],
			table[i+2],
			table[i+3],
			table[i+4],
			table[i+5],
			table[i+6],
			table[i+7]
			));
	}

}

void ct_im_disp3a_output_ushort_33_table(volatile kushort table[33])
{
	kint32 i;
	for(i = 0; i < 32; i += 8) {
		Ddim_Print(("%04X %04X %04X %04X %04X %04X %04X %04X\n",
			table[i],
			table[i+1],
			table[i+2],
			table[i+3],
			table[i+4],
			table[i+5],
			table[i+6],
			table[i+7]
			));
	}
	Ddim_Print(("%04X\n", table[32]));

}

void ct_im_disp3a_output_word_table(kuint32 table[], kint32 size)
{
	kint32 i;
	kint32 j;
	for(i = 0, j = 1; i < size; i++, j++) {
		Ddim_Print((" %08X", table[i]));
		if(j == 8){
			Ddim_Print(("\n"));
			j = 0;
		}
	}
	if(j != 1){
		Ddim_Print(("\n"));
	}
}

void ct_im_disp3a_output_dcore_gamma(const T_IM_DISP_GAMMA_TBL_OUT gammaTbl)
{
	if(gammaTbl.r_data){
		Ddim_Print(("--- r_data ---\n"));
		outputShortTable((kushort*)gammaTbl.r_data, 33);
	}
	if(gammaTbl.g_data){
		Ddim_Print(("--- g_data ---\n"));
		outputShortTable((kushort*)gammaTbl.g_data, 33);
	}
	if(gammaTbl.b_data){
		Ddim_Print(("--- b_data ---\n"));
		outputShortTable((kushort*)gammaTbl.b_data, 33);
	}
}

void ct_im_disp3a_get_ctrl_main_layer(BYTE getDataType, E_IM_DISP_SEL block)
{
	kint32 i;
	T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT ctrlTrgLimit;
	T_IM_DISP_CTRL_MAIN_LAYER ctrl;

	memset(&ctrlTrgLimit,0,sizeof(T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT));//初始化
	memset(&ctrl,0,sizeof(T_IM_DISP_CTRL_MAIN_LAYER));//初始化

	T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT* pCtrlTrgLimit = NULL;
	T_IM_DISP_CTRL_MAIN_LAYER* pCtrl = NULL;

	switch(getDataType){
		case CtImDisp3_D_CT_IM_DISP_NO_PARA:
			break;
		case CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY:
			pCtrlTrgLimit =&ctrlTrgLimit;
			break;
		case CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY:
			pCtrl = &ctrl;
			break;
		case CtImDisp3_D_CT_IM_DISP_BOTH_PARA:
			pCtrlTrgLimit =&ctrlTrgLimit;
			pCtrl = &ctrl;
			break;
		default:
			Ddim_Print(("Command parameter error\n"));
			return;
	}
	kint32 error = Im_DISP_Get_Ctrl_Main_Layer(block, pCtrlTrgLimit, pCtrl);
	if(error != D_DDIM_OK){
		Ddim_Print(("Im_DISP_Get_Ctrl_Main_Layer error=%08X\n",error));
		return;
	}

	if(pCtrlTrgLimit) {
		Ddim_Print(("[T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT]\n"));
		Ddim_Print(("lrpgctl  = %08X\n", ctrlTrgLimit.lrpgctl));
		Ddim_Print(("ltblaset_igtaen = %08X\n", ctrlTrgLimit.ltblaset_igtaen));
		Ddim_Print(("ltblaset_gtaen  = %08X\n", ctrlTrgLimit.ltblaset_gtaen));
	}
	if(pCtrl){
		Ddim_Print(("[T_IM_DISP_CTRL_MAIN_LAYER]\n"));
		Ddim_Print(("lidt0        = %08X\n",(kuint32)ctrl.lidt.word[0]));
		Ddim_Print(("lidt1        = %08X\n",(kuint32)ctrl.lidt.word[1]));
		Ddim_Print(("lisize       = %08X\n",(kuint32)ctrl.lisize.word));
		for(i = 0; i < 4; i++){
			Ddim_Print(("laddr[%d] = %08X,%08X\n", i,
					(kuint32)ctrl.laddr[i].y_addr, (kuint32)ctrl.laddr[i].c_addr));
		}
		Ddim_Print(("y_hga    = %08X\n",(kuint32)ctrl.y_hga));
		Ddim_Print(("c_hga    = %08X\n",(kuint32)ctrl.c_hga));
		Ddim_Print(("libctl_iben  = %08X\n",ctrl.libctl_iben));
		Ddim_Print(("libctl_ibset = %08X\n",ctrl.libctl_ibset));
		Ddim_Print(("lrsz0   = %08X\n",ctrl.lrsz0));
		Ddim_Print(("lrsz1   = %08X\n",(kuint32)ctrl.lrsz1.word));
		Ddim_Print(("lrsz2   = %08X\n",(kuint32)ctrl.lrsz2.word));
		Ddim_Print(("lrsz3   = %08X\n",(kuint32)ctrl.lrsz3.word));
		Ddim_Print(("yhlp.lyhlpcl   = %08X\n",(kuint32)ctrl.yhlp.lyhlpcl.word));
		Ddim_Print(("yhlp.lyhlpk[0] = %08X\n",(kuint32)ctrl.yhlp.lyhlpk.word[0]));
		Ddim_Print(("yhlp.lyhlpk[1] = %08X\n",(kuint32)ctrl.yhlp.lyhlpk.word[1]));
		Ddim_Print(("yhlp.lyhlpol   = %08X\n",(kuint32)ctrl.yhlp.lyhlpol.word));
		Ddim_Print(("yhlp.lyhlpclr  = %llX\n",(ULLONG)ctrl.yhlp.lyhlpclr.dword));
		Ddim_Print(("warning.lywctl  = %08X\n",(kuint32)ctrl.warning.lywctl.word));
		Ddim_Print(("warning.lyw0th  = %08X\n",(kuint32)ctrl.warning.lyw0th.word));
		Ddim_Print(("warning.lyw1th  = %08X\n",(kuint32)ctrl.warning.lyw1th.word));
		Ddim_Print(("warning.lyw0st  = %08X\n",(kuint32)ctrl.warning.lyw0st));
		Ddim_Print(("warning.lyw0ca  = %llX\n",(ULLONG)ctrl.warning.lyw0ca.dword));
		Ddim_Print(("warning.lyw0cb  = %llX\n",(ULLONG)ctrl.warning.lyw0cb.dword));
		Ddim_Print(("warning.lyw1st  = %08X\n",(kuint32)ctrl.warning.lyw1st));
		Ddim_Print(("warning.lyw1ca  = %llX\n",(ULLONG)ctrl.warning.lyw1ca.dword));
		Ddim_Print(("warning.lyw1cb  = %llX\n",(ULLONG)ctrl.warning.lyw1cb.dword));
		Ddim_Print(("warning.lbost   = %08X\n",(kuint32)ctrl.warning.lbost));
		Ddim_Print(("lbltmr = %08X\n",(kuint32)ctrl.lbltmr.word));
		Ddim_Print(("zebra.lzbwid   = %08X\n",(kuint32)ctrl.zebra.lzbwid.word));
		Ddim_Print(("zebra.lzbv     = %08X\n",(kuint32)ctrl.zebra.lzbv.word));
		Ddim_Print(("zebra.lzbpt    = %08X\n",(kuint32)ctrl.zebra.lzbpt.word));
		Ddim_Print(("--- ly2r ---\n"));
		ct_im_disp3a_output_byte_9_table(ctrl.ly2r);
		Ddim_Print(("ltblaset_igen  = %08X\n",ctrl.ltblaset_igen));
		Ddim_Print(("ltblaset_igtsl = %08X\n",ctrl.ltblaset_igtsl));
		Ddim_Print(("ltblaset_gmen  = %08X\n",ctrl.ltblaset_gmen));
		Ddim_Print(("ltblaset_gmtsl = %08X\n",ctrl.ltblaset_gmtsl));
		Ddim_Print(("--- lcc ---\n"));
		outputByte9LccTable(ctrl.lcc);
		Ddim_Print(("lgmmd    = %08X\n",(kuint32)ctrl.lgmmd.word));
		Ddim_Print(("lalp     = %08X\n",(kuint32)ctrl.lalp.word));
		Ddim_Print(("ldsta    = %08X\n",(kuint32)ctrl.ldsta.word));
		Ddim_Print(("lrevdisp = %08X\n",(kuint32)ctrl.lrevdisp.word));
	}
}

#endif //CtImDisp_CO_DEBUG_DISP

CtImDisp3a *ct_im_disp3a_new(kuchar *pclkCounter, kuchar *hclkCounter)
{
	CtImDisp3a *self = (CtImDisp3a *) k_object_new_with_private(CT_TYPE_IM_DISP3A,sizeof(CtImDisp3aPrivate));
	CtImDisp3aPrivate *priv = self->privCtImDisp3a;
	priv->pImDispPclkCounter = pclkCounter;
	priv->pImDispHclkCounter = hclkCounter;
	return self;
}
