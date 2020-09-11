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
	Im_IIP_Dmb();
}

// Enable Interrupt
static UINT32 imIipUtilSetIntFact( const ULLONG unitid_bitmask )
{
	UINT32 int_fact = D_IM_IIP_INT_FACTOR_AXIERR;

	if( unitid_bitmask & D_IM_IIP_PARAM_PLDUNIT_SL0 ) {
		int_fact = D_IM_IIP_INT_FACTOR_SL0END;
	}
	if( unitid_bitmask & D_IM_IIP_PARAM_PLDUNIT_SL1 ) {
		int_fact = D_IM_IIP_INT_FACTOR_SL1END;
	}
	if( unitid_bitmask & D_IM_IIP_PARAM_PLDUNIT_SL2 ) {
		int_fact = D_IM_IIP_INT_FACTOR_SL2END;
	}
	if( unitid_bitmask & D_IM_IIP_PARAM_PLDUNIT_SL3 ) {
		int_fact = D_IM_IIP_INT_FACTOR_SL3END;
	}
	if( unitid_bitmask & D_IM_IIP_PARAM_PLDUNIT_SL4 ) {
		int_fact = D_IM_IIP_INT_FACTOR_SL4END;
	}
	if( unitid_bitmask & D_IM_IIP_PARAM_PLDUNIT_SL5 ) {
		int_fact = D_IM_IIP_INT_FACTOR_SL5END;
	}
	if( unitid_bitmask & D_IM_IIP_PARAM_PLDUNIT_SL6 ) {
		int_fact = D_IM_IIP_INT_FACTOR_SL6END;
	}
	if( unitid_bitmask & D_IM_IIP_PARAM_PLDUNIT_SL7 ) {
		int_fact = D_IM_IIP_INT_FACTOR_SL7END;
	}
	if( unitid_bitmask & D_IM_IIP_PARAM_PLDUNIT_SL8 ) {
		int_fact = D_IM_IIP_INT_FACTOR_SL8END;
	}

	return int_fact;
}

VOID im_iip_set_axi_param( const E_IM_IIP_UNIT_ID unitid, E_IM_IIP_AXI_ID* const axi_id, T_IM_IIP_CTRL_AXI* const axi_cfg, const UCHAR master_IF )
{
	switch( unitid ) {
		case E_IM_IIP_UNIT_ID_AFN0:
			*axi_id = E_IM_IIP_AXI_ID_AFN0;
			break;
		case E_IM_IIP_UNIT_ID_AFN1:
			*axi_id = E_IM_IIP_AXI_ID_AFN1;
			break;
		case E_IM_IIP_UNIT_ID_AFN2:
			*axi_id = E_IM_IIP_AXI_ID_AFN2;
			break;
		case E_IM_IIP_UNIT_ID_AFN3:
			*axi_id = E_IM_IIP_AXI_ID_AFN3;
			break;
		case E_IM_IIP_UNIT_ID_FRECT0:
			*axi_id = E_IM_IIP_AXI_ID_FRECT0;
			break;
		case E_IM_IIP_UNIT_ID_FRECT1:
			*axi_id = E_IM_IIP_AXI_ID_FRECT1;
			break;
		case E_IM_IIP_UNIT_ID_GPC:
			*axi_id = E_IM_IIP_AXI_ID_GPC;
			break;
		case E_IM_IIP_UNIT_ID_SL0:
			*axi_id = E_IM_IIP_AXI_ID_SL0;
			break;
		case E_IM_IIP_UNIT_ID_SL1:
			*axi_id = E_IM_IIP_AXI_ID_SL1;
			break;
		case E_IM_IIP_UNIT_ID_SL2:
			*axi_id = E_IM_IIP_AXI_ID_SL2;
			break;
		case E_IM_IIP_UNIT_ID_SL3:
			*axi_id = E_IM_IIP_AXI_ID_SL3;
			break;
		case E_IM_IIP_UNIT_ID_SL4:
			*axi_id = E_IM_IIP_AXI_ID_SL4;
			break;
		case E_IM_IIP_UNIT_ID_SL5:
			*axi_id = E_IM_IIP_AXI_ID_SL5;
			break;
		case E_IM_IIP_UNIT_ID_SL6:
			*axi_id = E_IM_IIP_AXI_ID_SL6;
			break;
		case E_IM_IIP_UNIT_ID_SL7:
			*axi_id = E_IM_IIP_AXI_ID_SL7;
			break;
		case E_IM_IIP_UNIT_ID_SL8:
			*axi_id = E_IM_IIP_AXI_ID_SL8;
			break;
		default:
			*axi_id = E_IM_IIP_AXI_ID_MAX;		// mean "None"
			return;	// Do nothing
	}

	axi_cfg->trans_req_ctrl = 0;	// register default
	axi_cfg->cache_type = 1;		// register default
	axi_cfg->protection_type = 0;	// register default
}

