/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro16Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro16print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImPro16Print, im_pro_1_6_print, ABS_TYPE_IM_PRO_PRINT)
#define IM_PRO_1_6_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImPro16PrintPrivate, IM_TYPE_PRO_1_6_PRINT))


struct _ImPro16PrintPrivate
{


};


/**
 *IMPL 
 */
static void im_pro_1_6_print_constructor(ImPro16Print *self)
{
	ImPro16PrintPrivate *priv = IM_PRO_1_6_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void im_pro_1_6_print_destructor(ImPro16Print *self)
{
	ImPro16PrintPrivate *priv = IM_PRO_1_6_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *PUBLIC 
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_6_print_0(ImPro16Print *self,const char* string, kuchar ch, kuchar paenTrg0, kuchar paenTrg1)
{
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpaen0.bit.paen0 != paenTrg0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Set_PAEN(%u) %s result:paen0(%d) mpictrg(%d) paenTrg0(%d) paenTrg1(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpaen0.bit.paen0, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpictrg.bit.mpictrg, 
        paenTrg0, paenTrg1))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpaen1.bit.paen1 != paenTrg1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Set_PAEN(%u) %s result:paen1(%d) mpictrg(%d) paenTrg0(%d) paenTrg1(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpaen1.bit.paen1, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpictrg.bit.mpictrg, 
        paenTrg0, paenTrg1))
    };  
}

void im_pro_1_6_print_1(ImPro16Print *self,const char* string, kuchar ch, T_IM_PRO_CMIPI_STATUS* status)
{
    if(status->rxstopstateL0 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpvr.bit.ssl0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:ssl0 (%d) reg_val (%u)\n", 
        ch, string, status->rxstopstateL0, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpvr.bit.ssl0))
    };  
        
    if(status->rxstopstateL1 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpvr.bit.ssl1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:ssl1 (%d) reg_val (%u)\n", 
        ch, string, status->rxstopstateL1, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpvr.bit.ssl1))
    };  
        
    if(status->rxstopstateL2 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpvr.bit.ssl2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:ssl2 (%d) reg_val (%u)\n", 
        ch, string, status->rxstopstateL2, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpvr.bit.ssl2))
    };  
        
    if(status->lstatus0 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrLstatus0 (%d) reg_val (%u)\n", 
        ch, string, status->lstatus0, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus0))
    };  
        
    if(status->lstatus1 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrLstatus1 (%d) reg_val (%u)\n", 
        ch, string, status->lstatus1, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus1))
    };  
        
    if(status->lstatus2 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrLstatus2 (%d) reg_val (%u)\n", 
        ch, string, status->lstatus2, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrlst.bit.cpRlrLstatus2))
    };  
        
    if(status->werrcnt0 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwecnt0.bit.cpRlrWerrcnt0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrWerrcnt0 (%d) reg_val (%u)\n", 
        ch, string, status->werrcnt0, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwecnt0.bit.cpRlrWerrcnt0))
    };  
        
    if(status->werrcnt1 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwecnt1.bit.cpRlrWerrcnt1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrWerrcnt1 (%d) reg_val (%u)\n", 
        ch, string, status->werrcnt1, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwecnt1.bit.cpRlrWerrcnt1))
    };  
        
    if(status->werrcnt2 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwecnt2.bit.cpRlrWerrcnt2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrWerrcnt2 (%d) reg_val (%u)\n", 
        ch, string, status->werrcnt2, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwecnt2.bit.cpRlrWerrcnt2))
    };  
        
    if(status->wcnt0 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwcnt0.bit.cpRlrWcnt0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrWcnt0 (%lld) reg_val (%lld)\n", 
        ch, string, status->wcnt0, (ULLONG)((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwcnt0.bit.cpRlrWcnt0))
    };  
        
    if(status->wcnt1 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwcnt1.bit.cpRlrWcnt1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrWcnt1 (%lld) reg_val (%lld)\n", 
        ch, string, status->wcnt1, (ULLONG)((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwcnt1.bit.cpRlrWcnt1))
    };  
        
    if(status->wcnt2 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwcnt2.bit.cpRlrWcnt2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrWcnt2 (%lld) reg_val (%lld)\n", 
        ch, string, status->wcnt2, (ULLONG)((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrwcnt2.bit.cpRlrWcnt2))
    };  
        
    if(status->syerrcnt0 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrcnt0.bit.cpRlrSyerrcnt0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrSyerrcnt0 (%d) reg_val (%u)\n", 
        ch, string, status->syerrcnt0, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrcnt0.bit.cpRlrSyerrcnt0))
    };  
        
    if(status->syerrcnt1 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrcnt1.bit.cpRlrSyerrcnt1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrSyerrcnt1 (%d) reg_val (%u)\n", 
        ch, string, status->syerrcnt1, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrcnt1.bit.cpRlrSyerrcnt1))
    };  
        
    if(status->syerrcnt2 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrcnt2.bit.cpRlrSyerrcnt2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrSyerrcnt2 (%d) reg_val (%u)\n", 
        ch, string, status->syerrcnt2, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrcnt2.bit.cpRlrSyerrcnt2))
    };  
        
    if(status->syerrloc0 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrloc0.bit.cpRlrSyerrloc0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrSyerrloc0 (%llu) reg_val (%llu)\n", 
        ch, string, status->syerrloc0, (ULLONG)((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrloc0.bit.cpRlrSyerrloc0))
    };  
        
    if(status->syerrloc1 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrloc1.bit.cpRlrSyerrloc1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrSyerrloc1 (%llu) reg_val (%llu)\n", 
        ch, string, status->syerrloc1, (ULLONG)((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrloc1.bit.cpRlrSyerrloc1))
    };  
        
    if(status->syerrloc2 != ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrloc2.bit.cpRlrSyerrloc2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Get_Status(%u) %s result:cpRlrSyerrloc2 (%llu) reg_val (%llu)\n", 
        ch, string, status->syerrloc2, (ULLONG)((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrserrloc2.bit.cpRlrSyerrloc2))
    };  
}

