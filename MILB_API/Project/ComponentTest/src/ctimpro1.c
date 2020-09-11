/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro1
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsentop.h"
#include "improsensg.h"
#include "ctimpro1.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro1, ct_im_pro1)
#define CT_IM_PRO1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro1Private, CT_TYPE_IM_PRO1))


struct _CtImPro1Private
{
	ImproSentop *improSentop;
	ImproSensg *improSensg;
	ImPro10Print *imPro10Print;
	kint32 ercd;
};


/**********
 * IMPL
 */
static void ct_im_pro1_constructor(CtImPro1 *self)
{
	self->priv = CT_IM_PRO1_GET_PRIVATE(self);
	self->priv->improSentop = impro_sentop_new();
	self->priv->improSensg = impro_sensg_new();
	self->priv->imPro10Print = im_pro_1_0_print_new();
	self->priv->ercd = 0;
}

static void ct_im_pro1_destructor(CtImPro1 *self)
{
	CtImPro1Private *priv = CT_IM_PRO1_GET_PRIVATE(self);

	if (priv->improSentop) {
		k_object_unref(priv->improSentop);
		priv->improSentop = NULL;
	}

	if (priv->improSensg) {
		k_object_unref(priv->improSensg);
		priv->improSensg = NULL;
	}

	if (priv->imPro10Print) {
		k_object_unref(priv->imPro10Print);
		priv->imPro10Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro1_1(CtImPro1* self, const kuint32 idx)
{
	impro_sentop_init(self->priv->improSentop);
	Ddim_Print(("impro_sentop_init() result:sr(%d)\n", ioPro.sen.sentop.sr.bit.sr));
}

void ct_im_pro1_2(CtImPro1* self, const kuint32 idx)
{
	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sentop_sw_reset() sr (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.sr.word,    ioPro.sen.sentop.sr.word  ));

// Normal case
		self->priv->ercd = impro_sentop_sw_reset(self->priv->improSentop);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_sw_reset() Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			Ddim_Print(("impro_sentop_sw_reset() result:sr(%d)\n", ioPro.sen.sentop.sr.bit.sr));
		}

		// illegal case
		impro_sensg_start(self->priv->improSensg, ImproSensg_E_IM_PRO_SG_CH_0);

		self->priv->ercd = impro_sentop_sw_reset(self->priv->improSentop);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_sw_reset() Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			Ddim_Print(("impro_sentop_sw_reset() result:sr(%d)\n", ioPro.sen.sentop.sr.bit.sr));
		}
		impro_sensg_stop(self->priv->improSensg, ImproSensg_E_IM_PRO_SG_CH_0, 0);
	}
}

void ct_im_pro1_3(CtImPro1* self, const kuint32 idx)
{
	EimproSentopClkType clkType;
	kuchar onOff;
	kuchar waitSkip;

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sentop_control_clock() clkstp1 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.clkstp.clkstp1.word,  ioPro.sen.sentop.clkstp.clkstp1.word  ));

