/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈元
*@brief : CtImPro4Continue
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improstat.h"
#include "ctimpro4continue.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro4Continue, ct_im_pro4_continue)
#define CT_IM_PRO4_CONTINUE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro4ContinuePrivate, CT_TYPE_IM_PRO4_CONTINUE))


struct _CtImPro4ContinuePrivate
{
	ImProStat *imProStat;
	ImPro42Print *imPro42Print;
	ImPro43Print *imPro43Print;
	ImPro44Print *imPro44Print;
	ImPro45Print *imPro45Print;
	kint32 ercd;
	kulong calcData;
	kuchar ch;
	E_IM_PRO_AF_WINDOW_NO winNo;
};


/********
 * IMPL
 */
static void ct_im_pro4_continue_constructor(CtImPro4Continue *self)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	priv->imProStat = im_pro_stat_new();
	priv->imPro42Print = im_pro_4_2_print_new();
	priv->imPro43Print = im_pro_4_3_print_new();
	priv->imPro44Print = im_pro_4_4_print_new();
	priv->imPro45Print = im_pro_4_5_print_new();
	priv->ercd = 0;
	priv->calcData = 0;
	priv->ch = 0;
	priv->winNo = 0;
}

static void ct_im_pro4_continue_destructor(CtImPro4Continue *self)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (priv->imProStat) {
		k_object_unref(priv->imProStat);
		priv->imProStat = NULL;
	}

	if (priv->imPro42Print) {
		k_object_unref(priv->imPro42Print);
		priv->imPro42Print = NULL;
	}

	if (priv->imPro43Print) {
		k_object_unref(priv->imPro43Print);
		priv->imPro43Print = NULL;
	}

	if (priv->imPro44Print) {
		k_object_unref(priv->imPro44Print);
		priv->imPro44Print = NULL;
	}

	if (priv->imPro45Print) {
		k_object_unref(priv->imPro45Print);
		priv->imPro45Print = NULL;
	}
}


