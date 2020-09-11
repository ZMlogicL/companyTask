/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla3类
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

K_TYPE_DEFINE_WITH_PRIVATE(CtImEla3, ct_im_ela3);
#define CT_IM_ELA3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImEla3Private,CT_TYPE_IM_ELA3))

struct _CtImEla3Private
{
	kint32 result;
	CtImEla *ela;
	ImElaCore *elacore;	
	ImEla* imela;	
};

static void ct_im_ela3_constructor(CtImEla3 *self) 
{
	CtImEla3Private *priv = CT_IM_ELA3_GET_PRIVATE(self);
	priv->ela = ct_im_ela_new();
	priv->elacore =  im_ela_core_new();	
	priv->imela = im_ela_get();	
}

static void ct_im_ela3_destructor(CtImEla3 *self) 
{
	CtImEla3Private *priv = CT_IM_ELA3_GET_PRIVATE(self);
	if(priv->ela){
		k_object_unref(priv->ela);
		priv->ela = NULL;
	}
	if(priv->elacore != NULL)
	{
		k_object_unref(priv->elacore);
		priv->elacore = NULL;			
	}	
}

void ct_im_ela3_2_01(CtImEla3 *self)
{
	CtImEla3Private *priv = CT_IM_ELA3_GET_PRIVATE(self);
	TImElaCtrl ctrlEla = {0};
	kuint32 i;
	TImElaCtrlCore core[ImElaReg_D_IM_ELA_STAGE_MAX] = {{0}};
	TImElaMultipleTimesInfo multipleExecInfo = {{0}};

#ifdef CT_IM_ELA_MSG_PRINT_ON
	Ddim_Print(("<<< ELA Register Initial value >>>\n"));
	ct_im_ela_reg_print(priv->ela);
	Ddim_Print(("\n"));
#endif

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_core_init(priv->elacore);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		multipleExecInfo.core[i]  = &core[i];
	}

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);
#ifdef CT_IM_ELA_MSG_PRINT_ON
	Ddim_Print(("TImElaCtrl Test Data Set OK\n"));
#endif

//	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 8896*2;
//	ctrlEla.ctrl_eirch.in_bayer_hsize = 8896;
//	ctrlEla.ctrl_eirch.in_bayer_vline = 4976;

	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 6048;
	ctrlEla.ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_12M_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_12M_LINES;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_0;

