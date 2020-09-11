/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro12
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsenslvs.h"
#include "ctimpro12.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro12, ct_im_pro1_2)
#define CT_IM_PRO1_2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro12Private, CT_TYPE_IM_PRO1_2))


struct _CtImPro12Private
{
	ImproSenslvs *improSenslvs;
	ImPro12Print *imPro12Print;
	kint32 ercd;
};


/**********
 * IMPL
 */
static void ct_im_pro1_2_constructor(CtImPro12 *self)
{
	self->priv = CT_IM_PRO1_2_GET_PRIVATE(self);
	self->priv->improSenslvs = impro_senslvs_new();
	self->priv->imPro12Print = im_pro_1_2_print_new();
	self->priv->ercd = 0;
}

static void ct_im_pro1_2_destructor(CtImPro12 *self)
{
	CtImPro12Private *priv = CT_IM_PRO1_2_GET_PRIVATE(self);

	if (priv->improSenslvs) {
		k_object_unref(priv->improSenslvs);
		priv->improSenslvs = NULL;
	}

	if (priv->imPro12Print) {
		k_object_unref(priv->imPro12Print);
		priv->imPro12Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro1_2_0(CtImPro12* self, const kuint32 idx)
{
    TimproSlvsPmaInit pmaInitMax = {
        .invertSel.lane0 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_INVERT,
        .invertSel.lane1 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_INVERT,
        .invertSel.lane2 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_INVERT,
        .invertSel.lane3 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_INVERT,
        .invertSel.lane4 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_INVERT,
        .invertSel.lane5 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_INVERT,
        .invertSel.lane6 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_INVERT,
        .invertSel.lane7 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_INVERT,
        .multiplicationFactor = ImproSenslvs_E_IM_PRO_SLVS_MULTIPLICATION_FACTOR_RESERVED,
        .optInitParam.enabled = 1,
        .optInitParam.refsel  = 1,
        .optInitParam.icpcode = 0xF,
    };

    TimproSlvsPmaInit pmaInitMin = {
        .invertSel.lane0 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL,
        .invertSel.lane1 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL,
        .invertSel.lane2 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL,
        .invertSel.lane3 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL,
        .invertSel.lane4 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL,
        .invertSel.lane5 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL,
        .invertSel.lane6 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL,
        .invertSel.lane7 = ImproSenslvs_E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL,
        .multiplicationFactor = ImproSenslvs_E_IM_PRO_SLVS_MULTIPLICATION_FACTOR_REF_CLK_72MHZ,
        .optInitParam.enabled = 0,
        .optInitParam.refsel = 0,
        .optInitParam.icpcode = 0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senslvs_pma_init() PHYCR0  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.common.PHYCR0.word, ioPro.sen.slvsec.common.PHYCR0.word));
//        Ddim_Print(("impro_senslvs_pma_init() PHYCR1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.common.PHYCR1.word, ioPro.sen.slvsec.common.PHYCR1.word));
//        Ddim_Print(("impro_senslvs_pma_init() PHYCR2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.common.PHYCR2.word, ioPro.sen.slvsec.common.PHYCR2.word));

// Maximum value parameter
		self->priv->ercd = impro_senslvs_pma_init(self->priv->improSenslvs, &pmaInitMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_pma_init() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_0(self->priv->imPro12Print, "max_para", &pmaInitMax);
		}

		// Minimum value parameter
		self->priv->ercd = impro_senslvs_pma_init(self->priv->improSenslvs, &pmaInitMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_pma_init() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_0(self->priv->imPro12Print, "min_para", &pmaInitMin);
		}
    }
}

void ct_im_pro1_2_1(CtImPro12* self, const kuint32 idx)
{
    TimproSlvsPmaPd pmaPdMax = {
        .lane0PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_NORMAL,
        .lane1PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_NORMAL,
        .lane2PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_NORMAL,
        .lane3PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_NORMAL,
        .lane4PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_NORMAL,
        .lane5PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_NORMAL,
        .lane6PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_NORMAL,
        .lane7PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_NORMAL,
    };

    TimproSlvsPmaPd pmaPdMin = {
        .lane0PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_POWER_DOWN,
        .lane1PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_POWER_DOWN,
        .lane2PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_POWER_DOWN,
        .lane3PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_POWER_DOWN,
        .lane4PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_POWER_DOWN,
        .lane5PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_POWER_DOWN,
        .lane6PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_POWER_DOWN,
        .lane7PdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_POWER_DOWN,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senslvs_pma_power_down() PHYCR2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.common.PHYCR2.word, ioPro.sen.slvsec.common.PHYCR2.word));