INT32 im_iip_util_exec_rotate( T_IM_IIP_UTIL_PARAM_RESIZE_ROTATE* const rr_param, const T_IM_IIP_UTIL_RR* const cfg )
{
	INT32	retval;
	UINT32	loopcnt;

	for ( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		retval = Im_IIP_Ctrl_PIXFMTTBL( rr_param->pixid[loopcnt], &rr_param->pixfmttbl[loopcnt] );
		if( retval != D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->afn_unitid, &rr_param->unit_cfg_afn );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->sl_unitid, &rr_param->unit_cfg_sl );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	if( rr_param->axi_id_afn != E_IM_IIP_AXI_ID_MAX ) {
		retval = Im_IIP_Ctrl_AXI( rr_param->axi_id_afn, &rr_param->axi_cfg_afn );
		if( retval != D_IM_IIP_OK ) {
				return retval;
		}
	}

	if( rr_param->axi_id_sl != E_IM_IIP_AXI_ID_MAX ) {
		retval = Im_IIP_Ctrl_AXI( rr_param->axi_id_sl, &rr_param->axi_cfg_sl );
		if( retval != D_IM_IIP_OK ) {
				return retval;
		}
	}

	rr_param->wait_param.int_fact = imIipUtilSetIntFact( rr_param->open_param.unitid_bitmask );

	retval = Im_IIP_Set_Interrupt( rr_param->wait_param.int_fact, 1 );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}


	imIipUtilCleanDcache( rr_param->param_buffer_addr -D_IM_IIP_UTIL_RR_BUF_BYTES, D_IM_IIP_UTIL_RR_BUF_BYTES );


	retval = Im_IIP_Start_SWTRG( cfg->sl_unitid, D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->afn_unitid, D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	return D_IM_IIP_OK;
}

INT32 im_iip_util_exec_csc( T_IM_IIP_UTIL_PARAM_CSC* const csc_param, const T_IM_IIP_UTIL_CSC* const cfg )
{
	INT32	retval;
	UINT32	loopcnt;

	for ( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		retval = Im_IIP_Ctrl_PIXFMTTBL( csc_param->pixid[loopcnt], &csc_param->pixfmttbl[loopcnt] );
		if( retval != D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->ld_unitid, &csc_param->unit_cfg_1d );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->csc_unitid, &csc_param->unit_cfg_csc );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->sl_unitid, &csc_param->unit_cfg_sl );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	if( csc_param->axi_id_ld != E_IM_IIP_AXI_ID_MAX ) {
		retval = Im_IIP_Ctrl_AXI( csc_param->axi_id_ld, &csc_param->axi_cfg_1d );
		if( retval != D_IM_IIP_OK ) {
				return retval;
		}
	}

	if( csc_param->axi_id_sl != E_IM_IIP_AXI_ID_MAX ) {
		retval = Im_IIP_Ctrl_AXI( csc_param->axi_id_sl, &csc_param->axi_cfg_sl );
		if( retval != D_IM_IIP_OK ) {
				return retval;
		}
	}

	csc_param->wait_param.int_fact = imIipUtilSetIntFact( csc_param->open_param.unitid_bitmask );

	retval = Im_IIP_Set_Interrupt( csc_param->wait_param.int_fact, 1 );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}


	imIipUtilCleanDcache( csc_param->param_buffer_addr -D_IM_IIP_UTIL_CSC_BUF_BYTES, D_IM_IIP_UTIL_CSC_BUF_BYTES );


	retval = Im_IIP_Start_SWTRG( cfg->sl_unitid, D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->csc_unitid, D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->ld_unitid, D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	return D_IM_IIP_OK;
}

