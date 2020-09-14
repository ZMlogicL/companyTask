/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro11Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro11print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImPro11Print, im_pro_1_1_print, ABS_TYPE_IM_PRO_PRINT)
#define IM_PRO_1_1_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImPro11PrintPrivate, IM_TYPE_PRO_1_1_PRINT))


struct _ImPro11PrintPrivate
{

};


/**
 *IMPL
 */
static void im_pro_1_1_print_constructor(ImPro11Print *self)
{
	ImPro11PrintPrivate *priv = IM_PRO_1_1_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void im_pro_1_1_print_destructor(ImPro11Print *self)
{
	ImPro11PrintPrivate *priv = IM_PRO_1_1_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_1_print_0(ImPro11Print *self,const char* string, T_IM_PRO_SENTOP_SG_CTRL* sentopCtrl)
{
    if(ioPro.sen.sentop.sgoutctl.bit.sgsel0 != sentopCtrl->sgIfOutputSel[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SG_Ctrl() %s result:sgsel0(%d) in(%d)\n", string, 
        ioPro.sen.sentop.sgoutctl.bit.sgsel0, sentopCtrl->sgIfOutputSel[0]))
    }; 
        
    if(ioPro.sen.sentop.sgoutctl.bit.sgsel1 != sentopCtrl->sgIfOutputSel[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SG_Ctrl() %s result:sgsel1(%d) in(%d)\n", string, 
        ioPro.sen.sentop.sgoutctl.bit.sgsel1, sentopCtrl->sgIfOutputSel[1]))
    }; 
        
    if(ioPro.sen.sentop.sgoutctl.bit.sgsel2 != sentopCtrl->sgIfOutputSel[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SG_Ctrl() %s result:sgsel2(%d) in(%d)\n", string, 
        ioPro.sen.sentop.sgoutctl.bit.sgsel2, sentopCtrl->sgIfOutputSel[2]))
    }; 
        
    if(ioPro.sen.sentop.sgoutctl.bit.sgsel3 != sentopCtrl->sgIfOutputSel[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SG_Ctrl() %s result:sgsel3(%d) in(%d)\n", string, 
        ioPro.sen.sentop.sgoutctl.bit.sgsel3, sentopCtrl->sgIfOutputSel[3]))
    }; 
}

