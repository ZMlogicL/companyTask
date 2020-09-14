/*
*@Copyright (C) 2040-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*4、
*2、
*@version
*4.0.0 2020年06月开始开发
*/

#include "imiipdefine.h"

#include "imiipstruct.h"
#include "imiipmain.h"

#include "imiipnew.h"
#include "im_iip_param.h"
#include "driver_common.h"
#include <klib.h>
//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
//#endif
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include "jdsiip.h"
// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#endif //CO_PT_ENABLE
// ### REMOVE_RELEASE END
#include <string.h>

 K_TYPE_DEFINE_WITH_PRIVATE(ImIipNew, im_iip_new);
 #define IM_IIP_NEW_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipNewPrivate, IM_TYPE_IIP_NEW))

 struct _ImIipNewPrivate
 {
 	int a;
 };

 static void im_iip_new_constructor(ImIipNew *self)
 {
 //	ImIipNewPrivate *priv = IM_IIP_NEW_GET_PRIVATE(self);
 //	priv-> a =  0;
 }

 static void im_iip_new_destructor(ImIipNew *self)
 {
 //	ImIipNewPrivate *priv = IM_IIP_NEW_GET_PRIVATE(self);
 //	priv-> a =  0;
 }

static VOID imIipUtilCleanDcache( const ULONG addr, const ULONG bytes )
{
	DDIM_User_L1l2cache_Clean_Addr( addr, bytes );
	ImIipDefine_IM_IIP_DMD();
}

// Enable Interrupt
static UINT32 imIipUtilSetIntFact( const ULLONG unitidBitmask )
{
	UINT32 intFact = ImIipDefine_D_IM_IIP_INT_FACTOR_AXIERR;

	if( unitidBitmask & ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL0 ) {
		intFact = ImIipDefine_D_IM_IIP_INT_FACTOR_SL0END;
	}
	if( unitidBitmask & ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL1 ) {
		intFact = ImIipDefine_D_IM_IIP_INT_FACTOR_SL1END;
	}
	if( unitidBitmask & ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL2 ) {
		intFact = ImIipDefine_D_IM_IIP_INT_FACTOR_SL2END;
	}
	if( unitidBitmask & ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL3 ) {
		intFact = ImIipDefine_D_IM_IIP_INT_FACTOR_SL3END;
	}
	if( unitidBitmask & ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL4 ) {
		intFact = ImIipDefine_D_IM_IIP_INT_FACTOR_SL4END;
	}
	if( unitidBitmask & ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL5 ) {
		intFact = ImIipDefine_D_IM_IIP_INT_FACTOR_SL5END;
	}
	if( unitidBitmask & ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL6 ) {
		intFact = ImIipDefine_D_IM_IIP_INT_FACTOR_SL6END;
	}
	if( unitidBitmask & ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL7 ) {
		intFact = ImIipDefine_D_IM_IIP_INT_FACTOR_SL7END;
	}
	if( unitidBitmask & ImIipDefine_D_IM_IIP_PARAM_PLDUNIT_SL8 ) {
		intFact = ImIipDefine_D_IM_IIP_INT_FACTOR_SL8END;
	}

	return intFact;
}

VOID im_iip_new_set_axi_param(  ImIipDefine* self,const EImIipUnitId unitid, EImIipAxiId* const axi_id, TIMIipCtrlAxi* const axi_cfg, const UCHAR master_IF )
{
	switch( unitid ) {
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN0:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_AFN0;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN1:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_AFN1;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN2:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_AFN2;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN3:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_AFN3;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_FRECT0:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_FRECT0;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_FRECT1:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_FRECT1;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_GPC:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_GPC;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL0:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_SL0;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL1:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_SL1;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL2:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_SL2;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL3:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_SL3;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL4:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_SL4;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL5:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_SL5;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL6:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_SL6;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL7:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_SL7;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL8:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_SL8;
			break;
		default:
			*axi_id = ImIipStruct_E_IM_IIP_AXI_ID_MAX;		// mean "None"
			return;	// Do nothing
	}

	axi_cfg->transReqCtrl = 0;	// register default
	axi_cfg->cacheType = 1;		// register default
	axi_cfg->protectionType = 0;	// register default
}

INT32 im_iip_new_util_exec_rotate( TImIipUtilParamResizeRotate* const rr_param, const TImIipUtilRr* const cfg )
{
	INT32	retval;
	UINT32	loopcnt;

	for ( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		retval = Im_IIP_Ctrl_PIXFMTTBL( rr_param->pixid[loopcnt], &rr_param->pixfmttbl[loopcnt] );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->afnUnitid, &rr_param->unitCfgAfn );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->slUnitid, &rr_param->unitCfgSl );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	if( rr_param->axiIdAfn != ImIipStruct_E_IM_IIP_AXI_ID_MAX ) {
		retval = im_iip_sub_ctrl_axi( rr_param->axiIdAfn, &rr_param->axiCfgAfn );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
				return retval;
		}
	}

	if( rr_param->axiIdSl != ImIipStruct_E_IM_IIP_AXI_ID_MAX ) {
		retval = im_iip_sub_ctrl_axi( rr_param->axiIdSl, &rr_param->axiCfgSl );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
				return retval;
		}
	}

	rr_param->waitParam.intFact = imIipUtilSetIntFact( rr_param->openParam.unitidBitmask );

	retval = Im_IIP_Set_Interrupt( rr_param->waitParam.intFact, 1 );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}


	imIipUtilCleanDcache( rr_param->paramBufferAddr -ImIipDefine_D_IM_IIP_UTIL_RR_BUF_BYTES, ImIipDefine_D_IM_IIP_UTIL_RR_BUF_BYTES );


	retval = Im_IIP_Start_SWTRG( cfg->slUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->afnUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	return ImIipDefine_D_IM_IIP_OK;
}