// Maximum value parameter
		self->priv->ercd = impro_senslvs_pma_power_down(self->priv->improSenslvs, &pmaPdMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senslvs_pma_power_down() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_1(self->priv->imPro12Print, "max_para", &pmaPdMax);
		}

		// Minimum value parameter
		self->priv->ercd = impro_senslvs_pma_power_down(self->priv->improSenslvs, &pmaPdMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_senslvs_pma_power_down() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_1(self->priv->imPro12Print, "min_para", &pmaPdMin);
		}
    }
}

void ct_im_pro1_2_2(CtImPro12* self, const kuint32 idx)
{
    TimproSlvsCommonCfg commonCfgMax = {
        .standbyLength = 0xFF,
        .standbySymbolType = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_K_CODE,
        .standbySymbol = 0xFF,
        .deskewInterval = 0xFF,
        .deskewLength = 0xFF,
        .deskewSymbolType = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_K_CODE,
        .deskewSymbol = 0xFF,
        .idleSymbolType1 = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_K_CODE,
        .idleSymbol1 = 0xFF,
        .idleSymbolType0 = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_K_CODE,
        .idleSymbol0 = 0xFF,
        .idleSymbolType3 = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_K_CODE,
        .idleSymbol3 = 0xFF,
        .idleSymbolType2 = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_K_CODE,
        .idleSymbol2 = 0xFF,
    };

    TimproSlvsCommonCfg commonCfgMin = {
        .standbyLength = 18,
        .standbySymbolType = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_DATA,
        .standbySymbol = 0,
        .deskewInterval = 20,
        .deskewLength = 3,
        .deskewSymbolType = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_DATA,
        .deskewSymbol = 0,
        .idleSymbolType1 = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_DATA,
        .idleSymbol1 = 0,
        .idleSymbolType0 = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_DATA,
        .idleSymbol0 = 0,
        .idleSymbolType3 = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_DATA,
        .idleSymbol3 = 0,
        .idleSymbolType2 = ImproSenslvs_E_IM_PRO_SLVS_SYMBOL_TYPE_DATA,
        .idleSymbol2 = 0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senslvs_common_cfg() ATTR1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.common.ATTR1.word, ioPro.sen.slvsec.common.ATTR1.word));
//        Ddim_Print(("impro_senslvs_common_cfg() ATTR2  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.common.ATTR2.word, ioPro.sen.slvsec.common.ATTR2.word));
//        Ddim_Print(("impro_senslvs_common_cfg() ATTR3  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.common.ATTR3.word, ioPro.sen.slvsec.common.ATTR3.word));
//        Ddim_Print(("impro_senslvs_common_cfg() ATTR4  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.common.ATTR4.word, ioPro.sen.slvsec.common.ATTR4.word));

// Maximum value parameter
		self->priv->ercd = impro_senslvs_common_cfg(self->priv->improSenslvs, &commonCfgMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_common_cfg() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_2(self->priv->imPro12Print, "max_para", &commonCfgMax);
		}

		// Minimum value parameter
		self->priv->ercd = impro_senslvs_common_cfg(self->priv->improSenslvs, &commonCfgMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_common_cfg() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_2(self->priv->imPro12Print, "min_para", &commonCfgMin);
		}
    }
}

void ct_im_pro1_2_3(CtImPro12* self, const kuint32 idx)
{
    E_IM_PRO_SLVS_STREAM_TYPE streamType;//TODO
    TimproSlvsCtrl slvsCtrlMax = {
        .ramPdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_NORMAL,
        .vdoutCtrl = ImproSenslvs_E_IM_PRO_SLVS_VDOUT_CTRL_OUTPUT,
        .ecccrcOpt = ImproSenslvs_E_IM_PRO_SLVS_ECCCRC_OPT_W_ECC_4BYTE_PARITY,
        .expectVal = ImproSenslvs_E_IM_PRO_SLVS_EXPECT_VAL_H_1FFF,
    };

    TimproSlvsCtrl slvsCtrlMin = {
        .ramPdState = ImproSenslvs_E_IM_PRO_SLVS_PD_STATE_POWER_DOWN,
        .vdoutCtrl = ImproSenslvs_E_IM_PRO_SLVS_VDOUT_CTRL_NO_OUTPUT,
        .ecccrcOpt = ImproSenslvs_E_IM_PRO_SLVS_ECCCRC_OPT_WO_ECC_CRC,
        .expectVal = ImproSenslvs_E_IM_PRO_SLVS_EXPECT_VAL_H_0000,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senslvs_ctrl(0) RAMPD  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].RAMPD.word, ioPro.sen.slvsec.stream[0].RAMPD.word));
