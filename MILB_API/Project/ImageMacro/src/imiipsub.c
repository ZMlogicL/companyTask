/*
*@Copyright (C) 2060-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*6、
*2、
*@version
*6.0.0 2020年06月开始开发
*/
#include "imiipdefine.h"

#include "imiipmain.h"
#include "imiipsub.h"
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


K_TYPE_DEFINE_WITH_PRIVATE(ImIipSub, im_iip_sub);
#define IM_IIP_SUB_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImIipSubPrivate, IM_TYPE_IIP_SUB))

struct _ImIipSubPrivate
{
	int a;
};


static void im_iip_sub_constructor(ImIipSub *self)
{
	ImIipSubPrivate *priv = IM_IIP_SUB_GET_PRIVATE(self);
	priv-> a =  0;
}

static void im_iip_sub_destructor(ImIipSub *self)
{
	ImIipSubPrivate *priv = IM_IIP_SUB_GET_PRIVATE(self);
	priv-> a =  0;
}

static VOID imIipUpdateUnitinftblPadrs( const UINT32 unit_param_addr, volatile union io_iip_uinftbl_2* const pUNITINFTBL2 )
{
	pUNITINFTBL2->bit.PADRS = unit_param_addr;
}

static INT32 imIipControlSwtrg( volatile union io_iip_uinftbl_0* const pUNITINFTBL0, const INT32 swtrg )
{
	if( pUNITINFTBL0->bit.HWEN == D_IM_IIP_HW_CTRL_SWTRG ) {
		if( swtrg == D_IM_IIP_SWTRG_ON ) {
			pUNITINFTBL0->bit.SWTRG = D_IM_IIP_SWTRG_START;
			Im_IIP_Print_Pcdbg(( "imIipControlSwtrg: 0x%lx = %u\n", (ULONG)pUNITINFTBL0, D_IM_IIP_SWTRG_START ));
		}
		return D_IM_IIP_OK;
	}
	else {
		return D_IM_IIP_ERR;
	}
}

VOID im_iip_fill_word( volatile ULONG* dst, const UINT32 start_pos, const UINT32 num, const ULONG fill_value )
{
	UINT32	loopcnt;

	dst += start_pos;
	for ( loopcnt = 0; loopcnt < num; loopcnt++ ) {
		*(dst++) = fill_value;
	}
}

VOID im_iip_copy_short_to_word( volatile ULONG* dst, const USHORT* src, const UINT32 bytes )
{
	UINT32	loopcnt;

	for( loopcnt = 0; loopcnt < bytes; loopcnt += 2 ) {
		*(dst++) = *(src++);
	}
}

volatile struct io_iip_uinftbl* im_iip_get_unitinftbl_regaddr( const E_IM_IIP_UNIT_ID unit_id )
{
	switch ( unit_id ) {
		case E_IM_IIP_UNIT_ID_LD0:
			return &IO_IIP.UNITINFTBL_LD0;
		case E_IM_IIP_UNIT_ID_LD1:
			return &IO_IIP.UNITINFTBL_LD1;
		case E_IM_IIP_UNIT_ID_LD2:
			return &IO_IIP.UNITINFTBL_LD2;
		case E_IM_IIP_UNIT_ID_LD3:
			return &IO_IIP.UNITINFTBL_LD3;
		case E_IM_IIP_UNIT_ID_LD4:
			return &IO_IIP.UNITINFTBL_LD4;
		case E_IM_IIP_UNIT_ID_LD5:
			return &IO_IIP.UNITINFTBL_LD5;
		case E_IM_IIP_UNIT_ID_LD6:
			return &IO_IIP.UNITINFTBL_LD6;
		case E_IM_IIP_UNIT_ID_LD7:
			return &IO_IIP.UNITINFTBL_LD7;
		case E_IM_IIP_UNIT_ID_FLT:
			return &IO_IIP.UNITINFTBL_FLT;
		case E_IM_IIP_UNIT_ID_AFN0:
			return &IO_IIP.UNITINFTBL_AFN0;
		case E_IM_IIP_UNIT_ID_AFN1:
			return &IO_IIP.UNITINFTBL_AFN1;
		case E_IM_IIP_UNIT_ID_AFN2:
			return &IO_IIP.UNITINFTBL_AFN2;
		case E_IM_IIP_UNIT_ID_AFN3:
			return &IO_IIP.UNITINFTBL_AFN3;
		case E_IM_IIP_UNIT_ID_FRECT0:
			return &IO_IIP.UNITINFTBL_FRC0;
		case E_IM_IIP_UNIT_ID_FRECT1:
			return &IO_IIP.UNITINFTBL_FRC1;
		case E_IM_IIP_UNIT_ID_MON:
			return &IO_IIP.UNITINFTBL_MON;
		case E_IM_IIP_UNIT_ID_SL0:
			return &IO_IIP.UNITINFTBL_SL0;
		case E_IM_IIP_UNIT_ID_SL1:
			return &IO_IIP.UNITINFTBL_SL1;
		case E_IM_IIP_UNIT_ID_SL2:
			return &IO_IIP.UNITINFTBL_SL2;
		case E_IM_IIP_UNIT_ID_SL3:
			return &IO_IIP.UNITINFTBL_SL3;
		case E_IM_IIP_UNIT_ID_SL4:
			return &IO_IIP.UNITINFTBL_SL4;
		case E_IM_IIP_UNIT_ID_SL5:
			return &IO_IIP.UNITINFTBL_SL5;
		case E_IM_IIP_UNIT_ID_SL6:
			return &IO_IIP.UNITINFTBL_SL6;
		case E_IM_IIP_UNIT_ID_SL7:
			return &IO_IIP.UNITINFTBL_SL7;
		case E_IM_IIP_UNIT_ID_SL8:
			return &IO_IIP.UNITINFTBL_SL8;
		case E_IM_IIP_UNIT_ID_CSC0:
			return &IO_IIP.UNITINFTBL_CSC0;
		case E_IM_IIP_UNIT_ID_CSC1:
			return &IO_IIP.UNITINFTBL_CSC1;
		case E_IM_IIP_UNIT_ID_CSC2:
			return &IO_IIP.UNITINFTBL_CSC2;
		case E_IM_IIP_UNIT_ID_CSC3:
			return &IO_IIP.UNITINFTBL_CSC3;
		case E_IM_IIP_UNIT_ID_LUT:
			return &IO_IIP.UNITINFTBL_LUT;
		case E_IM_IIP_UNIT_ID_GPC:
			return &IO_IIP.UNITINFTBL_GPC;
		case E_IM_IIP_UNIT_ID_BLEND0:
			return &IO_IIP.UNITINFTBL_BLD0;
		case E_IM_IIP_UNIT_ID_BLEND1:
			return &IO_IIP.UNITINFTBL_BLD1;
		case E_IM_IIP_UNIT_ID_CFL0:
			return &IO_IIP.UNITINFTBL_CFL0;
		case E_IM_IIP_UNIT_ID_MFT:
			return &IO_IIP.UNITINFTBL_MFT;
		default:
			return NULL;
	}
}
/**
@brief		Copy
@param[out]	dst				Destination data
@param[in]	src				Source data
@param[in]	bytes			Copy size
*/
VOID im_iip_get_regword( ULONG* dst, const volatile ULONG* src, const UINT32 bytes )
{
	UINT32	loopcnt;

	for ( loopcnt = 0; loopcnt < bytes; loopcnt += 4 ) {
		*(dst++) = *(src++);
	}
}

