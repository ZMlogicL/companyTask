/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro22Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro22print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro22Print, impro_2_2_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_2_2_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro22PrintPrivate, IMPRO_TYPE_2_2_PRINT))


struct _Impro22PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_2_2_print_constructor(Impro22Print *self)
{
	Impro22PrintPrivate *priv = IMPRO_2_2_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_2_2_print_destructor(Impro22Print *self)
{
	Impro22PrintPrivate *priv = IMPRO_2_2_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_2_2_print_0(Impro22Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Stop(%u %u) result:cagtrg  0x%08lx(%u)\n", 
            unitNo, force, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagtrg.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagtrg.bit.cagtrg));
}

void im_pro_2_2_print_1(Impro22Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_CAG_CTRL* cagCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].sro.cag.rbr.bit.rbrv != cagCtrl->vBinningRatioReciprocalNum) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:rbrv  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.rbr.word, 
            ioPro.imgPipe[unitNo].sro.cag.rbr.bit.rbrv,cagCtrl->vBinningRatioReciprocalNum))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.rbr.bit.rbrh != cagCtrl->hBinningRatioReciprocalNum) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:rbrh  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.rbr.word, 
            ioPro.imgPipe[unitNo].sro.cag.rbr.bit.rbrh,cagCtrl->hBinningRatioReciprocalNum))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.aboarh.bit.aboarh != cagCtrl->optCenterPosH[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:aboarh  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboarh.word, 
            ioPro.imgPipe[unitNo].sro.cag.aboarh.bit.aboarh,cagCtrl->optCenterPosH[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.aboagh.bit.aboagh != cagCtrl->optCenterPosH[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:aboagh  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboagh.word, 
            ioPro.imgPipe[unitNo].sro.cag.aboagh.bit.aboagh,cagCtrl->optCenterPosH[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.aboabh.bit.aboabh != cagCtrl->optCenterPosH[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:aboabh  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboabh.word, 
            ioPro.imgPipe[unitNo].sro.cag.aboabh.bit.aboabh,cagCtrl->optCenterPosH[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.aboarv.bit.aboarv != cagCtrl->optCenterPosV[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:aboarv  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboarv.word, 
            ioPro.imgPipe[unitNo].sro.cag.aboarv.bit.aboarv,cagCtrl->optCenterPosV[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.aboagv.bit.aboagv != cagCtrl->optCenterPosV[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:aboagv  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboagv.word, 
            ioPro.imgPipe[unitNo].sro.cag.aboagv.bit.aboagv,cagCtrl->optCenterPosV[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.aboabv.bit.aboabv != cagCtrl->optCenterPosV[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:aboabv  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboabv.word, 
            ioPro.imgPipe[unitNo].sro.cag.aboabv.bit.aboabv,cagCtrl->optCenterPosV[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abgar.bit.abgar != cagCtrl->gain[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abgar  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abgar.word, 
            ioPro.imgPipe[unitNo].sro.cag.abgar.bit.abgar,cagCtrl->gain[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abgag.bit.abgag != cagCtrl->gain[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abgag  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abgag.word, 
            ioPro.imgPipe[unitNo].sro.cag.abgag.bit.abgag,cagCtrl->gain[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abgab.bit.abgab != cagCtrl->gain[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abgab  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abgab.word, 
            ioPro.imgPipe[unitNo].sro.cag.abgab.bit.abgab,cagCtrl->gain[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablrh.bit.ablrhu != cagCtrl->transferULimitH[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablrhu  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablrh.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablrh.bit.ablrhu,cagCtrl->transferULimitH[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablgh.bit.ablghu != cagCtrl->transferULimitH[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablghu  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablgh.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablgh.bit.ablghu,cagCtrl->transferULimitH[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablbh.bit.ablbhu != cagCtrl->transferULimitH[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablbhu  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablbh.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablbh.bit.ablbhu,cagCtrl->transferULimitH[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablrh.bit.ablrhl != cagCtrl->transferLLimitH[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablrhl  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablrh.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablrh.bit.ablrhl,cagCtrl->transferLLimitH[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablgh.bit.ablghl != cagCtrl->transferLLimitH[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablghl  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablgh.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablgh.bit.ablghl,cagCtrl->transferLLimitH[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablbh.bit.ablbhl != cagCtrl->transferLLimitH[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablbhl  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablbh.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablbh.bit.ablbhl,cagCtrl->transferLLimitH[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablrv.bit.ablrvu != cagCtrl->transferULimitV[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablrvu  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablrv.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablrv.bit.ablrvu,cagCtrl->transferULimitV[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablgv.bit.ablgvu != cagCtrl->transferULimitV[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablgvu  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablgv.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablgv.bit.ablgvu,cagCtrl->transferULimitV[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablbv.bit.ablbvu != cagCtrl->transferULimitV[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablbvu  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablbv.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablbv.bit.ablbvu,cagCtrl->transferULimitV[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablrv.bit.ablrvl != cagCtrl->transferLLimitV[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablrvl  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablrv.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablrv.bit.ablrvl,cagCtrl->transferLLimitV[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablgv.bit.ablgvl != cagCtrl->transferLLimitV[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablgvl  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablgv.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablgv.bit.ablgvl,cagCtrl->transferLLimitV[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.ablbv.bit.ablbvl != cagCtrl->transferLLimitV[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:ablbvl  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablbv.word, 
            ioPro.imgPipe[unitNo].sro.cag.ablbv.bit.ablbvl,cagCtrl->transferLLimitV[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abofsrh.bit.abofsrh != cagCtrl->transferOffsetH[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abofsrh  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsrh.word, 
            ioPro.imgPipe[unitNo].sro.cag.abofsrh.bit.abofsrh,cagCtrl->transferOffsetH[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abofsgh.bit.abofsgh != cagCtrl->transferOffsetH[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abofsgh  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsgh.word, 
            ioPro.imgPipe[unitNo].sro.cag.abofsgh.bit.abofsgh,cagCtrl->transferOffsetH[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abofsbh.bit.abofsbh != cagCtrl->transferOffsetH[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abofsbh  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsbh.word, 
            ioPro.imgPipe[unitNo].sro.cag.abofsbh.bit.abofsbh,cagCtrl->transferOffsetH[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abofsrv.bit.abofsrv != cagCtrl->transferOffsetV[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abofsrv  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsrv.word, 
            ioPro.imgPipe[unitNo].sro.cag.abofsrv.bit.abofsrv,cagCtrl->transferOffsetV[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abofsgv.bit.abofsgv != cagCtrl->transferOffsetV[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abofsgv  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsgv.word, 
            ioPro.imgPipe[unitNo].sro.cag.abofsgv.bit.abofsgv,cagCtrl->transferOffsetV[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abofsbv.bit.abofsbv != cagCtrl->transferOffsetV[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abofsbv  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsbv.word, 
            ioPro.imgPipe[unitNo].sro.cag.abofsbv.bit.abofsbv,cagCtrl->transferOffsetV[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthr1.bit.abnlthr1 != cagCtrl->cornerThresh1[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthr1  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr1.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthr1.bit.abnlthr1,cagCtrl->cornerThresh1[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthg1.bit.abnlthg1 != cagCtrl->cornerThresh1[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthg1  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg1.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthg1.bit.abnlthg1,cagCtrl->cornerThresh1[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthb1.bit.abnlthb1 != cagCtrl->cornerThresh1[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthb1  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb1.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthb1.bit.abnlthb1,cagCtrl->cornerThresh1[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgar1.bit.abnlgar1 != cagCtrl->cornerGain1[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgar1  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar1.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgar1.bit.abnlgar1,cagCtrl->cornerGain1[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgag1.bit.abnlgag1 != cagCtrl->cornerGain1[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgag1  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag1.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgag1.bit.abnlgag1,cagCtrl->cornerGain1[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgab1.bit.abnlgab1 != cagCtrl->cornerGain1[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgab1  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab1.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgab1.bit.abnlgab1,cagCtrl->cornerGain1[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthr2.bit.abnlthr2 != cagCtrl->cornerThresh2[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthr2  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr2.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthr2.bit.abnlthr2,cagCtrl->cornerThresh2[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthg2.bit.abnlthg2 != cagCtrl->cornerThresh2[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthg2  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg2.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthg2.bit.abnlthg2,cagCtrl->cornerThresh2[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthb2.bit.abnlthb2 != cagCtrl->cornerThresh2[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthb2  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb2.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthb2.bit.abnlthb2,cagCtrl->cornerThresh2[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgar2.bit.abnlgar2 != cagCtrl->cornerGain2[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgar2  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar2.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgar2.bit.abnlgar2,cagCtrl->cornerGain2[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgag2.bit.abnlgag2 != cagCtrl->cornerGain2[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgag2  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag2.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgag2.bit.abnlgag2,cagCtrl->cornerGain2[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgab2.bit.abnlgab2 != cagCtrl->cornerGain2[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgab2  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab2.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgab2.bit.abnlgab2,cagCtrl->cornerGain2[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthr3.bit.abnlthr3 != cagCtrl->cornerThresh3[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthr3  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr3.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthr3.bit.abnlthr3,cagCtrl->cornerThresh3[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthg3.bit.abnlthg3 != cagCtrl->cornerThresh3[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthg3  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg3.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthg3.bit.abnlthg3,cagCtrl->cornerThresh3[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthb3.bit.abnlthb3 != cagCtrl->cornerThresh3[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthb3  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb3.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthb3.bit.abnlthb3,cagCtrl->cornerThresh3[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgar3.bit.abnlgar3 != cagCtrl->cornerGain3[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgar3  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar3.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgar3.bit.abnlgar3,cagCtrl->cornerGain3[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgag3.bit.abnlgag3 != cagCtrl->cornerGain3[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgag3  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag3.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgag3.bit.abnlgag3,cagCtrl->cornerGain3[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgab3.bit.abnlgab3 != cagCtrl->cornerGain3[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgab3  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab3.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgab3.bit.abnlgab3,cagCtrl->cornerGain3[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthr4.bit.abnlthr4 != cagCtrl->cornerThresh4[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthr4  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr4.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthr4.bit.abnlthr4,cagCtrl->cornerThresh4[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthg4.bit.abnlthg4 != cagCtrl->cornerThresh4[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthg4  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg4.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthg4.bit.abnlthg4,cagCtrl->cornerThresh4[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlthb4.bit.abnlthb4 != cagCtrl->cornerThresh4[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlthb4  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb4.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlthb4.bit.abnlthb4,cagCtrl->cornerThresh4[2]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgar4.bit.abnlgar4 != cagCtrl->cornerGain4[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgar4  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar4.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgar4.bit.abnlgar4,cagCtrl->cornerGain4[0]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgag4.bit.abnlgag4 != cagCtrl->cornerGain4[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgag4  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag4.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgag4.bit.abnlgag4,cagCtrl->cornerGain4[1]))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.abnlgab4.bit.abnlgab4 != cagCtrl->cornerGain4[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) %s result:abnlgab4  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab4.word, 
            ioPro.imgPipe[unitNo].sro.cag.abnlgab4.bit.abnlgab4,cagCtrl->cornerGain4[2]))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl(%u) error ercd=0x%x\n", 
            unitNo, ercd));
    }
}

void im_pro_2_2_print_2(Impro22Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Set_PAEN(%u %u) result:paen  0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagpaen.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagpaen.bit.cpaen));
    DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Set_PAEN(%u %u) result:cagtrg  0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagtrg.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagtrg.bit.cagtrg));
}

void im_pro_2_2_print_3(Impro22Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_CAG_AREA* cagCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].sro.cag.caggwp.bit.caggh != cagCtrl->gPosX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Set_Area(%u) %s result:caggh  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.caggwp.word, 
            ioPro.imgPipe[unitNo].sro.cag.caggwp.bit.caggh,cagCtrl->gPosX))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.caggwp.bit.caggv != cagCtrl->gPosY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Set_Area(%u) %s result:caggv  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.caggwp.word, 
            ioPro.imgPipe[unitNo].sro.cag.caggwp.bit.caggv,cagCtrl->gPosY))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.caggws.bit.cagghw != cagCtrl->gWidth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Set_Area(%u) %s result:cagghw  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.caggws.word, 
            ioPro.imgPipe[unitNo].sro.cag.caggws.bit.cagghw,cagCtrl->gWidth))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.caggws.bit.caggvw != cagCtrl->gLines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Set_Area(%u) %s result:caggvw  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.caggws.word, 
            ioPro.imgPipe[unitNo].sro.cag.caggws.bit.caggvw,cagCtrl->gLines))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.cagwp.bit.cagh != cagCtrl->posX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Set_Area(%u) %s result:cagh  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagwp.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagwp.bit.cagh,cagCtrl->posX))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.cagwp.bit.cagv != cagCtrl->posY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Set_Area(%u) %s result:cagv  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagwp.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagwp.bit.cagv,cagCtrl->posY))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.cagws.bit.caghw != cagCtrl->width) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Set_Area(%u) %s result:caghw  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagws.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagws.bit.caghw,cagCtrl->width))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.cagws.bit.cagvw != cagCtrl->lines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Set_Area(%u) %s result:cagvw  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagws.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagws.bit.cagvw,cagCtrl->lines))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Set_Area(%u) error ercd=0x%x\n", 
            unitNo, ercd));
    }
}

void im_pro_2_2_print_4(Impro22Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                            T_IM_PRO_CAG_CTRL_GLEVEL_DIFF* cagCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.clpsel != cagCtrl->clipMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl_Glv_Diff(%u) %s result:clpsel  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagmd.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.clpsel,cagCtrl->clipMode))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.gcamd != cagCtrl->gGapCorMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl_Glv_Diff(%u) %s result:gcamd  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagmd.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.gcamd,cagCtrl->gGapCorMode))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.cagpdd != cagCtrl->gGapPadMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl_Glv_Diff(%u) %s result:cagpdd  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagmd.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.cagpdd,cagCtrl->gGapPadMode))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.camd != cagCtrl->gGapMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl_Glv_Diff(%u) %s result:camd  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagmd.word, 
            ioPro.imgPipe[unitNo].sro.cag.cagmd.bit.camd,cagCtrl->gGapMode))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.bfglmt.bit.bfglmth != cagCtrl->gradientULimit) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl_Glv_Diff(%u) %s result:bfglmth  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.bfglmt.word, 
            ioPro.imgPipe[unitNo].sro.cag.bfglmt.bit.bfglmth,cagCtrl->gradientULimit))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.bfglmt.bit.bfglmtl != cagCtrl->gradientLLimit) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl_Glv_Diff(%u) %s result:bfglmtl  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.bfglmt.word, 
            ioPro.imgPipe[unitNo].sro.cag.bfglmt.bit.bfglmtl,cagCtrl->gradientLLimit))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.bfgth.bit.bfgtha != cagCtrl->gradientThreshold) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl_Glv_Diff(%u) %s result:bfgtha  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.bfgth.word, 
            ioPro.imgPipe[unitNo].sro.cag.bfgth.bit.bfgtha,cagCtrl->gradientThreshold))
        };

        if(ioPro.imgPipe[unitNo].sro.cag.bfgth.bit.bfgthk != cagCtrl->gradientThresholdGain) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl_Glv_Diff(%u) %s result:bfgthk  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.bfgth.word, 
            ioPro.imgPipe[unitNo].sro.cag.bfgth.bit.bfgthk,cagCtrl->gradientThresholdGain))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_CAG_Ctrl_Glv_Diff(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_2_print_5(Impro22Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                            const T_IM_PRO_RDMA_CAG_ADDR** cagCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.cagmd.word != (*cagCtrl)->cagmd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:cagmd  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.cagmd.word, (kulong)(*cagCtrl)->cagmd))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.rbr.word != (*cagCtrl)->rbr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:rbr  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.rbr.word, (kulong)(*cagCtrl)->rbr))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.aboarv.word != (*cagCtrl)->aboarv) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:aboarv  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboarv.word, (kulong)(*cagCtrl)->aboarv))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.aboarh.word != (*cagCtrl)->aboarh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:aboarh  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboarh.word, (kulong)(*cagCtrl)->aboarh))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.aboagv.word != (*cagCtrl)->aboagv) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:aboagv  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboagv.word, (kulong)(*cagCtrl)->aboagv))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.aboagh.word != (*cagCtrl)->aboagh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:aboagh  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboagh.word, (kulong)(*cagCtrl)->aboagh))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.aboabv.word != (*cagCtrl)->aboabv) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:aboabv  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboabv.word, (kulong)(*cagCtrl)->aboabv))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.aboabh.word != (*cagCtrl)->aboabh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:aboabh  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.aboabh.word, (kulong)(*cagCtrl)->aboabh))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abgar.word != (*cagCtrl)->abgar) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abgar  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abgar.word, (kulong)(*cagCtrl)->abgar))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abgag.word != (*cagCtrl)->abgag) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abgag  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abgag.word, (kulong)(*cagCtrl)->abgag))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abgab.word != (*cagCtrl)->abgab) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abgab  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abgab.word, (kulong)(*cagCtrl)->abgab))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.ablrv.word != (*cagCtrl)->ablrv) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:ablrv  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablrv.word, (kulong)(*cagCtrl)->ablrv))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.ablrh.word != (*cagCtrl)->ablrh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:ablrh  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablrh.word, (kulong)(*cagCtrl)->ablrh))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.ablgv.word != (*cagCtrl)->ablgv) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:ablgv  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablgv.word, (kulong)(*cagCtrl)->ablgv))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.ablgh.word != (*cagCtrl)->ablgh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:ablgh  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablgh.word, (kulong)(*cagCtrl)->ablgh))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.ablbv.word != (*cagCtrl)->ablbv) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:ablbv  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablbv.word, (kulong)(*cagCtrl)->ablbv))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.ablbh.word != (*cagCtrl)->ablbh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:ablbh  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.ablbh.word, (kulong)(*cagCtrl)->ablbh))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsrv.word != (*cagCtrl)->abofsrv) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abofsrv  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsrv.word, 
                (kulong)(*cagCtrl)->abofsrv))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsrh.word != (*cagCtrl)->abofsrh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abofsrh  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsrh.word, 
                (kulong)(*cagCtrl)->abofsrh))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsgv.word != (*cagCtrl)->abofsgv) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abofsgv  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsgv.word, 
                (kulong)(*cagCtrl)->abofsgv))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsgh.word != (*cagCtrl)->abofsgh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abofsgh  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsgh.word, 
                (kulong)(*cagCtrl)->abofsgh))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsbv.word != (*cagCtrl)->abofsbv) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abofsbv  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsbv.word, 
                (kulong)(*cagCtrl)->abofsbv))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsbh.word != (*cagCtrl)->abofsbh) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abofsbh  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abofsbh.word, 
                (kulong)(*cagCtrl)->abofsbh))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr1.word != (*cagCtrl)->abnlthr1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthr1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr1.word, 
               (kulong)(*cagCtrl)->abnlthr1))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg1.word != (*cagCtrl)->abnlthg1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthg1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg1.word, 
               (kulong)(*cagCtrl)->abnlthg1))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb1.word != (*cagCtrl)->abnlthb1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthb1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb1.word, 
               (kulong)(*cagCtrl)->abnlthb1))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar1.word != (*cagCtrl)->abnlgar1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgar1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar1.word, 
               (kulong)(*cagCtrl)->abnlgar1))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag1.word != (*cagCtrl)->abnlgag1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgag1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag1.word, 
               (kulong)(*cagCtrl)->abnlgag1))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab1.word != (*cagCtrl)->abnlgab1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgab1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab1.word, 
               (kulong)(*cagCtrl)->abnlgab1))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr2.word != (*cagCtrl)->abnlthr2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthr2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr2.word, 
               (kulong)(*cagCtrl)->abnlthr2))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg2.word != (*cagCtrl)->abnlthg2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthg2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg2.word, 
               (kulong)(*cagCtrl)->abnlthg2))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb2.word != (*cagCtrl)->abnlthb2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthb2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb2.word, 
               (kulong)(*cagCtrl)->abnlthb2))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar2.word != (*cagCtrl)->abnlgar2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgar2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar2.word, 
               (kulong)(*cagCtrl)->abnlgar2))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag2.word != (*cagCtrl)->abnlgag2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgag2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag2.word, 
               (kulong)(*cagCtrl)->abnlgag2))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab2.word != (*cagCtrl)->abnlgab2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgab2  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab2.word, 
               (kulong)(*cagCtrl)->abnlgab2))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr3.word != (*cagCtrl)->abnlthr3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthr3  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr3.word, 
               (kulong)(*cagCtrl)->abnlthr3))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg3.word != (*cagCtrl)->abnlthg3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthg3  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg3.word, 
               (kulong)(*cagCtrl)->abnlthg3))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb3.word != (*cagCtrl)->abnlthb3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthb3  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb3.word, 
               (kulong)(*cagCtrl)->abnlthb3))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar3.word != (*cagCtrl)->abnlgar3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgar3  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar3.word, 
               (kulong)(*cagCtrl)->abnlgar3))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag3.word != (*cagCtrl)->abnlgag3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgag3  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag3.word, 
               (kulong)(*cagCtrl)->abnlgag3))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab3.word != (*cagCtrl)->abnlgab3) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgab3  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab3.word, 
               (kulong)(*cagCtrl)->abnlgab3))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr4.word != (*cagCtrl)->abnlthr4) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthr4  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthr4.word, 
               (kulong)(*cagCtrl)->abnlthr4))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg4.word != (*cagCtrl)->abnlthg4) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthg4  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthg4.word, 
               (kulong)(*cagCtrl)->abnlthg4))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb4.word != (*cagCtrl)->abnlthb4) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlthb4  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlthb4.word, 
               (kulong)(*cagCtrl)->abnlthb4))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar4.word != (*cagCtrl)->abnlgar4) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgar4  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgar4.word, 
               (kulong)(*cagCtrl)->abnlgar4))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag4.word != (*cagCtrl)->abnlgag4) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgag4  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgag4.word, 
               (kulong)(*cagCtrl)->abnlgag4))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab4.word != (*cagCtrl)->abnlgab4) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:abnlgab4  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.abnlgab4.word, 
               (kulong)(*cagCtrl)->abnlgab4))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.bfglmt.word != (*cagCtrl)->bfglmt) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:bfglmt  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.bfglmt.word, (kulong)(*cagCtrl)->bfglmt))
        };

        if((kulong)&ioPro.imgPipe[unitNo].sro.cag.bfgth.word != (*cagCtrl)->bfgth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) %s result:bfgth  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.cag.bfgth.word, (kulong)(*cagCtrl)->bfgth))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_CAG_Cntl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_2_print_6(Impro22Print *self, E_IM_PRO_UNIT_NUM unitNo)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Start(%u) result:dpctrg 0x%08lx(%u)\n", 
            unitNo, (kulong)&ioPro.imgPipe[unitNo].sro.dpc.dpctrg.word, 
            ioPro.imgPipe[unitNo].sro.dpc.dpctrg.bit.dpctrg));
}

