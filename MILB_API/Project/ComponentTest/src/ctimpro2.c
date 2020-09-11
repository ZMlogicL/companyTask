/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro2
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsrotop.h"
#include "improsrovrb.h"
#include "improsroafpb.h"
#include "ctimpro2.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro2, ct_im_pro2)
#define CT_IM_PRO2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro2Private, CT_TYPE_IM_PRO2))


struct _CtImPro2Private
{
	ImproSrotop *improSrotop;
	ImproSrovrb *improSrovrb;
	ImproSroafpb *improSroafpb;
	ImPro20Print *imPro20Print;
	kint32 ercd;
	E_IM_PRO_UNIT_NUM unitNo;
	kuchar ch;
};


static void ct_im_pro2_constructor(CtImPro2 *self)
{
	self->priv = CT_IM_PRO2_GET_PRIVATE(self);
	self->priv->improSrotop = impro_srotop_new();
	self->priv->improSrovrb = impro_srovrb_new();
	self->priv->improSroafpb = impro_sroafpb_new();
	self->priv->imPro20Print = im_pro_2_0_print_new();
	self->priv->ercd = 0;
	self->priv->unitNo = 0;
	self->priv->ch = 0;
}

static void ct_im_pro2_destructor(CtImPro2 *self)
{
	CtImPro2Private *priv = CT_IM_PRO2_GET_PRIVATE(self);

	if (priv->improSrotop) {
		k_object_unref(priv->improSrotop);
		priv->improSrotop = NULL;
	}

	if (priv->improSrovrb) {
		k_object_unref(priv->improSrovrb);
		priv->improSrovrb = NULL;
	}

	if (priv->improSroafpb) {
		k_object_unref(priv->improSroafpb);
		priv->improSroafpb = NULL;
	}

	if (priv->imPro20Print) {
		k_object_unref(priv->imPro20Print);
		priv->imPro20Print = NULL;
	}
}


#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro2_1(CtImPro2* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {//TODO
			impro_srotop_init(self->priv->improSrotop, self->priv->unitNo);
			Ddim_Print(
					("impro_srotop_init(%u) result:sr(%u)\n", self->priv->unitNo,
							ioPro.imgPipe[self->priv->unitNo].sro.srotop.sr.bit.sr));
		}
    }
}

void ct_im_pro2_2(CtImPro2* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
//            Ddim_Print(("Target register address\n"));
//            Ddim_Print(("impro_srotop_sw_reset(%u) sr (0x%08lx, %lx)\n", self->priv->unitNo, (kulong)&ioPro.imgPipe[self->priv->unitNo].sro.srotop.sr.word,   ioPro.imgPipe[self->priv->unitNo].sro.srotop.sr.word));

// Normal case
			self->priv->ercd = impro_srotop_sw_reset(self->priv->improSrotop, self->priv->unitNo);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srotop_sw_reset(%u) Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				Ddim_Print(
						("impro_srotop_sw_reset(%u) result:sr(%u)\n", self->priv->unitNo,
								ioPro.imgPipe[self->priv->unitNo].sro.srotop.sr.bit.sr));
			}

			// illegal case
			impro_srovrb_start(self->priv->improSrovrb, self->priv->unitNo);

			self->priv->ercd = impro_srotop_sw_reset(self->priv->improSrotop, self->priv->unitNo);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srotop_sw_reset(%u) Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				Ddim_Print(
						("impro_srotop_sw_reset(%u) result:sr(%u)\n", self->priv->unitNo,
								ioPro.imgPipe[self->priv->unitNo].sro.srotop.sr.bit.sr));
			}
			impro_srovrb_stop(self->priv->improSrovrb, self->priv->unitNo, 0);
		}
    }
}

