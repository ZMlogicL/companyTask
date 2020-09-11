/*
 *ctimdisp3.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-02
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#include <stdlib.h>
#include <string.h>
#include "ctimdisp.h"//already define CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
#include "im_disp.h"
#include "dd_top.h"
#include "ddim_user_custom.h"
#include "jdsdisp3a.h"

#include "ct_im_disptbl_define.h"

#include "ctimdisp4.h"//variable
#include "ctimdisp3a.h"
#include "ctimdisp3.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(CtImDisp3, ct_im_disp3, K_TYPE_OBJECT)
#define CT_IM_DISP3_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImDisp3Private, CT_TYPE_IM_DISP3))

struct _CtImDisp3Private
{
	kpointer qwertyu;
	kuchar *pImDispPclkCounter;
//	kuchar *pImDispHclkCounter;
};

/*
 * DECLS
 * */

/*
 * IMPL
 * */
static void ct_im_disp3_constructor(CtImDisp3 *self)
{
	CtImDisp3Private *priv = CT_IM_DISP3_GET_PRIVATE(self);
	self->privCtImDisp3 = priv;
}

static void ct_im_disp3_destructor(CtImDisp3 *self)
{
}

/*
 * PUBLIC
 * */

#ifdef CtImDisp_CO_DEBUG_DISP
/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/

