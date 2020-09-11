/*
*
*@Copyright(C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro63Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro63print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro63Print, impro_6_3_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_6_3_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE((o), Impro63PrintPrivate, IMPRO_TYPE_6_3_PRINT))


struct _Impro63PrintPrivate
{

};


static void impro_6_3_print_constructor(Impro63Print *self)
{
	Impro63PrintPrivate *priv = IMPRO_6_3_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_6_3_print_destructor(Impro63Print *self)
{
	Impro63PrintPrivate *priv = IMPRO_6_3_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_6_3_print_0(Impro63Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                            kint32 ercd, T_IM_PRO_PG_CTRL* pgCtrl )
{
    const T_IM_PRO_COMMON_PG_INFO* pgInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_pg_reg_info( unitNo, blockType, &pgInfo );
        if(pgInfo->regPtr->pgctl.bit.pgmd != pgCtrl->mode ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PG_Ctrl(%u %u) %s result:pgmd(%d) in(%d)\n", 
            unitNo, blockType, string, pgInfo->regPtr->pgctl.bit.pgmd, pgCtrl->mode));
        }   
        
        if(pgInfo->regPtr->pgvw.bit.pgvw != pgCtrl->inputImgLines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PG_Ctrl(%u %u) %s result:pgvw(%d) in(%d)\n", 
            unitNo, blockType, string, pgInfo->regPtr->pgvw.bit.pgvw, pgCtrl->inputImgLines ));
        }   
        
        if(pgInfo->regPtr->pghw.bit.pghw != pgCtrl->inputImgWidth) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PG_Ctrl(%u %u) %s result:pghw(%d) in(%d)\n", 
            unitNo, blockType, string, pgInfo->regPtr->pghw.bit.pghw, pgCtrl->inputImgWidth ));
        }   
        
        if(pgInfo->regPtr->pgvblnk.bit.pgvblnk != pgCtrl->verticalBlanking) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PG_Ctrl(%u %u) %s result:pgvblnk(%d) in(%d)\n", 
            unitNo, blockType, string, pgInfo->regPtr->pgvblnk.bit.pgvblnk, pgCtrl->verticalBlanking ));
        }   
        
        if(pgInfo->regPtr->pghblnk.bit.pghblnk != pgCtrl->horizontalBlanking) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PG_Ctrl(%u %u) %s result:pghblnk(%d) in(%d)\n", 
            unitNo, blockType, string, pgInfo->regPtr->pghblnk.bit.pghblnk, pgCtrl->horizontalBlanking ));
        }   
        
        if(pgInfo->regPtr->pgvdhdblnk.bit.pgvhblnk != pgCtrl->startBlanking ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_PG_Ctrl(%u %u) %s result:pgvhblnk(%d) in(%d)\n", 
            unitNo, blockType, string, pgInfo->regPtr->pgvdhdblnk.bit.pgvhblnk, pgCtrl->startBlanking));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PG_Ctrl(%u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ercd ));
    }
}

void im_pro_6_3_print_1(Impro63Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd )
{
    const T_IM_PRO_COMMON_MONI_INFO* moniInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_moni_reg_info( unitNo, blockType, ch, &moniInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Start(%u %u %u) result:monitrg(%u)\n", 
            unitNo, blockType, ch, moniInfo->regPtr->monitrg.bit.monitrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Start(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}                                                    

void im_pro_6_3_print_2(Impro63Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
                            kint32 ercd, kuchar force )
{
    const T_IM_PRO_COMMON_MONI_INFO* moniInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_moni_reg_info( unitNo, blockType, ch, &moniInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Stop(%u %u %u %u) result:monitrg(%u)\n", 
            unitNo, blockType, ch, force, moniInfo->regPtr->monitrg.bit.monitrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Stop(%u %u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, force, ercd ));
    }
}                                                    

void im_pro_6_3_print_3(Impro63Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                            kuchar ch, kint32 ercd, T_IM_PRO_MONI_CTRL* moniCtrl )
{
    const T_IM_PRO_COMMON_MONI_INFO* moniInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_moni_reg_info( unitNo, blockType, ch, &moniInfo );
        if(moniInfo->regPtr->monictl.bit.monimd != moniCtrl->monitorMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Ctrl(%u %u %u) %s result:monimd(%u) in(%u)\n", 
            unitNo, blockType, ch, string, moniInfo->regPtr->monictl.bit.monimd, moniCtrl->monitorMode ));
        }   
        
        if(moniInfo->regPtr->monihdexp.bit.monihdexp != moniCtrl->hdCntExpectVal ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Ctrl(%u %u %u) %s result:monihdexp(%u) in(%u)\n", 
            unitNo, blockType, ch, string, moniInfo->regPtr->monihdexp.bit.monihdexp, 
            moniCtrl->hdCntExpectVal));
        }   
        
        if(moniInfo->regPtr->moniepfexp.bit.moniepfexp != moniCtrl->validPixelExpectCntIn1frame) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Ctrl(%u %u %u) %s result:moniepfexp(%lu) in(%lu)\n", 
            unitNo, blockType, ch, string, moniInfo->regPtr->moniepfexp.bit.moniepfexp, 
            moniCtrl->validPixelExpectCntIn1frame ));
        }   
        
        if(moniInfo->regPtr->monibllminexp.bit.monibllminexp != moniCtrl->lowerLimitExceptHBlank) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Ctrl(%u %u %u) %s result:monibllminexp(%lu) in(%lu)\n", 
            unitNo, blockType, ch, string, moniInfo->regPtr->monibllminexp.bit.monibllminexp, 
            moniCtrl->lowerLimitExceptHBlank ));
        }   
        
        if(moniInfo->regPtr->monibllmaxexp.bit.monibllmaxexp != moniCtrl->upperLimitExceptHBlank) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Ctrl(%u %u %u) %s result:monibllmaxexp(%lu) in(%lu)\n", 
            unitNo, blockType, ch, string, moniInfo->regPtr->monibllmaxexp.bit.monibllmaxexp, 
            moniCtrl->upperLimitExceptHBlank ));
        }   
        
        if(moniInfo->regPtr->moniadhd.bit.moniadhd != moniCtrl->additionalHdCnt ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Ctrl(%u %u %u) %s result:moniadhd(%u) in(%d)\n", 
            unitNo, blockType, ch, string, moniInfo->regPtr->moniadhd.bit.moniadhd, 
            moniCtrl->additionalHdCnt));
        }   
        
        if(moniInfo->regPtr->moniadhw.bit.moniadhw != moniCtrl->additionalHdGapCnt ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Ctrl(%u %u %u) %s result:moniadhw(%llu) in(%llu)\n", 
            unitNo, blockType, ch, string,(ULLONG)moniInfo->regPtr->moniadhw.bit.moniadhw, 
            moniCtrl->additionalHdGapCnt));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Ctrl(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_3_print_4(Impro63Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, T_IM_PRO_MONI_RESULT* moniResult )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Get_Monitor_Count(%u %u %u) %s result:vdCnt(%u)\n", 
            unitNo, blockType, ch, string, moniResult->vdCnt ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Get_Monitor_Count(%u %u %u) %s result:hdCnt(%u)\n", 
            unitNo, blockType, ch, string, moniResult->hdCnt ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Get_Monitor_Count(%u %u %u) %s result:pixelCntIn1frame(%lu)\n", 
            unitNo, blockType, ch, string, moniResult->pixelCntIn1frame));
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Get_Monitor_Count(%u %u %u) %s result:minValHValidPixelCnt(%u)\n", 
            unitNo, blockType, ch, string, moniResult->minValHValidPixelCnt));
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Get_Monitor_Count(%u %u %u) %s result:maxValHValidPixelCnt(%u)\n", 
            unitNo, blockType, ch, string, moniResult->maxValHValidPixelCnt));
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Get_Monitor_Count(%u %u %u) %s result:intraFrameBlankCycle(%llu)\n", 
            unitNo, blockType, ch, string, moniResult->intraFrameBlankCycle));
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Get_Monitor_Count(%u %u %u) %s result:minValHBlankCycle(%lu)\n", 
            unitNo, blockType, ch, string, moniResult->minValHBlankCycle));
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Get_Monitor_Count(%u %u %u) %s result:maxValHBlankCycle(%lu)\n", 
            unitNo, blockType, ch, string, moniResult->maxValHBlankCycle));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_MONI_Get_Monitor_Count(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_3_print_5(Impro63Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, kint32 ercd )
{
    const T_IM_PRO_COMMON_M2P_INFO* m2pInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_m2p_reg_info( unitNo, blockType, ch, &m2pInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Start(%u %u %u) result:m2ptrg(%u)\n", 
            unitNo, blockType, ch, m2pInfo->regPtr->m2ptrg.bit.m2ptrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Start(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}                                                    

void im_pro_6_3_print_6(Impro63Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                            kuchar ch, kint32 ercd, kuchar force )
{
    const T_IM_PRO_COMMON_M2P_INFO* m2pInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_m2p_reg_info( unitNo, blockType, ch, &m2pInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Stop(%u %u %u %u) result:m2ptrg(%u)\n", 
            unitNo, blockType, ch, force, m2pInfo->regPtr->m2ptrg.bit.m2ptrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Stop(%u %u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, force, ercd ));
    }
}                                                    

void im_pro_6_3_print_7(Impro63Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                            kuchar ch, kint32 ercd, T_IM_PRO_M2P_CTRL* m2pCtrl )
{
    const T_IM_PRO_COMMON_M2P_INFO* m2pInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_m2p_reg_info( unitNo, blockType, ch, &m2pInfo );
        if(m2pInfo->regPtr->m2pctl.bit.m2ptyp != m2pCtrl->dataType ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Ctrl(%u %u %u) %s result:m2ptyp(%d) in(%d)\n", 
            unitNo, blockType, ch, string, m2pInfo->regPtr->m2pctl.bit.m2ptyp, m2pCtrl->dataType));
        }   
        
        if(m2pInfo->regPtr->m2pctl.bit.mdknmd != m2pCtrl->dekneeEnable ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Ctrl(%u %u %u) %s result:mdknmd(%d) in(%d)\n", 
            unitNo, blockType, ch, string, m2pInfo->regPtr->m2pctl.bit.mdknmd, m2pCtrl->dekneeEnable));
        }   
        
        if(m2pInfo->regPtr->m2pbsft.bit.m2pbsft != m2pCtrl->shiftBit ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Ctrl(%u %u %u) %s result:m2pbsft(%d) in(%d)\n", 
            unitNo, blockType, ch, string, m2pInfo->regPtr->m2pbsft.bit.m2pbsft, m2pCtrl->shiftBit));
        }   
        
        if(m2pInfo->regPtr->m2pbsft.bit.m2pbmd != m2pCtrl->shiftSat ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Ctrl(%u %u %u) %s result:m2pbmd(%d) in(%d)\n", 
            unitNo, blockType, ch, string, m2pInfo->regPtr->m2pbsft.bit.m2pbmd, m2pCtrl->shiftSat));
        }   
        
        if(m2pInfo->regPtr->m2pbsft.bit.m2pblr != m2pCtrl->bitShift ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Ctrl(%u %u %u) %s result:m2pblr(%d) in(%d)\n", 
            unitNo, blockType, ch, string, m2pInfo->regPtr->m2pbsft.bit.m2pblr, m2pCtrl->bitShift));
        }   
        
        if(m2pInfo->regPtr->m2pbsft.bit.m2pbt != m2pCtrl->validBitCount ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Ctrl(%u %u %u) %s result:m2pbt(%d) in(%d)\n", 
            unitNo, blockType, ch, string, m2pInfo->regPtr->m2pbsft.bit.m2pbt, m2pCtrl->validBitCount));
        }   
        
        if(m2pInfo->regPtr->m2pofs.bit.m2pofs != m2pCtrl->shiftValue ) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Ctrl(%u %u %u) %s result:m2pofs(%d) in(%d)\n", 
            unitNo, blockType, ch, string, m2pInfo->regPtr->m2pofs.bit.m2pofs, m2pCtrl->shiftValue));
        }   
        
        if(m2pInfo->regPtr->m2pclip.bit.m2pcliplw != m2pCtrl->lowerLimitClipValue) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Ctrl(%u %u %u) %s result:m2pcliplw(%d) in(%d)\n", 
            unitNo, blockType, ch, string, m2pInfo->regPtr->m2pclip.bit.m2pcliplw, 
            m2pCtrl->lowerLimitClipValue ));
        }   
        
        if(m2pInfo->regPtr->m2pclip.bit.m2pcliphi != m2pCtrl->upperLimitClipValue) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Ctrl(%u %u %u) %s result:m2pcliphi(%d) in(%d)\n", 
            unitNo, blockType, ch, string, m2pInfo->regPtr->m2pclip.bit.m2pcliphi, 
            m2pCtrl->upperLimitClipValue ));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Ctrl(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_3_print_8(Impro63Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, kuchar paenTrg )
{
    const T_IM_PRO_COMMON_M2P_INFO* m2pInfo;

    if( ercd == DdimUserCustom_E_OK ) {
        im_pro_comm_get_m2p_reg_info( unitNo, blockType, ch, &m2pInfo );
        DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Set_PAEN(%u %u %u %u) result:paen(%u)\n", 
            unitNo, blockType, ch, paenTrg, m2pInfo->regPtr->m2ppaen.bit.mppaen ));
        DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Set_PAEN(%u %u %u %u) result:m2ptrg(%u)\n", 
            unitNo, blockType, ch, paenTrg, m2pInfo->regPtr->m2ptrg.bit.m2ptrg ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Set_PAEN(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}

void im_pro_6_3_print_9(Impro63Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, 
                        kuchar ch, kint32 ercd, kint32 cmpErcd )
{
    if( ercd == DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Set_Table(%u %u %u) API result(0x%x) memcmp result(0x%x)\n", 
            unitNo, blockType, ch, ercd, cmpErcd ));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_M2P_Set_Table(%u %u %u) error(not exist) ercd=0x%x\n", 
            unitNo, blockType, ch, ercd ));
    }
}
#endif

Impro63Print* impro_6_3_print_new(void)
{
	Impro63Print* self = k_object_new_with_private(IMPRO_TYPE_6_3_PRINT, sizeof(Impro63PrintPrivate));

	return self;
}

Impro63Print* impro_6_3_print_get(void)
{
	static Impro63Print* self = NULL;

	if(!self) {
		self = k_object_new_with_private(IMPRO_TYPE_6_3_PRINT, sizeof(Impro63PrintPrivate));
	}

	return self;
}
