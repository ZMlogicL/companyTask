/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro22
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsrocag.h"
#include "improsrodpc.h"
#include "ctimpro22.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro22, ct_im_pro2_2)
#define CT_IM_PRO2_2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro22Private, CT_TYPE_IM_PRO2_2))


struct _CtImPro22Private
{
	ImproSrocag *improSrocag;
	ImproSrodpc *improSrodpc;
	ImPro22Print *imPro22Print;
	kint32 ercd;
	E_IM_PRO_UNIT_NUM unitNo;
	kuchar force;
	kuchar paenTrg;
};


/**********
 * IMPL
 */
static void ct_im_pro2_2_constructor(CtImPro22 *self)
{
	self->priv = CT_IM_PRO2_2_GET_PRIVATE(self);
	self->priv->improSrocag = impro_srocag_new();
	self->priv->improSrodpc = impro_srodpc_new();
	self->priv->imPro22Print = im_pro_2_2_print_new();
	self->priv->ercd = 0;
	self->priv->unitNo = 0;
	self->priv->force = 0;
	self->priv->paenTrg = 0;
}

static void ct_im_pro2_2_destructor(CtImPro22 *self)
{
	CtImPro22Private *priv = CT_IM_PRO2_2_GET_PRIVATE(self);

	if (priv->improSrocag) {
		k_object_unref(priv->improSrocag);
		priv->improSrocag = NULL;
	}

	if (priv->improSrodpc) {
		k_object_unref(priv->improSrodpc);
		priv->improSrodpc = NULL;
	}

	if (priv->imPro22Print) {
		k_object_unref(priv->imPro22Print);
			priv->imPro22Print = NULL;
		}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro2_2_0(CtImPro22* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->force = 0; self->priv->force < 2 + 1; self->priv->force++) {
#ifdef CO_DEBUG_ON_PC
				ioPro.imgPipe[self->priv->unitNo].sro.cag.cagtrg.bit.cagtrg = 3;
#endif
				impro_srocag_stop(self->priv->improSrocag, self->priv->unitNo, self->priv->force);
				im_pro_2_2_print_0(self->priv->imPro22Print, self->priv->unitNo, self->priv->force);
			}
        }
    }
}

void ct_im_pro2_2_1(CtImPro22* self, const kuint32 idx)
{
	TimproCagCtrl cagCtrlMax = {
		.vBinningRatioReciprocalNum = 4095,
		.hBinningRatioReciprocalNum = 4095,
		.optCenterPosH[0] = 65535,
		.optCenterPosH[1] = 65535,
		.optCenterPosH[2] = 65535,
		.optCenterPosV[0] = 65535,
		.optCenterPosV[1] = 65535,
		.optCenterPosV[2] = 65535,
		.gain[0] = 8191,
		.gain[1] = 8191,
		.gain[2] = 8191,
		.transferULimitH[0] = 0x800,
		.transferULimitH[1] = 0x800,
		.transferULimitH[2] = 0x800,
		.transferLLimitH[0] = 0x800,
		.transferLLimitH[1] = 0x800,
		.transferLLimitH[2] = 0x800,
		.transferULimitV[0] = 0x400,
		.transferULimitV[1] = 0x400,
		.transferULimitV[2] = 0x400,
		.transferLLimitV[0] = 0x400,
		.transferLLimitV[1] = 0x400,
		.transferLLimitV[2] = 0x400,
		.transferOffsetH[0] = 4095,
		.transferOffsetH[1] = 4095,
		.transferOffsetH[2] = 4095,
		.transferOffsetV[0] = 2047,
		.transferOffsetV[1] = 2047,
		.transferOffsetV[2] = 2047,
		.cornerThresh1[0] = 0xFFFF,
		.cornerThresh1[1] = 0xFFFF,
		.cornerThresh1[2] = 0xFFFF,
		.cornerGain1[0] = 32767,
		.cornerGain1[1] = 32767,
		.cornerGain1[2] = 32767,
		.cornerThresh2[0] = 0xFFFF,
		.cornerThresh2[1] = 0xFFFF,
		.cornerThresh2[2] = 0xFFFF,
		.cornerGain2[0] = 32767,
		.cornerGain2[1] = 32767,
		.cornerGain2[2] = 32767,
		.cornerThresh3[0] = 0xFFFF,
		.cornerThresh3[1] = 0xFFFF,
		.cornerThresh3[2] = 0xFFFF,
		.cornerGain3[0] = 32767,
		.cornerGain3[1] = 32767,
		.cornerGain3[2] = 32767,
		.cornerThresh4[0] = 0xFFFF,
		.cornerThresh4[1] = 0xFFFF,
		.cornerThresh4[2] = 0xFFFF,
		.cornerGain4[0] = 32767,
		.cornerGain4[1] = 32767,
		.cornerGain4[2] = 32767,
	};

	TimproCagCtrl cagCtrlMin = {
		.vBinningRatioReciprocalNum = 0,
		.hBinningRatioReciprocalNum = 0,
		.optCenterPosH[0] = 0,
		.optCenterPosH[1] = 0,
		.optCenterPosH[2] = 0,
		.optCenterPosV[0] = 0,
		.optCenterPosV[1] = 0,
		.optCenterPosV[2] = 0,
		.gain[0] = 0,
		.gain[1] = 0,
		.gain[2] = 0,
		.transferULimitH[0] = 0x1800,
		.transferULimitH[1] = 0x1800,
		.transferULimitH[2] = 0x1800,
		.transferLLimitH[0] = 0x1800,
		.transferLLimitH[1] = 0x1800,
		.transferLLimitH[2] = 0x1800,
		.transferULimitV[0] = 0xC00,
		.transferULimitV[1] = 0xC00,
		.transferULimitV[2] = 0xC00,
		.transferLLimitV[0] = 0xC00,
		.transferLLimitV[1] = 0xC00,
		.transferLLimitV[2] = 0xC00,
		.transferOffsetH[0] = 0,
		.transferOffsetH[1] = 0,
		.transferOffsetH[2] = 0,
		.transferOffsetV[0] = 0,
		.transferOffsetV[1] = 0,
		.transferOffsetV[2] = 0,
		.cornerThresh1[0] = 0,
		.cornerThresh1[1] = 0,
		.cornerThresh1[2] = 0,
		.cornerGain1[0] = 0,
		.cornerGain1[1] = 0,
		.cornerGain1[2] = 0,
		.cornerThresh2[0] = 0,
		.cornerThresh2[1] = 0,
		.cornerThresh2[2] = 0,
		.cornerGain2[0] = 0,
		.cornerGain2[1] = 0,
		.cornerGain2[2] = 0,
		.cornerThresh3[0] = 0,
		.cornerThresh3[1] = 0,
		.cornerThresh3[2] = 0,
		.cornerGain3[0] = 0,
		.cornerGain3[1] = 0,
		.cornerGain3[2] = 0,
		.cornerThresh4[0] = 0,
		.cornerThresh4[1] = 0,
		.cornerThresh4[2] = 0,
		.cornerGain4[0] = 0,
		.cornerGain4[1] = 0,
		.cornerGain4[2] = 0,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srocag_ctrl(self->priv->improSrocag, self->priv->unitNo, &cagCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srocag_ctrl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_2_print_1(self->priv->imPro22Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &cagCtrlMax);
			}

			self->priv->ercd = impro_srocag_ctrl(self->priv->improSrocag, self->priv->unitNo, &cagCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srocag_ctrl(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_2_print_1(self->priv->imPro22Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &cagCtrlMin);
			}
        }
    }
}

