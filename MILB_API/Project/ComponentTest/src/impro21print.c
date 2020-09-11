/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro21Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro21print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro21Print, impro_2_1_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_2_1_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro21PrintPrivate, IMPRO_TYPE_2_1_PRINT))


struct _Impro21PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_2_1_print_constructor(Impro21Print *self)
{
	Impro21PrintPrivate *priv = IMPRO_2_1_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_2_1_print_destructor(Impro21Print *self)
{
	Impro21PrintPrivate *priv = IMPRO_2_1_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_2_1_print_0(Impro21Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FSHDL_CH ch)
{
    const T_IM_PRO_SRO_FSHDL_INFO* fshdlInfo;
    im_pro_comm_get_fshdl_reg_info( unitNo, ch, &fshdlInfo);

    DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Start(%u %u) result: 0x%08lx(%u)\n", 
            unitNo, ch, (kulong)&fshdlInfo->regPtr->ffshtrg.word, 
            fshdlInfo->regPtr->ffshtrg.bit.ffshtrg));
}

void im_pro_2_1_print_1(Impro21Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FSHDL_CH ch, kuchar force)
{
    const T_IM_PRO_SRO_FSHDL_INFO* fshdlInfo;
    im_pro_comm_get_fshdl_reg_info( unitNo, ch, &fshdlInfo);

    DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Stop(%u %u %u) result:ffshtrg  0x%08lx(%u)\n", 
            unitNo, ch, force, (kulong)&fshdlInfo->regPtr->ffshtrg.word, 
            fshdlInfo->regPtr->ffshtrg.bit.ffshtrg));
}

