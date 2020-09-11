/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro15Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro15print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImPro15Print, im_pro_1_5_print, ABS_TYPE_IM_PRO_PRINT)
#define IM_PRO_1_5_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImPro15PrintPrivate, IM_TYPE_PRO_1_5_PRINT))


struct _ImPro15PrintPrivate
{


};


/**
 *IMPL 
 */
static void im_pro_1_5_print_constructor(ImPro15Print *self)
{
	ImPro15PrintPrivate *priv = IM_PRO_1_5_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void im_pro_1_5_print_destructor(ImPro15Print *self)
{
	ImPro15PrintPrivate *priv = IM_PRO_1_5_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *PUBLIC 
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_5_print_0(ImPro15Print *self,const char* string, kuchar ch)
{
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpitrg.bit.mpitrg != D_IM_PRO_TRG_STATUS_RUNNING) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Start(%u) %s result:mpitrg (%u)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpitrg.bit.mpitrg))}; 
}

void im_pro_1_5_print_1(ImPro15Print *self,const char* string, kuchar ch, kuchar force)
{
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpitrg.bit.mpitrg != D_IM_PRO_TRG_STATUS_STOPPED) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Stop(%u %u) %s result:mpitrg (%u)\n", 
        ch, force, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpitrg.bit.mpitrg))}; 
}

void im_pro_1_5_print_2(ImPro15Print *self,const char* string, kuchar ch, T_IM_PRO_DMIPI_CTRL* dmipiCtrl)
{
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpilmode.bit.lane != dmipiCtrl->laneSel) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:lane (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpilmode.bit.lane, dmipiCtrl->laneSel))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd0.bit.dtmd0 != dmipiCtrl->inputDataMode[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:dtmd0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd0.bit.dtmd0, dmipiCtrl->inputDataMode[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd0.bit.outmd0 != dmipiCtrl->outputDataMode[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:outmd0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd0.bit.outmd0, dmipiCtrl->outputDataMode[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd0.bit.vcout0 != dmipiCtrl->vcModeSel[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:vcout0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd0.bit.vcout0, dmipiCtrl->vcModeSel[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd0.bit.dtcomd0 != dmipiCtrl->outputDtSel[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:dtcomd0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd0.bit.dtcomd0, dmipiCtrl->outputDtSel[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd0.bit.dtco0 != dmipiCtrl->outputDtSetting[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:dtco0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd0.bit.dtco0, dmipiCtrl->outputDtSetting[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd1.bit.dtmd1 != dmipiCtrl->inputDataMode[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:dtmd1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd1.bit.dtmd1, dmipiCtrl->inputDataMode[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd1.bit.outmd1 != dmipiCtrl->outputDataMode[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:outmd1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd1.bit.outmd1, dmipiCtrl->outputDataMode[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd1.bit.vcout1 != dmipiCtrl->vcModeSel[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:vcout1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd1.bit.vcout1, dmipiCtrl->vcModeSel[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd1.bit.dtcomd1 != dmipiCtrl->outputDtSel[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:dtcomd1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd1.bit.dtcomd1, dmipiCtrl->outputDtSel[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd1.bit.dtco1 != dmipiCtrl->outputDtSetting[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:dtco1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiiomd1.bit.dtco1, dmipiCtrl->outputDtSetting[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpidpi.bit.dpsmtc != dmipiCtrl->phyCtrl.rxsmtCVal) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:dpsmtc (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpidpi.bit.dpsmtc, dmipiCtrl->phyCtrl.rxsmtCVal))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpidpi.bit.dpsmtd != dmipiCtrl->phyCtrl.rxsmtDVal) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:dpsmtd (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpidpi.bit.dpsmtd, dmipiCtrl->phyCtrl.rxsmtDVal))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpidpi.bit.dpsm != dmipiCtrl->phyCtrl.rxsyncmode) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:dpsm (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpidpi.bit.dpsm, dmipiCtrl->phyCtrl.rxsyncmode))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpihdpdsel.bit.hdpdsel0 != dmipiCtrl->outCycle[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:hdpdsel0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpihdpdsel.bit.hdpdsel0, dmipiCtrl->outCycle[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpihdpdsel.bit.hdpdsel1 != dmipiCtrl->outCycle[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:hdpdsel1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpihdpdsel.bit.hdpdsel1, dmipiCtrl->outCycle[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpidpi.bit.dpen != dmipiCtrl->phyCtrl.rxenable) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Ctrl(%u) %s result:dpen (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpidpi.bit.dpen, dmipiCtrl->phyCtrl.rxenable))}; 
}

void im_pro_1_5_print_3(ImPro15Print *self,const char* string, kuchar ch, kuchar paenTrg0, kuchar paenTrg1)
{
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpipaen0.bit.paen0 != paenTrg0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Set_PAEN(%u) %s result:paen0(%d) mpitrg(%d) paenTrg0(%d) paenTrg1(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpipaen0.bit.paen0, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpitrg.bit.mpitrg, 
        paenTrg0, paenTrg1))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpipaen1.bit.paen1 != paenTrg1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Set_PAEN(%u) %s result:paen1(%d) mpitrg(%d) paenTrg0(%d) paenTrg1(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpipaen1.bit.paen1, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpitrg.bit.mpitrg, 
        paenTrg0, paenTrg1))}; 
}

void im_pro_1_5_print_4(ImPro15Print *self,const char* string, kuchar ch, T_IM_PRO_DMIPI_STATUS* status)
{
    if(status->input_signal_status !=  ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpidpvr.word) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Get_Status(%u) %s result:mpidpvr(%lu) reg_val (%lu)\n", 
        ch, string, status->input_signal_status, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpidpvr.word))}; 
        
    if(status->skewCalibrationStatus !=  ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiscs.word) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Get_Status(%u) %s result:mpiscs (%lu) reg_val (%lu)\n", 
        ch, string, status->skewCalibrationStatus, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiscs.word))}; 
}                                                    

void im_pro_1_5_print_5(ImPro15Print *self,const char* string, kuchar ch)
{
    { DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Init(%u) %s result:sr(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicsr.bit.sr))}; 
}

void im_pro_1_5_print_6(ImPro15Print *self,const char* string, kuchar ch)
{
    { DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_SR(%u) %s result:sr(%u)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicsr.bit.sr))}; 
}

void im_pro_1_5_print_7(ImPro15Print *self,const char* string, kuchar ch)
{
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpictrg.bit.mpictrg != D_IM_PRO_TRG_STATUS_RUNNING) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Start(%u) %s result:mpictrg (%u)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpictrg.bit.mpictrg))}; 
}

