/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro74
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro74.h"
#include "impro7print.h"
#include "improdebug.h"
#include "improcallback.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImpro74, ct_impro_7_4)
#define CT_IMPRO_7_4_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro74Private, CT_TYPE_IMPRO_7_4))


struct _CtImpro74Private
{
    T_IM_PRO_INT_CFG intCtrl;
    TImProCallbackCfg callbackIntCtrl;
    T_IM_PRO_INT_SROTOP_CTRL srotopIntCtrl;
    T_IM_PRO_INT_VHD_DELAY_CTRL intCtrlMax;
    T_IM_PRO_INT_VHD_DELAY_CTRL intCtrlMin;
};


/**
 * IMPL
 */
static void ct_impro_7_4_constructor(CtImpro74 *self)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
    priv->intCtrl.interruptBit = 0;
    priv->intCtrl.permissionFlg = 0;

    priv->callbackIntCtrl.inthandler = NULL;
    priv->callbackIntCtrl.userParam = 0;

    priv->srotopIntCtrl.intMode = E_IM_PRO_INT_INTMD_ORAND;
    priv->srotopIntCtrl.vdEnable[0].interruptBit = 0;
    priv->srotopIntCtrl.vdEnable[0].permissionFlg = 0;
    priv->srotopIntCtrl.hdEnable[0].interruptBit = 0;
    priv->srotopIntCtrl.hdEnable[0].permissionFlg = 0;
    priv->srotopIntCtrl.vdEnable[1].interruptBit = 0;
    priv->srotopIntCtrl.vdEnable[1].permissionFlg = 0;
    priv->srotopIntCtrl.hdEnable[1].interruptBit = 0;
    priv->srotopIntCtrl.hdEnable[1].permissionFlg = 0;

    priv->intCtrlMax.hdDelay = 12288;
    priv->intCtrlMax.vdHDelay = 12288;
    priv->intCtrlMax.vdVDelay = 16383;

    priv->intCtrlMin.hdDelay = 0;
    priv->intCtrlMin.vdHDelay = 0;
    priv->intCtrlMin.vdVDelay = 0;
}

static void ct_impro_7_4_destructor(CtImpro74 *self)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_4_0(CtImpro74* self,const kuint32 idx)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;

#ifdef CO_DEBUG_ON_PC
    const T_IM_PRO_COMMON_MONI_INFO* moniInfo;
#endif  // CO_DEBUG_ON_PC

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = 0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                        priv->intCtrl.permissionFlg = permissionFlg;

                        priv->intCtrl.interruptBit = (D_IM_PRO_MONIINTENB_MONIHDE |
                                                D_IM_PRO_MONIINTENB_MONIEPFE |
                                                D_IM_PRO_MONIINTENB_MONIEPLE |
                                                D_IM_PRO_MONIINTENB_MONIBLLMINE |
                                                D_IM_PRO_MONIINTENB_MONIBLLMAXE);
#ifdef CO_DEBUG_ON_PC
                        im_pro_comm_get_moni_reg_info(unitNo, blockType, ch, &moniInfo);
                        moniInfo->regPtr->moniintflg.word = priv->intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                        ercd = Im_PRO_MONI_Set_Interrupt(unitNo, blockType, ch, &priv->intCtrl);
                        im_pro_7_print_40(im_pro_7_print_get(), ercd, unitNo, blockType, ch, &priv->intCtrl, permissionFlg);
                    }
                }
            }
        }
    }
}

void ct_im_pro_7_4_1(CtImpro74* self,const kuint32 idx)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;
    kulong userParam;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = 0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    for(userParam = 0; userParam < 4; userParam++) {
                        priv->callbackIntCtrl.inthandler = im_pro_callback_sen_moni_int_cb;
                        priv->callbackIntCtrl.userParam = userParam;
                        ercd = Im_PRO_MONI_Set_Int_Handler(unitNo, blockType, ch, &priv->callbackIntCtrl);
                        im_pro_7_print_41(im_pro_7_print_get(), "", unitNo, blockType, ch,  ercd, &priv->callbackIntCtrl);
                    }
                }
            }
        }
    }
}

void ct_im_pro_7_4_2(CtImpro74* self,const kuint32 idx)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_LDIV_CH_NUM; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                priv->intCtrl.permissionFlg = permissionFlg;

                priv->intCtrl.interruptBit = D_IM_PRO_LDIVINTENB_LDIVEE;
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.ldiv[ch].ldivintflg.word = priv->intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_LDIV_Set_Interrupt(ch, &priv->intCtrl);
                im_pro_7_print_42(im_pro_7_print_get(), ercd, ch, &priv->intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_4_3(CtImpro74* self,const kuint32 idx)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
    kint32 ercd;
    kuchar ch;
    kulong userParam;

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_LDIV_CH_NUM; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                priv->callbackIntCtrl.inthandler = im_pro_callback_sen_ldiv_int_cb;
                priv->callbackIntCtrl.userParam = userParam;
                ercd = Im_PRO_LDIV_Set_Int_Handler(ch, &priv->callbackIntCtrl);
                im_pro_7_print_43(im_pro_7_print_get(), "", ch, ercd, &priv->callbackIntCtrl);
            }
        }
    }
}

void ct_im_pro_7_4_4(CtImpro74* self,const kuint32 idx)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;
#ifdef CO_DEBUG_ON_PC
    kuchar blockNum = 0;
    kuchar chNum = 0;
#endif  // CO_DEBUG_ON_PC

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_OBT_CNT; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                priv->intCtrl.permissionFlg = permissionFlg;

                priv->intCtrl.interruptBit = D_IM_PRO_OBDINTENB_OBDE;
