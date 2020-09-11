/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro41Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro41print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro41Print, impro_4_1_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_4_1_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro41PrintPrivate, IMPRO_TYPE_4_1_PRINT))


struct _Impro41PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_4_1_print_constructor(Impro41Print *self)
{
	Impro41PrintPrivate *priv = IMPRO_4_1_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_4_1_print_destructor(Impro41Print *self)
{
	Impro41PrintPrivate *priv = IMPRO_4_1_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_4_1_print_4(Impro41Print *self,const char *string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_CW *aeawbCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw1.bit.aecvw != aeawbCtrl->aecvw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:aecvw   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw1.bit.aecvw, 
        aeawbCtrl->aecvw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw1.bit.aechw != aeawbCtrl->aechw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:aechw   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw1.bit.aechw, 
        aeawbCtrl->aechw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw2.bit.aectw != aeawbCtrl->aectw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:aectw   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw2.bit.aectw, 
        aeawbCtrl->aectw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw3.bit.aecbw != aeawbCtrl->aecbw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:aecbw   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw3.bit.aecbw, 
        aeawbCtrl->aecbw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw2.bit.aeclw != aeawbCtrl->aeclw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:aeclw   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw2.bit.aeclw, 
        aeawbCtrl->aeclw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw3.bit.aecrw != aeawbCtrl->aecrw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:aecrw   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aecw3.bit.aecrw, 
        aeawbCtrl->aecrw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw1.bit.awbcvw != aeawbCtrl->awcvw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:awbcvw  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw1.bit.awbcvw, 
        aeawbCtrl->awcvw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw1.bit.awbchw != aeawbCtrl->awchw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:awbchw  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw1.bit.awbchw, 
        aeawbCtrl->awchw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw2.bit.awbctw != aeawbCtrl->awctw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:awbctw  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw2.bit.awbctw, 
        aeawbCtrl->awctw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw3.bit.awbcbw != aeawbCtrl->awcbw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:awbcbw  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw3.bit.awbcbw, 
        aeawbCtrl->awcbw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw2.bit.awbclw != aeawbCtrl->awclw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:awbclw  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw2.bit.awbclw, 
        aeawbCtrl->awclw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw3.bit.awbcrw != aeawbCtrl->awcrw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_CW(%u) %s result:awbcrw  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awbcw3.bit.awbcrw, 
        aeawbCtrl->awcrw));
    }
}

void im_pro_4_1_print_5(Impro41Print *self,const char *string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_LV_GATE *aeawbCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.bit.awtduy != aeawbCtrl->awtduy)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Lv_Gate(%u) %s result:awtduy 0x%08lx(%u) (%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.bit.awtduy, 
        aeawbCtrl->awtduy));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdr.bit.awtdur != aeawbCtrl->awtdur)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Lv_Gate(%u) %s result:awtdur 0x%08lx(%u) (%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdr.bit.awtdur, 
        aeawbCtrl->awtdur));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdg.bit.awtdug != aeawbCtrl->awtdug)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Lv_Gate(%u) %s result:awtdug 0x%08lx(%u) (%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdg.bit.awtdug, 
        aeawbCtrl->awtdug));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdb.bit.awtdub != aeawbCtrl->awtdub)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Lv_Gate(%u) %s result:awtdub 0x%08lx(%u) (%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdb.bit.awtdub, 
        aeawbCtrl->awtdub));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.bit.awtdly != aeawbCtrl->awtdly)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Lv_Gate(%u) %s result:awtdly 0x%08lx(%u) (%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.bit.awtdly, 
        aeawbCtrl->awtdly));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdr.bit.awtdlr != aeawbCtrl->awtdlr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Lv_Gate(%u) %s result:awtdlr 0x%08lx(%u) (%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdr.bit.awtdlr, 
        aeawbCtrl->awtdlr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdg.bit.awtdlg != aeawbCtrl->awtdlg)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Lv_Gate(%u) %s result:awtdlg 0x%08lx(%u) (%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdg.bit.awtdlg, 
        aeawbCtrl->awtdlg));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdb.bit.awtdlb != aeawbCtrl->awtdlb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Lv_Gate(%u) %s result:awtdlb 0x%08lx(%u) (%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdb.bit.awtdlb, 
        aeawbCtrl->awtdlb));
    }
}