//	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_16BIT;
	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_REDUCTION;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_2;
	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;

	ctrlEla.ob_correction.ob_rr = 0x000;
	ctrlEla.ob_correction.ob_bb = 0x000;
	ctrlEla.ob_correction.ob_gr = 0x000;
	ctrlEla.ob_correction.ob_gb = 0x000;

	ctrlEla.ctrl_common.bayer_start_pixel_type = ImEla_D_IM_ELA_ORG_R;

	ct_im_ela_multiple_set_test_data(priv->ela, &multipleExecInfo);
	multipleExecInfo.core[0]->limit.noise_plus_limit = 0x0277;
	multipleExecInfo.core[0]->limit.noise_minus_limit = 0x0277;
	multipleExecInfo.core[0]->zero_point_level = 0x00C7;
	multipleExecInfo.core[0]->anb_r.offset[ImEla_E_IM_ELA_ANB_1] = 0x0058;
	multipleExecInfo.core[0]->anb_r.offset[ImEla_E_IM_ELA_ANB_2] = 0x0093;
	multipleExecInfo.core[0]->anb_r.offset[ImEla_E_IM_ELA_ANB_3] = 0x00c5;
	multipleExecInfo.core[0]->anb_r.offset[ImEla_E_IM_ELA_ANB_4] = 0x0103;
	multipleExecInfo.core[0]->anb_r.gain[ImEla_E_IM_ELA_ANB_1] = 0x0273;
	multipleExecInfo.core[0]->anb_r.gain[ImEla_E_IM_ELA_ANB_2] = 0x0215;
	multipleExecInfo.core[0]->anb_r.gain[ImEla_E_IM_ELA_ANB_3] = 0x0149;
	multipleExecInfo.core[0]->anb_r.gain[ImEla_E_IM_ELA_ANB_4] = 0x00f5;
	multipleExecInfo.core[0]->anb_r.boundary[ImEla_E_IM_ELA_ANB_1] = 0x0000;
	multipleExecInfo.core[0]->anb_r.boundary[ImEla_E_IM_ELA_ANB_2] = 0x0180;
	multipleExecInfo.core[0]->anb_r.boundary[ImEla_E_IM_ELA_ANB_3] = 0x0300;
	multipleExecInfo.core[0]->anb_r.boundary[ImEla_E_IM_ELA_ANB_4] = 0x0600;
	multipleExecInfo.core[0]->anb_g.offset[ImEla_E_IM_ELA_ANB_1] = 0x0058;
	multipleExecInfo.core[0]->anb_g.offset[ImEla_E_IM_ELA_ANB_2] = 0x0093;
	multipleExecInfo.core[0]->anb_g.offset[ImEla_E_IM_ELA_ANB_3] = 0x00c5;
	multipleExecInfo.core[0]->anb_g.offset[ImEla_E_IM_ELA_ANB_4] = 0x0103;
	multipleExecInfo.core[0]->anb_g.gain[ImEla_E_IM_ELA_ANB_1] = 0x0273;
	multipleExecInfo.core[0]->anb_g.gain[ImEla_E_IM_ELA_ANB_2] = 0x0215;
	multipleExecInfo.core[0]->anb_g.gain[ImEla_E_IM_ELA_ANB_3] = 0x0149;
	multipleExecInfo.core[0]->anb_g.gain[ImEla_E_IM_ELA_ANB_4] = 0x00f5;
	multipleExecInfo.core[0]->anb_g.boundary[ImEla_E_IM_ELA_ANB_1] = 0x0000;
	multipleExecInfo.core[0]->anb_g.boundary[ImEla_E_IM_ELA_ANB_2] = 0x0180;
	multipleExecInfo.core[0]->anb_g.boundary[ImEla_E_IM_ELA_ANB_3] = 0x0300;
	multipleExecInfo.core[0]->anb_g.boundary[ImEla_E_IM_ELA_ANB_4] = 0x0600;
	multipleExecInfo.core[0]->anb_b.offset[ImEla_E_IM_ELA_ANB_1] = 0x0058;
	multipleExecInfo.core[0]->anb_b.offset[ImEla_E_IM_ELA_ANB_2] = 0x0093;
	multipleExecInfo.core[0]->anb_b.offset[ImEla_E_IM_ELA_ANB_3] = 0x00c5;
	multipleExecInfo.core[0]->anb_b.offset[ImEla_E_IM_ELA_ANB_4] = 0x0103;
	multipleExecInfo.core[0]->anb_b.gain[ImEla_E_IM_ELA_ANB_1] = 0x0273;
	multipleExecInfo.core[0]->anb_b.gain[ImEla_E_IM_ELA_ANB_2] = 0x0215;
	multipleExecInfo.core[0]->anb_b.gain[ImEla_E_IM_ELA_ANB_3] = 0x0149;
	multipleExecInfo.core[0]->anb_b.gain[ImEla_E_IM_ELA_ANB_4] = 0x00f5;
	multipleExecInfo.core[0]->anb_b.boundary[ImEla_E_IM_ELA_ANB_1] = 0x0000;
	multipleExecInfo.core[0]->anb_b.boundary[ImEla_E_IM_ELA_ANB_2] = 0x0180;
	multipleExecInfo.core[0]->anb_b.boundary[ImEla_E_IM_ELA_ANB_3] = 0x0300;
	multipleExecInfo.core[0]->anb_b.boundary[ImEla_E_IM_ELA_ANB_4] = 0x0600;
	multipleExecInfo.core[0]->edge_adjust_a1 = 0x008a;
	multipleExecInfo.core[0]->edge_adjust_a2 = 0x0083;
	multipleExecInfo.core[0]->edge_adjust_b1 = 0x02fc;
	multipleExecInfo.core[0]->edge_adjust_b2 = 0x0033;
	multipleExecInfo.core[0]->edge_threshold[ImEla_E_IM_ELA_ALNGE_1] = 0x008e;
	multipleExecInfo.core[0]->edge_threshold[ImEla_E_IM_ELA_ALNGE_2] = 0x00d5;
	multipleExecInfo.core[0]->edge_threshold[ImEla_E_IM_ELA_ALNGE_3] = 0x011c;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L1E1N] = 0x00b4;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L1E2N] = 0x0082;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L1E3N] = 0x0000;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L2E1N] = 0x00a0;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L2E2N] = 0x0069;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L2E3N] = 0x0000;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L3E1N] = 0x008c;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L3E2N] = 0x0050;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L3E3N] = 0x0000;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L4E1N] = 0x0078;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L4E2N] = 0x003c;
	multipleExecInfo.core[0]->nr[ImEla_E_IM_ELA_ALNG_L4E3N] = 0x0000;
	multipleExecInfo.core[0]->l_noise = 0x00c8;
	multipleExecInfo.core[0]->l_edge[ImEla_E_IM_ELA_LCOMEN_1] = 0x008e;
	multipleExecInfo.core[0]->l_edge[ImEla_E_IM_ELA_LCOMEN_2] = 0x011c;
	multipleExecInfo.core[0]->l_intense[ImEla_E_IM_ELA_LCOMEN_1] = 0x0000;
	multipleExecInfo.core[0]->l_intense[ImEla_E_IM_ELA_LCOMEN_2] = 0x00cd;

