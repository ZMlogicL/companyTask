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

};


static void ct_impro_7_6_constructor(CtImpro76 *self)
{
	CtImpro76Private *priv = CT_IMPRO_7_6_GET_PRIVATE(self);
}

static void ct_impro_7_6_destructor(CtImpro76 *self)
{
	CtImpro76Private *priv = CT_IMPRO_7_6_GET_PRIVATE(self);
}

#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_60(const kuint32 idx)
{
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar ch;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(unitNo = 0; unitNo < E_IM_PRO_BOTH_UNIT; unitNo++) {
            for(ch = 0; ch < D_IM_PRO_SRO_SDC_CH_NUM; ch++) {
                for(userParam = 0; userParam < 4; userParam++) {
                    intCtrl.inthandler = im_pro_callback_sro_sdc_int_cb;
                    intCtrl.userParam = userParam;
                    ercd = Im_PRO_SDC_Set_Int_Handler(unitNo, ch, &intCtrl);
                    im_pro_7_60_Print(NULL,"", unitNo, ch, ercd, &intCtrl);
                }
            }
        }
    }
}

void ct_im_pro_7_61(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar  intMode;
    T_IM_PRO_INT_B2BTOP_CTRL intCtrl = {
        .intMode = E_IM_PRO_INT_INTMD_ORAND,
        .vdEnable[0].interruptBit = 0,
        .vdEnable[0].permissionFlg = 0,
        .hdEnable[0].interruptBit = 0,
        .hdEnable[0].permissionFlg = 0,
        .vdEnable[1].interruptBit = 0,
        .vdEnable[1].permissionFlg = 0,
        .hdEnable[1].interruptBit = 0,
        .hdEnable[1].permissionFlg = 0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(intMode = E_IM_PRO_INT_INTMD_OR; intMode < E_IM_PRO_INT_INTMD_ORAND + 1; intMode++) {
                for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                    intCtrl.vdEnable[0].permissionFlg = permissionFlg;
                    intCtrl.hdEnable[0].permissionFlg = permissionFlg;
                    intCtrl.vdEnable[1].permissionFlg = permissionFlg;
                    intCtrl.hdEnable[1].permissionFlg = permissionFlg;

                    intCtrl.vdEnable[0].interruptBit = D_IM_PRO_B2BTOP_INT_VDE0;
                    intCtrl.hdEnable[0].interruptBit = D_IM_PRO_B2BTOP_INT_HDE0;
                    intCtrl.vdEnable[1].interruptBit = D_IM_PRO_B2BTOP_INT_VDE1;
                    intCtrl.hdEnable[1].interruptBit = D_IM_PRO_B2BTOP_INT_HDE1;
                    intCtrl.intMode = intMode;

#ifdef CO_DEBUG_ON_PC
                    ioPro.imgPipe[unitNo].b2b.b2btop.vhdintflg.word = (intCtrl.vdEnable[0].interruptBit | intCtrl.vdEnable[1].interruptBit | intCtrl.hdEnable[0].interruptBit | intCtrl.hdEnable[1].interruptBit);
#endif  // CO_DEBUG_ON_PC
                    ercd = Im_PRO_B2BTOP_Interrupt_Ctrl(unitNo, &intCtrl);
                    im_pro_7_61_Print(NULL,ercd, unitNo, &intCtrl, permissionFlg);
                }
            }
        }
    }
}

void ct_im_pro_7_62(const kuint32 idx)
{
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar ch;
    T_IM_PRO_INT_VHD_DELAY_CTRL intCtrlMax = {
        .hdDelay = 12288,
        .vdHDelay = 12288,
        .vdVDelay = 16383,
    };

    T_IM_PRO_INT_VHD_DELAY_CTRL intCtrlMin = {
        .hdDelay = 0,
        .vdHDelay = 0,
        .vdVDelay = 0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(ch = 0; ch < 2; ch++) {
                ercd = Im_PRO_B2BTOP_Set_VHD_Delay(unitNo, ch, &intCtrlMax);
                im_pro_7_62_Print(NULL,"max_para", unitNo, ch, ercd, &intCtrlMax);

                ercd = Im_PRO_B2BTOP_Set_VHD_Delay(unitNo, ch, &intCtrlMin);
                im_pro_7_62_Print(NULL,"min_para", unitNo, ch, ercd, &intCtrlMin);
            }
        }
    }
}

void ct_im_pro_7_63(const kuint32 idx)
{
}