void im_pro_1_1_print_1(ImPro11Print *self,const char* string, T_IM_PRO_SENTOP_CPHY_CTRL* cphyCtrl)
{
    if(ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyPregcnt != cphyCtrl->commonIfCtrl.pregcnt) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phyPregcnt (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyPregcnt, cphyCtrl->commonIfCtrl.pregcnt))
    }; 
        
    if(ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyFreqcnt != cphyCtrl->commonIfCtrl.freqcnt) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phyFreqcnt (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyFreqcnt, cphyCtrl->commonIfCtrl.freqcnt))
    }; 
        
    if(ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyPdccnt != cphyCtrl->commonIfCtrl.pdccnt) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phyPdccnt (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyPdccnt, cphyCtrl->commonIfCtrl.pdccnt))
    }; 
        
    if(ioPro.sen.sentop.phycifctl.phycifctl1.bit.phySetdf != cphyCtrl->commonIfCtrl.setdf) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phySetdf (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phycifctl.phycifctl1.bit.phySetdf, cphyCtrl->commonIfCtrl.setdf))
    }; 
        
    if(ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyPicodetst != cphyCtrl->commonIfCtrl.picodetst) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phyPicodetst (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phycifctl.phycifctl1.bit.phyPicodetst, cphyCtrl->commonIfCtrl.picodetst))
    }; 
        
    if(ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyPmonsel != cphyCtrl->commonIfCtrl.pmonsel) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phyPmonsel (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyPmonsel, cphyCtrl->commonIfCtrl.pmonsel))
    }; 
        
    if(ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyDmonsel != cphyCtrl->commonIfCtrl.dmonsel) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phyDmonsel (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyDmonsel, cphyCtrl->commonIfCtrl.dmonsel))
    }; 
        
    if(ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyCntsel != cphyCtrl->commonIfCtrl.cntsel) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phyCntsel (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyCntsel, cphyCtrl->commonIfCtrl.cntsel))
    }; 
        
    if(ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyMulgainf != cphyCtrl->commonIfCtrl.mulgainf) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phyMulgainf (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyMulgainf, cphyCtrl->commonIfCtrl.mulgainf))
    }; 
        
    if(ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyMulgainp != cphyCtrl->commonIfCtrl.mulgainp) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phyMulgainp (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phycifctl.phycifctl2.bit.phyMulgainp, cphyCtrl->commonIfCtrl.mulgainp))
    }; 
        
    if(ioPro.sen.sentop.phycifctl.phycifctl3.bit.phyCdrfunc != cphyCtrl->commonIfCtrl.cdrfunc) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phyCdrfunc (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phycifctl.phycifctl3.bit.phyCdrfunc, cphyCtrl->commonIfCtrl.cdrfunc))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop3uicp0 != cphyCtrl->cpmodeCtrl[0].zerop3uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop3uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop3uicp0, cphyCtrl->cpmodeCtrl[0].zerop3uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop4uicp0 != cphyCtrl->cpmodeCtrl[0].zerop4uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop4uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop4uicp0, cphyCtrl->cpmodeCtrl[0].zerop4uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop5uicp0 != cphyCtrl->cpmodeCtrl[0].zerop5uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop5uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop5uicp0, cphyCtrl->cpmodeCtrl[0].zerop5uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop6uicp0 != cphyCtrl->cpmodeCtrl[0].zerop6uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop6uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0Zerop6uicp0, cphyCtrl->cpmodeCtrl[0].zerop6uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0DetcntCp0 != cphyCtrl->cpmodeCtrl[0].detcntCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0DetcntCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0DetcntCp0, cphyCtrl->cpmodeCtrl[0].detcntCp0))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0EqEnCp0 != cphyCtrl->cpmodeCtrl[0].eqEnCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0EqEnCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0EqEnCp0, cphyCtrl->cpmodeCtrl[0].eqEnCp0))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0EqSetCp0 != cphyCtrl->cpmodeCtrl[0].eqSetCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0EqSetCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl1.bit.phy0EqSetCp0, cphyCtrl->cpmodeCtrl[0].eqSetCp0))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop3uicp1 != cphyCtrl->cpmodeCtrl[0].zerop3uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop3uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop3uicp1, cphyCtrl->cpmodeCtrl[0].zerop3uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop4uicp1 != cphyCtrl->cpmodeCtrl[0].zerop4uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop4uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop4uicp1, cphyCtrl->cpmodeCtrl[0].zerop4uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop5uicp1 != cphyCtrl->cpmodeCtrl[0].zerop5uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop5uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop5uicp1, cphyCtrl->cpmodeCtrl[0].zerop5uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop6uicp1 != cphyCtrl->cpmodeCtrl[0].zerop6uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop6uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0Zerop6uicp1, cphyCtrl->cpmodeCtrl[0].zerop6uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0DetcntCp1 != cphyCtrl->cpmodeCtrl[0].detcntCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0DetcntCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0DetcntCp1, cphyCtrl->cpmodeCtrl[0].detcntCp1))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0EqEnCp1 != cphyCtrl->cpmodeCtrl[0].eqEnCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0EqEnCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0EqEnCp1, cphyCtrl->cpmodeCtrl[0].eqEnCp1))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0EqSetCp1 != cphyCtrl->cpmodeCtrl[0].eqSetCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0EqSetCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl2.bit.phy0EqSetCp1, cphyCtrl->cpmodeCtrl[0].eqSetCp1))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop3uicp2 != cphyCtrl->cpmodeCtrl[0].zerop3uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop3uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop3uicp2, cphyCtrl->cpmodeCtrl[0].zerop3uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop4uicp2 != cphyCtrl->cpmodeCtrl[0].zerop4uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop4uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop4uicp2, cphyCtrl->cpmodeCtrl[0].zerop4uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop5uicp2 != cphyCtrl->cpmodeCtrl[0].zerop5uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop5uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop5uicp2, cphyCtrl->cpmodeCtrl[0].zerop5uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop6uicp2 != cphyCtrl->cpmodeCtrl[0].zerop6uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Zerop6uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0Zerop6uicp2, cphyCtrl->cpmodeCtrl[0].zerop6uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0DetcntCp2 != cphyCtrl->cpmodeCtrl[0].detcntCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0DetcntCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0DetcntCp2, cphyCtrl->cpmodeCtrl[0].detcntCp2))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0EqEnCp2 != cphyCtrl->cpmodeCtrl[0].eqEnCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0EqEnCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0EqEnCp2, cphyCtrl->cpmodeCtrl[0].eqEnCp2))
    }; 
        
    if(ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0EqSetCp2 != cphyCtrl->cpmodeCtrl[0].eqSetCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0EqSetCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0mdcpctl.phy0mdcpctl3.bit.phy0EqSetCp2, cphyCtrl->cpmodeCtrl[0].eqSetCp2))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop3uicp0 != cphyCtrl->cpmodeCtrl[1].zerop3uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop3uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop3uicp0, cphyCtrl->cpmodeCtrl[1].zerop3uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop4uicp0 != cphyCtrl->cpmodeCtrl[1].zerop4uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop4uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop4uicp0, cphyCtrl->cpmodeCtrl[1].zerop4uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop5uicp0 != cphyCtrl->cpmodeCtrl[1].zerop5uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop5uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop5uicp0, cphyCtrl->cpmodeCtrl[1].zerop5uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop6uicp0 != cphyCtrl->cpmodeCtrl[1].zerop6uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop6uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1Zerop6uicp0, cphyCtrl->cpmodeCtrl[1].zerop6uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1DetcntCp0 != cphyCtrl->cpmodeCtrl[1].detcntCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1DetcntCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1DetcntCp0, cphyCtrl->cpmodeCtrl[1].detcntCp0))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1EqEnCp0 != cphyCtrl->cpmodeCtrl[1].eqEnCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1EqEnCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1EqEnCp0, cphyCtrl->cpmodeCtrl[1].eqEnCp0))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1EqSetCp0 != cphyCtrl->cpmodeCtrl[1].eqSetCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1EqSetCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl1.bit.phy1EqSetCp0, cphyCtrl->cpmodeCtrl[1].eqSetCp0))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop3uicp1 != cphyCtrl->cpmodeCtrl[1].zerop3uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop3uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop3uicp1, cphyCtrl->cpmodeCtrl[1].zerop3uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop4uicp1 != cphyCtrl->cpmodeCtrl[1].zerop4uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop4uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop4uicp1, cphyCtrl->cpmodeCtrl[1].zerop4uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop5uicp1 != cphyCtrl->cpmodeCtrl[1].zerop5uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop5uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop5uicp1, cphyCtrl->cpmodeCtrl[1].zerop5uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop6uicp1 != cphyCtrl->cpmodeCtrl[1].zerop6uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop6uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1Zerop6uicp1, cphyCtrl->cpmodeCtrl[1].zerop6uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1DetcntCp1 != cphyCtrl->cpmodeCtrl[1].detcntCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1DetcntCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1DetcntCp1, cphyCtrl->cpmodeCtrl[1].detcntCp1))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1EqEnCp1 != cphyCtrl->cpmodeCtrl[1].eqEnCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1EqEnCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1EqEnCp1, cphyCtrl->cpmodeCtrl[1].eqEnCp1))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1EqSetCp1 != cphyCtrl->cpmodeCtrl[1].eqSetCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1EqSetCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl2.bit.phy1EqSetCp1, cphyCtrl->cpmodeCtrl[1].eqSetCp1))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop3uicp2 != cphyCtrl->cpmodeCtrl[1].zerop3uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop3uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop3uicp2, cphyCtrl->cpmodeCtrl[1].zerop3uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop4uicp2 != cphyCtrl->cpmodeCtrl[1].zerop4uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop4uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop4uicp2, cphyCtrl->cpmodeCtrl[1].zerop4uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop5uicp2 != cphyCtrl->cpmodeCtrl[1].zerop5uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop5uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop5uicp2, cphyCtrl->cpmodeCtrl[1].zerop5uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop6uicp2 != cphyCtrl->cpmodeCtrl[1].zerop6uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Zerop6uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1Zerop6uicp2, cphyCtrl->cpmodeCtrl[1].zerop6uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1DetcntCp2 != cphyCtrl->cpmodeCtrl[1].detcntCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1DetcntCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1DetcntCp2, cphyCtrl->cpmodeCtrl[1].detcntCp2))
    }; 
        
    if(ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1EqEnCp2 != cphyCtrl->cpmodeCtrl[1].eqEnCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1EqEnCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1mdcpctl.phy1mdcpctl3.bit.phy1EqEnCp2, cphyCtrl->cpmodeCtrl[1].eqEnCp2))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop3uicp0 != cphyCtrl->cpmodeCtrl[2].zerop3uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop3uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop3uicp0, cphyCtrl->cpmodeCtrl[2].zerop3uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop4uicp0 != cphyCtrl->cpmodeCtrl[2].zerop4uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop4uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop4uicp0, cphyCtrl->cpmodeCtrl[2].zerop4uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop5uicp0 != cphyCtrl->cpmodeCtrl[2].zerop5uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop5uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop5uicp0, cphyCtrl->cpmodeCtrl[2].zerop5uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop6uicp0 != cphyCtrl->cpmodeCtrl[2].zerop6uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop6uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2Zerop6uicp0, cphyCtrl->cpmodeCtrl[2].zerop6uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2DetcntCp0 != cphyCtrl->cpmodeCtrl[2].detcntCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2DetcntCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2DetcntCp0, cphyCtrl->cpmodeCtrl[2].detcntCp0))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2EqEnCp0 != cphyCtrl->cpmodeCtrl[2].eqEnCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2EqEnCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2EqEnCp0, cphyCtrl->cpmodeCtrl[2].eqEnCp0))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2EqSetCp0 != cphyCtrl->cpmodeCtrl[2].eqSetCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2EqSetCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl1.bit.phy2EqSetCp0, cphyCtrl->cpmodeCtrl[2].eqSetCp0))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop3uicp1 != cphyCtrl->cpmodeCtrl[2].zerop3uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop3uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop3uicp1, cphyCtrl->cpmodeCtrl[2].zerop3uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop4uicp1 != cphyCtrl->cpmodeCtrl[2].zerop4uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop4uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop4uicp1, cphyCtrl->cpmodeCtrl[2].zerop4uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop5uicp1 != cphyCtrl->cpmodeCtrl[2].zerop5uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop5uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop5uicp1, cphyCtrl->cpmodeCtrl[2].zerop5uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop6uicp1 != cphyCtrl->cpmodeCtrl[2].zerop6uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop6uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2Zerop6uicp1, cphyCtrl->cpmodeCtrl[2].zerop6uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2DetcntCp1 != cphyCtrl->cpmodeCtrl[2].detcntCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2DetcntCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2DetcntCp1, cphyCtrl->cpmodeCtrl[2].detcntCp1))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2EqEnCp1 != cphyCtrl->cpmodeCtrl[2].eqEnCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2EqEnCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2EqEnCp1, cphyCtrl->cpmodeCtrl[2].eqEnCp1))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2EqSetCp1 != cphyCtrl->cpmodeCtrl[2].eqSetCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2EqSetCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl2.bit.phy2EqSetCp1, cphyCtrl->cpmodeCtrl[2].eqSetCp1))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop3uicp2 != cphyCtrl->cpmodeCtrl[2].zerop3uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop3uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop3uicp2, cphyCtrl->cpmodeCtrl[2].zerop3uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop4uicp2 != cphyCtrl->cpmodeCtrl[2].zerop4uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop4uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop4uicp2, cphyCtrl->cpmodeCtrl[2].zerop4uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop5uicp2 != cphyCtrl->cpmodeCtrl[2].zerop5uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop5uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop5uicp2, cphyCtrl->cpmodeCtrl[2].zerop5uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop6uicp2 != cphyCtrl->cpmodeCtrl[2].zerop6uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Zerop6uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2Zerop6uicp2, cphyCtrl->cpmodeCtrl[2].zerop6uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2DetcntCp2 != cphyCtrl->cpmodeCtrl[2].detcntCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2DetcntCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2DetcntCp2, cphyCtrl->cpmodeCtrl[2].detcntCp2))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2EqEnCp2 != cphyCtrl->cpmodeCtrl[2].eqEnCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2EqEnCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2EqEnCp2, cphyCtrl->cpmodeCtrl[2].eqEnCp2))
    }; 
        
    if(ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2EqSetCp2 != cphyCtrl->cpmodeCtrl[2].eqSetCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2EqSetCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2mdcpctl.phy2mdcpctl3.bit.phy2EqSetCp2, cphyCtrl->cpmodeCtrl[2].eqSetCp2))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop3uicp0 != cphyCtrl->cpmodeCtrl[3].zerop3uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop3uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop3uicp0, cphyCtrl->cpmodeCtrl[3].zerop3uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop4uicp0 != cphyCtrl->cpmodeCtrl[3].zerop4uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop4uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop4uicp0, cphyCtrl->cpmodeCtrl[3].zerop4uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop5uicp0 != cphyCtrl->cpmodeCtrl[3].zerop5uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop5uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop5uicp0, cphyCtrl->cpmodeCtrl[3].zerop5uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop6uicp0 != cphyCtrl->cpmodeCtrl[3].zerop6uicp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop6uicp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3Zerop6uicp0, cphyCtrl->cpmodeCtrl[3].zerop6uicp0))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3DetcntCp0 != cphyCtrl->cpmodeCtrl[3].detcntCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3DetcntCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3DetcntCp0, cphyCtrl->cpmodeCtrl[3].detcntCp0))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3EqEnCp0 != cphyCtrl->cpmodeCtrl[3].eqEnCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3EqEnCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3EqEnCp0, cphyCtrl->cpmodeCtrl[3].eqEnCp0))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3EqSetCp0 != cphyCtrl->cpmodeCtrl[3].eqSetCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3EqSetCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl1.bit.phy3EqSetCp0, cphyCtrl->cpmodeCtrl[3].eqSetCp0))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop3uicp1 != cphyCtrl->cpmodeCtrl[3].zerop3uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop3uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop3uicp1, cphyCtrl->cpmodeCtrl[3].zerop3uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop4uicp1 != cphyCtrl->cpmodeCtrl[3].zerop4uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop4uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop4uicp1, cphyCtrl->cpmodeCtrl[3].zerop4uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop5uicp1 != cphyCtrl->cpmodeCtrl[3].zerop5uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop5uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop5uicp1, cphyCtrl->cpmodeCtrl[3].zerop5uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop6uicp1 != cphyCtrl->cpmodeCtrl[3].zerop6uicp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop6uicp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3Zerop6uicp1, cphyCtrl->cpmodeCtrl[3].zerop6uicp1))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3DetcntCp1 != cphyCtrl->cpmodeCtrl[3].detcntCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3DetcntCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3DetcntCp1, cphyCtrl->cpmodeCtrl[3].detcntCp1))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3EqEnCp1 != cphyCtrl->cpmodeCtrl[3].eqEnCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3EqEnCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3EqEnCp1, cphyCtrl->cpmodeCtrl[3].eqEnCp1))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3EqSetCp1 != cphyCtrl->cpmodeCtrl[3].eqSetCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3EqSetCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl2.bit.phy3EqSetCp1, cphyCtrl->cpmodeCtrl[3].eqSetCp1))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop3uicp2 != cphyCtrl->cpmodeCtrl[3].zerop3uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop3uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop3uicp2, cphyCtrl->cpmodeCtrl[3].zerop3uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop4uicp2 != cphyCtrl->cpmodeCtrl[3].zerop4uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop4uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop4uicp2, cphyCtrl->cpmodeCtrl[3].zerop4uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop5uicp2 != cphyCtrl->cpmodeCtrl[3].zerop5uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop5uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop5uicp2, cphyCtrl->cpmodeCtrl[3].zerop5uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop6uicp2 != cphyCtrl->cpmodeCtrl[3].zerop6uicp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Zerop6uicp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3Zerop6uicp2, cphyCtrl->cpmodeCtrl[3].zerop6uicp2))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3DetcntCp2 != cphyCtrl->cpmodeCtrl[3].detcntCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3DetcntCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3DetcntCp2, cphyCtrl->cpmodeCtrl[3].detcntCp2))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3EqEnCp2 != cphyCtrl->cpmodeCtrl[3].eqEnCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3EqEnCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3EqEnCp2, cphyCtrl->cpmodeCtrl[3].eqEnCp2))
    }; 
        
    if(ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3EqSetCp2 != cphyCtrl->cpmodeCtrl[3].eqSetCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3EqSetCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3mdcpctl.phy3mdcpctl3.bit.phy3EqSetCp2, cphyCtrl->cpmodeCtrl[3].eqSetCp2))
    }; 
        
    if(ioPro.sen.sentop.phy0dlctl.bit.phy0D0rxspeed != cphyCtrl->delayCtrl[0].d0rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0D0rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dlctl.bit.phy0D0rxspeed, cphyCtrl->delayCtrl[0].d0rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy0dlctl.bit.phy0D1rxspeed != cphyCtrl->delayCtrl[0].d1rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0D1rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dlctl.bit.phy0D1rxspeed, cphyCtrl->delayCtrl[0].d1rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy0dlctl.bit.phy0D2rxspeed != cphyCtrl->delayCtrl[0].d2rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0D2rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dlctl.bit.phy0D2rxspeed, cphyCtrl->delayCtrl[0].d2rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy0dlctl.bit.phy0D3rxspeed != cphyCtrl->delayCtrl[0].d3rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0D3rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dlctl.bit.phy0D3rxspeed, cphyCtrl->delayCtrl[0].d3rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy0dlctl.bit.phy0SkwselCp0 != cphyCtrl->delayCtrl[0].skwselCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0SkwselCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dlctl.bit.phy0SkwselCp0, cphyCtrl->delayCtrl[0].skwselCp0))
    }; 
        
    if(ioPro.sen.sentop.phy0dlctl.bit.phy0SkwselCp1 != cphyCtrl->delayCtrl[0].skwselCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0SkwselCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dlctl.bit.phy0SkwselCp1, cphyCtrl->delayCtrl[0].skwselCp1))
    }; 
        
    if(ioPro.sen.sentop.phy0dlctl.bit.phy0SkwselCp2 != cphyCtrl->delayCtrl[0].skwselCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0SkwselCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dlctl.bit.phy0SkwselCp2, cphyCtrl->delayCtrl[0].skwselCp2))
    }; 
        
    if(ioPro.sen.sentop.phy1dlctl.bit.phy1D0rxspeed != cphyCtrl->delayCtrl[1].d0rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1D0rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dlctl.bit.phy1D0rxspeed, cphyCtrl->delayCtrl[1].d0rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy1dlctl.bit.phy1D1rxspeed != cphyCtrl->delayCtrl[1].d1rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1D1rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dlctl.bit.phy1D1rxspeed, cphyCtrl->delayCtrl[1].d1rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy1dlctl.bit.phy1D2rxspeed != cphyCtrl->delayCtrl[1].d2rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1D2rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dlctl.bit.phy1D2rxspeed, cphyCtrl->delayCtrl[1].d2rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy1dlctl.bit.phy1D3rxspeed != cphyCtrl->delayCtrl[1].d3rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1D3rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dlctl.bit.phy1D3rxspeed, cphyCtrl->delayCtrl[1].d3rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy1dlctl.bit.phy1SkwselCp0 != cphyCtrl->delayCtrl[1].skwselCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1SkwselCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dlctl.bit.phy1SkwselCp0, cphyCtrl->delayCtrl[1].skwselCp0))
    }; 
        
    if(ioPro.sen.sentop.phy1dlctl.bit.phy1SkwselCp1 != cphyCtrl->delayCtrl[1].skwselCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1SkwselCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dlctl.bit.phy1SkwselCp1, cphyCtrl->delayCtrl[1].skwselCp1))
    }; 
        
    if(ioPro.sen.sentop.phy1dlctl.bit.phy1SkwselCp2 != cphyCtrl->delayCtrl[1].skwselCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1SkwselCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dlctl.bit.phy1SkwselCp2, cphyCtrl->delayCtrl[1].skwselCp2))
    }; 
        
    if(ioPro.sen.sentop.phy2dlctl.bit.phy2D0rxspeed != cphyCtrl->delayCtrl[2].d0rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2D0rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dlctl.bit.phy2D0rxspeed, cphyCtrl->delayCtrl[2].d0rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy2dlctl.bit.phy2D1rxspeed != cphyCtrl->delayCtrl[2].d1rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2D1rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dlctl.bit.phy2D1rxspeed, cphyCtrl->delayCtrl[2].d1rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy2dlctl.bit.phy2D2rxspeed != cphyCtrl->delayCtrl[2].d2rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2D2rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dlctl.bit.phy2D2rxspeed, cphyCtrl->delayCtrl[2].d2rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy2dlctl.bit.phy2D3rxspeed != cphyCtrl->delayCtrl[2].d3rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2D3rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dlctl.bit.phy2D3rxspeed, cphyCtrl->delayCtrl[2].d3rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy2dlctl.bit.phy2SkwselCp0 != cphyCtrl->delayCtrl[2].skwselCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2SkwselCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dlctl.bit.phy2SkwselCp0, cphyCtrl->delayCtrl[2].skwselCp0))
    }; 
        
    if(ioPro.sen.sentop.phy2dlctl.bit.phy2SkwselCp1 != cphyCtrl->delayCtrl[2].skwselCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2SkwselCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dlctl.bit.phy2SkwselCp1, cphyCtrl->delayCtrl[2].skwselCp1))
    }; 
        
    if(ioPro.sen.sentop.phy2dlctl.bit.phy2SkwselCp2 != cphyCtrl->delayCtrl[2].skwselCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2SkwselCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dlctl.bit.phy2SkwselCp2, cphyCtrl->delayCtrl[2].skwselCp2))
    }; 
        
    if(ioPro.sen.sentop.phy3dlctl.bit.phy3D0rxspeed != cphyCtrl->delayCtrl[3].d0rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3D0rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dlctl.bit.phy3D0rxspeed, cphyCtrl->delayCtrl[3].d0rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy3dlctl.bit.phy3D1rxspeed != cphyCtrl->delayCtrl[3].d1rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3D1rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dlctl.bit.phy3D1rxspeed, cphyCtrl->delayCtrl[3].d1rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy3dlctl.bit.phy3D2rxspeed != cphyCtrl->delayCtrl[3].d2rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3D2rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dlctl.bit.phy3D2rxspeed, cphyCtrl->delayCtrl[3].d2rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy3dlctl.bit.phy3D3rxspeed != cphyCtrl->delayCtrl[3].d3rxspeed) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3D3rxspeed (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dlctl.bit.phy3D3rxspeed, cphyCtrl->delayCtrl[3].d3rxspeed))
    }; 
        
    if(ioPro.sen.sentop.phy3dlctl.bit.phy3SkwselCp0 != cphyCtrl->delayCtrl[3].skwselCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3SkwselCp0 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dlctl.bit.phy3SkwselCp0, cphyCtrl->delayCtrl[3].skwselCp0))
    }; 
        
    if(ioPro.sen.sentop.phy3dlctl.bit.phy3SkwselCp1 != cphyCtrl->delayCtrl[3].skwselCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3SkwselCp1 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dlctl.bit.phy3SkwselCp1, cphyCtrl->delayCtrl[3].skwselCp1))
    }; 
        
    if(ioPro.sen.sentop.phy3dlctl.bit.phy3SkwselCp2 != cphyCtrl->delayCtrl[3].skwselCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3SkwselCp2 (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dlctl.bit.phy3SkwselCp2, cphyCtrl->delayCtrl[3].skwselCp2))
    }; 
        
    if(ioPro.sen.sentop.phy0dskctl.bit.phy0Rxspden != cphyCtrl->desknewCtrl[0].rxspden) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Rxspden (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dskctl.bit.phy0Rxspden, cphyCtrl->desknewCtrl[0].rxspden))
    }; 
        
    if(ioPro.sen.sentop.phy0dskctl.bit.phy0Dcntnum != cphyCtrl->desknewCtrl[0].dcntnum) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Dcntnum (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dskctl.bit.phy0Dcntnum, cphyCtrl->desknewCtrl[0].dcntnum))
    }; 
        
    if(ioPro.sen.sentop.phy0dskctl.bit.phy0Grdwidth != cphyCtrl->desknewCtrl[0].grdwidth) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Grdwidth (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dskctl.bit.phy0Grdwidth, cphyCtrl->desknewCtrl[0].grdwidth))
    }; 
        
    if(ioPro.sen.sentop.phy0dskctl.bit.PHY0_RDWAIT != cphyCtrl->desknewCtrl[0].rdwait) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:PHY0_RDWAIT (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dskctl.bit.PHY0_RDWAIT, cphyCtrl->desknewCtrl[0].rdwait))
    }; 
        
    if(ioPro.sen.sentop.phy0dskctl.bit.phy0Vldprd != cphyCtrl->desknewCtrl[0].vldprd) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy0Vldprd (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy0dskctl.bit.phy0Vldprd, cphyCtrl->desknewCtrl[0].vldprd))
    }; 
        
    if(ioPro.sen.sentop.phy1dskctl.bit.phy1Rxspden != cphyCtrl->desknewCtrl[1].rxspden) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Rxspden (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dskctl.bit.phy1Rxspden, cphyCtrl->desknewCtrl[1].rxspden))
    }; 
        
    if(ioPro.sen.sentop.phy1dskctl.bit.phy1Dcntnum != cphyCtrl->desknewCtrl[1].dcntnum) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Dcntnum (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dskctl.bit.phy1Dcntnum, cphyCtrl->desknewCtrl[1].dcntnum))
    }; 
        
    if(ioPro.sen.sentop.phy1dskctl.bit.phy1Grdwidth != cphyCtrl->desknewCtrl[1].grdwidth) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Grdwidth (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dskctl.bit.phy1Grdwidth, cphyCtrl->desknewCtrl[1].grdwidth))
    }; 
        
    if(ioPro.sen.sentop.phy1dskctl.bit.phy1Rdwait != cphyCtrl->desknewCtrl[1].rdwait) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Rdwait (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dskctl.bit.phy1Rdwait, cphyCtrl->desknewCtrl[1].rdwait))
    }; 
        
    if(ioPro.sen.sentop.phy1dskctl.bit.phy1Vldprd != cphyCtrl->desknewCtrl[1].vldprd) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy1Vldprd (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy1dskctl.bit.phy1Vldprd, cphyCtrl->desknewCtrl[1].vldprd))
    }; 
        
    if(ioPro.sen.sentop.phy2dskctl.bit.phy2Rxspden != cphyCtrl->desknewCtrl[2].rxspden) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Rxspden (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dskctl.bit.phy2Rxspden, cphyCtrl->desknewCtrl[2].rxspden))
    }; 
        
    if(ioPro.sen.sentop.phy2dskctl.bit.phy2Dcntnum != cphyCtrl->desknewCtrl[2].dcntnum) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Dcntnum (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dskctl.bit.phy2Dcntnum, cphyCtrl->desknewCtrl[2].dcntnum))
    }; 
        
    if(ioPro.sen.sentop.phy2dskctl.bit.phy2Grdwidth != cphyCtrl->desknewCtrl[2].grdwidth) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Grdwidth (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dskctl.bit.phy2Grdwidth, cphyCtrl->desknewCtrl[2].grdwidth))
    }; 
        
    if(ioPro.sen.sentop.phy2dskctl.bit.phy2Rdwait != cphyCtrl->desknewCtrl[2].rdwait) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Rdwait (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dskctl.bit.phy2Rdwait, cphyCtrl->desknewCtrl[2].rdwait))
    }; 
        
    if(ioPro.sen.sentop.phy2dskctl.bit.phy2Vldprd != cphyCtrl->desknewCtrl[2].vldprd) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy2Vldprd (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy2dskctl.bit.phy2Vldprd, cphyCtrl->desknewCtrl[2].vldprd))
    }; 
        
    if(ioPro.sen.sentop.phy3dskctl.bit.phy3Rxspden != cphyCtrl->desknewCtrl[3].rxspden) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Rxspden (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dskctl.bit.phy3Rxspden, cphyCtrl->desknewCtrl[3].rxspden))
    }; 
        
    if(ioPro.sen.sentop.phy3dskctl.bit.phy3Dcntnum != cphyCtrl->desknewCtrl[3].dcntnum) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Dcntnum (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dskctl.bit.phy3Dcntnum, cphyCtrl->desknewCtrl[3].dcntnum))
    }; 
        
    if(ioPro.sen.sentop.phy3dskctl.bit.phy3Grdwidth != cphyCtrl->desknewCtrl[3].grdwidth) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Grdwidth (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dskctl.bit.phy3Grdwidth, cphyCtrl->desknewCtrl[3].grdwidth))
    }; 
        
    if(ioPro.sen.sentop.phy3dskctl.bit.phy3Rdwait != cphyCtrl->desknewCtrl[3].rdwait) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Rdwait (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dskctl.bit.phy3Rdwait, cphyCtrl->desknewCtrl[3].rdwait))
    }; 
        
    if(ioPro.sen.sentop.phy3dskctl.bit.phy3Vldprd != cphyCtrl->desknewCtrl[3].vldprd) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:phy3Vldprd (%d) in(%d)\n", string, 
        ioPro.sen.sentop.phy3dskctl.bit.phy3Vldprd, cphyCtrl->desknewCtrl[3].vldprd))
    }; 
        
    if(ioPro.sen.sentop.pll0ctl.bit.pll0Ibcnt != cphyCtrl->pll0Ctrl.ibcnt) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:pll0Ibcnt (%d) in(%d)\n", string, 
        ioPro.sen.sentop.pll0ctl.bit.pll0Ibcnt, cphyCtrl->pll0Ctrl.ibcnt))
    }; 
        
    if(ioPro.sen.sentop.pll0ctl.bit.pll0Ilfsel != cphyCtrl->pll0Ctrl.ilfsel) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:pll0Ilfsel (%d) in(%d)\n", string, 
        ioPro.sen.sentop.pll0ctl.bit.pll0Ilfsel, cphyCtrl->pll0Ctrl.ilfsel))
    }; 
        
    if(ioPro.sen.sentop.pll0ctl.bit.pll0Ioclken != cphyCtrl->pll0Ctrl.ioclken) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:pll0Ioclken (%d) in(%d)\n", string, 
        ioPro.sen.sentop.pll0ctl.bit.pll0Ioclken, cphyCtrl->pll0Ctrl.ioclken))
    }; 
        
    if(ioPro.sen.sentop.pll0ctl.bit.pll0Itxpclk2aen != cphyCtrl->pll0Ctrl.itxpclk2aen) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() %s result:pll0Itxpclk2aen (%d) in(%d)\n", string, 
        ioPro.sen.sentop.pll0ctl.bit.pll0Itxpclk2aen, cphyCtrl->pll0Ctrl.itxpclk2aen))
    }; 
}

