/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro60Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro60print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro60Print, impro_6_0_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_6_0_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro60PrintPrivate, IMPRO_TYPE_6_0_PRINT))


struct _Impro60PrintPrivate
{


};


static void impro_6_0_print_constructor(Impro60Print *self)
{
	Impro60PrintPrivate *priv = IMPRO_6_0_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_6_0_print_destructor(Impro60Print *self)
{
	Impro60PrintPrivate *priv = IMPRO_6_0_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_6_0_print_1(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd )
{
    const T_IM_PRO_COMMON_P2M_INFO* p2mInfo = 0;

    DriverCommon_DDIM_PRINT(( "im_pro_6_0_print_1(Impro60Print *self,%u %u %u) start\n", 
            unitNo, blockType, ch ));
    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_p2m_reg_info( unitNo, blockType, ch, &p2mInfo );
        DriverCommon_DDIM_PRINT(( "im_pro_comm_get_p2m_reg_info(%u %u %u)\n", unitNo, blockType, ch ));
        DriverCommon_DDIM_PRINT(( "im_pro_6_0_print_1(Impro60Print *self,%u %u %u) regPtr  =0x%08lx\n", 
            unitNo, blockType, ch, (kulong)(*p2mInfo).regPtr ));
        DriverCommon_DDIM_PRINT(( "im_pro_6_0_print_1(Impro60Print *self,%u %u %u) kntblPtr=0x%08lx\n", 
            unitNo, blockType, ch, (kulong)(*p2mInfo).kntblPtr ));
        DriverCommon_DDIM_PRINT(( "im_pro_6_0_print_1(Impro60Print *self,%u %u %u) status   =0x%08lx\n", 
            unitNo, blockType, ch, (kulong)(*p2mInfo).status ));
        DriverCommon_DDIM_PRINT(( "im_pro_6_0_print_1(Impro60Print *self,%u %u %u) (kulong)&ioPro.sen.P2M[0] =0x%08lx\n", 
            unitNo, blockType, ch, (kulong)&ioPro.sen.P2M[0] ));
        if( D_IM_PRO_TRG_STATUS_RUNNING != p2mInfo->regPtr->p2mtrg.bit.p2mtrg ) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_start(%u %u %u) result:p2mtrg (%u)\n", 
            unitNo, blockType, ch, p2mInfo->regPtr->p2mtrg.bit.p2mtrg ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_start(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
    DriverCommon_DDIM_PRINT(( "im_pro_6_0_print_1(Impro60Print *self,%u %u %u) end\n", 
            unitNo, blockType, ch ));
}

void im_pro_6_0_print_2(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, kuchar force )
{
    const T_IM_PRO_COMMON_P2M_INFO* p2mInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_p2m_reg_info( unitNo, blockType, ch, &p2mInfo );
        if( D_IM_PRO_TRG_STATUS_STOPPED != p2mInfo->regPtr->p2mtrg.bit.p2mtrg ) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_stop(%u %u %u %u) result:p2mtrg   (%u)\n", 
            unitNo, blockType, ch, force, p2mInfo->regPtr->p2mtrg.bit.p2mtrg ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_stop(%u %u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, force, ercd ));
    }
}  

void im_pro_6_0_print_3(Impro60Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, T_IM_PRO_P2M_CTRL* p2mCtrl )
{
    const T_IM_PRO_COMMON_P2M_INFO* p2mInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_p2m_reg_info( unitNo, blockType, ch, &p2mInfo );
        if( p2mCtrl->kneeEnable != p2mInfo->regPtr->p2mctl.bit.pknemd) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:pknemd    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->p2mctl.bit.pknemd, p2mCtrl->kneeEnable ));
        }   
        
        if( p2mCtrl->lpfMode != p2mInfo->regPtr->p2mctl.bit.plpf) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:plpf      (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->p2mctl.bit.plpf, p2mCtrl->lpfMode));
        }   
        
        if( p2mCtrl->recMode != p2mInfo->regPtr->p2mctl.bit.p2mtyp) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:p2mtyp    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->p2mctl.bit.p2mtyp, p2mCtrl->recMode));
        }   
        
        if( p2mCtrl->shiftValue != p2mInfo->regPtr->p2mofs.bit.p2mofs) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:p2mofs    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->p2mofs.bit.p2mofs, p2mCtrl->shiftValue ));
        }   
        
        if( p2mCtrl->shiftBit != p2mInfo->regPtr->pbsft.bit.pbsft) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:pbsft     (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->pbsft.bit.pbsft, p2mCtrl->shiftBit ));
        }   
        
        if( p2mCtrl->clipValue != p2mInfo->regPtr->pclph.bit.pclph) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:pclph     (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->pclph.bit.pclph, p2mCtrl->clipValue));
        }   
        
        if( p2mCtrl->startY != p2mInfo->regPtr->ptrmv.bit.ptrmv) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:ptrmv     (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->ptrmv.bit.ptrmv, p2mCtrl->startY ));
        }   
        
        if( p2mCtrl->startX != p2mInfo->regPtr->ptrmh.bit.ptrmh) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:ptrmh     (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->ptrmh.bit.ptrmh, p2mCtrl->startX ));
        }   
        
        if( p2mCtrl->height != p2mInfo->regPtr->ptrmvw.bit.ptrmvw) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:ptrmvw    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->ptrmvw.bit.ptrmvw, p2mCtrl->height));
        }   
        
        if( p2mCtrl->width != p2mInfo->regPtr->ptrmhw.bit.ptrmhw) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:ptrmhw    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->ptrmhw.bit.ptrmhw, p2mCtrl->width ));
        }   
        
        if( p2mCtrl->verticalThin != p2mInfo->regPtr->ptrmxvcyc.bit.ptrmxvcyc) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:ptrmxvcyc (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->ptrmxvcyc.bit.ptrmxvcyc, p2mCtrl->verticalThin ));
        }   
        
        if( p2mCtrl->horizonThin != p2mInfo->regPtr->ptrmxhcyc.bit.ptrmxhcyc) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:ptrmxhcyc (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->ptrmxhcyc.bit.ptrmxhcyc, p2mCtrl->horizonThin));
        }   
        
        if( p2mCtrl->sampleLine != p2mInfo->regPtr->ptrmxven.bit.ptrmxven) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:ptrmxven  (%lld) in(%lld)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->ptrmxven.bit.ptrmxven, p2mCtrl->sampleLine ));
        }   
        
        if( p2mCtrl->sampleWidth != p2mInfo->regPtr->ptrmxhen.bit.ptrmxhen) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:ptrmxhen  (%lld) in(%lld)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->ptrmxhen.bit.ptrmxhen, p2mCtrl->sampleWidth));
        }   
        
        if( p2mCtrl->enableMirror != p2mInfo->regPtr->p2mmir.bit.p2mmir) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:p2mmir    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->p2mmir.bit.p2mmir, p2mCtrl->enableMirror ));
        }   
        
        if( p2mCtrl->inputMode != p2mInfo->regPtr->p2m2pmd.bit.p2m2pmd) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) %s result:p2m2pmd   (%d) in(%d)\n", 
            unitNo, blockType, ch, string, p2mInfo->regPtr->p2m2pmd.bit.p2m2pmd, p2mCtrl->inputMode));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_ctrl(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_0_print_4(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, kuchar paenTrg )
{
    const T_IM_PRO_COMMON_P2M_INFO* p2mInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_p2m_reg_info( unitNo, blockType, ch, &p2mInfo );
        if( paenTrg != p2mInfo->regPtr->p2mpaen.bit.paen ) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_set_paen(%u %u %u %u) result:paen     (%u)\n", 
            unitNo, blockType, ch, paenTrg, p2mInfo->regPtr->p2mpaen.bit.paen ));
        }   
        
        if( D_IM_PRO_TRG_STATUS_STOPPED != p2mInfo->regPtr->p2mtrg.bit.p2mtrg) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_set_paen(%u %u %u %u) result:p2mtrg   (%u)\n", 
            unitNo, blockType, ch, paenTrg, p2mInfo->regPtr->p2mtrg.bit.p2mtrg ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_set_paen(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_0_print_5(Impro60Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, kint32 cmpErcd )
{
    if( ( ercd == DdimUserCustom_E_OK ) && ( cmpErcd != 0 ) ) {
        DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_set_table(%u %u %u) API result(0x%x) memcmp result(0x%x)\n", 
            unitNo, blockType, ch, ercd, cmpErcd ));
    } else {
        DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_p2m_set_table(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_0_print_6(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
                        kint32 ercd, const T_IM_PRO_RDMA_P2M_KNEE_TBL_ADDR** addr )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_P2M_Knee_Tbl(%u %u %u) p2mkntbl   reg_addr (0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)(*addr)->p2mkntbl));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_P2M_Knee_Tbl(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_0_print_7(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd )
{
    const T_IM_PRO_COMMON_PWCH_INFO* pwchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pwch_reg_info( unitNo, blockType, ch, &pwchInfo );
        if( D_IM_PRO_TRG_STATUS_RUNNING != pwchInfo->regPtr->pwchtrg.bit.pwchtrg ) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_pwch_start(%u %u %u) result:pwchtrg    (%u)\n", 
            unitNo, blockType, ch, pwchInfo->regPtr->pwchtrg.bit.pwchtrg ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_pwch_start(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}                                                    

void im_pro_6_0_print_8(Impro60Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
                        kint32 ercd, kuchar force )
{
    const T_IM_PRO_COMMON_PWCH_INFO* pwchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pwch_reg_info( unitNo, blockType, ch, &pwchInfo );
        if( D_IM_PRO_TRG_STATUS_STOPPED != pwchInfo->regPtr->pwchtrg.bit.pwchtrg ) {
            DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_pwch_stop(%u %u %u %u) result:pwchtrg  (%u)\n", 
            unitNo, blockType, ch, force, pwchInfo->regPtr->pwchtrg.bit.pwchtrg ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "im_pro_pommon_list_pwch_stop(%u %u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, force, ercd ));
    }
}                                                    

void im_pro_6_0_print_9(Impro60Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, T_IM_PRO_PWCH_CTRL* pwchCtrl )
{
    const T_IM_PRO_COMMON_PWCH_INFO* pwchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pwch_reg_info( unitNo, blockType, ch, &pwchInfo );
        if(pwchInfo->regPtr->PWS.bit.PWS != pwchCtrl->transTo ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Ctrl(%u %u %u) %s result:PWS      (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pwchInfo->regPtr->PWS.bit.PWS, pwchCtrl->transTo ));
        }   
        
        if(pwchInfo->regPtr->pwchctl.bit.pwlv != pwchCtrl->reqThreshold) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Ctrl(%u %u %u) %s result:pwlv     (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pwchInfo->regPtr->pwchctl.bit.pwlv, pwchCtrl->reqThreshold));
        }   
        
        if(pwchInfo->regPtr->pwchctl.bit.pwmw != pwchCtrl->writeMask ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Ctrl(%u %u %u) %s result:pwmw     (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pwchInfo->regPtr->pwchctl.bit.pwmw, pwchCtrl->writeMask ));
        }   
        
        if(pwchInfo->regPtr->pwvfm.bit.pwvfm != pwchCtrl->burstAlignSize) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Ctrl(%u %u %u) %s result:PWDW     (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pwchInfo->regPtr->PWDW.bit.PWDW, pwchCtrl->burstAlignSize));
        }   
        
        if(pwchInfo->regPtr->pwvfm.bit.pwvfm != pwchCtrl->outputFormat) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Ctrl(%u %u %u) %s result:pwvfm    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pwchInfo->regPtr->pwvfm.bit.pwvfm, pwchCtrl->outputFormat));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PWch_Ctrl(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}
#endif

Impro60Print* impro_6_0_print_new(void)
{
	Impro60Print* self = k_object_new_with_private(IMPRO_TYPE_6_0_PRINT, sizeof(Impro60PrintPrivate));

	return self;
}

Impro60Print* impro_6_0_print_get(void)
{
	static Impro60Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_6_0_PRINT, sizeof(Impro60PrintPrivate));
	}

	return self;
}
