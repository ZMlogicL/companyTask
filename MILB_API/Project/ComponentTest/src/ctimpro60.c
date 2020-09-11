/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro60
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro60.h"
#include "impro6print.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImpro60, ct_impro_6_0)
#define CT_IMPRO_6_0_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro60Private, CT_TYPE_IMPRO_6_0))


struct _CtImpro60Private
{

};


static void ct_impro_6_0_constructor(CtImpro60 *self)
{
	CtImpro60Private *priv = CT_IMPRO_6_0_GET_PRIVATE(self);
}

static void ct_impro_6_0_destructor(CtImpro60 *self)
{
	CtImpro60Private *priv = CT_IMPRO_6_0_GET_PRIVATE(self);
}

#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_6_0_1(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_P2M_CH0; ch < E_IM_PRO_P2M_MAX; ch++) {
                    ercd = Im_PRO_P2M_Start(unitNo, blockType, ch);
                    im_pro_6_0_print_1(NULL,unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_0_2(const kuint32 idx)
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
                for(ch = E_IM_PRO_P2M_CH0; ch < E_IM_PRO_P2M_MAX; ch++) {
                    ercd = Im_PRO_P2M_Stop(unitNo, blockType, ch, force);
                    im_pro_6_0_print_2(NULL,unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_0_3(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_P2M_CTRL   p2mCtrlMax = {
        .kneeEnable    = E_IM_PRO_P2M_KNEE_EN_12BIT_TO_10BIT,
        .lpfMode       = E_IM_PRO_P2M_LPF_MODE_LONG,
        .recMode       = E_IM_PRO_P2M_REC_MODE_16BIT,
        .shiftValue    = 16383,
        .shiftBit      = E_IM_PRO_P2M_SHIFT_8BIT,
        .clipValue     = 65535,
        .startY        = 8191,
        .startX        = 12287,
        .height         = 8192,
        .width          = 12288,
        .verticalThin  = 63,
        .horizonThin   = 63,
        .sampleLine    = 0xFFFFFFFFFFFFFFFF,
        .sampleWidth   = 0xFFFFFFFFFFFFFFFF,
        .enableMirror  = E_IM_PRO_P2M_MIRROR_ENABLE_EN,
        .inputMode     = E_IM_PRO_P2M_INPUT_MODE_1POINT,
    };

    T_IM_PRO_P2M_CTRL   p2mCtrlMin = {
        .kneeEnable    = E_IM_PRO_P2M_KNEE_DIS,
        .lpfMode       = E_IM_PRO_P2M_LPF_MODE_OFF,
        .recMode       = E_IM_PRO_P2M_REC_MODE_8BIT,
        .shiftValue    = -16384,
        .shiftBit      = E_IM_PRO_P2M_SHIFT_0BIT,
        .clipValue     = 0,
        .startY        = 0,
        .startX        = 0,
        .height         = 1,
        .width          = 1,
        .verticalThin  = 1,
        .horizonThin   = 1,
        .sampleLine    = 0,
        .sampleWidth   = 0,
        .enableMirror  = E_IM_PRO_P2M_MIRROR_ENABLE_DIS,
        .inputMode     = E_IM_PRO_P2M_INPUT_MODE_1POINT,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_P2M_CH0; ch < E_IM_PRO_P2M_MAX; ch++) {
                    ercd = Im_PRO_P2M_Ctrl(unitNo, blockType, ch, &p2mCtrlMax);
                    im_pro_6_0_print_3(NULL,"max_para", unitNo, blockType, ch, ercd, &p2mCtrlMax);

                    ercd = Im_PRO_P2M_Ctrl(unitNo, blockType, ch, &p2mCtrlMin);
                    im_pro_6_0_print_3(NULL,"min_para", unitNo, blockType, ch, ercd, &p2mCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_0_4(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kuchar               paenTrg;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_P2M_CH0; ch < E_IM_PRO_P2M_MAX; ch++) {
                    paenTrg = 1;
                    ercd = Im_PRO_P2M_Set_PAEN(unitNo, blockType, ch, paenTrg);
                    im_pro_6_0_print_4(NULL,unitNo, blockType, ch, ercd, paenTrg);

                    paenTrg = 0;
                    ercd = Im_PRO_P2M_Set_PAEN(unitNo, blockType, ch, paenTrg);
                    im_pro_6_0_print_4(NULL,unitNo, blockType, ch, ercd, paenTrg);
                }
            }
        }
    }
}

void ct_im_pro_6_0_5(const kuint32 idx)
{
    kint32               ercd;
    kint32               cmpErcd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_P2M_TABLE  p2mTbl;
    USHORT              kneeTbl[257];
    const T_IM_PRO_COMMON_P2M_INFO* p2mInfo;

    p2mTbl.pp2m_tbl    = kneeTbl;
    p2mTbl.size        = 257;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_P2M_CH0; ch < E_IM_PRO_P2M_MAX; ch++) {

                    im_pro_comm_get_p2m_reg_info(unitNo, blockType, ch, &p2mInfo);
                    p2mTbl.size        = 257;
                    memset(kneeTbl, 1023, sizeof(kneeTbl));
                    ercd = Im_PRO_P2M_Set_Table(unitNo, blockType, ch, &p2mTbl);
                    if(ercd == DdimUserCustom_E_OK) {
                        cmpErcd = memcmp((void*)&p2mInfo->kntblPtr->hword, kneeTbl, p2mTbl.size * sizeof(USHORT));
                    } else {
                        cmpErcd = -1;
                    }
                    im_pro_6_0_print_5(NULL,"max_para", unitNo, blockType, ch, ercd, cmpErcd);	/* pgr0539 */

                    p2mTbl.size        = 1;
                    memset(kneeTbl, 0, sizeof(kneeTbl));
                    ercd = Im_PRO_P2M_Set_Table(unitNo, blockType, ch, &p2mTbl);
                    if(ercd == DdimUserCustom_E_OK) {
                        cmpErcd = memcmp((void*)&p2mInfo->kntblPtr->hword, kneeTbl, p2mTbl.size * sizeof(USHORT));
                    } else {
                        cmpErcd = -1;
                    }
                    im_pro_6_0_print_5(NULL,"min_para", unitNo, blockType, ch, ercd, cmpErcd);	/* pgr0539 */
                }
            }
        }
    }
}