void im_pro_1_1_print_2(ImPro11Print *self,const char* string, T_IM_PRO_SENTOP_CPHY_DESKNEW_MONITOR* cphyMoni)
{
    if(cphyMoni->desknewMoni[0].dtypemon0 != ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy0Dtypemon0 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[0].dtypemon0, ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon0))
    }; 
        
    if(cphyMoni->desknewMoni[0].dtypemon1 != ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy0Dtypemon1 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[0].dtypemon1, ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon1))
    }; 
        
    if(cphyMoni->desknewMoni[0].dtypemon2 != ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy0Dtypemon2 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[0].dtypemon2, ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon2))
    }; 
        
    if(cphyMoni->desknewMoni[0].dtypemon3 != ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon3) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy0Dtypemon3 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[0].dtypemon3, ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Dtypemon3))
    }; 
        
    if(cphyMoni->desknewMoni[0].vldwindow0 != ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Vldwindow0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy0Vldwindow0 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[0].vldwindow0, ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Vldwindow0))
    }; 
        
    if(cphyMoni->desknewMoni[0].vldwindow1 != ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Vldwindow1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy0Vldwindow1 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[0].vldwindow1, ioPro.sen.sentop.phy0dskmoni.phy0dskmoni1.bit.phy0Vldwindow1))
    }; 
        
    if(cphyMoni->desknewMoni[0].vldwindow2 != ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.bit.phy0Vldwindow2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy0Vldwindow2 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[0].vldwindow2, ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.bit.phy0Vldwindow2))
    }; 
        
    if(cphyMoni->desknewMoni[0].vldwindow3 != ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.bit.phy0Vldwindow3) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy0Vldwindow3 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[0].vldwindow3, ioPro.sen.sentop.phy0dskmoni.phy0dskmoni2.bit.phy0Vldwindow3))
    }; 
        
    if(cphyMoni->desknewMoni[1].dtypemon0 != ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1typemon0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy1typemon0 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[1].dtypemon0, ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1typemon0))
    }; 
        
    if(cphyMoni->desknewMoni[1].dtypemon1 != ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy1Dtypemon1 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[1].dtypemon1, ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon1))
    }; 
        
    if(cphyMoni->desknewMoni[1].dtypemon2 != ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy1Dtypemon2 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[1].dtypemon2, ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon2))
    }; 
        
    if(cphyMoni->desknewMoni[1].dtypemon3 != ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon3) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy1Dtypemon3 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[1].dtypemon3, ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Dtypemon3))
    }; 
        
    if(cphyMoni->desknewMoni[1].vldwindow0 != ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Vldwindow0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy1Vldwindow0 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[1].vldwindow0, ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Vldwindow0))
    }; 
        
    if(cphyMoni->desknewMoni[1].vldwindow1 != ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Vldwindow1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy1Vldwindow1 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[1].vldwindow1, ioPro.sen.sentop.phy1dskmoni.phy1dskmoni1.bit.phy1Vldwindow1))
    }; 
        
    if(cphyMoni->desknewMoni[1].vldwindow2 != ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.bit.phy1Vldwindow2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy1Vldwindow2 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[1].vldwindow2, ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.bit.phy1Vldwindow2))
    }; 
        
    if(cphyMoni->desknewMoni[1].vldwindow3 != ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.bit.phy1Vldwindow3) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy1Vldwindow3 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[1].vldwindow3, ioPro.sen.sentop.phy1dskmoni.phy1dskmoni2.bit.phy1Vldwindow3))
    }; 
        
    if(cphyMoni->desknewMoni[2].dtypemon0 != ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2typemon0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy2typemon0 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[2].dtypemon0, ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2typemon0))
    }; 
        
    if(cphyMoni->desknewMoni[2].dtypemon1 != ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy2Dtypemon1 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[2].dtypemon1, ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon1))
    }; 
        
    if(cphyMoni->desknewMoni[2].dtypemon2 != ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy2Dtypemon2 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[2].dtypemon2, ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon2))
    }; 
        
    if(cphyMoni->desknewMoni[2].dtypemon3 != ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon3) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy2Dtypemon3 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[2].dtypemon3, ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Dtypemon3))
    }; 
        
    if(cphyMoni->desknewMoni[2].vldwindow0 != ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Vldwindow0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy2Vldwindow0 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[2].vldwindow0, ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Vldwindow0))
    }; 
        
    if(cphyMoni->desknewMoni[2].vldwindow1 != ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Vldwindow1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy2Vldwindow1 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[2].vldwindow1, ioPro.sen.sentop.phy2dskmoni.phy2dskmoni1.bit.phy2Vldwindow1))
    }; 
        
    if(cphyMoni->desknewMoni[2].vldwindow2 != ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.bit.phy2Vldwindow2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy2Vldwindow2 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[2].vldwindow2, ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.bit.phy2Vldwindow2))
    }; 
        
    if(cphyMoni->desknewMoni[2].vldwindow3 != ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.bit.phy2Vldwindow3) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DesKnew_Monitor() %s result:phy2Vldwindow3 (%d) reg_val (%d)\n", 
        string, cphyMoni->desknewMoni[2].vldwindow3, ioPro.sen.sentop.phy2dskmoni.phy2dskmoni2.bit.phy2Vldwindow3))
    }; 
}

