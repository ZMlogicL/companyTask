/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro23Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro23print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro23Print, impro_2_3_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_2_3_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro23PrintPrivate, IMPRO_TYPE_2_3_PRINT))


struct _Impro23PrintPrivate
{


};

/**
 *IMPL
 */
static void impro_2_3_print_constructor(Impro23Print *self)
{
	Impro23PrintPrivate *priv = IMPRO_2_3_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_2_3_print_destructor(Impro23Print *self)
{
	Impro23PrintPrivate *priv = IMPRO_2_3_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_2_3_print_0(Impro23Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_DPC_AREA* dpcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgwp.bit.dpcgh != dpcCtrl->gPosX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Set_Area(%u) %s result:dpcgh  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgwp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgwp.bit.dpcgh,dpcCtrl->gPosX))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgwp.bit.dpcgv != dpcCtrl->gPosY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Set_Area(%u) %s result:dpcgv  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgwp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgwp.bit.dpcgv,dpcCtrl->gPosY))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgws.bit.dpcghw != dpcCtrl->gWidth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Set_Area(%u) %s result:dpcghw  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgws.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgws.bit.dpcghw,dpcCtrl->gWidth))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgws.bit.dpcgvw != dpcCtrl->gLines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Set_Area(%u) %s result:dpcgvw  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgws.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcgws.bit.dpcgvw,dpcCtrl->gLines))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcwp.bit.dpch != dpcCtrl->posX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Set_Area(%u) %s result:dpch  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcwp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcwp.bit.dpch,dpcCtrl->posX))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcwp.bit.dpcv != dpcCtrl->posY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Set_Area(%u) %s result:dpcv  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcwp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcwp.bit.dpcv,dpcCtrl->posY))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcws.bit.dpchw != dpcCtrl->width) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Set_Area(%u) %s result:dpchw  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcws.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcws.bit.dpchw,dpcCtrl->width))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcws.bit.dpcvw != dpcCtrl->lines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Set_Area(%u) %s result:dpcvw  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcws.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcws.bit.dpcvw,dpcCtrl->lines))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Set_Area(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_3_print_1(Impro23Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_DPC_AB_CTRL* dpcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblp.bit.dpcblwp != dpcCtrl->alphaBlendTransitionWidthP) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Alpha_Blend_Ctrl(%u) %s result:dpcblwp 0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblp.bit.dpcblwp,dpcCtrl->alphaBlendTransitionWidthP))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblp.bit.dpcblsp != dpcCtrl->alphaBlendStartPosP) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Alpha_Blend_Ctrl(%u) %s result:dpcblsp 0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblp.bit.dpcblsp,dpcCtrl->alphaBlendStartPosP))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblm.bit.dpcblwm != dpcCtrl->alphaBlendTransitionWidthM) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Alpha_Blend_Ctrl(%u) %s result:dpcblwm 0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblm.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblm.bit.dpcblwm,dpcCtrl->alphaBlendTransitionWidthM))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblm.bit.dpcblsm != dpcCtrl->alphaBlendStartPosM) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Alpha_Blend_Ctrl(%u) %s result:dpcblsm 0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblm.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblm.bit.dpcblsm,dpcCtrl->alphaBlendStartPosM))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Alpha_Blend_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_3_print_2(Impro23Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_DPC_DDD_CTRL* dpcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfgrgb != dpcCtrl->grgbIndependentSetting) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfgrgb  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfgrgb,dpcCtrl->grgbIndependentSetting))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfmdg != dpcCtrl->gMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfmdg  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfmdg,dpcCtrl->gMode))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfmdrb != dpcCtrl->rbMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfmdrb  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfmdrb,dpcCtrl->rbMode))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfdcnt != dpcCtrl->upperLimitLocalRegistration) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfdcnt  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfdcnt,dpcCtrl->upperLimitLocalRegistration))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfrbug != dpcCtrl->useMdd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfrbug  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfrbug,dpcCtrl->useMdd))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfagnd != dpcCtrl->support2concecutiveDefect) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfagnd  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.bit.dfagnd,dpcCtrl->support2concecutiveDefect))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs1.bit.dfsrp != dpcCtrl->pThresholdStartPos[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfsrp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs1.bit.dfsrp,dpcCtrl->pThresholdStartPos[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs2.bit.dfsgp != dpcCtrl->pThresholdStartPos[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfsgp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs2.bit.dfsgp,dpcCtrl->pThresholdStartPos[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs3.bit.dfsbp != dpcCtrl->pThresholdStartPos[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfsbp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs3.bit.dfsbp,dpcCtrl->pThresholdStartPos[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs1.bit.dfsrm != dpcCtrl->mThresholdStartPos[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfsrm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs1.bit.dfsrm,dpcCtrl->mThresholdStartPos[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs2.bit.dfsgm != dpcCtrl->mThresholdStartPos[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfsgm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs2.bit.dfsgm,dpcCtrl->mThresholdStartPos[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs3.bit.dfsbm != dpcCtrl->mThresholdStartPos[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfsbm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs3.bit.dfsbm,dpcCtrl->mThresholdStartPos[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo1.bit.dforp != dpcCtrl->pThresholdStartOffset[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dforp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo1.bit.dforp,dpcCtrl->pThresholdStartOffset[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo2.bit.dfogp != dpcCtrl->pThresholdStartOffset[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfogp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo2.bit.dfogp,dpcCtrl->pThresholdStartOffset[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo3.bit.dfobp != dpcCtrl->pThresholdStartOffset[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfobp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo3.bit.dfobp,dpcCtrl->pThresholdStartOffset[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo1.bit.dform != dpcCtrl->mThresholdStartOffset[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dform  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo1.bit.dform,dpcCtrl->mThresholdStartOffset[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo2.bit.dfogm != dpcCtrl->mThresholdStartOffset[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfogm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo2.bit.dfogm,dpcCtrl->mThresholdStartOffset[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo3.bit.dfobm != dpcCtrl->mThresholdStartOffset[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfobm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo3.bit.dfobm,dpcCtrl->mThresholdStartOffset[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk1.bit.dfkrp != dpcCtrl->pThresholdGain[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfkrp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk1.bit.dfkrp,dpcCtrl->pThresholdGain[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk2.bit.dfkgp != dpcCtrl->pThresholdGain[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfkgp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk2.bit.dfkgp,dpcCtrl->pThresholdGain[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk3.bit.dfkbp != dpcCtrl->pThresholdGain[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfkbp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk3.bit.dfkbp,dpcCtrl->pThresholdGain[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk1.bit.dfkrm != dpcCtrl->mThresholdGain[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfkrm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk1.bit.dfkrm,dpcCtrl->mThresholdGain[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk2.bit.dfkgm != dpcCtrl->mThresholdGain[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfkgm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk2.bit.dfkgm,dpcCtrl->mThresholdGain[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk3.bit.dfkbm != dpcCtrl->mThresholdGain[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfkbm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk3.bit.dfkbm,dpcCtrl->mThresholdGain[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh1.bit.dfhrp != dpcCtrl->pThresholdUpperLimit[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfhrp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh1.bit.dfhrp,dpcCtrl->pThresholdUpperLimit[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh2.bit.dfhgp != dpcCtrl->pThresholdUpperLimit[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfhgp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh2.bit.dfhgp,dpcCtrl->pThresholdUpperLimit[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh3.bit.dfhbp != dpcCtrl->pThresholdUpperLimit[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfhbp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh3.bit.dfhbp,dpcCtrl->pThresholdUpperLimit[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh1.bit.dfhrm != dpcCtrl->mThresholdUpperLimit[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfhrm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh1.bit.dfhrm,dpcCtrl->mThresholdUpperLimit[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh2.bit.dfhgm != dpcCtrl->mThresholdUpperLimit[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfhgm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh2.bit.dfhgm,dpcCtrl->mThresholdUpperLimit[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh3.bit.dfhbm != dpcCtrl->mThresholdUpperLimit[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfhbm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh3.bit.dfhbm,dpcCtrl->mThresholdUpperLimit[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfcsr.bit.dfcsrp != dpcCtrl->pThreshold2consecutive) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfcsrp  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfcsr.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfcsr.bit.dfcsrp,dpcCtrl->pThreshold2consecutive))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfcsr.bit.dfcsrm != dpcCtrl->mThreshold2consecutive) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dfcsrm  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfcsr.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfcsr.bit.dfcsrm,dpcCtrl->mThreshold2consecutive))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth1.bit.dflsthr != 
            dpcCtrl->threshold2consecutiveBrightPix[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dflsthr  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth1.bit.dflsthr,dpcCtrl->threshold2consecutiveBrightPix[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth1.bit.dflsthg != 
            dpcCtrl->threshold2consecutiveBrightPix[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dflsthg  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth1.bit.dflsthg,dpcCtrl->threshold2consecutiveBrightPix[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth2.bit.dflsthb != 
            dpcCtrl->threshold2consecutiveBrightPix[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) %s result:dflsthb  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth2.bit.dflsthb,
            dpcCtrl->threshold2consecutiveBrightPix[2]))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Dynamic_Detect_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_3_print_3(Impro23Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                            kint32 ercd, T_IM_PRO_DPC_MDD_CTRL* dpcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef.bit.dfagefp != dpcCtrl->pMddEffect) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Mis_Determination_Calc_Ctrl(%u) %s result:dfagefp  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef.bit.dfagefp,dpcCtrl->pMddEffect))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef.bit.dfagefm != dpcCtrl->mMddEffect) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Mis_Determination_Calc_Ctrl(%u) %s result:dfagefm  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef.bit.dfagefm,dpcCtrl->mMddEffect))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef2.bit.dfagefp2 != dpcCtrl->pMddEffect2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Mis_Determination_Calc_Ctrl(%u) %s result:dfagefp2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef2.bit.dfagefp2,dpcCtrl->pMddEffect2))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef2.bit.dfagefm2 != dpcCtrl->mMddEffect2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Mis_Determination_Calc_Ctrl(%u) %s result:dfagefm2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef2.bit.dfagefm2,dpcCtrl->mMddEffect2))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagth.bit.dfagthp != dpcCtrl->pThresholdOffset) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Mis_Determination_Calc_Ctrl(%u) %s result:dfagthp  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagth.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagth.bit.dfagthp,dpcCtrl->pThresholdOffset))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagth.bit.dfagthm != dpcCtrl->mThresholdOffset) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Mis_Determination_Calc_Ctrl(%u) %s result:dfagthm  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagth.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagth.bit.dfagthm,dpcCtrl->mThresholdOffset))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagthk.bit.dfagthkp != dpcCtrl->pThresholdGain) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Mis_Determination_Calc_Ctrl(%u) %s result:dfagthkp 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagthk.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagthk.bit.dfagthkp,dpcCtrl->pThresholdGain))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagthk.bit.dfagthkm != dpcCtrl->mThresholdGain) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Mis_Determination_Calc_Ctrl(%u) %s result:dfagthkm 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagthk.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagthk.bit.dfagthkm,dpcCtrl->mThresholdGain))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Mis_Determination_Calc_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_3_print_4(Impro23Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_DPC_MDC_CTRL* dpcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmctl.bit.dmgug != dpcCtrl->useOcd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Magnitude_Defect_Ctrl(%u) %s result:dmgug  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmctl.bit.dmgug,dpcCtrl->useOcd))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwks.bit.dmwksp != dpcCtrl->pManualAdjValSingle) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Magnitude_Defect_Ctrl(%u) %s result:dmwksp 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwks.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwks.bit.dmwksp,dpcCtrl->pManualAdjValSingle))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwks.bit.dmwksm != dpcCtrl->mManualAdjValSingle) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Magnitude_Defect_Ctrl(%u) %s result:dmwksm 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwks.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwks.bit.dmwksm,dpcCtrl->mManualAdjValSingle))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwkd.bit.dmwkdp != dpcCtrl->pManualAdjVal2consecutive) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Magnitude_Defect_Ctrl(%u) %s result:dmwkdp 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwkd.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwkd.bit.dmwkdp,dpcCtrl->pManualAdjVal2consecutive))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwkd.bit.dmwkdm != dpcCtrl->mManualAdjVal2consecutive) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Magnitude_Defect_Ctrl(%u) %s result:dmwkdm 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwkd.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwkd.bit.dmwkdm,dpcCtrl->mManualAdjVal2consecutive))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmagk.bit.dmagkp != dpcCtrl->pCorrectionLevelOnOcd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Magnitude_Defect_Ctrl(%u) %s result:dmagkp 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmagk.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmagk.bit.dmagkp,dpcCtrl->pCorrectionLevelOnOcd))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmagk.bit.dmagkm != dpcCtrl->mCorrectionLevelOnOcd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Magnitude_Defect_Ctrl(%u) %s result:dmagkm 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmagk.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmagk.bit.dmagkm,dpcCtrl->mCorrectionLevelOnOcd))};
    }      
    else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Magnitude_Defect_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_3_print_5(Impro23Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_DPC_ESDC_CTRL* dpcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dectl.bit.degrgb != dpcCtrl->esd_mode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) %s result:degrgb  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dectl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dectl.bit.degrgb,dpcCtrl->esd_mode))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dectl.bit.derbug != dpcCtrl->useRbJdge) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) %s result:derbug  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dectl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dectl.bit.derbug,dpcCtrl->useRbJdge))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dectl.bit.degug != dpcCtrl->useOcd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) %s result:degug  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dectl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dectl.bit.degug,dpcCtrl->useOcd))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.denss.bit.denss != dpcCtrl->thresholdStartPos) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) %s result:denss  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.denss.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.denss.bit.denss,dpcCtrl->thresholdStartPos))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.denso.bit.denso != dpcCtrl->thresholdOffset) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) %s result:denso  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.denso.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.denso.bit.denso,dpcCtrl->thresholdOffset))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densk.bit.densk != dpcCtrl->thresholdGain) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) %s result:densk  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densk.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densk.bit.densk,dpcCtrl->thresholdGain))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densh.bit.densh != dpcCtrl->thresholdUpperLimit) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) %s result:densh  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densh.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densh.bit.densh,dpcCtrl->thresholdUpperLimit))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densmgn.bit.densmgn != dpcCtrl->noiseTolerance) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) %s result:densmgn  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densmgn.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densmgn.bit.densmgn,dpcCtrl->noiseTolerance))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dendcth.bit.dendcth != dpcCtrl->thresholdCalculation) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) %s result:dendcth  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dendcth.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dendcth.bit.dendcth,dpcCtrl->thresholdCalculation))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.deagk.bit.deagkp != dpcCtrl->pCorrectionLevelOnOcd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) %s result:deagkp  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.deagk.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.deagk.bit.deagkp,dpcCtrl->pCorrectionLevelOnOcd))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.deagk.bit.deagkm != dpcCtrl->mCorrectionLevelOnOcd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) %s result:deagkm  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.deagk.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.deagk.bit.deagkm,dpcCtrl->mCorrectionLevelOnOcd))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Edge_Storage_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_3_print_6(Impro23Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_DPC_OCD_CTRL* dpcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagef.bit.dcagefp != dpcCtrl->pOcdEffect) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Over_Correction_Detect_Ctrl(%u) %s result:dcagefp  0x%08lx(%d) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagef.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagef.bit.dcagefp,dpcCtrl->pOcdEffect))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagef.bit.dcagefm != dpcCtrl->mOcdEffect) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Over_Correction_Detect_Ctrl(%u) %s result:dcagefm  0x%08lx(%d) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagef.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagef.bit.dcagefm,dpcCtrl->mOcdEffect))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagth.bit.dcagthp != dpcCtrl->pThreshold) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Over_Correction_Detect_Ctrl(%u) %s result:dcagthp  0x%08lx(%d) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagth.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagth.bit.dcagthp,dpcCtrl->pThreshold))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagth.bit.dcagthm != dpcCtrl->mThreshold) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Over_Correction_Detect_Ctrl(%u) %s result:dcagthm  0x%08lx(%d) in(%u)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagth.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagth.bit.dcagthm,dpcCtrl->mThreshold))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Over_Correction_Detect_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_3_print_7(Impro23Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                        kint32 ercd, const T_IM_PRO_RDMA_DPC_ADDR** dpcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcmd.word != (*dpcCtrl)->dpcmd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dpcmd  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcmd.word, (kulong)(*dpcCtrl)->dpcmd))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblp.word != (*dpcCtrl)->dpcblp) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dpcblp  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblp.word, 
                     (kulong)(*dpcCtrl)->dpcblp))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblm.word != (*dpcCtrl)->dpcblm) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dpcblm  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dpcblm.word, 
                     (kulong)(*dpcCtrl)->dpcblm))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.word != (*dpcCtrl)->dfctl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfctl  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfctl.word, (kulong)(*dpcCtrl)->dfctl))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs1.word != (*dpcCtrl)->dfs1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfs1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs1.word, 
                   (kulong)(*dpcCtrl)->dfs1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs2.word != (*dpcCtrl)->dfs2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfs2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs2.word, 
                   (kulong)(*dpcCtrl)->dfs2))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs3.word != (*dpcCtrl)->dfs3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfs3  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfs.dfs3.word, 
                   (kulong)(*dpcCtrl)->dfs3))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo1.word != (*dpcCtrl)->dfo1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfo1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo1.word, 
                   (kulong)(*dpcCtrl)->dfo1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo2.word != (*dpcCtrl)->dfo2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfo2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo2.word, 
                   (kulong)(*dpcCtrl)->dfo2))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo3.word != (*dpcCtrl)->dfo3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfo3  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfo.dfo3.word, 
                   (kulong)(*dpcCtrl)->dfo3))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk1.word != (*dpcCtrl)->dfk1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfk1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk1.word, 
                   (kulong)(*dpcCtrl)->dfk1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk2.word != (*dpcCtrl)->dfk2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfk2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk2.word, 
                   (kulong)(*dpcCtrl)->dfk2))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk3.word != (*dpcCtrl)->dfk3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfk3  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfk.dfk3.word, 
                   (kulong)(*dpcCtrl)->dfk3))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh1.word != (*dpcCtrl)->dfh1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfh1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh1.word, 
                   (kulong)(*dpcCtrl)->dfh1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh2.word != (*dpcCtrl)->dfh2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfh2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh2.word, 
                   (kulong)(*dpcCtrl)->dfh2))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh3.word != (*dpcCtrl)->dfh3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfh3  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfh.dfh3.word, 
                   (kulong)(*dpcCtrl)->dfh3))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfcsr.word != (*dpcCtrl)->dfcsr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfcsr  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfcsr.word, (kulong)(*dpcCtrl)->dfcsr))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth1.word != (*dpcCtrl)->dflsth1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dflsth1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth1.word, 
             (kulong)(*dpcCtrl)->dflsth1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth2.word != (*dpcCtrl)->dflsth2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dflsth2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dflsth.dflsth2.word, 
             (kulong)(*dpcCtrl)->dflsth2))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef.word != (*dpcCtrl)->dfagef) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfagef  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef.word, 
                     (kulong)(*dpcCtrl)->dfagef))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef2.word != (*dpcCtrl)->dfagef2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfagef2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagef2.word, (kulong)(*dpcCtrl)->dfagef2))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagth.word != (*dpcCtrl)->dfagth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfagth  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagth.word, 
                     (kulong)(*dpcCtrl)->dfagth))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagthk.word != (*dpcCtrl)->dfagthk) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dfagthk  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dfagthk.word, (kulong)(*dpcCtrl)->dfagthk))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmctl.word != (*dpcCtrl)->dmctl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dmctl  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmctl.word, (kulong)(*dpcCtrl)->dmctl))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwks.word != (*dpcCtrl)->dmwks) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dmwks  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwks.word, (kulong)(*dpcCtrl)->dmwks))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwkd.word != (*dpcCtrl)->dmwkd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dmwkd  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmwkd.word, (kulong)(*dpcCtrl)->dmwkd))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmagk.word != (*dpcCtrl)->dmagk) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dmagk  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dmagk.word, (kulong)(*dpcCtrl)->dmagk))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dectl.word != (*dpcCtrl)->dectl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dectl  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dectl.word, (kulong)(*dpcCtrl)->dectl))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.denss.word != (*dpcCtrl)->denss) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:denss  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.denss.word, (kulong)(*dpcCtrl)->denss))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.denso.word != (*dpcCtrl)->denso) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:denso  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.denso.word, (kulong)(*dpcCtrl)->denso))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densk.word != (*dpcCtrl)->densk) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:densk  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densk.word, (kulong)(*dpcCtrl)->densk))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densh.word != (*dpcCtrl)->densh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:densh  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densh.word, (kulong)(*dpcCtrl)->densh))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densmgn.word != (*dpcCtrl)->densmgn) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:densmgn  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.densmgn.word, (kulong)(*dpcCtrl)->densmgn))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dendcth.word != (*dpcCtrl)->dendcth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dendcth  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dendcth.word, (kulong)(*dpcCtrl)->dendcth))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.deagk.word != (*dpcCtrl)->deagk) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:deagk  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.deagk.word, (kulong)(*dpcCtrl)->deagk))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagef.word != (*dpcCtrl)->dcagef) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dcagef  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagef.word, 
                     (kulong)(*dpcCtrl)->dcagef))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagth.word != (*dpcCtrl)->dcagth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%d) %s result:dcagth  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.dpc.dcagth.word, 
                     (kulong)(*dpcCtrl)->dcagth))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_DPC_Cntl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_3_print_8(Impro23Print *self, E_IM_PRO_UNIT_NUM unitNo)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Start(%u) result:fctrg  0x%08lx(%u)\n", 
            unitNo, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fctrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fctrg.bit.fctrg));
}

void im_pro_2_3_print_9(Impro23Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Stop(%u %u) result:fctrg  0x%08lx(%u)\n", 
            unitNo, force, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fctrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fctrg.bit.fctrg));
}
#endif

Impro23Print* impro_2_3_print_new(void)
{
	Impro23Print* self = k_object_new_with_private(IMPRO_TYPE_2_3_PRINT, sizeof(Impro23PrintPrivate));

	return self;
}

Impro23Print* impro_2_3_print_get(void)
{
	static Impro23Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_2_3_PRINT, sizeof(Impro23PrintPrivate));
	}

	return self;
}
