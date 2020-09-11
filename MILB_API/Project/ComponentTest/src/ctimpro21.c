/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro21
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsrofshdl.h"
#include "ctimpro21.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro21, ct_im_pro2_1)
#define CT_IM_PRO2_1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro21Private, CT_TYPE_IM_PRO2_1))


struct _CtImPro21Private
{
	ImproSrofshdl *improSrofshdl;
	ImPro21Print *imPro21Print;
	kint32 ercd;
	E_IM_PRO_UNIT_NUM unitNo;//TODO
	kuchar ch;
};


/**********
 * IMPL
 */
static void ct_im_pro2_1_constructor(CtImPro21 *self)
{
	self->priv = CT_IM_PRO2_1_GET_PRIVATE(self);
	self->priv->improSrofshdl = impro_srofshdl_new();
	self->priv->imPro21Print = im_pro_2_1_print_new();
	self->priv->ercd = 0;
	self->priv->unitNo = 0;
	self->priv->ch = 0;
}

static void ct_im_pro2_1_destructor(CtImPro21 *self)
{
	CtImPro21Private *priv = CT_IM_PRO2_1_GET_PRIVATE(self);

	if (priv->improSrofshdl) {
		k_object_unref(priv->improSrofshdl);
		priv->improSrofshdl = NULL;
	}

	if (priv->imPro21Print) {
		k_object_unref(priv->imPro21Print);
		priv->imPro21Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro2_1_0(CtImPro21* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSrofshdl_E_IM_PRO_FSHDL_CH_0; self->priv->ch < ImproSrofshdl_E_IM_PRO_FSHDL_CH_1 + 1;
					self->priv->ch++) {
				impro_srofshdl_start(self->priv->improSrofshdl, self->priv->unitNo, self->priv->ch);
				im_pro_2_1_print_0(self->priv->imPro21Print, self->priv->unitNo, self->priv->ch);
			}
        }
    }
}

void ct_im_pro2_1_1(CtImPro21* self, const kuint32 idx)
{
	kuchar force;
#ifdef CO_DEBUG_ON_PC
	const T_IM_PRO_SRO_FSHDL_INFO* fshdlInfo;
#endif

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (force = 0; force < 2 + 1; force++) {
				for (self->priv->ch = ImproSrofshdl_E_IM_PRO_FSHDL_CH_0; self->priv->ch < ImproSrofshdl_E_IM_PRO_FSHDL_CH_1 + 1;
						self->priv->ch++) {
#ifdef CO_DEBUG_ON_PC
					impro_srofshdl_comm_get_fshdl_reg_info(self->priv->improSrofshdl,
							self->priv->unitNo, self->priv->ch, &fshdlInfo);
					fshdlInfo->reg_ptr->ffshtrg.bit.ffshtrg = 3;
#endif
					impro_srofshdl_stop(self->priv->improSrofshdl, self->priv->unitNo, self->priv->ch, force);
					im_pro_2_1_print_1(self->priv->imPro21Print, self->priv->unitNo, self->priv->ch, force);
				}
            }
        }
    }
}

