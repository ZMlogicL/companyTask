/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro30Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro30print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro30Print, impro_3_0_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_3_0_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro30PrintPrivate, IMPRO_TYPE_3_0_PRINT))


struct _Impro30PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_3_0_print_constructor(Impro30Print *self)
{
	Impro30PrintPrivate *priv = IMPRO_3_0_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_3_0_print_destructor(Impro30Print *self)
{
	Impro30PrintPrivate *priv = IMPRO_3_0_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_3_0_print_4(Impro30Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_B2BTOP_CTRL* b2btopCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl1.bit.b2bisw != b2btopCtrl->inputMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Ctrl(%u) %s result:b2bisw 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl1.word , 
            ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl1.bit.b2bisw ,b2btopCtrl->inputMode));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl1.bit.cagsl != b2btopCtrl->cagTargetSel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Ctrl(%u) %s result:cagsl 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl1.word , 
            ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl1.bit.cagsl,b2btopCtrl->cagTargetSel));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl2.bit.org0 != b2btopCtrl->firstPixel[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Ctrl(%u) %s result:org0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl2.word , 
            ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl2.bit.org0 ,b2btopCtrl->firstPixel[0]));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl2.bit.org1 != b2btopCtrl->firstPixel[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Ctrl(%u) %s result:org1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl2.word , 
            ioPro.imgPipe[unitNo].b2b.b2btop.b2btopctl2.bit.org1 ,b2btopCtrl->firstPixel[1]));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_0_print_5(Impro30Print *self, E_IM_PRO_UNIT_NUM unitNo)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Start(%u) result:elftrg 0x%08lx(%u)\n", 
            unitNo, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elftrg.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elftrg.bit.elftrg));
}

void im_pro_3_0_print_6(Impro30Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Stop(%u %u) result:elftrg 0x%08lx(%u)\n", 
            unitNo, force, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elftrg.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elftrg.bit.elftrg));
}

void im_pro_3_0_print_7(Impro30Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_PAEN(%u %u) result:paen 0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfpaen.word , 
            ioPro.imgPipe[unitNo].b2b.elf.elfpaen.bit.epaen));
    DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_PAEN(%u %u) result:elftrg 0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elftrg.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elftrg.bit.elftrg));
}

void im_pro_3_0_print_8(Impro30Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                        T_IM_PRO_ELF_COMMON_CTRL* elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.elfpdd != elfCtrl->pixPadding) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl_Common(%u) %s result:elfpdd 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfctl.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.elfpdd,elfCtrl->pixPadding));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.elfrng != elfCtrl->paddingMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl_Common(%u) %s result:elfrng 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfctl.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.elfrng,elfCtrl->paddingMode));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.elfafs != elfCtrl->nrSelect) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl_Common(%u) %s result:elfafs 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfctl.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.elfafs,elfCtrl->nrSelect));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl_Common(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_3_0_print_9(Impro30Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_ELF_CTRL* elfCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.n1s5en != elfCtrl->cmn1.n1s5Enable) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:n1s5en 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfctl.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.n1s5en,elfCtrl->cmn1.n1s5Enable));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.n5s9en != elfCtrl->cmn1.n5s9Enable) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:n5s9en 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfctl.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.n5s9en,elfCtrl->cmn1.n5s9Enable));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.nfs9en != elfCtrl->cmn1.f9Enable) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:nfs9en 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfctl.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.nfs9en,elfCtrl->cmn1.f9Enable));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.nla0en != elfCtrl->cmn1.a0Enable) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:nla0en 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfctl.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.nla0en,elfCtrl->cmn1.a0Enable));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.f5md != elfCtrl->cmn1.f5FilterMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:f5md 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfctl.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.f5md,elfCtrl->cmn1.f5FilterMode));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.f9md != elfCtrl->cmn1.f9FilterMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:f9md 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfctl.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.f9md,elfCtrl->cmn1.f9FilterMode));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.efmd != elfCtrl->cmn1.eFilterMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:efmd 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfctl.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.efmd,elfCtrl->cmn1.eFilterMode));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.lfmd != elfCtrl->cmn1.lFilterMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:lfmd 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfctl.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfctl.bit.lfmd,elfCtrl->cmn1.lFilterMode));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl1.bit.elfl1 != elfCtrl->cmn2.elfl1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:elfl1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl1.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl1.bit.elfl1 ,elfCtrl->cmn2.elfl1));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl1.bit.elfl2 != elfCtrl->cmn2.elfl2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:elfl2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl1.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl1.bit.elfl2 ,elfCtrl->cmn2.elfl2));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl2.bit.elfl3 != elfCtrl->cmn2.elfl3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:elfl3 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl2.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl2.bit.elfl3 ,elfCtrl->cmn2.elfl3));
        }
        
        if(ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl2.bit.elfl4 != elfCtrl->cmn2.elfl4) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) %s result:elfl4 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl2.word, 
            ioPro.imgPipe[unitNo].b2b.elf.elfl.elfl2.bit.elfl4 ,elfCtrl->cmn2.elfl4));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}
#endif

Impro30Print* impro_3_0_print_new(void)
{
	Impro30Print* self = k_object_new_with_private(IMPRO_TYPE_3_0_PRINT, sizeof(Impro30PrintPrivate));

	return self;
}

Impro30Print* impro_3_0_print_get(void)
{
	static Impro30Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_3_0_PRINT, sizeof(Impro30PrintPrivate));
	}

	return self;
}
