/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro20Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro20print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro20Print, impro_2_0_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_2_0_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro20PrintPrivate, IMPRO_TYPE_2_0_PRINT))


struct _Impro20PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_2_0_print_constructor(Impro20Print *self)
{
	Impro20PrintPrivate *priv = IMPRO_2_0_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_2_0_print_destructor(Impro20Print *self)
{
	Impro20PrintPrivate *priv = IMPRO_2_0_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_2_0_print_4(Impro20Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_SROTOP_CTRL* ctrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.sroisw != ctrl->inputMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_STATTOP_Ctrl(%u) result:sroisw (%d) in(%d)\n", 
            unitNo, ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.sroisw, ctrl->inputMode))
        };

        if(ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.sromd != ctrl->sroModeSel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_STATTOP_Ctrl(%u) result:sromd  (%d) in(%d)\n", 
            unitNo, ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.sromd, ctrl->sroModeSel))
        };

        if(ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.cagsl != ctrl->cagTargetSel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_STATTOP_Ctrl(%u) result:cagsl  (%d) in(%d)\n", 
            unitNo, ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.cagsl, ctrl->cagTargetSel))
        };

        if(ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.brpsw0 != ctrl->bayOutPathSel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_STATTOP_Ctrl(%u) result:brpsw0 (%d) in(%d)\n", 
            unitNo, ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.brpsw0, ctrl->bayOutPathSel))
        };

        if(ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.brpsw1 != ctrl->b2bConnectPathSel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_STATTOP_Ctrl(%u) result:brpsw1 (%d) in(%d)\n", 
            unitNo, ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.brpsw1, ctrl->b2bConnectPathSel))
        };

        if(ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.brpsw2 != ctrl->ltmConnectPathSel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_STATTOP_Ctrl(%u) result:brpsw2 (%d) in(%d)\n", 
            unitNo, ioPro.imgPipe[unitNo].sro.srotop.srotopctl1.bit.brpsw2, ctrl->ltmConnectPathSel))
        };

        if(ioPro.imgPipe[unitNo].sro.srotop.srotopctl2.bit.org0 != ctrl->firstPixel[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_STATTOP_Ctrl(%u) result:org0   (%d) in(%d)\n", 
            unitNo, ioPro.imgPipe[unitNo].sro.srotop.srotopctl2.bit.org0, ctrl->firstPixel[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.srotop.srotopctl2.bit.org1 != ctrl->firstPixel[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_STATTOP_Ctrl(%u) result:org1   (%d) in(%d)\n", 
            unitNo, ioPro.imgPipe[unitNo].sro.srotop.srotopctl2.bit.org1, ctrl->firstPixel[1]))
        };
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_STATTOP_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_0_print_5(Impro20Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, 
kint32 ercd, T_IM_PRO_SROTOP_WEITGEN_CTRL* ctrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if( ch == E_IM_PRO_WEITGEN_CH0) {
            if(ioPro.imgPipe[unitNo].sro.srotop.waitgenv.bit.genv0 != ctrl->vWaitSignalPos) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_WEITGEN_Ctrl(%u %u) result:genv0    (%d) in(%d)\n", 
            unitNo, ch, ioPro.imgPipe[unitNo].sro.srotop.waitgenv.bit.genv0, ctrl->vWaitSignalPos))
            };
            
            if(ioPro.imgPipe[unitNo].sro.srotop.waitgenh.bit.genh0 != ctrl->hWaitSignalPos) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_WEITGEN_Ctrl(%u %u) result:genh0    (%d) in(%d)\n", 
            unitNo, ch, ioPro.imgPipe[unitNo].sro.srotop.waitgenh.bit.genh0, ctrl->hWaitSignalPos))
            };
        } else {
            if(ioPro.imgPipe[unitNo].sro.srotop.waitgenv.bit.genv1 != ctrl->vWaitSignalPos) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_WEITGEN_Ctrl(%u %u) result:genv0    (%d) in(%d)\n", 
            unitNo, ch, ioPro.imgPipe[unitNo].sro.srotop.waitgenv.bit.genv1, ctrl->vWaitSignalPos))
            };
            
            if(ioPro.imgPipe[unitNo].sro.srotop.waitgenh.bit.genh1 != ctrl->hWaitSignalPos) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_WEITGEN_Ctrl(%u %u) result:genh0    (%d) in(%d)\n", 
            unitNo, ch, ioPro.imgPipe[unitNo].sro.srotop.waitgenh.bit.genh1, ctrl->hWaitSignalPos))
            };
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_WEITGEN_Ctrl(%u %u) error ercd=0x%x\n",  unitNo, ch, ercd));
    }
}

