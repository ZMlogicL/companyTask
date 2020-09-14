/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro75
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro75.h"
#include "impro7print.h"
#include "improdebug.h"
#include "improcallback.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImpro75, ct_impro_7_5)
#define CT_IMPRO_7_5_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro75Private, CT_TYPE_IMPRO_7_5))


struct _CtImpro75Private
{
        TImProCallbackCfg callbackIntCtrlMax;
        T_IM_PRO_INT_CFG intCtrl;
};


/**
 *IMPL
 */
static void ct_impro_7_5_constructor(CtImpro75 *self)
{
	CtImpro75Private *priv = CT_IMPRO_7_5_GET_PRIVATE(self);

    priv->callbackIntCtrlMax.inthandler = im_pro_callback_sro_vd_int_cb;
    priv->callbackIntCtrlMax.userParam = 0;
    priv->intCtrl.interruptBit = 0;
    priv->intCtrl.permissionFlg = 0;
}

static void ct_impro_7_5_destructor(CtImpro75 *self)
{
	CtImpro75Private *priv = CT_IMPRO_7_5_GET_PRIVATE(self);
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_5_0(CtImpro75* self,const kuint32 idx)
{
}

void ct_im_pro_7_5_1(CtImpro75* self,const kuint32 idx)
{
	CtImpro75Private *priv = CT_IMPRO_7_5_GET_PRIVATE(self);
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kulong userParam;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(userParam = 0; userParam < 4; userParam++) {
                priv->callbackIntCtrlMax.userParam = userParam;
                ercd = Im_PRO_SROTOP_Pipe_Set_VD_Int_Handler(unitNo, &priv->callbackIntCtrlMax);
                im_pro_7_print_51(im_pro_7_print_get(), "", ercd, unitNo, &priv->callbackIntCtrlMax);
            }
        }
    }
}

void ct_im_pro_7_5_2(CtImpro75* self,const kuint32 idx)
{
	CtImpro75Private *priv = CT_IMPRO_7_5_GET_PRIVATE(self);
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kulong userParam;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(userParam = 0; userParam < 4; userParam++) {
                priv->callbackIntCtrlMax.userParam = userParam;
                ercd = Im_PRO_SROTOP_Pipe_Set_HD_Int_Handler(unitNo, &priv->callbackIntCtrlMax);
                im_pro_7_print_52(im_pro_7_print_get(), "", ercd, unitNo, &priv->callbackIntCtrlMax);
            }
        }
    }
}

void ct_im_pro_7_5_3(CtImpro75* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32  chLoopcnt;
    kuint32 moniInte = (D_IM_PRO_MONIINTENB_MONIHDE |
                        D_IM_PRO_MONIINTENB_MONIEPFE |
                        D_IM_PRO_MONIINTENB_MONIEPLE |
                        D_IM_PRO_MONIINTENB_MONIBLLMINE |
                        D_IM_PRO_MONIINTENB_MONIBLLMAXE);

    kuint32 moniIntf = (D_IM_PRO_MONIINTFLG_MONIHDF |
                        D_IM_PRO_MONIINTFLG_MONIEPFF |
                        D_IM_PRO_MONIINTFLG_MONIEPLF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMINF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMAXF);

    kuint32 sdcInte = D_IM_PRO_SDCINTENB_SDCE;
    kuint32 sdcIntf = D_IM_PRO_SDCINTFLG_SDCF;
    kuint32 pwchInte = (D_IM_PRO_PWCHINTENB_PWE |
                        D_IM_PRO_PWCHINTENB_PWEE |
                        D_IM_PRO_PWCHINTENB_PWXE);

    kuint32 pwchIntf = (D_IM_PRO_PWCHINTFLG_PWF |
                        D_IM_PRO_PWCHINTFLG_PWEF |
                        D_IM_PRO_PWCHINTFLG_PWXF);

    kuint32 prchInte = (D_IM_PRO_PRCHINTENB_PRE |
                        D_IM_PRO_PRCHINTENB_PREE |
                        D_IM_PRO_PRCHINTENB_PRXE);

    kuint32 prchIntf = (D_IM_PRO_PRCHINTFLG_PRF |
                        D_IM_PRO_PRCHINTFLG_PREF |
                        D_IM_PRO_PRCHINTFLG_PRXF);


    im_pro_debug_sro_moni_intflg_fill(im_pro_debug_get(),0, moniInte, moniIntf);

    im_pro_debug_sro_sdc_intflg_fill(im_pro_debug_get(),0, 0, sdcInte, sdcIntf);
    im_pro_debug_sro_sdc_intflg_fill(im_pro_debug_get(),0, 1, sdcInte, sdcIntf);

    for(chLoopcnt = 0; chLoopcnt < ImProPwch_MAX; chLoopcnt++) {
        im_pro_debug_pwch_intflg_fill(im_pro_debug_get(),0, E_IM_PRO_BLOCK_TYPE_SRO, chLoopcnt, pwchInte, pwchIntf);
    }

    for(chLoopcnt = 0; chLoopcnt < E_IM_PRO_PRCH_MAX; chLoopcnt++) {
        im_pro_debug_prch_intflg_fill(im_pro_debug_get(),0, E_IM_PRO_BLOCK_TYPE_SRO, chLoopcnt, prchInte, prchIntf);
    }
#endif  // CO_DEBUG_ON_PC
    Im_PRO_SROTOP_Pipe1_Int_Handler();
}