void im_pro_4_1_print_6(Impro41Print *self,const char *string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_MATRIX_LV_GATE *aeawbCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcy.bit.awmlucy != aeawbCtrl->awmlucy)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmlucy 0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcy.bit.awmlucy, 
        aeawbCtrl->awmlucy));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcy.bit.awmllcy != aeawbCtrl->awmllcy)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmllcy 0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcy.bit.awmllcy, 
        aeawbCtrl->awmllcy));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcb.bit.awmlucb != aeawbCtrl->awmlucb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmlucb 0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcb.bit.awmlucb, 
        aeawbCtrl->awmlucb));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcb.bit.awmllcb != aeawbCtrl->awmllcb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmllcb 0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcb.bit.awmllcb, 
        aeawbCtrl->awmllcb));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcr.bit.awmlucr != aeawbCtrl->awmlucr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmlucr 0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcr.bit.awmlucr, 
        aeawbCtrl->awmlucr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcr.bit.awmllcr != aeawbCtrl->awmllcr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmllcr 0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmlcr.bit.awmllcr, 
        aeawbCtrl->awmllcr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc1.bit.awmc00 != aeawbCtrl->awmc[0][0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmc00  0x%08lx(%d) (%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc1.bit.awmc00, 
        aeawbCtrl->awmc[0][0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc1.bit.awmc01 != aeawbCtrl->awmc[0][1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmc01  0x%08lx(%d) (%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc1.bit.awmc01, 
        aeawbCtrl->awmc[0][1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc2.bit.awmc02 != aeawbCtrl->awmc[0][2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmc02  0x%08lx(%d) (%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc2.bit.awmc02, 
        aeawbCtrl->awmc[0][2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc2.bit.awmc10 != aeawbCtrl->awmc[1][0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmc10  0x%08lx(%d) (%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc2.bit.awmc10, 
        aeawbCtrl->awmc[1][0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc3.bit.awmc11 != aeawbCtrl->awmc[1][1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmc11  0x%08lx(%d) (%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc3.bit.awmc11, 
        aeawbCtrl->awmc[1][1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc3.bit.awmc12 != aeawbCtrl->awmc[1][2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmc12  0x%08lx(%d) (%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc3.bit.awmc12, 
        aeawbCtrl->awmc[1][2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc4.bit.awmc20 != aeawbCtrl->awmc[2][0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmc20  0x%08lx(%d) (%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc4.bit.awmc20, 
        aeawbCtrl->awmc[2][0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc4.bit.awmc21 != aeawbCtrl->awmc[2][1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmc21  0x%08lx(%d) (%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc4.bit.awmc21, 
        aeawbCtrl->awmc[2][1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc5.bit.awmc22 != aeawbCtrl->awmc[2][2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Matrix_Lv_Gate(%u) %s result:awmc22  0x%08lx(%d) (%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awtdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].awmc.awmc5.bit.awmc22, 
        aeawbCtrl->awmc[2][2]));
    }
}

void im_pro_4_1_print_7(Impro41Print *self,const char *string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_STAT_YK *aeawbCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykrr.bit.aeykrr != aeawbCtrl->ykr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_AEYK(%u) %s result:aeykrr    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykrr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykrr.bit.aeykrr, 
        aeawbCtrl->ykr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykgr.bit.aeykgr != aeawbCtrl->ykgr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_AEYK(%u) %s result:aeykgr    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykgr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykgr.bit.aeykgr, 
        aeawbCtrl->ykgr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykgb.bit.aeykgb != aeawbCtrl->ykgb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_AEYK(%u) %s result:aeykgb    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykgb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykgb.bit.aeykgb, 
        aeawbCtrl->ykgb));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykbb.bit.aeykbb != aeawbCtrl->ykb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_AEYK(%u) %s result:aeykbb    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykbb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykbb.bit.aeykbb, 
        aeawbCtrl->ykb));
    }
}

void im_pro_4_1_print_8(Impro41Print *self,const char *string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_STAT_YK *aeyk)
{
    if (aeyk->ykr != ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykrr.bit.aeykrr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_AEYK(%u) %s result:aeykrr    (%d)  reg_val (%d)\n", 
        ch, string, aeyk->ykr, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykrr.bit.aeykrr));
    }
    
    if (aeyk->ykgr != ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykgr.bit.aeykgr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_AEYK(%u) %s result:aeykgr    (%d)  reg_val (%d)\n", 
        ch, string, aeyk->ykgr, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykgr.bit.aeykgr));
    }
    
    if (aeyk->ykgb != ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykgb.bit.aeykgb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_AEYK(%u) %s result:aeykgb    (%d)  reg_val (%d)\n", 
        ch, string, aeyk->ykgb, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykgb.bit.aeykgb));
    }
    
    if (aeyk->ykb != ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykbb.bit.aeykbb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_AEYK(%u) %s result:aeykbb    (%d)  reg_val (%d)\n", 
        ch, string, aeyk->ykb, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeykbb.bit.aeykbb));
    }
}

void im_pro_4_1_print_9(Impro41Print *self,const char *string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_LINE_INFO *aeawbCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev1.bit.linev_0 != aeawbCtrl->startLine[0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Line_Data_Position(%u) %s result:linev_0 0x%08lx(%u) in(%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev1.bit.linev_0, 
        aeawbCtrl->startLine[0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev1.bit.linev_1 != aeawbCtrl->startLine[1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Line_Data_Position(%u) %s result:linev_1 0x%08lx(%u) in(%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev1.bit.linev_1, 
        aeawbCtrl->startLine[1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev2.bit.linev_2 != aeawbCtrl->startLine[2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Line_Data_Position(%u) %s result:linev_2 0x%08lx(%u) in(%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev2.bit.linev_2, 
        aeawbCtrl->startLine[2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev2.bit.linev_3 != aeawbCtrl->startLine[3])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_Line_Data_Position(%u) %s result:linev_3 0x%08lx(%u) in(%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].linev.linev2.bit.linev_3, 
        aeawbCtrl->startLine[3]));
    }
}
#endif

Impro41Print* impro_4_1_print_new(void)
{
	Impro41Print* self = k_object_new_with_private(IMPRO_TYPE_4_1_PRINT, sizeof(Impro41PrintPrivate));

	return self;
}

Impro41Print* impro_4_1_print_get(void)
{
	static Impro41Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_4_1_PRINT, sizeof(Impro41PrintPrivate));
	}

	return self;
}