INT32 im_iip_new_util_exec_csc( TImIipUtilParamCsc* const csc_param, const TImIipUtilCsc* const cfg )
{
	INT32	retval;
	UINT32	loopcnt;

	for ( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		retval = Im_IIP_Ctrl_PIXFMTTBL( csc_param->pixid[loopcnt], &csc_param->pixfmttbl[loopcnt] );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->ldUnitid, &csc_param->unitCfg1D );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->cscUnitid, &csc_param->unitCfgCsc );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->slUnitid, &csc_param->unitCfgSl );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	if( csc_param->axiIdLd != ImIipStruct_E_IM_IIP_AXI_ID_MAX ) {
		retval = im_iip_sub_ctrl_axi( csc_param->axiIdLd, &csc_param->axiCfg1D );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
				return retval;
		}
	}

	if( csc_param->axiIdSl != ImIipStruct_E_IM_IIP_AXI_ID_MAX ) {
		retval = im_iip_sub_ctrl_axi( csc_param->axiIdSl, &csc_param->axiCfgSl );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
				return retval;
		}
	}

	csc_param->waitParam.intFact = imIipUtilSetIntFact( csc_param->openParam.unitidBitmask );

	retval = Im_IIP_Set_Interrupt( csc_param->waitParam.intFact, 1 );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}


	imIipUtilCleanDcache( csc_param->paramBufferAddr -ImIipDefine_D_IM_IIP_UTIL_CSC_BUF_BYTES, ImIipDefine_D_IM_IIP_UTIL_CSC_BUF_BYTES );


	retval = Im_IIP_Start_SWTRG( cfg->slUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->cscUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->ldUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	return ImIipDefine_D_IM_IIP_OK;
}

static INT32 im_iip_util_exec_lut( TImIipUtilParamLut* const lut_param, const TImIipUtilLut* const cfg )
{
	INT32	retval;
	UINT32	loopcnt;

	for ( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		retval = Im_IIP_Ctrl_PIXFMTTBL( lut_param->pixid[loopcnt], &lut_param->pixfmttbl[loopcnt] );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->ldUnitid, &lut_param->unitCfg1D );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->lutUnitid, &lut_param->unitCfgLut );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->slUnitid, &lut_param->unitCfgSl );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	if( lut_param->axiIdLd != ImIipStruct_E_IM_IIP_AXI_ID_MAX ) {
		retval = im_iip_sub_ctrl_axi( lut_param->axiIdLd, &lut_param->axiCfg1D );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
				return retval;
		}
	}

	if( lut_param->axiIdSl != ImIipStruct_E_IM_IIP_AXI_ID_MAX ) {
		retval = im_iip_sub_ctrl_axi( lut_param->axiIdSl, &lut_param->axiCfgSl );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
				return retval;
		}
	}

	lut_param->waitParam.intFact = imIipUtilSetIntFact( lut_param->openParam.unitidBitmask );

	retval = Im_IIP_Set_Interrupt( lut_param->waitParam.intFact, 1 );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}


	imIipUtilCleanDcache( lut_param->paramBufferAddr -ImIipDefine_D_IM_IIP_UTIL_LUT_BUF_BYTES, ImIipDefine_D_IM_IIP_UTIL_LUT_BUF_BYTES );

#if 0
	{	// Print register for debug.
		extern VOID CT_Im_IIP_Print_Unitcfg_Byid( const EImIipUnitId unitid );
		extern VOID CT_Im_IIP_Print_Pixfmttbl_Byid( const EImIipPixid pixid );

		CT_Im_IIP_Print_Unitcfg_Byid( cfg->ldUnitid );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->lutUnitid );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->slUnitid );
		CT_Im_IIP_Print_Pixfmttbl_Byid( cfg->srcPixid );
		CT_Im_IIP_Print_Pixfmttbl_Byid( cfg->dstPixid );
	}
