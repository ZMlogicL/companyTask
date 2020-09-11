/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro62Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro62print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro62Print, impro_6_2_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_6_2_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro62PrintPrivate, IMPRO_TYPE_6_2_PRINT))


struct _Impro62PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_6_2_print_constructor(Impro62Print *self)
{
	Impro62PrintPrivate *priv = IMPRO_6_2_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_6_2_print_destructor(Impro62Print *self)
{
	Impro62PrintPrivate *priv = IMPRO_6_2_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_6_2_print_0(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd )
{
    const T_IM_PRO_COMMON_PGAIN_INFO* pgainInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pgain_reg_info( unitNo, blockType, ch, &pgainInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Start(%u %u %u) result:pgaintrg  (%d)\n", 
            unitNo, blockType, ch, pgainInfo->regPtr->pgaintrg.bit.pgaintrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Start(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_2_print_1(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
                            kint32 ercd, kuchar force )
{
    const T_IM_PRO_COMMON_PGAIN_INFO* pgainInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pgain_reg_info( unitNo, blockType, ch, &pgainInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Stop(%u %u %u %u) result:pgaintrg    (%d)\n", 
            unitNo, blockType, ch, force, pgainInfo->regPtr->pgaintrg.bit.pgaintrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Stop(%u %u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, force, ercd ));
    }
}                                                    

void im_pro_6_2_print_2(Impro62Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
                            kint32 ercd, T_IM_PRO_PGAIN_CTRL* pgainCtrl )
{
    const T_IM_PRO_COMMON_PGAIN_INFO* pgainInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pgain_reg_info( unitNo, blockType, ch, &pgainInfo );
        if(pgainInfo->regPtr->pgainr.bit.pgainr != pgainCtrl->R ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Ctrl(%u %u %u) %s result:pgainr   (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pgainInfo->regPtr->pgainr.bit.pgainr, pgainCtrl->R ));
        }   
        
        if(pgainInfo->regPtr->pgaingr.bit.pgaingr != pgainCtrl->Gr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Ctrl(%u %u %u) %s result:pgaingr  (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pgainInfo->regPtr->pgaingr.bit.pgaingr, pgainCtrl->Gr));
        }   
        
        if(pgainInfo->regPtr->pgaingb.bit.pgaingb != pgainCtrl->Gb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Ctrl(%u %u %u) %s result:pgaingb  (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pgainInfo->regPtr->pgaingb.bit.pgaingb, pgainCtrl->Gb));
        }   
        
        if(pgainInfo->regPtr->pgainb.bit.pgainb != pgainCtrl->B ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Ctrl(%u %u %u) %s result:pgainb   (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pgainInfo->regPtr->pgainb.bit.pgainb, pgainCtrl->B ));
        }   
        
        if(pgainInfo->regPtr->pofsr.bit.pofsr != pgainCtrl->ROffset) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Ctrl(%u %u %u) %s result:pofsr    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pgainInfo->regPtr->pofsr.bit.pofsr, pgainCtrl->ROffset));
        }   
        
        if(pgainInfo->regPtr->pofsgr.bit.pofsgr != pgainCtrl->GrOffset ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Ctrl(%u %u %u) %s result:pofsgr   (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pgainInfo->regPtr->pofsgr.bit.pofsgr, pgainCtrl->GrOffset ));
        }   
        
        if(pgainInfo->regPtr->pofsgb.bit.pofsgb != pgainCtrl->GbOffset ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Ctrl(%u %u %u) %s result:pofsgb   (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pgainInfo->regPtr->pofsgb.bit.pofsgb, pgainCtrl->GbOffset ));
        }   
        
        if(pgainInfo->regPtr->pofsb.bit.pofsb != pgainCtrl->BOffset) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Ctrl(%u %u %u) %s result:pofsb    (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pgainInfo->regPtr->pofsb.bit.pofsb, pgainCtrl->BOffset));
        }   
        
        if(pgainInfo->regPtr->pgaindp.bit.pgaindp != pgainCtrl->decimalPointPosition) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Ctrl(%u %u %u) %s result:pgaindp  (%d) in(%d)\n", 
            unitNo, blockType, ch, string, pgainInfo->regPtr->pgaindp.bit.pgaindp, pgainCtrl->decimalPointPosition));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Ctrl(%u %u %u) error(not exist) ercd=0x%x\n", unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_2_print_3(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
                        kint32 ercd, const T_IM_PRO_RDMA_PGAIN_ADDR** addr )
{
    const T_IM_PRO_COMMON_PGAIN_INFO* pgainInfo;
    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pgain_reg_info( unitNo, blockType, ch, &pgainInfo );
        if((kulong)&pgainInfo->regPtr->pgainr.word != (*addr)->pgainr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_PGAIN_Cntl(%u %u %u) pgainr   reg_addr (0x%08lx) rdma_addr(0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)&pgainInfo->regPtr->pgainr.word, (kulong)(*addr)->pgainr ));
        }   
        
        if((kulong)&pgainInfo->regPtr->pgaingr.word != (*addr)->pgaingr ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_PGAIN_Cntl(%u %u %u) pgaingr  reg_addr (0x%08lx) rdma_addr(0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)&pgainInfo->regPtr->pgaingr.word, (kulong)(*addr)->pgaingr));
        }   
        
        if((kulong)&pgainInfo->regPtr->pgaingb.word != (*addr)->pgaingb ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_PGAIN_Cntl(%u %u %u) pgaingb  reg_addr (0x%08lx) rdma_addr(0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)&pgainInfo->regPtr->pgaingb.word, (kulong)(*addr)->pgaingb));
        }   
        
        if((kulong)&pgainInfo->regPtr->pgainb.word != (*addr)->pgainb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_PGAIN_Cntl(%u %u %u) pgainb   reg_addr (0x%08lx) rdma_addr(0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)&pgainInfo->regPtr->pgainb.word, (kulong)(*addr)->pgainb ));
        }   
        
        if((kulong)&pgainInfo->regPtr->pofsr.word != (*addr)->pofsr ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_PGAIN_Cntl(%u %u %u) pofsr    reg_addr (0x%08lx) rdma_addr(0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)&pgainInfo->regPtr->pofsr.word, (kulong)(*addr)->pofsr));
        }   
        
        if((kulong)&pgainInfo->regPtr->pofsgr.word != (*addr)->pofsgr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_PGAIN_Cntl(%u %u %u) pofsgr   reg_addr (0x%08lx) rdma_addr(0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)&pgainInfo->regPtr->pofsgr.word, (kulong)(*addr)->pofsgr ));
        }   
        
        if((kulong)&pgainInfo->regPtr->pofsgb.word != (*addr)->pofsgb) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_PGAIN_Cntl(%u %u %u) pofsgb   reg_addr (0x%08lx) rdma_addr(0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)&pgainInfo->regPtr->pofsgb.word, (kulong)(*addr)->pofsgb ));
        }   
        
        if((kulong)&pgainInfo->regPtr->pofsb.word != (*addr)->pofsb ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_PGAIN_Cntl(%u %u %u) pofsb    reg_addr (0x%08lx) rdma_addr(0x%08lx)\n", 
            unitNo, blockType, ch, (kulong)&pgainInfo->regPtr->pofsb.word, (kulong)(*addr)->pofsb));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_PGAIN_Cntl(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_2_print_4(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar     ch, kint32 ercd )
{
    const T_IM_PRO_COMMON_PZSFT_INFO* pzsftInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pzsft_reg_info( unitNo, ch, &pzsftInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Start(%u %u) result:pzsfttrg (%u)\n", 
            unitNo, ch, pzsftInfo->regPtr->pzsfttrg.bit.pzsfttrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PGAIN_Start(%u %u) error(not exist) ercd=0x%x\n", 
            unitNo, ch, ercd ));
    }
}