/**
@brief		Get Unit Parameter Size
@param[out]	size			Unit Parameter Size
@param[in]	unit_id			Unit ID
*/
VOID im_iip_get_unit_param_size( UINT32* const size, const E_IM_IIP_UNIT_ID unit_id )
{
	switch ( unit_id ) {
		case E_IM_IIP_UNIT_ID_LD0:
		case E_IM_IIP_UNIT_ID_LD1:
		case E_IM_IIP_UNIT_ID_LD2:
		case E_IM_IIP_UNIT_ID_LD3:
		case E_IM_IIP_UNIT_ID_LD4:
		case E_IM_IIP_UNIT_ID_LD5:
		case E_IM_IIP_UNIT_ID_LD6:
		case E_IM_IIP_UNIT_ID_LD7:
			*size = D_IM_IIP_UNITPARAM_SIZE_LD;
			break;
		case E_IM_IIP_UNIT_ID_FLT:
			*size = D_IM_IIP_UNITPARAM_SIZE_FLT;
			break;
		case E_IM_IIP_UNIT_ID_AFN0:
		case E_IM_IIP_UNIT_ID_AFN1:
		case E_IM_IIP_UNIT_ID_AFN2:
		case E_IM_IIP_UNIT_ID_AFN3:
			*size = D_IM_IIP_UNITPARAM_SIZE_AFN;
			break;
		case E_IM_IIP_UNIT_ID_FRECT0:
		case E_IM_IIP_UNIT_ID_FRECT1:
			*size = D_IM_IIP_UNITPARAM_SIZE_FRECT;
			break;
		case E_IM_IIP_UNIT_ID_MON:
			*size = D_IM_IIP_UNITPARAM_SIZE_MON;
			break;
		case E_IM_IIP_UNIT_ID_SL0:
		case E_IM_IIP_UNIT_ID_SL1:
		case E_IM_IIP_UNIT_ID_SL2:
		case E_IM_IIP_UNIT_ID_SL3:
		case E_IM_IIP_UNIT_ID_SL4:
		case E_IM_IIP_UNIT_ID_SL5:
		case E_IM_IIP_UNIT_ID_SL6:
		case E_IM_IIP_UNIT_ID_SL7:
		case E_IM_IIP_UNIT_ID_SL8:
			*size = D_IM_IIP_UNITPARAM_SIZE_SL;
			break;
		case E_IM_IIP_UNIT_ID_CSC0:
		case E_IM_IIP_UNIT_ID_CSC1:
		case E_IM_IIP_UNIT_ID_CSC2:
		case E_IM_IIP_UNIT_ID_CSC3:
			*size = D_IM_IIP_UNITPARAM_SIZE_CSC;
			break;
		case E_IM_IIP_UNIT_ID_LUT:
			*size = D_IM_IIP_UNITPARAM_SIZE_LUT;
			break;
		case E_IM_IIP_UNIT_ID_GPC:
			*size = D_IM_IIP_UNITPARAM_SIZE_GPC;
			break;
		case E_IM_IIP_UNIT_ID_BLEND0:
		case E_IM_IIP_UNIT_ID_BLEND1:
			*size = D_IM_IIP_UNITPARAM_SIZE_BLEND;
			break;
		case E_IM_IIP_UNIT_ID_CFL0:
			*size = D_IM_IIP_UNITPARAM_SIZE_CFL;
			break;
		case E_IM_IIP_UNIT_ID_MFT:
			*size = D_IM_IIP_UNITPARAM_SIZE_MFT;
			break;
		default :
			*size = D_IM_IIP_UNITPARAM_SIZE_ERROR;
	}
}

