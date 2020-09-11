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

};


/**
 * IMPL
 */
static void ct_impro_6_4_constructor(CtImpro64 *self)
{
	CtImpro64Private *priv = CT_IMPRO_6_4_GET_PRIVATE(self);
}

static void ct_impro_6_4_destructor(CtImpro64 *self)
{
	CtImpro64Private *priv = CT_IMPRO_6_4_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_6_0_40(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    const T_IM_PRO_RDMA_M2P_DEKNEE_TBL_ADDR*    addr;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_M2P_0; ch < E_IM_PRO_M2P_MAX; ch++) {
                    ercd = Im_PRO_Get_RdmaAddr_M2P_Deknee_Tbl(unitNo, blockType, ch, &addr);
                    im_pro_6_4_print_0(NULL,unitNo, blockType, ch, ercd, &addr);
                }
            }
        }
    }
}

void ct_im_pro_6_0_41(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Start(unitNo, blockType, ch);
                    im_pro_6_4_print_1(NULL,unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_0_42(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;
    kuchar               force = 0;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                force = blockType % 2;
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Stop(unitNo, blockType, ch, force);
                    im_pro_6_4_print_2(NULL,unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_0_43(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_PRCH_CTRL  prchCtrlMax = {
        .transMode = E_IM_PRO_PRCH_BURST_512BYTE,
        .reqThreshold = E_IM_PRO_PRCH_CNT_MAX3,
        .transTo = E_IM_PRO_PRCH_TRANS_IO_0,
    };

    T_IM_PRO_PRCH_CTRL  prchCtrlMin = {
        .transMode = E_IM_PRO_PRCH_BURST_512BYTE,
        .reqThreshold = E_IM_PRO_PRCH_CNT_NOLIMIT,
        .transTo = E_IM_PRO_PRCH_TRANS_IO_0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Ctrl(unitNo, blockType, ch, &prchCtrlMax);
                    im_pro_6_4_print_3(NULL,"max_para", unitNo, blockType, ch, ercd, &prchCtrlMax);

                    ercd = Im_PRO_PRch_Ctrl(unitNo, blockType, ch, &prchCtrlMin);
                    im_pro_6_4_print_3(NULL,"min_para", unitNo, blockType, ch, ercd, &prchCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_0_44(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_AXI_CTRL   axiCtrlMax = {
        .cacheType     = 15,
        .protectType   = 7,
    };

    T_IM_PRO_AXI_CTRL   axiCtrlMin = {
        .cacheType     = 0,
        .protectType   = 0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Ctrl_Axi(unitNo, blockType, ch, &axiCtrlMax);
                    im_pro_6_4_print_4(NULL,"max_para", unitNo, blockType, ch, ercd, &axiCtrlMax);

                    ercd = Im_PRO_PRch_Ctrl_Axi(unitNo, blockType, ch, &axiCtrlMin);
                    im_pro_6_4_print_4(NULL,"min_para", unitNo, blockType, ch, ercd, &axiCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_0_45(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kulong               prAddr;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    prAddr = 1;
                    ercd = Im_PRO_PRch_Set_Addr(unitNo, blockType, ch, prAddr);
                    im_pro_6_4_print_5(NULL,"max_para", unitNo, blockType, ch, ercd, prAddr);

                    prAddr = 0xFFFFFFFF;
                    ercd = Im_PRO_PRch_Set_Addr(unitNo, blockType, ch, prAddr);
                    im_pro_6_4_print_5(NULL,"min_para", unitNo, blockType, ch, ercd, prAddr);
                }
            }
        }
    }
}

void ct_im_pro_6_0_46(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_PRCH_AREA  prAreaMax = {
        .width          = 16777215,
        .height         = 16383,
        .globalWidth   = 4294967295,
    };

    T_IM_PRO_PRCH_AREA  prAreaMin = {
        .width          = 0,
        .height         = 0,
        .globalWidth   = 0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Set_Area(unitNo, blockType, ch, &prAreaMax);
                    im_pro_6_4_print_6(NULL,"max_para", unitNo, blockType, ch, ercd, &prAreaMax);

                    ercd = Im_PRO_PRch_Set_Area(unitNo, blockType, ch, &prAreaMin);
                    im_pro_6_4_print_6(NULL,"min_para", unitNo, blockType, ch, ercd, &prAreaMin);
                }
            }
        }
    }
}

void ct_im_pro_6_0_47(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kuchar               axiResponse;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PRCH_0; ch < E_IM_PRO_PRCH_MAX; ch++) {
                    ercd = Im_PRO_PRch_Get_AXI_Response(unitNo, blockType, ch, &axiResponse);
                    im_pro_6_4_print_7(NULL,unitNo, blockType, ch, ercd, axiResponse);
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
