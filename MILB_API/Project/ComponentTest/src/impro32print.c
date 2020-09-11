/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro32Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro32print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro32Print, impro_3_2_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_3_2_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro32PrintPrivate, IMPRO_TYPE_3_2_PRINT))


struct _Impro32PrintPrivate
{


};


static void impro_3_2_print_constructor(Impro32Print *self)
{
	Impro32PrintPrivate *priv = IMPRO_3_2_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_3_2_print_destructor(Impro32Print *self)
{
	Impro32PrintPrivate *priv = IMPRO_3_2_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}

void im_pro_3_2_print_0(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Stop_NSL(%u %u) result:nsltrg 0x%08lx(%u)\n", 
            unitNo, force, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nsltrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nsltrg.bit.nsltrg));
}

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_3_2_print_1(Impro32Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_NSL_CTRL* elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfctl.bit.nslmd != elfCtrl->lNoiseMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl_NSL(%u) %s result:nslmd 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfctl.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfctl.bit.nslmd ,elfCtrl->lNoiseMode));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfctl.bit.nslres != elfCtrl->lNoisePrecision) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl_NSL(%u) %s result:nslres 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfctl.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfctl.bit.nslres,elfCtrl->lNoisePrecision));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfctl.bit.nslkne != elfCtrl->longNoiseComp) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl_NSL(%u) %s result:nslkne 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfctl.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfctl.bit.nslkne,elfCtrl->longNoiseComp));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl_NSL(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_2_print_2(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_PAEN(%u %u) result:EPAENA0 0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfpaen.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfpaen.bit.EPAENA0));
    DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_A0_PAEN(%u %u) result:elftrg 0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elftrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elftrg.bit.elftrg));
}

void im_pro_3_2_print_3(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_NSL_PAEN(%u %u) result:EPAENNSL 0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfpaen.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfpaen.bit.EPAENNSL));
    DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_NSL_PAEN(%u %u) result:elftrg 0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elftrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elftrg.bit.elftrg));
}


