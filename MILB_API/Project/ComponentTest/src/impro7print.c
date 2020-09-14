/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈阳
*@brief : ImPro7Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/
#include "impro7print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImPro7Print, im_pro_7_print, ABS_TYPE_IM_PRO_PRINT)
#define IM_PRO_7_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImPro7PrintPrivate, IM_TYPE_PRO_7_PRINT))


struct _ImPro7PrintPrivate
{
};


/**
 *IMPL
 */
static void im_pro_7_print_constructor(ImPro7Print *self)
{
	ImPro7PrintPrivate *priv = IM_PRO_7_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void im_pro_7_print_destructor(ImPro7Print *self)
{
	ImPro7PrintPrivate *priv = IM_PRO_7_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_7_print_15(ImPro7Print *self, kint32 ercd, TImProIntSentopCtrl* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "interrupt_clear1_sentop_interrupt_ctrl() intmd(%u %u)\n", 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.intctl.bit.intmd, intctrl->intMode  ));

        DriverCommon_DDIM_PRINT(( "interrupt_clear1_sentop_interrupt_ctrl(%u) vhdintflg1(0x%08lx) \
        vhdintenb1(0x%08lx) input_param(%lu) AND(0x%08lx)\n", permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.vhdintflg.vhdintflg1.word, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.vhdintenb.vhdintenb1.word, intctrl->vdEnable.interruptBit, 
        ( ((AbsImProPrint*)self)->ioPro->sen.sentop.vhdintenb.vhdintenb1.word & intctrl->vdEnable.interruptBit )   ));

        DriverCommon_DDIM_PRINT(( "interrupt_clear1_sentop_interrupt_ctrl(%u) vhdintflg2(0x%08lx) \
        vhdintenb2(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
        permissionFlg, ((AbsImProPrint*)self)->ioPro->sen.sentop.vhdintflg.vhdintflg2.word, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.vhdintenb.vhdintenb2.word, intctrl->hdEnable.interruptBit, 
        ( ((AbsImProPrint*)self)->ioPro->sen.sentop.vhdintenb.vhdintenb2.word & intctrl->hdEnable.interruptBit )   ));
    } else {
        DriverCommon_DDIM_PRINT(( "interrupt_clear1_sentop_interrupt_ctrl(%u) error ercd=0x%x\n", 
        permissionFlg, ercd ));
    }
}

void im_pro_7_print_16(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_SG_CTRL* intctrl, kuchar permissionFlg, kuchar vhdeg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_SG_Interrupt_Ctrl(%u %u) sgvhdintflg(0x%08lx) \
        sgvhdintenb(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
        permissionFlg, vhdeg, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sgvhdintflg.word, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.sgvhdintenb.word, intctrl->sgVdEnable.interruptBit, 
        ( ((AbsImProPrint*)self)->ioPro->sen.sentop.sgvhdintenb.word & intctrl->sgVdEnable.interruptBit & 
        intctrl->sgHdEnable.interruptBit )  ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_SG_Interrupt_Ctrl(%u) error ercd=0x%x\n", permissionFlg, ercd ));
    }
}

void im_pro_7_print_17(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_GYRO_CTRL* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Gyro_Interrupt_Ctrl(%u) gintflg(0x%08lx) \
        gintenb(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
        permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.gintflg.word, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.gintenb.word, intctrl->gyroEofEnable.interruptBit, 
        ( ((AbsImProPrint*)self)->ioPro->sen.sentop.gintenb.word & intctrl->gyroSofEnable.interruptBit & 
        intctrl->gyroEofEnable.interruptBit )  ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Gyro_Interrupt_Ctrl(%u) error ercd=0x%x\n", permissionFlg, ercd ));
    }
}