static INT32 im_iip_util_exec_lut( T_IM_IIP_UTIL_PARAM_LUT* const lut_param, const T_IM_IIP_UTIL_LUT* const cfg )
{
	INT32	retval;
	UINT32	loopcnt;

	for ( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		retval = Im_IIP_Ctrl_PIXFMTTBL( lut_param->pixid[loopcnt], &lut_param->pixfmttbl[loopcnt] );
		if( retval != D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->ld_unitid, &lut_param->unit_cfg_1d );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->lut_unitid, &lut_param->unit_cfg_lut );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->sl_unitid, &lut_param->unit_cfg_sl );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	if( lut_param->axi_id_ld != E_IM_IIP_AXI_ID_MAX ) {
		retval = Im_IIP_Ctrl_AXI( lut_param->axi_id_ld, &lut_param->axi_cfg_1d );
		if( retval != D_IM_IIP_OK ) {
				return retval;
		}
	}

	if( lut_param->axi_id_sl != E_IM_IIP_AXI_ID_MAX ) {
		retval = Im_IIP_Ctrl_AXI( lut_param->axi_id_sl, &lut_param->axi_cfg_sl );
		if( retval != D_IM_IIP_OK ) {
				return retval;
		}
	}

	lut_param->wait_param.int_fact = imIipUtilSetIntFact( lut_param->open_param.unitid_bitmask );

	retval = Im_IIP_Set_Interrupt( lut_param->wait_param.int_fact, 1 );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}


	imIipUtilCleanDcache( lut_param->param_buffer_addr -D_IM_IIP_UTIL_LUT_BUF_BYTES, D_IM_IIP_UTIL_LUT_BUF_BYTES );

#if 0
	{	// Print register for debug.
		extern VOID CT_Im_IIP_Print_Unitcfg_Byid( const E_IM_IIP_UNIT_ID unitid );
		extern VOID CT_Im_IIP_Print_Pixfmttbl_Byid( const E_IM_IIP_PIXID pixid );

		CT_Im_IIP_Print_Unitcfg_Byid( cfg->ld_unitid );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->lut_unitid );
		CT_Im_IIP_Print_Unitcfg_Byid( cfg->sl_unitid );
		CT_Im_IIP_Print_Pixfmttbl_Byid( cfg->src_pixid );
		CT_Im_IIP_Print_Pixfmttbl_Byid( cfg->dst_pixid );
	}
#endif

	retval = Im_IIP_Start_SWTRG( cfg->sl_unitid, D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->lut_unitid, D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->ld_unitid, D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	return D_IM_IIP_OK;
}
/**
@brief		Execute Utility function
*/
static INT32 im_iip_util_exec_alpha( T_IM_IIP_UTIL_PARAM_ALPHA* const alp_param, const T_IM_IIP_UTIL_ALPHABLEND* const cfg )
{
	INT32	retval;
	UINT32	loopcnt;

	for ( loopcnt = 0; loopcnt < 3; loopcnt++ ) {
		retval = Im_IIP_Ctrl_PIXFMTTBL( alp_param->pixid[loopcnt], &alp_param->pixfmttbl[loopcnt] );
		if( retval != D_IM_IIP_OK ) {
			return retval;
		}
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->ld_unitid[0], &alp_param->unit_cfg_1d[0] );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->ld_unitid[1], &alp_param->unit_cfg_1d[1] );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->blend_unitid, &alp_param->unit_cfg_alp );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Ctrl_SWTRG_Unit( cfg->sl_unitid, &alp_param->unit_cfg_sl );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	if( alp_param->axi_id_ld[0] != E_IM_IIP_AXI_ID_MAX ) {
		retval = Im_IIP_Ctrl_AXI( alp_param->axi_id_ld[0], &alp_param->axi_cfg_1d[0] );
		if( retval != D_IM_IIP_OK ) {
				return retval;
		}
	}

	if( alp_param->axi_id_ld[1] != E_IM_IIP_AXI_ID_MAX ) {
		retval = Im_IIP_Ctrl_AXI( alp_param->axi_id_ld[1], &alp_param->axi_cfg_1d[1] );
		if( retval != D_IM_IIP_OK ) {
				return retval;
		}
	}

	if( alp_param->axi_id_sl != E_IM_IIP_AXI_ID_MAX ) {
		retval = Im_IIP_Ctrl_AXI( alp_param->axi_id_sl, &alp_param->axi_cfg_sl );
		if( retval != D_IM_IIP_OK ) {
				return retval;
		}
	}

	alp_param->wait_param.int_fact = imIipUtilSetIntFact( alp_param->open_param.unitid_bitmask );

	retval = Im_IIP_Set_Interrupt( alp_param->wait_param.int_fact, 1 );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}


	imIipUtilCleanDcache( alp_param->param_buffer_addr -D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES, D_IM_IIP_UTIL_ALPHABLEND_BUF_BYTES );


	retval = Im_IIP_Start_SWTRG( cfg->sl_unitid, D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->blend_unitid, D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->ld_unitid[1], D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	retval = Im_IIP_Start_SWTRG( cfg->ld_unitid[0], D_IM_IIP_SWTRG_ON );
	if( retval != D_IM_IIP_OK ) {
			return retval;
	}

	return D_IM_IIP_OK;
}