void ct_im_disp3_dump_reg_yhelp(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHLPCTL = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYHLPCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHLPK0  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYHLPK0.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHLPK1  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYHLPK1.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHLPOL  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYHLPOL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHLPCLR = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].LCH.LYHLPCLR.dword));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_warning(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYWCTL = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYWCTL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW0TH = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYW0TH.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW1TH = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYW1TH.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW0ST = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYW0ST.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW0CA = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].LCH.LYW0CA.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW0CB = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].LCH.LYW0CB.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW1ST = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LYW1ST.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW1CA = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].LCH.LYW1CA.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYW1CB = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].LCH.LYW1CB.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LBOST  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LBOST.word));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_zebra(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LZBWID = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LZBWID.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LZBV   = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LZBV.word));
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LZBPT  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].LCH.LZBPT.word));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_matrix(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	kint32 loop = 0;
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	for (loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
		Ddim_Print(("IO_DISP.MAIN[%d].LCH.LY2R[%d].dword = 0x%llX\n",
				block, loop, IO_DISP.MAIN[block].LCH.LY2R[loop].dword));
	}
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_output_size(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.OVSIZE = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.OVSIZE.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.OHSIZE = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.OHSIZE.word));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_clbdt(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CLBDT =\n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].DCORE.CLBDT[0].word), 16);
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_out_matrix(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	kint32 loop = 0;
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	for (loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
		Ddim_Print(("IO_DISP.MAIN[%d].DCORE.R2Y[%d].dword = 0x%llX\n",
				block, loop, IO_DISP.MAIN[block].DCORE.R2Y[loop].dword));
	}
	for (loop = D_IM_DISP_MATRIX_SIZE - 1; loop >= 0; loop--) {
		Ddim_Print(("IO_DISP.MAIN[%d].DCORE.Y2R[%d].dword = 0x%llX\n",
				block, loop, IO_DISP.MAIN[block].DCORE.Y2R[loop].dword));
	}
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_clip(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.YCAL   = %llX\n",
			block, (LLONG)IO_DISP.MAIN[block].DCORE.YCAL.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.YCLIP  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.YCLIP.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CBCAL  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.CBCAL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CBCLIP = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.CBCLIP.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CRCAL  = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.CRCAL.word));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.CRCLIP = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.CRCLIP.word));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_face(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDSTA   = \n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].DCORE.FFDSTA[0].word),
			D_IM_DISP_FACE_FRAME_COUNT);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFSIZE   = \n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].DCORE.FFSIZE[0].word),
			D_IM_DISP_FACE_FRAME_COUNT);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFWIDTH  = \n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].DCORE.FFWIDTH[0].word),
			D_IM_DISP_FACE_FRAME_COUNT);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFCLR    = \n", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].DCORE.FFCLR[0].word),
			D_IM_DISP_FACE_FRAME_COUNT);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDISPEN = %016llX\n",
			block, IO_DISP.MAIN[block].DCORE.FFDISPEN.dword));
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.FFDO     = %08X\n",
			block, (kuint32)IO_DISP.MAIN[block].DCORE.FFDO.word));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_osd_area_size(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	kint32 i;

	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	for (i = 0; i < 2; i++) {
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRISIZE = \n", block, i));
		ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRISIZE[0].word),
				D_IM_DISP_OSD_DISPLAY_AREA_COUNT);
	}
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_osd_area_addr(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	kint32 i;

	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	for (i = 0; i < 2; i++) {
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRSA0 = \n", block, i));
		ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRSA0[0]),
				D_IM_DISP_OSD_ADDR_0_BANK_SIZE);
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRSA  = \n", block, i));
		ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRSA[0]),
				D_IM_DISP_OSD_ADDR_BANK_SIZE);
	}
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_osd_area_adata_addr(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	kint32 i;

	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	for (i = 0; i < 2; i++) {
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRASA = \n", block, i));
		ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRASA[0].word),
				D_IM_DISP_OSD_DISPLAY_AREA_COUNT);
	}
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_osd_lfd(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	kint32 i;

	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	for (i = 0; i < 2; i++) {
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRHGA = \n", block, i));
		ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRHGA[0].word),
				D_IM_DISP_OSD_DISPLAY_AREA_COUNT);
	}
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_osd_adata_lfd(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	kint32 i;

	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	for (i = 0; i < 2; i++) {
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRAHGA = \n", block, i));
		ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRAHGA[0].word),
				D_IM_DISP_OSD_DISPLAY_AREA_COUNT);
	}
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_osd_pos(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	kint32 i;

	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	for (i = 0; i < 2; i++) {
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRDSTA = \n", block, i));
		ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRDSTA[0].word),
				D_IM_DISP_OSD_DISPLAY_AREA_COUNT);
	}
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_osd_blink_timer(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	kint32 i;

	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	for (i = 0; i < 2; i++) {
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRBLINK = \n", block, i));
		ct_im_disp3a_output_word_table((kuint32*) (&IO_DISP.MAIN[block].GRCH[i].GRBLINK.word[0]),
				D_IM_DISP_GRBLINK_SIZE);
	}
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_osd_resize(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	kint32 i;

	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	for (i = 0; i < 2; i++) {
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRRSZ0 = %08X\n",
				block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRRSZ0.word));
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRRSZ1 = %08X\n",
				block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRRSZ1.word));
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRRSZ2 = %08X\n",
				block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRRSZ2.word));
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRRSZ3 = %08X\n",
				block, i, (kuint32)IO_DISP.MAIN[block].GRCH[i].GRRSZ3.word));
	}
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_osd_matrix(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	kint32 i;

	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	for (i = 0; i < 2; i++) {
		Ddim_Print(("IO_DISP.MAIN[%d].GRCH[%d].GRY2R = ", block, i));
		ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[i].GRY2R[0].word),
				D_IM_DISP_MATRIX_SIZE);
	}
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_anti_gamma_table(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.IGTBLA.IGTBLR = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.IGTBLA.IGTBLR.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.IGTBLA.IGTBLG = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.IGTBLA.IGTBLG.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.IGTBLA.IGTBLB = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.IGTBLA.IGTBLB.hword);

	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.IGTBLB.IGTBLR = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.IGTBLB.IGTBLR.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.IGTBLB.IGTBLG = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.IGTBLB.IGTBLG.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.IGTBLB.IGTBLB = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.IGTBLB.IGTBLB.hword);


	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_main_gamma_table(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.GTBLA.GTBLR = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.GTBLA.GTBLR.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.GTBLA.GTBLG = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.GTBLA.GTBLG.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.GTBLA.GTBLB = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.GTBLA.GTBLB.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.GTBLB.GTBLR = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.GTBLB.GTBLR.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.GTBLB.GTBLG = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.GTBLB.GTBLG.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].LCH.GTBLB.GTBLB = \n", block));
	ct_im_disp3a_output_ushort_32_table(IO_DISP_TBL.MAIN[block].LCH.GTBLB.GTBLB.hword);
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_dcore_gamma_table(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].DCORE.GTBLA.GTBLR = \n", block));
	ct_im_disp3a_output_ushort_33_table(IO_DISP_TBL.MAIN[block].DCORE.GTBLA.GTBLR.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].DCORE.GTBLA.GTBLG = \n", block));
	ct_im_disp3a_output_ushort_33_table(IO_DISP_TBL.MAIN[block].DCORE.GTBLA.GTBLG.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].DCORE.GTBLA.GTBLB = \n", block));
	ct_im_disp3a_output_ushort_33_table(IO_DISP_TBL.MAIN[block].DCORE.GTBLA.GTBLB.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].DCORE.GTBLB.GTBLR = \n", block));
	ct_im_disp3a_output_ushort_33_table(IO_DISP_TBL.MAIN[block].DCORE.GTBLB.GTBLR.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].DCORE.GTBLB.GTBLG = \n", block));
	ct_im_disp3a_output_ushort_33_table(IO_DISP_TBL.MAIN[block].DCORE.GTBLB.GTBLG.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].DCORE.GTBLB.GTBLB = \n", block));
	ct_im_disp3a_output_ushort_33_table(IO_DISP_TBL.MAIN[block].DCORE.GTBLB.GTBLB.hword);
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_lumi_gamma_table(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].DCORE.YSTBLAYT = \n", block));
	ct_im_disp3a_output_ushort_33_table(IO_DISP_TBL.MAIN[block].DCORE.YSTBLAYT.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].DCORE.YSTBLBYT = \n", block));
	ct_im_disp3a_output_ushort_33_table(IO_DISP_TBL.MAIN[block].DCORE.YSTBLBYT.hword);
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_gain_table(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].DCORE.YSTBLACG = \n", block));
	ct_im_disp3a_output_ushort_33_table(IO_DISP_TBL.MAIN[block].DCORE.YSTBLACG.hword);
	Ddim_Print(("IO_DISP_TBL.MAIN[%d].DCORE.YSTBLBCG = \n", block));
	ct_im_disp3a_output_ushort_33_table(IO_DISP_TBL.MAIN[block].DCORE.YSTBLBCG.hword);
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_bb(CtImDisp3 *self)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[0].DCORE.OHSIZE   = %08X\n", (kuint32)IO_DISP.MAIN[0].DCORE.OHSIZE.word));
	Ddim_Print(("IO_DISP.MAIN[0].DCORE.CLBHSIZE = %08X\n", (kuint32)IO_DISP.MAIN[0].DCORE.CLBHSIZE.word));
	Ddim_Print(("IO_DISP.MAIN[0].DCORE.CLBDT    = \n"));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[0].DCORE.CLBDT[0].word), 16);
	Ddim_Print(("IO_DISP.MAIN[1].DCORE.OHSIZE   = %08X\n", (kuint32)IO_DISP.MAIN[1].DCORE.OHSIZE.word));
	Ddim_Print(("IO_DISP.MAIN[1].DCORE.CLBHSIZE = %08X\n", (kuint32)IO_DISP.MAIN[1].DCORE.CLBHSIZE.word));
	Ddim_Print(("IO_DISP.MAIN[1].DCORE.CLBDT    = \n"));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[1].DCORE.CLBDT[0].word), 16);
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_reset(CtImDisp3 *self)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);

	// Common block 0.
	Ddim_Print(("IO_DISP.MAIN[0].LCH.LRST         = %08X\n", (kuint32)IO_DISP.MAIN[0].LCH.LRST.word));
	Ddim_Print(("IO_DISP.MAIN[0].DCORE.RESET      = %08X\n", (kuint32)IO_DISP.MAIN[0].DCORE.RESET.word));
	Ddim_Print(("IO_DISP.MAIN[0].GRCH[0].GRRST    = %08X\n", (kuint32)IO_DISP.MAIN[0].GRCH[0].GRRST.word));
	Ddim_Print(("IO_DISP.MAIN[0].GRCH[1].GRRST    = %08X\n", (kuint32)IO_DISP.MAIN[0].GRCH[1].GRRST.word));

	// Common block 1.
	Ddim_Print(("IO_DISP.MAIN[1].LCH.LRST         = %08X\n", (kuint32)IO_DISP.MAIN[1].LCH.LRST.word));
	Ddim_Print(("IO_DISP.MAIN[1].DCORE.RESET      = %08X\n", (kuint32)IO_DISP.MAIN[1].DCORE.RESET.word));
	Ddim_Print(("IO_DISP.MAIN[1].GRCH[0].GRRST    = %08X\n", (kuint32)IO_DISP.MAIN[1].GRCH[0].GRRST.word));
	Ddim_Print(("IO_DISP.MAIN[1].GRCH[1].GRRST    = %08X\n", (kuint32)IO_DISP.MAIN[1].GRCH[1].GRRST.word));

	// MIPI-DSI.
	Ddim_Print(("IO_DISP.MDSCTL.MDSSR             = %08X\n", (kuint32)IO_DISP.MDSCTL.MDSSR.word));

	// HDMI.
	Ddim_Print(("IO_DISP.JDDISP_HDMI_HDMIC.HDMISR = %08X\n", (kuint32)IO_DISP.JDDISP_HDMI_HDMIC.HDMISR.word));

	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_addr(CtImDisp3 *self)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[0].LCH.LYSA  ="));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[0].LCH.LYSA[0].word), 4);
	Ddim_Print(("IO_DISP.MAIN[0].LCH.LCSA  ="));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[0].LCH.LCSA[0].word), 4);
	Ddim_Print(("IO_DISP.MAIN[1].LCH.LYSA  ="));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[1].LCH.LYSA[0].word), 4);
	Ddim_Print(("IO_DISP.MAIN[1].LCH.LCSA  ="));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[1].LCH.LCSA[0].word), 4);
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_resize(CtImDisp3 *self)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[0].LCH.LRSZ0 = %08X\n", (kuint32)IO_DISP.MAIN[0].LCH.LRSZ0.word));
	Ddim_Print(("IO_DISP.MAIN[0].LCH.LRSZ1 = %08X\n", (kuint32)IO_DISP.MAIN[0].LCH.LRSZ1.word));
	Ddim_Print(("IO_DISP.MAIN[0].LCH.LRSZ2 = %08X\n", (kuint32)IO_DISP.MAIN[0].LCH.LRSZ2.word));
	Ddim_Print(("IO_DISP.MAIN[0].LCH.LRSZ3 = %08X\n", (kuint32)IO_DISP.MAIN[0].LCH.LRSZ3.word));
	Ddim_Print(("IO_DISP.MAIN[1].LCH.LRSZ0 = %08X\n", (kuint32)IO_DISP.MAIN[1].LCH.LRSZ0.word));
	Ddim_Print(("IO_DISP.MAIN[1].LCH.LRSZ1 = %08X\n", (kuint32)IO_DISP.MAIN[1].LCH.LRSZ1.word));
	Ddim_Print(("IO_DISP.MAIN[1].LCH.LRSZ2 = %08X\n", (kuint32)IO_DISP.MAIN[1].LCH.LRSZ2.word));
	Ddim_Print(("IO_DISP.MAIN[1].LCH.LRSZ3 = %08X\n", (kuint32)IO_DISP.MAIN[1].LCH.LRSZ3.word));
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_dump_reg_csc_matrix(CtImDisp3 *self, E_IM_DISP_SEL block)
{
	CtImDisp3Private *priv = self->privCtImDisp3;
	ct_im_disp3_pclk_counter_on(priv->pImDispPclkCounter);
	Ddim_Print(("IO_DISP.MAIN[%d].LCH.LY2R      =", block));
	ct_im_disp3a_output_dword_table((LLONG*)(&IO_DISP.MAIN[block].LCH.LY2R[0].dword), 3);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[0].GRY2R =", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[0].GRY2R[0].word), 3);
	Ddim_Print(("IO_DISP.MAIN[%d].GRCH[1].GRY2R =", block));
	ct_im_disp3a_output_word_table((kuint32*)(&IO_DISP.MAIN[block].GRCH[1].GRY2R[0].word), 3);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.R2Y     =", block));
	ct_im_disp3a_output_dword_table((LLONG*)(&IO_DISP.MAIN[block].DCORE.R2Y[0].dword), 3);
	Ddim_Print(("IO_DISP.MAIN[%d].DCORE.Y2R     =", block));
	ct_im_disp3a_output_dword_table((LLONG*)(&IO_DISP.MAIN[block].DCORE.Y2R[0].dword), 3);
	ct_im_disp3_pclk_counter_off(priv->pImDispPclkCounter);
}

