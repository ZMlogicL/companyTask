/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include <stdlib.h>
#include <string.h> 
#include <ImageMacro/src/imelacore.h>
#include <ImageMacro/src/imelareg.h>
#include <ImageMacro/src/imela.h>
#include "jdsela.h"
#include "im_ela.h"
#include "ctimela.h"
#include "driver_common.h"
#include "dd_top.h"
#include "ctimela1.h"
#include "ctimela2.h"
#include "ctimela3.h"
#include "ctimela4.h"
#include "ctimela5.h"
#include "ctimela6.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImEla1, ct_im_ela1);
#define CT_IM_ELA1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImEla1Private,CT_TYPE_IM_ELA1))

struct _CtImEla1Private
{
	kuint32 result;
	CtImEla *ela;
	ImElaReg* elareg;
};

static void 	ctImEla1OnPclk(CtImEla1 *self);
static void 	ctImEla1OffPclk(CtImEla1 *self);

static void ct_im_ela1_constructor(CtImEla1 *self) 
{
	CtImEla1Private *priv = CT_IM_ELA1_GET_PRIVATE(self);
	priv->ela = ct_im_ela_new();
	priv->elareg = im_ela_reg_new();
}

static void ct_im_ela1_destructor(CtImEla1 *self) 
{
	CtImEla1Private *priv = CT_IM_ELA1_GET_PRIVATE(self);
	if(priv->ela){
		k_object_unref(priv->ela);
		priv->ela = NULL;
	}
	if(priv->elareg != NULL)
	{
		k_object_unref(priv->elareg);
		priv->elareg = NULL;			
	}	
}

static void ctImEla1OnPclk(CtImEla1 *self)
{
#ifdef CO_ACT_PCLOCK
	Dd_Top_Start_Clock((KType)&gCT_IM_ELA_PCLK_Counter, &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_ELAAP_BIT);
#endif	// CO_ACT_PCLOCK
}

/* ELA PCLK change to OFF */
static void ctImEla1OffPclk(CtImEla1 *self)
{
#ifdef CO_ACT_PCLOCK
	Dd_Top_Stop_Clock((KType)&gCT_IM_ELA_PCLK_Counter, &Dd_Top_Get_CLKSTOP6(), D_DD_TOP_ELAAP_BIT);
#endif	// CO_ACT_PCLOCK
}

void ct_im_ela1_1_04(CtImEla1 *self)
{
	CtImEla1Private *priv = CT_IM_ELA1_GET_PRIVATE(self);
	T_IM_ELA_CTRL_COMMON ctrl_ela_common;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	priv->result = im_ela_get_ctrl_common(priv->imela, &ctrl_ela_common);
	Ddim_Print(("priv->result=0x%08X\n", priv->result));

	ctImEla1OnPclk(self);
	if(ctrl_ela_common.noise_data_mode != IO_ELA.NSLMD.bit.NSLMD){
		Ddim_Print(("TEST NG : (NSLMD) %d != %d\n", ctrl_ela_common.noise_data_mode, IO_ELA.NSLMD.bit.NSLMD));
	}
	else if(ctrl_ela_common.noise_data_precision != IO_ELA.NSLMD.bit.NSLRES){
		Ddim_Print(("TEST NG : (NSLRES) %d != %d\n", ctrl_ela_common.noise_data_precision, IO_ELA.NSLMD.bit.NSLRES));
	}
	else if(ctrl_ela_common.noise_data_compress_enable != IO_ELA.NSLMD.bit.NSLKNE){
		Ddim_Print(("TEST NG : (NSLKNE) %d != %d\n", ctrl_ela_common.noise_data_compress_enable, IO_ELA.NSLMD.bit.NSLKNE));
	}
	else if(ctrl_ela_common.bayer_start_pixel_type != IO_ELA.BYRTYP.bit.ORG){
		Ddim_Print(("TEST NG : (ORG) %d != %d\n", ctrl_ela_common.bayer_start_pixel_type, IO_ELA.BYRTYP.bit.ORG));
	}
	else{
		Ddim_Print(("TEST OK!\n"));
	}
	ctImEla1OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);

	im_ela_reg_close(priv->elareg);
}

void ct_im_ela1_1_05(CtImEla1 *self)
{
	CtImEla1Private *priv = CT_IM_ELA1_GET_PRIVATE(self);
	TImElaCtrlEirch ctrl_ela_eirch;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	priv->result = im_ela_get_ctrl_eirch(priv->imela, &ctrl_ela_eirch);
	Ddim_Print(("result=0x%08X\n", priv->result));

	ctImEla1OnPclk(self);
	if(ctrl_ela_eirch.in_bayer_top_addr != IO_ELA.EIRA.bit.EIRA){
		Ddim_Print(("TEST NG : (EIRA) 0x%lx != 0x%lx\n", ctrl_ela_eirch.in_bayer_top_addr, IO_ELA.EIRA.bit.EIRA));
	}
	else if(ctrl_ela_eirch.in_bayer_top_offset != IO_ELA.EIROFS.bit.EIROFS){
		Ddim_Print(("TEST NG : (EIROFS) %d != %d\n", ctrl_ela_eirch.in_bayer_top_offset, IO_ELA.EIROFS.bit.EIROFS));
	}
	else if(ctrl_ela_eirch.in_bayer_total_hsize != IO_ELA.EIRDEF.bit.EIRDEF){
		Ddim_Print(("TEST NG : (EIRDEF) %d != %d\n", ctrl_ela_eirch.in_bayer_total_hsize, IO_ELA.EIRDEF.bit.EIRDEF));
	}
	else if(ctrl_ela_eirch.in_bayer_hsize != IO_ELA.EIRHSIZ.bit.EIRHSIZ){
		Ddim_Print(("TEST NG : (EIRHSIZ) %d != %d\n", ctrl_ela_eirch.in_bayer_hsize, IO_ELA.EIRHSIZ.bit.EIRHSIZ));
	}
	else if(ctrl_ela_eirch.in_bayer_vline != IO_ELA.EIRVSIZ.bit.EIRVSIZ){
		Ddim_Print(("TEST NG : (EIRVSIZ) %d != %d\n", ctrl_ela_eirch.in_bayer_vline, IO_ELA.EIRVSIZ.bit.EIRVSIZ));
	}
	else{
		Ddim_Print(("TEST OK!\n"));
	}
	ctImEla1OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);

	im_ela_reg_close(priv->elareg);
}

