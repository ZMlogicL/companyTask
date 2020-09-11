/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈元
*@brief : CtImPro32
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improb2b.h"
#include "ctimpro32.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro32, ct_im_pro3_2)
#define CT_IM_PRO3_2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro32Private, CT_TYPE_IM_PRO3_2))


struct _CtImPro32Private
{
	ImProB2b *imProB2b;
	ImPro32Print *imPro32Print;
	kint32 ercd;
	E_IM_PRO_UNIT_NUM unitNo;
	kuchar paenTrg;
};


/**********
 * IMPL
 */
static void ct_im_pro3_2_constructor(CtImPro32 *self)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);

	priv->imProB2b = im_pro_b2b_new();
	priv->imPro32Print = im_pro_3_2_print_new();
	priv->ercd = 0;
	priv->unitNo = 0;
	priv->paenTrg = 0;
}

static void ct_im_pro3_2_destructor(CtImPro32 *self)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);

	if (priv->imProB2b) {
		k_object_unref(priv->imProB2b);
		priv->imProB2b = NULL;
	}

	if (priv->imPro32Print) {
		k_object_unref(priv->imPro32Print);
		priv->imPro32Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE

void ct_im_pro3_2_0(CtImPro32* self, const UINT32 idx)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);
    kuchar force;

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			for (force = 0; force < 2 + 1; force++) {
#ifdef CO_DEBUG_ON_PC
				ioPro.imgPipe[priv->unitNo].b2b.elf.nsltrg.bit.nsltrg = 3;
#endif
				Im_PRO_ELF_Stop_NSL(priv->imProB2b, priv->unitNo, force);
				im_pro_3_2_print_0(priv->imPro32Print, priv->unitNo, force);
			}
		}
    }
}


void ct_im_pro3_2_1(CtImPro32* self, const UINT32 idx)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);
    T_IM_PRO_NSL_CTRL elfCtrlMax = {
        .lNoiseMode = E_IM_PRO_ELF_NSLMD_MAGNIFICATION,
        .lNoisePrecision = E_IM_PRO_ELF_NSLRES_3,
        .longNoiseComp = E_IM_PRO_ELF_NSLKEN_EN,
    };

    T_IM_PRO_NSL_CTRL elfCtrlMin = {
        .lNoiseMode = E_IM_PRO_ELF_NSLMD_REDUCTION,
        .lNoisePrecision = E_IM_PRO_ELF_NSLRES_0,
        .longNoiseComp = E_IM_PRO_ELF_NSLKEN_DIS,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Ctrl_NSL(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Ctrl_NSL(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_2_print_1(priv->imPro32Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Ctrl_NSL(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Ctrl_NSL(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_2_print_1(priv->imPro32Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_2_2(CtImPro32* self, const UINT32 idx)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			for (priv->paenTrg = 0; priv->paenTrg < 2 + 1; priv->paenTrg++) {
				priv->ercd = Im_PRO_ELF_Set_A0_PAEN(priv->imProB2b, priv->unitNo, priv->paenTrg);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_ELF_Set_A0_PAEN(%u) Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
				} else {
					im_pro_3_2_print_2(priv->imPro32Print, priv->unitNo, priv->paenTrg);
				}
            }
        }
    }
}

void ct_im_pro3_2_3(CtImPro32* self, const UINT32 idx)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			for (priv->paenTrg = 0; priv->paenTrg < 2 + 1; priv->paenTrg++) {
				priv->ercd = Im_PRO_ELF_Set_NSL_PAEN(priv->imProB2b, priv->unitNo, priv->paenTrg);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_ELF_Set_NSL_PAEN(%u) Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
				} else {
					im_pro_3_2_print_3(priv->imPro32Print, priv->unitNo, priv->paenTrg);
				}
            }
        }
    }
}

void ct_im_pro3_2_4(CtImPro32* self, const UINT32 idx)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);
    const T_IM_PRO_RDMA_ELF_ADDR* elfCtrl;

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_Get_RdmaAddr_ELF_Cntl(priv->imProB2b, priv->unitNo, &elfCtrl);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("impro_sroffc_get_rdma_addr_ffc_cntl(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_2_print_4(priv->imPro32Print, "", priv->unitNo, priv->ercd, &elfCtrl);
			}
        }
    }
}

