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
    T_IM_PRO_PGAIN_CTRL pgainCtrlMax;
    T_IM_PRO_PGAIN_CTRL pgainCtrlMin;
    T_IM_PRO_PZSFT_CTRL pzsftCtrlMax;
    T_IM_PRO_PZSFT_CTRL pzsftCtrlMin;
};


/**
 * IMPL
 */
static void ct_impro_6_2_constructor(CtImpro62 *self)
{
	CtImpro62Private *priv = CT_IMPRO_6_2_GET_PRIVATE(self);

    priv->pgainCtrlMax.R  = 8191;
    priv->pgainCtrlMax.Gr = 8191;
    priv->pgainCtrlMax.Gb = 8191;
    priv->pgainCtrlMax.B  = 8191;
    priv->pgainCtrlMax.ROffset = 4095;
    priv->pgainCtrlMax.GrOffset = 4095;
    priv->pgainCtrlMax.GbOffset = 4095;
    priv->pgainCtrlMax.BOffset = 4095;
    priv->pgainCtrlMax.decimalPointPosition = E_IM_PRO_PGAIN_DECI_POS_3;

    priv->pgainCtrlMin.R  = 0;
    priv->pgainCtrlMin.Gr = 0;
    priv->pgainCtrlMin.Gb = 0;
    priv->pgainCtrlMin.B  = 0;
    priv->pgainCtrlMin.ROffset = -4096;
    priv->pgainCtrlMin.GrOffset = -4096;
    priv->pgainCtrlMin.GbOffset = -4096;
    priv->pgainCtrlMin.BOffset = -4096;
    priv->pgainCtrlMin.decimalPointPosition = E_IM_PRO_PGAIN_DECI_POS_8;
    priv->pzsftCtrlMax.offsetShift = 32767;
    priv->pzsftCtrlMin.offsetShift = -32768;
}

static void ct_impro_6_2_destructor(CtImpro62 *self)
{
	CtImpro62Private *priv = CT_IMPRO_6_2_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_6_2_0(CtImpro62* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PGAIN0_SELECT; ch < D_IM_PRO_PGAIN_CNT; ch++) {
                    ercd = Im_PRO_PGAIN_Start(unitNo, blockType, ch);
                    im_pro_6_2_print_0(im_pro_6_2_print_get(), unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_2_1(CtImpro62* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kuchar               force = 0;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                force = blockType % 2;
                for(ch = E_IM_PRO_PGAIN0_SELECT; ch < D_IM_PRO_PGAIN_CNT; ch++) {
                    ercd = Im_PRO_PGAIN_Stop(unitNo, blockType, ch, force);
                    im_pro_6_2_print_1(im_pro_6_2_print_get(),unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_2_2(CtImpro62* self,const kuint32 idx)
{
	CtImpro62Private *priv = CT_IMPRO_6_2_GET_PRIVATE(self);
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar                 ch;
    
    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PGAIN0_SELECT; ch < D_IM_PRO_PGAIN_CNT; ch++) {
                    ercd = Im_PRO_PGAIN_Ctrl(unitNo, blockType, ch, &priv->pgainCtrlMax);
                    im_pro_6_2_print_2(im_pro_6_2_print_get(),"max_para", unitNo, blockType, ch, ercd, &priv->pgainCtrlMax);

                    ercd = Im_PRO_PGAIN_Ctrl(unitNo, blockType, ch, &priv->pgainCtrlMin);
                    im_pro_6_2_print_2(im_pro_6_2_print_get(),"min_para", unitNo, blockType, ch, ercd, &priv->pgainCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_2_3(CtImpro62* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    const T_IM_PRO_RDMA_PGAIN_ADDR* addr;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PGAIN0_SELECT; ch < D_IM_PRO_PGAIN_CNT; ch++) {
                    ercd = Im_PRO_Get_RdmaAddr_PGAIN_Cntl(unitNo, blockType, ch, &addr);
                    im_pro_6_2_print_3(im_pro_6_2_print_get(),unitNo, blockType, ch, ercd, &addr);
                }
            }
        }
    }
}

void ct_im_pro_6_2_4(CtImpro62* self,const kuint32 idx)
{
    kint32             ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar             ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(ch = E_IM_PRO_PZSFT_CH_B1; ch < E_IM_PRO_PZSFT_CH_MAX; ch++) {
                ercd = Im_PRO_PZSFT_Start(unitNo, ch);
                im_pro_6_2_print_4(im_pro_6_2_print_get(),unitNo, ch, ercd);
            }
        }
    }
}

void ct_im_pro_6_2_5(CtImpro62* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    kuchar               ch;
    kuchar               force = 0;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(ch = E_IM_PRO_PZSFT_CH_B1; ch < E_IM_PRO_PZSFT_CH_MAX; ch++) {
                force = ch % 2;
                ercd = Im_PRO_PZSFT_Stop(unitNo, ch, force);
                im_pro_6_2_print_5(im_pro_6_2_print_get(),unitNo, ch, ercd, force);
            }
        }
    }
}

void ct_im_pro_6_2_6(CtImpro62* self,const kuint32 idx)
{
	CtImpro62Private *priv = CT_IMPRO_6_2_GET_PRIVATE(self);
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(ch = E_IM_PRO_PZSFT_CH_B1; ch < E_IM_PRO_PZSFT_CH_MAX; ch++) {
                ercd = Im_PRO_PZSFT_Ctrl(unitNo, ch, &priv->pzsftCtrlMax);
                im_pro_6_2_print_6(im_pro_6_2_print_get(),"max_para", unitNo, ch, ercd, &priv->pzsftCtrlMax);

                ercd = Im_PRO_PZSFT_Ctrl(unitNo, ch, &priv->pzsftCtrlMin);
                im_pro_6_2_print_6(im_pro_6_2_print_get(),"min_para", unitNo, ch, ercd, &priv->pzsftCtrlMin);
            }
        }
    }
}

void ct_im_pro_6_2_7(CtImpro62* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    kuchar               ch;
    const T_IM_PRO_RDMA_PZSFT_ADDR* addr;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(ch = E_IM_PRO_PZSFT_CH_B1; ch < E_IM_PRO_PZSFT_CH_MAX; ch++) {
                ercd = Im_PRO_Get_RdmaAddr_PZSFT_Cntl(unitNo, ch, &addr);
                im_pro_6_2_print_7(im_pro_6_2_print_get(),unitNo, ch, ercd, &addr);
            }
        }
    }
}

void ct_im_pro_6_2_8(CtImpro62* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                ercd = Im_PRO_PG_Start(unitNo, blockType);
                im_pro_6_2_print_8(im_pro_6_2_print_get(),unitNo, blockType, ercd);
            }
        }
    }
}

void ct_im_pro_6_2_9(CtImpro62* self,const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                ercd = Im_PRO_PG_Stop(unitNo, blockType);
                im_pro_6_2_print_9(im_pro_6_2_print_get(),unitNo, blockType, ercd);
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