// SENSORCLK ON
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_SENSORCLK;
		onOff = D_IM_PRO_CLOCK_ON;//TODO
		waitSkip = 0;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
			return;
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}

		// APCLK0 ON
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK0;
		onOff = D_IM_PRO_CLOCK_ON;
		waitSkip = 0;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
			return;
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}

		// APCLK1 ON
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK1;
		onOff = D_IM_PRO_CLOCK_ON;
		waitSkip = 0;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
			return;
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}

		// APCLK2 ON
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK2;
		onOff = D_IM_PRO_CLOCK_ON;
		waitSkip = 0;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			return;
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}

		// APCLK3 ON
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK3;
		onOff = D_IM_PRO_CLOCK_ON;
		waitSkip = 0;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
			return;
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}

		// SENSORCLK OFF
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_SENSORCLK;
		onOff = D_IM_PRO_CLOCK_OFF;
		waitSkip = 0;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
			return;
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}

		// APCLK0 OFF
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK0;
		onOff = D_IM_PRO_CLOCK_OFF;
		waitSkip = 0;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
			return;
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}

		// APCLK1 OFF
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK1;
		onOff = D_IM_PRO_CLOCK_OFF;
		waitSkip = 0;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
			return;
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}

		// APCLK2 OFF
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK2;
		onOff = D_IM_PRO_CLOCK_OFF;
		waitSkip = 0;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
			return;
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}

		// APCLK3 OFF
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK3;
		onOff = D_IM_PRO_CLOCK_OFF;
		waitSkip = 0;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
			return;
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}

		// wait skip on
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_SENSORCLK;
		onOff = D_IM_PRO_CLOCK_ON;
		waitSkip = 1;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
			return;
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}

		// wait skip on
		clkType = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_SENSORCLK;
		onOff = D_IM_PRO_CLOCK_OFF;
		waitSkip = 1;
		self->priv->ercd = impro_sentop_control_clock(self->priv->improSentop, clkType, onOff, waitSkip);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) Error self->priv->ercd=0x%x\n",
							clkType, onOff, waitSkip, self->priv->ercd));
			return;
		} else {
			Ddim_Print(
					("impro_sentop_control_clock(%u, %u, %u) result:clkstp1(%lu)\n",
							clkType, onOff, waitSkip, ioPro.sen.sentop.clkstp.clkstp1.word));
		}
    }
}