void ct_im_disp3_print_param_resize(T_IM_DISP_RESIZE resize)
{
	Ddim_Print(("[T_IM_DISP_RESIZE]\n"));
	Ddim_Print(("HRSZSL = %d\n", resize.rsz0));
	Ddim_Print(("HRSZM = %08X, HRSZN = %08X, HRSZOF = %08X\n",
			resize.rsz1.bit.HRSZM, resize.rsz1.bit.HRSZN, resize.rsz1.bit.HRSZOF));
	Ddim_Print(("VRSZM = %08X, VRSZN = %08X, VRSZOF = %08X\n",
			resize.rsz2.bit.VRSZM, resize.rsz2.bit.VRSZN, resize.rsz2.bit.VRSZOF));
	Ddim_Print(("VCSTA = %08X, HCSTA = %08X\n", resize.rsz3.bit.VCSTA, resize.rsz3.bit.HCSTA));
}

void ct_im_disp3_print_param_yhelp(T_IM_DISP_YHLP Yhlp)
{
	Ddim_Print(("[T_IM_DISP_YHLP]\n"));
	Ddim_Print(("LYHLPCTL = 0x%08X\n", (kuint32)Yhlp.lyhlpcl.word));
	Ddim_Print(("LYHLPK0  = 0x%08X\n", (kuint32)Yhlp.lyhlpk.word[0]));
	Ddim_Print(("LYHLPK1  = 0x%08X\n", (kuint32)Yhlp.lyhlpk.word[1]));
	Ddim_Print(("LYHLPOL  = 0x%08X\n", (kuint32)Yhlp.lyhlpol.word));
	Ddim_Print(("LYHLPCLR = 0x%llX\n", (LLONG)Yhlp.lyhlpclr.dword));
}

