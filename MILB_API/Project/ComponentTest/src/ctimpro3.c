/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈元
*@brief : CtImPro3
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improb2b.h"
#include "improsro.h"
#include "ctimpro3.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro3, ct_im_pro3)
#define CT_IM_PRO3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro3Private, CT_TYPE_IM_PRO3))


struct _CtImPro3Private
{
	ImProB2b *imProB2b;
	ImProSro *imProSro;
	ImPro30Print *imPro30Print;
	E_IM_PRO_UNIT_NUM unitNo;
	kint32 ercd;
};


/**********
 * IMPL
 */
static void ct_im_pro3_constructor(CtImPro3 *self)
{
	CtImPro3Private *priv = CT_IM_PRO3_GET_PRIVATE(self);

	priv->imProB2b = im_pro_b2b_new();
	priv->imProSro = im_pro_sro_new();
	priv->imPro30Print = im_pro_3_0_print_new();
	priv->unitNo = 0;
	priv->ercd = 0;
}

static void ct_im_pro3_destructor(CtImPro3 *self)
{
	CtImPro3Private *priv = CT_IM_PRO3_GET_PRIVATE(self);

	if (priv->imProB2b) {
		k_object_unref(priv->imProB2b);
		priv->imProB2b = NULL;
	}

	if (priv->imProSro) {
		k_object_unref(priv->imProSro);
		priv->imProSro = NULL;
	}

	if (priv->imPro30Print) {
		k_object_unref(priv->imPro30Print);
		priv->imPro30Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE

void ct_im_pro3_1(CtImPro3* self, const UINT32 idx)
{
	CtImPro3Private *priv = CT_IM_PRO3_GET_PRIVATE(self);

    if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			Im_PRO_B2BTOP_Init(priv->imProB2b, priv->unitNo);
			Ddim_Print(
					("Im_PRO_B2BTOP_Init(%u) result:sr(%u)\n", priv->unitNo,
							ioPro.imgPipe[priv->unitNo].b2b.B2BTOP.sr.bit.sr));
		}
    }
}

void ct_im_pro3_2(CtImPro3* self, const UINT32 idx)
{
	CtImPro3Private *priv = CT_IM_PRO3_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
//            Ddim_Print(("Target register address\n"));
//            Ddim_Print(("Im_PRO_B2BTOP_SW_Reset(%u) sr (0x%08lx, %lx)\n", priv->unitNo, (kulong)&ioPro.imgPipe[priv->unitNo].b2b.B2BTOP.sr.word,   ioPro.imgPipe[priv->unitNo].b2b.B2BTOP.sr.word));

// Normal case
			priv->ercd = Im_PRO_B2BTOP_SW_Reset(priv->imProB2b, priv->unitNo);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_B2BTOP_SW_Reset(%u) Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				Ddim_Print(
						("Im_PRO_B2BTOP_SW_Reset(%u) result:sr(%u)\n", priv->unitNo,
								ioPro.imgPipe[priv->unitNo].b2b.B2BTOP.sr.bit.sr));
			}

			// illegal case
			impro_srovrb_start(priv->imProSro, priv->unitNo);

			priv->ercd = Im_PRO_B2BTOP_SW_Reset(priv->imProB2b, priv->unitNo);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_B2BTOP_SW_Reset(%u) Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				Ddim_Print(
						("Im_PRO_B2BTOP_SW_Reset(%u) result:sr(%u)\n", priv->unitNo,
								ioPro.imgPipe[priv->unitNo].b2b.B2BTOP.sr.bit.sr));
			}
			impro_srovrb_stop(priv->imProSro, priv->unitNo, 0);
		}
    }
}

