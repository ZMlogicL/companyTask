/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro24Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro24print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro24Print, impro_2_4_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_2_4_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro24PrintPrivate, IMPRO_TYPE_2_4_PRINT))


struct _Impro24PrintPrivate
{


};


/**
 *IMPL 
 */
static void impro_2_4_print_constructor(Impro24Print *self)
{
	Impro24PrintPrivate *priv = IMPRO_2_4_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_2_4_print_destructor(Impro24Print *self)
{
	Impro24PrintPrivate *priv = IMPRO_2_4_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *PUBLIC 
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_2_4_print_0(Impro24Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_FFC_CTRL* ffcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubpr.bit.fcsubprh != ffcCtrl->coefHorizontalSize) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Ctrl(%u) %s result:fcsubprh  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubpr.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubpr.bit.fcsubprh,ffcCtrl->coefHorizontalSize))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubpr.bit.fcsubprv != ffcCtrl->coefVerticalSize) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Ctrl(%u) %s result:fcsubprv  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubpr.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubpr.bit.fcsubprv,ffcCtrl->coefVerticalSize))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubsp.bit.fcsubsph != ffcCtrl->horizontalPixel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Ctrl(%u) %s result:fcsubsph  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubsp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubsp.bit.fcsubsph,ffcCtrl->horizontalPixel))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubsp.bit.fcsubspv != ffcCtrl->verticalPixel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Ctrl(%u) %s result:fcsubspv  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubsp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubsp.bit.fcsubspv,ffcCtrl->verticalPixel))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubdr.bit.fcsubdrm != ffcCtrl->inverseBase) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Ctrl(%u) %s result:fcsubdrm  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubdr.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubdr.bit.fcsubdrm,ffcCtrl->inverseBase))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubdr.bit.fcsubdre != ffcCtrl->inverseExponent) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Ctrl(%u) %s result:fcsubdre  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubdr.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubdr.bit.fcsubdre,ffcCtrl->inverseExponent))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubst.bit.fcsubsth != ffcCtrl->coefPosX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Ctrl(%u) %s result:fcsubsth  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubst.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubst.bit.fcsubsth,ffcCtrl->coefPosX))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubst.bit.fcsubstv != ffcCtrl->coefPosY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Ctrl(%u) %s result:fcsubstv  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubst.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubst.bit.fcsubstv,ffcCtrl->coefPosY))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_4_print_1(Impro24Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_FFC_BLEND_CTRL* ffcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcbc.bit.fcbc0 != ffcCtrl->blendRatio0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_Blend(%u) %s result:fcbc0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcbc.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcbc.bit.fcbc0,ffcCtrl->blendRatio0))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcbc.bit.fcbc1 != ffcCtrl->blendRatio1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_Blend(%u) %s result:fcbc1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcbc.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcbc.bit.fcbc1,ffcCtrl->blendRatio1))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_Blend(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_4_print_2(Impro24Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_PAEN(%u %u) result:paen  0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcpaen.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcpaen.bit.fcpaen));
    DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_PAEN(%u %u) result:fctrg  0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fctrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fctrg.bit.fctrg));
}