void ct_im_ela1_1_06(CtImEla1 *self)
{
	CtImEla1Private *priv = CT_IM_ELA1_GET_PRIVATE(self);
	kuint32 errF = 0;
	kuint32 i;
	TImElaCtrlEiwch ctrl_ela_eiwch;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	priv->result = im_ela_get_ctrl_eiwch(priv->imela, &ctrl_ela_eiwch);
	Ddim_Print(("result=0x%08X\n", priv->result));

	ctImEla1OnPclk(self);
	for(i = 0; i < ImEla_D_IM_ELA_EIWCH_ADDR_MAX; i++){
		if(ctrl_ela_eiwch.out_bayer_top_addr[i] != IO_ELA.EIWA.word[i]){
			Ddim_Print(("TEST NG : (EIWA[%d]) 0x%x != 0x%lx\n" ,i ,ctrl_ela_eiwch.out_bayer_top_addr[i], IO_ELA.EIWA.word[i]));
			errF = 1;
		}
	}
	if(errF == 0){
		if(ctrl_ela_eiwch.out_bayer_total_hsize != IO_ELA.EIWDEF.bit.EIWDEF){
			Ddim_Print(("TEST NG : (EIRVSIZ) %d != %d\n", ctrl_ela_eiwch.out_bayer_total_hsize, IO_ELA.EIWDEF.bit.EIWDEF));
		}
		else{
			Ddim_Print(("TEST OK!\n"));
		}
	}
	ctImEla1OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);

	im_ela_reg_close(priv->elareg);
}

void ct_im_ela1_1_07(CtImEla1 *self)
{
	CtImEla1Private *priv = CT_IM_ELA1_GET_PRIVATE(self);
	TImElaCtrlEnwch ctrl_ela_enwch;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	priv->result = im_ela_get_ctrl_enwch(priv->imela, &ctrl_ela_enwch);
	Ddim_Print(("result=0x%08X\n", priv->result));

	ctImEla1OnPclk(self);
	if(ctrl_ela_enwch.out_extract_noise_top_addr != IO_ELA.ENWA.bit.ENWA){
		Ddim_Print(("TEST NG : (EIRA) 0x%x != 0x%lx\n", ctrl_ela_enwch.out_extract_noise_top_addr, IO_ELA.ENWA.bit.ENWA));
	}
	else if(ctrl_ela_enwch.out_extract_noise_total_hsize != IO_ELA.ENWDEF.bit.ENWDEF){
		Ddim_Print(("TEST NG : (ENWDEF) %d != %d\n", ctrl_ela_enwch.out_extract_noise_total_hsize, IO_ELA.ENWDEF.bit.ENWDEF));
	}
	else{
		Ddim_Print(("TEST OK!\n"));
	}
	ctImEla1OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);

	im_ela_reg_close(priv->elareg);
}

void ct_im_ela1_1_08(CtImEla1 *self)
{
	CtImEla1Private *priv = CT_IM_ELA1_GET_PRIVATE(self);
	kuint32 errF = 0;
	kuint32 i;
	TImElaCtrlEnrech ctrl_ela_enrech;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	priv->result = im_ela_get_ctrl_enrech(priv->imela, &ctrl_ela_enrech);
	Ddim_Print(("result=0x%08X\n", priv->result));

	ctImEla1OnPclk(self);
	for(i = 0; i < ImEla_D_IM_ELA_EIWCH_ADDR_MAX; i++){
		if(ctrl_ela_enrech.in_extract_noise_top_addr[i] != IO_ELA.ENRA.word[i]){
			Ddim_Print(("TEST NG : (ENRA[%d]) 0x%x != 0x%lx\n" ,i ,ctrl_ela_enrech.in_extract_noise_top_addr[i], IO_ELA.ENRA.word[i]));
			errF = 1;
		}
	}
	if(errF == 0){
		if(ctrl_ela_enrech.in_extract_noise_hsize != IO_ELA.ENRHSIZ.bit.ENRHSIZ){
			Ddim_Print(("TEST NG : (ENRHSIZ) %d != %d\n", ctrl_ela_enrech.in_extract_noise_hsize, IO_ELA.ENRHSIZ.bit.ENRHSIZ));
		}
		else if(ctrl_ela_enrech.in_extract_noise_vline != IO_ELA.ENRVSIZ.bit.ENRVSIZ){
			Ddim_Print(("TEST NG : (ENRVSIZ) %d != %d\n", ctrl_ela_enrech.in_extract_noise_vline, IO_ELA.ENRVSIZ.bit.ENRVSIZ));
		}
		else{
			Ddim_Print(("TEST OK!\n"));
		}
	}
	ctImEla1OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);

	im_ela_reg_close(priv->elareg);
}