void ct_im_pro3_3(CtImPro3* self, const UINT32 idx)
{
	CtImPro3Private *priv = CT_IM_PRO3_GET_PRIVATE(self);
    kuchar clkType;
    kuchar onOff;
    kuchar waitSkip;

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
//            Ddim_Print(("Target register address\n"));
//            Ddim_Print(("Im_PRO_B2BTOP_Control_Clock(%lu) clkstp1 (0x%08lx, %lx)\n", priv->unitNo, (kulong)&ioPro.imgPipe[priv->unitNo].b2b.B2BTOP.clkstp.word, ioPro.imgPipe[priv->unitNo].b2b.B2BTOP.clkstp.word));

			for (waitSkip = 0; waitSkip < 2; waitSkip++) {
				for (clkType = E_IM_PRO_B2BTOP_CLK_TYPE_B2BCLK; clkType < E_IM_PRO_B2BTOP_CLK_TYPE_B2BCLK + 1;
						clkType++) {
					// STATCLK ON
					onOff = D_IM_PRO_CLOCK_ON;
					priv->ercd = Im_PRO_B2BTOP_Control_Clock(priv->imProB2b, priv->unitNo, clkType, onOff, waitSkip);
					if (priv->ercd != DdimUserCustom_E_OK) {
						Ddim_Print(
								("Im_PRO_B2BTOP_Control_Clock(%u, %u, %u, %u) Error priv->ercd=0x%x\n",
										priv->unitNo, clkType, onOff, waitSkip, priv->ercd));
					} else {
						Ddim_Print(
								("Im_PRO_B2BTOP_Control_Clock(%u, %u, %u, %u) result:clkstp1(%lu)\n",
										priv->unitNo, clkType, onOff, waitSkip,
										ioPro.imgPipe[priv->unitNo].b2b.B2BTOP.clkstp.word));
					}

					// STATCLK OFF
					onOff = D_IM_PRO_CLOCK_OFF;
					priv->ercd = Im_PRO_B2BTOP_Control_Clock(priv->imProB2b, priv->unitNo, clkType, onOff, waitSkip);
					if (priv->ercd != DdimUserCustom_E_OK) {
						Ddim_Print(
								("Im_PRO_B2BTOP_Control_Clock(%u, %u, %u, %u) Error priv->ercd=0x%x\n",
										priv->unitNo, clkType, onOff, waitSkip, priv->ercd));
					} else {
						Ddim_Print(
								("Im_PRO_B2BTOP_Control_Clock(%u, %u, %u, %u) result:clkstp1(%lu)\n",
										priv->unitNo, clkType, onOff, waitSkip,
										ioPro.imgPipe[priv->unitNo].b2b.B2BTOP.clkstp.word));
					}
                }
            }
        }
    }
}

void ct_im_pro3_4(CtImPro3* self, const UINT32 idx)
{
	CtImPro3Private *priv = CT_IM_PRO3_GET_PRIVATE(self);
    T_IM_PRO_B2BTOP_CTRL b2bTopCtrlMax = {
    };

    T_IM_PRO_B2BTOP_CTRL b2bTopCtrlMin = {
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_B2BTOP_Ctrl(priv->imProB2b, priv->unitNo, &b2bTopCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_B2BTOP_Ctrl(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_0_print_4(priv->imPro30Print, "max_para", priv->unitNo, priv->ercd, &b2bTopCtrlMax);
			}

			priv->ercd = Im_PRO_B2BTOP_Ctrl(priv->imProB2b, priv->unitNo, &b2bTopCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_B2BTOP_Ctrl(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_0_print_4(priv->imPro30Print, "min_para", priv->unitNo, priv->ercd, &b2bTopCtrlMin);
			}
        }
    }
}

void ct_im_pro3_5(CtImPro3* self, const UINT32 idx)
{
	CtImPro3Private *priv = CT_IM_PRO3_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			Im_PRO_ELF_Start(priv->imProB2b, priv->unitNo);
			im_pro_3_0_print_5(priv->imPro30Print, priv->unitNo);
		}
    }
}

void ct_im_pro3_6(CtImPro3* self, const UINT32 idx)
{
	CtImPro3Private *priv = CT_IM_PRO3_GET_PRIVATE(self);
    kuchar force;

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			for (force = 0; force < 2 + 1; force++) {
#ifdef CO_DEBUG_ON_PC
				ioPro.imgPipe[priv->unitNo].b2b.elf.elftrg.bit.elftrg = 3;
#endif
				Im_PRO_ELF_Stop(priv->imProB2b, priv->unitNo, force);
				im_pro_3_0_print_6(priv->imPro30Print, priv->unitNo, force);
			}
        }
    }
}

void ct_im_pro3_7(CtImPro3* self, const UINT32 idx)
{
	CtImPro3Private *priv = CT_IM_PRO3_GET_PRIVATE(self);
    kuchar paenTrg;

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			for (paenTrg = 0; paenTrg < 2 + 1; paenTrg++) {
				priv->ercd = Im_PRO_ELF_Set_PAEN(priv->imProB2b, priv->unitNo, paenTrg);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(("Im_PRO_ELF_Set_PAEN(%u) Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
				} else {
					im_pro_3_0_print_7(priv->imPro30Print, priv->unitNo, paenTrg);
				}
			}
        }
    }
}