void ct_im_pro2_1_2(CtImPro21* self, const kuint32 idx)
{
	TimproFshdlCommonCtrl fshdlCtrlMax = {
		.montageMode = ImproSrofshdl_E_IM_PRO_FSHD_MONTAGE_MODE_ON,
		.clipR = 16383,
		.clipGr = 16383,
		.clipGb = 16383,
		.clipB = 16383,
	};

	TimproFshdlCommonCtrl fshdlCtrlMin = {
		.montageMode = ImproSrofshdl_E_IM_PRO_FSHD_MONTAGE_MODE_OFF,
		.clipR = 0,
		.clipGr = 0,
		.clipGb = 0,
		.clipB = 0,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSrofshdl_E_IM_PRO_FSHDL_CH_0; self->priv->ch < ImproSrofshdl_E_IM_PRO_FSHDL_CH_1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_srofshdl_ctrl(self->priv->improSrofshdl, self->priv->unitNo, self->priv->ch,
						&fshdlCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_ctrl(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_2(self->priv->imPro21Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &fshdlCtrlMax);
				}

				self->priv->ercd = impro_srofshdl_ctrl(self->priv->improSrofshdl, self->priv->unitNo, self->priv->ch,
						&fshdlCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_ctrl(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_2(self->priv->imPro21Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &fshdlCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_1_3(CtImPro21* self, const kuint32 idx)
{
	TimproFshdlBlendCtrl fshdlCtrlMax = {
		.shadingBlend0 = 511,
		.shadingBlend1 = 511,
	};

	TimproFshdlBlendCtrl fshdlCtrlMin = {
		.shadingBlend0 = -512,
		.shadingBlend1 = -512,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSrofshdl_E_IM_PRO_FSHDL_CH_0; self->priv->ch < ImproSrofshdl_E_IM_PRO_FSHDL_CH_1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_srofshdl_set_blend(self->priv->improSrofshdl, self->priv->unitNo,
						self->priv->ch, &fshdlCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_set_blend(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_3(self->priv->imPro21Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &fshdlCtrlMax);
				}

				self->priv->ercd = impro_srofshdl_set_blend(self->priv->improSrofshdl, self->priv->unitNo,
						self->priv->ch, &fshdlCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_set_blend(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_3(self->priv->imPro21Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &fshdlCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_1_4(CtImPro21* self, const kuint32 idx)
{
	kuchar fshdlCtrlMax = 1;

	kuchar fshdlCtrlMin = 0;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSrofshdl_E_IM_PRO_FSHDL_CH_0; self->priv->ch < ImproSrofshdl_E_IM_PRO_FSHDL_CH_1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_srofshdl_set_paen(self->priv->improSrofshdl, self->priv->unitNo,
						self->priv->ch, fshdlCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_set_paen(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_4(self->priv->imPro21Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, fshdlCtrlMax);
				}

				self->priv->ercd = impro_srofshdl_set_paen(self->priv->improSrofshdl, self->priv->unitNo,
						self->priv->ch, fshdlCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_set_paen(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_4(self->priv->imPro21Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, fshdlCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_1_5(CtImPro21* self, const kuint32 idx)
{
	T_IM_PRO_AREA_INFO fshdlCtrlMax = {//TODO
		.posY = D_IM_PRO_FSHDL_FFSHV_MAX,
		.posX = D_IM_PRO_FSHDL_FFSHH_MAX,
		.lines = D_IM_PRO_FSHDL_FFSHVW_MAX,
		.width = D_IM_PRO_FSHDL_FFSHHW_MAX,
	};

	T_IM_PRO_AREA_INFO fshdlCtrlMin = {
		.posY = D_IM_PRO_FSHDL_FFSHV_MIN,
		.posX = D_IM_PRO_FSHDL_FFSHH_MIN,
		.lines = D_IM_PRO_FSHDL_FFSHVW_MIN,
		.width = D_IM_PRO_FSHDL_FFSHHW_MIN,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSrofshdl_E_IM_PRO_FSHDL_CH_0; self->priv->ch < ImproSrofshdl_E_IM_PRO_FSHDL_CH_1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_srofshdl_set_area(self->priv->improSrofshdl, self->priv->unitNo,
						self->priv->ch, &fshdlCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_set_area(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_5(self->priv->imPro21Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &fshdlCtrlMax);
				}

				self->priv->ercd = impro_srofshdl_set_area(self->priv->improSrofshdl, self->priv->unitNo,
						self->priv->ch, &fshdlCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_set_area(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_5(self->priv->imPro21Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &fshdlCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_1_6(CtImPro21* self, const kuint32 idx)
{
	TimproFshdlFrameCtrl fshdlCtrlMax = {
		.selectFormat = ImproSrofshdl_E_IM_PRO_FSHDL_CORRECTION_FORMAT_7,
		.frameHorizontalSize = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRH_MAX,
		.frameVerticalSize = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRV_MAX,
		.horizontalPixel = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPH_MAX,
		.verticalPixel = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPV_MAX,
		.inverseBase = 65535,
		.inverseExponent = 11,
		.startPosH = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTH_MAX,
		.startPosV = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTV_MAX,
		.montagePosH = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHWPH_MAX,
		.satCorrectionEnabled = ImproSrofshdl_E_IM_PRO_FSHDL_SAT_CORRECTION_EN,
		.satSlopeGain[0] = 4095,
		.satSlopeGain[1] = 4095,
		.satSlopeGain[2] = 4095,
		.satSlopeGain[3] = 4095,
	};

	TimproFshdlFrameCtrl fshdlCtrlMin = {
		.selectFormat = ImproSrofshdl_E_IM_PRO_FSHDL_CORRECTION_FORMAT_0,
		.frameHorizontalSize = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRH_MIN,
		.frameVerticalSize = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRV_MIN,
		.horizontalPixel = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPH_MIN,
		.verticalPixel = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPV_MIN,
		.inverseBase = 0,
		.inverseExponent = 0,
		.startPosH = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTH_MIN,
		.startPosV = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTV_MIN,
		.montagePosH = ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHWPH_MIN,
		.satCorrectionEnabled = ImproSrofshdl_E_IM_PRO_FSHDL_SAT_CORRECTION_DIS,
		.satSlopeGain[0] = 0,
		.satSlopeGain[1] = 0,
		.satSlopeGain[2] = 0,
		.satSlopeGain[3] = 0,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSrofshdl_E_IM_PRO_FSHDL_CH_0; self->priv->ch < ImproSrofshdl_E_IM_PRO_FSHDL_CH_1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_srofshdl_set_frame(self->priv->improSrofshdl, self->priv->unitNo,
						self->priv->ch, &fshdlCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_set_frame(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_6(self->priv->imPro21Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &fshdlCtrlMax);
				}

				self->priv->ercd = impro_srofshdl_set_frame(self->priv->improSrofshdl, self->priv->unitNo,
						self->priv->ch, &fshdlCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_set_frame(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_6(self->priv->imPro21Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &fshdlCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_1_7(CtImPro21* self, const kuint32 idx)
{
	kuint16 fshdlCtrlMax = 1023;
	kuint16 fshdlCtrlMin = 4;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSrofshdl_E_IM_PRO_FSHDL_CH_0; self->priv->ch < ImproSrofshdl_E_IM_PRO_FSHDL_CH_1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_srofshdl_set_coeff_read_line_wait(self->priv->improSrofshdl,
						self->priv->unitNo, self->priv->ch, fshdlCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_set_coeff_read_line_wait(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_7(self->priv->imPro21Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, fshdlCtrlMax);
				}

				self->priv->ercd = impro_srofshdl_set_coeff_read_line_wait(self->priv->improSrofshdl,
						self->priv->unitNo, self->priv->ch, fshdlCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_set_coeff_read_line_wait(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_7(self->priv->imPro21Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, fshdlCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_1_8(CtImPro21* self, const kuint32 idx)
{
	const TimproRdmaFshdlAddr* fshdl_ctrl;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSrofshdl_E_IM_PRO_FSHDL_CH_0; self->priv->ch < ImproSrofshdl_E_IM_PRO_FSHDL_CH_1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_srofshdl_get_rdma_addr_fshdl_cntl(self->priv->improSrofshdl, self->priv->unitNo,
						self->priv->ch, &fshdl_ctrl);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srofshdl_get_rdma_addr_fshdl_cntl(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_1_print_8(self->priv->imPro21Print, "", self->priv->unitNo, self->priv->ch,
							self->priv->ercd, &fshdl_ctrl);
				}
            }
        }
    }
}

void ct_im_pro2_1_9(CtImPro21* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			Im_PRO_CAG_Start(self->priv->improSrofshdl, self->priv->unitNo);
			im_pro_2_1_print_9(self->priv->imPro21Print, self->priv->unitNo);
		}
    }
}
#endif  //CO_CT_IM_PRO_DISABLE

CtImPro21* ct_im_pro2_1_new(void)
{
	CtImPro21* self = k_object_new_with_private(CT_TYPE_IM_PRO2_1, sizeof(CtImPro21Private));

	return self;
}