void ct_im_ela1_1_09(CtImEla1 *self)
{
	CtImEla1Private *priv = CT_IM_ELA1_GET_PRIVATE(self);
	TImElaCtrlEnrachEnwmch ctrl_ela_enrach_enwmch;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	priv->result = im_ela_get_ctrl_enrach_enwmch(priv->imela, &ctrl_ela_enrach_enwmch);
	Ddim_Print(("result=0x%08X\n", priv->result));

	ctImEla1OnPclk(self);
	if(ctrl_ela_enrach_enwmch.synthetic_noise_top_addr != IO_ELA.ENSA.bit.ENSA){
		Ddim_Print(("TEST NG : (ENSA) 0x%x != 0x%lx\n", ctrl_ela_enrach_enwmch.synthetic_noise_top_addr, IO_ELA.ENSA.bit.ENSA));
	}
	else if(ctrl_ela_enrach_enwmch.synthetic_noise_total_hsize != IO_ELA.ENSDEF.bit.ENSDEF){
		Ddim_Print(("TEST NG : (ENWDEF) %d != %d\n", ctrl_ela_enrach_enwmch.synthetic_noise_total_hsize, IO_ELA.ENWDEF.bit.ENWDEF));
	}
	else if(ctrl_ela_enrach_enwmch.synthetic_noise_hsize != IO_ELA.ENSHSIZ.bit.ENSHSIZ){
		Ddim_Print(("TEST NG : (ENSHSIZ) %d != %d\n", ctrl_ela_enrach_enwmch.synthetic_noise_hsize, IO_ELA.ENSHSIZ.bit.ENSHSIZ));
	}
	else if(ctrl_ela_enrach_enwmch.synthetic_noise_vline != IO_ELA.ENSVSIZ.bit.ENSVSIZ){
		Ddim_Print(("TEST NG : (ENSVSIZ) %d != %d\n", ctrl_ela_enrach_enwmch.synthetic_noise_vline, IO_ELA.ENSVSIZ.bit.ENSVSIZ));
	}
	else{
		Ddim_Print(("TEST OK!\n"));
	}
	ctImEla1OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);

	im_ela_reg_close(priv->elareg);
}

