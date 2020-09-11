/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro31Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro31print.h"
#include "impro311print.h"
#include "impro314print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro31Print, impro_3_1_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_3_1_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro31PrintPrivate, IMPRO_TYPE_3_1_PRINT))


struct _Impro31PrintPrivate
{


};


static void impro_3_1_print_constructor(Impro31Print *self)
{
	Impro31PrintPrivate *priv = IMPRO_3_1_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_3_1_print_destructor(Impro31Print *self)
{
	Impro31PrintPrivate *priv = IMPRO_3_1_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_3_1_print_0(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_ELF_AREA* elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgws.bit.elfghw != elfCtrl->gWidth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Area(%u) %s result:elfghw 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgws.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgws.bit.elfghw,elfCtrl->gWidth));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgws.bit.elfgvw != elfCtrl->gLines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Area(%u) %s result:elfgvw 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgws.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgws.bit.elfgvw,elfCtrl->gLines));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgwp.bit.elfgh != elfCtrl->gPosX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Area(%u) %s result:elfgh 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgwp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgwp.bit.elfgh ,elfCtrl->gPosX));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgwp.bit.elfgv != elfCtrl->gPosY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Area(%u) %s result:elfgv 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgwp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfgwp.bit.elfgv ,elfCtrl->gPosY));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfws.bit.elfhw != elfCtrl->width) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Area(%u) %s result:elfhw 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfws.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfws.bit.elfhw,elfCtrl->width));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfws.bit.elfvw != elfCtrl->lines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Area(%u) %s result:elfvw 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfws.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfws.bit.elfvw,elfCtrl->lines));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfwp.bit.elfh != elfCtrl->posX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Area(%u) %s result:elfh 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfwp.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfwp.bit.elfh ,elfCtrl->posX));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfwp.bit.elfv != elfCtrl->posY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Area(%u) %s result:elfv 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfwp.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfwp.bit.elfv ,elfCtrl->posY));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Area(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_1_print_1(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                        T_IM_PRO_ELF_NOISE_FUNC* elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
       im_pro_3_1_1_Print(impro_3_1_1_print_get(),string,unitNo,ercd,elfCtrl);
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_LGT_EDG_Filter(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_1_print_3(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_ELF_L_E_FUNC* elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth1.bit.efl1th != elfCtrl->eThreshold1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_E_L_Filter(%u) %s result:efl1th 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth1.bit.efl1th,elfCtrl->eThreshold1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth1.bit.efl2th != elfCtrl->eThreshold2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_E_L_Filter(%u) %s result:efl2th 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth1.bit.efl2th,elfCtrl->eThreshold2));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth2.bit.efl3th != elfCtrl->eThreshold3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_E_L_Filter(%u) %s result:efl3th 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth2.bit.efl3th,elfCtrl->eThreshold3));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth2.bit.efl4th != elfCtrl->eThreshold4) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_E_L_Filter(%u) %s result:efl4th 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth2.bit.efl4th,elfCtrl->eThreshold4));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lfth.bit.lfth != elfCtrl->lThreshold) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_E_L_Filter(%u) %s result:lfth 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lfth.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lfth.bit.lfth,elfCtrl->lThreshold));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcome.bit.elcome1 != elfCtrl->lContour1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_E_L_Filter(%u) %s result:elcome1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcome.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcome.bit.elcome1 ,elfCtrl->lContour1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcome.bit.elcome2 != elfCtrl->lContour2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_E_L_Filter(%u) %s result:elcome2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcome.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcome.bit.elcome2 ,elfCtrl->lContour2));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcomen.bit.elcome1n != elfCtrl->lCintensity1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_E_L_Filter(%u) %s result:elcome1n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcomen.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcomen.bit.elcome1n ,elfCtrl->lCintensity1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcomen.bit.elcome2n != elfCtrl->lCintensity2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_E_L_Filter(%u) %s result:elcome2n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcomen.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcomen.bit.elcome2n ,elfCtrl->lCintensity2));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_E_L_Filter(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_1_print_4(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                        T_IM_PRO_ELF_f9_SAMPLING* elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
       im_pro_3_1_4_Print(impro_3_1_4_print_get(),string, unitNo, ercd, elfCtrl);
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_1s5_Sampling(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_1_print_6(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
kint32 ercd, T_IM_PRO_ELF_5s9_SAMPLING* elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e1.bit.a5s9e1 != elfCtrl->s5s9Threshold[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9e1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e1.bit.a5s9e1,elfCtrl->s5s9Threshold[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e1.bit.a5s9e2 != elfCtrl->s5s9Threshold[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9e2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e1.bit.a5s9e2,elfCtrl->s5s9Threshold[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e2.bit.a5s9e3 != elfCtrl->s5s9Threshold[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9e3 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e2.bit.a5s9e3,elfCtrl->s5s9Threshold[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l11.bit.a5s9l1e1n != elfCtrl->s5s9NrL1E13[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l1e1n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l11.bit.a5s9l1e1n ,elfCtrl->s5s9NrL1E13[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l11.bit.a5s9l1e2n != elfCtrl->s5s9NrL1E13[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l1e2n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l11.bit.a5s9l1e2n ,elfCtrl->s5s9NrL1E13[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l12.bit.a5s9l1e3n != elfCtrl->s5s9NrL1E13[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l1e3n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l12.bit.a5s9l1e3n ,elfCtrl->s5s9NrL1E13[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l21.bit.a5s9l2e1n != elfCtrl->s5s9NrL2E13[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l2e1n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l21.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l21.bit.a5s9l2e1n ,elfCtrl->s5s9NrL2E13[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l21.bit.a5s9l2e2n != elfCtrl->s5s9NrL2E13[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l2e2n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l21.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l21.bit.a5s9l2e2n ,elfCtrl->s5s9NrL2E13[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l22.bit.a5s9l2e3n != elfCtrl->s5s9NrL2E13[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l2e3n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l22.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l22.bit.a5s9l2e3n ,elfCtrl->s5s9NrL2E13[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l31.bit.a5s9l3e1n != elfCtrl->s5s9NrL3E13[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l3e1n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l31.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l31.bit.a5s9l3e1n ,elfCtrl->s5s9NrL3E13[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l31.bit.a5s9l3e2n != elfCtrl->s5s9NrL3E13[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l3e2n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l31.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l31.bit.a5s9l3e2n ,elfCtrl->s5s9NrL3E13[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l32.bit.a5s9l3e3n != elfCtrl->s5s9NrL3E13[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l3e3n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l32.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l32.bit.a5s9l3e3n ,elfCtrl->s5s9NrL3E13[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l41.bit.a5s9l4e1n != elfCtrl->s5s9NrL4E13[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l4e1n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l41.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l41.bit.a5s9l4e1n ,elfCtrl->s5s9NrL4E13[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l41.bit.a5s9l4e2n != elfCtrl->s5s9NrL4E13[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l4e2n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l41.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l41.bit.a5s9l4e2n ,elfCtrl->s5s9NrL4E13[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l42.bit.a5s9l4e3n != elfCtrl->s5s9NrL4E13[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:a5s9l4e3n 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l42.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l42.bit.a5s9l4e3n ,elfCtrl->s5s9NrL4E13[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb1.bit.nr5s9r != elfCtrl->s5s9NrAdjustment[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:nr5s9r 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb1.bit.nr5s9r,elfCtrl->s5s9NrAdjustment[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb1.bit.nr5s9g != elfCtrl->s5s9NrAdjustment[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:nr5s9g 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb1.bit.nr5s9g,elfCtrl->s5s9NrAdjustment[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb2.bit.nr5s9b != elfCtrl->s5s9NrAdjustment[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:nr5s9b 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb2.bit.nr5s9b,elfCtrl->s5s9NrAdjustment[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.ns5s9lm.bit.ns5s9lmp != elfCtrl->s5s9NoiseLimitPlus) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:ns5s9lmp 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.ns5s9lm.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.ns5s9lm.bit.ns5s9lmp ,elfCtrl->s5s9NoiseLimitPlus));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.ns5s9lm.bit.ns5s9lmm != elfCtrl->s5s9NoiseLimitMinus) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) %s result:ns5s9lmm 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.ns5s9lm.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.ns5s9lm.bit.ns5s9lmm ,elfCtrl->s5s9NoiseLimitMinus));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_5s9_Sampling(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_1_print_7(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                            T_IM_PRO_ELF_Noise_Adj* elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.bit.elfmnnrrl1 != elfCtrl->nrStrengthL1[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrrl1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.bit.elfmnnrrl1 ,elfCtrl->nrStrengthL1[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.bit.elfmnnrgl1 != elfCtrl->nrStrengthL1[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrgl1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.bit.elfmnnrgl1 ,elfCtrl->nrStrengthL1[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.bit.elfmnnrbl1 != elfCtrl->nrStrengthL1[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrbl1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.bit.elfmnnrbl1 ,elfCtrl->nrStrengthL1[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.bit.elfmnnrrl2 != elfCtrl->nrStrengthL2[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrrl2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.bit.elfmnnrrl2 ,elfCtrl->nrStrengthL2[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.bit.elfmnnrgl2 != elfCtrl->nrStrengthL2[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrgl2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.bit.elfmnnrgl2 ,elfCtrl->nrStrengthL2[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.bit.elfmnnrbl2 != elfCtrl->nrStrengthL2[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrbl2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.bit.elfmnnrbl2 ,elfCtrl->nrStrengthL2[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.bit.elfmnnrrl3 != elfCtrl->nrStrengthL3[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrrl3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.bit.elfmnnrrl3 ,elfCtrl->nrStrengthL3[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.bit.elfmnnrgl3 != elfCtrl->nrStrengthL3[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrgl3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.bit.elfmnnrgl3 ,elfCtrl->nrStrengthL3[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.bit.elfmnnrbl3 != elfCtrl->nrStrengthL3[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrbl3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.bit.elfmnnrbl3 ,elfCtrl->nrStrengthL3[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.bit.elfmnnrrl4 != elfCtrl->nrStrengthL4[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrrl4 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.bit.elfmnnrrl4 ,elfCtrl->nrStrengthL4[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.bit.elfmnnrgl4 != elfCtrl->nrStrengthL4[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrgl4 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.bit.elfmnnrgl4 ,elfCtrl->nrStrengthL4[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.bit.elfmnnrbl4 != elfCtrl->nrStrengthL4[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfmnnrbl4 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.bit.elfmnnrbl4 ,elfCtrl->nrStrengthL4[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfafnr.bit.elfafnr != elfCtrl->afPathNrStrength) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) %s result:elfafnr 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfafnr.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfafnr.bit.elfafnr,elfCtrl->afPathNrStrength));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noise_Adj(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_1_print_8(Impro31Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_ELF_a0_FILTER* elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zeladcmd.bit.zeladcmd != elfCtrl->dpcMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zeladcmd 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zeladcmd.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zeladcmd.bit.zeladcmd,elfCtrl->dpcMode));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor1.bit.zanbor_0 != elfCtrl->nce[0].offset[ 0 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbor_0 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor1.bit.zanbor_0,elfCtrl->nce[0].offset[ 0 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor1.bit.zanbor_1 != elfCtrl->nce[0].offset[ 1 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbor_1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor1.bit.zanbor_1,elfCtrl->nce[0].offset[ 1 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor2.bit.zanbor_2 != elfCtrl->nce[0].offset[ 2 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbor_2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor2.bit.zanbor_2,elfCtrl->nce[0].offset[ 2 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor2.bit.zanbor_3 != elfCtrl->nce[0].offset[ 3 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbor_3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor2.bit.zanbor_3,elfCtrl->nce[0].offset[ 3 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog1.bit.zanbog_0 != elfCtrl->nce[1].offset[ 0 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbog_0 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog1.bit.zanbog_0,elfCtrl->nce[1].offset[ 0 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog1.bit.zanbog_1 != elfCtrl->nce[1].offset[ 1 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbog_1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog1.bit.zanbog_1,elfCtrl->nce[1].offset[ 1 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog2.bit.zanbog_2 != elfCtrl->nce[1].offset[ 2 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbog_2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog2.bit.zanbog_2,elfCtrl->nce[1].offset[ 2 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog2.bit.zanbog_3 != elfCtrl->nce[1].offset[ 3 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbog_3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog2.bit.zanbog_3,elfCtrl->nce[1].offset[ 3 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob1.bit.zanbob_0 != elfCtrl->nce[2].offset[ 0 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbob_0 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob1.bit.zanbob_0,elfCtrl->nce[2].offset[ 0 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob1.bit.zanbob_1 != elfCtrl->nce[2].offset[ 1 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbob_1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob1.bit.zanbob_1,elfCtrl->nce[2].offset[ 1 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob2.bit.zanbob_2 != elfCtrl->nce[2].offset[ 2 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbob_2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob2.bit.zanbob_2,elfCtrl->nce[2].offset[ 2 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob2.bit.zanbob_3 != elfCtrl->nce[2].offset[ 3 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbob_3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob2.bit.zanbob_3,elfCtrl->nce[2].offset[ 3 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr1.bit.zanbkr_0 != elfCtrl->nce[0].gain[ 0 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkr_0 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr1.bit.zanbkr_0,elfCtrl->nce[0].gain[ 0 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr1.bit.zanbkr_1 != elfCtrl->nce[0].gain[ 1 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkr_1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr1.bit.zanbkr_1,elfCtrl->nce[0].gain[ 1 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr2.bit.zanbkr_2 != elfCtrl->nce[0].gain[ 2 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkr_2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr2.bit.zanbkr_2,elfCtrl->nce[0].gain[ 2 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr2.bit.zanbkr_3 != elfCtrl->nce[0].gain[ 3 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkr_3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr2.bit.zanbkr_3,elfCtrl->nce[0].gain[ 3 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg1.bit.zanbkg_0 != elfCtrl->nce[1].gain[ 0 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkg_0 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg1.bit.zanbkg_0,elfCtrl->nce[1].gain[ 0 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg1.bit.zanbkg_1 != elfCtrl->nce[1].gain[ 1 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkg_1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg1.bit.zanbkg_1,elfCtrl->nce[1].gain[ 1 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg2.bit.zanbkg_2 != elfCtrl->nce[1].gain[ 2 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkg_2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg2.bit.zanbkg_2,elfCtrl->nce[1].gain[ 2 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg2.bit.zanbkg_3 != elfCtrl->nce[1].gain[ 3 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkg_3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg2.bit.zanbkg_3,elfCtrl->nce[1].gain[ 3 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb1.bit.zanbkb_0 != elfCtrl->nce[2].gain[ 0 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkb_0 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb1.bit.zanbkb_0,elfCtrl->nce[2].gain[ 0 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb1.bit.zanbkb_1 != elfCtrl->nce[2].gain[ 1 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkb_1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb1.bit.zanbkb_1,elfCtrl->nce[2].gain[ 1 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb2.bit.zanbkb_2 != elfCtrl->nce[2].gain[ 2 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkb_2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb2.bit.zanbkb_2,elfCtrl->nce[2].gain[ 2 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb2.bit.zanbkb_3 != elfCtrl->nce[2].gain[ 3 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbkb_3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb2.bit.zanbkb_3,elfCtrl->nce[2].gain[ 3 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr1.bit.zanbdr_0 != elfCtrl->nce[0].areaBoundary[ 0 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdr_0 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr1.bit.zanbdr_0,elfCtrl->nce[0].areaBoundary[ 0 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr1.bit.zanbdr_1 != elfCtrl->nce[0].areaBoundary[ 1 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdr_1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr1.bit.zanbdr_1,elfCtrl->nce[0].areaBoundary[ 1 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr2.bit.zanbdr_2 != elfCtrl->nce[0].areaBoundary[ 2 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdr_2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr2.bit.zanbdr_2,elfCtrl->nce[0].areaBoundary[ 2 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr2.bit.zanbdr_3 != elfCtrl->nce[0].areaBoundary[ 3 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdr_3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr2.bit.zanbdr_3,elfCtrl->nce[0].areaBoundary[ 3 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg1.bit.zanbdg_0 != elfCtrl->nce[1].areaBoundary[ 0 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdg_0 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg1.bit.zanbdg_0,elfCtrl->nce[1].areaBoundary[ 0 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg1.bit.zanbdg_1 != elfCtrl->nce[1].areaBoundary[ 1 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdg_1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg1.bit.zanbdg_1,elfCtrl->nce[1].areaBoundary[ 1 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg2.bit.zanbdg_2 != elfCtrl->nce[1].areaBoundary[ 2 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdg_2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg2.bit.zanbdg_2,elfCtrl->nce[1].areaBoundary[ 2 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg2.bit.zanbdg_3 != elfCtrl->nce[1].areaBoundary[ 3 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdg_3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg2.bit.zanbdg_3,elfCtrl->nce[1].areaBoundary[ 3 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb1.bit.zanbdb_0 != elfCtrl->nce[2].areaBoundary[ 0 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdb_0 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb1.bit.zanbdb_0,elfCtrl->nce[2].areaBoundary[ 0 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb1.bit.zanbdb_1 != elfCtrl->nce[2].areaBoundary[ 1 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdb_1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb1.bit.zanbdb_1,elfCtrl->nce[2].areaBoundary[ 1 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb2.bit.zanbdb_2 != elfCtrl->nce[2].areaBoundary[ 2 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdb_2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb2.bit.zanbdb_2,elfCtrl->nce[2].areaBoundary[ 2 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb2.bit.zanbdb_3 != elfCtrl->nce[2].areaBoundary[ 3 ]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zanbdb_3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb2.bit.zanbdb_3,elfCtrl->nce[2].areaBoundary[ 3 ]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw1.bit.zlgtwr != elfCtrl->lumiRgbGain[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlgtwr 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw1.bit.zlgtwr,elfCtrl->lumiRgbGain[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw1.bit.zlgtwg != elfCtrl->lumiRgbGain[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlgtwg 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw1.bit.zlgtwg,elfCtrl->lumiRgbGain[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw2.bit.zlgtwb != elfCtrl->lumiRgbGain[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlgtwb 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw2.bit.zlgtwb,elfCtrl->lumiRgbGain[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.bit.zlgtr      != elfCtrl->lumiRgbCoeff[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlgtr 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.bit.zlgtr ,elfCtrl->lumiRgbCoeff[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.bit.zlgtg      != elfCtrl->lumiRgbCoeff[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlgtg 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.bit.zlgtg ,elfCtrl->lumiRgbCoeff[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.bit.zlgtb      != elfCtrl->lumiRgbCoeff[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlgtb 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.bit.zlgtb ,elfCtrl->lumiRgbCoeff[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.bit.zlgtc      != elfCtrl->lumiCCoeff) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlgtc 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.bit.zlgtc ,elfCtrl->lumiCCoeff));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgte.bit.zlgter    != elfCtrl->tWeight[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlgter 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgte.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgte.bit.zlgter ,elfCtrl->tWeight[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgte.bit.zlgteg    != elfCtrl->tWeight[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlgteg 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgte.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgte.bit.zlgteg ,elfCtrl->tWeight[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgte.bit.zlgteb    != elfCtrl->tWeight[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlgteb 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgte.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgte.bit.zlgteb ,elfCtrl->tWeight[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedg2anba.bit.zedg2anba != elfCtrl->tAdjA.coeff1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zedg2anba 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedg2anba.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedg2anba.bit.zedg2anba,elfCtrl->tAdjA.coeff1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedgscla.bit.zedgscla != elfCtrl->tAdjA.coeff2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zedgscla 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedgscla.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedgscla.bit.zedgscla,elfCtrl->tAdjA.coeff2));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedg2anbb.bit.zedg2anbb != elfCtrl->tAdjB.coeff1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zedg2anbb 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedg2anbb.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedg2anbb.bit.zedg2anbb,elfCtrl->tAdjB.coeff1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedgsclb.bit.zedgsclb != elfCtrl->tAdjB.coeff2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zedgsclb 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedgsclb.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedgsclb.bit.zedgsclb,elfCtrl->tAdjB.coeff2));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge1.bit.zalnge1 != elfCtrl->tLongWavelengthThreshold[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalnge1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge1.bit.zalnge1 ,elfCtrl->tLongWavelengthThreshold[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge1.bit.zalnge2 != elfCtrl->tLongWavelengthThreshold[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalnge2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge1.bit.zalnge2 ,elfCtrl->tLongWavelengthThreshold[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge2.bit.zalnge3 != elfCtrl->tLongWavelengthThreshold[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalnge3 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge2.bit.zalnge3 ,elfCtrl->tLongWavelengthThreshold[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng1.bit.zalngl1e1n != 
        elfCtrl->tLongWavelengthNrStrength[0][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl1e1n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng1.bit.zalngl1e1n,elfCtrl->tLongWavelengthNrStrength[0][0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng1.bit.zalngl1e2n != 
        elfCtrl->tLongWavelengthNrStrength[0][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl1e2n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng1.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng1.bit.zalngl1e2n,elfCtrl->tLongWavelengthNrStrength[0][1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng2.bit.zalngl1e3n != 
        elfCtrl->tLongWavelengthNrStrength[0][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl1e3n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng2.bit.zalngl1e3n,elfCtrl->tLongWavelengthNrStrength[0][2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng2.bit.zalngl2e1n != 
        elfCtrl->tLongWavelengthNrStrength[1][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl2e1n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng2.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng2.bit.zalngl2e1n,elfCtrl->tLongWavelengthNrStrength[1][0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng3.bit.zalngl2e2n != 
        elfCtrl->tLongWavelengthNrStrength[1][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl2e2n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng3.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng3.bit.zalngl2e2n,elfCtrl->tLongWavelengthNrStrength[1][1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng3.bit.zalngl2e3n != 
        elfCtrl->tLongWavelengthNrStrength[1][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl2e3n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng3.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng3.bit.zalngl2e3n,elfCtrl->tLongWavelengthNrStrength[1][2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng4.bit.zalngl3e1n != 
        elfCtrl->tLongWavelengthNrStrength[2][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl3e1n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng4.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng4.bit.zalngl3e1n,elfCtrl->tLongWavelengthNrStrength[2][0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng4.bit.zalngl3e2n != 
        elfCtrl->tLongWavelengthNrStrength[2][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl3e2n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng4.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng4.bit.zalngl3e2n,elfCtrl->tLongWavelengthNrStrength[2][1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng5.bit.zalngl3e3n != 
        elfCtrl->tLongWavelengthNrStrength[2][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl3e3n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng5.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng5.bit.zalngl3e3n,elfCtrl->tLongWavelengthNrStrength[2][2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng5.bit.zalngl4e1n != 
        elfCtrl->tLongWavelengthNrStrength[3][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl4e1n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng5.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng5.bit.zalngl4e1n,elfCtrl->tLongWavelengthNrStrength[3][0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng6.bit.zalngl4e2n != 
        elfCtrl->tLongWavelengthNrStrength[3][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl4e2n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng6.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng6.bit.zalngl4e2n,elfCtrl->tLongWavelengthNrStrength[3][1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng6.bit.zalngl4e3n != 
        elfCtrl->tLongWavelengthNrStrength[3][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zalngl4e3n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng6.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng6.bit.zalngl4e3n,elfCtrl->tLongWavelengthNrStrength[3][2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlfth.bit.zlfth     != elfCtrl->lFilterExtractionThreshold) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlfth 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlfth.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlfth.bit.zlfth,elfCtrl->lFilterExtractionThreshold));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcome.bit.zlcome1  != elfCtrl->lAppToleranceThreshold[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlcome1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcome.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcome.bit.zlcome1 ,elfCtrl->lAppToleranceThreshold[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcome.bit.zlcome2  != elfCtrl->lAppToleranceThreshold[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlcome2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcome.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcome.bit.zlcome2 ,elfCtrl->lAppToleranceThreshold[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcomen.bit.zlcome1n != elfCtrl->lAppStrength[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlcome1n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcomen.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcomen.bit.zlcome1n ,elfCtrl->lAppStrength[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcomen.bit.zlcome2n != elfCtrl->lAppStrength[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:zlcome2n 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcomen.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcomen.bit.zlcome2n ,elfCtrl->lAppStrength[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.znslnglm.bit.znslnglmp != elfCtrl->longWavelengthNoisePLimiter) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:znslnglmp 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.znslnglm.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.znslnglm.bit.znslnglmp ,elfCtrl->longWavelengthNoisePLimiter));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.znslnglm.bit.znslnglmm != elfCtrl->longWavelengthNoiseMLimiter) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) %s result:znslnglmm 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.znslnglm.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.znslnglm.bit.znslnglmm ,elfCtrl->longWavelengthNoiseMLimiter));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_Sampling(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_1_print_9(Impro31Print *self, E_IM_PRO_UNIT_NUM unitNo)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Start_NSL(%u) result:nsltrg 0x%08lx(%u)\n", 
            unitNo, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nsltrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nsltrg.bit.nsltrg));
}
#endif

Impro31Print* impro_3_1_print_new(void)
{
	Impro31Print* self = k_object_new_with_private(IMPRO_TYPE_3_1_PRINT, sizeof(Impro31PrintPrivate));

	return self;
}

Impro31Print* impro_3_1_print_get(void)
{
	static Impro31Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_3_1_PRINT, sizeof(Impro31PrintPrivate));
	}

	return self;
}