void ct_im_pro2_3(CtImPro2* self, const kuint32 idx)
{
    kuchar clkType;
    kuchar onOff;
    kuchar waitSkip;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
//            Ddim_Print(("Target register address\n"));
//            Ddim_Print(("impro_srotop_control_clock(%lu) clkstp1 (0x%08lx, %lx)\n", self->priv->unitNo, (kulong)&ioPro.imgPipe[self->priv->unitNo].sro.srotop.clkstp.word, ioPro.imgPipe[self->priv->unitNo].sro.srotop.clkstp.word));

			for (waitSkip = 0; waitSkip < 2; waitSkip++) {
				for (clkType = ImproSrotop_E_IM_PRO_SROTOP_CLK_TYPE_SROCLK;
						clkType < ImproSrotop_E_IM_PRO_SROTOP_CLK_TYPE_SROCLK2 + 1; clkType++) {
					// STATCLK ON
					onOff = D_IM_PRO_CLOCK_ON;
					self->priv->ercd = impro_srotop_control_clock(self->priv->improSrotop,
							self->priv->unitNo, clkType, onOff, waitSkip);
					if (self->priv->ercd != DdimUserCustom_E_OK) {
						Ddim_Print(
								("impro_srotop_control_clock(%u, %u, %u, %u) Error self->priv->ercd=0x%x\n",
										self->priv->unitNo, clkType, onOff, waitSkip, self->priv->ercd));
					} else {
						Ddim_Print(
								("impro_srotop_control_clock(%u, %u, %u, %u) result:clkstp1(%lu)\n",
										self->priv->unitNo, clkType, onOff, waitSkip,
										ioPro.imgPipe[self->priv->unitNo].sro.srotop.clkstp.word));
					}

					// STATCLK OFF
					onOff = D_IM_PRO_CLOCK_OFF;
					self->priv->ercd = impro_srotop_control_clock(self->priv->improSrotop,
							self->priv->unitNo, clkType, onOff, waitSkip);
					if (self->priv->ercd != DdimUserCustom_E_OK) {
						Ddim_Print(
								("impro_srotop_control_clock(%u, %u, %u, %u) Error self->priv->ercd=0x%x\n",
										self->priv->unitNo, clkType, onOff, waitSkip, self->priv->ercd));
					} else {
						Ddim_Print(
								("impro_srotop_control_clock(%u, %u, %u, %u) result:clkstp1(%lu)\n",
										self->priv->unitNo, clkType, onOff, waitSkip,
										ioPro.imgPipe[self->priv->unitNo].sro.srotop.clkstp.word));
					}
                }
            }
        }
    }
}

void ct_im_pro2_4(CtImPro2* self, const kuint32 idx)
{
    TimproSrotopCtrl ctrlMax = {
        .inputMode = ImproSrotop_E_IM_PRO_SROTOP_INPUT_MODE_REINPUT,
        .sroModeSel = ImproSrotop_E_IM_PRO_SROTOP_MODE2,
        .cagTargetSel = ImproSrotop_E_IM_PRO_SROTOP_CAG_TARGET_BLOCK_B2B,
        .bayOutPathSel = ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_BAY_OUT_CAG_OUT,
        .b2bConnectPathSel = ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_B2B_CONN_WITH_BR,
        .ltmConnectPathSel = ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_LTM_CONN_WITH_BR,
        .firstPixel[0] = E_IM_PRO_ORG_GB,//TODO
        .firstPixel[1] = E_IM_PRO_ORG_GB,
    };

    TimproSrotopCtrl ctrlMin = {
        .inputMode = ImproSrotop_E_IM_PRO_SROTOP_INPUT_MODE_DIRECT,
        .sroModeSel = ImproSrotop_E_IM_PRO_SROTOP_MODE0,
        .cagTargetSel = ImproSrotop_E_IM_PRO_SROTOP_CAG_TARGET_BLOCK_SRO,
        .bayOutPathSel = ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_BAY_OUT_WITHOUT_BR,
        .b2bConnectPathSel = ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_B2B_CONN_WITHOUT_BR,
        .ltmConnectPathSel = ImproSrotop_E_IM_PRO_SROTOP_PATH_SEL_LTM_CONN_WITHOUT_BR,
        .firstPixel[0] = E_IM_PRO_ORG_R,
        .firstPixel[1] = E_IM_PRO_ORG_R,
    };

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srotop_ctrl(self->priv->improSrotop, self->priv->unitNo, &ctrlMax);
			im_pro_2_0_print_4(self->priv->imPro20Print, "max_para", self->priv->unitNo, self->priv->ercd, &ctrlMax);

			self->priv->ercd = impro_srotop_ctrl(self->priv->improSrotop, self->priv->unitNo, &ctrlMin);
			im_pro_2_0_print_4(self->priv->imPro20Print, "min_para", self->priv->unitNo, self->priv->ercd, &ctrlMin);
		}
    }
}

void ct_im_pro2_5(CtImPro2* self, const kuint32 idx)
{
	TimproSrotopWeitgenCtrl ctrlMax = {
		.vWaitSignalPos = 16382,
		.hWaitSignalPos = 16382,
	};

	TimproSrotopWeitgenCtrl ctrlMin = {
		.vWaitSignalPos = 2,
		.hWaitSignalPos = 2,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {//TODO
			for (self->priv->ch = 0; self->priv->ch < E_IM_PRO_WEITGEN_CH1 + 1; self->priv->ch++) {
				self->priv->ercd = impro_srotop_weitgen_ctrl(self->priv->improSrotop,
						self->priv->unitNo, self->priv->ch, &ctrlMax);
				im_pro_2_0_print_5(self->priv->imPro20Print, "max_para",
						self->priv->unitNo, self->priv->ch, self->priv->ercd, &ctrlMax);

				self->priv->ercd = impro_srotop_weitgen_ctrl(self->priv->improSrotop,
						self->priv->unitNo, self->priv->ch, &ctrlMin);
				im_pro_2_0_print_5(self->priv->imPro20Print, "min_para", self->priv->unitNo,
						self->priv->ch, self->priv->ercd, &ctrlMin);
			}
        }
    }
}

