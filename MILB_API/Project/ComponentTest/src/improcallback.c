/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 陈阳
*@brief : ImProCallback
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

#include "ctimpro1.h"
#include "ctimpro4.h"
#include "ctimpro6.h"
#include "improcallback.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImProCallback, im_pro_callback)
#define IM_PRO_CALLBACK_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImProCallbackPrivate, IM_TYPE_PRO_CALLBACK))


struct _ImProCallbackPrivate
{
    
};


/**
 * IMPL
 */
static void im_pro_callback_constructor(ImProCallback *self)
{
	ImProCallbackPrivate *priv = IM_PRO_CALLBACK_GET_PRIVATE(self);
}

static void im_pro_callback_destructor(ImProCallback *self)
{
	ImProCallbackPrivate *priv = IM_PRO_CALLBACK_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_callback_sen_vd_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_vd_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_hd_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_hd_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_slvs_common_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_slvs_common_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_slvs_intn_o_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_slvs_intn_o_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_slvs_link_err_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_slvs_link_err_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_slvs_mac_err1_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_slvs_mac_err1_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_slvs_mac_err2_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_slvs_mac_err2_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_lvds_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_lvds_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_dmipi_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_dmipi_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_cmipi_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_cmipi_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_moni_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    kint32                   ercd;
    T_IM_PRO_MONI_RESULT    moniResult;

    ercd = Im_PRO_MONI_Get_Monitor_Count(cbId->unitNo, cbId->blockType, cbId->channel, &moniResult);
    im_pro_6_3_print_4(impro_6_3_print_get(), "", cbId->unitNo, cbId->blockType, cbId->channel, ercd, &moniResult);
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_moni_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_ldiv_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_ldiv_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_obd_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    kint32           ercd;
    T_IM_PRO_RGB4   obcnt;

    ercd = Im_PRO_OBD_Get_OBCNT(cbId->channel, &obcnt);
    if(ercd != DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Get_OBCNT() Error ercd=0x%x\n", ercd));
    } else {
        im_pro_1_3_print_9(im_pro_1_3_print_get(),"", cbId->channel, &obcnt);
    }

    ercd = Im_PRO_OBD_Get_OBData(cbId->channel, &obcnt);
    if(ercd != DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Get_OBData() Error ercd=0x%x\n", ercd));
    } else {
        im_pro_1_4_print_0(im_pro_1_4_print_get(), "", cbId->channel, &obcnt);
    }

    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_obd_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_obt_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    kint32           ercd;
    T_IM_PRO_RGB2   obcnt;

    ercd = Im_PRO_OBT_Get_OBTData(cbId->channel, &obcnt);
    if(ercd != DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Get_OBTata() Error ercd=0x%x\n", ercd));
    } else {
        im_pro_1_4_print_6(im_pro_1_4_print_get(), "", cbId->channel, &obcnt);
    }

    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_obt_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sen_pwch_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    kint32   ercd;
    kulong   currentAddr = 0;
    kulong   lastAddr = 0;
    kuchar   axiResponse = 0;
    kulong   dataAddress;

    lastAddr = Im_PRO_PWch_Get_Buf_Data(cbId->unitNo, cbId->blockType, cbId->channel);
    ercd = Im_PRO_PWch_Update_Buf_Index(cbId->unitNo, cbId->blockType, cbId->channel);
    im_pro_6_1_print_3(impro_6_1_print_get(), 0, cbId->unitNo, cbId->blockType, cbId->channel, ercd);
    currentAddr = Im_PRO_PWch_Get_Buf_Data(cbId->unitNo, cbId->blockType, cbId->channel);
    DriverCommon_DDIM_PRINT(("Im_PRO_PWch_Get_Buf_Data(%u %u %u) LastAddr(0x%08lx) CurrentAddr(0x%08lx)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, lastAddr, currentAddr));

    ercd = Im_PRO_PWch_Get_AXI_Response(cbId->unitNo, cbId->blockType, cbId->channel, &axiResponse);
    im_pro_6_1_print_5(impro_6_1_print_get(), cbId->unitNo, cbId->blockType, cbId->channel, ercd, axiResponse);

    if(cbId->blockType == E_IM_PRO_BLOCK_TYPE_STAT) {
        dataAddress = Im_PRO_AEAWB_Get_AEAWBData(cbId->channel);
        if(dataAddress == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_AEAWBData(%u) max_para Error\n", 
            cbId->channel));
        } else {
            im_pro_4_2_print_1(impro_4_2_print_get(), "", cbId->channel, &dataAddress);
        }

        dataAddress = Im_PRO_AEAWB_Get_LastAEAWBData(cbId->channel);
        if(dataAddress == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_LastAEAWBData(%u) max_para Error\n", 
            cbId->channel));
        } else {
            im_pro_4_2_print_2(impro_4_2_print_get(), "", cbId->channel, &dataAddress);
        }
    }
    DriverCommon_DDIM_PRINT(("im_pro_callback_sen_pwch_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_prch_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_prch_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sro_vd_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sro_vd_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sro_hd_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sro_hd_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_sro_sdc_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sro_sdc_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_b2b_vd_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sro_vd_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_b2b_hd_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_sro_hd_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_stat_aeawb_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    kint32 ercd;
    kulong               lineData[4];

    ercd = Im_PRO_AEAWB_Get_Line_Data(cbId->channel, lineData);
    if(ercd != DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(("Im_PRO_AEAWB_Get_Line_Data(%u)  Error\n", 
            cbId->channel));
    } else {
        im_pro_4_2_print_0(impro_4_2_print_get(), "", cbId->channel, lineData);
    }

    DriverCommon_DDIM_PRINT(("im_pro_callback_stat_aeawb_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_stat_af_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    kulong                   calcData;
    E_IM_PRO_AF_WINDOW_NO   winNo;

    for(winNo = E_IM_PRO_AF_WINDOW_0; winNo < E_IM_PRO_AF_WINDOW_MAX; winNo++) {
        calcData = Im_PRO_AF_Get_Eval_Calc_Data(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Eval_Calc_Data(%u %u) max_para Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_3_print_3(impro_4_3_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Bright_Data(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Bright_Data(%u %u) max_para Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_3_print_4(impro_4_3_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Dark_Data(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Dark_Data(%u %u) max_para Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_3_print_5(impro_4_3_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal0_Data(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal0_Data(%u %u) max_para Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_3_print_6(impro_4_3_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal1_Data(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal1_Data(%u %u) max_para Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_3_print_7(impro_4_3_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal2_Data(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal2_Data(%u %u) max_para Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_3_print_8(impro_4_3_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Vertical_Data(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Vertical_Data(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_3_print_9(impro_4_3_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Max_Eval_Calc_Value(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Max_Eval_Calc_Value(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_4_print_0(impro_4_4_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Min_Eval_Calc_Value(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Min_Eval_Calc_Value(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_4_print_1(impro_4_4_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Max_Assess_Value(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Max_Assess_Value(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_4_print_2(impro_4_4_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Min_Assess_Value(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Min_Assess_Value(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_4_print_3(impro_4_4_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal0_Line_Accum_Max_Value(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal0_Line_Accum_Max_Value(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_4_print_4(impro_4_4_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal1_Line_Accum_Max_Value(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal1_Line_Accum_Max_Value(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_4_print_5(impro_4_4_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal2_Line_Accum_Max_Value(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal2_Line_Accum_Max_Value(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_4_print_6(impro_4_4_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Eval_Calc_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Eval_Calc_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_4_print_7(impro_4_4_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Bright_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Bright_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_4_print_8(impro_4_4_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Dark_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Dark_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_4_print_9(impro_4_4_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal0_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal0_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_5_print_0(impro_4_5_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal1_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal1_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_5_print_1(impro_4_5_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal2_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal2_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_5_print_2(impro_4_5_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Vertical_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Vertical_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_5_print_3(impro_4_5_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Max_Eval_Calc_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Max_Eval_Calc_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_5_print_4(impro_4_5_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Min_Eval_Calc_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Min_Eval_Calc_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_5_print_5(impro_4_5_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Max_Assess_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Max_Assess_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_5_print_6(impro_4_5_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Min_Assess_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Min_Assess_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_5_print_7(impro_4_5_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal0_Line_Accum_Max_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal0_Line_Accum_Max_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_5_print_8(impro_4_5_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal1_Line_Accum_Max_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal1_Line_Accum_Max_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_5_print_9(impro_4_5_print_get(), "", cbId->channel, winNo, &calcData);
        }

        calcData = Im_PRO_AF_Get_Horizontal2_Line_Accum_Max_LastData(cbId->channel, winNo);
        if(calcData == 0) {
            DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal2_Line_Accum_Max_LastData(%u %u)  Error calcData=0x%lx\n", 
            cbId->channel, winNo, calcData));
        } else {
            im_pro_4_6_print_0(impro_4_6_print_get(), "", cbId->channel, winNo, &calcData);
        }
    }

    DriverCommon_DDIM_PRINT(("im_pro_callback_stat_af_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_stat_hist_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    kint32               ercd;
    T_IM_PRO_HIST_DATA  histData;

    ercd = Im_PRO_HIST_Get_HIST_Data(cbId->channel, &histData);
    if(ercd != DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Data(%u) max_para Error ercd=0x%x\n", 
            cbId->channel, ercd));
    }
    else {
        im_pro_4_6_print_9(impro_4_6_print_get(), "", cbId->channel, &histData);
    }

    DriverCommon_DDIM_PRINT(("im_pro_callback_stat_hist_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_pas_vd_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_pas_vd_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}

void im_pro_callback_pas_hd_int_cb(T_CALLBACK_ID* cbId, kulong result, kulong userParam)
{
    DriverCommon_DDIM_PRINT(("im_pro_callback_pas_hd_int_cb(%u %u %u 0x%08lx %lu)\n", 
    cbId->unitNo, cbId->blockType, cbId->channel, result, userParam));
}
#endif

ImProCallback* im_pro_callback_new(void)
{
	ImProCallback* self = k_object_new_with_private(IM_TYPE_PRO_CALLBACK, sizeof(ImProCallbackPrivate));

	return self;
}

ImProCallback* im_pro_callback_get(void)
{
	static ImProCallback* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_CALLBACK, sizeof(ImProCallbackPrivate));
	}

	return self;
}