void ct_im_disp3_print_param_warning(T_IM_DISP_WARNING warning)
{
	Ddim_Print(("[T_IM_DISP_WARNING]\n"));

	Ddim_Print(("LYWCTL = 0x%08X\n", (kuint32)warning.lywctl.word));
	Ddim_Print(("LYW0TH = 0x%08X\n", (kuint32)warning.lyw0th.word));
	Ddim_Print(("LYW1TH = 0x%08X\n", (kuint32)warning.lyw1th.word));
	Ddim_Print(("LYW0ST = 0x%08X\n", (kuint32)warning.lyw0st));
	Ddim_Print(("LYW0CA = 0x%llX\n", (LLONG)warning.lyw0ca.dword));
	Ddim_Print(("LYW0CB = 0x%llX\n", (LLONG)warning.lyw0cb.dword));
	Ddim_Print(("LYW1ST = 0x%08X\n", (kuint32)warning.lyw1st));
	Ddim_Print(("LYW1CA = 0x%llX\n", (LLONG)warning.lyw1ca.dword));
	Ddim_Print(("LYW1CB = 0x%llX\n", (LLONG)warning.lyw1cb.dword));
	Ddim_Print(("LBOST  = 0x%08X\n", (kuint32)warning.lbost));
}

void ct_im_disp3_print_param_zebra(T_IM_DISP_ZEBRA zebra)
{
	Ddim_Print(("[T_IM_DISP_ZEBRA]\n"));

	Ddim_Print(("lzbwid.bit.ZBHH = 0x%08X\n", zebra.lzbwid.bit.ZBHH));
	Ddim_Print(("lzbwid.bit.ZBHL = 0x%08X\n", zebra.lzbwid.bit.ZBHL));
	Ddim_Print(("lzbv.bit.ZBVSTA = 0x%08X\n", zebra.lzbv.bit.ZBVSTA));
	Ddim_Print(("lzbv.bit.ZBVCYC = 0x%08X\n", zebra.lzbv.bit.ZBVCYC));
	Ddim_Print(("lzbpt.bit.ZBDIR = 0x%08X\n", zebra.lzbpt.bit.ZBDIR));
}

