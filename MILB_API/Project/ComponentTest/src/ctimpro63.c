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

};


/**
 * IMPL
 */
static void ct_impro_6_3_constructor(CtImpro63 *self)
{
	CtImpro63Private *priv = CT_IMPRO_6_3_GET_PRIVATE(self);
}

static void ct_impro_6_3_destructor(CtImpro63 *self)
{
	CtImpro63Private *priv = CT_IMPRO_6_3_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_6_0_30(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    T_IM_PRO_PG_CTRL    pgCtrlMax = {
        .mode                   = E_IM_PRO_PG_MODE_2LINE,
        .inputImgLines        = 8192,
        .inputImgWidth        = 12288,
        .verticalBlanking      = 8192,
        .horizontalBlanking    = 8192,
        .startBlanking         = 16383,
    };
    T_IM_PRO_PG_CTRL    pgCtrlMin = {
        .mode                   = E_IM_PRO_PG_MODE_1LINE,
        .inputImgLines        = 2,
        .inputImgWidth        = 2,
        .verticalBlanking      = 1,
        .horizontalBlanking    = 0,
        .startBlanking         = 0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                ercd = Im_PRO_PG_Ctrl(unitNo, blockType, &pgCtrlMax);
                im_pro_6_3_print_0(NULL,"max_para", unitNo, blockType, ercd, &pgCtrlMax);

                ercd = Im_PRO_PG_Ctrl(unitNo, blockType, &pgCtrlMin);
                im_pro_6_3_print_0(NULL,"min_para", unitNo, blockType, ercd, &pgCtrlMin);
            }
        }
    }
}

void ct_im_pro_6_0_31(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar ch;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_MONI_CH_0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    ercd = Im_PRO_MONI_Start(unitNo, blockType, ch);
                    im_pro_6_3_print_1(NULL,unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_0_32(const kuint32 idx)
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
                for(ch = E_IM_PRO_MONI_CH_0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    ercd = Im_PRO_MONI_Stop(unitNo, blockType, ch, force);
                    im_pro_6_3_print_2(NULL,unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_0_33(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_MONI_CTRL  moniCtrlMax = {
        .monitorMode                       = E_IM_PRO_MONI_MODE_8POINT_INPUT,
        .hdCntExpectVal                  = 0xFFFF,
        .validPixelExpectCntIn1frame   = 0xFFFFFFFF,
        .lowerLimitExceptHBlank         = 0xFFFFFFFF,
        .upperLimitExceptHBlank         = 0xFFFFFFFF,
        .additionalHdCnt                  = 4095,
        .additionalHdGapCnt              = 0xFFFFFFFFFFFF,
    };

    T_IM_PRO_MONI_CTRL  moniCtrlMin = {
        .monitorMode                       = E_IM_PRO_MONI_MODE_2POINT_INPUT,
        .hdCntExpectVal                  = 0,
        .validPixelExpectCntIn1frame   = 0,
        .lowerLimitExceptHBlank         = 0,
        .upperLimitExceptHBlank         = 0,
        .additionalHdCnt                  = 0,
        .additionalHdGapCnt              = 0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_MONI_CH_0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    ercd = Im_PRO_MONI_Ctrl(unitNo, blockType, ch, &moniCtrlMax);
                    im_pro_6_3_print_3(NULL,"max_para", unitNo, blockType, ch, ercd, &moniCtrlMax);

                    ercd = Im_PRO_MONI_Ctrl(unitNo, blockType, ch, &moniCtrlMin);
                    im_pro_6_3_print_3(NULL,"min_para", unitNo, blockType, ch, ercd, &moniCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_0_34(const kuint32 idx)
{
    kint32                   ercd;
    E_IM_PRO_UNIT_NUM       unitNo;
    E_IM_PRO_BLOCK_TYPE     blockType;
    kuchar                   ch;
    T_IM_PRO_MONI_RESULT    moniResult;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_MONI_CH_0; ch < D_IM_PRO_SEN_MONI_CH_NUM; ch++) {
                    ercd = Im_PRO_MONI_Get_Monitor_Count(unitNo, blockType, ch, &moniResult);
                    im_pro_6_3_print_4(NULL,"max_para", unitNo, blockType, ch, ercd, &moniResult);

                    ercd = Im_PRO_MONI_Get_Monitor_Count(unitNo, blockType, ch, &moniResult);
                    im_pro_6_3_print_4(NULL,"min_para", unitNo, blockType, ch, ercd, &moniResult);
                }
            }
        }
    }
    
}

void ct_im_pro_6_0_35(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar           ch;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_M2P_0; ch < E_IM_PRO_M2P_MAX; ch++) {
                    ercd = Im_PRO_M2P_Start(unitNo, blockType, ch);
                    im_pro_6_3_print_5(NULL,unitNo, blockType, ch, ercd);
                }
            }
        }
    }
}

