/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro12Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro12print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImPro12Print, im_pro_1_2_print, ABS_TYPE_IM_PRO_PRINT)
#define IM_PRO_1_2_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImPro12PrintPrivate, IM_TYPE_PRO_1_2_PRINT))


struct _ImPro12PrintPrivate
{


};


/**
 *IMPL
 */
static void im_pro_1_2_print_constructor(ImPro12Print *self)
{
	ImPro12PrintPrivate *priv = IM_PRO_1_2_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void im_pro_1_2_print_destructor(ImPro12Print *self)
{
	ImPro12PrintPrivate *priv = IM_PRO_1_2_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_2_print_0(ImPro12Print *self,const char* string, T_IM_PRO_SLVS_PMA_INIT* pmaInit)
{
    kuint32 invertSel;
    invertSel = (pmaInit->invertSel.lane0 << 0 & 
                    pmaInit->invertSel.lane1 << 1 &
                    pmaInit->invertSel.lane2 << 2 &
                    pmaInit->invertSel.lane3 << 3 &
                    pmaInit->invertSel.lane4 << 4 &
                    pmaInit->invertSel.lane5 << 5 &
                    pmaInit->invertSel.lane6 << 6 &
                    pmaInit->invertSel.lane7 << 7);
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.pdx != E_IM_PRO_SLVS_PD_STATE_NORMAL) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_pmaInit() %s result:pdx (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.pdx))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr1.bit.invdata != invertSel) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_pmaInit() %s result:invdata(%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr1.bit.invdata,invertSel))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr1.bit.ifvdcnt != pmaInit->multiplicationFactor) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_pmaInit() %s result:ifvdcnt(%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr1.bit.ifvdcnt, pmaInit->multiplicationFactor))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.ipdpllx != pmaInit->optInitParam.enabled) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_pmaInit() %s result:ipdpllx(%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.ipdpllx, pmaInit->optInitParam.enabled))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr0.bit.refsel != pmaInit->optInitParam.refsel) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_pmaInit() %s result:refsel (%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr0.bit.refsel, pmaInit->optInitParam.refsel))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr0.bit.icpcode != pmaInit->optInitParam.icpcode) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_pmaInit() %s result:icpcode(%d) in(%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr0.bit.icpcode, pmaInit->optInitParam.icpcode))
    }; 
}

void im_pro_1_2_print_1(ImPro12Print *self,const char* string, T_IM_PRO_SLVS_PMA_PD* pmaPd)
{
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx0 != pmaPd->lane0PdState) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Pma_Power_Down() %s result:irxpdx0 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx0, pmaPd->lane0PdState))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx1 != pmaPd->lane1PdState) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Pma_Power_Down() %s result:irxpdx1 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx1, pmaPd->lane1PdState))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx2 != pmaPd->lane2PdState) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Pma_Power_Down() %s result:irxpdx2 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx2, pmaPd->lane2PdState))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx3 != pmaPd->lane3PdState) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Pma_Power_Down() %s result:irxpdx3 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx3, pmaPd->lane3PdState))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx4 != pmaPd->lane4PdState) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Pma_Power_Down() %s result:irxpdx4 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx4, pmaPd->lane4PdState))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx5 != pmaPd->lane5PdState) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Pma_Power_Down() %s result:irxpdx5 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx5, pmaPd->lane5PdState))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx6 != pmaPd->lane6PdState) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Pma_Power_Down() %s result:irxpdx6 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx6, pmaPd->lane6PdState))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx7 != pmaPd->lane7PdState) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Pma_Power_Down() %s result:irxpdx7 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.phycr2.bit.irxpdx7, pmaPd->lane7PdState))
    }; 
}

