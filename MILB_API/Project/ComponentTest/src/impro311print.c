/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro311Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro311print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro311Print, impro_3_1_1_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_3_1_1_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro311PrintPrivate, IMPRO_TYPE_3_1_1_PRINT))


struct _Impro311PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_3_1_1_print_constructor(Impro311Print *self)
{
	Impro311PrintPrivate *priv = IMPRO_3_1_1_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_3_1_1_print_destructor(Impro311Print *self)
{
	Impro311PrintPrivate *priv = IMPRO_3_1_1_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_3_1_1_Print(Impro311Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                        T_IM_PRO_ELF_NOISE_FUNC* elfCtrl)
{
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor1.bit.anbor_0 != elfCtrl[0].offset[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbor_0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor1.bit.anbor_0 ,elfCtrl[0].offset[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor1.bit.anbor_1 != elfCtrl[0].offset[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbor_1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor1.bit.anbor_1 ,elfCtrl[0].offset[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor2.bit.anbor_2 != elfCtrl[0].offset[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbor_2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor2.bit.anbor_2 ,elfCtrl[0].offset[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor2.bit.anbor_3 != elfCtrl[0].offset[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbor_3 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor2.bit.anbor_3 ,elfCtrl[0].offset[3]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog1.bit.anbog_0 != elfCtrl[1].offset[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbog_0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog1.bit.anbog_0 ,elfCtrl[1].offset[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog1.bit.anbog_1 != elfCtrl[1].offset[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbog_1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog1.bit.anbog_1 ,elfCtrl[1].offset[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog2.bit.anbog_2 != elfCtrl[1].offset[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbog_2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog2.bit.anbog_2 ,elfCtrl[1].offset[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog2.bit.anbog_3 != elfCtrl[1].offset[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbog_3 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog2.bit.anbog_3 ,elfCtrl[1].offset[3]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob1.bit.anbob_0 != elfCtrl[2].offset[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbob_0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob1.bit.anbob_0 ,elfCtrl[2].offset[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob1.bit.anbob_1 != elfCtrl[2].offset[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbob_1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob1.bit.anbob_1 ,elfCtrl[2].offset[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob2.bit.anbob_2 != elfCtrl[2].offset[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbob_2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob2.bit.anbob_2 ,elfCtrl[2].offset[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob2.bit.anbob_3 != elfCtrl[2].offset[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbob_3 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob2.bit.anbob_3 ,elfCtrl[2].offset[3]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr1.bit.anbkr_0 != elfCtrl[0].gain[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkr_0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr1.bit.anbkr_0 ,elfCtrl[0].gain[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr1.bit.anbkr_1 != elfCtrl[0].gain[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkr_1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr1.bit.anbkr_1 ,elfCtrl[0].gain[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr2.bit.anbkr_2 != elfCtrl[0].gain[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkr_2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr2.bit.anbkr_2 ,elfCtrl[0].gain[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr2.bit.anbkr_3 != elfCtrl[0].gain[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkr_3 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr2.bit.anbkr_3 ,elfCtrl[0].gain[3]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg1.bit.anbkg_0 != elfCtrl[1].gain[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkg_0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg1.bit.anbkg_0 ,elfCtrl[1].gain[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg1.bit.anbkg_1 != elfCtrl[1].gain[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkg_1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg1.bit.anbkg_1 ,elfCtrl[1].gain[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg2.bit.anbkg_2 != elfCtrl[1].gain[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkg_2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg2.bit.anbkg_2 ,elfCtrl[1].gain[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg2.bit.anbkg_3 != elfCtrl[1].gain[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkg_3 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg2.bit.anbkg_3 ,elfCtrl[1].gain[3]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb1.bit.anbkb_0 != elfCtrl[2].gain[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkb_0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb1.bit.anbkb_0 ,elfCtrl[2].gain[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb1.bit.anbkb_1 != elfCtrl[2].gain[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkb_1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb1.bit.anbkb_1 ,elfCtrl[2].gain[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb2.bit.anbkb_2 != elfCtrl[2].gain[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkb_2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb2.bit.anbkb_2 ,elfCtrl[2].gain[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb2.bit.anbkb_3 != elfCtrl[2].gain[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbkb_3 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb2.bit.anbkb_3 ,elfCtrl[2].gain[3]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr1.bit.anbdr_0 != elfCtrl[0].boundary[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdr_0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr1.bit.anbdr_0 ,elfCtrl[0].boundary[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr1.bit.anbdr_1 != elfCtrl[0].boundary[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdr_1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr1.bit.anbdr_1 ,elfCtrl[0].boundary[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr2.bit.anbdr_2 != elfCtrl[0].boundary[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdr_2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr2.bit.anbdr_2 ,elfCtrl[0].boundary[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr2.bit.anbdr_3 != elfCtrl[0].boundary[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdr_3 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr2.bit.anbdr_3 ,elfCtrl[0].boundary[3]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg1.bit.anbdg_0 != elfCtrl[1].boundary[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdg_0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg1.bit.anbdg_0 ,elfCtrl[1].boundary[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg1.bit.anbdg_1 != elfCtrl[1].boundary[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdg_1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg1.bit.anbdg_1 ,elfCtrl[1].boundary[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg2.bit.anbdg_2 != elfCtrl[1].boundary[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdg_2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg2.bit.anbdg_2 ,elfCtrl[1].boundary[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg2.bit.anbdg_3 != elfCtrl[1].boundary[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdg_3 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg2.bit.anbdg_3 ,elfCtrl[1].boundary[3]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb1.bit.anbdb_0 != elfCtrl[2].boundary[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdb_0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb1.bit.anbdb_0 ,elfCtrl[2].boundary[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb1.bit.anbdb_1 != elfCtrl[2].boundary[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdb_1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb1.bit.anbdb_1 ,elfCtrl[2].boundary[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb2.bit.anbdb_2 != elfCtrl[2].boundary[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdb_2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb2.bit.anbdb_2 ,elfCtrl[2].boundary[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb2.bit.anbdb_3 != elfCtrl[2].boundary[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Noisefunc(%u) %s result:anbdb_3 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb2.bit.anbdb_3 ,elfCtrl[2].boundary[3]));
        }
}
#endif

Impro311Print* impro_3_1_1_print_new(void)
{
	Impro311Print* self = k_object_new_with_private(IMPRO_TYPE_3_1_1_PRINT, sizeof(Impro311PrintPrivate));

	return self;
}

Impro311Print* impro_3_1_1_print_get(void)
{
	static Impro311Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_3_1_1_PRINT, sizeof(Impro311PrintPrivate));
	}

	return self;
}
