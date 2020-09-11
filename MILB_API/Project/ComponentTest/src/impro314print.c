/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro314Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro314print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro314Print, impro_3_1_4_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_3_1_4_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro314PrintPrivate, IMPRO_TYPE_3_1_4_PRINT))


struct _Impro314PrintPrivate
{


};


static void impro_3_1_4_print_constructor(Impro314Print *self)
{
	Impro314PrintPrivate *priv = IMPRO_3_1_4_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_3_1_4_print_destructor(Impro314Print *self)
{
	Impro314PrintPrivate *priv = IMPRO_3_1_4_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_3_1_4_Print(Impro314Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, 
                        T_IM_PRO_ELF_f9_SAMPLING* elfCtrl)
{
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w1.bit.fs9wR != elfCtrl->rgbGain.gain[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9wR 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w1.bit.fs9wR ,elfCtrl->rgbGain.gain[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w1.bit.fs9wG != elfCtrl->rgbGain.gain[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9wG 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w1.bit.fs9wG ,elfCtrl->rgbGain.gain[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w2.bit.fs9wB != elfCtrl->rgbGain.gain[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9wB 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9w.fs9w2.bit.fs9wB ,elfCtrl->rgbGain.gain[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc1.bit.fs9yc00 != elfCtrl->ycConvMatrix[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9yc00 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc1.bit.fs9yc00 ,elfCtrl->ycConvMatrix[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc1.bit.fs9yc01 != elfCtrl->ycConvMatrix[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9yc01 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc1.bit.fs9yc01 ,elfCtrl->ycConvMatrix[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc2.bit.fs9yc02 != elfCtrl->ycConvMatrix[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9yc02 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc2.bit.fs9yc02 ,elfCtrl->ycConvMatrix[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc2.bit.fs9yc10 != elfCtrl->ycConvMatrix[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9yc10 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc2.bit.fs9yc10 ,elfCtrl->ycConvMatrix[3]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc3.bit.fs9yc11 != elfCtrl->ycConvMatrix[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9yc11 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc3.bit.fs9yc11 ,elfCtrl->ycConvMatrix[4]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc3.bit.fs9yc12 != elfCtrl->ycConvMatrix[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9yc12 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc3.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc3.bit.fs9yc12 ,elfCtrl->ycConvMatrix[5]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc4.bit.fs9yc20 != elfCtrl->ycConvMatrix[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9yc20 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc4.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc4.bit.fs9yc20 ,elfCtrl->ycConvMatrix[6]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc4.bit.fs9yc21 != elfCtrl->ycConvMatrix[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9yc21 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc4.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc4.bit.fs9yc21 ,elfCtrl->ycConvMatrix[7]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc5.bit.fs9yc22 != elfCtrl->ycConvMatrix[8]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fs9yc22 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc5.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fs9yc.fs9yc5.bit.fs9yc22 ,elfCtrl->ycConvMatrix[8]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fastr.bit.fastr != elfCtrl->f9aGroup.strength) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fastr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fastr.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fastr.bit.fastr,elfCtrl->f9aGroup.strength));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.bit.crvafx1 != elfCtrl->f9aGroup.eFocusCoord[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:crvafx1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.bit.crvafx1,elfCtrl->f9aGroup.eFocusCoord[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.bit.crvafy1 != elfCtrl->f9aGroup.eFocusCoord[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:crvafy1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.bit.crvafy1,elfCtrl->f9aGroup.eFocusCoord[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.bit.crvafx2 != elfCtrl->f9aGroup.eFocusCoord[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:crvafx2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.bit.crvafx2,elfCtrl->f9aGroup.eFocusCoord[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.bit.crvafy2 != elfCtrl->f9aGroup.eFocusCoord[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:crvafy2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvaf.bit.crvafy2,elfCtrl->f9aGroup.eFocusCoord[3]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtof.bit.fcrvabtof1 != elfCtrl->f9aGroup.ePolygonalLineOffset1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvabtof1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtof.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtof.bit.fcrvabtof1 ,elfCtrl->f9aGroup.ePolygonalLineOffset1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtga.bit.fcrvabtga0 != 
        elfCtrl->f9aGroup.ePolygonalLineMinusInclination[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvabtga0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtga.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtga.bit.fcrvabtga0 ,
            elfCtrl->f9aGroup.ePolygonalLineMinusInclination[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtga.bit.fcrvabtga1 != 
        elfCtrl->f9aGroup.ePolygonalLineMinusInclination[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvabtga1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtga.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtga.bit.fcrvabtga1 ,
            elfCtrl->f9aGroup.ePolygonalLineMinusInclination[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtbd.bit.fcrvabtbd1 != 
        elfCtrl->f9aGroup.ePolygonalLineBoundary1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvabtbd1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtbd.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtbd.bit.fcrvabtbd1 ,
            elfCtrl->f9aGroup.ePolygonalLineBoundary1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtcp.bit.fcrvabtcph != elfCtrl->f9aGroup.eUpperClip) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvabtcph 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtcp.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtcp.bit.fcrvabtcph ,elfCtrl->f9aGroup.eUpperClip));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtcp.bit.fcrvabtcpl != elfCtrl->f9aGroup.eLowerClip) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvabtcpl 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtcp.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvabtcp.bit.fcrvabtcpl ,elfCtrl->f9aGroup.eLowerClip));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtga.bit.fyabtga0 != 
        elfCtrl->f9aGroup.lPolygonalLinePlusInclination0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fyabtga0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtga.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtga.bit.fyabtga0 ,
            elfCtrl->f9aGroup.lPolygonalLinePlusInclination0));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtga.bit.fyabtga1 != 
        elfCtrl->f9aGroup.lPolygonalLineMinusInclination1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fyabtga1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtga.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtga.bit.fyabtga1 ,
            elfCtrl->f9aGroup.lPolygonalLineMinusInclination1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtbd.bit.fyabtbd0 != 
        elfCtrl->f9aGroup.lPolygonalLineBoundary[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fyabtbd0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtbd.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtbd.bit.fyabtbd0 ,
            elfCtrl->f9aGroup.lPolygonalLineBoundary[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtbd.bit.fyabtbd1 != 
        elfCtrl->f9aGroup.lPolygonalLineBoundary[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fyabtbd1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtbd.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtbd.bit.fyabtbd1 ,
            elfCtrl->f9aGroup.lPolygonalLineBoundary[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtclp.bit.fyabtclph != elfCtrl->f9aGroup.lUpperClip) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fyabtclph 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtclp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtclp.bit.fyabtclph ,elfCtrl->f9aGroup.lUpperClip));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtclp.bit.fyabtclpl != elfCtrl->f9aGroup.lLowerClip) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fyabtclpl 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtclp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fyabtclp.bit.fyabtclpl ,elfCtrl->f9aGroup.lLowerClip));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.faehh.bit.faechh != elfCtrl->f9aGroup.tFProfileTransition) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:faechh 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.faehh.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.faehh.bit.faechh ,elfCtrl->f9aGroup.tFProfileTransition));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.faehh.bit.faethh != elfCtrl->f9aGroup.tFProfileThreshold) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:faethh 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.faehh.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.faehh.bit.faethh ,elfCtrl->f9aGroup.tFProfileThreshold));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbstr.bit.fbstr != elfCtrl->f9bGroup.strength) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fbstr 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbstr.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbstr.bit.fbstr,elfCtrl->f9bGroup.strength));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.bit.crvbfy2 != elfCtrl->f9bGroup.eFocusCoord[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:crvbfy2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.bit.crvbfy2,elfCtrl->f9bGroup.eFocusCoord[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.bit.crvbfx2 != elfCtrl->f9bGroup.eFocusCoord[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:crvbfx2 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.bit.crvbfx2,elfCtrl->f9bGroup.eFocusCoord[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.bit.crvbfy1 != elfCtrl->f9bGroup.eFocusCoord[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:crvbfy1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.bit.crvbfy1,elfCtrl->f9bGroup.eFocusCoord[2]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.bit.crvbfx1 != elfCtrl->f9bGroup.eFocusCoord[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:crvbfx1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.crvbf.bit.crvbfx1,elfCtrl->f9bGroup.eFocusCoord[3]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtof.bit.fcrvbbtof1 != elfCtrl->f9bGroup.ePolygonalLineOffset1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvbbtof1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtof.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtof.bit.fcrvbbtof1 ,elfCtrl->f9bGroup.ePolygonalLineOffset1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtga.bit.fcrvbbtga0 != 
        elfCtrl->f9bGroup.ePolygonalLineMinusInclination[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvbbtga0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtga.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtga.bit.fcrvbbtga0 ,
            elfCtrl->f9bGroup.ePolygonalLineMinusInclination[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtga.bit.fcrvbbtga1 != 
        elfCtrl->f9bGroup.ePolygonalLineMinusInclination[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvbbtga1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtga.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtga.bit.fcrvbbtga1 ,
            elfCtrl->f9bGroup.ePolygonalLineMinusInclination[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtbd.bit.fcrvbbtbd1 != 
        elfCtrl->f9bGroup.ePolygonalLineBoundary1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvbbtbd1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtbd.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtbd.bit.fcrvbbtbd1 ,
            elfCtrl->f9bGroup.ePolygonalLineBoundary1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtcp.bit.fcrvbbtcpl != elfCtrl->f9bGroup.eUpperClip) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvbbtcpl 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtcp.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtcp.bit.fcrvbbtcpl ,elfCtrl->f9bGroup.eUpperClip));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtcp.bit.fcrvbbtcph != elfCtrl->f9bGroup.eLowerClip) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fcrvbbtcph 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtcp.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fcrvbbtcp.bit.fcrvbbtcph ,elfCtrl->f9bGroup.eLowerClip));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtga.bit.fybbtga0 != 
        elfCtrl->f9bGroup.lPolygonalLinePlusInclination0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fybbtga0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtga.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtga.bit.fybbtga0 ,
            elfCtrl->f9bGroup.lPolygonalLinePlusInclination0));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtga.bit.fybbtga1 != 
        elfCtrl->f9bGroup.lPolygonalLineMinusInclination1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fybbtga1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtga.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtga.bit.fybbtga1 ,
            elfCtrl->f9bGroup.lPolygonalLineMinusInclination1));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtbd.bit.fybbtbd0 != 
        elfCtrl->f9bGroup.lPolygonalLineBoundary[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fybbtbd0 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtbd.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtbd.bit.fybbtbd0 ,
            elfCtrl->f9bGroup.lPolygonalLineBoundary[0]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtbd.bit.fybbtbd1 != 
        elfCtrl->f9bGroup.lPolygonalLineBoundary[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fybbtbd1 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtbd.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtbd.bit.fybbtbd1 ,
            elfCtrl->f9bGroup.lPolygonalLineBoundary[1]));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtclp.bit.fybbtclpl != elfCtrl->f9bGroup.lUpperClip) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fybbtclpl 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtclp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtclp.bit.fybbtclpl ,elfCtrl->f9bGroup.lUpperClip));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtclp.bit.fybbtclph != elfCtrl->f9bGroup.lLowerClip) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fybbtclph 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtclp.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fybbtclp.bit.fybbtclph ,elfCtrl->f9bGroup.lLowerClip));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbehh.bit.fbechh != elfCtrl->f9bGroup.tFProfileTransition) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fbechh 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbehh.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbehh.bit.fbechh ,elfCtrl->f9bGroup.tFProfileTransition));
        }
        
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbehh.bit.fbethh != elfCtrl->f9bGroup.tFProfileThreshold) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_ELF_Set_F9_Filter(%u) %s result:fbethh 0x%08lx(%d) in(%d)\n", 
            unitNo, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbehh.word , 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.elf.fbehh.bit.fbethh ,elfCtrl->f9bGroup.tFProfileThreshold));
        }
}
#endif

Impro314Print* impro_3_1_4_print_new(void)
{
	Impro314Print* self = k_object_new_with_private(IMPRO_TYPE_3_1_4_PRINT, sizeof(Impro314PrintPrivate));

	return self;
}

Impro314Print* impro_3_1_4_print_get(void)
{
	static Impro314Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_3_1_4_PRINT, sizeof(Impro314PrintPrivate));
	}

	return self;
}