void ct_im_pro2_2_2(CtImPro22* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->paenTrg = 0; self->priv->paenTrg < 2 + 1; self->priv->paenTrg++) {
				self->priv->ercd = impro_srocag_set_paen(self->priv->improSrocag, self->priv->unitNo,
						self->priv->paenTrg);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srocag_set_paen(%u) Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ercd));
				} else {
					im_pro_2_2_print_2(self->priv->imPro22Print, self->priv->unitNo, self->priv->paenTrg);
				}
            }
        }
    }
}

void ct_im_pro2_2_3(CtImPro22* self, const kuint32 idx)
{
	TimproCagArea cagCtrlMax = {
		.gPosX = ImproSrocag_D_IM_PRO_CAG_CAGGH_MAX,
		.gPosY = ImproSrocag_D_IM_PRO_CAG_CAGGV_MAX,
		.gWidth = ImproSrocag_D_IM_PRO_CAG_CAGGHW_MAX,
		.gLines = ImproSrocag_D_IM_PRO_CAG_CAGGVW_MAX,
		.posX = ImproSrocag_D_IM_PRO_CAG_CAGH_MAX,
		.posY = ImproSrocag_D_IM_PRO_CAG_CAGV_MAX,
		.width = ImproSrocag_D_IM_PRO_CAG_CAGHW_MAX,
		.lines = ImproSrocag_D_IM_PRO_CAG_CAGVW_MAX,
	};

	TimproCagArea cagCtrlMin = {
		.gPosX = ImproSrocag_D_IM_PRO_CAG_CAGGH_MIN,
		.gPosY = ImproSrocag_D_IM_PRO_CAG_CAGGV_MIN,
		.gWidth = ImproSrocag_D_IM_PRO_CAG_CAGGHW_MIN,
		.gLines = ImproSrocag_D_IM_PRO_CAG_CAGGVW_MIN,
		.posX = ImproSrocag_D_IM_PRO_CAG_CAGH_MIN,
		.posY = ImproSrocag_D_IM_PRO_CAG_CAGV_MIN,
		.width = ImproSrocag_D_IM_PRO_CAG_CAGHW_MIN,
		.lines = ImproSrocag_D_IM_PRO_CAG_CAGVW_MIN,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srocag_set_area(self->priv->improSrocag, self->priv->unitNo, &cagCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srocag_set_area(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_2_print_3(self->priv->imPro22Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &cagCtrlMax);
			}

			self->priv->ercd = impro_srocag_set_area(self->priv->improSrocag, self->priv->unitNo, &cagCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srocag_set_area(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_2_print_3(self->priv->imPro22Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &cagCtrlMin);
			}
        }
    }
}

void ct_im_pro2_2_4(CtImPro22* self, const kuint32 idx)
{
	TimproCagCtrlGlevelDiff cagCtrlMax = {
		.clipMode = ImproSrocag_E_IM_PRO_CAG_CLIP_MODE_14BIT_MAX,
		.gGapCorMode = ImproSrocag_E_IM_PRO_CAG_COR_MODE_G,
		.gGapPadMode = ImproSrocag_E_IM_PRO_CAG_PAD_MODE_EN,
		.gGapMode = ImproSrocag_E_IM_PRO_CAG_MODE_OPT_CENTER_SURFACE_ADD,
		.gradientULimit = 16383,
		.gradientLLimit = 16383,
		.gradientThreshold = 16383,
		.gradientThresholdGain = 0xFF,
	};

	TimproCagCtrlGlevelDiff cagCtrlMin = {
		.clipMode = ImproSrocag_E_IM_PRO_CAG_CLIP_MODE_14BIT,
		.gGapCorMode = ImproSrocag_E_IM_PRO_CAG_COR_MODE_GBGB,
		.gGapPadMode = ImproSrocag_E_IM_PRO_CAG_PAD_MODE_DIS,
		.gGapMode = ImproSrocag_E_IM_PRO_CAG_MODE_OPT_CENTER_ONLY,
		.gradientULimit = 0,
		.gradientLLimit = 0,
		.gradientThreshold = 0,
		.gradientThresholdGain = 0,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srocag_ctrl_glv_diff(self->priv->improSrocag, self->priv->unitNo,
					&cagCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srocag_ctrl_glv_diff(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_2_print_4(self->priv->imPro22Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &cagCtrlMax);
			}

			self->priv->ercd = impro_srocag_ctrl_glv_diff(self->priv->improSrocag, self->priv->unitNo,
					&cagCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srocag_ctrl_glv_diff(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_2_print_4(self->priv->imPro22Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &cagCtrlMin);
			}
        }
    }
}

void ct_im_pro2_2_5(CtImPro22* self, const kuint32 idx)
{
	const TimproRdmaCagAddr* cagCtrl;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srocag_get_rdma_addr_cag_cntl(self->priv->improSrocag, self->priv->unitNo,
					&cagCtrl);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srocag_get_rdma_addr_cag_cntl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_2_print_5(self->priv->imPro22Print, "", self->priv->unitNo, self->priv->ercd, &cagCtrl);
			}
        }
    }
}

