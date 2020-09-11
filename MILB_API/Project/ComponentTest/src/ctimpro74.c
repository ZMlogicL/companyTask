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

};


/**
 * IMPL
 */
static void ct_impro_7_4_constructor(CtImpro74 *self)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
}

static void ct_impro_7_4_destructor(CtImpro74 *self)
{
	CtImpro74Private *priv = CT_IMPRO_7_4_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_40(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;
    T_IM_PRO_INT_CFG intCtrl = {
        .interruptBit = 0,
        .permissionFlg = 0,
    };
#ifdef CO_DEBUG_ON_PC
    const T_IM_PRO_COMMON_MONI_INFO* moniInfo;
#endif  // CO_DEBUG_ON_PC

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = 0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                        intCtrl.permissionFlg = permissionFlg;

                        intCtrl.interruptBit = (D_IM_PRO_MONIINTENB_MONIHDE |
                                                D_IM_PRO_MONIINTENB_MONIEPFE |
                                                D_IM_PRO_MONIINTENB_MONIEPLE |
                                                D_IM_PRO_MONIINTENB_MONIBLLMINE |
                                                D_IM_PRO_MONIINTENB_MONIBLLMAXE);
#ifdef CO_DEBUG_ON_PC
                        im_pro_comm_get_moni_reg_info(unitNo, blockType, ch, &moniInfo);
                        moniInfo->regPtr->moniintflg.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                        ercd = Im_PRO_MONI_Set_Interrupt(unitNo, blockType, ch, &intCtrl);
                        im_pro_7_40_Print(NULL,ercd, unitNo, blockType, ch, &intCtrl, permissionFlg);
                    }
                }
            }
        }
    }
}

void ct_im_pro_7_41(const kuint32 idx)
{
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = 0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    for(userParam = 0; userParam < 4; userParam++) {
                        intCtrl.inthandler = im_pro_callback_sen_moni_int_cb;
                        intCtrl.userParam = userParam;
                        ercd = Im_PRO_MONI_Set_Int_Handler(unitNo, blockType, ch, &intCtrl);
                        im_pro_7_41_Print(NULL,"", unitNo, blockType, ch,  ercd, &intCtrl);
                    }
                }
            }
        }
    }
}

void ct_im_pro_7_42(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;
    T_IM_PRO_INT_CFG intCtrl = {
        .interruptBit = 0,
        .permissionFlg = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_LDIV_CH_NUM; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                intCtrl.permissionFlg = permissionFlg;

                intCtrl.interruptBit = D_IM_PRO_LDIVINTENB_LDIVEE;
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.ldiv[ch].ldivintflg.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_LDIV_Set_Interrupt(ch, &intCtrl);
                im_pro_7_42_Print(NULL,ercd, ch, &intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_43(const kuint32 idx)
{
    kint32 ercd;
    kuchar ch;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_LDIV_CH_NUM; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                intCtrl.inthandler = im_pro_callback_sen_ldiv_int_cb;
                intCtrl.userParam = userParam;
                ercd = Im_PRO_LDIV_Set_Int_Handler(ch, &intCtrl);
                im_pro_7_43_Print(NULL,"", ch, ercd, &intCtrl);
            }
        }
    }
}

void ct_im_pro_7_44(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;
#ifdef CO_DEBUG_ON_PC
    kuchar blockNum = 0;
    kuchar chNum = 0;
#endif  // CO_DEBUG_ON_PC
    T_IM_PRO_INT_CFG intCtrl = {
        .interruptBit = 0,
        .permissionFlg = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_OBT_CNT; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                intCtrl.permissionFlg = permissionFlg;

                intCtrl.interruptBit = D_IM_PRO_OBDINTENB_OBDE;
#ifdef CO_DEBUG_ON_PC
                im_pro_comm_get_obt_block_ch(ch, &blockNum, &chNum);
                ioPro.sen.obt[blockNum][chNum].obtintflg.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_OBT_Set_Interrupt(ch, &intCtrl);
                im_pro_7_44_Print(NULL,ercd, ch, &intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_45(const kuint32 idx)
{
    kint32 ercd;
    kuchar ch;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_OBT_CNT; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                intCtrl.inthandler = im_pro_callback_sen_obt_int_cb;
                intCtrl.userParam = userParam;
                ercd = Im_PRO_OBT_Set_Int_Handler(ch, &intCtrl);
                im_pro_7_45_Print(NULL,"", ch, ercd, &intCtrl);
            }
        }
    }
}

void ct_im_pro_7_46(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;
#ifdef CO_DEBUG_ON_PC
    kuchar blockNum = 0;
    kuchar chNum = 0;
#endif  // CO_DEBUG_ON_PC
    T_IM_PRO_INT_CFG intCtrl = {
        .interruptBit = 0,
        .permissionFlg = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_OBD_CNT; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                intCtrl.permissionFlg = permissionFlg;

                intCtrl.interruptBit = D_IM_PRO_OBDINTENB_OBDE;
#ifdef CO_DEBUG_ON_PC
                im_pro_comm_get_obd_block_ch(ch, &blockNum, &chNum);
                ioPro.sen.obd[blockNum][chNum].obdintflg.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_OBD_Set_Interrupt(ch, &intCtrl);
                im_pro_7_46_Print(NULL,ercd, ch, &intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_47(const kuint32 idx)
{
    kint32 ercd;
    kuchar ch;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_OBD_CNT; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                intCtrl.inthandler = im_pro_callback_sen_obd_int_cb;
                intCtrl.userParam = userParam;
                ercd = Im_PRO_OBD_Set_Int_Handler(ch, &intCtrl);
                im_pro_7_45_Print(NULL,"", ch, ercd, &intCtrl);
            }
        }
    }
}

void ct_im_pro_7_48(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar  intMode;
    T_IM_PRO_INT_SROTOP_CTRL intCtrl = {
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

                    intCtrl.vdEnable[0].interruptBit = D_IM_PRO_SROTOP_INT_VDE0;
                    intCtrl.hdEnable[0].interruptBit = D_IM_PRO_SROTOP_INT_HDE0;
                    intCtrl.vdEnable[1].interruptBit = D_IM_PRO_SROTOP_INT_VDE1;
                    intCtrl.hdEnable[1].interruptBit = D_IM_PRO_SROTOP_INT_HDE1;
                    intCtrl.intMode = intMode;

#ifdef CO_DEBUG_ON_PC
                    ioPro.imgPipe[unitNo].sro.srotop.vhdintflg.word = (intCtrl.vdEnable[0].interruptBit | intCtrl.vdEnable[1].interruptBit | intCtrl.hdEnable[0].interruptBit | intCtrl.hdEnable[1].interruptBit);
#endif  // CO_DEBUG_ON_PC
                    ercd = Im_PRO_SROTOP_Interrupt_Ctrl(unitNo, &intCtrl);
                    im_pro_7_48_Print(NULL,ercd, unitNo, &intCtrl, permissionFlg);

                }
            }
        }
    }
}

void ct_im_pro_7_49(const kuint32 idx)
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
                ercd = Im_PRO_SROTOP_Set_VHD_Delay(unitNo, ch, &intCtrlMax);
                im_pro_7_49_Print(NULL,"max_para", unitNo, ch, ercd, &intCtrlMax);

                ercd = Im_PRO_SROTOP_Set_VHD_Delay(unitNo, ch, &intCtrlMin);
                im_pro_7_49_Print(NULL,"min_para", unitNo, ch, ercd, &intCtrlMin);
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