//        Ddim_Print(("impro_senslvs_ctrl(0) trgr   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].trgr.word,  ioPro.sen.slvsec.stream[0].trgr.word ));
//        Ddim_Print(("impro_senslvs_ctrl(0) CFGR0  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].CFGR0.word, ioPro.sen.slvsec.stream[0].CFGR0.word));
//        Ddim_Print(("impro_senslvs_ctrl(0) MMODE  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].MMODE.word, ioPro.sen.slvsec.stream[0].MMODE.word));
//        Ddim_Print(("impro_senslvs_ctrl(1) RAMPD  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].RAMPD.word, ioPro.sen.slvsec.stream[1].RAMPD.word));
//        Ddim_Print(("impro_senslvs_ctrl(1) trgr   (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].trgr.word,  ioPro.sen.slvsec.stream[1].trgr.word ));
//        Ddim_Print(("impro_senslvs_ctrl(1) CFGR0  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].CFGR0.word, ioPro.sen.slvsec.stream[1].CFGR0.word));
//        Ddim_Print(("impro_senslvs_ctrl(1) MMODE  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].MMODE.word, ioPro.sen.slvsec.stream[1].MMODE.word));

// Maximum value parameter
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_BOTH;//TODO
		self->priv->ercd = impro_senslvs_ctrl(self->priv->improSenslvs, streamType, &slvsCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_3(self->priv->imPro12Print, "max_para", streamType, &slvsCtrlMax);
		}

		// Minimum value parameter
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_A;
		self->priv->ercd = impro_senslvs_ctrl(self->priv->improSenslvs, streamType, &slvsCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_3(self->priv->imPro12Print, "min_para", streamType, &slvsCtrlMin);
		}
    }
}

void ct_im_pro1_2_4(CtImPro12* self, const kuint32 idx)
{
    E_IM_PRO_SLVS_STREAM_TYPE streamType;//TODO
    TimproSlvsModeCfg modeCtrlMax = {
        .pixelbit = ImproSenslvs_E_IM_PRO_SLVS_PIXEL_BIT_16BIT,
        .lanenum = ImproSenslvs_E_IM_PRO_SLVS_LANE_NUM_8LANE,
        .linelength = 0xFFFF,
        .outputFormat = ImproSenslvs_E_IM_PRO_SLVS_OUT_FORMAT_8POINT,
        .swapLane[0] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_7,
        .swapLane[1] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_7,
        .swapLane[2] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_7,
        .swapLane[3] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_7,
        .swapLane[4] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_7,
        .swapLane[5] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_7,
        .swapLane[6] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_7,
        .swapLane[7] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_7,
        .validLane.lane0 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_EN,
        .validLane.lane1 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_EN,
        .validLane.lane2 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_EN,
        .validLane.lane3 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_EN,
        .validLane.lane4 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_EN,
        .validLane.lane5 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_EN,
        .validLane.lane6 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_EN,
        .validLane.lane7 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_EN,
    };

    TimproSlvsModeCfg modeCtrlMin = {
        .pixelbit = ImproSenslvs_E_IM_PRO_SLVS_PIXEL_BIT_8BIT,
        .lanenum = ImproSenslvs_E_IM_PRO_SLVS_LANE_NUM_1LANE,
        .linelength = 0,
        .outputFormat = ImproSenslvs_E_IM_PRO_SLVS_OUT_FORMAT_1POINT,
        .swapLane[0] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_0,
        .swapLane[1] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_0,
        .swapLane[2] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_0,
        .swapLane[3] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_0,
        .swapLane[4] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_0,
        .swapLane[5] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_0,
        .swapLane[6] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_0,
        .swapLane[7] = ImproSenslvs_E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_0,
        .validLane.lane0 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_DIS,
        .validLane.lane1 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_DIS,
        .validLane.lane2 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_DIS,
        .validLane.lane3 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_DIS,
        .validLane.lane4 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_DIS,
        .validLane.lane5 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_DIS,
        .validLane.lane6 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_DIS,
        .validLane.lane7 = ImproSenslvs_E_IM_PRO_SLVS_LANE_ENABLE_DIS,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senslvs_mode_cfg(0) CFGR0  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].CFGR0.word, ioPro.sen.slvsec.stream[0].CFGR0.word));