void im_pro_1_5_print_8(ImPro15Print *self,const char* string, kuchar ch, kuchar force)
{
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpictrg.bit.mpictrg != D_IM_PRO_TRG_STATUS_STOPPED) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Stop(%u %u) %s result:mpictrg (%u)\n", 
        ch, force, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpictrg.bit.mpictrg))}; 
}

void im_pro_1_5_print_9(ImPro15Print *self,const char* string, kuchar ch, T_IM_PRO_CMIPI_CTRL* cmipiCtrl)
{
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiclmode.bit.lane != cmipiCtrl->laneSel) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:lane (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiclmode.bit.lane, cmipiCtrl->laneSel))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd0.bit.dtmd0 != cmipiCtrl->inputDataMode[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:dtmd0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd0.bit.dtmd0, cmipiCtrl->inputDataMode[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd0.bit.outmd0 != cmipiCtrl->outputDataMode[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:outmd0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd0.bit.outmd0, cmipiCtrl->outputDataMode[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd0.bit.vcout0 != cmipiCtrl->vcModeSel[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:vcout0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd0.bit.vcout0, cmipiCtrl->vcModeSel[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd0.bit.dtcomd0 != cmipiCtrl->outputDtSel[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:dtcomd0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd0.bit.dtcomd0, cmipiCtrl->outputDtSel[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd0.bit.dtco0 != cmipiCtrl->outputDtSetting[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:dtco0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd0.bit.dtco0, cmipiCtrl->outputDtSetting[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd1.bit.dtmd1 != cmipiCtrl->inputDataMode[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:dtmd1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd1.bit.dtmd1, cmipiCtrl->inputDataMode[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd1.bit.outmd1 != cmipiCtrl->outputDataMode[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:outmd1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd1.bit.outmd1, cmipiCtrl->outputDataMode[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd1.bit.vcout1 != cmipiCtrl->vcModeSel[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:vcout1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd1.bit.vcout1, cmipiCtrl->vcModeSel[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd1.bit.dtcomd1 != cmipiCtrl->outputDtSel[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:dtcomd1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd1.bit.dtcomd1, cmipiCtrl->outputDtSel[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd1.bit.dtco1 != cmipiCtrl->outputDtSetting[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:dtco1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiciomd1.bit.dtco1, cmipiCtrl->outputDtSetting[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpichdpdsel.bit.hdpdsel0 != cmipiCtrl->outCycle[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:hdpdsel0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpichdpdsel.bit.hdpdsel0, cmipiCtrl->outCycle[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpichdpdsel.bit.hdpdsel1 != cmipiCtrl->outCycle[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:hdpdsel1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpichdpdsel.bit.hdpdsel1, cmipiCtrl->outCycle[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiccpi2.bit.cpHsSettlecnt != cmipiCtrl->phyCtrl.hsSettlecnt) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:cpHsSettlecnt (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiccpi2.bit.cpHsSettlecnt, cmipiCtrl->phyCtrl.hsSettlecnt))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiccpi2.bit.cpHsStopcnt != cmipiCtrl->phyCtrl.hsStopcnt) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:cpHsStopcnt (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiccpi2.bit.cpHsStopcnt, cmipiCtrl->phyCtrl.hsStopcnt))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiccpi2.bit.cpHsSyncmode != cmipiCtrl->phyCtrl.hsSyncmode) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:cpHsSyncmode (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpiccpi2.bit.cpHsSyncmode, cmipiCtrl->phyCtrl.hsSyncmode))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrlconf.bit.cpRlrLconfig != cmipiCtrl->phyCtrl.rlrLconfig) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:cpRlrLconfig (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrlconf.bit.cpRlrLconfig, cmipiCtrl->phyCtrl.rlrLconfig))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrltpsel.bit.cpRlrRpsel != cmipiCtrl->phyCtrl.rlrTpsel) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:cpRlrRpsel (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrltpsel.bit.cpRlrRpsel, cmipiCtrl->phyCtrl.rlrTpsel))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrprbs.bit.cpRlrPrbssp != cmipiCtrl->phyCtrl.rlrPrbssp) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:cpRlrPrbssp (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicprlrprbs.bit.cpRlrPrbssp, cmipiCtrl->phyCtrl.rlrPrbssp))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpprogseq.bit.cpTgrProgseq != cmipiCtrl->phyCtrl.tgrProgseq) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:cpTgrProgseq (%llu) (%llu)\n", 
        ch, string, (ULLONG)((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpprogseq.bit.cpTgrProgseq, 
        (ULLONG)cmipiCtrl->phyCtrl.tgrProgseq))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpfrxmode.bit.cpForcerxmode2 != cmipiCtrl->phyCtrl.forcerxmode2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:cpForcerxmode2 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpfrxmode.bit.cpForcerxmode2, cmipiCtrl->phyCtrl.forcerxmode2))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpfrxmode.bit.cpForcerxmode1 != cmipiCtrl->phyCtrl.forcerxmode1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:cpForcerxmode1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpfrxmode.bit.cpForcerxmode1, cmipiCtrl->phyCtrl.forcerxmode1))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpfrxmode.bit.cpForcerxmode0 != cmipiCtrl->phyCtrl.forcerxmode0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_CMIPI_Ctrl(%u) %s result:cpForcerxmode0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicpfrxmode.bit.cpForcerxmode0, cmipiCtrl->phyCtrl.forcerxmode0))}; 
}
#endif

ImPro15Print* im_pro_1_5_print_new(void)
{
	ImPro15Print* self = k_object_new_with_private(IM_TYPE_PRO_1_5_PRINT, sizeof(ImPro15PrintPrivate));

	return self;
}

ImPro15Print* im_pro_1_5_print_get(void)
{
	static ImPro15Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_1_5_PRINT, sizeof(ImPro15PrintPrivate));
	}

	return self;
}