/**
@brief		Set Alpha unit parameter
@param[out]	alpha			Pointer of ALPHA unit paramter
@param[in]	cfg				Pointer of Alpha parameter
*/
static VOID im_iip_set_alpha_unit_param( T_IM_IIP_PARAM_BLEND* const alpha,
										 const T_IM_IIP_UTIL_ALPHABLEND* const cfg )
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
	if( cfg->dst.gbl.alpha == D_IM_IIP_ALPHA_TRUE ) {
		alpha->BLENDCTL.bit.ALPHA_OUT = cfg->alpha.out;
	}
	else {
		alpha->BLENDCTL.bit.ALPHA_OUT = E_IM_IIP_PARAM_ALPHA_OUT_NONE;
	}

	alpha->ALPHACTL0.bit.ALPHA_STEP = cfg->alpha.step;
	alpha->ALPHACTL0.bit.ALPHA_SEL = cfg->alpha.sel;
	alpha->ALPHACTL1.bit.ALPHA_VAL0 = cfg->alpha.ALPHA_VAL[0];
	alpha->ALPHACTL1.bit.ALPHA_VAL1 = cfg->alpha.ALPHA_VAL[1];
	alpha->ALPHACTL2.bit.ALPHA_VAL2 = cfg->alpha.ALPHA_VAL[2];
	alpha->ALPHACTL2.bit.ALPHA_VAL3 = cfg->alpha.ALPHA_VAL[3];

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
static VOID im_iip_util_set_param_alpha( T_IM_IIP_UTIL_PARAM_ALPHA* const alp_param, const T_IM_IIP_UTIL_ALPHABLEND* const cfg )
{
	T_IM_IIP_PARAM_1DL*			oned[2];
	T_IM_IIP_PARAM_BLEND*		alpha;
	T_IM_IIP_PARAM_STS*			sl;
	T_IM_IIP_UTIL_PHVSZ			phvsz;

	/// Set Pointer of SDRAM parameter

	oned[0] = (T_IM_IIP_PARAM_1DL*)alp_param->param_buffer_addr;
	alp_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_1DL) );

	oned[1] = (T_IM_IIP_PARAM_1DL*)alp_param->param_buffer_addr;
	alp_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_1DL) );

	alpha = (T_IM_IIP_PARAM_BLEND*)alp_param->param_buffer_addr;
	alp_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_BLEND) );

	sl = (T_IM_IIP_PARAM_STS*)alp_param->param_buffer_addr;
	alp_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_STS) );



	/// Set SDRAM paramter
	im_iip_set_phvsz_1d_sl( &phvsz, &cfg->dst );

	im_iip_set_1d_unit_param( oned[0], &phvsz, &cfg->src[0], cfg->pix_depth, cfg->ld_cache_select[0] );
	im_iip_set_1d_unit_param( oned[1], &phvsz, &cfg->src[1], cfg->pix_depth, cfg->ld_cache_select[1] );

	im_iip_set_alpha_unit_param( alpha, cfg );

	im_iip_set_sl_unit_param( sl, &phvsz, &cfg->dst.rect, &cfg->dst.gbl, cfg->pix_depth );

	oned[0]->PIXIDDEF.bit.IPIXID = alp_param->pixid[0];
	oned[0]->LD_TOPCNF0.bit.WAITCONF = im_iip_util_conv_portid( cfg->blend_unitid );

	oned[1]->PIXIDDEF.bit.IPIXID = alp_param->pixid[1];
	oned[1]->LD_TOPCNF0.bit.WAITCONF = im_iip_util_conv_portid_1( cfg->blend_unitid );

	alpha->BLENDTOPCNF0.bit.DATACONF_0 = im_iip_util_conv_portid( cfg->ld_unitid[0] );
	alpha->BLENDTOPCNF1.bit.DATACONF_1 = im_iip_util_conv_portid( cfg->ld_unitid[1] );
	alpha->BLENDTOPCNF0.bit.WAITCONF_0 = im_iip_util_conv_portid( cfg->sl_unitid );

	sl->BASE.PIXIDDEF.bit.OPIXID = alp_param->pixid[2];
	sl->BASE.SL_TOPCNF0.bit.DATACONF = im_iip_util_conv_portid( cfg->blend_unitid );

	alp_param->p_param_1d[0] = oned[0];
	alp_param->p_param_1d[0] = oned[1];
	alp_param->p_param_alp = alpha;
	alp_param->p_param_sl = sl;

	/// Set UNITINFTBL parameter
	im_iip_set_unitinftbl_param( &alp_param->unit_cfg_1d[0], cfg->ld_unitid[0], oned[0], 0ULL );
	im_iip_set_unitinftbl_param( &alp_param->unit_cfg_1d[1], cfg->ld_unitid[1], oned[1], 0ULL );
	im_iip_set_unitinftbl_param( &alp_param->unit_cfg_alp, cfg->blend_unitid, alpha, 0ULL );
	im_iip_set_unitinftbl_param( &alp_param->unit_cfg_sl, cfg->sl_unitid, sl, alp_param->open_param.unitid_bitmask );
}