#endif

	retval = Im_IIP_Start_SWTRG( cfg->slUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->lutUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->ldUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	return ImIipDefine_D_IM_IIP_OK;
}
/**
@brief		Execute Utility function
*/
static INT32 im_iip_util_exec_alpha( TImIipUtilParamAlpha* const alp_param, const TImIipUtilAlphablend* const cfg )
{
	INT32	retval;
	UINT32	loopcnt;

	for ( loopcnt = 0; loopcnt < 3; loopcnt++ ) {
		retval = Im_IIP_Ctrl_PIXFMTTBL( alp_param->pixid[loopcnt], &alp_param->pixfmttbl[loopcnt] );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->ldUnitid[0], &alp_param->unitCfg1D[0] );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->ldUnitid[1], &alp_param->unitCfg1D[1] );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->blendUnitid, &alp_param->unitCfgAlp );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->slUnitid, &alp_param->unitCfgSl );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	if( alp_param->axiIdLd[0] != ImIipStruct_E_IM_IIP_AXI_ID_MAX ) {
		retval = im_iip_sub_ctrl_axi( alp_param->axiIdLd[0], &alp_param->axiCfg1D[0] );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
				return retval;
		}
	}

	if( alp_param->axiIdLd[1] != ImIipStruct_E_IM_IIP_AXI_ID_MAX ) {
		retval = im_iip_sub_ctrl_axi( alp_param->axiIdLd[1], &alp_param->axiCfg1D[1] );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
				return retval;
		}
	}

	if( alp_param->axiIdSl != ImIipStruct_E_IM_IIP_AXI_ID_MAX ) {
		retval = im_iip_sub_ctrl_axi( alp_param->axiIdSl, &alp_param->axiCfgSl );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
				return retval;
		}
	}

	alp_param->waitParam.intFact = imIipUtilSetIntFact( alp_param->openParam.unitidBitmask );

	retval = Im_IIP_Set_Interrupt( alp_param->waitParam.intFact, 1 );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}


	imIipUtilCleanDcache( alp_param->paramBufferAddr -ImIipDefine_D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES, ImIipDefine_D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES );


	retval = Im_IIP_Start_SWTRG( cfg->slUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->blendUnitid, ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->ldUnitid[1], ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->ldUnitid[0], ImIipDefine_D_IM_IIP_SWTRG_ON );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
	}

	return ImIipDefine_D_IM_IIP_OK;
}

/**
@brief		Set Alpha unit parameter
@param[out]	alpha			Pointer of ALPHA unit paramter
@param[in]	cfg				Pointer of Alpha parameter
*/
static VOID im_iip_set_alpha_unit_param( T_IM_IIP_PARAM_BLEND* const alpha,
										 const TImIipUtilAlphablend* const cfg )
{
	memset( alpha, '\0', sizeof(*alpha) );

	alpha->header0.bit.BeginningAddress = 0x0000;
	alpha->header0.bit.WordLength = 4;
	alpha->header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_LOAD_ONLY;
//	alpha->BLENDTOPCNF0.bit.WAITCONF_0;	// set later
//	alpha->BLENDTOPCNF0.bit.DATACONF_0;	// set later
//	alpha->BLENDTOPCNF1.bit.WAITCONF_1;	// set later
//	alpha->BLENDTOPCNF1.bit.DATACONF_1;	// set later
	alpha->BLENDTOPCNF2.bit.DATACONF_2 = E_IM_IIP_PARAM_PORTID_NONE;

	alpha->header1.bit.BeginningAddress = 0x0080;
	alpha->header1.bit.WordLength = 24;
	alpha->header1.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET;
	alpha->BLENDCTL.bit.BLD_MD = E_IM_IIP_PARAM_BLD_MD_ALPHA_BLEND;
	alpha->BLENDCTL.bit.CLP_MD = E_IM_IIP_PARAM_CLP_MD_NO_CLIP;
	if( cfg->dst.gbl.alpha == ImIipDefine_D_IM_IIP_ALPHA_TRUE ) {
		alpha->BLENDCTL.bit.ALPHA_OUT = cfg->alpha.out;
	}
	else {
		alpha->BLENDCTL.bit.ALPHA_OUT = E_IM_IIP_PARAM_ALPHA_OUT_NONE;
	}

	alpha->ALPHACTL0.bit.ALPHA_STEP = cfg->alpha.step;
	alpha->ALPHACTL0.bit.ALPHA_SEL = cfg->alpha.sel;
	alpha->ALPHACTL1.bit.ALPHA_VAL0 = cfg->alpha.alphaVal[0];
	alpha->ALPHACTL1.bit.ALPHA_VAL1 = cfg->alpha.alphaVal[1];
	alpha->ALPHACTL2.bit.ALPHA_VAL2 = cfg->alpha.alphaVal[2];
	alpha->ALPHACTL2.bit.ALPHA_VAL3 = cfg->alpha.alphaVal[3];

// alpha->WADCTl[0].bit.WADD_KA = 0;	// not used
// alpha->WADCTl[0].bit.WADD_KB = 0;	// not used
// alpha->WADCTl[1].bit.WADD_KA = 0;	// not used
// alpha->WADCTl[1].bit.WADD_KB = 0;	// not used
// alpha->WADCTl[2].bit.WADD_KA = 0;	// not used
// alpha->WADCTl[2].bit.WADD_KB = 0;	// not used
// alpha->WADCTl[3].bit.WADD_KA = 0;	// not used
// alpha->WADCTl[3].bit.WADD_KB = 0;	// not used
// alpha->DIVCTL0.bit.RSFT = 0;	// not used
// alpha->MSKCTL0.bit.MSKSEL = 0;	// not used
// alpha->MSKCTL0.bit.DINSEL = 0;	// not used
// alpha->MULCTL[0].bit.ADDVAL_A = 0;	// not used
// alpha->MULCTL[0].bit.ADDVAL_B = 0;	// not used
// alpha->MULCTL[0].bit.ADDVAL_C = 0;	// not used
// alpha->MULCTL[0].bit.SFTSEL = 0;	// not used
// alpha->MULCTL[1].bit.ADDVAL_A = 0;	// not used
// alpha->MULCTL[1].bit.ADDVAL_B = 0;	// not used
// alpha->MULCTL[1].bit.ADDVAL_C = 0;	// not used
// alpha->MULCTL[1].bit.SFTSEL = 0;	// not used
// alpha->MULCTL[2].bit.ADDVAL_A = 0;	// not used
// alpha->MULCTL[2].bit.ADDVAL_B = 0;	// not used
// alpha->MULCTL[2].bit.ADDVAL_C = 0;	// not used
// alpha->MULCTL[2].bit.SFTSEL = 0;	// not used
// alpha->MULCTL[3].bit.ADDVAL_A = 0;	// not used
// alpha->MULCTL[3].bit.ADDVAL_B = 0;	// not used
// alpha->MULCTL[3].bit.ADDVAL_C = 0;	// not used
// alpha->MULCTL[3].bit.SFTSEL = 0;	// not used
}