//        Ddim_Print(("impro_senslvs_mode_cfg(0) CFGR1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].CFGR1.word, ioPro.sen.slvsec.stream[0].CFGR1.word));
//        Ddim_Print(("impro_senslvs_mode_cfg(0) OUTMD  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].OUTMD.word, ioPro.sen.slvsec.stream[0].OUTMD.word));
//        Ddim_Print(("impro_senslvs_mode_cfg(0) LSWAP  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].LSWAP.word, ioPro.sen.slvsec.stream[0].LSWAP.word));
//        Ddim_Print(("impro_senslvs_mode_cfg(0) VLANE  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].VLANE.word, ioPro.sen.slvsec.stream[0].VLANE.word));
//        Ddim_Print(("impro_senslvs_mode_cfg(1) CFGR0  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].CFGR0.word, ioPro.sen.slvsec.stream[1].CFGR0.word));
//        Ddim_Print(("impro_senslvs_mode_cfg(1) CFGR1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].CFGR1.word, ioPro.sen.slvsec.stream[1].CFGR1.word));
//        Ddim_Print(("impro_senslvs_mode_cfg(1) OUTMD  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].OUTMD.word, ioPro.sen.slvsec.stream[1].OUTMD.word));
//        Ddim_Print(("impro_senslvs_mode_cfg(1) LSWAP  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].LSWAP.word, ioPro.sen.slvsec.stream[1].LSWAP.word));
//        Ddim_Print(("impro_senslvs_mode_cfg(1) VLANE  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].VLANE.word, ioPro.sen.slvsec.stream[1].VLANE.word));
		// Maximum value parameter
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_BOTH;//TODO
		self->priv->ercd = impro_senslvs_mode_cfg(self->priv->improSenslvs, streamType, &modeCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_mode_cfg() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_4(self->priv->imPro12Print, "max_para", streamType, &modeCtrlMax);
		}

		// Minimum value parameter
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_A;
		self->priv->ercd = impro_senslvs_mode_cfg(self->priv->improSenslvs, streamType, &modeCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_mode_cfg() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_4(self->priv->imPro12Print, "min_para", streamType, &modeCtrlMin);
		}
    }
}

void ct_im_pro1_2_5(CtImPro12* self, const kuint32 idx)
{
    E_IM_PRO_SLVS_STREAM_TYPE streamType;//TODO
    TimproSlvsTrimCfg trimCtrlMax = {
        .enabled = ImproSenslvs_E_IM_PRO_SLVS_TRIM_EN,
        .startX = 0xFFFF,
        .width = 0xFFFF,
    };

    TimproSlvsTrimCfg trimCtrlMin = {
        .enabled = ImproSenslvs_E_IM_PRO_SLVS_TRIM_DIS,
        .startX = 0,
        .width = 0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senslvs_trim_cfg(0) CFGR0  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].OUTMD.word, ioPro.sen.slvsec.stream[0].OUTMD.word));
//        Ddim_Print(("impro_senslvs_trim_cfg(0) CFGR1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].HSADD.word, ioPro.sen.slvsec.stream[0].HSADD.word));
//        Ddim_Print(("impro_senslvs_trim_cfg(0) OUTMD  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].hsize.word, ioPro.sen.slvsec.stream[0].hsize.word));
//        Ddim_Print(("impro_senslvs_trim_cfg(1) CFGR0  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].OUTMD.word, ioPro.sen.slvsec.stream[1].OUTMD.word));
//        Ddim_Print(("impro_senslvs_trim_cfg(1) CFGR1  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].HSADD.word, ioPro.sen.slvsec.stream[1].HSADD.word));
//        Ddim_Print(("impro_senslvs_trim_cfg(1) OUTMD  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].hsize.word, ioPro.sen.slvsec.stream[1].hsize.word));
		// Maximum value parameter
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_BOTH;//TODO
		self->priv->ercd = impro_senslvs_trim_cfg(self->priv->improSenslvs, streamType, &trimCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_trim_cfg() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_5(self->priv->imPro12Print, "max_para", streamType, &trimCtrlMax);
		}

		// Minimum value parameter
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_A;
		self->priv->ercd = impro_senslvs_trim_cfg(self->priv->improSenslvs, streamType, &trimCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_trim_cfg() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_5(self->priv->imPro12Print, "min_para", streamType, &trimCtrlMin);
		}
    }
}

void ct_im_pro1_2_6(CtImPro12* self, const kuint32 idx)
{
	E_IM_PRO_SLVS_STREAM_TYPE streamType;
	TimproSlvsStatus status;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senslvs_get_status(0) ebdst  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].ebdst.word, ioPro.sen.slvsec.stream[0].ebdst.word));
