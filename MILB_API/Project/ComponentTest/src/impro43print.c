/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro43Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro43print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro43Print, impro_4_3_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_4_3_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro43PrintPrivate, IMPRO_TYPE_4_3_PRINT))


struct _Impro43PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_4_3_print_constructor(Impro43Print *self)
{
	Impro43PrintPrivate *priv = IMPRO_4_3_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_4_3_print_destructor(Impro43Print *self)
{
	Impro43PrintPrivate *priv = IMPRO_4_3_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_4_3_print_0(Impro43Print *self,const char *string, E_IM_PRO_AF_CH ch, T_IM_PRO_AF_VERTICAL_CTRL *afVerticalCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvsctl.bit.afvscyc != afVerticalCtrl->updateCycle)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afvscyc     0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvsctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvsctl.bit.afvscyc, afVerticalCtrl->updateCycle));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvsctl.bit.afslv != afVerticalCtrl->evalCalUnit)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afslv       0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvsctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvsctl.bit.afslv, afVerticalCtrl->evalCalUnit));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvsh.bit.afvsh != afVerticalCtrl->startAddr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afvsh       0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvsh.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvsh.bit.afvsh, afVerticalCtrl->startAddr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvshw.bit.afvshw != afVerticalCtrl->horizonSize)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afvshw      0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvshw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afvshw.bit.afvshw, afVerticalCtrl->horizonSize));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb1.bit.afiirvk != afVerticalCtrl->iirK)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afiirvk     0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb1.bit.afiirvk, afVerticalCtrl->iirK));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb1.bit.afiirva0 != afVerticalCtrl->iirA0)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afiirva0    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb1.bit.afiirva0, afVerticalCtrl->iirA0));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb1.bit.afiirva1 != afVerticalCtrl->iirA1)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afiirva1    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb1.bit.afiirva1, afVerticalCtrl->iirA1));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb2.bit.afiirva2 != afVerticalCtrl->iirA2)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afiirva2    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb2.bit.afiirva2, afVerticalCtrl->iirA2));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb2.bit.afiirvb1 != afVerticalCtrl->iirB1)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afiirvb1    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb2.bit.afiirvb1, afVerticalCtrl->iirB1));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb3.bit.afiirvb2 != afVerticalCtrl->iirB2)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afiirvb2    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afiirvb.afiirvb3.bit.afiirvb2, afVerticalCtrl->iirB2));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afcor2v.bit.afcor2lvv != afVerticalCtrl->corThreshold)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afcor2lvv   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afcor2v.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afcor2v.bit.afcor2lvv, afVerticalCtrl->corThreshold));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afcor2v.bit.afcor2v != afVerticalCtrl->corLevel)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:afcor2v     0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afcor2v.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.afcor2v.bit.afcor2v, afVerticalCtrl->corLevel));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.affirvb.bit.affirvb1 != afVerticalCtrl->firFilter[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:affirvb1    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.affirvb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.affirvb.bit.affirvb1, afVerticalCtrl->firFilter[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.affirvb.bit.affirvb2 != afVerticalCtrl->firFilter[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:affirvb2    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.affirvb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.affirvb.bit.affirvb2, afVerticalCtrl->firFilter[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.affirvb.bit.affirvb3 != afVerticalCtrl->firFilter[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Vertical(%u) %s result:affirvb3    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.affirvb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afvs.affirvb.bit.affirvb3, afVerticalCtrl->firFilter[2]));
    }
}

void im_pro_4_3_print_1(Impro43Print *self,const char *string, E_IM_PRO_AF_CH ch, kuchar tapNo, T_IM_PRO_AF_HORIZON_CTRL *afCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctla.bit.afiha != afCtrl->groupA.iirEnable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiha         0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctla.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctla.bit.afiha, afCtrl->groupA.iirEnable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctla.bit.affha != afCtrl->groupA.firEnable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affha         0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctla.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctla.bit.affha, afCtrl->groupA.firEnable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctla.bit.afslha != afCtrl->groupA.inputSelect)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afslha        0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctla.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctla.bit.afslha, afCtrl->groupA.inputSelect));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.bit.affirhba1 != afCtrl->groupA.firCoefficient[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affirhba1    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.bit.affirhba1, afCtrl->groupA.firCoefficient[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.bit.affirhba2 != afCtrl->groupA.firCoefficient[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affirhba2    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.bit.affirhba2, afCtrl->groupA.firCoefficient[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.bit.affirhba3 != afCtrl->groupA.firCoefficient[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affirhba3    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.bit.affirhba3, afCtrl->groupA.firCoefficient[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.bit.affirhba4 != afCtrl->groupA.firCoefficient[3])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affirhba4    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba1.bit.affirhba4, afCtrl->groupA.firCoefficient[3]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba2.bit.affirhba5 != afCtrl->groupA.firCoefficient[4])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affirhba5    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhba.affirhba2.bit.affirhba5, afCtrl->groupA.firCoefficient[4]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcor1ha.bit.afcor1ha != afCtrl->groupA.firLevel)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcor1ha      0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcor1ha.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcor1ha.bit.afcor1ha, afCtrl->groupA.firLevel));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afgainha.bit.afgainha != afCtrl->groupA.gain)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afgainha      0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afgainha.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afgainha.bit.afgainha, afCtrl->groupA.gain));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba1.bit.afiirhka != afCtrl->groupA.iirK)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirhka      0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba1.bit.afiirhka, afCtrl->groupA.iirK));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba1.bit.afiirha0a != afCtrl->groupA.iirA0)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirha0a     0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba1.bit.afiirha0a, afCtrl->groupA.iirA0));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba1.bit.afiirha1a != afCtrl->groupA.iirA1)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirha1a     0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba1.bit.afiirha1a, afCtrl->groupA.iirA1));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba2.bit.afiirha2a != afCtrl->groupA.iirA2)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirha2a     0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba2.bit.afiirha2a, afCtrl->groupA.iirA2));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba2.bit.afiirhb1a != afCtrl->groupA.iirB1)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirhb1a     0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba2.bit.afiirhb1a, afCtrl->groupA.iirB1));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba3.bit.afiirhb2a != afCtrl->groupA.iirB2)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirhb2a     0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhba.afiirhba3.bit.afiirhb2a, afCtrl->groupA.iirB2));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbha.afcorbha1.bit.afcorbha1 != afCtrl->groupA.coringBounder[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorbha1    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbha.afcorbha1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbha.afcorbha1.bit.afcorbha1, afCtrl->groupA.coringBounder[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbha.afcorbha1.bit.afcorbha2 != afCtrl->groupA.coringBounder[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorbha2    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbha.afcorbha1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbha.afcorbha1.bit.afcorbha2, afCtrl->groupA.coringBounder[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbha.afcorbha2.bit.afcorbha3 != afCtrl->groupA.coringBounder[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorbha3    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbha.afcorbha2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbha.afcorbha2.bit.afcorbha3, afCtrl->groupA.coringBounder[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha1.bit.afcorincha0 != afCtrl->groupA.coringSlope[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorincha0  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha1.bit.afcorincha0, afCtrl->groupA.coringSlope[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha1.bit.afcorincha1 != afCtrl->groupA.coringSlope[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorincha1  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha1.bit.afcorincha1, afCtrl->groupA.coringSlope[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha2.bit.afcorincha2 != afCtrl->groupA.coringSlope[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorincha2  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha2.bit.afcorincha2, afCtrl->groupA.coringSlope[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha2.bit.afcorincha3 != afCtrl->groupA.coringSlope[3])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorincha3  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorincha.afcorincha2.bit.afcorincha3, afCtrl->groupA.coringSlope[3]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha1.bit.afcorofsha0 != afCtrl->groupA.coringOffset[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorofsha0  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha1.bit.afcorofsha0, afCtrl->groupA.coringOffset[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha1.bit.afcorofsha1 != afCtrl->groupA.coringOffset[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorofsha1  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha1.bit.afcorofsha1, afCtrl->groupA.coringOffset[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha2.bit.afcorofsha2 != afCtrl->groupA.coringOffset[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorofsha2  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha2.bit.afcorofsha2, afCtrl->groupA.coringOffset[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha2.bit.afcorofsha3 != afCtrl->groupA.coringOffset[3])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorofsha3  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofsha.afcorofsha2.bit.afcorofsha3, afCtrl->groupA.coringOffset[3]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctlb.bit.afihb != afCtrl->groupB.iirEnable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afihb         0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctlb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctlb.bit.afihb, afCtrl->groupB.iirEnable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctlb.bit.affhb != afCtrl->groupB.firEnable)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affhb         0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctlb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctlb.bit.affhb, afCtrl->groupB.firEnable));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctlb.bit.afslhb != afCtrl->groupB.inputSelect)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afslhb        0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctlb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afhsctlb.bit.afslhb, afCtrl->groupB.inputSelect));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.bit.affirhbb_1 != afCtrl->groupB.firCoefficient[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affirhbb_1    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.bit.affirhbb_1, afCtrl->groupB.firCoefficient[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.bit.affirhbb_2 != afCtrl->groupB.firCoefficient[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affirhbb_2    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.bit.affirhbb_2, afCtrl->groupB.firCoefficient[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.bit.affirhbb_3 != afCtrl->groupB.firCoefficient[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affirhbb_3    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.bit.affirhbb_3, afCtrl->groupB.firCoefficient[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.bit.affirhbb_4 != afCtrl->groupB.firCoefficient[3])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affirhbb_4    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb1.bit.affirhbb_4, afCtrl->groupB.firCoefficient[3]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb2.bit.affirhbb_5 != afCtrl->groupB.firCoefficient[4])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:affirhbb_5    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].affirhbb.affirhbb2.bit.affirhbb_5, afCtrl->groupB.firCoefficient[4]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcor1hb.bit.afcor1hb != afCtrl->groupB.firLevel)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcor1hb      0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcor1hb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcor1hb.bit.afcor1hb, afCtrl->groupB.firLevel));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afgainhb.bit.afgainhb != afCtrl->groupB.gain)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afgainhb      0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afgainhb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afgainhb.bit.afgainhb, afCtrl->groupB.gain));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb1.bit.afiirhkb != afCtrl->groupB.iirK)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirhkb      0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb1.bit.afiirhkb, afCtrl->groupB.iirK));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb1.bit.afiirha0b != afCtrl->groupB.iirA0)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirha0b     0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb1.bit.afiirha0b, afCtrl->groupB.iirA0));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb1.bit.afiirha1b != afCtrl->groupB.iirA1)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirha1b     0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb1.bit.afiirha1b, afCtrl->groupB.iirA1));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb2.bit.afiirha2b != afCtrl->groupB.iirA2)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirha2b     0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb2.bit.afiirha2b, afCtrl->groupB.iirA2));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb2.bit.afiirhb1b != afCtrl->groupB.iirB1)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirhb1b     0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb2.bit.afiirhb1b, afCtrl->groupB.iirB1));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb3.bit.afiirhb2b != afCtrl->groupB.iirB2)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afiirhb2b     0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afiirhbb.afiirhbb3.bit.afiirhb2b, afCtrl->groupB.iirB2));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbhb.afcorbhb1.bit.afcorbhb_1 != afCtrl->groupB.coringBounder[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorbhb_1    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbhb.afcorbhb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbhb.afcorbhb1.bit.afcorbhb_1, afCtrl->groupB.coringBounder[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbhb.afcorbhb1.bit.afcorbhb_2 != afCtrl->groupB.coringBounder[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorbhb_2    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbhb.afcorbhb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbhb.afcorbhb1.bit.afcorbhb_2, afCtrl->groupB.coringBounder[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbhb.afcorbhb2.bit.afcorbhb_3 != afCtrl->groupB.coringBounder[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorbhb_3    0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbhb.afcorbhb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorbhb.afcorbhb2.bit.afcorbhb_3, afCtrl->groupB.coringBounder[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb1.bit.afcorinchb_0 != afCtrl->groupB.coringSlope[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorinchb_0  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb1.bit.afcorinchb_0, afCtrl->groupB.coringSlope[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb1.bit.afcorinchb_1 != afCtrl->groupB.coringSlope[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorinchb_1  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb1.bit.afcorinchb_1, afCtrl->groupB.coringSlope[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb2.bit.afcorinchb_2 != afCtrl->groupB.coringSlope[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorinchb_2  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb2.bit.afcorinchb_2, afCtrl->groupB.coringSlope[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb2.bit.afcorinchb_3 != afCtrl->groupB.coringSlope[3])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorinchb_3  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorinchb.afcorinchb2.bit.afcorinchb_3, afCtrl->groupB.coringSlope[3]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb1.bit.afcorofshb_0 != afCtrl->groupB.coringOffset[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorofshb_0  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb1.bit.afcorofshb_0, afCtrl->groupB.coringOffset[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb1.bit.afcorofshb_1 != afCtrl->groupB.coringOffset[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorofshb_1  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb1.bit.afcorofshb_1, afCtrl->groupB.coringOffset[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb2.bit.afcorofshb_2 != afCtrl->groupB.coringOffset[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorofshb_2  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb2.bit.afcorofshb_2, afCtrl->groupB.coringOffset[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb2.bit.afcorofshb_3 != afCtrl->groupB.coringOffset[3])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Horizon(%u %u) %s result:afcorofshb_3  0x%08lx(%d) in(%d)\n", 
        ch, tapNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afhs[tapNo].afcorofshb.afcorofshb2.bit.afcorofshb_3, afCtrl->groupB.coringOffset[3]));
    }
}

void im_pro_4_3_print_2(Impro43Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, T_IM_PRO_AF_WIN_CTRL *afCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.bit.afslwh0 != afCtrl->hSel0)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Win(%u %u) %s result:afslwh0   0x%08lx(%d) in(%d)\n", 
        ch, winNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.bit.afslwh0, afCtrl->hSel0));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.bit.afslwh1 != afCtrl->hSel1)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Win(%u %u) %s result:afslwh1   0x%08lx(%d) in(%d)\n", 
        ch, winNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.bit.afslwh1, afCtrl->hSel1));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.bit.afslwh2 != afCtrl->hSel2)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Win(%u %u) %s result:afslwh2   0x%08lx(%d) in(%d)\n", 
        ch, winNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.bit.afslwh2, afCtrl->hSel2));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.bit.afslwc != afCtrl->evalCalUnit)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Win(%u %u) %s result:afslwc    0x%08lx(%d) in(%d)\n", 
        ch, winNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afwinctl.bit.afslwc, afCtrl->evalCalUnit));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afclvge.bit.afclvge != afCtrl->brightThreshold)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Win(%u %u) %s result:afclvge   0x%08lx(%d) in(%d)\n", 
        ch, winNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afclvge.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afclvge.bit.afclvge, afCtrl->brightThreshold));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afclvl.bit.afclvl != afCtrl->darkThreshold)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Win(%u %u) %s result:afclvl    0x%08lx(%d) in(%d)\n", 
        ch, winNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afclvl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afclvl.bit.afclvl, afCtrl->darkThreshold));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afh.bit.afh != afCtrl->startPosX)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Win(%u %u) %s result:afh       0x%08lx(%d) in(%d)\n", 
        ch, winNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afh.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afh.bit.afh, afCtrl->startPosX));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afv.bit.afv != afCtrl->startPosY)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Win(%u %u) %s result:afv       0x%08lx(%d) in(%d)\n", 
        ch, winNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afv.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afv.bit.afv, afCtrl->startPosY));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afhw.bit.afhw != afCtrl->width)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Win(%u %u) %s result:afhw      0x%08lx(%d) in(%d)\n", 
        ch, winNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afhw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afhw.bit.afhw, afCtrl->width));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afvw.bit.afvw != afCtrl->height)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Win(%u %u) %s result:afvw      0x%08lx(%d) in(%d)\n", 
        ch, winNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afvw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afvw.bit.afvw, afCtrl->height));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afslwm.bit.afslwm != afCtrl->maxMixSelect)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Ctrl_Win(%u %u) %s result:afslwm    0x%08lx(%d) in(%d)\n", 
        ch, winNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afslwm.word, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afwin[winNo].afslwm.bit.afslwm, afCtrl->maxMixSelect));
    }
}

void im_pro_4_3_print_3(Impro43Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Eval_Calc_Data(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, (kulong)*calcData));
}

void im_pro_4_3_print_4(Impro43Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Bright_Data(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_3_print_5(Impro43Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Dark_Data(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_3_print_6(Impro43Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal0_Data(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_3_print_7(Impro43Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal1_Data(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_3_print_8(Impro43Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal2_Data(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_3_print_9(Impro43Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Vertical_Data(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}
#endif

Impro43Print* impro_4_3_print_new(void)
{
	Impro43Print* self = k_object_new_with_private(IMPRO_TYPE_4_3_PRINT, sizeof(Impro43PrintPrivate));

	return self;
}

Impro43Print* impro_4_3_print_get(void)
{
	static Impro43Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_4_3_PRINT, sizeof(Impro43PrintPrivate));
	}

	return self;
}