#ifdef CT_IM_ELA_MSG_PRINT_ON
	Ddim_Print(("TImElaMultipleTimesInfo Test Data Set OK\n"));
#endif

	im_ela_core_init(priv->elacore);

	while(1){
		// Setting of ELA control parameter
		priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
		if(priv->result != D_DDIM_OK){
			// Error processing
			Ddim_Print(("E:im_ela_ctrl NG : result=%d.\n", priv->result));
			break;
		}
#ifdef CT_IM_ELA_MSG_PRINT_ON
		Ddim_Print(("im_ela_ctrl OK\n"));
#endif

		priv->result = im_ela_set_multiple_exec_info(priv->imela, &multipleExecInfo);
		if(priv->result != D_DDIM_OK){
			// Error processing
			Ddim_Print(("E:im_ela_set_multiple_exec_info NG : result=%d.\n", priv->result));
			break;
		}
#ifdef CT_IM_ELA_MSG_PRINT_ON
		Ddim_Print(("im_ela_set_multiple_exec_info OK\n"));
#endif

		// Processing is started synchronously
		priv->result = im_ela_reg_start_sync(priv->elareg);
		if(priv->result != D_DDIM_OK){
			// Error processing
			Ddim_Print(("E:im_ela_reg_start_sync NG : result=%d.\n", priv->result));
			break;
		}
#ifdef CT_IM_ELA_MSG_PRINT_ON
		Ddim_Print(("im_ela_reg_start_sync OK\n"));
#endif
		break;
	}

	ct_im_ela_clk_chk(priv->ela);

#ifdef CT_IM_ELA_MSG_PRINT_ON
	Ddim_Print(("<<< ELA Register >>>\n"));
	ct_im_ela_reg_print(priv->ela);
#endif
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela3_2_02(CtImEla3 *self)
{
	CtImEla3Private *priv = CT_IM_ELA3_GET_PRIVATE(self);
	TImElaCtrl ctrlEla = {0};
	TImElaCtrlCore core[ImElaReg_D_IM_ELA_STAGE_MAX] = {{0}};
	kuint32 i;
	TImElaMultipleTimesInfo multipleExecInfo = {{0}};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_core_init(priv->elacore);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		multipleExecInfo.core[i]  = &core[i];
	}

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);

	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 6672;
	ctrlEla.ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_4K2K_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_4K2K_LINES;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_0;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_1;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_REDUCTION;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;

	ctrlEla.ob_correction.ob_rr = 0x000;
	ctrlEla.ob_correction.ob_bb = 0x000;
	ctrlEla.ob_correction.ob_gr = 0x000;
	ctrlEla.ob_correction.ob_gb = 0x000;

	ctrlEla.ctrl_common.bayer_start_pixel_type = ImEla_D_IM_ELA_ORG_R;

	ct_im_ela_multiple_set_test_data(priv->ela, &multipleExecInfo);

	im_ela_core_init(priv->elacore);

	// Setting of ELA control parameter
	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_ctrl NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	priv->result = im_ela_set_multiple_exec_info(priv->imela, &multipleExecInfo);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_set_multiple_exec_info NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	// Processing is started synchronously
	priv->result = im_ela_reg_start_sync(priv->elareg);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_reg_start_sync NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela3_2_03(CtImEla3 *self)
{
	CtImEla3Private *priv = CT_IM_ELA3_GET_PRIVATE(self);
	TImElaCtrl	ctrlEla = {0};
	kuint32 i;
	TImElaCtrlCore	core[ImElaReg_D_IM_ELA_STAGE_MAX] = {{0}};
	TImElaMultipleTimesInfo multipleExecInfo = {{0}};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_core_init(priv->elacore);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		multipleExecInfo.core[i]  = &core[i];
	}

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);