void ct_im_ela1_1_10(CtImEla1 *self)
{
	CtImEla1Private *priv = CT_IM_ELA1_GET_PRIVATE(self);
	kuint32 errF = 0;
	TImElaCtrlCore ctrl_ela_core;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	priv->result = im_ela_get_ctrl_core(priv->imela, &ctrl_ela_core);
	Ddim_Print(("result=0x%08X\n", priv->result));

	ctImEla1OnPclk(self);
	if(ctrl_ela_core.defect_correction_mode != IO_ELA.BYRTYP.bit.ELADCMD){
		Ddim_Print(("TEST NG : (ELADCMD) %d != %d\n", ctrl_ela_core.defect_correction_mode, IO_ELA.BYRTYP.bit.ELADCMD));
		errF = 1;
	}
	if(ctrl_ela_core.zero_point_level != IO_ELA.ELFZP.bit.ELFZP){
		Ddim_Print(("TEST NG : (ELFZP) %d != %d\n", ctrl_ela_core.zero_point_level, IO_ELA.ELFZP.bit.ELFZP));
		errF = 1;
	}
	if(ctrl_ela_core.elflt[0] != IO_ELA.ELFL.ELFL1.bit.ELFL_1){
		Ddim_Print(("TEST NG : (ELFL_1) %d != %d\n", ctrl_ela_core.elflt[0], IO_ELA.ELFL.ELFL1.bit.ELFL_1));
		errF = 1;
	}
	if(ctrl_ela_core.elflt[1] != IO_ELA.ELFL.ELFL1.bit.ELFL_2){
		Ddim_Print(("TEST NG : (ELFL_2) %d != %d\n", ctrl_ela_core.elflt[1], IO_ELA.ELFL.ELFL1.bit.ELFL_2));
		errF = 1;
	}
	if(ctrl_ela_core.elflt[2] != IO_ELA.ELFL.ELFL2.bit.ELFL_3){
		Ddim_Print(("TEST NG : (ELFL_3) %d != %d\n", ctrl_ela_core.elflt[2], IO_ELA.ELFL.ELFL2.bit.ELFL_3));
		errF = 1;
	}
	if(ctrl_ela_core.elflt[3] != IO_ELA.ELFL.ELFL2.bit.ELFL_4){
		Ddim_Print(("TEST NG : (ELFL4) %d != %d\n", ctrl_ela_core.elflt[3], IO_ELA.ELFL.ELFL2.bit.ELFL_4));
		errF = 1;
	}

	// Noise characteristics of the pixel R
	if(ctrl_ela_core.anb_r.offset[0] != IO_ELA.ANBOR.ANBOR1.bit.ANBOR_0){
		Ddim_Print(("TEST NG : (ANBOR_0) %d != %d\n", ctrl_ela_core.anb_r.offset[0], IO_ELA.ANBOR.ANBOR1.bit.ANBOR_0));
		errF = 1;
	}
	if(ctrl_ela_core.anb_r.offset[1] != IO_ELA.ANBOR.ANBOR1.bit.ANBOR_1){
		Ddim_Print(("TEST NG : (ANBOR_1) %d != %d\n", ctrl_ela_core.anb_r.offset[1], IO_ELA.ANBOR.ANBOR1.bit.ANBOR_1));
		errF = 1;
	}
	if(ctrl_ela_core.anb_r.offset[2] != IO_ELA.ANBOR.ANBOR2.bit.ANBOR_2){
		Ddim_Print(("TEST NG : (ANBOR_2) %d != %d\n", ctrl_ela_core.anb_r.offset[2], IO_ELA.ANBOR.ANBOR2.bit.ANBOR_2));
		errF = 1;
	}
	if(ctrl_ela_core.anb_r.offset[3] != IO_ELA.ANBOR.ANBOR2.bit.ANBOR_3){
		Ddim_Print(("TEST NG : (ANBOR_3) %d != %d\n", ctrl_ela_core.anb_r.offset[3], IO_ELA.ANBOR.ANBOR2.bit.ANBOR_3));
		errF = 1;
	}
	if(ctrl_ela_core.anb_r.gain[0] != IO_ELA.ANBKR.ANBKR1.bit.ANBKR_0){
		Ddim_Print(("TEST NG : (ANBKR_0) %d != %d\n", ctrl_ela_core.anb_r.gain[0], IO_ELA.ANBKR.ANBKR1.bit.ANBKR_0));
		errF = 1;
	}
	if(ctrl_ela_core.anb_r.gain[1] != IO_ELA.ANBKR.ANBKR1.bit.ANBKR_1){
		Ddim_Print(("TEST NG : (ANBKR_1) %d != %d\n", ctrl_ela_core.anb_r.gain[1], IO_ELA.ANBKR.ANBKR1.bit.ANBKR_1));
		errF = 1;
	}
	if(ctrl_ela_core.anb_r.gain[2] != IO_ELA.ANBKR.ANBKR2.bit.ANBKR_2){
		Ddim_Print(("TEST NG : (ANBKR_2) %d != %d\n", ctrl_ela_core.anb_r.gain[2], IO_ELA.ANBKR.ANBKR2.bit.ANBKR_2));
		errF = 1;
	}
	if(ctrl_ela_core.anb_r.gain[3] != IO_ELA.ANBKR.ANBKR2.bit.ANBKR_3){
		Ddim_Print(("TEST NG : (ANBKR_3) %d != %d\n", ctrl_ela_core.anb_r.gain[3], IO_ELA.ANBKR.ANBKR2.bit.ANBKR_3));
		errF = 1;
	}
	if(ctrl_ela_core.anb_r.boundary[0] != IO_ELA.ANBDR.ANBDR1.bit.ANBDR_0){
		Ddim_Print(("TEST NG : (ANBDR_0) %d != %d\n", ctrl_ela_core.anb_r.boundary[0], IO_ELA.ANBDR.ANBDR1.bit.ANBDR_0));
		errF = 1;
	}
	if(ctrl_ela_core.anb_r.boundary[1] != IO_ELA.ANBDR.ANBDR1.bit.ANBDR_1){
		Ddim_Print(("TEST NG : (ANBDR_1) %d != %d\n", ctrl_ela_core.anb_r.boundary[1], IO_ELA.ANBDR.ANBDR1.bit.ANBDR_1));
		errF = 1;
	}
	if(ctrl_ela_core.anb_r.boundary[2] != IO_ELA.ANBDR.ANBDR2.bit.ANBDR_2){
		Ddim_Print(("TEST NG: (ANBDR_2) %d != %d\n", ctrl_ela_core.anb_r.boundary[2], IO_ELA.ANBDR.ANBDR2.bit.ANBDR_2));
		errF = 1;
	}
	if(ctrl_ela_core.anb_r.boundary[3] != IO_ELA.ANBDR.ANBDR2.bit.ANBDR_3){
		Ddim_Print(("TEST NG : (ANBDR_3) %d != %d\n", ctrl_ela_core.anb_r.boundary[3], IO_ELA.ANBDR.ANBDR2.bit.ANBDR_3));
		errF = 1;
	}

	// Noise characteristics of the pixel G
	if(ctrl_ela_core.anb_g.offset[0] != IO_ELA.ANBOG.ANBOG1.bit.ANBOG_0){
		Ddim_Print(("TEST NG : (ANBOG_0) %d != %d\n", ctrl_ela_core.anb_g.offset[0], IO_ELA.ANBOG.ANBOG1.bit.ANBOG_0));
		errF = 1;
	}
	if(ctrl_ela_core.anb_g.offset[1] != IO_ELA.ANBOG.ANBOG1.bit.ANBOG_1){
		Ddim_Print(("TEST NG : (ANBOG_1) %d != %d\n", ctrl_ela_core.anb_g.offset[1], IO_ELA.ANBOG.ANBOG1.bit.ANBOG_1));
		errF = 1;
	}
	if(ctrl_ela_core.anb_g.offset[2] != IO_ELA.ANBOG.ANBOG2.bit.ANBOG_2){
		Ddim_Print(("TEST NG : (ANBOG_2) %d != %d\n", ctrl_ela_core.anb_g.offset[2], IO_ELA.ANBOG.ANBOG2.bit.ANBOG_2));
		errF = 1;
	}
	if(ctrl_ela_core.anb_g.offset[3] != IO_ELA.ANBOG.ANBOG2.bit.ANBOG_3){
		Ddim_Print(("TEST NG : (ANBOG_3) %d != %d\n", ctrl_ela_core.anb_g.offset[3], IO_ELA.ANBOG.ANBOG2.bit.ANBOG_3));
		errF = 1;
	}
	if(ctrl_ela_core.anb_g.gain[0] != IO_ELA.ANBKG.ANBKG1.bit.ANBKG_0){
		Ddim_Print(("TEST NG : (ANBKG_0) %d != %d\n", ctrl_ela_core.anb_g.gain[0], IO_ELA.ANBKG.ANBKG1.bit.ANBKG_0));
		errF = 1;
	}
	if(ctrl_ela_core.anb_g.gain[1] != IO_ELA.ANBKG.ANBKG1.bit.ANBKG_1){
		Ddim_Print(("TEST NG : (ANBKG_1) %d != %d\n", ctrl_ela_core.anb_g.gain[1], IO_ELA.ANBKG.ANBKG1.bit.ANBKG_1));
		errF = 1;
	}
	if(ctrl_ela_core.anb_g.gain[2] != IO_ELA.ANBKG.ANBKG2.bit.ANBKG_2){
		Ddim_Print(("TEST NG : (ANBKG_2) %d != %d\n", ctrl_ela_core.anb_g.gain[2], IO_ELA.ANBKG.ANBKG2.bit.ANBKG_2));
		errF = 1;
	}
	if(ctrl_ela_core.anb_g.gain[3] != IO_ELA.ANBKG.ANBKG2.bit.ANBKG_3){
		Ddim_Print(("TEST NG : (ANBKG_3) %d != %d\n", ctrl_ela_core.anb_g.gain[3], IO_ELA.ANBKG.ANBKG2.bit.ANBKG_3));
		errF = 1;
	}
	if(ctrl_ela_core.anb_g.boundary[0] != IO_ELA.ANBDG.ANBDG1.bit.ANBDG_0){
		Ddim_Print(("TEST NG : (ANBDG_0) %d != %d\n", ctrl_ela_core.anb_g.boundary[0], IO_ELA.ANBDG.ANBDG1.bit.ANBDG_0));
		errF = 1;
	}
	if(ctrl_ela_core.anb_g.boundary[1] != IO_ELA.ANBDG.ANBDG1.bit.ANBDG_1){
		Ddim_Print(("TEST NG : (ANBDG_1) %d != %d\n", ctrl_ela_core.anb_g.boundary[1], IO_ELA.ANBDG.ANBDG1.bit.ANBDG_1));
		errF = 1;
	}
	if(ctrl_ela_core.anb_g.boundary[2] != IO_ELA.ANBDG.ANBDG2.bit.ANBDG_2){
		Ddim_Print(("TEST NG: (ANBDG_2) %d != %d\n", ctrl_ela_core.anb_g.boundary[2], IO_ELA.ANBDG.ANBDG2.bit.ANBDG_2));
		errF = 1;
	}
	if(ctrl_ela_core.anb_g.boundary[3] != IO_ELA.ANBDG.ANBDG2.bit.ANBDG_3){
		Ddim_Print(("TEST NG : (ANBDG_3) %d != %d\n", ctrl_ela_core.anb_g.boundary[3], IO_ELA.ANBDG.ANBDG2.bit.ANBDG_3));
		errF = 1;
	}

	// Noise characteristics of the pixel B
	if(ctrl_ela_core.anb_b.offset[0] != IO_ELA.ANBOB.ANBOB1.bit.ANBOB_0){
		Ddim_Print(("TEST NG : (ANBOB_0) %d != %d\n", ctrl_ela_core.anb_b.offset[0], IO_ELA.ANBOB.ANBOB1.bit.ANBOB_0));
		errF = 1;
	}
	if(ctrl_ela_core.anb_b.offset[1] != IO_ELA.ANBOB.ANBOB1.bit.ANBOB_1){
		Ddim_Print(("TEST NG : (ANBOB_1) %d != %d\n", ctrl_ela_core.anb_b.offset[1], IO_ELA.ANBOB.ANBOB1.bit.ANBOB_1));
		errF = 1;
	}
	if(ctrl_ela_core.anb_b.offset[2] != IO_ELA.ANBOB.ANBOB2.bit.ANBOB_2){
		Ddim_Print(("TEST NG : (ANBOB_2) %d != %d\n", ctrl_ela_core.anb_b.offset[2], IO_ELA.ANBOB.ANBOB2.bit.ANBOB_2));
		errF = 1;
	}
	if(ctrl_ela_core.anb_b.offset[3] != IO_ELA.ANBOB.ANBOB2.bit.ANBOB_3){
		Ddim_Print(("TEST NG : (ANBOB_3) %d != %d\n", ctrl_ela_core.anb_b.offset[3], IO_ELA.ANBOB.ANBOB2.bit.ANBOB_3));
		errF = 1;
	}
	if(ctrl_ela_core.anb_b.gain[0] != IO_ELA.ANBKB.ANBKB1.bit.ANBKB_0){
		Ddim_Print(("TEST NG : (ANBKB_0) %d != %d\n", ctrl_ela_core.anb_b.gain[0], IO_ELA.ANBKB.ANBKB1.bit.ANBKB_0));
		errF = 1;
	}
	if(ctrl_ela_core.anb_b.gain[1] != IO_ELA.ANBKB.ANBKB1.bit.ANBKB_1){
		Ddim_Print(("TEST NG : (ANBKB_1) %d != %d\n", ctrl_ela_core.anb_b.gain[1], IO_ELA.ANBKB.ANBKB1.bit.ANBKB_1));
		errF = 1;
	}
	if(ctrl_ela_core.anb_b.gain[2] != IO_ELA.ANBKB.ANBKB2.bit.ANBKB_2){
		Ddim_Print(("TEST NG : (ANBKB_2) %d != %d\n", ctrl_ela_core.anb_b.gain[2], IO_ELA.ANBKB.ANBKB2.bit.ANBKB_2));
		errF = 1;
	}
	if(ctrl_ela_core.anb_b.gain[3] != IO_ELA.ANBKB.ANBKB2.bit.ANBKB_3){
		Ddim_Print(("TEST NG : (ANBKB_3) %d != %d\n", ctrl_ela_core.anb_b.gain[3], IO_ELA.ANBKB.ANBKB2.bit.ANBKB_3));
		errF = 1;
	}
	if(ctrl_ela_core.anb_b.boundary[0] != IO_ELA.ANBDB.ANBDB1.bit.ANBDB_0){
		Ddim_Print(("TEST NG : (ANBDB_0) %d != %d\n", ctrl_ela_core.anb_b.boundary[0], IO_ELA.ANBDB.ANBDB1.bit.ANBDB_0));
		errF = 1;
	}
	if(ctrl_ela_core.anb_b.boundary[1] != IO_ELA.ANBDB.ANBDB1.bit.ANBDB_1){
		Ddim_Print(("TEST NG : (ANBDB_1) %d != %d\n", ctrl_ela_core.anb_b.boundary[1], IO_ELA.ANBDB.ANBDB1.bit.ANBDB_1));
		errF = 1;
	}
	if(ctrl_ela_core.anb_b.boundary[2] != IO_ELA.ANBDB.ANBDB2.bit.ANBDB_2){
		Ddim_Print(("TEST NG : (ANBDB_2) %d != %d\n", ctrl_ela_core.anb_b.boundary[2], IO_ELA.ANBDB.ANBDB2.bit.ANBDB_2));
		errF = 1;
	}
	if(ctrl_ela_core.anb_b.boundary[3] != IO_ELA.ANBDB.ANBDB2.bit.ANBDB_3){
		Ddim_Print(("TEST NG : (ANBDB_3) %d != %d\n", ctrl_ela_core.anb_b.boundary[3], IO_ELA.ANBDB.ANBDB2.bit.ANBDB_3));
		errF = 1;
	}

	if(ctrl_ela_core.lumen_gain_r != IO_ELA.LGTW.LGTW1.bit.LGTWR){
		Ddim_Print(("TEST NG : (LGTWR) %d != %d\n", ctrl_ela_core.lumen_gain_r, IO_ELA.LGTW.LGTW1.bit.LGTWR));
		errF = 1;
	}
	if(ctrl_ela_core.lumen_gain_g != IO_ELA.LGTW.LGTW1.bit.LGTWG){
		Ddim_Print(("TEST NG : (LGTWG) %d != %d\n", ctrl_ela_core.lumen_gain_g, IO_ELA.LGTW.LGTW1.bit.LGTWG));
		errF = 1;
	}
	if(ctrl_ela_core.lumen_gain_b != IO_ELA.LGTW.LGTW2.bit.LGTWB){
		Ddim_Print(("TEST NG : (LGTWB) %d != %d\n", ctrl_ela_core.lumen_gain_b, IO_ELA.LGTW.LGTW2.bit.LGTWB));
		errF = 1;
	}

	if(ctrl_ela_core.lumen_factor_r != IO_ELA.LGT.bit.LGTR){
		Ddim_Print(("TEST NG : (LGTR) %d != %d\n", ctrl_ela_core.lumen_factor_r, IO_ELA.LGT.bit.LGTR));
		errF = 1;
	}
	if(ctrl_ela_core.lumen_factor_g != IO_ELA.LGT.bit.LGTG){
		Ddim_Print(("TEST NG : (LGTG) %d != %d\n", ctrl_ela_core.lumen_factor_g, IO_ELA.LGT.bit.LGTG));
		errF = 1;
	}
	if(ctrl_ela_core.lumen_factor_b != IO_ELA.LGT.bit.LGTB){
		Ddim_Print(("TEST NG : (LGTB) %d != %d\n", ctrl_ela_core.lumen_factor_b, IO_ELA.LGT.bit.LGTB));
		errF = 1;
	}
	if(ctrl_ela_core.lumen_factor_c != IO_ELA.LGT.bit.LGTC){
		Ddim_Print(("TEST NG : (LGTC) %d != %d\n", ctrl_ela_core.lumen_factor_c, IO_ELA.LGT.bit.LGTC));
		errF = 1;
	}

	if(ctrl_ela_core.lumen_edge_r != IO_ELA.LGTE.bit.LGTER){
		Ddim_Print(("TEST NG : (LGTER) %d != %d\n", ctrl_ela_core.lumen_edge_r, IO_ELA.LGTE.bit.LGTER));
		errF = 1;
	}
	if(ctrl_ela_core.lumen_edge_g != IO_ELA.LGTE.bit.LGTEG){
		Ddim_Print(("TEST NG : (LGTEG) %d != %d\n", ctrl_ela_core.lumen_edge_g, IO_ELA.LGTE.bit.LGTEG));
		errF = 1;
	}
	if(ctrl_ela_core.lumen_edge_b != IO_ELA.LGTE.bit.LGTEB){
		Ddim_Print(("TEST NG : (LGTEB) %d != %d\n", ctrl_ela_core.lumen_edge_b, IO_ELA.LGTE.bit.LGTEB));
		errF = 1;
	}

	if(ctrl_ela_core.edge_adjust_a1 != IO_ELA.EDG2ANBA.bit.EDG2ANBA){
		Ddim_Print(("TEST NG : (EDG2ANBA) %d != %d\n", ctrl_ela_core.edge_adjust_a1, IO_ELA.EDG2ANBA.bit.EDG2ANBA));
		errF = 1;
	}
	if(ctrl_ela_core.edge_adjust_a2 != IO_ELA.EDGSCLA.bit.EDGSCLA){
		Ddim_Print(("TEST NG : (EDGSCLA) %d != %d\n", ctrl_ela_core.edge_adjust_a2, IO_ELA.EDGSCLA.bit.EDGSCLA));
		errF = 1;
	}
	if(ctrl_ela_core.edge_adjust_b1 != IO_ELA.EDG2ANBB.bit.EDG2ANBB){
		Ddim_Print(("TEST NG : (EDG2ANBB) %d != %d\n", ctrl_ela_core.edge_adjust_b1, IO_ELA.EDG2ANBB.bit.EDG2ANBB));
		errF = 1;
	}
	if(ctrl_ela_core.edge_adjust_b2 != IO_ELA.EDGSCLB.bit.EDGSCLB){
		Ddim_Print(("TEST NG : (EDGSCLB) %d != %d\n", ctrl_ela_core.edge_adjust_b2, IO_ELA.EDGSCLB.bit.EDGSCLB));
		errF = 1;
	}

	if(ctrl_ela_core.edge_threshold[0] != IO_ELA.ALNGE.ALNGE1.bit.ALNGE_1){
		Ddim_Print(("TEST NG : (ALNGE_1) %d != %d\n", ctrl_ela_core.edge_threshold[0], IO_ELA.ALNGE.ALNGE1.bit.ALNGE_1));
		errF = 1;
	}
	if(ctrl_ela_core.edge_threshold[1] != IO_ELA.ALNGE.ALNGE1.bit.ALNGE_2){
		Ddim_Print(("TEST NG : (ALNGE_2) %d != %d\n", ctrl_ela_core.edge_threshold[1], IO_ELA.ALNGE.ALNGE1.bit.ALNGE_2));
		errF = 1;
	}
	if(ctrl_ela_core.edge_threshold[2] != IO_ELA.ALNGE.ALNGE2.bit.ALNGE_3){
		Ddim_Print(("TEST NG : (ALNGE_3) %d != %d\n", ctrl_ela_core.edge_threshold[2], IO_ELA.ALNGE.ALNGE2.bit.ALNGE_3));
		errF = 1;
	}

	if(ctrl_ela_core.nr[0] != IO_ELA.ALNG.ALNG1.bit.ALNGL1E1N){
		Ddim_Print(("TEST NG : (ALNGL1E1N) %d != %d\n", ctrl_ela_core.nr[0], IO_ELA.ALNG.ALNG1.bit.ALNGL1E1N));
		errF = 1;
	}
	if(ctrl_ela_core.nr[1] != IO_ELA.ALNG.ALNG1.bit.ALNGL1E2N){
		Ddim_Print(("TEST NG : (ALNGL1E2N) %d != %d\n", ctrl_ela_core.nr[1], IO_ELA.ALNG.ALNG1.bit.ALNGL1E2N));
		errF = 1;
	}
	if(ctrl_ela_core.nr[2] != IO_ELA.ALNG.ALNG2.bit.ALNGL1E3N){
		Ddim_Print(("TEST NG : (ALNGL1E2N) %d != %d\n", ctrl_ela_core.nr[2], IO_ELA.ALNG.ALNG2.bit.ALNGL1E3N));
		errF = 1;
	}
	if(ctrl_ela_core.nr[3] != IO_ELA.ALNG.ALNG2.bit.ALNGL2E1N){
		Ddim_Print(("TEST NG : (ALNGL1E2N) %d != %d\n", ctrl_ela_core.nr[3], IO_ELA.ALNG.ALNG2.bit.ALNGL2E1N));
		errF = 1;
	}
	if(ctrl_ela_core.nr[4] != IO_ELA.ALNG.ALNG3.bit.ALNGL2E2N){
		Ddim_Print(("TEST NG : (ALNGL2E2N) %d != %d\n", ctrl_ela_core.nr[4], IO_ELA.ALNG.ALNG3.bit.ALNGL2E2N));
		errF = 1;
	}
	if(ctrl_ela_core.nr[5] != IO_ELA.ALNG.ALNG3.bit.ALNGL2E3N){
		Ddim_Print(("TEST NG : (ALNGL2E3N) %d != %d\n", ctrl_ela_core.nr[5], IO_ELA.ALNG.ALNG3.bit.ALNGL2E3N));
		errF = 1;
	}
	if(ctrl_ela_core.nr[6] != IO_ELA.ALNG.ALNG4.bit.ALNGL3E1N){
		Ddim_Print(("TEST NG : (ALNGL3E1N) %d != %d\n", ctrl_ela_core.nr[6], IO_ELA.ALNG.ALNG4.bit.ALNGL3E1N));
		errF = 1;
	}
	if(ctrl_ela_core.nr[7] != IO_ELA.ALNG.ALNG4.bit.ALNGL3E2N){
		Ddim_Print(("TEST NG : (ALNGL3E2N) %d != %d\n", ctrl_ela_core.nr[7], IO_ELA.ALNG.ALNG4.bit.ALNGL3E2N));
		errF = 1;
	}
	if(ctrl_ela_core.nr[8] != IO_ELA.ALNG.ALNG5.bit.ALNGL3E3N){
		Ddim_Print(("TEST NG : (ALNGL3E3N) %d != %d\n", ctrl_ela_core.nr[8], IO_ELA.ALNG.ALNG5.bit.ALNGL3E3N));
		errF = 1;
	}
	if(ctrl_ela_core.nr[9] != IO_ELA.ALNG.ALNG5.bit.ALNGL4E1N){
		Ddim_Print(("TEST NG : (ALNGL4E1N) %d != %d\n", ctrl_ela_core.nr[9], IO_ELA.ALNG.ALNG5.bit.ALNGL4E1N));
		errF = 1;
	}
	if(ctrl_ela_core.nr[10] != IO_ELA.ALNG.ALNG6.bit.ALNGL4E2N){
		Ddim_Print(("TEST NG : (ALNGL4E2N) %d != %d\n", ctrl_ela_core.nr[10], IO_ELA.ALNG.ALNG6.bit.ALNGL4E2N));
		errF = 1;
	}
	if(ctrl_ela_core.nr[11] != IO_ELA.ALNG.ALNG6.bit.ALNGL4E3N){
		Ddim_Print(("TEST NG : (ALNGL4E3N) %d != %d\n", ctrl_ela_core.nr[11], IO_ELA.ALNG.ALNG6.bit.ALNGL4E3N));
		errF = 1;
	}

	if(ctrl_ela_core.l_noise != IO_ELA.LFTH.bit.LFTH){
		Ddim_Print(("TEST NG : (LFTH) %d != %d\n", ctrl_ela_core.l_noise, IO_ELA.LFTH.bit.LFTH));
		errF = 1;
	}
	
	if(ctrl_ela_core.l_edge[0] != IO_ELA.LCOME.bit.LCOME1){
		Ddim_Print(("TEST NG : (LCOME1) %d != %d\n", ctrl_ela_core.l_edge[0], IO_ELA.LCOME.bit.LCOME1));
		errF = 1;
	}
	if(ctrl_ela_core.l_edge[1] != IO_ELA.LCOME.bit.LCOME2){
		Ddim_Print(("TEST NG : (LCOME1) %d != %d\n", ctrl_ela_core.l_edge[1], IO_ELA.LCOME.bit.LCOME2));
		errF = 1;
	}
	
	if(ctrl_ela_core.l_intense[0] != IO_ELA.LCOMEN.bit.LCOME1N){
		Ddim_Print(("TEST NG : (LCOME1N) %d != %d\n", ctrl_ela_core.l_intense[0], IO_ELA.LCOMEN.bit.LCOME1N));
		errF = 1;
	}
	if(ctrl_ela_core.l_intense[1] != IO_ELA.LCOMEN.bit.LCOME2N){
		Ddim_Print(("TEST NG : (LCOME2N) %d != %d\n", ctrl_ela_core.l_intense[1], IO_ELA.LCOMEN.bit.LCOME2N));
		errF = 1;
	}

	ctImEla1OffPclk(self);

	if(!errF){
		Ddim_Print(("TEST OK!\n"));
	}
	ct_im_ela_clk_chk(priv->ela);

	im_ela_reg_close(priv->elareg);
}

