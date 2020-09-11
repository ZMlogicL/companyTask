/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla2类
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
#include "ctimela.h"
#include "ctimela1.h"
#include "ctimela2.h"
#include "ctimela3.h"
#include "ctimela4.h"
#include "ctimela5.h"
#include "ctimela6.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImEla2, ct_im_ela2);
#define CT_IM_ELA2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImEla2Private,CT_TYPE_IM_ELA2))

struct _CtImEla2Private
{
	CtImEla *ela;
	T_IM_ELA_CTRL_EACH g_ctrl_each;
	ImElaReg* elareg;	
};

/* TODO：申明放回im_ela类,由该文件进行初始化传值进来，先不删 */
// volatile ULONG									S_G_IM_ELA_AXI_ERR = ImEla_D_IM_ELA_NORMAL_END;//imelacore
extern volatile kint32 gIM_ELA_Axi_Err;

static void ctImEla2OnPclk(CtImEla2 *self);
static void ctImEla2OffPclk(CtImEla2 *self);

static void ct_im_ela2_constructor(CtImEla2 *self) 
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	priv->ela = ct_im_ela_new();
	priv->elareg = im_ela_reg_new();	
}

static void ct_im_ela2_destructor(CtImEla2 *self) 
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
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

static void ctImEla2OnPclk(CtImEla2 *self)
{
#ifdef CO_ACT_PCLOCK
	Dd_Top_Start_Clock((kuchar*)&gCT_IM_ELA_PCLK_Counter, &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_ELAAP_BIT);
#endif	// CO_ACT_PCLOCK
}

/* ELA PCLK change to OFF */
static void ctImEla2OffPclk(CtImEla2 *self)
{
#ifdef CO_ACT_PCLOCK
	Dd_Top_Stop_Clock((kuchar*)&gCT_IM_ELA_PCLK_Counter, &Dd_Top_Get_CLKSTOP6(), D_DD_TOP_ELAAP_BIT);
#endif	// CO_ACT_PCLOCK
}

void ct_im_ela2_1_12(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);	
	kushort zeroLevelShift;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	zeroLevelShift = Im_ELA_Get_Optical_Zero_Level_Shift();

	ctImEla2OnPclk(self);
	if(zeroLevelShift != IO_ELA.EZSFTA1.bit.EZSFTA1){
		Ddim_Print(("TEST NG : (EZSFTA1) %d != %d\n", zeroLevelShift, IO_ELA.EZSFTA1.bit.EZSFTA1));
	}
	else{
		Ddim_Print(("TEST OK!\n"));
	}
	ctImEla2OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);

	im_ela_reg_close(priv->elareg);
}