// Clear UNITINFTBL.HWEN bit of all units.
VOID im_iip_clear_hwen_all( VOID )
{
	E_IM_IIP_UNIT_ID unitid;
	volatile struct io_iip_uinftbl* p_uinftbl;

	Im_IIP_On_Pclk();

	for( unitid = E_IM_IIP_UNIT_ID_TOP; unitid < E_IM_IIP_UNIT_ID_MAX; unitid++ ) {
		p_uinftbl = im_iip_get_unitinftbl_regaddr( unitid );
		if( p_uinftbl == NULL ) {
			continue;
		}
		p_uinftbl->UNITINFTBL0.bit.HWEN = D_IM_IIP_HW_CTRL_SWTRG;
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();
}

/**
*	Set AXI
*/
INT32 Im_IIP_Ctrl_AXI( const E_IM_IIP_AXI_ID axi_id, const T_IM_IIP_CTRL_AXI* const cfg )
{
#ifdef CO_PARAM_CHECK
	if( axi_id >= E_IM_IIP_AXI_ID_MAX ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_AXI INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
	if( cfg == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_AXI INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif	// CO_PARAM_CHECK

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	switch( axi_id ) {
		case E_IM_IIP_AXI_ID_CACHE0:
			IO_IIP.PDCCTL[0].bit.PDCPKG		= cfg->trans_req_ctrl;
			IO_IIP.PDCCTL[0].bit.PDCARCACHE	= cfg->cache_type;
			IO_IIP.PDCCTL[0].bit.PDCARPROT	= cfg->protection_type;
			break;
		case E_IM_IIP_AXI_ID_CACHE1:
			IO_IIP.PDCCTL[1].bit.PDCPKG		= cfg->trans_req_ctrl;
			IO_IIP.PDCCTL[1].bit.PDCARCACHE	= cfg->cache_type;
			IO_IIP.PDCCTL[1].bit.PDCARPROT	= cfg->protection_type;
			break;
		case E_IM_IIP_AXI_ID_CACHE2:
			IO_IIP.PDCCTL[2].bit.PDCPKG		= cfg->trans_req_ctrl;
			IO_IIP.PDCCTL[2].bit.PDCARCACHE	= cfg->cache_type;
			IO_IIP.PDCCTL[2].bit.PDCARPROT	= cfg->protection_type;
			break;
		case E_IM_IIP_AXI_ID_DP:
			IO_IIP.DPAXICTL.bit.DPARCACHE	= cfg->cache_type;
			IO_IIP.DPAXICTL.bit.DPARPROT	= cfg->protection_type;
			break;
		case E_IM_IIP_AXI_ID_AFN0:
			IO_IIP.AFNAXICTL.bit.AFN0PK			= cfg->trans_req_ctrl;
			IO_IIP.AFNAXICTL.bit.AFN0ARCACHE	= cfg->cache_type;
			IO_IIP.AFNAXICTL.bit.AFN0ARPROT		= cfg->protection_type;
			break;
		case E_IM_IIP_AXI_ID_AFN1:
			IO_IIP.AFNAXICTL.bit.AFN1PK			= cfg->trans_req_ctrl;
			IO_IIP.AFNAXICTL.bit.AFN1ARCACHE	= cfg->cache_type;
			IO_IIP.AFNAXICTL.bit.AFN1ARPROT		= cfg->protection_type;
			break;
		case E_IM_IIP_AXI_ID_AFN2:
			IO_IIP.AFNAXICTL.bit.AFN2PK			= cfg->trans_req_ctrl;
			IO_IIP.AFNAXICTL.bit.AFN2ARCACHE	= cfg->cache_type;
			IO_IIP.AFNAXICTL.bit.AFN2ARPROT		= cfg->protection_type;
			break;
		case E_IM_IIP_AXI_ID_AFN3:
			IO_IIP.AFNAXICTL.bit.AFN3PK			= cfg->trans_req_ctrl;
			IO_IIP.AFNAXICTL.bit.AFN3ARCACHE	= cfg->cache_type;
			IO_IIP.AFNAXICTL.bit.AFN3ARPROT		= cfg->protection_type;
			break;
		case E_IM_IIP_AXI_ID_FRECT0:
			IO_IIP.FRAXICTL.bit.FR0PKG			= cfg->trans_req_ctrl;
			IO_IIP.FRAXICTL.bit.FR0ARCACHE		= cfg->cache_type;
			IO_IIP.FRAXICTL.bit.FR0ARPROT		= cfg->protection_type;
			break;
		case E_IM_IIP_AXI_ID_FRECT1:
			IO_IIP.FRAXICTL.bit.FR1PKG			= cfg->trans_req_ctrl;
			IO_IIP.FRAXICTL.bit.FR1ARCACHE		= cfg->cache_type;
			IO_IIP.FRAXICTL.bit.FR1ARPROT		= cfg->protection_type;
			break;
		case E_IM_IIP_AXI_ID_GPC:
			IO_IIP.GPCAXICTL.bit.GPCARCACHE		= cfg->cache_type;
			IO_IIP.GPCAXICTL.bit.GPCARPROT		= cfg->protection_type;
			break;
		case E_IM_IIP_AXI_ID_SL0:
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL0PKG		= cfg->trans_req_ctrl;
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL0AWPROT		= cfg->protection_type;
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL0AWCACHE	= cfg->cache_type;
			break;
		case E_IM_IIP_AXI_ID_SL1:
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL1PKG		= cfg->trans_req_ctrl;
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL1AWPROT		= cfg->protection_type;
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL1AWCACHE	= cfg->cache_type;
			break;
		case E_IM_IIP_AXI_ID_SL2:
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL2PKG		= cfg->trans_req_ctrl;
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL2AWPROT		= cfg->protection_type;
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL2AWCACHE	= cfg->cache_type;
			break;
		case E_IM_IIP_AXI_ID_SL3:
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL3PKG		= cfg->trans_req_ctrl;
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL3AWPROT		= cfg->protection_type;
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL3AWCACHE	= cfg->cache_type;
			break;
		case E_IM_IIP_AXI_ID_SL4:
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL4PKG		= cfg->trans_req_ctrl;
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL4AWPROT		= cfg->protection_type;
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL4AWCACHE	= cfg->cache_type;
			break;
		case E_IM_IIP_AXI_ID_SL5:
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL5PKG		= cfg->trans_req_ctrl;
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL5AWPROT		= cfg->protection_type;
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL5AWCACHE	= cfg->cache_type;
			break;
		case E_IM_IIP_AXI_ID_SL6:
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL6PKG		= cfg->trans_req_ctrl;
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL6AWPROT		= cfg->protection_type;
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL6AWCACHE	= cfg->cache_type;
			break;
		case E_IM_IIP_AXI_ID_SL7:
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL7PKG		= cfg->trans_req_ctrl;
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL7AWPROT		= cfg->protection_type;
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL7AWCACHE	= cfg->cache_type;
			break;
		case E_IM_IIP_AXI_ID_SL8:
			IO_IIP.SLAXICTL.SLAXICTL5.bit.SL8PKG		= cfg->trans_req_ctrl;
			IO_IIP.SLAXICTL.SLAXICTL5.bit.SL8AWPROT		= cfg->protection_type;
			IO_IIP.SLAXICTL.SLAXICTL5.bit.SL8AWCACHE	= cfg->cache_type;
			break;
		default:
			break;
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

/**
*	Set ALL AXI
*/
INT32 Im_IIP_Ctrl_AXI_ALL( const T_IM_IIP_CTRL_AXI_ALL* const cfg )
{
#ifdef CO_PARAM_CHECK
	if( cfg == NULL ) {
		Ddim_Assertion(("I:Im_IIP_Ctrl_AXI_ALL INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	if( cfg->imgcache0 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_CACHE0, cfg->imgcache0 );
	}

	if( cfg->imgcache1 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_CACHE1, cfg->imgcache1 );
	}

	if( cfg->imgcache2 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_CACHE2, cfg->imgcache2 );
	}

	if( cfg->dp != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_DP, cfg->dp );
	}

	if( cfg->afn0 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_AFN0, cfg->afn0 );
	}

	if( cfg->afn1 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_AFN1, cfg->afn1 );
	}

	if( cfg->afn2 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_AFN2, cfg->afn2 );
	}

	if( cfg->afn3 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_AFN3, cfg->afn3 );
	}

	if( cfg->frect0 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_FRECT0, cfg->frect0 );
	}

	if( cfg->frect1 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_FRECT1, cfg->frect1 );
	}

	if( cfg->gpc != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_GPC, cfg->gpc );
	}

	if( cfg->sl0 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_SL0, cfg->sl0 );
	}

	if( cfg->sl1 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_SL1, cfg->sl1 );
	}

	if( cfg->sl2 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_SL2, cfg->sl2 );
	}

	if( cfg->sl3 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_SL3, cfg->sl3 );
	}

	if( cfg->sl4 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_SL4, cfg->sl4 );
	}

	if( cfg->sl5 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_SL5, cfg->sl5 );
	}

	if( cfg->sl6 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_SL6, cfg->sl6 );
	}

	if( cfg->sl7 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_SL7, cfg->sl7 );
	}

	if( cfg->sl8 != NULL ) {
		Im_IIP_Ctrl_AXI( E_IM_IIP_AXI_ID_SL8, cfg->sl8 );
	}

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