void ct_im_disp3_print_param_matrix(U_IM_DISP_YR_MATRIX_COEFFICIENT matrix[D_IM_DISP_MATRIX_SIZE])
{
	kint32 i;

	Ddim_Print(("[U_IM_DISP_YR_MATRIX_COEFFICIENT]\n"));
	for(i = 0; i < 3; i++) {
//		Ddim_Print(("  %04X %04X %04X\n",
//		matrix[i].bit.COEFFICIENT0, matrix[i].bit.COEFFICIENT1, matrix[i].bit.COEFFICIENT2));
		Ddim_Print(("  [%d]  0x%llX\n", i, matrix[i].dword));
	}
}

void ct_im_disp3_print_param_clbdt(U_IM_DISP_IMAGE_COLOR* clbdt)
{
	kint32 i;

	Ddim_Print(("[U_IM_DISP_IMAGE_COLOR]\n"));
	for(i = 0; i < D_IM_DISP_COLOR_BAR_COUNT; i++) {
		Ddim_Print(("  CLBDT%02d (RGB) %02X %02X %02X\n", i, clbdt[i].rgb.r, clbdt[i].rgb.g, clbdt[i].rgb.b));
	}
}

void ct_im_disp3_print_param_out_matrix(U_IM_DISP_YR_MATRIX_COEFFICIENT* matrix)
{
	kint32 i;

	Ddim_Print(("[U_IM_DISP_YR_MATRIX_COEFFICIENT]\n"));
	for(i = 0; i < 3; i++) {
		Ddim_Print(("  COEFFICIENT0:%04X\n", (kushort)(matrix[i].bit.COEFFICIENT0)));
		Ddim_Print(("  COEFFICIENT1:%04X\n", (kushort)(matrix[i].bit.COEFFICIENT1)));
		Ddim_Print(("  COEFFICIENT2:%04X\n", (kushort)(matrix[i].bit.COEFFICIENT2)));
	}
}