void ct_im_pro1_4(CtImPro1* self, const kuint32 idx)
{
    TimproSentopCtrl sentopCtrlMin = {
        .senConnectTypeSel[0] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_LVDS,
        .senConnectTypeSel[1] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_LVDS,
        .senConnectTypeSel[2] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_LVDS,
        .senConnectTypeSel[3] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_LVDS,
        .blobInputSel[0] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_0,
        .blobInputSel[1] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_0,
        .blobInputSel[2] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_0,
        .blobInputSel[3] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_0,
        .sdramOutputType[0] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_0_PRE_BLOB,
        .sdramOutputType[1] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_0_PRE_BLOB,
        .sdramOutputType[2] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_0_PRE_BLOB,
        .sdramOutputType[3] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_0_PRE_BLOB,
        .outputSelSro2 = ImproSentop_E_IM_PRO_SENTOP_OUT_SEL_LDIV0,
        .sencoreHmaxSizeCtrl = ImproSentop_E_IM_PRO_SENTOP_SENCORE_MAX_HSIZE_CTRL_0,
        .ldivHmaxSizeCtrl = ImproSentop_E_IM_PRO_SENTOP_LDIV_MAX_HSIZE_CTRL_0,
        .ldivMultiChInputCtrl = ImproSentop_E_IM_PRO_SENTOP_LDIV_MULTI_INPUT_CTRL_DISABLE,
        .firstPixel[0][0] = E_IM_PRO_ORG_R,
        .firstPixel[0][1] = E_IM_PRO_ORG_R,
        .firstPixel[1][0] = E_IM_PRO_ORG_R,
        .firstPixel[1][1] = E_IM_PRO_ORG_R,
        .firstPixel[2][0] = E_IM_PRO_ORG_R,
        .firstPixel[2][1] = E_IM_PRO_ORG_R,
        .firstPixel[3][0] = E_IM_PRO_ORG_R,
        .firstPixel[3][1] = E_IM_PRO_ORG_R,
    };

    TimproSentopCtrl sentopCtrlMax = {
        .senConnectTypeSel[0] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_EXT_LVDS,
        .senConnectTypeSel[1] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_EXT_LVDS,
        .senConnectTypeSel[2] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_EXT_LVDS,
        .senConnectTypeSel[3] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_EXT_LVDS,
        .blobInputSel[0] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV3_0,
        .blobInputSel[1] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV3_0,
        .blobInputSel[2] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV3_0,
        .blobInputSel[3] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV3_0,
        .sdramOutputType[0] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV3_0_POST_BLOB,
        .sdramOutputType[1] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV3_0_POST_BLOB,
        .sdramOutputType[2] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV3_0_POST_BLOB,
        .sdramOutputType[3] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV3_0_POST_BLOB,
        .outputSelSro2 = ImproSentop_E_IM_PRO_SENTOP_OUT_SEL_LDIV1,
        .sencoreHmaxSizeCtrl = ImproSentop_E_IM_PRO_SENTOP_SENCORE_MAX_HSIZE_CTRL_3,
        .ldivHmaxSizeCtrl = ImproSentop_E_IM_PRO_SENTOP_LDIV_MAX_HSIZE_CTRL_3,
        .ldivMultiChInputCtrl = ImproSentop_E_IM_PRO_SENTOP_LDIV_MULTI_INPUT_CTRL_4CH,
        .firstPixel[0][0] = E_IM_PRO_ORG_GB,
        .firstPixel[0][1] = E_IM_PRO_ORG_GB,
        .firstPixel[1][0] = E_IM_PRO_ORG_GB,
        .firstPixel[1][1] = E_IM_PRO_ORG_GB,
        .firstPixel[2][0] = E_IM_PRO_ORG_GB,
        .firstPixel[2][1] = E_IM_PRO_ORG_GB,
        .firstPixel[3][0] = E_IM_PRO_ORG_GB,
        .firstPixel[3][1] = E_IM_PRO_ORG_GB,
    };

	if (idx == 1) {
		// Maximum value parameter
		self->priv->ercd = impro_sentop_ctrl(self->priv->improSentop, &sentopCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_4(self->priv->imPro10Print, "max_para", &sentopCtrlMax);
		}

		// Minimum value parameter
		self->priv->ercd = impro_sentop_ctrl(self->priv->improSentop, &sentopCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_4(self->priv->imPro10Print, "min_para", &sentopCtrlMin);
		}

//        sentopCtrlMax.sencoreHmaxSizeCtrl = ImproSentop_E_IM_PRO_SENTOP_SENCORE_MAX_HSIZE_CTRL_3;
//        self->priv->ercd = impro_sentop_ctrl(&sentopCtrlMax);
//        if(self->priv->ercd != DdimUserCustom_E_OK) {
//            Ddim_Print(("impro_sentop_ctrl() invalid Error self->priv->ercd=0x%x\n", self->priv->ercd));
//            return;
//        }
//        else {
//            im_pro_1_0_print_4("invalid_para1", &sentopCtrlMax);
//        }
//
//        sentopCtrlMax.ldivHmaxSizeCtrl = ImproSentop_E_IM_PRO_SENTOP_LDIV_MAX_HSIZE_CTRL_3;
//        self->priv->ercd = impro_sentop_ctrl(&sentopCtrlMax);
//        if(self->priv->ercd != DdimUserCustom_E_OK) {
//            Ddim_Print(("impro_sentop_ctrl() invalid Error self->priv->ercd=0x%x\n", self->priv->ercd));
//            return;
//        }
//        else {
//            im_pro_1_0_print_4("invalid_para2", &sentopCtrlMax);
//        }
    }
}

void ct_im_pro1_5(CtImPro1* self, const kuint32 idx)
{
    TimproSentopBsCtrl bsCtrlMax = {
        .shiftValue[0] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_6BIT,
        .shiftValue[1] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_6BIT,
        .shiftValue[2] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_6BIT,
        .shiftValue[3] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_6BIT,
        .satCompensation[0] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_COMP,
        .satCompensation[1] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_COMP,
        .satCompensation[2] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_COMP,
        .satCompensation[3] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_COMP,
        .shiftDir[0] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_R,
        .shiftDir[1] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_R,
        .shiftDir[2] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_R,
        .shiftDir[3] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_R,
    };

    TimproSentopBsCtrl bsCtrlMin = {
        .shiftValue[0] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_0BIT,
        .shiftValue[1] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_0BIT,
        .shiftValue[2] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_0BIT,
        .shiftValue[3] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_0BIT,
        .satCompensation[0] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_NOCOMP,
        .satCompensation[1] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_NOCOMP,
        .satCompensation[2] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_NOCOMP,
        .satCompensation[3] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_NOCOMP,
        .shiftDir[0] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_L,
        .shiftDir[1] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_L,
        .shiftDir[2] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_L,
        .shiftDir[3] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_L,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sentop_bs_ctrl() BSCTL1 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.BSCTL.BSCTL1.word,   ioPro.sen.sentop.BSCTL.BSCTL1.word));
