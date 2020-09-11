/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro24
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsroffc.h"
#include "improsrohrb.h"
#include "ctimpro24.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro24, ct_im_pro2_4)
#define CT_IM_PRO2_4_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro24Private, CT_TYPE_IM_PRO2_4))


struct _CtImPro24Private
{
	ImproSroffc *improSroffc;
	ImproSrohrb *improSrohrb;
	ImPro24Print *imPro24Print;
	kint32 ercd;
	E_IM_PRO_UNIT_NUM unitNo;
	kuchar paenTrg;
};


/**********
 * IMPL
 */
static void ct_im_pro2_4_constructor(CtImPro24 *self)
{
	self->priv = CT_IM_PRO2_4_GET_PRIVATE(self);
	self->priv->improSroffc = impro_sroffc_new();
	self->priv->improSrohrb = impro_srohrb_new();
	self->priv->imPro24Print = im_pro_2_4_print_new();
	self->priv->ercd = 0;
	self->priv->unitNo = 0;
	self->priv->paenTrg = 0;
}

static void ct_im_pro2_4_destructor(CtImPro24 *self)
{
	CtImPro24Private *priv = CT_IM_PRO2_4_GET_PRIVATE(self);

	if (priv->improSroffc) {
		k_object_unref(priv->improSroffc);
		priv->improSroffc = NULL;
	}

	if (priv->improSrohrb) {
		k_object_unref(priv->improSrohrb);
		priv->improSrohrb = NULL;
	}

	if (priv->imPro24Print) {
		k_object_unref(priv->imPro24Print);
		priv->imPro24Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro2_4_0(CtImPro24* self, const kuint32 idx)
{
	TimproFfcCtrl ffcCtrlMax = {
		.coefHorizontalSize = 314,
		.coefVerticalSize = 1122,
		.horizontalPixel = 724,
		.verticalPixel = 724,
		.inverseBase = 65535,
		.inverseExponent = 11,
		.coefPosX = 722, .coefPosY = 722, };

	TimproFfcCtrl ffcCtrlMin = {
		.coefHorizontalSize = 4,
		.coefVerticalSize = 4,
		.horizontalPixel = 16,
		.verticalPixel = 16,
		.inverseBase = 0,
		.inverseExponent = 0,
		.coefPosX = 0,
		.coefPosY = 0,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_sroffc_ctrl(self->priv->improSroffc, self->priv->unitNo, &ffcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_sroffc_ctrl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_4_print_0(self->priv->imPro24Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &ffcCtrlMax);
			}

			self->priv->ercd = impro_sroffc_ctrl(self->priv->improSroffc, self->priv->unitNo, &ffcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_sroffc_ctrl(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_4_print_0(self->priv->imPro24Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &ffcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_4_1(CtImPro24* self, const kuint32 idx)
{
	TimproFfcBlendCtrl ffcCtrlMax = {
		.blendRatio0 = 511,
		.blendRatio1 = 511,
	};

	TimproFfcBlendCtrl ffcCtrlMin = {
		.blendRatio0 = -512,
		.blendRatio1 = -512,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_sroffc_set_blend(self->priv->improSroffc, self->priv->unitNo, &ffcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_sroffc_set_blend(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_4_print_1(self->priv->imPro24Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &ffcCtrlMax);
			}

			self->priv->ercd = impro_sroffc_set_blend(self->priv->improSroffc, self->priv->unitNo, &ffcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_sroffc_set_blend(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_4_print_1(self->priv->imPro24Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &ffcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_4_2(CtImPro24* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->paenTrg = 0; self->priv->paenTrg < 2 + 1; self->priv->paenTrg++) {
				self->priv->ercd = impro_sroffc_set_paen(self->priv->improSroffc, self->priv->unitNo,
						self->priv->paenTrg);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_sroffc_set_paen(%u) Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ercd));
				} else {
					im_pro_2_4_print_2(self->priv->imPro24Print, self->priv->unitNo, self->priv->paenTrg);
				}
            }
        }
    }
}

void ct_im_pro2_4_3(CtImPro24* self, const kuint32 idx)
{
	TimproFfcArea ffcCtrlMax = {
		.posX = ImproSroffc_D_IM_PRO_FFC_FCH_MAX,
		.posY = ImproSroffc_D_IM_PRO_FFC_FCV_MAX,
		.width = ImproSroffc_D_IM_PRO_FFC_FCHW_MAX,
		.lines = ImproSroffc_D_IM_PRO_FFC_FCVW_MAX,
	};

	TimproFfcArea ffcCtrlMin = {
		.posX = ImproSroffc_D_IM_PRO_FFC_FCH_MIN,
		.posY = ImproSroffc_D_IM_PRO_FFC_FCV_MIN,
		.width = ImproSroffc_D_IM_PRO_FFC_FCHW_MIN,
		.lines = ImproSroffc_D_IM_PRO_FFC_FCVW_MIN,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_sroffc_set_area(self->priv->improSroffc, self->priv->unitNo, &ffcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_sroffc_set_area(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_4_print_3(self->priv->imPro24Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &ffcCtrlMax);
			}

			self->priv->ercd = impro_sroffc_set_area(self->priv->improSroffc, self->priv->unitNo, &ffcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_sroffc_set_area(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_4_print_3(self->priv->imPro24Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &ffcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_4_4(CtImPro24* self, const kuint32 idx)
{
	kuint16 ffcCtrlMax = 1023;
	kuint16 ffcCtrlMin = 4;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_sroffc_set_coeff_read_line_wait(self->priv->improSroffc, self->priv->unitNo,
					ffcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_sroffc_set_coeff_read_line_wait(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_4_print_4(self->priv->imPro24Print, "max_para", self->priv->unitNo,
						self->priv->ercd, ffcCtrlMax);
			}

			self->priv->ercd = impro_sroffc_set_coeff_read_line_wait(self->priv->improSroffc, self->priv->unitNo,
					ffcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_sroffc_set_coeff_read_line_wait(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_4_print_4(self->priv->imPro24Print, "min_para", self->priv->unitNo,
						self->priv->ercd, ffcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_4_5(CtImPro24* self, const kuint32 idx)
{
	const TimproRdmaFfcAddr* ffcCtrl;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_sroffc_get_rdma_addr_ffc_cntl(self->priv->improSroffc, self->priv->unitNo,
					&ffcCtrl);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_sroffc_get_rdma_addr_ffc_cntl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_4_print_5(self->priv->imPro24Print, "", self->priv->unitNo, self->priv->ercd, &ffcCtrl);
			}
        }
    }
}

void ct_im_pro2_4_6(CtImPro24* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			impro_srohrb_start(self->priv->improSrohrb, self->priv->unitNo);
			im_pro_2_4_print_6(self->priv->imPro24Print, self->priv->unitNo);
		}
    }
}

void ct_im_pro2_4_7(CtImPro24* self, const kuint32 idx)
{
	kuchar force;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (force = 0; force < 2 + 1; force++) {
#ifdef CO_DEBUG_ON_PC
				ioPro.imgPipe[self->priv->unitNo].sro.hrb.hrbtrg.bit.hrbtrg = 3;
#endif
				impro_srohrb_stop(self->priv->improSrohrb, self->priv->unitNo, force);
				im_pro_2_4_print_7(self->priv->imPro24Print, self->priv->unitNo, force);
			}
		}
    }
}

void ct_im_pro2_4_8(CtImPro24* self, const kuint32 idx)
{
    TimproHrbCtrl hrbCtrlMax = {
        .inPosX = ImproSrohrb_D_IM_PRO_HRB_HRBH_MAX,
        .inPosY = ImproSrohrb_D_IM_PRO_HRB_HRBV_MAX,
        .inWidth = ImproSrohrb_D_IM_PRO_HRB_HRBHW_MAX,
        .inLines = ImproSrohrb_D_IM_PRO_HRB_HRBVW_MAX,
        .outWidth = ImproSrohrb_D_IM_PRO_HRB_HRBHW_MAX,
        .cycle = ImproSrohrb_D_IM_PRO_HRB_HRBSCYC_MAX,
        .outTiming = ImproSrohrb_D_IM_PRO_HRB_HRBOSM_MAX,
        .coefficient[0][0] = 65535,
        .coefficient[0][1] = 65535,
        .coefficient[0][2] = 65535,
        .coefficient[0][3] = 65535,
        .coefficient[0][4] = 65535,
        .coefficient[1][0] = 65535,
        .coefficient[1][1] = 65535,
        .coefficient[1][2] = 65535,
        .coefficient[1][3] = 65535,
        .coefficient[1][4] = 65535,
        .coefficient[2][0] = 65535,
        .coefficient[2][1] = 65535,
        .coefficient[2][2] = 65535,
        .coefficient[2][3] = 65535,
        .coefficient[2][4] = 65535,
        .coefficient[3][0] = 65535,
        .coefficient[3][1] = 65535,
        .coefficient[3][2] = 65535,
        .coefficient[3][3] = 65535,
        .coefficient[3][4] = 65535,
        .coefficient[4][0] = 65535,
        .coefficient[4][1] = 65535,
        .coefficient[4][2] = 65535,
        .coefficient[4][3] = 65535,
        .coefficient[4][4] = 65535,
        .coefficient[5][0] = 65535,
        .coefficient[5][1] = 65535,
        .coefficient[5][2] = 65535,
        .coefficient[5][3] = 65535,
        .coefficient[5][4] = 65535,
        .coefficient[6][0] = 65535,
        .coefficient[6][1] = 65535,
        .coefficient[6][2] = 65535,
        .coefficient[6][3] = 65535,
        .coefficient[6][4] = 65535,
        .coefficient[7][0] = 65535,
        .coefficient[7][1] = 65535,
        .coefficient[7][2] = 65535,
        .coefficient[7][3] = 65535,
        .coefficient[7][4] = 65535,
        .coefficient[8][0] = 65535,
        .coefficient[8][1] = 65535,
        .coefficient[8][2] = 65535,
        .coefficient[8][3] = 65535,
        .coefficient[8][4] = 65535,
        .coefficient[9][0] = 65535,
        .coefficient[9][1] = 65535,
        .coefficient[9][2] = 65535,
        .coefficient[9][3] = 65535,
        .coefficient[9][4] = 65535,
        .coefficient[10][0] = 65535,
        .coefficient[10][1] = 65535,
        .coefficient[10][2] = 65535,
        .coefficient[10][3] = 65535,
        .coefficient[10][4] = 65535,
        .coefficient[11][0] = 65535,
        .coefficient[11][1] = 65535,
        .coefficient[11][2] = 65535,
        .coefficient[11][3] = 65535,
        .coefficient[11][4] = 65535,
        .coefficient[12][0] = 65535,
        .coefficient[12][1] = 65535,
        .coefficient[12][2] = 65535,
        .coefficient[12][3] = 65535,
        .coefficient[12][4] = 65535,
        .coefficient[13][0] = 65535,
        .coefficient[13][1] = 65535,
        .coefficient[13][2] = 65535,
        .coefficient[13][3] = 65535,
        .coefficient[13][4] = 65535,
        .coefficient[14][0] = 65535,
        .coefficient[14][1] = 65535,
        .coefficient[14][2] = 65535,
        .coefficient[14][3] = 65535,
        .coefficient[14][4] = 65535,
        .coefficient[15][0] = 65535,
        .coefficient[15][1] = 65535,
        .coefficient[15][2] = 65535,
        .coefficient[15][3] = 65535,
        .coefficient[15][4] = 65535,
        .coefficient[16][0] = 65535,
        .coefficient[16][1] = 65535,
        .coefficient[16][2] = 65535,
        .coefficient[16][3] = 65535,
        .coefficient[16][4] = 65535,
        .coefficient[17][0] = 65535,
        .coefficient[17][1] = 65535,
        .coefficient[17][2] = 65535,
        .coefficient[17][3] = 65535,
        .coefficient[17][4] = 65535,
        .coefficient[18][0] = 65535,
        .coefficient[18][1] = 65535,
        .coefficient[18][2] = 65535,
        .coefficient[18][3] = 65535,
        .coefficient[18][4] = 65535,
        .coefficient[19][0] = 65535,
        .coefficient[19][1] = 65535,
        .coefficient[19][2] = 65535,
        .coefficient[19][3] = 65535,
        .coefficient[19][4] = 65535,
    };

    TimproHrbCtrl hrb_ctrl_min = {
        .inPosX = ImproSrohrb_D_IM_PRO_HRB_HRBH_MIN,
        .inPosY = ImproSrohrb_D_IM_PRO_HRB_HRBV_MIN,
        .inWidth = ImproSrohrb_D_IM_PRO_HRB_HRBHW_MIN,
        .inLines = ImproSrohrb_D_IM_PRO_HRB_HRBVW_MIN,
        .outWidth = ImproSrohrb_D_IM_PRO_HRB_HRBHW_MIN,
        .cycle = ImproSrohrb_D_IM_PRO_HRB_HRBSCYC_MIN,
        .outTiming = ImproSrohrb_D_IM_PRO_HRB_HRBOSM_MIN,
        .coefficient[0][0] = 0,
        .coefficient[0][1] = 0,
        .coefficient[0][2] = 0,
        .coefficient[0][3] = 0,
        .coefficient[0][4] = 0,
        .coefficient[1][0] = 0,
        .coefficient[1][1] = 0,
        .coefficient[1][2] = 0,
        .coefficient[1][3] = 0,
        .coefficient[1][4] = 0,
        .coefficient[2][0] = 0,
        .coefficient[2][1] = 0,
        .coefficient[2][2] = 0,
        .coefficient[2][3] = 0,
        .coefficient[2][4] = 0,
        .coefficient[3][0] = 0,
        .coefficient[3][1] = 0,
        .coefficient[3][2] = 0,
        .coefficient[3][3] = 0,
        .coefficient[3][4] = 0,
        .coefficient[4][0] = 0,
        .coefficient[4][1] = 0,
        .coefficient[4][2] = 0,
        .coefficient[4][3] = 0,
        .coefficient[4][4] = 0,
        .coefficient[5][0] = 0,
        .coefficient[5][1] = 0,
        .coefficient[5][2] = 0,
        .coefficient[5][3] = 0,
        .coefficient[5][4] = 0,
        .coefficient[6][0] = 0,
        .coefficient[6][1] = 0,
        .coefficient[6][2] = 0,
        .coefficient[6][3] = 0,
        .coefficient[6][4] = 0,
        .coefficient[7][0] = 0,
        .coefficient[7][1] = 0,
        .coefficient[7][2] = 0,
        .coefficient[7][3] = 0,
        .coefficient[7][4] = 0,
        .coefficient[8][0] = 0,
        .coefficient[8][1] = 0,
        .coefficient[8][2] = 0,
        .coefficient[8][3] = 0,
        .coefficient[8][4] = 0,
        .coefficient[9][0] = 0,
        .coefficient[9][1] = 0,
        .coefficient[9][2] = 0,
        .coefficient[9][3] = 0,
        .coefficient[9][4] = 0,
        .coefficient[10][0] = 0,
        .coefficient[10][1] = 0,
        .coefficient[10][2] = 0,
        .coefficient[10][3] = 0,
        .coefficient[10][4] = 0,
        .coefficient[11][0] = 0,
        .coefficient[11][1] = 0,
        .coefficient[11][2] = 0,
        .coefficient[11][3] = 0,
        .coefficient[11][4] = 0,
        .coefficient[12][0] = 0,
        .coefficient[12][1] = 0,
        .coefficient[12][2] = 0,
        .coefficient[12][3] = 0,
        .coefficient[12][4] = 0,
        .coefficient[13][0] = 0,
        .coefficient[13][1] = 0,
        .coefficient[13][2] = 0,
        .coefficient[13][3] = 0,
        .coefficient[13][4] = 0,
        .coefficient[14][0] = 0,
        .coefficient[14][1] = 0,
        .coefficient[14][2] = 0,
        .coefficient[14][3] = 0,
        .coefficient[14][4] = 0,
        .coefficient[15][0] = 0,
        .coefficient[15][1] = 0,
        .coefficient[15][2] = 0,
        .coefficient[15][3] = 0,
        .coefficient[15][4] = 0,
        .coefficient[16][0] = 0,
        .coefficient[16][1] = 0,
        .coefficient[16][2] = 0,
        .coefficient[16][3] = 0,
        .coefficient[16][4] = 0,
        .coefficient[17][0] = 0,
        .coefficient[17][1] = 0,
        .coefficient[17][2] = 0,
        .coefficient[17][3] = 0,
        .coefficient[17][4] = 0,
        .coefficient[18][0] = 0,
        .coefficient[18][1] = 0,
        .coefficient[18][2] = 0,
        .coefficient[18][3] = 0,
        .coefficient[18][4] = 0,
        .coefficient[19][0] = 0,
        .coefficient[19][1] = 0,
        .coefficient[19][2] = 0,
        .coefficient[19][3] = 0,
        .coefficient[19][4] = 0,
    };

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srohrb_ctrl(self->priv->improSrohrb, self->priv->unitNo, &hrbCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srohrb_ctrl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_4_print_8(self->priv->imPro24Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &hrbCtrlMax);
			}

			self->priv->ercd = impro_srohrb_ctrl(self->priv->improSrohrb, self->priv->unitNo, &hrb_ctrl_min);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srohrb_ctrl(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_4_print_8(self->priv->imPro24Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &hrb_ctrl_min);
			}
        }
    }
}

void ct_im_pro2_4_9(CtImPro24* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->paenTrg = 0; self->priv->paenTrg < 2 + 1; self->priv->paenTrg++) {
				self->priv->ercd = impro_srohrb_set_paen(self->priv->improSrohrb, self->priv->unitNo,
						self->priv->paenTrg);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srohrb_set_paen(%u) Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ercd));
				} else {
					im_pro_2_4_print_9(self->priv->imPro24Print, self->priv->unitNo, self->priv->paenTrg);
				}
            }
        }
    }
}
#endif  //CO_CT_IM_PRO_DISABLE

CtImPro24* ct_im_pro2_4_new(void)
{
	CtImPro24* self = k_object_new_with_private(CT_TYPE_IM_PRO2_4, sizeof(CtImPro24Private));

	return self;
}

