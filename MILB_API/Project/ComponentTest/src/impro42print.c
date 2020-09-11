/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro42Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro42print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro42Print, impro_4_2_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_4_2_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro42PrintPrivate, IMPRO_TYPE_4_2_PRINT))


struct _Impro42PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_4_2_print_constructor(Impro42Print *self)
{
	Impro42PrintPrivate *priv = IMPRO_4_2_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_4_2_print_destructor(Impro42Print *self)
{
	Impro42PrintPrivate *priv = IMPRO_4_2_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_4_2_print_0(Impro42Print *self,const char *string, E_IM_PRO_AEAWB_CH ch, kulong *lineData)
{
    if (lineData[0] != ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev1.bit.linev_0)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_Line_Data(%u) %s result:linev_0  (%lu)  reg_val (%u)\n", 
        ch, string, lineData[0], 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev1.bit.linev_0));
    }
    
    if (lineData[1] != ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev1.bit.linev_1)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_Line_Data(%u) %s result:linev_1  (%lu)  reg_val (%u)\n", 
        ch, string, lineData[1], 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev1.bit.linev_1));
    }
    
    if (lineData[2] != ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev2.bit.linev_2)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_Line_Data(%u) %s result:linev_2  (%lu)  reg_val (%u)\n", 
        ch, string, lineData[2], 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev2.bit.linev_2));
    }
    
    if (lineData[3] != ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev2.bit.linev_3)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_Line_Data(%u) %s result:linev_3  (%lu)  reg_val (%u)\n", 
        ch, string, lineData[3], 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev2.bit.linev_3));
    }
}

void im_pro_4_2_print_1(Impro42Print *self,const char *string, E_IM_PRO_AEAWB_CH ch, kulong *dataAddress)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_AEAWBData(%u) %s result:current_addr(0x%08lx)\n", 
        ch, string, *dataAddress));
}

void im_pro_4_2_print_2(Impro42Print *self,const char *string, E_IM_PRO_AEAWB_CH ch, kulong *dataAddress)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_LastAEAWBData(%u) %s result:last_addr(0x%08lx)\n", 
        ch, string, *dataAddress));
}

void im_pro_4_2_print_3(Impro42Print *self,const char *string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_WD_INFO *wdInfo)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_WD_Info(%u, %u, %u, %u) %s result:dataAddress (0x%08lx) gWidth (%lu)\n", 
        ch, wdInfo->mode, wdInfo->type, wdInfo->aehbc, string, (kulong)wdInfo->address, 
        (kulong)wdInfo->globalDataWidth));
}

void im_pro_4_2_print_4(Impro42Print *self,E_IM_PRO_AF_CH ch)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Start(%u) result:aetrg  0x%08lx(%u)\n", 
        ch, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetrg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetrg.bit.aetrg));
}

void im_pro_4_2_print_5(Impro42Print *self,E_IM_PRO_AF_CH ch, kuchar force)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Stop(%u %u) result:aetrg    0x%08lx(%u)\n", 
        ch, force, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetrg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetrg.bit.aetrg));
}

