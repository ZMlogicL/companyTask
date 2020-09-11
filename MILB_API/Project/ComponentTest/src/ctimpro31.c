/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈元
*@brief : CtImPro31
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improb2b.h"
#include "ctimpro31.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro31, ct_im_pro3_1)
#define CT_IM_PRO3_1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro31Private, CT_TYPE_IM_PRO3_1))


struct _CtImPro31Private
{
	ImProB2b *imProB2b;
	ImPro31Print *imPro31Print;
	kint32 ercd;
	E_IM_PRO_UNIT_NUM unitNo;
};


/**********
 * IMPL
 */
static void ct_im_pro3_1_constructor(CtImPro31 *self)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);

	priv->imProB2b = im_pro_b2b_new();
	priv->imPro31Print = im_pro_3_1_print_new();
	priv->ercd = 0;
	priv->unitNo = 0;
}

static void ct_im_pro3_1_destructor(CtImPro31 *self)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);

	if (priv->imProB2b) {
		k_object_unref(priv->imProB2b);
		priv->imProB2b = NULL;
	}

	if (priv->imPro31Print) {
		k_object_unref(priv->imPro31Print);
		priv->imPro31Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE

void ct_im_pro3_1_0(CtImPro31* self, const UINT32 idx)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);
    T_IM_PRO_ELF_AREA elfCtrlMax = {
        .gWidth = 2496,
        .gLines = 8960,
        .gPosX = 2496,
        .gPosY = 8960,
        .width = 2488,
        .lines = 8952,
        .posX = 2491,
        .posY = 8954,
    };

    T_IM_PRO_ELF_AREA elfCtrlMin = {
        .gWidth = 10,
        .gLines = 10,
        .gPosX = 0,
        .gPosY = 0,
        .width = 2,
        .lines = 2,
        .posX = 4,
        .posY = 4,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Set_Area(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_Area(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_0(priv->imPro31Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Set_Area(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_Area(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_0(priv->imPro31Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_1_1(CtImPro31* self, const UINT32 idx)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);
    T_IM_PRO_ELF_NOISE_FUNC elfCtrlMax[3] = {
        {
            .offset[ 0 ] = 4095,
            .offset[ 1 ] = 4095,
            .offset[ 2 ] = 4095,
            .offset[ 3 ] = 4095,
            .gain[ 0 ] = 4095,
            .gain[ 1 ] = 4095,
            .gain[ 2 ] = 4095,
            .gain[ 3 ] = 4095,
            .boundary[ 0 ] = 4095,
            .boundary[ 1 ] = 4095,
            .boundary[ 2 ] = 4095,
            .boundary[ 3 ] = 4095,
        },
        {
            .offset[ 0 ] = 4095,
            .offset[ 1 ] = 4095,
            .offset[ 2 ] = 4095,
            .offset[ 3 ] = 4095,
            .gain[ 0 ] = 4095,
            .gain[ 1 ] = 4095,
            .gain[ 2 ] = 4095,
            .gain[ 3 ] = 4095,
            .boundary[ 0 ] = 4095,
            .boundary[ 1 ] = 4095,
            .boundary[ 2 ] = 4095,
            .boundary[ 3 ] = 4095,
        },
        {
            .offset[ 0 ] = 4095,
            .offset[ 1 ] = 4095,
            .offset[ 2 ] = 4095,
            .offset[ 3 ] = 4095,
            .gain[ 0 ] = 4095,
            .gain[ 1 ] = 4095,
            .gain[ 2 ] = 4095,
            .gain[ 3 ] = 4095,
            .boundary[ 0 ] = 4095,
            .boundary[ 1 ] = 4095,
            .boundary[ 2 ] = 4095,
            .boundary[ 3 ] = 4095,
        },
    };

    T_IM_PRO_ELF_NOISE_FUNC elfCtrlMin[3] = {
        {
            .offset[ 0 ] = 0,
            .offset[ 1 ] = 0,
            .offset[ 2 ] = 0,
            .offset[ 3 ] = 0,
            .gain[ 0 ] = 0,
            .gain[ 1 ] = 0,
            .gain[ 2 ] = 0,
            .gain[ 3 ] = 0,
            .boundary[ 0 ] = 0,
            .boundary[ 1 ] = 0,
            .boundary[ 2 ] = 0,
            .boundary[ 3 ] = 0,
        },
        {
            .offset[ 0 ] = 0,
            .offset[ 1 ] = 0,
            .offset[ 2 ] = 0,
            .offset[ 3 ] = 0,
            .gain[ 0 ] = 0,
            .gain[ 1 ] = 0,
            .gain[ 2 ] = 0,
            .gain[ 3 ] = 0,
            .boundary[ 0 ] = 0,
            .boundary[ 1 ] = 0,
            .boundary[ 2 ] = 0,
            .boundary[ 3 ] = 0,
        },
        {
            .offset[ 0 ] = 0,
            .offset[ 1 ] = 0,
            .offset[ 2 ] = 0,
            .offset[ 3 ] = 0,
            .gain[ 0 ] = 0,
            .gain[ 1 ] = 0,
            .gain[ 2 ] = 0,
            .gain[ 3 ] = 0,
            .boundary[ 0 ] = 0,
            .boundary[ 1 ] = 0,
            .boundary[ 2 ] = 0,
            .boundary[ 3 ] = 0,
        },
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Set_Noisefunc(priv->imProB2b, priv->unitNo, elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_Noisefunc(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_1(priv->imPro31Print, "max_para", priv->unitNo, priv->ercd, elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Set_Noisefunc(priv->imProB2b, priv->unitNo, elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_Noisefunc(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_1(priv->imPro31Print, "min_para", priv->unitNo, priv->ercd, elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_1_2(CtImPro31* self, const UINT32 idx)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);
    T_IM_PRO_ELF_LGT_EDG_FUNC elfCtrlMax = {
        .zeroPoint = 4095,
        .gainR = 1023,
        .gainG = 1023,
        .gainB = 1023,
        .factorR = 31,
        .factorG = 31,
        .factorB = 31,
        .colorPara = 16,
        .contourR = 16,
        .contourG = 16,
        .contourB = 16,
        .contourA1 = 255,
        .contourA2 = 1023,
        .contourB1 = 1023,
        .contourB2 = 1023,
        .contourC1 = 1023,
        .contourC2 = 1023,
    };

    T_IM_PRO_ELF_LGT_EDG_FUNC elfCtrlMin = {
        .zeroPoint = 0,
        .gainR = 0,
        .gainG = 0,
        .gainB = 0,
        .factorR = 0,
        .factorG = 0,
        .factorB = 0,
        .colorPara = 0,
        .contourR = 0,
        .contourG = 0,
        .contourB = 0,
        .contourA1 = 0,
        .contourA2 = 0,
        .contourB1 = 0,
        .contourB2 = 0,
        .contourC1 = 0,
        .contourC2 = 0,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Set_LGT_EDG_Filter(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_LGT_EDG_Filter(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_2(priv->imPro31Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Set_LGT_EDG_Filter(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_LGT_EDG_Filter(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_2(priv->imPro31Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_1_3(CtImPro31* self, const UINT32 idx)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);
    T_IM_PRO_ELF_L_E_FUNC elfCtrlMax = {
        .eThreshold1 = 1023,
        .eThreshold2 = 1023,
        .eThreshold3 = 1023,
        .eThreshold4 = 1023,
        .lThreshold = 1023,
        .lContour1 = 4095,
        .lContour2 = 4095,
        .lCintensity1 = 256,
        .lCintensity2 = 256,
    };

    T_IM_PRO_ELF_L_E_FUNC elfCtrlMin = {
        .eThreshold1 = 0,
        .eThreshold2 = 0,
        .eThreshold3 = 0,
        .eThreshold4 = 0,
        .lThreshold = -1024,
        .lContour1 = 0,
        .lContour2 = 0,
        .lCintensity1 = 0,
        .lCintensity2 = 0,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Set_E_L_Filter(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_E_L_Filter(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_3(priv->imPro31Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Set_E_L_Filter(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_E_L_Filter(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_3(priv->imPro31Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_1_4(CtImPro31* self, const UINT32 idx)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);
    T_IM_PRO_ELF_f9_SAMPLING elfCtrlMax = {
        .rgbGain.gain[0] = 1023,
        .rgbGain.gain[1] = 1023,
        .rgbGain.gain[2] = 1023,
        .ycConvMatrix[0] = 255,
        .ycConvMatrix[1] = 255,
        .ycConvMatrix[2] = 255,
        .ycConvMatrix[3] = 255,
        .ycConvMatrix[4] = 255,
        .ycConvMatrix[5] = 255,
        .ycConvMatrix[6] = 255,
        .ycConvMatrix[7] = 255,
        .ycConvMatrix[8] = 255,
        .f9aGroup.strength = 256,
        .f9aGroup.eFocusCoord[0] = 127,
        .f9aGroup.eFocusCoord[1] = 127,
        .f9aGroup.eFocusCoord[2] = 127,
        .f9aGroup.eFocusCoord[3] = 127,
        .f9aGroup.ePolygonalLineOffset1 = 511,
        .f9aGroup.ePolygonalLineMinusInclination[0] = 511,
        .f9aGroup.ePolygonalLineMinusInclination[1] = 511,
        .f9aGroup.ePolygonalLineBoundary1 = 127,
        .f9aGroup.eUpperClip = 511,
        .f9aGroup.eLowerClip = 511,
        .f9aGroup.lPolygonalLinePlusInclination0 = 255,
        .f9aGroup.lPolygonalLineMinusInclination1 = 255,
        .f9aGroup.lPolygonalLineBoundary[0] = 4095,
        .f9aGroup.lPolygonalLineBoundary[1] = 4095,
        .f9aGroup.lUpperClip = 511,
        .f9aGroup.lLowerClip = 511,
        .f9aGroup.tFProfileTransition = 15,
        .f9aGroup.tFProfileThreshold = 511,
        .f9bGroup.strength = 256,
        .f9bGroup.eFocusCoord[0] = 127,
        .f9bGroup.eFocusCoord[1] = 127,
        .f9bGroup.eFocusCoord[2] = 127,
        .f9bGroup.eFocusCoord[3] = 127,
        .f9bGroup.ePolygonalLineOffset1 = 511,
        .f9bGroup.ePolygonalLineMinusInclination[0] = 511,
        .f9bGroup.ePolygonalLineMinusInclination[1] = 511,
        .f9bGroup.ePolygonalLineBoundary1 = 127,
        .f9bGroup.eUpperClip = 511,
        .f9bGroup.eLowerClip = 511,
        .f9bGroup.lPolygonalLinePlusInclination0 = 255,
        .f9bGroup.lPolygonalLineMinusInclination1 = 255,
        .f9bGroup.lPolygonalLineBoundary[0] = 4095,
        .f9bGroup.lPolygonalLineBoundary[1] = 4095,
        .f9bGroup.lUpperClip = 511,
        .f9bGroup.lLowerClip = 511,
        .f9bGroup.tFProfileTransition = 15,
        .f9bGroup.tFProfileThreshold = 511,
    };

    T_IM_PRO_ELF_f9_SAMPLING elfCtrlMin = {
        .rgbGain.gain[0] = 0,
        .rgbGain.gain[1] = 0,
        .rgbGain.gain[2] = 0,
        .ycConvMatrix[0] = -256,
        .ycConvMatrix[1] = -256,
        .ycConvMatrix[2] = -256,
        .ycConvMatrix[3] = -256,
        .ycConvMatrix[4] = -256,
        .ycConvMatrix[5] = -256,
        .ycConvMatrix[6] = -256,
        .ycConvMatrix[7] = -256,
        .ycConvMatrix[8] = -256,
        .f9aGroup.strength = 0,
        .f9aGroup.eFocusCoord[0] = -128,
        .f9aGroup.eFocusCoord[1] = -128,
        .f9aGroup.eFocusCoord[2] = -128,
        .f9aGroup.eFocusCoord[3] = -128,
        .f9aGroup.ePolygonalLineOffset1 = 0,
        .f9aGroup.ePolygonalLineMinusInclination[0] = 0,
        .f9aGroup.ePolygonalLineMinusInclination[1] = 0,
        .f9aGroup.ePolygonalLineBoundary1 = 0,
        .f9aGroup.eUpperClip = 0,
        .f9aGroup.eLowerClip = 0,
        .f9aGroup.lPolygonalLinePlusInclination0 = 0,
        .f9aGroup.lPolygonalLineMinusInclination1 = 0,
        .f9aGroup.lPolygonalLineBoundary[0] = 0,
        .f9aGroup.lPolygonalLineBoundary[1] = 0,
        .f9aGroup.lUpperClip = 0,
        .f9aGroup.lLowerClip = 0,
        .f9aGroup.tFProfileTransition = 0,
        .f9aGroup.tFProfileThreshold = 0,
        .f9bGroup.strength = 0,
        .f9bGroup.eFocusCoord[0] = -128,
        .f9bGroup.eFocusCoord[1] = -128,
        .f9bGroup.eFocusCoord[2] = -128,
        .f9bGroup.eFocusCoord[3] = -128,
        .f9bGroup.ePolygonalLineOffset1 = 0,
        .f9bGroup.ePolygonalLineMinusInclination[0] = 0,
        .f9bGroup.ePolygonalLineMinusInclination[1] = 0,
        .f9bGroup.ePolygonalLineBoundary1 = 0,
        .f9bGroup.eUpperClip = 0,
        .f9bGroup.eLowerClip = 0,
        .f9bGroup.lPolygonalLinePlusInclination0 = 0,
        .f9bGroup.lPolygonalLineMinusInclination1 = 0,
        .f9bGroup.lPolygonalLineBoundary[0] = 0,
        .f9bGroup.lPolygonalLineBoundary[1] = 0,
        .f9bGroup.lUpperClip = 0,
        .f9bGroup.lLowerClip = 0,
        .f9bGroup.tFProfileTransition = 0,
        .f9bGroup.tFProfileThreshold = 0,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Set_F9_Filter(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_F9_Filter(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_4(priv->imPro31Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Set_F9_Filter(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_F9_Filter(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_4(priv->imPro31Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_1_5(CtImPro31* self, const UINT32 idx)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);
    T_IM_PRO_ELF_1s5_SAMPLING elfCtrlMax = {
        .s1s5Threshold[0] = 4095,
        .s1s5Threshold[1] = 4095,
        .s1s5Threshold[2] = 4095,
        .s1s5NrL1E13[0] = 256,
        .s1s5NrL1E13[1] = 256,
        .s1s5NrL1E13[2] = 256,
        .s1s5NrL2E13[0] = 256,
        .s1s5NrL2E13[1] = 256,
        .s1s5NrL2E13[2] = 256,
        .s1s5NrL3E13[0] = 256,
        .s1s5NrL3E13[1] = 256,
        .s1s5NrL3E13[2] = 256,
        .s1s5NrL4E13[0] = 256,
        .s1s5NrL4E13[1] = 256,
        .s1s5NrL4E13[2] = 256,
        .s1s5NrAdjustment[0] = 256,
        .s1s5NrAdjustment[1] = 256,
        .s1s5NrAdjustment[2] = 256,
        .s1s5NoiseLimitPlus = 4095,
        .s1s5NoiseLimitMinus = 4095,
    };

    T_IM_PRO_ELF_1s5_SAMPLING elfCtrlMin = {
        .s1s5Threshold[0] = 0,
        .s1s5Threshold[1] = 0,
        .s1s5Threshold[2] = 0,
        .s1s5NrL1E13[0] = 0,
        .s1s5NrL1E13[1] = 0,
        .s1s5NrL1E13[2] = 0,
        .s1s5NrL2E13[0] = 0,
        .s1s5NrL2E13[1] = 0,
        .s1s5NrL2E13[2] = 0,
        .s1s5NrL3E13[0] = 0,
        .s1s5NrL3E13[1] = 0,
        .s1s5NrL3E13[2] = 0,
        .s1s5NrL4E13[0] = 0,
        .s1s5NrL4E13[1] = 0,
        .s1s5NrL4E13[2] = 0,
        .s1s5NrAdjustment[0] = 0,
        .s1s5NrAdjustment[1] = 0,
        .s1s5NrAdjustment[2] = 0,
        .s1s5NoiseLimitPlus = 0,
        .s1s5NoiseLimitMinus = 0,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Set_1s5_Sampling(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_1s5_Sampling(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_5(priv->imPro31Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Set_1s5_Sampling(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_1s5_Sampling(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_5(priv->imPro31Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_1_6(CtImPro31* self, const UINT32 idx)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);
    T_IM_PRO_ELF_5s9_SAMPLING   elfCtrlMax = {
        .s5s9Threshold[0] = 4095,
        .s5s9Threshold[1] = 4095,
        .s5s9Threshold[2] = 4095,
        .s5s9NrL1E13[0] = 256,
        .s5s9NrL1E13[1] = 256,
        .s5s9NrL1E13[2] = 256,
        .s5s9NrL2E13[0] = 256,
        .s5s9NrL2E13[1] = 256,
        .s5s9NrL2E13[2] = 256,
        .s5s9NrL3E13[0] = 256,
        .s5s9NrL3E13[1] = 256,
        .s5s9NrL3E13[2] = 256,
        .s5s9NrL4E13[0] = 256,
        .s5s9NrL4E13[1] = 256,
        .s5s9NrL4E13[2] = 256,
        .s5s9NrAdjustment[0] = 256,
        .s5s9NrAdjustment[1] = 256,
        .s5s9NrAdjustment[2] = 256,
        .s5s9NoiseLimitPlus = 4095,
        .s5s9NoiseLimitMinus = 4095,
    };

    T_IM_PRO_ELF_5s9_SAMPLING elfCtrlMin = {
        .s5s9Threshold[0] = 0,
        .s5s9Threshold[1] = 0,
        .s5s9Threshold[2] = 0,
        .s5s9NrL1E13[0] = 0,
        .s5s9NrL1E13[1] = 0,
        .s5s9NrL1E13[2] = 0,
        .s5s9NrL2E13[0] = 0,
        .s5s9NrL2E13[1] = 0,
        .s5s9NrL2E13[2] = 0,
        .s5s9NrL3E13[0] = 0,
        .s5s9NrL3E13[1] = 0,
        .s5s9NrL3E13[2] = 0,
        .s5s9NrL4E13[0] = 0,
        .s5s9NrL4E13[1] = 0,
        .s5s9NrL4E13[2] = 0,
        .s5s9NrAdjustment[0] = 0,
        .s5s9NrAdjustment[1] = 0,
        .s5s9NrAdjustment[2] = 0,
        .s5s9NoiseLimitPlus = 0,
        .s5s9NoiseLimitMinus = 0,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Set_5s9_Sampling(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_5s9_Sampling(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_6(priv->imPro31Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Set_5s9_Sampling(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_5s9_Sampling(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_6(priv->imPro31Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_1_7(CtImPro31* self, const UINT32 idx)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);
    T_IM_PRO_ELF_Noise_Adj elfCtrlMax = {
        .nrStrengthL1[0] = 255,
        .nrStrengthL1[1] = 255,
        .nrStrengthL1[2] = 255,
        .nrStrengthL2[0] = 255,
        .nrStrengthL2[1] = 255,
        .nrStrengthL2[2] = 255,
        .nrStrengthL3[0] = 255,
        .nrStrengthL3[1] = 255,
        .nrStrengthL3[2] = 255,
        .nrStrengthL4[0] = 255,
        .nrStrengthL4[1] = 255,
        .nrStrengthL4[1] = 255,
        .afPathNrStrength = 255,
    };

    T_IM_PRO_ELF_Noise_Adj elfCtrlMin = {
        .nrStrengthL1[0] = 0,
        .nrStrengthL1[1] = 0,
        .nrStrengthL1[2] = 0,
        .nrStrengthL2[0] = 0,
        .nrStrengthL2[1] = 0,
        .nrStrengthL2[2] = 0,
        .nrStrengthL3[0] = 0,
        .nrStrengthL3[1] = 0,
        .nrStrengthL3[2] = 0,
        .nrStrengthL4[0] = 0,
        .nrStrengthL4[1] = 0,
        .nrStrengthL4[1] = 0,
        .afPathNrStrength = 0,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Set_Noise_Adj(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_Noise_Adj(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_7(priv->imPro31Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Set_Noise_Adj(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_Noise_Adj(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_7(priv->imPro31Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_1_8(CtImPro31* self, const UINT32 idx)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);
    T_IM_PRO_ELF_a0_FILTER elfCtrlMax = {
        .dpcMode = E_IM_PRO_ELF_A0_DPC_MODE_ENABLE_HIGH,
        .nce[0].offset[ 0 ] = 4095,
        .nce[0].offset[ 1 ] = 4095,
        .nce[0].offset[ 2 ] = 4095,
        .nce[0].offset[ 3 ] = 4095,
        .nce[1].offset[ 0 ] = 4095,
        .nce[1].offset[ 1 ] = 4095,
        .nce[1].offset[ 2 ] = 4095,
        .nce[1].offset[ 3 ] = 4095,
        .nce[2].offset[ 0 ] = 4095,
        .nce[2].offset[ 1 ] = 4095,
        .nce[2].offset[ 2 ] = 4095,
        .nce[2].offset[ 3 ] = 4095,
        .nce[0].gain[ 0 ] = 4095,
        .nce[0].gain[ 1 ] = 4095,
        .nce[0].gain[ 2 ] = 4095,
        .nce[0].gain[ 3 ] = 4095,
        .nce[1].gain[ 0 ] = 4095,
        .nce[1].gain[ 1 ] = 4095,
        .nce[1].gain[ 2 ] = 4095,
        .nce[1].gain[ 3 ] = 4095,
        .nce[2].gain[ 0 ] = 4095,
        .nce[2].gain[ 1 ] = 4095,
        .nce[2].gain[ 2 ] = 4095,
        .nce[2].gain[ 3 ] = 4095,
        .nce[0].areaBoundary[ 0 ] = 4095,
        .nce[0].areaBoundary[ 1 ] = 4095,
        .nce[0].areaBoundary[ 2 ] = 4095,
        .nce[0].areaBoundary[ 3 ] = 4095,
        .nce[1].areaBoundary[ 0 ] = 4095,
        .nce[1].areaBoundary[ 1 ] = 4095,
        .nce[1].areaBoundary[ 2 ] = 4095,
        .nce[1].areaBoundary[ 3 ] = 4095,
        .nce[2].areaBoundary[ 0 ] = 4095,
        .nce[2].areaBoundary[ 1 ] = 4095,
        .nce[2].areaBoundary[ 2 ] = 4095,
        .nce[2].areaBoundary[ 3 ] = 4095,
        .lumiRgbGain[0] = 1023,
        .lumiRgbGain[1] = 1023,
        .lumiRgbGain[2] = 1023,
        .lumiRgbCoeff[0] = 31,
        .lumiRgbCoeff[1] = 31,
        .lumiRgbCoeff[2] = 31,
        .lumiCCoeff = 31,
        .tWeight[0] = 31,
        .tWeight[1] = 31,
        .tWeight[2] = 31,
        .tAdjA.coeff1 = 255,
        .tAdjA.coeff2 = 255,
        .tAdjB.coeff1 = 255,
        .tAdjB.coeff2 = 255,
        .tLongWavelengthThreshold[0] = 4095,
        .tLongWavelengthThreshold[1] = 4095,
        .tLongWavelengthThreshold[2] = 4095,
        .tLongWavelengthNrStrength[0][0] = 511,
        .tLongWavelengthNrStrength[0][1] = 511,
        .tLongWavelengthNrStrength[0][2] = 511,
        .tLongWavelengthNrStrength[1][0] = 511,
        .tLongWavelengthNrStrength[1][1] = 511,
        .tLongWavelengthNrStrength[1][2] = 511,
        .tLongWavelengthNrStrength[2][0] = 511,
        .tLongWavelengthNrStrength[2][1] = 511,
        .tLongWavelengthNrStrength[2][2] = 511,
        .tLongWavelengthNrStrength[3][0] = 511,
        .tLongWavelengthNrStrength[3][1] = 511,
        .tLongWavelengthNrStrength[3][2] = 511,
        .lFilterExtractionThreshold = 4095,
        .lAppToleranceThreshold[0] = 4095,
        .lAppToleranceThreshold[1] = 4095,
        .lAppStrength[0] = 4095,
        .lAppStrength[1] = 4095,
        .longWavelengthNoisePLimiter = 4095,
        .longWavelengthNoiseMLimiter = 4095,
    };

    T_IM_PRO_ELF_a0_FILTER elfCtrlMin = {
        .dpcMode = E_IM_PRO_ELF_A0_DPC_MODE_DISABLE,
        .nce[0].offset[ 0 ] = 0,
        .nce[0].offset[ 1 ] = 0,
        .nce[0].offset[ 2 ] = 0,
        .nce[0].offset[ 3 ] = 0,
        .nce[1].offset[ 0 ] = 0,
        .nce[1].offset[ 1 ] = 0,
        .nce[1].offset[ 2 ] = 0,
        .nce[1].offset[ 3 ] = 0,
        .nce[2].offset[ 0 ] = 0,
        .nce[2].offset[ 1 ] = 0,
        .nce[2].offset[ 2 ] = 0,
        .nce[2].offset[ 3 ] = 0,
        .nce[0].gain[ 0 ] = 0,
        .nce[0].gain[ 1 ] = 0,
        .nce[0].gain[ 2 ] = 0,
        .nce[0].gain[ 3 ] = 0,
        .nce[1].gain[ 0 ] = 0,
        .nce[1].gain[ 1 ] = 0,
        .nce[1].gain[ 2 ] = 0,
        .nce[1].gain[ 3 ] = 0,
        .nce[2].gain[ 0 ] = 0,
        .nce[2].gain[ 1 ] = 0,
        .nce[2].gain[ 2 ] = 0,
        .nce[2].gain[ 3 ] = 0,
        .nce[0].areaBoundary[ 0 ] = 0,
        .nce[0].areaBoundary[ 1 ] = 0,
        .nce[0].areaBoundary[ 2 ] = 0,
        .nce[0].areaBoundary[ 3 ] = 0,
        .nce[1].areaBoundary[ 0 ] = 0,
        .nce[1].areaBoundary[ 1 ] = 0,
        .nce[1].areaBoundary[ 2 ] = 0,
        .nce[1].areaBoundary[ 3 ] = 0,
        .nce[2].areaBoundary[ 0 ] = 0,
        .nce[2].areaBoundary[ 1 ] = 0,
        .nce[2].areaBoundary[ 2 ] = 0,
        .nce[2].areaBoundary[ 3 ] = 0,
        .lumiRgbGain[0] = 0,
        .lumiRgbGain[1] = 0,
        .lumiRgbGain[2] = 0,
        .lumiRgbCoeff[0] = 0,
        .lumiRgbCoeff[1] = 0,
        .lumiRgbCoeff[2] = 0,
        .lumiCCoeff = 0,
        .tWeight[0] = 0,
        .tWeight[1] = 0,
        .tWeight[2] = 0,
        .tAdjA.coeff1 = 0,
        .tAdjA.coeff2 = 0,
        .tAdjB.coeff1 = 0,
        .tAdjB.coeff2 = 0,
        .tLongWavelengthThreshold[0] = 0,
        .tLongWavelengthThreshold[1] = 0,
        .tLongWavelengthThreshold[2] = 0,
        .tLongWavelengthNrStrength[0][0] = 0,
        .tLongWavelengthNrStrength[0][1] = 0,
        .tLongWavelengthNrStrength[0][2] = 0,
        .tLongWavelengthNrStrength[1][0] = 0,
        .tLongWavelengthNrStrength[1][1] = 0,
        .tLongWavelengthNrStrength[1][2] = 0,
        .tLongWavelengthNrStrength[2][0] = 0,
        .tLongWavelengthNrStrength[2][1] = 0,
        .tLongWavelengthNrStrength[2][2] = 0,
        .tLongWavelengthNrStrength[3][0] = 0,
        .tLongWavelengthNrStrength[3][1] = 0,
        .tLongWavelengthNrStrength[3][2] = 0,
        .lFilterExtractionThreshold = 0,
        .lAppToleranceThreshold[0] = 0,
        .lAppToleranceThreshold[1] = 0,
        .lAppStrength[0] = 0,
        .lAppStrength[1] = 0,
        .longWavelengthNoisePLimiter = 0,
        .longWavelengthNoiseMLimiter = 0,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Set_A0_Sampling(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_A0_Sampling(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_8(priv->imPro31Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Set_A0_Sampling(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_A0_Sampling(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_1_print_8(priv->imPro31Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_1_9(CtImPro31* self, const UINT32 idx)
{
	CtImPro31Private *priv = CT_IM_PRO3_1_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			Im_PRO_ELF_Start_NSL(priv->imProB2b, priv->unitNo);
			im_pro_3_1_print_9(priv->imPro31Print, priv->unitNo);
		}
    }
}

#endif   //CO_CT_IM_PRO_DISABLE

CtImPro31* ct_im_pro3_1_new(void)
{
	CtImPro31* self = k_object_new_with_private(CT_TYPE_IM_PRO3_1, sizeof(CtImPro31Private));

	return self;
}

