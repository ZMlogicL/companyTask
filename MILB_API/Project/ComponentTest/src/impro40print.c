/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro40Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro40print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro40Print, impro_4_0_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_4_0_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro40PrintPrivate, IMPRO_TYPE_4_0_PRINT))


struct _Impro40PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_4_0_print_constructor(Impro40Print *self)
{
	Impro40PrintPrivate *priv = IMPRO_4_0_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_4_0_print_destructor(Impro40Print *self)
{
	Impro40PrintPrivate *priv = IMPRO_4_0_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_4_0_print_4(Impro40Print *self,const char *string, kint32 ercd, T_IM_PRO_STATTOP_CTRL *ctrl)
{
    if (ercd == DdimUserCustom_E_OK)
    {
        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.afsw0 != ctrl->afInputSel[0])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:afsw0    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.afsw0, ctrl->afInputSel[0]));
        }

        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.afsw1 != ctrl->afInputSel[1])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:afsw1    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.afsw1, ctrl->afInputSel[1]));
        }

        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.flsw0 != ctrl->flckInputSel[0])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:flsw0    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.flsw0, ctrl->flckInputSel[0]));
        }

        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.flsw1 != ctrl->flckInputSel[1])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:flsw1    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.flsw1, ctrl->flckInputSel[1]));
        }

        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.aesw0 != ctrl->aeawbInputSel[0])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:aesw0    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.aesw0, ctrl->aeawbInputSel[0]));
        }

        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.aesw1 != ctrl->aeawbInputSel[1])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:aesw1    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.aesw1, ctrl->aeawbInputSel[1]));
        }

        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.aesw2 != ctrl->aeawbInputSel[2])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:aesw2    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.aesw2, ctrl->aeawbInputSel[2]));
        }

        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.aesw3 != ctrl->aeawbInputSel[3])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:aesw3    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.aesw3, ctrl->aeawbInputSel[3]));
        }

        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.hisw0 != ctrl->histInputSel[0])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:hisw0    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.hisw0, ctrl->histInputSel[0]));
        }

        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.hisw1 != ctrl->histInputSel[1])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:hisw1    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.hisw1, ctrl->histInputSel[1]));
        }

        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.hisw2 != ctrl->histInputSel[2])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:hisw2    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.hisw2, ctrl->histInputSel[2]));
        }

        if (((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.hisw3 != ctrl->histInputSel[3])
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() result:hisw3    (%u) in(%d)\n", 
            ((AbsImProPrint*)self)->ioPro->stat.stattop.stattopctl1.bit.hisw3, ctrl->histInputSel[3]));
        }
    } else {
            DriverCommon_DDIM_PRINT(("Im_PRO_STATTOP_Ctrl() error(not exist) ercd=0x%x\n", ercd));
        }
}

void im_pro_4_0_print_5(Impro40Print *self,E_IM_PRO_AEAWB_CH ch)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Start(%u) result:aetrg   0x%08lx(%u)\n", 
        ch, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetrg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetrg.bit.aetrg));
}

void im_pro_4_0_print_6(Impro40Print *self,E_IM_PRO_AEAWB_CH ch, kuchar force)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Stop(%u %u) result:aetrg 0x%08lx(%u)\n", 
        ch, force, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetrg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetrg.bit.aetrg));
}

void im_pro_4_0_print_7(Impro40Print *self,const char *string, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_CTRL *aeawbCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeawbctl.bit.aeawbwmd != aeawbCtrl->aeawbMode)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aeawbwmd  0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeawbctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeawbctl.bit.aeawbwmd, 
        aeawbCtrl->aeawbMode));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeawbctl.bit.awbgmd != aeawbCtrl->awb_mode)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:awbgmd    0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeawbctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeawbctl.bit.awbgmd, 
        aeawbCtrl->awb_mode));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeawbctl.bit.aeewmd != aeawbCtrl->awbWdWindowMode)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aeewmd    0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeawbctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeawbctl.bit.aeewmd, 
        aeawbCtrl->awbWdWindowMode));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeh.bit.aeh != aeawbCtrl->awbArea.posX)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aeh       0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeh.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeh.bit.aeh, 
        aeawbCtrl->awbArea.posX));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aev.bit.aev != aeawbCtrl->awbArea.posY)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aev       0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aev.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aev.bit.aev, 
        aeawbCtrl->awbArea.posY));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aehw.bit.aehw != aeawbCtrl->awbArea.width)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aehw      0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aehw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aehw.bit.aehw, 
        aeawbCtrl->awbArea.width));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aevw.bit.aevw != aeawbCtrl->awbArea.lines)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aevw      0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aevw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aevw.bit.aevw, 
        aeawbCtrl->awbArea.lines));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetw.bit.aetw != aeawbCtrl->awbArea.topLines)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aetw      0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetw.bit.aetw, 
        aeawbCtrl->awbArea.topLines));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aebw.bit.aebw != aeawbCtrl->awbArea.bottomLines)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aebw      0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aebw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aebw.bit.aebw, 
        aeawbCtrl->awbArea.bottomLines));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aelw.bit.aelw != aeawbCtrl->awbArea.leftWidth)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aelw      0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aelw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aelw.bit.aelw, 
        aeawbCtrl->awbArea.leftWidth));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aerw.bit.aerw != aeawbCtrl->awbArea.rightWidth)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aerw      0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aerw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aerw.bit.aerw, 
        aeawbCtrl->awbArea.rightWidth));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aevbc.bit.aevbc != aeawbCtrl->hBcNum)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aevbc     0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aevbc.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aevbc.bit.aevbc, 
        aeawbCtrl->hBcNum));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aehbc.bit.aehbc != aeawbCtrl->vBcNum)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Ctrl(%u) %s result:aehbc     0x%08lx(%u) (%u)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aehbc.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aehbc.bit.aehbc, 
        aeawbCtrl->vBcNum));
    }
}

void im_pro_4_0_print_8(Impro40Print *self,E_IM_PRO_AEAWB_CH ch, kuchar paenTrg)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_PAEN(%u %u) result:paen     0x%08lx(%u)\n", 
        ch, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeawbpaen.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aeawbpaen.bit.paen));
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Set_PAEN(%u %u) result:aetrg    0x%08lx(%u)\n", 
        ch, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetrg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].aetrg.bit.aetrg));
}
#endif

Impro40Print* impro_4_0_print_new(void)
{
	Impro40Print* self = k_object_new_with_private(IMPRO_TYPE_4_0_PRINT, sizeof(Impro40PrintPrivate));

	return self;
}

Impro40Print* impro_4_0_print_get(void)
{
	static Impro40Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_4_0_PRINT, sizeof(Impro40PrintPrivate));
	}

	return self;
}
