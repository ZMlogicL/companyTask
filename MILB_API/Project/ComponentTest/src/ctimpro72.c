/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : CtImpro72
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro72.h"
#include "impro7print.h"
#include "improdebug.h"
#include "improcallback.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImpro72, ct_impro_7_2)
#define CT_IMPRO_7_2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImpro72Private, CT_TYPE_IMPRO_7_2))


struct _CtImpro72Private
{

};


/**
 * IMPL
 */
static void ct_impro_7_2_constructor(CtImpro72 *self)
{
	CtImpro72Private *priv = CT_IMPRO_7_2_GET_PRIVATE(self);
}

static void ct_impro_7_2_destructor(CtImpro72 *self)
{
	CtImpro72Private *priv = CT_IMPRO_7_2_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_7_20(const kuint32 idx)
{
}

void ct_im_pro_7_21(const kuint32 idx)
{
    kint32 ercd;
    kulong userParam;
    TImProCallbackCfg intCtrlMax = {
        .inthandler = im_pro_callback_sen_vd_int_cb,
        .userParam = 0,
    };

    if(idx == 1) {
        for(userParam = 0; userParam < 4; userParam++) {
            intCtrlMax.userParam = userParam;
            ercd = interrupt_sen_set_vd_int_handler(&intCtrlMax);
            im_pro_7_21_Print(NULL,"", ercd, &intCtrlMax);
        }
    }
}

void ct_im_pro_7_22(const kuint32 idx)
{
    kint32 ercd;
    kulong userParam;
    TImProCallbackCfg intCtrlMax = {
        .inthandler = im_pro_callback_sen_hd_int_cb,
        .userParam = 0,
    };

    if(idx == 1) {
        for(userParam = 0; userParam < 4; userParam++) {
            intCtrlMax.userParam = userParam;
            ercd = Im_PRO_SEN_Set_HD_Int_Handler(&intCtrlMax);
            im_pro_7_22_Print(NULL,"", ercd, &intCtrlMax);
        }
    }
}

void ct_im_pro_7_23(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32  loopcnt;
    kuint32  chLoopcnt;
    kuint32  inte = 0;
    kuint32  intf = 0;
    inte = (D_IM_PRO_PWCHINTENB_PWE | D_IM_PRO_PWCHINTENB_PWEE | D_IM_PRO_PWCHINTENB_PWXE);
    intf = (D_IM_PRO_PWCHINTFLG_PWF | D_IM_PRO_PWCHINTFLG_PWEF | D_IM_PRO_PWCHINTFLG_PWXF);
    for(chLoopcnt = 0; chLoopcnt < E_IM_PRO_PWCH_MAX; chLoopcnt++) {
        im_pro_debug_pwch_intflg_fill(im_pro_debug_get(),0, 0, chLoopcnt, inte, intf);
    }

    inte = D_IM_PRO_LDIVINTENB_LDIVEE;
    intf = D_IM_PRO_LDIVINTFLG_LDIVEF;
    for(chLoopcnt = 0; chLoopcnt < D_IM_PRO_SEN_LDIV_NUM; chLoopcnt++) {
        im_pro_debug_ldiv_intflg_fill(im_pro_debug_get(),chLoopcnt, inte, intf);
    }

    for(loopcnt = 0; loopcnt < D_IM_PRO_SENTOP_BLOB_NUM; loopcnt++) {
        for(chLoopcnt = 0; chLoopcnt < D_IM_PRO_SEN_OBD_CH_NUM; chLoopcnt++) {
            inte = D_IM_PRO_OBDINTENB_OBDE;
            intf = D_IM_PRO_OBDINTFLG_OBDF;
            im_pro_debug_obd_intflg_fill(im_pro_debug_get(),loopcnt, chLoopcnt, inte, intf);

            inte = D_IM_PRO_OBTINTENB_OBTE;
            intf = D_IM_PRO_OBTINTFLG_OBTF;
            im_pro_debug_obt_intflg_fill(im_pro_debug_get(),loopcnt, chLoopcnt, inte, intf);

            ioPro.sen.obd[loopcnt][chLoopcnt].obdcore.obddatar.bit.obddatar = 0xFFFFFFFF;
            ioPro.sen.obd[loopcnt][chLoopcnt].obdcore.obddatagr.bit.obddatagr = 0xFFFFFFFF;
            ioPro.sen.obd[loopcnt][chLoopcnt].obdcore.obddatagb.bit.obddatagb = 0xFFFFFFFF;
            ioPro.sen.obd[loopcnt][chLoopcnt].obdcore.obddatab.bit.obddatab = 0xFFFFFFFF;
            ioPro.sen.obd[loopcnt][chLoopcnt].obdcore.obdcntr.bit.obdcntr = 0xFFFFF;
            ioPro.sen.obd[loopcnt][chLoopcnt].obdcore.obdcntgr.bit.obdcntgr = 0xFFFFF;
            ioPro.sen.obd[loopcnt][chLoopcnt].obdcore.obdcntgb.bit.obdcntgb = 0xFFFFF;
            ioPro.sen.obd[loopcnt][chLoopcnt].obdcore.obdcntb.bit.obdcntb = 0xFFFFF;

            ioPro.sen.obt[loopcnt][chLoopcnt].obtcore.obtdatar.bit.obtdatar = 0x3FFF;
            ioPro.sen.obt[loopcnt][chLoopcnt].obtcore.obtdatagr.bit.obtdatagr = 0x3FFF;
            ioPro.sen.obt[loopcnt][chLoopcnt].obtcore.obtdatagb.bit.obtdatagb = 0x3FFF;
            ioPro.sen.obt[loopcnt][chLoopcnt].obtcore.obtdatab.bit.obtdatab = 0x3FFF;
        }
    }

#endif  // CO_DEBUG_ON_PC
    Im_PRO_SEN_Int_Handler();
}

void ct_im_pro_7_24(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32  inte = (D_IM_PRO_INT_VDE00 | 
                    D_IM_PRO_INT_VDE01 |
                    D_IM_PRO_INT_VDE10 |
                    D_IM_PRO_INT_VDE11 |
                    D_IM_PRO_INT_VDE20 |
                    D_IM_PRO_INT_VDE21 |
                    D_IM_PRO_INT_VDE30 |
                    D_IM_PRO_INT_VDE31);

    kuint32  intf = (D_IM_PRO_INT_VDF00 |
                    D_IM_PRO_INT_VDF01 |
                    D_IM_PRO_INT_VDF10 |
                    D_IM_PRO_INT_VDF11 |
                    D_IM_PRO_INT_VDF20 |
                    D_IM_PRO_INT_VDF21 |
                    D_IM_PRO_INT_VDF30 |
                    D_IM_PRO_INT_VDF31);

    kuint32  sgInte = (D_IM_PRO_INT_SGVDE0 |
                      D_IM_PRO_INT_SGVDE1 |
                      D_IM_PRO_INT_SGVDE2 |
                      D_IM_PRO_INT_SGVDE3);

    kuint32  sgIntf = (D_IM_PRO_INT_SGVDF0 |
                      D_IM_PRO_INT_SGVDF1 |
                      D_IM_PRO_INT_SGVDF2 |
                      D_IM_PRO_INT_SGVDF3);

    kuint32  gyroInte = (D_IM_PRO_INT_GYRO_SOFE0 |
                        D_IM_PRO_INT_GYRO_SOFE1 |
                        D_IM_PRO_INT_GYRO_SOFE2 |
                        D_IM_PRO_INT_GYRO_SOFE3 |
                        D_IM_PRO_INT_GYRO_EOFE0 |
                        D_IM_PRO_INT_GYRO_EOFE1 |
                        D_IM_PRO_INT_GYRO_EOFE2 |
                        D_IM_PRO_INT_GYRO_EOFE3);

    kuint32  gyroIntf = (D_IM_PRO_INT_GYRO_SOFF0 |
                        D_IM_PRO_INT_GYRO_SOFF1 |
                        D_IM_PRO_INT_GYRO_SOFF2 |
                        D_IM_PRO_INT_GYRO_SOFF3 |
                        D_IM_PRO_INT_GYRO_EOFF0 |
                        D_IM_PRO_INT_GYRO_EOFF1 |
                        D_IM_PRO_INT_GYRO_EOFF2 |
                        D_IM_PRO_INT_GYRO_EOFF3);

    im_pro_debug_sentop_vd_intflg_fill(im_pro_debug_get(),inte, intf, sgInte, sgIntf, gyroInte, gyroIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_SEN_VD_Int_Handler();
}

void ct_im_pro_7_25(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32  inte = (D_IM_PRO_INT_HDE00 |
                    D_IM_PRO_INT_HDE01 |
                    D_IM_PRO_INT_HDE10 |
                    D_IM_PRO_INT_HDE11 |
                    D_IM_PRO_INT_HDE20 |
                    D_IM_PRO_INT_HDE21 |
                    D_IM_PRO_INT_HDE30 |
                    D_IM_PRO_INT_HDE31);

    kuint32  intf = (D_IM_PRO_INT_HDF00 |
                    D_IM_PRO_INT_HDF01 |
                    D_IM_PRO_INT_HDF10 |
                    D_IM_PRO_INT_HDF11 |
                    D_IM_PRO_INT_HDF20 |
                    D_IM_PRO_INT_HDF21 |
                    D_IM_PRO_INT_HDF30 |
                    D_IM_PRO_INT_HDF31);

    kuint32  sgInte = (D_IM_PRO_INT_SGHDE0 |
                     D_IM_PRO_INT_SGHDE1 |
                     D_IM_PRO_INT_SGHDE2 |
                     D_IM_PRO_INT_SGHDE3);

    kuint32  sgIntf = (D_IM_PRO_INT_SGHDF0 |
                     D_IM_PRO_INT_SGHDF1 |
                     D_IM_PRO_INT_SGHDF2 |
                     D_IM_PRO_INT_SGHDF3);
                                
    im_pro_debug_sentop_hd_intflg_fill(im_pro_debug_get(),inte, intf, sgInte, sgIntf);
#endif  // CO_DEBUG_ON_PC
    Im_PRO_SEN_HD_Int_Handler();
}

void ct_im_pro_7_26(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 slvsCommInte = (D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE7_BIT |
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

    kuint32 slvsCommIntf = (D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE7_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE6_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE5_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE4_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE3_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE2_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE1_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE0_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE7_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE6_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE5_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE4_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE3_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE2_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE1_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE0_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE7_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE6_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE5_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE4_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE3_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE2_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE1_BIT |
                            D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE0_BIT);

    kuint32 slvsInte = (D_IM_PRO_SLVS_INTEN_FSI_BIT |
                        D_IM_PRO_SLVS_INTEN_FSO_BIT |
                        D_IM_PRO_SLVS_INTEN_FEI_BIT |
                        D_IM_PRO_SLVS_INTEN_FEO_BIT |
                        D_IM_PRO_SLVS_INTEN_RDY_BIT |
                        D_IM_PRO_SLVS_INTEN_STBY_BIT);

    kuint32 slvsIntf = (D_IM_PRO_SLVS_INTST_FSI_BIT |
                        D_IM_PRO_SLVS_INTST_FSO_BIT |
                        D_IM_PRO_SLVS_INTST_FEI_BIT |
                        D_IM_PRO_SLVS_INTST_FEO_BIT |
                        D_IM_PRO_SLVS_INTST_RDY_BIT |
                        D_IM_PRO_SLVS_INTST_STBY_BIT);

    kuint32 slvsLeinte = (D_IM_PRO_SLVS_LEINTEN_LBOVF_BIT |
                        D_IM_PRO_SLVS_LEINTEN_LNE_BIT  |
                        D_IM_PRO_SLVS_LEINTEN_ECCE_BIT |
                        D_IM_PRO_SLVS_LEINTEN_ECC2C_BIT |
                        D_IM_PRO_SLVS_LEINTEN_ECC1C_BIT |
                        D_IM_PRO_SLVS_LEINTEN_HCRCE_BIT |
                        D_IM_PRO_SLVS_LEINTEN_HCRC2C_BIT |
                        D_IM_PRO_SLVS_LEINTEN_HCRC1C_BIT |
                        D_IM_PRO_SLVS_LEINTEN_PCRCE_BIT |
                        D_IM_PRO_SLVS_LEINTEN_LLE_BIT);
                                    
    kuint32 slvsLeintf = (D_IM_PRO_SLVS_LEINTST_LBOVF_BIT |
                        D_IM_PRO_SLVS_LEINTST_LNE_BIT  |
                        D_IM_PRO_SLVS_LEINTST_ECCE_BIT |
                        D_IM_PRO_SLVS_LEINTST_ECC2C_BIT |
                        D_IM_PRO_SLVS_LEINTST_ECC1C_BIT |
                        D_IM_PRO_SLVS_LEINTST_HCRCE_BIT |
                        D_IM_PRO_SLVS_LEINTST_HCRC2C_BIT |
                        D_IM_PRO_SLVS_LEINTST_HCRC1C_BIT |
                        D_IM_PRO_SLVS_LEINTST_PCRCE_BIT |
                        D_IM_PRO_SLVS_LEINTST_LLE_BIT);

    kuint32 slvsMeinte0 = (D_IM_PRO_SLVS_MEINTEN0_DSD_BIT |
                            D_IM_PRO_SLVS_MEINTEN0_DCL_BIT |
                            D_IM_PRO_SLVS_MEINTEN0_SCL_BIT |
                            D_IM_PRO_SLVS_MEINTEN0_ECL_BIT);

    kuint32 slvsMeintf0 = (D_IM_PRO_SLVS_MEINTST0_DSD_BIT |
                            D_IM_PRO_SLVS_MEINTST0_DCL_BIT |
                            D_IM_PRO_SLVS_MEINTST0_SCL_BIT |
                            D_IM_PRO_SLVS_MEINTST0_ECL_BIT);

    kuint32 slvsMeinte1 = (D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE7_BIT |
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

    kuint32 slvsMeintf1 = (D_IM_PRO_SLVS_MEINTST1_FUNF_LANE7_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FUNF_LANE6_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FUNF_LANE5_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FUNF_LANE4_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FUNF_LANE3_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FUNF_LANE2_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FUNF_LANE1_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FUNF_LANE0_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FOVF_LANE7_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FOVF_LANE6_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FOVF_LANE5_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FOVF_LANE4_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FOVF_LANE3_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FOVF_LANE2_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FOVF_LANE1_BIT |
                            D_IM_PRO_SLVS_MEINTST1_FOVF_LANE0_BIT);

    kuint32 lvdsInte1 = (D_IM_PRO_LVDSINTENB_SOFE0 |
                        D_IM_PRO_LVDSINTENB_EOFE0 |
                        D_IM_PRO_LVDSINTENB_SOLE0 |
                        D_IM_PRO_LVDSINTENB_EOLE0);

    kuint32 lvdsInte2 = (D_IM_PRO_LVDSINTENB_SOFE1 |
                        D_IM_PRO_LVDSINTENB_EOFE1 |
                        D_IM_PRO_LVDSINTENB_SOLE1 |
                        D_IM_PRO_LVDSINTENB_EOLE1);

    kuint32 lvdsInte3 = (D_IM_PRO_LVDSINTENB_SOFE2 |
                        D_IM_PRO_LVDSINTENB_EOFE2 |
                        D_IM_PRO_LVDSINTENB_SOLE2 |
                        D_IM_PRO_LVDSINTENB_EOLE2);

    kuint32 lvdsIntf1 = (D_IM_PRO_LVDSINTFLG_SOFF0 |
                        D_IM_PRO_LVDSINTFLG_EOFF0 |
                        D_IM_PRO_LVDSINTFLG_SOLF0 |
                        D_IM_PRO_LVDSINTFLG_EOLF0);

    kuint32 lvdsIntf2 = (D_IM_PRO_LVDSINTFLG_SOFF1 |
                        D_IM_PRO_LVDSINTFLG_EOFF1 |
                        D_IM_PRO_LVDSINTFLG_SOLF1 |
                        D_IM_PRO_LVDSINTFLG_EOLF1);

    kuint32 lvdsIntf3 = (D_IM_PRO_LVDSINTFLG_SOFF2 |
                        D_IM_PRO_LVDSINTFLG_EOFF2 |
                        D_IM_PRO_LVDSINTFLG_SOLF2 |
                        D_IM_PRO_LVDSINTFLG_EOLF2);

    kuint32 dmipiInte = (D_IM_PRO_MPIINTE_DEC3 |
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

    kuint32 dmipiIntf = (D_IM_PRO_MPIINTF_DEC3 |
                        D_IM_PRO_MPIINTF_DEC2 |
                        D_IM_PRO_MPIINTF_DEC1 |
                        D_IM_PRO_MPIINTF_DEC0 |
                        D_IM_PRO_MPIINTF_DEE3 |
                        D_IM_PRO_MPIINTF_DEE2 |
                        D_IM_PRO_MPIINTF_DEE1 |
                        D_IM_PRO_MPIINTF_DEE0 |
                        D_IM_PRO_MPIINTF_DESSH3 |
                        D_IM_PRO_MPIINTF_DESSH2 |
                        D_IM_PRO_MPIINTF_DESSH1 |
                        D_IM_PRO_MPIINTF_DESSH0 |
                        D_IM_PRO_MPIINTF_DESH3 |
                        D_IM_PRO_MPIINTF_DESH2 |
                        D_IM_PRO_MPIINTF_DESH1 |
                        D_IM_PRO_MPIINTF_DESH0 |
                        D_IM_PRO_MPIINTF_FEO1 |
                        D_IM_PRO_MPIINTF_FEO0 |
                        D_IM_PRO_MPIINTF_FEI1 |
                        D_IM_PRO_MPIINTF_FEI0 |
                        D_IM_PRO_MPIINTF_FSO1 |
                        D_IM_PRO_MPIINTF_FSO0 |
                        D_IM_PRO_MPIINTF_FSI1 |
                        D_IM_PRO_MPIINTF_FSI0 |
                        D_IM_PRO_MPIINTF_LZE3 |
                        D_IM_PRO_MPIINTF_LZE2 |
                        D_IM_PRO_MPIINTF_LZE1 |
                        D_IM_PRO_MPIINTF_LZE0 |
                        D_IM_PRO_MPIINTF_EFS |
                        D_IM_PRO_MPIINTF_CRCE |
                        D_IM_PRO_MPIINTF_ECCW |
                        D_IM_PRO_MPIINTF_ECCE);

    kuint32 cmipiInte1 = (D_IM_PRO_MPICINTE1_CEC2 |
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

    kuint32 cmipiIntf1 = (D_IM_PRO_MPICINTF1_CECF2 |
                        D_IM_PRO_MPICINTF1_CECF1 |
                        D_IM_PRO_MPICINTF1_CECF0 |
                        D_IM_PRO_MPICINTF1_CEEF2 |
                        D_IM_PRO_MPICINTF1_CEEF1 |
                        D_IM_PRO_MPICINTF1_CEEF0 |
                        D_IM_PRO_MPICINTF1_CESSHF2 |
                        D_IM_PRO_MPICINTF1_CESSHF1 |
                        D_IM_PRO_MPICINTF1_CESSHF0 |
                        D_IM_PRO_MPICINTF1_CESHF2 |
                        D_IM_PRO_MPICINTF1_CESHF1 |
                        D_IM_PRO_MPICINTF1_CESHF0 |
                        D_IM_PRO_MPICINTF1_FEO1F |
                        D_IM_PRO_MPICINTF1_FEO0F |
                        D_IM_PRO_MPICINTF1_FEI1F |
                        D_IM_PRO_MPICINTF1_FEI0F |
                        D_IM_PRO_MPICINTF1_FSO1F |
                        D_IM_PRO_MPICINTF1_FSO0F |
                        D_IM_PRO_MPICINTF1_FSI1F |
                        D_IM_PRO_MPICINTF1_FSI0F |
                        D_IM_PRO_MPICINTF1_LZEF2 |
                        D_IM_PRO_MPICINTF1_LZEF1 |
                        D_IM_PRO_MPICINTF1_LZEF0 |
                        D_IM_PRO_MPICINTF1_EFSF |
                        D_IM_PRO_MPICINTF1_CRCDTEF |
                        D_IM_PRO_MPICINTF1_PHCRC2EF |
                        D_IM_PRO_MPICINTF1_PHCRC1EF);

    kuint32 cmipiInte2 = (D_IM_PRO_MPICINTE2_CICHSE2 |
                        D_IM_PRO_MPICINTE2_CICHSE1 |
                        D_IM_PRO_MPICINTE2_CICHSE0 |
                        D_IM_PRO_MPICINTE2_PHCRCAEE);

    kuint32 cmipiIntf2 = (D_IM_PRO_MPICINTF2_CICHSF2 |
                        D_IM_PRO_MPICINTF2_CICHSF1 |
                        D_IM_PRO_MPICINTF2_CICHSF0 |
                        D_IM_PRO_MPICINTF2_PHCRCAEF);

    kuint32 moniInte = (D_IM_PRO_MONIINTENB_MONIHDE |
                        D_IM_PRO_MONIINTENB_MONIEPFE |
                        D_IM_PRO_MONIINTENB_MONIEPLE |
                        D_IM_PRO_MONIINTENB_MONIBLLMINE |
                        D_IM_PRO_MONIINTENB_MONIBLLMAXE);

    kuint32 moniIntf = (D_IM_PRO_MONIINTFLG_MONIHDF |
                        D_IM_PRO_MONIINTFLG_MONIEPFF |
                        D_IM_PRO_MONIINTFLG_MONIEPLF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMINF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMAXF);

    kuint32  chLoopcnt;
    const T_IM_PRO_COMMON_MONI_INFO* moniInfo;

    im_pro_debug_slvs_comm_intflg_fill(im_pro_debug_get(),slvsCommInte, slvsCommIntf);
    for(chLoopcnt = 0; chLoopcnt < E_IM_PRO_SLVS_STREAM_TYPE_BOTH; chLoopcnt++) {
        im_pro_debug_slvs_strm_intflg_fill(im_pro_debug_get(),chLoopcnt, slvsInte, slvsIntf, slvsLeinte, slvsLeintf, slvsMeinte0, slvsMeintf0, slvsMeinte1, slvsMeintf1);
    }

    im_pro_debug_lvds_intflg_fill(im_pro_debug_get(),0, lvdsInte1, lvdsIntf1, lvdsInte2, lvdsIntf2, lvdsInte3, lvdsIntf3);

    im_pro_debug_dmipi_intflg_fill(im_pro_debug_get(),0, dmipiInte, dmipiIntf);

    im_pro_debug_cmipi_intflg_fill(im_pro_debug_get(),0, cmipiInte1, cmipiIntf1, cmipiInte2, cmipiIntf2);

    im_pro_debug_moni_intflg_fill(im_pro_debug_get(),0, moniInte, moniIntf);

    im_pro_comm_get_moni_reg_info(0, 0, 0, &moniInfo);
    moniInfo->regPtr->MONIVD.bit.MONIVD = 0xFFFF;;
    moniInfo->regPtr->MONIHD.bit.MONIHD = 0xFFFF;;
    moniInfo->regPtr->MONIEPF.bit.MONIEPF = 0xFFFFFFFF;;
    moniInfo->regPtr->MONIEPLMIN.bit.MONIEPLMIN = 0xFFFF;;
    moniInfo->regPtr->MONIEPLMAX.bit.MONIEPLMAX = 0xFFFF;;
    moniInfo->regPtr->MONIBLLMIN.bit.MONIBLLMIN = 0xFFFFFFFF;;
    moniInfo->regPtr->MONIBLLMAX.bit.MONIBLLMAX = 0xFFFFFFFF;;
#endif  // CO_DEBUG_ON_PC
    Im_PRO_SEN_Sensor_If_Int_Handler_0();
}

void ct_im_pro_7_27(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 lvdsInte1 = (D_IM_PRO_LVDSINTENB_SOFE0 |
                        D_IM_PRO_LVDSINTENB_EOFE0 |
                        D_IM_PRO_LVDSINTENB_SOLE0 |
                        D_IM_PRO_LVDSINTENB_EOLE0);

    kuint32 lvdsInte2 = (D_IM_PRO_LVDSINTENB_SOFE1 |
                        D_IM_PRO_LVDSINTENB_EOFE1 |
                        D_IM_PRO_LVDSINTENB_SOLE1 |
                        D_IM_PRO_LVDSINTENB_EOLE1);
                                
    kuint32 lvdsInte3 = (D_IM_PRO_LVDSINTENB_SOFE2 |
                        D_IM_PRO_LVDSINTENB_EOFE2 |
                        D_IM_PRO_LVDSINTENB_SOLE2 |
                        D_IM_PRO_LVDSINTENB_EOLE2);

    kuint32 lvdsIntf1 = (D_IM_PRO_LVDSINTFLG_SOFF0 |
                        D_IM_PRO_LVDSINTFLG_EOFF0 |
                        D_IM_PRO_LVDSINTFLG_SOLF0 |
                        D_IM_PRO_LVDSINTFLG_EOLF0);

    kuint32 lvdsIntf2 = (D_IM_PRO_LVDSINTFLG_SOFF1 |
                        D_IM_PRO_LVDSINTFLG_EOFF1 |
                        D_IM_PRO_LVDSINTFLG_SOLF1 |
                        D_IM_PRO_LVDSINTFLG_EOLF1);

    kuint32 lvdsIntf3 = (D_IM_PRO_LVDSINTFLG_SOFF2 |
                        D_IM_PRO_LVDSINTFLG_EOFF2 |
                        D_IM_PRO_LVDSINTFLG_SOLF2 |
                        D_IM_PRO_LVDSINTFLG_EOLF2);

    kuint32 dmipiInte = (D_IM_PRO_MPIINTE_DEC3 |
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

    kuint32 dmipiIntf = (D_IM_PRO_MPIINTF_DEC3 |
                        D_IM_PRO_MPIINTF_DEC2 |
                        D_IM_PRO_MPIINTF_DEC1 |
                        D_IM_PRO_MPIINTF_DEC0 |
                        D_IM_PRO_MPIINTF_DEE3 |
                        D_IM_PRO_MPIINTF_DEE2 |
                        D_IM_PRO_MPIINTF_DEE1 |
                        D_IM_PRO_MPIINTF_DEE0 |
                        D_IM_PRO_MPIINTF_DESSH3 |
                        D_IM_PRO_MPIINTF_DESSH2 |
                        D_IM_PRO_MPIINTF_DESSH1 |
                        D_IM_PRO_MPIINTF_DESSH0 |
                        D_IM_PRO_MPIINTF_DESH3 |
                        D_IM_PRO_MPIINTF_DESH2 |
                        D_IM_PRO_MPIINTF_DESH1 |
                        D_IM_PRO_MPIINTF_DESH0 |
                        D_IM_PRO_MPIINTF_FEO1 |
                        D_IM_PRO_MPIINTF_FEO0 |
                        D_IM_PRO_MPIINTF_FEI1 |
                        D_IM_PRO_MPIINTF_FEI0 |
                        D_IM_PRO_MPIINTF_FSO1 |
                        D_IM_PRO_MPIINTF_FSO0 |
                        D_IM_PRO_MPIINTF_FSI1 |
                        D_IM_PRO_MPIINTF_FSI0 |
                        D_IM_PRO_MPIINTF_LZE3 |
                        D_IM_PRO_MPIINTF_LZE2 |
                        D_IM_PRO_MPIINTF_LZE1 |
                        D_IM_PRO_MPIINTF_LZE0 |
                        D_IM_PRO_MPIINTF_EFS |
                        D_IM_PRO_MPIINTF_CRCE |
                        D_IM_PRO_MPIINTF_ECCW |
                        D_IM_PRO_MPIINTF_ECCE);

    kuint32 cmipiInte1 = (D_IM_PRO_MPICINTE1_CEC2 |
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

    kuint32 cmipiIntf1 = (D_IM_PRO_MPICINTF1_CECF2 |
                        D_IM_PRO_MPICINTF1_CECF1 |
                        D_IM_PRO_MPICINTF1_CECF0 |
                        D_IM_PRO_MPICINTF1_CEEF2 |
                        D_IM_PRO_MPICINTF1_CEEF1 |
                        D_IM_PRO_MPICINTF1_CEEF0 |
                        D_IM_PRO_MPICINTF1_CESSHF2 |
                        D_IM_PRO_MPICINTF1_CESSHF1 |
                        D_IM_PRO_MPICINTF1_CESSHF0 |
                        D_IM_PRO_MPICINTF1_CESHF2 |
                        D_IM_PRO_MPICINTF1_CESHF1 |
                        D_IM_PRO_MPICINTF1_CESHF0 |
                        D_IM_PRO_MPICINTF1_FEO1F |
                        D_IM_PRO_MPICINTF1_FEO0F |
                        D_IM_PRO_MPICINTF1_FEI1F |
                        D_IM_PRO_MPICINTF1_FEI0F |
                        D_IM_PRO_MPICINTF1_FSO1F |
                        D_IM_PRO_MPICINTF1_FSO0F |
                        D_IM_PRO_MPICINTF1_FSI1F |
                        D_IM_PRO_MPICINTF1_FSI0F |
                        D_IM_PRO_MPICINTF1_LZEF2 |
                        D_IM_PRO_MPICINTF1_LZEF1 |
                        D_IM_PRO_MPICINTF1_LZEF0 |
                        D_IM_PRO_MPICINTF1_EFSF |
                        D_IM_PRO_MPICINTF1_CRCDTEF |
                        D_IM_PRO_MPICINTF1_PHCRC2EF |
                        D_IM_PRO_MPICINTF1_PHCRC1EF);

    kuint32 cmipiInte2 = (D_IM_PRO_MPICINTE2_CICHSE2 |
                        D_IM_PRO_MPICINTE2_CICHSE1 |
                        D_IM_PRO_MPICINTE2_CICHSE0 |
                        D_IM_PRO_MPICINTE2_PHCRCAEE);

    kuint32 cmipiIntf2 = (D_IM_PRO_MPICINTF2_CICHSF2 |
                        D_IM_PRO_MPICINTF2_CICHSF1 |
                        D_IM_PRO_MPICINTF2_CICHSF0 |
                        D_IM_PRO_MPICINTF2_PHCRCAEF);

    kuint32 moniInte = (D_IM_PRO_MONIINTENB_MONIHDE |
                        D_IM_PRO_MONIINTENB_MONIEPFE |
                        D_IM_PRO_MONIINTENB_MONIEPLE |
                        D_IM_PRO_MONIINTENB_MONIBLLMINE |
                        D_IM_PRO_MONIINTENB_MONIBLLMAXE);

    kuint32 moniIntf = (D_IM_PRO_MONIINTFLG_MONIHDF |
                        D_IM_PRO_MONIINTFLG_MONIEPFF |
                        D_IM_PRO_MONIINTFLG_MONIEPLF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMINF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMAXF);

    const T_IM_PRO_COMMON_MONI_INFO* moniInfo;

    im_pro_debug_lvds_intflg_fill(im_pro_debug_get(),1, lvdsInte1, lvdsIntf1, lvdsInte2, lvdsIntf2, lvdsInte3, lvdsIntf3);

    im_pro_debug_dmipi_intflg_fill(im_pro_debug_get(),1, dmipiInte, dmipiIntf);

    im_pro_debug_cmipi_intflg_fill(im_pro_debug_get(),1, cmipiInte1, cmipiIntf1, cmipiInte2, cmipiIntf2);

    im_pro_debug_moni_intflg_fill(im_pro_debug_get(),1, moniInte, moniIntf);

    im_pro_comm_get_moni_reg_info(0, 0, 1, &moniInfo);
    moniInfo->regPtr->MONIVD.bit.MONIVD = 0xFFFF;;
    moniInfo->regPtr->MONIHD.bit.MONIHD = 0xFFFF;;
    moniInfo->regPtr->MONIEPF.bit.MONIEPF = 0xFFFFFFFF;;
    moniInfo->regPtr->MONIEPLMIN.bit.MONIEPLMIN = 0xFFFF;;
    moniInfo->regPtr->MONIEPLMAX.bit.MONIEPLMAX = 0xFFFF;;
    moniInfo->regPtr->MONIBLLMIN.bit.MONIBLLMIN = 0xFFFFFFFF;;
    moniInfo->regPtr->MONIBLLMAX.bit.MONIBLLMAX = 0xFFFFFFFF;;
#endif  // CO_DEBUG_ON_PC

    Im_PRO_SEN_Sensor_If_Int_Handler_1();
}

void ct_im_pro_7_28(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 lvdsInte1 = (D_IM_PRO_LVDSINTENB_SOFE0 |
                        D_IM_PRO_LVDSINTENB_EOFE0 |
                        D_IM_PRO_LVDSINTENB_SOLE0 |
                        D_IM_PRO_LVDSINTENB_EOLE0);

    kuint32 lvdsInte2 = (D_IM_PRO_LVDSINTENB_SOFE1 |
                        D_IM_PRO_LVDSINTENB_EOFE1 |
                        D_IM_PRO_LVDSINTENB_SOLE1 |
                        D_IM_PRO_LVDSINTENB_EOLE1);

    kuint32 lvdsInte3 = (D_IM_PRO_LVDSINTENB_SOFE2 |
                        D_IM_PRO_LVDSINTENB_EOFE2 |
                        D_IM_PRO_LVDSINTENB_SOLE2 |
                        D_IM_PRO_LVDSINTENB_EOLE2);

    kuint32 lvdsIntf1 = (D_IM_PRO_LVDSINTFLG_SOFF0 |
                        D_IM_PRO_LVDSINTFLG_EOFF0 |
                        D_IM_PRO_LVDSINTFLG_SOLF0 |
                        D_IM_PRO_LVDSINTFLG_EOLF0);

    kuint32 lvdsIntf2 = (D_IM_PRO_LVDSINTFLG_SOFF1 |
                        D_IM_PRO_LVDSINTFLG_EOFF1 |
                        D_IM_PRO_LVDSINTFLG_SOLF1 |
                        D_IM_PRO_LVDSINTFLG_EOLF1);

    kuint32 lvdsIntf3 = (D_IM_PRO_LVDSINTFLG_SOFF2 |
                        D_IM_PRO_LVDSINTFLG_EOFF2 |
                        D_IM_PRO_LVDSINTFLG_SOLF2 |
                        D_IM_PRO_LVDSINTFLG_EOLF2);

    kuint32 dmipiInte = (D_IM_PRO_MPIINTE_DEC3 |
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

    kuint32 dmipiIntf = (D_IM_PRO_MPIINTF_DEC3 |
                        D_IM_PRO_MPIINTF_DEC2 |
                        D_IM_PRO_MPIINTF_DEC1 |
                        D_IM_PRO_MPIINTF_DEC0 |
                        D_IM_PRO_MPIINTF_DEE3 |
                        D_IM_PRO_MPIINTF_DEE2 |
                        D_IM_PRO_MPIINTF_DEE1 |
                        D_IM_PRO_MPIINTF_DEE0 |
                        D_IM_PRO_MPIINTF_DESSH3 |
                        D_IM_PRO_MPIINTF_DESSH2 |
                        D_IM_PRO_MPIINTF_DESSH1 |
                        D_IM_PRO_MPIINTF_DESSH0 |
                        D_IM_PRO_MPIINTF_DESH3 |
                        D_IM_PRO_MPIINTF_DESH2 |
                        D_IM_PRO_MPIINTF_DESH1 |
                        D_IM_PRO_MPIINTF_DESH0 |
                        D_IM_PRO_MPIINTF_FEO1 |
                        D_IM_PRO_MPIINTF_FEO0 |
                        D_IM_PRO_MPIINTF_FEI1 |
                        D_IM_PRO_MPIINTF_FEI0 |
                        D_IM_PRO_MPIINTF_FSO1 |
                        D_IM_PRO_MPIINTF_FSO0 |
                        D_IM_PRO_MPIINTF_FSI1 |
                        D_IM_PRO_MPIINTF_FSI0 |
                        D_IM_PRO_MPIINTF_LZE3 |
                        D_IM_PRO_MPIINTF_LZE2 |
                        D_IM_PRO_MPIINTF_LZE1 |
                        D_IM_PRO_MPIINTF_LZE0 |
                        D_IM_PRO_MPIINTF_EFS |
                        D_IM_PRO_MPIINTF_CRCE |
                        D_IM_PRO_MPIINTF_ECCW |
                        D_IM_PRO_MPIINTF_ECCE);

    kuint32 cmipiInte1 = (D_IM_PRO_MPICINTE1_CEC2 |
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

    kuint32 cmipiIntf1 = (D_IM_PRO_MPICINTF1_CECF2 |
                        D_IM_PRO_MPICINTF1_CECF1 |
                        D_IM_PRO_MPICINTF1_CECF0 |
                        D_IM_PRO_MPICINTF1_CEEF2 |
                        D_IM_PRO_MPICINTF1_CEEF1 |
                        D_IM_PRO_MPICINTF1_CEEF0 |
                        D_IM_PRO_MPICINTF1_CESSHF2 |
                        D_IM_PRO_MPICINTF1_CESSHF1 |
                        D_IM_PRO_MPICINTF1_CESSHF0 |
                        D_IM_PRO_MPICINTF1_CESHF2 |
                        D_IM_PRO_MPICINTF1_CESHF1 |
                        D_IM_PRO_MPICINTF1_CESHF0 |
                        D_IM_PRO_MPICINTF1_FEO1F |
                        D_IM_PRO_MPICINTF1_FEO0F |
                        D_IM_PRO_MPICINTF1_FEI1F |
                        D_IM_PRO_MPICINTF1_FEI0F |
                        D_IM_PRO_MPICINTF1_FSO1F |
                        D_IM_PRO_MPICINTF1_FSO0F |
                        D_IM_PRO_MPICINTF1_FSI1F |
                        D_IM_PRO_MPICINTF1_FSI0F |
                        D_IM_PRO_MPICINTF1_LZEF2 |
                        D_IM_PRO_MPICINTF1_LZEF1 |
                        D_IM_PRO_MPICINTF1_LZEF0 |
                        D_IM_PRO_MPICINTF1_EFSF |
                        D_IM_PRO_MPICINTF1_CRCDTEF |
                        D_IM_PRO_MPICINTF1_PHCRC2EF |
                        D_IM_PRO_MPICINTF1_PHCRC1EF);

    kuint32 cmipiInte2 = (D_IM_PRO_MPICINTE2_CICHSE2 |
                        D_IM_PRO_MPICINTE2_CICHSE1 |
                        D_IM_PRO_MPICINTE2_CICHSE0 |
                        D_IM_PRO_MPICINTE2_PHCRCAEE);

    kuint32 cmipiIntf2 = (D_IM_PRO_MPICINTF2_CICHSF2 |
                        D_IM_PRO_MPICINTF2_CICHSF1 |
                        D_IM_PRO_MPICINTF2_CICHSF0 |
                        D_IM_PRO_MPICINTF2_PHCRCAEF);

    kuint32 moniInte = (D_IM_PRO_MONIINTENB_MONIHDE |
                        D_IM_PRO_MONIINTENB_MONIEPFE |
                        D_IM_PRO_MONIINTENB_MONIEPLE |
                        D_IM_PRO_MONIINTENB_MONIBLLMINE |
                        D_IM_PRO_MONIINTENB_MONIBLLMAXE);

    kuint32 moniIntf = (D_IM_PRO_MONIINTFLG_MONIHDF |
                        D_IM_PRO_MONIINTFLG_MONIEPFF |
                        D_IM_PRO_MONIINTFLG_MONIEPLF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMINF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMAXF);

    const T_IM_PRO_COMMON_MONI_INFO* moniInfo;

    im_pro_debug_lvds_intflg_fill(im_pro_debug_get(),2, lvdsInte1, lvdsIntf1, lvdsInte2, lvdsIntf2, lvdsInte3, lvdsIntf3);

    im_pro_debug_dmipi_intflg_fill(im_pro_debug_get(),2, dmipiInte, dmipiIntf);

    im_pro_debug_cmipi_intflg_fill(im_pro_debug_get(),2, cmipiInte1, cmipiIntf1, cmipiInte2, cmipiIntf2);

    im_pro_debug_moni_intflg_fill(im_pro_debug_get(),2, moniInte, moniIntf);

    im_pro_comm_get_moni_reg_info(0, 0, 2, &moniInfo);
    moniInfo->regPtr->MONIVD.bit.MONIVD = 0xFFFF;;
    moniInfo->regPtr->MONIHD.bit.MONIHD = 0xFFFF;;
    moniInfo->regPtr->MONIEPF.bit.MONIEPF = 0xFFFFFFFF;;
    moniInfo->regPtr->MONIEPLMIN.bit.MONIEPLMIN = 0xFFFF;;
    moniInfo->regPtr->MONIEPLMAX.bit.MONIEPLMAX = 0xFFFF;;
    moniInfo->regPtr->MONIBLLMIN.bit.MONIBLLMIN = 0xFFFFFFFF;;
    moniInfo->regPtr->MONIBLLMAX.bit.MONIBLLMAX = 0xFFFFFFFF;;
#endif  // CO_DEBUG_ON_PC
    Im_PRO_SEN_Sensor_If_Int_Handler_2();
}

void ct_im_pro_7_29(const kuint32 idx)
{
#ifdef CO_DEBUG_ON_PC
    kuint32 lvdsInte1 = (D_IM_PRO_LVDSINTENB_SOFE0 |
                        D_IM_PRO_LVDSINTENB_EOFE0 |
                        D_IM_PRO_LVDSINTENB_SOLE0 | 
                        D_IM_PRO_LVDSINTENB_EOLE0);

    kuint32 lvdsInte2 = (D_IM_PRO_LVDSINTENB_SOFE1 |
                        D_IM_PRO_LVDSINTENB_EOFE1 |
                        D_IM_PRO_LVDSINTENB_SOLE1 |
                        D_IM_PRO_LVDSINTENB_EOLE1);

    kuint32 lvdsInte3 = (D_IM_PRO_LVDSINTENB_SOFE2 |
                        D_IM_PRO_LVDSINTENB_EOFE2 |
                        D_IM_PRO_LVDSINTENB_SOLE2 |
                        D_IM_PRO_LVDSINTENB_EOLE2);

    kuint32 lvdsIntf1 = (D_IM_PRO_LVDSINTFLG_SOFF0 |
                        D_IM_PRO_LVDSINTFLG_EOFF0 |
                        D_IM_PRO_LVDSINTFLG_SOLF0 |
                        D_IM_PRO_LVDSINTFLG_EOLF0);

    kuint32 lvdsIntf2 = (D_IM_PRO_LVDSINTFLG_SOFF1 |
                        D_IM_PRO_LVDSINTFLG_EOFF1 |
                        D_IM_PRO_LVDSINTFLG_SOLF1 |
                        D_IM_PRO_LVDSINTFLG_EOLF1);

    kuint32 lvdsIntf3 = (D_IM_PRO_LVDSINTFLG_SOFF2 |
                        D_IM_PRO_LVDSINTFLG_EOFF2 |
                        D_IM_PRO_LVDSINTFLG_SOLF2 |
                        D_IM_PRO_LVDSINTFLG_EOLF2);

    kuint32 dmipiInte = (D_IM_PRO_MPIINTE_DEC3 |
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

    kuint32 dmipiIntf = (D_IM_PRO_MPIINTF_DEC3 |
                        D_IM_PRO_MPIINTF_DEC2 |
                        D_IM_PRO_MPIINTF_DEC1 |
                        D_IM_PRO_MPIINTF_DEC0 |
                        D_IM_PRO_MPIINTF_DEE3 |
                        D_IM_PRO_MPIINTF_DEE2 |
                        D_IM_PRO_MPIINTF_DEE1 |
                        D_IM_PRO_MPIINTF_DEE0 |
                        D_IM_PRO_MPIINTF_DESSH3 |
                        D_IM_PRO_MPIINTF_DESSH2 |
                        D_IM_PRO_MPIINTF_DESSH1 |
                        D_IM_PRO_MPIINTF_DESSH0 |
                        D_IM_PRO_MPIINTF_DESH3 |
                        D_IM_PRO_MPIINTF_DESH2 |
                        D_IM_PRO_MPIINTF_DESH1 |
                        D_IM_PRO_MPIINTF_DESH0 |
                        D_IM_PRO_MPIINTF_FEO1 |
                        D_IM_PRO_MPIINTF_FEO0 |
                        D_IM_PRO_MPIINTF_FEI1 |
                        D_IM_PRO_MPIINTF_FEI0 |
                        D_IM_PRO_MPIINTF_FSO1 |
                        D_IM_PRO_MPIINTF_FSO0 |
                        D_IM_PRO_MPIINTF_FSI1 |
                        D_IM_PRO_MPIINTF_FSI0 |
                        D_IM_PRO_MPIINTF_LZE3 |
                        D_IM_PRO_MPIINTF_LZE2 |
                        D_IM_PRO_MPIINTF_LZE1 |
                        D_IM_PRO_MPIINTF_LZE0 |
                        D_IM_PRO_MPIINTF_EFS |
                        D_IM_PRO_MPIINTF_CRCE |
                        D_IM_PRO_MPIINTF_ECCW |
                        D_IM_PRO_MPIINTF_ECCE);

    kuint32 cmipiInte1 = (D_IM_PRO_MPICINTE1_CEC2 |
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

    kuint32 cmipiIntf1 = (D_IM_PRO_MPICINTF1_CECF2 |
                        D_IM_PRO_MPICINTF1_CECF1 |
                        D_IM_PRO_MPICINTF1_CECF0 |
                        D_IM_PRO_MPICINTF1_CEEF2 |
                        D_IM_PRO_MPICINTF1_CEEF1 |
                        D_IM_PRO_MPICINTF1_CEEF0 |
                        D_IM_PRO_MPICINTF1_CESSHF2 |
                        D_IM_PRO_MPICINTF1_CESSHF1 |
                        D_IM_PRO_MPICINTF1_CESSHF0 |
                        D_IM_PRO_MPICINTF1_CESHF2 |
                        D_IM_PRO_MPICINTF1_CESHF1 |
                        D_IM_PRO_MPICINTF1_CESHF0 |
                        D_IM_PRO_MPICINTF1_FEO1F |
                        D_IM_PRO_MPICINTF1_FEO0F |
                        D_IM_PRO_MPICINTF1_FEI1F |
                        D_IM_PRO_MPICINTF1_FEI0F |
                        D_IM_PRO_MPICINTF1_FSO1F |
                        D_IM_PRO_MPICINTF1_FSO0F |
                        D_IM_PRO_MPICINTF1_FSI1F |
                        D_IM_PRO_MPICINTF1_FSI0F |
                        D_IM_PRO_MPICINTF1_LZEF2 |
                        D_IM_PRO_MPICINTF1_LZEF1 |
                        D_IM_PRO_MPICINTF1_LZEF0 |
                        D_IM_PRO_MPICINTF1_EFSF |
                        D_IM_PRO_MPICINTF1_CRCDTEF |
                        D_IM_PRO_MPICINTF1_PHCRC2EF |
                        D_IM_PRO_MPICINTF1_PHCRC1EF);

    kuint32 cmipiInte2 = (D_IM_PRO_MPICINTE2_CICHSE2 |
                        D_IM_PRO_MPICINTE2_CICHSE1 |
                        D_IM_PRO_MPICINTE2_CICHSE0 |
                        D_IM_PRO_MPICINTE2_PHCRCAEE);

    kuint32 cmipiIntf2 = (D_IM_PRO_MPICINTF2_CICHSF2 |
                        D_IM_PRO_MPICINTF2_CICHSF1 |
                        D_IM_PRO_MPICINTF2_CICHSF0 |
                        D_IM_PRO_MPICINTF2_PHCRCAEF);

    kuint32 moniInte = (D_IM_PRO_MONIINTENB_MONIHDE |
                        D_IM_PRO_MONIINTENB_MONIEPFE |
                        D_IM_PRO_MONIINTENB_MONIEPLE |
                        D_IM_PRO_MONIINTENB_MONIBLLMINE |
                        D_IM_PRO_MONIINTENB_MONIBLLMAXE);

    kuint32 moniIntf = (D_IM_PRO_MONIINTFLG_MONIHDF |
                        D_IM_PRO_MONIINTFLG_MONIEPFF |
                        D_IM_PRO_MONIINTFLG_MONIEPLF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMINF |
                        D_IM_PRO_MONIINTFLG_MONIBLLMAXF);

    const T_IM_PRO_COMMON_MONI_INFO* moniInfo;

    im_pro_debug_lvds_intflg_fill(im_pro_debug_get(),3, lvdsInte1, lvdsIntf1, lvdsInte2, lvdsIntf2, lvdsInte3, lvdsIntf3);

    im_pro_debug_dmipi_intflg_fill(im_pro_debug_get(),3, dmipiInte, dmipiIntf);

    im_pro_debug_cmipi_intflg_fill(im_pro_debug_get(),3, cmipiInte1, cmipiIntf1, cmipiInte2, cmipiIntf2);

    im_pro_debug_moni_intflg_fill(im_pro_debug_get(),3, moniInte, moniIntf);
    im_pro_comm_get_moni_reg_info(0, 0, 3, &moniInfo);

    moniInfo->regPtr->MONIVD.bit.MONIVD = 0xFFFF;;
    moniInfo->regPtr->MONIHD.bit.MONIHD = 0xFFFF;;
    moniInfo->regPtr->MONIEPF.bit.MONIEPF = 0xFFFFFFFF;;
    moniInfo->regPtr->MONIEPLMIN.bit.MONIEPLMIN = 0xFFFF;;
    moniInfo->regPtr->MONIEPLMAX.bit.MONIEPLMAX = 0xFFFF;;
    moniInfo->regPtr->MONIBLLMIN.bit.MONIBLLMIN = 0xFFFFFFFF;;
    moniInfo->regPtr->MONIBLLMAX.bit.MONIBLLMAX = 0xFFFFFFFF;;
#endif  // CO_DEBUG_ON_PC
    Im_PRO_SEN_Sensor_If_Int_Handler_3();
}
#endif

CtImpro72* ct_impro_7_2_new(void)
{
	CtImpro72* self = k_object_new_with_private(CT_TYPE_IMPRO_7_2, sizeof(CtImpro72Private));

	return self;
}

CtImpro72* ct_impro_7_2_get(void)
{
	static CtImpro72* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IMPRO_7_2, sizeof(CtImpro72Private));
	}

	return self;
}