/**
@brief		Set Parameters of Alpha Blend Utility
*/
static VOID im_iip_util_set_param_alpha( TImIipUtilParamAlpha* const alp_param, const TImIipUtilAlphablend* const cfg )
{
	T_IM_IIP_PARAM_1DL*			oned[2];
	T_IM_IIP_PARAM_BLEND*		alpha;
	T_IM_IIP_PARAM_STS*			sl;
	TImIipUtilPhvsz			phvsz;

	/// Set Pointer of SDRAM parameter

	oned[0] = (T_IM_IIP_PARAM_1DL*)alp_param->paramBufferAddr;
	alp_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_1DL) );

	oned[1] = (T_IM_IIP_PARAM_1DL*)alp_param->paramBufferAddr;
	alp_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_1DL) );

	alpha = (T_IM_IIP_PARAM_BLEND*)alp_param->paramBufferAddr;
	alp_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_BLEND) );

	sl = (T_IM_IIP_PARAM_STS*)alp_param->paramBufferAddr;
	alp_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_STS) );



	/// Set SDRAM paramter
	im_iip_sub_set_phvsz_1d_sl( NULL,&phvsz, &cfg->dst );

	im_iip_define_set_1d_unit_param(NULL, oned[0], &phvsz, &cfg->src[0], cfg->pixDepth, cfg->ldCacheSelect[0] );
	im_iip_define_set_1d_unit_param( NULL,oned[1], &phvsz, &cfg->src[1], cfg->pixDepth, cfg->ldCacheSelect[1] );

	im_iip_set_alpha_unit_param( alpha, cfg );

	im_iip_define_set_sl_unit_param( NULL,sl, &phvsz, &cfg->dst.rect, &cfg->dst.gbl, cfg->pixDepth );

	oned[0]->PIXIDDEF.bit.IPIXID = alp_param->pixid[0];
	oned[0]->LD_TOPCNF0.bit.WAITCONF = im_iip_sub_util_conv_portid( cfg->blendUnitid );

	oned[1]->PIXIDDEF.bit.IPIXID = alp_param->pixid[1];
	oned[1]->LD_TOPCNF0.bit.WAITCONF = im_iip_new_util_conv_portid_1( cfg->blendUnitid );

	alpha->BLENDTOPCNF0.bit.DATACONF_0 = im_iip_sub_util_conv_portid( cfg->ldUnitid[0] );
	alpha->BLENDTOPCNF1.bit.DATACONF_1 = im_iip_sub_util_conv_portid( cfg->ldUnitid[1] );
	alpha->BLENDTOPCNF0.bit.WAITCONF_0 = im_iip_sub_util_conv_portid( cfg->slUnitid );

	sl->BASE.PIXIDDEF.bit.OPIXID = alp_param->pixid[2];
	sl->BASE.SL_TOPCNF0.bit.DATACONF = im_iip_sub_util_conv_portid( cfg->blendUnitid );

	alp_param->pParam1D[0] = oned[0];
	alp_param->pParam1D[0] = oned[1];
	alp_param->pParamAlp = alpha;
	alp_param->pParamSl = sl;

	/// Set UNITINFTBL parameter
	im_iip_sub_set_unitinftbl_param( NULL, &alp_param->unitCfg1D[0], cfg->ldUnitid[0], oned[0], 0ULL );
	im_iip_sub_set_unitinftbl_param( NULL, &alp_param->unitCfg1D[1], cfg->ldUnitid[1], oned[1], 0ULL );
	im_iip_sub_set_unitinftbl_param( NULL, &alp_param->unitCfgAlp, cfg->blendUnitid, alpha, 0ULL );
	im_iip_sub_set_unitinftbl_param(NULL,  &alp_param->unitCfgSl, cfg->slUnitid, sl, alp_param->openParam.unitidBitmask );
}