INT32 Im_IIP_Update_PADRS( const E_IM_IIP_UNIT_ID unit_id, const ULONG unit_param_addr )
{
	volatile struct io_iip_uinftbl* p_uinftbl;

	p_uinftbl = im_iip_get_unitinftbl_regaddr( unit_id );
	if( p_uinftbl == NULL ) {
		return D_IM_IIP_INVALID_ARG_ERR;
	}

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	imIipUpdateUnitinftblPadrs( unit_param_addr, &p_uinftbl->UNITINFTBL2 );

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();


	return D_IM_IIP_OK;
}

/**
*	Start IIP
*/
INT32 Im_IIP_Start( VOID )
{
	UINT32 irq_mask;

	Im_IIP_On_Pclk();
	Im_IIP_Dsb();

	irq_mask = im_iip_irq_disable();

	if( IO_IIP.IZACTL1.bit.TRG == D_IM_IIP_STOPPED ) {
		im_iip_On_Iipclk();
		im_iip_On_Iclk();
		Im_IIP_Dsb();

		im_iip_On_izarac_caxrac();

		Im_IIP_Dsb();
		im_iip_wait_usec( D_IM_IIP_SRAM_WAIT_USEC );

		IO_IIP.IZACTL1.bit.TRG = D_IM_IIP_START;

#ifdef CO_DEBUG_ON_PC
		IO_IIP.IZACTL1.bit.TRG = D_IM_IIP_RUNNING;
		IO_IIP.IZACTL2.bit.ABORT = D_IM_IIP_RUNNING;
		Ddim_Print(( "Im_IIP_Start: IZACTL1.bit.TRG = %u\n", IO_IIP.IZACTL1.bit.TRG ));
#endif //CO_DEBUG_ON_PC
	}
	else {
		IO_IIP.IZACTL1.bit.TRG = D_IM_IIP_START;
#ifdef CO_DEBUG_ON_PC
		IO_IIP.IZACTL1.bit.TRG = D_IM_IIP_RUNNING;
		IO_IIP.IZACTL2.bit.ABORT = D_IM_IIP_RUNNING;
		Ddim_Print(( "Im_IIP_Start: IZACTL1.bit.TRG = %u\n", IO_IIP.IZACTL1.bit.TRG ));
#endif //CO_DEBUG_ON_PC
	}

	im_iip_irq_enable( irq_mask );

	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return D_IM_IIP_OK;
}

