/*
*
*@Copyright(C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro64Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro64print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro64Print, impro_6_4_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_6_4_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE((o), Impro64PrintPrivate, IMPRO_TYPE_6_4_PRINT))


struct _Impro64PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_6_4_print_constructor(Impro64Print *self)
{
	Impro64PrintPrivate *priv = IMPRO_6_4_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_6_4_print_destructor(Impro64Print *self)
{
	Impro64PrintPrivate *priv = IMPRO_6_4_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_6_4_print_0(Impro64Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
                        kint32 ercd, const T_IM_PRO_RDMA_M2P_DEKNEE_TBL_ADDR** addr )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_M2P_Knee_Tbl(%u %u %u) M2PKNTBL   reg_addr(0x%08lx)\n", 
            unitNo, blockType, ch,(kulong)(*addr)->m2pdkntbl));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_M2P_Knee_Tbl(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_4_print_1(Impro64Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd )
{
    const T_IM_PRO_COMMON_PRCH_INFO* prchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_prch_reg_info( unitNo, blockType, ch, &prchInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Start(%u %u %u) result:prchtrg(%u)\n", 
            unitNo, blockType, ch, prchInfo->regPtr->prchtrg.bit.prchtrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Start(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}                                                    

void im_pro_6_4_print_2(Impro64Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, kuchar force )
{
    const T_IM_PRO_COMMON_PRCH_INFO* prchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_prch_reg_info( unitNo, blockType, ch, &prchInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Stop(%u %u %u %u) result:prchtrg(%u)\n", 
            unitNo, blockType, ch, force, prchInfo->regPtr->prchtrg.bit.prchtrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Stop(%u %u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, force, ercd ));
    }
}

void im_pro_6_4_print_3(Impro64Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType,
                         kuchar ch, kint32 ercd, T_IM_PRO_PRCH_CTRL* prchCtrl )
{
    const T_IM_PRO_COMMON_PRCH_INFO* prchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_prch_reg_info( unitNo, blockType, ch, &prchInfo );
        if(prchInfo->regPtr->prchctl.bit.prbmd != prchCtrl->transMode ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Ctrl(%u %u %u) %s result:prbmd(%d) in(%d)\n", 
            unitNo, blockType, ch, string, prchInfo->regPtr->prchctl.bit.prbmd, prchCtrl->transMode));
        }   
        
        if(prchInfo->regPtr->prchctl.bit.PRLV != prchCtrl->reqThreshold) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Ctrl(%u %u %u) %s result:PRLV(%d) in(%d)\n", 
            unitNo, blockType, ch, string, prchInfo->regPtr->prchctl.bit.PRLV, prchCtrl->reqThreshold ));
        }   
        
        if(prchInfo->regPtr->prchrs.bit.prs != prchCtrl->transTo ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Ctrl(%u %u %u) %s result:prs(%d) in(%d)\n", 
            unitNo, blockType, ch, string, prchInfo->regPtr->prchrs.bit.prs, prchCtrl->transTo));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Ctrl(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_4_print_4(Impro64Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, T_IM_PRO_AXI_CTRL* axiCtrl )
{
    const T_IM_PRO_COMMON_PRCH_INFO* prchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_prch_reg_info( unitNo, blockType, ch, &prchInfo );
        if(prchInfo->regPtr->praxctl.bit.arcache != axiCtrl->cacheType) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Ctrl_Axi(%u %u %u) %s result:arcache(%u) in(%u)\n", 
            unitNo, blockType, ch, string, prchInfo->regPtr->praxctl.bit.arcache, axiCtrl->cacheType ));
        }   
        
        if(prchInfo->regPtr->praxctl.bit.arprot != axiCtrl->protectType) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Ctrl_Axi(%u %u %u) %s result:arprot(%u) in(%u)\n", 
            unitNo, blockType, ch, string, prchInfo->regPtr->praxctl.bit.arprot, axiCtrl->protectType ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Ctrl_Axi(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_4_print_5(Impro64Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, kulong prAddr )
{
    const T_IM_PRO_COMMON_PRCH_INFO* prchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_prch_reg_info( unitNo, blockType, ch, &prchInfo );
        if( prchInfo->regPtr->prsa.bit.prsa != prAddr ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Set_Addr(%u %u %u) %s result:prsa(%lu) in(%lu)\n", 
            unitNo, blockType, ch, string,(kulong)prchInfo->regPtr->prsa.bit.prsa, prAddr ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Set_Addr(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_4_print_6(Impro64Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, T_IM_PRO_PRCH_AREA* prArea )
{
    const T_IM_PRO_COMMON_PRCH_INFO* prchInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_prch_reg_info( unitNo, blockType, ch, &prchInfo );
        if(prchInfo->regPtr->prlsize.bit.prlsize != prArea->globalWidth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Set_Area(%u %u %u) %s result:prlsize(%lu) in(%lu)\n", 
            unitNo, blockType, ch, string, prchInfo->regPtr->prlsize.bit.prlsize, prArea->globalWidth));
        }   
        
        if(prchInfo->regPtr->prvsize.bit.prvsize != prArea->height) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Set_Area(%u %u %u) %s result:prvsize(%u) in(%u)\n", 
            unitNo, blockType, ch, string, prchInfo->regPtr->prvsize.bit.prvsize, prArea->height));
        }   
        
        if(prchInfo->regPtr->prhsize.bit.prhsize != prArea->width ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Set_Area(%u %u %u) %s result:prhsize(%u) in(%lu)\n", 
            unitNo, blockType, ch, string, prchInfo->regPtr->prhsize.bit.prhsize, prArea->width ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Set_Area(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_4_print_7(Impro64Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, kuchar axiResponse )
{
    const T_IM_PRO_COMMON_PRCH_INFO* prchInfo;
    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_prch_reg_info( unitNo, blockType, ch, &prchInfo );
        if(prchInfo->regPtr[ch].prchbresp.bit.prchbresp != axiResponse) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Get_AXI_Response(%u %u %u) result:prchbresp(%u)\n", 
            unitNo, blockType, ch, axiResponse ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PRch_Get_AXI_Response(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}
#endif

Impro64Print* impro_6_4_print_new(void)
{
	Impro64Print* self = k_object_new_with_private(IMPRO_TYPE_6_4_PRINT, sizeof(Impro64PrintPrivate));

	return self;
}

Impro64Print* impro_6_4_print_get(void)
{
	static Impro64Print* self = NULL;

	if(!self) {
		self = k_object_new_with_private(IMPRO_TYPE_6_4_PRINT, sizeof(Impro64PrintPrivate));
	}

	return self;
}
