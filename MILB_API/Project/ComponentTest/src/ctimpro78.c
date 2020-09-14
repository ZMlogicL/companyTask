/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro78
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro78.h"
#include "impro7print.h"
#include "improdebug.h"
#include "improcallback.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImpro78, ct_impro_7_8)
#define CT_IMPRO_7_8_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro78Private, CT_TYPE_IMPRO_7_8))


struct _CtImpro78Private
{
    T_IM_PRO_INT_PASTOP_CTRL pastopIntCtrl;
    T_IM_PRO_INT_VHD_DELAY_CTRL vhdDelayIntCtrlMax;
    T_IM_PRO_INT_VHD_DELAY_CTRL vhdDelayIntCtrlMin;
    T_IM_PRO_INT_CFG intCtrl;
    TImProCallbackCfg callBackIntCtrl;
};


/**
 *IMPL
 */
static void ct_impro_7_8_constructor(CtImpro78 *self)
{
	CtImpro78Private *priv = CT_IMPRO_7_8_GET_PRIVATE(self);

    priv->pastopIntCtrl.intMode = E_IM_PRO_INT_INTMD_ORAND;
    priv->pastopIntCtrl.vdEnable[0].interruptBit = 0;
    priv->pastopIntCtrl.vdEnable[0].permissionFlg = 0;
    priv->pastopIntCtrl.hdEnable[0].interruptBit = 0;
    priv->pastopIntCtrl.hdEnable[0].permissionFlg = 0;
    priv->pastopIntCtrl.vdEnable[1].interruptBit = 0;
    priv->pastopIntCtrl.vdEnable[1].permissionFlg = 0;
    priv->pastopIntCtrl.hdEnable[1].interruptBit = 0;
    priv->pastopIntCtrl.hdEnable[1].permissionFlg = 0;
    priv->vhdDelayIntCtrlMax.hdDelay = 12288;
    priv->vhdDelayIntCtrlMax.vdHDelay = 12288;
    priv->vhdDelayIntCtrlMax.vdVDelay = 16383;
    priv->vhdDelayIntCtrlMin.hdDelay = 0;
    priv->vhdDelayIntCtrlMin.vdHDelay = 0;
    priv->vhdDelayIntCtrlMin.vdVDelay = 0;
    priv->intCtrl.interruptBit = 0;
    priv->intCtrl.permissionFlg = 0;
    priv->callBackIntCtrl.inthandler = NULL;
    priv->callBackIntCtrl.userParam = 0;
}