void im_pro_1_6_print_2(ImPro16Print *self,const char* string, kuchar ch)
{
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdstrg.bit.lvdstrg != D_IM_PRO_TRG_STATUS_RUNNING) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Start(%u) %s result:lvdstrg (%u)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdstrg.bit.lvdstrg))
    };  
}

void im_pro_1_6_print_3(ImPro16Print *self,const char* string, kuchar ch)
{
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdstrg.bit.lvdstrg != D_IM_PRO_TRG_STATUS_STOPPED) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Stop(%u) %s result:lvdstrg (%u)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdstrg.bit.lvdstrg))
    };  
}

void im_pro_1_6_print_4(ImPro16Print *self,const char* string, kuchar ch, T_IM_PRO_LVDS_CTRL* lvdsCtrl)
{
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.lmd != lvdsCtrl->transMode) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:lmd (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.lmd, lvdsCtrl->transMode))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.lch != lvdsCtrl->outputChNo) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:lch (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.lch, lvdsCtrl->outputChNo))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.lane != lvdsCtrl->lane) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:lane (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.lane, lvdsCtrl->lane))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.ldw != lvdsCtrl->dataBitWidth) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:ldw (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.ldw, lvdsCtrl->dataBitWidth))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.lsft != lvdsCtrl->lsft) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:lsft (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.lsft, lvdsCtrl->lsft))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.synt != lvdsCtrl->syncType) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:synt (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.synt, lvdsCtrl->syncType))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.szen != lvdsCtrl->dataInputType) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:szen (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.szen, lvdsCtrl->dataInputType))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.syn16 != lvdsCtrl->syncBitFix) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:syn16 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl1.bit.syn16, lvdsCtrl->syncBitFix))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl2.bit.divot != lvdsCtrl->divideOutput) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:divot (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl2.bit.divot, lvdsCtrl->divideOutput))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl2.bit.lmir != lvdsCtrl->invertedOutput) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:lmir (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl2.bit.lmir, lvdsCtrl->invertedOutput))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl2.bit.dolmd != lvdsCtrl->outputMode) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dolmd (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl2.bit.dolmd, lvdsCtrl->outputMode))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl2.bit.lmsk != lvdsCtrl->laneMask) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:lmsk (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsctl2.bit.lmsk, lvdsCtrl->laneMask))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks0 != lvdsCtrl->clockSelectSp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:clks0 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks0, lvdsCtrl->clockSelectSp0))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks1 != lvdsCtrl->clockSelectSp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:clks1 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks1, lvdsCtrl->clockSelectSp1))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks2 != lvdsCtrl->clockSelectSp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:clks2 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks2, lvdsCtrl->clockSelectSp2))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks3 != lvdsCtrl->clockSelectSp3) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:clks3 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks3, lvdsCtrl->clockSelectSp3))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks4 != lvdsCtrl->clockSelectSp4) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:clks4 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks4, lvdsCtrl->clockSelectSp4))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks5 != lvdsCtrl->clockSelectSp5) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:clks5 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks5, lvdsCtrl->clockSelectSp5))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks6 != lvdsCtrl->clockSelectSp6) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:clks6 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks6, lvdsCtrl->clockSelectSp6))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks7 != lvdsCtrl->clockSelectSp7) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:clks7 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsclks.bit.clks7, lvdsCtrl->clockSelectSp7))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats00 != lvdsCtrl->dataSelectSp0_0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats00 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats00, lvdsCtrl->dataSelectSp0_0))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats01 != lvdsCtrl->dataSelectSp0_1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats01 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats01, lvdsCtrl->dataSelectSp0_1))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats10 != lvdsCtrl->dataSelectSp1_0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats10 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats10, lvdsCtrl->dataSelectSp1_0))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats11 != lvdsCtrl->dataSelectSp1_1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats11 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats11, lvdsCtrl->dataSelectSp1_1))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats20 != lvdsCtrl->dataSelectSp2_0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats20 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats20, lvdsCtrl->dataSelectSp2_0))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats21 != lvdsCtrl->dataSelectSp2_1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats21 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats21, lvdsCtrl->dataSelectSp2_1))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats30 != lvdsCtrl->dataSelectSp3_0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats30 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats30, lvdsCtrl->dataSelectSp3_0))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats31 != lvdsCtrl->dataSelectSp3_1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats31 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats31, lvdsCtrl->dataSelectSp3_1))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats40 != lvdsCtrl->dataSelectSp4_0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats40 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats40, lvdsCtrl->dataSelectSp4_0))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats41 != lvdsCtrl->dataSelectSp4_1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats41 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats41, lvdsCtrl->dataSelectSp4_1))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats50 != lvdsCtrl->dataSelectSp5_0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats50 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats50, lvdsCtrl->dataSelectSp5_0))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats51 != lvdsCtrl->dataSelectSp5_1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats51 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats51, lvdsCtrl->dataSelectSp5_1))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats60 != lvdsCtrl->dataSelectSp6_0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats60 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats60, lvdsCtrl->dataSelectSp6_0))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats61 != lvdsCtrl->dataSelectSp6_1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats61 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats61, lvdsCtrl->dataSelectSp6_1))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats71 != lvdsCtrl->dataSelectSp7_0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats71 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats71, lvdsCtrl->dataSelectSp7_0))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats70 != lvdsCtrl->dataSelectSp7_1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:dats70 (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsdats.bit.dats70, lvdsCtrl->dataSelectSp7_1))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].syncsel.bit.syncsel != lvdsCtrl->laneSelect) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Ctrl(%u) %s result:syncsel (%u) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].syncsel.bit.syncsel, lvdsCtrl->laneSelect))
    };  
}