/*
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 960;
	ctrlEla.ctrl_eirch.in_bayer_hsize = 640;
	ctrlEla.ctrl_eirch.in_bayer_vline = 480;
*/
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 6672;
	ctrlEla.ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_4K2K_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_4K2K_LINES;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_3;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_0;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_2;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_REDUCTION;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;

	ctrlEla.ob_correction.ob_rr = 0x000;
	ctrlEla.ob_correction.ob_bb = 0x000;
	ctrlEla.ob_correction.ob_gr = 0x000;
	ctrlEla.ob_correction.ob_gb = 0x000;

	ctrlEla.ctrl_common.bayer_start_pixel_type = ImEla_D_IM_ELA_ORG_R;

	ct_im_ela_multiple_set_test_data(priv->ela, &multipleExecInfo);

	im_ela_core_init(priv->elacore);

	// Setting of ELA control parameter
	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_ctrl NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	priv->result = im_ela_set_multiple_exec_info(priv->imela, &multipleExecInfo);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_set_multiple_exec_info NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	// Processing is started synchronously
	priv->result = im_ela_reg_start_sync(priv->elareg);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_reg_start_sync NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela3_2_04(CtImEla3 *self)
{
	CtImEla3Private *priv = CT_IM_ELA3_GET_PRIVATE(self);
	TImElaCtrl	ctrlEla = {0};
	kuint32 i;
	TImElaCtrlCore	core[ImElaReg_D_IM_ELA_STAGE_MAX] = {{0}};
	TImElaMultipleTimesInfo multipleExecInfo = {{0}};

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		multipleExecInfo.core[i]  = &core[i];
	}

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_core_init(priv->elacore);

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);
/*
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 960;
	ctrlEla.ctrl_eirch.in_bayer_hsize = 640;
	ctrlEla.ctrl_eirch.in_bayer_vline = 480;
*/
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 6672;
	ctrlEla.ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_4K2K_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_4K2K_LINES;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_4;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_0;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_3;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_REDUCTION;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;

	ctrlEla.ob_correction.ob_rr = 0x000;
	ctrlEla.ob_correction.ob_bb = 0x000;
	ctrlEla.ob_correction.ob_gr = 0x000;
	ctrlEla.ob_correction.ob_gb = 0x000;

	ctrlEla.ctrl_common.bayer_start_pixel_type = ImEla_D_IM_ELA_ORG_R;

	ct_im_ela_multiple_set_test_data(priv->ela, &multipleExecInfo);

	im_ela_core_init(priv->elacore);

	// Setting of ELA control parameter
	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_ctrl NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	priv->result = im_ela_set_multiple_exec_info(priv->imela, &multipleExecInfo);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_set_multiple_exec_info NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	// Processing is started synchronously
	priv->result = im_ela_reg_start_sync(priv->elareg);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_reg_start_sync NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela3_2_05(CtImEla3 *self)
{
	CtImEla3Private *priv = CT_IM_ELA3_GET_PRIVATE(self);
	TImElaCtrl	ctrlEla = {0};
	kuint32 i;
	TImElaCtrlCore	core[ImElaReg_D_IM_ELA_STAGE_MAX] = {{0}};
	TImElaMultipleTimesInfo multipleExecInfo = {{0}};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_core_init(priv->elacore);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		multipleExecInfo.core[i]  = &core[i];
	}

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);

/*
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 960;
	ctrlEla.ctrl_eirch.in_bayer_hsize = 640;
	ctrlEla.ctrl_eirch.in_bayer_vline = 480;
*/
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 6672;
	ctrlEla.ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_4K2K_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_4K2K_LINES;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_5;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_0;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_3;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_5] = ImEla_E_IM_ELA_DENSITY_MODE_3;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_REDUCTION;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;

	ctrlEla.ob_correction.ob_rr = 0x000;
	ctrlEla.ob_correction.ob_bb = 0x000;
	ctrlEla.ob_correction.ob_gr = 0x000;
	ctrlEla.ob_correction.ob_gb = 0x000;

	ctrlEla.ctrl_common.bayer_start_pixel_type = ImEla_D_IM_ELA_ORG_R;

	ct_im_ela_multiple_set_test_data(priv->ela, &multipleExecInfo);

	im_ela_core_init(priv->elacore);

	// Setting of ELA control parameter
	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_ctrl NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	priv->result = im_ela_set_multiple_exec_info(priv->imela, &multipleExecInfo);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_set_multiple_exec_info NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	// Processing is started synchronously
	priv->result = im_ela_reg_start_sync(priv->elareg);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_reg_start_sync NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela3_2_06(CtImEla3 *self)
{
	CtImEla3Private *priv = CT_IM_ELA3_GET_PRIVATE(self);
	TImElaCtrl ctrlEla = {0};
	kuint32 i;
	TImElaCtrlCore core[ImElaReg_D_IM_ELA_STAGE_MAX] = {{0}};
	TImElaMultipleTimesInfo multipleExecInfo = {{0}};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_core_init(priv->elacore);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		multipleExecInfo.core[i]  = &core[i];
	}

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);