void im_pro_2_2_print_7(Impro22Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Stop(%u %u) result:dpctrg  0x%08lx(%u)\n", 
            unitNo, force, (kulong)&ioPro.imgPipe[unitNo].sro.dpc.dpctrg.word, 
            ioPro.imgPipe[unitNo].sro.dpc.dpctrg.bit.dpctrg));
}

void im_pro_2_2_print_8(Impro22Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_DPC_CTRL* dpcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].sro.dpc.dpcmd.bit.dpcmd != dpcCtrl->dpcMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Ctrl(%u) %s result:dpcmd  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.dpc.dpcmd.word, 
            ioPro.imgPipe[unitNo].sro.dpc.dpcmd.bit.dpcmd,dpcCtrl->dpcMode))
        };

        if(ioPro.imgPipe[unitNo].sro.dpc.dpcmd.bit.dpcrtz != dpcCtrl->threConv0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Ctrl(%u) %s result:dpcrtz  0x%08lx(%u) in(%u)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.dpc.dpcmd.word, 
            ioPro.imgPipe[unitNo].sro.dpc.dpcmd.bit.dpcrtz,dpcCtrl->threConv0))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Ctrl(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_2_print_9(Impro22Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Set_PAEN(%u %u) result:paen  0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&ioPro.imgPipe[unitNo].sro.dpc.dpcpaen.word, 
            ioPro.imgPipe[unitNo].sro.dpc.dpcpaen.bit.dpaen));
    DriverCommon_DDIM_PRINT(( "Im_PRO_DPC_Set_PAEN(%u %u) result:dpctrg  0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&ioPro.imgPipe[unitNo].sro.dpc.dpctrg.word, 
            ioPro.imgPipe[unitNo].sro.dpc.dpctrg.bit.dpctrg));
}
#endif

Impro22Print* impro_2_2_print_new(void)
{
	Impro22Print* self = k_object_new_with_private(IMPRO_TYPE_2_2_PRINT, sizeof(Impro22PrintPrivate));

	return self;
}

Impro22Print* impro_2_2_print_get(void)
{
	static Impro22Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_2_2_PRINT, sizeof(Impro22PrintPrivate));
	}

	return self;
}