void ct_im_pro3_2_5(CtImPro32* self, const UINT32 idx)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);
    T_IM_PRO_ELF_HIGH_FREQ_AREA_EDGE_ADJ elfCtrlMax = {
        .highFreqAreaAdjCoeff = 4095,
        .testPara1 = 0xFF,
        .testPara2 = 0xFF,
    };

    T_IM_PRO_ELF_HIGH_FREQ_AREA_EDGE_ADJ elfCtrlMin = {
        .highFreqAreaAdjCoeff = 0,
        .testPara1 = 0xFF,
        .testPara2 = 0x09,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Set_Edge_Adj(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_Edge_Adj(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_2_print_5(priv->imPro32Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Set_Edge_Adj(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Set_Edge_Adj(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_2_print_5(priv->imPro32Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_2_6(CtImPro32* self, const UINT32 idx)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			Im_PRO_FSHD_Start(priv->imProB2b, priv->unitNo);
			im_pro_3_2_print_6(priv->imPro32Print, priv->unitNo);
		}
	}
}

void ct_im_pro3_2_7(CtImPro32* self, const UINT32 idx)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);
    kuchar force;

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			for (force = 0; force < 2 + 1; force++) {
#ifdef CO_DEBUG_ON_PC
				ioPro.imgPipe[priv->unitNo].b2b.fshd.fshdtrg.bit.fshdtrg = 3;
#endif
				Im_PRO_FSHD_Stop(priv->imProB2b, priv->unitNo, force);
				im_pro_3_2_print_7(priv->imPro32Print, priv->unitNo, force);
			}
		}
    }
}

void ct_im_pro3_2_8(CtImPro32* self, const UINT32 idx)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);
    T_IM_PRO_FSHD_COMMON_CTRL fshdCtrlMax = {
        .correctionMode = E_IM_PRO_FSHD_FRAME_CONCENTRIC_ADDITION,
        .correctionModeAwb = E_IM_PRO_FSHD_FRAME,
        .montageMode = ImproSrofshdl_E_IM_PRO_FSHD_MONTAGE_MODE_ON,
        .clipR = 4095,
        .clipGr = 4095,
        .clipGb = 4095,
        .clipB = 4095,
    };

    T_IM_PRO_FSHD_COMMON_CTRL fshdCtrlMin = {
        .correctionMode = E_IM_PRO_FSHD_FRAME_ONLY,
        .correctionModeAwb = E_IM_PRO_FSHD_FSMODE,
        .montageMode = ImproSrofshdl_E_IM_PRO_FSHD_MONTAGE_MODE_OFF,
        .clipR = 0,
        .clipGr = 0,
        .clipGb = 0,
        .clipB = 0,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_FSHD_Ctrl(priv->imProB2b, priv->unitNo, &fshdCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Ctrl(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_2_print_8(priv->imPro32Print, "max_para", priv->unitNo, priv->ercd, &fshdCtrlMax);
			}

			priv->ercd = Im_PRO_FSHD_Ctrl(priv->imProB2b, priv->unitNo, &fshdCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FSHD_Ctrl(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_2_print_8(priv->imPro32Print, "min_para", priv->unitNo, priv->ercd, &fshdCtrlMin);
			}
        }
    }
}

void ct_im_pro3_2_9(CtImPro32* self, const UINT32 idx)
{
	CtImPro32Private *priv = CT_IM_PRO3_2_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			for (priv->paenTrg = 0; priv->paenTrg < 2 + 1; priv->paenTrg++) {
				priv->ercd = Im_PRO_FSHD_Set_PAEN(priv->imProB2b, priv->unitNo, priv->paenTrg);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(("Im_PRO_FSHD_Set_PAEN(%u) Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
				} else {
					im_pro_3_2_print_9(priv->imPro32Print, priv->unitNo, priv->paenTrg);
				}
            }
        }
    }
}

#endif   //CO_CT_IM_PRO_DISABLE

CtImPro32* ct_im_pro3_2_new(void)
{
	CtImPro32* self = k_object_new_with_private(CT_TYPE_IM_PRO3_2, sizeof(CtImPro32Private));

	return self;
}

