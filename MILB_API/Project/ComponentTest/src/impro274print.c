/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro274Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro274print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro274Print, impro_2_7_4_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_2_7_4_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro274PrintPrivate, IMPRO_TYPE_2_7_4_PRINT))


struct _Impro274PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_2_7_4_print_constructor(Impro274Print *self)
{
	Impro274PrintPrivate *priv = IMPRO_2_7_4_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_2_7_4_print_destructor(Impro274Print *self)
{
	Impro274PrintPrivate *priv = IMPRO_2_7_4_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
void im_pro_2_7_4_Print(Impro274Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
kint32 ercd, const T_IM_PRO_RDMA_SDC_ADDR** sdcCtrl)
{
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.word != (*sdcCtrl)->sdcctl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcctl  0x%08lx  reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.word,(kulong)(*sdcCtrl)->sdcctl))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcsgd.word != (*sdcCtrl)->sdcsgd) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcsgd  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcsgd.word,(kulong)(*sdcCtrl)->sdcsgd))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph01.dword != (*sdcCtrl)->sdcph01_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph01_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph01.dword,
            (kulong)(*sdcCtrl)->sdcph01_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph01.dword != (*sdcCtrl)->sdcph01_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph01_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph01.dword,
            (kulong)(*sdcCtrl)->sdcph01_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph02.dword != (*sdcCtrl)->sdcph02_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph02_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph02.dword,
            (kulong)(*sdcCtrl)->sdcph02_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph02.dword != (*sdcCtrl)->sdcph02_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph02_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph02.dword,
            (kulong)(*sdcCtrl)->sdcph02_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph03.dword != (*sdcCtrl)->sdcph03_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph03_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph03.dword,
            (kulong)(*sdcCtrl)->sdcph03_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph03.dword != (*sdcCtrl)->sdcph03_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph03_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph03.dword,
            (kulong)(*sdcCtrl)->sdcph03_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph04.dword != (*sdcCtrl)->sdcph04_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph04_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph04.dword,
            (kulong)(*sdcCtrl)->sdcph04_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph04.dword != (*sdcCtrl)->sdcph04_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph04_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph04.dword,
            (kulong)(*sdcCtrl)->sdcph04_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph05.dword != (*sdcCtrl)->sdcph05_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph05_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph05.dword,
            (kulong)(*sdcCtrl)->sdcph05_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph05.dword != (*sdcCtrl)->sdcph05_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph05_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph05.dword,
            (kulong)(*sdcCtrl)->sdcph05_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph06.dword != (*sdcCtrl)->sdcph06_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph06_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph06.dword,
            (kulong)(*sdcCtrl)->sdcph06_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph06.dword != (*sdcCtrl)->sdcph06_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph06_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph06.dword,
            (kulong)(*sdcCtrl)->sdcph06_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph07.dword != (*sdcCtrl)->sdcph07_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph07_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph07.dword,
            (kulong)(*sdcCtrl)->sdcph07_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph07.dword != (*sdcCtrl)->sdcph07_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph07_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph07.dword,
            (kulong)(*sdcCtrl)->sdcph07_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph08.dword != (*sdcCtrl)->sdcph08_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph08_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph08.dword,
            (kulong)(*sdcCtrl)->sdcph08_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph08.dword != (*sdcCtrl)->sdcph08_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph08_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph08.dword,
            (kulong)(*sdcCtrl)->sdcph08_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph09.dword != (*sdcCtrl)->sdcph09_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph09_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph09.dword,
            (kulong)(*sdcCtrl)->sdcph09_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph09.dword != (*sdcCtrl)->sdcph09_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph09_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph09.dword,
            (kulong)(*sdcCtrl)->sdcph09_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph11.dword != (*sdcCtrl)->sdcph11_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph11_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph11.dword,
            (kulong)(*sdcCtrl)->sdcph11_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph11.dword != (*sdcCtrl)->sdcph11_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph11_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph11.dword,
            (kulong)(*sdcCtrl)->sdcph11_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph12.dword != (*sdcCtrl)->sdcph12_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph12_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph12.dword,
            (kulong)(*sdcCtrl)->sdcph12_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph12.dword != (*sdcCtrl)->sdcph12_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph12_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph12.dword,
            (kulong)(*sdcCtrl)->sdcph12_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph13.dword != (*sdcCtrl)->sdcph13_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph13_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph13.dword,
            (kulong)(*sdcCtrl)->sdcph13_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph13.dword != (*sdcCtrl)->sdcph13_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph13_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph13.dword,
            (kulong)(*sdcCtrl)->sdcph13_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph14.dword != (*sdcCtrl)->sdcph14_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph14_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph14.dword,
            (kulong)(*sdcCtrl)->sdcph14_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph14.dword != (*sdcCtrl)->sdcph14_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph14_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph14.dword,
            (kulong)(*sdcCtrl)->sdcph14_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph15.dword != (*sdcCtrl)->sdcph15_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph15_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph15.dword,
            (kulong)(*sdcCtrl)->sdcph15_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph15.dword != (*sdcCtrl)->sdcph15_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph15_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph15.dword,
            (kulong)(*sdcCtrl)->sdcph15_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph16.dword != (*sdcCtrl)->sdcph16_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph16_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph16.dword,
            (kulong)(*sdcCtrl)->sdcph16_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph16.dword != (*sdcCtrl)->sdcph16_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph16_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph16.dword,
            (kulong)(*sdcCtrl)->sdcph16_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph17.dword != (*sdcCtrl)->sdcph17_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph17_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph17.dword,
            (kulong)(*sdcCtrl)->sdcph17_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph17.dword != (*sdcCtrl)->sdcph17_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph17_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph17.dword,
            (kulong)(*sdcCtrl)->sdcph17_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph18.dword != (*sdcCtrl)->sdcph18_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph18_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph18.dword,
            (kulong)(*sdcCtrl)->sdcph18_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph18.dword != (*sdcCtrl)->sdcph18_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph18_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph18.dword,
            (kulong)(*sdcCtrl)->sdcph18_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph19.dword != (*sdcCtrl)->sdcph19_0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph19_0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph19.dword,
            (kulong)(*sdcCtrl)->sdcph19_0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph19.dword != (*sdcCtrl)->sdcph19_1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcph19_1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph19.dword,
            (kulong)(*sdcCtrl)->sdcph19_1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.word != (*sdcCtrl)->sdcphW01) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcphW01  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.word,
            (kulong)(*sdcCtrl)->sdcphW01))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.word != (*sdcCtrl)->sdcphW02) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcphW02  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.word,
            (kulong)(*sdcCtrl)->sdcphW02))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW03.word != (*sdcCtrl)->sdcphW03) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcphW03  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW03.word,
            (kulong)(*sdcCtrl)->sdcphW03))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.word != (*sdcCtrl)->sdcphW10) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcphW10  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.word,
            (kulong)(*sdcCtrl)->sdcphW10))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.word != (*sdcCtrl)->sdcphW11) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcphW11  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.word,
            (kulong)(*sdcCtrl)->sdcphW11))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW13.word != (*sdcCtrl)->sdcphW12) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcphW12  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW13.word,
            (kulong)(*sdcCtrl)->sdcphW12))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw01.word != (*sdcCtrl)->sdcp1hw01) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1hw00  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw01.word,
            (kulong)(*sdcCtrl)->sdcp1hw01))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw02.word != (*sdcCtrl)->sdcp1hw02) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1hw01  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw02.word,
            (kulong)(*sdcCtrl)->sdcp1hw02))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw03.word != (*sdcCtrl)->sdcp1hw03) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1hw02  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw03.word,
            (kulong)(*sdcCtrl)->sdcp1hw03))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw04.word != (*sdcCtrl)->sdcp1hw04) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1hw03  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw04.word,
            (kulong)(*sdcCtrl)->sdcp1hw04))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw05.word != (*sdcCtrl)->sdcp1hw05) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1hw04  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw05.word,
            (kulong)(*sdcCtrl)->sdcp1hw05))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw11.word != (*sdcCtrl)->sdcp1hw11) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1hw10  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw11.word,
            (kulong)(*sdcCtrl)->sdcp1hw11))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw12.word != (*sdcCtrl)->sdcp1hw12) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1hw11  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw12.word,
            (kulong)(*sdcCtrl)->sdcp1hw12))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw13.word != (*sdcCtrl)->sdcp1hw13) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1hw12  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw13.word,
            (kulong)(*sdcCtrl)->sdcp1hw13))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw14.word != (*sdcCtrl)->sdcp1hw14) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1hw13  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw14.word,
            (kulong)(*sdcCtrl)->sdcp1hw14))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw15.word != (*sdcCtrl)->sdcp1hw15) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1hw14  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw15.word,
            (kulong)(*sdcCtrl)->sdcp1hw15))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw01.word != (*sdcCtrl)->sdcn1hw01) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1hw00  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw01.word,
            (kulong)(*sdcCtrl)->sdcn1hw01))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw02.word != (*sdcCtrl)->sdcn1hw02) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1hw01  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw02.word,
            (kulong)(*sdcCtrl)->sdcn1hw02))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw03.word != (*sdcCtrl)->sdcn1hw03) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1hw02  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw03.word,
            (kulong)(*sdcCtrl)->sdcn1hw03))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw04.word != (*sdcCtrl)->sdcn1hw04) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1hw03  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw04.word,
            (kulong)(*sdcCtrl)->sdcn1hw04))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw05.word != (*sdcCtrl)->sdcn1hw05) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1hw04  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw05.word,
            (kulong)(*sdcCtrl)->sdcn1hw05))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw11.word != (*sdcCtrl)->sdcn1hw11) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1hw10  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw11.word,
            (kulong)(*sdcCtrl)->sdcn1hw11))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw12.word != (*sdcCtrl)->sdcn1hw12) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1hw11  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw12.word,
            (kulong)(*sdcCtrl)->sdcn1hw12))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw13.word != (*sdcCtrl)->sdcn1hw13) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1hw12  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw13.word,
            (kulong)(*sdcCtrl)->sdcn1hw13))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw14.word != (*sdcCtrl)->sdcn1hw14) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1hw13  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw14.word,
            (kulong)(*sdcCtrl)->sdcn1hw14))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw15.word != (*sdcCtrl)->sdcn1hw15) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1hw14  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw15.word,
            (kulong)(*sdcCtrl)->sdcn1hw15))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw01.word != (*sdcCtrl)->sdcp2hw01) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2hw00  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw01.word,
            (kulong)(*sdcCtrl)->sdcp2hw01))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw02.word != (*sdcCtrl)->sdcp2hw02) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2hw01  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw02.word,
            (kulong)(*sdcCtrl)->sdcp2hw02))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw03.word != (*sdcCtrl)->sdcp2hw03) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2hw02  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw03.word,
            (kulong)(*sdcCtrl)->sdcp2hw03))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw04.word != (*sdcCtrl)->sdcp2hw04) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2hw03  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw04.word,
            (kulong)(*sdcCtrl)->sdcp2hw04))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw05.word != (*sdcCtrl)->sdcp2hw05) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2hw04  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw05.word,
            (kulong)(*sdcCtrl)->sdcp2hw05))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw11.word != (*sdcCtrl)->sdcp2hw11) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2hw10  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw11.word,
            (kulong)(*sdcCtrl)->sdcp2hw11))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw12.word != (*sdcCtrl)->sdcp2hw12) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2hw11  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw12.word,
            (kulong)(*sdcCtrl)->sdcp2hw12))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw13.word != (*sdcCtrl)->sdcp2hw13) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2hw12  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw13.word,
            (kulong)(*sdcCtrl)->sdcp2hw13))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw14.word != (*sdcCtrl)->sdcp2hw14) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2hw13  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw14.word,
            (kulong)(*sdcCtrl)->sdcp2hw14))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw15.word != (*sdcCtrl)->sdcp2hw15) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2hw14  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw15.word,
            (kulong)(*sdcCtrl)->sdcp2hw15))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw01.word != (*sdcCtrl)->sdcn2hw01) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2hw00  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw01.word,
            (kulong)(*sdcCtrl)->sdcn2hw01))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw02.word != (*sdcCtrl)->sdcn2hw02) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2hw01  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw02.word,
            (kulong)(*sdcCtrl)->sdcn2hw02))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw03.word != (*sdcCtrl)->sdcn2hw03) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2hw02  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw03.word,
            (kulong)(*sdcCtrl)->sdcn2hw03))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw04.word != (*sdcCtrl)->sdcn2hw04) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2hw03  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw04.word,
            (kulong)(*sdcCtrl)->sdcn2hw04))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw05.word != (*sdcCtrl)->sdcn2hw05) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2hw04  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw05.word,
            (kulong)(*sdcCtrl)->sdcn2hw05))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw11.word != (*sdcCtrl)->sdcn2hw11) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2hw10  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw11.word,
            (kulong)(*sdcCtrl)->sdcn2hw11))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw12.word != (*sdcCtrl)->sdcn2hw12) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2hw11  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw12.word,
            (kulong)(*sdcCtrl)->sdcn2hw12))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw13.word != (*sdcCtrl)->sdcn2hw13) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2hw12  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw13.word,
            (kulong)(*sdcCtrl)->sdcn2hw13))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw14.word != (*sdcCtrl)->sdcn2hw14) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2hw13  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw14.word,
            (kulong)(*sdcCtrl)->sdcn2hw14))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw15.word != (*sdcCtrl)->sdcn2hw15) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2hw14  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw15.word,
            (kulong)(*sdcCtrl)->sdcn2hw15))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.word != (*sdcCtrl)->sdcpc01) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc01  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.word,
            (kulong)(*sdcCtrl)->sdcpc01))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.word != (*sdcCtrl)->sdcpc02) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc02  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.word,
            (kulong)(*sdcCtrl)->sdcpc02))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.word != (*sdcCtrl)->sdcpc03) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc03  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.word,
            (kulong)(*sdcCtrl)->sdcpc03))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.word != (*sdcCtrl)->sdcpc04) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc04  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.word,
            (kulong)(*sdcCtrl)->sdcpc04))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.word != (*sdcCtrl)->sdcpc05) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc05  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.word,
            (kulong)(*sdcCtrl)->sdcpc05))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.word != (*sdcCtrl)->sdcpc06) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc06  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.word,
            (kulong)(*sdcCtrl)->sdcpc06))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.word != (*sdcCtrl)->sdcpc07) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc07  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.word,
            (kulong)(*sdcCtrl)->sdcpc07))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.word != (*sdcCtrl)->sdcpc08) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc08  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.word,
            (kulong)(*sdcCtrl)->sdcpc08))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.word != (*sdcCtrl)->sdcpc09) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc09  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.word,
            (kulong)(*sdcCtrl)->sdcpc09))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.word != (*sdcCtrl)->sdcpc010) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc010  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.word,
            (kulong)(*sdcCtrl)->sdcpc010))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.word != (*sdcCtrl)->sdcpc011) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc011  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.word,
            (kulong)(*sdcCtrl)->sdcpc011))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.word != (*sdcCtrl)->sdcpc012) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc012  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.word,
            (kulong)(*sdcCtrl)->sdcpc012))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.word != (*sdcCtrl)->sdcpc013) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc013  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.word,
            (kulong)(*sdcCtrl)->sdcpc013))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.word != (*sdcCtrl)->sdcpc014) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc014  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.word,
            (kulong)(*sdcCtrl)->sdcpc014))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.word != (*sdcCtrl)->sdcpc015) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc015  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.word,
            (kulong)(*sdcCtrl)->sdcpc015))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.word != (*sdcCtrl)->sdcpc016) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc016  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.word,
            (kulong)(*sdcCtrl)->sdcpc016))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.word != (*sdcCtrl)->sdcpc11) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc11  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.word,
            (kulong)(*sdcCtrl)->sdcpc11))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.word != (*sdcCtrl)->sdcpc12) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc12  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.word,
            (kulong)(*sdcCtrl)->sdcpc12))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.word != (*sdcCtrl)->sdcpc13) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc13  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.word,
            (kulong)(*sdcCtrl)->sdcpc13))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.word != (*sdcCtrl)->sdcpc14) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc14  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.word,
            (kulong)(*sdcCtrl)->sdcpc14))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.word != (*sdcCtrl)->sdcpc15) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc15  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.word,
            (kulong)(*sdcCtrl)->sdcpc15))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.word != (*sdcCtrl)->sdcpc16) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc16  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.word,
            (kulong)(*sdcCtrl)->sdcpc16))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.word != (*sdcCtrl)->sdcpc17) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc17  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.word,
            (kulong)(*sdcCtrl)->sdcpc17))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.word != (*sdcCtrl)->sdcpc18) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc18  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.word,
            (kulong)(*sdcCtrl)->sdcpc18))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.word != (*sdcCtrl)->sdcpc19) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc19  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.word,
            (kulong)(*sdcCtrl)->sdcpc19))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.word != (*sdcCtrl)->sdcpc110) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc110  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.word,
            (kulong)(*sdcCtrl)->sdcpc110))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.word != (*sdcCtrl)->sdcpc111) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc111  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.word,
            (kulong)(*sdcCtrl)->sdcpc111))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.word != (*sdcCtrl)->sdcpc112) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc112  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.word,
            (kulong)(*sdcCtrl)->sdcpc112))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.word != (*sdcCtrl)->sdcpc113) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc113  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.word,
            (kulong)(*sdcCtrl)->sdcpc113))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.word != (*sdcCtrl)->sdcpc114) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc114  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.word,
            (kulong)(*sdcCtrl)->sdcpc114))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.word != (*sdcCtrl)->sdcpc115) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc115  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.word,
            (kulong)(*sdcCtrl)->sdcpc115))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.word != (*sdcCtrl)->sdcpc116) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpc116  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.word,
            (kulong)(*sdcCtrl)->sdcpc116))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpcW0.word != (*sdcCtrl)->sdcpcW0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpcW0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpcW0.word,
            (kulong)(*sdcCtrl)->sdcpcW0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpcW1.word != (*sdcCtrl)->sdcpcW1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcpcW1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpcW1.word,
            (kulong)(*sdcCtrl)->sdcpcW1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1cw0.word != (*sdcCtrl)->sdcp1cw0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1cw0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1cw0.word,
            (kulong)(*sdcCtrl)->sdcp1cw0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1cw1.word != (*sdcCtrl)->sdcp1cw1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp1cw1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1cw1.word,
            (kulong)(*sdcCtrl)->sdcp1cw1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1cw0.word != (*sdcCtrl)->sdcn1cw0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1cw0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1cw0.word,
            (kulong)(*sdcCtrl)->sdcn1cw0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1cw1.word != (*sdcCtrl)->sdcn1cw1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn1cw1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1cw1.word,
            (kulong)(*sdcCtrl)->sdcn1cw1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2cw0.word != (*sdcCtrl)->sdcp2cw0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2cw0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2cw0.word,
            (kulong)(*sdcCtrl)->sdcp2cw0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2cw1.word != (*sdcCtrl)->sdcp2cw1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcp2cw1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2cw1.word,
            (kulong)(*sdcCtrl)->sdcp2cw1))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2cw0.word != (*sdcCtrl)->sdcn2cw0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2cw0  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2cw0.word,
            (kulong)(*sdcCtrl)->sdcn2cw0))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2cw1.word != (*sdcCtrl)->sdcn2cw1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcn2cw1  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2cw1.word,
            (kulong)(*sdcCtrl)->sdcn2cw1))
        };

}
Impro274Print* impro_2_7_4_print_new(void)
{
	Impro274Print* self = k_object_new_with_private(IMPRO_TYPE_2_7_4_PRINT, sizeof(Impro274PrintPrivate));

	return self;
}

Impro274Print* impro_2_7_4_print_get(void)
{
	static Impro274Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_2_7_4_PRINT, sizeof(Impro274PrintPrivate));
	}

	return self;
}
