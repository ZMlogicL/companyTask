/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro76
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro76.h"
#include "impro7print.h"
#include "improdebug.h"
#include "improcallback.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImpro76, ct_impro_7_6)
#define CT_IMPRO_7_6_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro76Private, CT_TYPE_IMPRO_7_6))


struct _CtImpro76Private
{
    TImProCallbackCfg callbackIntCtrl;
    T_IM_PRO_INT_B2BTOP_CTRL b2btopIntCtrl;
    T_IM_PRO_INT_VHD_DELAY_CTRL vhdDelayIntCtrlMax;
    T_IM_PRO_INT_VHD_DELAY_CTRL vhdDelayIntCtrlMin;
    TImProCallbackCfg callbackIntCtrlMax;
};


static void ct_impro_7_6_constructor(CtImpro76 *self)
{
	CtImpro76Private *priv = CT_IMPRO_7_6_GET_PRIVATE(self);

    priv->callbackIntCtrl.inthandler = NULL;
    priv->callbackIntCtrl.userParam = 0;

    priv->b2btopIntCtrl.intMode = E_IM_PRO_INT_INTMD_ORAND;
    priv->b2btopIntCtrl.vdEnable[0].interruptBit = 0;
    priv->b2btopIntCtrl.vdEnable[0].permissionFlg = 0;
    priv->b2btopIntCtrl.hdEnable[0].interruptBit = 0;
    priv->b2btopIntCtrl.hdEnable[0].permissionFlg = 0;
    priv->b2btopIntCtrl.vdEnable[1].interruptBit = 0;
    priv->b2btopIntCtrl.vdEnable[1].permissionFlg = 0;
    priv->b2btopIntCtrl.hdEnable[1].interruptBit = 0;
    priv->b2btopIntCtrl.hdEnable[1].permissionFlg = 0;

    priv->vhdDelayIntCtrlMax.hdDelay = 12288;
    priv->vhdDelayIntCtrlMax.vdHDelay = 12288;
    priv->vhdDelayIntCtrlMax.vdVDelay = 16383;

    priv->vhdDelayIntCtrlMin.hdDelay = 0;
    priv->vhdDelayIntCtrlMin.vdHDelay = 0;
    priv->vhdDelayIntCtrlMin.vdVDelay = 0;
    
    priv->callbackIntCtrlMax.inthandler = im_pro_callback_b2b_hd_int_cb;
    priv->callbackIntCtrlMax.userParam = 0;
}

static void ct_impro_7_6_destructor(CtImpro76 *self)
{
	CtImpro76Private *priv = CT_IMPRO_7_6_GET_PRIVATE(self);
}

#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_6_0(CtImpro76* self,const kuint32 idx)
{
	CtImpro76Private *priv = CT_IMPRO_7_6_GET_PRIVATE(self);
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar ch;
    kulong userParam;

    if(idx == 1) {
        for(unitNo = 0; unitNo < E_IM_PRO_BOTH_UNIT; unitNo++) {
            for(ch = 0; ch < D_IM_PRO_SRO_SDC_CH_NUM; ch++) {
                for(userParam = 0; userParam < 4; userParam++) {
                    priv->callbackIntCtrl.inthandler = im_pro_callback_sro_sdc_int_cb;
                    priv->callbackIntCtrl.userParam = userParam;
                    ercd = Im_PRO_SDC_Set_Int_Handler(unitNo, ch, &priv->callbackIntCtrl);
                    im_pro_7_print_60(im_pro_7_print_get(), "", unitNo, ch, ercd, &priv->callbackIntCtrl);
                }
            }
        }
    }
}