ULONG im_iip_util_conv_portid_1( const E_IM_IIP_UNIT_ID unitid )
{
	switch( unitid ) {
		case E_IM_IIP_UNIT_ID_FLT:
			return E_IM_IIP_PARAM_PORTID_FLT_P1;
		case E_IM_IIP_UNIT_ID_LUT:
			return E_IM_IIP_PARAM_PORTID_LUT_P1;
		case E_IM_IIP_UNIT_ID_GPC:
			return E_IM_IIP_PARAM_PORTID_GPC_P1;
		case E_IM_IIP_UNIT_ID_BLEND0:
			return E_IM_IIP_PARAM_PORTID_BLEND0_P1;
		case E_IM_IIP_UNIT_ID_CFL0:
			return E_IM_IIP_PARAM_PORTID_CFL0_P1;
		case E_IM_IIP_UNIT_ID_BLEND1:
			return E_IM_IIP_PARAM_PORTID_BLEND1_P1;
		default:
			return E_IM_IIP_PARAM_PORTID_NONE;	// Other unit
	}
}
static INT32 im_iip_set_LUTRAM( const T_IM_IIP_LUTRAM* const lutram,
							    const UINT32 alpha )
{
	T_IM_IIP_LUT			lut;
	INT32					retval = D_IM_IIP_ERR;
	E_IM_IIP_LUTRAM_TYPE	loopcnt;

	for ( loopcnt = E_IM_IIP_LUTRAM_TYPE_A; loopcnt < E_IM_IIP_LUTRAM_TYPE_MAX; loopcnt++ ) {
		lut.buffer_bytes = lutram->buffer_bytes[loopcnt];
		lut.buffer_addr = lutram->buffer_addr[loopcnt];
		lut.lutram_type = loopcnt;
		retval = Im_IIP_Ctrl_LUT( &lut );
		if( retval != D_IM_IIP_OK ) {
			return retval;
		}
	}
	return retval;
}