void im_pro_1_6_print_5(ImPro16Print *self,const char* string, kuchar ch, USHORT inputPos, USHORT inputSize)
{
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lhsadd.bit.lhsadd != inputPos) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_Area(%u) %s result:lhsadd(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lhsadd.bit.lhsadd, inputPos))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lhsize.bit.lhsize != inputSize) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_Area(%u) %s result:lhsize(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lhsize.bit.lhsize, inputSize))
    };  
}

void im_pro_1_6_print_6(ImPro16Print *self,const char* string, kuchar ch, T_IM_PRO_LVDS_PIXEL_ORDER* lvdsOrder)
{
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.sela != lvdsOrder->ptnA) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:sela(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.sela, lvdsOrder->ptnA))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selb != lvdsOrder->ptnB) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:selb(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selb, lvdsOrder->ptnB))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selc != lvdsOrder->ptnC) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:selc(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selc, lvdsOrder->ptnC))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.seld != lvdsOrder->ptnD) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:seld(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.seld, lvdsOrder->ptnD))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.sele != lvdsOrder->ptnE) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:sele(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.sele, lvdsOrder->ptnE))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.self != lvdsOrder->ptnF) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:self(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.self, lvdsOrder->ptnF))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selg != lvdsOrder->ptnG) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:selg(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selg, lvdsOrder->ptnG))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selh != lvdsOrder->ptnH) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:selh(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selh, lvdsOrder->ptnH))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.seli != lvdsOrder->ptnI) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:seli(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.seli, lvdsOrder->ptnI))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selj != lvdsOrder->ptnJ) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:selj(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selj, lvdsOrder->ptnJ))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selk != lvdsOrder->ptnK) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:selk(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selk, lvdsOrder->ptnK))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.sell != lvdsOrder->ptnL) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:sell(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.sell, lvdsOrder->ptnL))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selm != lvdsOrder->ptnM) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:selm(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selm, lvdsOrder->ptnM))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.seln != lvdsOrder->ptnN) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:seln(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.seln, lvdsOrder->ptnN))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selo != lvdsOrder->ptnO) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:selo(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selo, lvdsOrder->ptnO))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selp != lvdsOrder->ptnP) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PixelOrder(%u) %s result:selp(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lpdchg.bit.selp, lvdsOrder->ptnP))
    };  
}