//        Ddim_Print(("impro_sentop_bs_ctrl() BSCTL2 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.BSCTL.BSCTL2.word,   ioPro.sen.sentop.BSCTL.BSCTL2.word));

// Maximum value parameter
		self->priv->ercd = impro_sentop_bs_ctrl(self->priv->improSentop, &bsCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_bs_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_5(self->priv->imPro10Print, "max_para", &bsCtrlMax);
		}

		// Minimum value parameter
		self->priv->ercd = impro_sentop_bs_ctrl(self->priv->improSentop, &bsCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_bs_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_5(self->priv->imPro10Print, "min_para", &bsCtrlMin);
		}
    }
}

void ct_im_pro1_6(CtImPro1* self, const kuint32 idx)
{
    TimproSentopObtCtrl obtCtrlMax = {
        .obtCommPerttern = ImproSentop_E_IM_PRO_SENTOP_OBT_COMM_PARTTERN_BLOB0_1_BLOB2_3,
    };

    TimproSentopObtCtrl obtCtrlMin = {
        .obtCommPerttern = ImproSentop_E_IM_PRO_SENTOP_OBT_COMM_PARTTERN_ANY_2SETS,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sentop_obt_ctrl() OBTCDCCTL1 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.OBTCDCCTL1.word,    ioPro.sen.sentop.OBTCDCCTL1.word  ));

// Maximum value parameter
		self->priv->ercd = impro_sentop_obt_ctrl(self->priv->improSentop, &obtCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_obt_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_6(self->priv->imPro10Print, "max_para", &obtCtrlMax);
		}

		// Minimum value parameter
		self->priv->ercd = impro_sentop_obt_ctrl(self->priv->improSentop, &obtCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_obt_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_6(self->priv->imPro10Print, "min_para", &obtCtrlMin);
		}
    }
}

void ct_im_pro1_7(CtImPro1* self, const kuint32 idx)
{
    TimproSentopObtWeightCoeff obtWeightCoeffMax = {
        .coeff[0][0] = 0xFF,
        .coeff[0][1] = 0xFF,
        .coeff[1][0] = 0xFF,
        .coeff[1][1] = 0xFF,
        .coeff[2][0] = 0xFF,
        .coeff[2][1] = 0xFF,
        .coeff[3][0] = 0xFF,
        .coeff[3][1] = 0xFF,
    };

    TimproSentopObtWeightCoeff obtWeightCoeffMin = {
        .coeff[0][0] = 0,
        .coeff[0][1] = 0,
        .coeff[1][0] = 0,
        .coeff[1][1] = 0,
        .coeff[2][0] = 0,
        .coeff[2][1] = 0,
        .coeff[3][0] = 0,
        .coeff[3][1] = 0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sentop_obt_set_weight_coeff() OBTCDCCTL2_1 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.OBTCDCCTL2.OBTCDCCTL2_1.word, ioPro.sen.sentop.OBTCDCCTL2.OBTCDCCTL2_1.word ));