ULONG im_iip_new_util_conv_portid_1( const EImIipUnitId unitid )
{
	switch( unitid ) {
		case ImIipStruct_E_IM_IIP_UNIT_ID_FLT:
			return E_IM_IIP_PARAM_PORTID_FLT_P1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LUT:
			return E_IM_IIP_PARAM_PORTID_LUT_P1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_GPC:
			return E_IM_IIP_PARAM_PORTID_GPC_P1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_BLEND0:
			return E_IM_IIP_PARAM_PORTID_BLEND0_P1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_CFL0:
			return E_IM_IIP_PARAM_PORTID_CFL0_P1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_BLEND1:
			return E_IM_IIP_PARAM_PORTID_BLEND1_P1;
		default:
			return E_IM_IIP_PARAM_PORTID_NONE;	// Other unit
	}
}
static INT32 im_iip_set_LUTRAM( const TImIipLutram* const lutram,
							    const UINT32 alpha )
{
	TImIipLut			lut;
	INT32					retval = ImIipDefine_D_IM_IIP_ERR;
	EImIipLutramType	loopcnt;

	for ( loopcnt = ImIipStruct_E_IM_IIP_LUTRAM_TYPE_A; loopcnt < ImIipStruct_E_IM_IIP_LUTRAM_TYPE_MAX; loopcnt++ ) {
		lut.bufferBytes = lutram->bufferBytes[loopcnt];
		lut.bufferAddr = lutram->bufferAddr[loopcnt];
		lut.lutramType = loopcnt;
		retval = Im_IIP_Ctrl_LUT( &lut );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			return retval;
		}
	}
	return retval;
}

static VOID im_iip_util_set_param_lut( TImIipUtilParamLut* const lut_param, const TImIipUtilLut* const cfg )
{
	T_IM_IIP_PARAM_1DL*			oned;
	T_IM_IIP_PARAM_LUT*			lut;
	T_IM_IIP_PARAM_STS*			sl;
	TImIipUtilPhvsz			phvsz;

	/// Set Pointer of SDRAM parameter

	oned = (T_IM_IIP_PARAM_1DL*)lut_param->paramBufferAddr;
	lut_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_1DL) );

	lut = (T_IM_IIP_PARAM_LUT*)lut_param->paramBufferAddr;
	lut_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_LUT) );

	sl = (T_IM_IIP_PARAM_STS*)lut_param->paramBufferAddr;
	lut_param->paramBufferAddr += ImIipDefine_IM_IIP_ROUNDUN_8( sizeof(T_IM_IIP_PARAM_STS) );


	/// Set SDRAM paramter
	im_iip_sub_set_phvsz_1d_sl( NULL,&phvsz, &cfg->dst );

	im_iip_define_set_1d_unit_param(NULL, oned, &phvsz, &cfg->src, cfg->pixDepth, cfg->ldCacheSelect );

	im_iip_new_util_set_lut_unit_param(NULL, lut, cfg );

	im_iip_define_set_sl_unit_param(NULL, sl, &phvsz, &cfg->dst.rect, &cfg->dst.gbl, cfg->pixDepth );

	oned->PIXIDDEF.bit.IPIXID = lut_param->pixid[0];
	oned->LD_TOPCNF0.bit.WAITCONF = im_iip_sub_util_conv_portid( cfg->lutUnitid );

	lut->LUTTOPCNF[0].bit.DATACONF = im_iip_sub_util_conv_portid( cfg->ldUnitid );
	lut->LUTTOPCNF[0].bit.WAITCONF = im_iip_sub_util_conv_portid( cfg->slUnitid );

	sl->BASE.PIXIDDEF.bit.OPIXID = lut_param->pixid[1];
	sl->BASE.SL_TOPCNF0.bit.DATACONF = im_iip_sub_util_conv_portid( cfg->lutUnitid );

	lut_param->pParam1D = oned;
	lut_param->pParamLut = lut;
	lut_param->pParamSl = sl;

	im_iip_sub_set_unitinftbl_param(NULL, &lut_param->unitCfg1D, cfg->ldUnitid, oned, 0ULL );
	im_iip_sub_set_unitinftbl_param( NULL, &lut_param->unitCfgLut, cfg->lutUnitid, lut, 0ULL );
	im_iip_sub_set_unitinftbl_param( NULL, &lut_param->unitCfgSl, cfg->slUnitid, sl, lut_param->openParam.unitidBitmask );
}

