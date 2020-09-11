/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈元
*@brief : CtImPro4Last
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "improstat.h"
#include "ctimpro4last.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro4Last, ct_im_pro4_last)
#define CT_IM_PRO4_LAST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro4LastPrivate, CT_TYPE_IM_PRO4_LAST))


struct _CtImPro4LastPrivate
{
	ImProStat *imProStat;
	ImPro45Print *imPro45Print;
	ImPro46Print *imPro46Print;
	ImPro47Print *imPro47Print;
	ImPro48Print *imPro48Print;
	kulong calcData;
	kuchar ch;
	E_IM_PRO_AF_WINDOW_NO winNo;
	kint32 ercd;
	T_IM_PRO_HIST_DATA histCtrl;
	kuchar force;
	kulong flckCtrl;
};


/**********
 * IMPL
 */
static void ct_im_pro4_last_constructor(CtImPro4Last *self)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);

	priv->imProStat = im_pro_stat_new();
	priv->imPro45Print = im_pro_4_5_print_new();
	priv->imPro46Print = im_pro_4_6_print_new();
	priv->imPro47Print = im_pro_4_7_print_new();
	priv->imPro48Print = im_pro_4_8_print_new();
//	TODO 还没初始化属性
}

static void ct_im_pro4_last_destructor(CtImPro4Last *self)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);

	if (priv->imProStat) {
		k_object_unref(priv->imProStat);
		priv->imProStat = NULL;
	}

	if (priv->imPro45Print) {
		k_object_unref(priv->imPro45Print);
		priv->imPro45Print = NULL;
	}

	if (priv->imPro46Print) {
		k_object_unref(priv->imPro46Print);
		priv->imPro46Print = NULL;
	}

	if (priv->imPro47Print) {
		k_object_unref(priv->imPro47Print);
		priv->imPro47Print = NULL;
	}

	if (priv->imPro48Print) {
		k_object_unref(priv->imPro48Print);
		priv->imPro48Print = NULL;
	}
}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro4_last_58(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX; priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal0_Line_Accum_Max_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal0_Line_Accum_Max_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_5_print_8(priv->imPro45Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_last_59(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX; priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal1_Line_Accum_Max_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal1_Line_Accum_Max_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_5_print_9(priv->imPro45Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_last_60(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_AF_CH0; priv->ch < E_IM_PRO_AF_CH1 + 1; priv->ch++) {
			for (priv->winNo = E_IM_PRO_AF_WINDOW_0; priv->winNo < E_IM_PRO_AF_WINDOW_MAX; priv->winNo++) {
				priv->calcData = Im_PRO_AF_Get_Horizontal2_Line_Accum_Max_LastData(priv->imProStat, priv->ch, priv->winNo);
				if (priv->calcData != 0) {
					Ddim_Print(
							("Im_PRO_AF_Get_Horizontal2_Line_Accum_Max_LastData(%u %u) max_para Error priv->ercd=0x%lx\n",
									priv->ch, priv->winNo, (kulong)&priv->calcData));
				} else {
					im_pro_4_6_print_0(priv->imPro46Print, "max_para", priv->ch, priv->winNo, &priv->calcData);
				}
            }
        }
    }
}

void ct_im_pro4_last_61(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_HIST_CH0; priv->ch < E_IM_PRO_HIST_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_HIST_Start(priv->imProStat, priv->ch);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_HIST_Start(%u) Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_1(priv->imPro46Print, priv->ch);
			}
        }
    }
}

void ct_im_pro4_last_62(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->force = 0; priv->force < 2 + 1; priv->force++) {
			for (priv->ch = E_IM_PRO_HIST_CH0; priv->ch < E_IM_PRO_HIST_CH3 + 1; priv->ch++) {
#ifdef CO_DEBUG_ON_PC
				ioPro.stat.hist[priv->ch].histtrg.bit.histtrg = 3;
#endif
				priv->ercd = Im_PRO_HIST_Stop(priv->imProStat, priv->ch, priv->force);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_HIST_Stop(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
				} else {
					im_pro_4_6_print_2(priv->imPro46Print, priv->ch, priv->force);
				}
            }
        }
    }
}