void im_pro_1_1_print_3(ImPro11Print *self,const char* string)
{
    if(ioPro.sen.sg[0].sgtrg.bit.sgtrg != D_IM_PRO_TRG_STATUS_RUNNING) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_start() %s result:sgtrg ch0 (%d)\n", string, 
        ioPro.sen.sg[0].sgtrg.bit.sgtrg))
    }; 
        
    if(ioPro.sen.sg[1].sgtrg.bit.sgtrg != D_IM_PRO_TRG_STATUS_RUNNING) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_start() %s result:sgtrg ch1 (%d)\n", string, 
        ioPro.sen.sg[1].sgtrg.bit.sgtrg))
    }; 
        
    if(ioPro.sen.sg[2].sgtrg.bit.sgtrg != D_IM_PRO_TRG_STATUS_RUNNING) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_start() %s result:sgtrg ch2 (%d)\n", string, 
        ioPro.sen.sg[2].sgtrg.bit.sgtrg))
    }; 
        
    if(ioPro.sen.sg[3].sgtrg.bit.sgtrg != D_IM_PRO_TRG_STATUS_RUNNING) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_start() %s result:sgtrg ch3 (%d)\n", string, 
        ioPro.sen.sg[3].sgtrg.bit.sgtrg))
    }; 
}

