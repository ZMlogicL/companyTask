/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro63
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro63.h"
#include "impro6print.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImpro63, ct_impro_6_3)
#define CT_IMPRO_6_3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro63Private, CT_TYPE_IMPRO_6_3))


struct _CtImpro63Private
{
    T_IM_PRO_PG_CTRL    pgCtrlMax;
    T_IM_PRO_PG_CTRL    pgCtrlMin;
    T_IM_PRO_MONI_CTRL  moniCtrlMax;
    T_IM_PRO_MONI_CTRL  moniCtrlMin;
    T_IM_PRO_M2P_CTRL   m2pCtrlMax;
    T_IM_PRO_M2P_CTRL   m2pCtrlMin;

};


/**
 * IMPL
 */
static void ct_impro_6_3_constructor(CtImpro63 *self)
{
	CtImpro63Private *priv = CT_IMPRO_6_3_GET_PRIVATE(self);

        priv->pgCtrlMax.mode                   = E_IM_PRO_PG_MODE_2LINE;
        priv->pgCtrlMax.inputImgLines        = 8192;
        priv->pgCtrlMax.inputImgWidth        = 12288;
        priv->pgCtrlMax.verticalBlanking      = 8192;
        priv->pgCtrlMax.horizontalBlanking    = 8192;
        priv->pgCtrlMax.startBlanking         = 16383;

        priv->pgCtrlMin.mode                   = E_IM_PRO_PG_MODE_1LINE;
        priv->pgCtrlMin.inputImgLines        = 2;
        priv->pgCtrlMin.inputImgWidth        = 2;
        priv->pgCtrlMin.verticalBlanking      = 1;
        priv->pgCtrlMin.horizontalBlanking    = 0;
        priv->pgCtrlMin.startBlanking         = 0;

        priv->moniCtrlMax.monitorMode                       = E_IM_PRO_MONI_MODE_8POINT_INPUT;
        priv->moniCtrlMax.hdCntExpectVal                  = 0xFFFF;
        priv->moniCtrlMax.validPixelExpectCntIn1frame   = 0xFFFFFFFF;
        priv->moniCtrlMax.lowerLimitExceptHBlank         = 0xFFFFFFFF;
        priv->moniCtrlMax.upperLimitExceptHBlank         = 0xFFFFFFFF;
        priv->moniCtrlMax.additionalHdCnt                  = 4095;
        priv->moniCtrlMax.additionalHdGapCnt              = 0xFFFFFFFFFFFF;

        priv->monitorMode.monitorMode                       = E_IM_PRO_MONI_MODE_2POINT_INPUT;
        priv->monitorMode.hdCntExpectVal                  = 0;
        priv->monitorMode.validPixelExpectCntIn1frame   = 0;
        priv->monitorMode.lowerLimitExceptHBlank         = 0;
        priv->monitorMode.upperLimitExceptHBlank         = 0;
        priv->monitorMode.additionalHdCnt                  = 0;
        priv->monitorMode.additionalHdGapCnt              = 0;

        priv->m2pCtrlMax.dataType              = E_IM_PRO_M2P_DATA_TYPE_16BIT;
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
        priv->m2pCtrlMax.dekneeEnable          = E_IM_PRO_M2P_DEKNEE_EN_8BIT_TO_12BIT;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
        priv->m2pCtrlMax.dekneeEnable          = E_IM_PRO_M2P_DEKNEE_EN_10BIT_TO_12BIT;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
        priv->m2pCtrlMax.shiftBit              = E_IM_PRO_M2P_SHIFT_8BIT;
        priv->m2pCtrlMax.shiftSat              = E_IM_PRO_M2P_SAT_COMP;
        priv->m2pCtrlMax.bitShift              = E_IM_PRO_M2P_BIT_SHIFT_R;
        priv->m2pCtrlMax.validBitCount        = 16;
        priv->m2pCtrlMax.shiftValue            = 16383;
        priv->m2pCtrlMax.lowerLimitClipValue = 32767;
        priv->m2pCtrlMax.upperLimitClipValue = 65535;

        priv->m2pCtrlMin.dataType              = E_IM_PRO_M2P_DATA_TYPE_8BIT;
        priv->m2pCtrlMin.dekneeEnable          = E_IM_PRO_M2P_DEKNEE_DIS;
        priv->m2pCtrlMin.shiftBit              = E_IM_PRO_M2P_SHIFT_0BIT;
        priv->m2pCtrlMin.shiftSat              = E_IM_PRO_M2P_SAT_NOCOMP;
        priv->m2pCtrlMin.bitShift              = E_IM_PRO_M2P_BIT_SHIFT_L;
        priv->m2pCtrlMin.validBitCount        = 8;
        priv->m2pCtrlMin.shiftValue            = -16384;
        priv->m2pCtrlMin.lowerLimitClipValue = -32768;
        priv->m2pCtrlMin.upperLimitClipValue = 0;
}