void ct_im_ela2_1_13(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	kuint32 i,j;
	kuint32 result;
	TImElaCtrlCore core[ImElaReg_D_IM_ELA_STAGE_MAX] = {{0}};
	TImElaMultipleTimesInfo multipleExecInfo = {{0}};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		core[i].optical_zero_level_shift = 0x07FF;		// 2047
		core[i].defect_correction_mode = ImEla_D_IM_ELA_ELADCMD_WEAK;		// 1
		core[i].zero_point_level = 0x0FFF;					// 4095

		for(j = 0; j < ImEla_E_IM_ELA_ELFL_MAX; j++){
			core[i].elflt[j] = 0x0FFF;								// 4095
		}
		for(j = 0; j < ImEla_E_IM_ELA_ANB_MAX; j++){
			core[i].anb_r.offset[j] = 0x0FFF;					// 4095
			core[i].anb_r.gain[j] = 0x0FFF;					// 4095
			core[i].anb_r.boundary[j] = 0x0FF0;			// 4080

			core[i].anb_g.offset[j] = 0x0FFF;					// 4095
			core[i].anb_g.gain[j] = 0x0FFF;					// 4095
			core[i].anb_g.boundary[j] = 0x0FF0;			// 4080

			core[i].anb_b.offset[j] = 0x0FFF;				// 4095
			core[i].anb_b.gain[j] = 0x0FFF;					// 4095
			core[i].anb_b.boundary[j] = 0x0FF0;			// 4080
		}
		core[i].lumen_gain_r = 0x03FF;						// 1023
		core[i].lumen_gain_g = 0x03FF;
		core[i].lumen_gain_b = 0x03FF;

		core[i].lumen_factor_r = 0x10;
		core[i].lumen_factor_g = 0x10;
		core[i].lumen_factor_b = 0x10;
		core[i].lumen_factor_c = 0x10;

		core[i].lumen_edge_r = 0x10;
		core[i].lumen_edge_g = 0x10;
		core[i].lumen_edge_b = 0x10;

		core[i].edge_adjust_a1 = 0x00FF;					// 255
		core[i].edge_adjust_a2 = 0x03FF;					// 1023
		core[i].edge_adjust_b1 = 0x03FF;					// 1023
		core[i].edge_adjust_b2 = 0x0FFF;					// 4095

		for(j = 0; j < ImEla_E_IM_ELA_ALNGE_MAX; j++){
			core[i].edge_threshold[j] = 0x0FFF;			// 4095
		}
		for(j = 0; j < ImEla_E_IM_ELA_ALNG_MAX; j++){
			core[i].nr[j] = 0x01FF;								 	// 511
		}
		core[i].l_noise = 0x0FFF;
		for(j = 0; j < ImEla_E_IM_ELA_LCOME_MAX; j++){
			core[i].l_edge[j] = 0x0FFF;
		}
		for(j = 0; j < ImEla_E_IM_ELA_LCOMEN_MAX; j++){
			core[i].l_intense[j] = 0x0100;
		}
	}
	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		multipleExecInfo.core[i]  = &core[i];
	}

	result = im_ela_set_multiple_exec_info(priv->imela, &multipleExecInfo);
	Ddim_Print(("result=0x%08X\n", result));

