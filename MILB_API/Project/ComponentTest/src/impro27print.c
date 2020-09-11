/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro27Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro27print.h"
#include "impro271print.h"
#include "impro274print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro27Print, impro_2_7_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_2_7_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro27PrintPrivate, IMPRO_TYPE_2_7_PRINT))


struct _Impro27PrintPrivate
{


};


/**
 *IMPL 
 */
static void impro_2_7_print_constructor(Impro27Print *self)
{
	Impro27PrintPrivate *priv = IMPRO_2_7_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_2_7_print_destructor(Impro27Print *self)
{
	Impro27PrintPrivate *priv = IMPRO_2_7_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *PUBLIC 
 */
Impro27Print* impro_2_7_print_new(void)
{
	Impro27Print* self = k_object_new_with_private(IMPRO_TYPE_2_7_PRINT, sizeof(Impro27PrintPrivate));

	return self;
}

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_2_7_print_0(Impro27Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
                        kint32 ercd, E_IM_PRO_SDC_GAIN_TABLE_SEL sdcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcsgd.bit.sdcsgd != sdcCtrl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Select_Gain_Table(%u %u) %s result:sdcsgd  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcsgd.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcsgd.bit.sdcsgd,sdcCtrl))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Select_Gain_Table(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}
void im_pro_2_7_print_1(Impro27Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch,
                         kint32 ercd, T_IM_PRO_SDC_CTRL_AFPB* sdcCtrl)
{

    if( ercd == DdimUserCustom_E_OK) {
            im_pro_2_7_1_Print(impro_2_7_1_print_get(),string, unitNo, ch, ercd, sdcCtrl);
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc0_16 != sdcCtrl->hColumnPattern0[16]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_16  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc0_16,sdcCtrl->hColumnPattern0[16]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc0_17 != sdcCtrl->hColumnPattern0[17]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_17  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc0_17,sdcCtrl->hColumnPattern0[17]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc0_18 != sdcCtrl->hColumnPattern0[18]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_18  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc0_18,sdcCtrl->hColumnPattern0[18]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc0_19 != sdcCtrl->hColumnPattern0[19]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_19  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc05.bit.sdcpc0_19,sdcCtrl->hColumnPattern0[19]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc0_20 != sdcCtrl->hColumnPattern0[20]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_20  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc0_20,sdcCtrl->hColumnPattern0[20]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc0_21 != sdcCtrl->hColumnPattern0[21]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_21  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc0_21,sdcCtrl->hColumnPattern0[21]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc0_22 != sdcCtrl->hColumnPattern0[22]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_22  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc0_22,sdcCtrl->hColumnPattern0[22]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc0_23 != sdcCtrl->hColumnPattern0[23]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_23  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc06.bit.sdcpc0_23,sdcCtrl->hColumnPattern0[23]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc0_24 != sdcCtrl->hColumnPattern0[24]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_24  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc0_24,sdcCtrl->hColumnPattern0[24]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc0_25 != sdcCtrl->hColumnPattern0[25]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_25  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc0_25,sdcCtrl->hColumnPattern0[25]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc0_26 != sdcCtrl->hColumnPattern0[26]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_26  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc0_26,sdcCtrl->hColumnPattern0[26]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc0_27 != sdcCtrl->hColumnPattern0[27]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_27  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc07.bit.sdcpc0_27,sdcCtrl->hColumnPattern0[27]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc0_28 != sdcCtrl->hColumnPattern0[28]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_28  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc0_28,sdcCtrl->hColumnPattern0[28]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc0_29 != sdcCtrl->hColumnPattern0[29]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_29  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc0_29,sdcCtrl->hColumnPattern0[29]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc0_30 != sdcCtrl->hColumnPattern0[30]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_30  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc0_30,sdcCtrl->hColumnPattern0[30]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc0_31 != sdcCtrl->hColumnPattern0[31]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_31  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc08.bit.sdcpc0_31,sdcCtrl->hColumnPattern0[31]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc0_32 != sdcCtrl->hColumnPattern0[32]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_32  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc0_32,sdcCtrl->hColumnPattern0[32]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc0_33 != sdcCtrl->hColumnPattern0[33]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_33  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc0_33,sdcCtrl->hColumnPattern0[33]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc0_34 != sdcCtrl->hColumnPattern0[34]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_34  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc0_34,sdcCtrl->hColumnPattern0[34]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc0_35 != sdcCtrl->hColumnPattern0[35]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_35  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc09.bit.sdcpc0_35,sdcCtrl->hColumnPattern0[35]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc0_36 != sdcCtrl->hColumnPattern0[36]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_36  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc0_36,sdcCtrl->hColumnPattern0[36]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc0_37 != sdcCtrl->hColumnPattern0[37]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_37  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc0_37,sdcCtrl->hColumnPattern0[37]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc0_38 != sdcCtrl->hColumnPattern0[38]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_38  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc0_38,sdcCtrl->hColumnPattern0[38]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc0_39 != sdcCtrl->hColumnPattern0[39]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_39  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc010.bit.sdcpc0_39,sdcCtrl->hColumnPattern0[39]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc0_40 != sdcCtrl->hColumnPattern0[40]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_40  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc0_40,sdcCtrl->hColumnPattern0[40]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc0_41 != sdcCtrl->hColumnPattern0[41]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_41  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc0_41,sdcCtrl->hColumnPattern0[41]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc0_42 != sdcCtrl->hColumnPattern0[42]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_42  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc0_42,sdcCtrl->hColumnPattern0[42]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc0_43 != sdcCtrl->hColumnPattern0[43]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_43  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc011.bit.sdcpc0_43,sdcCtrl->hColumnPattern0[43]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc0_44 != sdcCtrl->hColumnPattern0[44]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_44  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc0_44,sdcCtrl->hColumnPattern0[44]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc0_45 != sdcCtrl->hColumnPattern0[45]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_45  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc0_45,sdcCtrl->hColumnPattern0[45]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc0_46 != sdcCtrl->hColumnPattern0[46]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_46  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc0_46,sdcCtrl->hColumnPattern0[46]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc0_47 != sdcCtrl->hColumnPattern0[47]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_47  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc012.bit.sdcpc0_47,sdcCtrl->hColumnPattern0[47]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc0_48 != sdcCtrl->hColumnPattern0[48]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_48  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc0_48,sdcCtrl->hColumnPattern0[48]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc0_49 != sdcCtrl->hColumnPattern0[49]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_49  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc0_49,sdcCtrl->hColumnPattern0[49]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc0_50 != sdcCtrl->hColumnPattern0[50]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_50  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc0_50,sdcCtrl->hColumnPattern0[50]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc0_51 != sdcCtrl->hColumnPattern0[51]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_51  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc013.bit.sdcpc0_51,sdcCtrl->hColumnPattern0[51]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc0_52 != sdcCtrl->hColumnPattern0[52]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_52  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc0_52,sdcCtrl->hColumnPattern0[52]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc0_53 != sdcCtrl->hColumnPattern0[53]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_53  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc0_53,sdcCtrl->hColumnPattern0[53]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc0_54 != sdcCtrl->hColumnPattern0[54]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_54  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc0_54,sdcCtrl->hColumnPattern0[54]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc0_55 != sdcCtrl->hColumnPattern0[55]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_55  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc014.bit.sdcpc0_55,sdcCtrl->hColumnPattern0[55]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc0_56 != sdcCtrl->hColumnPattern0[56]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_56  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc0_56,sdcCtrl->hColumnPattern0[56]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc0_57 != sdcCtrl->hColumnPattern0[57]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_57  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc0_57,sdcCtrl->hColumnPattern0[57]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc0_58 != sdcCtrl->hColumnPattern0[58]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_58  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc0_58,sdcCtrl->hColumnPattern0[58]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc0_59 != sdcCtrl->hColumnPattern0[59]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_59  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc015.bit.sdcpc0_59,sdcCtrl->hColumnPattern0[59]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc0_60 != sdcCtrl->hColumnPattern0[60]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_60  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc0_60,sdcCtrl->hColumnPattern0[60]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc0_61 != sdcCtrl->hColumnPattern0[61]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_61  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc0_61,sdcCtrl->hColumnPattern0[61]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc0_62 != sdcCtrl->hColumnPattern0[62]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_62  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc0_62,sdcCtrl->hColumnPattern0[62]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc0_63 != sdcCtrl->hColumnPattern0[63]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc0_63  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc0.sdcpc016.bit.sdcpc0_63,sdcCtrl->hColumnPattern0[63]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc1_0 != sdcCtrl->hColumnPattern1[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc1_0,sdcCtrl->hColumnPattern1[0]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc1_1 != sdcCtrl->hColumnPattern1[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc1_1,sdcCtrl->hColumnPattern1[1]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc1_2 != sdcCtrl->hColumnPattern1[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_2  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc1_2,sdcCtrl->hColumnPattern1[2]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc1_3 != sdcCtrl->hColumnPattern1[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_3  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc11.bit.sdcpc1_3,sdcCtrl->hColumnPattern1[3]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc1_4 != sdcCtrl->hColumnPattern1[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_4  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc1_4,sdcCtrl->hColumnPattern1[4]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc1_5 != sdcCtrl->hColumnPattern1[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_5  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc1_5,sdcCtrl->hColumnPattern1[5]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc1_6 != sdcCtrl->hColumnPattern1[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_6  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc1_6,sdcCtrl->hColumnPattern1[6]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc1_7 != sdcCtrl->hColumnPattern1[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_7  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc12.bit.sdcpc1_7,sdcCtrl->hColumnPattern1[7]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc1_8 != sdcCtrl->hColumnPattern1[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_8  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc1_8,sdcCtrl->hColumnPattern1[8]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc1_9 != sdcCtrl->hColumnPattern1[9]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_9  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc1_9,sdcCtrl->hColumnPattern1[9]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc1_10 != sdcCtrl->hColumnPattern1[10]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_10  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc1_10,sdcCtrl->hColumnPattern1[10]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc1_11 != sdcCtrl->hColumnPattern1[11]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_11  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc13.bit.sdcpc1_11,sdcCtrl->hColumnPattern1[11]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc1_12 != sdcCtrl->hColumnPattern1[12]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_12  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc1_12,sdcCtrl->hColumnPattern1[12]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc1_13 != sdcCtrl->hColumnPattern1[13]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_13  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc1_13,sdcCtrl->hColumnPattern1[13]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc1_14 != sdcCtrl->hColumnPattern1[14]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_14  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc1_14,sdcCtrl->hColumnPattern1[14]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc1_15 != sdcCtrl->hColumnPattern1[15]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_15  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc14.bit.sdcpc1_15,sdcCtrl->hColumnPattern1[15]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc1_16 != sdcCtrl->hColumnPattern1[16]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_16  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc1_16,sdcCtrl->hColumnPattern1[16]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc1_17 != sdcCtrl->hColumnPattern1[17]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_17  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc1_17,sdcCtrl->hColumnPattern1[17]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc1_18 != sdcCtrl->hColumnPattern1[18]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_18  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc1_18,sdcCtrl->hColumnPattern1[18]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc1_19 != sdcCtrl->hColumnPattern1[19]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_19  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc15.bit.sdcpc1_19,sdcCtrl->hColumnPattern1[19]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc1_20 != sdcCtrl->hColumnPattern1[20]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_20  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc1_20,sdcCtrl->hColumnPattern1[20]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc1_21 != sdcCtrl->hColumnPattern1[21]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_21  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc1_21,sdcCtrl->hColumnPattern1[21]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc1_22 != sdcCtrl->hColumnPattern1[22]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_22  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc1_22,sdcCtrl->hColumnPattern1[22]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc1_23 != sdcCtrl->hColumnPattern1[23]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_23  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc16.bit.sdcpc1_23,sdcCtrl->hColumnPattern1[23]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc1_24 != sdcCtrl->hColumnPattern1[24]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_24  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc1_24,sdcCtrl->hColumnPattern1[24]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc1_25 != sdcCtrl->hColumnPattern1[25]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_25  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc1_25,sdcCtrl->hColumnPattern1[25]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc1_26 != sdcCtrl->hColumnPattern1[26]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_26  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc1_26,sdcCtrl->hColumnPattern1[26]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc1_27 != sdcCtrl->hColumnPattern1[27]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_27  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc17.bit.sdcpc1_27,sdcCtrl->hColumnPattern1[27]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc1_28 != sdcCtrl->hColumnPattern1[28]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_28  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc1_28,sdcCtrl->hColumnPattern1[28]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc1_29 != sdcCtrl->hColumnPattern1[29]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_29  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc1_29,sdcCtrl->hColumnPattern1[29]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc1_30 != sdcCtrl->hColumnPattern1[30]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_30  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc1_30,sdcCtrl->hColumnPattern1[30]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc1_31 != sdcCtrl->hColumnPattern1[31]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_31  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc18.bit.sdcpc1_31,sdcCtrl->hColumnPattern1[31]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc1_32 != sdcCtrl->hColumnPattern1[32]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_32  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc1_32,sdcCtrl->hColumnPattern1[32]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc1_33 != sdcCtrl->hColumnPattern1[33]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_33  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc1_33,sdcCtrl->hColumnPattern1[33]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc1_34 != sdcCtrl->hColumnPattern1[34]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_34  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc1_34,sdcCtrl->hColumnPattern1[34]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc1_35 != sdcCtrl->hColumnPattern1[35]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_35  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc19.bit.sdcpc1_35,sdcCtrl->hColumnPattern1[35]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc1_36 != sdcCtrl->hColumnPattern1[36]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_36  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc1_36,sdcCtrl->hColumnPattern1[36]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc1_37 != sdcCtrl->hColumnPattern1[37]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_37  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc1_37,sdcCtrl->hColumnPattern1[37]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc1_38 != sdcCtrl->hColumnPattern1[38]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_38  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc1_38,sdcCtrl->hColumnPattern1[38]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc1_39 != sdcCtrl->hColumnPattern1[39]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_39  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc110.bit.sdcpc1_39,sdcCtrl->hColumnPattern1[39]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc1_40 != sdcCtrl->hColumnPattern1[40]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_40  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc1_40,sdcCtrl->hColumnPattern1[40]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc1_41 != sdcCtrl->hColumnPattern1[41]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_41  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc1_41,sdcCtrl->hColumnPattern1[41]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc1_42 != sdcCtrl->hColumnPattern1[42]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_42  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc1_42,sdcCtrl->hColumnPattern1[42]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc1_43 != sdcCtrl->hColumnPattern1[43]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_43  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc111.bit.sdcpc1_43,sdcCtrl->hColumnPattern1[43]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc1_44 != sdcCtrl->hColumnPattern1[44]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_44  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc1_44,sdcCtrl->hColumnPattern1[44]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc1_45 != sdcCtrl->hColumnPattern1[45]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_45  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc1_45,sdcCtrl->hColumnPattern1[45]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc1_46 != sdcCtrl->hColumnPattern1[46]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_46  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc1_46,sdcCtrl->hColumnPattern1[46]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc1_47 != sdcCtrl->hColumnPattern1[47]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_47  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc112.bit.sdcpc1_47,sdcCtrl->hColumnPattern1[47]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc1_48 != sdcCtrl->hColumnPattern1[48]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_48  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc1_48,sdcCtrl->hColumnPattern1[48]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc1_49 != sdcCtrl->hColumnPattern1[49]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_49  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc1_49,sdcCtrl->hColumnPattern1[49]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc1_50 != sdcCtrl->hColumnPattern1[50]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_50  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc1_50,sdcCtrl->hColumnPattern1[50]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc1_51 != sdcCtrl->hColumnPattern1[51]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_51  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc113.bit.sdcpc1_51,sdcCtrl->hColumnPattern1[51]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc1_52 != sdcCtrl->hColumnPattern1[52]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_52  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc1_52,sdcCtrl->hColumnPattern1[52]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc1_53 != sdcCtrl->hColumnPattern1[53]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_53  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc1_53,sdcCtrl->hColumnPattern1[53]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc1_54 != sdcCtrl->hColumnPattern1[54]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_54  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc1_54,sdcCtrl->hColumnPattern1[54]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc1_55 != sdcCtrl->hColumnPattern1[55]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_55  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc114.bit.sdcpc1_55,sdcCtrl->hColumnPattern1[55]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc1_56 != sdcCtrl->hColumnPattern1[56]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_56  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc1_56,sdcCtrl->hColumnPattern1[56]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc1_57 != sdcCtrl->hColumnPattern1[57]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_57  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc1_57,sdcCtrl->hColumnPattern1[57]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc1_58 != sdcCtrl->hColumnPattern1[58]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_58  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc1_58,sdcCtrl->hColumnPattern1[58]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc1_59 != sdcCtrl->hColumnPattern1[59]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_59  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc115.bit.sdcpc1_59,sdcCtrl->hColumnPattern1[59]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc1_60 != sdcCtrl->hColumnPattern1[60]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_60  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc1_60,sdcCtrl->hColumnPattern1[60]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc1_61 != sdcCtrl->hColumnPattern1[61]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_61  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc1_61,sdcCtrl->hColumnPattern1[61]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc1_62 != sdcCtrl->hColumnPattern1[62]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_62  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc1_62,sdcCtrl->hColumnPattern1[62]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc1_63 != sdcCtrl->hColumnPattern1[63]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpc1_63  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpc1.sdcpc116.bit.sdcpc1_63,sdcCtrl->hColumnPattern1[63]))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpcW0.bit.sdcpcW0 != sdcCtrl->hColumnPatternValidWidth0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpcW0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpcW0.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpcW0.bit.sdcpcW0,sdcCtrl->hColumnPatternValidWidth0))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpcW1.bit.sdcpcW1 != sdcCtrl->hColumnPatternValidWidth1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcpcW1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpcW1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpcW1.bit.sdcpcW1,sdcCtrl->hColumnPatternValidWidth1))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1cw0.bit.sdcp1cw0 != sdcCtrl->hColumnPattern1ValidWidth0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1cw0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1cw0.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1cw0.bit.sdcp1cw0,sdcCtrl->hColumnPattern1ValidWidth0))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1cw1.bit.sdcp1cw1 != sdcCtrl->hColumnPattern1ValidWidth1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp1cw1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1cw1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp1cw1.bit.sdcp1cw1,sdcCtrl->hColumnPattern1ValidWidth1))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2cw0.bit.sdcp2cw0 != sdcCtrl->hColumnPattern2ValidWidth0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2cw0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2cw0.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2cw0.bit.sdcp2cw0,sdcCtrl->hColumnPattern2ValidWidth0))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2cw1.bit.sdcp2cw1 != sdcCtrl->hColumnPattern2ValidWidth1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcp2cw1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2cw1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcp2cw1.bit.sdcp2cw1,sdcCtrl->hColumnPattern2ValidWidth1))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1cw0.bit.sdcn1cw0 != sdcCtrl->hColumnPattern1InvalidWidth0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1cw0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1cw0.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1cw0.bit.sdcn1cw0,sdcCtrl->hColumnPattern1InvalidWidth0))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1cw1.bit.sdcn1cw1 != sdcCtrl->hColumnPattern1InvalidWidth1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn1cw1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1cw1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn1cw1.bit.sdcn1cw1,sdcCtrl->hColumnPattern1InvalidWidth1))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2cw0.bit.sdcn2cw0 != sdcCtrl->hColumnPattern2InvalidWidth0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2cw0  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2cw0.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2cw0.bit.sdcn2cw0,sdcCtrl->hColumnPattern2InvalidWidth0))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2cw1.bit.sdcn2cw1 != sdcCtrl->hColumnPattern2InvalidWidth1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcn2cw1  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2cw1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcn2cw1.bit.sdcn2cw1,sdcCtrl->hColumnPattern2InvalidWidth1))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcgmaxmin.bit.sdcgmax != sdcCtrl->afpbGainCorrectionUThreshold) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcgmax  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcgmaxmin.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcgmaxmin.bit.sdcgmax,sdcCtrl->afpbGainCorrectionUThreshold))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcgmaxmin.bit.sdcgmin != sdcCtrl->afGainCorrectionLThreshold) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcgmin  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcgmaxmin.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcgmaxmin.bit.sdcgmin,sdcCtrl->afGainCorrectionLThreshold))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcnmax.bit.sdcnmax != sdcCtrl->afpbNeighborPixelCorrectionLevel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) %s result:sdcnmax  0x%08lx(%u)   in(%u)\n",          
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcnmax.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcnmax.bit.sdcnmax,sdcCtrl->afpbNeighborPixelCorrectionLevel))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl_Afpb(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}
void im_pro_2_7_print_2(Impro27Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
E_IM_PRO_SDC_GAIN_TABLE_SEL tblSel, kint32 ercd, T_IM_PRO_SDC_GAIN_TABLE* sdcCtrl, kint32 cmpErcd)
{
    if( ercd == DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Set_Gain_Table(%u %u %u) %s API result(0x%x) memcmp result(0x%x)\n", 
            unitNo, ch, tblSel, string, ercd, cmpErcd));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Set_Gain_Table(%u %u %u) error ercd=0x%x\n", unitNo, ch, tblSel, ercd));
    }
}

