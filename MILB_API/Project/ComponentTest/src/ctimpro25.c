/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro25
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsrovrb.h"
#include "improsroffsh.h"
#include "ctimpro25.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro25, ct_im_pro2_5)
#define CT_IM_PRO2_5_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro25Private, CT_TYPE_IM_PRO2_5))


struct _CtImPro25Private
{
	ImproSrovrb *improSrovrb;
	ImproSroffsh *improSroffsh;
	ImPro25Print *imPro25Print;
	kint32 ercd;
	E_IM_PRO_UNIT_NUM unitNo;
	kuchar ch;
	kuchar paenTrg;
};


/**********
 * IMPL
 */
static void ct_im_pro2_5_constructor(CtImPro25 *self)
{
	CtImPro25Private *priv = CT_IM_PRO2_5_GET_PRIVATE(self);
	self->priv->improSrovrb = impro_srovrb_new();
	self->priv->improSroffsh = impro_sroffsh_new();
	self->priv->imPro25Print = im_pro_2_5_print_new();
	self->priv->ercd = 0;
	self->priv->unitNo = 0;
	self->priv->ch = 0;
	self->priv->paenTrg = 0;
}

static void ct_im_pro2_5_destructor(CtImPro25 *self)
{
	CtImPro25Private *priv = CT_IM_PRO2_5_GET_PRIVATE(self);

	if (priv->improSrovrb) {
		k_object_unref(priv->improSrovrb);
		priv->improSrovrb = NULL;
	}

	if (priv->improSroffsh) {
		k_object_unref(priv->improSroffsh);
		priv->improSroffsh = NULL;
	}

	if (priv->imPro25Print) {
		k_object_unref(priv->imPro25Print);
		priv->imPro25Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro2_5_0(CtImPro25* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			impro_srovrb_start(self->priv->improSrovrb, self->priv->unitNo);
			im_pro_2_5_print_0(self->priv->imPro25Print, self->priv->unitNo);
		}
    }
}

void ct_im_pro2_5_1(CtImPro25* self, const kuint32 idx)
{
	kuchar force;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (force = 0; force < 2 + 1; force++) {
#ifdef CO_DEBUG_ON_PC
				ioPro.imgPipe[self->priv->unitNo].sro.VRB.VRBTRG.bit.VRBTRG = 3;
#endif
				impro_srovrb_stop(self->priv->improSrovrb, self->priv->unitNo, force);
				im_pro_2_5_print_1(self->priv->imPro25Print, self->priv->unitNo, force);
			}
        }
    }
}

