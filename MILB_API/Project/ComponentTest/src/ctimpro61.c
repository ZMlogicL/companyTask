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

};


/**
 * IMPL
 */
static void ct_impro_6_1_constructor(CtImpro61 *self)
{
	CtImpro61Private *priv = CT_IMPRO_6_1_GET_PRIVATE(self);
}

static void ct_impro_6_1_destructor(CtImpro61 *self)
{
	CtImpro61Private *priv = CT_IMPRO_6_1_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_6_0_10(const kuint32 idx)
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
                for(ch = E_IM_PRO_PWCH_0; ch < E_IM_PRO_PWCH_MAX; ch++) {
                    ercd = Im_PRO_PWch_Ctrl_Axi(unitNo, blockType, ch, &axiCtrlMax);
                    im_pro_6_1_print_0("max_para", unitNo, blockType, ch, ercd, &axiCtrlMax);

                    ercd = Im_PRO_PWch_Ctrl_Axi(unitNo, blockType, ch, &axiCtrlMin);
                    im_pro_6_1_print_0("min_para", unitNo, blockType, ch, ercd, &axiCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_0_11(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_PWCH_INFO  pwchInfoMax = {
        .bufferNum     =8,
        .buffAddr[0]   =0x40000000,
        .buffAddr[1]   =0x50000000,
        .buffAddr[2]   =0x60000000,
        .buffAddr[3]   =0x70000000,
        .buffAddr[4]   =0x80000000,
        .buffAddr[5]   =0x90000000,
        .buffAddr[6]   =0xA0000000,
        .buffAddr[7]   =0xB0000000,
    };

    T_IM_PRO_PWCH_INFO  pwchInfoMin = {
        .bufferNum     =1,
        .buffAddr[0]   =0x40000000,
        .buffAddr[1]   =0,
        .buffAddr[2]   =0,
        .buffAddr[3]   =0,
        .buffAddr[4]   =0,
        .buffAddr[5]   =0,
        .buffAddr[6]   =0,
        .buffAddr[7]   =0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PWCH_0; ch < E_IM_PRO_PWCH_MAX; ch++) {
                    ercd = Im_PRO_PWch_Set_Buf_Addr(unitNo, blockType, ch, &pwchInfoMax);
                    im_pro_6_1_print_1("max_para", unitNo, blockType, ch, ercd);

                    ercd = Im_PRO_PWch_Set_Buf_Addr(unitNo, blockType, ch, &pwchInfoMin);
                    im_pro_6_1_print_1("min_para", unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_0_12(const kuint32 idx)
{
    kulong               bufAddr;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PWCH_0; ch < E_IM_PRO_PWCH_MAX; ch++) {
                    bufAddr = Im_PRO_PWch_Get_Buf_Data(unitNo, blockType, ch);
                    DriverCommon_DDIM_PRINT(("Im_PRO_PWch_Get_Buf_Data(%u %u %u) BufAddr    (0x%lx)\n", 
                    unitNo, blockType, ch, bufAddr));
                }
            }
        }
    }
}

void ct_im_pro_6_0_13(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_PWCH_INFO  pwchInfoMax = {
        .bufferNum     =8,
        .buffAddr[0]   =0x40000000,
        .buffAddr[1]   =0x50000000,
        .buffAddr[2]   =0x60000000,
        .buffAddr[3]   =0x70000000,
        .buffAddr[4]   =0x80000000,
        .buffAddr[5]   =0x90000000,
        .buffAddr[6]   =0xA0000000,
        .buffAddr[7]   =0xB0000000,
    };
    kuint32              bufIdx;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PWCH_0; ch < E_IM_PRO_PWCH_MAX; ch++) {
                    Im_PRO_PWch_Set_Buf_Addr(unitNo, blockType, ch, &pwchInfoMax);
                    for(bufIdx = 0; bufIdx < D_IM_PRO_PWCH_BUFFER_MAX; bufIdx++) {
                        ercd = Im_PRO_PWch_Update_Buf_Index(unitNo, blockType, ch);
                        im_pro_6_1_print_3(bufIdx, unitNo, blockType, ch, ercd);
                    }
                }
            }
        }
    }
}

void ct_im_pro_6_0_14(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kulong               lineFeed;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PWCH_0; ch < E_IM_PRO_PWCH_MAX; ch++) {
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

void ct_im_pro_6_0_15(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kuchar               axiResponse;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PWCH_0; ch < E_IM_PRO_PWCH_MAX; ch++) {
                    ercd = Im_PRO_PWch_Get_AXI_Response(unitNo, blockType, ch, &axiResponse);
                    im_pro_6_1_print_5(unitNo, blockType, ch, ercd, axiResponse);
                }
            }
        }
    }
}