void ct_im_pro2_2_6(CtImPro22* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			impro_srodpc_start(self->priv->improSrodpc, self->priv->unitNo);
			im_pro_2_2_print_6(self->priv->imPro22Print, self->priv->unitNo);
		}
    }
}

void ct_im_pro2_2_7(CtImPro22* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->force = 0; self->priv->force < 2 + 1; self->priv->force++) {
#ifdef CO_DEBUG_ON_PC
				ioPro.imgPipe[self->priv->unitNo].sro.dpc.dpctrg.bit.dpctrg = 3;
#endif
				impro_srodpc_stop(self->priv->improSrodpc, self->priv->unitNo, self->priv->force);
				im_pro_2_2_print_7(self->priv->imPro22Print, self->priv->unitNo, self->priv->force);
			}
        }
    }
}

void ct_im_pro2_2_8(CtImPro22* self, const kuint32 idx)
{
	TimproDpcCtrl dpcCtrlMax = {
		.dpcMode = ImproSrocag_E_IM_PRO_DPC_MODE_5,
		.threConv0 = ImproSrocag_E_IM_PRO_DPC_THRE_CONV_0_EN,
	};

	TimproDpcCtrl dpcCtrlMin = {
		.dpcMode = ImproSrocag_E_IM_PRO_DPC_MODE_0,
		.threConv0 = ImproSrocag_E_IM_PRO_DPC_THRE_CONV_0_DIS,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srodpc_ctrl(self->priv->improSrodpc, self->priv->unitNo, &dpcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_ctrl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_2_print_8(self->priv->imPro22Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMax);
			}

			self->priv->ercd = impro_srodpc_ctrl(self->priv->improSrodpc, self->priv->unitNo, &dpcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_ctrl(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_2_print_8(self->priv->imPro22Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_2_9(CtImPro22* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (self->priv->paenTrg = 0; self->priv->paenTrg < 2 + 1; self->priv->paenTrg++) {
				self->priv->ercd = impro_srodpc_set_paen(self->priv->improSrodpc, self->priv->unitNo,
						self->priv->paenTrg);
				if (self->priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("impro_srodpc_set_paen(%u) Error self->priv->ercd=0x%x\n",
									self->priv->unitNo, self->priv->ercd));
				} else {
					im_pro_2_2_print_9(self->priv->imPro22Print, self->priv->unitNo, self->priv->paenTrg);
				}
            }
        }
    }
}
#endif  //CO_CT_IM_PRO_DISABLE

CtImPro22* ct_im_pro2_2_new(void)
{
	CtImPro22* self = k_object_new_with_private(CT_TYPE_IM_PRO2_2, sizeof(CtImPro22Private));

	return self;
}