void im_pro_7_print_18(ImPro7Print *self, const char* string, kuchar blocknum, kuchar ch, kint32 ercd, 
                        T_IM_PRO_INT_VHD_DELAY_CTRL* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        switch( blocknum ) {
            case 0:
                if( ch == 0 ) {
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr1.bit.hmihadr00 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay \
                        (%u %u) %s hmihadr00(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr1.bit.hmihadr00, intctrl->hdDelay     ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr1.bit.vmihadr00 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmihadr00(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr1.bit.vmihadr00, intctrl->vdHDelay   ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr1.bit.vmivadr00 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmivadr00(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr1.bit.vmivadr00, intctrl->vdVDelay   ));
                    }
                } else {
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr1.bit.hmihadr01 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s hmihadr01(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr1.bit.hmihadr01, intctrl->hdDelay     ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr1.bit.vmihadr01 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmihadr01(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr1.bit.vmihadr01, intctrl->vdHDelay   ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr1.bit.vmivadr01 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmivadr01(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr1.bit.vmivadr01, intctrl->vdVDelay   ));
                    }
                }
                break;

            case 1:
                if( ch == 0 ) {
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr2.bit.hmihadr10 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s hmihadr10(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr2.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr2.bit.hmihadr10, intctrl->hdDelay     ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr2.bit.vmihadr10 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmihadr10(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr2.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr2.bit.vmihadr10, intctrl->vdHDelay   ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr2.bit.vmivadr10 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmivadr10(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr2.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr2.bit.vmivadr10, intctrl->vdVDelay   ));
                    }
                } else {
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr2.bit.hmihadr11 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s hmihadr11(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr2.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr2.bit.hmihadr11, intctrl->hdDelay     ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr2.bit.vmihadr11 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmihadr11(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr2.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr2.bit.vmihadr11, intctrl->vdHDelay   ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr2.bit.vmivadr11 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmivadr11(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr2.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr2.bit.vmivadr11, intctrl->vdVDelay   ));
                    }
                }
                break;

            case 2:
                if( ch == 0 ) {
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr3.bit.hmihadr20 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s hmihadr20(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr3.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr3.bit.hmihadr20, intctrl->hdDelay     ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr3.bit.vmihadr20 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmihadr20(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr3.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr3.bit.vmihadr20, intctrl->vdHDelay   ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr3.bit.vmivadr20 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmivadr20(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr3.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr3.bit.vmivadr20, intctrl->vdVDelay   ));
                    }
                } else {
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr3.bit.hmihadr21 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s hmihadr21(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr3.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr3.bit.hmihadr21, intctrl->hdDelay     ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr3.bit.vmihadr21 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmihadr21(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr3.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr3.bit.vmihadr21, intctrl->vdHDelay   ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr3.bit.vmivadr21 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmivadr21(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr3.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr3.bit.vmivadr21, intctrl->vdVDelay   ));
                    }
                }
                break;

            //case 3:
            default:
                if( ch == 0 ) {
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr4.bit.hmihadr30 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s hmihadr30(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr4.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr4.bit.hmihadr30, intctrl->hdDelay     ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr4.bit.vmihadr30 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmihadr30(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr4.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr4.bit.vmihadr30, intctrl->vdHDelay   ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr4.bit.vmivadr30 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmivadr30(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr4.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr4.bit.vmivadr30, intctrl->vdVDelay   ));
                    }
                } else {
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr4.bit.hmihadr31 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s hmihadr31(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr4.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.hmihadr.hmihadr4.bit.hmihadr31, intctrl->hdDelay     ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr4.bit.vmihadr31 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmihadr31(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr4.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmihadr.vmihadr4.bit.vmihadr31, intctrl->vdHDelay   ));
                    }
                    
                    if(((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr4.bit.vmivadr31 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) %s vmivadr31(0x%08lx %u) input_param(%d)\n", 
                        blocknum, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr4.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.vmivadr.vmivadr4.bit.vmivadr31, intctrl->vdVDelay   ));
                    }
                }
                break;
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_VHD_Delay(%u %u) error ercd=0x%x\n", blocknum, ch, ercd ));
    }
}

void im_pro_7_print_19(ImPro7Print *self, const char* string, kuchar blocknum, kint32 ercd, T_IM_PRO_INT_VHD_DELAY_CTRL* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        if( blocknum == 0 ) {
            if(((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr1.bit.ghadr0 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_Gyro_Int_Delay(%u) %s ghadr0(0x%08lx %u) input_param(%d)\n", 
                        blocknum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr1.bit.ghadr0, intctrl->hdDelay      ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr1.bit.gvadr0 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_Gyro_Int_Delay(%u) %s gvadr0(0x%08lx %u) input_param(%d)\n", 
                        blocknum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr1.bit.gvadr0, intctrl->vdVDelay    ));
            }
        } else if( blocknum == 1 ) {
            if(((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr1.bit.ghadr1 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_Gyro_Int_Delay(%u) %s ghadr1(0x%08lx %u) input_param(%d)\n", 
                        blocknum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr1.bit.ghadr1, intctrl->hdDelay      ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr1.bit.gvadr1 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_Gyro_Int_Delay(%u) %s gvadr1(0x%08lx %u) input_param(%d)\n", 
                        blocknum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr1.bit.gvadr1, intctrl->vdVDelay    ));
            }
        } else if( blocknum == 2 ) {
            if(((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr2.bit.ghadr2 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_Gyro_Int_Delay(%u) %s ghadr2(0x%08lx %u) input_param(%d)\n", 
                        blocknum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr2.bit.ghadr2, intctrl->hdDelay      ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr2.bit.gvadr2 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_Gyro_Int_Delay(%u) %s gvadr2(0x%08lx %u) input_param(%d)\n", 
                        blocknum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr2.bit.gvadr2, intctrl->vdVDelay    ));
            }
        } else {
            if(((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr2.bit.ghadr3 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_Gyro_Int_Delay(%u) %s ghadr3(0x%08lx %u) input_param(%d)\n", 
                        blocknum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.ghadr.ghadr2.bit.ghadr3, intctrl->hdDelay      ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr2.bit.GVADR3 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_Gyro_Int_Delay(%u) %s GVADR3(0x%08lx %u) input_param(%d)\n", 
                        blocknum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr1.word, 
                        ((AbsImProPrint*)self)->ioPro->sen.sentop.gvadr.gvadr2.bit.GVADR3, intctrl->vdVDelay    ));
            }
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_Set_Gyro_Int_Delay(%u) error ercd=0x%x\n", blocknum, ercd ));
    }
}


void im_pro_7_print_20(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intctrl )
{
}

void im_pro_7_print_21(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "interrupt_sen_set_vd_int_handler() %s CB address 0x%08lx userParam 0x%08lx\n", 
        string, (kulong)intctrl->inthandler, intctrl->userParam ));
    } else {
        DriverCommon_DDIM_PRINT(( "interrupt_sen_set_vd_int_handler() error ercd=0x%x\n", ercd ));
    }
}