static VOID im_iip_util_set_param_lut( T_IM_IIP_UTIL_PARAM_LUT* const lut_param, const T_IM_IIP_UTIL_LUT* const cfg )
{
	T_IM_IIP_PARAM_1DL*			oned;
	T_IM_IIP_PARAM_LUT*			lut;
	T_IM_IIP_PARAM_STS*			sl;
	T_IM_IIP_UTIL_PHVSZ			phvsz;

	/// Set Pointer of SDRAM parameter

	oned = (T_IM_IIP_PARAM_1DL*)lut_param->param_buffer_addr;
	lut_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_1DL) );

	lut = (T_IM_IIP_PARAM_LUT*)lut_param->param_buffer_addr;
	lut_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_LUT) );

	sl = (T_IM_IIP_PARAM_STS*)lut_param->param_buffer_addr;
	lut_param->param_buffer_addr += im_iip_roundup_8( sizeof(T_IM_IIP_PARAM_STS) );


	/// Set SDRAM paramter
	im_iip_set_phvsz_1d_sl( &phvsz, &cfg->dst );

	im_iip_set_1d_unit_param( oned, &phvsz, &cfg->src, cfg->pix_depth, cfg->ld_cache_select );

	im_iip_util_set_lut_unit_param( lut, cfg );

	im_iip_set_sl_unit_param( sl, &phvsz, &cfg->dst.rect, &cfg->dst.gbl, cfg->pix_depth );

	oned->PIXIDDEF.bit.IPIXID = lut_param->pixid[0];
	oned->LD_TOPCNF0.bit.WAITCONF = im_iip_util_conv_portid( cfg->lut_unitid );

	lut->LUTTOPCNF[0].bit.DATACONF = im_iip_util_conv_portid( cfg->ld_unitid );
	lut->LUTTOPCNF[0].bit.WAITCONF = im_iip_util_conv_portid( cfg->sl_unitid );

	sl->BASE.PIXIDDEF.bit.OPIXID = lut_param->pixid[1];
	sl->BASE.SL_TOPCNF0.bit.DATACONF = im_iip_util_conv_portid( cfg->lut_unitid );

	lut_param->p_param_1d = oned;
	lut_param->p_param_lut = lut;
	lut_param->p_param_sl = sl;

	im_iip_set_unitinftbl_param( &lut_param->unit_cfg_1d, cfg->ld_unitid, oned, 0ULL );
	im_iip_set_unitinftbl_param( &lut_param->unit_cfg_lut, cfg->lut_unitid, lut, 0ULL );
	im_iip_set_unitinftbl_param( &lut_param->unit_cfg_sl, cfg->sl_unitid, sl, lut_param->open_param.unitid_bitmask );
}