VOID im_iip_new_util_set_lut_unit_param( ImIipDefine* self,T_IM_IIP_PARAM_LUT* const lut,
									   const TImIipUtilLut* const cfg )
{
	INT32	loopcnt;

	memset( lut, '\0', sizeof(*lut) );

	lut->header0.bit.BeginningAddress = 0x0000;
	lut->header0.bit.WordLength = 57;
	lut->header0.bit.CtrlCode = E_IM_IIP_PARAM_CTL_CODE_EXE_LAST_PACKET;
//	lut->LUTTOPCNF[0].bit.DATACONF;	// set later
//	lut->LUTTOPCNF[0].bit.WAITCONF;	// set later
	for ( loopcnt = 1; loopcnt < 4; loopcnt++ ) {
		lut->LUTTOPCNF[loopcnt].bit.DATACONF = E_IM_IIP_PARAM_PORTID_NONE;
		lut->LUTTOPCNF[loopcnt].bit.WAITCONF = E_IM_IIP_PARAM_PORTID_NONE;
	}
	lut->LUTUNITCTL.bit.PORTEN = 0x1;
	lut->LUTUNITCTL.bit.PORT3SELI = 0;
	lut->LUTUNITCTL.bit.PORT3SELO = 0;
	lut->LUTUNITCTL.bit.BRANCH = 0;
	lut->LUTUNITCTL.bit.PORT2SELI = 0;
	lut->LUTUNITCTL.bit.PORT2SELO = 0;
	lut->LUTUNITCTL.bit.OUTMD0 = 0;
	lut->LUTUNITCTL.bit.OUTMD1 = 0;
	lut->LUTUNITCTL.bit.OUTMD2 = 0;
	lut->LUTUNITCTL.bit.OUTMD3 = 0;

	// LUT A
	lut->LUTCTL_A.bit.LUTBIT = cfg->lutPixDepth[0];
	lut->LUTCTL_A.bit.USE = E_IM_IIP_PARAM_LUTUSE_LUT_OUT;
	lut->LUTCTL_A.bit.SGN = cfg->src.gbl.signYG;
	lut->LUTCTL_A.bit.SPLBIT = cfg->splbit[0];
	lut->LUTPRECAL_A.bit.SHIFT = 0;
	lut->LUTPRECAL_A.bit.OFSET = 0;
	lut->LUTPRECAL_A.bit.CLPMAX = 0x3FFF;
	lut->LUTPRECAL_A.bit.THMAX = 0x3FFF;
	lut->LUTPRECAL_A.bit.CLPMIN = -0x4000;
	lut->LUTPRECAL_A.bit.THMIN = -0x4000;
	lut->LUTPRECAL_A.bit.ABS = 0x0;
	lut->LUTPRECAL_A.bit.LUTADRS = 0x0000;

	// LUT B
	lut->LUTCTL_B.bit.LUTBIT = cfg->lutPixDepth[1];
	lut->LUTCTL_B.bit.USE = E_IM_IIP_PARAM_LUTUSE_LUT_OUT;
	lut->LUTCTL_B.bit.SGN = cfg->src.gbl.signCbB;
	lut->LUTCTL_B.bit.SPLBIT = cfg->splbit[1];
	lut->LUTPRECAL_B.bit.SHIFT = 0;
	lut->LUTPRECAL_B.bit.OFSET = 0;
	lut->LUTPRECAL_B.bit.CLPMAX = 0x3FFF;
	lut->LUTPRECAL_B.bit.THMAX = 0x3FFF;
	lut->LUTPRECAL_B.bit.CLPMIN = -0x4000;
	lut->LUTPRECAL_B.bit.THMIN = -0x4000;
	lut->LUTPRECAL_B.bit.ABS = 0x0;
	lut->LUTPRECAL_B.bit.LUTADRS = 0x2000;

	// LUT C
	lut->LUTCTL_C.bit.LUTBIT = cfg->lutPixDepth[2];
	lut->LUTCTL_C.bit.USE = E_IM_IIP_PARAM_LUTUSE_LUT_OUT;
	lut->LUTCTL_C.bit.SGN = cfg->src.gbl.signCrR;
	lut->LUTCTL_C.bit.SPLBIT = cfg->splbit[2];
	lut->LUTPRECAL_C.bit.SHIFT = 0;
	lut->LUTPRECAL_C.bit.OFSET = 0;
	lut->LUTPRECAL_C.bit.CLPMAX = 0x3FFF;
	lut->LUTPRECAL_C.bit.THMAX = 0x3FFF;
	lut->LUTPRECAL_C.bit.CLPMIN = -0x4000;
	lut->LUTPRECAL_C.bit.THMIN = -0x4000;
	lut->LUTPRECAL_C.bit.ABS = 0x0;
	lut->LUTPRECAL_C.bit.LUTADRS = 0x4000;

	// LUT D
	lut->LUTCTL_D.bit.LUTBIT = cfg->lutPixDepth[3];
	lut->LUTCTL_D.bit.USE = E_IM_IIP_PARAM_LUTUSE_PRECALC;
	lut->LUTCTL_D.bit.SGN = cfg->src.gbl.signD3;
	lut->LUTCTL_D.bit.SPLBIT = cfg->splbit[3];
	lut->LUTPRECAL_D.bit.SHIFT = 0;
	lut->LUTPRECAL_D.bit.OFSET = 0;
	lut->LUTPRECAL_D.bit.CLPMAX = 0x3FFF;
	lut->LUTPRECAL_D.bit.THMAX = 0x3FFF;
	lut->LUTPRECAL_D.bit.CLPMIN = -0x4000;
	lut->LUTPRECAL_D.bit.THMIN = -0x4000;
	lut->LUTPRECAL_D.bit.ABS = 0x0;
	lut->LUTPRECAL_D.bit.LUTADRS = 0x1000;

	// LUT E
	lut->LUTCTL_E.bit.LUTBIT = cfg->lutPixDepth[0];
	lut->LUTCTL_E.bit.USE = E_IM_IIP_PARAM_LUTUSE_PRECALC;
	lut->LUTCTL_E.bit.SGN = cfg->src.gbl.signYG;
	lut->LUTCTL_E.bit.SPLBIT = 0;
	lut->LUTPRECAL_E.bit.SHIFT = 0;
	lut->LUTPRECAL_E.bit.OFSET = 0;
	lut->LUTPRECAL_E.bit.CLPMAX = 0x3FFF;
	lut->LUTPRECAL_E.bit.THMAX = 0x3FFF;
	lut->LUTPRECAL_E.bit.CLPMIN = -0x4000;
	lut->LUTPRECAL_E.bit.THMIN = -0x4000;
	lut->LUTPRECAL_E.bit.ABS = 0x0;
	lut->LUTPRECAL_E.bit.LUTADRS = 0x3000;

	// LUT F
	lut->LUTCTL_F.bit.LUTBIT = cfg->lutPixDepth[1];
	lut->LUTCTL_F.bit.USE = E_IM_IIP_PARAM_LUTUSE_PRECALC;
	lut->LUTCTL_F.bit.SGN = cfg->src.gbl.signCbB;
	lut->LUTCTL_F.bit.SPLBIT = 0;
	lut->LUTPRECAL_F.bit.SHIFT = 0;
	lut->LUTPRECAL_F.bit.OFSET = 0;
	lut->LUTPRECAL_F.bit.CLPMAX = 0x3FFF;
	lut->LUTPRECAL_F.bit.THMAX = 0x3FFF;
	lut->LUTPRECAL_F.bit.CLPMIN = -0x4000;
	lut->LUTPRECAL_F.bit.THMIN = -0x4000;
	lut->LUTPRECAL_F.bit.ABS = 0x0;
	lut->LUTPRECAL_F.bit.LUTADRS = 0x5000;

}
/**
@brief		Set Parameters of Alpha Blend Utility
*/
INT32 im_iip_new_util_alpha_main( TImIipUtilParamAlpha* const alp_param, const TImIipUtilAlphablend* const cfg )
{
	INT32						retval;
	TImIipUtilAlphaInfo	alpha_info;

	alp_param->openParam.unitidBitmask = ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->ldUnitid[0])
										 | ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->ldUnitid[1])
										 | ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->blendUnitid)
										 | ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->slUnitid);
	alp_param->openParam.pixidBitmask = cfg->srcPixid[0] | cfg->srcPixid[1] | cfg->dstPixid;
	alp_param->openParam.openResBitmask = ImIipStruct_E_IM_IIP_OPEN_RES_NONE;

	switch( cfg->ldCacheSelect[0] ) {
		case E_IM_IIP_PARAM_CSEL_0:
			alp_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0;
			break;
		case E_IM_IIP_PARAM_CSEL_1:
			alp_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE1;
			break;
		case E_IM_IIP_PARAM_CSEL_2:
			alp_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE2;
			break;
		default:
			return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	switch( cfg->ldCacheSelect[1] ) {
		case E_IM_IIP_PARAM_CSEL_0:
			alp_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0;
			break;
		case E_IM_IIP_PARAM_CSEL_1:
			alp_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE1;
			break;
		case E_IM_IIP_PARAM_CSEL_2:
			alp_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE2;
			break;
		default:
			return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	alp_param->pixid[0] = im_iip_sub_util_conv_pixid( cfg->srcPixid[0] );
	if( alp_param->pixid[0] == ImIipStruct_E_IM_IIP_PIXID_INVALID ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
	alp_param->pixid[1] = im_iip_sub_util_conv_pixid( cfg->srcPixid[1] );
	if( alp_param->pixid[1] == ImIipStruct_E_IM_IIP_PIXID_INVALID ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
	alp_param->pixid[2] = im_iip_sub_util_conv_pixid( cfg->dstPixid );
	if( alp_param->pixid[2] == ImIipStruct_E_IM_IIP_PIXID_INVALID ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	retval = Im_IIP_Open_SWTRG( alp_param->openParam.unitidBitmask, alp_param->openParam.pixidBitmask, alp_param->openParam.openResBitmask, alp_param->waitParam.waitTime );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
		return retval;
	}


	while( 1 ) {
		/// Set SDRAM parameter and UNITINFTBL parameter
		im_iip_util_set_param_alpha( alp_param, cfg );

		/// Set IIP driver parameter
		alpha_info.alphaDepth = cfg->alphaDepth;
		alpha_info.alphaSubsampling = cfg->alphaSubsampling;
		im_iip_sub_set_pixfmttbl_param( NULL,&alp_param->pixfmttbl[0], &cfg->src[0].gbl, cfg->pixDepth, &alpha_info );
		im_iip_sub_set_pixfmttbl_param( NULL,&alp_param->pixfmttbl[1], &cfg->src[1].gbl, cfg->pixDepth, &alpha_info );
		im_iip_sub_set_pixfmttbl_param(NULL, &alp_param->pixfmttbl[2], &cfg->dst.gbl,    cfg->pixDepth, &alpha_info );

		im_iip_new_set_axi_param(  NULL,cfg->ldUnitid[0], &alp_param->axiIdLd[0], &alp_param->axiCfg1D[0], alp_param->paramMasterIf );
		im_iip_new_set_axi_param(  NULL,cfg->ldUnitid[1], &alp_param->axiIdLd[1], &alp_param->axiCfg1D[1], alp_param->paramMasterIf );
		im_iip_new_set_axi_param(  NULL,cfg->slUnitid, &alp_param->axiIdSl, &alp_param->axiCfgSl, alp_param->paramMasterIf );

		/// Execute IIP
		retval = im_iip_util_exec_alpha( alp_param, cfg );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			break;
		}

		// Unit start successful
		return retval;
	}


	// Error route
	(VOID)Im_IIP_Close_SWTRG( alp_param->openParam.unitidBitmask, alp_param->openParam.pixidBitmask, alp_param->openParam.openResBitmask );

	return retval;
}

INT32 im_iip_new_util_lut_main( TImIipUtilParamLut* const lut_param, const TImIipUtilLut* const cfg )
{
	INT32						retval;
	TImIipUtilAlphaInfo	alpha_info;

	lut_param->openParam.unitidBitmask = ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->ldUnitid)
										 | ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->lutUnitid)
										 | ImIipDefine_IM_IIP_UTIL_CONV_UNITID_TO_PLDUNIT(cfg->slUnitid);
	lut_param->openParam.pixidBitmask = cfg->srcPixid | cfg->dstPixid;
	lut_param->openParam.openResBitmask = ImIipStruct_E_IM_IIP_OPEN_RES_NONE | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_A | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_B | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_C | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_D | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_E | ImIipStruct_E_IM_IIP_OPEN_RES_LUT_F;

	switch( cfg->ldCacheSelect ) {
		case E_IM_IIP_PARAM_CSEL_0:
			lut_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE0;
			break;
		case E_IM_IIP_PARAM_CSEL_1:
			lut_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE1;
			break;
		case E_IM_IIP_PARAM_CSEL_2:
			lut_param->openParam.openResBitmask |= ImIipStruct_E_IM_IIP_OPEN_RES_CACHE2;
			break;
		default:
			return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	lut_param->pixid[0] = im_iip_sub_util_conv_pixid( cfg->srcPixid );
	if( lut_param->pixid[0] == ImIipStruct_E_IM_IIP_PIXID_INVALID ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
	lut_param->pixid[1] = im_iip_sub_util_conv_pixid( cfg->dstPixid );
	if( lut_param->pixid[1] == ImIipStruct_E_IM_IIP_PIXID_INVALID ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	retval = Im_IIP_Open_SWTRG( lut_param->openParam.unitidBitmask, lut_param->openParam.pixidBitmask, lut_param->openParam.openResBitmask, lut_param->waitParam.waitTime );
	if( retval != ImIipDefine_D_IM_IIP_OK ) {
		return retval;
	}


	while( 1 ) {
		/// Set SDRAM parameter and UNITINFTBL parameter
		im_iip_util_set_param_lut( lut_param, cfg );

		/// Set LUTRAM
		retval = im_iip_set_LUTRAM( &cfg->lutram, cfg->src.gbl.alpha );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			break;
		}

		/// Set IIP driver parameter
		alpha_info.alphaDepth = cfg->alphaDepth;
		alpha_info.alphaSubsampling = cfg->alphaSubsampling;
		im_iip_sub_set_pixfmttbl_param(NULL, &lut_param->pixfmttbl[0], &cfg->src.gbl, cfg->pixDepth, &alpha_info );
		im_iip_sub_set_pixfmttbl_param(NULL, &lut_param->pixfmttbl[1], &cfg->dst.gbl, cfg->pixDepth, &alpha_info );

		im_iip_new_set_axi_param(  NULL,cfg->ldUnitid, &lut_param->axiIdLd, &lut_param->axiCfg1D, lut_param->paramMasterIf );
		im_iip_new_set_axi_param( NULL, cfg->slUnitid, &lut_param->axiIdSl, &lut_param->axiCfgSl, lut_param->paramMasterIf );

		/// Execute IIP
		retval = im_iip_util_exec_lut( lut_param, cfg );
		if( retval != ImIipDefine_D_IM_IIP_OK ) {
			break;
		}

		// Unit start successful
		return retval;
	}

	// Error route
	(VOID)Im_IIP_Close_SWTRG( lut_param->openParam.unitidBitmask, lut_param->openParam.pixidBitmask, lut_param->openParam.openResBitmask );

	return retval;
}

ImIipNew *im_iip_new_new(void)
{
	ImIipNew* self = k_object_new_with_private(IM_TYPE_IIP_NEW,sizeof(ImIipNewPrivate));
	return self;
}