void ct_im_pro_6_0_36(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar           ch;
    kuchar               force = 0;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                force = blockType % 2;
                for(ch = E_IM_PRO_M2P_0; ch < E_IM_PRO_M2P_MAX; ch++) {
                    ercd = Im_PRO_M2P_Stop(unitNo, blockType, ch, force);
                    im_pro_6_3_print_6(NULL,unitNo, blockType, ch, ercd, force);
                }
            }
        }
    }
}

void ct_im_pro_6_0_37(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    T_IM_PRO_M2P_CTRL   m2pCtrlMax = {
        .dataType              = E_IM_PRO_M2P_DATA_TYPE_16BIT,
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
        .dekneeEnable          = E_IM_PRO_M2P_DEKNEE_EN_8BIT_TO_12BIT,
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
        .dekneeEnable          = E_IM_PRO_M2P_DEKNEE_EN_10BIT_TO_12BIT,
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
        .shiftBit              = E_IM_PRO_M2P_SHIFT_8BIT,
        .shiftSat              = E_IM_PRO_M2P_SAT_COMP,
        .bitShift              = E_IM_PRO_M2P_BIT_SHIFT_R,
        .validBitCount        = 16,
        .shiftValue            = 16383,
        .lowerLimitClipValue = 32767,
        .upperLimitClipValue = 65535,
    };

    T_IM_PRO_M2P_CTRL   m2pCtrlMin = {
        .dataType              = E_IM_PRO_M2P_DATA_TYPE_8BIT,
        .dekneeEnable          = E_IM_PRO_M2P_DEKNEE_DIS,
        .shiftBit              = E_IM_PRO_M2P_SHIFT_0BIT,
        .shiftSat              = E_IM_PRO_M2P_SAT_NOCOMP,
        .bitShift              = E_IM_PRO_M2P_BIT_SHIFT_L,
        .validBitCount        = 8,
        .shiftValue            = -16384,
        .lowerLimitClipValue = -32768,
        .upperLimitClipValue = 0,
    };

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_M2P_0; ch < E_IM_PRO_M2P_MAX; ch++) {
                    ercd = Im_PRO_M2P_Ctrl(unitNo, blockType, ch, &m2pCtrlMax);
                    im_pro_6_3_print_7(NULL,"max_para", unitNo, blockType, ch, ercd, &m2pCtrlMax);

                    ercd = Im_PRO_M2P_Ctrl(unitNo, blockType, ch, &m2pCtrlMin);
                    im_pro_6_3_print_7(NULL,"min_para", unitNo, blockType, ch, ercd, &m2pCtrlMin);
                }
            }
        }
    }
}

void ct_im_pro_6_0_38(const kuint32 idx)
{
    kint32               ercd;
    E_IM_PRO_UNIT_NUM   unitNo;
    E_IM_PRO_BLOCK_TYPE blockType;
    kuchar               ch;
    kuchar               paenTrg;

    if(idx == 1) {
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
                for(ch = E_IM_PRO_M2P_0; ch < E_IM_PRO_M2P_MAX; ch++) {
                    paenTrg = 1;
                    ercd = Im_PRO_M2P_Set_PAEN(unitNo, blockType, ch, paenTrg);
                    im_pro_6_3_print_8(NULL,unitNo, blockType, ch, ercd, paenTrg);

                    paenTrg = 0;
                    ercd = Im_PRO_M2P_Set_PAEN(unitNo, blockType, ch, paenTrg);
                    im_pro_6_3_print_8(NULL,unitNo, blockType, ch, ercd, paenTrg);
                }
            }
        }
    }
}

void ct_im_pro_6_0_39(const kuint32 idx)
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
        for(unitNo = E_IM_PRO_UNIT_NUM_1; unitNo < E_IM_PRO_UNIT_NUM_MAX; unitNo++) {
            for(blockType = E_IM_PRO_BLOCK_TYPE_SEN; blockType < E_IM_PRO_BLOCK_TYPE_MAX; blockType++) {
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
                    im_pro_6_3_print_9(NULL,"max_para", unitNo, blockType, ch, ercd, cmpErcd);	/* pgr0539 */

                    m2pTbl.size    = 1;
                    memset(dekneeTbl, 0, sizeof(dekneeTbl));
                    ercd = Im_PRO_M2P_Set_Table(unitNo, blockType, ch, &m2pTbl);
                    if(ercd == DdimUserCustom_E_OK) {
                        cmpErcd = memcmp((void*)m2pInfo->dkntblPtr->hword, dekneeTbl, m2pTbl.size * sizeof(kushort));
                    }  else {
                        cmpErcd = -1;
                    }
                    im_pro_6_3_print_9(NULL,"min_para", unitNo, blockType, ch, ercd, cmpErcd);	/* pgr0539 */
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
