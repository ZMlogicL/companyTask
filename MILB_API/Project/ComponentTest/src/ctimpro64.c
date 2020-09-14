/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro64
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro64.h"
#include "impro6print.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImpro64, ct_impro_6_4)
#define CT_IMPRO_6_4_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro64Private, CT_TYPE_IMPRO_6_4))


struct _CtImpro64Private
{
    T_IM_PRO_PRCH_CTRL  prchCtrlMax;
    T_IM_PRO_PRCH_CTRL  prchCtrlMin;
    T_IM_PRO_AXI_CTRL   axiCtrlMax;
    T_IM_PRO_AXI_CTRL   axiCtrlMin;
    T_IM_PRO_PRCH_AREA  prAreaMax;
    T_IM_PRO_PRCH_AREA  prAreaMin;
};


/**
 * IMPL
 */
static void ct_impro_6_4_constructor(CtImpro64 *self)
{
	CtImpro64Private *priv = CT_IMPRO_6_4_GET_PRIVATE(self);

    priv->prchCtrlMax.transMode = E_IM_PRO_PRCH_BURST_512BYTE;
    priv->prchCtrlMax.reqThreshold = E_IM_PRO_PRCH_CNT_MAX3;
    priv->prchCtrlMax.transTo = E_IM_PRO_PRCH_TRANS_IO_0;

    priv->prchCtrlMin.transMode = E_IM_PRO_PRCH_BURST_512BYTE;
    priv->prchCtrlMin.reqThreshold = E_IM_PRO_PRCH_CNT_NOLIMIT;
    priv->prchCtrlMin.transTo = E_IM_PRO_PRCH_TRANS_IO_0;

    priv->axiCtrlMax.cacheType = 15;
    priv->axiCtrlMax.protectType = 7;

    priv->axiCtrlMin.cacheType = 0;
    priv->axiCtrlMin.protectType = 0;

    priv->prAreaMax.width = 16777215;
    priv->prAreaMax.height = 16383;
    priv->prAreaMax.globalWidth = 4294967295;

    priv->prAreaMin.width = 0;
    priv->prAreaMin.height = 0;
    priv->prAreaMin.globalWidth = 0;
}

static void ct_impro_6_4_destructor(CtImpro64 *self)
{
	CtImpro64Private *priv = CT_IMPRO_6_4_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_6_4_0(CtImpro64* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    const T_IM_PRO_RDMA_M2P_DEKNEE_TBL_ADDR*    addr;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_M2P_0; ch < E_IM_PRO_M2P_MAX; ch++) {
                    ercd = Im_PRO_Get_RdmaAddr_M2P_Deknee_Tbl(unitNo, blockType, ch, &addr);
                    im_pro_6_4_print_0(im_pro_6_4_print_get(),unitNo, blockType, ch, ercd, &addr);
                }
            }
        }
    }
}

void ct_im_pro_6_4_1(CtImpro64* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Start(unitNo, blockType, ch);
                    im_pro_6_4_print_1(im_pro_6_4_print_get(),unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_4_2(CtImpro64* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;
    kuchar               force = 0;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                force = blockType % 2;
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Stop(unitNo, blockType, ch, force);
                    im_pro_6_4_print_2(im_pro_6_4_print_get(),unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_4_3(CtImpro64* self,const kuint32 idx)
{
	CtImpro64Private *priv = CT_IMPRO_6_4_GET_PRIVATE(self);
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Ctrl(unitNo, blockType, ch, &priv->prchCtrlMax);
                    im_pro_6_4_print_3(im_pro_6_4_print_get(),"max_para", unitNo, blockType, ch, ercd, &priv->prchCtrlMax);

                    ercd = Im_PRO_PRch_Ctrl(unitNo, blockType, ch, &priv->prchCtrlMin);
                    im_pro_6_4_print_3(im_pro_6_4_print_get(),"min_para", unitNo, blockType, ch, ercd, &priv->prchCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_4_4(CtImpro64* self,const kuint32 idx)
{
	CtImpro64Private *priv = CT_IMPRO_6_4_GET_PRIVATE(self);
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Ctrl_Axi(unitNo, blockType, ch, &priv->axiCtrlMax);
                    im_pro_6_4_print_4(im_pro_6_4_print_get(),"max_para", unitNo, blockType, ch, ercd, &priv->axiCtrlMax);

                    ercd = Im_PRO_PRch_Ctrl_Axi(unitNo, blockType, ch, &priv->axiCtrlMin);
                    im_pro_6_4_print_4(im_pro_6_4_print_get(),"min_para", unitNo, blockType, ch, ercd, &priv->axiCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_4_5(CtImpro64* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kulong               prAddr;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    prAddr = 1;
                    ercd = Im_PRO_PRch_Set_Addr(unitNo, blockType, ch, prAddr);
                    im_pro_6_4_print_5(im_pro_6_4_print_get(),"max_para", unitNo, blockType, ch, ercd, prAddr);

                    prAddr = 0xFFFFFFFF;
                    ercd = Im_PRO_PRch_Set_Addr(unitNo, blockType, ch, prAddr);
                    im_pro_6_4_print_5(im_pro_6_4_print_get(),"min_para", unitNo, blockType, ch, ercd, prAddr);
                }
            }
        }
    }
}

void ct_im_pro_6_4_6(CtImpro64* self,const kuint32 idx)
{
	CtImpro64Private *priv = CT_IMPRO_6_4_GET_PRIVATE(self);
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Set_Area(unitNo, blockType, ch, &priv->prAreaMax);
                    im_pro_6_4_print_6(im_pro_6_4_print_get(),"max_para", unitNo, blockType, ch, ercd, &priv->prAreaMax);

                    ercd = Im_PRO_PRch_Set_Area(unitNo, blockType, ch, &priv->prAreaMin);
                    im_pro_6_4_print_6(im_pro_6_4_print_get(),"min_para", unitNo, blockType, ch, ercd, &priv->prAreaMin);
                }
            }
        }
    }
}

void ct_im_pro_6_4_7(CtImpro64* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kuchar               axiResponse;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Get_AXI_Response(unitNo, blockType, ch, &axiResponse);
                    im_pro_6_4_print_7(im_pro_6_4_print_get(),unitNo, blockType, ch, ercd, axiResponse);
                }
            }
        }
    }
}
#endif

CtImpro64* ct_impro_6_4_new(void)
{
	CtImpro64* self = k_object_new_with_private(CT_TYPE_IMPRO_6_4, sizeof(CtImpro64Private));

	return self;
}

CtImpro64* ct_impro_6_4_get(void)
{
	static CtImpro64* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_6_4, sizeof(CtImpro64Private));
	}

	return self;
}