void im_pro_6_2_print_5(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar     ch, kint32 ercd, kuchar force )
{
    const T_IM_PRO_COMMON_PZSFT_INFO* pzsftInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pzsft_reg_info( unitNo, ch, &pzsftInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PZSFT_Stop(%u %u %u) result:pzsfttrg   (%u)\n", 
            unitNo, ch, force, pzsftInfo->regPtr->pzsfttrg.bit.pzsfttrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PZSFT_Stop(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, ch, force, ercd ));
    }
}

void im_pro_6_2_print_6(Impro62Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, 
                        kint32 ercd, T_IM_PRO_PZSFT_CTRL* pzsftCtrl )
{
    const T_IM_PRO_COMMON_PZSFT_INFO* pzsftInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pzsft_reg_info( unitNo, ch, &pzsftInfo );
        if(pzsftInfo->regPtr->pzofst.bit.pzofst != pzsftCtrl->offsetShift) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PZSFT_Ctrl(%u %u) %s result:pzofst  (%d) in(%d)\n", 
            unitNo, ch, string, pzsftInfo->regPtr->pzofst.bit.pzofst, pzsftCtrl->offsetShift ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PZSFT_Ctrl(%u %u) error(not exist) ercd=0x%x\n", 
            unitNo, ch, ercd ));
    }
}

void im_pro_6_2_print_7(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, kint32 ercd, 
                        const T_IM_PRO_RDMA_PZSFT_ADDR** addr )
{
    const T_IM_PRO_COMMON_PZSFT_INFO* pzsftInfo;
    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pzsft_reg_info( unitNo, ch, &pzsftInfo );
        if((kulong)&pzsftInfo->regPtr->pzofst.word != (*addr)->pzofst) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_PZSFT_Cntl(%u %u) pzofst   reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
            unitNo, ch, (kulong)&pzsftInfo->regPtr->pzofst.word, (kulong)(*addr)->pzofst ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_PZSFT_Cntl(%u %u) error(not exist) ercd=0x%x\n", 
            unitNo, ch, ercd ));
    }
}

void im_pro_6_2_print_8(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kint32 ercd )
{
    const T_IM_PRO_COMMON_PG_INFO* pgInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pg_reg_info( unitNo, blockType, &pgInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PG_Start(%u %u) result:pgtrg   (%u)\n", 
            unitNo, blockType, pgInfo->regPtr->pgtrg.bit.pgtrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PG_Start(%u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ercd ));
    }
}

void im_pro_6_2_print_9(Impro62Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kint32 ercd )
{
    const T_IM_PRO_COMMON_PG_INFO* pgInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pg_reg_info( unitNo, blockType, &pgInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_PG_Stop(%u %u) result:pgtrg    (%u)\n", 
            unitNo, blockType, pgInfo->regPtr->pgtrg.bit.pgtrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PG_Stop(%u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ercd ));
    }
}                                                    
#endif

Impro62Print* impro_6_2_print_new(void)
{
	Impro62Print* self = k_object_new_with_private(IMPRO_TYPE_6_2_PRINT, sizeof(Impro62PrintPrivate));

	return self;
}

Impro62Print* impro_6_2_print_get(void)
{
	static Impro62Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_6_2_PRINT, sizeof(Impro62PrintPrivate));
	}

	return self;
}
