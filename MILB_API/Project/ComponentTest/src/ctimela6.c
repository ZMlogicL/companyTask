/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla6类
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

K_TYPE_DEFINE_WITH_PRIVATE(CtImEla6, ct_im_ela6);
#define CT_IM_ELA6_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImEla6Private,CT_TYPE_IM_ELA6))

struct _CtImEla6Private
{
	kint32 result;
	kint32 imErcd;
	CtImEla *ela;
	ImElaReg* elareg;
	ImEla* imela;	
};

static void ct_im_ela6_constructor(CtImEla6 *self) 
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	priv->ela = ct_im_ela_new();
	priv->elareg = im_ela_reg_new();
	priv->imela = im_ela_get();		
}

static void ct_im_ela6_destructor(CtImEla6 *self) 
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
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

void ct_im_ela6_3_01(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = Im_ELA_Open(-2);

	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_02(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->imErcd = im_ela_reg_open(priv->elareg, 100);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("Open error = 0x%x\n", priv->imErcd));
		return ;
	}

	priv->imErcd = im_ela_reg_open(priv->elareg, 100);
	if(priv->imErcd != ImEla_D_IM_ELA_SEM_TIMEOUT_ERR){
		Ddim_Print(("result = 0x%x\n", priv->imErcd));
	}

	priv->imErcd = im_ela_reg_close(priv->elareg);
	if(priv->imErcd != D_DDIM_OK){
		Ddim_Print(("Close error = 0x%x\n", priv->imErcd));
		return ;
	}
}

void ct_im_ela6_3_03(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	DDIM_USER_ID sidBack; //TODO:调用文件还未改名

	Ddim_Print(("<%s>\n", __FUNCTION__));

	sidBack = SID_IM_ELA;//TODO:调用文件还未改名
	SID_IM_ELA = 0xfff;

	priv->imErcd = im_ela_reg_open(priv->elareg, 100);
	if(priv->imErcd != D_IM_ELA_SEM_NG){
		Ddim_Print(("Open error = 0x%x\n", priv->imErcd));
		return ;
	}

	SID_IM_ELA = sidBack;
}

void ct_im_ela6_3_04(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_ctrl(priv->imela, NULL);

	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_05(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	TImElaCtrl	ctrlEla = {0};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);

	ctrlEla.ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_MAX;

	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);

	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_06(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	TImElaCtrl ctrlEla = {0};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);

	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrlEla.ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_3;

	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_07(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	TImElaCtrl	ctrlEla = {0};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);

	Ddim_Print(("(1)\n"));
	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_3;

	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	Ddim_Print(("result=0x%08X\n", priv->result));

	Ddim_Print(("(2)\n"));
	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_4;

	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	Ddim_Print(("result=0x%08X\n", priv->result));

	return;
}

void ct_im_ela6_3_08(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_get_ctrl_common(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_09(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_get_ctrl_eirch(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_10(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_get_ctrl_eiwch(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_11(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_get_ctrl_enwch(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_12(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_get_ctrl_enrech(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_13(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_get_ctrl_enrach_enwmch(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_14(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_get_ctrl_core(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_15(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_get_ctrl_ob_correction(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_16(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_set_multiple_exec_info(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_17(CtImEla6 *self)
{
	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_set_deknee_lut_sleep(priv->elareg, 2);
	Ddim_Print(("<%s> END\n", __FUNCTION__));
}

void ct_im_ela6_3_18(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_get_nslmd(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_19(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_set_each(priv->imela, NULL);

	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_20(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_get_each(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_21(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_get_axi_status(priv->imela, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_22(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_reg_set_deknee_tbl(priv->elareg, NULL, 0, 256);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_23(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	USHORT src_tbl[256];

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_reg_set_deknee_tbl(priv->elareg, &src_tbl[0], 1, 256);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_24(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_reg_set_curtail_bayer_data_tbl(priv->elareg, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_25(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = Im_ELA_Get_Curtail_Bayer_Data_Tbl(priv->elareg, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_26(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);

	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_reg_set_extract_noise_data_tbl(priv->elareg, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_27(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	Ddim_Print(("<%s>\n", __FUNCTION__));

	priv->result = im_ela_reg_get_extract_noise_data_tbl(priv->elareg, NULL);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_28(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	Ddim_Print(("<%s>\n", __FUNCTION__));

#ifdef CO_DEBUG_ON_PC
	IO_ELA.ELATRG.bit.ELATRG = 3;
#endif	//CO_DEBUG_ON_PC
	// Processing is started synchronously
	priv->result = im_ela_reg_start_sync(priv->elareg);
	Ddim_Print(("im_ela_reg_start_sync : result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_29(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	Ddim_Print(("<%s>\n", __FUNCTION__));

#ifdef CO_DEBUG_ON_PC
	IO_ELA.ELATRG.bit.ELATRG = 3;
#endif	//CO_DEBUG_ON_PC
	// Processing is started asynchronously
	priv->result = im_ela_reg_start_async(priv->elareg);
	Ddim_Print(("Im_ELA_Start_Aync : result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_30(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	Ddim_Print(("<%s>\n", __FUNCTION__));

	// wait for the process to finish
	priv->result = im_ela_reg_wait_end(priv->elareg);
	Ddim_Print(("Im_ELA_Wait_End : result=0x%08X\n", priv->result));
}

void ct_im_ela6_3_31(CtImEla6 *self)
{
	CtImEla6Private *priv = CT_IM_ELA6_GET_PRIVATE(self);
	TImElaCtrl	ctrlEla = {0};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	IO_ELA.ELATRG.bit.ELATRG = 0;

	ct_im_ela_ctrl_set_test_data(priv->ela, &ctrlEla);

	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;	
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_1;

	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	Ddim_Print(("result=0x%08X\n", priv->result));

	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;	
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_2;

	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	Ddim_Print(("result=0x%08X\n", priv->result));

	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;	
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_3;

	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	Ddim_Print(("result=0x%08X\n", priv->result));

	ctrlEla.ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;	
	ctrlEla.ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_4;

	priv->result = im_ela_ctrl(priv->imela, &ctrlEla);
	Ddim_Print(("result=0x%08X\n", priv->result));
}

CtImEla6* ct_im_ela6_new(void) 
{
    CtImEla6 *self = k_object_new_with_private(CT_TYPE_IM_ELA6, sizeof(CtImEla6Private));
    return self;
}
