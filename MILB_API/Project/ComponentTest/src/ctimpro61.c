/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro61
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro61.h"
#include "impro6print.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImpro61, ct_impro_6_1)
#define CT_IMPRO_6_1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro61Private, CT_TYPE_IMPRO_6_1))


struct _CtImpro61Private
{
    T_IM_PRO_AXI_CTRL   axiCtrlMax;
    T_IM_PRO_AXI_CTRL   axiCtrlMin;
    T_IM_PRO_PWCH_INFO  pwchInfoMax;
    T_IM_PRO_PWCH_INFO  pwchInfoMin;
    T_IM_PRO_LNR_CTRL   lnrCtrlMax;
    T_IM_PRO_LNR_CTRL   lnrCtrlMin;
};


/**
 * IMPL
 */
static void ct_impro_6_1_constructor(CtImpro61 *self)
{
	CtImpro61Private *priv = CT_IMPRO_6_1_GET_PRIVATE(self);

        priv->axiCtrlMax.cacheType     = 15,
        priv->axiCtrlMax.protectType   = 7,

        priv->axiCtrlMin.cacheType     = 0,
        priv->axiCtrlMin.protectType   = 0,

        priv->pwchInfoMax.bufferNum     =8,
        priv->pwchInfoMax.buffAddr[0]   =0x40000000,
        priv->pwchInfoMax.buffAddr[1]   =0x50000000,
        priv->pwchInfoMax.buffAddr[2]   =0x60000000,
        priv->pwchInfoMax.buffAddr[3]   =0x70000000,
        priv->pwchInfoMax.buffAddr[4]   =0x80000000,
        priv->pwchInfoMax.buffAddr[5]   =0x90000000,
        priv->pwchInfoMax.buffAddr[6]   =0xA0000000,
        priv->pwchInfoMax.buffAddr[7]   =0xB0000000,

        priv->pwchInfoMin.bufferNum     =1,
        priv->pwchInfoMin.buffAddr[0]   =0x40000000,
        priv->pwchInfoMin.buffAddr[1]   =0,
        priv->pwchInfoMin.buffAddr[2]   =0,
        priv->pwchInfoMin.buffAddr[3]   =0,
        priv->pwchInfoMin.buffAddr[4]   =0,
        priv->pwchInfoMin.buffAddr[5]   =0,
        priv->pwchInfoMin.buffAddr[6]   =0,
        priv->pwchInfoMin.buffAddr[7]   =0,

        priv->lnrCtrlMax.lnrBr[0]      = 16383,
        priv->lnrCtrlMax.lnrBr[1]      = 16383,
        priv->lnrCtrlMax.lnrBr[2]      = 16383,
        priv->lnrCtrlMax.lnrBr[3]      = 16383,
        priv->lnrCtrlMax.lnrBr[4]      = 16383,
        priv->lnrCtrlMax.lnrBr[5]      = 16383,
        priv->lnrCtrlMax.lnrBr[6]      = 16383,
        priv->lnrCtrlMax.lnrIncr[0]    = 1023,
        priv->lnrCtrlMax.lnrIncr[1]    = 1023,
        priv->lnrCtrlMax.lnrIncr[2]    = 1023,
        priv->lnrCtrlMax.lnrIncr[3]    = 1023,
        priv->lnrCtrlMax.lnrIncr[4]    = 1023,
        priv->lnrCtrlMax.lnrIncr[5]    = 1023,
        priv->lnrCtrlMax.lnrIncr[6]    = 1023,
        priv->lnrCtrlMax.lnrIncr[7]    = 1023,
        priv->lnrCtrlMax.lnrOfsr[0]    = 16383,
        priv->lnrCtrlMax.lnrOfsr[1]    = 16383,
        priv->lnrCtrlMax.lnrOfsr[2]    = 16383,
        priv->lnrCtrlMax.lnrOfsr[3]    = 16383,
        priv->lnrCtrlMax.lnrOfsr[4]    = 16383,
        priv->lnrCtrlMax.lnrOfsr[5]    = 16383,
        priv->lnrCtrlMax.lnrOfsr[6]    = 16383,
        priv->lnrCtrlMax.lnrOfsr[7]    = 16383,
        priv->lnrCtrlMax.lnrBgr[0]     = 16383,
        priv->lnrCtrlMax.lnrBgr[1]     = 16383,
        priv->lnrCtrlMax.lnrBgr[2]     = 16383,
        priv->lnrCtrlMax.lnrBgr[3]     = 16383,
        priv->lnrCtrlMax.lnrBgr[4]     = 16383,
        priv->lnrCtrlMax.lnrBgr[5]     = 16383,
        priv->lnrCtrlMax.lnrBgr[6]     = 16383,
        priv->lnrCtrlMax.lnrIncgr[0]   = 1023,
        priv->lnrCtrlMax.lnrIncgr[1]   = 1023,
        priv->lnrCtrlMax.lnrIncgr[2]   = 1023,
        priv->lnrCtrlMax.lnrIncgr[3]   = 1023,
        priv->lnrCtrlMax.lnrIncgr[4]   = 1023,
        priv->lnrCtrlMax.lnrIncgr[5]   = 1023,
        priv->lnrCtrlMax.lnrIncgr[6]   = 1023,
        priv->lnrCtrlMax.lnrIncgr[7]   = 1023,
        priv->lnrCtrlMax.lnrOfsgr[0]   = 16383,
        priv->lnrCtrlMax.lnrOfsgr[1]   = 16383,
        priv->lnrCtrlMax.lnrOfsgr[2]   = 16383,
        priv->lnrCtrlMax.lnrOfsgr[3]   = 16383,
        priv->lnrCtrlMax.lnrOfsgr[4]   = 16383,
        priv->lnrCtrlMax.lnrOfsgr[5]   = 16383,
        priv->lnrCtrlMax.lnrOfsgr[6]   = 16383,
        priv->lnrCtrlMax.lnrOfsgr[7]   = 16383,
        priv->lnrCtrlMax.lnrBgb[0]     = 16383,
        priv->lnrCtrlMax.lnrBgb[1]     = 16383,
        priv->lnrCtrlMax.lnrBgb[2]     = 16383,
        priv->lnrCtrlMax.lnrBgb[3]     = 16383,
        priv->lnrCtrlMax.lnrBgb[4]     = 16383,
        priv->lnrCtrlMax.lnrBgb[5]     = 16383,
        priv->lnrCtrlMax.lnrBgb[6]     = 16383,
        priv->lnrCtrlMax.lnrIncgb[0]   = 1023,
        priv->lnrCtrlMax.lnrIncgb[1]   = 1023,
        priv->lnrCtrlMax.lnrIncgb[2]   = 1023,
        priv->lnrCtrlMax.lnrIncgb[3]   = 1023,
        priv->lnrCtrlMax.lnrIncgb[4]   = 1023,
        priv->lnrCtrlMax.lnrIncgb[5]   = 1023,
        priv->lnrCtrlMax.lnrIncgb[6]   = 1023,
        priv->lnrCtrlMax.lnrIncgb[7]   = 1023,
        priv->lnrCtrlMax.lnrOfsgb[0]   = 1023,
        priv->lnrCtrlMax.lnrOfsgb[1]   = 1023,
        priv->lnrCtrlMax.lnrOfsgb[2]   = 1023,
        priv->lnrCtrlMax.lnrOfsgb[3]   = 1023,
        priv->lnrCtrlMax.lnrOfsgb[4]   = 1023,
        priv->lnrCtrlMax.lnrOfsgb[5]   = 1023,
        priv->lnrCtrlMax.lnrOfsgb[6]   = 1023,
        priv->lnrCtrlMax.lnrOfsgb[7]   = 1023,
        priv->lnrCtrlMax.lnrBb[0]      = 16383,
        priv->lnrCtrlMax.lnrBb[1]      = 16383,
        priv->lnrCtrlMax.lnrBb[2]      = 16383,
        priv->lnrCtrlMax.lnrBb[3]      = 16383,
        priv->lnrCtrlMax.lnrBb[4]      = 16383,
        priv->lnrCtrlMax.lnrBb[5]      = 16383,
        priv->lnrCtrlMax.lnrBb[6]      = 16383,
        priv->lnrCtrlMax.lnrIncb[0]    = 1023,
        priv->lnrCtrlMax.lnrIncb[1]    = 1023,
        priv->lnrCtrlMax.lnrIncb[2]    = 1023,
        priv->lnrCtrlMax.lnrIncb[3]    = 1023,
        priv->lnrCtrlMax.lnrIncb[4]    = 1023,
        priv->lnrCtrlMax.lnrIncb[5]    = 1023,
        priv->lnrCtrlMax.lnrIncb[6]    = 1023,
        priv->lnrCtrlMax.lnrIncb[7]    = 1023,
        priv->lnrCtrlMax.lnrOfsb[0]    = 16383,
        priv->lnrCtrlMax.lnrOfsb[1]    = 16383,
        priv->lnrCtrlMax.lnrOfsb[2]    = 16383,
        priv->lnrCtrlMax.lnrOfsb[3]    = 16383,
        priv->lnrCtrlMax.lnrOfsb[4]    = 16383,
        priv->lnrCtrlMax.lnrOfsb[5]    = 16383,
        priv->lnrCtrlMax.lnrOfsb[6]    = 16383,
        priv->lnrCtrlMax.lnrOfsb[7]    = 16383,

        priv->lnrCtrlMin.lnrBr[0]      = 0,
        priv->lnrCtrlMin.lnrBr[1]      = 0,
        priv->lnrCtrlMin.lnrBr[2]      = 0,
        priv->lnrCtrlMin.lnrBr[3]      = 0,
        priv->lnrCtrlMin.lnrBr[4]      = 0,
        priv->lnrCtrlMin.lnrBr[5]      = 0,
        priv->lnrCtrlMin.lnrBr[6]      = 0,
        priv->lnrCtrlMin.lnrIncr[0]    = 0,
        priv->lnrCtrlMin.lnrIncr[1]    = 0,
        priv->lnrCtrlMin.lnrIncr[2]    = 0,
        priv->lnrCtrlMin.lnrIncr[3]    = 0,
        priv->lnrCtrlMin.lnrIncr[4]    = 0,
        priv->lnrCtrlMin.lnrIncr[5]    = 0,
        priv->lnrCtrlMin.lnrIncr[6]    = 0,
        priv->lnrCtrlMin.lnrIncr[7]    = 0,
        priv->lnrCtrlMin.lnrOfsr[0]    = 0,
        priv->lnrCtrlMin.lnrOfsr[1]    = 0,
        priv->lnrCtrlMin.lnrOfsr[2]    = 0,
        priv->lnrCtrlMin.lnrOfsr[3]    = 0,
        priv->lnrCtrlMin.lnrOfsr[4]    = 0,
        priv->lnrCtrlMin.lnrOfsr[5]    = 0,
        priv->lnrCtrlMin.lnrOfsr[6]    = 0,
        priv->lnrCtrlMin.lnrOfsr[7]    = 0,
        priv->lnrCtrlMin.lnrBgr[0]     = 0,
        priv->lnrCtrlMin.lnrBgr[1]     = 0,
        priv->lnrCtrlMin.lnrBgr[2]     = 0,
        priv->lnrCtrlMin.lnrBgr[3]     = 0,
        priv->lnrCtrlMin.lnrBgr[4]     = 0,
        priv->lnrCtrlMin.lnrBgr[5]     = 0,
        priv->lnrCtrlMin.lnrBgr[6]     = 0,
        priv->lnrCtrlMin.lnrIncgr[0]   = 0,
        priv->lnrCtrlMin.lnrIncgr[1]   = 0,
        priv->lnrCtrlMin.lnrIncgr[2]   = 0,
        priv->lnrCtrlMin.lnrIncgr[3]   = 0,
        priv->lnrCtrlMin.lnrIncgr[4]   = 0,
        priv->lnrCtrlMin.lnrIncgr[5]   = 0,
        priv->lnrCtrlMin.lnrIncgr[6]   = 0,
        priv->lnrCtrlMin.lnrIncgr[7]   = 0,
        priv->lnrCtrlMin.lnrOfsgr[0]   = 0,
        priv->lnrCtrlMin.lnrOfsgr[1]   = 0,
        priv->lnrCtrlMin.lnrOfsgr[2]   = 0,
        priv->lnrCtrlMin.lnrOfsgr[3]   = 0,
        priv->lnrCtrlMin.lnrOfsgr[4]   = 0,
        priv->lnrCtrlMin.lnrOfsgr[5]   = 0,
        priv->lnrCtrlMin.lnrOfsgr[6]   = 0,
        priv->lnrCtrlMin.lnrOfsgr[7]   = 0,
        priv->lnrCtrlMin.lnrBgb[0]     = 0,
        priv->lnrCtrlMin.lnrBgb[1]     = 0,
        priv->lnrCtrlMin.lnrBgb[2]     = 0,
        priv->lnrCtrlMin.lnrBgb[3]     = 0,
        priv->lnrCtrlMin.lnrBgb[4]     = 0,
        priv->lnrCtrlMin.lnrBgb[5]     = 0,
        priv->lnrCtrlMin.lnrBgb[6]     = 0,
        priv->lnrCtrlMin.lnrIncgb[0]   = 0,
        priv->lnrCtrlMin.lnrIncgb[1]   = 0,
        priv->lnrCtrlMin.lnrIncgb[2]   = 0,
        priv->lnrCtrlMin.lnrIncgb[3]   = 0,
        priv->lnrCtrlMin.lnrIncgb[4]   = 0,
        priv->lnrCtrlMin.lnrIncgb[5]   = 0,
        priv->lnrCtrlMin.lnrIncgb[6]   = 0,
        priv->lnrCtrlMin.lnrIncgb[7]   = 0,
        priv->lnrCtrlMin.lnrOfsgb[0]   = 0,
        priv->lnrCtrlMin.lnrOfsgb[1]   = 0,
        priv->lnrCtrlMin.lnrOfsgb[2]   = 0,
        priv->lnrCtrlMin.lnrOfsgb[3]   = 0,
        priv->lnrCtrlMin.lnrOfsgb[4]   = 0,
        priv->lnrCtrlMin.lnrOfsgb[5]   = 0,
        priv->lnrCtrlMin.lnrOfsgb[6]   = 0,
        priv->lnrCtrlMin.lnrOfsgb[7]   = 0,
        priv->lnrCtrlMin.lnrBb[0]      = 0,
        priv->lnrCtrlMin.lnrBb[1]      = 0,
        priv->lnrCtrlMin.lnrBb[2]      = 0,
        priv->lnrCtrlMin.lnrBb[3]      = 0,
        priv->lnrCtrlMin.lnrBb[4]      = 0,
        priv->lnrCtrlMin.lnrBb[5]      = 0,
        priv->lnrCtrlMin.lnrBb[6]      = 0,
        priv->lnrCtrlMin.lnrIncb[0]    = 0,
        priv->lnrCtrlMin.lnrIncb[1]    = 0,
        priv->lnrCtrlMin.lnrIncb[2]    = 0,
        priv->lnrCtrlMin.lnrIncb[3]    = 0,
        priv->lnrCtrlMin.lnrIncb[4]    = 0,
        priv->lnrCtrlMin.lnrIncb[5]    = 0,
        priv->lnrCtrlMin.lnrIncb[6]    = 0,
        priv->lnrCtrlMin.lnrIncb[7]    = 0,
        priv->lnrCtrlMin.lnrOfsb[0]    = 0,
        priv->lnrCtrlMin.lnrOfsb[1]    = 0,
        priv->lnrCtrlMin.lnrOfsb[2]    = 0,
        priv->lnrCtrlMin.lnrOfsb[3]    = 0,
        priv->lnrCtrlMin.lnrOfsb[4]    = 0,
        priv->lnrCtrlMin.lnrOfsb[5]    = 0,
        priv->lnrCtrlMin.lnrOfsb[6]    = 0,
        priv->lnrCtrlMin.lnrOfsb[7]    = 0,

}

