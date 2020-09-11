/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro73
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro73.h"
#include "impro7print.h"
#include "improdebug.h"
#include "improcallback.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImpro73, ct_impro_7_3)
#define CT_IMPRO_7_3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro73Private, CT_TYPE_IMPRO_7_3))


struct _CtImpro73Private
{

};


/**
 *IMPL
 */
static void ct_impro_7_3_constructor(CtImpro73 *self)
{
	CtImpro73Private *priv = CT_IMPRO_7_3_GET_PRIVATE(self);
}

static void ct_impro_7_3_destructor(CtImpro73 *self)
{
	CtImpro73Private *priv = CT_IMPRO_7_3_GET_PRIVATE(self);
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_30(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    T_IM_PRO_INT_CFG intCtrl = {
        .interruptBit = 0,
        .permissionFlg = 0,
    };

    if(idx == 1) {
        for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
            intCtrl.permissionFlg = permissionFlg;

            intCtrl.interruptBit = (D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE7_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE6_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE5_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE4_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE3_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE2_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE1_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE0_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE7_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE6_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE5_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE4_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE3_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE2_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE1_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE0_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE7_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE6_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE5_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE4_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE3_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE2_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE1_BIT |
                                    D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE0_BIT);

#ifdef CO_DEBUG_ON_PC
            ioPro.sen.sentop.sgvhdintflg.word = 0xFFFFFFFF;
#endif  // CO_DEBUG_ON_PC
            ercd = Im_PRO_SLVS_Set_Common_Interrupt(&intCtrl);
            im_pro_7_30_Print(NULL,ercd, &intCtrl, permissionFlg);
        }
    }
}

void ct_im_pro_7_31(const kuint32 idx)
{
    kint32 ercd;
    kulong userParam;
    TImProCallbackCfg intCtrlMax = {
        .inthandler = im_pro_callback_sen_slvs_common_int_cb,
        .userParam = 0,
    };

    if(idx == 1) {
        for(userParam = 0; userParam < 4; userParam++) {
            intCtrlMax.userParam = userParam;
            ercd = Im_PRO_SLVS_Set_Common_Int_Handler(&intCtrlMax);
            im_pro_7_31_Print(NULL,"", ercd, &intCtrlMax);
        }
    }
}