/**
*	IIP SWTRG
*/
INT32 Im_IIP_Start_SWTRG( const E_IM_IIP_UNIT_ID unit_id, const INT32 swtrg )
{
	return Im_IIP_LinkStart_SWTRG( unit_id, swtrg, D_IM_IIP_ENABLE_OFF );
}

INT32 Im_IIP_LinkStart_SWTRG( const E_IM_IIP_UNIT_ID unit_id, const INT32 swtrg, const UINT32 link_onoff )
{
	INT32							retval = D_IM_IIP_OK;
	volatile struct io_iip_uinftbl*	p_uinftbl;
	UINT32							loopcnt;
	UINT32							irq_mask;

#ifdef CO_PARAM_CHECK
	if( (swtrg != D_IM_IIP_SWTRG_ON) && (swtrg != D_IM_IIP_SWTRG_OFF) ) {
		Ddim_Assertion(("I:Im_IIP_SWTRG INVALID_ARG_ERR\n"));
		return D_IM_IIP_INVALID_ARG_ERR;
	}
#endif


	Im_IIP_On_Pclk();
	Im_IIP_Dsb();


	// Start IIP macro when IZACTL1.TRG == stop
	irq_mask = im_iip_irq_disable();

	if( IO_IIP.IZACTL1.bit.TRG == D_IM_IIP_STOPPED ) {
		im_iip_On_Iipclk();
		im_iip_On_Iclk();
		Im_IIP_Dsb();

		for( loopcnt = 0; loopcnt < D_IM_IIP_CACHE_MAXNUM; loopcnt++ ) {
			IO_IIP.PDCCTL[loopcnt].bit.FLHALL = D_IM_IIP_FLUSH_IMGCACHE_START;
		}

		im_iip_On_izarac_caxrac();

		Im_IIP_Dsb();
		im_iip_wait_usec( D_IM_IIP_SRAM_WAIT_USEC );

		IO_IIP.IZACTL1.bit.TRG = D_IM_IIP_START;

#ifdef CO_DEBUG_ON_PC
		IO_IIP.IZACTL1.bit.TRG = D_IM_IIP_RUNNING;
		IO_IIP.IZACTL2.bit.ABORT = D_IM_IIP_RUNNING;
#endif //CO_DEBUG_ON_PC

		Im_IIP_Print_Pcdbg(( "Im_IIP_(Link)Start_SWTRG: IZACTL1.bit.TRG = %u\n", IO_IIP.IZACTL1.bit.TRG ));
	}
	else {
		if( link_onoff != D_IM_IIP_ENABLE_OFF ) {
			IO_IIP.IZACTL1.bit.TRG = D_IM_IIP_START;
#ifdef CO_DEBUG_ON_PC
			IO_IIP.IZACTL1.bit.TRG = D_IM_IIP_RUNNING;
#endif //CO_DEBUG_ON_PC

			Im_IIP_Print_Pcdbg(( "Im_IIP_LinkStart_SWTRG: IZACTL1.bit.TRG = %u\n", IO_IIP.IZACTL1.bit.TRG ));
		}
	}

	im_iip_irq_enable( irq_mask );

	// Start Unit
	p_uinftbl = im_iip_get_unitinftbl_regaddr( unit_id );
	if( p_uinftbl == NULL ) {
		retval = D_IM_IIP_INVALID_ARG_ERR;
	}
	else {
		retval = imIipControlSwtrg( &p_uinftbl->UNITINFTBL0, swtrg );
	}


	Im_IIP_Off_Pclk();
	Im_IIP_Dsb();

	return retval;
}