#if 1
	extern volatile TImElaMultipleTimesInfo	gIM_ELA_Multiple_Exec_Info;

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		Ddim_Print(("<<<STAGE=%d>>>\n", i));
		Ddim_Print(("core[%d].optical_zero_level_shift=%d\n", i, gIM_ELA_Multiple_Exec_Info.core[i]->optical_zero_level_shift));
		Ddim_Print(("core[%d].defect_correction_mode=%d\n", i, gIM_ELA_Multiple_Exec_Info.core[i]->defect_correction_mode));
		Ddim_Print(("core[%d].zero_point_level=%d\n", i, gIM_ELA_Multiple_Exec_Info.core[i]->zero_point_level));

		for(j = 0; j < ImEla_E_IM_ELA_ELFL_MAX; j++){
			Ddim_Print(("core[%d].elflt[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->elflt[j]));
		}
		for(j = 0; j < ImEla_E_IM_ELA_ANB_MAX; j++){
			Ddim_Print(("core[%d].anb_r.offset[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->anb_r.offset[j]));
			Ddim_Print(("core[%d].anb_r.gain[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->anb_r.gain[j]));
			Ddim_Print(("core[%d].anb_r.boundary[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->anb_r.boundary[j]));

			Ddim_Print(("core[%d].anb_g.offset[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->anb_g.offset[j]));
			Ddim_Print(("core[%d].anb_g.gain[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->anb_g.gain[j]));
			Ddim_Print(("core[%d].anb_g.boundary[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->anb_g.boundary[j]));

			Ddim_Print(("core[%d].anb_b.offset[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->anb_b.offset[j]));
			Ddim_Print(("core[%d].anb_b.gain[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->anb_b.gain[j]));
			Ddim_Print(("core[%d].anb_b.boundary[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->anb_b.boundary[j]));
		}
		Ddim_Print(("core[%d].lumen_gain_r=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->lumen_gain_r));
		Ddim_Print(("core[%d].lumen_gain_g=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->lumen_gain_g));
		Ddim_Print(("core[%d].lumen_gain_b=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->lumen_gain_b));

		Ddim_Print(("core[%d].lumen_factor_r=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->lumen_factor_r));
		Ddim_Print(("core[%d].lumen_factor_g=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->lumen_factor_g));
		Ddim_Print(("core[%d].lumen_factor_b=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->lumen_factor_b));
		Ddim_Print(("core[%d].lumen_factor_c=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->lumen_factor_c));

		Ddim_Print(("core[%d].lumen_edge_r=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->lumen_edge_r));
		Ddim_Print(("core[%d].lumen_edge_g=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->lumen_edge_g));
		Ddim_Print(("core[%d].lumen_edge_b=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->lumen_edge_b));

		Ddim_Print(("core[%d].edge_adjust_a1=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->edge_adjust_a1));
		Ddim_Print(("core[%d].edge_adjust_a2=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->edge_adjust_a2));
		Ddim_Print(("core[%d].edge_adjust_b1=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->edge_adjust_b1));
		Ddim_Print(("core[%d].edge_adjust_b2=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->edge_adjust_b2));

		for(j = 0; j < ImEla_E_IM_ELA_ALNGE_MAX; j++){
			Ddim_Print(("core[%d].edge_threshold[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->edge_threshold[j]));
		}
		for(j = 0; j < ImEla_E_IM_ELA_ALNG_MAX; j++){
			Ddim_Print(("core[%d].nr[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->nr[j]));
		}
		Ddim_Print(("core[%d].l_noise=%d\n",i , gIM_ELA_Multiple_Exec_Info.core[i]->l_noise));
		for(j = 0; j < ImEla_E_IM_ELA_LCOME_MAX; j++){
			Ddim_Print(("core[%d].l_edge[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->l_edge[j]));
		}
		for(j = 0; j < ImEla_E_IM_ELA_LCOMEN_MAX; j++){
			Ddim_Print(("core[%d].l_intense[%d]=%d\n",i ,j , gIM_ELA_Multiple_Exec_Info.core[i]->l_intense[j]));
		}
		ddim_user_custom_dly_tsk(10);
	}
#endif
	ct_im_ela_clk_chk(priv->ela);

	im_ela_reg_close(priv->elareg);
}

void ct_im_ela2_1_14(CtImEla2 *self)
{
	Ddim_Print(("<%s>\n", __FUNCTION__));

	Ddim_Print(("(1)\n"));
	IO_ELA.ELAINTE.bit.AXWERE = 1;
	IO_ELA.ELAINTE.bit.AXRERE = 1;
	IO_ELA.ELAINTE.bit.ENWE = 1;
	IO_ELA.ELAINTF.bit.__AXWERF = 1;
	IO_ELA.ELAINTF.bit.__AXRERF = 1;
	IO_ELA.ELAINTF.bit.__ENWF = 1;
	IO_ELA.ELATRG.bit.ELATRG = 3;

	im_ela_core_int_handler();

	Ddim_Print(("(1)gIM_ELA_Axi_Err = %d\n",gIM_ELA_Axi_Err));

	Ddim_Print(("(2)\n"));
	IO_ELA.ELAINTE.bit.AXWERE = 1;
	IO_ELA.ELAINTE.bit.AXRERE = 1;
	IO_ELA.ELAINTE.bit.ENWE = 1;
	IO_ELA.ELAINTF.bit.__AXWERF = 1;
	IO_ELA.ELAINTF.bit.__AXRERF = 0;
	IO_ELA.ELAINTF.bit.__ENWF = 1;
	IO_ELA.ELATRG.bit.ELATRG = 3;
	im_ela_core_int_handler();
	Ddim_Print(("(2)gIM_ELA_Axi_Err = %d\n",gIM_ELA_Axi_Err));

	Ddim_Print(("(3)\n"));
	IO_ELA.ELAINTE.bit.AXWERE = 1;
	IO_ELA.ELAINTE.bit.AXRERE = 1;
	IO_ELA.ELAINTE.bit.ENWE = 1;
	IO_ELA.ELAINTF.bit.__AXWERF = 0;
	IO_ELA.ELAINTF.bit.__AXRERF = 1;
	IO_ELA.ELAINTF.bit.__ENWF = 1;
	IO_ELA.ELATRG.bit.ELATRG = 3;
	im_ela_core_int_handler();
	Ddim_Print(("(3)gIM_ELA_Axi_Err = %d\n",gIM_ELA_Axi_Err));
}

void ct_im_ela2_1_15(CtImEla2 *self)
{
	Ddim_Print(("<%s>\n", __FUNCTION__));

	IO_ELA.ELAINTE.bit.AXWERE = 1;
	IO_ELA.ELAINTE.bit.AXRERE = 1;
	IO_ELA.ELAINTE.bit.ENWE = 1;
	IO_ELA.ELAINTF.bit.__AXWERF = 0;
	IO_ELA.ELAINTF.bit.__AXRERF = 0;
	IO_ELA.ELAINTF.bit.__ENWF = 1;
	IO_ELA.ELATRG.bit.ELATRG = 3;

	im_ela_core_int_handler();

	Ddim_Print(("gIM_ELA_Axi_Err] = %d\n", gIM_ELA_Axi_Err));
}

void ct_im_ela2_1_16(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	kuint32 errF = 0;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	ctImEla2OnPclk(self);
	im_ela_reg_set_deknee_lut_sleep(priv->elareg, ImEla_D_IM_ELA_ENABLE);
	if(IO_ELA.ELABYR.bit.DKNACT != 1){
		Ddim_Print(("TEST NG : Deknee sleep \n"));
		errF = 1;
	}
	im_ela_reg_set_deknee_lut_sleep(priv->elareg, ImEla_D_IM_ELA_DISABLE);
	if(IO_ELA.ELABYR.bit.DKNACT != 0){
		Ddim_Print(("TEST NG : Deknee wake \n"));
		errF = 1;
	}

	if(!errF){
		Ddim_Print(("TEST OK!\n"));
	}
	ctImEla2OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela2_1_17(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	kuint32 errF = 0;
	TImElaCtrlNslmd nslmd;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_get_nslmd(priv->imela, &nslmd);

	ctImEla2OnPclk(self);
	if(nslmd.noise_data_mode != IO_ELA.NSLMD.bit.NSLMD){
		Ddim_Print(("TEST NG : (NSLMD) %d != %d\n", nslmd.noise_data_mode, IO_ELA.NSLMD.bit.NSLMD));
		errF = 1;
	}
	if(nslmd.noise_data_precision != IO_ELA.NSLMD.bit.NSLRES){
		Ddim_Print(("TEST NG : (NSLRES) %d != %d\n", nslmd.noise_data_precision, IO_ELA.NSLMD.bit.NSLRES));
		errF = 1;
	}
	if(nslmd.noise_data_compress_enable != IO_ELA.NSLMD.bit.NSLKNE){
		Ddim_Print(("TEST NG : (NSLKNE) %d != %d\n", nslmd.noise_data_compress_enable, IO_ELA.NSLMD.bit.NSLKNE));
		errF = 1;
	}

	if(!errF){
		Ddim_Print(("TEST OK!\n"));
	}
	ctImEla2OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela2_1_18(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	kuint32 i;
	kuint32 errF = 0;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	for(i = 0; i < D_IM_ELA_EACH_DATA_MAX; i++){
		priv->g_ctrl_each.cache_type_r[i] = i;
		priv->g_ctrl_each.cache_type_w[i] = i+1;
		priv->g_ctrl_each.protect_type_r[i] = i+1;
		priv->g_ctrl_each.protect_type_w[i] = i;
		priv->g_ctrl_each.req_mask_r[i] = i+10;
		priv->g_ctrl_each.req_mask_w[i] = i+20;
	}

	im_ela_set_each(priv->imela, &priv->g_ctrl_each);

	ctImEla2OnPclk(self);
	if(priv->g_ctrl_each.cache_type_r[0] != IO_ELA.EARCACHE.bit.EARCACHE_0){
		Ddim_Print(("TEST NG : (EARCACHE_0) %d != %d\n", priv->g_ctrl_each.cache_type_r[0], IO_ELA.EARCACHE.bit.EARCACHE_0));
		errF = 1;
	}
	if(priv->g_ctrl_each.cache_type_r[1] != IO_ELA.EARCACHE.bit.EARCACHE_1){
		Ddim_Print(("TEST NG : (EARCACHE_1) %d != %d\n", priv->g_ctrl_each.cache_type_r[1], IO_ELA.EARCACHE.bit.EARCACHE_1));
		errF = 1;
	}
	if(priv->g_ctrl_each.cache_type_r[2] != IO_ELA.EARCACHE.bit.EARCACHE_2){
		Ddim_Print(("TEST NG : (EARCACHE_2) %d != %d\n", priv->g_ctrl_each.cache_type_r[2], IO_ELA.EARCACHE.bit.EARCACHE_2));
		errF = 1;
	}

	if(priv->g_ctrl_each.cache_type_w[0] != IO_ELA.EAWCACHE.bit.EAWCACHE_0){
		Ddim_Print(("TEST NG : (EAWCACHE_0) %d != %d\n", priv->g_ctrl_each.cache_type_w[0], IO_ELA.EAWCACHE.bit.EAWCACHE_0));
		errF = 1;
	}
	if(priv->g_ctrl_each.cache_type_w[1] != IO_ELA.EAWCACHE.bit.EAWCACHE_1){
		Ddim_Print(("TEST NG : (EAWCACHE_1) %d != %d\n", priv->g_ctrl_each.cache_type_w[1], IO_ELA.EAWCACHE.bit.EAWCACHE_1));
		errF = 1;
	}
	if(priv->g_ctrl_each.cache_type_w[2] != IO_ELA.EAWCACHE.bit.EAWCACHE_2){
		Ddim_Print(("TEST NG : (EAWCACHE_2) %d != %d\n", priv->g_ctrl_each.cache_type_w[2], IO_ELA.EAWCACHE.bit.EAWCACHE_2));
		errF = 1;
	}

	if(priv->g_ctrl_each.protect_type_r[0] != IO_ELA.EARPROT.bit.EARPROT_0){
		Ddim_Print(("TEST NG : (EARPROT_0) %d != %d\n", priv->g_ctrl_each.protect_type_r[0], IO_ELA.EARPROT.bit.EARPROT_0));
		errF = 1;
	}
	if(priv->g_ctrl_each.protect_type_r[1] != IO_ELA.EARPROT.bit.EARPROT_1){
		Ddim_Print(("TEST NG : (EARPROT_1) %d != %d\n", priv->g_ctrl_each.protect_type_r[1], IO_ELA.EARPROT.bit.EARPROT_1));
		errF = 1;
	}
	if(priv->g_ctrl_each.protect_type_r[2] != IO_ELA.EARPROT.bit.EARPROT_2){
		Ddim_Print(("TEST NG : (EARPROT_2) %d != %d\n", priv->g_ctrl_each.protect_type_r[2], IO_ELA.EARPROT.bit.EARPROT_2));
		errF = 1;
	}

	if(priv->g_ctrl_each.protect_type_w[0] != IO_ELA.EAWPROT.bit.EAWPROT_0){
		Ddim_Print(("TEST NG : (EAWPROT_0) %d != %d\n", priv->g_ctrl_each.protect_type_w[0], IO_ELA.EAWPROT.bit.EAWPROT_0));
		errF = 1;
	}
	if(priv->g_ctrl_each.protect_type_w[1] != IO_ELA.EAWPROT.bit.EAWPROT_1){
		Ddim_Print(("TEST NG : (EAWPROT_1) %d != %d\n", priv->g_ctrl_each.protect_type_w[1], IO_ELA.EAWPROT.bit.EAWPROT_1));
		errF = 1;
	}
	if(priv->g_ctrl_each.protect_type_w[2] != IO_ELA.EAWPROT.bit.EAWPROT_2){
		Ddim_Print(("TEST NG : (EAWPROT_2) %d != %d\n", priv->g_ctrl_each.protect_type_w[2], IO_ELA.EAWPROT.bit.EAWPROT_2));
		errF = 1;
	}

	if(priv->g_ctrl_each.req_mask_r[0] != IO_ELA.EARREQMSK.EARREQMSK1.bit.EARREQMSK_0){
		Ddim_Print(("TEST NG : (EARREQMSK_0) %d != %d\n", priv->g_ctrl_each.req_mask_r[0], IO_ELA.EARREQMSK.EARREQMSK1.bit.EARREQMSK_0));
		errF = 1;
	}
	if(priv->g_ctrl_each.req_mask_r[1] != IO_ELA.EARREQMSK.EARREQMSK1.bit.EARREQMSK_1){
		Ddim_Print(("TEST NG : (EARREQMSK_1) %d != %d\n", priv->g_ctrl_each.req_mask_r[1], IO_ELA.EARREQMSK.EARREQMSK1.bit.EARREQMSK_1));
		errF = 1;
	}
	if(priv->g_ctrl_each.req_mask_r[2] != IO_ELA.EARREQMSK.EARREQMSK2.bit.EARREQMSK_2){
		Ddim_Print(("TEST NG : (EARREQMSK_2) %d != %d\n", priv->g_ctrl_each.req_mask_r[2], IO_ELA.EARREQMSK.EARREQMSK2.bit.EARREQMSK_2));
		errF = 1;
	}

	if(priv->g_ctrl_each.req_mask_w[0] != IO_ELA.EAWREQMSK.EAWREQMSK1.bit.EAWREQMSK_0){
		Ddim_Print(("TEST NG : (EAWREQMSK_0) %d != %d\n", priv->g_ctrl_each.req_mask_w[0], IO_ELA.EAWREQMSK.EAWREQMSK1.bit.EAWREQMSK_0));
		errF = 1;
	}
	if(priv->g_ctrl_each.req_mask_w[1] != IO_ELA.EAWREQMSK.EAWREQMSK1.bit.EAWREQMSK_1){
		Ddim_Print(("TEST NG : (EAWREQMSK_1) %d != %d\n", priv->g_ctrl_each.req_mask_w[1], IO_ELA.EAWREQMSK.EAWREQMSK1.bit.EAWREQMSK_1));
		errF = 1;
	}
	if(priv->g_ctrl_each.req_mask_w[2] != IO_ELA.EAWREQMSK.EAWREQMSK2.bit.EAWREQMSK_2){
		Ddim_Print(("TEST NG : (EAWREQMSK_2) %d != %d\n", priv->g_ctrl_each.req_mask_w[2], IO_ELA.EAWREQMSK.EAWREQMSK2.bit.EAWREQMSK_2));
		errF = 1;
	}
	if(!errF){
		Ddim_Print(("TEST OK!\n"));
	}
	ctImEla2OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela2_1_19(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	TImElaCtrlEach getCtrlEach;
	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_get_each(priv->imela, &getCtrlEach);

	if(memcmp(&getCtrlEach, &priv->g_ctrl_each, sizeof(TImElaCtrlEach)) == 0){
		Ddim_Print(("TEST OK!\n"));
	}
	else{
		Ddim_Print(("TEST NG!\n"));
	}

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela2_1_20(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	TImElaEachAxi each_axi;
	kuint32 errF = 0;

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	ctImEla2OnPclk(self);
	IO_ELA.EARAXSTS.bit.RRESP_0 = 1;
	IO_ELA.EARAXSTS.bit.RRESP_1 = 2;
	IO_ELA.EARAXSTS.bit.RRESP_2 = 3;

	IO_ELA.EAWAXSTS.bit.BRESP_0 = 3;
	IO_ELA.EAWAXSTS.bit.BRESP_1 = 2;
	IO_ELA.EAWAXSTS.bit.BRESP_2 = 1;
	ctImEla2OffPclk(self);

	im_ela_get_axi_status(priv->imela, &each_axi);

	ctImEla2OnPclk(self);
	if(each_axi.axi_reply_r[0] != IO_ELA.EARAXSTS.bit.RRESP_0){
		Ddim_Print(("TEST NG : (RRESP_0) %d != %d\n", each_axi.axi_reply_r[0], IO_ELA.EARAXSTS.bit.RRESP_0));
		errF = 1;
	}
	if(each_axi.axi_reply_r[1] != IO_ELA.EARAXSTS.bit.RRESP_1){
		Ddim_Print(("TEST NG : (RRESP_1) %d != %d\n", each_axi.axi_reply_r[1], IO_ELA.EARAXSTS.bit.RRESP_1));
		errF = 1;
	}
	if(each_axi.axi_reply_r[2] != IO_ELA.EARAXSTS.bit.RRESP_2){
		Ddim_Print(("TEST NG : (RRESP_2) %d != %d\n", each_axi.axi_reply_r[2], IO_ELA.EARAXSTS.bit.RRESP_2));
		errF = 1;
	}
	if(each_axi.axi_reply_w[0] != IO_ELA.EAWAXSTS.bit.BRESP_0){
		Ddim_Print(("TEST NG : (BRESP_0) %d != %d\n", each_axi.axi_reply_w[0], IO_ELA.EAWAXSTS.bit.BRESP_0));
		errF = 1;
	}
	if(each_axi.axi_reply_w[1] != IO_ELA.EAWAXSTS.bit.BRESP_1){
		Ddim_Print(("TEST NG : (BRESP_1) %d != %d\n", each_axi.axi_reply_w[1], IO_ELA.EAWAXSTS.bit.BRESP_1));
		errF = 1;
	}
	if(each_axi.axi_reply_w[2] != IO_ELA.EAWAXSTS.bit.BRESP_2){
		Ddim_Print(("TEST NG : (BRESP_2) %d != %d\n", each_axi.axi_reply_w[2], IO_ELA.EAWAXSTS.bit.BRESP_2));
		errF = 1;
	}
	if(!errF){
		Ddim_Print(("TEST OK!\n"));
	}
	ctImEla2OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela2_1_21(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	kuint32 result;
	kuint32 i;
	kushort srcTbl[ImEla_D_IM_ELA_DEKNEE_TBL_MAX];

	Ddim_Print(("<%s>\n", __FUNCTION__));

	IO_ELA.ELATRG.bit.ELATRG = 0;
	im_ela_reg_open(priv->elareg, 100);

	for(i = 0; i < ImEla_D_IM_ELA_DEKNEE_TBL_MAX; i++){
		srcTbl[i]=i;
	}

	result = im_ela_reg_set_deknee_tbl(priv->elareg, &srcTbl[0], 0, ImEla_D_IM_ELA_DEKNEE_TBL_MAX);
	Ddim_Print(("Im_ELA_Set_Deknee_Tbl = %d\n", result));

	ctImEla2OnPclk(self);
	IO_ELA.ELABYR.bit.DKNACT = 1;
	for(i = 0; i < (ImEla_D_IM_ELA_DEKNEE_TBL_MAX / 2); i++){
		Ddim_Print(("DKNTBL[%03d] = 0x%08lx\n",i ,IO_ELA.DKNTBL.word[i]));
	}
	IO_ELA.ELABYR.bit.DKNACT = 0;
	ctImEla2OffPclk(self);

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela2_1_22(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	kuint32 i, j;
	kuint32 result;
	TImElaCurtailBayerData curtailBayer[ImElaReg_D_IM_ELA_STAGE_MAX];
	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		for(j = 0; j < ImElaReg_D_IM_ELA_STEP_MAX; j++){
			curtailBayer[i].bayer_addr[j] = 0x10000000 + (0x100 * i) + j;
		}
		curtailBayer[i].gl_hbyte = i + 100;
		curtailBayer[i].hsize = i + 200;
		curtailBayer[i].vline = i + 300;
	}

	result = im_ela_reg_set_curtail_bayer_data_tbl(priv->elareg, curtailBayer);
	Ddim_Print(("result=0x%08X\n", result));

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela2_1_23(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	kuint32 i, j;
	TImElaCurtailBayerData curtailBayer[ImElaReg_D_IM_ELA_STAGE_MAX];

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_reg_get_curtail_bayer_data_tbl(priv->elareg, curtailBayer);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		Ddim_Print(("(((Stage%d)))\n", i + 1));
		Ddim_Print(("gl_hbyte = %d\n",	curtailBayer[i].gl_hbyte));
		Ddim_Print(("hsize = %d\n",	curtailBayer[i].hsize));
		Ddim_Print(("vline = %d\n",	curtailBayer[i].vline));
		for(j = 0; j < ImElaReg_D_IM_ELA_STEP_MAX; j++){
			Ddim_Print(("(Sterp%02d)bayer_addr = 0x%08X\n", j, curtailBayer[i].bayer_addr[j]));
			ddim_user_custom_dly_tsk(10);
		}
	}

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela2_1_24(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	kuint32 i, j;
	kuint32 result;
	TImElaExtractNoiseData extractNoise[ImElaReg_D_IM_ELA_STAGE_MAX];

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		for(j = 0; j < ImElaReg_D_IM_ELA_STEP_MAX; j++){
			extractNoise[i].noise_data_addr[j] = 0x20000000 + (0x100 * i) + j;
		}
		extractNoise[i].gl_hbyte = i + 100;
		extractNoise[i].hsize    = i + 200;
		extractNoise[i].vline    = i + 300;
	}

	result = im_ela_reg_set_extract_noise_data_tbl(priv->elareg, extractNoise);
	Ddim_Print(("result=0x%08X\n", result));

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela2_1_25(CtImEla2 *self)
{
	CtImEla2Private *priv = CT_IM_ELA2_GET_PRIVATE(self);
	kuint32 i, j;
	TImElaExtractNoiseData extractNoise[ImElaReg_D_IM_ELA_STAGE_MAX];

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_reg_get_extract_noise_data_tbl(priv->elareg,extractNoise);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		Ddim_Print(("(((Stage%d)))\n", i + 1));
		Ddim_Print(("gl_hbyte = %d\n",	extractNoise[i].gl_hbyte));
		Ddim_Print(("hsize = %d\n",	extractNoise[i].hsize));
		Ddim_Print(("vline = %d\n",	extractNoise[i].vline));
		for(j = 0; j < ImElaReg_D_IM_ELA_STEP_MAX; j++){
			Ddim_Print(("(Sterp%02d)noise_data_addr = 0x%08X\n", j, extractNoise[i].noise_data_addr[j]));
			ddim_user_custom_dly_tsk(10);
		}
	}

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

CtImEla2* ct_im_ela2_new(void) 
{
    CtImEla2 *self = k_object_new_with_private(CT_TYPE_IM_ELA2, sizeof(CtImEla2Private));
    return self;
}