void im_pro_7_print_22(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SEN_Set_HD_Int_Handler() %s CB address 0x%08lx userParam 0x%08lx\n", 
        string, (kulong)intctrl->inthandler, intctrl->userParam    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SEN_Set_HD_Int_Handler() error ercd=0x%x\n", ercd ));
    }
}

void im_pro_7_print_30(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        if(((AbsImProPrint*)self)->ioPro->sen.slvsec.common.peinten.word != intctrl->interruptBit) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SLVS_Set_Common_Interrupt(%u) sgvhdintflg(0x%08lx) \
                        sgvhdintenb(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                        permissionFlg,
                        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.peintst.word,
                        ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.peinten.word,intctrl->interruptBit,
                        ( ((AbsImProPrint*)self)->ioPro->sen.slvsec.common.peinten.word & intctrl->interruptBit ) ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SLVS_Set_Common_Interrupt(%u) error ercd=0x%x\n", permissionFlg, ercd ));
    }
}

void im_pro_7_print_31(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SLVS_Set_Common_Int_Handler() %s CB address 0x%08lx userParam 0x%08lx\n", 
        string, (kulong)intctrl->inthandler, intctrl->userParam   ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SLVS_Set_Common_Int_Handler() error ercd=0x%x\n", ercd ));
    }
}

void im_pro_7_print_32(ImPro7Print *self, kint32 ercd, E_IM_PRO_SLVS_STREAM_TYPE streaType, 
                        E_IM_PRO_SLVS_INT_TYPE intType, T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
	if( streaType > E_IM_PRO_SLVS_STREAM_TYPE_B  ) {
		return;
	}
    if( ercd == DdimUserCustom_E_OK ) {
        switch( intType ) {
            case E_IM_PRO_SLVS_INT_TYPE_INTN_O:
                DriverCommon_DDIM_PRINT(( "Im_PRO_SLVS_Set_Interrupt(%u %u %u) intst(0x%08lx) \
                            inten(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                            streaType,
                            intType,
                            permissionFlg,
                            ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].intst.word,
                            ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].inten.word,
                            intctrl->interruptBit,
                            ( ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].inten.word & intctrl->interruptBit )  ));
                break;
            case E_IM_PRO_SLVS_INT_TYPE_LINK_ERR:
                DriverCommon_DDIM_PRINT(( "Im_PRO_SLVS_Set_Interrupt(%u %u %u) leintst(0x%08lx) \
                            leinten(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                            streaType,
                            intType,
                            permissionFlg,
                            ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].leintst.word,
                            ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].leinten.word,
                            intctrl->interruptBit,
                            ( ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].inten.word & 
                            intctrl->interruptBit )  ));
                break;
            case E_IM_PRO_SLVS_INT_TYPE_MAC_ERR1:
                DriverCommon_DDIM_PRINT(( "Im_PRO_SLVS_Set_Interrupt(%u %u %u) meintst0(0x%08lx) \
                            meinten0(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                            streaType,
                            intType,
                            permissionFlg,
                            ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].meintst0.word,
                            ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].meinten0.word,
                            intctrl->interruptBit,
                            ( ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].inten.word & intctrl->interruptBit )  ));
                break;
            //case E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2:
            default:
                DriverCommon_DDIM_PRINT(( "Im_PRO_SLVS_Set_Interrupt(%u %u %u) meintst1(0x%08lx) \
                            meinten1(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                            streaType,
                            intType,
                            permissionFlg,
                            ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].meintst1.word,
                            ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].meinten1.word,
                            intctrl->interruptBit,
                            ( ((AbsImProPrint*)self)->ioPro->sen.slvsec.stream[streaType].inten.word & intctrl->interruptBit )  ));
                break;
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SLVS_Set_Interrupt(%u %u %u) error ercd=0x%x\n", 
                            streaType, intType, permissionFlg, ercd ));
    }
}

void im_pro_7_print_33(ImPro7Print *self, const char* string, E_IM_PRO_SLVS_STREAM_TYPE streaType, 
                            E_IM_PRO_SLVS_INT_TYPE intType, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SLVS_Set_Common_Int_Handler(%u %u) %s CB \
                            address 0x%08lx userParam 0x%08lx\n",  streaType, intType,
                            string, (kulong)intctrl->inthandler, intctrl->userParam    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SLVS_Set_Common_Int_Handler(%u %u) error ercd=0x%x\n", streaType, intType, ercd ));
    }
}

