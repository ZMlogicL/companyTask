/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro46Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro46print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro46Print, impro_4_6_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_4_6_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro46PrintPrivate, IMPRO_TYPE_4_6_PRINT))


struct _Impro46PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_4_6_print_constructor(Impro46Print *self)
{
	Impro46PrintPrivate *priv = IMPRO_4_6_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_4_6_print_destructor(Impro46Print *self)
{
	Impro46PrintPrivate *priv = IMPRO_4_6_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_4_6_print_0(Impro46Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal2_Line_Accum_Max_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_6_print_1(Impro46Print *self,E_IM_PRO_HIST_CH ch)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Start(%u) result:histtrg  0x%08lx(%u)\n", 
        ch, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histtrg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histtrg.bit.histtrg));
}

void im_pro_4_6_print_2(Impro46Print *self,E_IM_PRO_HIST_CH ch, kuchar force)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Stop(%u %u) result:histtrg    0x%08lx(%u)\n", 
        ch, force, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histtrg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histtrg.bit.histtrg));
}

void im_pro_4_6_print_3(Impro46Print *self,const char *string, E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_CTRL *histCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.bit.histct != histCtrl->histMode)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Ctrl(%u) %s result:histct     0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.bit.histct, histCtrl->histMode));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.bit.histhcyc != histCtrl->histCycle)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Ctrl(%u) %s result:histhcyc   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.bit.histhcyc, histCtrl->histCycle));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.bit.histsums != histCtrl->histShiftVal)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Ctrl(%u) %s result:histsums   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.bit.histsums, histCtrl->histShiftVal));
    }
}

void im_pro_4_6_print_4(Impro46Print *self,E_IM_PRO_AF_CH ch, kuchar paenTrg)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_PAEN(%u %u) result:paen  0x%08lx(%u)\n", 
        ch, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histpaen.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histpaen.bit.paen));
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_PAEN(%u %u) result:aetrg 0x%08lx(%u)\n", 
        ch, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histtrg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histtrg.bit.histtrg));
}

void im_pro_4_6_print_5(Impro46Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_HIST_CYCLE histCycle)
{
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.bit.histhcyc != histCycle)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_H_Cycle(%u) %s result:histhcyc    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histctl.bit.histhcyc, histCycle));
    }
}

void im_pro_4_6_print_6(Impro46Print *self,const char *string, E_IM_PRO_AF_CH ch, T_IM_PRO_HIST_AREA *histCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histh.bit.histh != histCtrl->posX)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_Area(%u) %s result:histh  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histh.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histh.bit.histh, histCtrl->posX));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histv.bit.histv != histCtrl->posY)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_Area(%u) %s result:histv  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histv.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histv.bit.histv, histCtrl->posY));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histhw.bit.histhw != histCtrl->width)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_Area(%u) %s result:histhw 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histhw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histhw.bit.histhw, histCtrl->width));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histvw.bit.histvw != histCtrl->lines)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_Area(%u) %s result:histvw 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histvw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histvw.bit.histvw, histCtrl->lines));
    }
}

void im_pro_4_6_print_7(Impro46Print *self,const char *string, E_IM_PRO_AF_CH ch, T_IM_PRO_HIST_GAIN *histCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histwbgr.bit.histwbgr != histCtrl->rGain)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_Gain(%u) %s result:HHISTWBGR  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histwbgr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histwbgr.bit.histwbgr, histCtrl->rGain));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histwbgg.bit.histwbgg != histCtrl->gGain)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_Gain(%u) %s result:HHISTWBGG  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histwbgg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histwbgg.bit.histwbgg, histCtrl->gGain));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histwbgb.bit.histwbgb != histCtrl->bGain)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_Gain(%u) %s result:HHISTWBGB  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histwbgb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histwbgb.bit.histwbgb, histCtrl->bGain));
    }
}

void im_pro_4_6_print_8(Impro46Print *self,const char *string, E_IM_PRO_AF_CH ch, T_IM_PRO_STAT_YK *histCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykrr.bit.histykrr != histCtrl->ykr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_HISTYK(%u) %s result:HHISTWBGR    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykrr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykrr.bit.histykrr, histCtrl->ykr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykgr.bit.histykgr != histCtrl->ykgr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_HISTYK(%u) %s result:HHISTWBGG    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykgr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykgr.bit.histykgr, histCtrl->ykgr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykgb.bit.histykgb != histCtrl->ykgb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_HISTYK(%u) %s result:HHISTWBGB    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykgb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykgb.bit.histykgb, histCtrl->ykgb));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykbb.bit.histykbb != histCtrl->ykb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Set_HISTYK(%u) %s result:HHISTWBGB    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykbb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histykbb.bit.histykbb, histCtrl->ykb));
    }
}

void im_pro_4_6_print_9(Impro46Print *self,const char *string, E_IM_PRO_AF_CH ch, T_IM_PRO_HIST_DATA *histCtrl)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Data(%u) %s result:HISTRMODE (%lu)\n", 
        ch, string, histCtrl->mostFrequentValue[0]));
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Data(%u) %s result:HISTGMODE (%lu)\n", 
        ch, string, histCtrl->mostFrequentValue[1]));
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Data(%u) %s result:HISTBMODE (%lu)\n", 
        ch, string, histCtrl->mostFrequentValue[2]));
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Data(%u) %s result:HISTYMODE (%lu)\n", 
        ch, string, histCtrl->mostFrequentValue[3]));
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Data(%u) %s result:HISTRSUM  (%lu)\n", 
        ch, string, histCtrl->accumulationValue[0]));
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Data(%u) %s result:HISTGSUM  (%lu)\n", 
        ch, string, histCtrl->accumulationValue[1]));
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Data(%u) %s result:HISTBSUM  (%lu)\n", 
        ch, string, histCtrl->accumulationValue[2]));
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Data(%u) %s result:HISTYSUM  (%lu)\n", 
        ch, string, histCtrl->accumulationValue[3]));
}
#endif

Impro46Print* impro_4_6_print_new(void)
{
	Impro46Print* self = k_object_new_with_private(IMPRO_TYPE_4_6_PRINT, sizeof(Impro46PrintPrivate));

	return self;
}

Impro46Print* impro_4_6_print_get(void)
{
	static Impro46Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_4_6_PRINT, sizeof(Impro46PrintPrivate));
	}

	return self;
}