void ct_im_ela1_1_11(CtImEla1 *self)
{
	CtImEla1Private *priv = CT_IM_ELA1_GET_PRIVATE(self);
	TImElaCtrlObCorrection ctrl_ela_ob;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	IO_ELA.OBOF.OBOF1.bit.EOBRR = -1;
	IO_ELA.OBOF.OBOF1.bit.EOBBB = -16;
	IO_ELA.OBOF.OBOF2.bit.EOBGR = -256;
	IO_ELA.OBOF.OBOF2.bit.EOBGB = 256;

	priv->result = im_ela_get_ctrl_ob_correction(priv->imela, &ctrl_ela_ob);
	Ddim_Print(("result=0x%08X\n", priv->result));

	ctImEla1OnPclk(self);
	if(ctrl_ela_ob.ob_rr != IO_ELA.OBOF.OBOF1.bit.EOBRR){
		Ddim_Print(("TEST NG : (EOBRR) %d != %d\n", ctrl_ela_ob.ob_rr, IO_ELA.OBOF.OBOF1.bit.EOBRR));
	}
	else if(ctrl_ela_ob.ob_bb != IO_ELA.OBOF.OBOF1.bit.EOBBB){
		Ddim_Print(("TEST NG : (EOBBB) %d != %d\n", ctrl_ela_ob.ob_bb, IO_ELA.OBOF.OBOF1.bit.EOBBB));
	}
	else if(ctrl_ela_ob.ob_gr != IO_ELA.OBOF.OBOF2.bit.EOBGR){
		Ddim_Print(("TEST NG : (EOBGR) %d != %d\n", ctrl_ela_ob.ob_gr, IO_ELA.OBOF.OBOF2.bit.EOBGR));
	}
	else if(ctrl_ela_ob.ob_gb != IO_ELA.OBOF.OBOF2.bit.EOBGB){
		Ddim_Print(("TEST NG : (EOBGB) %d != %d\n", ctrl_ela_ob.ob_gb, IO_ELA.OBOF.OBOF2.bit.EOBGB));
	}
	else{
		Ddim_Print(("TEST OK!\n"));
	}
	ctImEla1OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);

	im_ela_reg_close(priv->elareg);
}

CtImEla1* ct_im_ela1_new(void) 
{
    CtImEla1 *self = k_object_new_with_private(CT_TYPE_IM_ELA1, sizeof(CtImEla1Private));
    return self;
}
