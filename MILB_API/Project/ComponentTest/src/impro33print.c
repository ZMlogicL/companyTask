/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro33Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro33print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro33Print, impro_3_3_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_3_3_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro33PrintPrivate, IMPRO_TYPE_3_3_PRINT))


struct _Impro33PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_3_3_print_constructor(Impro33Print *self)
{
	Impro33PrintPrivate *priv = IMPRO_3_3_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_3_3_print_destructor(Impro33Print *self)
{
	Impro33PrintPrivate *priv = IMPRO_3_3_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_3_3_print_0(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_AREA_INFO* fshdCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdh.bit.fshdh != fshdCtrl->posX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Area(%u) %s result:fshdh 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdh.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdh.bit.fshdh ,fshdCtrl->posX));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdv.bit.fshdv != fshdCtrl->posY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Area(%u) %s result:fshdv 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdv.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdv.bit.fshdv ,fshdCtrl->posY));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhw.bit.fshdhw != fshdCtrl->width) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Area(%u) %s result:fshdhw 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhw.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhw.bit.fshdhw ,fshdCtrl->width));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdvw.bit.fshdvw != fshdCtrl->lines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Area(%u) %s result:fshdvw 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdvw.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdvw.bit.fshdvw ,fshdCtrl->lines));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Area(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_3_print_1(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                        T_IM_PRO_FSHD_BLEND_CTRL* fshdCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdbc.bit.fshdbc0 != fshdCtrl->shadingBlend_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Blend(%u) %s result:fshdbc0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdbc.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdbc.bit.fshdbc0,fshdCtrl->shadingBlend_0));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdbc.bit.fshdbc1 != fshdCtrl->shadingBlend_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Blend(%u) %s result:fshdbc1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdbc.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdbc.bit.fshdbc1,fshdCtrl->shadingBlend_1));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Blend(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_3_print_2(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                        T_IM_PRO_FSHD_FRAME_CTRL* fshdCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsctl.bit.fsfmt != fshdCtrl->fsctl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fsfmt 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsctl.bit.fsfmt ,fshdCtrl->fsctl));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubpr.bit.fssubprh != fshdCtrl->frameHorizontalSize) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fssubprh 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubpr.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubpr.bit.fssubprh,fshdCtrl->frameHorizontalSize));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubpr.bit.fssubprv != fshdCtrl->frameVerticalSize) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fssubprv 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubpr.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubpr.bit.fssubprv,fshdCtrl->frameVerticalSize));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubsp.bit.fssubsph != fshdCtrl->horizontalPixel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fssubsph 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubsp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubsp.bit.fssubsph,fshdCtrl->horizontalPixel));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubsp.bit.fssubspv != fshdCtrl->verticalPixel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fssubspv 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubsp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubsp.bit.fssubspv,fshdCtrl->verticalPixel));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubdr.bit.fssubdrm != fshdCtrl->InverseBase) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fssubdrm 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubdr.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubdr.bit.fssubdrm,fshdCtrl->InverseBase));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubdr.bit.fssubdre != fshdCtrl->InverseExponent) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fssubdre 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubdr.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubdr.bit.fssubdre,fshdCtrl->InverseExponent));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhwph.bit.fshdhwph != fshdCtrl->montagePosH) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fshdhwph 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhwph.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhwph.bit.fshdhwph ,fshdCtrl->montagePosH));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubst.bit.fssubsth != fshdCtrl->startPosH) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fssubsth 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubst.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubst.bit.fssubsth,fshdCtrl->startPosH));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubst.bit.fssubstv != fshdCtrl->startPosV) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fssubstv 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubst.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubst.bit.fssubstv,fshdCtrl->startPosV));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsa1.bit.fsarr != fshdCtrl->magnificationR) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fsarr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsa1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsa1.bit.fsarr,fshdCtrl->magnificationR));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsa1.bit.fsagr != fshdCtrl->magnificationGr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fsagr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsa1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsa1.bit.fsagr,fshdCtrl->magnificationGr));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.FSA2.bit.fsagb != fshdCtrl->magnificationGb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fsagb 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.FSA2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.FSA2.bit.fsagb,fshdCtrl->magnificationGb));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.FSA2.bit.fsabb != fshdCtrl->magnificationB) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fsabb 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.FSA2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.FSA2.bit.fsabb,fshdCtrl->magnificationB));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhcctl.bit.fshcen != fshdCtrl->satCorrectionEnabled) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fshcen 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhcctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhcctl.bit.fshcen,fshdCtrl->satCorrectionEnabled));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp1.bit.fsslprr != fshdCtrl->satSlopeGain[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fsslprr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp1.bit.fsslprr,fshdCtrl->satSlopeGain[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp1.bit.fsslpgr != fshdCtrl->satSlopeGain[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fsslpgr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp1.bit.fsslpgr,fshdCtrl->satSlopeGain[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp2.bit.fsslpgb != fshdCtrl->satSlopeGain[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fsslpgb 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp2.bit.fsslpgb,fshdCtrl->satSlopeGain[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp2.bit.fsslpbb != fshdCtrl->satSlopeGain[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) %s result:fsslpbb 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp2.bit.fsslpbb,fshdCtrl->satSlopeGain[3]));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Frame(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_3_print_3(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                        T_IM_PRO_FSHD_CONCENTRIC_CTRL* fshdCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl1.bit.csstbl != fshdCtrl->selectRam) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:csstbl 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl1.bit.csstbl ,fshdCtrl->selectRam));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.bit.csfmt != fshdCtrl->selectFormat) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:csfmt 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.bit.csfmt,fshdCtrl->selectFormat));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.bit.cshdlir != fshdCtrl->interpolated_val) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:cshdlir 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.bit.cshdlir,fshdCtrl->interpolated_val));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.bit.cshdparh != fshdCtrl->intervalH) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:cshdparh 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.bit.cshdparh ,fshdCtrl->intervalH));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.bit.cshdparv != fshdCtrl->intervalV) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:cshdparv 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.bit.cshdparv ,fshdCtrl->intervalV));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls1.bit.cstblsrr != fshdCtrl->startAddressR) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:cstblsrr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls1.bit.cstblsrr,fshdCtrl->startAddressR));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls1.bit.cstblsgr != fshdCtrl->startAddressGr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:cstblsgr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls1.bit.cstblsgr,fshdCtrl->startAddressGr));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls2.bit.cstblsgb != fshdCtrl->startAddressGb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:cstblsgb 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls2.bit.cstblsgb,fshdCtrl->startAddressGb));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls2.bit.cstblsbb != fshdCtrl->startAddressB) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:cstblsbb 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls2.bit.cstblsbb,fshdCtrl->startAddressB));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdd.bit.cshddo != fshdCtrl->offset) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:cshddo 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdd.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdd.bit.cshddo,fshdCtrl->offset));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdd.bit.cshddm != fshdCtrl->clipValue) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:cshddm 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdd.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdd.bit.cshddm,fshdCtrl->clipValue));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdoa.bit.cshdoah != fshdCtrl->posH) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:cshdoah 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdoa.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdoa.bit.cshdoah,fshdCtrl->posH));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdoa.bit.cshdoav != fshdCtrl->posV) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:cshdoav 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdoa.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdoa.bit.cshdoav,fshdCtrl->posV));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa1.bit.csarr != fshdCtrl->magnificationR) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:csarr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa1.bit.csarr,fshdCtrl->magnificationR));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa1.bit.csagr != fshdCtrl->magnificationGr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:csagr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa1.bit.csagr,fshdCtrl->magnificationGr));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa2.bit.csagb != fshdCtrl->magnificationGb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:csagb 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa2.bit.csagb,fshdCtrl->magnificationGb));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa2.bit.csabb != fshdCtrl->magnificationB) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) %s result:csabb 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa2.bit.csabb,fshdCtrl->magnificationB));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Concentric(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_3_print_5(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar tblSel, kint32 ercd, kint32 cmpErcd)
{
    if( ercd == DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Table(%u %u) %s API result(0x%x) memcmp result(0x%x)\n\n", 
            unitNo, tblSel, string, ercd, cmpErcd));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Table(%u %u) error ercd=0x%x\n", 
            unitNo, tblSel, ercd));
    }
}