/********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro4_continue_29(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);
	kuchar unitNo;
    T_IM_PRO_AF_EVAL_CALC_CTRL  afCtrlMax = {
        .r = 511,
        .gr = 511,
        .gb = 511,
        .b = 511,
        .medianEnable = E_IM_PRO_AF_ENABLE_EN,
        .kneeEnable = E_IM_PRO_AF_ENABLE_EN,
        .kneeBoundary[0] = 0x3fff,
        .kneeBoundary[1] = 0x3fff,
        .kneeBoundary[2] = 0x3fff,
        .kneeBoundary[3] = 0x3fff,
        .kneeBoundary[4] = 0x3fff,
        .kneeBoundary[5] = 0x3fff,
        .kneeBoundary[6] = 0x3fff,
        .kneeSlope[0] = 0x0fff,
        .kneeSlope[1] = 0x0fff,
        .kneeSlope[2] = 0x0fff,
        .kneeSlope[3] = 0x0fff,
        .kneeSlope[4] = 0x0fff,
        .kneeSlope[5] = 0x0fff,
        .kneeSlope[6] = 0x0fff,
        .kneeSlope[7] = 0x0fff,
        .knee_offset[0] = 0x0fff,
        .knee_offset[1] = 0x0fff,
        .knee_offset[2] = 0x0fff,
        .knee_offset[3] = 0x0fff,
        .knee_offset[4] = 0x0fff,
        .knee_offset[5] = 0x0fff,
        .knee_offset[6] = 0x0fff,
        .knee_offset[7] = 0x0fff,
    };

    T_IM_PRO_AF_EVAL_CALC_CTRL  afCtrlMin = {
        .r = -512,
        .gr = -512,
        .gb = -512,
        .b = -512,
        .medianEnable = 0,
        .kneeEnable = 0,
        .kneeBoundary[0] = 0,
        .kneeBoundary[1] = 0,
        .kneeBoundary[2] = 0,
        .kneeBoundary[3] = 0,
        .kneeBoundary[4] = 0,
        .kneeBoundary[5] = 0,
        .kneeBoundary[6] = 0,
        .kneeSlope[0] = 0,
        .kneeSlope[1] = 0,
        .kneeSlope[2] = 0,
        .kneeSlope[3] = 0,
        .kneeSlope[4] = 0,
        .kneeSlope[5] = 0,
        .kneeSlope[6] = 0,
        .kneeSlope[7] = 0,
        .knee_offset[0] = 0,
        .knee_offset[1] = 0,
        .knee_offset[2] = 0,
        .knee_offset[3] = 0,
        .knee_offset[4] = 0,
        .knee_offset[5] = 0,
        .knee_offset[6] = 0,
        .knee_offset[7] = 0,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (unitNo = E_IM_PRO_AF_EVAL_CALC_UNIT_0; unitNo < E_IM_PRO_AF_EVAL_CALC_UNIT_2 + 1;
					unitNo++) {
				priv->ercd = Im_PRO_AF_Ctrl_Eval_Calc(priv->imProStat, priv->ch, unitNo, &afCtrlMax);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_AF_Ctrl_Eval_Calc(%u %u) max_para Error priv->ercd=0x%x\n",
									priv->ch, unitNo, priv->ercd));
				} else {
					im_pro_4_2_print_9(priv->imPro42Print, "max_para", priv->ch, unitNo, &afCtrlMax);
				}

				priv->ercd = Im_PRO_AF_Ctrl_Eval_Calc(priv->imProStat, priv->ch, unitNo, &afCtrlMin);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_AF_Ctrl_Eval_Calc(%u %u) min_para Error priv->ercd=0x%x\n",
									priv->ch, unitNo, priv->ercd));
				} else {
					im_pro_4_2_print_9(priv->imPro42Print, "min_para", priv->ch, unitNo, &afCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro4_continue_30(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);
    T_IM_PRO_AF_VERTICAL_CTRL afCtrlMax = {
        .updateCycle = 15,
        .evalCalUnit = E_IM_PRO_AF_EVAL_CALC_UNIT_2,
        .startAddr = D_IM_PRO_AF_AFVSH_MAX,
        .horizonSize = D_IM_PRO_AF_AFVSHW_MAX,
        .iirK = 32767,
        .iirA0 = 255,
        .iirA1 = 255,
        .iirA2 = 255,
        .iirB1 = 32767,
        .iirB2 = 32767,
        .corThreshold = 0x0FFF,
        .corLevel = 0x0FFF,
        .firFilter[0] = 255,
        .firFilter[1] = 255,
        .firFilter[2] = 255,
    };

    T_IM_PRO_AF_VERTICAL_CTRL afCtrlMin = {
        .updateCycle = 0,
        .evalCalUnit = E_IM_PRO_AF_EVAL_CALC_UNIT_0,
        .startAddr = D_IM_PRO_AF_AFVSH_MIN,
        .horizonSize = D_IM_PRO_AF_AFVSHW_MIN,
        .iirK = 0,
        .iirA0 = 0,
        .iirA1 = 0,
        .iirA2 = 0,
        .iirB1 = 0,
        .iirB2 = 0,
        .corThreshold = 0,
        .corLevel = 0,
        .firFilter[0] = 0,
        .firFilter[1] = 0,
        .firFilter[2] = 0,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_AF_Ctrl_Vertical(priv->imProStat, priv->ch, &afCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_AF_Ctrl_Vertical(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_3_print_0(priv->imPro43Print, "max_para", priv->ch, &afCtrlMax);
			}

			priv->ercd = Im_PRO_AF_Ctrl_Vertical(priv->imProStat, priv->ch, &afCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_AF_Ctrl_Vertical(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_3_print_0(priv->imPro43Print, "min_para", priv->ch, &afCtrlMin);
			}
        }
    }
}

void ct_im_pro4_continue_31(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);
    kuchar tapNo;
    T_IM_PRO_AF_HORIZON_CTRL afCtrlMax = {
        .groupA.iirEnable = E_IM_PRO_AF_ENABLE_EN,
        .groupA.firEnable = E_IM_PRO_AF_ENABLE_EN,
        .groupA.inputSelect = E_IM_PRO_AF_TAP_2,
        .groupA.firCoefficient[0] = 127,
        .groupA.firCoefficient[1] = 127,
        .groupA.firCoefficient[2] = 127,
        .groupA.firCoefficient[3] = 127,
        .groupA.firCoefficient[4] = 127,
        .groupA.firLevel = 0x0FFF,
        .groupA.gain = 0xFF,
        .groupA.iirK = 16383,
        .groupA.iirA0 = 127,
        .groupA.iirA1 = 127,
        .groupA.iirA2 = 127,
        .groupA.iirB1 = 16383,
        .groupA.iirB2 = 16383,
        .groupA.coringBounder[0] = 0x0FFF,
        .groupA.coringBounder[1] = 0x0FFF,
        .groupA.coringBounder[2] = 0x0FFF,
        .groupA.coringSlope[0] = 2047,
        .groupA.coringSlope[1] = 2047,
        .groupA.coringSlope[2] = 2047,
        .groupA.coringSlope[3] = 2047,
        .groupA.coringOffset[0] = 0x0FFF,
        .groupA.coringOffset[1] = 0x0FFF,
        .groupA.coringOffset[2] = 0x0FFF,
        .groupA.coringOffset[3] = 0x0FFF,
        .groupB.iirEnable = E_IM_PRO_AF_ENABLE_EN,
        .groupB.firEnable = E_IM_PRO_AF_ENABLE_EN,
        .groupB.inputSelect = E_IM_PRO_AF_TAP_2,
        .groupB.firCoefficient[0] = 127,
        .groupB.firCoefficient[1] = 127,
        .groupB.firCoefficient[2] = 127,
        .groupB.firCoefficient[3] = 127,
        .groupB.firCoefficient[4] = 127,
        .groupB.firLevel = 0x0FFF,
        .groupB.gain = 0xFF,
        .groupB.iirK = 16383,
        .groupB.iirA0 = 127,
        .groupB.iirA1 = 127,
        .groupB.iirA2 = 127,
        .groupB.iirB1 = 16383,
        .groupB.iirB2 = 16383,
        .groupB.coringBounder[0] = 0x0FFF,
        .groupB.coringBounder[1] = 0x0FFF,
        .groupB.coringBounder[2] = 0x0FFF,
        .groupB.coringSlope[0] = 2047,
        .groupB.coringSlope[1] = 2047,
        .groupB.coringSlope[2] = 2047,
        .groupB.coringSlope[3] = 2047,
        .groupB.coringOffset[0] = 0x0FFF,
        .groupB.coringOffset[1] = 0x0FFF,
        .groupB.coringOffset[2] = 0x0FFF,
        .groupB.coringOffset[3] = 0x0FFF,
    };

    T_IM_PRO_AF_HORIZON_CTRL afCtrlMin = {
        .groupA.iirEnable = E_IM_PRO_AF_ENABLE_DIS,
        .groupA.firEnable = E_IM_PRO_AF_ENABLE_DIS,
        .groupA.inputSelect = E_IM_PRO_AF_TAP_0,
        .groupA.firCoefficient[0] = -128,
        .groupA.firCoefficient[1] = -128,
        .groupA.firCoefficient[2] = -128,
        .groupA.firCoefficient[3] = -128,
        .groupA.firCoefficient[4] = -128,
        .groupA.firLevel = 0,
        .groupA.gain = 0,
        .groupA.iirK = -16384,
        .groupA.iirA0 = -128,
        .groupA.iirA1 = -128,
        .groupA.iirA2 = -128,
        .groupA.iirB1 = -16384,
        .groupA.iirB2 = -16384,
        .groupA.coringBounder[0] = 0,
        .groupA.coringBounder[1] = 0,
        .groupA.coringBounder[2] = 0,
        .groupA.coringSlope[0] = -2048,
        .groupA.coringSlope[1] = -2048,
        .groupA.coringSlope[2] = -2048,
        .groupA.coringSlope[3] = -2048,
        .groupA.coringOffset[0] = 0,
        .groupA.coringOffset[1] = 0,
        .groupA.coringOffset[2] = 0,
        .groupA.coringOffset[3] = 0,
        .groupB.iirEnable = E_IM_PRO_AF_ENABLE_DIS,
        .groupB.firEnable = E_IM_PRO_AF_ENABLE_DIS,
        .groupB.inputSelect = E_IM_PRO_AF_TAP_0,
        .groupB.firCoefficient[0] = -128,
        .groupB.firCoefficient[1] = -128,
        .groupB.firCoefficient[2] = -128,
        .groupB.firCoefficient[3] = -128,
        .groupB.firCoefficient[4] = -128,
        .groupB.firLevel = 0,
        .groupB.gain = 0,
        .groupB.iirK = -16384,
        .groupB.iirA0 = -128,
        .groupB.iirA1 = -128,
        .groupB.iirA2 = -128,
        .groupB.iirB1 = -16384,
        .groupB.iirB2 = -16384,
        .groupB.coringBounder[0] = 0,
        .groupB.coringBounder[1] = 0,
        .groupB.coringBounder[2] = 0,
        .groupB.coringSlope[0] = -2048,
        .groupB.coringSlope[1] = -2048,
        .groupB.coringSlope[2] = -2048,
        .groupB.coringSlope[3] = -2048,
        .groupB.coringOffset[0] = 0,
        .groupB.coringOffset[1] = 0,
        .groupB.coringOffset[2] = 0,
        .groupB.coringOffset[3] = 0,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (tapNo = E_IM_PRO_AF_TAP_0; tapNo < E_IM_PRO_AF_TAP_2 + 1; tapNo++) {
				priv->ercd = Im_PRO_AF_Ctrl_Horizon(priv->imProStat, priv->ch, tapNo, &afCtrlMax);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_AF_Ctrl_Horizon(%u %u) max_para Error priv->ercd=0x%x\n",
									priv->ch, tapNo, priv->ercd));
				} else {
					im_pro_4_3_print_1(priv->imPro43Print, "max_para", priv->ch, tapNo, &afCtrlMax);
				}

				priv->ercd = Im_PRO_AF_Ctrl_Horizon(priv->imProStat, priv->ch, tapNo, &afCtrlMin);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_AF_Ctrl_Horizon(%u %u) min_para Error priv->ercd=0x%x\n",
									priv->ch, tapNo, priv->ercd));
				} else {
					im_pro_4_3_print_1(priv->imPro43Print, "min_para", priv->ch, tapNo, &afCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro4_continue_32(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);
    T_IM_PRO_AF_WIN_CTRL afCtrlMax = {
        .hSel0 = E_IM_PRO_AF_WIN_H2_B,
        .hSel1 = E_IM_PRO_AF_WIN_H2_B,
        .hSel2 = E_IM_PRO_AF_WIN_H2_B,
        .evalCalUnit = E_IM_PRO_AF_EVAL_CALC_UNIT_2,
        .brightThreshold = 4095,
        .darkThreshold = 4095,
        .startPosX = 8190,
        .startPosY = 16380,
        .width = 4094,
        .height = 4094,
        .maxMixSelect = E_IM_PRO_AF_MIN_MAX_DETECT_SEL_V_UNIT,
    };

    T_IM_PRO_AF_WIN_CTRL afCtrlMin = {
        .hSel0 = E_IM_PRO_AF_WIN_H0_A,
        .hSel1 = E_IM_PRO_AF_WIN_H0_A,
        .hSel2 = E_IM_PRO_AF_WIN_H0_A,
        .evalCalUnit = E_IM_PRO_AF_EVAL_CALC_UNIT_0,
        .brightThreshold = 0,
        .darkThreshold = 0,
        .startPosX = 0,
        .startPosY = 0,
        .width = 2,
        .height = 2,
        .maxMixSelect = E_IM_PRO_AF_MIN_MAX_DETECT_SEL_H_UNIT0_A,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->ercd = Im_PRO_AF_Ctrl_Win(priv->imProStat, priv->ch, priv->winNo, &afCtrlMax);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_AF_Ctrl_Win(%u %u) max_para Error priv->ercd=0x%x\n",
									priv->ch, priv->winNo, priv->ercd));
				} else {
					im_pro_4_3_print_2(priv->imPro43Print, "max_para", priv->ch, priv->winNo, &afCtrlMax);
				}

				priv->ercd = Im_PRO_AF_Ctrl_Win(priv->imProStat, priv->ch, priv->winNo, &afCtrlMin);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_AF_Ctrl_Win(%u %u) min_para Error priv->ercd=0x%x\n",
									priv->ch, priv->winNo, priv->ercd));
				} else {
					im_pro_4_3_print_2(priv->imPro43Print, "min_para", priv->ch, priv->winNo, &afCtrlMin);
				}
            }
        }
    }
}

void ct_im_pro4_continue_33(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Eval_Calc_Data(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Eval_Calc_Data(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_3_print_3(priv->imPro43Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_34(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Bright_Data(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Bright_Data(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_3_print_4(priv->imPro43Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_35(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Dark_Data(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Dark_Data(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_3_print_5(priv->imPro43Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_36(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal0_Data(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal0_Data(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_3_print_6(priv->imPro43Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_37(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal1_Data(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal1_Data(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_3_print_7(priv->imPro43Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_38(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal2_Data(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal2_Data(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_3_print_8(priv->imPro43Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_39(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Vertical_Data(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Vertical_Data(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_3_print_9(priv->imPro43Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_40(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Max_Eval_Calc_Value(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Max_Eval_Calc_Value(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_4_print_0(priv->imPro44Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_41(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Min_Eval_Calc_Value(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Min_Eval_Calc_Value(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_4_print_1(priv->imPro44Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_42(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Max_Assess_Value(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Max_Assess_Value(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_4_print_2(priv->imPro44Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_43(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Min_Assess_Value(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Min_Assess_Value(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_4_print_3(priv->imPro44Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_44(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal0_Line_Accum_Max_Value(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal0_Line_Accum_Max_Value(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_4_print_4(priv->imPro44Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_45(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal1_Line_Accum_Max_Value(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal1_Line_Accum_Max_Value(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_4_print_5(priv->imPro44Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_46(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal2_Line_Accum_Max_Value(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal2_Line_Accum_Max_Value(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_4_print_6(priv->imPro44Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_47(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Eval_Calc_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Eval_Calc_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_4_print_7(priv->imPro44Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_48(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Bright_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Bright_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_4_print_8(priv->imPro44Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_49(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Dark_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Dark_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_4_print_9(priv->imPro44Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_50(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal0_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal0_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_5_print_0(priv->imPro45Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_51(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal1_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal1_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_5_print_1(priv->imPro45Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_52(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal2_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal2_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_5_print_2(priv->imPro45Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_53(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Vertical_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Vertical_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_5_print_3(priv->imPro45Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_54(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Max_Eval_Calc_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Max_Eval_Calc_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_5_print_4(priv->imPro45Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_55(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Min_Eval_Calc_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Min_Eval_Calc_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_5_print_5(priv->imPro45Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_56(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Max_Assess_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Max_Assess_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_5_print_6(priv->imPro45Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_continue_57(CtImPro4Continue* self, const kuint32 idx)
{
	CtImPro4ContinuePrivate *priv = CT_IM_PRO4_CONTINUE_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX;
					priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Min_Assess_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Min_Assess_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_5_print_7(priv->imPro45Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

#endif //CO_CT_IM_PRO_DISABLE

CtImPro4Continue* ct_im_pro4_continue_new(void)
{
	CtImPro4Continue* self = k_object_new_with_private(CT_TYPE_IM_PRO4_CONTINUE, sizeof(CtImPro4ContinuePrivate));

	return self;
}

