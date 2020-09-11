/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈阳
*@brief : CtImPro4
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improstat.h"
#include "ctimpro4.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro4, ct_im_pro4)
#define CT_IM_PRO4_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro4Private, CT_TYPE_IM_PRO4))


struct _CtImPro4Private
{
	ImProStat *imProStat;
	ImPro40Print *imPro40Print;
	ImPro41Print *imPro41Print;
	ImPro42Print *imPro42Print;
	kint32 		ercd;
	kuchar    	ch;
};


/********
 * IMPL
 */
static void ct_im_pro4_constructor(CtImPro4 *self)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);

	priv->imProStat = im_pro_stat_new();
	priv->imPro40Print = im_pro_4_0_print_new();
	priv->imPro41Print = im_pro_4_1_print_new();
	priv->imPro42Print = im_pro_4_2_print_new();
	priv->ercd = 0;
	priv->ch = 0;
}

static void ct_im_pro4_destructor(CtImPro4 *self)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);

	if (priv->imProStat) {
		k_object_unref(priv->imProStat);
		priv->imProStat = NULL;
	}

	if (priv->imPro40Print) {
		k_object_unref(priv->imPro40Print);
		priv->imPro40Print = NULL;
	}

	if (priv->imPro41Print) {
		k_object_unref(priv->imPro41Print);
		priv->imPro41Print = NULL;
	}

	if (priv->imPro42Print) {
		k_object_unref(priv->imPro42Print);
		priv->imPro42Print = NULL;
	}


}