void ct_im_pro_7_6_1(CtImpro76* self,const kuint32 idx)
{
	CtImpro76Private *priv = CT_IMPRO_7_6_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar  intMode;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(intMode = ImPro_INT_INTMD_OR; intMode < E_IM_PRO_INT_INTMD_ORAND + 1; intMode++) {
                for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                    priv->b2btopIntCtrl.vdEnable[0].permissionFlg = permissionFlg;
                    priv->b2btopIntCtrl.hdEnable[0].permissionFlg = permissionFlg;
                    priv->b2btopIntCtrl.vdEnable[1].permissionFlg = permissionFlg;
                    priv->b2btopIntCtrl.hdEnable[1].permissionFlg = permissionFlg;

                    priv->b2btopIntCtrl.vdEnable[0].interruptBit = D_IM_PRO_B2BTOP_INT_VDE0;
                    priv->b2btopIntCtrl.hdEnable[0].interruptBit = D_IM_PRO_B2BTOP_INT_HDE0;
                    priv->b2btopIntCtrl.vdEnable[1].interruptBit = D_IM_PRO_B2BTOP_INT_VDE1;
                    priv->b2btopIntCtrl.hdEnable[1].interruptBit = D_IM_PRO_B2BTOP_INT_HDE1;
                    priv->b2btopIntCtrl.intMode = intMode;

#ifdef CO_DEBUG_ON_PC
                    ioPro.imgPipe[unitNo].b2b.b2btop.vhdintflg.word = (priv->b2btopIntCtrl.vdEnable[0].interruptBit | priv->b2btopIntCtrl.vdEnable[1].interruptBit | priv->b2btopIntCtrl.hdEnable[0].interruptBit | priv->b2btopIntCtrl.hdEnable[1].interruptBit);
#endif  // CO_DEBUG_ON_PC
                    ercd = Im_PRO_B2BTOP_Interrupt_Ctrl(unitNo, &priv->b2btopIntCtrl);
                    im_pro_7_print_61(im_pro_7_print_get(), ercd, unitNo, &priv->b2btopIntCtrl, permissionFlg);
                }
            }
        }
    }
}

void ct_im_pro_7_6_2(CtImpro76* self,const kuint32 idx)
{
	CtImpro76Private *priv = CT_IMPRO_7_6_GET_PRIVATE(self);
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(ch = 0; ch < 2; ch++) {
                ercd = Im_PRO_B2BTOP_Set_VHD_Delay(unitNo, ch, &priv->vhdDelayIntCtrlMax);
                im_pro_7_print_62(im_pro_7_print_get(), "max_para", unitNo, ch, ercd, &priv->vhdDelayIntCtrlMax);

                ercd = Im_PRO_B2BTOP_Set_VHD_Delay(unitNo, ch, &priv->vhdDelayIntCtrlMin);
                im_pro_7_print_62(im_pro_7_print_get(), "min_para", unitNo, ch, ercd, &priv->vhdDelayIntCtrlMin);
            }
        }
    }
}

void ct_im_pro_7_6_3(CtImpro76* self,const kuint32 idx)
{
}

void ct_im_pro_7_6_4(CtImpro76* self,const kuint32 idx)
{
	CtImpro76Private *priv = CT_IMPRO_7_6_GET_PRIVATE(self);
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kulong userParam;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(userParam = 0; userParam < 4; userParam++) {
                priv->callbackIntCtrlMax.userParam = userParam;
                ercd = Im_PRO_B2BTOP_Pipe_Set_VD_Int_Handler(unitNo, &priv->callbackIntCtrlMax);
                im_pro_7_print_64(im_pro_7_print_get(), "", ercd, unitNo, &priv->callbackIntCtrlMax);
            }
        }
    }
}

void ct_im_pro_7_6_5(CtImpro76* self,const kuint32 idx)
{
	CtImpro76Private *priv = CT_IMPRO_7_6_GET_PRIVATE(self);
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kulong userParam;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(userParam = 0; userParam < 4; userParam++) {
                priv->callbackIntCtrlMax.userParam = userParam;
                ercd = Im_PRO_B2BTOP_Pipe_Set_HD_Int_Handler(unitNo, &priv->callbackIntCtrlMax);
                im_pro_7_print_65(im_pro_7_print_get(), "", ercd, unitNo, &priv->callbackIntCtrlMax);
            }
        }
    }
}