void im_pro_7_print_34(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_LVDS_CTRL* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_LVDS_Set_Interrupt(%u %u) lvdsintflg0(0x%08lx) \
                            lvdsintenb0(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                            ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintenb0.word,
                            ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintflg0.word,
                            intctrl->lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_NORNAL].interruptBit,
                            ( ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintenb0.word & 
                            intctrl->lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_NORNAL].interruptBit )    ));

        DriverCommon_DDIM_PRINT(( "Im_PRO_LVDS_Set_Interrupt(%u %u) lvdsintflg1(0x%08lx)  \
                            lvdsintenb1(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                            ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintenb1.word,
                            ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintflg1.word,
                            intctrl->lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL1].interruptBit,
                            ( ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintenb1.word & 
                            intctrl->lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL1].interruptBit )      ));

        DriverCommon_DDIM_PRINT(( "Im_PRO_LVDS_Set_Interrupt(%u %u) lvdsintflg2(0x%08lx) \
                            lvdsintenb2(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                            ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintenb2.word,
                            ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintflg2.word,
                            intctrl->lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL2].interruptBit,
                            ( ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdsintenb2.word & 
                            intctrl->lvdsIntEnable[E_IM_PRO_LVDS_OUTPUT_MODE_DOL2].interruptBit )      ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_LVDS_Set_Interrupt(%u %u) error ercd=0x%x\n", ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_35(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_LVDS_Set_Int_Handler(%u) %s CB address 0x%08lx userParam 0x%08lx\n", 
                            ch, string, (kulong)intctrl->inthandler, intctrl->userParam ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_LVDS_Set_Int_Handler(%u) error ercd=0x%x\n", ch, ercd ));
    }
}

void im_pro_7_print_36(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DMIPI_Set_Interrupt(%u %u) DMIPIINTFLG0(0x%08lx) \
                    DMIPIINTENB0(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                    ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiinte.word,
                    ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiintf.word, intctrl->interruptBit,
                    ( ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpiinte.word & intctrl->interruptBit ) ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DMIPI_Set_Interrupt(%u %u) error ercd=0x%x\n", 
        ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_37(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DMIPI_Set_Int_Handler(%u) %s CB address 0x%08lx userParam 0x%08lx\n", 
                    ch, string, (kulong)intctrl->inthandler, intctrl->userParam));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_DMIPI_Set_Int_Handler(%u) error ercd=0x%x\n", ch, ercd ));
    }
}

void im_pro_7_print_38(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CMIPI_CTRL* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_CMIPI_Set_Interrupt(%u %u) mpicintf1(0x%08lx) mpicinte1(0x%08lx) \
                    input_param(%lu) AND(0x%08lx)\n", 
                    ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicinte1.word,
                    ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicintf1.word, intctrl->cmipiInt1Enable.interruptBit,
                    ( ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicinte1.word & intctrl->cmipiInt1Enable.interruptBit ) ));

        DriverCommon_DDIM_PRINT(( "Im_PRO_CMIPI_Set_Interrupt(%u %u) mpicintf2(0x%08lx) \
                    mpicinte2(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                    ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicinte2.word,
                    ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicintf2.word,
                    intctrl->cmipiInt2Enable.interruptBit,
                    ( ((AbsImProPrint*)self)->ioPro->sen.mipic[ch].mpicinte2.word & intctrl->cmipiInt2Enable.interruptBit ) ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_CMIPI_Set_Interrupt(%u %u) error ercd=0x%x\n", ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_39(ImPro7Print *self, const char* string, kuchar ch, kuchar  cate, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_CMIPI_Set_Int_Handler(%u %u) %s CB address 0x%08lx userParam 0x%08lx\n", 
                    ch, cate, string, (kulong)intctrl->inthandler, intctrl->userParam ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_CMIPI_Set_Int_Handler(%u %u) error ercd=0x%x\n", ch, cate, ercd ));
    }
}