/********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro4_1(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);

    if (idx == 1) {
        Im_PRO_STATTOP_Init(priv->imProStat);
        Ddim_Print(("Im_PRO_STATTOP_Init() result:sr(%u)\n", ioPro.stat.stattop.sr.bit.sr));
    }
}

void ct_im_pro4_2(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("Im_PRO_STATTOP_SW_Reset() sr (0x%08lx, %lx)\n", (kulong)&ioPro.stat.stattop.sr.word, ioPro.stat.stattop.sr.word));

        // Normal case
        priv->ercd = Im_PRO_STATTOP_SW_Reset(priv->imProStat);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("Im_PRO_STATTOP_SW_Reset() Error priv->ercd=0x%x\n", priv->ercd));
        } else {
            Ddim_Print(("Im_PRO_STATTOP_SW_Reset() result:sr(%u)\n", ioPro.stat.stattop.sr.bit.sr));
        }

        // illegal case
        Im_PRO_AF_Start(priv->imProStat, E_IM_PRO_AF_CH0);

        priv->ercd = Im_PRO_STATTOP_SW_Reset(priv->imProStat);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("Im_PRO_STATTOP_SW_Reset() Error priv->ercd=0x%x\n", priv->ercd));
        } else {
            Ddim_Print(("Im_PRO_STATTOP_SW_Reset() result:sr(%u)\n", ioPro.stat.stattop.sr.bit.sr));
        }
        Im_PRO_AF_Stop(priv->imProStat, E_IM_PRO_AF_CH0, 0);
    }
}

void ct_im_pro4_3(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
    E_IM_PRO_STATTOP_CLK_TYPE clkType;
    kuchar onOff;
    kuchar waitSkip;

    if (idx == 1) {
//        Ddim_Print(("Target register address\n"));
//        Ddim_Print(("Im_PRO_STATTOP_Control_Clock() clkstp1 (0x%08lx, %lx)\n", (kulong)&ioPro.stat.stattop.clkstp.word,   ioPro.stat.stattop.clkstp.word));

        // SENSORCLK ON
        clkType = E_IM_PRO_STATTOP_CLK_TYPE_STATCLK;
        onOff = D_IM_PRO_CLOCK_ON;
        waitSkip = 0;
        priv->ercd = Im_PRO_STATTOP_Control_Clock(priv->imProStat, clkType, onOff, waitSkip);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("Im_PRO_STATTOP_Control_Clock(%u, %u, %u) Error priv->ercd=0x%x\n",
            		clkType, onOff, waitSkip, priv->ercd));
        } else {
            Ddim_Print(("Im_PRO_STATTOP_Control_Clock(%u, %u, %u) result:clkstp1(%lu)\n",
            		clkType, onOff, waitSkip, ioPro.stat.stattop.clkstp.word));
        }

        // SENSORCLK OFF
        clkType = E_IM_PRO_STATTOP_CLK_TYPE_STATCLK;
        onOff = D_IM_PRO_CLOCK_OFF;
        waitSkip = 0;
        priv->ercd = Im_PRO_STATTOP_Control_Clock(priv->imProStat, clkType, onOff, waitSkip);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("Im_PRO_STATTOP_Control_Clock(%u, %u, %u) Error priv->ercd=0x%x\n",
            		clkType, onOff, waitSkip, priv->ercd));
        } else {
            Ddim_Print(("Im_PRO_STATTOP_Control_Clock(%u, %u, %u) result:clkstp1(%lu)\n",
            		clkType, onOff, waitSkip, ioPro.stat.stattop.clkstp.word));
        }

        // wait skip on
        clkType = E_IM_PRO_STATTOP_CLK_TYPE_STATCLK;
        onOff = D_IM_PRO_CLOCK_ON;
        waitSkip = 1;
        priv->ercd = Im_PRO_STATTOP_Control_Clock(priv->imProStat, clkType, onOff, waitSkip);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("Im_PRO_STATTOP_Control_Clock(%u, %u, %u) Error priv->ercd=0x%x\n",
            		clkType, onOff, waitSkip, priv->ercd));
        } else {
            Ddim_Print(("Im_PRO_STATTOP_Control_Clock(%u, %u, %u) result:clkstp1(%lu)\n",
            		clkType, onOff, waitSkip, ioPro.stat.stattop.clkstp.word));
        }

        // wait skip on
        clkType = E_IM_PRO_STATTOP_CLK_TYPE_STATCLK;
        onOff = D_IM_PRO_CLOCK_OFF;
        waitSkip = 1;
        priv->ercd = Im_PRO_STATTOP_Control_Clock(priv->imProStat, clkType, onOff, waitSkip);
        if (priv->ercd != DdimUserCustom_E_OK) {
            Ddim_Print(("Im_PRO_STATTOP_Control_Clock(%u, %u, %u) Error priv->ercd=0x%x\n",
            		clkType, onOff, waitSkip, priv->ercd));
        } else {
            Ddim_Print(("Im_PRO_STATTOP_Control_Clock(%u, %u, %u) result:clkstp1(%lu)\n",
            		clkType, onOff, waitSkip, ioPro.stat.stattop.clkstp.word));
        }
    }
}

void ct_im_pro4_4(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
    T_IM_PRO_STATTOP_CTRL ctrlMax = {
        .afInputSel[0] = E_IM_PRO_STATTOP_INPUT_SEL_SEN_STAT_IF4,
        .afInputSel[1] = E_IM_PRO_STATTOP_INPUT_SEL_SEN_STAT_IF4,
        .flckInputSel[0] = E_IM_PRO_STATTOP_FLCK_INPUT_SEL_SRO2_FSHDL0,
        .flckInputSel[1] = E_IM_PRO_STATTOP_FLCK_INPUT_SEL_SRO2_FSHDL0,
        .aeawbInputSel[0] = E_IM_PRO_STATTOP_INPUT_SEL_SEN_STAT_IF4,
        .aeawbInputSel[1] = E_IM_PRO_STATTOP_INPUT_SEL_SEN_STAT_IF4,
        .aeawbInputSel[2] = E_IM_PRO_STATTOP_INPUT_SEL_SEN_STAT_IF4,
        .aeawbInputSel[3] = E_IM_PRO_STATTOP_INPUT_SEL_SEN_STAT_IF4,
        .histInputSel[0] = E_IM_PRO_STATTOP_INPUT_SEL_SEN_STAT_IF4,
        .histInputSel[1] = E_IM_PRO_STATTOP_INPUT_SEL_SEN_STAT_IF4,
        .histInputSel[2] = E_IM_PRO_STATTOP_INPUT_SEL_SEN_STAT_IF4,
        .histInputSel[3] = E_IM_PRO_STATTOP_INPUT_SEL_SEN_STAT_IF4,
    };

    T_IM_PRO_STATTOP_CTRL ctrlMin = {
        .afInputSel[0] = E_IM_PRO_STATTOP_INPUT_SEL_SRO1_PZSFTC2,
        .afInputSel[1] = E_IM_PRO_STATTOP_INPUT_SEL_SRO1_PZSFTC2,
        .flckInputSel[0] = E_IM_PRO_STATTOP_FLCK_INPUT_SEL_SRO1_PZSFTC2,
        .flckInputSel[1] = E_IM_PRO_STATTOP_FLCK_INPUT_SEL_SRO1_PZSFTC2,
        .aeawbInputSel[0] = E_IM_PRO_STATTOP_INPUT_SEL_SRO1_PZSFTC2,
        .aeawbInputSel[1] = E_IM_PRO_STATTOP_INPUT_SEL_SRO1_PZSFTC2,
        .aeawbInputSel[2] = E_IM_PRO_STATTOP_INPUT_SEL_SRO1_PZSFTC2,
        .aeawbInputSel[3] = E_IM_PRO_STATTOP_INPUT_SEL_SRO1_PZSFTC2,
        .histInputSel[0] = E_IM_PRO_STATTOP_INPUT_SEL_SRO1_PZSFTC2,
        .histInputSel[1] = E_IM_PRO_STATTOP_INPUT_SEL_SRO1_PZSFTC2,
        .histInputSel[2] = E_IM_PRO_STATTOP_INPUT_SEL_SRO1_PZSFTC2,
        .histInputSel[3] = E_IM_PRO_STATTOP_INPUT_SEL_SRO1_PZSFTC2,
    };

    if (idx == 1) {
        priv->ercd = Im_PRO_STATTOP_Ctrl(priv->imProStat, &ctrlMax);
        im_pro_4_0_print_4(priv->imPro40Print, "max_para", priv->ercd, &ctrlMax);

        priv->ercd = Im_PRO_STATTOP_Ctrl(priv->imProStat, &ctrlMin);
        im_pro_4_0_print_4(priv->imPro40Print, "min_para", priv->ercd, &ctrlMin);
    }
}

void ct_im_pro4_5(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);

    if (idx == 1) {
        for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
            priv->ercd = Im_PRO_AEAWB_Start(priv->imProStat, priv->ch);
            if (priv->ercd != DdimUserCustom_E_OK) {
                Ddim_Print(("Im_PRO_AEAWB_Start(%u) Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
            } else {
                im_pro_4_0_print_5(priv->imPro40Print, priv->ch);
            }
        }
    }
}

void ct_im_pro4_6(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
    kuchar force;

    if (idx == 1) {
        for (force = 0; force < 2 + 1; force++) {
            for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
#ifdef CO_DEBUG_ON_PC
                ioPro.stat.aeawb[priv->ch].aetrg.bit.aetrg = 3;
#endif
                priv->ercd = Im_PRO_AEAWB_Stop(priv->imProStat, priv->ch, force);
                if (priv->ercd != DdimUserCustom_E_OK) {
                    Ddim_Print(("Im_PRO_AEAWB_Stop(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
                } else {
                    im_pro_4_0_print_6(priv->imPro40Print, priv->ch, force);
                }
            }
        }
    }
}

void ct_im_pro4_7(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
    T_IM_PRO_AEAWB_CTRL aeawbCtrlMax = {
        .aeawbMode = E_IM_PRO_AEAWB_MODE_AE_AWB_LWB,
        .awbMode = E_IM_PRO_AWB_MODE_R_GR_GB_B,
        .awbWdWindowMode = E_IM_PRO_AWB_WD_WINDOW_MODE_SEPARATE,
        .awbArea.posX = 8190,
        .awbArea.posY = 16382,
        .awbArea.width = 512,
        .awbArea.lines = 256,
        .awbArea.topLines = 256,
        .awbArea.bottomLines = 256,
        .awbArea.leftWidth = 512,
        .awbArea.rightWidth = 512,
        .hBcNum = 64,
        .vBcNum = 64,
    };

    T_IM_PRO_AEAWB_CTRL aeawbCtrlMin = {
        .aeawbMode = E_IM_PRO_AEAWB_MODE_AE,
        .awbMode = E_IM_PRO_AWB_MODE_RGB_CNT,
        .awbWdWindowMode = E_IM_PRO_AWB_WD_WINDOW_MODE_SAME,
        .awbArea.posX = 0,
        .awbArea.posY = 0,
        .awbArea.width = 6,
        .awbArea.lines = 2,
        .awbArea.topLines = 2,
        .awbArea.bottomLines = 2,
        .awbArea.leftWidth = 6,
        .awbArea.rightWidth = 6,
        .hBcNum = 1,
        .vBcNum = 1,
    };

    if (idx == 1) {
        for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
            priv->ercd = Im_PRO_AEAWB_Ctrl(priv->imProStat, priv->ch, &aeawbCtrlMax);
            if (priv->ercd != DdimUserCustom_E_OK) {
                Ddim_Print(("Im_PRO_AEAWB_Ctrl(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
            } else {
                im_pro_4_0_print_7(priv->imPro40Print, "max_para", priv->ch, &aeawbCtrlMax);
            }

            priv->ercd = Im_PRO_AEAWB_Ctrl(priv->imProStat, priv->ch, &aeawbCtrlMin);
            if (priv->ercd != DdimUserCustom_E_OK) {
                Ddim_Print(("Im_PRO_AEAWB_Ctrl(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
            } else {
                im_pro_4_0_print_7(priv->imPro40Print, "min_para", priv->ch, &aeawbCtrlMin);
            }
        }
    }
}

void ct_im_pro4_8(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
	kuchar paenTrg;

	if (idx == 1) {
		for (paenTrg = 0; paenTrg < 2 + 1; paenTrg++) {
			for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
				priv->ercd = Im_PRO_AEAWB_Set_PAEN(priv->imProStat, priv->ch, paenTrg);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(("Im_PRO_AEAWB_Set_PAEN(%u) Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
				} else {
					im_pro_4_0_print_8(priv->imPro40Print, priv->ch, paenTrg);
				}
			}
		}
	}
}

void ct_im_pro4_9(CtImPro4* self, const kuint32 idx)
{
}

void ct_im_pro4_10(CtImPro4* self, const kuint32 idx)
{
}

void ct_im_pro4_11(CtImPro4* self, const kuint32 idx)
{
}

void ct_im_pro4_12(CtImPro4* self, const kuint32 idx)
{
}

void ct_im_pro4_13(CtImPro4* self, const kuint32 idx)
{
}

void ct_im_pro4_14(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
	T_IM_PRO_AEAWB_CW aeawbCtrlMax = {
		.aecvw = 510,
		.aechw = 1022,
		.aectw = 510,
		.aecbw = 510,
		.aeclw = 1022,
		.aecrw = 1022,
		.awcvw = 510,
		.awchw = 1022,
		.awctw = 510,
		.awcbw = 510,
		.awclw = 1022,
		.awcrw = 1022,
	};

	T_IM_PRO_AEAWB_CW aeawbCtrlMin = {
		.aecvw = 2,
		.aechw = 2,
		.aectw = 2,
		.aecbw = 2,
		.aeclw = 2,
		.aecrw = 2,
		.awcvw = 2,
		.awchw = 2,
		.awctw = 2,
		.awcbw = 2,
		.awclw = 2,
		.awcrw = 2,
	};

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_AEAWB_Set_CW(priv->imProStat, priv->ch, &aeawbCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_AEAWB_Set_CW(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_4(priv->imPro41Print, "max_para", priv->ch, &aeawbCtrlMax);
			}

			priv->ercd = Im_PRO_AEAWB_Set_CW(priv->imProStat, priv->ch, &aeawbCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_AEAWB_Set_CW(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_4(priv->imPro41Print, "min_para", priv->ch, &aeawbCtrlMin);
			}
		}
	}
}

void ct_im_pro4_15(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
    T_IM_PRO_AEAWB_LV_GATE  aeawbCtrlMax = {
        .awtduy = 255,
        .awtdur = 255,
        .awtdug = 255,
        .awtdub = 255,
        .awtdly = 255,
        .awtdlr = 255,
        .awtdlg = 255,
        .awtdlb = 255,
    };

    T_IM_PRO_AEAWB_LV_GATE  aeawbCtrlMin = {
        .awtduy = 0,
        .awtdur = 0,
        .awtdug = 0,
        .awtdub = 0,
        .awtdly = 0,
        .awtdlr = 0,
        .awtdlg = 0,
        .awtdlb = 0,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_AEAWB_Set_Lv_Gate(priv->imProStat, priv->ch, &aeawbCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_AEAWB_Set_Lv_Gate(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_5(priv->imPro41Print, "max_para", priv->ch, &aeawbCtrlMax);
			}

			priv->ercd = Im_PRO_AEAWB_Set_Lv_Gate(priv->imProStat, priv->ch, &aeawbCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_AEAWB_Set_Lv_Gate(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_5(priv->imPro41Print, "min_para", priv->ch, &aeawbCtrlMin);
			}
        }
    }
}

void ct_im_pro4_16(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
    T_IM_PRO_AEAWB_MATRIX_LV_GATE   aeawbCtrlMax = {
        .awmlucy = 255,
        .awmllcy = 255,
        .awmlucb = 255,
        .awmllcb = 255,
        .awmlucr = 255,
        .awmllcr = 255,
        .awmc[0][0] = 255,
        .awmc[0][1] = 255,
        .awmc[0][2] = 255,
        .awmc[1][0] = 255,
        .awmc[1][1] = 255,
        .awmc[1][2] = 255,
        .awmc[2][0] = 255,
        .awmc[2][1] = 255,
        .awmc[2][2] = 255,
    };

    T_IM_PRO_AEAWB_MATRIX_LV_GATE   aeawbCtrlMin = {
        .awmlucy = 0,
        .awmllcy = 0,
        .awmlucb = 0,
        .awmllcb = 0,
        .awmlucr = 0,
        .awmllcr = 0,
        .awmc[0][0] = -256,
        .awmc[0][1] = -256,
        .awmc[0][2] = -256,
        .awmc[1][0] = -256,
        .awmc[1][1] = -256,
        .awmc[1][2] = -256,
        .awmc[2][0] = -256,
        .awmc[2][1] = -256,
        .awmc[2][2] = -256,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_AEAWB_Set_Matrix_Lv_Gate(priv->imProStat, priv->ch, &aeawbCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) max_para Error priv->ercd=0x%x\n",
						priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_6(priv->imPro41Print, "max_para", priv->ch, &aeawbCtrlMax);
			}

			priv->ercd = Im_PRO_AEAWB_Set_Matrix_Lv_Gate(priv->imProStat, priv->ch, &aeawbCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) min_para Error priv->ercd=0x%x\n",
						priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_6(priv->imPro41Print, "min_para", priv->ch, &aeawbCtrlMin);
			}
        }
    }
}

void ct_im_pro4_17(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
	T_IM_PRO_STAT_YK aeawbCtrlMax = {
        .ykr = 255,
        .ykgr = 255,
        .ykgb = 255,
        .ykb = 255,
    };

	T_IM_PRO_STAT_YK aeawbCtrlMin = {
        .ykr = -256,
        .ykgr = -256,
        .ykgb = -256,
        .ykb = -256,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_AEAWB_Set_AEYK(priv->imProStat, priv->ch, &aeawbCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_AEAWB_Set_AEYK(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_7(priv->imPro41Print, "max_para", priv->ch, &aeawbCtrlMax);
			}

			priv->ercd = Im_PRO_AEAWB_Set_AEYK(priv->imProStat, priv->ch, &aeawbCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_AEAWB_Set_AEYK(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_7(priv->imPro41Print, "min_para", priv->ch, &aeawbCtrlMin);
			}
        }
    }
}

void ct_im_pro4_18(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
    T_IM_PRO_STAT_YK    aeyk;

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
#ifdef CO_DEBUG_ON_PC
			im_pro_set_reg_signed(ioPro.stat.aeawb[priv->ch].aeykrr, union io_aeykrr, aeykrr, 0x0FF);
			im_pro_set_reg_signed(ioPro.stat.aeawb[priv->ch].aeykgr, union io_aeykgr, aeykgr, 0x0FF);
			im_pro_set_reg_signed(ioPro.stat.aeawb[priv->ch].aeykgb, union io_aeykgb, aeykgb, 0x0FF);
			im_pro_set_reg_signed(ioPro.stat.aeawb[priv->ch].aeykbb, union io_aeykbb, aeykbb, 0x0FF);
#endif  // CO_DEBUG_ON_PC
			priv->ercd = Im_PRO_AEAWB_Get_AEYK(priv->imProStat, priv->ch, &aeyk);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_AEAWB_Get_AEYK(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_8(priv->imPro41Print, "max_para", priv->ch, &aeyk);
			}

#ifdef CO_DEBUG_ON_PC
			im_pro_set_reg_signed(ioPro.stat.aeawb[priv->ch].aeykrr, union io_aeykrr, aeykrr, 0x100);
			im_pro_set_reg_signed(ioPro.stat.aeawb[priv->ch].aeykgr, union io_aeykgr, aeykgr, 0x100);
			im_pro_set_reg_signed(ioPro.stat.aeawb[priv->ch].aeykgb, union io_aeykgb, aeykgb, 0x100);
			im_pro_set_reg_signed(ioPro.stat.aeawb[priv->ch].aeykbb, union io_aeykbb, aeykbb, 0x100);
#endif  // CO_DEBUG_ON_PC
			priv->ercd = Im_PRO_AEAWB_Get_AEYK(priv->imProStat, priv->ch, &aeyk);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_AEAWB_Get_AEYK(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_8(priv->imPro41Print, "min_para", priv->ch, &aeyk);
			}
        }
    }
}

void ct_im_pro4_19(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
	T_IM_PRO_AEAWB_LINE_INFO aeawbCtrlMax = {
        .startLine[0] = 32766,
        .startLine[1] = 32766,
        .startLine[2] = 32766,
        .startLine[3] = 32766,
    };

	T_IM_PRO_AEAWB_LINE_INFO aeawbCtrlMin = {
        .startLine[0] = 0,
        .startLine[1] = 0,
        .startLine[2] = 0,
        .startLine[3] = 0,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_AEAWB_Set_Line_Data_Position(priv->imProStat, priv->ch, &aeawbCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_AEAWB_Set_Line_Data_Position(%u) max_para Error priv->ercd=0x%x\n",
						priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_9(priv->imPro41Print, "max_para", priv->ch, &aeawbCtrlMax);
			}

			priv->ercd = Im_PRO_AEAWB_Set_Line_Data_Position(priv->imProStat, priv->ch, &aeawbCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_AEAWB_Set_Line_Data_Position(%u) min_para Error priv->ercd=0x%x\n",
						priv->ch, priv->ercd));
			} else {
				im_pro_4_1_print_9(priv->imPro41Print, "min_para", priv->ch, &aeawbCtrlMin);
			}
        }
    }
}

void ct_im_pro4_20(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
	kulong lineData[4];

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
#ifdef CO_DEBUG_ON_PC
			ioPro.stat.aeawb[priv->ch].linev.linev1.bit.LINEV_0 = 32766;
			ioPro.stat.aeawb[priv->ch].linev.linev1.bit.LINEV_1 = 32766;
			ioPro.stat.aeawb[priv->ch].linev.linev2.bit.LINEV_2 = 32766;
			ioPro.stat.aeawb[priv->ch].linev.linev2.bit.LINEV_3 = 32766;
#endif  // CO_DEBUG_ON_PC
			priv->ercd = Im_PRO_AEAWB_Get_Line_Data(priv->imProStat, priv->ch, lineData);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_AEAWB_Get_Line_Data(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_2_print_0(priv->imPro42Print, "max_para", priv->ch, lineData);
			}

#ifdef CO_DEBUG_ON_PC
			ioPro.stat.aeawb[priv->ch].linev.linev1.bit.LINEV_0 = 0;
			ioPro.stat.aeawb[priv->ch].linev.linev1.bit.LINEV_1 = 0;
			ioPro.stat.aeawb[priv->ch].linev.linev2.bit.LINEV_2 = 0;
			ioPro.stat.aeawb[priv->ch].linev.linev2.bit.LINEV_3 = 0;
#endif  // CO_DEBUG_ON_PC
			priv->ercd = Im_PRO_AEAWB_Get_Line_Data(priv->imProStat, priv->ch, lineData);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_AEAWB_Get_Line_Data(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_2_print_0(priv->imPro42Print, "min_para", priv->ch, lineData);
			}
        }
    }
}

void ct_im_pro4_21(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
	kulong dataAddress;

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
			dataAddress = Im_PRO_AEAWB_Get_AEAWBData(priv->imProStat, priv->ch);
			if (dataAddress == 0) {
				Ddim_Print(("Im_PRO_AEAWB_Get_AEAWBData(%u) max_para Error \n", priv->ch));
			} else {
				im_pro_4_2_print_1(priv->imPro42Print, "", priv->ch, &dataAddress);
			}
        }
    }
}

void ct_im_pro4_22(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
	kulong dataAddress;

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
			dataAddress = Im_PRO_AEAWB_Get_LastAEAWBData(priv->imProStat, priv->ch);
			if (dataAddress == 0) {
				Ddim_Print(("Im_PRO_AEAWB_Get_LastAEAWBData(%u) max_para Error\n", priv->ch));
			} else {
				im_pro_4_2_print_2(priv->imPro42Print, "", priv->ch, &dataAddress);
			}
		}
    }
}

void ct_im_pro4_23(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
	T_IM_PRO_AEAWB_WD_INFO wdInfo;
	kuchar mode;
	kuchar type;
	kuchar blockCount = 0;

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AEAWB_CH0; priv->ch < E_IM_PRO_AEAWB_CH3 + 1; priv->ch++) {
			for (mode = E_IM_PRO_AEAWB_MODE_AE; mode < E_IM_PRO_AEAWB_MODE_AE_AWB_LWB + 1; mode++) {
				for (type = E_IM_PRO_AEAWB_TYPE_AE; type < E_IM_PRO_AEAWB_TYPE_LAWB + 1; type++) {
					wdInfo.mode = mode;
					wdInfo.type = type;
					wdInfo.aehbc = 64;

					priv->ercd = Im_PRO_AEAWB_Get_WD_Info(priv->imProStat, priv->ch, &wdInfo);
					if (priv->ercd != DdimUserCustom_E_OK) {
						Ddim_Print(
								("Im_PRO_AEAWB_Get_WD_Info(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
					} else {
						im_pro_4_2_print_3(priv->imPro42Print, "max_para", priv->ch, &wdInfo);
					}

					wdInfo.aehbc = blockCount;
					blockCount++;
					priv->ercd = Im_PRO_AEAWB_Get_WD_Info(priv->imProStat, priv->ch, &wdInfo);
					if (priv->ercd != DdimUserCustom_E_OK) {
						Ddim_Print(
								("Im_PRO_AEAWB_Get_WD_Info(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
					} else {
						im_pro_4_2_print_3(priv->imPro42Print, "min_para", priv->ch, &wdInfo);
					}
                }
            }
        }
    }
}

void ct_im_pro4_24(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			Im_PRO_AF_Start(priv->imProStat, priv->ch);
			im_pro_4_2_print_4(priv->imPro42Print, priv->ch);
		}
    }
}

void ct_im_pro4_25(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
	kuchar force;

	if (idx == 1) {
		for (force = 0; force < 2 + 1; force++) {
			for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
#ifdef CO_DEBUG_ON_PC
				ioPro.stat.aeawb[priv->ch].aetrg.bit.aetrg = 3;
#endif
				Im_PRO_AF_Stop(priv->imProStat, priv->ch, force);
				im_pro_4_2_print_5(priv->imPro42Print, priv->ch, force);
			}
        }
    }
}

void ct_im_pro4_26(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
	T_IM_PRO_AF_CTRL afCtrlMax = {
        .evalCalc0Enable = E_IM_PRO_AF_ENABLE_EN,
        .evalCalc1Enable = E_IM_PRO_AF_ENABLE_EN,
        .evalCalc2Enable = E_IM_PRO_AF_ENABLE_EN,
        .verticalEnable = E_IM_PRO_AF_ENABLE_EN,
        .horizon0Enable = E_IM_PRO_AF_ENABLE_EN,
        .horizon1Enable = E_IM_PRO_AF_ENABLE_EN,
        .horizon2Enable = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_0] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_1] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_2] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_3] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_4] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_5] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_6] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_7] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_8] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_9] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_10] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_11] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_12] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_13] = E_IM_PRO_AF_ENABLE_EN,
        .enable[E_IM_PRO_AF_WINDOW_14] = E_IM_PRO_AF_ENABLE_EN,
    };

    T_IM_PRO_AF_CTRL afCtrlMin = {
        .evalCalc0Enable = E_IM_PRO_AF_ENABLE_DIS,
        .evalCalc1Enable = E_IM_PRO_AF_ENABLE_DIS,
        .evalCalc2Enable = E_IM_PRO_AF_ENABLE_DIS,
        .verticalEnable = E_IM_PRO_AF_ENABLE_DIS,
        .horizon0Enable = E_IM_PRO_AF_ENABLE_DIS,
        .horizon1Enable = E_IM_PRO_AF_ENABLE_DIS,
        .horizon2Enable = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_0] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_1] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_2] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_3] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_4] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_5] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_6] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_7] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_8] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_9] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_10] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_11] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_12] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_13] = E_IM_PRO_AF_ENABLE_DIS,
        .enable[E_IM_PRO_AF_WINDOW_14] = E_IM_PRO_AF_ENABLE_DIS,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_AF_Ctrl(priv->imProStat, priv->ch, &afCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_AF_Ctrl(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_2_print_6(priv->imPro42Print, "max_para", priv->ch, &afCtrlMax);
			}

			priv->ercd = Im_PRO_AF_Ctrl(priv->imProStat, priv->ch, &afCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_AF_Ctrl(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_2_print_6(priv->imPro42Print, "min_para", priv->ch, &afCtrlMin);
			}
        }
    }
}

void ct_im_pro4_27(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
    kuchar paenTrg;

	if (idx == 1) {
		for (paenTrg = 0; paenTrg < 2 + 1; paenTrg++) {
			for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
				priv->ercd = Im_PRO_AF_Set_PAEN(priv->imProStat, priv->ch, paenTrg);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(("Im_PRO_AF_Set_PAEN(%u) Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
				} else {
					im_pro_4_2_print_7(priv->imPro42Print, priv->ch, paenTrg);
				}
            }
        }
    }
}

void ct_im_pro4_28(CtImPro4* self, const kuint32 idx)
{
	CtImPro4Private *priv = CT_IM_PRO_4_GET_PRIVATE(self);
    T_IM_PRO_AREA_INFO globalWinMax = {
        .posX = D_IM_PRO_AF_AFGH_MAX,
        .posY = D_IM_PRO_AF_AFGV_MAX,
        .width = D_IM_PRO_AF_AFGHW_MAX,
        .lines = D_IM_PRO_AF_AFGVW_MAX,
    };

    T_IM_PRO_AREA_INFO globalWinMin = {
        .posX = D_IM_PRO_AF_AFGH_MIN,
        .posY = D_IM_PRO_AF_AFGV_MIN,
        .width = D_IM_PRO_AF_AFGHW_MIN,
        .lines = D_IM_PRO_AF_AFGVW_MIN,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_AF_Set_Global_Area(priv->imProStat, priv->ch, &globalWinMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_AF_Set_Global_Area(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_2_print_8(priv->imPro42Print, "max_para", priv->ch, &globalWinMax);
			}

			priv->ercd = Im_PRO_AF_Set_Global_Area(priv->imProStat, priv->ch, &globalWinMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_AF_Set_Global_Area(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_2_print_8(priv->imPro42Print, "min_para", priv->ch, &globalWinMin);
			}
        }
    }
}

#endif //CO_CT_IM_PRO_DISABLE

CtImPro4* ct_im_pro_4_new(void)
{
	CtImPro4* self = k_object_new_with_private(CT_TYPE_IM_PRO4, sizeof(CtImPro4Private));

	return self;
}