void ct_im_disp3_print_param_clip(T_IM_DISP_CLIP_CAL clipCal)
{
	Ddim_Print(("[T_IM_DISP_CLIP_CAL]\n"));
	Ddim_Print(("clipCal.y_cal.ygain  = 0x%02X\n",(kuint32)clipCal.y_cal.ygain));
	Ddim_Print(("clipCal.y_cal.yofs   = %d\n",  (kuint32)clipCal.y_cal.yofs));
	Ddim_Print(("clipCal.y_clip.cph   = 0x%04X\n",(kuint32)clipCal.y_clip.cph));
	Ddim_Print(("clipCal.y_clip.cpl   = 0x%04X\n",(kuint32)clipCal.y_clip.cpl));
	Ddim_Print(("clipCal.cb_cal.cgain = 0x%02X\n",(kuint32)clipCal.cb_cal.cgain));
	Ddim_Print(("clipCal.cb_cal.cofs  = %d\n",  clipCal.cb_cal.cofs));
	Ddim_Print(("clipCal.cb_clip.cph  = 0x%04X\n",(kuint32)clipCal.cb_clip.cph));
	Ddim_Print(("clipCal.cb_clip.cpl  = 0x%04X\n",(kuint32)clipCal.cb_clip.cpl));
	Ddim_Print(("clipCal.cr_cal.cgain = 0x%02X\n",(kuint32)clipCal.cr_cal.cgain));
	Ddim_Print(("clipCal.cr_cal.cofs  = %d\n",  clipCal.cr_cal.cofs));
	Ddim_Print(("clipCal.cr_clip.cph  = 0x%04X\n",(kuint32)clipCal.cr_clip.cph));
	Ddim_Print(("clipCal.cr_clip.cpl  = 0x%04X\n",(kuint32)clipCal.cr_clip.cpl));
}

void ct_im_disp3_print_param_face(T_IM_DISP_FACE_FRAME face)
{
	kint32 i;

	Ddim_Print(("[T_IM_DISP_FACE_FRAME]\n"));
	for (i = 0; i < D_IM_DISP_FACE_FRAME_COUNT; i++) {
		Ddim_Print(("ffdsta[%02d]  : DSH = %04X, DSV = %04X\n", i,
					face.param[i].ffdsta.bit.DSH,
					face.param[i].ffdsta.bit.DSV));
		Ddim_Print(("ffsize[%02d]  : FFHSZ = %04X, FFVSZ = %04X\n", i,
					face.param[i].ffsize.bit.FFHSZ,
					face.param[i].ffsize.bit.FFVSZ));
		Ddim_Print(("ffwidth[%02d] : FFHWID = %02X, FFVWID = %02X\n", i,
					face.param[i].ffwidth.bit.FFHWID,
					face.param[i].ffwidth.bit.FFVWID));
		Ddim_Print(("ffclr[%02d]   : FFCLRR = %02X, FFCLRG = %02X, FFCLRB = %02X\n", i,
					face.param[i].ffclr.bit.FFCLRR,
					face.param[i].ffclr.bit.FFCLRG,
					face.param[i].ffclr.bit.FFCLRB));
	}
	Ddim_Print(("ffden = %016llX\n", face.ffden));
	Ddim_Print(("msff = %d\n", face.msff));
}