void im_pro_7_print_40(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    const T_IM_PRO_COMMON_MONI_INFO* moniInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_moni_reg_info( unitNo, blockType, ch, &moniInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Set_Interrupt(%u %u %u %u) MONIINTFLG0(0x%08lx) \
                    MONIINTENB0(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                    unitNo, blockType, ch, permissionFlg, moniInfo->regPtr->moniintenb.word,
                    moniInfo->regPtr->moniintflg.word, intctrl->interruptBit,
                    ( moniInfo->regPtr->moniintenb.word & intctrl->interruptBit )    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Set_Interrupt(%u %u %u %u) error ercd=0x%x\n", 
        unitNo, blockType, ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_41(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType,
                         kuchar ch, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Set_Int_Handler(%u %u %u) %s CB address 0x%08lx userParam 0x%08lx\n", 
                    unitNo, blockType, ch, string, (kulong)intctrl->inthandler,
                    intctrl->userParam    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Set_Int_Handler(%u %u %u) error ercd=0x%x\n",  unitNo, blockType, ch, ercd ));
    }
}

void im_pro_7_print_42(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_LDIV_Set_Interrupt(%u %u) LDIVINTFLG0(0x%08lx) \
                    LDIVINTENB0(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                    ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivintenb.word,
                    ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivintflg.word, intctrl->interruptBit,
                    ( ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivintenb.word & intctrl->interruptBit )   ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_LDIV_Set_Interrupt(%u %u) error ercd=0x%x\n", 
        ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_43(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_LDIV_Set_Int_Handler(%u) %s CB address 0x%08lx userParam 0x%08lx\n", 
                    ch, string, (kulong)intctrl->inthandler, intctrl->userParam    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_LDIV_Set_Int_Handler(%u) error ercd=0x%x\n", ch, ercd ));
    }
}

void im_pro_7_print_44(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        kuchar blocknum = 0;
        kuchar chNum = 0;
        im_pro_comm_get_obt_block_ch( ch, &blocknum, &chNum );
        DriverCommon_DDIM_PRINT(( "Im_PRO_OBT_Set_Interrupt(%u %u) OBTINTFLG0(0x%08lx) OBTINTENB0(0x%08lx) \
                     input_param(%lu) AND(0x%08lx)\n", 
                    ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blocknum][chNum].obtintenb.word,
                    ((AbsImProPrint*)self)->ioPro->sen.obt[blocknum][chNum].obtintflg.word, intctrl->interruptBit,
                    ( ((AbsImProPrint*)self)->ioPro->sen.obt[blocknum][chNum].obtintenb.word & intctrl->interruptBit )  ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_OBT_Set_Interrupt(%u %u) error ercd=0x%x\n", ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_45(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        kuchar blocknum = 0;
        kuchar chNum = 0;
        im_pro_comm_get_obt_block_ch( ch, &blocknum, &chNum );
        DriverCommon_DDIM_PRINT(( "Im_PRO_OBT_Set_Int_Handler(%u) %s CB address 0x%08lx userParam 0x%08lx\n", 
                    ch, string, (kulong)intctrl->inthandler, intctrl->userParam    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_OBT_Set_Int_Handler(%u) error ercd=0x%x\n", ch, ercd ));
    }
}

void im_pro_7_print_46(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        kuchar blocknum = 0;
        kuchar chNum = 0;
        im_pro_comm_get_obd_block_ch( ch, &blocknum, &chNum );
        DriverCommon_DDIM_PRINT(( "Im_PRO_OBD_Set_Interrupt(%u %u) OBDINTFLG0(0x%08lx) \
                    OBDINTENB0(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                    ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blocknum][chNum].obdintenb.word,
                    ((AbsImProPrint*)self)->ioPro->sen.obd[blocknum][chNum].obdintflg.word, intctrl->interruptBit,
                    ( ((AbsImProPrint*)self)->ioPro->sen.obd[blocknum][chNum].obdintenb.word & intctrl->interruptBit )  ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_OBD_Set_Interrupt(%u %u) error ercd=0x%x\n", ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_47(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        kuchar blocknum = 0;
        kuchar chNum = 0;
        im_pro_comm_get_obd_block_ch( ch, &blocknum, &chNum );
        DriverCommon_DDIM_PRINT(( "Im_PRO_OBD_Set_Int_Handler(%u) %s CB address 0x%08lx userParam 0x%08lx\n", 
                    ch, string, (kulong)intctrl->inthandler,
                    intctrl->userParam    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_OBD_Set_Int_Handler(%u) error ercd=0x%x\n", ch, ercd ));
    }
}

void im_pro_7_print_48(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, 
                        T_IM_PRO_INT_SROTOP_CTRL* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Interrupt_Ctrl(%u %u) intmd(%u %u) vhdintflg(0x%08lx) \
                    vhdintenb(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                    unitNo, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.intctl.bit.intmd,
                    intctrl->intMode, 
        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vhdintflg.word,
                    ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vhdintenb.word,
                    ( intctrl->vdEnable[0].interruptBit | intctrl->vdEnable[1].interruptBit | 
                    intctrl->hdEnable[0].interruptBit | intctrl->hdEnable[1].interruptBit ),
                    ( ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vhdintenb.word & ( intctrl->vdEnable[0].interruptBit | 
                    intctrl->vdEnable[1].interruptBit | intctrl->hdEnable[0].interruptBit | 
                    intctrl->hdEnable[1].interruptBit ) )  ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Interrupt_Ctrl(%u %u) error ercd=0x%x\n", unitNo, permissionFlg, ercd ));
    }
}

void im_pro_7_print_49(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, 
                        kint32 ercd, T_IM_PRO_INT_VHD_DELAY_CTRL* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        if( ch == 0 ) {
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.hmihadr.bit.hmihadr0 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Set_VHD_Delay(%u %u) %s hmihadr0(0x%08lx %d) input_param(%d)\n", 
                        unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.hmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.hmihadr.bit.hmihadr0, intctrl->hdDelay        ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmihadr.bit.vmihadr0 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Set_VHD_Delay(%u %u) %s vmihadr0(0x%08lx %d) input_param(%d)\n", 
                        unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmihadr.bit.vmihadr0, intctrl->vdHDelay      ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmivadr.bit.vmivadr0 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Set_VHD_Delay(%u %u) %s vmivadr0(0x%08lx %d) input_param(%d)\n", 
                        unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmivadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmivadr.bit.vmivadr0, intctrl->vdVDelay      ));
            }
        } else {
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.hmihadr.bit.hmihadr1 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Set_VHD_Delay(%u %u) %s hmihadr1(0x%08lx %d) input_param(%d)\n", 
                        unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.hmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.hmihadr.bit.hmihadr1, intctrl->hdDelay        ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmihadr.bit.vmihadr1 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Set_VHD_Delay(%u %u) %s vmihadr1(0x%08lx %d) input_param(%d)\n", 
                        unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmihadr.bit.vmihadr1, intctrl->vdHDelay      ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmivadr.bit.vmivadr1 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Set_VHD_Delay(%u %u) %s vmivadr1(0x%08lx %d) input_param(%d)\n", 
                        unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmivadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.srotop.vmivadr.bit.vmivadr1, intctrl->vdVDelay      ));
            }
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Set_VHD_Delay(%u %u) error ercd=0x%x\n", unitNo, ch, ercd ));
    }
}

void im_pro_7_print_50(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, TImProCallbackCfg* intctrl )
{
}

void im_pro_7_print_51(ImPro7Print *self, const char* string, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Pipe_Set_VD_Int_Handler(%u) %s CB address 0x%08lx userParam 0x%08lx\n", 
        unitNo, string, (kulong)intctrl->inthandler, intctrl->userParam ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Pipe_Set_VD_Int_Handler(%u) error ercd=0x%x\n", unitNo, ercd ));
    }
}

void im_pro_7_print_52(ImPro7Print *self, const char* string, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Pipe_Set_HD_Int_Handler(%u) %s CB address 0x%08lx userParam 0x%08lx\n", 
        unitNo, string, (kulong)intctrl->inthandler, intctrl->userParam ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SROTOP_Pipe_Set_HD_Int_Handler(%u) error ercd=0x%x\n",unitNo, ercd ));
    }
}