static void ct_impro_7_8_destructor(CtImpro78 *self)
{
	CtImpro78Private *priv = CT_IMPRO_7_8_GET_PRIVATE(self);
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_8_0(CtImpro78* self,const kuint32 idx)
{
	CtImpro78Private *priv = CT_IMPRO_7_8_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    kuchar  intMode;

    if(idx == 1) {
        for(intMode = ImPro_INT_INTMD_OR; intMode < E_IM_PRO_INT_INTMD_ORAND + 1; intMode++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                priv->pastopIntCtrl.vdEnable[0].permissionFlg = permissionFlg;
                priv->pastopIntCtrl.hdEnable[0].permissionFlg = permissionFlg;
                priv->pastopIntCtrl.vdEnable[1].permissionFlg = permissionFlg;
                priv->pastopIntCtrl.hdEnable[1].permissionFlg = permissionFlg;

                priv->pastopIntCtrl.vdEnable[0].interruptBit = D_IM_PRO_PASTOP_INT_VDE0;
                priv->pastopIntCtrl.hdEnable[0].interruptBit = D_IM_PRO_PASTOP_INT_HDE0;
                priv->pastopIntCtrl.vdEnable[1].interruptBit = D_IM_PRO_PASTOP_INT_VDE1;
                priv->pastopIntCtrl.hdEnable[1].interruptBit = D_IM_PRO_PASTOP_INT_HDE1;
                priv->pastopIntCtrl.intMode = intMode;
                ercd = Im_PRO_PASTOP_Interrupt_Ctrl(&priv->pastopIntCtrl);
                im_pro_7_print_80(im_pro_7_print_get(), ercd, &priv->pastopIntCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_8_1(CtImpro78* self,const kuint32 idx)
{
	CtImpro78Private *priv = CT_IMPRO_7_8_GET_PRIVATE(self);
    kint32 ercd;
    kuchar ch;

    if(idx == 1) {
        for(ch = 0; ch < 2; ch++) {
            ercd = Im_PRO_PASTOP_Set_VHD_Delay(ch, &priv->vhdDelayIntCtrlMax);
            im_pro_7_print_81(im_pro_7_print_get(), "max_para", ch, ercd, &priv->vhdDelayIntCtrlMax);

            ercd = Im_PRO_PASTOP_Set_VHD_Delay(ch, &priv->vhdDelayIntCtrlMin);
            im_pro_7_print_81(im_pro_7_print_get(), "min_para", ch, ercd, &priv->vhdDelayIntCtrlMin);
        }
    }
}

void ct_im_pro_7_8_2(CtImpro78* self,const kuint32 idx)
{
}

void ct_im_pro_7_8_3(CtImpro78* self,const kuint32 idx)
{
    kint32 ercd;
    kulong userParam;
    TImProCallbackCfg intCtrlMax = {
        .inthandler = im_pro_callback_pas_vd_int_cb,
        .userParam = 0,
    };

    if(idx == 1) {
        for(userParam = 0; userParam < 4; userParam++) {
            intCtrlMax.userParam = userParam;
            ercd = Im_PRO_PASTOP_Set_VD_Int_Handler(&intCtrlMax);
            im_pro_7_print_83(im_pro_7_print_get(), "", ercd, &intCtrlMax);
        }
    }
}

void ct_im_pro_7_8_4(CtImpro78* self,const kuint32 idx)
{
    kint32 ercd;
    kulong userParam;
    TImProCallbackCfg intCtrlMax = {
        .inthandler = im_pro_callback_pas_hd_int_cb,
        .userParam = 0,
    };

    if(idx == 1) {
        for(userParam = 0; userParam < 4; userParam++) {
            intCtrlMax.userParam = userParam;
            ercd = Im_PRO_PASTOP_Set_HD_Int_Handler(&intCtrlMax);
            im_pro_7_print_84(im_pro_7_print_get(), "", ercd, &intCtrlMax);
        }
    }
}

void ct_im_pro_7_8_5(CtImpro78* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32  chLoopcnt;
    kuint32 pwchInte = (D_IM_PRO_PWCHINTENB_PWE | D_IM_PRO_PWCHINTENB_PWEE | D_IM_PRO_PWCHINTENB_PWXE);
    kuint32 pwchIntf = (D_IM_PRO_PWCHINTFLG_PWF | D_IM_PRO_PWCHINTFLG_PWEF | D_IM_PRO_PWCHINTFLG_PWXF);
    kuint32 prchInte = (D_IM_PRO_PRCHINTENB_PRE | D_IM_PRO_PRCHINTENB_PREE | D_IM_PRO_PRCHINTENB_PRXE);
    kuint32 prchIntf = (D_IM_PRO_PRCHINTFLG_PRF | D_IM_PRO_PRCHINTFLG_PREF | D_IM_PRO_PRCHINTFLG_PRXF);

    for(chLoopcnt = 0; chLoopcnt < ImProPwch_MAX; chLoopcnt++) {
        im_pro_debug_pwch_intflg_fill(im_pro_debug_get(),0, E_IM_PRO_BLOCK_TYPE_PAS, chLoopcnt, pwchInte, pwchIntf);
    }

    for(chLoopcnt = 0; chLoopcnt < E_IM_PRO_PRCH_MAX; chLoopcnt++) {
        im_pro_debug_prch_intflg_fill(im_pro_debug_get(),0, E_IM_PRO_BLOCK_TYPE_PAS, chLoopcnt, prchInte, prchIntf);
    }
#endif  // CO_DEBUG_ON_PC
    Im_PRO_PASTOP_Int_Handler();
}

void ct_im_pro_7_8_6(CtImpro78* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 vdInte = (D_IM_PRO_PASTOP_INT_VDE0 | D_IM_PRO_PASTOP_INT_VDE1);
    kuint32 vdIntf = (D_IM_PRO_PASTOP_INT_VDF0 | D_IM_PRO_PASTOP_INT_VDF1);

    im_pro_debug_pastop_vd_intflg_fill(im_pro_debug_get(),0, vdInte, vdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_PASTOP_VD_Int_Handler();
}

void ct_im_pro_7_8_7(CtImpro78* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 hdInte = (D_IM_PRO_PASTOP_INT_HDE0 | D_IM_PRO_PASTOP_INT_HDE1);
    kuint32 hdIntf = (D_IM_PRO_PASTOP_INT_HDF0 | D_IM_PRO_PASTOP_INT_HDF1);

    im_pro_debug_pastop_hd_intflg_fill(im_pro_debug_get(),1, hdInte, hdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_PASTOP_HD_Int_Handler();
}

void ct_im_pro_7_8_8(CtImpro78* self,const kuint32 idx)
{
	CtImpro78Private *priv = CT_IMPRO_7_8_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;

#ifdef CO_DEBUG_ON_PC
    const T_IM_PRO_COMMON_PWCH_INFO* pwch_reg_info = 0;
#endif  // CO_DEBUG_ON_PC

    if(idx == 1) {
        for(unitNo = 0; unitNo < E_IM_PRO_BOTH_UNIT; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = 0; ch < ImProPwch_MAX; ch++) {
                    for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                        priv->intCtrl.permissionFlg = permissionFlg;

                        priv->intCtrl.interruptBit = (D_IM_PRO_PWCHINTENB_PWE |
                                                D_IM_PRO_PWCHINTENB_PWEE |
                                                D_IM_PRO_PWCHINTENB_PWXE |
                                                D_IM_PRO_PWCHINTFLG_PWF |
                                                D_IM_PRO_PWCHINTFLG_PWEF |
                                                D_IM_PRO_PWCHINTFLG_PWXF);
#ifdef CO_DEBUG_ON_PC
                        im_pro_comm_get_pwch_reg_info(unitNo, blockType, ch, &pwch_reg_info);
                        pwch_reg_info->regPtr->pwchintflg.word = priv->intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                        ercd = Im_PRO_PWch_Set_Interrupt(unitNo, blockType, ch, &priv->intCtrl);
                        im_pro_7_print_88(im_pro_7_print_get(), ercd, unitNo, blockType, ch, &priv->intCtrl, permissionFlg);
                    }
                }
            }
        }
    }
}

void ct_im_pro_7_8_9(CtImpro78* self,const kuint32 idx)
{
	CtImpro78Private *priv = CT_IMPRO_7_8_GET_PRIVATE(self);
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;
    kulong userParam;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = 0; ch < ImProPwch_MAX; ch++) {
                    for(userParam = 0; userParam < 4; userParam++) {
                        priv->callBackIntCtrl.inthandler = im_pro_callback_sen_pwch_int_cb;
                        priv->callBackIntCtrl.userParam = userParam;
                        ercd = Im_PRO_PWch_Set_Int_Handler(unitNo, blockType, ch, &priv->callBackIntCtrl);
                        im_pro_7_print_89(im_pro_7_print_get(), "", unitNo, blockType, ch,  ercd, &priv->callBackIntCtrl);
                    }
                }
            }
        }
    }
}
#endif

CtImpro78* ct_impro_7_8_new(void)
{
	CtImpro78* self = k_object_new_with_private(CT_TYPE_IMPRO_7_8, sizeof(CtImpro78Private));

	return self;
}

CtImpro78* ct_impro_7_8_get(void)
{
	static CtImpro78* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_7_8, sizeof(CtImpro78Private));
	}

	return self;
}