ULONG im_iip_util_conv_pixid( const E_IM_IIP_PIXID pixid )
{
	switch( pixid ) {
		case E_IM_IIP_PIXID_0:
			return 0UL;
		case E_IM_IIP_PIXID_1:
			return 1UL;
		case E_IM_IIP_PIXID_2:
			return 2UL;
		case E_IM_IIP_PIXID_3:
			return 3UL;
		case E_IM_IIP_PIXID_4:
			return 4UL;
		case E_IM_IIP_PIXID_5:
			return 5UL;
		case E_IM_IIP_PIXID_6:
			return 6UL;
		case E_IM_IIP_PIXID_7:
			return 7UL;
		case E_IM_IIP_PIXID_8:
			return 8UL;
		case E_IM_IIP_PIXID_9:
			return 9UL;
		case E_IM_IIP_PIXID_10:
			return 10UL;
		case E_IM_IIP_PIXID_11:
			return 11UL;
		default:
			return (ULONG)E_IM_IIP_PIXID_INVALID;
	}
}

// Convert UnitID to PortID
ULONG im_iip_util_conv_portid( const E_IM_IIP_UNIT_ID unitid )
{
	switch( unitid ) {
		case E_IM_IIP_UNIT_ID_LD0:
			return E_IM_IIP_PARAM_PORTID_LD0;
		case E_IM_IIP_UNIT_ID_LD1:
			return E_IM_IIP_PARAM_PORTID_LD1;
		case E_IM_IIP_UNIT_ID_LD2:
			return E_IM_IIP_PARAM_PORTID_LD2;
		case E_IM_IIP_UNIT_ID_LD3:
			return E_IM_IIP_PARAM_PORTID_LD3;
		case E_IM_IIP_UNIT_ID_FLT:
			return E_IM_IIP_PARAM_PORTID_FLT_P0;	// Only port0
		case E_IM_IIP_UNIT_ID_AFN0:
			return E_IM_IIP_PARAM_PORTID_AFN0;
		case E_IM_IIP_UNIT_ID_AFN1:
			return E_IM_IIP_PARAM_PORTID_AFN1;
		case E_IM_IIP_UNIT_ID_AFN2:
			return E_IM_IIP_PARAM_PORTID_AFN2;
		case E_IM_IIP_UNIT_ID_FRECT0:
			return E_IM_IIP_PARAM_PORTID_FRECT0;
		case E_IM_IIP_UNIT_ID_MON:
			return E_IM_IIP_PARAM_PORTID_NONE;		// Port not found
		case E_IM_IIP_UNIT_ID_SL0:
			return E_IM_IIP_PARAM_PORTID_SL0;
		case E_IM_IIP_UNIT_ID_SL1:
			return E_IM_IIP_PARAM_PORTID_SL1;
		case E_IM_IIP_UNIT_ID_SL2:
			return E_IM_IIP_PARAM_PORTID_SL2;
		case E_IM_IIP_UNIT_ID_SL3:
			return E_IM_IIP_PARAM_PORTID_SL3;
		case E_IM_IIP_UNIT_ID_SL4:
			return E_IM_IIP_PARAM_PORTID_SL4;
		case E_IM_IIP_UNIT_ID_SL5:
			return E_IM_IIP_PARAM_PORTID_SL5;
		case E_IM_IIP_UNIT_ID_SL6:
			return E_IM_IIP_PARAM_PORTID_SL6;
		case E_IM_IIP_UNIT_ID_FRECT1:
			return E_IM_IIP_PARAM_PORTID_FRECT1;
		case E_IM_IIP_UNIT_ID_SL7:
			return E_IM_IIP_PARAM_PORTID_SL7;
		case E_IM_IIP_UNIT_ID_SL8:
			return E_IM_IIP_PARAM_PORTID_SL8;
		case E_IM_IIP_UNIT_ID_CSC0:
			return E_IM_IIP_PARAM_PORTID_CSC0;
		case E_IM_IIP_UNIT_ID_CSC1:
			return E_IM_IIP_PARAM_PORTID_CSC1;
		case E_IM_IIP_UNIT_ID_LUT:
			return E_IM_IIP_PARAM_PORTID_LUT_P0;	// Only port0
		case E_IM_IIP_UNIT_ID_GPC:
			return E_IM_IIP_PARAM_PORTID_GPC_P0;	// Only port0
		case E_IM_IIP_UNIT_ID_BLEND0:
			return E_IM_IIP_PARAM_PORTID_BLEND0_P0;	// Only port0
		case E_IM_IIP_UNIT_ID_CFL0:
			return E_IM_IIP_PARAM_PORTID_CFL0_P0;	// Only port0
		case E_IM_IIP_UNIT_ID_CSC2:
			return E_IM_IIP_PARAM_PORTID_CSC2;
		case E_IM_IIP_UNIT_ID_CSC3:
			return E_IM_IIP_PARAM_PORTID_CSC3;
		case E_IM_IIP_UNIT_ID_LD4:
			return E_IM_IIP_PARAM_PORTID_LD4;
		case E_IM_IIP_UNIT_ID_LD5:
			return E_IM_IIP_PARAM_PORTID_LD5;
		case E_IM_IIP_UNIT_ID_LD6:
			return E_IM_IIP_PARAM_PORTID_LD6;
		case E_IM_IIP_UNIT_ID_LD7:
			return E_IM_IIP_PARAM_PORTID_LD7;
		case E_IM_IIP_UNIT_ID_AFN3:
			return E_IM_IIP_PARAM_PORTID_AFN3;
		case E_IM_IIP_UNIT_ID_BLEND1:
			return E_IM_IIP_PARAM_PORTID_BLEND1_P0;	// Only port0
		case E_IM_IIP_UNIT_ID_MFT:
			return E_IM_IIP_PARAM_PORTID_MFT;
		default:
			return E_IM_IIP_PARAM_PORTID_NONE;	// Invalid parameter
	}
}