void im_pro_7_print_59(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
                        T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Set_Interrupt(%u %u %u) sdcintflg(0x%08lx) \
                sdcintenb(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
                unitNo, ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcintenb.word,
                ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcintflg.word, intctrl->interruptBit,
                ( ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcintenb.word & intctrl->interruptBit )));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Set_Interrupt(%u %u %u) error ercd=0x%x\n", unitNo, ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_60(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
                        kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Set_Int_Handler(%u %u) %s CB address 0x%08lx userParam 0x%08lx\n", 
                unitNo, ch, string, (kulong)intctrl->inthandler, intctrl->userParam));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Set_Int_Handler(%u %u) error ercd=0x%x\n", unitNo, ch, ercd ));
    }
}

void im_pro_7_print_61(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_INT_B2BTOP_CTRL* 
                        intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Interrupt_Ctrl(%u %u) intmd(%u %u) \
            vhdintflg(0x%08lx) vhdintenb(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
            unitNo, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.intctl.bit.intmd,
            intctrl->intMode, 
        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vhdintflg.word,
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vhdintenb.word,
            ( intctrl->vdEnable[0].interruptBit | intctrl->vdEnable[1].interruptBit | 
            intctrl->hdEnable[0].interruptBit | intctrl->hdEnable[1].interruptBit ),
            ( ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vhdintenb.word & ( intctrl->vdEnable[0].interruptBit | 
            intctrl->vdEnable[1].interruptBit | intctrl->hdEnable[0].interruptBit | 
            intctrl->hdEnable[1].interruptBit ) )  ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Interrupt_Ctrl(%u %u) error ercd=0x%x\n", unitNo, permissionFlg, ercd ));
    }
}

void im_pro_7_print_62(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, kint32 ercd, 
                        T_IM_PRO_INT_VHD_DELAY_CTRL* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        if( ch == 0 ) {
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.hmihadr.bit.hmihadr0 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Set_VHD_Delay(%u %u) %s hmihadr0(0x%08lx %d) input_param(%d)\n", 
                        unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.hmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.hmihadr.bit.hmihadr0, intctrl->hdDelay        ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmihadr.bit.vmihadr0 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Set_VHD_Delay(%u %u) %s vmihadr0(0x%08lx %d) input_param(%d)\n", 
                         unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmihadr.bit.vmihadr0, intctrl->vdHDelay      ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmivadr.bit.vmivadr0 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Set_VHD_Delay(%u %u) %s vmivadr0(0x%08lx %d) input_param(%d)\n", 
                         unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmivadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmivadr.bit.vmivadr0, intctrl->vdVDelay      ));
            }
        } else {
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.hmihadr.bit.hmihadr1 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Set_VHD_Delay(%u %u) %s hmihadr1(0x%08lx %d) input_param(%d)\n", 
                         unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.hmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.hmihadr.bit.hmihadr1, intctrl->hdDelay        ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmihadr.bit.vmihadr1 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Set_VHD_Delay(%u %u) %s vmihadr1(0x%08lx %d) input_param(%d)\n", 
                         unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmihadr.bit.vmihadr1, intctrl->vdHDelay      ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmivadr.bit.vmivadr1 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Set_VHD_Delay(%u %u) %s vmivadr1(0x%08lx %d) input_param(%d)\n", 
                         unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmivadr.word, 
                        ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].b2b.b2btop.vmivadr.bit.vmivadr1, intctrl->vdVDelay      ));
            }
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Set_VHD_Delay(%u %u) error ercd=0x%x\n", unitNo, ch, ercd ));
    }
}

void im_pro_7_print_64(ImPro7Print *self, const char* string, kint32 ercd, 
                        E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Pipe_Set_VD_Int_Handler(%u) %s CB \
                                address 0x%08lx userParam 0x%08lx\n", 
        unitNo, string, (kulong)intctrl->inthandler, intctrl->userParam ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Pipe_Set_VD_Int_Handler(%u) error ercd=0x%x\n", unitNo, ercd ));
    }
}

void im_pro_7_print_65(ImPro7Print *self, const char* string, kint32 ercd, 
                        E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Pipe_Set_HD_Int_Handler(%u) %s CB address 0x%08lx userParam 0x%08lx\n", 
        unitNo, string, (kulong)intctrl->inthandler, intctrl->userParam ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_B2BTOP_Pipe_Set_HD_Int_Handler(%u) error ercd=0x%x\n", unitNo, ercd ));
    }
}

