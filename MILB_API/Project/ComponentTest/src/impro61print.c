/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro61Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro61print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro61Print, impro_6_1_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_6_1_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro61PrintPrivate, IMPRO_TYPE_6_1_PRINT))


struct _Impro61PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_6_1_print_constructor(Impro61Print *self)
{
	Impro61PrintPrivate *priv = IMPRO_6_1_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_6_1_print_destructor(Impro61Print *self)
{
	Impro61PrintPrivate *priv = IMPRO_6_1_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_6_1_print_0(Impro61Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, T_IM_PRO_AXI_CTRL* axiCtrl )
{
    const T_IM_PRO_COMMON_PWCH_INFO* pwchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pwch_reg_info( unitNo, blockType, ch, &pwchInfo );
        if(pwchInfo->regPtr->pwaxctl.bit.awcache != axiCtrl->cacheType) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Ctrl_Axi(%u %u %u) %s result:awcache  (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pwchInfo->regPtr->pwaxctl.bit.awcache, axiCtrl->cacheType ));
        }   
        
        if(pwchInfo->regPtr->pwaxctl.bit.awprot != axiCtrl->protectType) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Ctrl_Axi(%u %u %u) %s result:awprot   (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pwchInfo->regPtr->pwaxctl.bit.awprot, axiCtrl->protectType ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Ctrl_Axi(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_1_print_1(Impro61Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                            E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd )
{
    const T_IM_PRO_COMMON_PWCH_INFO* pwchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pwch_reg_info( unitNo, blockType, ch, &pwchInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Set_Buf_Addr(%u %u %u) %s result:pwsa (0x%08lx)\n", 
            unitNo, blockType, ch, string, pwchInfo->regPtr->pwsa.bit.pwsa ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Set_Buf_Addr(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_1_print_3(Impro61Print *self, kuint32 bufIdx, E_IM_PRO_UNIT_NUM unitNo, 
                        E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd )
{
    const T_IM_PRO_COMMON_PWCH_INFO* pwchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pwch_reg_info( unitNo, blockType, ch, &pwchInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Update_Buf_Index(%u %u %u %u) result:pwsa    (0x%lx)\n", 
            unitNo, blockType, ch, bufIdx, (kulong)pwchInfo->regPtr->pwsa.bit.pwsa));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Update_Buf_Index(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_1_print_4(Impro61Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                        E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd, kulong lineFeed )
{
    const T_IM_PRO_COMMON_PWCH_INFO* pwchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pwch_reg_info( unitNo, blockType, ch, &pwchInfo );
        if(pwchInfo->regPtr->pwlsize.bit.pwlsize != lineFeed) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Set_LineFeed(%u %u %u) %s result:pwlsize  (%lu) in(%lu)\n", 
            unitNo, blockType, ch, string, pwchInfo->regPtr->pwlsize.bit.pwlsize, lineFeed ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Set_LineFeed(%u %u %u) %s %lu error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, string, lineFeed, ercd ));
    }
}

void im_pro_6_1_print_5(Impro61Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                            kuchar ch, kint32 ercd, kuchar axiResponse )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Get_AXI_Response(%u %u %u) result:pwlsize (%d)\n", 
            unitNo, blockType, ch, axiResponse ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Get_AXI_Response(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_1_print_6(Impro61Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                            kuchar ch, kint32 ercd )
{
    const T_IM_PRO_COMMON_LNR_INFO* lnrInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_lnr_reg_info( unitNo, blockType, ch, &lnrInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Start(%u %u %u) result:lnrtrg  (%d)\n", 
            unitNo, blockType, ch, lnrInfo->regPtr->lnrtrg.bit.lnrtrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Start(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_1_print_7(Impro61Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, kuchar force )
{
    const T_IM_PRO_COMMON_LNR_INFO* lnrInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_lnr_reg_info( unitNo, blockType, ch, &lnrInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Stop(%u %u %u %u) result:lnrtrg    (%d)\n", 
            unitNo, blockType, ch, force, lnrInfo->regPtr->lnrtrg.bit.lnrtrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Stop(%u %u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, force, ercd ));
    }
}                                                    

void im_pro_6_1_print_8(Impro61Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, T_IM_PRO_LNR_CTRL* lnrCtrl )
{
    const T_IM_PRO_COMMON_LNR_INFO* lnrInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_lnr_reg_info( unitNo, blockType, ch, &lnrInfo );
        if(lnrInfo->regPtr->lnrbr.lnrbr1.bit.lnrbr_1 != lnrCtrl->lnrBr[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbr.lnrbr1.bit.lnrbr_1, 
            lnrCtrl->lnrBr[0] ));
        }   
        
        if(lnrInfo->regPtr->lnrbr.lnrbr1.bit.lnrbr_2 != lnrCtrl->lnrBr[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbr.lnrbr1.bit.lnrbr_2, lnrCtrl->lnrBr[1] ));
        }   
        
        if(lnrInfo->regPtr->lnrbr.lnrbr2.bit.lnrbr_3 != lnrCtrl->lnrBr[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbr.lnrbr2.bit.lnrbr_3, lnrCtrl->lnrBr[2] ));
        }   
        
        if(lnrInfo->regPtr->lnrbr.lnrbr2.bit.lnrbr_4 != lnrCtrl->lnrBr[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbr.lnrbr2.bit.lnrbr_4, lnrCtrl->lnrBr[3] ));
        }   
        
        if(lnrInfo->regPtr->lnrbr.lnrbr3.bit.lnrbr_5 != lnrCtrl->lnrBr[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbr.lnrbr3.bit.lnrbr_5, lnrCtrl->lnrBr[4] ));
        }   
        
        if(lnrInfo->regPtr->lnrbr.lnrbr3.bit.lnrbr_6 != lnrCtrl->lnrBr[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbr.lnrbr3.bit.lnrbr_6, lnrCtrl->lnrBr[5] ));
        }   
        
        if(lnrInfo->regPtr->lnrbr.lnrbr4.bit.lnrbr_7 != lnrCtrl->lnrBr[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbr.lnrbr4.bit.lnrbr_7, lnrCtrl->lnrBr[6] ));
        }   
        