void im_pro_2_0_print_6(Impro20Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, 
kint32 ercd, E_IM_PRO_WEITGEN_ENABLE ctrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if( ch == E_IM_PRO_WEITGEN_CH0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_WEITGEN_Enable(%u %u) result:genen0 (%d) in(%d)\n", 
            unitNo, ch, ioPro.imgPipe[unitNo].sro.srotop.waitgenen.bit.genen0, ctrl));
        } else {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_WEITGEN_Enable(%u %u) result:genen1 (%d) in(%d)\n", 
            unitNo, ch, ioPro.imgPipe[unitNo].sro.srotop.waitgenen.bit.genen1, ctrl));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_WEITGEN_Enable(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_0_print_7(Impro20Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_AFPB_CH ch)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_AFPB_Start(%u %u) result:afpbtrg  0x%08lx(%u)\n", 
            unitNo, ch, (kulong)&ioPro.imgPipe[unitNo].sro.afpb[ch].afpbtrg.word, 
            ioPro.imgPipe[unitNo].sro.afpb[ch].afpbtrg.bit.afpbtrg));
}

void im_pro_2_0_print_8(Impro20Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_AFPB_CH ch, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_AFPB_Stop(%u %u %u) result:afpbtrg 0x%08lx(%u)\n", 
            unitNo, ch, force, (kulong)&ioPro.imgPipe[unitNo].sro.afpb[ch].afpbtrg.word, 
            ioPro.imgPipe[unitNo].sro.afpb[ch].afpbtrg.bit.afpbtrg));
}

void im_pro_2_0_print_9(Impro20Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_AFPB_CH ch, 
                        T_IM_PRO_AFPB_CTRL* afpbCtrl)
{
    if(ioPro.imgPipe[unitNo].sro.afpb[ch].afpbh.bit.afpbh != afpbCtrl->afpbArea.posX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_AFPB_Ctrl(%u %u) %s result:afpbh  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.afpb[ch].afpbh.word, 
            ioPro.imgPipe[unitNo].sro.afpb[ch].afpbh.bit.afpbh,afpbCtrl->afpbArea.posX))
    };
    
    if(ioPro.imgPipe[unitNo].sro.afpb[ch].afpbv.bit.afpbv != afpbCtrl->afpbArea.posY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_AFPB_Ctrl(%u %u) %s result:afpbv  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.afpb[ch].afpbv.word, 
            ioPro.imgPipe[unitNo].sro.afpb[ch].afpbv.bit.afpbv,afpbCtrl->afpbArea.posY))
    };
    
    if(ioPro.imgPipe[unitNo].sro.afpb[ch].afpbhw.bit.afpbhw != afpbCtrl->afpbArea.width) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_AFPB_Ctrl(%u %u) %s result:afpbhw  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.afpb[ch].afpbhw.word, 
            ioPro.imgPipe[unitNo].sro.afpb[ch].afpbhw.bit.afpbhw,afpbCtrl->afpbArea.width))
    };
    
    if(ioPro.imgPipe[unitNo].sro.afpb[ch].afpbvw.bit.afpbvw != afpbCtrl->afpbArea.lines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_AFPB_Ctrl(%u %u) %s result:afpbvw  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.afpb[ch].afpbvw.word, 
            ioPro.imgPipe[unitNo].sro.afpb[ch].afpbvw.bit.afpbvw,afpbCtrl->afpbArea.lines))
    };
    
}
#endif

Impro20Print* impro_2_0_print_new(void)
{
	Impro20Print* self = k_object_new_with_private(IMPRO_TYPE_2_0_PRINT, sizeof(Impro20PrintPrivate));

	return self;
}

Impro20Print* impro_2_0_print_get(void)
{
	static Impro20Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_2_0_PRINT, sizeof(Impro20PrintPrivate));
	}

	return self;
}