void im_pro_3_2_print_4(Impro32Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                        kint32 ercd, const T_IM_PRO_RDMA_ELF_ADDR** elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfctl.word != (*elfCtrl)->elfctl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:elfctl 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfctl.word , (kulong)(*elfCtrl)->elfctl));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfzp.word != (*elfCtrl)->elfzp) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:elfzp 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfzp.word, (kulong)(*elfCtrl)->elfzp));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfl.elfl1.word != (*elfCtrl)->elfl1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:elfl1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfl.elfl1.word , (kulong)(*elfCtrl)->elfl1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfl.elfl2.word != (*elfCtrl)->elfl2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:elfl2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfl.elfl2.word , (kulong)(*elfCtrl)->elfl2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor1.word != (*elfCtrl)->anbor1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbor1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor1.word , (kulong)(*elfCtrl)->anbor1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor2.word != (*elfCtrl)->anbor2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbor2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbor.anbor2.word , (kulong)(*elfCtrl)->anbor2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr1.word != (*elfCtrl)->anbkr1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbkr1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr1.word , (kulong)(*elfCtrl)->anbkr1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr2.word != (*elfCtrl)->anbkr2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbkr2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkr.anbkr2.word , (kulong)(*elfCtrl)->anbkr2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr1.word != (*elfCtrl)->anbdr1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbdr1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr1.word , (kulong)(*elfCtrl)->anbdr1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr2.word != (*elfCtrl)->anbdr2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbdr2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdr.anbdr2.word , (kulong)(*elfCtrl)->anbdr2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog1.word != (*elfCtrl)->anbog1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbog1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog1.word , (kulong)(*elfCtrl)->anbog1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog2.word != (*elfCtrl)->anbog2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbog2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbog.anbog2.word , (kulong)(*elfCtrl)->anbog2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg1.word != (*elfCtrl)->anbkg1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbkg1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg1.word , (kulong)(*elfCtrl)->anbkg1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg2.word != (*elfCtrl)->anbkg2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbkg2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkg.anbkg2.word , (kulong)(*elfCtrl)->anbkg2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg1.word != (*elfCtrl)->anbdg1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbdg1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg1.word , (kulong)(*elfCtrl)->anbdg1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg2.word != (*elfCtrl)->anbdg2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbdg2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdg.anbdg2.word , (kulong)(*elfCtrl)->anbdg2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob1.word != (*elfCtrl)->anbob1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbob1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob1.word , (kulong)(*elfCtrl)->anbob1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob2.word != (*elfCtrl)->anbob2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbob2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbob.anbob2.word , (kulong)(*elfCtrl)->anbob2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb1.word != (*elfCtrl)->anbkb1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbkb1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb1.word , (kulong)(*elfCtrl)->anbkb1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb2.word != (*elfCtrl)->anbkb2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbkb2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbkb.anbkb2.word , (kulong)(*elfCtrl)->anbkb2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb1.word != (*elfCtrl)->anbdb1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbdb1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb1.word , (kulong)(*elfCtrl)->anbdb1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb2.word != (*elfCtrl)->anbdb2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:anbdb2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.anbdb.anbdb2.word , (kulong)(*elfCtrl)->anbdb2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lgtw.lgtw1.word != (*elfCtrl)->lgtw1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:lgtw1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lgtw.lgtw1.word , (kulong)(*elfCtrl)->lgtw1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lgtw.lgtw2.word != (*elfCtrl)->lgtw2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:lgtw2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lgtw.lgtw2.word , (kulong)(*elfCtrl)->lgtw2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lgt.word != (*elfCtrl)->lgt) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:lgt  0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lgt.word  , (kulong)(*elfCtrl)->lgt));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lgte.word != (*elfCtrl)->lgte) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:lgte 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lgte.word , (kulong)(*elfCtrl)->lgte));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edg2anba.word != (*elfCtrl)->edg2anba) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:edg2anba 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edg2anba.word , (kulong)(*elfCtrl)->edg2anba));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgscla.word != (*elfCtrl)->edgscla) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:edgscla 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgscla.word, (kulong)(*elfCtrl)->edgscla));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edg2anbb.word != (*elfCtrl)->edg2anbb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:edg2anbb 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edg2anbb.word , (kulong)(*elfCtrl)->edg2anbb));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgsclb.word != (*elfCtrl)->edgsclb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:edgsclb 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgsclb.word, (kulong)(*elfCtrl)->edgsclb));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edg2anbc.word != (*elfCtrl)->edg2anbc) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:edg2anbc 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edg2anbc.word , (kulong)(*elfCtrl)->edg2anbc));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgsclc.word != (*elfCtrl)->edgsclc) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:edgsclc 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgsclc.word, (kulong)(*elfCtrl)->edgsclc));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth1.word != (*elfCtrl)->efth1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:efth1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth1.word , (kulong)(*elfCtrl)->efth1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth2.word != (*elfCtrl)->efth2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:efth2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.efth.efth2.word , (kulong)(*elfCtrl)->efth2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lfth.word != (*elfCtrl)->lfth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:lfth 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.lfth.word , (kulong)(*elfCtrl)->lfth));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcome.word != (*elfCtrl)->elcome) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:elcome 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcome.word , (kulong)(*elfCtrl)->elcome));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcomen.word != (*elfCtrl)->elcomen) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:elcomen 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elcomen.word, (kulong)(*elfCtrl)->elcomen));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5e.a1s5e1.word != (*elfCtrl)->a1s5e1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a1s5e1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5e.a1s5e1.word , (kulong)(*elfCtrl)->a1s5e1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5e.a1s5e2.word != (*elfCtrl)->a1s5e2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a1s5e2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5e.a1s5e2.word , (kulong)(*elfCtrl)->a1s5e2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l1.a1s5l11.word != (*elfCtrl)->a1s5l11) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a1s5l11 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l1.a1s5l11.word , (kulong)(*elfCtrl)->a1s5l11));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l1.a1s5l12.word != (*elfCtrl)->a1s5l12) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a1s5l12 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l1.a1s5l12.word , (kulong)(*elfCtrl)->a1s5l12));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l2.a1s5l21.word != (*elfCtrl)->a1s5l21) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a1s5l21 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l2.a1s5l21.word , (kulong)(*elfCtrl)->a1s5l21));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l2.a1s5l22.word != (*elfCtrl)->a1s5l22) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a1s5l22 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l2.a1s5l22.word , (kulong)(*elfCtrl)->a1s5l22));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l3.a1s5l31.word != (*elfCtrl)->a1s5l31) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a1s5l31 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l3.a1s5l31.word , (kulong)(*elfCtrl)->a1s5l31));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l3.a1s5l32.word != (*elfCtrl)->a1s5l32) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a1s5l32 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l3.a1s5l32.word , (kulong)(*elfCtrl)->a1s5l32));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l4.a1s5l41.word != (*elfCtrl)->a1s5l41) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a1s5l41 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l4.a1s5l41.word , (kulong)(*elfCtrl)->a1s5l41));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l4.a1s5l42.word != (*elfCtrl)->a1s5l42) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a1s5l42 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a1s5l4.a1s5l42.word ,
            (kulong)(*elfCtrl)->a1s5l42));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr1s5rgb.nr1s5rgb1.word != (*elfCtrl)->nr1s5rgb1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:nr1s5rgb1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr1s5rgb.nr1s5rgb1.word ,
            (kulong)(*elfCtrl)->nr1s5rgb1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr1s5rgb.nr1s5rgb2.word != (*elfCtrl)->nr1s5rgb2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:nr1s5rgb2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr1s5rgb.nr1s5rgb2.word ,
            (kulong)(*elfCtrl)->nr1s5rgb2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.ns1s5lm.word != (*elfCtrl)->ns1s5lm) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:ns1s5lm 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.ns1s5lm.word, (kulong)(*elfCtrl)->ns1s5lm));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e1.word != (*elfCtrl)->a5s9e1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a5s9e1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e1.word , (kulong)(*elfCtrl)->a5s9e1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e2.word != (*elfCtrl)->a5s9e2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a5s9e2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9e.a5s9e2.word , (kulong)(*elfCtrl)->a5s9e2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l11.word != (*elfCtrl)->a5s9l11) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a5s9l11 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l11.word , (kulong)(*elfCtrl)->a5s9l11));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l12.word != (*elfCtrl)->a5s9l12) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a5s9l12 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l1.a5s9l12.word , (kulong)(*elfCtrl)->a5s9l12));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l21.word != (*elfCtrl)->a5s9l21) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a5s9l21 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l21.word , (kulong)(*elfCtrl)->a5s9l21));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l22.word != (*elfCtrl)->a5s9l22) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a5s9l22 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l2.a5s9l22.word , (kulong)(*elfCtrl)->a5s9l22));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l31.word != (*elfCtrl)->a5s9l31) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a5s9l31 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l31.word , (kulong)(*elfCtrl)->a5s9l31));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l32.word != (*elfCtrl)->a5s9l32) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a5s9l32 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l3.a5s9l32.word , (kulong)(*elfCtrl)->a5s9l32));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l41.word != (*elfCtrl)->a5s9l41) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a5s9l41 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l41.word , (kulong)(*elfCtrl)->a5s9l41));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l42.word != (*elfCtrl)->a5s9l42) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:a5s9l42 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.a5s9l4.a5s9l42.word , (kulong)(*elfCtrl)->a5s9l42));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb1.word != (*elfCtrl)->nr5s9rgb1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:nr5s9rgb1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb1.word , 
            (kulong)(*elfCtrl)->nr5s9rgb1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb2.word != (*elfCtrl)->nr5s9rgb2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:nr5s9rgb2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.nr5s9rgb.nr5s9rgb2.word , 
            (kulong)(*elfCtrl)->nr5s9rgb2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.ns5s9lm.word != (*elfCtrl)->ns5s9lm) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:ns5s9lm 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.ns5s9lm.word, (kulong)(*elfCtrl)->ns5s9lm));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w1.word != (*elfCtrl)->fs9w1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fs9w1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w1.word , (kulong)(*elfCtrl)->fs9w1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w2.word != (*elfCtrl)->fs9w2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fs9w2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w2.word , (kulong)(*elfCtrl)->fs9w2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc1.word != (*elfCtrl)->fs9yc1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fs9yc1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc1.word , (kulong)(*elfCtrl)->fs9yc1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc2.word != (*elfCtrl)->fs9yc2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fs9yc2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc2.word , (kulong)(*elfCtrl)->fs9yc2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc3.word != (*elfCtrl)->fs9yc3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fs9yc3 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc3.word , (kulong)(*elfCtrl)->fs9yc3));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc4.word != (*elfCtrl)->fs9yc4) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fs9yc4 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc4.word , (kulong)(*elfCtrl)->fs9yc4));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc5.word != (*elfCtrl)->fs9yc5) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fs9yc5 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc5.word , (kulong)(*elfCtrl)->fs9yc5));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fastr.word != (*elfCtrl)->fastr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fastr 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fastr.word, (kulong)(*elfCtrl)->fastr));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.word != (*elfCtrl)->crvaf) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:crvaf 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.word, (kulong)(*elfCtrl)->crvaf));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtof.word != (*elfCtrl)->fcrvabtof) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fcrvabtof 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtof.word, (kulong)(*elfCtrl)->fcrvabtof));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtga.word != (*elfCtrl)->fcrvabtga) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fcrvabtga 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtga.word, (kulong)(*elfCtrl)->fcrvabtga));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtbd.word != (*elfCtrl)->fcrvabtbd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fcrvabtbd 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtbd.word, (kulong)(*elfCtrl)->fcrvabtbd));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtcp.word != (*elfCtrl)->fcrvabtcp) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fcrvabtcp 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtcp.word, (kulong)(*elfCtrl)->fcrvabtcp));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtga.word != (*elfCtrl)->fyabtga) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fyabtga 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtga.word, (kulong)(*elfCtrl)->fyabtga));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtbd.word != (*elfCtrl)->fyabtbd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fyabtbd 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtbd.word, (kulong)(*elfCtrl)->fyabtbd));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtclp.word != (*elfCtrl)->fyabtclp) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fyabtclp 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtclp.word , (kulong)(*elfCtrl)->fyabtclp));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.faehh.word != (*elfCtrl)->faehh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:faehh 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.faehh.word, (kulong)(*elfCtrl)->faehh));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbstr.word != (*elfCtrl)->fbstr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fbstr 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbstr.word, (kulong)(*elfCtrl)->fbstr));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.word != (*elfCtrl)->crvbf) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:crvbf 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.word, (kulong)(*elfCtrl)->crvbf));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtof.word != (*elfCtrl)->fcrvbbtof) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fcrvbbtof 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtof.word, (kulong)(*elfCtrl)->fcrvbbtof));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtga.word != (*elfCtrl)->fcrvbbtga) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fcrvbbtga 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtga.word, (kulong)(*elfCtrl)->fcrvbbtga));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtbd.word != (*elfCtrl)->fcrvbbtbd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fcrvbbtbd 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtbd.word, (kulong)(*elfCtrl)->fcrvbbtbd));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtcp.word != (*elfCtrl)->fcrvbbtcp) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fcrvbbtcp 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtcp.word, (kulong)(*elfCtrl)->fcrvbbtcp));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtga.word != (*elfCtrl)->fybbtga) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fybbtga 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtga.word, (kulong)(*elfCtrl)->fybbtga));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtbd.word != (*elfCtrl)->fybbtbd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fybbtbd 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtbd.word, (kulong)(*elfCtrl)->fybbtbd));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtclp.word != (*elfCtrl)->fybbtclp) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fybbtclp 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtclp.word , (kulong)(*elfCtrl)->fybbtclp));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbehh.word != (*elfCtrl)->fbehh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:fbehh 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbehh.word, (kulong)(*elfCtrl)->fbehh));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.word != (*elfCtrl)->elfmnnrrl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:elfmnnrrl 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrrl.word, (kulong)(*elfCtrl)->elfmnnrrl));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.word != (*elfCtrl)->elfmnnrgl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:elfmnnrgl 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrgl.word, (kulong)(*elfCtrl)->elfmnnrgl));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.word != (*elfCtrl)->elfmnnrbl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:elfmnnrbl 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfmnnrbl.word, (kulong)(*elfCtrl)->elfmnnrbl));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfafnr.word != (*elfCtrl)->elfafnr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:elfafnr 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.elfafnr.word, (kulong)(*elfCtrl)->elfafnr));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zeladcmd.word != (*elfCtrl)->zeladcmd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zeladcmd 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zeladcmd.word , (kulong)(*elfCtrl)->zeladcmd));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor1.word != (*elfCtrl)->zanbor1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbor1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor1.word , (kulong)(*elfCtrl)->zanbor1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor2.word != (*elfCtrl)->zanbor2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbor2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbor.zanbor2.word , (kulong)(*elfCtrl)->zanbor2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr1.word != (*elfCtrl)->zanbkr1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbkr1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr1.word , (kulong)(*elfCtrl)->zanbkr1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr2.word != (*elfCtrl)->zanbkr2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbkr2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkr.zanbkr2.word , (kulong)(*elfCtrl)->zanbkr2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr1.word != (*elfCtrl)->zanbdr1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbdr1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr1.word , (kulong)(*elfCtrl)->zanbdr1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr2.word != (*elfCtrl)->zanbdr2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbdr2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdr.zanbdr2.word , (kulong)(*elfCtrl)->zanbdr2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog1.word != (*elfCtrl)->zanbog1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbog1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog1.word , (kulong)(*elfCtrl)->zanbog1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog2.word != (*elfCtrl)->zanbog2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbog2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbog.zanbog2.word , (kulong)(*elfCtrl)->zanbog2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg1.word != (*elfCtrl)->zanbkg1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbkg1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg1.word , (kulong)(*elfCtrl)->zanbkg1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg2.word != (*elfCtrl)->zanbkg2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbkg2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkg.zanbkg2.word , (kulong)(*elfCtrl)->zanbkg2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg1.word != (*elfCtrl)->zanbdg1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbdg1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg1.word , (kulong)(*elfCtrl)->zanbdg1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg2.word != (*elfCtrl)->zanbdg2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbdg2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdg.zanbdg2.word , (kulong)(*elfCtrl)->zanbdg2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob1.word != (*elfCtrl)->zanbob1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbob1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob1.word , (kulong)(*elfCtrl)->zanbob1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob2.word != (*elfCtrl)->zanbob2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbob2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbob.zanbob2.word , (kulong)(*elfCtrl)->zanbob2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb1.word != (*elfCtrl)->zanbkb1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbkb1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb1.word , (kulong)(*elfCtrl)->zanbkb1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb2.word != (*elfCtrl)->zanbkb2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbkb2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbkb.zanbkb2.word , (kulong)(*elfCtrl)->zanbkb2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb1.word != (*elfCtrl)->zanbdb1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbdb1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb1.word , (kulong)(*elfCtrl)->zanbdb1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb2.word != (*elfCtrl)->zanbdb2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zanbdb2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zanbdb.zanbdb2.word , (kulong)(*elfCtrl)->zanbdb2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw1.word != (*elfCtrl)->zlgtw1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zlgtw1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw1.word , (kulong)(*elfCtrl)->zlgtw1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw2.word != (*elfCtrl)->zlgtw2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zlgtw2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgtw.zlgtw2.word , (kulong)(*elfCtrl)->zlgtw2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.word != (*elfCtrl)->zlgt) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zlgt 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgt.word , (kulong)(*elfCtrl)->zlgt));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgte.word != (*elfCtrl)->zlgte) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zlgte 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlgte.word, (kulong)(*elfCtrl)->zlgte));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedg2anba.word != (*elfCtrl)->zedg2anba) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zedg2anba 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedg2anba.word, (kulong)(*elfCtrl)->zedg2anba));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedgscla.word != (*elfCtrl)->zedgscla) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zedgscla 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedgscla.word , (kulong)(*elfCtrl)->zedgscla));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedg2anbb.word != (*elfCtrl)->zedg2anbb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zedg2anbb 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedg2anbb.word, (kulong)(*elfCtrl)->zedg2anbb));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedgsclb.word != (*elfCtrl)->zedgsclb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zedgsclb 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zedgsclb.word , (kulong)(*elfCtrl)->zedgsclb));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge1.word != (*elfCtrl)->zalnge1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zalnge1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge1.word , (kulong)(*elfCtrl)->zalnge1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge2.word != (*elfCtrl)->zalnge2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zalnge2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalnge.zalnge2.word , (kulong)(*elfCtrl)->zalnge2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng1.word != (*elfCtrl)->zalng1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zalng1 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng1.word , (kulong)(*elfCtrl)->zalng1));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng2.word != (*elfCtrl)->zalng2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zalng2 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zalng.zalng2.word , (kulong)(*elfCtrl)->zalng2));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlfth.word != (*elfCtrl)->zlfth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zlfth 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlfth.word, (kulong)(*elfCtrl)->zlfth));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcome.word != (*elfCtrl)->zlcome) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zlcome 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcome.word , (kulong)(*elfCtrl)->zlcome));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcomen.word != (*elfCtrl)->zlcomen) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:zlcomen 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.zlcomen.word, (kulong)(*elfCtrl)->zlcomen));
        }
        
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.znslnglm.word != (*elfCtrl)->znslnglm) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) %s result:znslnglm 0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.znslnglm.word , (kulong)(*elfCtrl)->znslnglm));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_ELF_Cntl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_2_print_5(Impro32Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                        T_IM_PRO_ELF_HIGH_FREQ_AREA_EDGE_ADJ* elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgcath.bit.edgcatha != elfCtrl->highFreqAreaAdjCoeff) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Edge_Adj(%u) %s result:edgcatha 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgcath.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgcath.bit.edgcatha ,elfCtrl->highFreqAreaAdjCoeff));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgcath.bit.elftest1 != elfCtrl->testPara1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Edge_Adj(%u) %s result:elftest1 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgcath.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgcath.bit.elftest1 ,elfCtrl->testPara1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgcath.bit.elftest2 != elfCtrl->testPara2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Edge_Adj(%u) %s result:elftest2 0x%08lx(%d) in(%d)\n", 
            unitNo,    string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgcath.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.edgcath.bit.elftest2 ,elfCtrl->testPara2));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_Edge_Adj(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_2_print_6(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Start(%u) result:fshdtrg 0x%08lx(%u)\n", 
            unitNo, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdtrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdtrg.bit.fshdtrg));
}