void im_pro_1_1_print_4(ImPro11Print *self,const char* string, kuchar force)
{
    if(ioPro.sen.sg[0].sgtrg.bit.sgtrg != D_IM_PRO_TRG_STATUS_STOPPED) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Stop(%u) %s result:sgtrg ch0 (%d)\n", 
        force, string, ioPro.sen.sg[0].sgtrg.bit.sgtrg))
    }; 
        
    if(ioPro.sen.sg[1].sgtrg.bit.sgtrg != D_IM_PRO_TRG_STATUS_STOPPED) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Stop(%u) %s result:sgtrg ch1 (%d)\n", 
        force, string, ioPro.sen.sg[1].sgtrg.bit.sgtrg))
    }; 
        
    if(ioPro.sen.sg[2].sgtrg.bit.sgtrg != D_IM_PRO_TRG_STATUS_STOPPED) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Stop(%u) %s result:sgtrg ch2 (%d)\n", 
        force, string, ioPro.sen.sg[2].sgtrg.bit.sgtrg))
    }; 
        
    if(ioPro.sen.sg[3].sgtrg.bit.sgtrg != D_IM_PRO_TRG_STATUS_STOPPED) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Stop(%u) %s result:sgtrg ch3 (%d)\n", 
        force, string, ioPro.sen.sg[3].sgtrg.bit.sgtrg))
    }; 
}