void im_pro_1_2_print_2(ImPro12Print *self,const char* string, T_IM_PRO_SLVS_COMMON_CFG* commonCfg)
{
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr1.bit.StandbyLength != commonCfg->StandbyLength) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:StandbyLength (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr1.bit.StandbyLength, commonCfg->StandbyLength))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr1.bit.StandbySymbolType != commonCfg->StandbySymbolType) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:StandbySymbolType (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr1.bit.StandbySymbolType, commonCfg->StandbySymbolType))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr1.bit.StandbySymbol != commonCfg->StandbySymbol) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:StandbySymbol (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr1.bit.StandbySymbol, commonCfg->StandbySymbol))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr2.bit.DeskewInterval != commonCfg->DeskewInterval) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:DeskewInterval (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr2.bit.DeskewInterval, commonCfg->DeskewInterval))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr2.bit.DeskewLength != commonCfg->DeskewLength) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:DeskewLength (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr2.bit.DeskewLength, commonCfg->DeskewLength))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr2.bit.DeskewSymbolType != commonCfg->DeskewSymbolType) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:DeskewSymbolType (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr2.bit.DeskewSymbolType, commonCfg->DeskewSymbolType))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr2.bit.DeskewSymbol != commonCfg->DeskewSymbol) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:DeskewSymbol (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr2.bit.DeskewSymbol, commonCfg->DeskewSymbol))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr3.bit.IdleSymbolType1 != commonCfg->IdleSymbolType1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:IdleSymbolType1 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr3.bit.IdleSymbolType1, commonCfg->IdleSymbolType1))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr3.bit.IdleSymbol1 != commonCfg->IdleSymbol1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:IdleSymbol1 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr3.bit.IdleSymbol1, commonCfg->IdleSymbol1))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr3.bit.IdleSymbolType0 != commonCfg->IdleSymbolType0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:IdleSymbolType0 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr3.bit.IdleSymbolType0, commonCfg->IdleSymbolType0))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr3.bit.IdleSymbol0 != commonCfg->IdleSymbol0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:IdleSymbol0 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr3.bit.IdleSymbol0, commonCfg->IdleSymbol0))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr4.bit.IdleSymbolType3 != commonCfg->IdleSymbolType3) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:IdleSymbolType3 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr4.bit.IdleSymbolType3, commonCfg->IdleSymbolType3))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr4.bit.IdleSymbol3 != commonCfg->IdleSymbol3) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:IdleSymbol3 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr4.bit.IdleSymbol3, commonCfg->IdleSymbol3))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr4.bit.IdleSymbolType2 != commonCfg->IdleSymbolType2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:IdleSymbolType2 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr4.bit.IdleSymbolType2, commonCfg->IdleSymbolType2))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr4.bit.IdleSymbol2 != commonCfg->IdleSymbol2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() %s result:IdleSymbol2 (%d) (%d)\n", string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.attr4.bit.IdleSymbol2, commonCfg->IdleSymbol2))
    }; 
}

void im_pro_1_2_print_3(ImPro12Print *self,const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType, T_IM_PRO_SLVS_CTRL* slvsCtrl)
{
	if(streamType > E_IM_PRO_SLVS_STREAM_TYPE_B) {
		return;
	}
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].rampd.bit.rampd != slvsCtrl->ramPdState) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Ctrl(%u) %s result:rampd (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].rampd.bit.rampd, slvsCtrl->ramPdState))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].trgr.bit.vden != slvsCtrl->vdoutCtrl) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Ctrl(%u) %s result:vden (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].trgr.bit.vden, slvsCtrl->vdoutCtrl))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].cfgr0.bit.ecccrc != slvsCtrl->ecccrcOpt) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Ctrl(%u) %s result:ecccrc (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].cfgr0.bit.ecccrc, slvsCtrl->ecccrcOpt))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].mmode.bit.lnmaxclp != slvsCtrl->expectVal) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Ctrl(%u) %s result:lnmaxclp (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].mmode.bit.lnmaxclp, slvsCtrl->expectVal))
    }; 
}

void im_pro_1_2_print_4(ImPro12Print *self,const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType, 
                            T_IM_PRO_SLVS_MODE_CFG* modeCtrl)
{
	if(streamType > E_IM_PRO_SLVS_STREAM_TYPE_B) {
		return;
	}

    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].cfgr0.bit.PixelBit != modeCtrl->pixelbit) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:PixelBit (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].cfgr0.bit.PixelBit, modeCtrl->pixelbit))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].cfgr0.bit.LaneNum != modeCtrl->lanenum) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:LaneNum (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].cfgr0.bit.LaneNum, modeCtrl->lanenum))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].cfgr1.bit.LineLength != modeCtrl->linelength) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:LineLength (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].cfgr1.bit.LineLength, modeCtrl->linelength))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].outmd.bit.outmd != modeCtrl->outputFormat) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:outmd (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].outmd.bit.outmd, modeCtrl->outputFormat))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l0out != modeCtrl->swapLane[0]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:l0out (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l0out, modeCtrl->swapLane[0]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l1out != modeCtrl->swapLane[1]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:l1out (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l1out, modeCtrl->swapLane[1]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l2out != modeCtrl->swapLane[2]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:l2out (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l2out, modeCtrl->swapLane[2]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l3out != modeCtrl->swapLane[3]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:l3out (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l3out, modeCtrl->swapLane[3]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l4out != modeCtrl->swapLane[4]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:l4out (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l4out, modeCtrl->swapLane[4]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l5out != modeCtrl->swapLane[5]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:l5out (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l5out, modeCtrl->swapLane[5]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l6out != modeCtrl->swapLane[6]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:l6out (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l6out, modeCtrl->swapLane[6]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l7out != modeCtrl->swapLane[7]) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:l7out (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lswap.bit.l7out, modeCtrl->swapLane[7]))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane0 != modeCtrl->validLane.lane0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:lane0 (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane0, modeCtrl->validLane.lane0))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane1 != modeCtrl->validLane.lane1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:lane1 (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane1, modeCtrl->validLane.lane1))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane2 != modeCtrl->validLane.lane2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:lane2 (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane2, modeCtrl->validLane.lane2))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane3 != modeCtrl->validLane.lane3) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:lane3 (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane3, modeCtrl->validLane.lane3))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane4 != modeCtrl->validLane.lane4) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:lane4 (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane4, modeCtrl->validLane.lane4))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane5 != modeCtrl->validLane.lane5) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:lane5 (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane5, modeCtrl->validLane.lane5))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane6 != modeCtrl->validLane.lane6) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:lane6 (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane6, modeCtrl->validLane.lane6))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane7 != modeCtrl->validLane.lane7) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg(%u) %s result:lane7 (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].vlane.bit.lane7, modeCtrl->validLane.lane7))
    }; 
}                                                                          

