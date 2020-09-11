/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈元
*@brief : CtImPro33
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improb2b.h"
#include "ctimpro33.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro33, ct_im_pro3_3)
#define CT_IM_PRO3_3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro33Private, CT_TYPE_IM_PRO3_3))


struct _CtImPro33Private
{
	ImProB2b *imProB2b;
	ImPro33Print *imPro33Print;
	kint32 ercd;
	E_IM_PRO_UNIT_NUM unitNo;
};


/**********
 * IMPL
 */
static void ct_im_pro3_3_constructor(CtImPro33 *self)
{
	CtImPro33Private *priv = CT_IM_PRO3_3_GET_PRIVATE(self);

	priv->imProB2b = im_pro_b2b_new();
	priv->imPro33Print = im_pro_3_3_print_new();
	priv->ercd = 0;
	priv->unitNo = 0;
}

static void ct_im_pro3_3_destructor(CtImPro33 *self)
{
	CtImPro33Private *priv = CT_IM_PRO3_3_GET_PRIVATE(self);

	if (priv->imProB2b) {
		k_object_unref(priv->imProB2b);
		priv->imProB2b = NULL;
	}

	if (priv->imPro33Print) {
		k_object_unref(priv->imPro33Print);
		priv->imPro33Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE

void ct_im_pro3_3_0(CtImPro33* self, const UINT32 idx)
{
	CtImPro33Private *priv = CT_IM_PRO3_3_GET_PRIVATE(self);
    T_IM_PRO_AREA_INFO fshdCtrlMax = {
        .posX = 4095,
        .posY = 8960,
        .width = 2496,
        .lines = 8960,
    };

    T_IM_PRO_AREA_INFO fshdCtrlMin = {
        .posX = 0,
        .posY = 2,
        .width = 4,
        .lines = 4,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_FSHD_Set_Area(priv->imProB2b, priv->unitNo, &fshdCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Set_Area(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_3_print_0(priv->imPro33Print, "max_para", priv->unitNo, priv->ercd, &fshdCtrlMax);
			}

			priv->ercd = Im_PRO_FSHD_Set_Area(priv->imProB2b, priv->unitNo, &fshdCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Set_Area(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_3_print_0(priv->imPro33Print, "min_para", priv->unitNo, priv->ercd, &fshdCtrlMin);
			}
        }
    }
}

void ct_im_pro3_3_1(CtImPro33* self, const UINT32 idx)
{
	CtImPro33Private *priv = CT_IM_PRO3_3_GET_PRIVATE(self);
    T_IM_PRO_FSHD_BLEND_CTRL fshdCtrlMax = {
        .shadingBlend0 = 511,
        .shadingBlend1 = 511,
    };

    T_IM_PRO_FSHD_BLEND_CTRL fshdCtrlMin = {
        .shadingBlend0 = -512,
        .shadingBlend1 = -512,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_FSHD_Set_Blend(priv->imProB2b, priv->unitNo, &fshdCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Set_Blend(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_3_print_1(priv->imPro33Print, "max_para", priv->unitNo, priv->ercd, &fshdCtrlMax);
			}

			priv->ercd = Im_PRO_FSHD_Set_Blend(priv->imProB2b, priv->unitNo, &fshdCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Set_Blend(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_3_print_1(priv->imPro33Print, "min_para", priv->unitNo, priv->ercd, &fshdCtrlMin);
			}
        }
    }
}

void ct_im_pro3_3_2(CtImPro33* self, const UINT32 idx)
{
	CtImPro33Private *priv = CT_IM_PRO3_3_GET_PRIVATE(self);
    T_IM_PRO_FSHD_FRAME_CTRL fshdCtrlMax = {
        .fsctl = E_IM_PRO_FSHD_CORRECTION_FORMAT_1,
        .frameHorizontalSize = 314,
        .frameVerticalSize = 1122,
        .horizontalPixel = 724,
        .verticalPixel = 724,
        .inverseBase = 65535,
        .inverseExponent = 11,
        .montagePosH = 2496,
        .startPosH = 722,
        .startPosV = 722,
        .magnificationR = 511,
        .magnificationGr = 511,
        .magnificationGb = 511,
        .magnificationB = 511,
        .satCorrectionEnabled = E_IM_PRO_FSHD_SAT_CORRECTION_EN,
        .satSlopeGain[0] = 4095,
        .satSlopeGain[1] = 4095,
        .satSlopeGain[2] = 4095,
        .satSlopeGain[3] = 4095,
    };

    T_IM_PRO_FSHD_FRAME_CTRL fshdCtrlMin = {
        .fsctl = E_IM_PRO_FSHD_CORRECTION_FORMAT_0,
        .frameHorizontalSize = 4,
        .frameVerticalSize = 4,
        .horizontalPixel = 16,
        .verticalPixel = 16,
        .inverseBase = 0,
        .inverseExponent = 0,
        .montagePosH = 4,
        .startPosH = 0,
        .startPosV = 0,
        .magnificationR = 0,
        .magnificationGr = 0,
        .magnificationGb = 0,
        .magnificationB = 0,
        .satCorrectionEnabled = E_IM_PRO_FSHD_SAT_CORRECTION_DIS,
        .satSlopeGain[0] = 0,
        .satSlopeGain[1] = 0,
        .satSlopeGain[2] = 0,
        .satSlopeGain[3] = 0,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_FSHD_Set_Frame(priv->imProB2b, priv->unitNo, &fshdCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Set_Frame(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_3_print_2(priv->imPro33Print, "max_para", priv->unitNo, priv->ercd, &fshdCtrlMax);
			}

			priv->ercd = Im_PRO_FSHD_Set_Frame(priv->imProB2b, priv->unitNo, &fshdCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Set_Frame(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_3_print_2(priv->imPro33Print, "min_para", priv->unitNo, priv->ercd, &fshdCtrlMin);
			}
		}
    }
}

void ct_im_pro3_3_3(CtImPro33* self, const UINT32 idx)
{
	CtImPro33Private *priv = CT_IM_PRO3_3_GET_PRIVATE(self);
    T_IM_PRO_FSHD_CONCENTRIC_CTRL fshdCtrlMax = {
        .selectRam = E_IM_PRO_FSHD_LUT_SEL_RAM1,
        .selectFormat = E_IM_PRO_FSHD_CORRECTION_FORMAT_1,
        .interpolatedVal = 7,
        .intervalH = 64,
        .intervalV = 64,
        .startAddressR = 1023,
        .startAddressGr = 1023,
        .startAddressGb = 1023,
        .startAddressB = 1023,
        .offset = 16383,
        .clipValue = 16383,
        .posH = 16383,
        .posV = 16383,
        .magnificationR = 511,
        .magnificationGr = 511,
        .magnificationGb = 511,
        .magnificationB = 511,
    };

    T_IM_PRO_FSHD_CONCENTRIC_CTRL fshdCtrlMin = {
        .selectRam = E_IM_PRO_FSHD_LUT_SEL_RAM0,
        .selectFormat = E_IM_PRO_FSHD_CORRECTION_FORMAT_0,
        .interpolatedVal = 0,
        .intervalH = 16,
        .intervalV = 16,
        .startAddressR = 2,
        .startAddressGr = 2,
        .startAddressGb = 2,
        .startAddressB = 2,
        .offset = 0,
        .clipValue = 0,
        .posH = 0,
        .posV = 0,
        .magnificationR = 0,
        .magnificationGr = 0,
        .magnificationGb = 0,
        .magnificationB = 0,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_FSHD_Set_Concentric(priv->imProB2b, priv->unitNo, &fshdCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Set_Concentric(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_3_print_3(priv->imPro33Print, "max_para", priv->unitNo, priv->ercd, &fshdCtrlMax);
			}

			priv->ercd = Im_PRO_FSHD_Set_Concentric(priv->imProB2b, priv->unitNo, &fshdCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Set_Concentric(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_3_print_3(priv->imPro33Print, "min_para", priv->unitNo, priv->ercd, &fshdCtrlMin);
			}
        }
    }
}

void ct_im_pro3_3_4(CtImPro33* self, const UINT32 idx)
{
	CtImPro33Private *priv = CT_IM_PRO3_3_GET_PRIVATE(self);
    E_IM_PRO_FSHD_LUT_SEL fshdCtrl;

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			fshdCtrl = Im_PRO_FSHD_Get_Ctbl_Number(priv->imProB2b, priv->unitNo);
			Ddim_Print(
					("Im_PRO_FSHD_Get_Ctbl_Number(%u) result:CSTBST 0x%08lx(%d) in(%d)\n",
							priv->unitNo, (kulong)&ioPro.imgPipe[priv->unitNo].b2b.fshd.CSTBLST.word,
							ioPro.imgPipe[priv->unitNo].b2b.fshd.CSTBLST.bit.CSTBST, fshdCtrl ));
		}
    }
}

void ct_im_pro3_3_5(CtImPro33* self, const UINT32 idx)
{
	CtImPro33Private *priv = CT_IM_PRO3_3_GET_PRIVATE(self);
    kint32 cmpErcd;
    kuchar tblSel;
    T_IM_PRO_FSHD_TABLE fshdCtrlMax;
    T_IM_PRO_FSHD_TABLE fshdCtrlMin;
    kint16 fshdTbl[1024];
    const T_IM_PRO_FSHD_INFO* fshdInfo;

	if (idx == 1) {
		fshdCtrlMax.pshdTbl = fshdTbl;
		fshdCtrlMax.size = 1024;

		fshdCtrlMin.pshdTbl = fshdTbl;
		fshdCtrlMin.size = 1024;
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {

			for (tblSel = E_IM_PRO_FSHD_LUT_SEL_RAM0; tblSel < E_IM_PRO_FSHD_LUT_SEL_RAM1 + 1; tblSel++) {
				memset(fshdTbl, 0xFFFF, sizeof(fshdTbl));
				priv->ercd = Im_PRO_FSHD_Set_Table(priv->imProB2b, priv->unitNo, tblSel, &fshdCtrlMax);

				im_pro_comm_get_fshd_reg_info(priv->imProB2b, priv->unitNo, &fshdInfo);
				if (priv->ercd == DdimUserCustom_E_OK) {
					cmpErcd = memcmp((void*) &fshdInfo->tblRegPtr[tblSel].hword[0], fshdTbl,
							fshdCtrlMax.size * sizeof(kint16));
				} else {
					cmpErcd = -1;
				}
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_FSHD_Set_Table(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
				} else {
					//pgr0539
					im_pro_3_3_print_5(priv->imPro33Print, "max_para", priv->unitNo, tblSel, priv->ercd, cmpErcd);
				}

				memset(fshdTbl, 0, sizeof(fshdTbl));
				if (priv->ercd == DdimUserCustom_E_OK) {
					cmpErcd = memcmp((void*) &fshdInfo->tblRegPtr[tblSel].hword[0], fshdTbl,
							fshdCtrlMin.size * sizeof(kint16));
				} else {
					cmpErcd = -1;
				}
				priv->ercd = Im_PRO_FSHD_Set_Table(priv->imProB2b, priv->unitNo, tblSel, &fshdCtrlMin);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_FSHD_Set_Table(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
				} else {
					im_pro_3_3_print_5(priv->imPro33Print, "min_para", priv->unitNo, tblSel, priv->ercd, cmpErcd); /* pgr0539 */
				}
            }
        }
    }
}

void ct_im_pro3_3_6(CtImPro33* self, const UINT32 idx)
{
	CtImPro33Private *priv = CT_IM_PRO3_3_GET_PRIVATE(self);
    kuint16 fshdCtrlMax = 1023;
    kuint16 fshdCtrlMin = 4;

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_FSHD_Set_Coeff_Read_Line_Wait(priv->imProB2b, priv->unitNo, fshdCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Set_Coeff_Read_Line_Wait(%u) max_para Error priv->ercd=0x%x\n",
								priv->unitNo, priv->ercd));
			} else {
				im_pro_3_3_print_6(priv->imPro33Print, "max_para", priv->unitNo, priv->ercd, fshdCtrlMax);
			}

			priv->ercd = Im_PRO_FSHD_Set_Coeff_Read_Line_Wait(priv->imProB2b, priv->unitNo, fshdCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Set_Coeff_Read_Line_Wait(%u) min_para Error priv->ercd=0x%x\n",
								priv->unitNo, priv->ercd));
			} else {
				im_pro_3_3_print_6(priv->imPro33Print, "min_para", priv->unitNo, priv->ercd, fshdCtrlMin);
			}
		}
    }
}