void im_pro_2_1_print_2(Impro21Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FSHDL_CH ch, 
                        kint32 ercd, T_IM_PRO_FSHDL_COMMON_CTRL* fshdlCtrl)
{
    const T_IM_PRO_SRO_FSHDL_INFO* fshdlInfo;

    if( ercd == DdimUserCustom_E_OK) {
        im_pro_comm_get_fshdl_reg_info( unitNo, ch, &fshdlInfo);
        if(fshdlInfo->regPtr->ffshctl.bit.ffshptmd != fshdlCtrl->montageMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Ctrl(%u %u) %s result:FSHDLH 0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshctl.word, 
            fshdlInfo->regPtr->ffshctl.bit.ffshptmd,fshdlCtrl->montageMode))
        };

        if(fshdlInfo->regPtr->ffshul1.bit.ffshulrr != fshdlCtrl->clipR) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Ctrl(%u %u) %s result:FSHDLH 0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshul1.word, 
            fshdlInfo->regPtr->ffshul1.bit.ffshulrr,fshdlCtrl->clipR))
        };

        if(fshdlInfo->regPtr->ffshul1.bit.ffshulgr != fshdlCtrl->clipGr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Ctrl(%u %u) %s result:FSHDLH 0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshul1.word, 
            fshdlInfo->regPtr->ffshul1.bit.ffshulgr,fshdlCtrl->clipGr))
        };

        if(fshdlInfo->regPtr->ffshul2.bit.ffshulgb != fshdlCtrl->clipGb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Ctrl(%u %u) %s result:FSHDLH 0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshul2.word, 
            fshdlInfo->regPtr->ffshul2.bit.ffshulgb,fshdlCtrl->clipGb))
        };

        if(fshdlInfo->regPtr->ffshul2.bit.ffshulbb != fshdlCtrl->clipB) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Ctrl(%u %u) %s result:FSHDLH 0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshul2.word, 
            fshdlInfo->regPtr->ffshul2.bit.ffshulbb,fshdlCtrl->clipB))
        };
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Ctrl(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_1_print_3(Impro21Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FSHDL_CH ch, 
                        kint32 ercd, T_IM_PRO_FSHDL_BLEND_CTRL* fshdlCtrl)
{
    const T_IM_PRO_SRO_FSHDL_INFO* fshdlInfo;

    if( ercd == DdimUserCustom_E_OK) {
        im_pro_comm_get_fshdl_reg_info( unitNo, ch, &fshdlInfo);
        if(fshdlInfo->regPtr->ffshbc.bit.ffshbc0 != fshdlCtrl->shadingBlend_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Blend(%u %u) %s result:FSHDLH  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshbc.word, 
            fshdlInfo->regPtr->ffshbc.bit.ffshbc0,fshdlCtrl->shadingBlend_0))
        };

        if(fshdlInfo->regPtr->ffshbc.bit.ffshbc1 != fshdlCtrl->shadingBlend_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Blend(%u %u) %s result:FSHDLH  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshbc.word, 
            fshdlInfo->regPtr->ffshbc.bit.ffshbc1,fshdlCtrl->shadingBlend_1))
        };
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Blend(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_1_print_4(Impro21Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                            E_IM_PRO_FSHDL_CH ch, kint32 ercd, kuchar fshdlCtrl)
{
    const T_IM_PRO_SRO_FSHDL_INFO* fshdlInfo;

    if( ercd == DdimUserCustom_E_OK) {
        im_pro_comm_get_fshdl_reg_info( unitNo, ch, &fshdlInfo);
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_PAEN(%u %u) %s result:FSHDLH 0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshpaen.word, 
            fshdlInfo->regPtr->ffshpaen.bit.ffshpaen,fshdlCtrl));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_PAEN(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_1_print_5(Impro21Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FSHDL_CH ch, 
                        kint32 ercd, T_IM_PRO_AREA_INFO* fshdlCtrl)
{
    const T_IM_PRO_SRO_FSHDL_INFO* fshdlInfo;

    if( ercd == DdimUserCustom_E_OK) {
        im_pro_comm_get_fshdl_reg_info( unitNo, ch, &fshdlInfo);
        if(fshdlInfo->regPtr->ffshv.bit.ffshv != fshdlCtrl->posY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Area(%u %u) %s result:FSHDLH 0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshv.word, 
            fshdlInfo->regPtr->ffshv.bit.ffshv,fshdlCtrl->posY))
        };

        if(fshdlInfo->regPtr->ffshh.bit.ffshh != fshdlCtrl->posX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Area(%u %u) %s result:FSHDLH 0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshh.word, 
            fshdlInfo->regPtr->ffshh.bit.ffshh,fshdlCtrl->posX))
        };

        if(fshdlInfo->regPtr->ffshvw.bit.ffshvw != fshdlCtrl->lines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Area(%u %u) %s result:FSHDLH 0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshvw.word, 
            fshdlInfo->regPtr->ffshvw.bit.ffshvw,fshdlCtrl->lines))
        };

        if(fshdlInfo->regPtr->ffshhw.bit.ffshhw != fshdlCtrl->width) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Area(%u %u) %s result:FSHDLH 0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshhw.word, 
            fshdlInfo->regPtr->ffshhw.bit.ffshhw,fshdlCtrl->width))
        };
    
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Area(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_1_print_6(Impro21Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FSHDL_CH ch, 
                        kint32 ercd, T_IM_PRO_FSHDL_FRAME_CTRL* fshdlCtrl)
{
    const T_IM_PRO_SRO_FSHDL_INFO* fshdlInfo;

    if( ercd == DdimUserCustom_E_OK) {
        im_pro_comm_get_fshdl_reg_info( unitNo, ch, &fshdlInfo);
        if(fshdlInfo->regPtr->ffshgfmt.bit.ffshgfmt != fshdlCtrl->selectFormat) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshgfmt  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshgfmt.word, 
            fshdlInfo->regPtr->ffshgfmt.bit.ffshgfmt,fshdlCtrl->selectFormat))
        };

        if(fshdlInfo->regPtr->ffshsubpr.bit.ffshsubprh != fshdlCtrl->frameHorizontalSize) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshsubprh  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubpr.word, 
            fshdlInfo->regPtr->ffshsubpr.bit.ffshsubprh,fshdlCtrl->frameHorizontalSize))
        };

        if(fshdlInfo->regPtr->ffshsubpr.bit.ffshsubprv != fshdlCtrl->frameVerticalSize) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshsubprv  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubpr.word, 
            fshdlInfo->regPtr->ffshsubpr.bit.ffshsubprv,fshdlCtrl->frameVerticalSize))
        };

        if(fshdlInfo->regPtr->ffshsubsp.bit.ffshsubsph != fshdlCtrl->horizontalPixel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshsubsph  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubsp.word, 
            fshdlInfo->regPtr->ffshsubsp.bit.ffshsubsph,fshdlCtrl->horizontalPixel))
        };

        if(fshdlInfo->regPtr->ffshsubsp.bit.ffshsubspv != fshdlCtrl->verticalPixel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshsubspv  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubsp.word, 
            fshdlInfo->regPtr->ffshsubsp.bit.ffshsubspv,fshdlCtrl->verticalPixel))
        };

        if(fshdlInfo->regPtr->ffshsubdr.bit.ffshsubdrm != fshdlCtrl->InverseBase) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshsubdrm  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubdr.word, 
            fshdlInfo->regPtr->ffshsubdr.bit.ffshsubdrm,fshdlCtrl->InverseBase))
        };

        if(fshdlInfo->regPtr->ffshsubdr.bit.ffshsubdre != fshdlCtrl->InverseExponent) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshsubdre  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubdr.word, 
            fshdlInfo->regPtr->ffshsubdr.bit.ffshsubdre,fshdlCtrl->InverseExponent))
        };

        if(fshdlInfo->regPtr->ffshsubst.bit.ffshsubsth != fshdlCtrl->startPosH) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshsubsth  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubst.word, 
            fshdlInfo->regPtr->ffshsubst.bit.ffshsubsth,fshdlCtrl->startPosH))
        };

        if(fshdlInfo->regPtr->ffshsubst.bit.ffshsubstv != fshdlCtrl->startPosV) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshsubstv  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubst.word, 
            fshdlInfo->regPtr->ffshsubst.bit.ffshsubstv,fshdlCtrl->startPosV))
        };

        if(fshdlInfo->regPtr->ffshhwph.bit.ffshhwph != fshdlCtrl->montagePosH) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshhwph  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshhwph.word, 
            fshdlInfo->regPtr->ffshhwph.bit.ffshhwph,fshdlCtrl->montagePosH))
        };

        if(fshdlInfo->regPtr->ffshcctl.bit.ffshcen != fshdlCtrl->satCorrectionEnabled) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshcen  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshcctl.word, 
            fshdlInfo->regPtr->ffshcctl.bit.ffshcen,fshdlCtrl->satCorrectionEnabled))
        };

        if(fshdlInfo->regPtr->ffshlp1.bit.ffshlprr != fshdlCtrl->satSlopeGain[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshlprr  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshlp1.word, 
            fshdlInfo->regPtr->ffshlp1.bit.ffshlprr,fshdlCtrl->satSlopeGain[0]))
        };

        if(fshdlInfo->regPtr->ffshlp1.bit.ffshlpgr != fshdlCtrl->satSlopeGain[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshlpgr  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshlp1.word, 
            fshdlInfo->regPtr->ffshlp1.bit.ffshlpgr,fshdlCtrl->satSlopeGain[1]))
        };

        if(fshdlInfo->regPtr->ffshlp2.bit.ffshlpgb != fshdlCtrl->satSlopeGain[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshlpgb  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshlp2.word, 
            fshdlInfo->regPtr->ffshlp2.bit.ffshlpgb,fshdlCtrl->satSlopeGain[2]))
        };

        if(fshdlInfo->regPtr->ffshlp2.bit.ffshlpbb != fshdlCtrl->satSlopeGain[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) %s result:ffshlpbb  0x%08lx(%u) in(%u)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshlp2.word, 
            fshdlInfo->regPtr->ffshlp2.bit.ffshlpbb,fshdlCtrl->satSlopeGain[3]))
        };
    
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Frame(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_1_print_7(Impro21Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FSHDL_CH ch, 
                            kint32 ercd, USHORT fshdlCtrl)
{
    const T_IM_PRO_SRO_FSHDL_INFO* fshdlInfo;

    if( ercd == DdimUserCustom_E_OK) {
        im_pro_comm_get_fshdl_reg_info( unitNo, ch, &fshdlInfo);
        if(fshdlInfo->regPtr->ffshwric.bit.ffshwric != fshdlCtrl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Coeff_Read_Line_Wait(%u %u) %s result:ffshgfmt  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshgfmt.word, 
            fshdlInfo->regPtr->ffshwric.bit.ffshwric,fshdlCtrl))
        };
    
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHDL_Set_Coeff_Read_Line_Wait(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_1_print_8(Impro21Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FSHDL_CH ch, 
                            kint32 ercd, const T_IM_PRO_RDMA_FSHDL_ADDR** fshdlCtrl)
{
    const T_IM_PRO_SRO_FSHDL_INFO* fshdlInfo;

    if( ercd == DdimUserCustom_E_OK) {
        im_pro_comm_get_fshdl_reg_info( unitNo, ch, &fshdlInfo);
        if((kulong)&fshdlInfo->regPtr->ffshbc.word !=  (*fshdlCtrl)->ffshbc) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshbc    \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshbc.word, 
                        (kulong)(*fshdlCtrl)->ffshbc))
        };

        if((kulong)&fshdlInfo->regPtr->ffshul1.word !=  (*fshdlCtrl)->ffshul1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshul1       \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshul1.word, 
                        (kulong)(*fshdlCtrl)->ffshul1))
        };

        if((kulong)&fshdlInfo->regPtr->ffshul2.word !=  (*fshdlCtrl)->ffshul2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshul2       \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshul2.word, 
                        (kulong)(*fshdlCtrl)->ffshul2))
        };

        if((kulong)&fshdlInfo->regPtr->ffshgfmt.word !=  (*fshdlCtrl)->ffshgfmt) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshgfmt      \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshgfmt.word, 
                        (kulong)(*fshdlCtrl)->ffshgfmt))
        };

        if((kulong)&fshdlInfo->regPtr->ffshsubpr.word !=  (*fshdlCtrl)->ffshsubpr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshsubpr     \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubpr.word, 
                        (kulong)(*fshdlCtrl)->ffshsubpr))
        };

        if((kulong)&fshdlInfo->regPtr->ffshsubsp.word !=  (*fshdlCtrl)->ffshsubsp) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshsubsp     \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubsp.word, 
                        (kulong)(*fshdlCtrl)->ffshsubsp))
        };

        if((kulong)&fshdlInfo->regPtr->ffshsubdr.word !=  (*fshdlCtrl)->ffshsubdr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshsubdr     \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubdr.word, 
                        (kulong)(*fshdlCtrl)->ffshsubdr))
        };

        if((kulong)&fshdlInfo->regPtr->ffshsubst.word !=  (*fshdlCtrl)->ffshsubst) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshsubst     \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshsubst.word, 
                        (kulong)(*fshdlCtrl)->ffshsubst))
        };

        if((kulong)&fshdlInfo->regPtr->ffshctl.word !=  (*fshdlCtrl)->ffshctl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshctl       \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshctl.word, 
                        (kulong)(*fshdlCtrl)->ffshctl))
        };

        if((kulong)&fshdlInfo->regPtr->ffshhwph.word !=  (*fshdlCtrl)->ffshhwph) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshhwph      \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshhwph.word, 
                        (kulong)(*fshdlCtrl)->ffshhwph))
        };

        if((kulong)&fshdlInfo->regPtr->ffshcctl.word !=  (*fshdlCtrl)->ffshcctl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshcctl      \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshcctl.word, 
                        (kulong)(*fshdlCtrl)->ffshcctl))
        };

        if((kulong)&fshdlInfo->regPtr->ffshlp1.word !=  (*fshdlCtrl)->ffshlp1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshlp1       \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshlp1.word, 
                        (kulong)(*fshdlCtrl)->ffshlp1))
        };

        if((kulong)&fshdlInfo->regPtr->ffshlp2.word !=  (*fshdlCtrl)->ffshlp2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) %s result:ffshlp2       \
                        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
                        unitNo, ch, string, (kulong)&fshdlInfo->regPtr->ffshlp2.word, 
                        (kulong)(*fshdlCtrl)->ffshlp2))
        };
    
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FSHDL_Cntl(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_1_print_9(Impro21Print *self, E_IM_PRO_UNIT_NUM unitNo)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Start(%u) result:cagtrg 0x%08lx(%u)\n", 
            unitNo, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagtrg.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagtrg.bit.cagtrg));
}
#endif

Impro21Print* impro_2_1_print_new(void)
{
	Impro21Print* self = k_object_new_with_private(IMPRO_TYPE_2_1_PRINT, sizeof(Impro21PrintPrivate));

	return self;
}

Impro21Print* impro_2_1_print_get(void)
{
	static Impro21Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_2_1_PRINT, sizeof(Impro21PrintPrivate));
	}

	return self;
}