void im_pro_1_1_print_5(ImPro11Print *self,const char* string, E_IM_PRO_SG_CH ch, TImProSgCtrl* sgCtrl)
{
    if(ioPro.sen.sg[ch].sgctl1.bit.vhdo != sgCtrl->vhdo) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:vhdo (%d) in(%d)\n", 
        ch, string, ioPro.sen.sg[ch].sgctl1.bit.vhdo, sgCtrl->vhdo))
    }; 
        
    if(ioPro.sen.sg[ch].sgctl1.bit.vdot != sgCtrl->vdot) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:vdot (%d) in(%d)\n", 
        ch, string, ioPro.sen.sg[ch].sgctl1.bit.vdot, sgCtrl->vdot))
    }; 
        
    if(ioPro.sen.sg[ch].sgctl1.bit.vdinv != sgCtrl->vdinv) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:vdinv (%d) in(%d)\n", 
        ch, string, ioPro.sen.sg[ch].sgctl1.bit.vdinv, sgCtrl->vdinv))
    }; 
        
    if(ioPro.sen.sg[ch].sgctl1.bit.hdinv != sgCtrl->hdinv) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:hdinv (%d) in(%d)\n", 
        ch, string, ioPro.sen.sg[ch].sgctl1.bit.hdinv, sgCtrl->hdinv))
    }; 
        
    if(ioPro.sen.sg[ch].sgctl2.bit.hdchg != sgCtrl->hdchg) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:hdchg (%d) in(%d)\n", 
        ch, string, ioPro.sen.sg[ch].sgctl2.bit.hdchg, sgCtrl->hdchg))
    }; 
        
    if(ioPro.sen.sg[ch].sgctl2.bit.vddly != sgCtrl->vddly) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:vddly (%d) in(%d)\n", 
        ch, string, ioPro.sen.sg[ch].sgctl2.bit.vddly, sgCtrl->vddly))
    }; 
        
    if(ioPro.sen.sg[ch].vdocyc.bit.vdocyc != sgCtrl->vdocyc) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:vdocyc (%d) in(%lu)\n", 
        ch, string, ioPro.sen.sg[ch].vdocyc.bit.vdocyc, sgCtrl->vdocyc))
    }; 
        
    if(ioPro.sen.sg[ch].vdow.bit.vdow != sgCtrl->vdow) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:vdow (%d) in(%d)\n", 
        ch, string, ioPro.sen.sg[ch].vdow.bit.vdow, sgCtrl->vdow))
    }; 
        
    if(ioPro.sen.sg[ch].hdocyc.bit.hdocyc != sgCtrl->hdocyc) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:hdocyc (%d) in(%d)\n", 
        ch, string, ioPro.sen.sg[ch].hdocyc.bit.hdocyc, sgCtrl->hdocyc))
    }; 
        
    if(ioPro.sen.sg[ch].hdow.bit.hdow != sgCtrl->hdow) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:hdow (%d) in(%d)\n", 
        ch, string, ioPro.sen.sg[ch].hdow.bit.hdow, sgCtrl->hdow))
    }; 
        
    if(ioPro.sen.sg[ch].hdocyc2.bit.hdocyc2 != sgCtrl->hdocyc2) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:hdocyc2 (%d) in(%d)\n", 
        ch, string, ioPro.sen.sg[ch].hdocyc2.bit.hdocyc2, sgCtrl->hdocyc2))
    }; 
        
    if(ioPro.sen.sg[ch].hdow2.bit.hdow2 != sgCtrl->hdow2) { 
        DriverCommon_DDIM_PRINT(("impro_sensg_ctrl(%u) %s result:hdow2 (%d) in(%d)\n", 
        ch, string, ioPro.sen.sg[ch].hdow2.bit.hdow2, sgCtrl->hdow2))
    }; 
}      

