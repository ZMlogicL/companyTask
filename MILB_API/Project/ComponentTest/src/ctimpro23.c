/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 陈元
*@brief : CtImPro23
*@rely : klib
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improsrodpc.h"
#include "improsroffc.h"
#include "ctimpro23.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro23, ct_im_pro2_3)
#define CT_IM_PRO2_3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro23Private, CT_TYPE_IM_PRO2_3))


struct _CtImPro23Private
{
	ImproSrodpc *improSrodpc;
	ImproSroffc *improSroffc;
	ImPro23Print *imPro23Print;
	kint32 ercd;
	E_IM_PRO_UNIT_NUM unitNo;
};


/**********
 * IMPL
 */
static void ct_im_pro2_3_constructor(CtImPro23 *self)
{
	self->priv = CT_IM_PRO2_3_GET_PRIVATE(self);
	self->priv->improSrodpc = impro_srodpc_new();
	self->priv->improSroffc = impro_sroffc_new();
	self->priv->imPro23Print = im_pro_2_3_print_new();
	self->priv->ercd = 0;
	self->priv->unitNo = 0;
}

static void ct_im_pro2_3_destructor(CtImPro23 *self)
{
	CtImPro23Private *priv = CT_IM_PRO2_3_GET_PRIVATE(self);

	if (priv->improSrodpc) {
		k_object_unref(priv->improSrodpc);
		priv->improSrodpc = NULL;
	}

	if (priv->improSroffc) {
		k_object_unref(priv->improSroffc);
		priv->improSroffc = NULL;
	}

	if (priv->imPro23Print) {
		k_object_unref(priv->imPro23Print);
		priv->imPro23Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro2_3_0(CtImPro23* self, const kuint32 idx)
{
	TimproDpcArea dpcCtrlMax = {
		.gPosX = ImproSrodpc_D_IM_PRO_DPC_DPCGH_MAX,
		.gPosY = ImproSrodpc_D_IM_PRO_DPC_DPCGV_MAX,
		.gWidth = ImproSrodpc_D_IM_PRO_DPC_DPCGHW_MAX,
		.gLines = ImproSrodpc_D_IM_PRO_DPC_DPCGVW_MAX,
		.posX = ImproSrodpc_D_IM_PRO_DPC_DPCH_MAX,
		.posY = ImproSrodpc_D_IM_PRO_DPC_DPCV_MAX,
		.width = ImproSrodpc_D_IM_PRO_DPC_DPCHW_MAX,
		.lines = ImproSrodpc_D_IM_PRO_DPC_DPCVW_MAX,
	};

	TimproDpcArea dpcCtrlMin = {
		.gPosX = ImproSrodpc_D_IM_PRO_DPC_DPCGH_MIN,
		.gPosY = ImproSrodpc_D_IM_PRO_DPC_DPCGV_MIN,
		.gWidth = ImproSrodpc_D_IM_PRO_DPC_DPCGHW_MIN,
		.gLines = ImproSrodpc_D_IM_PRO_DPC_DPCGVW_MIN,
		.posX = ImproSrodpc_D_IM_PRO_DPC_DPCH_MIN,
		.posY = ImproSrodpc_D_IM_PRO_DPC_DPCV_MIN,
		.width = ImproSrodpc_D_IM_PRO_DPC_DPCHW_MIN,
		.lines = ImproSrodpc_D_IM_PRO_DPC_DPCVW_MIN,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srodpc_set_area(self->priv->improSrodpc, self->priv->unitNo, &dpcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_set_area(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_0(self->priv->imPro23Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMax);
			}

			self->priv->ercd = impro_srodpc_set_area(self->priv->improSrodpc, self->priv->unitNo, &dpcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_set_area(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_0(self->priv->imPro23Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_3_1(CtImPro23* self, const kuint32 idx)
{
	TimproDpcAbCtrl dpcCtrlMax = {
		.alphaBlendTransitionWidthP = 15,
		.alphaBlendStartPosP = 16383,
		.alphaBlendTransitionWidthM = 15,
		.alphaBlendStartPosM = 16383,
	};

	TimproDpcAbCtrl dpcCtrlMin = {
		.alphaBlendTransitionWidthP = 0,
		.alphaBlendStartPosP = 0,
		.alphaBlendTransitionWidthM = 0,
		.alphaBlendStartPosM = 0,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srodpc_alpha_blend_ctrl(self->priv->improSrodpc, self->priv->unitNo,
					&dpcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_alpha_blend_ctrl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_1(self->priv->imPro23Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMax);
			}

			self->priv->ercd = impro_srodpc_alpha_blend_ctrl(self->priv->improSrodpc, self->priv->unitNo,
					&dpcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_alpha_blend_ctrl(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_1(self->priv->imPro23Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_3_2(CtImPro23* self, const kuint32 idx)
{
	TimproDpcDddCtrl dpcCtrlMax = {
		.grgbIndependentSetting = ImproSrodpc_E_IM_PRO_DPC_DD_GRGB_INDEPENDENT,
		.gMode = ImproSrodpc_E_IM_PRO_DPC_DD_MODE_G_2_CONSECUTIVE_DEFECT,
		.rbMode = ImproSrodpc_E_IM_PRO_DPC_DD_MODE_RB_2_CONSECUTIVE_DEFECT,
		.upperLimitLocalRegistration = 6,
		.useMdd = ImproSrodpc_E_IM_PRO_DPC_DD_USE_MDD_EN,
		.support2concecutiveDefect = ImproSrodpc_E_IM_PRO_DPC_DD_MDD_2CONSECUTIVE_DEFECT_EN,
		.pThresholdStartPos[0] = 16383,
		.pThresholdStartPos[1] = 16383,
		.pThresholdStartPos[2] = 16383,
		.mThresholdStartPos[0] = 16383,
		.mThresholdStartPos[1] = 16383,
		.mThresholdStartPos[2] = 16383,
		.pThresholdStartOffset[0] = 16383,
		.pThresholdStartOffset[1] = 16383,
		.pThresholdStartOffset[2] = 16383,
		.mThresholdStartOffset[0] = 16383,
		.mThresholdStartOffset[1] = 16383,
		.mThresholdStartOffset[2] = 16383,
		.pThresholdGain[0] = 63,
		.pThresholdGain[1] = 63,
		.pThresholdGain[2] = 63,
		.mThresholdGain[0] = 63,
		.mThresholdGain[1] = 63,
		.mThresholdGain[2] = 63,
		.pThresholdUpperLimit[0] = 16383,
		.pThresholdUpperLimit[1] = 16383,
		.pThresholdUpperLimit[2] = 16383,
		.mThresholdUpperLimit[0] = 16383,
		.mThresholdUpperLimit[1] = 16383,
		.mThresholdUpperLimit[2] = 16383,
		.pThreshold2consecutive = 63,
		.mThreshold2consecutive = 63,
		.threshold2consecutiveBrightPix[0] = 4095,
		.threshold2consecutiveBrightPix[1] = 4095,
		.threshold2consecutiveBrightPix[2] = 4095,
	};

	TimproDpcDddCtrl dpcCtrlMin = {
		.grgbIndependentSetting = ImproSrodpc_E_IM_PRO_DPC_DD_GRGB_UNITED,
		.gMode = ImproSrodpc_E_IM_PRO_DPC_DD_MODE_G_SINGLE_DEFECT,
		.rbMode = ImproSrodpc_E_IM_PRO_DPC_DD_MODE_RB_SINGLE_DEFECT,
		.upperLimitLocalRegistration = 0,
		.useMdd = ImproSrodpc_E_IM_PRO_DPC_DD_USE_MDD_DIS,
		.support2concecutiveDefect = ImproSrodpc_E_IM_PRO_DPC_DD_MDD_2CONSECUTIVE_DEFECT_DIS,
		.pThresholdStartPos[0] = 0,
		.pThresholdStartPos[1] = 0,
		.pThresholdStartPos[2] = 0,
		.mThresholdStartPos[0] = 0,
		.mThresholdStartPos[1] = 0,
		.mThresholdStartPos[2] = 0,
		.pThresholdStartOffset[0] = 0,
		.pThresholdStartOffset[1] = 0,
		.pThresholdStartOffset[2] = 0,
		.mThresholdStartOffset[0] = 0,
		.mThresholdStartOffset[1] = 0,
		.mThresholdStartOffset[2] = 0,
		.pThresholdGain[0] = 0,
		.pThresholdGain[1] = 0,
		.pThresholdGain[2] = 0,
		.mThresholdGain[0] = 0,
		.mThresholdGain[1] = 0,
		.mThresholdGain[2] = 0,
		.pThresholdUpperLimit[0] = 0,
		.pThresholdUpperLimit[1] = 0,
		.pThresholdUpperLimit[2] = 0,
		.mThresholdUpperLimit[0] = 0,
		.mThresholdUpperLimit[1] = 0,
		.mThresholdUpperLimit[2] = 0,
		.pThreshold2consecutive = 0,
		.mThreshold2consecutive = 0,
		.threshold2consecutiveBrightPix[0] = 0,
		.threshold2consecutiveBrightPix[1] = 0,
		.threshold2consecutiveBrightPix[2] = 0,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srodpc_dynamic_detect_ctrl(self->priv->improSrodpc, self->priv->unitNo,
					&dpcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_dynamic_detect_ctrl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_2(self->priv->imPro23Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMax);
			}

			self->priv->ercd = impro_srodpc_dynamic_detect_ctrl(self->priv->improSrodpc, self->priv->unitNo,
					&dpcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_dynamic_detect_ctrl(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_2(self->priv->imPro23Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_3_3(CtImPro23* self, const kuint32 idx)
{
	TimproDpcMddCtrl dpcCtrlMax = {
		.pMddEffect = 7,
		.mMddEffect = 7,
		.pMddEffect2 = 3,
		.mMddEffect2 = 3,
		.pThresholdOffset = 1023,
		.mThresholdOffset = 1023,
		.pThresholdGain = 63,
		.mThresholdGain = 63,
	};

	TimproDpcMddCtrl dpcCtrlMin = {
		.pMddEffect = 0,
		.mMddEffect = 0,
		.pMddEffect2 = 0,
		.mMddEffect2 = 0,
		.pThresholdOffset = 0,
		.mThresholdOffset = 0,
		.pThresholdGain = 0,
		.mThresholdGain = 0,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srodpc_mis_determination_calc_ctrl(self->priv->improSrodpc,
					self->priv->unitNo, &dpcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_mis_determination_calc_ctrl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_3(self->priv->imPro23Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMax);
			}

			self->priv->ercd = impro_srodpc_mis_determination_calc_ctrl(self->priv->improSrodpc,
					self->priv->unitNo, &dpcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_mis_determination_calc_ctrl(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_3(self->priv->imPro23Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_3_4(CtImPro23* self, const kuint32 idx)
{
	TimproDpcMdcCtrl dpcCtrlMax = {
		.useOcd = ImproSrodpc_E_IM_PRO_DPC_MDC_USE_OCD_EN,
		.pManualAdjValSingle = 1023,
		.mManualAdjValSingle = 1023,
		.pManualAdjVal2consecutive = 1023,
		.mManualAdjVal2consecutive = 1023,
		.pCorrectionLevelOnOcd = 63,
		.mCorrectionLevelOnOcd = 63,
	};

	TimproDpcMdcCtrl dpcCtrlMin = {
		.useOcd = ImproSrodpc_E_IM_PRO_DPC_MDC_USE_OCD_DIS,
		.pManualAdjValSingle = 0,
		.mManualAdjValSingle = 0,
		.pManualAdjVal2consecutive = 0,
		.mManualAdjVal2consecutive = 0,
		.pCorrectionLevelOnOcd = 0,
		.mCorrectionLevelOnOcd = 0,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srodpc_magnitude_defect_ctrl(self->priv->improSrodpc, self->priv->unitNo,
					&dpcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_magnitude_defect_ctrl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_4(self->priv->imPro23Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMax);
			}

			self->priv->ercd = impro_srodpc_magnitude_defect_ctrl(self->priv->improSrodpc, self->priv->unitNo,
					&dpcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_magnitude_defect_ctrl(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_4(self->priv->imPro23Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_3_5(CtImPro23* self, const kuint32 idx)
{
	TimproDpcEsdcCtrl dpcCtrlMax = {
		.esdMode = ImproSrodpc_E_IM_PRO_DPC_ESD_MODE_3,
		.useRbJdge = ImproSrodpc_E_IM_PRO_DPC_ESD_USE_RB_JUDGE_EN,
		.useOcd = ImproSrodpc_E_IM_PRO_DPC_ESD_USE_OCD_EN,
		.thresholdStartPos = 16383,
		.thresholdOffset = 16383,
		.thresholdGain = 255,
		.thresholdUpperLimit = 16383,
		.noiseTolerance = 5,
		.thresholdCalculation = 16383,
		.pCorrectionLevelOnOcd = 63,
		.mCorrectionLevelOnOcd = 63,
	};

	TimproDpcEsdcCtrl dpcCtrlMin = {
		.esdMode = ImproSrodpc_E_IM_PRO_DPC_ESD_MODE_0,
		.useRbJdge = ImproSrodpc_E_IM_PRO_DPC_ESD_USE_RB_JUDGE_DIS,
		.useOcd = ImproSrodpc_E_IM_PRO_DPC_ESD_USE_OCD_DIS,
		.thresholdStartPos = 0,
		.thresholdOffset = 0,
		.thresholdGain = 0,
		.thresholdUpperLimit = 0,
		.noiseTolerance = 0,
		.thresholdCalculation = 0,
		.pCorrectionLevelOnOcd = 0,
		.mCorrectionLevelOnOcd = 0,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srodpc_edge_storage_ctrl(self->priv->improSrodpc, self->priv->unitNo,
					&dpcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_edge_storage_ctrl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_5(self->priv->imPro23Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMax);
			}

			self->priv->ercd = impro_srodpc_edge_storage_ctrl(self->priv->improSrodpc, self->priv->unitNo,
					&dpcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_edge_storage_ctrl(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_5(self->priv->imPro23Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_3_6(CtImPro23* self, const kuint32 idx)
{
	TimproDpcOcdCtrl dpcCtrlMax = {
		.pOcdEffect = 7,
		.mOcdEffect = 7,
		.pThreshold = 16383,
		.mThreshold = 16383,
	};

	TimproDpcOcdCtrl dpcCtrlMin = {
		.pOcdEffect = 0,
		.mOcdEffect = 0,
		.pThreshold = 0,
		.mThreshold = 0,
	};

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srodpc_over_correction_detect_ctrl(self->priv->improSrodpc,
					self->priv->unitNo, &dpcCtrlMax);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_over_correction_detect_ctrl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_6(self->priv->imPro23Print, "max_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMax);
			}

			self->priv->ercd = impro_srodpc_over_correction_detect_ctrl(self->priv->improSrodpc,
					self->priv->unitNo, &dpcCtrlMin);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_over_correction_detect_ctrl(%u) min_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_6(self->priv->imPro23Print, "min_para", self->priv->unitNo,
						self->priv->ercd, &dpcCtrlMin);
			}
        }
    }
}

void ct_im_pro2_3_7(CtImPro23* self, const kuint32 idx)
{
	const TimproRdmaDpcAddr* dpcCtrl;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			self->priv->ercd = impro_srodpc_get_rdma_addr_dpc_cntl(self->priv->improSrodpc, self->priv->unitNo,
					&dpcCtrl);
			if (self->priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_srodpc_get_rdma_addr_dpc_cntl(%u) max_para Error self->priv->ercd=0x%x\n",
								self->priv->unitNo, self->priv->ercd));
			} else {
				im_pro_2_3_print_7(self->priv->imPro23Print, "", self->priv->unitNo, self->priv->ercd,
						&dpcCtrl);
			}
        }
    }
}

void ct_im_pro2_3_8(CtImPro23* self, const kuint32 idx)
{
	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			impro_sroffc_start(self->priv->improSroffc, self->priv->unitNo);
			im_pro_2_3_print_8(self->priv->imPro23Print, self->priv->unitNo);
		}
    }
}

void ct_im_pro2_3_9(CtImPro23* self, const kuint32 idx)
{
	kuchar force;

	if (idx == 1) {
		for (self->priv->unitNo = 0; self->priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; self->priv->unitNo++) {
			for (force = 0; force < 2 + 1; force++) {
#ifdef CO_DEBUG_ON_PC
				ioPro.imgPipe[self->priv->unitNo].sro.ffc.fctrg.bit.fctrg = 3;
#endif
				impro_sroffc_stop(self->priv->improSroffc, self->priv->unitNo, force);
				im_pro_2_3_print_9(self->priv->imPro23Print, self->priv->unitNo, force);
			}
        }
    }
}
#endif  //CO_CT_IM_PRO_DISABLE

CtImPro23* ct_im_pro2_3_new(void)
{
	CtImPro23* self = k_object_new_with_private(CT_TYPE_IM_PRO2_3, sizeof(CtImPro23Private));

	return self;
}