/*
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 960;
	ctrlEla.ctrl_eirch.in_bayer_hsize = 640;
	ctrlEla.ctrl_eirch.in_bayer_vline = 480;
*/

	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 6672;
	ctrlEla.ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_4K2K_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_4K2K_LINES;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_5;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_0;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_0;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_0;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_0;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_5] = ImEla_E_IM_ELA_DENSITY_MODE_0;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_REDUCTION;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;

	ctrlEla.ob_correction.ob_rr = 0x000;
	ctrlEla.ob_correction.ob_bb = 0x000;
	ctrlEla.ob_correction.ob_gr = 0x000;
	ctrlEla.ob_correction.ob_gb = 0x000;

	ctrlEla.ctrl_common.bayer_start_pixel_type = ImEla_D_IM_ELA_ORG_R;

	ct_im_ela_multiple_set_test_data(priv->ela, &multipleExecInfo);

	im_ela_core_init(priv->elacore);

	// Setting of ELA control parameter
	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_ctrl NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	priv->result = im_ela_set_multiple_exec_info(priv->imela, &multipleExecInfo);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_set_multiple_exec_info NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	// Processing is started synchronously
	priv->result = im_ela_reg_start_sync(priv->elareg);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_reg_start_sync NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela3_2_07(CtImEla3 *self)
{
	CtImEla3Private *priv = CT_IM_ELA3_GET_PRIVATE(self);
	TImElaCtrl ctrlEla = {0};
	kuint32 i;
	TImElaCtrlCore core[ImElaReg_D_IM_ELA_STAGE_MAX] = {{0}};
	TImElaMultipleTimesInfo multipleExecInfo = {{0}};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_core_init(priv->elacore);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		multipleExecInfo.core[i] = &core[i];
	}

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);

/*
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 960;
	ctrlEla.ctrl_eirch.in_bayer_hsize = 640;
	ctrlEla.ctrl_eirch.in_bayer_vline = 480;
*/
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 6672;
	ctrlEla.ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_4K2K_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_4K2K_LINES;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_5;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_0;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_0;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_5] = ImEla_E_IM_ELA_DENSITY_MODE_1;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_REDUCTION;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;

	ctrlEla.ob_correction.ob_rr = 0x000;
	ctrlEla.ob_correction.ob_bb = 0x000;
	ctrlEla.ob_correction.ob_gr = 0x000;
	ctrlEla.ob_correction.ob_gb = 0x000;

	ctrlEla.ctrl_common.bayer_start_pixel_type = ImEla_D_IM_ELA_ORG_R;

	ct_im_ela_multiple_set_test_data(priv->ela, &multipleExecInfo);

	im_ela_core_init(priv->elacore);

	// Setting of ELA control parameter
	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_ctrl NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	priv->result = im_ela_set_multiple_exec_info(priv->imela, &multipleExecInfo);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_set_multiple_exec_info NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	// Processing is started synchronously
	priv->result = im_ela_reg_start_sync(priv->elareg);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_reg_start_sync NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela3_2_08(CtImEla3 *self)
{
	CtImEla3Private *priv = CT_IM_ELA3_GET_PRIVATE(self);
	TImElaCtrl ctrlEla = {0};
	kuint32 i;
	TImElaCtrlCore core[ImElaReg_D_IM_ELA_STAGE_MAX] = {{0}};
	TImElaMultipleTimesInfo multipleExecInfo = {{0}};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_core_init(priv->elacore);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		multipleExecInfo.core[i] = &core[i];
	}

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);