void im_pro_1_1_print_6(ImPro11Print *self,const char* string, E_IM_PRO_SG_CH ch, TImProSgCtrl* sgCtrl)
{
    if(sgCtrl->vhdo !=  ioPro.sen.sg[ch].sgctl1.bit.vhdo) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:vhdo (%d) reg_val (%d)\n", 
        string, sgCtrl->vhdo, ioPro.sen.sg[ch].sgctl1.bit.vhdo))
    }; 
        
    if(sgCtrl->vdot !=  ioPro.sen.sg[ch].sgctl1.bit.vdot) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:vdot (%d) reg_val (%d)\n", 
        string, sgCtrl->vdot, ioPro.sen.sg[ch].sgctl1.bit.vdot))
    }; 
        
    if(sgCtrl->vdinv !=  ioPro.sen.sg[ch].sgctl1.bit.vdinv) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:vdinv (%d) reg_val (%d)\n", 
        string, sgCtrl->vdinv, ioPro.sen.sg[ch].sgctl1.bit.vdinv))
    }; 
        
    if(sgCtrl->hdinv !=  ioPro.sen.sg[ch].sgctl1.bit.hdinv) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:hdinv (%d) reg_val (%d)\n", 
        string, sgCtrl->hdinv, ioPro.sen.sg[ch].sgctl1.bit.hdinv))
    }; 
        
    if(sgCtrl->hdchg !=  ioPro.sen.sg[ch].sgctl2.bit.hdchg) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:hdchg (%d) reg_val (%d)\n", 
        string, sgCtrl->hdchg, ioPro.sen.sg[ch].sgctl2.bit.hdchg))
    }; 
        
    if(sgCtrl->vddly !=  ioPro.sen.sg[ch].sgctl2.bit.vddly) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:vddly (%d) reg_val (%d)\n", 
        string, sgCtrl->vddly, ioPro.sen.sg[ch].sgctl2.bit.vddly))
    }; 
        
    if(sgCtrl->vdocyc !=  ioPro.sen.sg[ch].vdocyc.bit.vdocyc) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:vdocyc (%lu)reg_val (%d)\n", 
        string, sgCtrl->vdocyc, ioPro.sen.sg[ch].vdocyc.bit.vdocyc))
    }; 
        
    if(sgCtrl->vdow !=  ioPro.sen.sg[ch].vdow.bit.vdow) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:vdow (%d) reg_val (%d)\n", 
        string, sgCtrl->vdow, ioPro.sen.sg[ch].vdow.bit.vdow))
    }; 
        
    if(sgCtrl->hdocyc !=  ioPro.sen.sg[ch].hdocyc.bit.hdocyc) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:hdocyc (%d) reg_val (%d)\n", 
        string, sgCtrl->hdocyc, ioPro.sen.sg[ch].hdocyc.bit.hdocyc))
    }; 
        
    if(sgCtrl->hdow !=  ioPro.sen.sg[ch].hdow.bit.hdow) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:hdow (%d) reg_val (%d)\n", 
        string, sgCtrl->hdow, ioPro.sen.sg[ch].hdow.bit.hdow))
    }; 
        
    if(sgCtrl->hdocyc2!=  ioPro.sen.sg[ch].hdocyc2.bit.hdocyc2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:hdocyc2 (%d) reg_val (%d)\n", 
        string, sgCtrl->hdocyc2, ioPro.sen.sg[ch].hdocyc2.bit.hdocyc2))
    }; 
        
    if(sgCtrl->hdow2 !=  ioPro.sen.sg[ch].hdow2.bit.hdow2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Cycle() %s result:hdow2 (%d) reg_val (%d)\n", 
        string, sgCtrl->hdow2, ioPro.sen.sg[ch].hdow2.bit.hdow2))
    }; 
}

