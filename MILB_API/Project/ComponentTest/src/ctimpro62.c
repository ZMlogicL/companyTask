/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro62
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro62.h"
#include "impro6print.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImpro62, ct_impro_6_2)
#define CT_IMPRO_6_2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro62Private, CT_TYPE_IMPRO_6_2))


struct _CtImpro62Private
{

};


/**
 * IMPL
 */
static void ct_impro_6_2_constructor(CtImpro62 *self)
{
	CtImpro62Private *priv = CT_IMPRO_6_2_GET_PRIVATE(self);
}

static void ct_impro_6_2_destructor(CtImpro62 *self)
{
	CtImpro62Private *priv = CT_IMPRO_6_2_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_6_0_20(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PGAIN0_SELECT; ch < D_IM_PRO_PGAIN_CNT; ch++) {
                    ercd = Im_PRO_PGAIN_Start(unitNo, blockType, ch);
                    im_pro_6_2_print_0(NULL,unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_0_21(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kuchar               force = 0;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                force = blockType % 2;
                for(ch = E_IM_PRO_PGAIN0_SELECT; ch < D_IM_PRO_PGAIN_CNT; ch++) {
                    ercd = Im_PRO_PGAIN_Stop(unitNo, blockType, ch, force);
                    im_pro_6_2_print_1(NULL,unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_0_22(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar                 ch;
    T_IM_PRO_PGAIN_CTRL pgainCtrlMax = {
        .R                      = 8191,
        .Gr                     = 8191,
        .Gb                     = 8191,
        .B                      = 8191,
        .ROffset               = 4095,
        .GrOffset              = 4095,
        .GbOffset              = 4095,
        .BOffset               = 4095,
        .decimalPointPosition = E_IM_PRO_PGAIN_DECI_POS_3,
    };

    T_IM_PRO_PGAIN_CTRL pgainCtrlMin = {
        .R                      = 0,
        .Gr                     = 0,
        .Gb                     = 0,
        .B                      = 0,
        .ROffset               = -4096,
        .GrOffset              = -4096,
        .GbOffset              = -4096,
        .BOffset               = -4096,
        .decimalPointPosition = E_IM_PRO_PGAIN_DECI_POS_8,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PGAIN0_SELECT; ch < D_IM_PRO_PGAIN_CNT; ch++) {
                    ercd = Im_PRO_PGAIN_Ctrl(unitNo, blockType, ch, &pgainCtrlMax);
                    im_pro_6_2_print_2(NULL,"max_para", unitNo, blockType, ch, ercd, &pgainCtrlMax);

                    ercd = Im_PRO_PGAIN_Ctrl(unitNo, blockType, ch, &pgainCtrlMin);
                    im_pro_6_2_print_2(NULL,"min_para", unitNo, blockType, ch, ercd, &pgainCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_0_23(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    const T_IM_PRO_RDMA_PGAIN_ADDR* addr;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PGAIN0_SELECT; ch < D_IM_PRO_PGAIN_CNT; ch++) {
                    ercd = Im_PRO_Get_RdmaAddr_PGAIN_Cntl(unitNo, blockType, ch, &addr);
                    im_pro_6_2_print_3(NULL,unitNo, blockType, ch, ercd, &addr);
                }
            }
        }
    }
}

void ct_im_pro_6_0_24(const kuint32 idx)
{
    kint32             ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar             ch;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(ch = E_IM_PRO_PZSFT_CH_B1; ch < E_IM_PRO_PZSFT_CH_MAX; ch++) {
                ercd = Im_PRO_PZSFT_Start(unitNo, ch);
                im_pro_6_2_print_4(NULL,unitNo, ch, ercd);
            }
        }
    }
}

void ct_im_pro_6_0_25(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar               ch;
    kuchar               force = 0;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(ch = E_IM_PRO_PZSFT_CH_B1; ch < E_IM_PRO_PZSFT_CH_MAX; ch++) {
                force = ch % 2;
                ercd = Im_PRO_PZSFT_Stop(unitNo, ch, force);
                im_pro_6_2_print_5(NULL,unitNo, ch, ercd, force);
            }
        }
    }
}

void ct_im_pro_6_0_26(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    kuchar               ch;
    T_IM_PRO_PZSFT_CTRL pzsftCtrlMax = {
        .offsetShift   = 32767,
    };

    T_IM_PRO_PZSFT_CTRL pzsftCtrlMin = {
        .offsetShift   = -32768,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(ch = E_IM_PRO_PZSFT_CH_B1; ch < E_IM_PRO_PZSFT_CH_MAX; ch++) {
                ercd = Im_PRO_PZSFT_Ctrl(unitNo, ch, &pzsftCtrlMax);
                im_pro_6_2_print_6(NULL,"max_para", unitNo, ch, ercd, &pzsftCtrlMax);

                ercd = Im_PRO_PZSFT_Ctrl(unitNo, ch, &pzsftCtrlMin);
                im_pro_6_2_print_6(NULL,"min_para", unitNo, ch, ercd, &pzsftCtrlMin);
            }
        }
    }
}

void ct_im_pro_6_0_27(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    kuchar               ch;
    const T_IM_PRO_RDMA_PZSFT_ADDR* addr;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(ch = E_IM_PRO_PZSFT_CH_B1; ch < E_IM_PRO_PZSFT_CH_MAX; ch++) {
                ercd = Im_PRO_Get_RdmaAddr_PZSFT_Cntl(unitNo, ch, &addr);
                im_pro_6_2_print_7(NULL,unitNo, ch, ercd, &addr);
            }
        }
    }
}

void ct_im_pro_6_0_28(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                ercd = Im_PRO_PG_Start(unitNo, blockType);
                im_pro_6_2_print_8(NULL,unitNo, blockType, ercd);
            }
        }
    }
}

void ct_im_pro_6_0_29(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                ercd = Im_PRO_PG_Stop(unitNo, blockType);
                im_pro_6_2_print_9(NULL,unitNo, blockType, ercd);
            }
        }
    }
}
#endif

CtImpro62* ct_impro_6_2_new(void)
{
	CtImpro62* self = k_object_new_with_private(CT_TYPE_IMPRO_6_2, sizeof(CtImpro62Private));

	return self;
}

CtImpro62* ct_impro_6_2_get(void)
{
	static CtImpro62* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_6_2, sizeof(CtImpro62Private));
	}

	return self;
}
