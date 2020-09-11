/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro25Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro25print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro25Print, impro_2_5_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_2_5_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro25PrintPrivate, IMPRO_TYPE_2_5_PRINT))


struct _Impro25PrintPrivate
{


};


/**
 *IMPL 
 */
static void impro_2_5_print_constructor(Impro25Print *self)
{
	Impro25PrintPrivate *priv = IMPRO_2_5_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_2_5_print_destructor(Impro25Print *self)
{
	Impro25PrintPrivate *priv = IMPRO_2_5_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *PUBLIC 
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_2_5_print_0(Impro25Print *self, E_IM_PRO_UNIT_NUM unitNo)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Start(%u) result:vrbtrg 0x%08lx(%u)\n", 
            unitNo, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrbtrg.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrbtrg.bit.vrbtrg));
}

void im_pro_2_5_print_1(Impro25Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Stop(%u %u) result:vrbtrg  0x%08lx(%u)\n", 
            unitNo, force, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrbtrg.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrbtrg.bit.vrbtrg));
}

void im_pro_2_5_print_2(Impro25Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, T_IM_PRO_VRB_CTRL* vrbCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].sro.vrb.vrbh.bit.vrbh != vrbCtrl->inPosX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrbh  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrbh.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrbh.bit.vrbh,vrbCtrl->inPosX))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrbv.bit.vrbv != vrbCtrl->inPosY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrbv  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrbv.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrbv.bit.vrbv,vrbCtrl->inPosY))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrbhw.bit.vrbhw != vrbCtrl->inWidth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrbhw  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrbhw.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrbhw.bit.vrbhw,vrbCtrl->inWidth))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrbvw.bit.vrbvw != vrbCtrl->inLines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrbvw  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrbvw.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrbvw.bit.vrbvw,vrbCtrl->inLines))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrbscyc.bit.vrbscyc != vrbCtrl->cycle) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrbscyc  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrbscyc.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrbscyc.bit.vrbscyc,vrbCtrl->cycle))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k1.bit.vrb0k0_0 != vrbCtrl->coefficient0[0][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k0_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k1.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k1.bit.vrb0k0_0,vrbCtrl->coefficient0[0][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k1.bit.vrb0k0_1 != vrbCtrl->coefficient0[0][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k0_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k1.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k1.bit.vrb0k0_1,vrbCtrl->coefficient0[0][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k2.bit.vrb0k0_2 != vrbCtrl->coefficient0[0][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k0_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k2.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k2.bit.vrb0k0_2,vrbCtrl->coefficient0[0][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k2.bit.vrb0k1_0 != vrbCtrl->coefficient0[1][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k1_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k2.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k2.bit.vrb0k1_0,vrbCtrl->coefficient0[1][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k3.bit.vrb0k1_1 != vrbCtrl->coefficient0[1][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k1_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k3.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k3.bit.vrb0k1_1,vrbCtrl->coefficient0[1][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k3.bit.vrb0k1_2 != vrbCtrl->coefficient0[1][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k1_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k3.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k3.bit.vrb0k1_2,vrbCtrl->coefficient0[1][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k4.bit.vrb0k2_0 != vrbCtrl->coefficient0[2][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k2_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k4.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k4.bit.vrb0k2_0,vrbCtrl->coefficient0[2][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k4.bit.vrb0k2_1 != vrbCtrl->coefficient0[2][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k2_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k4.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k4.bit.vrb0k2_1,vrbCtrl->coefficient0[2][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k5.bit.vrb0k2_2 != vrbCtrl->coefficient0[2][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k2_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k5.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k5.bit.vrb0k2_2,vrbCtrl->coefficient0[2][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k5.bit.vrb0k3_0 != vrbCtrl->coefficient0[3][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k3_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k5.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k5.bit.vrb0k3_0,vrbCtrl->coefficient0[3][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k6.bit.vrb0k3_1 != vrbCtrl->coefficient0[3][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k3_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k6.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k6.bit.vrb0k3_1,vrbCtrl->coefficient0[3][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k6.bit.vrb0k3_2 != vrbCtrl->coefficient0[3][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k3_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k6.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k6.bit.vrb0k3_2,vrbCtrl->coefficient0[3][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k7.bit.vrb0k4_0 != vrbCtrl->coefficient0[4][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k4_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k7.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k7.bit.vrb0k4_0,vrbCtrl->coefficient0[4][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k7.bit.vrb0k4_1 != vrbCtrl->coefficient0[4][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k4_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k7.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k7.bit.vrb0k4_1,vrbCtrl->coefficient0[4][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k8.bit.vrb0k4_2 != vrbCtrl->coefficient0[4][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k4_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k8.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k8.bit.vrb0k4_2,vrbCtrl->coefficient0[4][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k8.bit.vrb0k5_0 != vrbCtrl->coefficient0[5][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k5_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k8.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k8.bit.vrb0k5_0,vrbCtrl->coefficient0[5][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k9.bit.vrb0k5_1 != vrbCtrl->coefficient0[5][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k5_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k9.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k9.bit.vrb0k5_1,vrbCtrl->coefficient0[5][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k9.bit.vrb0k5_2 != vrbCtrl->coefficient0[5][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k5_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k9.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k9.bit.vrb0k5_2,vrbCtrl->coefficient0[5][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k10.bit.vrb0k6_0 != vrbCtrl->coefficient0[6][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k6_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k10.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k10.bit.vrb0k6_0,vrbCtrl->coefficient0[6][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k10.bit.vrb0k6_1 != vrbCtrl->coefficient0[6][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k6_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k10.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k10.bit.vrb0k6_1,vrbCtrl->coefficient0[6][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k11.bit.vrb0k6_2 != vrbCtrl->coefficient0[6][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k6_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k11.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k11.bit.vrb0k6_2,vrbCtrl->coefficient0[6][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k11.bit.vrb0k7_0 != vrbCtrl->coefficient0[7][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k7_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k11.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k11.bit.vrb0k7_0,vrbCtrl->coefficient0[7][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k12.bit.vrb0k7_1 != vrbCtrl->coefficient0[7][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k7_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k12.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k12.bit.vrb0k7_1,vrbCtrl->coefficient0[7][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k12.bit.vrb0k7_2 != vrbCtrl->coefficient0[7][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k7_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k12.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k12.bit.vrb0k7_2,vrbCtrl->coefficient0[7][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k13.bit.vrb0k8_0 != vrbCtrl->coefficient0[8][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k8_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k13.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k13.bit.vrb0k8_0,vrbCtrl->coefficient0[8][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k13.bit.vrb0k8_1 != vrbCtrl->coefficient0[8][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k8_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k13.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k13.bit.vrb0k8_1,vrbCtrl->coefficient0[8][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k14.bit.vrb0k8_2 != vrbCtrl->coefficient0[8][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k8_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k14.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k14.bit.vrb0k8_2,vrbCtrl->coefficient0[8][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k14.bit.vrb0k9_0 != vrbCtrl->coefficient0[9][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k9_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k14.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k14.bit.vrb0k9_0,vrbCtrl->coefficient0[9][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k15.bit.vrb0k9_1 != vrbCtrl->coefficient0[9][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k9_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k15.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k15.bit.vrb0k9_1,vrbCtrl->coefficient0[9][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k15.bit.vrb0k9_2 != vrbCtrl->coefficient0[9][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb0k9_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k15.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb0k.vrb0k15.bit.vrb0k9_2,vrbCtrl->coefficient0[9][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k1.bit.vrb1k0_0 != vrbCtrl->coefficient1[0][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k0_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k1.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k1.bit.vrb1k0_0,vrbCtrl->coefficient1[0][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k1.bit.vrb1k0_1 != vrbCtrl->coefficient1[0][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k0_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k1.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k1.bit.vrb1k0_1,vrbCtrl->coefficient1[0][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k2.bit.vrb1k0_2 != vrbCtrl->coefficient1[0][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k0_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k2.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k2.bit.vrb1k0_2,vrbCtrl->coefficient1[0][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k2.bit.vrb1k1_0 != vrbCtrl->coefficient1[1][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k1_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k2.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k2.bit.vrb1k1_0,vrbCtrl->coefficient1[1][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k3.bit.vrb1k1_1 != vrbCtrl->coefficient1[1][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k1_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k3.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k3.bit.vrb1k1_1,vrbCtrl->coefficient1[1][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k3.bit.vrb1k1_2 != vrbCtrl->coefficient1[1][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k1_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k3.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k3.bit.vrb1k1_2,vrbCtrl->coefficient1[1][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k4.bit.vrb1k2_0 != vrbCtrl->coefficient1[2][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k2_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k4.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k4.bit.vrb1k2_0,vrbCtrl->coefficient1[2][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k4.bit.vrb1k2_1 != vrbCtrl->coefficient1[2][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k2_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k4.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k4.bit.vrb1k2_1,vrbCtrl->coefficient1[2][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k5.bit.vrb1k2_2 != vrbCtrl->coefficient1[2][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k2_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k5.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k5.bit.vrb1k2_2,vrbCtrl->coefficient1[2][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k5.bit.vrb1k3_0 != vrbCtrl->coefficient1[3][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k3_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k5.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k5.bit.vrb1k3_0,vrbCtrl->coefficient1[3][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k6.bit.vrb1k3_1 != vrbCtrl->coefficient1[3][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k3_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k6.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k6.bit.vrb1k3_1,vrbCtrl->coefficient1[3][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k6.bit.vrb1k3_2 != vrbCtrl->coefficient1[3][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k3_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k6.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k6.bit.vrb1k3_2,vrbCtrl->coefficient1[3][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k7.bit.vrb1k4_0 != vrbCtrl->coefficient1[4][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k4_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k7.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k7.bit.vrb1k4_0,vrbCtrl->coefficient1[4][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k7.bit.vrb1k4_1 != vrbCtrl->coefficient1[4][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k4_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k7.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k7.bit.vrb1k4_1,vrbCtrl->coefficient1[4][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k8.bit.vrb1k4_2 != vrbCtrl->coefficient1[4][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k4_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k8.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k8.bit.vrb1k4_2,vrbCtrl->coefficient1[4][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k8.bit.vrb1k5_0 != vrbCtrl->coefficient1[5][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k5_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k8.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k8.bit.vrb1k5_0,vrbCtrl->coefficient1[5][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k9.bit.vrb1k5_1 != vrbCtrl->coefficient1[5][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k5_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k9.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k9.bit.vrb1k5_1,vrbCtrl->coefficient1[5][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k9.bit.vrb1k5_2 != vrbCtrl->coefficient1[5][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k5_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k9.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k9.bit.vrb1k5_2,vrbCtrl->coefficient1[5][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k10.bit.vrb1k6_0 != vrbCtrl->coefficient1[6][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k6_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k10.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k10.bit.vrb1k6_0,vrbCtrl->coefficient1[6][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k10.bit.vrb1k6_1 != vrbCtrl->coefficient1[6][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k6_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k10.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k10.bit.vrb1k6_1,vrbCtrl->coefficient1[6][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k11.bit.vrb1k6_2 != vrbCtrl->coefficient1[6][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k6_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k11.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k11.bit.vrb1k6_2,vrbCtrl->coefficient1[6][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k11.bit.vrb1k7_0 != vrbCtrl->coefficient1[7][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k7_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k11.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k11.bit.vrb1k7_0,vrbCtrl->coefficient1[7][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k12.bit.vrb1k7_1 != vrbCtrl->coefficient1[7][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k7_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k12.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k12.bit.vrb1k7_1,vrbCtrl->coefficient1[7][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k12.bit.vrb1k7_2 != vrbCtrl->coefficient1[7][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k7_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k12.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k12.bit.vrb1k7_2,vrbCtrl->coefficient1[7][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k13.bit.vrb1k8_0 != vrbCtrl->coefficient1[8][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k8_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k13.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k13.bit.vrb1k8_0,vrbCtrl->coefficient1[8][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k13.bit.vrb1k8_1 != vrbCtrl->coefficient1[8][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k8_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k13.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k13.bit.vrb1k8_1,vrbCtrl->coefficient1[8][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k14.bit.vrb1k8_2 != vrbCtrl->coefficient1[8][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k8_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k14.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k14.bit.vrb1k8_2,vrbCtrl->coefficient1[8][2]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k14.bit.vrb1k9_0 != vrbCtrl->coefficient1[9][0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k9_0  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k14.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k14.bit.vrb1k9_0,vrbCtrl->coefficient1[9][0]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k15.bit.vrb1k9_1 != vrbCtrl->coefficient1[9][1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k9_1  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k15.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k15.bit.vrb1k9_1,vrbCtrl->coefficient1[9][1]))
        };

        if(ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k15.bit.vrb1k9_2 != vrbCtrl->coefficient1[9][2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) %s result:vrb1k9_2  0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k15.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrb1k.vrb1k15.bit.vrb1k9_2,vrbCtrl->coefficient1[9][2]))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Ctrl(%u) error ercd=0x%x\n", 
            unitNo, ercd));
    }
}

void im_pro_2_5_print_3(Impro25Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar paenTrg)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Set_PAEN(%u %u) result:paen  0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrbpaen.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrbpaen.bit.paen));
    DriverCommon_DDIM_PRINT(( "Im_PRO_VRB_Set_PAEN(%u %u) result:vrbtrg  0x%08lx(%u)\n", 
            unitNo, paenTrg, (kulong)&ioPro.imgPipe[unitNo].sro.vrb.vrbtrg.word, 
            ioPro.imgPipe[unitNo].sro.vrb.vrbtrg.bit.vrbtrg));
}

void im_pro_2_5_print_4(Impro25Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Start(%u %u) result:  0x%08lx(%u)\n", 
            unitNo, ch, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshtrg.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshtrg.bit.ffshtrg));
}

void im_pro_2_5_print_5(Impro25Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Stop(%u %u %u) result:ffshtrg 0x%08lx(%u)\n", 
            unitNo, ch, force, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshtrg.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshtrg.bit.ffshtrg));
}

void im_pro_2_5_print_6(Impro25Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                        E_IM_PRO_FFSH_CH ch, kint32 ercd, T_IM_PRO_FFSH_CTRL* ffshCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubpr.bit.ffshsubprh != ffshCtrl->hSizeCorrectionCoeff) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Ctrl(%u %u) %s result:ffshsubprh  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubpr.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubpr.bit.ffshsubprh,ffshCtrl->hSizeCorrectionCoeff))
        };

        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubpr.bit.ffshsubprv != ffshCtrl->vSizeCorrectionCoeff) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Ctrl(%u %u) %s result:ffshsubprv  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubpr.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubpr.bit.ffshsubprv,ffshCtrl->vSizeCorrectionCoeff))
        };

        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubsp.bit.ffshsubsph != ffshCtrl->hPixelUnitInterpolation) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Ctrl(%u %u) %s result:ffshsubsph  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubsp.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubsp.bit.ffshsubsph,ffshCtrl->hPixelUnitInterpolation))
        };

        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubsp.bit.ffshsubspv != ffshCtrl->vPixelUnitInterpolation) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Ctrl(%u %u) %s result:ffshsubspv  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubsp.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubsp.bit.ffshsubspv,ffshCtrl->vPixelUnitInterpolation))
        };

        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubdr.bit.ffshsubdrm 
 != ffshCtrl->radInverseCoeffInterpolation) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Ctrl(%u %u) %s result:ffshsubdrm  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubdr.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubdr.bit.ffshsubdrm,ffshCtrl->radInverseCoeffInterpolation))
        };

        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubdr.bit.ffshsubdre != 
            ffshCtrl->exp_inverse_coeff_interpolation) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Ctrl(%u %u) %s result:ffshsubdre  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubdr.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubdr.bit.ffshsubdre,
            ffshCtrl->exp_inverse_coeff_interpolation))
        };

        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubst.bit.ffshsubsth != ffshCtrl->hStartPosCoeff) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Ctrl(%u %u) %s result:ffshsubsth  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubst.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubst.bit.ffshsubsth,ffshCtrl->hStartPosCoeff))
        };

        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubst.bit.ffshsubstv != ffshCtrl->vStartPosCoeff) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Ctrl(%u %u) %s result:ffshsubstv  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubst.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshsubst.bit.ffshsubstv,ffshCtrl->vStartPosCoeff))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Ctrl(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_5_print_7(Impro25Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch, kint32 ercd, 
                           T_IM_PRO_FFSH_BLEND_CTRL* ffshCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshbc.bit.ffshbc0 != ffshCtrl->frameCorrectionBlend0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_Blend(%u %u) %s result:ffshbc0  0x%08lx(%d) in(%d)\n", 
            unitNo, unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshbc.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshbc.bit.ffshbc0,ffshCtrl->frameCorrectionBlend0))
        };

        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshbc.bit.ffshbc1 != ffshCtrl->frameCorrectionBlend1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_Blend(%u %u) %s result:ffshbc1  0x%08lx(%d) in(%d)\n", 
            unitNo, unitNo, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshbc.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshbc.bit.ffshbc1,ffshCtrl->frameCorrectionBlend1))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_Blend(%u) error ercd=0x%x\n", unitNo, ercd));
    }
}

void im_pro_2_5_print_8(Impro25Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch, 
                        kint32 ercd, T_IM_PRO_FFSH_AREA* ffshCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshh.bit.ffshh != ffshCtrl->ffshArea.posX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_Area(%u %u) %s result:ffshh  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshh.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshh.bit.ffshh,ffshCtrl->ffshArea.posX))
        };

        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshv.bit.ffshv != ffshCtrl->ffshArea.posY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_Area(%u %u) %s result:ffshv  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshv.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshv.bit.ffshv,ffshCtrl->ffshArea.posY))
        };

        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshhw.bit.ffshhw != ffshCtrl->ffshArea.width) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_Area(%u %u) %s result:ffshhw  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshhw.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshhw.bit.ffshhw,ffshCtrl->ffshArea.width))
        };

        if(ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshvw.bit.ffshvw != ffshCtrl->ffshArea.lines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_Area(%u %u) %s result:ffshvw  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshvw.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshvw.bit.ffshvw,ffshCtrl->ffshArea.lines))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_Area(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_5_print_9(Impro25Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FFSH_CH ch, kint32 ercd, kuchar paenTrg)
{
    if( ercd == DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_PAEN(%u %u %u) result:paen  0x%08lx(%u)\n", 
            unitNo, ch, paenTrg, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshpaen.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshpaen.bit.ffshpaen));
        DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_PAEN(%u %u %u) result:fctrg  0x%08lx(%u)\n", 
            unitNo, ch, paenTrg, (kulong)&ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshtrg.word, 
            ioPro.imgPipe[unitNo].sro.ffsh[ch].ffshtrg.bit.ffshtrg));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_PAEN(%u %u %u) error ercd=0x%x\n", unitNo, ch, paenTrg, ercd));
    }
}
#endif

Impro25Print* impro_2_5_print_new(void)
{
	Impro25Print* self = k_object_new_with_private(IMPRO_TYPE_2_5_PRINT, sizeof(Impro25PrintPrivate));

	return self;
}

Impro25Print* impro_2_5_print_get(void)
{
	static Impro25Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_2_5_PRINT, sizeof(Impro25PrintPrivate));
	}

	return self;
}