void im_pro_1_1_print_7(ImPro11Print *self,const char* string, E_IM_PRO_SG_CH ch, T_IM_PRO_SG_MONI_INFO* sgMoniInfo)
{
    if(sgMoniInfo->inputVdSignal != ioPro.sen.sg[ch].vdhdmon.bit.vdin) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Monitor_Info() %s result:VDINO (%d) reg_val (%d)\n", 
        string, sgMoniInfo->inputVdSignal, ioPro.sen.sg[ch].vdhdmon.bit.vdin))
    }; 
        
    if(sgMoniInfo->inputHdSignal != ioPro.sen.sg[ch].vdhdmon.bit.hdin) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SG_Get_Monitor_Info() %s result:HDINO (%d) reg_val (%d)\n", 
        string, sgMoniInfo->inputHdSignal, ioPro.sen.sg[ch].vdhdmon.bit.hdin))
    }; 
}

void im_pro_1_1_print_8(ImPro11Print *self,const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType)
{
    DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_SR(%u) %s result:upda (%d)\n", 
        streamType, string, ioPro.sen.slvsec.common.sr.bit.upda)); 
    DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_SR(%u) %s result:inita (%d)\n", 
        streamType, string, ioPro.sen.slvsec.common.sr.bit.inita)); 
    DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_SR(%u) %s result:updb (%d)\n", 
        streamType, string, ioPro.sen.slvsec.common.sr.bit.updb)); 
    DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_SR(%u) %s result:initb (%d)\n", 
        streamType, string, ioPro.sen.slvsec.common.sr.bit.initb)); 
}

void im_pro_1_1_print_9(ImPro11Print *self,const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType)
{
    DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Update_Cfg(%u) %s result:upda (%d)\n", 
        streamType, string, ioPro.sen.slvsec.common.sr.bit.upda)); 
    DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Update_Cfg(%u) %s result:inita (%d)\n", 
        streamType, string, ioPro.sen.slvsec.common.sr.bit.inita)); 
    DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Update_Cfg(%u) %s result:updb (%d)\n", 
        streamType, string, ioPro.sen.slvsec.common.sr.bit.updb)); 
    DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Update_Cfg(%u) %s result:initb (%d)\n", 
        streamType, string, ioPro.sen.slvsec.common.sr.bit.initb)); 
}
#endif

ImPro11Print* im_pro_1_1_print_new(void)
{
	ImPro11Print* self = k_object_new_with_private(IM_TYPE_PRO_1_1_PRINT, sizeof(ImPro11PrintPrivate));

	return self;
}

ImPro11Print* im_pro_1_1_print_get(void)
{
	static ImPro11Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_1_1_PRINT, sizeof(ImPro11PrintPrivate));
	}

	return self;
}
