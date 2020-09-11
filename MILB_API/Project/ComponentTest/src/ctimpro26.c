/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro26
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsroffsh.h"
#include "improsroff.h"
#include "improsrosdc.h"
#include "ctimpro26.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro26, ct_im_pro2_6)
#define CT_IM_PRO2_6_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro26Private, CT_TYPE_IM_PRO2_6))


struct _CtImPro26Private
{
	ImproSroffsh *improSroffsh;
	ImproSroff *improSroff;
	ImproSrosdc *improSrosdc;
	ImPro26Print *imPro26Print;
	kint32 ercd;
	E_IM_PRO_UNIT_NUM unitNo;
	kuchar ch;
};


/**********
 * IMPL
 */
static void ct_im_pro2_6_constructor(CtImPro26 *self)
{
	self->priv = CT_IM_PRO2_6_GET_PRIVATE(self);
	self->priv->improSroffsh = impro_sroffsh_new();
	self->priv->improSroff = impro_sroff_new();
	self->priv->improSrosdc = impro_srosdc_new();
	self->priv->imPro26Print = im_pro_2_6_print_new();
	self->priv->ercd = 0;
	self->priv->unitNo = 0;
	self->priv->ch = 0;
}

static void ct_im_pro2_6_destructor(CtImPro26 *self)
{
	CtImPro26Private *priv = CT_IM_PRO2_6_GET_PRIVATE(self);

	if (priv->improSroffsh) {
		k_object_unref(priv->improSroffsh);
		priv->improSroffsh = NULL;
	}

	if (priv->improSroff) {
		k_object_unref(priv->improSroff);
		priv->improSroff = NULL;
	}

	if (priv->improSrosdc) {
		k_object_unref(priv->improSrosdc);
		priv->improSrosdc = NULL;
	}

	if (priv->imPro26Print) {
		k_object_unref(priv->imPro26Print);
		priv->imPro26Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro2_6_0(CtImPro26* self, const kuint32 idx)
{
	kuint16 ffshCtrlMax = 1023;
	kuint16 ffshCtrlMin = 4;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroffsh_E_IM_PRO_FFSH_CH0; self->priv->ch < ImproSroffsh_E_IM_PRO_FFSH_CH1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_sroffsh_set_coeff_read_line_wait(self->priv->improSroffsh,
						self->priv->unitNo, self->priv->ch, ffshCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroffsh_set_coeff_read_line_wait(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_6_print_0(self->priv->imPro26Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, ffshCtrlMax);
				}

				self->priv->ercd = impro_sroffsh_set_coeff_read_line_wait(self->priv->improSroffsh,
						self->priv->unitNo, self->priv->ch, ffshCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroffsh_set_coeff_read_line_wait(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_6_print_0(self->priv->imPro26Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, ffshCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_6_1(CtImPro26* self, const kuint32 idx)
{
    const TimproRdmaFfshAddr* ffshCtrl;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroffsh_E_IM_PRO_FFSH_CH0; self->priv->ch < ImproSroffsh_E_IM_PRO_FFSH_CH1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_sroffsh_get_rdma_addr_ffsh_cntl(self->priv->improSroffsh, self->priv->unitNo,
						self->priv->ch, &ffshCtrl);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroffsh_get_rdma_addr_ffsh_cntl(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_6_print_1(self->priv->imPro26Print, "", self->priv->unitNo, self->priv->ch,
							self->priv->ercd, &ffshCtrl);
				}
            }
        }
    }
}

void ct_im_pro2_6_2(CtImPro26* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroff_E_IM_PRO_FF_CH0; self->priv->ch < ImproSroff_E_IM_PRO_FF_CH1 + 1; self->priv->ch++) {
				impro_sroff_start(self->priv->improSroff, self->priv->unitNo, self->priv->ch);
				im_pro_2_6_print_2(self->priv->imPro26Print, self->priv->unitNo, self->priv->ch);
			}
        }
    }
}

void ct_im_pro2_6_3(CtImPro26* self, const kuint32 idx)
{
	kuchar force;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (force = 0; force < 2 + 1; force++) {
				for (self->priv->ch = ImproSroff_E_IM_PRO_FF_CH0; self->priv->ch < ImproSroff_E_IM_PRO_FF_CH1 + 1;
						self->priv->ch++) {
#ifdef CO_DEBUG_ON_PC
					ioPro.imgPipe[self->priv->unitNo].sro.ff[self->priv->ch].fftrg.bit.fftrg = 3;
#endif
					impro_sroff_stop(self->priv->improSroff, self->priv->unitNo, self->priv->ch, force);
					im_pro_2_6_print_3(self->priv->imPro26Print, self->priv->unitNo, self->priv->ch, force);
				}
            }
        }
    }
}

