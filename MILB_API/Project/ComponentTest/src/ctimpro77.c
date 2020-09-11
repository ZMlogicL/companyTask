/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro77
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro77.h"
#include "impro7print.h"
#include "improdebug.h"
#include "improcallback.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImpro77, ct_impro_7_7)
#define CT_IMPRO_7_7_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro77Private, CT_TYPE_IMPRO_7_7))


struct _CtImpro77Private
{

};


/**
 *IMPL 
 */
static void ct_impro_7_7_constructor(CtImpro77 *self)
{
	CtImpro77Private *priv = CT_IMPRO_7_7_GET_PRIVATE(self);
}

static void ct_impro_7_7_destructor(CtImpro77 *self)
{
	CtImpro77Private *priv = CT_IMPRO_7_7_GET_PRIVATE(self);
}


/**
 *PUBLIC 
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_70(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 vdInte = (D_IM_PRO_B2BTOP_INT_VDE0 | D_IM_PRO_B2BTOP_INT_VDE1);
    kuint32 vdIntf = (D_IM_PRO_B2BTOP_INT_VDF0 | D_IM_PRO_B2BTOP_INT_VDF1);

    im_pro_debug_b2btop_vd_intflg_fill(im_pro_debug_get(),1, vdInte, vdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_B2BTOP_Pipe2_VD_Int_Handler();
}

void ct_im_pro_7_71(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 hdInte = (D_IM_PRO_B2BTOP_INT_HDE0 | D_IM_PRO_B2BTOP_INT_HDE1);
    kuint32 hdIntf = (D_IM_PRO_B2BTOP_INT_HDF0 | D_IM_PRO_B2BTOP_INT_HDF1);

    im_pro_debug_b2btop_hd_intflg_fill(im_pro_debug_get(),1, hdInte, hdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_B2BTOP_Pipe2_HD_Int_Handler();
}

void ct_im_pro_7_72(const kuint32 idx)
{
    kint32 ercd;
    kuchar  intMode;
    T_IM_PRO_INT_STATTOP_CTRL intCtrl = {
        .intMode = E_IM_PRO_INT_INTMD_ORAND,
    };

    if(idx == 1) {
        for(intMode = E_IM_PRO_INT_INTMD_OR; intMode < E_IM_PRO_INT_INTMD_ORAND + 1; intMode++) {
            intCtrl.intMode = intMode;
            ercd = Im_PRO_STATTOP_Interrupt_Ctrl(&intCtrl);
            im_pro_7_72_Print(NULL,ercd, &intCtrl);
        }
    }
}

void ct_im_pro_7_73(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 ch = 0;
    kuint32 aeawbInte = D_IM_PRO_LINEINTENB_LINEE;
    kuint32 aeawbIntf = D_IM_PRO_LINEINTFLG_LINEF;

    kuint32 afInte = D_IM_PRO_AFINTENB_AFE;
    kuint32 afIntf = D_IM_PRO_AFINTFLG_AFF;

    kuint32 histInte = D_IM_PRO_HISTINTENB_HISTE;
    kuint32 histIntf = D_IM_PRO_HISTINTFLG_HISTF;

    for(ch = 0; ch < D_IM_PRO_STAT_AEAWB_CH_NUM; ch++) {
        im_pro_debug_stat_aeawb_intflg_fill(im_pro_debug_get(),ch, aeawbInte, aeawbIntf);
    }

    for(ch = 0; ch < D_IM_PRO_STAT_AF_CH_NUM; ch++) {
        im_pro_debug_stat_af_intflg_fill(im_pro_debug_get(),ch, afInte, afIntf);
    }

    for(ch = 0; ch < D_IM_PRO_STAT_HIST_CH_NUM; ch++) {
        im_pro_debug_stat_hist_intflg_fill(im_pro_debug_get(),ch, histInte, histIntf);
    }
#endif  // CO_DEBUG_ON_PC
    Im_PRO_STAT_Int_Handler();
}

void ct_im_pro_7_74(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;
    T_IM_PRO_INT_CFG intCtrl = {
        .interruptBit = 0,
        .permissionFlg = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_AEAWB_CH_NUM; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                intCtrl.permissionFlg = permissionFlg;

                intCtrl.interruptBit = D_IM_PRO_LINEINTENB_LINEE;
#ifdef CO_DEBUG_ON_PC
                ioPro.stat.aeawb[ch].lineintflg.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_AEAWB_Set_Interrupt(ch, &intCtrl);
                im_pro_7_74_Print(NULL,ercd, ch, &intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_75(const kuint32 idx)
{
    kint32 ercd;
    kuchar ch;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_AEAWB_CH_NUM; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                intCtrl.inthandler = im_pro_callback_stat_aeawb_int_cb;
                intCtrl.userParam = userParam;
                ercd = Im_PRO_AEAWB_Set_Int_Handler(ch, &intCtrl);
                im_pro_7_75_Print(NULL,"", ch, ercd, &intCtrl);
            }
        }
    }
}

void ct_im_pro_7_76(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;
    T_IM_PRO_INT_CFG intCtrl = {
        .interruptBit = 0,
        .permissionFlg = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_AF_CH_NUM; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                intCtrl.permissionFlg = permissionFlg;

                intCtrl.interruptBit = D_IM_PRO_AFINTENB_AFE;
#ifdef CO_DEBUG_ON_PC
                ioPro.stat.af[ch].afgbal.afintflg.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_AF_Set_Interrupt(ch, &intCtrl);
                im_pro_7_76_Print(NULL,ercd, ch, &intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_77(const kuint32 idx)
{
    kint32 ercd;
    kuchar ch;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_AF_CH_NUM; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                intCtrl.inthandler = im_pro_callback_stat_af_int_cb;
                intCtrl.userParam = userParam;
                ercd = Im_PRO_AF_Set_Int_Handler(ch, &intCtrl);
                im_pro_7_77_Print(NULL,"", ch, ercd, &intCtrl);
            }
        }
    }
}

void ct_im_pro_7_78(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;
    T_IM_PRO_INT_CFG intCtrl = {
        .interruptBit = 0,
        .permissionFlg = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_HIST_CH_NUM; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                intCtrl.permissionFlg = permissionFlg;

                intCtrl.interruptBit = D_IM_PRO_HISTINTENB_HISTE;
#ifdef CO_DEBUG_ON_PC
                ioPro.stat.hist[ch].histintflg.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_HIST_Set_Interrupt(ch, &intCtrl);
                im_pro_7_78_Print(NULL,ercd, ch, &intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_79(const kuint32 idx)
{
    kint32 ercd;
    kuchar ch;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_HIST_CH_NUM; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                intCtrl.inthandler = im_pro_callback_stat_hist_int_cb;
                intCtrl.userParam = userParam;
                ercd = Im_PRO_HIST_Set_Int_Handler(ch, &intCtrl);
                im_pro_7_79_Print(NULL,"", ch, ercd, &intCtrl);
            }
        }
    }
}
#endif

CtImpro77* ct_impro_7_7_new(void)
{
	CtImpro77* self = k_object_new_with_private(CT_TYPE_IMPRO_7_7, sizeof(CtImpro77Private));

	return self;
}

CtImpro77* ct_impro_7_7_get(void)
{
	static CtImpro77* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_7_7, sizeof(CtImpro77Private));
	}

	return self;
}