void im_pro_4_2_print_6(Impro42Print *self,const char *string, E_IM_PRO_AF_CH ch, T_IM_PRO_AF_CTRL *afCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enm0 != afCtrl->evalCalc0Enable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enm0, 
        afCtrl->evalCalc0Enable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enm1 != afCtrl->evalCalc1Enable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enm1, 
        afCtrl->evalCalc1Enable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enm2 != afCtrl->evalCalc2Enable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enm2, 
        afCtrl->evalCalc2Enable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.env0 != afCtrl->verticalEnable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.env0, 
        afCtrl->verticalEnable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enh0 != afCtrl->horizon0Enable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enh0, 
        afCtrl->horizon0Enable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enh1 != afCtrl->horizon1Enable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enh1, 
        afCtrl->horizon1Enable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enh2 != afCtrl->horizon2Enable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enh2, 
        afCtrl->horizon2Enable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw0 != afCtrl->enable[E_IM_PRO_AF_WINDOW_0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw0, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw1 != afCtrl->enable[E_IM_PRO_AF_WINDOW_1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw1, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw2 != afCtrl->enable[E_IM_PRO_AF_WINDOW_2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw2, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw3 != afCtrl->enable[E_IM_PRO_AF_WINDOW_3])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw3, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_3]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw4 != afCtrl->enable[E_IM_PRO_AF_WINDOW_4])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw4, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_4]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw5 != afCtrl->enable[E_IM_PRO_AF_WINDOW_5])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw5, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_5]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw6 != afCtrl->enable[E_IM_PRO_AF_WINDOW_6])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw6, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_6]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw7 != afCtrl->enable[E_IM_PRO_AF_WINDOW_7])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw7, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_7]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw8 != afCtrl->enable[E_IM_PRO_AF_WINDOW_8])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw8, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_8]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw9 != afCtrl->enable[E_IM_PRO_AF_WINDOW_9])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw9, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_9]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw10 != afCtrl->enable[E_IM_PRO_AF_WINDOW_10])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw10, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_10]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw11 != afCtrl->enable[E_IM_PRO_AF_WINDOW_11])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw11, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_11]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw12 != afCtrl->enable[E_IM_PRO_AF_WINDOW_12])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw12, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_12]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw13 != afCtrl->enable[E_IM_PRO_AF_WINDOW_13])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw13, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_13]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw14 != afCtrl->enable[E_IM_PRO_AF_WINDOW_14])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl(%u) %s result:aeawbwmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afeben.bit.enw14, 
        afCtrl->enable[E_IM_PRO_AF_WINDOW_14]));
    }
}

void im_pro_4_2_print_7(Impro42Print *self,E_IM_PRO_AF_CH ch, kuchar paenTrg)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Set_PAEN(%u %u) result:paen    0x%08lx(%u)\n", 
        ch, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afpaen.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afpaen.bit.afpaen));
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Set_PAEN(%u %u) result:aftrg   0x%08lx(%u)\n", 
        ch, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.aftrg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.aftrg.bit.aftrg));
}

void im_pro_4_2_print_8(Impro42Print *self,const char *string, E_IM_PRO_AF_CH ch, T_IM_PRO_AREA_INFO *globalWin)
{
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afgh.bit.afgh != globalWin->posX)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Set_Global_Area(%u) %s result:afgh  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afgh.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afgh.bit.afgh, globalWin->posX));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afgv.bit.afgv != globalWin->posY)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Set_Global_Area(%u) %s result:afgv  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afgv.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afgv.bit.afgv, globalWin->posY));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afghw.bit.afghw != globalWin->width)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Set_Global_Area(%u) %s result:afghw 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afghw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afghw.bit.afghw, globalWin->width));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afgvw.bit.afgvw != globalWin->lines)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Set_Global_Area(%u) %s result:afgvw 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afgvw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afgvw.bit.afgvw, globalWin->lines));
    }
}