VOID im_iip_util_set_lut_unit_param( T_IM_IIP_PARAM_LUT* const lut,
									   const T_IM_IIP_UTIL_LUT* const cfg )
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
	lut->LUTCTL_A.bit.LUTBIT = cfg->lut_pix_depth[0];
	lut->LUTCTL_A.bit.USE = E_IM_IIP_PARAM_LUTUSE_LUT_OUT;
	lut->LUTCTL_A.bit.SGN = cfg->src.gbl.sign_Y_G;
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
	lut->LUTCTL_B.bit.LUTBIT = cfg->lut_pix_depth[1];
	lut->LUTCTL_B.bit.USE = E_IM_IIP_PARAM_LUTUSE_LUT_OUT;
	lut->LUTCTL_B.bit.SGN = cfg->src.gbl.sign_Cb_B;
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
	lut->LUTCTL_C.bit.LUTBIT = cfg->lut_pix_depth[2];
	lut->LUTCTL_C.bit.USE = E_IM_IIP_PARAM_LUTUSE_LUT_OUT;
	lut->LUTCTL_C.bit.SGN = cfg->src.gbl.sign_Cr_R;
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
	lut->LUTCTL_D.bit.LUTBIT = cfg->lut_pix_depth[3];
	lut->LUTCTL_D.bit.USE = E_IM_IIP_PARAM_LUTUSE_PRECALC;
	lut->LUTCTL_D.bit.SGN = cfg->src.gbl.sign_D3;
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
	lut->LUTCTL_E.bit.LUTBIT = cfg->lut_pix_depth[0];
	lut->LUTCTL_E.bit.USE = E_IM_IIP_PARAM_LUTUSE_PRECALC;
	lut->LUTCTL_E.bit.SGN = cfg->src.gbl.sign_Y_G;
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
	lut->LUTCTL_F.bit.LUTBIT = cfg->lut_pix_depth[1];
	lut->LUTCTL_F.bit.USE = E_IM_IIP_PARAM_LUTUSE_PRECALC;
	lut->LUTCTL_F.bit.SGN = cfg->src.gbl.sign_Cb_B;
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
INT32 im_iip_util_alpha_main( T_IM_IIP_UTIL_PARAM_ALPHA* const alp_param, const T_IM_IIP_UTIL_ALPHABLEND* const cfg )
{
	INT32						retval;
	T_IM_IIP_UTIL_ALPHA_INFO	alpha_info;

	alp_param->open_param.unitid_bitmask = im_iip_util_conv_unitid_to_pldunit(cfg->ld_unitid[0])
										 | im_iip_util_conv_unitid_to_pldunit(cfg->ld_unitid[1])
										 | im_iip_util_conv_unitid_to_pldunit(cfg->blend_unitid)
										 | im_iip_util_conv_unitid_to_pldunit(cfg->sl_unitid);
	alp_param->open_param.pixid_bitmask = cfg->src_pixid[0] | cfg->src_pixid[1] | cfg->dst_pixid;
	alp_param->open_param.open_res_bitmask = E_IM_IIP_OPEN_RES_NONE;

	switch( cfg->ld_cache_select[0] ) {
		case E_IM_IIP_PARAM_CSEL_0:
			alp_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE0;
			break;
		case E_IM_IIP_PARAM_CSEL_1:
			alp_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE1;
			break;
		case E_IM_IIP_PARAM_CSEL_2:
			alp_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE2;
			break;
		default:
			return D_IM_IIP_INVALID_ARG_ERR;
	}

	switch( cfg->ld_cache_select[1] ) {
		case E_IM_IIP_PARAM_CSEL_0:
			alp_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE0;
			break;
		case E_IM_IIP_PARAM_CSEL_1:
			alp_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE1;
			break;
		case E_IM_IIP_PARAM_CSEL_2:
			alp_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE2;
			break;
		default:
			return D_IM_IIP_INVALID_ARG_ERR;
	}

	alp_param->pixid[0] = im_iip_util_conv_pixid( cfg->src_pixid[0] );
	if( alp_param->pixid[0] == E_IM_IIP_PIXID_INVALID ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}
	alp_param->pixid[1] = im_iip_util_conv_pixid( cfg->src_pixid[1] );
	if( alp_param->pixid[1] == E_IM_IIP_PIXID_INVALID ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}
	alp_param->pixid[2] = im_iip_util_conv_pixid( cfg->dst_pixid );
	if( alp_param->pixid[2] == E_IM_IIP_PIXID_INVALID ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}

	retval = Im_IIP_Open_SWTRG( alp_param->open_param.unitid_bitmask, alp_param->open_param.pixid_bitmask, alp_param->open_param.open_res_bitmask, alp_param->wait_param.wait_time );
	if( retval != D_IM_IIP_OK ) {
		return retval;
	}


	while( 1 ) {
		/// Set SDRAM parameter and UNITINFTBL parameter
		im_iip_util_set_param_alpha( alp_param, cfg );

		/// Set IIP driver parameter
		alpha_info.alpha_depth = cfg->alpha_depth;
		alpha_info.alpha_subsampling = cfg->alpha_subsampling;
		im_iip_set_pixfmttbl_param( &alp_param->pixfmttbl[0], &cfg->src[0].gbl, cfg->pix_depth, &alpha_info );
		im_iip_set_pixfmttbl_param( &alp_param->pixfmttbl[1], &cfg->src[1].gbl, cfg->pix_depth, &alpha_info );
		im_iip_set_pixfmttbl_param( &alp_param->pixfmttbl[2], &cfg->dst.gbl,    cfg->pix_depth, &alpha_info );

		im_iip_set_axi_param( cfg->ld_unitid[0], &alp_param->axi_id_ld[0], &alp_param->axi_cfg_1d[0], alp_param->param_master_IF );
		im_iip_set_axi_param( cfg->ld_unitid[1], &alp_param->axi_id_ld[1], &alp_param->axi_cfg_1d[1], alp_param->param_master_IF );
		im_iip_set_axi_param( cfg->sl_unitid, &alp_param->axi_id_sl, &alp_param->axi_cfg_sl, alp_param->param_master_IF );

		/// Execute IIP
		retval = im_iip_util_exec_alpha( alp_param, cfg );
		if( retval != D_IM_IIP_OK ) {
			break;
		}

		// Unit start successful
		return retval;
	}


	// Error route
	(VOID)Im_IIP_Close_SWTRG( alp_param->open_param.unitid_bitmask, alp_param->open_param.pixid_bitmask, alp_param->open_param.open_res_bitmask );

	return retval;
}