/*
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 960;
	ctrlEla.ctrl_eirch.in_bayer_hsize = 640;
	ctrlEla.ctrl_eirch.in_bayer_vline = 480;
*/
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 6672;
	ctrlEla.ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_4K2K_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_4K2K_LINES;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_SAME;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_2;
	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;

	ctrlEla.ob_correction.ob_rr = 0x000;
	ctrlEla.ob_correction.ob_bb = 0x000;
	ctrlEla.ob_correction.ob_gr = 0x000;
	ctrlEla.ob_correction.ob_gb = 0x000;

	ctrlEla.ctrl_common.bayer_start_pixel_type = ImEla_D_IM_ELA_ORG_R;

	ct_im_ela_multiple_set_test_data(priv->ela, &multipleExecInfo);

	im_ela_core_init(priv->elacore);

	while(1){
		// Setting of ELA control parameter
		priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
		if(priv->result != D_DDIM_OK){
			// Error processing
			Ddim_Print(("E:im_ela_ctrl NG : result=%d.\n", priv->result));
			break;
		}
#ifdef CT_IM_ELA_MSG_PRINT_ON
		Ddim_Print(("im_ela_ctrl OK\n"));
#endif

		priv->result = im_ela_set_multiple_exec_info(priv->imela, &multipleExecInfo);
		if(priv->result != D_DDIM_OK){
			// Error processing
			Ddim_Print(("E:im_ela_set_multiple_exec_info NG : result=%d.\n", priv->result));
			break;
		}
#ifdef CT_IM_ELA_MSG_PRINT_ON
		Ddim_Print(("im_ela_set_multiple_exec_info OK\n"));
#endif

		// Processing is started synchronously
		priv->result = im_ela_reg_start_sync(priv->elareg);
		if(priv->result != D_DDIM_OK){
			// Error processing
			Ddim_Print(("E:im_ela_reg_start_sync NG : result=%d.\n", priv->result));
			break;
		}
#ifdef CT_IM_ELA_MSG_PRINT_ON
		Ddim_Print(("im_ela_reg_start_sync OK\n"));
#endif
		break;
	}

	ct_im_ela_clk_chk(priv->ela);

#ifdef CT_IM_ELA_MSG_PRINT_ON
	Ddim_Print(("<<< ELA Register >>>\n"));
	ct_im_ela_reg_print(priv->ela);
#endif
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela3_2_08_a(CtImEla3 *self)
{
	CtImEla3Private *priv = CT_IM_ELA3_GET_PRIVATE(self);
	TImElaCtrl ctrlEla = {0};
	kuint32 i;
	TImElaCtrlCore core[ImElaReg_D_IM_ELA_STAGE_MAX] = {{0}};
	TImElaMultipleTimesInfo multipleExecInfo = {{0}};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_core_init(priv->elacore);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		multipleExecInfo.core[i] = &core[i];
	}

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);

	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 4224;
	ctrlEla.ctrl_eirch.in_bayer_hsize = 2796;
	ctrlEla.ctrl_eirch.in_bayer_vline = 1560;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_SAME;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_2;
	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_DISABLE;

	ctrlEla.ob_correction.ob_rr = 0x000;
	ctrlEla.ob_correction.ob_bb = 0x000;
	ctrlEla.ob_correction.ob_gr = 0x000;
	ctrlEla.ob_correction.ob_gb = 0x000;

	ctrlEla.ctrl_common.bayer_start_pixel_type = ImEla_D_IM_ELA_ORG_R;

	ct_im_ela_multiple_set_test_data(priv->ela, &multipleExecInfo);

	im_ela_core_init(priv->elacore);

	// Setting of ELA control parameter
	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_ctrl NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	priv->result = im_ela_set_multiple_exec_info(priv->imela, &multipleExecInfo);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_set_multiple_exec_info NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	// Processing is started synchronously
	priv->result = im_ela_reg_start_sync(priv->elareg);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_reg_start_sync NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	ct_im_ela_clk_chk(priv->ela);

#ifdef CT_IM_ELA_MSG_PRINT_ON
	Ddim_Print(("<<< ELA Register >>>\n"));
	ct_im_ela_reg_print(priv->ela);
#endif
	im_ela_reg_close(priv->elareg);
}

CtImEla3* ct_im_ela3_new(void) 
{
    CtImEla3 *self = k_object_new_with_private(CT_TYPE_IM_ELA3, sizeof(CtImEla3Private));
    return self;
}