#ifdef CO_DEBUG_ON_PC
                im_pro_comm_get_obt_block_ch(ch, &blockNum, &chNum);
                ioPro.sen.obt[blockNum][chNum].obtintflg.word = priv->intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_OBT_Set_Interrupt(ch, &priv->intCtrl);
                im_pro_7_print_44(im_pro_7_print_get(), ercd, ch, &priv->intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_4_5(CtImpro74* self,const kuint32 idx)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
    kint32 ercd;
    kuchar ch;
    kulong userParam;

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_OBT_CNT; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                priv->callbackIntCtrl.inthandler = im_pro_callback_sen_obt_int_cb;
                priv->callbackIntCtrl.userParam = userParam;
                ercd = Im_PRO_OBT_Set_Int_Handler(ch, &priv->callbackIntCtrl);
                im_pro_7_print_45(im_pro_7_print_get(), "", ch, ercd, &priv->callbackIntCtrl);
            }
        }
    }
}

void ct_im_pro_7_4_6(CtImpro74* self,const kuint32 idx)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;
#ifdef CO_DEBUG_ON_PC
    kuchar blockNum = 0;
    kuchar chNum = 0;
#endif  // CO_DEBUG_ON_PC

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_OBD_CNT; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                priv->intCtrl.permissionFlg = permissionFlg;

                priv->intCtrl.interruptBit = D_IM_PRO_OBDINTENB_OBDE;
#ifdef CO_DEBUG_ON_PC
                im_pro_comm_get_obd_block_ch(ch, &blockNum, &chNum);
                ioPro.sen.obd[blockNum][chNum].obdintflg.word = priv->intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_OBD_Set_Interrupt(ch, &priv->intCtrl);
                im_pro_7_print_46(im_pro_7_print_get(), ercd, ch, &priv->intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_4_7(CtImpro74* self,const kuint32 idx)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
    kint32 ercd;
    kuchar ch;
    kulong userParam;

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_OBD_CNT; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                priv->callbackIntCtrl.inthandler = im_pro_callback_sen_obd_int_cb;
                priv->callbackIntCtrl.userParam = userParam;
                ercd = Im_PRO_OBD_Set_Int_Handler(ch, &priv->callbackIntCtrl);
                im_pro_7_print_45(im_pro_7_print_get(), "", ch, ercd, &priv->callbackIntCtrl);
            }
        }
    }
}

void ct_im_pro_7_4_8(CtImpro74* self,const kuint32 idx)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
    kint32 ercd;
    kuchar permissionFlg;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar  intMode;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(intMode = ImPro_INT_INTMD_OR; intMode < E_IM_PRO_INT_INTMD_ORAND + 1; intMode++) {
                for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                    priv->srotopIntCtrl.vdEnable[0].permissionFlg = permissionFlg;
                    priv->srotopIntCtrl.hdEnable[0].permissionFlg = permissionFlg;
                    priv->srotopIntCtrl.vdEnable[1].permissionFlg = permissionFlg;
                    priv->srotopIntCtrl.hdEnable[1].permissionFlg = permissionFlg;

                    priv->srotopIntCtrl.vdEnable[0].interruptBit = D_IM_PRO_SROTOP_INT_VDE0;
                    priv->srotopIntCtrl.hdEnable[0].interruptBit = D_IM_PRO_SROTOP_INT_HDE0;
                    priv->srotopIntCtrl.vdEnable[1].interruptBit = D_IM_PRO_SROTOP_INT_VDE1;
                    priv->srotopIntCtrl.hdEnable[1].interruptBit = D_IM_PRO_SROTOP_INT_HDE1;
                    priv->srotopIntCtrl.intMode = intMode;

#ifdef CO_DEBUG_ON_PC
                    ioPro.imgPipe[unitNo].sro.srotop.vhdintflg.word = (priv->srotopIntCtrl.vdEnable[0].interruptBit | priv->srotopIntCtrl.vdEnable[1].interruptBit | priv->srotopIntCtrl.hdEnable[0].interruptBit | priv->srotopIntCtrl.hdEnable[1].interruptBit);
#endif  // CO_DEBUG_ON_PC
                    ercd = Im_PRO_SROTOP_Interrupt_Ctrl(unitNo, &priv->srotopIntCtrl);
                    im_pro_7_print_48(im_pro_7_print_get(), ercd, unitNo, &priv->srotopIntCtrl, permissionFlg);

                }
            }
        }
    }
}

void ct_im_pro_7_4_9(CtImpro74* self,const kuint32 idx)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(ch = 0; ch < 2; ch++) {
                ercd = Im_PRO_SROTOP_Set_VHD_Delay(unitNo, ch, &priv->intCtrlMax);
                im_pro_7_print_49(im_pro_7_print_get(), "max_para", unitNo, ch, ercd, &priv->intCtrlMax);

                ercd = Im_PRO_SROTOP_Set_VHD_Delay(unitNo, ch, &priv->intCtrlMin);
                im_pro_7_print_49(im_pro_7_print_get(), "min_para", unitNo, ch, ercd, &priv->intCtrlMin);
            }
        }
    }
}
#endif

CtImpro74* ct_impro_7_4_new(void)
{
	CtImpro74* self = k_object_new_with_private(CT_TYPE_IMPRO_7_4, sizeof(CtImpro74Private));

	return self;
}

CtImpro74* ct_impro_7_4_get(void)
{
	static CtImpro74* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_7_4, sizeof(CtImpro74Private));
	}

	return self;
}