void ct_im_pro2_5_2(CtImPro25* self, const kuint32 idx)
{
    TimproVrbCtrl vrbCtrlMax = {
        .inPosX = ImproSrovrb_D_IM_PRO_VRB_VRBH_MAX,
        .inPosY = ImproSrovrb_D_IM_PRO_VRB_VRBV_MAX,
        .inWidth = ImproSrovrb_D_IM_PRO_VRB_VRBHW_MAX,
        .inLines = ImproSrovrb_D_IM_PRO_VRB_VRBVW_MAX,
        .cycle = ImproSrovrb_D_IM_PRO_VRB_VRBSCYC_MAX,
        .coefficient0[0][0] = 65535,
        .coefficient0[0][1] = 65535,
        .coefficient0[0][2] = 65535,
        .coefficient0[1][0] = 65535,
        .coefficient0[1][1] = 65535,
        .coefficient0[1][2] = 65535,
        .coefficient0[2][0] = 65535,
        .coefficient0[2][1] = 65535,
        .coefficient0[2][2] = 65535,
        .coefficient0[3][0] = 65535,
        .coefficient0[3][1] = 65535,
        .coefficient0[3][2] = 65535,
        .coefficient0[4][0] = 65535,
        .coefficient0[4][1] = 65535,
        .coefficient0[4][2] = 65535,
        .coefficient0[5][0] = 65535,
        .coefficient0[5][1] = 65535,
        .coefficient0[5][2] = 65535,
        .coefficient0[6][0] = 65535,
        .coefficient0[6][1] = 65535,
        .coefficient0[6][2] = 65535,
        .coefficient0[7][0] = 65535,
        .coefficient0[7][1] = 65535,
        .coefficient0[7][2] = 65535,
        .coefficient0[8][0] = 65535,
        .coefficient0[8][1] = 65535,
        .coefficient0[8][2] = 65535,
        .coefficient0[9][0] = 65535,
        .coefficient0[9][1] = 65535,
        .coefficient0[9][2] = 65535,
        .coefficient1[0][0] = 65535,
        .coefficient1[0][1] = 65535,
        .coefficient1[0][2] = 65535,
        .coefficient1[1][0] = 65535,
        .coefficient1[1][1] = 65535,
        .coefficient1[1][2] = 65535,
        .coefficient1[2][0] = 65535,
        .coefficient1[2][1] = 65535,
        .coefficient1[2][2] = 65535,
        .coefficient1[3][0] = 65535,
        .coefficient1[3][1] = 65535,
        .coefficient1[3][2] = 65535,
        .coefficient1[4][0] = 65535,
        .coefficient1[4][1] = 65535,
        .coefficient1[4][2] = 65535,
        .coefficient1[5][0] = 65535,
        .coefficient1[5][1] = 65535,
        .coefficient1[5][2] = 65535,
        .coefficient1[6][0] = 65535,
        .coefficient1[6][1] = 65535,
        .coefficient1[6][2] = 65535,
        .coefficient1[7][0] = 65535,
        .coefficient1[7][1] = 65535,
        .coefficient1[7][2] = 65535,
        .coefficient1[8][0] = 65535,
        .coefficient1[8][1] = 65535,
        .coefficient1[8][2] = 65535,
        .coefficient1[9][0] = 65535,
        .coefficient1[9][1] = 65535,
        .coefficient1[9][2] = 65535,
    };

    TimproVrbCtrl vrbCtrlMin = {
        .inPosX = ImproSrovrb_D_IM_PRO_VRB_VRBH_MIN,
        .inPosY = ImproSrovrb_D_IM_PRO_VRB_VRBV_MIN,
        .inWidth = ImproSrovrb_D_IM_PRO_VRB_VRBHW_MIN,
        .inLines = ImproSrovrb_D_IM_PRO_VRB_VRBVW_MIN,
        .cycle = ImproSrovrb_D_IM_PRO_VRB_VRBSCYC_MIN,
        .coefficient0[0][0] = 0,
        .coefficient0[0][1] = 0,
        .coefficient0[0][2] = 0,
        .coefficient0[1][0] = 0,
        .coefficient0[1][1] = 0,
        .coefficient0[1][2] = 0,
        .coefficient0[2][0] = 0,
        .coefficient0[2][1] = 0,
        .coefficient0[2][2] = 0,
        .coefficient0[3][0] = 0,
        .coefficient0[3][1] = 0,
        .coefficient0[3][2] = 0,
        .coefficient0[4][0] = 0,
        .coefficient0[4][1] = 0,
        .coefficient0[4][2] = 0,
        .coefficient0[5][0] = 0,
        .coefficient0[5][1] = 0,
        .coefficient0[5][2] = 0,
        .coefficient0[6][0] = 0,
        .coefficient0[6][1] = 0,
        .coefficient0[6][2] = 0,
        .coefficient0[7][0] = 0,
        .coefficient0[7][1] = 0,
        .coefficient0[7][2] = 0,
        .coefficient0[8][0] = 0,
        .coefficient0[8][1] = 0,
        .coefficient0[8][2] = 0,
        .coefficient0[9][0] = 0,
        .coefficient0[9][1] = 0,
        .coefficient0[9][2] = 0,
        .coefficient1[0][0] = 0,
        .coefficient1[0][1] = 0,
        .coefficient1[0][2] = 0,
        .coefficient1[1][0] = 0,
        .coefficient1[1][1] = 0,
        .coefficient1[1][2] = 0,
        .coefficient1[2][0] = 0,
        .coefficient1[2][1] = 0,
        .coefficient1[2][2] = 0,
        .coefficient1[3][0] = 0,
        .coefficient1[3][1] = 0,
        .coefficient1[3][2] = 0,
        .coefficient1[4][0] = 0,
        .coefficient1[4][1] = 0,
        .coefficient1[4][2] = 0,
        .coefficient1[5][0] = 0,
        .coefficient1[5][1] = 0,
        .coefficient1[5][2] = 0,
        .coefficient1[6][0] = 0,
        .coefficient1[6][1] = 0,
        .coefficient1[6][2] = 0,
        .coefficient1[7][0] = 0,
        .coefficient1[7][1] = 0,
        .coefficient1[7][2] = 0,
        .coefficient1[8][0] = 0,
        .coefficient1[8][1] = 0,
        .coefficient1[8][2] = 0,
        .coefficient1[9][0] = 0,
        .coefficient1[9][1] = 0,
        .coefficient1[9][2] = 0,
    };

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srovrb_ctrl(self->priv->improSrovrb, self->priv->unitNo, &vrbCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srovrb_ctrl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_5_print_2(self->priv->imPro25Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &vrbCtrlMax);
			}

			self->priv->ercd = impro_srovrb_ctrl(self->priv->improSrovrb, self->priv->unitNo, &vrbCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srovrb_ctrl(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_5_print_2(self->priv->imPro25Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &vrbCtrlMin);
			}
        }
    }
}