void ct_im_pro2_6(CtImPro2* self, const kuint32 idx)
{
    EimproWeitgenEnable ctrlMax = ImproSrotop_E_IM_PRO_WEITGEN_EN;
    EimproWeitgenEnable ctrlMin = ImproSrotop_E_IM_PRO_WEITGEN_DIS;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = 0; self->priv->ch < E_IM_PRO_WEITGEN_CH1 + 1; self->priv->ch++) {
				self->priv->ercd = impro_srotop_weitgen_enable(self->priv->improSrotop,
						self->priv->unitNo, self->priv->ch, ctrlMax);
				im_pro_2_0_print_6(self->priv->imPro20Print, "max_para",
						self->priv->unitNo, self->priv->ch, self->priv->ercd, ctrlMax);

				self->priv->ercd = impro_srotop_weitgen_enable(self->priv->improSrotop,
						self->priv->unitNo, self->priv->ch, ctrlMin);
				im_pro_2_0_print_6(self->priv->imPro20Print, "min_para",
						self->priv->unitNo, self->priv->ch, self->priv->ercd, ctrlMin);
			}
        }
    }
}

void ct_im_pro2_7(CtImPro2* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroafpb_E_IM_PRO_AFPB_CH_A; self->priv->ch < ImproSroafpb_E_IM_PRO_AFPB_CH_G + 1;
					self->priv->ch++) {
				impro_sroafpb_start(self->priv->improSroafpb, self->priv->unitNo, self->priv->ch);
				im_pro_2_0_print_7(self->priv->imPro20Print, self->priv->unitNo, self->priv->ch);
			}
        }
    }
}

void ct_im_pro2_8(CtImPro2* self, const kuint32 idx)
{
	kuchar force;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (force = 0; force < 2 + 1; force++) {
				for (self->priv->ch = ImproSroafpb_E_IM_PRO_AFPB_CH_A; self->priv->ch < ImproSroafpb_E_IM_PRO_AFPB_CH_G + 1;
						self->priv->ch++) {
#ifdef CO_DEBUG_ON_PC
					ioPro.imgPipe[self->priv->unitNo].sro.afpb[self->priv->ch].afpbtrg.bit.afpbtrg = 3;
#endif
					impro_sroafpb_stop(self->priv->improSroafpb, self->priv->unitNo, self->priv->ch, force);
					im_pro_2_0_print_8(self->priv->imPro20Print, self->priv->unitNo, self->priv->ch, force);
				}
            }
        }
    }
}

void ct_im_pro2_9(CtImPro2* self, const kuint32 idx)
{
	TimproAfpbCtrl afpbCtrlMax = {
		.afpbArea.posX = 16382,
		.afpbArea.posY = 16380,
		.afpbArea.width = 16382,
		.afpbArea.lines = 16382,
	};

	TimproAfpbCtrl afpbCtrlMin = {
		.afpbArea.posX = 0,
		.afpbArea.posY = 0,
		.afpbArea.width = 2,
		.afpbArea.lines = 2,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroafpb_E_IM_PRO_AFPB_CH_A; self->priv->ch < ImproSroafpb_E_IM_PRO_AFPB_CH_G + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_sroafpb_ctrl(self->priv->improSroafpb, self->priv->unitNo, self->priv->ch,
						&afpbCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroafpb_ctrl(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_0_print_9(self->priv->imPro20Print, "max_para", self->priv->unitNo,
							self->priv->ch, &afpbCtrlMax);
				}

				self->priv->ercd = impro_sroafpb_ctrl(self->priv->improSroafpb, self->priv->unitNo, self->priv->ch,
						&afpbCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroafpb_ctrl(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_0_print_9(self->priv->imPro20Print, "min_para", self->priv->unitNo,
							self->priv->ch, &afpbCtrlMin);
				}
            }
        }
    }
}
#endif  //CO_CT_IM_PRO_DISABLE

CtImPro2* ct_im_pro2_new(void)
{
	CtImPro2* self = k_object_new_with_private(CT_TYPE_IM_PRO2, sizeof(CtImPro2Private));

	return self;
}