void ct_im_pro_7_32(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    E_IM_PRO_SLVS_STREAM_TYPE streamType;
    T_IM_PRO_INT_CFG intCtrl = {
        .interruptBit = 0,
        .permissionFlg = 0,
    };

    if(idx == 1) {
        for(streamType = 0; streamType < E_IM_PRO_SLVS_STREAM_TYPE_BOTH; streamType++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                intCtrl.permissionFlg = permissionFlg;

                intCtrl.interruptBit = (D_IM_PRO_SLVS_INTEN_FSI_BIT |
                                        D_IM_PRO_SLVS_INTEN_FSO_BIT |
                                        D_IM_PRO_SLVS_INTEN_FEI_BIT |
                                        D_IM_PRO_SLVS_INTEN_FEO_BIT |
                                        D_IM_PRO_SLVS_INTEN_RDY_BIT |
                                        D_IM_PRO_SLVS_INTEN_STBY_BIT);
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.slvsec.stream[streamType].intst.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC
                ercd = Im_PRO_SLVS_Set_Interrupt(streamType, E_IM_PRO_SLVS_INT_TYPE_INTN_O, &intCtrl);
                im_pro_7_32_Print(NULL,ercd, streamType, E_IM_PRO_SLVS_INT_TYPE_INTN_O, &intCtrl, permissionFlg);

                intCtrl.interruptBit = (D_IM_PRO_SLVS_LEINTEN_LBOVF_BIT |
                                        D_IM_PRO_SLVS_LEINTEN_LNE_BIT  |
                                        D_IM_PRO_SLVS_LEINTEN_ECCE_BIT |
                                        D_IM_PRO_SLVS_LEINTEN_ECC2C_BIT |
                                        D_IM_PRO_SLVS_LEINTEN_ECC1C_BIT |
                                        D_IM_PRO_SLVS_LEINTEN_HCRCE_BIT |
                                        D_IM_PRO_SLVS_LEINTEN_HCRC2C_BIT |
                                        D_IM_PRO_SLVS_LEINTEN_HCRC1C_BIT |
                                        D_IM_PRO_SLVS_LEINTEN_PCRCE_BIT |
                                        D_IM_PRO_SLVS_LEINTEN_LLE_BIT);
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.slvsec.stream[streamType].intst.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC
                ercd = Im_PRO_SLVS_Set_Interrupt(streamType, E_IM_PRO_SLVS_INT_TYPE_LINK_ERR, &intCtrl);
                im_pro_7_32_Print(NULL,ercd, streamType, E_IM_PRO_SLVS_INT_TYPE_LINK_ERR, &intCtrl, permissionFlg);

                intCtrl.interruptBit = (D_IM_PRO_SLVS_MEINTEN0_DSD_BIT |
                                        D_IM_PRO_SLVS_MEINTEN0_DCL_BIT |
                                        D_IM_PRO_SLVS_MEINTEN0_SCL_BIT |
                                        D_IM_PRO_SLVS_MEINTEN0_ECL_BIT);
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.slvsec.stream[streamType].intst.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC
                ercd = Im_PRO_SLVS_Set_Interrupt(streamType, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR1, &intCtrl);
                im_pro_7_32_Print(NULL,ercd, streamType, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR1, &intCtrl, permissionFlg);

                intCtrl.interruptBit = (D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE7_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE6_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE5_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE4_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE3_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE2_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE1_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE0_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE7_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE6_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE5_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE4_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE3_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE2_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE1_BIT |
                                        D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE0_BIT);
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.slvsec.stream[streamType].intst.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC
                ercd = Im_PRO_SLVS_Set_Interrupt(streamType, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2, &intCtrl);
                im_pro_7_32_Print(NULL,ercd, streamType, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2, &intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_33(const kuint32 idx)
{
    kint32 ercd;
    E_IM_PRO_SLVS_STREAM_TYPE streamType;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(streamType = 0; streamType < E_IM_PRO_SLVS_STREAM_TYPE_BOTH; streamType++) {
            for(userParam = 0; userParam < 4; userParam++) {
                intCtrl.inthandler = im_pro_callback_sen_slvs_intn_o_int_cb;
                intCtrl.userParam = userParam;
                ercd = Im_PRO_SLVS_Set_Int_Handler(streamType, E_IM_PRO_SLVS_INT_TYPE_INTN_O, &intCtrl);
                im_pro_7_33_Print(NULL,"", streamType, E_IM_PRO_SLVS_INT_TYPE_INTN_O, ercd, &intCtrl);

                intCtrl.inthandler = im_pro_callback_sen_slvs_link_err_int_cb;
                intCtrl.userParam = userParam;
                ercd = Im_PRO_SLVS_Set_Int_Handler(streamType, E_IM_PRO_SLVS_INT_TYPE_LINK_ERR, &intCtrl);
                im_pro_7_33_Print(NULL,"", streamType, E_IM_PRO_SLVS_INT_TYPE_LINK_ERR, ercd, &intCtrl);

                intCtrl.inthandler = im_pro_callback_sen_slvs_mac_err1_int_cb;
                intCtrl.userParam = userParam;
                ercd = Im_PRO_SLVS_Set_Int_Handler(streamType, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR1, &intCtrl);
                im_pro_7_33_Print(NULL,"", streamType, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR1, ercd, &intCtrl);

                intCtrl.inthandler = im_pro_callback_sen_slvs_mac_err2_int_cb;
                intCtrl.userParam = userParam;
                ercd = Im_PRO_SLVS_Set_Int_Handler(streamType, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2, &intCtrl);
                im_pro_7_33_Print(NULL,"", streamType, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2, ercd, &intCtrl);
            }
        }
    }
}

void ct_im_pro_7_34(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;
    T_IM_PRO_INT_LVDS_CTRL intCtrl = {
        .lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_NORNAL].interruptBit = 0,
        .lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_NORNAL].permissionFlg = 0,
        .lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL1].interruptBit = 0,
        .lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL1].permissionFlg = 0,
        .lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL2].interruptBit = 0,
        .lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL2].permissionFlg = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_LVDS_CH_NUM; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                intCtrl.lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_NORNAL].permissionFlg = permissionFlg;
                intCtrl.lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL1].permissionFlg = permissionFlg;
                intCtrl.lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL2].permissionFlg = permissionFlg;

                intCtrl.lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_NORNAL].interruptBit = 
                (D_IM_PRO_LVDSINTENB_SOFE0 | D_IM_PRO_LVDSINTENB_EOFE0 |
                   D_IM_PRO_LVDSINTENB_SOLE0 | D_IM_PRO_LVDSINTENB_EOLE0);
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.lvds[ch].lvdsintflg0.word = intCtrl.lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_NORNAL].interruptBit;
#endif  // CO_DEBUG_ON_PC

                intCtrl.lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL1].interruptBit = (D_IM_PRO_LVDSINTENB_SOFE1 |
                                                                                                D_IM_PRO_LVDSINTENB_EOFE1 |
                                                                                                D_IM_PRO_LVDSINTENB_SOLE1 |
                                                                                                D_IM_PRO_LVDSINTENB_EOLE1);
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.lvds[ch].lvdsintflg1.word = intCtrl.lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL1].interruptBit;
#endif  // CO_DEBUG_ON_PC

                intCtrl.lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL2].interruptBit = (D_IM_PRO_LVDSINTENB_SOFE2 |
                                                                                                D_IM_PRO_LVDSINTENB_EOFE2 |
                                                                                                D_IM_PRO_LVDSINTENB_SOLE2 |
                                                                                                D_IM_PRO_LVDSINTENB_EOLE2);
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.lvds[ch].lvdsintflg2.word = intCtrl.lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL2].interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_LVDS_Set_Interrupt(ch, &intCtrl);
                im_pro_7_34_Print(NULL,ercd, ch, &intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_35(const kuint32 idx)
{
    kint32 ercd;
    kuchar ch;
    E_IM_PRO_LVDS_OUTPUT_MODE   dolMode;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_LVDS_CH_NUM; ch++) {
            for(dolMode = E_IM_PRO_LVDS_OUTPUT_MODE_NORNAL; dolMode < E_IM_PRO_LVDS_OUTPUT_MODE_MAX; dolMode++) {
                for(userParam = 0; userParam < 4; userParam++) {
                    intCtrl.inthandler = im_pro_callback_sen_lvds_int_cb;
                    intCtrl.userParam = userParam;
                    ercd = Im_PRO_LVDS_Set_Int_Handler(ch, dolMode, &intCtrl);
                    im_pro_7_35_Print(NULL,"", ch, ercd, &intCtrl);
                }
            }
        }
    }
}