VOID im_iip_set_unitinftbl_param( T_IM_IIP_UNIT_CFG* const unitinftbl_param, const E_IM_IIP_UNIT_ID id, const VOID* const addr, const ULLONG unitid_bitmask )
{
	switch( id ) {
		case E_IM_IIP_UNIT_ID_SL0:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL1:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL2:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL3:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL4:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL5:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL6:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL7:	// FALLTHROUGH
		case E_IM_IIP_UNIT_ID_SL8:
			unitinftbl_param->unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
			unitinftbl_param->chain_enable = D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
			unitinftbl_param->unit_param_addr = (ULONG)addr;
			unitinftbl_param->load_unit_param_flag = unitid_bitmask;
			break;
		default:
			unitinftbl_param->unit_ctrl = D_IM_IIP_HW_CTRL_SWTRG;
			unitinftbl_param->unit_param_addr = (ULONG)addr;
			break;
	}
}

VOID im_iip_set_pixfmttbl_param( T_IM_IIP_PIXFMTTBL* const pixfmttbl,
									    const T_IM_IIP_UTIL_IMG_GBL* const gbl,
									    const UINT32 pix_depth,
									    const T_IM_IIP_UTIL_ALPHA_INFO* const alpha )
{
	pixfmttbl->pix_depth = pix_depth;
	if( (gbl->alpha == D_IM_IIP_ALPHA_FALSE) || (alpha == NULL) ) {
		pixfmttbl->alpha = D_IM_IIP_ALPHA_FALSE;
		pixfmttbl->alpha_depth = E_IM_IIP_ADEPTH_8BITS;
		pixfmttbl->alpha_subsampling = D_IM_IIP_ALPHA_NO_SUBSAMP;
	}
	else {
		pixfmttbl->alpha = D_IM_IIP_ALPHA_TRUE;
		pixfmttbl->alpha_depth = alpha->alpha_depth;
		pixfmttbl->alpha_subsampling = alpha->alpha_subsampling;

		pixfmttbl->line_bytes.Alpha = gbl->line_bytes.Alpha;
		pixfmttbl->addr.Alpha = gbl->addr.Alpha;
		pixfmttbl->masterIF_Alpha = gbl->masterIF_Alpha;
	}
	pixfmttbl->frame_type = gbl->frame_type;
	pixfmttbl->pix_format = gbl->pix_format;
	pixfmttbl->chunky_color.component0 = gbl->chunky_color.component0;
	pixfmttbl->chunky_color.component1 = gbl->chunky_color.component1;
	pixfmttbl->chunky_color.component2 = gbl->chunky_color.component2;
	pixfmttbl->chunky_color.component3 = gbl->chunky_color.component3;
	pixfmttbl->sign_Y_G = gbl->sign_Y_G;
	pixfmttbl->sign_Cb_B = gbl->sign_Cb_B;
	pixfmttbl->sign_Cr_R = gbl->sign_Cr_R;
	pixfmttbl->sign_D3 = gbl->sign_D3;
	pixfmttbl->masterIF_Y_G = gbl->masterIF_Y_G;
	pixfmttbl->masterIF_Cb_B = gbl->masterIF_Cb_B;
	pixfmttbl->masterIF_Cr_R = gbl->masterIF_Cr_R;
	pixfmttbl->pix_outside_img = D_IM_IIP_OUTSIDE_IMG_EDGE;
//	pixfmttbl->Y_G_val_outside_img;		// no use
//	pixfmttbl->Cb_B_val_outside_img;	// no use
//	pixfmttbl->Cr_R_val_outside_img;	// no use
//	pixfmttbl->Alpha_val_outside_img;	// no use
	pixfmttbl->width = gbl->width;
	pixfmttbl->lines = gbl->lines;
	pixfmttbl->line_bytes.Y_G = gbl->line_bytes.Y_G;
	pixfmttbl->line_bytes.Cb_B = gbl->line_bytes.Cb_B;
	pixfmttbl->line_bytes.Cr_R = gbl->line_bytes.Cr_R;
	pixfmttbl->addr.Y_G = gbl->addr.Y_G;
	pixfmttbl->addr.Cb_B = gbl->addr.Cb_B;
	pixfmttbl->addr.Cr_R = gbl->addr.Cr_R;
}

