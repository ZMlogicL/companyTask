/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro10Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro10print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImPro10Print, im_pro_1_0_print, ABS_TYPE_IM_PRO_PRINT)
#define IM_PRO_1_0_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImPro10PrintPrivate, IM_TYPE_PRO_1_0_PRINT))


struct _ImPro10PrintPrivate
{

};

/**
 *IMPL
 */
static void im_pro_1_0_print_constructor(ImPro10Print *self)
{
	ImPro10PrintPrivate *priv = IM_PRO_1_0_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void im_pro_1_0_print_destructor(ImPro10Print *self)
{
	ImPro10PrintPrivate *priv = IM_PRO_1_0_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
    //k_object_unref(((AbsImProPrint*)self)->ioPro->);
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_0_print_4(ImPro10Print *self,const char* string, TImProSentopCtrl* sentopCtrl)
{
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.senin0 != sentopCtrl->senConnectTypeSel[0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:senin0 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.senin0, sentopCtrl->senConnectTypeSel[0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.senin1 != sentopCtrl->senConnectTypeSel[1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:senin1 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.senin1, sentopCtrl->senConnectTypeSel[1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.senin2 != sentopCtrl->senConnectTypeSel[2]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:senin2 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.senin2, sentopCtrl->senConnectTypeSel[2]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.senin3 != sentopCtrl->senConnectTypeSel[3]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:senin3 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.senin3, sentopCtrl->senConnectTypeSel[3]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.blobset0 != sentopCtrl->blobInputSel[0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:blobset0 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.blobset0, sentopCtrl->blobInputSel[0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.blobset1 != sentopCtrl->blobInputSel[1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:blobset1 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl11.bit.blobset1, sentopCtrl->blobInputSel[1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl12.bit.blobset2 != sentopCtrl->blobInputSel[2]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:blobset2 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl12.bit.blobset2, sentopCtrl->blobInputSel[2]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl12.bit.blobset3 != sentopCtrl->blobInputSel[3]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:blobset3 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl12.bit.blobset3, sentopCtrl->blobInputSel[3]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl12.bit.pwsw0 != sentopCtrl->sdramOutputType[0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:pwsw0 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl12.bit.pwsw0, sentopCtrl->sdramOutputType[0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl12.bit.pwsw1 != sentopCtrl->sdramOutputType[1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:pwsw1 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl12.bit.pwsw1, sentopCtrl->sdramOutputType[1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.pwsw2 != sentopCtrl->sdramOutputType[2]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:pwsw2 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.pwsw2, sentopCtrl->sdramOutputType[2]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.pwsw3 != sentopCtrl->sdramOutputType[3]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:pwsw3 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.pwsw3, sentopCtrl->sdramOutputType[3]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.pipe2s != sentopCtrl->outputSelSro2) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:pipe2s (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.pipe2s, sentopCtrl->outputSelSro2))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.senramsw != sentopCtrl->sencoreHmaxSizeCtrl) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:senramsw (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.senramsw, sentopCtrl->sencoreHmaxSizeCtrl))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw != sentopCtrl->ldivHmaxSizeCtrl) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:ldivramsw (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw, sentopCtrl->ldivHmaxSizeCtrl))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.ldivmch != sentopCtrl->ldivMultiChInputCtrl) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:ldivmch (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl1.sentopctl13.bit.ldivmch, sentopCtrl->ldivMultiChInputCtrl))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_1.bit.org00 != sentopCtrl->firstPixel[0][0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:org00 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_1.bit.org00, sentopCtrl->firstPixel[0][0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_1.bit.org01 != sentopCtrl->firstPixel[0][1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:org01 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_1.bit.org01, sentopCtrl->firstPixel[0][1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_1.bit.org10 != sentopCtrl->firstPixel[1][0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:org10 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_1.bit.org10, sentopCtrl->firstPixel[1][0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_1.bit.org11 != sentopCtrl->firstPixel[1][1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:org11 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_1.bit.org11, sentopCtrl->firstPixel[1][1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_2.bit.org20 != sentopCtrl->firstPixel[2][0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:org20 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_2.bit.org20, sentopCtrl->firstPixel[2][0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_2.bit.org21 != sentopCtrl->firstPixel[2][1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:org21 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_2.bit.org21, sentopCtrl->firstPixel[2][1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_2.bit.org30 != sentopCtrl->firstPixel[3][0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:org30 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_2.bit.org30, sentopCtrl->firstPixel[3][0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_2.bit.org31 != sentopCtrl->firstPixel[3][1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_ctrl() %s result:org31 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sentopctl2.sentopctl2_2.bit.org31, sentopCtrl->firstPixel[3][1]))
    }; 
}

void im_pro_1_0_print_5(ImPro10Print *self,const char* string, TImProSentopBsCtrl* sentopCtrl)
{
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bsamnt0!= sentopCtrl->shiftValue[0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bsamnt0 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bsamnt0, sentopCtrl->shiftValue[0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bsamnt1!= sentopCtrl->shiftValue[1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bsamnt1 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bsamnt1, sentopCtrl->shiftValue[1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bsamnt2!= sentopCtrl->shiftValue[2]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bsamnt2 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bsamnt2, sentopCtrl->shiftValue[2]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bsamnt3!= sentopCtrl->shiftValue[3]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bsamnt3 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bsamnt3, sentopCtrl->shiftValue[3]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bslmd0 != sentopCtrl->satCompensation[0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bslmd0 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bslmd0, sentopCtrl->satCompensation[0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bslmd1 != sentopCtrl->satCompensation[1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bslmd1 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bslmd1, sentopCtrl->satCompensation[1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bslmd2 != sentopCtrl->satCompensation[2]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bslmd2 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bslmd2, sentopCtrl->satCompensation[2]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bslmd3 != sentopCtrl->satCompensation[3]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bslmd3 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl1.bit.bslmd3, sentopCtrl->satCompensation[3]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl2.bit.bslr0 != sentopCtrl->shiftDir[0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bslr0 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl2.bit.bslr0, sentopCtrl->shiftDir[0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl2.bit.bslr1 != sentopCtrl->shiftDir[1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bslr1 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl2.bit.bslr1, sentopCtrl->shiftDir[1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl2.bit.bslr2 != sentopCtrl->shiftDir[2]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bslr2 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl2.bit.bslr2, sentopCtrl->shiftDir[2]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl2.bit.bslr3 != sentopCtrl->shiftDir[3]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_bs_ctrl() %s result:bslr3 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.bsctl.bsctl2.bit.bslr3, sentopCtrl->shiftDir[3]))
    }; 
}

void im_pro_1_0_print_6(ImPro10Print *self,const char* string, TImProSentopObtCtrl* sentopCtrl)
{
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.btcdcctl1.bit.OBTCPAT != sentopCtrl->obtCommPerttern) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_obt_ctrl() %s result:OBTCPAT (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.btcdcctl1.bit.OBTCPAT, sentopCtrl->obtCommPerttern))
    }; 
}

void im_pro_1_0_print_7(ImPro10Print *self,const char* string, TImProSentopObtWeightCoeff* sentopCtrl)
{
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.obtcdcctl2_1.bit.obtdwc00 != sentopCtrl->coeff[0][0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_obt_set_weight_coeff() %s result:obtdwc00 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.obtcdcctl2_1.bit.obtdwc00, sentopCtrl->coeff[0][0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.obtcdcctl2_1.bit.obtdwc01 != sentopCtrl->coeff[0][1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_obt_set_weight_coeff() %s result:obtdwc01 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.obtcdcctl2_1.bit.obtdwc01, sentopCtrl->coeff[0][1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.obtcdcctl2_1.bit.obtdwc10 != sentopCtrl->coeff[1][0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_obt_set_weight_coeff() %s result:obtdwc10 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.obtcdcctl2_1.bit.obtdwc10, sentopCtrl->coeff[1][0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.obtcdcctl2_1.bit.obtdwc11 != sentopCtrl->coeff[1][1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_obt_set_weight_coeff() %s result:obtdwc11 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.obtcdcctl2_1.bit.obtdwc11, sentopCtrl->coeff[1][1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.btcdcctl2_2.bit.obtdwc20 != sentopCtrl->coeff[2][0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_obt_set_weight_coeff() %s result:obtdwc20 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.btcdcctl2_2.bit.obtdwc20, sentopCtrl->coeff[2][0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.btcdcctl2_2.bit.obtdwc21 != sentopCtrl->coeff[2][1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_obt_set_weight_coeff() %s result:obtdwc21 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.btcdcctl2_2.bit.obtdwc21, sentopCtrl->coeff[2][1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.btcdcctl2_2.bit.obtdwc30 != sentopCtrl->coeff[3][0]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_obt_set_weight_coeff() %s result:obtdwc30 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.btcdcctl2_2.bit.obtdwc30, sentopCtrl->coeff[3][0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.btcdcctl2_2.bit.obtdwc31 != sentopCtrl->coeff[3][1]) { 
        DriverCommon_DDIM_PRINT(("impro_sentop_obt_set_weight_coeff() %s result:obtdwc31 (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.obtcdcctl2.btcdcctl2_2.bit.obtdwc31, sentopCtrl->coeff[3][1]))
    }; 
}

void im_pro_1_0_print_8(ImPro10Print *self,const char* string, T_IM_PRO_SENTOP_LVDS_CTRL* sentopCtrl)
{
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.lvdsctl.bit.lvdsckpd != sentopCtrl->clockLanePowerdown) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_LVDS_Ctrl() %s result:lvdsckpd (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.lvdsctl.bit.lvdsckpd, sentopCtrl->clockLanePowerdown))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.lvdsctl.bit.lvdsdlpd != sentopCtrl->dataLanePowerdown) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_LVDS_Ctrl() %s result:lvdsdlpd (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.lvdsctl.bit.lvdsdlpd, sentopCtrl->dataLanePowerdown))
    }; 
}

void im_pro_1_0_print_9(ImPro10Print *self,const char* string, T_IM_PRO_SENTOP_SLVS_CTRL* sentopCtrl)
{
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.slvsecsel != sentopCtrl->linkMode) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SLVS_Ctrl() %s result:slvsecsel (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.slvsecsel, sentopCtrl->linkMode))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy0Rxpdck != sentopCtrl->phy0Rxpdck) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SLVS_Ctrl() %s result:phy0Rxpdck (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy0Rxpdck, sentopCtrl->phy0Rxpdck))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy1Rxpdck != sentopCtrl->phy1Rxpdck) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SLVS_Ctrl() %s result:phy1Rxpdck (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy1Rxpdck, sentopCtrl->phy1Rxpdck))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy2Rxpdck != sentopCtrl->phy2Rxpdck) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SLVS_Ctrl() %s result:phy2Rxpdck (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy2Rxpdck, sentopCtrl->phy2Rxpdck))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy3Rxpdck != sentopCtrl->phy3Rxpdck) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SLVS_Ctrl() %s result:phy3Rxpdck (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy3Rxpdck, sentopCtrl->phy3Rxpdck))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy0Rxpclk2aen != sentopCtrl->phy0Rxpclk2aen) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SLVS_Ctrl() %s result:phy0Rxpclk2aen (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy0Rxpclk2aen, sentopCtrl->phy0Rxpclk2aen))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy1Rxpclk2aen != sentopCtrl->phy1Rxpclk2aen) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SLVS_Ctrl() %s result:phy1Rxpclk2aen (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.slvsecctl.bit.phy1Rxpclk2aen, sentopCtrl->phy1Rxpclk2aen))
    }; 
}
#endif

ImPro10Print* im_pro_1_0_print_new(void)
{
	ImPro10Print* self = k_object_new_with_private(IM_TYPE_PRO_1_0_PRINT, sizeof(ImPro10PrintPrivate));

	return self;
}

ImPro10Print* im_pro_1_0_print_get(void)
{
	static ImPro10Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_1_0_PRINT, sizeof(ImPro10PrintPrivate));
	}

	return self;
}