void ct_im_pro_7_36(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;
    T_IM_PRO_INT_CFG intCtrl = {
        .interruptBit = 0,
        .permissionFlg = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_DMIPI_CH_NUM; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                intCtrl.permissionFlg = permissionFlg;

                intCtrl.interruptBit = (D_IM_PRO_MPIINTE_DEC3 |
                                        D_IM_PRO_MPIINTE_DEC2 |
                                        D_IM_PRO_MPIINTE_DEC1 |
                                        D_IM_PRO_MPIINTE_DEC0 |
                                        D_IM_PRO_MPIINTE_DEE3 |
                                        D_IM_PRO_MPIINTE_DEE2 |
                                        D_IM_PRO_MPIINTE_DEE1 |
                                        D_IM_PRO_MPIINTE_DEE0 |
                                        D_IM_PRO_MPIINTE_DESSH3 |
                                        D_IM_PRO_MPIINTE_DESSH2 |
                                        D_IM_PRO_MPIINTE_DESSH1 |
                                        D_IM_PRO_MPIINTE_DESSH0 |
                                        D_IM_PRO_MPIINTE_DESHE3 |
                                        D_IM_PRO_MPIINTE_DESHE2 |
                                        D_IM_PRO_MPIINTE_DESHE1 |
                                        D_IM_PRO_MPIINTE_DESHE0 |
                                        D_IM_PRO_MPIINTE_FEO1 |
                                        D_IM_PRO_MPIINTE_FEO0 |
                                        D_IM_PRO_MPIINTE_FEI1 |
                                        D_IM_PRO_MPIINTE_FEI0 |
                                        D_IM_PRO_MPIINTE_FSO1 |
                                        D_IM_PRO_MPIINTE_FSO0 |
                                        D_IM_PRO_MPIINTE_FSI1 |
                                        D_IM_PRO_MPIINTE_FSI0 |
                                        D_IM_PRO_MPIINTE_LZE3 |
                                        D_IM_PRO_MPIINTE_LZE2 |
                                        D_IM_PRO_MPIINTE_LZE1 |
                                        D_IM_PRO_MPIINTE_LZE0 |
                                        D_IM_PRO_MPIINTE_EFS |
                                        D_IM_PRO_MPIINTE_CRCE |
                                        D_IM_PRO_MPIINTE_ECCW |
                                        D_IM_PRO_MPIINTE_ECCE);
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.mipid[ch].mpiintf.word = intCtrl.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_DMIPI_Set_Interrupt(ch, &intCtrl);
                im_pro_7_36_Print(NULL,ercd, ch, &intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_37(const kuint32 idx)
{
    kint32 ercd;
    kuchar ch;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_DMIPI_CH_NUM; ch++) {
            for(userParam = 0; userParam < 4; userParam++) {
                intCtrl.inthandler = im_pro_callback_sen_dmipi_int_cb;
                intCtrl.userParam = userParam;
                ercd = Im_PRO_DMIPI_Set_Int_Handler(ch, &intCtrl);
                im_pro_7_37_Print(NULL,"", ch, ercd, &intCtrl);
            }
        }
    }
}

void ct_im_pro_7_38(const kuint32 idx)
{
    kint32 ercd;
    kuchar permissionFlg;
    kuchar ch;
    T_IM_PRO_INT_CMIPI_CTRL intCtrl = {
        .cmipiInt1Enable.interruptBit = 0,
        .cmipiInt1Enable.permissionFlg = 0,
        .cmipiInt2Enable.interruptBit = 0,
        .cmipiInt2Enable.permissionFlg = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_CMIPI_CH_NUM; ch++) {
            for(permissionFlg = 0; permissionFlg < 2; permissionFlg++) {
                intCtrl.cmipiInt1Enable.permissionFlg = permissionFlg;
                intCtrl.cmipiInt2Enable.permissionFlg = permissionFlg;

                intCtrl.cmipiInt1Enable.interruptBit = (D_IM_PRO_MPICINTE1_CEC2 |
                                                        D_IM_PRO_MPICINTE1_CEC1 |
                                                        D_IM_PRO_MPICINTE1_CEC0 |
                                                        D_IM_PRO_MPICINTE1_CEE2 |
                                                        D_IM_PRO_MPICINTE1_CEE1 |
                                                        D_IM_PRO_MPICINTE1_CEE0 |
                                                        D_IM_PRO_MPICINTE1_CESSH2 |
                                                        D_IM_PRO_MPICINTE1_CESSH1 |
                                                        D_IM_PRO_MPICINTE1_CESSH0 |
                                                        D_IM_PRO_MPICINTE1_CESH2 |
                                                        D_IM_PRO_MPICINTE1_CESH1 |
                                                        D_IM_PRO_MPICINTE1_CESH0 |
                                                        D_IM_PRO_MPICINTE1_FEO1 |
                                                        D_IM_PRO_MPICINTE1_FEO0 |
                                                        D_IM_PRO_MPICINTE1_FEI1 |
                                                        D_IM_PRO_MPICINTE1_FEI0 |
                                                        D_IM_PRO_MPICINTE1_FSO1 |
                                                        D_IM_PRO_MPICINTE1_FSO0 |
                                                        D_IM_PRO_MPICINTE1_FSI1 |
                                                        D_IM_PRO_MPICINTE1_FSI0 |
                                                        D_IM_PRO_MPICINTE1_LZE2 |
                                                        D_IM_PRO_MPICINTE1_LZE1 |
                                                        D_IM_PRO_MPICINTE1_LZE0 |
                                                        D_IM_PRO_MPICINTE1_EFS |
                                                        D_IM_PRO_MPICINTE1_CRCDTE |
                                                        D_IM_PRO_MPICINTE1_PHCRC2E |
                                                        D_IM_PRO_MPICINTE1_PHCRC1E);
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.mipic[ch].mpicintf1.word = intCtrl.cmipiInt1Enable.interruptBit;
#endif  // CO_DEBUG_ON_PC

                intCtrl.cmipiInt2Enable.interruptBit = (D_IM_PRO_MPICINTE2_CICHSE2 |
                                                        D_IM_PRO_MPICINTE2_CICHSE1 |
                                                        D_IM_PRO_MPICINTE2_CICHSE0 |
                                                        D_IM_PRO_MPICINTE2_PHCRCAEE);
#ifdef CO_DEBUG_ON_PC
                ioPro.sen.mipic[ch].mpicintf2.word = intCtrl.cmipiInt2Enable.interruptBit;
#endif  // CO_DEBUG_ON_PC

                ercd = Im_PRO_CMIPI_Set_Interrupt(ch, &intCtrl);
                im_pro_7_38_Print(NULL,ercd, ch, &intCtrl, permissionFlg);
            }
        }
    }
}