void ct_im_pro4_last_63(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    T_IM_PRO_HIST_CTRL histCtrlMax = {
        .histMode = E_IM_PRO_HIST_MODE_CONTINUOUS,
        .histCycle = E_IM_PRO_HIST_CYCLE_8PIXEL_SUBSAMPLING,
        .histShiftVal = E_IM_PRO_HIST_SHIFT_VAL_4BIT_RIGHT,
    };

    T_IM_PRO_HIST_CTRL histCtrlMin = {
        .histMode = E_IM_PRO_HIST_MODE_1_FRAME_DETECT,
        .histCycle = E_IM_PRO_HIST_CYCLE_NORMAL,
        .histShiftVal = E_IM_PRO_HIST_SHIFT_VAL_NO_SHIFT,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_HIST_CH0; priv->ch < E_IM_PRO_HIST_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_HIST_Ctrl(priv->imProStat, priv->ch, &histCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_HIST_Ctrl(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_3(priv->imPro46Print, "max_para", priv->ch, &histCtrlMax);
			}

			priv->ercd = Im_PRO_HIST_Ctrl(priv->imProStat, priv->ch, &histCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_HIST_Ctrl(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_3(priv->imPro46Print, "min_para", priv->ch, &histCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_64(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    kuchar paenTrg;

	if (idx == 1) {
		for (paenTrg = 0; paenTrg < 2 + 1; paenTrg++) {
			for (priv->ch = E_IM_PRO_HIST_CH0; priv->ch < E_IM_PRO_HIST_CH1 + 1; priv->ch++) {
				priv->ercd = Im_PRO_HIST_Set_PAEN(priv->imProStat, priv->ch, paenTrg);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(("Im_PRO_HIST_Set_PAEN(%u) Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
				} else {
					im_pro_4_6_print_4(priv->imPro46Print, priv->ch, paenTrg);
				}
            }
        }
    }
}

void ct_im_pro4_last_65(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    E_IM_PRO_HIST_CYCLE histCycleMax = E_IM_PRO_HIST_CYCLE_8PIXEL_SUBSAMPLING;
    E_IM_PRO_HIST_CYCLE histCycleMin = E_IM_PRO_HIST_CYCLE_NORMAL;

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_HIST_CH0; priv->ch < E_IM_PRO_HIST_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_HIST_Set_H_Cycle(priv->imProStat, priv->ch, histCycleMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_HIST_Set_H_Cycle(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_5(priv->imPro46Print, "max_para", priv->ch, histCycleMax);
			}

			priv->ercd = Im_PRO_HIST_Set_H_Cycle(priv->imProStat, priv->ch, histCycleMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_HIST_Set_H_Cycle(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_5(priv->imPro46Print, "min_para", priv->ch, histCycleMin);
			}
        }
    }
}

void ct_im_pro4_last_66(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    T_IM_PRO_HIST_AREA histCtrlMax = {
        .posX = 16382,
        .posY = 16382,
        .width = 16382,
        .lines = 12288,
    };

    T_IM_PRO_HIST_AREA histCtrlMin = {
        .posX = 0,
        .posY = 0,
        .width = 2,
        .lines = 2,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_HIST_CH0; priv->ch < E_IM_PRO_HIST_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_HIST_Set_Area(priv->imProStat, priv->ch, &histCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_HIST_Set_Area(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_6(priv->imPro46Print, "max_para", priv->ch, &histCtrlMax);
			}

			priv->ercd = Im_PRO_HIST_Set_Area(priv->imProStat, priv->ch, &histCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_HIST_Set_Area(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_6(priv->imPro46Print, "min_para", priv->ch, &histCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_67(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    T_IM_PRO_HIST_GAIN histCtrlMax = {
        .rGain = 1023,
        .gGain = 1023,
        .bGain = 1023,
    };

    T_IM_PRO_HIST_GAIN histCtrlMin = {
        .rGain = 0,
        .gGain = 0,
        .bGain = 0,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_HIST_CH0; priv->ch < E_IM_PRO_HIST_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_HIST_Set_Gain(priv->imProStat, priv->ch, &histCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_HIST_Set_Gain(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_7(priv->imPro46Print, "max_para", priv->ch, &histCtrlMax);
			}

			priv->ercd = Im_PRO_HIST_Set_Gain(priv->imProStat, priv->ch, &histCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_HIST_Set_Gain(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_7(priv->imPro46Print, "min_para", priv->ch, &histCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_68(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    T_IM_PRO_STAT_YK histCtrlMax = {
        .ykr = 255,
        .ykgr = 255,
        .ykgb = 255,
        .ykb = 255,
    };

    T_IM_PRO_STAT_YK histCtrlMin = {
        .ykr = -256,
        .ykgr = -256,
        .ykgb = -256,
        .ykb = -256,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_HIST_CH0; priv->ch < E_IM_PRO_HIST_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_HIST_Set_HISTYK(priv->imProStat, priv->ch, &histCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_HIST_Set_HISTYK(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_8(priv->imPro46Print, "max_para", priv->ch, &histCtrlMax);
			}

			priv->ercd = Im_PRO_HIST_Set_HISTYK(priv->imProStat, priv->ch, &histCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_HIST_Set_HISTYK(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_8(priv->imPro46Print, "min_para", priv->ch, &histCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_69(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
	kint32 loopCnt = 0;

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_HIST_CH0; priv->ch < D_IM_PRO_STAT_HIST_CH_NUM; priv->ch++) {
			priv->ercd = Im_PRO_HIST_Get_HIST_Data(priv->imProStat, priv->ch, &priv->histCtrl);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_HIST_Get_HIST_Data(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_6_print_9(priv->imPro46Print, "max_para", priv->ch, &priv->histCtrl);
			}
			loopCnt++;
        }
    }
}

void ct_im_pro4_last_70(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    kint32 loopCnt = 0;


    if (idx == 1) {
		for (priv->ch = E_IM_PRO_HIST_CH0; priv->ch < E_IM_PRO_HIST_CH3 + 1; priv->ch++) {
			priv->ercd = Im_PRO_HIST_Get_HIST_Ram(priv->imProStat, priv->ch, &priv->histCtrl);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_HIST_Get_HIST_Ram(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_0(priv->imPro47Print, "max_para", priv->ch, &priv->histCtrl);
			}
			loopCnt++;
		}
    }
}

void ct_im_pro4_last_71(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_FLCK_Start(priv->imProStat, priv->ch);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_FLCK_Start(%u) Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_1(priv->imPro47Print, priv->ch);
			}
        }
    }
}

void ct_im_pro4_last_72(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->force = 0; priv->force < 2 + 1; priv->force++) {
			for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
#ifdef CO_DEBUG_ON_PC
				ioPro.stat.flck[priv->ch].fltrg.bit.fltrg = 3;
#endif
				priv->ercd = Im_PRO_FLCK_Stop(priv->imProStat, priv->ch, priv->force);
				if (priv->ercd != DdimUserCustom_E_OK) {
					Ddim_Print(
							("Im_PRO_FLCK_Stop(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
				} else {
					im_pro_4_7_print_2(priv->imPro47Print, priv->ch, priv->force);
				}
            }
        }
    }
}

void ct_im_pro4_last_73(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    T_IM_PRO_FLCK_CTRL flckCtrlMax = {
        .flckType = E_IM_PRO_FLCK_TYPE_YG,
        .flckMode = E_IM_PRO_FLCK_MODE_LINE,
        .flcvw = 1024,
        .bcNum = 4096,
    };

    T_IM_PRO_FLCK_CTRL flckCtrlMin = {
        .flckType = E_IM_PRO_FLCK_TYPE_RGB,
        .flckMode = E_IM_PRO_FLCK_MODE_NORMAL,
        .flcvw = 2,
        .bcNum = 1,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_FLCK_Ctrl(priv->imProStat, priv->ch, &flckCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_FLCK_Ctrl(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_3(priv->imPro47Print, "max_para", priv->ch, &flckCtrlMax);
			}

			priv->ercd = Im_PRO_FLCK_Ctrl(priv->imProStat, priv->ch, &flckCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_FLCK_Ctrl(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_3(priv->imPro47Print, "min_para", priv->ch, &flckCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_74(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    E_IM_PRO_FLCK_TYPE  flckCtrlMax = E_IM_PRO_FLCK_TYPE_YG;
    E_IM_PRO_FLCK_TYPE  flckCtrlMin = E_IM_PRO_FLCK_TYPE_RGB;

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_FLCK_Set_FLCKDataFormat(priv->imProStat, priv->ch, flckCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_FLCKDataFormat(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_4(priv->imPro47Print, "max_para", priv->ch, flckCtrlMax);
			}

			priv->ercd = Im_PRO_FLCK_Set_FLCKDataFormat(priv->imProStat, priv->ch, flckCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_FLCKDataFormat(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_4(priv->imPro47Print, "min_para", priv->ch, flckCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_75(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    E_IM_PRO_FLCK_MODE  flckCtrlMax = E_IM_PRO_FLCK_MODE_LINE;
    E_IM_PRO_FLCK_MODE  flckCtrlMin = E_IM_PRO_FLCK_MODE_NORMAL;

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_FLCK_Set_WD_Mode(priv->imProStat, priv->ch, flckCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_WD_Mode(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_5(priv->imPro47Print, "max_para", priv->ch, flckCtrlMax);
			}

			priv->ercd = Im_PRO_FLCK_Set_WD_Mode(priv->imProStat, priv->ch, flckCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_WD_Mode(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_5(priv->imPro47Print, "min_para", priv->ch, flckCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_76(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    T_IM_PRO_FLCK_AREA flckCtrlMax = {
        .posX = 8190,
        .posY = 16382,
        .width = 8192,
        .lines = 1024,
    };
    T_IM_PRO_FLCK_AREA  flckCtrlMin = {
        .posX = 0,
        .posY = 0,
        .width = 6,
        .lines = 2,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_FLCK_Set_Area(priv->imProStat, priv->ch, &flckCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_Area(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_6(priv->imPro47Print, "max_para", priv->ch, &flckCtrlMax);
			}

			priv->ercd = Im_PRO_FLCK_Set_Area(priv->imProStat, priv->ch, &flckCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_Area(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_6(priv->imPro47Print, "min_para", priv->ch, &flckCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_77(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    kuint16 flckCtrlMax = 4096;
    kuint16 flckCtrlMin = 1;

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_FLCK_Set_Blocks(priv->imProStat, priv->ch, flckCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_Blocks(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_7(priv->imPro47Print, "max_para", priv->ch, flckCtrlMax);
			}

			priv->ercd = Im_PRO_FLCK_Set_Blocks(priv->imProStat, priv->ch, flckCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_Blocks(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_7(priv->imPro47Print, "min_para", priv->ch, flckCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_78(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    kuint16 flckCtrlMax = 1024;
    kuint16 flckCtrlMin = 2;

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_FLCK_Set_CW(priv->imProStat, priv->ch, flckCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_FLCK_Set_CW(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_8(priv->imPro47Print, "max_para", priv->ch, flckCtrlMax);
			}

			priv->ercd = Im_PRO_FLCK_Set_CW(priv->imProStat, priv->ch, flckCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_FLCK_Set_CW(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_8(priv->imPro47Print, "min_para", priv->ch, flckCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_79(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    T_IM_PRO_FLCK_LV_GATE flckCtrlMax = {
        .fltduy = 255,
        .fltdur = 255,
        .fltdug = 255,
        .fltdub = 255,
        .fltdly = 255,
        .fltdlr = 255,
        .fltdlg = 255,
        .fltdlb = 255,
    };
    T_IM_PRO_FLCK_LV_GATE flckCtrlMin = {
        .fltduy = 0,
        .fltdur = 0,
        .fltdug = 0,
        .fltdub = 0,
        .fltdly = 0,
        .fltdlr = 0,
        .fltdlg = 0,
        .fltdlb = 0,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_FLCK_Set_Lv_Gate(priv->imProStat, priv->ch, &flckCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_Lv_Gate(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_9(priv->imPro47Print, "max_para", priv->ch, &flckCtrlMax);
			}

			priv->ercd = Im_PRO_FLCK_Set_Lv_Gate(priv->imProStat, priv->ch, &flckCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_Lv_Gate(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_7_print_9(priv->imPro47Print, "min_para", priv->ch, &flckCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_80(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    T_IM_PRO_FLCK_MATRIX_LV_GATE flckCtrlMax = {
        .flmlucy = 255,
        .flmllcy = 255,
        .flmlucb = 255,
        .flmllcb = 255,
        .flmlucr = 255,
        .flmllcr = 255,
        .flmc[0][0] = 511,
        .flmc[0][1] = 511,
        .flmc[0][2] = 511,
        .flmc[1][0] = 511,
        .flmc[1][1] = 511,
        .flmc[1][2] = 511,
        .flmc[2][0] = 511,
        .flmc[2][1] = 511,
        .flmc[2][2] = 511,
    };
    T_IM_PRO_FLCK_MATRIX_LV_GATE flckCtrlMin = {
        .flmlucy = 0,
        .flmllcy = 0,
        .flmlucb = 0,
        .flmllcb = 0,
        .flmlucr = 0,
        .flmllcr = 0,
        .flmc[0][0] = 0,
        .flmc[0][1] = 0,
        .flmc[0][2] = 0,
        .flmc[1][0] = 0,
        .flmc[1][1] = 0,
        .flmc[1][2] = 0,
        .flmc[2][0] = 0,
        .flmc[2][1] = 0,
        .flmc[2][2] = 0,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_FLCK_Set_Matrix_Lv_Gate(priv->imProStat, priv->ch, &flckCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_8_print_0(priv->imPro48Print, "max_para", priv->ch, &flckCtrlMax);
			}

			priv->ercd = Im_PRO_FLCK_Set_Matrix_Lv_Gate(priv->imProStat, priv->ch, &flckCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_8_print_0(priv->imPro48Print, "min_para", priv->ch, &flckCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_81(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);
    T_IM_PRO_STAT_YK histCtrlMax = {
        .ykr = 255,
        .ykgr = 255,
        .ykgb = 255,
        .ykb = 255,
    };

    T_IM_PRO_STAT_YK histCtrlMin = {
        .ykr = -256,
        .ykgr = -256,
        .ykgb = -256,
        .ykb = -256,
    };

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->ercd = Im_PRO_FLCK_Set_FLYK(priv->imProStat, priv->ch, &histCtrlMax);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_FLYK(%u) max_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_8_print_1(priv->imPro48Print, "max_para", priv->ch, &histCtrlMax);
			}

			priv->ercd = Im_PRO_FLCK_Set_FLYK(priv->imProStat, priv->ch, &histCtrlMin);
			if (priv->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(
						("Im_PRO_FLCK_Set_FLYK(%u) min_para Error priv->ercd=0x%x\n", priv->ch, priv->ercd));
			} else {
				im_pro_4_8_print_1(priv->imPro48Print, "min_para", priv->ch, &histCtrlMin);
			}
        }
    }
}

void ct_im_pro4_last_82(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->flckCtrl = Im_PRO_FLCK_Get_FLCKData(priv->imProStat, priv->ch);
			if (priv->flckCtrl != 0) {
				Ddim_Print(("Im_PRO_FLCK_Get_FLCKData(%u) max_para Error \n", priv->ch));
			} else {
				im_pro_4_8_print_2(priv->imPro48Print, priv->ch, priv->flckCtrl);
			}
        }
    }
}

void ct_im_pro4_last_83(CtImPro4Last* self, const kuint32 idx)
{
	CtImPro4LastPrivate *priv = CT_IM_PRO4_LAST_GET_PRIVATE(self);

	if (idx == 1) {
		for (priv->ch = E_IM_PRO_FLCK_CH0; priv->ch < E_IM_PRO_FLCK_CH1 + 1; priv->ch++) {
			priv->flckCtrl = Im_PRO_FLCK_Get_LastFLCKData(priv->imProStat, priv->ch);
			if (priv->flckCtrl != 0) {
				Ddim_Print(("Im_PRO_FLCK_Get_LastFLCKData(%u) max_para Error\n", priv->ch));
			} else {
				im_pro_4_8_print_3(priv->imPro48Print, priv->ch, priv->flckCtrl);
			}
        }
    }
}

#endif //CO_CT_IM_PRO_DISABLE

CtImPro4Last* ct_im_pro4_last_new(void)
{
	CtImPro4Last* self = k_object_new_with_private(CT_TYPE_IM_PRO4_LAST, sizeof(CtImPro4LastPrivate));

	return self;
}