void im_pro_3_2_print_7(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Stop(%u %u) result:fshdtrg 0x%08lx(%u)\n", 
            unitNo, force, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdtrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdtrg.bit.fshdtrg));
}

void im_pro_3_2_print_8(Impro32Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                            T_IM_PRO_FSHD_COMMON_CTRL* fshdCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdctl.bit.fsmode != fshdCtrl->correctionMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Ctrl(%u) %s result:fsmode 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdctl.bit.fsmode,fshdCtrl->correctionMode));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdctl.bit.fwmode != fshdCtrl->correctionModeAwb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Ctrl(%u) %s result:fwmode 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdctl.bit.fwmode,fshdCtrl->correctionModeAwb));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdctl.bit.fshdptmd != fshdCtrl->montageMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Ctrl(%u) %s result:fshdptmd 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdctl.bit.fshdptmd,fshdCtrl->montageMode));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul1.bit.fsulrr != fshdCtrl->clipR) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Ctrl(%u) %s result:fsulrr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul1.bit.fsulrr,fshdCtrl->clipR));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul1.bit.fsulgr != fshdCtrl->clipGr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Ctrl(%u) %s result:fsulgr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul1.bit.fsulgr,fshdCtrl->clipGr));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul2.bit.fsulgb != fshdCtrl->clipGb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Ctrl(%u) %s result:fsulgb 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul2.bit.fsulgb,fshdCtrl->clipGb));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul2.bit.fsulbb != fshdCtrl->clipB) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Ctrl(%u) %s result:fsulbb 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fsul2.bit.fsulbb,fshdCtrl->clipB));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_2_print_9(Impro32Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_PAEN(%u %u) result:paen 0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdpaen.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdpaen.bit.fspaen));
    DriverCommon_DDIM_PRINT(( "Im_PRO_FSHD_Set_PAEN(%u %u) result:fshdtrg 0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdtrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.fshd.fshdtrg.bit.fshdtrg));
}
#endif

Impro32Print* impro_3_2_print_new(void)
{
	Impro32Print* self = k_object_new_with_private(IMPRO_TYPE_3_2_PRINT, sizeof(Impro32PrintPrivate));

	return self;
}

Impro32Print* impro_3_2_print_get(void)
{
	static Impro32Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_3_2_PRINT, sizeof(Impro32PrintPrivate));
	}

	return self;
}