void ct_im_pro3_3_7(CtImPro33* self, const UINT32 idx)
{
	CtImPro33Private *priv = CT_IM_PRO3_3_GET_PRIVATE(self);
    const T_IM_PRO_RDMA_FSHD_ADDR* fshdCtrl;

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_Get_RdmaAddr_FSHD_Cntl(priv->imProB2b, priv->unitNo, &fshdCtrl);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) max_para Error priv->ercd=0x%x\n",
								priv->unitNo, priv->ercd));
			} else {
				im_pro_3_3_print_7(priv->imPro33Print, "", priv->unitNo, priv->ercd, &fshdCtrl);
			}
        }
    }
}

void ct_im_pro3_3_8(CtImPro33* self, const UINT32 idx)
{
	CtImPro33Private *priv = CT_IM_PRO3_3_GET_PRIVATE(self);
    kuchar tblSel;
    const T_IM_PRO_RDMA_FSHD_CTBL_ADDR* fshdCtrl;

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			for (tblSel = E_IM_PRO_FSHD_LUT_SEL_RAM0; tblSel < E_IM_PRO_FSHD_LUT_SEL_RAM1 + 1; tblSel++) {
				priv->ercd = Im_PRO_Get_RdmaAddr_FSHD_Ctbl(priv->imProB2b, priv->unitNo, tblSel, &fshdCtrl);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_Get_RdmaAddr_FSHD_Ctbl(%u %u) max_para Error priv->ercd=0x%x\n",
									priv->unitNo, tblSel, priv->ercd));
				} else {
					im_pro_3_3_print_8(priv->imPro33Print, "", priv->unitNo, tblSel, priv->ercd, &fshdCtrl);
				}
            }
        }
    }
}

#endif   //CO_CT_IM_PRO_DISABLE

CtImPro33* ct_im_pro3_3_new(void)
{
	CtImPro33* self = k_object_new_with_private(CT_TYPE_IM_PRO3_3, sizeof(CtImPro33Private));

	return self;
}