static void ct_impro_6_1_destructor(CtImpro61 *self)
{
	CtImpro61Private *priv = CT_IMPRO_6_1_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_6_1_0(CtImpro61* self, const kuint32 idx)
{
	CtImpro61Private *priv = CT_IMPRO_6_1_GET_PRIVATE(self);
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;


    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProPwch_0; ch < ImProPwch_MAX; ch++) {
                    ercd = Im_PRO_PWch_Ctrl_Axi(unitNo, blockType, ch, &priv->axiCtrlMax);
                    im_pro_6_1_print_0("max_para", unitNo, blockType, ch, ercd, &priv->axiCtrlMax);

                    ercd = Im_PRO_PWch_Ctrl_Axi(unitNo, blockType, ch, &priv->axiCtrlMin);
                    im_pro_6_1_print_0("min_para", unitNo, blockType, ch, ercd, &priv->axiCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_1_1(CtImpro61* self, const kuint32 idx)
{
	CtImpro61Private *priv = CT_IMPRO_6_1_GET_PRIVATE(self);
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
  
    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProPwch_0; ch < ImProPwch_MAX; ch++) {
                    ercd = Im_PRO_PWch_Set_Buf_Addr(unitNo, blockType, ch, &priv->pwchInfoMax);
                    im_pro_6_1_print_1("max_para", unitNo, blockType, ch, ercd);

                    ercd = Im_PRO_PWch_Set_Buf_Addr(unitNo, blockType, ch, &priv->pwchInfoMin);
                    im_pro_6_1_print_1("min_para", unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_1_2(CtImpro61* self, const kuint32 idx)
{
    kulong               bufAddr;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProPwch_0; ch < ImProPwch_MAX; ch++) {
                    bufAddr = Im_PRO_PWch_Get_Buf_Data(unitNo, blockType, ch);
                    DriverCommon_DDIM_PRINT(("Im_PRO_PWch_Get_Buf_Data(%u %u %u) BufAddr    (0x%lx)\n", 
                    unitNo, blockType, ch, bufAddr));
                }
            }
        }
    }
}

void ct_im_pro_6_1_3(CtImpro61* self, const kuint32 idx)
{
	CtImpro61Private *priv = CT_IMPRO_6_1_GET_PRIVATE(self);
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kuint32              bufIdx;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProPwch_0; ch < ImProPwch_MAX; ch++) {
                    Im_PRO_PWch_Set_Buf_Addr(unitNo, blockType, ch, &priv->pwchInfoMax);
                    for(bufIdx = 0; bufIdx < D_IM_PRO_PWCH_BUFFER_MAX; bufIdx++) {
                        ercd = Im_PRO_PWch_Update_Buf_Index(unitNo, blockType, ch);
                        im_pro_6_1_print_3(bufIdx, unitNo, blockType, ch, ercd);
                    }
                }
            }
        }
    }
}

