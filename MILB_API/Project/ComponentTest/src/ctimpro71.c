/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro71
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro71.h"
#include "impro7print.h"
#include "improdebug.h"
#include "improcallback.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImpro71, ct_impro_7_1)
#define CT_IMPRO_7_1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro71Private, CT_TYPE_IMPRO_7_1))


struct _CtImpro71Private
{

};


/**
 *IPML
 */
static void ct_impro_7_1_constructor(CtImpro71 *self)
{
	CtImpro71Private *priv = CT_IMPRO_7_1_GET_PRIVATE(self);
}

static void ct_impro_7_1_destructor(CtImpro71 *self)
{
	CtImpro71Private *priv = CT_IMPRO_7_1_GET_PRIVATE(self);
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_10(const kuint32 idx)
{
}

void ct_im_pro_7_11(const kuint32 idx)
{
}

void ct_im_pro_7_12(const kuint32 idx)
{
}

void ct_im_pro_7_13(const kuint32 idx)
{
}

void ct_im_pro_7_14(const kuint32 idx)
{
}

void ct_im_pro_7_15(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    kuchar  intMode;
    TImProIntSentopCtrl intCtrl = {
        .intMode = E_IM_PRO_INT_INTMD_ORAND,
        .vdEnable.interruptBit = 0,
        .vdEnable.permissionFlg = 0,
        .hdEnable.interruptBit = 0,
        .hdEnable.permissionFlg = 0,
    };

    if(idx == 1) {
        for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
            for(intMode = E_IM_PRO_INT_INTMD_OR; intMode < E_IM_PRO_INT_INTMD_ORAND + 1; intMode++) {
                intCtrl.vdEnable.permissionFlg = permissionFlg;
                intCtrl.hdEnable.permissionFlg = permissionFlg;

                intCtrl.vdEnable.interruptBit = (D_IM_PRO_INT_VDE00 |
                                                D_IM_PRO_INT_VDE01 |
                                                D_IM_PRO_INT_VDE10 |
                                                D_IM_PRO_INT_VDE11 |
                                                D_IM_PRO_INT_VDE20 |
                                                D_IM_PRO_INT_VDE21 |
                                                D_IM_PRO_INT_VDE30 |
                                                D_IM_PRO_INT_VDE31);

                intCtrl.hdEnable.interruptBit = (D_IM_PRO_INT_HDE00 |
                                                D_IM_PRO_INT_HDE01 |
                                                D_IM_PRO_INT_HDE10 |
                                                D_IM_PRO_INT_HDE11 |
                                                D_IM_PRO_INT_HDE20 |
                                                D_IM_PRO_INT_HDE21 |
                                                D_IM_PRO_INT_HDE30 |
                                                D_IM_PRO_INT_HDE31);

                intCtrl.intMode = intMode;
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.sentop.vhdintflg.vhdintflg1.word = 0xFFFFFFFF;
                ioPro.sen.sentop.vhdintflg.vhdintflg2.word = 0xFFFFFFFF;
#endif  // CO_DEBUG_ON_PC
                ercd = interrupt_clear1_sentop_interrupt_ctrl(&intCtrl);
                im_pro_7_15_Print(NULL,ercd, &intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_16(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    kuchar vhdeg;
    T_IM_PRO_INT_SG_CTRL intCtrl = {
        .sgSync.vdeg[0] = 0,
        .sgSync.vdeg[1] = 0,
        .sgSync.vdeg[2] = 0,
        .sgSync.vdeg[3] = 0,
        .sgSync.hdeg[0] = 0,
        .sgSync.hdeg[1] = 0,
        .sgSync.hdeg[2] = 0,
        .sgSync.hdeg[3] = 0,
        .sgVdEnable.interruptBit = 0,
        .sgVdEnable.permissionFlg = 0,
        .sgHdEnable.interruptBit = 0,
        .sgHdEnable.permissionFlg = 0,
    };

    if(idx == 1) {
        for(vhdeg = 0; vhdeg < 2; vhdeg++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                intCtrl.sgVdEnable.permissionFlg = permissionFlg;
                intCtrl.sgHdEnable.permissionFlg = permissionFlg;

                intCtrl.sgVdEnable.interruptBit = (D_IM_PRO_INT_SGVDE0 |
                                                    D_IM_PRO_INT_SGVDE1 |
                                                    D_IM_PRO_INT_SGVDE2 |
                                                    D_IM_PRO_INT_SGVDE3);

                intCtrl.sgHdEnable.interruptBit = (D_IM_PRO_INT_SGHDE0 |
                                                    D_IM_PRO_INT_SGHDE1 |
                                                    D_IM_PRO_INT_SGHDE2 |
                                                    D_IM_PRO_INT_SGHDE3);
                intCtrl.sgSync.vdeg[0] = vhdeg;
                intCtrl.sgSync.vdeg[1] = vhdeg;
                intCtrl.sgSync.vdeg[2] = vhdeg;
                intCtrl.sgSync.vdeg[3] = vhdeg;
                intCtrl.sgSync.hdeg[0] = vhdeg;
                intCtrl.sgSync.hdeg[1] = vhdeg;
                intCtrl.sgSync.hdeg[2] = vhdeg;
                intCtrl.sgSync.hdeg[3] = vhdeg;

#ifdef CO_DEBUG_ON_PC
                ioPro.sen.sentop.sgvhdintflg.word = 0xFFFFFFFF;
#endif  // CO_DEBUG_ON_PC
                ercd = Im_PRO_SENTOP_SG_Interrupt_Ctrl(&intCtrl);
                im_pro_7_16_Print(NULL,ercd, &intCtrl, permissionFlg, vhdeg);

            }
        }
    }
}

void ct_im_pro_7_17(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    T_IM_PRO_INT_GYRO_CTRL intCtrl = {
        .gyroSofEnable.interruptBit = 0,
        .gyroSofEnable.permissionFlg = 0,
        .gyroEofEnable.interruptBit = 0,
        .gyroEofEnable.permissionFlg = 0,
    };

    if(idx == 1) {
        for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
            intCtrl.gyroSofEnable.permissionFlg = permissionFlg;
            intCtrl.gyroEofEnable.permissionFlg = permissionFlg;

            intCtrl.gyroSofEnable.interruptBit = (D_IM_PRO_INT_GYRO_SOFE0 |
                                                D_IM_PRO_INT_GYRO_SOFE1 |
                                                D_IM_PRO_INT_GYRO_SOFE2 |
                                                D_IM_PRO_INT_GYRO_SOFE3);

            intCtrl.gyroEofEnable.interruptBit = (D_IM_PRO_INT_GYRO_EOFE0 |
                                                D_IM_PRO_INT_GYRO_EOFE1 |
                                                D_IM_PRO_INT_GYRO_EOFE2 |
                                                D_IM_PRO_INT_GYRO_EOFE3);

#ifdef CO_DEBUG_ON_PC
            ioPro.sen.sentop.gintflg.word = 0xFFFFFFFF;
#endif  // CO_DEBUG_ON_PC
            ercd = Im_PRO_SENTOP_Gyro_Interrupt_Ctrl(&intCtrl);
            im_pro_7_17_Print(NULL,ercd, &intCtrl, permissionFlg);
        }
    }
}

void ct_im_pro_7_18(const kuint32 idx)
{
    kint32 ercd;
    kuchar blockNum;
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
        for(blockNum = 0; blockNum < 4; blockNum++) {
            for(ch = 0; ch < 2; ch++) {
                ercd = Im_PRO_SENTOP_Set_VHD_Delay(blockNum, ch, &intCtrlMax);
                im_pro_7_18_Print(NULL,"max_para", blockNum, ch, ercd, &intCtrlMax);

                ercd = Im_PRO_SENTOP_Set_VHD_Delay(blockNum, ch, &intCtrlMin);
                im_pro_7_18_Print(NULL,"min_para", blockNum, ch, ercd, &intCtrlMin);
            }
        }
    }
}

void ct_im_pro_7_19(const kuint32 idx)
{
    kint32 ercd;
    kuchar blockNum;
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
        for(blockNum = 0; blockNum < 4; blockNum++) {
            ercd = Im_PRO_SENTOP_Set_Gyro_Int_Delay(blockNum, &intCtrlMax);
            im_pro_7_19_Print(NULL,"max_para", blockNum, ercd, &intCtrlMax);

            ercd = Im_PRO_SENTOP_Set_Gyro_Int_Delay(blockNum, &intCtrlMin);
            im_pro_7_19_Print(NULL,"min_para", blockNum, ercd, &intCtrlMin);
        }
    }
}
#endif

CtImpro71* ct_impro_7_1_new(void)
{
	CtImpro71* self = k_object_new_with_private(CT_TYPE_IMPRO_7_1, sizeof(CtImpro71Private));

	return self;
}

CtImpro71* ct_impro_7_1_get(void)
{
	static CtImpro71* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_7_1, sizeof(CtImpro71Private));
	}

	return self;
}