INT32 im_iip_util_lut_main( T_IM_IIP_UTIL_PARAM_LUT* const lut_param, const T_IM_IIP_UTIL_LUT* const cfg )
{
	INT32						retval;
	T_IM_IIP_UTIL_ALPHA_INFO	alpha_info;

	lut_param->open_param.unitid_bitmask = im_iip_util_conv_unitid_to_pldunit(cfg->ld_unitid)
										 | im_iip_util_conv_unitid_to_pldunit(cfg->lut_unitid)
										 | im_iip_util_conv_unitid_to_pldunit(cfg->sl_unitid);
	lut_param->open_param.pixid_bitmask = cfg->src_pixid | cfg->dst_pixid;
	lut_param->open_param.open_res_bitmask = E_IM_IIP_OPEN_RES_NONE | E_IM_IIP_OPEN_RES_LUT_A | E_IM_IIP_OPEN_RES_LUT_B | E_IM_IIP_OPEN_RES_LUT_C | E_IM_IIP_OPEN_RES_LUT_D | E_IM_IIP_OPEN_RES_LUT_E | E_IM_IIP_OPEN_RES_LUT_F;

	switch( cfg->ld_cache_select ) {
		case E_IM_IIP_PARAM_CSEL_0:
			lut_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE0;
			break;
		case E_IM_IIP_PARAM_CSEL_1:
			lut_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE1;
			break;
		case E_IM_IIP_PARAM_CSEL_2:
			lut_param->open_param.open_res_bitmask |= E_IM_IIP_OPEN_RES_CACHE2;
			break;
		default:
			return D_IM_IIP_INVALID_ARG_ERR;
	}

	lut_param->pixid[0] = im_iip_util_conv_pixid( cfg->src_pixid );
	if( lut_param->pixid[0] == E_IM_IIP_PIXID_INVALID ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}
	lut_param->pixid[1] = im_iip_util_conv_pixid( cfg->dst_pixid );
	if( lut_param->pixid[1] == E_IM_IIP_PIXID_INVALID ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}

	retval = Im_IIP_Open_SWTRG( lut_param->open_param.unitid_bitmask, lut_param->open_param.pixid_bitmask, lut_param->open_param.open_res_bitmask, lut_param->wait_param.wait_time );
	if( retval != D_IM_IIP_OK ) {
		return retval;
	}


	while( 1 ) {
		/// Set SDRAM parameter and UNITINFTBL parameter
		im_iip_util_set_param_lut( lut_param, cfg );

		/// Set LUTRAM
		retval = im_iip_set_LUTRAM( &cfg->lutram, cfg->src.gbl.alpha );
		if( retval != D_IM_IIP_OK ) {
			break;
		}

		/// Set IIP driver parameter
		alpha_info.alpha_depth = cfg->alpha_depth;
		alpha_info.alpha_subsampling = cfg->alpha_subsampling;
		im_iip_set_pixfmttbl_param( &lut_param->pixfmttbl[0], &cfg->src.gbl, cfg->pix_depth, &alpha_info );
		im_iip_set_pixfmttbl_param( &lut_param->pixfmttbl[1], &cfg->dst.gbl, cfg->pix_depth, &alpha_info );

		im_iip_set_axi_param( cfg->ld_unitid, &lut_param->axi_id_ld, &lut_param->axi_cfg_1d, lut_param->param_master_IF );
		im_iip_set_axi_param( cfg->sl_unitid, &lut_param->axi_id_sl, &lut_param->axi_cfg_sl, lut_param->param_master_IF );

		/// Execute IIP
		retval = im_iip_util_exec_lut( lut_param, cfg );
		if( retval != D_IM_IIP_OK ) {
			break;
		}

		// Unit start successful
		return retval;
	}

	// Error route
	(VOID)Im_IIP_Close_SWTRG( lut_param->open_param.unitid_bitmask, lut_param->open_param.pixid_bitmask, lut_param->open_param.open_res_bitmask );

	return retval;
}

ImIipNew *im_iip_new_new(void)
{
	ImIipNew* self = k_object_new_with_private(IM_TYPE_IIP_NEW,sizeof(ImIipNewPrivate));
	return self;
}
