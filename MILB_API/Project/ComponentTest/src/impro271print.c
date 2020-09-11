/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro271Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro271print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro271Print, impro_2_7_1_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_2_7_1_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro271PrintPrivate, IMPRO_TYPE_2_7_1_PRINT))


struct _Impro271PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_2_7_1_print_constructor(Impro271Print *self)
{
	Impro271PrintPrivate *priv = IMPRO_2_7_1_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_2_7_1_print_destructor(Impro271Print *self)
{
	Impro271PrintPrivate *priv = IMPRO_2_7_1_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
void im_pro_2_7_1_Print(Impro271Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch,
                         kint32 ercd, T_IM_PRO_SDC_CTRL_AFPB* sdcCtrl)
{
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph01.bit.sdcph0_0 != sdcCtrl->hPattern0[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph0_0  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph01.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph01.bit.sdcph0_0,sdcCtrl->hPattern0[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph02.bit.sdcph0_1 != sdcCtrl->hPattern0[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph0_1  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph02.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph02.bit.sdcph0_1,sdcCtrl->hPattern0[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph03.bit.sdcph0_2 != sdcCtrl->hPattern0[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph0_2  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph03.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph03.bit.sdcph0_2,sdcCtrl->hPattern0[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph04.bit.sdcph0_3 != sdcCtrl->hPattern0[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph0_3  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph04.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph04.bit.sdcph0_3,sdcCtrl->hPattern0[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph05.bit.sdcph0_4 != sdcCtrl->hPattern0[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph0_4  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph05.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph05.bit.sdcph0_4,sdcCtrl->hPattern0[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph06.bit.sdcph0_5 != sdcCtrl->hPattern0[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph0_5  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph06.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph06.bit.sdcph0_5,sdcCtrl->hPattern0[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph07.bit.sdcph0_6 != sdcCtrl->hPattern0[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph0_6  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph07.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph07.bit.sdcph0_6,sdcCtrl->hPattern0[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph08.bit.sdcph0_7 != sdcCtrl->hPattern0[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph0_7  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph08.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph08.bit.sdcph0_7,sdcCtrl->hPattern0[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph09.bit.sdcph0_8 != sdcCtrl->hPattern0[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph0_8  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph09.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph0.sdcph09.bit.sdcph0_8,sdcCtrl->hPattern0[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph11.bit.sdcph1_0 != sdcCtrl->hPattern1[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph1_0  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph11.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph11.bit.sdcph1_0,sdcCtrl->hPattern1[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph12.bit.sdcph1_1 != sdcCtrl->hPattern1[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph1_1  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph12.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph12.bit.sdcph1_1,sdcCtrl->hPattern1[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph13.bit.sdcph1_2 != sdcCtrl->hPattern1[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph1_2  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph13.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph13.bit.sdcph1_2,sdcCtrl->hPattern1[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph14.bit.sdcph1_3 != sdcCtrl->hPattern1[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph1_3  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph14.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph14.bit.sdcph1_3,sdcCtrl->hPattern1[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph15.bit.sdcph1_4 != sdcCtrl->hPattern1[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph1_4  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph15.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph15.bit.sdcph1_4,sdcCtrl->hPattern1[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph16.bit.sdcph1_5 != sdcCtrl->hPattern1[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph1_5  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph16.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph16.bit.sdcph1_5,sdcCtrl->hPattern1[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph17.bit.sdcph1_6 != sdcCtrl->hPattern1[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph1_6  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph17.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph17.bit.sdcph1_6,sdcCtrl->hPattern1[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph18.bit.sdcph1_7 != sdcCtrl->hPattern1[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph1_7  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph18.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph18.bit.sdcph1_7,sdcCtrl->hPattern1[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph19.bit.sdcph1_8 != sdcCtrl->hPattern1[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcph1_8  0x%08lx(%llu) input_param(%llu)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph19.dword, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcph1.sdcph19.bit.sdcph1_8,sdcCtrl->hPattern1[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.bit.sdcphW0_0 != sdcCtrl->hPattern0ValidWidth[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW0_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.bit.sdcphW0_0,sdcCtrl->hPattern0ValidWidth[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.bit.sdcphW0_1 != sdcCtrl->hPattern0ValidWidth[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW0_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.bit.sdcphW0_1,sdcCtrl->hPattern0ValidWidth[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.bit.sdcphW0_2 != sdcCtrl->hPattern0ValidWidth[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW0_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.bit.sdcphW0_2,sdcCtrl->hPattern0ValidWidth[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.bit.sdcphW0_3 != sdcCtrl->hPattern0ValidWidth[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW0_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW01.bit.sdcphW0_3,sdcCtrl->hPattern0ValidWidth[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.bit.sdcphW0_4 != sdcCtrl->hPattern0ValidWidth[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW0_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.bit.sdcphW0_4,sdcCtrl->hPattern0ValidWidth[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.bit.sdcphW0_5 != sdcCtrl->hPattern0ValidWidth[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW0_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.bit.sdcphW0_5,sdcCtrl->hPattern0ValidWidth[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.bit.sdcphW0_6 != sdcCtrl->hPattern0ValidWidth[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW0_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.bit.sdcphW0_6,sdcCtrl->hPattern0ValidWidth[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.bit.sdcphW0_7 != sdcCtrl->hPattern0ValidWidth[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW0_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW02.bit.sdcphW0_7,sdcCtrl->hPattern0ValidWidth[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW03.bit.sdcphW0_8 != sdcCtrl->hPattern0ValidWidth[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW0_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW0.sdcphW03.bit.sdcphW0_8,sdcCtrl->hPattern0ValidWidth[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.bit.sdcphW1_0 != sdcCtrl->hPattern1ValidWidth[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW1_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.bit.sdcphW1_0,sdcCtrl->hPattern1ValidWidth[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.bit.sdcphW1_1 != sdcCtrl->hPattern1ValidWidth[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW1_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.bit.sdcphW1_1,sdcCtrl->hPattern1ValidWidth[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.bit.sdcphW1_2 != sdcCtrl->hPattern1ValidWidth[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW1_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.bit.sdcphW1_2,sdcCtrl->hPattern1ValidWidth[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.bit.sdcphW1_3 != sdcCtrl->hPattern1ValidWidth[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW1_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW11.bit.sdcphW1_3,sdcCtrl->hPattern1ValidWidth[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.bit.sdcphW1_4 != sdcCtrl->hPattern1ValidWidth[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW1_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.bit.sdcphW1_4,sdcCtrl->hPattern1ValidWidth[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.bit.sdcphW1_5 != sdcCtrl->hPattern1ValidWidth[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW1_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.bit.sdcphW1_5,sdcCtrl->hPattern1ValidWidth[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.bit.sdcphW1_6 != sdcCtrl->hPattern1ValidWidth[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW1_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.bit.sdcphW1_6,sdcCtrl->hPattern1ValidWidth[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.bit.sdcphW1_7 != sdcCtrl->hPattern1ValidWidth[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW1_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW12.bit.sdcphW1_7,sdcCtrl->hPattern1ValidWidth[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW13.bit.sdcphW1_8 != sdcCtrl->hPattern1ValidWidth[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcphW1_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcphW1.sdcphW13.bit.sdcphW1_8,sdcCtrl->hPattern1ValidWidth[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw01.bit.sdcp1hw0_0 
            != sdcCtrl->hPattern0R1ValidWidth[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw0_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw01.bit.sdcp1hw0_0,
            sdcCtrl->hPattern0R1ValidWidth[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw01.bit.sdcp1hw0_1 
        != sdcCtrl->hPattern0R1ValidWidth[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw0_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw01.bit.sdcp1hw0_1,
            sdcCtrl->hPattern0R1ValidWidth[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw02.bit.sdcp1hw0_2 
        != sdcCtrl->hPattern0R1ValidWidth[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw0_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw02.bit.sdcp1hw0_2,
            sdcCtrl->hPattern0R1ValidWidth[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw02.bit.sdcp1hw0_3 
        != sdcCtrl->hPattern0R1ValidWidth[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw0_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw02.bit.sdcp1hw0_3,
            sdcCtrl->hPattern0R1ValidWidth[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw03.bit.sdcp1hw0_4 
        != sdcCtrl->hPattern0R1ValidWidth[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw0_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw03.bit.sdcp1hw0_4,
            sdcCtrl->hPattern0R1ValidWidth[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw03.bit.sdcp1hw0_5 
        != sdcCtrl->hPattern0R1ValidWidth[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw0_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw03.bit.sdcp1hw0_5,
            sdcCtrl->hPattern0R1ValidWidth[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw04.bit.sdcp1hw0_6 
        != sdcCtrl->hPattern0R1ValidWidth[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw0_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw04.bit.sdcp1hw0_6,
            sdcCtrl->hPattern0R1ValidWidth[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw04.bit.sdcp1hw0_7 
        != sdcCtrl->hPattern0R1ValidWidth[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw0_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw04.bit.sdcp1hw0_7,
            sdcCtrl->hPattern0R1ValidWidth[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw05.bit.sdcp1hw0_8 
        != sdcCtrl->hPattern0R1ValidWidth[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw0_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw05.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw0.sdcp1hw05.bit.sdcp1hw0_8,
            sdcCtrl->hPattern0R1ValidWidth[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw11.bit.sdcp1hw1_0 
        != sdcCtrl->hPattern1R1ValidWidth[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw1_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw11.bit.sdcp1hw1_0,
            sdcCtrl->hPattern1R1ValidWidth[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw11.bit.sdcp1hw1_1 
        != sdcCtrl->hPattern1R1ValidWidth[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw1_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw11.bit.sdcp1hw1_1,
            sdcCtrl->hPattern1R1ValidWidth[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw12.bit.sdcp1hw1_2 
        != sdcCtrl->hPattern1R1ValidWidth[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw1_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw12.bit.sdcp1hw1_2,
            sdcCtrl->hPattern1R1ValidWidth[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw12.bit.sdcp1hw1_3 
        != sdcCtrl->hPattern1R1ValidWidth[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw1_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw12.bit.sdcp1hw1_3,
            sdcCtrl->hPattern1R1ValidWidth[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw13.bit.sdcp1hw1_4 
        != sdcCtrl->hPattern1R1ValidWidth[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw1_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw13.bit.sdcp1hw1_4,
            sdcCtrl->hPattern1R1ValidWidth[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw13.bit.sdcp1hw1_5 
        != sdcCtrl->hPattern1R1ValidWidth[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw1_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw13.bit.sdcp1hw1_5,
            sdcCtrl->hPattern1R1ValidWidth[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw14.bit.sdcp1hw1_6 
        != sdcCtrl->hPattern1R1ValidWidth[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw1_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw14.bit.sdcp1hw1_6,
            sdcCtrl->hPattern1R1ValidWidth[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw14.bit.sdcp1hw1_7 
        != sdcCtrl->hPattern1R1ValidWidth[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw1_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw14.bit.sdcp1hw1_7,
            sdcCtrl->hPattern1R1ValidWidth[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw15.bit.sdcp1hw1_8 
        != sdcCtrl->hPattern1R1ValidWidth[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1hw1_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw15.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1hw1.sdcp1hw15.bit.sdcp1hw1_8,
            sdcCtrl->hPattern1R1ValidWidth[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw01.bit.sdcn1hw0_0 
        != sdcCtrl->hPattern0R1InvalidWidth[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw0_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw01.bit.sdcn1hw0_0,
            sdcCtrl->hPattern0R1InvalidWidth[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw01.bit.sdcn1hw0_1 
        != sdcCtrl->hPattern0R1InvalidWidth[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw0_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw01.bit.sdcn1hw0_1,
            sdcCtrl->hPattern0R1InvalidWidth[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw02.bit.sdcn1hw0_2 
        != sdcCtrl->hPattern0R1InvalidWidth[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw0_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw02.bit.sdcn1hw0_2,
            sdcCtrl->hPattern0R1InvalidWidth[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw02.bit.sdcn1hw0_3 
        != sdcCtrl->hPattern0R1InvalidWidth[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw0_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw02.bit.sdcn1hw0_3,
            sdcCtrl->hPattern0R1InvalidWidth[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw03.bit.sdcn1hw0_4 
        != sdcCtrl->hPattern0R1InvalidWidth[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw0_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw03.bit.sdcn1hw0_4,
            sdcCtrl->hPattern0R1InvalidWidth[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw03.bit.sdcn1hw0_5 
        != sdcCtrl->hPattern0R1InvalidWidth[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw0_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw03.bit.sdcn1hw0_5,
            sdcCtrl->hPattern0R1InvalidWidth[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw04.bit.sdcn1hw0_6 
        != sdcCtrl->hPattern0R1InvalidWidth[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw0_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw04.bit.sdcn1hw0_6,
            sdcCtrl->hPattern0R1InvalidWidth[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw04.bit.sdcn1hw0_7 
        != sdcCtrl->hPattern0R1InvalidWidth[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw0_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw04.bit.sdcn1hw0_7,
            sdcCtrl->hPattern0R1InvalidWidth[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw05.bit.sdcn1hw0_8 
        != sdcCtrl->hPattern0R1InvalidWidth[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw0_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw05.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw0.sdcn1hw05.bit.sdcn1hw0_8,
            sdcCtrl->hPattern0R1InvalidWidth[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw11.bit.sdcn1hw1_0 
        != sdcCtrl->hPattern1R1InvalidWidth[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw1_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw11.bit.sdcn1hw1_0,
            sdcCtrl->hPattern1R1InvalidWidth[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw11.bit.sdcn1hw1_1 
        != sdcCtrl->hPattern1R1InvalidWidth[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw1_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw11.bit.sdcn1hw1_1,
            sdcCtrl->hPattern1R1InvalidWidth[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw12.bit.sdcn1hw1_2 
        != sdcCtrl->hPattern1R1InvalidWidth[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw1_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw12.bit.sdcn1hw1_2,
            sdcCtrl->hPattern1R1InvalidWidth[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw12.bit.sdcn1hw1_3 
        != sdcCtrl->hPattern1R1InvalidWidth[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw1_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw12.bit.sdcn1hw1_3,
            sdcCtrl->hPattern1R1InvalidWidth[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw13.bit.sdcn1hw1_4 
        != sdcCtrl->hPattern1R1InvalidWidth[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw1_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw13.bit.sdcn1hw1_4,
            sdcCtrl->hPattern1R1InvalidWidth[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw13.bit.sdcn1hw1_5 
        != sdcCtrl->hPattern1R1InvalidWidth[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw1_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw13.bit.sdcn1hw1_5,
            sdcCtrl->hPattern1R1InvalidWidth[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw14.bit.sdcn1hw1_6 
        != sdcCtrl->hPattern1R1InvalidWidth[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw1_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw14.bit.sdcn1hw1_6,
            sdcCtrl->hPattern1R1InvalidWidth[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw14.bit.sdcn1hw1_7 
        != sdcCtrl->hPattern1R1InvalidWidth[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw1_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw14.bit.sdcn1hw1_7,
            sdcCtrl->hPattern1R1InvalidWidth[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw15.bit.sdcn1hw1_8 
        != sdcCtrl->hPattern1R1InvalidWidth[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1hw1_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw15.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1hw1.sdcn1hw15.bit.sdcn1hw1_8,
            sdcCtrl->hPattern1R1InvalidWidth[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw01.bit.sdcp2hw0_0 
        != sdcCtrl->hPattern0R2ValidWidth[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw0_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw01.bit.sdcp2hw0_0,
            sdcCtrl->hPattern0R2ValidWidth[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw01.bit.sdcp2hw0_1 
        != sdcCtrl->hPattern0R2ValidWidth[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw0_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw01.bit.sdcp2hw0_1,
            sdcCtrl->hPattern0R2ValidWidth[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw02.bit.sdcp2hw0_2 
        != sdcCtrl->hPattern0R2ValidWidth[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw0_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw02.bit.sdcp2hw0_2,
            sdcCtrl->hPattern0R2ValidWidth[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw02.bit.sdcp2hw0_3 
        != sdcCtrl->hPattern0R2ValidWidth[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw0_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw02.bit.sdcp2hw0_3,
            sdcCtrl->hPattern0R2ValidWidth[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw03.bit.sdcp2hw0_4 
        != sdcCtrl->hPattern0R2ValidWidth[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw0_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw03.bit.sdcp2hw0_4,
            sdcCtrl->hPattern0R2ValidWidth[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw03.bit.sdcp2hw0_5 
        != sdcCtrl->hPattern0R2ValidWidth[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw0_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw03.bit.sdcp2hw0_5,
            sdcCtrl->hPattern0R2ValidWidth[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw04.bit.sdcp2hw0_6 
        != sdcCtrl->hPattern0R2ValidWidth[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw0_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw04.bit.sdcp2hw0_6,
            sdcCtrl->hPattern0R2ValidWidth[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw04.bit.sdcp2hw0_7 
        != sdcCtrl->hPattern0R2ValidWidth[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw0_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw04.bit.sdcp2hw0_7,
            sdcCtrl->hPattern0R2ValidWidth[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw05.bit.sdcp2hw0_8 
        != sdcCtrl->hPattern0R2ValidWidth[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw0_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw05.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw0.sdcp2hw05.bit.sdcp2hw0_8,
            sdcCtrl->hPattern0R2ValidWidth[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw11.bit.sdcp2hw1_0 
        != sdcCtrl->hPattern1R2ValidWidth[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw1_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw11.bit.sdcp2hw1_0,
            sdcCtrl->hPattern1R2ValidWidth[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw11.bit.sdcp2hw1_1 
        != sdcCtrl->hPattern1R2ValidWidth[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw1_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw11.bit.sdcp2hw1_1,
            sdcCtrl->hPattern1R2ValidWidth[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw12.bit.sdcp2hw1_2 
        != sdcCtrl->hPattern1R2ValidWidth[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw1_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw12.bit.sdcp2hw1_2,
            sdcCtrl->hPattern1R2ValidWidth[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw12.bit.sdcp2hw1_3 
        != sdcCtrl->hPattern1R2ValidWidth[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw1_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw12.bit.sdcp2hw1_3,
            sdcCtrl->hPattern1R2ValidWidth[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw13.bit.sdcp2hw1_4 
        != sdcCtrl->hPattern1R2ValidWidth[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw1_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw13.bit.sdcp2hw1_4,
            sdcCtrl->hPattern1R2ValidWidth[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw13.bit.sdcp2hw1_5 
        != sdcCtrl->hPattern1R2ValidWidth[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw1_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw13.bit.sdcp2hw1_5,
            sdcCtrl->hPattern1R2ValidWidth[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw14.bit.sdcp2hw1_6 
        != sdcCtrl->hPattern1R2ValidWidth[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw1_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw14.bit.sdcp2hw1_6,
            sdcCtrl->hPattern1R2ValidWidth[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw14.bit.sdcp2hw1_7 
        != sdcCtrl->hPattern1R2ValidWidth[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw1_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw14.bit.sdcp2hw1_7,
            sdcCtrl->hPattern1R2ValidWidth[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw15.bit.sdcp2hw1_8 
        != sdcCtrl->hPattern1R2ValidWidth[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2hw1_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw15.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2hw1.sdcp2hw15.bit.sdcp2hw1_8,
            sdcCtrl->hPattern1R2ValidWidth[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw01.bit.sdcn2hw0_0 
        != sdcCtrl->hPattern0R2InvalidWidth[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw0_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw01.bit.sdcn2hw0_0,
            sdcCtrl->hPattern0R2InvalidWidth[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw01.bit.sdcn2hw0_1 
        != sdcCtrl->hPattern0R2InvalidWidth[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw0_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw01.bit.sdcn2hw0_1,
            sdcCtrl->hPattern0R2InvalidWidth[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw02.bit.sdcn2hw0_2 
        != sdcCtrl->hPattern0R2InvalidWidth[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw0_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw02.bit.sdcn2hw0_2,
            sdcCtrl->hPattern0R2InvalidWidth[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw02.bit.sdcn2hw0_3 
        != sdcCtrl->hPattern0R2InvalidWidth[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw0_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw02.bit.sdcn2hw0_3,
            sdcCtrl->hPattern0R2InvalidWidth[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw03.bit.sdcn2hw0_4 
        != sdcCtrl->hPattern0R2InvalidWidth[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw0_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw03.bit.sdcn2hw0_4,
            sdcCtrl->hPattern0R2InvalidWidth[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw03.bit.sdcn2hw0_5 
        != sdcCtrl->hPattern0R2InvalidWidth[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw0_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw03.bit.sdcn2hw0_5,
            sdcCtrl->hPattern0R2InvalidWidth[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw04.bit.sdcn2hw0_6 
        != sdcCtrl->hPattern0R2InvalidWidth[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw0_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw04.bit.sdcn2hw0_6,
            sdcCtrl->hPattern0R2InvalidWidth[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw04.bit.sdcn2hw0_7 
        != sdcCtrl->hPattern0R2InvalidWidth[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw0_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw04.bit.sdcn2hw0_7,
            sdcCtrl->hPattern0R2InvalidWidth[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw05.bit.sdcn2hw0_8 
        != sdcCtrl->hPattern0R2InvalidWidth[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw0_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw05.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw0.sdcn2hw05.bit.sdcn2hw0_8,
            sdcCtrl->hPattern0R2InvalidWidth[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw11.bit.sdcn2hw1_0 
        != sdcCtrl->hPattern1R2InvalidWidth[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw1_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw11.bit.sdcn2hw1_0,
            sdcCtrl->hPattern1R2InvalidWidth[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw11.bit.sdcn2hw1_1 
        != sdcCtrl->hPattern1R2InvalidWidth[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw1_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw11.bit.sdcn2hw1_1,
            sdcCtrl->hPattern1R2InvalidWidth[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw12.bit.sdcn2hw1_2 
        != sdcCtrl->hPattern1R2InvalidWidth[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw1_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw12.bit.sdcn2hw1_2,
            sdcCtrl->hPattern1R2InvalidWidth[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw12.bit.sdcn2hw1_3 
        != sdcCtrl->hPattern1R2InvalidWidth[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw1_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw12.bit.sdcn2hw1_3,
            sdcCtrl->hPattern1R2InvalidWidth[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw13.bit.sdcn2hw1_4 
        != sdcCtrl->hPattern1R2InvalidWidth[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw1_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw13.bit.sdcn2hw1_4,
            sdcCtrl->hPattern1R2InvalidWidth[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw13.bit.sdcn2hw1_5 
        != sdcCtrl->hPattern1R2InvalidWidth[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw1_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw13.bit.sdcn2hw1_5,
            sdcCtrl->hPattern1R2InvalidWidth[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw14.bit.sdcn2hw1_6 
        != sdcCtrl->hPattern1R2InvalidWidth[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw1_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw14.bit.sdcn2hw1_6,
            sdcCtrl->hPattern1R2InvalidWidth[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw14.bit.sdcn2hw1_7 
        != sdcCtrl->hPattern1R2InvalidWidth[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw1_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw14.bit.sdcn2hw1_7,
            sdcCtrl->hPattern1R2InvalidWidth[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw15.bit.sdcn2hw1_8 
        != sdcCtrl->hPattern1R2InvalidWidth[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2hw1_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw15.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2hw1.sdcn2hw15.bit.sdcn2hw1_8,
            sdcCtrl->hPattern1R2InvalidWidth[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc0_0 != sdcCtrl->hColumnPattern0[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc0_0,sdcCtrl->hColumnPattern0[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc0_1 != sdcCtrl->hColumnPattern0[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc0_1,sdcCtrl->hColumnPattern0[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc0_2 != sdcCtrl->hColumnPattern0[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc0_2,sdcCtrl->hColumnPattern0[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc0_3 != sdcCtrl->hColumnPattern0[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc01.bit.sdcpc0_3,sdcCtrl->hColumnPattern0[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc0_4 != sdcCtrl->hColumnPattern0[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc0_4,sdcCtrl->hColumnPattern0[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc0_5 != sdcCtrl->hColumnPattern0[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc0_5,sdcCtrl->hColumnPattern0[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc0_6 != sdcCtrl->hColumnPattern0[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc0_6,sdcCtrl->hColumnPattern0[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc0_7 != sdcCtrl->hColumnPattern0[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc02.bit.sdcpc0_7,sdcCtrl->hColumnPattern0[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc0_8 != sdcCtrl->hColumnPattern0[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc0_8,sdcCtrl->hColumnPattern0[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc0_9 != sdcCtrl->hColumnPattern0[9]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_9  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc0_9,sdcCtrl->hColumnPattern0[9]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc0_10 != sdcCtrl->hColumnPattern0[10]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_10  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc0_10,sdcCtrl->hColumnPattern0[10]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc0_11 != sdcCtrl->hColumnPattern0[11]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_11  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc03.bit.sdcpc0_11,sdcCtrl->hColumnPattern0[11]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc0_12 != sdcCtrl->hColumnPattern0[12]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_12  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc0_12,sdcCtrl->hColumnPattern0[12]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc0_13 != sdcCtrl->hColumnPattern0[13]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_13  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc0_13,sdcCtrl->hColumnPattern0[13]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc0_14 != sdcCtrl->hColumnPattern0[14]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_14  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc0_14,sdcCtrl->hColumnPattern0[14]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc0_15 != sdcCtrl->hColumnPattern0[15]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_15  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc04.bit.sdcpc0_15,sdcCtrl->hColumnPattern0[15]))
        };
}

Impro271Print* impro_2_7_1_print_new(void)
{
	Impro271Print* self = k_object_new_with_private(IMPRO_TYPE_2_7_1_PRINT, sizeof(Impro271PrintPrivate));

	return self;
}

Impro271Print* impro_2_7_1_print_get(void)
{
	static Impro271Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_2_7_1_PRINT, sizeof(Impro271PrintPrivate));
	}

	return self;
}