void ct_im_pro_7_5_4(CtImpro75* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 vdInte = (D_IM_PRO_SROTOP_INT_VDE0 | D_IM_PRO_SROTOP_INT_VDE1);
    kuint32 vdIntf = (D_IM_PRO_SROTOP_INT_VDF0 | D_IM_PRO_SROTOP_INT_VDF1);

    im_pro_debug_srotop_vd_intflg_fill(im_pro_debug_get(),0, vdInte, vdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_SROTOP_Pipe1_VD_Int_Handler();
}

void ct_im_pro_7_5_5(CtImpro75* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 hdInte = (D_IM_PRO_SROTOP_INT_HDE0 | D_IM_PRO_SROTOP_INT_HDE1);
    kuint32 hdIntf = (D_IM_PRO_SROTOP_INT_HDF0 | D_IM_PRO_SROTOP_INT_HDF1);

    im_pro_debug_srotop_hd_intflg_fill(im_pro_debug_get(),0, hdInte, hdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_SROTOP_Pipe1_HD_Int_Handler();
}

void ct_im_pro_7_5_6(CtImpro75* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32  chLoopcnt;
    kuint32 moniInte = (D_IM_PRO_MONIINTENB_MONIHDE |
                        D_IM_PRO_MONIINTENB_MONIEPFE |
                        D_IM_PRO_MONIINTENB_MONIEPLE |
                        D_IM_PRO_MONIINTENB_MONIBLLMINE |
                        D_IM_PRO_MONIINTENB_MONIBLLMAXE);

    kuint32 moniIntf = (D_IM_PRO_MONIINTFLG_MONIHDF |
                        D_IM_PRO_MONIINTFLG_MONIEPFF |
                        D_IM_PRO_MONIINTFLG_MONIEPLF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMINF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMAXF);

    kuint32 sdcInte = D_IM_PRO_SDCINTENB_SDCE;
    kuint32 sdcIntf = D_IM_PRO_SDCINTFLG_SDCF;
    kuint32 pwchInte = (D_IM_PRO_PWCHINTENB_PWE |
                        D_IM_PRO_PWCHINTENB_PWEE |
                        D_IM_PRO_PWCHINTENB_PWXE);

    kuint32 pwchIntf = (D_IM_PRO_PWCHINTFLG_PWF |
                        D_IM_PRO_PWCHINTFLG_PWEF |
                        D_IM_PRO_PWCHINTFLG_PWXF);

    kuint32 prchInte = (D_IM_PRO_PRCHINTENB_PRE |
                        D_IM_PRO_PRCHINTENB_PREE |
                        D_IM_PRO_PRCHINTENB_PRXE);

    kuint32 prchIntf = (D_IM_PRO_PRCHINTFLG_PRF |
                        D_IM_PRO_PRCHINTFLG_PREF |
                        D_IM_PRO_PRCHINTFLG_PRXF);


    im_pro_debug_sro_moni_intflg_fill(im_pro_debug_get(),1, moniInte, moniIntf);

    im_pro_debug_sro_sdc_intflg_fill(im_pro_debug_get(),1, 0, sdcInte, sdcIntf);
    im_pro_debug_sro_sdc_intflg_fill(im_pro_debug_get(),1, 1, sdcInte, sdcIntf);

    for(chLoopcnt = 0; chLoopcnt < ImProPwch_MAX; chLoopcnt++) {
        im_pro_debug_pwch_intflg_fill(im_pro_debug_get(),1, E_IM_PRO_BLOCK_TYPE_SRO, chLoopcnt, pwchInte, pwchIntf);
    }

    for(chLoopcnt = 0; chLoopcnt < E_IM_PRO_PRCH_MAX; chLoopcnt++) {
        im_pro_debug_prch_intflg_fill(im_pro_debug_get(),1, E_IM_PRO_BLOCK_TYPE_SRO, chLoopcnt, prchInte, prchIntf);
    }
#endif  // CO_DEBUG_ON_PC
    Im_PRO_SROTOP_Pipe2_Int_Handler();
}

void ct_im_pro_7_5_7(CtImpro75* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 vdInte = (D_IM_PRO_SROTOP_INT_VDE0 | D_IM_PRO_SROTOP_INT_VDE1);  
    kuint32 vdIntf = (D_IM_PRO_SROTOP_INT_VDF0 | D_IM_PRO_SROTOP_INT_VDF1);

    im_pro_debug_srotop_vd_intflg_fill(im_pro_debug_get(),1, vdInte, vdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_SROTOP_Pipe2_VD_Int_Handler();
}

void ct_im_pro_7_5_8(CtImpro75* self,const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 hdInte = (D_IM_PRO_SROTOP_INT_HDE0 | D_IM_PRO_SROTOP_INT_HDE1);
    kuint32 hdIntf = (D_IM_PRO_SROTOP_INT_HDF0 | D_IM_PRO_SROTOP_INT_HDF1);

    im_pro_debug_srotop_hd_intflg_fill(im_pro_debug_get(),1, hdInte, hdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_SROTOP_Pipe2_HD_Int_Handler();
}

void ct_im_pro_7_5_9(CtImpro75* self,const kuint32 idx)
{
	CtImpro75Private *priv = CT_IMPRO_7_5_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar ch;

    if(idx == 1) {
        for(unitNo = 0; unitNo < E_IM_PRO_BOTH_UNIT; unitNo++) {
            for(ch = 0; ch < D_IM_PRO_SRO_SDC_CH_NUM; ch++) {
                for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                    priv->intCtrl.permissionFlg = permissionFlg;

                    priv->intCtrl.interruptBit = D_IM_PRO_SDCINTENB_SDCE;
#ifdef CO_DEBUG_ON_PC
                    ioPro.imgPipe[unitNo].sro.sdc[ch].sdcintflg.word = priv->intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                    ercd = Im_PRO_SDC_Set_Interrupt(unitNo, ch, &priv->intCtrl);
                    im_pro_7_print_59(im_pro_7_print_get(), ercd, unitNo, ch, &priv->intCtrl, permissionFlg);
                }
            }
        }
    }
}
#endif

CtImpro75* ct_impro_7_5_new(void)
{
	CtImpro75* self = k_object_new_with_private(CT_TYPE_IMPRO_7_5, sizeof(CtImpro75Private));

	return self;
}

CtImpro75* ct_impro_7_5_get(void)
{
	static CtImpro75* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_7_5, sizeof(CtImpro75Private));
	}

	return self;
}