void ct_im_pro_7_39(const kuint32 idx)
{
    kint32 ercd;
    kuchar ch;
    kuchar                   cate;
    kulong userParam;
    TImProCallbackCfg intCtrl = {
        .inthandler = NULL,
        .userParam = 0,
    };

    if(idx == 1) {
        for(ch = 0; ch < D_IM_PRO_SEN_CMIPI_CH_NUM; ch++) {
            for(cate = E_IM_PRO_CMIPI_INT_CATE_0; cate < E_IM_PRO_CMIPI_INT_CATE_1 + 1; cate++) {
                for(userParam = 0; userParam < 4; userParam++) {
                    intCtrl.inthandler = im_pro_callback_sen_cmipi_int_cb;
                    intCtrl.userParam = userParam;
                    ercd = Im_PRO_CMIPI_Set_Int_Handler(ch, cate, &intCtrl);
                    im_pro_7_39_Print(NULL,"", ch, cate, ercd, &intCtrl);
                }
            }
        }
    }
}
#endif

CtImpro73* ct_impro_7_3_new(void)
{
	CtImpro73* self = k_object_new_with_private(CT_TYPE_IMPRO_7_3, sizeof(CtImpro73Private));

	return self;
}

CtImpro73* ct_impro_7_3_get(void)
{
	static CtImpro73* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_7_3, sizeof(CtImpro73Private));
	}

	return self;
}
