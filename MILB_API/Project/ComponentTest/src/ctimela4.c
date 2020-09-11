/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla4类
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

K_TYPE_DEFINE_WITH_PRIVATE(CtImEla4, ct_im_ela4);
#define CT_IM_ELA4_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImEla4Private,CT_TYPE_IM_ELA4))

struct _CtImEla4Private
{
	kint32 result;
	CtImEla *ela;
	ImElaReg* elareg;
	ImElaCore *elacore;	
	ImEla* imela;	
};

static void ct_im_ela4_constructor(CtImEla4 *self) 
{
	CtImEla4Private *priv = CT_IM_ELA4_GET_PRIVATE(self);
	priv->ela = ct_im_ela_new();
	priv->elareg = im_ela_reg_new();
	priv->elacore =  im_ela_core_new();	
	priv->imela = im_ela_get();		
}

static void ct_im_ela4_destructor(CtImEla4 *self) 
{
	CtImEla4Private *priv = CT_IM_ELA4_GET_PRIVATE(self);
	if(priv->ela){
		k_object_unref(priv->ela);
		priv->ela = NULL;
	}
	if(priv->elareg != NULL)
	{
		k_object_unref(priv->elareg);
		priv->elareg = NULL;			
	}
	if(priv->elacore != NULL)
	{
		k_object_unref(priv->elacore);
		priv->elacore = NULL;			
	}	
}

void ct_im_ela4_2_09(CtImEla4 *self)
{
	CtImEla4Private *priv = CT_IM_ELA4_GET_PRIVATE(self);
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

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_2;

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

void ct_im_ela4_2_10(CtImEla4 *self)
{
	CtImEla4Private *priv = CT_IM_ELA4_GET_PRIVATE(self);
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

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_3;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_3;

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

void ct_im_ela4_2_11(CtImEla4 *self)
{
	CtImEla4Private *priv = CT_IM_ELA4_GET_PRIVATE(self);
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

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_4;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_3;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_3;

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

void ct_im_ela4_2_12(CtImEla4 *self)
{
	CtImEla4Private *priv = CT_IM_ELA4_GET_PRIVATE(self);
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
	ctrlEla.next_ctrl_flag = ImEla_D_IM_ELA_DISABLE;
#ifdef CT_IM_ELA_MSG_PRINT_ON
	Ddim_Print(("TImElaCtrl Test Data Set OK\n"));
#endif

//	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 6656;
//	ctrlEla.ctrl_eirch.in_bayer_hsize = 4424;
//	ctrlEla.ctrl_eirch.in_bayer_vline = 2488;

	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 6672;
	ctrlEla.ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_4K2K_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_4K2K_LINES;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_5;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_3;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_3;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_5] = ImEla_E_IM_ELA_DENSITY_MODE_3;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_SAME;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;
	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;

	ctrlEla.ob_correction.ob_rr = 0x000;
	ctrlEla.ob_correction.ob_bb = 0x000;
	ctrlEla.ob_correction.ob_gr = 0x000;
	ctrlEla.ob_correction.ob_gb = 0x000;

	ctrlEla.ctrl_common.bayer_start_pixel_type = ImEla_D_IM_ELA_ORG_R;

	ct_im_ela_multiple_set_test_data(priv->ela, &multipleExecInfo);
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
//	im_ela_core_stop(priv->elacore);

	ct_im_ela_clk_chk(priv->ela);

#ifdef CT_IM_ELA_MSG_PRINT_ON
	Ddim_Print(("<<< ELA Register >>>\n"));
	ct_im_ela_reg_print(priv->ela);
#endif
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela4_2_13(CtImEla4 *self)
{
	CtImEla4Private *priv = CT_IM_ELA4_GET_PRIVATE(self);
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
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_5] = ImEla_E_IM_ELA_DENSITY_MODE_1;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_SAME;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;
	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;

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

void ct_im_ela4_2_14(CtImEla4 *self)
{
	CtImEla4Private *priv = CT_IM_ELA4_GET_PRIVATE(self);
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
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_3;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_5] = ImEla_E_IM_ELA_DENSITY_MODE_3;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_SAME;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;
	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;

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

void ct_im_ela4_2_15(CtImEla4 *self)
{
	CtImEla4Private *priv = CT_IM_ELA4_GET_PRIVATE(self);
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

	ctrlEla.next_ctrl_flag = ImEla_D_IM_ELA_ENABLE;

/*
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 960;
	ctrlEla.ctrl_eirch.in_bayer_hsize = 640;
	ctrlEla.ctrl_eirch.in_bayer_vline = 480;
*/
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 6672;
	ctrlEla.ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_4K2K_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_4K2K_LINES;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_2;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_SAME;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;
	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;

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
		Ddim_Print(("E:im_ela_reg_start_sync NG(1) : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	// Setting of ELA control parameter
	// The last ELA macro processing
	priv->result = im_ela_core_ctrl_next(priv->elacore);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:Im_ELA_Ctrl_Next NG : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	// Processing is started synchronously
	priv->result = im_ela_reg_start_sync(priv->elareg);
	if(priv->result != D_DDIM_OK){
		// Error processing
		Ddim_Print(("E:im_ela_reg_start_sync NG(2) : result=%d.\n", priv->result));
		im_ela_reg_close(priv->elareg);
		return;
	}

	ct_im_ela_clk_chk(priv->ela);
	im_ela_reg_close(priv->elareg);
}

void ct_im_ela4_2_16(CtImEla4 *self)
{
	CtImEla4Private *priv = CT_IM_ELA4_GET_PRIVATE(self);
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
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = 640;
	ctrlEla.ctrl_eirch.in_bayer_hsize = 640;
	ctrlEla.ctrl_eirch.in_bayer_vline = 480;
*/
	ctrlEla.ctrl_eirch.in_bayer_total_hsize = CtImEla_S_ELA_BAYER_4K2K_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_4K2K_WIDTH;
	ctrlEla.ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_4K2K_LINES;

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_5;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_2;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_3;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_3;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_5] = ImEla_E_IM_ELA_DENSITY_MODE_3;

	ctrlEla.ctrl_byr.in_data_type  = ImEla_D_IM_ELA_DATATYP_8BIT;
	ctrlEla.ctrl_byr.in_data_shift_mode  = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrlEla.ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_8BIT;
	ctrlEla.ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;

	ctrlEla.ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_SAME;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;
	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;

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

CtImEla4* ct_im_ela4_new(void) 
{
    CtImEla4 *self = k_object_new_with_private(CT_TYPE_IM_ELA4, sizeof(CtImEla4Private));
    return self;
}