void im_pro_1_6_print_7(ImPro16Print *self,const char* string, kuchar ch, T_IM_PRO_LVDS_SYNC_CODE_CTRL* syncCode)
{
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav0.sav01.bit.sav0_0 != syncCode->syncCode[0].sav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav0_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav0.sav01.bit.sav0_0, syncCode->syncCode[0].sav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav0.sav01.bit.sav0_1 != syncCode->syncCode[0].sav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav0_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav0.sav01.bit.sav0_1, syncCode->syncCode[0].sav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav0.sav02.bit.sav0_2 != syncCode->syncCode[0].sav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav0_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav0.sav02.bit.sav0_2, syncCode->syncCode[0].sav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav0.sav02.bit.sav0_3 != syncCode->syncCode[0].sav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav0_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav0.sav02.bit.sav0_3, syncCode->syncCode[0].sav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav0.eav01.bit.eav0_0 != syncCode->syncCode[0].eav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav0_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav0.eav01.bit.eav0_0, syncCode->syncCode[0].eav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav0.eav01.bit.eav0_1 != syncCode->syncCode[0].eav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav0_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav0.eav01.bit.eav0_1, syncCode->syncCode[0].eav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav0.eav02.bit.eav0_2 != syncCode->syncCode[0].eav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav0_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav0.eav02.bit.eav0_2, syncCode->syncCode[0].eav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav0.eav02.bit.eav0_3 != syncCode->syncCode[0].eav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav0_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav0.eav02.bit.eav0_3, syncCode->syncCode[0].eav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab0.sab01.bit.sab0_0 != syncCode->syncCode[0].sab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab0_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab0.sab01.bit.sab0_0, syncCode->syncCode[0].sab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab0.sab01.bit.sab0_1 != syncCode->syncCode[0].sab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab0_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab0.sab01.bit.sab0_1, syncCode->syncCode[0].sab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab0.sab02.bit.sab0_2 != syncCode->syncCode[0].sab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab0_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab0.sab02.bit.sab0_2, syncCode->syncCode[0].sab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab0.sab02.bit.sab0_3 != syncCode->syncCode[0].sab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab0_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab0.sab02.bit.sab0_3, syncCode->syncCode[0].sab[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab0.eab01.bit.eab0_0 != syncCode->syncCode[0].eab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab0_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab0.eab01.bit.eab0_0, syncCode->syncCode[0].eab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab0.eab01.bit.eab0_1 != syncCode->syncCode[0].eab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab0_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab0.eab01.bit.eab0_1, syncCode->syncCode[0].eab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab0.eab02.bit.eab0_2 != syncCode->syncCode[0].eab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab0_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab0.eab02.bit.eab0_2, syncCode->syncCode[0].eab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab0.eab02.bit.eab0_3 != syncCode->syncCode[0].eab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab0_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab0.eab02.bit.eab0_3, syncCode->syncCode[0].eab[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav1.sav11.bit.sav1_0 != syncCode->syncCode[1].sav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav1_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav1.sav11.bit.sav1_0, syncCode->syncCode[1].sav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav1.sav11.bit.sav1_1 != syncCode->syncCode[1].sav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav1_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav1.sav11.bit.sav1_1, syncCode->syncCode[1].sav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav1.SAV12.bit.sav1_2 != syncCode->syncCode[1].sav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav1_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav1.SAV12.bit.sav1_2, syncCode->syncCode[1].sav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav1.SAV12.bit.sav1_3 != syncCode->syncCode[1].sav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav1_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav1.SAV12.bit.sav1_3, syncCode->syncCode[1].sav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav1.eav11.bit.eav1_0 != syncCode->syncCode[1].eav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav1_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav1.eav11.bit.eav1_0, syncCode->syncCode[1].eav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav1.eav11.bit.eav1_1 != syncCode->syncCode[1].eav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav1_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav1.eav11.bit.eav1_1, syncCode->syncCode[1].eav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav1.eav12.bit.eav1_2 != syncCode->syncCode[1].eav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav1_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav1.eav12.bit.eav1_2, syncCode->syncCode[1].eav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav1.eav12.bit.eav1_3 != syncCode->syncCode[1].eav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav1_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav1.eav12.bit.eav1_3, syncCode->syncCode[1].eav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab1.sab11.bit.sab1_0 != syncCode->syncCode[1].sab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab1_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab1.sab11.bit.sab1_0, syncCode->syncCode[1].sab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab1.sab11.bit.sab1_1 != syncCode->syncCode[1].sab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab1_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab1.sab11.bit.sab1_1, syncCode->syncCode[1].sab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab1.sab12.bit.sab1_2 != syncCode->syncCode[1].sab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab1_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab1.sab12.bit.sab1_2, syncCode->syncCode[1].sab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab1.sab12.bit.sab1_3 != syncCode->syncCode[1].sab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab1_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab1.sab12.bit.sab1_3, syncCode->syncCode[1].sab[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab1.eab11.bit.eab1_0 != syncCode->syncCode[1].eab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab1_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab1.eab11.bit.eab1_0, syncCode->syncCode[1].eab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab1.eab11.bit.eab1_1 != syncCode->syncCode[1].eab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab1_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab1.eab11.bit.eab1_1, syncCode->syncCode[1].eab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab1.eab12.bit.eab1_2 != syncCode->syncCode[1].eab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab1_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab1.eab12.bit.eab1_2, syncCode->syncCode[1].eab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab1.eab12.bit.eab1_3 != syncCode->syncCode[1].eab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab1_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab1.eab12.bit.eab1_3, syncCode->syncCode[1].eab[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav2.sav21.bit.sav2_0 != syncCode->syncCode[2].sav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav2_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav2.sav21.bit.sav2_0, syncCode->syncCode[2].sav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav2.sav21.bit.sav2_1 != syncCode->syncCode[2].sav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav2_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav2.sav21.bit.sav2_1, syncCode->syncCode[2].sav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav2.sav22.bit.sav2_2 != syncCode->syncCode[2].sav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav2_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav2.sav22.bit.sav2_2, syncCode->syncCode[2].sav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav2.sav22.bit.sav2_3 != syncCode->syncCode[2].sav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sav2_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sav2.sav22.bit.sav2_3, syncCode->syncCode[2].sav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav2.eav21.bit.eav2_0 != syncCode->syncCode[2].eav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav2_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav2.eav21.bit.eav2_0, syncCode->syncCode[2].eav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav2.eav21.bit.eav2_1 != syncCode->syncCode[2].eav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav2_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav2.eav21.bit.eav2_1, syncCode->syncCode[2].eav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav2.eav22.bit.eav2_2 != syncCode->syncCode[2].eav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav2_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav2.eav22.bit.eav2_2, syncCode->syncCode[2].eav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav2.eav22.bit.eav2_3 != syncCode->syncCode[2].eav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eav2_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eav2.eav22.bit.eav2_3, syncCode->syncCode[2].eav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab2.sab21.bit.sab2_0 != syncCode->syncCode[2].sab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab2_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab2.sab21.bit.sab2_0, syncCode->syncCode[2].sab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab2.sab21.bit.sab2_1 != syncCode->syncCode[2].sab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab2_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab2.sab21.bit.sab2_1, syncCode->syncCode[2].sab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab2.sab22.bit.sab2_2 != syncCode->syncCode[2].sab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab2_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab2.sab22.bit.sab2_2, syncCode->syncCode[2].sab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab2.sab22.bit.sab2_3 != syncCode->syncCode[2].sab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:sab2_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].sab2.sab22.bit.sab2_3, syncCode->syncCode[2].sab[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab2.eab21.bit.eab2_0 != syncCode->syncCode[2].eab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab2_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab2.eab21.bit.eab2_0, syncCode->syncCode[2].eab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab2.eab21.bit.eab2_1 != syncCode->syncCode[2].eab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab2_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab2.eab21.bit.eab2_1, syncCode->syncCode[2].eab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab2.eab22.bit.eab2_2 != syncCode->syncCode[2].eab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab2_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab2.eab22.bit.eab2_2, syncCode->syncCode[2].eab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab2.eab22.bit.eab2_3 != syncCode->syncCode[2].eab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncCode(%u) %s result:eab2_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].eab2.eab22.bit.eab2_3, syncCode->syncCode[2].eab[3]))
    };  
}