void im_pro_2_7_print_3(Impro27Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, kint32 ercd, kuchar paenTrg)
{
    if( ercd == DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Set_PAEN(%u %u %u) result:sdcpaen  0x%08lx(%u)\n", 
            unitNo, ch, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpaen.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcpaen.bit.sdcpaen));
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Set_PAEN(%u %u %u) result:sdctrg  0x%08lx(%u)\n", 
            unitNo, ch, paenTrg, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdctrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdctrg.bit.sdctrg));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Set_PAEN(%u %u %u) error ercd=0x%x\n", unitNo, ch, paenTrg, ercd));
    }
}

void im_pro_2_7_print_4(Impro27Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
kint32 ercd, const T_IM_PRO_RDMA_SDC_ADDR** sdcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        im_pro_2_7_4_Print(impro_2_7_4_print_get(),string, unitNo, ch, ercd, sdcCtrl);
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcgmaxmin.word != (*sdcCtrl)->sdcgmaxmin) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcgmaxmin  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcgmaxmin.word,
            (kulong)(*sdcCtrl)->sdcgmaxmin))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcnmax.word != (*sdcCtrl)->sdcnmax) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) %s result:sdcnmax  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcnmax.word,
            (kulong)(*sdcCtrl)->sdcnmax))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Cntl(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_7_print_5(Impro27Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
E_IM_PRO_SDC_GAIN_TABLE_SEL tblSel, kint32 ercd, const T_IM_PRO_RDMA_SDC_GAIN_TBL_ADDR** sdcCtrl)
{
    const T_IM_PRO_SRO_SDC_INFO* sdcInfo;

    if( ercd == DdimUserCustom_E_OK) {
        im_pro_comm_get_sdc_reg_info( unitNo, ch, &sdcInfo);
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Gain_Tbl(%u %u %u) %s result:sdcgd  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, tblSel, string, (kulong)&sdcInfo->tblRegPtr[tblSel].hword,(kulong)(*sdcCtrl)->sdcgd));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SDC_Gain_Tbl(%u %u %u) error ercd=0x%x\n", unitNo, ch, tblSel, ercd));
    }
}
#endif

Impro27Print* impro_2_7_print_get(void)
{
	static Impro27Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_2_7_PRINT, sizeof(Impro27PrintPrivate));
	}

	return self;
}