void im_pro_2_4_print_3(Impro24Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_FFC_AREA* ffcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fch.bit.fch != ffcCtrl->posX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_Area(%u) %s result:fch  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fch.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fch.bit.fch,ffcCtrl->posX))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcv.bit.fcv != ffcCtrl->posY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_Area(%u) %s result:fcv  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcv.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcv.bit.fcv,ffcCtrl->posY))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fchw.bit.fchw != ffcCtrl->width) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_Area(%u) %s result:fchw  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fchw.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fchw.bit.fchw,ffcCtrl->width))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcvw.bit.fcvw != ffcCtrl->lines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_Area(%u) %s result:fcvw  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcvw.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcvw.bit.fcvw,ffcCtrl->lines))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_Area(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_4_print_4(Impro24Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, USHORT ffcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcwric.bit.fcwric != ffcCtrl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_Coeff_Read_Line_Wait(%u) %s result:fcwric  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcwric.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcwric.bit.fcwric,ffcCtrl))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FFC_Set_Coeff_Read_Line_Wait(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_4_print_5(Impro24Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                        kint32 ercd, const T_IM_PRO_RDMA_FFC_ADDR** ffcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcbc.word != (*ffcCtrl)->fcbc) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFC_Cntl(%u) %s result:dcagth  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcbc.word, 
               (kulong)(*ffcCtrl)->fcbc))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubpr.word != (*ffcCtrl)->fcsubpr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFC_Cntl(%u) %s result:dcagth  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubpr.word, 
            (kulong)(*ffcCtrl)->fcsubpr))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubsp.word != (*ffcCtrl)->fcsubsp) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFC_Cntl(%u) %s result:dcagth  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubsp.word, 
            (kulong)(*ffcCtrl)->fcsubsp))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubdr.word != (*ffcCtrl)->fcsubdr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFC_Cntl(%u) %s result:dcagth  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubdr.word, 
            (kulong)(*ffcCtrl)->fcsubdr))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubst.word != (*ffcCtrl)->fcsubst) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFC_Cntl(%u) %s result:dcagth  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffc.fcsubst.word, 
            (kulong)(*ffcCtrl)->fcsubst))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFC_Cntl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_4_print_6(Impro24Print *self, E_IM_PRO_UNIT_NUM unitNo)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Start(%u) result:hrbtrg 0x%08lx(%u)\n", 
            unitNo, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbtrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbtrg.bit.hrbtrg));
}

void im_pro_2_4_print_7(Impro24Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Stop(%u %u) result:hrbtrg  0x%08lx(%u)\n", 
            unitNo, force, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbtrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbtrg.bit.hrbtrg));
}

