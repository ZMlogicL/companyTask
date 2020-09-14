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
    TImProCallbackCfg callbackIntCtrl;
    T_IM_PRO_INT_STATTOP_CTRL stattopIntCtrl;
    T_IM_PRO_INT_CFG intCtrl;
};


/**
 *IMPL 
 */
static void ct_impro_7_7_constructor(CtImpro77 *self)
{
	CtImpro77Private *priv = CT_IMPRO_7_7_GET_PRIVATE(self);

    priv->callbackIntCtrl.inthandler = NULL;
    priv->callbackIntCtrl.userParam = 0;
    priv->stattopIntCtrl.intMode = E_IM_PRO_INT_INTMD_ORAND;
    priv->intCtrl.interruptBit = 0;
    priv->intCtrl.permissionFlg = 0;
}

static void ct_impro_7_7_destructor(CtImpro77 *self)
{
	CtImpro77Private *priv = CT_IMPRO_7_7_GET_PRIVATE(self);
}


/**
 *PUBLIC 
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_7_0(CtImpro77* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 vdInte = (D_IM_PRO_B2BTOP_INT_VDE0 | D_IM_PRO_B2BTOP_INT_VDE1);
    kuint32 vdIntf = (D_IM_PRO_B2BTOP_INT_VDF0 | D_IM_PRO_B2BTOP_INT_VDF1);

    im_pro_debug_b2btop_vd_intflg_fill(im_pro_debug_get(),1, vdInte, vdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_B2BTOP_Pipe2_VD_Int_Handler();
}

void ct_im_pro_7_7_1(CtImpro77* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 hdInte = (D_IM_PRO_B2BTOP_INT_HDE0 | D_IM_PRO_B2BTOP_INT_HDE1);
    kuint32 hdIntf = (D_IM_PRO_B2BTOP_INT_HDF0 | D_IM_PRO_B2BTOP_INT_HDF1);

    im_pro_debug_b2btop_hd_intflg_fill(im_pro_debug_get(),1, hdInte, hdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_B2BTOP_Pipe2_HD_Int_Handler();
}

void ct_im_pro_7_7_2(CtImpro77* self,const kuint32 idx)
{
	CtImpro77Private *priv = CT_IMPRO_7_7_GET_PRIVATE(self);
    kint32 ercd;
    kuchar  intMode;

    if(idx == 1) {
        for(intMode = ImPro_INT_INTMD_OR; intMode < E_IM_PRO_INT_INTMD_ORAND + 1; intMode++) {
            priv->stattopIntCtrl.intMode = intMode;
            ercd = Im_PRO_STATTOP_Interrupt_Ctrl(&priv->stattopIntCtrl);
            im_pro_7_print_72(im_pro_7_print_get(), ercd, &priv->stattopIntCtrl);
        }
    }
}

void ct_im_pro_7_7_3(CtImpro77* self,const kuint32 idx)
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

void ct_im_pro_7_7_4(CtImpro77* self,const kuint32 idx)
{
	CtImpro77Private *priv = CT_IMPRO_7_7_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_AEAWB_CH_NUM; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                priv->intCtrl.permissionFlg = permissionFlg;

                priv->intCtrl.interruptBit = D_IM_PRO_LINEINTENB_LINEE;
#ifdef CO_DEBUG_ON_PC
                ioPro.stat.aeawb[ch].lineintflg.word = priv->intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_AEAWB_Set_Interrupt(ch, &priv->intCtrl);
                im_pro_7_print_74(im_pro_7_print_get(), ercd, ch, &priv->intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_7_5(CtImpro77* self,const kuint32 idx)
{
	CtImpro77Private *priv = CT_IMPRO_7_7_GET_PRIVATE(self);
    kint32 ercd;
    kuchar ch;
    kulong userParam;

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_AEAWB_CH_NUM; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                priv->callbackIntCtrl.inthandler = im_pro_callback_stat_aeawb_int_cb;
                priv->callbackIntCtrl.userParam = userParam;
                ercd = Im_PRO_AEAWB_Set_Int_Handler(ch, &priv->callbackIntCtrl);
                im_pro_7_print_75(im_pro_7_print_get(), "", ch, ercd, &priv->callbackIntCtrl);
            }
        }
    }
}

void ct_im_pro_7_7_6(CtImpro77* self,const kuint32 idx)
{
	CtImpro77Private *priv = CT_IMPRO_7_7_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_AF_CH_NUM; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                priv->intCtrl.permissionFlg = permissionFlg;

                priv->intCtrl.interruptBit = D_IM_PRO_AFINTENB_AFE;
#ifdef CO_DEBUG_ON_PC
                ioPro.stat.af[ch].afgbal.afintflg.word = priv->intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_AF_Set_Interrupt(ch, &priv->intCtrl);
                im_pro_7_print_76(im_pro_7_print_get(), ercd, ch, &priv->intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_7_7(CtImpro77* self,const kuint32 idx)
{
	CtImpro77Private *priv = CT_IMPRO_7_7_GET_PRIVATE(self);
    kint32 ercd;
    kuchar ch;
    kulong userParam;

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_AF_CH_NUM; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                priv->callbackIntCtrl.inthandler = im_pro_callback_stat_af_int_cb;
                priv->callbackIntCtrl.userParam = userParam;
                ercd = Im_PRO_AF_Set_Int_Handler(ch, &priv->callbackIntCtrl);
                im_pro_7_print_77(im_pro_7_print_get(), "", ch, ercd, &priv->callbackIntCtrl);
            }
        }
    }
}

void ct_im_pro_7_7_8(CtImpro77* self,const kuint32 idx)
{
	CtImpro77Private *priv = CT_IMPRO_7_7_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_HIST_CH_NUM; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                priv->intCtrl.permissionFlg = permissionFlg;

                priv->intCtrl.interruptBit = D_IM_PRO_HISTINTENB_HISTE;
#ifdef CO_DEBUG_ON_PC
                ioPro.stat.hist[ch].histintflg.word = priv->intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_HIST_Set_Interrupt(ch, &priv->intCtrl);
                im_pro_7_print_78(im_pro_7_print_get(), ercd, ch, &priv->intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_7_9(CtImpro77* self,const kuint32 idx)
{
	CtImpro77Private *priv = CT_IMPRO_7_7_GET_PRIVATE(self);
    kint32 ercd;
    kuchar ch;
    kulong userParam;

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_STAT_HIST_CH_NUM; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                priv->callbackIntCtrl.inthandler = im_pro_callback_stat_hist_int_cb;
                priv->callbackIntCtrl.userParam = userParam;
                ercd = Im_PRO_HIST_Set_Int_Handler(ch, &priv->callbackIntCtrl);
                im_pro_7_print_79(im_pro_7_print_get(), "", ch, ercd, &priv->callbackIntCtrl);
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