void ct_im_pro2_5_3(CtImPro25* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->paenTrg = 0; self->priv->paenTrg < 2 + 1; self->priv->paenTrg++) {
				self->priv->ercd = impro_srovrb_set_paen(self->priv->improSrovrb, self->priv->unitNo,
						self->priv->paenTrg);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srovrb_set_paen(%u) Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ercd));
				} else {
					im_pro_2_5_print_3(self->priv->imPro25Print, self->priv->unitNo, self->priv->paenTrg);
				}
            }
        }
    }
}

void ct_im_pro2_5_4(CtImPro25* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroffsh_E_IM_PRO_FFSH_CH0; self->priv->ch < ImproSroffsh_E_IM_PRO_FFSH_CH1 + 1;
					self->priv->ch++) {
				impro_sroffsh_start(self->priv->improSroffsh, self->priv->unitNo, self->priv->ch);
				im_pro_2_5_print_4(self->priv->imPro25Print, self->priv->unitNo, self->priv->ch);
			}
        }
    }
}

void ct_im_pro2_5_5(CtImPro25* self, const kuint32 idx)
{
	kuchar force;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (force = 0; force < 2 + 1; force++) {
				for (self->priv->ch = ImproSroffsh_E_IM_PRO_FFSH_CH0; self->priv->ch < ImproSroffsh_E_IM_PRO_FFSH_CH1 + 1;
						self->priv->ch++) {
#ifdef CO_DEBUG_ON_PC
					ioPro.imgPipe[self->priv->unitNo].sro.ffsh[self->priv->ch].ffshtrg.bit.ffshtrg = 3;
#endif
					impro_sroffsh_stop(self->priv->improSroffsh, self->priv->unitNo, self->priv->ch, force);
					im_pro_2_5_print_5(self->priv->imPro25Print, self->priv->unitNo, self->priv->ch, force);
				}
			}
        }
    }
}