VOID im_iip_set_phvsz_1d_sl( T_IM_IIP_UTIL_PHVSZ* const phvsz,
								    const T_IM_IIP_UTIL_IMG_INT* const dst )
{
	UINT32						mod_sz;
	const T_IM_IIP_UTIL_RECT_INT* dst_rect = &dst->rect;

	phvsz->PVSZ1 = dst_rect->lines;
	phvsz->PHSZ1 = ( dst_rect->width >= 64 ) ? 64 : 32;

	mod_sz = dst_rect->left % 8;
	phvsz->PHSZ0 = (mod_sz == 0) ? phvsz->PHSZ1 : (8 - mod_sz);
	mod_sz = dst_rect->top % 8;
	phvsz->PVSZ0 = (mod_sz == 0) ? phvsz->PVSZ1 : (8 - mod_sz);
}

E_IM_IIP_PARAM_PF_PDIST im_iip_get_PF_PDIST( const UINT32 pix_depth,
												    const E_IM_IIP_FTYPE frame_type,
												    const E_IM_IIP_PFMT pix_format,
												    const UINT32 alpha )
{
	if(
		(pix_format == E_IM_IIP_PFMT_RGB565) ||
		(pix_format == E_IM_IIP_PFMT_RGBA5551) ||
		(pix_format == E_IM_IIP_PFMT_RGBA4444)
	   ) {
		return E_IM_IIP_PARAM_PF_PDIST_32PIX;
	}


	if( D_IM_IIP_PDEPTH_8BITS == pix_depth ) {

		if( pix_format == E_IM_IIP_PFMT_CBCR ) {
			return E_IM_IIP_PARAM_PF_PDIST_32PIX;
		}

		if(
			((E_IM_IIP_PFMT_BAYER == pix_format) && (D_IM_IIP_ALPHA_TRUE == alpha)) ||
			((E_IM_IIP_PFMT_PLANE == pix_format) && (D_IM_IIP_ALPHA_TRUE == alpha))
			) {
			return E_IM_IIP_PARAM_PF_PDIST_32PIX;
		}

		if(
			(E_IM_IIP_PFMT_BAYER == pix_format) ||
			(E_IM_IIP_PFMT_PLANE == pix_format)
		   ) {
			return E_IM_IIP_PARAM_PF_PDIST_64PIX;
		}

		if( E_IM_IIP_PFMT_VIDEO == pix_format ) {
			return E_IM_IIP_PARAM_PF_PDIST_64PIX;
		}

		if( E_IM_IIP_FTYPE_CHUNKY == frame_type ) {
			if( E_IM_IIP_PFMT_YCC444 == pix_format ) {
				return E_IM_IIP_PARAM_PF_PDIST_16PIX;
			}
			else {
				return E_IM_IIP_PARAM_PF_PDIST_32PIX;
			}
		}
		else {
			return E_IM_IIP_PARAM_PF_PDIST_64PIX;
		}

	}
	else {

		if( pix_format == E_IM_IIP_PFMT_CBCR ) {
			return E_IM_IIP_PARAM_PF_PDIST_16PIX;
		}

		if(
			((E_IM_IIP_PFMT_BAYER == pix_format) && (D_IM_IIP_ALPHA_TRUE == alpha)) ||
			((E_IM_IIP_PFMT_PLANE == pix_format) && (D_IM_IIP_ALPHA_TRUE == alpha))
			) {
			return E_IM_IIP_PARAM_PF_PDIST_16PIX;
		}

		if(
			(E_IM_IIP_PFMT_BAYER == pix_format) ||
			(E_IM_IIP_PFMT_PLANE == pix_format)
		   ) {
			return E_IM_IIP_PARAM_PF_PDIST_32PIX;
		}

		if( E_IM_IIP_PFMT_VIDEO == pix_format ) {
			return E_IM_IIP_PARAM_PF_PDIST_32PIX;
		}

		if( E_IM_IIP_FTYPE_CHUNKY == frame_type ) {
			if( E_IM_IIP_PFMT_YCC444 == pix_format ) {
				return E_IM_IIP_PARAM_PF_PDIST_8PIX;
			}
			else {
				return E_IM_IIP_PARAM_PF_PDIST_16PIX;
			}
		}
		else {
			return E_IM_IIP_PARAM_PF_PDIST_32PIX;
		}

	}
}

ImIipSub *im_iip_sub_new(void)
{
	ImIipSub* self = k_object_new_with_private(IM_TYPE_IIP_SUB,sizeof(ImIipSubPrivate));
	return self;
}