void im_pro_7_print_72(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_STATTOP_CTRL* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_STATTOP_Interrupt_Ctrl() intmd(%u) input_param(%d)\n", 
        ((AbsImProPrint*)self)->ioPro->stat.stattop.intctl.bit.intmd, intctrl->intMode  ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_STATTOP_Interrupt_Ctrl() error ercd=0x%x\n", ercd ));
    }
}

void im_pro_7_print_74(ImPro7Print *self, kint32 ercd, E_IM_PRO_AEAWB_CH ch, 
                        T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_AEAWB_Set_Interrupt(%u %u) lineintenb(0x%08lx) \
            lineintflg(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
            ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].lineintenb.word,
            ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].lineintflg.word, intctrl->interruptBit,
            ( ((AbsImProPrint*)self)->ioPro->stat.aeawb[ch].lineintenb.word & intctrl->interruptBit ) ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_AEAWB_Set_Interrupt(%u %u) error ercd=0x%x\n", ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_75(ImPro7Print *self, const char* string, 
                        E_IM_PRO_AEAWB_CH ch, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_AEAWB_Set_Int_Handler(%u) %s CB address 0x%08lx userParam 0x%08lx\n", 
            ch, string, (kulong)intctrl->inthandler, intctrl->userParam    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_AEAWB_Set_Int_Handler(%u) error ercd=0x%x\n", ch, ercd ));
    }
}

void im_pro_7_print_76(ImPro7Print *self, kint32 ercd, E_IM_PRO_AF_CH ch, 
                        T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_AF_Set_Interrupt(%u %u) lineintenb(0x%08lx) \
            lineintflg(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
            ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afintenb.word,
            ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afintflg.word, intctrl->interruptBit,
            ( ((AbsImProPrint*)self)->ioPro->stat.af[ch].afgbal.afintenb.word & intctrl->interruptBit )   ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_AF_Set_Interrupt(%u %u) error ercd=0x%x\n", ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_77(ImPro7Print *self, const char* string, E_IM_PRO_AF_CH ch, 
                        kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_AF_Set_Int_Handler(%u) %s CB address 0x%08lx userParam 0x%08lx\n", 
            ch, string, (kulong)intctrl->inthandler, intctrl->userParam    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_AF_Set_Int_Handler(%u) error ercd=0x%x\n", ch, ercd ));
    }
}

void im_pro_7_print_78(ImPro7Print *self, kint32 ercd, E_IM_PRO_HIST_CH ch, 
                        T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_HIST_Set_Interrupt(%u %u) lineintenb(0x%08lx)\
            lineintflg(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
            ch, permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histintenb.word,
            ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histintflg.word, intctrl->interruptBit,
            ( ((AbsImProPrint*)self)->ioPro->stat.hist[ch].histintenb.word & intctrl->interruptBit )  ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_HIST_Set_Interrupt(%u %u) error ercd=0x%x\n", ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_79(ImPro7Print *self, const char* string, E_IM_PRO_HIST_CH ch, 
                        kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_HIST_Set_Int_Handler(%u) %s CB address 0x%08lx userParam 0x%08lx\n", 
            ch, string, (kulong)intctrl->inthandler, intctrl->userParam    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_HIST_Set_Int_Handler(%u) error ercd=0x%x\n", ch, ercd ));
    }
}

void im_pro_7_print_80(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_PASTOP_CTRL* intctrl, kuchar permissionFlg )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Interrupt_CtrlTOP_Interrupt_Ctrl(%u) intmd(%u %u) \
            vhdintflg(0x%08lx) vhdintenb(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
            permissionFlg, 
        ((AbsImProPrint*)self)->ioPro->pas.pastop.intctl.bit.intmd,
            intctrl->intMode, 
        ((AbsImProPrint*)self)->ioPro->pas.pastop.vhdintflg.word, 
        ((AbsImProPrint*)self)->ioPro->pas.pastop.vhdintenb.word,
            ( intctrl->vdEnable[0].interruptBit | intctrl->vdEnable[1].interruptBit |
            intctrl->hdEnable[0].interruptBit | intctrl->hdEnable[1].interruptBit ),
            ( ((AbsImProPrint*)self)->ioPro->pas.pastop.vhdintenb.word & ( intctrl->vdEnable[0].interruptBit | 
            intctrl->vdEnable[1].interruptBit | intctrl->hdEnable[0].interruptBit | 
            intctrl->hdEnable[1].interruptBit ) )    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Interrupt_Ctrl() error ercd=0x%x\n", ercd ));
    }
}