void ct_im_pro_7_6_6(CtImpro76* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32  chLoopcnt;
    kuint32 pwchInte = (D_IM_PRO_PWCHINTENB_PWE | D_IM_PRO_PWCHINTENB_PWEE | D_IM_PRO_PWCHINTENB_PWXE);
    kuint32 pwchIntf = (D_IM_PRO_PWCHINTFLG_PWF | D_IM_PRO_PWCHINTFLG_PWEF | D_IM_PRO_PWCHINTFLG_PWXF);
    kuint32 prchInte = (D_IM_PRO_PRCHINTENB_PRE | D_IM_PRO_PRCHINTENB_PREE | D_IM_PRO_PRCHINTENB_PRXE);
    kuint32 prchIntf = (D_IM_PRO_PRCHINTFLG_PRF | D_IM_PRO_PRCHINTFLG_PREF | D_IM_PRO_PRCHINTFLG_PRXF);

    for(chLoopcnt = 0; chLoopcnt < ImProPwch_MAX; chLoopcnt++) {
        im_pro_debug_pwch_intflg_fill(im_pro_debug_get(),0, E_IM_PRO_BLOCK_TYPE_B2B, chLoopcnt, pwchInte, pwchIntf);
    }

    for(chLoopcnt = 0; chLoopcnt < E_IM_PRO_PRCH_MAX; chLoopcnt++) {
        im_pro_debug_prch_intflg_fill(im_pro_debug_get(),0, E_IM_PRO_BLOCK_TYPE_B2B, chLoopcnt, prchInte, prchIntf);
    }
#endif  // CO_DEBUG_ON_PC
    Im_PRO_B2BTOP_Pipe1_Int_Handler();
}

void ct_im_pro_7_6_7(CtImpro76* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 vdInte = (D_IM_PRO_B2BTOP_INT_VDE0 | D_IM_PRO_B2BTOP_INT_VDE1);
    kuint32 vdIntf = (D_IM_PRO_B2BTOP_INT_VDF0 | D_IM_PRO_B2BTOP_INT_VDF1);

    im_pro_debug_b2btop_vd_intflg_fill(im_pro_debug_get(),0, vdInte, vdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_B2BTOP_Pipe1_VD_Int_Handler();
}

void ct_im_pro_7_6_8(CtImpro76* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 hdInte = (D_IM_PRO_B2BTOP_INT_HDE0 | D_IM_PRO_B2BTOP_INT_HDE1);
    kuint32 hdIntf = (D_IM_PRO_B2BTOP_INT_HDF0 | D_IM_PRO_B2BTOP_INT_HDF1);

    im_pro_debug_b2btop_hd_intflg_fill(im_pro_debug_get(),0, hdInte, hdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_B2BTOP_Pipe1_HD_Int_Handler();
}

void ct_im_pro_7_6_9(CtImpro76* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32  chLoopcnt;
    kuint32 pwchInte = (D_IM_PRO_PWCHINTENB_PWE | D_IM_PRO_PWCHINTENB_PWEE | D_IM_PRO_PWCHINTENB_PWXE);
    kuint32 pwchIntf = (D_IM_PRO_PWCHINTFLG_PWF | D_IM_PRO_PWCHINTFLG_PWEF | D_IM_PRO_PWCHINTFLG_PWXF);
    kuint32 prchInte = (D_IM_PRO_PRCHINTENB_PRE | D_IM_PRO_PRCHINTENB_PREE | D_IM_PRO_PRCHINTENB_PRXE);
    kuint32 prchIntf = (D_IM_PRO_PRCHINTFLG_PRF | D_IM_PRO_PRCHINTFLG_PREF | D_IM_PRO_PRCHINTFLG_PRXF);

    for(chLoopcnt = 0; chLoopcnt < ImProPwch_MAX; chLoopcnt++) {
        im_pro_debug_pwch_intflg_fill(im_pro_debug_get(),1, E_IM_PRO_BLOCK_TYPE_B2B, chLoopcnt, pwchInte, pwchIntf);
    }

    for(chLoopcnt = 0; chLoopcnt < E_IM_PRO_PRCH_MAX; chLoopcnt++) {
        im_pro_debug_prch_intflg_fill(im_pro_debug_get(),1, E_IM_PRO_BLOCK_TYPE_B2B, chLoopcnt, prchInte, prchIntf);
    }
#endif  // CO_DEBUG_ON_PC
    Im_PRO_B2BTOP_Pipe2_Int_Handler();
}
#endif

CtImpro76* ct_impro_7_6_new(void)
{
	CtImpro76* self = k_object_new_with_private(CT_TYPE_IMPRO_7_6, sizeof(CtImpro76Private));

	return self;
}

CtImpro76* ct_impro_7_6_get(void)
{
	static CtImpro76* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_7_6, sizeof(CtImpro76Private));
	}

	return self;
}