void ct_im_pro3_8(CtImPro3* self, const UINT32 idx)
{
	CtImPro3Private *priv = CT_IM_PRO3_GET_PRIVATE(self);
    T_IM_PRO_ELF_COMMON_CTRL elfCtrlMax = {
        .pixPadding = E_IM_PRO_ELF_PDD_EN,
        .paddingMode = E_IM_PRO_ELF_PDD_MODE_SURROUND_8PIX,
        .nrSelect = E_IM_PRO_ELF_ELFAFS_NR_PATH,
    };

    T_IM_PRO_ELF_COMMON_CTRL elfCtrlMin = {
        .pixPadding = E_IM_PRO_ELF_PDD_DIS,
        .paddingMode = E_IM_PRO_ELF_PDD_MODE_SURROUND_4PIX,
        .nrSelect = E_IM_PRO_ELF_ELFAFS_MAIN_PATH,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Ctrl_Common(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Ctrl_Common(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_0_print_8(priv->imPro30Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Ctrl_Common(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_ELF_Ctrl_Common(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_0_print_8(priv->imPro30Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

void ct_im_pro3_9(CtImPro3* self, const UINT32 idx)
{
	CtImPro3Private *priv = CT_IM_PRO3_GET_PRIVATE(self);
    T_IM_PRO_ELF_CTRL elfCtrlMax = {
        .cmn1.n1s5Enable = E_IM_PRO_ELF_N1S5EN_EN,
        .cmn1.n5s9Enable = E_IM_PRO_ELF_N5S9EN_EN,
        .cmn1.f9Enable = E_IM_PRO_ELF_NFS9EN_EN,
        .cmn1.a0Enable = E_IM_PRO_ELF_NLA0EN_EN,
        .cmn1.f5FilterMode = E_IM_PRO_ELF_F5_MD_WEAK,
        .cmn1.f9FilterMode = E_IM_PRO_ELF_F9_MD_WEAK,
        .cmn1.eFilterMode = E_IM_PRO_ELF_EFMD_EN,
        .cmn1.lFilterMode = E_IM_PRO_ELF_LFMD_EN,
        .cmn2.elfl1 = 4095,
        .cmn2.elfl2 = 4095,
        .cmn2.elfl3 = 4095,
        .cmn2.elfl4 = 4095,
    };

    T_IM_PRO_ELF_CTRL elfCtrlMin = {
        .cmn1.n1s5Enable = E_IM_PRO_ELF_N1S5EN_DIS,
        .cmn1.n5s9Enable = E_IM_PRO_ELF_N5S9EN_DIS,
        .cmn1.f9Enable = E_IM_PRO_ELF_NFS9EN_DIS,
        .cmn1.a0Enable = E_IM_PRO_ELF_NLA0EN_DIS,
        .cmn1.f5FilterMode = E_IM_PRO_ELF_F5_MD_STRONG,
        .cmn1.f9FilterMode = E_IM_PRO_ELF_F9_MD_STRONG,
        .cmn1.eFilterMode = E_IM_PRO_ELF_EFMD_DIS,
        .cmn1.lFilterMode = E_IM_PRO_ELF_LFMD_DIS,
        .cmn2.elfl1 = 0,
        .cmn2.elfl2 = 0,
        .cmn2.elfl3 = 0,
        .cmn2.elfl4 = 0,
    };

	if (idx == 1) {
		for (priv->unitNo = 0; priv->unitNo < E_IM_PRO_UNIT_NUM_MAX; priv->unitNo++) {
			priv->ercd = Im_PRO_ELF_Ctrl(priv->imProB2b, priv->unitNo, &elfCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_ELF_Ctrl(%u) max_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_0_print_9(priv->imPro30Print, "max_para", priv->unitNo, priv->ercd, &elfCtrlMax);
			}

			priv->ercd = Im_PRO_ELF_Ctrl(priv->imProB2b, priv->unitNo, &elfCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_ELF_Ctrl(%u) min_para Error priv->ercd=0x%x\n", priv->unitNo, priv->ercd));
			} else {
				im_pro_3_0_print_9(priv->imPro30Print, "min_para", priv->unitNo, priv->ercd, &elfCtrlMin);
			}
        }
    }
}

#endif   //CO_CT_IM_PRO_DISABLE

CtImPro3* ct_im_pro3_new(void)
{
	CtImPro3* self = k_object_new_with_private(CT_TYPE_IM_PRO3, sizeof(CtImPro3Private));

	return self;
}