void ct_im_pro2_6_4(CtImPro26* self, const kuint32 idx)
{
    TimproFfCtrl ffCtrlMax = {
        .ffdefts = 16383,
        .mnwgt = 511,
        .sbwgt = 511,
    };

    TimproFfCtrl ffCtrlMin = {
        .ffdefts = 0,
        .mnwgt = -512,
        .sbwgt = -512,
    };

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroff_E_IM_PRO_FF_CH0; self->priv->ch < ImproSroff_E_IM_PRO_FF_CH1 + 1; self->priv->ch++) {
				self->priv->ercd = impro_sroff_ctrl(self->priv->improSroff, self->priv->unitNo, self->priv->ch,
						&ffCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroff_ctrl(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_6_print_4(self->priv->imPro26Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffCtrlMax);
				}

				self->priv->ercd = impro_sroff_ctrl(self->priv->improSroff, self->priv->unitNo, self->priv->ch,
						&ffCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroff_ctrl(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_6_print_4(self->priv->imPro26Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_6_5(CtImPro26* self, const kuint32 idx)
{
    T_IM_PRO_AREA_INFO ffCtrlMax = {//TODO
        .posX = 12287,
        .posY = 8191,
        .width = 12287,
        .lines = 8191,
    };

    T_IM_PRO_AREA_INFO ffCtrlMin = {
        .posX = 0,
        .posY = 0,
        .width = 4,
        .lines = 4,
    };

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroff_E_IM_PRO_FF_CH0; self->priv->ch < ImproSroff_E_IM_PRO_FF_CH1 + 1; self->priv->ch++) {
				self->priv->ercd = impro_sroff_set_area(self->priv->improSroff, self->priv->unitNo,
						self->priv->ch, &ffCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroff_set_area(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_6_print_5(self->priv->imPro26Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffCtrlMax);
				}

				self->priv->ercd = impro_sroff_set_area(self->priv->improSroff, self->priv->unitNo,
						self->priv->ch, &ffCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroff_set_area(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_6_print_5(self->priv->imPro26Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_6_6(CtImPro26* self, const kuint32 idx)
{
    TimproFfLpfCtrl ffCtrlMax = {
        .b0 = 255,
        .b1 = 255,
        .b2 = 255,
    };

    TimproFfLpfCtrl ffCtrlMin = {
        .b0 = 0,
        .b1 = 0,
        .b2 = 0,
    };

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroff_E_IM_PRO_FF_CH0; self->priv->ch < ImproSroff_E_IM_PRO_FF_CH1 + 1; self->priv->ch++) {
				self->priv->ercd = impro_sroff_set_fir_filter(self->priv->improSroff, self->priv->unitNo,
						self->priv->ch, &ffCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroff_set_fir_filter(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_6_print_6(self->priv->imPro26Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffCtrlMax);
				}

				self->priv->ercd = impro_sroff_set_fir_filter(self->priv->improSroff, self->priv->unitNo,
						self->priv->ch, &ffCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroff_set_fir_filter(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_6_print_6(self->priv->imPro26Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_6_7(CtImPro26* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = E_IM_PRO_SDC_CH0; self->priv->ch < E_IM_PRO_SDC_CH1 + 1; self->priv->ch++) {//TODO
				impro_srosdc_start(self->priv->improSrosdc, self->priv->unitNo, self->priv->ch);
				im_pro_2_6_print_7(self->priv->imPro26Print, self->priv->unitNo, self->priv->ch);
			}
        }
    }
}

void ct_im_pro2_6_8(CtImPro26* self, const kuint32 idx)
{
	kuchar force;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (force = 0; force < 2 + 1; force++) {
				for (self->priv->ch = E_IM_PRO_SDC_CH0; self->priv->ch < E_IM_PRO_SDC_CH1 + 1;
						self->priv->ch++) {
#ifdef CO_DEBUG_ON_PC
					ioPro.imgPipe[self->priv->unitNo].sro.sdc[self->priv->ch].sdctrg.bit.sdctrg = 3;
#endif
					impro_srosdc_stop(self->priv->improSrosdc, self->priv->unitNo, self->priv->ch, force);
					im_pro_2_6_print_8(self->priv->imPro26Print, self->priv->unitNo, self->priv->ch, force);
				}
            }
        }
    }
}

void ct_im_pro2_6_9(CtImPro26* self, const kuint32 idx)
{
    TimproSdcCtrl sdcCtrlMax = {
        .sdc_mode = ImproSrosdc_E_IM_PRO_SDC_MODE_COOP_DPC_AFPB_GAIN2,
        .afpb_output_ptn = ImproSrosdc_E_IM_PRO_SDC_AFPB_OUTPUT_PTN_AFOB_ONLY,
        .monochrome_mode = ImproSrosdc_E_IM_PRO_SDC_MONOCHROME_MODE_MONOCHROME_CORRECTION,
        .afpb_enabled = ImproSrosdc_E_IM_PRO_SDC_AFPB_EN,
    };

    TimproSdcCtrl   sdcCtrlMin = {
        .sdc_mode = ImproSrosdc_E_IM_PRO_SDC_MODE_SDC,
        .afpb_output_ptn = ImproSrosdc_E_IM_PRO_SDC_AFPB_OUTPUT_PTN_ALL_OR_SDC_ONLY,
        .monochrome_mode = ImproSrosdc_E_IM_PRO_SDC_MONOCHROME_MODE_BAYER_CORRECTION,
        .afpb_enabled = ImproSrosdc_E_IM_PRO_SDC_AFPB_DIS,
    };

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = E_IM_PRO_SDC_CH0; self->priv->ch < E_IM_PRO_SDC_CH1 + 1; self->priv->ch++) {
				self->priv->ercd = impro_srosdc_ctrl(self->priv->improSrosdc, self->priv->unitNo, self->priv->ch,
						&sdcCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srosdc_ctrl(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_6_print_9(self->priv->imPro26Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &sdcCtrlMax);
				}

				self->priv->ercd = impro_srosdc_ctrl(self->priv->improSrosdc, self->priv->unitNo, self->priv->ch,
						&sdcCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srosdc_ctrl(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_6_print_9(self->priv->imPro26Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &sdcCtrlMin);
				}
			}
        }
    }
}
#endif  //CO_CT_IM_PRO_DISABLE

CtImPro26* ct_im_pro2_6_new(void)
{
	CtImPro26* self = k_object_new_with_private(CT_TYPE_IM_PRO2_6, sizeof(CtImPro26Private));

	return self;
}