        if(lnrInfo->regPtr->lnrincr.lnrincr1.bit.lnrincr_0 != lnrCtrl->lnrIncr[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincr.lnrincr1.bit.lnrincr_0, 
            lnrCtrl->lnrIncr[0] ));
        }   
        
        if(lnrInfo->regPtr->lnrincr.lnrincr1.bit.lnrincr_1 != lnrCtrl->lnrIncr[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincr.lnrincr1.bit.lnrincr_1, 
            lnrCtrl->lnrIncr[1] ));
        }   
        
        if(lnrInfo->regPtr->lnrincr.lnrincr2.bit.lnrincr_2 != lnrCtrl->lnrIncr[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincr.lnrincr2.bit.lnrincr_2, 
            lnrCtrl->lnrIncr[2] ));
        }   
        
        if(lnrInfo->regPtr->lnrincr.lnrincr2.bit.lnrincr_3 != lnrCtrl->lnrIncr[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincr.lnrincr2.bit.lnrincr_3, 
            lnrCtrl->lnrIncr[3] ));
        }   
        
        if(lnrInfo->regPtr->lnrincr.lnrincr3.bit.lnrincr_4 != lnrCtrl->lnrIncr[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincr.lnrincr3.bit.lnrincr_4, 
            lnrCtrl->lnrIncr[4] ));
        }   
        
        if(lnrInfo->regPtr->lnrincr.lnrincr3.bit.lnrincr_5 != lnrCtrl->lnrIncr[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincr.lnrincr3.bit.lnrincr_5, 
            lnrCtrl->lnrIncr[5] ));
        }   
        
        if(lnrInfo->regPtr->lnrincr.lnrincr4.bit.lnrincr_6 != lnrCtrl->lnrIncr[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincr.lnrincr4.bit.lnrincr_6, 
            lnrCtrl->lnrIncr[6] ));
        }   
        
        if(lnrInfo->regPtr->lnrincr.lnrincr4.bit.lnrincr_7 != lnrCtrl->lnrIncr[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincr.lnrincr4.bit.lnrincr_7, 
            lnrCtrl->lnrIncr[7] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsr.lnrofsr1.bit.lnrofsr_0 != lnrCtrl->lnrOfsr[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsr.lnrofsr1.bit.lnrofsr_0, 
            lnrCtrl->lnrOfsr[0] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsr.lnrofsr1.bit.lnrofsr_1 != lnrCtrl->lnrOfsr[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsr.lnrofsr1.bit.lnrofsr_1, 
            lnrCtrl->lnrOfsr[1] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsr.lnrofsr2.bit.lnrofsr_2 != lnrCtrl->lnrOfsr[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsr.lnrofsr2.bit.lnrofsr_2, 
            lnrCtrl->lnrOfsr[2] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsr.lnrofsr2.bit.lnrofsr_3 != lnrCtrl->lnrOfsr[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsr.lnrofsr2.bit.lnrofsr_3, 
            lnrCtrl->lnrOfsr[3] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsr.lnrofsr3.bit.lnrofsr_4 != lnrCtrl->lnrOfsr[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsr.lnrofsr3.bit.lnrofsr_4, 
            lnrCtrl->lnrOfsr[4] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsr.lnrofsr3.bit.lnrofsr_5 != lnrCtrl->lnrOfsr[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsr.lnrofsr3.bit.lnrofsr_5, 
            lnrCtrl->lnrOfsr[5] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsr.lnrofsr4.bit.lnrofsr_6 != lnrCtrl->lnrOfsr[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsr.lnrofsr4.bit.lnrofsr_6, 
            lnrCtrl->lnrOfsr[6] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsr.lnrofsr4.bit.lnrofsr_7 != lnrCtrl->lnrOfsr[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsr.lnrofsr4.bit.lnrofsr_7, 
            lnrCtrl->lnrOfsr[7] ));
        }   
        
        if(lnrInfo->regPtr->lnrbgr.lnrbgr1.bit.lnrbgr_1 != lnrCtrl->lnrBgr[0] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgr.lnrbgr1.bit.lnrbgr_1, 
            lnrCtrl->lnrBgr[0]));
        }   
        
        if(lnrInfo->regPtr->lnrbgr.lnrbgr1.bit.lnrbgr_2 != lnrCtrl->lnrBgr[1] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgr.lnrbgr1.bit.lnrbgr_2, 
            lnrCtrl->lnrBgr[1]));
        }   
        
        if(lnrInfo->regPtr->lnrbgr.lnrbgr2.bit.lnrbgr_3 != lnrCtrl->lnrBgr[2] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgr.lnrbgr2.bit.lnrbgr_3, 
            lnrCtrl->lnrBgr[2]));
        }   
        
        if(lnrInfo->regPtr->lnrbgr.lnrbgr2.bit.lnrbgr_4 != lnrCtrl->lnrBgr[3] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgr.lnrbgr2.bit.lnrbgr_4, 
            lnrCtrl->lnrBgr[3]));
        }   
        
        if(lnrInfo->regPtr->lnrbgr.lnrbgr3.bit.lnrbgr_5 != lnrCtrl->lnrBgr[4] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgr.lnrbgr3.bit.lnrbgr_5, 
            lnrCtrl->lnrBgr[4]));
        }   
        
        if(lnrInfo->regPtr->lnrbgr.lnrbgr3.bit.lnrbgr_6 != lnrCtrl->lnrBgr[5] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgr.lnrbgr3.bit.lnrbgr_6, 
            lnrCtrl->lnrBgr[5]));
        }   
        
        if(lnrInfo->regPtr->lnrbgr.lnrbgr4.bit.lnrbgr_7 != lnrCtrl->lnrBgr[6] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgr.lnrbgr4.bit.lnrbgr_7, 
            lnrCtrl->lnrBgr[6]));
        }   
        
        if(lnrInfo->regPtr->lnrincgr.lnrincgr1.bit.lnrincgr_0 != lnrCtrl->lnrIncgr[0] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgr.lnrincgr1.bit.lnrincgr_0, 
            lnrCtrl->lnrIncgr[0]));
        }   
        
        if(lnrInfo->regPtr->lnrincgr.lnrincgr1.bit.lnrincgr_1 != lnrCtrl->lnrIncgr[1] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgr.lnrincgr1.bit.lnrincgr_1, 
            lnrCtrl->lnrIncgr[1]));
        }   
        
        if(lnrInfo->regPtr->lnrincgr.lnrincgr2.bit.lnrincgr_2 != lnrCtrl->lnrIncgr[2] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgr.lnrincgr2.bit.lnrincgr_2, 
            lnrCtrl->lnrIncgr[2]));
        }   
        
        if(lnrInfo->regPtr->lnrincgr.lnrincgr2.bit.lnrincgr_3 != lnrCtrl->lnrIncgr[3] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgr.lnrincgr2.bit.lnrincgr_3, 
            lnrCtrl->lnrIncgr[3]));
        }   
        
        if(lnrInfo->regPtr->lnrincgr.lnrincgr3.bit.lnrincgr_4 != lnrCtrl->lnrIncgr[4] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgr.lnrincgr3.bit.lnrincgr_4, 
            lnrCtrl->lnrIncgr[4]));
        }   
        
        if(lnrInfo->regPtr->lnrincgr.lnrincgr3.bit.lnrincgr_5 != lnrCtrl->lnrIncgr[5] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgr.lnrincgr3.bit.lnrincgr_5, 
            lnrCtrl->lnrIncgr[5]));
        }   
        
        if(lnrInfo->regPtr->lnrincgr.lnrincgr4.bit.lnrincgr_6 != lnrCtrl->lnrIncgr[6] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgr.lnrincgr4.bit.lnrincgr_6, 
            lnrCtrl->lnrIncgr[6]));
        }   
        
        if(lnrInfo->regPtr->lnrincgr.lnrincgr4.bit.lnrincgr_7 != lnrCtrl->lnrIncgr[7] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgr.lnrincgr4.bit.lnrincgr_7, 
            lnrCtrl->lnrIncgr[7]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgr.lnrofsgr1.bit.lnrofsgr_0 != lnrCtrl->lnrOfsgr[0] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgr.lnrofsgr1.bit.lnrofsgr_0, 
            lnrCtrl->lnrOfsgr[0]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgr.lnrofsgr1.bit.lnrofsgr_1 != lnrCtrl->lnrOfsgr[1] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgr.lnrofsgr1.bit.lnrofsgr_1, 
            lnrCtrl->lnrOfsgr[1]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgr.lnrofsgr2.bit.lnrofsgr_2 != lnrCtrl->lnrOfsgr[2] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgr.lnrofsgr2.bit.lnrofsgr_2, 
            lnrCtrl->lnrOfsgr[2]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgr.lnrofsgr2.bit.lnrofsgr_3 != lnrCtrl->lnrOfsgr[3] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgr.lnrofsgr2.bit.lnrofsgr_3, 
            lnrCtrl->lnrOfsgr[3]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgr.lnrofsgr3.bit.lnrofsgr_4 != lnrCtrl->lnrOfsgr[4] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgr.lnrofsgr3.bit.lnrofsgr_4, 
            lnrCtrl->lnrOfsgr[4]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgr.lnrofsgr3.bit.lnrofsgr_5 != lnrCtrl->lnrOfsgr[5] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgr.lnrofsgr3.bit.lnrofsgr_5, 
            lnrCtrl->lnrOfsgr[5]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgr.lnrofsgr4.bit.lnrofsgr_6 != lnrCtrl->lnrOfsgr[6] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgr.lnrofsgr4.bit.lnrofsgr_6, 
            lnrCtrl->lnrOfsgr[6]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgr.lnrofsgr4.bit.lnrofsgr_7 != lnrCtrl->lnrOfsgr[7] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgr.lnrofsgr4.bit.lnrofsgr_7, 
            lnrCtrl->lnrOfsgr[7]));
        }   
        
        if(lnrInfo->regPtr->lnrbgb.lnrbgb1.bit.lnrbgb_1 != lnrCtrl->lnrBgb[0] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgb.lnrbgb1.bit.lnrbgb_1, 
            lnrCtrl->lnrBgb[0]));
        }   
        
        if(lnrInfo->regPtr->lnrbgb.lnrbgb1.bit.lnrbgb_2 != lnrCtrl->lnrBgb[1] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgb.lnrbgb1.bit.lnrbgb_2, 
            lnrCtrl->lnrBgb[1]));
        }   
        
        if(lnrInfo->regPtr->lnrbgb.lnrbgb2.bit.lnrbgb_3 != lnrCtrl->lnrBgb[2] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgb.lnrbgb2.bit.lnrbgb_3, 
            lnrCtrl->lnrBgb[2]));
        }   
        
        if(lnrInfo->regPtr->lnrbgb.lnrbgb2.bit.lnrbgb_4 != lnrCtrl->lnrBgb[3] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgb.lnrbgb2.bit.lnrbgb_4, 
            lnrCtrl->lnrBgb[3]));
        }   
        
        if(lnrInfo->regPtr->lnrbgb.lnrbgb3.bit.lnrbgb_5 != lnrCtrl->lnrBgb[4] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgb.lnrbgb3.bit.lnrbgb_5, 
            lnrCtrl->lnrBgb[4]));
        }   
        
        if(lnrInfo->regPtr->lnrbgb.lnrbgb3.bit.lnrbgb_6 != lnrCtrl->lnrBgb[5] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgb.lnrbgb3.bit.lnrbgb_6, 
            lnrCtrl->lnrBgb[5]));
        }   
        
        if(lnrInfo->regPtr->lnrbgb.lnrbgb4.bit.lnrbgb_7 != lnrCtrl->lnrBgb[6] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbgb.lnrbgb4.bit.lnrbgb_7, 
            lnrCtrl->lnrBgb[6]));
        }   
        
        if(lnrInfo->regPtr->lnrincgb.lnrincgb1.bit.lnrincgb_0 != lnrCtrl->lnrIncgb[0] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgb.lnrincgb1.bit.lnrincgb_0, 
            lnrCtrl->lnrIncgb[0]));
        }   
        
        if(lnrInfo->regPtr->lnrincgb.lnrincgb1.bit.lnrincgb_1 != lnrCtrl->lnrIncgb[1] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgb.lnrincgb1.bit.lnrincgb_1, 
            lnrCtrl->lnrIncgb[1]));
        }   
        
        if(lnrInfo->regPtr->lnrincgb.lnrincgb2.bit.lnrincgb_2 != lnrCtrl->lnrIncgb[2] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgb.lnrincgb2.bit.lnrincgb_2, 
            lnrCtrl->lnrIncgb[2]));
        }   
        
        if(lnrInfo->regPtr->lnrincgb.lnrincgb2.bit.lnrincgb_3 != lnrCtrl->lnrIncgb[3] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgb.lnrincgb2.bit.lnrincgb_3, 
            lnrCtrl->lnrIncgb[3]));
        }   
        
        if(lnrInfo->regPtr->lnrincgb.lnrincgb3.bit.lnrincgb_4 != lnrCtrl->lnrIncgb[4] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgb.lnrincgb3.bit.lnrincgb_4, 
            lnrCtrl->lnrIncgb[4]));
        }   
        
        if(lnrInfo->regPtr->lnrincgb.lnrincgb3.bit.lnrincgb_5 != lnrCtrl->lnrIncgb[5] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgb.lnrincgb3.bit.lnrincgb_5, 
            lnrCtrl->lnrIncgb[5]));
        }   
        
        if(lnrInfo->regPtr->lnrincgb.lnrincgb4.bit.lnrincgb_6 != lnrCtrl->lnrIncgb[6] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgb.lnrincgb4.bit.lnrincgb_6, 
            lnrCtrl->lnrIncgb[6]));
        }   
        
        if(lnrInfo->regPtr->lnrincgb.lnrincgb4.bit.lnrincgb_7 != lnrCtrl->lnrIncgb[7] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincgb.lnrincgb4.bit.lnrincgb_7, 
            lnrCtrl->lnrIncgb[7]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgb.lnrofsgb1.bit.lnrofsgb_0 != lnrCtrl->lnrOfsgb[0] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgb.lnrofsgb1.bit.lnrofsgb_0, 
            lnrCtrl->lnrOfsgb[0]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgb.lnrofsgb1.bit.lnrofsgb_1 != lnrCtrl->lnrOfsgb[1] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgb.lnrofsgb1.bit.lnrofsgb_1, 
            lnrCtrl->lnrOfsgb[1]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgb.lnrofsgb2.bit.lnrofsgb_2 != lnrCtrl->lnrOfsgb[2] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgb.lnrofsgb2.bit.lnrofsgb_2, 
            lnrCtrl->lnrOfsgb[2]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgb.lnrofsgb2.bit.lnrofsgb_3 != lnrCtrl->lnrOfsgb[3] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgb.lnrofsgb2.bit.lnrofsgb_3, 
            lnrCtrl->lnrOfsgb[3]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgb.lnrofsgb3.bit.lnrofsgb_4 != lnrCtrl->lnrOfsgb[4] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgb.lnrofsgb3.bit.lnrofsgb_4, 
            lnrCtrl->lnrOfsgb[4]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgb.lnrofsgb3.bit.lnrofsgb_5 != lnrCtrl->lnrOfsgb[5] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgb.lnrofsgb3.bit.lnrofsgb_5, 
            lnrCtrl->lnrOfsgb[5]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgb.lnrofsgb4.bit.lnrofsgb_6 != lnrCtrl->lnrOfsgb[6] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgb.lnrofsgb4.bit.lnrofsgb_6, 
            lnrCtrl->lnrOfsgb[6]));
        }   
        
        if(lnrInfo->regPtr->lnrofsgb.lnrofsgb4.bit.lnrofsgb_7 != lnrCtrl->lnrOfsgb[7] ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsgb.lnrofsgb4.bit.lnrofsgb_7, 
            lnrCtrl->lnrOfsgb[7]));
        }   
        
        if(lnrInfo->regPtr->lnrbb.lnrbb1.bit.lnrbb_1 != lnrCtrl->lnrBb[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbb.lnrbb1.bit.lnrbb_1, 
            lnrCtrl->lnrBb[0] ));
        }   
        
        if(lnrInfo->regPtr->lnrbb.lnrbb1.bit.lnrbb_2 != lnrCtrl->lnrBb[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbb.lnrbb1.bit.lnrbb_2, 
            lnrCtrl->lnrBb[1] ));
        }   
        
        if(lnrInfo->regPtr->lnrbb.lnrbb2.bit.lnrbb_3 != lnrCtrl->lnrBb[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbb.lnrbb2.bit.lnrbb_3, 
            lnrCtrl->lnrBb[2] ));
        }   
        
        if(lnrInfo->regPtr->lnrbb.lnrbb2.bit.lnrbb_4 != lnrCtrl->lnrBb[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbb.lnrbb2.bit.lnrbb_4, 
            lnrCtrl->lnrBb[3] ));
        }   
        
        if(lnrInfo->regPtr->lnrbb.lnrbb3.bit.lnrbb_5 != lnrCtrl->lnrBb[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbb.lnrbb3.bit.lnrbb_5, 
            lnrCtrl->lnrBb[4] ));
        }   
        
        if(lnrInfo->regPtr->lnrbb.lnrbb3.bit.lnrbb_6 != lnrCtrl->lnrBb[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbb.lnrbb3.bit.lnrbb_6, 
            lnrCtrl->lnrBb[5] ));
        }   
        
        if(lnrInfo->regPtr->lnrbb.lnrbb4.bit.lnrbb_7 != lnrCtrl->lnrBb[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrbb.lnrbb4.bit.lnrbb_7, 
            lnrCtrl->lnrBb[6] ));
        }   
        
        if(lnrInfo->regPtr->lnrincb.lnrincb1.bit.lnrincb_0 != lnrCtrl->lnrIncb[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincb.lnrincb1.bit.lnrincb_0, 
            lnrCtrl->lnrIncb[0] ));
        }   
        
        if(lnrInfo->regPtr->lnrincb.lnrincb1.bit.lnrincb_1 != lnrCtrl->lnrIncb[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincb.lnrincb1.bit.lnrincb_1, 
            lnrCtrl->lnrIncb[1] ));
        }   
        
        if(lnrInfo->regPtr->lnrincb.lnrincb2.bit.lnrincb_2 != lnrCtrl->lnrIncb[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincb.lnrincb2.bit.lnrincb_2, 
            lnrCtrl->lnrIncb[2] ));
        }   
        
        if(lnrInfo->regPtr->lnrincb.lnrincb2.bit.lnrincb_3 != lnrCtrl->lnrIncb[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincb.lnrincb2.bit.lnrincb_3, 
            lnrCtrl->lnrIncb[3] ));
        }   
        
        if(lnrInfo->regPtr->lnrincb.lnrincb3.bit.lnrincb_4 != lnrCtrl->lnrIncb[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincb.lnrincb3.bit.lnrincb_4, 
            lnrCtrl->lnrIncb[4] ));
        }   
        
        if(lnrInfo->regPtr->lnrincb.lnrincb3.bit.lnrincb_5 != lnrCtrl->lnrIncb[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincb.lnrincb3.bit.lnrincb_5, 
            lnrCtrl->lnrIncb[5] ));
        }   
        
        if(lnrInfo->regPtr->lnrincb.lnrincb4.bit.lnrincb_6 != lnrCtrl->lnrIncb[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincb.lnrincb4.bit.lnrincb_6, 
            lnrCtrl->lnrIncb[6] ));
        }   
        
        if(lnrInfo->regPtr->lnrincb.lnrincb4.bit.lnrincb_7 != lnrCtrl->lnrIncb[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrincb.lnrincb4.bit.lnrincb_7, 
            lnrCtrl->lnrIncb[7] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsb.lnrofsb1.bit.lnrofsb_0 != lnrCtrl->lnrOfsb[0]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsb.lnrofsb1.bit.lnrofsb_0, 
            lnrCtrl->lnrOfsb[0] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsb.lnrofsb1.bit.lnrofsb_1 != lnrCtrl->lnrOfsb[1]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsb.lnrofsb1.bit.lnrofsb_1, 
            lnrCtrl->lnrOfsb[1] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsb.lnrofsb2.bit.lnrofsb_2 != lnrCtrl->lnrOfsb[2]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsb.lnrofsb2.bit.lnrofsb_2, 
            lnrCtrl->lnrOfsb[2] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsb.lnrofsb2.bit.lnrofsb_3 != lnrCtrl->lnrOfsb[3]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsb.lnrofsb2.bit.lnrofsb_3, 
            lnrCtrl->lnrOfsb[3] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsb.lnrofsb3.bit.lnrofsb_4 != lnrCtrl->lnrOfsb[4]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsb.lnrofsb3.bit.lnrofsb_4, 
            lnrCtrl->lnrOfsb[4] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsb.lnrofsb3.bit.lnrofsb_5 != lnrCtrl->lnrOfsb[5]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsb.lnrofsb3.bit.lnrofsb_5, 
            lnrCtrl->lnrOfsb[5] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsb.lnrofsb4.bit.lnrofsb_6 != lnrCtrl->lnrOfsb[6]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsb.lnrofsb4.bit.lnrofsb_6, 
            lnrCtrl->lnrOfsb[6] ));
        }   
        
        if(lnrInfo->regPtr->lnrofsb.lnrofsb4.bit.lnrofsb_7 != lnrCtrl->lnrOfsb[7]) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, lnrInfo->regPtr->lnrofsb.lnrofsb4.bit.lnrofsb_7, 
            lnrCtrl->lnrOfsb[7] ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_LNR_Ctrl(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_1_print_9(Impro61Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
                            kint32 ercd, const T_IM_PRO_RDMA_LNR_ADDR** addr )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbr0     reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbr0));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbr1     reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbr1));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbr2     reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbr2));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbr3     reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbr3));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincr0   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincr0));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincr1   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincr1));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincr2   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincr2));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincr3   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincr3));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsr0   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsr0));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsr1   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsr1));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsr2   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsr2));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsr3   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsr3));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbgr0    reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbgr0 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbgr1    reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbgr1 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbgr2    reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbgr2 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbgr3    reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbgr3 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincgr0  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincgr0 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincgr1  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincgr1 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincgr2  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincgr2 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincgr3  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincgr3 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsgr0  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsgr0 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsgr1  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsgr1 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsgr2  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsgr2 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsgr3  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsgr3 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbgb0    reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbgb0 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbgb1    reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbgb1 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbgb2    reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbgb2 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbgb3    reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbgb3 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincgb0  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincgb0 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincgb1  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincgb1 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincgb2  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincgb2 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincgb3  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincgb3 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsgb0  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsgb0 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsgb1  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsgb1 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsgb2  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsgb2 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsgb3  reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsgb3 ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbb0     reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbb0));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbb1     reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbb1));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbb2     reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbb2));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrbb3     reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrbb3));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincb0   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincb0));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincb1   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincb1));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincb2   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincb2));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrincb3   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrincb3));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsb0   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsb0));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsb1   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsb1));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsb2   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsb2));
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) lnrofsb3   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->lnrofsb3));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_LNR_Cntl(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}
#endif

Impro61Print* impro_6_1_print_new(void)
{
	Impro61Print* self = k_object_new_with_private(IMPRO_TYPE_6_1_PRINT, sizeof(Impro61PrintPrivate));

	return self;
}

Impro61Print* impro_6_1_print_get(void)
{
	static Impro61Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_6_1_PRINT, sizeof(Impro61PrintPrivate));
	}

	return self;
}