void ct_im_pro_6_1_4(CtImpro61* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kulong               lineFeed;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProPwch_0; ch < ImProPwch_MAX; ch++) {
                    lineFeed = 0;
                    ercd = Im_PRO_PWch_Set_LineFeed(unitNo, blockType, ch, lineFeed);
                    im_pro_6_1_print_4("max_para", unitNo, blockType, ch, ercd, lineFeed);

                    lineFeed = 0xFFFFFFFF;
                    ercd = Im_PRO_PWch_Set_LineFeed(unitNo, blockType, ch, lineFeed);
                    im_pro_6_1_print_4("max_para", unitNo, blockType, ch, ercd, lineFeed);
                }
            }
        }
    }
}

void ct_im_pro_6_1_5(CtImpro61* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kuchar               axiResponse;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProPwch_0; ch < ImProPwch_MAX; ch++) {
                    ercd = Im_PRO_PWch_Get_AXI_Response(unitNo, blockType, ch, &axiResponse);
                    im_pro_6_1_print_5(unitNo, blockType, ch, ercd, axiResponse);
                }
            }
        }
    }
}

void ct_im_pro_6_1_6(CtImpro61* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_LNR_CH_0; ch < D_IM_PRO_SEN_LNR_CH_NUM; ch++) {
                    ercd = Im_PRO_LNR_Start(unitNo, blockType, ch);
                    im_pro_6_1_print_6(unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_1_7(CtImpro61* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;
    kuchar               force = 0;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                force = blockType % 2;
                for(ch = E_IM_PRO_LNR_CH_0; ch < D_IM_PRO_SEN_LNR_CH_NUM; ch++) {
                    ercd = Im_PRO_LNR_Stop(unitNo, blockType, ch, force);
                    im_pro_6_0_print_2(unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_1_8(CtImpro61* self, const kuint32 idx)
{
	CtImpro61Private *priv = CT_IMPRO_6_1_GET_PRIVATE(self);
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_LNR_CH_0; ch < D_IM_PRO_SEN_LNR_CH_NUM; ch++) {
                    ercd = Im_PRO_LNR_Ctrl(unitNo, blockType, ch, &priv->lnrCtrlMax);
                    im_pro_6_1_print_8("max_para", unitNo, blockType, ch, ercd, &priv->lnrCtrlMax);

                    ercd = Im_PRO_LNR_Ctrl(unitNo, blockType, ch, &priv->lnrCtrlMin);
                    im_pro_6_1_print_8("min_para", unitNo, blockType, ch, ercd, &priv->lnrCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_1_9(CtImpro61* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    const T_IM_PRO_RDMA_LNR_ADDR*   addr;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_LNR_CH_0; ch < D_IM_PRO_SEN_LNR_CH_NUM; ch++) {
                    ercd = Im_PRO_Get_RdmaAddr_LNR_Cntl(unitNo, blockType, ch, &addr);
                    im_pro_6_1_print_9(unitNo, blockType, ch, ercd, &addr);
                }
            }
        }
    }
}
#endif

CtImpro61* ct_impro_6_1_new(void)
{
	CtImpro61* self = k_object_new_with_private(CT_TYPE_IMPRO_6_1, sizeof(CtImpro61Private));

	return self;
}

CtImpro61* ct_impro_6_1_get(void)
{
	static CtImpro61* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_6_1, sizeof(CtImpro61Private));
	}

	return self;
}
