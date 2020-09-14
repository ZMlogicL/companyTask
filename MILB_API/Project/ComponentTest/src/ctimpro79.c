/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro79
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro79.h"
#include "impro7print.h"
#include "improdebug.h"
#include "improcallback.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImpro79, ct_impro_7_9)
#define CT_IMPRO_7_9_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro79Private, CT_TYPE_IMPRO_7_9))


struct _CtImpro79Private
{
    T_IM_PRO_INT_CFG intCtrl;
    TImProCallbackCfg callbackIntCtrl;
};


/**
 *IMPL
 */
static void ct_impro_7_9_constructor(CtImpro79 *self)
{
	CtImpro79Private *priv = CT_IMPRO_7_9_GET_PRIVATE(self);

    priv->intCtrl.interruptBit = 0; 
    priv->intCtrl.permissionFlg = 0;

    priv->callbackIntCtrl.inthandler = NULL;
    priv->callbackIntCtrl.userParam = 0;
}

static void ct_impro_7_9_destructor(CtImpro79 *self)
{
	CtImpro79Private *priv = CT_IMPRO_7_9_GET_PRIVATE(self);
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_9_0(CtImpro79* self,const kuint32 idx)
{
	CtImpro79Private *priv = CT_IMPRO_7_9_GET_PRIVATE(self);    
    kint32 ercd;
    kuchar permissionFlg;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;

#ifdef CO_DEBUG_ON_PC
    const T_IM_PRO_COMMON_PRCH_INFO* prchRegInfo = 0;
#endif  // CO_DEBUG_ON_PC

    if(idx == 1) {
        for(unitNo = 0; unitNo < E_IM_PRO_BOTH_UNIT; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = 0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                        priv->intCtrl.permissionFlg = permissionFlg;

                        priv->intCtrl.interruptBit = (D_IM_PRO_PRCHINTENB_PRE |
                                                D_IM_PRO_PRCHINTENB_PREE |
                                                D_IM_PRO_PRCHINTENB_PRXE |
                                                D_IM_PRO_PRCHINTFLG_PRF |
                                                D_IM_PRO_PRCHINTFLG_PREF |
                                                D_IM_PRO_PRCHINTFLG_PRXF);
#ifdef CO_DEBUG_ON_PC
                        im_pro_comm_get_prchRegInfo(unitNo, blockType, ch, &prchRegInfo);
                        prchRegInfo->regPtr->prchintflg.word = priv->intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                        ercd = Im_PRO_PRch_Set_Interrupt(unitNo, blockType, ch, &priv->intCtrl);
                        im_pro_7_print_90(im_pro_7_print_get(), ercd, unitNo, blockType, ch, &priv->intCtrl, permissionFlg);
                    }
                }
            }
        }
    }
}

void ct_im_pro_7_9_1(CtImpro79* self,const kuint32 idx)
{
	CtImpro79Private *priv = CT_IMPRO_7_9_GET_PRIVATE(self);
    kint32 ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;
    kulong userParam;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = 0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    for(userParam = 0; userParam < 4; userParam++) {
                        priv->callbackIntCtrl.inthandler = im_pro_callback_prch_int_cb;
                        priv->callbackIntCtrl.userParam = userParam;
                        ercd = Im_PRO_PRch_Set_Int_Handler(unitNo, blockType, ch, &priv->callbackIntCtrl);
                        im_pro_7_print_91(im_pro_7_print_get(), "", unitNo, blockType, ch, ercd, &priv->callbackIntCtrl);
                    }
                }
            }
        }
    }
}
#endif

CtImpro79* ct_impro_7_9_new(void)
{
	CtImpro79* self = k_object_new_with_private(CT_TYPE_IMPRO_7_9, sizeof(CtImpro79Private));

	return self;
}

CtImpro79* ct_impro_7_9_get(void)
{
	static CtImpro79* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_7_9, sizeof(CtImpro79Private));
	}

	return self;
}
