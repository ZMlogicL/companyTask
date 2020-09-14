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
        T_IM_PRO_P2M_CTRL   p2mCtrlMax;
        T_IM_PRO_P2M_CTRL   p2mCtrlMin;
        T_IM_PRO_PWCH_CTRL  pwchCtrlMax;
        T_IM_PRO_PWCH_CTRL  pwchCtrlMin;
};


static void ct_impro_6_0_constructor(CtImpro60 *self)
{
	CtImpro60Private *priv = CT_IMPRO_6_0_GET_PRIVATE(self);

    priv->p2mCtrlMax.kneeEnable    = ImProP2m_KNEE_EN_12BIT_TO_10BIT;
    priv->p2mCtrlMax.lpfMode       = ImProP2m_LPF_MODE_LONG;
    priv->p2mCtrlMax.recMode       = ImProP2m_REC_MODE_16BIT;
    priv->p2mCtrlMax.shiftValue    = 16383;
    priv->p2mCtrlMax.shiftBit      = ImProP2m_SHIFT_8BIT;
    priv->p2mCtrlMax.clipValue     = 65535;
    priv->p2mCtrlMax.startY        = 8191;
    priv->p2mCtrlMax.startX        = 12287;
    priv->p2mCtrlMax.height         = 8192;
    priv->p2mCtrlMax.width          = 12288;
    priv->p2mCtrlMax.verticalThin  = 63;
    priv->p2mCtrlMax.horizonThin   = 63;
    priv->p2mCtrlMax.sampleLine    = 0xFFFFFFFFFFFFFFFF;
    priv->p2mCtrlMax.sampleWidth   = 0xFFFFFFFFFFFFFFFF;
    priv->p2mCtrlMax.enableMirror  = ImProP2m_MIRROR_ENABLE_EN;
    priv->p2mCtrlMax.inputMode     = ImProP2m_INPUT_MODE_1POINT;

    priv->p2mCtrlMin.kneeEnable    = ImProP2m_KNEE_DIS;
    priv->p2mCtrlMin.lpfMode       = ImProP2m_LPF_MODE_OFF;
    priv->p2mCtrlMin.recMode       = ImProP2m_REC_MODE_8BIT;
    priv->p2mCtrlMin.shiftValue    = -16384;
    priv->p2mCtrlMin.shiftBit      = ImProP2m_SHIFT_0BIT;
    priv->p2mCtrlMin.clipValue     = 0;
    priv->p2mCtrlMin.startY        = 0;
    priv->p2mCtrlMin.startX        = 0;
    priv->p2mCtrlMin.height         = 1;
    priv->p2mCtrlMin.width          = 1;
    priv->p2mCtrlMin.verticalThin  = 1;
    priv->p2mCtrlMin.horizonThin   = 1;
    priv->p2mCtrlMin.sampleLine    = 0;  
    priv->p2mCtrlMin.sampleWidth   = 0;
    priv->p2mCtrlMin.enableMirror  = ImProP2m_MIRROR_ENABLE_DIS;
    priv->p2mCtrlMin.inputMode     = ImProP2m_INPUT_MODE_1POINT;

    priv->pwchCtrlMax.transTo          = ImProPwch_TRANS_IO_0;
    priv->pwchCtrlMax.reqThreshold     = ImProPwch_CNT_NOLIMIT2;
    priv->pwchCtrlMax.writeMask        = ImProPwch_WRITE_MASK_EN;
    priv->pwchCtrlMax.burstAlignSize  = ImProPwch_BURST_ALIGN_SIZE_128BYTE;
    priv->pwchCtrlMax.outputFormat     = ImProPwch_OUTPUT_FORMAT_VIDEO;

    priv->pwchCtrlMin.transTo          = ImProPwch_TRANS_IO_0;
    priv->pwchCtrlMin.reqThreshold     = ImProPwch_CNT_NOLIMIT;
    priv->pwchCtrlMin.writeMask        = ImProPwch_WRITE_MASK_DIS;
    priv->pwchCtrlMin.burstAlignSize  = ImProPwch_BURST_ALIGN_SIZE_32BYTE;
    priv->pwchCtrlMin.outputFormat     = ImProPwch_OUTPUT_FORMAT_NORMAL;
}

static void ct_impro_6_0_destructor(CtImpro60 *self)
{
	CtImpro60Private *priv = CT_IMPRO_6_0_GET_PRIVATE(self);
}