void im_pro_2_4_print_8(Impro24Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                        kint32 ercd, T_IM_PRO_HRB_CTRL* hrbCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbh.bit.hrbh != hrbCtrl->inPosX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbh  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbh.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbh.bit.hrbh,hrbCtrl->inPosX))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbv.bit.hrbv != hrbCtrl->inPosY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbv  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbv.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbv.bit.hrbv,hrbCtrl->inPosY))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbhw.bit.hrbhw != hrbCtrl->inWidth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbhw  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbhw.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbhw.bit.hrbhw,hrbCtrl->inWidth))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbvw.bit.hrbvw != hrbCtrl->inLines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbvw  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbvw.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbvw.bit.hrbvw,hrbCtrl->inLines))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbohw.bit.hrbohw != hrbCtrl->outWidth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbohw  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbohw.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbohw.bit.hrbohw,hrbCtrl->outWidth))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbscyc.bit.hrbscyc != hrbCtrl->cycle) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbscyc  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbscyc.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbscyc.bit.hrbscyc,hrbCtrl->cycle))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbosm.bit.hrbosm != hrbCtrl->outTiming) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbosm  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbosm.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbosm.bit.hrbosm,hrbCtrl->outTiming))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk1.bit.hrbk0_0 != hrbCtrl->coefficient[ 0][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk0_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk1.bit.hrbk0_0,hrbCtrl->coefficient[ 0][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk1.bit.hrbk0_1 != hrbCtrl->coefficient[ 0][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk0_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk1.bit.hrbk0_1,hrbCtrl->coefficient[ 0][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk2.bit.hrbk0_2 != hrbCtrl->coefficient[ 0][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk0_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk2.bit.hrbk0_2,hrbCtrl->coefficient[ 0][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk2.bit.hrbk0_3 != hrbCtrl->coefficient[ 0][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk0_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk2.bit.hrbk0_3,hrbCtrl->coefficient[ 0][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk3.bit.hrbk0_4 != hrbCtrl->coefficient[ 0][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk0_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk3.bit.hrbk0_4,hrbCtrl->coefficient[ 0][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk3.bit.hrbk1_0 != hrbCtrl->coefficient[ 1][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk1_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk3.bit.hrbk1_0,hrbCtrl->coefficient[ 1][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk4.bit.hrbk1_1 != hrbCtrl->coefficient[ 1][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk1_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk4.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk4.bit.hrbk1_1,hrbCtrl->coefficient[ 1][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk4.bit.hrbk1_2 != hrbCtrl->coefficient[ 1][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk1_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk4.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk4.bit.hrbk1_2,hrbCtrl->coefficient[ 1][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk5.bit.hrbk1_3 != hrbCtrl->coefficient[ 1][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk1_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk5.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk5.bit.hrbk1_3,hrbCtrl->coefficient[ 1][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk5.bit.hrbk1_4 != hrbCtrl->coefficient[ 1][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk1_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk5.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk5.bit.hrbk1_4,hrbCtrl->coefficient[ 1][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk6.bit.hrbk2_0 != hrbCtrl->coefficient[ 2][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk2_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk6.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk6.bit.hrbk2_0,hrbCtrl->coefficient[ 2][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk6.bit.hrbk2_1 != hrbCtrl->coefficient[ 2][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk2_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk6.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk6.bit.hrbk2_1,hrbCtrl->coefficient[ 2][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk7.bit.hrbk2_2 != hrbCtrl->coefficient[ 2][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk2_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk7.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk7.bit.hrbk2_2,hrbCtrl->coefficient[ 2][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk7.bit.hrbk2_3 != hrbCtrl->coefficient[ 2][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk2_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk7.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk7.bit.hrbk2_3,hrbCtrl->coefficient[ 2][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk8.bit.hrbk2_4 != hrbCtrl->coefficient[ 2][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk2_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk8.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk8.bit.hrbk2_4,hrbCtrl->coefficient[ 2][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk8.bit.hrbk3_0 != hrbCtrl->coefficient[ 3][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk3_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk8.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk8.bit.hrbk3_0,hrbCtrl->coefficient[ 3][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk9.bit.hrbk3_1 != hrbCtrl->coefficient[ 3][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk3_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk9.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk9.bit.hrbk3_1,hrbCtrl->coefficient[ 3][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk9.bit.hrbk3_2 != hrbCtrl->coefficient[ 3][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk3_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk9.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk9.bit.hrbk3_2,hrbCtrl->coefficient[ 3][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk10.bit.hrbk3_3 != hrbCtrl->coefficient[ 3][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk3_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk10.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk10.bit.hrbk3_3,hrbCtrl->coefficient[ 3][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk10.bit.hrbk3_4 != hrbCtrl->coefficient[ 3][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk3_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk10.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk10.bit.hrbk3_4,hrbCtrl->coefficient[ 3][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk11.bit.hrbk4_0 != hrbCtrl->coefficient[ 4][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk4_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk11.bit.hrbk4_0,hrbCtrl->coefficient[ 4][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk11.bit.hrbk4_1 != hrbCtrl->coefficient[ 4][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk4_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk11.bit.hrbk4_1,hrbCtrl->coefficient[ 4][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk12.bit.hrbk4_2 != hrbCtrl->coefficient[ 4][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk4_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk12.bit.hrbk4_2,hrbCtrl->coefficient[ 4][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk12.bit.hrbk4_3 != hrbCtrl->coefficient[ 4][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk4_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk12.bit.hrbk4_3,hrbCtrl->coefficient[ 4][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk13.bit.hrbk4_4 != hrbCtrl->coefficient[ 4][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk4_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk13.bit.hrbk4_4,hrbCtrl->coefficient[ 4][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk13.bit.hrbk5_0 != hrbCtrl->coefficient[ 5][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk5_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk13.bit.hrbk5_0,hrbCtrl->coefficient[ 5][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk14.bit.hrbk5_1 != hrbCtrl->coefficient[ 5][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk5_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk14.bit.hrbk5_1,hrbCtrl->coefficient[ 5][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk14.bit.hrbk5_2 != hrbCtrl->coefficient[ 5][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk5_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk14.bit.hrbk5_2,hrbCtrl->coefficient[ 5][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk15.bit.hrbk5_3 != hrbCtrl->coefficient[ 5][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk5_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk15.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk15.bit.hrbk5_3,hrbCtrl->coefficient[ 5][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk15.bit.hrbk5_4 != hrbCtrl->coefficient[ 5][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk5_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk15.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk15.bit.hrbk5_4,hrbCtrl->coefficient[ 5][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk16.bit.hrbk6_0 != hrbCtrl->coefficient[ 6][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk6_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk16.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk16.bit.hrbk6_0,hrbCtrl->coefficient[ 6][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk16.bit.hrbk6_1 != hrbCtrl->coefficient[ 6][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk6_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk16.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk16.bit.hrbk6_1,hrbCtrl->coefficient[ 6][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk17.bit.hrbk6_2 != hrbCtrl->coefficient[ 6][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk6_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk17.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk17.bit.hrbk6_2,hrbCtrl->coefficient[ 6][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk17.bit.hrbk6_3 != hrbCtrl->coefficient[ 6][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk6_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk17.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk17.bit.hrbk6_3,hrbCtrl->coefficient[ 6][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk18.bit.hrbk6_4 != hrbCtrl->coefficient[ 6][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk6_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk18.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk18.bit.hrbk6_4,hrbCtrl->coefficient[ 6][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk18.bit.hrbk7_0 != hrbCtrl->coefficient[ 7][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk7_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk18.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk18.bit.hrbk7_0,hrbCtrl->coefficient[ 7][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk19.bit.hrbk7_1 != hrbCtrl->coefficient[ 7][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk7_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk19.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk19.bit.hrbk7_1,hrbCtrl->coefficient[ 7][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk19.bit.hrbk7_2 != hrbCtrl->coefficient[ 7][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk7_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk19.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk19.bit.hrbk7_2,hrbCtrl->coefficient[ 7][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk20.bit.hrbk7_3 != hrbCtrl->coefficient[ 7][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk7_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk20.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk20.bit.hrbk7_3,hrbCtrl->coefficient[ 7][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk20.bit.hrbk7_4 != hrbCtrl->coefficient[ 7][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk7_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk20.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk20.bit.hrbk7_4,hrbCtrl->coefficient[ 7][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk21.bit.hrbk8_0 != hrbCtrl->coefficient[ 8][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk8_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk21.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk21.bit.hrbk8_0,hrbCtrl->coefficient[ 8][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk21.bit.hrbk8_1 != hrbCtrl->coefficient[ 8][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk8_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk21.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk21.bit.hrbk8_1,hrbCtrl->coefficient[ 8][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk22.bit.hrbk8_2 != hrbCtrl->coefficient[ 8][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk8_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk22.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk22.bit.hrbk8_2,hrbCtrl->coefficient[ 8][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk22.bit.hrbk8_3 != hrbCtrl->coefficient[ 8][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk8_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk22.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk22.bit.hrbk8_3,hrbCtrl->coefficient[ 8][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk23.bit.hrbk8_4 != hrbCtrl->coefficient[ 8][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk8_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk23.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk23.bit.hrbk8_4,hrbCtrl->coefficient[ 8][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk23.bit.hrbk9_0 != hrbCtrl->coefficient[ 9][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk9_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk23.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk23.bit.hrbk9_0,hrbCtrl->coefficient[ 9][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk24.bit.hrbk9_1 != hrbCtrl->coefficient[ 9][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk9_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk24.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk24.bit.hrbk9_1,hrbCtrl->coefficient[ 9][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk24.bit.hrbk9_2 != hrbCtrl->coefficient[ 9][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk9_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk24.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk24.bit.hrbk9_2,hrbCtrl->coefficient[ 9][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk25.bit.hrbk9_3 != hrbCtrl->coefficient[ 9][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk9_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk25.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk25.bit.hrbk9_3,hrbCtrl->coefficient[ 9][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk25.bit.hrbk9_4 != hrbCtrl->coefficient[ 9][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk9_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk25.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk25.bit.hrbk9_4,hrbCtrl->coefficient[ 9][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk26.bit.hrbk10_0 != hrbCtrl->coefficient[10][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk10_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk26.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk26.bit.hrbk10_0,hrbCtrl->coefficient[10][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk26.bit.hrbk10_1 != hrbCtrl->coefficient[10][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk10_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk26.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk26.bit.hrbk10_1,hrbCtrl->coefficient[10][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk27.bit.hrbk10_2 != hrbCtrl->coefficient[10][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk10_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk27.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk27.bit.hrbk10_2,hrbCtrl->coefficient[10][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk27.bit.hrbk10_3 != hrbCtrl->coefficient[10][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk10_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk27.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk27.bit.hrbk10_3,hrbCtrl->coefficient[10][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk28.bit.hrbk10_4 != hrbCtrl->coefficient[10][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk10_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk28.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk28.bit.hrbk10_4,hrbCtrl->coefficient[10][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk28.bit.hrbk11_0 != hrbCtrl->coefficient[11][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk11_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk28.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk28.bit.hrbk11_0,hrbCtrl->coefficient[11][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk29.bit.hrbk11_1 != hrbCtrl->coefficient[11][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk11_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk29.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk29.bit.hrbk11_1,hrbCtrl->coefficient[11][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk29.bit.hrbk11_2 != hrbCtrl->coefficient[11][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk11_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk29.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk29.bit.hrbk11_2,hrbCtrl->coefficient[11][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk30.bit.hrbk11_3 != hrbCtrl->coefficient[11][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk11_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk30.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk30.bit.hrbk11_3,hrbCtrl->coefficient[11][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk30.bit.hrbk11_4 != hrbCtrl->coefficient[11][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk11_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk30.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk30.bit.hrbk11_4,hrbCtrl->coefficient[11][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk31.bit.hrbk12_0 != hrbCtrl->coefficient[12][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk12_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk31.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk31.bit.hrbk12_0,hrbCtrl->coefficient[12][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk31.bit.hrbk12_1 != hrbCtrl->coefficient[12][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk12_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk31.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk31.bit.hrbk12_1,hrbCtrl->coefficient[12][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk32.bit.hrbk12_2 != hrbCtrl->coefficient[12][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk12_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk32.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk32.bit.hrbk12_2,hrbCtrl->coefficient[12][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk32.bit.hrbk12_3 != hrbCtrl->coefficient[12][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk12_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk32.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk32.bit.hrbk12_3,hrbCtrl->coefficient[12][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk33.bit.hrbk12_4 != hrbCtrl->coefficient[12][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk12_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk33.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk33.bit.hrbk12_4,hrbCtrl->coefficient[12][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk33.bit.hrbk13_0 != hrbCtrl->coefficient[13][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk13_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk33.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk33.bit.hrbk13_0,hrbCtrl->coefficient[13][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk34.bit.hrbk13_1 != hrbCtrl->coefficient[13][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk13_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk34.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk34.bit.hrbk13_1,hrbCtrl->coefficient[13][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk34.bit.hrbk13_2 != hrbCtrl->coefficient[13][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk13_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk34.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk34.bit.hrbk13_2,hrbCtrl->coefficient[13][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk35.bit.hrbk13_3 != hrbCtrl->coefficient[13][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk13_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk35.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk35.bit.hrbk13_3,hrbCtrl->coefficient[13][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk35.bit.hrbk13_4 != hrbCtrl->coefficient[13][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk13_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk35.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk35.bit.hrbk13_4,hrbCtrl->coefficient[13][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk36.bit.hrbk14_0 != hrbCtrl->coefficient[14][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk14_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk36.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk36.bit.hrbk14_0,hrbCtrl->coefficient[14][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk36.bit.hrbk14_1 != hrbCtrl->coefficient[14][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk14_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk36.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk36.bit.hrbk14_1,hrbCtrl->coefficient[14][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk37.bit.hrbk14_2 != hrbCtrl->coefficient[14][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk14_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk37.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk37.bit.hrbk14_2,hrbCtrl->coefficient[14][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk37.bit.hrbk14_3 != hrbCtrl->coefficient[14][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk14_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk37.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk37.bit.hrbk14_3,hrbCtrl->coefficient[14][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk38.bit.hrbk14_4 != hrbCtrl->coefficient[14][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk14_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk38.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk38.bit.hrbk14_4,hrbCtrl->coefficient[14][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk38.bit.hrbk15_0 != hrbCtrl->coefficient[15][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk15_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk38.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk38.bit.hrbk15_0,hrbCtrl->coefficient[15][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk39.bit.hrbk15_1 != hrbCtrl->coefficient[15][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk15_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk39.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk39.bit.hrbk15_1,hrbCtrl->coefficient[15][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk39.bit.hrbk15_2 != hrbCtrl->coefficient[15][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk15_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk39.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk39.bit.hrbk15_2,hrbCtrl->coefficient[15][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk40.bit.hrbk15_3 != hrbCtrl->coefficient[15][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk15_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk40.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk40.bit.hrbk15_3,hrbCtrl->coefficient[15][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk40.bit.hrbk15_4 != hrbCtrl->coefficient[15][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk15_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk40.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk40.bit.hrbk15_4,hrbCtrl->coefficient[15][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk41.bit.hrbk16_0 != hrbCtrl->coefficient[16][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk16_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk41.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk41.bit.hrbk16_0,hrbCtrl->coefficient[16][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk41.bit.hrbk16_1 != hrbCtrl->coefficient[16][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk16_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk41.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk41.bit.hrbk16_1,hrbCtrl->coefficient[16][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk42.bit.hrbk16_2 != hrbCtrl->coefficient[16][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk16_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk42.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk42.bit.hrbk16_2,hrbCtrl->coefficient[16][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk42.bit.hrbk16_3 != hrbCtrl->coefficient[16][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk16_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk42.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk42.bit.hrbk16_3,hrbCtrl->coefficient[16][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk43.bit.hrbk16_4 != hrbCtrl->coefficient[16][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk16_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk43.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk43.bit.hrbk16_4,hrbCtrl->coefficient[16][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk43.bit.hrbk17_0 != hrbCtrl->coefficient[17][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk17_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk43.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk43.bit.hrbk17_0,hrbCtrl->coefficient[17][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk44.bit.hrbk17_1 != hrbCtrl->coefficient[17][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk17_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk44.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk44.bit.hrbk17_1,hrbCtrl->coefficient[17][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk44.bit.hrbk17_2 != hrbCtrl->coefficient[17][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk17_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk44.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk44.bit.hrbk17_2,hrbCtrl->coefficient[17][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk45.bit.hrbk17_3 != hrbCtrl->coefficient[17][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk17_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk45.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk45.bit.hrbk17_3,hrbCtrl->coefficient[17][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk45.bit.hrbk17_4 != hrbCtrl->coefficient[17][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk17_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk45.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk45.bit.hrbk17_4,hrbCtrl->coefficient[17][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk46.bit.hrbk18_0 != hrbCtrl->coefficient[18][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk18_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk46.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk46.bit.hrbk18_0,hrbCtrl->coefficient[18][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk46.bit.hrbk18_1 != hrbCtrl->coefficient[18][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk18_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk46.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk46.bit.hrbk18_1,hrbCtrl->coefficient[18][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk47.bit.hrbk18_2 != hrbCtrl->coefficient[18][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk18_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk47.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk47.bit.hrbk18_2,hrbCtrl->coefficient[18][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk47.bit.hrbk18_3 != hrbCtrl->coefficient[18][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk18_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk47.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk47.bit.hrbk18_3,hrbCtrl->coefficient[18][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk48.bit.hrbk18_4 != hrbCtrl->coefficient[18][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk18_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk48.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk48.bit.hrbk18_4,hrbCtrl->coefficient[18][4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk48.bit.hrbk19_0 != hrbCtrl->coefficient[19][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk19_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk48.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk48.bit.hrbk19_0,hrbCtrl->coefficient[19][0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk49.bit.hrbk19_1 != hrbCtrl->coefficient[19][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk19_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk49.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk49.bit.hrbk19_1,hrbCtrl->coefficient[19][1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk49.bit.hrbk19_2 != hrbCtrl->coefficient[19][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk19_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk49.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk49.bit.hrbk19_2,hrbCtrl->coefficient[19][2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk50.bit.hrbk19_3 != hrbCtrl->coefficient[19][3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk19_3  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk50.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk50.bit.hrbk19_3,hrbCtrl->coefficient[19][3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk50.bit.hrbk19_4 != hrbCtrl->coefficient[19][4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) %s result:hrbk19_4  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk50.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbk.hrbk50.bit.hrbk19_4,hrbCtrl->coefficient[19][4]))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Ctrl(%u) error ercd=0x%x\n", 
            unitNo, ercd));
    }
}

void im_pro_2_4_print_9(Impro24Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Set_PAEN(%u %u) result:paen  0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbpaen.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbpaen.bit.paen));
    DriverCommon_DDIM_PRINT(( "Im_PRO_HRB_Set_PAEN(%u %u) result:hrbtrg  0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbtrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.hrb.hrbtrg.bit.hrbtrg));
}
#endif

Impro24Print* impro_2_4_print_new(void)
{
	Impro24Print* self = k_object_new_with_private(IMPRO_TYPE_2_4_PRINT, sizeof(Impro24PrintPrivate));

	return self;
}

Impro24Print* impro_2_4_print_get(void)
{
	static Impro24Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_2_4_PRINT, sizeof(Impro24PrintPrivate));
	}

	return self;
}