//        Ddim_Print(("impro_sentop_obt_set_weight_coeff() OBTCDCCTL2_2 (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.OBTCDCCTL2.OBTCDCCTL2_2.word, ioPro.sen.sentop.OBTCDCCTL2.OBTCDCCTL2_2.word ));
		// Maximum value parameter
		self->priv->ercd = impro_sentop_obt_set_weight_coeff(self->priv->improSentop, &obtWeightCoeffMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_obt_set_weight_coeff() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_7(self->priv->imPro10Print, "max_para", &obtWeightCoeffMax);
		}

		// Minimum value parameter
		self->priv->ercd = impro_sentop_obt_set_weight_coeff(self->priv->improSentop, &obtWeightCoeffMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(
					("impro_sentop_obt_set_weight_coeff() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_7(self->priv->imPro10Print, "min_para", &obtWeightCoeffMin);
		}
    }
}

void ct_im_pro1_8(CtImPro1* self, const kuint32 idx)
{
    TimproSentopLvdsCtrl lvdsCtrlMax = {
        .clockLanePowerdown = 0xF,
        .dataLanePowerdown = 0xFFFF,
    };

    TimproSentopLvdsCtrl lvdsCtrlMin = {
        .clockLanePowerdown = 0,
        .dataLanePowerdown = 0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sentop_lvds_ctrl() LVDSCTL (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.LVDSCTL.word, ioPro.sen.sentop.LVDSCTL.word ));
		// Maximum value parameter
		self->priv->ercd = impro_sentop_lvds_ctrl(self->priv->improSentop, &lvdsCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_lvds_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_8(self->priv->imPro10Print, "max_para", &lvdsCtrlMax);
		}

		// Minimum value parameter
		self->priv->ercd = impro_sentop_lvds_ctrl(self->priv->improSentop, &lvdsCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_lvds_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_8(self->priv->imPro10Print, "min_para", &lvdsCtrlMin);
		}
    }
}

void ct_im_pro1_9(CtImPro1* self, const kuint32 idx)
{
    TimproSentopSlvsCtrl slvsCtrlMax = {
        .linkMode = ImproSentop_E_IM_PRO_SENTOP_SLVS_LINK_CONN_PHY1,
        .phy0Rxpdck = 0x1,
        .phy1Rxpdck = 0x1,
        .phy2Rxpdck = 0x1,
        .phy3Rxpdck = 0x1,
        .phy0Rxpclk2aen = 0x1,
        .phy1Rxpclk2aen = 0x1,
    };

    TimproSentopSlvsCtrl slvsCtrlMin = {
        .linkMode = ImproSentop_E_IM_PRO_SENTOP_SLVS_LINK_CONN_PHY0,
        .phy0Rxpdck = 0,
        .phy1Rxpdck = 0,
        .phy2Rxpdck = 0,
        .phy3Rxpdck = 0,
        .phy0Rxpclk2aen = 0,
        .phy1Rxpclk2aen = 0,
    };

	if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("impro_sentop_slvs_ctrl() SLVSECCTL (0x%08lx, %lx)\n", (kulong)&ioPro.sen.sentop.SLVSECCTL.word, ioPro.sen.sentop.SLVSECCTL.word   ));
		// Maximum value parameter
		self->priv->ercd = impro_sentop_slvs_ctrl(self->priv->improSentop, &slvsCtrlMax);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_slvs_ctrl() max_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_9(self->priv->imPro10Print, "max_para", &slvsCtrlMax);
		}

		// Minimum value parameter
		self->priv->ercd = impro_sentop_slvs_ctrl(self->priv->improSentop, &slvsCtrlMin);
		if (self->priv->ercd != DdimUserCustom_E_OK) {
			Ddim_Print(("impro_sentop_slvs_ctrl() min_para Error self->priv->ercd=0x%x\n", self->priv->ercd));
			return;
		} else {
			im_pro_1_0_print_9(self->priv->imPro10Print, "min_para", &slvsCtrlMin);
		}
    }
}
#endif //CO_CT_IM_PRO_DISABLE

CtImPro1* ct_im_pro1_new(void)
{
	CtImPro1* self = k_object_new_with_private(CT_TYPE_IM_PRO1, sizeof(CtImPro1Private));

	return self;
}