void im_pro_1_6_print_8(ImPro16Print *self,const char* string, kuchar ch, T_IM_PRO_LVDS_SYNC_MASK_CTRL* syncMask)
{
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav0.msav01.bit.msav00 != syncMask->syncMask[0].msav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav00(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav0.msav01.bit.msav00, syncMask->syncMask[0].msav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav0.msav01.bit.msav01 != syncMask->syncMask[0].msav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav01(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav0.msav01.bit.msav01, syncMask->syncMask[0].msav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav0.msav02.bit.msav02 != syncMask->syncMask[0].msav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav02(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav0.msav02.bit.msav02, syncMask->syncMask[0].msav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav0.msav02.bit.msav03 != syncMask->syncMask[0].msav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav03(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav0.msav02.bit.msav03, syncMask->syncMask[0].msav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav0.meav01.bit.meav0_0 != syncMask->syncMask[0].meav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav0_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav0.meav01.bit.meav0_0, syncMask->syncMask[0].meav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav0.meav01.bit.meav0_1 != syncMask->syncMask[0].meav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav0_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav0.meav01.bit.meav0_1, syncMask->syncMask[0].meav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav0.meav02.bit.meav0_2 != syncMask->syncMask[0].meav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav0_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav0.meav02.bit.meav0_2, syncMask->syncMask[0].meav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav0.meav02.bit.meav0_3 != syncMask->syncMask[0].meav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav0_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav0.meav02.bit.meav0_3, syncMask->syncMask[0].meav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab0.msab01.bit.msab0_0 != syncMask->syncMask[0].msab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab0_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab0.msab01.bit.msab0_0, syncMask->syncMask[0].msab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab0.msab01.bit.msab0_1 != syncMask->syncMask[0].msab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab0_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab0.msab01.bit.msab0_1, syncMask->syncMask[0].msab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab0.msab02.bit.msab0_2 != syncMask->syncMask[0].msab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab0_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab0.msab02.bit.msab0_2, syncMask->syncMask[0].msab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab0.msab02.bit.msab0_3 != syncMask->syncMask[0].msab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab0_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab0.msab02.bit.msab0_3, syncMask->syncMask[0].msab[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab0.meab01.bit.meab0_0 != syncMask->syncMask[0].meab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab0_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab0.meab01.bit.meab0_0, syncMask->syncMask[0].meab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab0.meab01.bit.meab0_1 != syncMask->syncMask[0].meab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab0_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab0.meab01.bit.meab0_1, syncMask->syncMask[0].meab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab0.meab02.bit.meab0_2 != syncMask->syncMask[0].meab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab0_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab0.meab02.bit.meab0_2, syncMask->syncMask[0].meab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab0.meab02.bit.meab0_3 != syncMask->syncMask[0].meab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab0_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab0.meab02.bit.meab0_3, syncMask->syncMask[0].meab[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav1.msav11.bit.msav1_0 != syncMask->syncMask[1].msav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav1_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav1.msav11.bit.msav1_0, syncMask->syncMask[1].msav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav1.msav11.bit.msav1_1 != syncMask->syncMask[1].msav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav1_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav1.msav11.bit.msav1_1, syncMask->syncMask[1].msav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav1.msav12.bit.msav1_2 != syncMask->syncMask[1].msav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav1_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav1.msav12.bit.msav1_2, syncMask->syncMask[1].msav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav1.msav12.bit.msav1_3 != syncMask->syncMask[1].msav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav1_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav1.msav12.bit.msav1_3, syncMask->syncMask[1].msav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav1.meav11.bit.meav1_0 != syncMask->syncMask[1].meav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav1_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav1.meav11.bit.meav1_0, syncMask->syncMask[1].meav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav1.meav11.bit.meav1_1 != syncMask->syncMask[1].meav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav1_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav1.meav11.bit.meav1_1, syncMask->syncMask[1].meav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav1.meav12.bit.meav1_2 != syncMask->syncMask[1].meav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav1_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav1.meav12.bit.meav1_2, syncMask->syncMask[1].meav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav1.meav12.bit.meav1_3 != syncMask->syncMask[1].meav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav1_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav1.meav12.bit.meav1_3, syncMask->syncMask[1].meav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab1.msab11.bit.msab1_0 != syncMask->syncMask[1].msab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab1_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab1.msab11.bit.msab1_0, syncMask->syncMask[1].msab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab1.msab11.bit.msab1_1 != syncMask->syncMask[1].msab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab1_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab1.msab11.bit.msab1_1, syncMask->syncMask[1].msab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab1.msab12.bit.msab1_2 != syncMask->syncMask[1].msab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab1_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab1.msab12.bit.msab1_2, syncMask->syncMask[1].msab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab1.msab12.bit.msab1_3 != syncMask->syncMask[1].msab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab1_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab1.msab12.bit.msab1_3, syncMask->syncMask[1].msab[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab1.meab11.bit.meab1_0 != syncMask->syncMask[1].meab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab1_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab1.meab11.bit.meab1_0, syncMask->syncMask[1].meab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab1.meab11.bit.meab1_1 != syncMask->syncMask[1].meab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab1_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab1.meab11.bit.meab1_1, syncMask->syncMask[1].meab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab1.meab12.bit.meab1_2 != syncMask->syncMask[1].meab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab1_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab1.meab12.bit.meab1_2, syncMask->syncMask[1].meab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab1.meab12.bit.meab1_3 != syncMask->syncMask[1].meab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab1_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab1.meab12.bit.meab1_3, syncMask->syncMask[1].meab[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav2.msav21.bit.msav2_0 != syncMask->syncMask[2].msav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav2_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav2.msav21.bit.msav2_0, syncMask->syncMask[2].msav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav2.msav21.bit.msav2_1 != syncMask->syncMask[2].msav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav2_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav2.msav21.bit.msav2_1, syncMask->syncMask[2].msav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav2.msav22.bit.msav2_2 != syncMask->syncMask[2].msav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav2_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav2.msav22.bit.msav2_2, syncMask->syncMask[2].msav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav2.msav22.bit.msav2_3 != syncMask->syncMask[2].msav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msav2_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msav2.msav22.bit.msav2_3, syncMask->syncMask[2].msav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav2.meav21.bit.meav2_0 != syncMask->syncMask[2].meav[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav2_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav2.meav21.bit.meav2_0, syncMask->syncMask[2].meav[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav2.meav21.bit.meav2_1 != syncMask->syncMask[2].meav[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav2_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav2.meav21.bit.meav2_1, syncMask->syncMask[2].meav[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav2.meav22.bit.meav2_2 != syncMask->syncMask[2].meav[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav2_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav2.meav22.bit.meav2_2, syncMask->syncMask[2].meav[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav2.meav22.bit.meav2_3 != syncMask->syncMask[2].meav[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meav2_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meav2.meav22.bit.meav2_3, syncMask->syncMask[2].meav[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab2.msab21.bit.msab2_0 != syncMask->syncMask[2].msab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab2_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab2.msab21.bit.msab2_0, syncMask->syncMask[2].msab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab2.msab21.bit.msab2_1 != syncMask->syncMask[2].msab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab2_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab2.msab21.bit.msab2_1, syncMask->syncMask[2].msab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab2.msab22.bit.msab2_2 != syncMask->syncMask[2].msab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab2_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab2.msab22.bit.msab2_2, syncMask->syncMask[2].msab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab2.msab22.bit.msab2_3 != syncMask->syncMask[2].msab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:msab2_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].msab2.msab22.bit.msab2_3, syncMask->syncMask[2].msab[3]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab2.meab21.bit.meab2_0 != syncMask->syncMask[2].meab[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab2_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab2.meab21.bit.meab2_0, syncMask->syncMask[2].meab[0]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab2.meab21.bit.meab2_1 != syncMask->syncMask[2].meab[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab2_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab2.meab21.bit.meab2_1, syncMask->syncMask[2].meab[1]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab2.meab22.bit.meab2_2 != syncMask->syncMask[2].meab[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab2_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab2.meab22.bit.meab2_2, syncMask->syncMask[2].meab[2]))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab2.meab22.bit.meab2_3 != syncMask->syncMask[2].meab[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_SyncMask(%u) %s result:meab2_3(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].meab2.meab22.bit.meab2_3, syncMask->syncMask[2].meab[3]))
    };  
}

void im_pro_1_6_print_9(ImPro16Print *self,const char* string, kuchar ch, T_IM_PRO_LVDS_INT_ADDR_CTRL* intAddr)
{
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr0.bit.solvadr_0 != intAddr->intAddr[0].solAddr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_IntAdr(%u) %s result:solvadr_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr0.bit.solvadr_0, intAddr->intAddr[0].solAddr))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr0.bit.eolvadr_0 != intAddr->intAddr[0].eolAddr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_IntAdr(%u) %s result:eolvadr_0(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr0.bit.eolvadr_0, intAddr->intAddr[0].eolAddr))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr1.bit.solvadr_1 != intAddr->intAddr[1].solAddr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_IntAdr(%u) %s result:solvadr_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr1.bit.solvadr_1, intAddr->intAddr[1].solAddr))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr1.bit.eolvadr_1 != intAddr->intAddr[1].eolAddr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_IntAdr(%u) %s result:eolvadr_1(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr1.bit.eolvadr_1, intAddr->intAddr[1].eolAddr))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr2.bit.solvadr_2 != intAddr->intAddr[2].solAddr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_IntAdr(%u) %s result:solvadr_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr2.bit.solvadr_2, intAddr->intAddr[2].solAddr))
    };  
        
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr2.bit.eolvadr_2 != intAddr->intAddr[2].eolAddr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_IntAdr(%u) %s result:eolvadr_2(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintadr2.bit.eolvadr_2, intAddr->intAddr[2].eolAddr))
    }; 
}
#endif

ImPro16Print* im_pro_1_6_print_new(void)
{
	ImPro16Print* self = k_object_new_with_private(IM_TYPE_PRO_1_6_PRINT, sizeof(ImPro16PrintPrivate));

	return self;
}

ImPro16Print* im_pro_1_6_print_get(void)
{
	static ImPro16Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_1_6_PRINT, sizeof(ImPro16PrintPrivate));
	}

	return self;
}