//        Ddim_Print(("impro_senslvs_get_status(0) lnest  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].lnest.word, ioPro.sen.slvsec.stream[0].lnest.word));
//        Ddim_Print(("impro_senslvs_get_status(1) ebdst  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].ebdst.word, ioPro.sen.slvsec.stream[1].ebdst.word));
//        Ddim_Print(("impro_senslvs_get_status(1) lnest  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[1].lnest.word, ioPro.sen.slvsec.stream[1].lnest.word));
		// Maximum value parameter
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_B;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.stream[streamType].ebdst.bit.ebd = 1;
		ioPro.sen.slvsec.stream[streamType].ebdst.bit.lnum = 8191;
		ioPro.sen.slvsec.stream[streamType].lnest.bit.expln = 8191;
		ioPro.sen.slvsec.stream[streamType].lnest.bit.detln = 8191;
#endif  // CO_DEBUG_ON_PC
		self->priv->ercd = impro_senslvs_get_status(self->priv->improSenslvs, streamType, &status);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_get_status() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_6(self->priv->imPro12Print, "max_para", streamType, &status);
		}

		streamType = E_IM_PRO_SLVS_STREAM_TYPE_A;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.stream[streamType].ebdst.bit.ebd = 0;
		ioPro.sen.slvsec.stream[streamType].ebdst.bit.lnum = 0;
		ioPro.sen.slvsec.stream[streamType].lnest.bit.expln = 0;
		ioPro.sen.slvsec.stream[streamType].lnest.bit.detln = 0;
#endif  // CO_DEBUG_ON_PC
		// Minimum value parameter
		self->priv->ercd = impro_senslvs_get_status(self->priv->improSenslvs, streamType, &status);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_get_status() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_6(self->priv->imPro12Print, "min_para", streamType, &status);
		}

		// invalid value parameter
		self->priv->ercd = impro_senslvs_get_status(self->priv->improSenslvs, streamType, NULL);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_get_status() invalid Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_6(self->priv->imPro12Print, "invalid", streamType, &status);
		}
	}
}

void ct_im_pro1_2_7(CtImPro12* self, const kuint32 idx)
{
	E_IM_PRO_SLVS_STREAM_TYPE streamType;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senslvs_start(0) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].trgr.word, ioPro.sen.slvsec.stream[0].trgr.word));
//        Ddim_Print(("impro_senslvs_start(1) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].trgr.word, ioPro.sen.slvsec.stream[0].trgr.word));
		// Maximum value parameter
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_BOTH;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.stream[E_IM_PRO_SLVS_STREAM_TYPE_A].trgr.bit.trg = 2;
#endif
		self->priv->ercd = impro_senslvs_start(self->priv->improSenslvs, streamType);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_start() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_7(self->priv->imPro12Print, "max_para", streamType);
		}

		// Minimum value parameter
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_A;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.stream[E_IM_PRO_SLVS_STREAM_TYPE_A].trgr.bit.trg = 2;
#endif
		self->priv->ercd = impro_senslvs_start(self->priv->improSenslvs, streamType);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_start() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_7(self->priv->imPro12Print, "min_para", streamType);
		}
	}
}

void ct_im_pro1_2_8(CtImPro12* self, const kuint32 idx)
{
	E_IM_PRO_SLVS_STREAM_TYPE streamType;
	kuchar force = 0;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_senslvs_stop(0) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].trgr.word, ioPro.sen.slvsec.stream[0].trgr.word));
//        Ddim_Print(("impro_senslvs_stop(1) trgr  (0x%08lx, %lx)\n", (kulong)&ioPro.sen.slvsec.stream[0].trgr.word, ioPro.sen.slvsec.stream[0].trgr.word));
		// Maximum value parameter
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_BOTH;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.stream[E_IM_PRO_SLVS_STREAM_TYPE_A].trgr.bit.trg = 3;
#endif
		self->priv->ercd = impro_senslvs_stop(self->priv->improSenslvs, streamType, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_stop() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_8(self->priv->imPro12Print, "max_para", streamType, force);
		}

		// Minimum value parameter
		streamType = E_IM_PRO_SLVS_STREAM_TYPE_A;
		force = 0;
#ifdef CO_DEBUG_ON_PC
		ioPro.sen.slvsec.stream[E_IM_PRO_SLVS_STREAM_TYPE_A].trgr.bit.trg = 3;
#endif
		self->priv->ercd = impro_senslvs_stop(self->priv->improSenslvs, streamType, force);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_senslvs_stop() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
		} else {
			im_pro_1_2_print_8(self->priv->imPro12Print, "min_para", streamType, force);
		}
	}
}

void ct_im_pro1_2_9(CtImPro12* self, const kuint32 idx)
{
    // To Do
}
#endif //CO_CT_IM_PRO_DISABLE

CtImPro12* ct_im_pro1_2_new(void)
{
	CtImPro12* self = k_object_new_with_private(CT_TYPE_IM_PRO1_2, sizeof(CtImPro12Private));

	return self;
}