void ct_im_pro_6_0_6(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    const T_IM_PRO_RDMA_P2M_KNEE_TBL_ADDR*  addr;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_P2M_CH0; ch < E_IM_PRO_P2M_MAX; ch++) {
                    ercd = Im_PRO_Get_RdmaAddr_P2M_Knee_Tbl(unitNo, blockType, ch, &addr);
                    im_pro_6_0_print_6(NULL,unitNo, blockType, ch, ercd, &addr);
                }
            }
        }
    }
}

void ct_im_pro_6_0_7(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PWCH_0; ch < E_IM_PRO_PWCH_MAX; ch++) {
                    ercd = Im_PRO_PWch_Start(unitNo, blockType, ch);
                    im_pro_6_0_print_7(NULL,unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_0_8(const kuint32 idx)
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
                for(ch = E_IM_PRO_PWCH_0; ch < E_IM_PRO_PWCH_MAX; ch++) {
                    ercd = Im_PRO_PWch_Stop(unitNo, blockType, ch, force);
                    im_pro_6_0_print_8(NULL,unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_0_9(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_PWCH_CTRL  pwchCtrlMax = {
        .transTo          = E_IM_PRO_PWCH_TRANS_IO_0,
        .reqThreshold     = E_IM_PRO_PWCH_CNT_NOLIMIT2,
        .writeMask        = E_IM_PRO_PWCH_WRITE_MASK_EN,
        .burstAlignSize  = E_IM_PRO_PWCH_BURST_ALIGN_SIZE_128BYTE,
        .outputFormat     = E_IM_PRO_PWCH_OUTPUT_FORMAT_VIDEO,
    };

    T_IM_PRO_PWCH_CTRL  pwchCtrlMin = {
        .transTo          = E_IM_PRO_PWCH_TRANS_IO_0,
        .reqThreshold     = E_IM_PRO_PWCH_CNT_NOLIMIT,
        .writeMask        = E_IM_PRO_PWCH_WRITE_MASK_DIS,
        .burstAlignSize  = E_IM_PRO_PWCH_BURST_ALIGN_SIZE_32BYTE,
        .outputFormat     = E_IM_PRO_PWCH_OUTPUT_FORMAT_NORMAL,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_PWCH_0; ch < E_IM_PRO_PWCH_MAX; ch++) {
                    ercd = Im_PRO_PWch_Ctrl(unitNo, blockType, ch, &pwchCtrlMax);
                    im_pro_6_0_print_9(NULL,"max_para", unitNo, blockType, ch, ercd, &pwchCtrlMax);

                    ercd = Im_PRO_PWch_Ctrl(unitNo, blockType, ch, &pwchCtrlMin);
                    im_pro_6_0_print_9(NULL,"min_para", unitNo, blockType, ch, ercd, &pwchCtrlMin);
                }
            }
        }
    }
}
#endif

CtImpro60* ct_impro_6_0_new(void)
{
	CtImpro60* self = k_object_new_with_private(CT_TYPE_IMPRO_6_0, sizeof(CtImpro60Private));

	return self;
}

CtImpro60* ct_impro_6_0_get(void)
{
	static CtImpro60* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_6_0, sizeof(CtImpro60Private));
	}

	return self;
}