static void ct_impro_6_3_destructor(CtImpro63 *self)
{
	CtImpro63Private *priv = CT_IMPRO_6_3_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_6_3_0(CtImpro63* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                ercd = Im_PRO_PG_Ctrl(unitNo, blockType, &priv->pgCtrlMax);
                im_pro_6_3_print_0(im_pro_6_3_print_get(),"max_para", unitNo, blockType, ercd, &priv->pgCtrlMax);

                ercd = Im_PRO_PG_Ctrl(unitNo, blockType, &priv->pgCtrlMin);
                im_pro_6_3_print_0(im_pro_6_3_print_get(),"min_para", unitNo, blockType, ercd, &priv->pgCtrlMin);
            }
        }
    }
}

void ct_im_pro_6_3_1(CtImpro63* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_MONI_CH_0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    ercd = Im_PRO_MONI_Start(unitNo, blockType, ch);
                    im_pro_6_3_print_1(im_pro_6_3_print_get(),unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_3_2(CtImpro63* self, const kuint32 idx)
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
                for(ch = E_IM_PRO_MONI_CH_0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    ercd = Im_PRO_MONI_Stop(unitNo, blockType, ch, force);
                    im_pro_6_3_print_2(im_pro_6_3_print_get(),unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_3_3(CtImpro63* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    
    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_MONI_CH_0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    ercd = Im_PRO_MONI_Ctrl(unitNo, blockType, ch, &priv->moniCtrlMax);
                    im_pro_6_3_print_3(im_pro_6_3_print_get(),"max_para", unitNo, blockType, ch, ercd, &priv->moniCtrlMax);

                    ercd = Im_PRO_MONI_Ctrl(unitNo, blockType, ch, &priv->moniCtrlMin);
                    im_pro_6_3_print_3(im_pro_6_3_print_get(),"min_para", unitNo, blockType, ch, ercd, &priv->moniCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_3_4(CtImpro63* self, const kuint32 idx)
{
    kint32                   ercd;
    E_IM_PRO_UNIT_NUM       unitNo;
    E_IM_PRO_BLOCK_TYPE     blockType;
    kuchar                   ch;
    T_IM_PRO_MONI_RESULT    moniResult;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_MONI_CH_0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    ercd = Im_PRO_MONI_Get_Monitor_Count(unitNo, blockType, ch, &moniResult);
                    im_pro_6_3_print_4(im_pro_6_3_print_get(),"max_para", unitNo, blockType, ch, ercd, &moniResult);

                    ercd = Im_PRO_MONI_Get_Monitor_Count(unitNo, blockType, ch, &moniResult);
                    im_pro_6_3_print_4(im_pro_6_3_print_get(),"min_para", unitNo, blockType, ch, ercd, &moniResult);
                }
            }
        }
    }
    
}

void ct_im_pro_6_3_5(CtImpro63* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar           ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_M2P_0; ch < E_IM_PRO_M2P_MAX; ch++) {
                    ercd = Im_PRO_M2P_Start(unitNo, blockType, ch);
                    im_pro_6_3_print_5(im_pro_6_3_print_get(),unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_3_6(CtImpro63* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar           ch;
    kuchar               force = 0;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                force = blockType % 2;
                for(ch = E_IM_PRO_M2P_0; ch < E_IM_PRO_M2P_MAX; ch++) {
                    ercd = Im_PRO_M2P_Stop(unitNo, blockType, ch, force);
                    im_pro_6_3_print_6(im_pro_6_3_print_get(),unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_3_7(CtImpro63* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_M2P_0; ch < E_IM_PRO_M2P_MAX; ch++) {
                    ercd = Im_PRO_M2P_Ctrl(unitNo, blockType, ch, &priv->m2pCtrlMax);
                    im_pro_6_3_print_7(im_pro_6_3_print_get(),"max_para", unitNo, blockType, ch, ercd, &priv->m2pCtrlMax);

                    ercd = Im_PRO_M2P_Ctrl(unitNo, blockType, ch, &priv->m2pCtrlMin);
                    im_pro_6_3_print_7(im_pro_6_3_print_get(),"min_para", unitNo, blockType, ch, ercd, &priv->m2pCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_3_8(CtImpro63* self, const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kuchar               paenTrg;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_M2P_0; ch < E_IM_PRO_M2P_MAX; ch++) {
                    paenTrg = 1;
                    ercd = Im_PRO_M2P_Set_PAEN(unitNo, blockType, ch, paenTrg);
                    im_pro_6_3_print_8(im_pro_6_3_print_get(),unitNo, blockType, ch, ercd, paenTrg);

                    paenTrg = 0;
                    ercd = Im_PRO_M2P_Set_PAEN(unitNo, blockType, ch, paenTrg);
                    im_pro_6_3_print_8(im_pro_6_3_print_get(),unitNo, blockType, ch, ercd, paenTrg);
                }
            }
        }
    }
}

void ct_im_pro_6_3_9(CtImpro63* self, const kuint32 idx)
{
    kint32               ercd;
    kint32               cmpErcd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_M2P_TABLE  m2pTbl;
    kushort               dekneeTbl[256];
    const T_IM_PRO_COMMON_M2P_INFO* m2pInfo;

    m2pTbl.pm2pTbl    = dekneeTbl;

    if(idx == 1) {
        for(unitNo = ImPro_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = ImPro_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_M2P_0; ch < E_IM_PRO_M2P_MAX; ch++) {
                    im_pro_comm_get_m2p_reg_info(unitNo, blockType, ch, &m2pInfo);

                    m2pTbl.size    = 256;
                    memset(dekneeTbl, 4095, sizeof(dekneeTbl));
                    ercd = Im_PRO_M2P_Set_Table(unitNo, blockType, ch, &m2pTbl);
                    if(ercd == DdimUserCustom_E_OK) {
                        cmpErcd = memcmp((void*)m2pInfo->dkntblPtr->hword, dekneeTbl, m2pTbl.size * sizeof(kushort));
                    } else {
                        cmpErcd = -1;
                    }
                    im_pro_6_3_print_9(im_pro_6_3_print_get(),"max_para", unitNo, blockType, ch, ercd, cmpErcd);	/* pgr0539 */

                    m2pTbl.size    = 1;
                    memset(dekneeTbl, 0, sizeof(dekneeTbl));
                    ercd = Im_PRO_M2P_Set_Table(unitNo, blockType, ch, &m2pTbl);
                    if(ercd == DdimUserCustom_E_OK) {
                        cmpErcd = memcmp((void*)m2pInfo->dkntblPtr->hword, dekneeTbl, m2pTbl.size * sizeof(kushort));
                    }  else {
                        cmpErcd = -1;
                    }
                    im_pro_6_3_print_9(im_pro_6_3_print_get(),"min_para", unitNo, blockType, ch, ercd, cmpErcd);	/* pgr0539 */
                }
            }
        }
    }
}
#endif

CtImpro63* ct_impro_6_3_new(void)
{
	CtImpro63* self = k_object_new_with_private(CT_TYPE_IMPRO_6_3, sizeof(CtImpro63Private));

	return self;
}

CtImpro63* ct_impro_6_3_get(void)
{
	static CtImpro63* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_6_3, sizeof(CtImpro63Private));
	}

	return self;
}