void im_pro_1_2_print_5(ImPro12Print *self,const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType, T_IM_PRO_SLVS_TRIM_CFG* trimCtrl)
{
	if(streamType > E_IM_PRO_SLVS_STREAM_TYPE_B) {
		return;
	}
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].outmd.bit.trmg != trimCtrl->enabled) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Trim_Cfg(%u) %s result:trmg (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].outmd.bit.trmg, trimCtrl->enabled))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].hsadd.bit.hsadd != trimCtrl->startX) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Trim_Cfg(%u) %s result:hsadd (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].hsadd.bit.hsadd, trimCtrl->startX))
    }; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].hsize.bit.hsize != trimCtrl->width) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Trim_Cfg(%u) %s result:hsize (%d) (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].hsize.bit.hsize, trimCtrl->width))
    }; 
}

void im_pro_1_2_print_6(ImPro12Print *self,const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType, T_IM_PRO_SLVS_STATUS* status)
{
	if(streamType > E_IM_PRO_SLVS_STREAM_TYPE_B) {
		return;
	}
    if(status->embeddedDataDetect != ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].ebdst.bit.ebd) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Get_Status(%u) %s result:VDINO (%d) reg_val (%d)\n", 
        streamType, string, status->embeddedDataDetect, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].ebdst.bit.ebd))
    }; 
        
    if(status->ebdStoredLineNum != ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].ebdst.bit.lnum) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Get_Status(%u) %s result:VDINO (%d) reg_val (%d)\n", 
        streamType, string, status->ebdStoredLineNum, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].ebdst.bit.lnum))
    }; 
        
    if(status->expectValueDiscontinuity != ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lnest.bit.expln) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Get_Status(%u) %s result:VDINO (%d) reg_val (%d)\n", 
        streamType, string, status->expectValueDiscontinuity, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lnest.bit.expln))
    }; 
        
    if(status->lineNumDiscontinuity != ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lnest.bit.detln) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Get_Status(%u) %s result:VDINO (%d) reg_val (%d)\n", 
        streamType, string, status->lineNumDiscontinuity, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streamType].lnest.bit.detln))
    }; 
}

void im_pro_1_2_print_7(ImPro12Print *self,const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType)
{
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[ImPro_SLVS_STREAM_TYPE_A].trgr.bit.trg != D_IM_PRO_TRG_STATUS_RUNNING) { 
        DriverCommon_DDIM_PRINT(("impro_senslvs_status(%d) %s result:trgr (%d)\n", 
        streamType, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[ImPro_SLVS_STREAM_TYPE_A].trgr.bit.trg))
    }; 
}

void im_pro_1_2_print_8(ImPro12Print *self,const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType, kuchar force)
{
    if(((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[ImPro_SLVS_STREAM_TYPE_A].trgr.bit.trg != D_IM_PRO_TRG_STATUS_STOPPED) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Stop(%u, %u) %s result:trgr (%d)\n", 
        streamType, force, string, 
        ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[ImPro_SLVS_STREAM_TYPE_A].trgr.bit.trg))
    }; 
}
#endif

ImPro12Print* im_pro_1_2_print_new(void)
{
	ImPro12Print* self = k_object_new_with_private(IM_TYPE_PRO_1_2_PRINT, sizeof(ImPro12PrintPrivate));

	return self;
}

ImPro12Print* im_pro_1_2_print_get(void)
{
	static ImPro12Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_1_2_PRINT, sizeof(ImPro12PrintPrivate));
	}

	return self;
}