void im_pro_7_print_81(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, T_IM_PRO_INT_VHD_DELAY_CTRL* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        if( ch == 0 ) {
            if(((AbsImProPrint*)self)->ioPro->pas.pastop.hmihadr.bit.hmihadr0 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Set_VHD_Delay(%u) %s hmihadr(0x%08lx %d) input_param(%u)\n", 
                        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->pas.pastop.hmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->pas.pastop.hmihadr.bit.hmihadr0, intctrl->hdDelay     ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->pas.pastop.vmihadr.bit.vmihadr0 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Set_VHD_Delay(%u) %s vmihadr(0x%08lx %d) input_param(%u)\n", 
                        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->pas.pastop.vmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->pas.pastop.vmihadr.bit.vmihadr0, intctrl->vdHDelay   ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->pas.pastop.vmivadr.bit.vmivadr0 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Set_VHD_Delay(%u) %s vmivadr(0x%08lx %d) input_param(%u)\n", 
                        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->pas.pastop.vmivadr.word, 
                        ((AbsImProPrint*)self)->ioPro->pas.pastop.vmivadr.bit.vmivadr0, intctrl->vdVDelay   ));
            }
        } else {
            if(((AbsImProPrint*)self)->ioPro->pas.pastop.hmihadr.bit.hmihadr1 != intctrl->hdDelay  ) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Set_VHD_Delay(%u) %s hmihadr(0x%08lx %d) input_param(%u)\n", 
                        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->pas.pastop.hmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->pas.pastop.hmihadr.bit.hmihadr1, intctrl->hdDelay     ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->pas.pastop.vmihadr.bit.vmihadr1 != intctrl->vdHDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Set_VHD_Delay(%u) %s vmihadr(0x%08lx %d) input_param(%u)\n", 
                        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->pas.pastop.vmihadr.word, 
                        ((AbsImProPrint*)self)->ioPro->pas.pastop.vmihadr.bit.vmihadr1, intctrl->vdHDelay   ));
            }
            
            if(((AbsImProPrint*)self)->ioPro->pas.pastop.vmivadr.bit.vmivadr1 != intctrl->vdVDelay) {
                        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Set_VHD_Delay(%u) %s vmivadr(0x%08lx %d) input_param(%u)\n", 
                        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->pas.pastop.vmivadr.word, 
                        ((AbsImProPrint*)self)->ioPro->pas.pastop.vmivadr.bit.vmivadr1, intctrl->vdVDelay   ));
            }
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Set_VHD_Delay(%u) error ercd=0x%x\n", ch, ercd ));
    }
}

void im_pro_7_print_83(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Set_VD_Int_Handler() %s CB address 0x%08lx userParam 0x%08lx\n", 
        string, (kulong)intctrl->inthandler, intctrl->userParam ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Set_VD_Int_Handler() error ercd=0x%x\n", ercd ));
    }
}

void im_pro_7_print_84(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Set_HD_Int_Handler() %s CB address 0x%08lx userParam 0x%08lx\n", 
        string, (kulong)intctrl->inthandler, intctrl->userParam ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Set_HD_Int_Handler() error ercd=0x%x\n", ercd ));
    }
}

void im_pro_7_print_88(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    const T_IM_PRO_COMMON_PWCH_INFO* pwchRegInfo = 0;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pwch_reg_info( unitNo, blockType, ch, &pwchRegInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Set_Interrupt(%u %u %u %u) pwchintflg(0x%08lx) \
            pwchintenb(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
            unitNo, blockType, ch, permissionFlg,
            pwchRegInfo->regPtr->pwchintenb.word,
            pwchRegInfo->regPtr->pwchintflg.word,
            intctrl->interruptBit,
            ( pwchRegInfo->regPtr->pwchintenb.word & intctrl->interruptBit )   ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Set_Interrupt(%u %u %u %u) error ercd=0x%x\n", 
        unitNo, blockType, ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_89(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Set_Int_Handler(%u %u %u) %s CB address 0x%08lx userParam 0x%08lx\n", 
                                unitNo, blockType, ch, string, (kulong)intctrl->inthandler, intctrl->userParam    ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Set_Int_Handler(%u %u %u) error ercd=0x%x\n", 
                                unitNo, blockType, ch, ercd ));
    }
}

void im_pro_7_print_90(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, T_IM_PRO_INT_CFG* intctrl, kuchar permissionFlg )
{
    const T_IM_PRO_COMMON_PRCH_INFO* prchRegInfo = 0;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_prch_reg_info( unitNo, blockType, ch, &prchRegInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Set_Interrupt(%u %u %u %u) prchintflg(0x%08lx) \
            prchintenb(0x%08lx) input_param(%lu) AND(0x%08lx)\n", 
            unitNo, blockType, ch, permissionFlg,
            prchRegInfo->regPtr->prchintenb.word,
            prchRegInfo->regPtr->prchintflg.word,
            intctrl->interruptBit,
            ( prchRegInfo->regPtr->prchintenb.word & intctrl->interruptBit )   ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Set_Interrupt(%u %u %u %u) error ercd=0x%x\n", 
        unitNo, blockType, ch, permissionFlg, ercd ));
    }
}

void im_pro_7_print_91(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, TImProCallbackCfg* intctrl )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Set_Int_Handler(%u %u %u) %s CB address 0x%08lx userParam 0x%08lx\n", 
            unitNo, blockType, ch, string, (kulong)intctrl->inthandler, intctrl->userParam));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Set_Int_Handler(%u %u %u) error ercd=0x%x\n", 
                                unitNo, blockType, ch, ercd ));
    }
}
#endif

ImPro7Print* im_pro_7_print_new(void)
{
	ImPro7Print* self = k_object_new_with_private(IM_TYPE_PRO_7_PRINT, sizeof(ImPro7PrintPrivate));

	return self;
}

ImPro7Print* im_pro_7_print_get(void)
{
	static ImPro7Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_7_PRINT, sizeof(ImPro7PrintPrivate));
	}

	return self;
}