void im_pro_3_3_print_6(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, USHORT fshdCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fswric.bit.fswric != fshdCtrl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Coeff_Read_Line_Wait(%u) %s result:csabb 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fswric.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fswric.bit.fswric ,fshdCtrl));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_Coeff_Read_Line_Wait(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_3_print_7(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, const T_IM_PRO_RDMA_FSHD_ADDR** fshdCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdctl.word != (*fshdCtrl)->fshdctl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fshdctl 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdctl.word , (kulong)(*fshdCtrl)->fshdctl));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhwph.word != (*fshdCtrl)->fshdhwph) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fshdhwph 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhwph.word, (kulong)(*fshdCtrl)->fshdhwph));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdbc.word != (*fshdCtrl)->fshdbc) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fshdbc 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdbc.word, (kulong)(*fshdCtrl)->fshdbc));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul1.word != (*fshdCtrl)->fsul1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fsul1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul1.word , (kulong)(*fshdCtrl)->fsul1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul2.word != (*fshdCtrl)->fsul2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fsul2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul2.word , (kulong)(*fshdCtrl)->fsul2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsctl.word != (*fshdCtrl)->fsctl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fsctl 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsctl.word , (kulong)(*fshdCtrl)->fsctl));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubpr.word != (*fshdCtrl)->fssubpr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fssubpr 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubpr.word , (kulong)(*fshdCtrl)->fssubpr));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubsp.word != (*fshdCtrl)->fssubsp) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fssubsp 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubsp.word , (kulong)(*fshdCtrl)->fssubsp));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubdr.word != (*fshdCtrl)->fssubdr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fssubdr 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubdr.word , (kulong)(*fshdCtrl)->fssubdr));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubst.word != (*fshdCtrl)->fssubst) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fssubst 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fssubst.word , (kulong)(*fshdCtrl)->fssubst));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsa1.word != (*fshdCtrl)->fsa1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fsa1  0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsa1.word, (kulong)(*fshdCtrl)->fsa1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.FSA2.word != (*fshdCtrl)->FSA2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:FSA2  0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.FSA2.word, (kulong)(*fshdCtrl)->FSA2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl1.word != (*fshdCtrl)->csctl1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:csctl1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl1.word, (kulong)(*fshdCtrl)->csctl1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.word != (*fshdCtrl)->csctl2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:csctl2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csctl2.word, (kulong)(*fshdCtrl)->csctl2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstblst.word != (*fshdCtrl)->cstblst) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:cstblst 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstblst.word , (kulong)(*fshdCtrl)->cstblst));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls1.word != (*fshdCtrl)->cstbls1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:cstbls1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls1.word , (kulong)(*fshdCtrl)->cstbls1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls2.word != (*fshdCtrl)->cstbls2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:cstbls2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cstbls2.word , (kulong)(*fshdCtrl)->cstbls2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdd.word != (*fshdCtrl)->cshdd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:cshdd 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdd.word , (kulong)(*fshdCtrl)->cshdd));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdoa.word != (*fshdCtrl)->cshdoa) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:cshdoa 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.cshdoa.word, (kulong)(*fshdCtrl)->cshdoa));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa1.word != (*fshdCtrl)->csa1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:csa1  0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa1.word, (kulong)(*fshdCtrl)->csa1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa2.word != (*fshdCtrl)->csa2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:csa2  0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.csa2.word, (kulong)(*fshdCtrl)->csa2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhcctl.word != (*fshdCtrl)->fshdhcctl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fshdhcctl 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdhcctl.word , (kulong)(*fshdCtrl)->fshdhcctl));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp1.word != (*fshdCtrl)->fsslp1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fsslp1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp1.word, (kulong)(*fshdCtrl)->fsslp1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp2.word != (*fshdCtrl)->fsslp2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) %s result:fsslp2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsslp2.word, (kulong)(*fshdCtrl)->fsslp2));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Cntl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_3_print_8(Impro33Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar tblSel, kint32 ercd, 
                           const T_IM_PRO_RDMA_FSHD_CTBL_ADDR** fshdCtrl)
{
    const T_IM_PRO_FSHD_INFO* fshdInfo;

    if( ercd == DdimUserCustom_E_OK) {
        im_pro_comm_get_fshd_reg_info( unitNo, &fshdInfo);
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Ctbl(%u %u) %s result:fshdctbl 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, tblSel, string, (kulong)fshdInfo->tblRegPtr, (kulong)(*fshdCtrl)->fshdctbl));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHD_Ctbl(%u %u) error ercd=0x%x\n", unitNo, tblSel, ercd));
    }
}
#endif //ifndef CO_CT_IM_PRO_DISABLE

Impro33Print* impro_3_3_print_new(void)
{
	Impro33Print* self = k_object_new_with_private(IMPRO_TYPE_3_3_PRINT, sizeof(Impro33PrintPrivate));

	return self;
}

Impro33Print* impro_3_3_print_get(void)
{
	static Impro33Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_3_3_PRINT, sizeof(Impro33PrintPrivate));
	}

	return self;
}