void ct_im_pro_7_64(const kuint32 idx)
{
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kulong userParam;
    TImProCallbackCfg intCtrlMax = {
        .inthandler = im_pro_callback_b2b_vd_int_cb,
        .userParam = 0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(userParam = 0; userParam < 4; userParam++) {
                intCtrlMax.userParam = userParam;
                ercd = Im_PRO_B2BTOP_Pipe_Set_VD_Int_Handler(unitNo, &intCtrlMax);
                im_pro_7_64_Print(NULL,"", ercd, unitNo, &intCtrlMax);
            }
        }
    }
}

void ct_im_pro_7_65(const kuint32 idx)
{
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kulong userParam;
    TImProCallbackCfg intCtrlMax = {
        .inthandler = im_pro_callback_b2b_hd_int_cb,
        .userParam = 0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(userParam = 0; userParam < 4; userParam++) {
                intCtrlMax.userParam = userParam;
                ercd = Im_PRO_B2BTOP_Pipe_Set_HD_Int_Handler(unitNo, &intCtrlMax);
                im_pro_7_65_Print(NULL,"", ercd, unitNo, &intCtrlMax);
            }
        }
    }
}

void ct_im_pro_7_66(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32  chLoopcnt;
    kuint32 pwchInte = (D_IM_PRO_PWCHINTENB_PWE | D_IM_PRO_PWCHINTENB_PWEE | D_IM_PRO_PWCHINTENB_PWXE);
    kuint32 pwchIntf = (D_IM_PRO_PWCHINTFLG_PWF | D_IM_PRO_PWCHINTFLG_PWEF | D_IM_PRO_PWCHINTFLG_PWXF);
    kuint32 prchInte = (D_IM_PRO_PRCHINTENB_PRE | D_IM_PRO_PRCHINTENB_PREE | D_IM_PRO_PRCHINTENB_PRXE);
    kuint32 prchIntf = (D_IM_PRO_PRCHINTFLG_PRF | D_IM_PRO_PRCHINTFLG_PREF | D_IM_PRO_PRCHINTFLG_PRXF);

    for(chLoopcnt = 0; chLoopcnt < E_IM_PRO_PWCH_MAX; chLoopcnt++) {
        im_pro_debug_pwch_intflg_fill(im_pro_debug_get(),0, E_IM_PRO_BLOCK_TYPE_B2B, chLoopcnt, pwchInte, pwchIntf);
    }

    for(chLoopcnt = 0; chLoopcnt < E_IM_PRO_PRCH_MAX; chLoopcnt++) {
        im_pro_debug_prch_intflg_fill(im_pro_debug_get(),0, E_IM_PRO_BLOCK_TYPE_B2B, chLoopcnt, prchInte, prchIntf);
    }
#endif  // CO_DEBUG_ON_PC
    Im_PRO_B2BTOP_Pipe1_Int_Handler();
}

void ct_im_pro_7_67(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 vdInte = (D_IM_PRO_B2BTOP_INT_VDE0 | D_IM_PRO_B2BTOP_INT_VDE1);
    kuint32 vdIntf = (D_IM_PRO_B2BTOP_INT_VDF0 | D_IM_PRO_B2BTOP_INT_VDF1);

    im_pro_debug_b2btop_vd_intflg_fill(im_pro_debug_get(),0, vdInte, vdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_B2BTOP_Pipe1_VD_Int_Handler();
}

void ct_im_pro_7_68(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 hdInte = (D_IM_PRO_B2BTOP_INT_HDE0 | D_IM_PRO_B2BTOP_INT_HDE1);
    kuint32 hdIntf = (D_IM_PRO_B2BTOP_INT_HDF0 | D_IM_PRO_B2BTOP_INT_HDF1);

    im_pro_debug_b2btop_hd_intflg_fill(im_pro_debug_get(),0, hdInte, hdIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_B2BTOP_Pipe1_HD_Int_Handler();
}

void ct_im_pro_7_69(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32  chLoopcnt;
    kuint32 pwchInte = (D_IM_PRO_PWCHINTENB_PWE | D_IM_PRO_PWCHINTENB_PWEE | D_IM_PRO_PWCHINTENB_PWXE);
    kuint32 pwchIntf = (D_IM_PRO_PWCHINTFLG_PWF | D_IM_PRO_PWCHINTFLG_PWEF | D_IM_PRO_PWCHINTFLG_PWXF);
    kuint32 prchInte = (D_IM_PRO_PRCHINTENB_PRE | D_IM_PRO_PRCHINTENB_PREE | D_IM_PRO_PRCHINTENB_PRXE);
    kuint32 prchIntf = (D_IM_PRO_PRCHINTFLG_PRF | D_IM_PRO_PRCHINTFLG_PREF | D_IM_PRO_PRCHINTFLG_PRXF);

    for(chLoopcnt = 0; chLoopcnt < E_IM_PRO_PWCH_MAX; chLoopcnt++) {
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