void ct_im_pro_6_0_16(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_LNR_CH_0; ch < D_IM_PRO_SEN_LNR_CH_NUM; ch++) {
                    ercd = Im_PRO_LNR_Start(unitNo, blockType, ch);
                    im_pro_6_1_print_6(unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_0_17(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;
    kuchar               force = 0;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                force = blockType % 2;
                for(ch = E_IM_PRO_LNR_CH_0; ch < D_IM_PRO_SEN_LNR_CH_NUM; ch++) {
                    ercd = Im_PRO_LNR_Stop(unitNo, blockType, ch, force);
                    im_pro_6_0_print_2(unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_0_18(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_LNR_CTRL   lnrCtrlMax = {
        .lnrBr[0]      = 16383,
        .lnrBr[1]      = 16383,
        .lnrBr[2]      = 16383,
        .lnrBr[3]      = 16383,
        .lnrBr[4]      = 16383,
        .lnrBr[5]      = 16383,
        .lnrBr[6]      = 16383,
        .lnrIncr[0]    = 1023,
        .lnrIncr[1]    = 1023,
        .lnrIncr[2]    = 1023,
        .lnrIncr[3]    = 1023,
        .lnrIncr[4]    = 1023,
        .lnrIncr[5]    = 1023,
        .lnrIncr[6]    = 1023,
        .lnrIncr[7]    = 1023,
        .lnrOfsr[0]    = 16383,
        .lnrOfsr[1]    = 16383,
        .lnrOfsr[2]    = 16383,
        .lnrOfsr[3]    = 16383,
        .lnrOfsr[4]    = 16383,
        .lnrOfsr[5]    = 16383,
        .lnrOfsr[6]    = 16383,
        .lnrOfsr[7]    = 16383,
        .lnrBgr[0]     = 16383,
        .lnrBgr[1]     = 16383,
        .lnrBgr[2]     = 16383,
        .lnrBgr[3]     = 16383,
        .lnrBgr[4]     = 16383,
        .lnrBgr[5]     = 16383,
        .lnrBgr[6]     = 16383,
        .lnrIncgr[0]   = 1023,
        .lnrIncgr[1]   = 1023,
        .lnrIncgr[2]   = 1023,
        .lnrIncgr[3]   = 1023,
        .lnrIncgr[4]   = 1023,
        .lnrIncgr[5]   = 1023,
        .lnrIncgr[6]   = 1023,
        .lnrIncgr[7]   = 1023,
        .lnrOfsgr[0]   = 16383,
        .lnrOfsgr[1]   = 16383,
        .lnrOfsgr[2]   = 16383,
        .lnrOfsgr[3]   = 16383,
        .lnrOfsgr[4]   = 16383,
        .lnrOfsgr[5]   = 16383,
        .lnrOfsgr[6]   = 16383,
        .lnrOfsgr[7]   = 16383,
        .lnrBgb[0]     = 16383,
        .lnrBgb[1]     = 16383,
        .lnrBgb[2]     = 16383,
        .lnrBgb[3]     = 16383,
        .lnrBgb[4]     = 16383,
        .lnrBgb[5]     = 16383,
        .lnrBgb[6]     = 16383,
        .lnrIncgb[0]   = 1023,
        .lnrIncgb[1]   = 1023,
        .lnrIncgb[2]   = 1023,
        .lnrIncgb[3]   = 1023,
        .lnrIncgb[4]   = 1023,
        .lnrIncgb[5]   = 1023,
        .lnrIncgb[6]   = 1023,
        .lnrIncgb[7]   = 1023,
        .lnrOfsgb[0]   = 1023,
        .lnrOfsgb[1]   = 1023,
        .lnrOfsgb[2]   = 1023,
        .lnrOfsgb[3]   = 1023,
        .lnrOfsgb[4]   = 1023,
        .lnrOfsgb[5]   = 1023,
        .lnrOfsgb[6]   = 1023,
        .lnrOfsgb[7]   = 1023,
        .lnrBb[0]      = 16383,
        .lnrBb[1]      = 16383,
        .lnrBb[2]      = 16383,
        .lnrBb[3]      = 16383,
        .lnrBb[4]      = 16383,
        .lnrBb[5]      = 16383,
        .lnrBb[6]      = 16383,
        .lnrIncb[0]    = 1023,
        .lnrIncb[1]    = 1023,
        .lnrIncb[2]    = 1023,
        .lnrIncb[3]    = 1023,
        .lnrIncb[4]    = 1023,
        .lnrIncb[5]    = 1023,
        .lnrIncb[6]    = 1023,
        .lnrIncb[7]    = 1023,
        .lnrOfsb[0]    = 16383,
        .lnrOfsb[1]    = 16383,
        .lnrOfsb[2]    = 16383,
        .lnrOfsb[3]    = 16383,
        .lnrOfsb[4]    = 16383,
        .lnrOfsb[5]    = 16383,
        .lnrOfsb[6]    = 16383,
        .lnrOfsb[7]    = 16383,
    };

    T_IM_PRO_LNR_CTRL   lnrCtrlMin = {
        .lnrBr[0]      = 0,
        .lnrBr[1]      = 0,
        .lnrBr[2]      = 0,
        .lnrBr[3]      = 0,
        .lnrBr[4]      = 0,
        .lnrBr[5]      = 0,
        .lnrBr[6]      = 0,
        .lnrIncr[0]    = 0,
        .lnrIncr[1]    = 0,
        .lnrIncr[2]    = 0,
        .lnrIncr[3]    = 0,
        .lnrIncr[4]    = 0,
        .lnrIncr[5]    = 0,
        .lnrIncr[6]    = 0,
        .lnrIncr[7]    = 0,
        .lnrOfsr[0]    = 0,
        .lnrOfsr[1]    = 0,
        .lnrOfsr[2]    = 0,
        .lnrOfsr[3]    = 0,
        .lnrOfsr[4]    = 0,
        .lnrOfsr[5]    = 0,
        .lnrOfsr[6]    = 0,
        .lnrOfsr[7]    = 0,
        .lnrBgr[0]     = 0,
        .lnrBgr[1]     = 0,
        .lnrBgr[2]     = 0,
        .lnrBgr[3]     = 0,
        .lnrBgr[4]     = 0,
        .lnrBgr[5]     = 0,
        .lnrBgr[6]     = 0,
        .lnrIncgr[0]   = 0,
        .lnrIncgr[1]   = 0,
        .lnrIncgr[2]   = 0,
        .lnrIncgr[3]   = 0,
        .lnrIncgr[4]   = 0,
        .lnrIncgr[5]   = 0,
        .lnrIncgr[6]   = 0,
        .lnrIncgr[7]   = 0,
        .lnrOfsgr[0]   = 0,
        .lnrOfsgr[1]   = 0,
        .lnrOfsgr[2]   = 0,
        .lnrOfsgr[3]   = 0,
        .lnrOfsgr[4]   = 0,
        .lnrOfsgr[5]   = 0,
        .lnrOfsgr[6]   = 0,
        .lnrOfsgr[7]   = 0,
        .lnrBgb[0]     = 0,
        .lnrBgb[1]     = 0,
        .lnrBgb[2]     = 0,
        .lnrBgb[3]     = 0,
        .lnrBgb[4]     = 0,
        .lnrBgb[5]     = 0,
        .lnrBgb[6]     = 0,
        .lnrIncgb[0]   = 0,
        .lnrIncgb[1]   = 0,
        .lnrIncgb[2]   = 0,
        .lnrIncgb[3]   = 0,
        .lnrIncgb[4]   = 0,
        .lnrIncgb[5]   = 0,
        .lnrIncgb[6]   = 0,
        .lnrIncgb[7]   = 0,
        .lnrOfsgb[0]   = 0,
        .lnrOfsgb[1]   = 0,
        .lnrOfsgb[2]   = 0,
        .lnrOfsgb[3]   = 0,
        .lnrOfsgb[4]   = 0,
        .lnrOfsgb[5]   = 0,
        .lnrOfsgb[6]   = 0,
        .lnrOfsgb[7]   = 0,
        .lnrBb[0]      = 0,
        .lnrBb[1]      = 0,
        .lnrBb[2]      = 0,
        .lnrBb[3]      = 0,
        .lnrBb[4]      = 0,
        .lnrBb[5]      = 0,
        .lnrBb[6]      = 0,
        .lnrIncb[0]    = 0,
        .lnrIncb[1]    = 0,
        .lnrIncb[2]    = 0,
        .lnrIncb[3]    = 0,
        .lnrIncb[4]    = 0,
        .lnrIncb[5]    = 0,
        .lnrIncb[6]    = 0,
        .lnrIncb[7]    = 0,
        .lnrOfsb[0]    = 0,
        .lnrOfsb[1]    = 0,
        .lnrOfsb[2]    = 0,
        .lnrOfsb[3]    = 0,
        .lnrOfsb[4]    = 0,
        .lnrOfsb[5]    = 0,
        .lnrOfsb[6]    = 0,
        .lnrOfsb[7]    = 0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_LNR_CH_0; ch < D_IM_PRO_SEN_LNR_CH_NUM; ch++) {
                    ercd = Im_PRO_LNR_Ctrl(unitNo, blockType, ch, &lnrCtrlMax);
                    im_pro_6_1_print_8("max_para", unitNo, blockType, ch, ercd, &lnrCtrlMax);

                    ercd = Im_PRO_LNR_Ctrl(unitNo, blockType, ch, &lnrCtrlMin);
                    im_pro_6_1_print_8("min_para", unitNo, blockType, ch, ercd, &lnrCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_0_19(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    const T_IM_PRO_RDMA_LNR_ADDR*   addr;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
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