#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_6_0_1(CtImpro60* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProP2m_CH0; ch < ImProP2m_MAX; ch++) {
                    ercd = im_pro_pommon_list_p2m_start(unitNo, blockType, ch);
                    im_pro_6_0_print_1(im_pro_6_0_print_get(), unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_0_2(CtImpro60* self, const kuint32 idx)
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
                for(ch = ImProP2m_CH0; ch < ImProP2m_MAX; ch++) {
                    ercd = im_pro_pommon_list_p2m_stop(unitNo, blockType, ch, force);
                    im_pro_6_0_print_2(im_pro_6_0_print_get(), unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_0_3(CtImpro60* self, const kuint32 idx)
{
    CtImpro60Private *priv = CT_IMPRO_6_0_GET_PRIVATE(self);
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProP2m_CH0; ch < ImProP2m_MAX; ch++) {
                    ercd = im_pro_pommon_list_p2m_ctrl(unitNo, blockType, ch, &priv->p2mCtrlMax);
                    im_pro_6_0_print_3(im_pro_6_0_print_get(), "max_para", 
                    unitNo, blockType, ch, ercd, &priv->p2mCtrlMax);

                    ercd = im_pro_pommon_list_p2m_ctrl(unitNo, blockType, ch, &priv->p2mCtrlMin);
                    im_pro_6_0_print_3(im_pro_6_0_print_get(), "min_para", 
                    unitNo, blockType, ch, ercd, &priv->p2mCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_0_4(CtImpro60* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kuchar               paenTrg;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProP2m_CH0; ch < ImProP2m_MAX; ch++) {
                    paenTrg = 1;
                    ercd = im_pro_pommon_list_p2m_set_paen(unitNo, blockType, ch, paenTrg);
                    im_pro_6_0_print_4(im_pro_6_0_print_get(), unitNo, blockType, ch, ercd, paenTrg);

                    paenTrg = 0;
                    ercd = im_pro_pommon_list_p2m_set_paen(unitNo, blockType, ch, paenTrg);
                    im_pro_6_0_print_4(im_pro_6_0_print_get(), unitNo, blockType, ch, ercd, paenTrg);
                }
            }
        }
    }
}

void ct_im_pro_6_0_5(CtImpro60* self, const kuint32 idx)
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
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProP2m_CH0; ch < ImProP2m_MAX; ch++) {

                    im_pro_comm_get_p2m_reg_info(unitNo, blockType, ch, &p2mInfo);
                    p2mTbl.size        = 257;
                    memset(kneeTbl, 1023, sizeof(kneeTbl));
                    ercd = im_pro_pommon_list_p2m_set_table(unitNo, blockType, ch, &p2mTbl);
                    if(ercd == DdimUserCustom_E_OK) {
                        cmpErcd = memcmp((void*)&p2mInfo->kntblPtr->hword, kneeTbl, p2mTbl.size * sizeof(USHORT));
                    } else {
                        cmpErcd = -1;
                    }
                    im_pro_6_0_print_5(im_pro_6_0_print_get(), "max_para", unitNo, blockType, 
                    ch, ercd, cmpErcd);	/* pgr0539 */

                    p2mTbl.size        = 1;
                    memset(kneeTbl, 0, sizeof(kneeTbl));
                    ercd = im_pro_pommon_list_p2m_set_table(unitNo, blockType, ch, &p2mTbl);
                    if(ercd == DdimUserCustom_E_OK) {
                        cmpErcd = memcmp((void*)&p2mInfo->kntblPtr->hword, kneeTbl, p2mTbl.size * sizeof(USHORT));
                    } else {
                        cmpErcd = -1;
                    }
                    im_pro_6_0_print_5(im_pro_6_0_print_get(), "min_para", unitNo, blockType, 
                    ch, ercd, cmpErcd);	/* pgr0539 */
                }
            }
        }
    }
}

void ct_im_pro_6_0_6(CtImpro60* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    const T_IM_PRO_RDMA_P2M_KNEE_TBL_ADDR*  addr;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProP2m_CH0; ch < ImProP2m_MAX; ch++) {
                    ercd = Im_PRO_Get_RdmaAddr_P2M_Knee_Tbl(unitNo, blockType, ch, &addr);
                    im_pro_6_0_print_6(im_pro_6_0_print_get(),unitNo, blockType, ch, ercd, &addr);
                }
            }
        }
    }
}

void ct_im_pro_6_0_7(CtImpro60* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProPwch_0; ch < ImProPwch_MAX; ch++) {
                    ercd = im_pro_pommon_list_pwch_start(unitNo, blockType, ch);
                    im_pro_6_0_print_7(im_pro_6_0_print_get(), unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_0_8(CtImpro60* self, const kuint32 idx)
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
                for(ch = ImProPwch_0; ch < ImProPwch_MAX; ch++) {
                    ercd = im_pro_pommon_list_pwch_stop(unitNo, blockType, ch, force);
                    im_pro_6_0_print_8(im_pro_6_0_print_get(), unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_0_9(CtImpro60* self, const kuint32 idx)
{
	CtImpro60Private *priv = CT_IMPRO_6_0_GET_PRIVATE(self);
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = ImProPwch_0; ch < ImProPwch_MAX; ch++) {
                    ercd = Im_PRO_PWch_Ctrl(unitNo, blockType, ch, &priv->pwchCtrlMax);
                    im_pro_6_0_print_9(im_pro_6_0_print_get(),"max_para", 
                    unitNo, blockType, ch, ercd, &priv->pwchCtrlMax);

                    ercd = Im_PRO_PWch_Ctrl(unitNo, blockType, ch, &priv->pwchCtrlMin);
                    im_pro_6_0_print_9(im_pro_6_0_print_get(),"min_para", 
                    unitNo, blockType, ch, ercd, &priv->pwchCtrlMin);
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