void im_pro_4_2_print_9(Impro42Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_EVAL_CALC_UNIT unitNo, 
T_IM_PRO_AF_EVAL_CALC_CTRL *afEvalCalcCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxrr.bit.afmtrxrr != afEvalCalcCtrl->r)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afmtrxrr   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxrr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxrr.bit.afmtrxrr, afEvalCalcCtrl->r));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxgr.bit.afmtrxgr != afEvalCalcCtrl->gr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afmtrxgr   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxgr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxgr.bit.afmtrxgr, afEvalCalcCtrl->gr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxgb.bit.afmtrxgb != afEvalCalcCtrl->gb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afmtrxgb   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxgb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxgb.bit.afmtrxgb, afEvalCalcCtrl->gb));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxbb.bit.afmtrxbb != afEvalCalcCtrl->b)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afmtrxbb   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxbb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmtrxbb.bit.afmtrxbb, afEvalCalcCtrl->b));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmden.bit.afmden != afEvalCalcCtrl->medianEnable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afmden     0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmden.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afmden.bit.afmden, afEvalCalcCtrl->medianEnable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknen.bit.afknen != afEvalCalcCtrl->kneeEnable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknen     0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknen.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknen.bit.afknen, afEvalCalcCtrl->kneeEnable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb1.bit.afknb1 != afEvalCalcCtrl->kneeBoundary[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknb1    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb1.bit.afknb1, afEvalCalcCtrl->kneeBoundary[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb1.bit.afknb2 != afEvalCalcCtrl->kneeBoundary[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknb2    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb1.bit.afknb2, afEvalCalcCtrl->kneeBoundary[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb2.bit.afknb3 != afEvalCalcCtrl->kneeBoundary[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknb3    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb2.bit.afknb3, afEvalCalcCtrl->kneeBoundary[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb2.bit.afknb4 != afEvalCalcCtrl->kneeBoundary[3])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknb4    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb2.bit.afknb4, afEvalCalcCtrl->kneeBoundary[3]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb3.bit.afknb5 != afEvalCalcCtrl->kneeBoundary[4])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknb5    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb3.bit.afknb5, afEvalCalcCtrl->kneeBoundary[4]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb3.bit.afknb6 != afEvalCalcCtrl->kneeBoundary[5])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknb6    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb3.bit.afknb6, afEvalCalcCtrl->kneeBoundary[5]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb4.bit.afknb7 != afEvalCalcCtrl->kneeBoundary[6])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknb7    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb4.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknb.afknb4.bit.afknb7, afEvalCalcCtrl->kneeBoundary[6]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc1.bit.afkninc0 != afEvalCalcCtrl->kneeSlope[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afkninc0  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc1.bit.afkninc0, afEvalCalcCtrl->kneeSlope[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc1.bit.afkninc1 != afEvalCalcCtrl->kneeSlope[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afkninc1  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc1.bit.afkninc1, afEvalCalcCtrl->kneeSlope[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc2.bit.afkninc2 != afEvalCalcCtrl->kneeSlope[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afkninc2  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc2.bit.afkninc2, afEvalCalcCtrl->kneeSlope[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc2.bit.afkninc3 != afEvalCalcCtrl->kneeSlope[3])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afkninc3  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc2.bit.afkninc3, afEvalCalcCtrl->kneeSlope[3]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc3.bit.afkninc4 != afEvalCalcCtrl->kneeSlope[4])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afkninc4  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc3.bit.afkninc4, afEvalCalcCtrl->kneeSlope[4]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc3.bit.afkninc5 != afEvalCalcCtrl->kneeSlope[5])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afkninc5  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc3.bit.afkninc5, afEvalCalcCtrl->kneeSlope[5]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc4.bit.afkninc6 != afEvalCalcCtrl->kneeSlope[6])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afkninc6  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc4.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc4.bit.afkninc6, afEvalCalcCtrl->kneeSlope[6]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc4.bit.afkninc7 != afEvalCalcCtrl->kneeSlope[7])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afkninc7  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc4.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afkninc.afkninc4.bit.afkninc7, afEvalCalcCtrl->kneeSlope[7]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs1.bit.afknofs0 != afEvalCalcCtrl->kneeOffset[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknofs0  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs1.bit.afknofs0, afEvalCalcCtrl->kneeOffset[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs1.bit.afknofs1 != afEvalCalcCtrl->kneeOffset[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknofs1  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs1.bit.afknofs1, afEvalCalcCtrl->kneeOffset[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs2.bit.afknofs2 != afEvalCalcCtrl->kneeOffset[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknofs2  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs2.bit.afknofs2, afEvalCalcCtrl->kneeOffset[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs2.bit.afknofs3 != afEvalCalcCtrl->kneeOffset[3])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknofs3  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs2.bit.afknofs3, afEvalCalcCtrl->kneeOffset[3]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs3.bit.afknofs4 != afEvalCalcCtrl->kneeOffset[4])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknofs4  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs3.bit.afknofs4, afEvalCalcCtrl->kneeOffset[4]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs3.bit.afknofs5 != afEvalCalcCtrl->kneeOffset[5])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknofs5  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs3.bit.afknofs5, afEvalCalcCtrl->kneeOffset[5]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs4.bit.afknofs6 != afEvalCalcCtrl->kneeOffset[6])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknofs6  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs4.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs4.bit.afknofs6, afEvalCalcCtrl->kneeOffset[6]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs4.bit.afknofs7 != afEvalCalcCtrl->kneeOffset[7])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Eval_Calc(%u) %s result:afknofs7  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs4.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afmain[unitNo].afknofs.afknofs4.bit.afknofs7, afEvalCalcCtrl->kneeOffset[7]));
    }
}
#endif

Impro42Print* impro_4_2_print_new(void)
{
	Impro42Print* self = k_object_new_with_private(IMPRO_TYPE_4_2_PRINT, sizeof(Impro42PrintPrivate));

	return self;
}

Impro42Print* impro_4_2_print_get(void)
{
	static Impro42Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_4_2_PRINT, sizeof(Impro42PrintPrivate));
	}

	return self;
}