void ct_im_disp3_print_param_osd_area_size(U_IM_DISP_SIZE* inputSize)
{
	kint32 i;
	for (i = 0; i < D_IM_DISP_OSD_DISPLAY_AREA_COUNT; i++) {
		Ddim_Print(("inputSize[%d] width:0x%04X, lines:0x%04X\n", i,
					inputSize[i].size.width, inputSize[i].size.lines));
	}
}

void ct_im_disp3_print_param_osd_matrix(U_IM_DISP_GRY2R* gry2r)
{
	kint32 i;

	Ddim_Print(("[U_IM_DISP_GRY2R]\n"));
	for(i = 0; i < 3; i++) {
		Ddim_Print(("  YR0:0x%02X YR1:0x%02X YR2:0x%02X\n",
				(kuchar)gry2r[i].bit.YR0, (kuchar)gry2r[i].bit.YR1, (kuchar)gry2r[i].bit.YR2));
	}
}

void ct_im_disp3_pclk_counter_on(kuchar *pclkCounter)
{
#ifdef CO_ACT_PCLOCK
	Dd_Top_Start_Clock(pclkCounter,
			&Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAP_ON);
#endif	// CO_ACT_PCLOCK
}

void ct_im_disp3_pclk_counter_off(kuchar *pclkCounter)
{
#ifdef CO_ACT_PCLOCK
	Dd_Top_Stop_Clock(pclkCounter,
			&Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAP_OFF);
#endif	// CO_ACT_PCLOCK
}

void ct_im_disp3_hclk_counter_on(kuchar *hclkCounter)
{
#ifdef CO_ACT_HCLOCK
	Dd_Top_Start_Clock(hclkCounter,
			&Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAH_ON);
#endif	// CO_ACT_HCLOCK
}

void ct_im_disp3_hclk_counter_off(kuchar *hclkCounter)
{
#ifdef CO_ACT_HCLOCK
	Dd_Top_Stop_Clock(hclkCounter,
			&Dd_Top_Get_CLKSTOP3(), D_IM_DISP_CLKSTOP3_DISPAH_OFF);
#endif	// CO_ACT_HCLOCK
}

void ct_im_disp3_int_00_cb()
{
	Ddim_Print(("ct_im_disp3_int_00_cb is called\n"));
}

void ct_im_disp3_int_01_cb()
{
	Ddim_Print(("ct_im_disp3_int_01_cb is called\n"));
}

void ct_im_disp3_int_02_cb()
{
	Ddim_Print(("ct_im_disp3_int_02_cb is called\n"));
}

void ct_im_disp3_int_03_cb()
{
	Ddim_Print(("ct_im_disp3_int_03_cb is called\n"));
}

void ct_im_disp3_int_04_cb()
{
	Ddim_Print(("ct_im_disp3_int_04_cb is called\n"));
}

void ct_im_disp3_int_05_cb()
{
	Ddim_Print(("ct_im_disp3_int_05_cb is called\n"));
}

void ct_im_disp3_int_06_cb()
{
	Ddim_Print(("ct_im_disp3_int_06_cb is called\n"));
}

void ct_im_disp3_int_07_cb()
{
	Ddim_Print(("ct_im_disp3_int_07_cb is called\n"));
}

void ct_im_disp3_int_08_cb()
{
	Ddim_Print(("ct_im_disp3_int_08_cb is called\n"));
}

void ct_im_disp3_int_09_cb()
{
	Ddim_Print(("ct_im_disp3_int_09_cb is called\n"));
}

void ct_im_disp3_int_10_cb()
{
	Ddim_Print(("ct_im_disp3_int_10_cb is called\n"));
}

void ct_im_disp3_int_11_cb()
{
	Ddim_Print(("ct_im_disp3_int_11_cb is called\n"));
}

#endif //CtImDisp_CO_DEBUG_DISP

CtImDisp3 *ct_im_disp3_new(kuchar *pclkCounter, kuchar *hclkCounter)
{
	CtImDisp3 *self = (CtImDisp3 *) k_object_new_with_private(CT_TYPE_IM_DISP3, sizeof(CtImDisp3Private));
	CtImDisp3Private *priv = self->privCtImDisp3;
	priv->pImDispPclkCounter = pclkCounter;
//	priv->pImDispHclkCounter = hclkCounter;
	return self;
}