void ct_im_pro2_5_6(CtImPro25* self, const kuint32 idx)
{
    TimproFfshCtrl ffshCtrlMax = {
        .hSizeCorrectionCoeff = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRH_MAX,
        .vSizeCorrectionCoeff = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRV_MAX,
        .hPixelUnitInterpolation = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPH_MAX,
        .vPixelUnitInterpolation = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPV_MAX,
        .radInverseCoeffInterpolation = 65535,
        .expInverseCoeffInterpolation = 11,
        .hStartPosCoeff = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTH_MAX,
        .vStartPosCoeff = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTV_MAX,
    };

    TimproFfshCtrl ffshCtrlMin = {
        .hSizeCorrectionCoeff = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRH_MIN,
        .vSizeCorrectionCoeff = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRV_MIN,
        .hPixelUnitInterpolation = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPH_MIN,
        .vPixelUnitInterpolation = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPV_MIN,
        .radInverseCoeffInterpolation = 0,
        .expInverseCoeffInterpolation = 0,
        .hStartPosCoeff = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTH_MAX,
        .vStartPosCoeff = ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTV_MAX,
    };

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroffsh_E_IM_PRO_FFSH_CH0; self->priv->ch < ImproSroffsh_E_IM_PRO_FFSH_CH1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_sroffsh_ctrl(self->priv->improSroffsh, self->priv->unitNo, self->priv->ch,
						&ffshCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroffsh_ctrl(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_5_print_6(self->priv->imPro25Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffshCtrlMax);
				}

				self->priv->ercd = impro_sroffsh_ctrl(self->priv->improSroffsh, self->priv->unitNo, self->priv->ch,
						&ffshCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroffsh_ctrl(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_5_print_6(self->priv->imPro25Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffshCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_5_7(CtImPro25* self, const kuint32 idx)
{
    TimproFfshBlendCtrl ffshCtrlMax = {
        .frameCorrectionBlend0 = 511,
        .frameCorrectionBlend1 = 511,
    };

    TimproFfshBlendCtrl ffshCtrlMin = {
        .frameCorrectionBlend0 = -512,
        .frameCorrectionBlend1 = -512,
    };

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroffsh_E_IM_PRO_FFSH_CH0; self->priv->ch < ImproSroffsh_E_IM_PRO_FFSH_CH1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_sroffsh_set_blend(self->priv->improSroffsh, self->priv->unitNo,
						self->priv->ch, &ffshCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroffsh_set_blend(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_5_print_7(self->priv->imPro25Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffshCtrlMax);
				}

				self->priv->ercd = impro_sroffsh_set_blend(self->priv->improSroffsh, self->priv->unitNo,
						self->priv->ch, &ffshCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroffsh_set_blend(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_5_print_7(self->priv->imPro25Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffshCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro2_5_8(CtImPro25* self, const kuint32 idx)
{
    TimproFfshArea ffshCtrlMax = {
        .ffshArea.posX = ImproSroffsh_D_IM_PRO_FFSH_FFSHH_MAX,
        .ffshArea.posY = ImproSroffsh_D_IM_PRO_FFSH_FFSHV_MAX,
        .ffshArea.width = ImproSroffsh_D_IM_PRO_FFSH_FFSHHW_MAX,
        .ffshArea.lines = ImproSroffsh_D_IM_PRO_FFSH_FFSHVW_MAX,
    };

    TimproFfshArea ffshCtrlMin = {
        .ffshArea.posX = ImproSroffsh_D_IM_PRO_FFSH_FFSHH_MIN,
        .ffshArea.posY = ImproSroffsh_D_IM_PRO_FFSH_FFSHV_MIN,
        .ffshArea.width = ImproSroffsh_D_IM_PRO_FFSH_FFSHHW_MIN,
        .ffshArea.lines = ImproSroffsh_D_IM_PRO_FFSH_FFSHVW_MIN,
    };

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroffsh_E_IM_PRO_FFSH_CH0; self->priv->ch < ImproSroffsh_E_IM_PRO_FFSH_CH1 + 1;
					self->priv->ch++) {
				self->priv->ercd = impro_sroffsh_set_area(self->priv->improSroffsh, self->priv->unitNo,
						self->priv->ch, &ffshCtrlMax);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroffsh_set_area(%u %u) max_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_5_print_8(self->priv->imPro25Print, "max_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffshCtrlMax);
				}

				self->priv->ercd = impro_sroffsh_set_area(self->priv->improSroffsh, self->priv->unitNo,
						self->priv->ch, &ffshCtrlMin);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroffsh_set_area(%u %u) min_para Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ch, self->priv->ercd));
				} else {
					im_pro_2_5_print_8(self->priv->imPro25Print, "min_para", self->priv->unitNo,
							self->priv->ch, self->priv->ercd, &ffshCtrlMin);
				}
			}
        }
    }
}

void ct_im_pro2_5_9(CtImPro25* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->ch = ImproSroffsh_E_IM_PRO_FFSH_CH0; self->priv->ch < ImproSroffsh_E_IM_PRO_FFSH_CH1 + 1;
					self->priv->ch++) {
				for (self->priv->paenTrg = 0; self->priv->paenTrg < 2 + 1; self->priv->paenTrg++) {
					self->priv->ercd = impro_sroffsh_set_paen(self->priv->improSroffsh, self->priv->unitNo,
							self->priv->ch, self->priv->paenTrg);
					im_pro_2_5_print_9(self->priv->imPro25Print, self->priv->unitNo, self->priv->ch,
							self->priv->ercd, self->priv->paenTrg);
				}
            }
        }
    }
}
#endif  //CO_CT_IM_PRO_DISABLE

CtImPro25* ct_im_pro2_5_new(void)
{
	CtImPro25* self = k_object_new_with_private(CT_TYPE_IM_PRO2_5, sizeof(CtImPro25Private));

	return self;
}

