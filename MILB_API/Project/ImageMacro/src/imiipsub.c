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

static VOID imIipUpdateUnitinftblPadrs( const UINT32 unitParamAddr, volatile union io_iip_uinftbl_2* const pUNITINFTBL2 )
{
	pUNITINFTBL2->bit.PADRS = unitParamAddr;
}

static INT32 imIipControlSwtrg( volatile union io_iip_uinftbl_0* const pUNITINFTBL0, const INT32 swtrg )
{
	if( pUNITINFTBL0->bit.HWEN == ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG ) {
		if( swtrg == ImIipDefine_D_IM_IIP_SWTRG_ON ) {
			pUNITINFTBL0->bit.SWTRG = ImIipDefine_D_IM_IIP_SWTRG_START;
			ImIipDefine_IM_IIP_PRINT_PCDBG(( "imIipControlSwtrg: 0x%lx = %u\n", (ULONG)pUNITINFTBL0, ImIipDefine_D_IM_IIP_SWTRG_START ));
		}
		return ImIipDefine_D_IM_IIP_OK;
	}
	else {
		return ImIipDefine_D_IM_IIP_ERR;
	}
}

VOID im_iip_sub_fill_word( ImIipDefine* self, volatile ULONG* dst, const UINT32 start_pos, const UINT32 num, const ULONG fill_value )
{
	UINT32	loopcnt;

	dst += start_pos;
	for ( loopcnt = 0; loopcnt < num; loopcnt++ ) {
		*(dst++) = fill_value;
	}
}

VOID im_iip_sub_copy_short_to_word( ImIipDefine* self, volatile ULONG* dst, const USHORT* src, const UINT32 bytes )
{
	UINT32	loopcnt;

	for( loopcnt = 0; loopcnt < bytes; loopcnt += 2 ) {
		*(dst++) = *(src++);
	}
}

volatile struct io_iip_uinftbl* im_iip_sun_get_unitinftbl_regaddr( const EImIipUnitId unitId )
{
	switch ( unitId ) {
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD0:
			return &IO_IIP.UNITINFTBL_LD0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD1:
			return &IO_IIP.UNITINFTBL_LD1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD2:
			return &IO_IIP.UNITINFTBL_LD2;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD3:
			return &IO_IIP.UNITINFTBL_LD3;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD4:
			return &IO_IIP.UNITINFTBL_LD4;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD5:
			return &IO_IIP.UNITINFTBL_LD5;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD6:
			return &IO_IIP.UNITINFTBL_LD6;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD7:
			return &IO_IIP.UNITINFTBL_LD7;
		case ImIipStruct_E_IM_IIP_UNIT_ID_FLT:
			return &IO_IIP.UNITINFTBL_FLT;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN0:
			return &IO_IIP.UNITINFTBL_AFN0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN1:
			return &IO_IIP.UNITINFTBL_AFN1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN2:
			return &IO_IIP.UNITINFTBL_AFN2;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN3:
			return &IO_IIP.UNITINFTBL_AFN3;
		case ImIipStruct_E_IM_IIP_UNIT_ID_FRECT0:
			return &IO_IIP.UNITINFTBL_FRC0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_FRECT1:
			return &IO_IIP.UNITINFTBL_FRC1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_MON:
			return &IO_IIP.UNITINFTBL_MON;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL0:
			return &IO_IIP.UNITINFTBL_SL0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL1:
			return &IO_IIP.UNITINFTBL_SL1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL2:
			return &IO_IIP.UNITINFTBL_SL2;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL3:
			return &IO_IIP.UNITINFTBL_SL3;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL4:
			return &IO_IIP.UNITINFTBL_SL4;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL5:
			return &IO_IIP.UNITINFTBL_SL5;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL6:
			return &IO_IIP.UNITINFTBL_SL6;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL7:
			return &IO_IIP.UNITINFTBL_SL7;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL8:
			return &IO_IIP.UNITINFTBL_SL8;
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC0:
			return &IO_IIP.UNITINFTBL_CSC0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC1:
			return &IO_IIP.UNITINFTBL_CSC1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC2:
			return &IO_IIP.UNITINFTBL_CSC2;
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC3:
			return &IO_IIP.UNITINFTBL_CSC3;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LUT:
			return &IO_IIP.UNITINFTBL_LUT;
		case ImIipStruct_E_IM_IIP_UNIT_ID_GPC:
			return &IO_IIP.UNITINFTBL_GPC;
		case ImIipStruct_E_IM_IIP_UNIT_ID_BLEND0:
			return &IO_IIP.UNITINFTBL_BLD0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_BLEND1:
			return &IO_IIP.UNITINFTBL_BLD1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_CFL0:
			return &IO_IIP.UNITINFTBL_CFL0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_MFT:
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
VOID im_iip_sub_get_regword( ImIipDefine* self, ULONG* dst, const volatile ULONG* src, const UINT32 bytes )
{
	UINT32	loopcnt;

	for ( loopcnt = 0; loopcnt < bytes; loopcnt += 4 ) {
		*(dst++) = *(src++);
	}
}

/**
@brief		Get Unit Parameter Size
@param[out]	size			Unit Parameter Size
@param[in]	unitId			Unit ID
*/
VOID im_iip_sub_get_unit_param_size(ImIipDefine* self, UINT32* const size, const EImIipUnitId unitId )
{
	switch ( unitId ) {
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD0:
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD1:
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD2:
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD3:
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD4:
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD5:
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD6:
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD7:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_LD;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_FLT:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_FLT;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN0:
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN1:
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN2:
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN3:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_AFN;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_FRECT0:
		case ImIipStruct_E_IM_IIP_UNIT_ID_FRECT1:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_FRECT;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_MON:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_MON;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL0:
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL1:
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL2:
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL3:
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL4:
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL5:
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL6:
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL7:
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL8:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_SL;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC0:
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC1:
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC2:
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC3:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_CSC;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LUT:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_LUT;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_GPC:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_GPC;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_BLEND0:
		case ImIipStruct_E_IM_IIP_UNIT_ID_BLEND1:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_BLEND;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_CFL0:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_CFL;
			break;
		case ImIipStruct_E_IM_IIP_UNIT_ID_MFT:
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_MFT;
			break;
		default :
			*size = ImIipDefine_D_IM_IIP_UNITPARAM_SIZE_ERROR;
	}
}

// Clear UNITINFTBL.HWEN bit of all units.
VOID im_iip_sub_clear_hwen_all( ImIipDefine* self )
{
	EImIipUnitId unitid;
	volatile struct io_iip_uinftbl* p_uinftbl;

	Im_IIP_On_Pclk();

	for( unitid = ImIipStruct_E_IM_IIP_UNIT_ID_TOP; unitid < ImIipStruct_E_IM_IIP_UNIT_ID_MAX; unitid++ ) {
		p_uinftbl = im_iip_sun_get_unitinftbl_regaddr( unitid );
		if( p_uinftbl == NULL ) {
			continue;
		}
		p_uinftbl->UNITINFTBL0.bit.HWEN = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
	}

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();
}

/**
*	Set AXI
*/
INT32 im_iip_sub_ctrl_axi( const EImIipAxiId axi_id, const TIMIipCtrlAxi* const cfg )
{
#ifdef ImIipStruct_CO_PARAM_CHECK
	if( axi_id >= ImIipStruct_E_IM_IIP_AXI_ID_MAX ) {
		Ddim_Assertion(("I:im_iip_sub_ctrl_axi INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
	if( cfg == NULL ) {
		Ddim_Assertion(("I:im_iip_sub_ctrl_axi INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif	// ImIipStruct_CO_PARAM_CHECK

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	switch( axi_id ) {
		case ImIipStruct_E_IM_IIP_AXI_ID_CACHE0:
			IO_IIP.PDCCTL[0].bit.PDCPKG		= cfg->transReqCtrl;
			IO_IIP.PDCCTL[0].bit.PDCARCACHE	= cfg->cacheType;
			IO_IIP.PDCCTL[0].bit.PDCARPROT	= cfg->protectionType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_CACHE1:
			IO_IIP.PDCCTL[1].bit.PDCPKG		= cfg->transReqCtrl;
			IO_IIP.PDCCTL[1].bit.PDCARCACHE	= cfg->cacheType;
			IO_IIP.PDCCTL[1].bit.PDCARPROT	= cfg->protectionType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_CACHE2:
			IO_IIP.PDCCTL[2].bit.PDCPKG		= cfg->transReqCtrl;
			IO_IIP.PDCCTL[2].bit.PDCARCACHE	= cfg->cacheType;
			IO_IIP.PDCCTL[2].bit.PDCARPROT	= cfg->protectionType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_DP:
			IO_IIP.DPAXICTL.bit.DPARCACHE	= cfg->cacheType;
			IO_IIP.DPAXICTL.bit.DPARPROT	= cfg->protectionType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_AFN0:
			IO_IIP.AFNAXICTL.bit.AFN0PK			= cfg->transReqCtrl;
			IO_IIP.AFNAXICTL.bit.AFN0ARCACHE	= cfg->cacheType;
			IO_IIP.AFNAXICTL.bit.AFN0ARPROT		= cfg->protectionType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_AFN1:
			IO_IIP.AFNAXICTL.bit.AFN1PK			= cfg->transReqCtrl;
			IO_IIP.AFNAXICTL.bit.AFN1ARCACHE	= cfg->cacheType;
			IO_IIP.AFNAXICTL.bit.AFN1ARPROT		= cfg->protectionType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_AFN2:
			IO_IIP.AFNAXICTL.bit.AFN2PK			= cfg->transReqCtrl;
			IO_IIP.AFNAXICTL.bit.AFN2ARCACHE	= cfg->cacheType;
			IO_IIP.AFNAXICTL.bit.AFN2ARPROT		= cfg->protectionType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_AFN3:
			IO_IIP.AFNAXICTL.bit.AFN3PK			= cfg->transReqCtrl;
			IO_IIP.AFNAXICTL.bit.AFN3ARCACHE	= cfg->cacheType;
			IO_IIP.AFNAXICTL.bit.AFN3ARPROT		= cfg->protectionType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_FRECT0:
			IO_IIP.FRAXICTL.bit.FR0PKG			= cfg->transReqCtrl;
			IO_IIP.FRAXICTL.bit.FR0ARCACHE		= cfg->cacheType;
			IO_IIP.FRAXICTL.bit.FR0ARPROT		= cfg->protectionType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_FRECT1:
			IO_IIP.FRAXICTL.bit.FR1PKG			= cfg->transReqCtrl;
			IO_IIP.FRAXICTL.bit.FR1ARCACHE		= cfg->cacheType;
			IO_IIP.FRAXICTL.bit.FR1ARPROT		= cfg->protectionType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_GPC:
			IO_IIP.GPCAXICTL.bit.GPCARCACHE		= cfg->cacheType;
			IO_IIP.GPCAXICTL.bit.GPCARPROT		= cfg->protectionType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_SL0:
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL0PKG		= cfg->transReqCtrl;
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL0AWPROT		= cfg->protectionType;
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL0AWCACHE	= cfg->cacheType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_SL1:
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL1PKG		= cfg->transReqCtrl;
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL1AWPROT		= cfg->protectionType;
			IO_IIP.SLAXICTL.SLAXICTL1.bit.SL1AWCACHE	= cfg->cacheType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_SL2:
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL2PKG		= cfg->transReqCtrl;
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL2AWPROT		= cfg->protectionType;
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL2AWCACHE	= cfg->cacheType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_SL3:
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL3PKG		= cfg->transReqCtrl;
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL3AWPROT		= cfg->protectionType;
			IO_IIP.SLAXICTL.SLAXICTL2.bit.SL3AWCACHE	= cfg->cacheType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_SL4:
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL4PKG		= cfg->transReqCtrl;
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL4AWPROT		= cfg->protectionType;
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL4AWCACHE	= cfg->cacheType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_SL5:
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL5PKG		= cfg->transReqCtrl;
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL5AWPROT		= cfg->protectionType;
			IO_IIP.SLAXICTL.SLAXICTL3.bit.SL5AWCACHE	= cfg->cacheType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_SL6:
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL6PKG		= cfg->transReqCtrl;
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL6AWPROT		= cfg->protectionType;
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL6AWCACHE	= cfg->cacheType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_SL7:
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL7PKG		= cfg->transReqCtrl;
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL7AWPROT		= cfg->protectionType;
			IO_IIP.SLAXICTL.SLAXICTL4.bit.SL7AWCACHE	= cfg->cacheType;
			break;
		case ImIipStruct_E_IM_IIP_AXI_ID_SL8:
			IO_IIP.SLAXICTL.SLAXICTL5.bit.SL8PKG		= cfg->transReqCtrl;
			IO_IIP.SLAXICTL.SLAXICTL5.bit.SL8AWPROT		= cfg->protectionType;
			IO_IIP.SLAXICTL.SLAXICTL5.bit.SL8AWCACHE	= cfg->cacheType;
			break;
		default:
			break;
	}

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

/**
*	Set ALL AXI
*/
INT32 im_iip_sub_ctrl_axi_all( const TIMIipCtrlAxiAll* const cfg )
{
#ifdef ImIipStruct_CO_PARAM_CHECK
	if( cfg == NULL ) {
		Ddim_Assertion(("I:im_iip_sub_ctrl_axi_all INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	if( cfg->imgcache0 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_CACHE0, cfg->imgcache0 );
	}

	if( cfg->imgcache1 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_CACHE1, cfg->imgcache1 );
	}

	if( cfg->imgcache2 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_CACHE2, cfg->imgcache2 );
	}

	if( cfg->dp != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_DP, cfg->dp );
	}

	if( cfg->afn0 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_AFN0, cfg->afn0 );
	}

	if( cfg->afn1 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_AFN1, cfg->afn1 );
	}

	if( cfg->afn2 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_AFN2, cfg->afn2 );
	}

	if( cfg->afn3 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_AFN3, cfg->afn3 );
	}

	if( cfg->frect0 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_FRECT0, cfg->frect0 );
	}

	if( cfg->frect1 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_FRECT1, cfg->frect1 );
	}

	if( cfg->gpc != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_GPC, cfg->gpc );
	}

	if( cfg->sl0 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_SL0, cfg->sl0 );
	}

	if( cfg->sl1 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_SL1, cfg->sl1 );
	}

	if( cfg->sl2 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_SL2, cfg->sl2 );
	}

	if( cfg->sl3 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_SL3, cfg->sl3 );
	}

	if( cfg->sl4 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_SL4, cfg->sl4 );
	}

	if( cfg->sl5 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_SL5, cfg->sl5 );
	}

	if( cfg->sl6 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_SL6, cfg->sl6 );
	}

	if( cfg->sl7 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_SL7, cfg->sl7 );
	}

	if( cfg->sl8 != NULL ) {
		im_iip_sub_ctrl_axi( ImIipStruct_E_IM_IIP_AXI_ID_SL8, cfg->sl8 );
	}

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

INT32 im_iip_sub_update_padrs( const EImIipUnitId unitId, const ULONG unitParamAddr )
{
	volatile struct io_iip_uinftbl* p_uinftbl;

	p_uinftbl = im_iip_sun_get_unitinftbl_regaddr( unitId );
	if( p_uinftbl == NULL ) {
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	imIipUpdateUnitinftblPadrs( unitParamAddr, &p_uinftbl->UNITINFTBL2 );

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();


	return ImIipDefine_D_IM_IIP_OK;
}

/**
*	Start IIP
*/
INT32 im_iip_sub_start( VOID )
{
	UINT32 irq_mask;

	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();

	irq_mask = im_iip_static_irq_disable();

	if( IO_IIP.IZACTL1.bit.TRG == ImIipDefine_D_IM_IIP_STOPPED ) {
		im_iip_counter_on_lipclk(NULL);
		im_iip_struct_on_lclk(NULL);
		ImIipDefine_IM_IIP_DSB();

		im_iip_counter_on_izarac_caxrac(NULL);

		ImIipDefine_IM_IIP_DSB();
		ImIipDefine_IM_IIP_WAIT_USEC( ImIipDefine_D_IM_IIP_SRAM_WAIT_USEC );

		IO_IIP.IZACTL1.bit.TRG = ImIipDefine_D_IM_IIP_START;

#ifdef CO_DEBUG_ON_PC
		IO_IIP.IZACTL1.bit.TRG = ImIipDefine_D_IM_IIP_RUNNING;
		IO_IIP.IZACTL2.bit.ABORT = ImIipDefine_D_IM_IIP_RUNNING;
		Ddim_Print(( "im_iip_sub_start: IZACTL1.bit.TRG = %u\n", IO_IIP.IZACTL1.bit.TRG ));
#endif //CO_DEBUG_ON_PC
	}
	else {
		IO_IIP.IZACTL1.bit.TRG = ImIipDefine_D_IM_IIP_START;
#ifdef CO_DEBUG_ON_PC
		IO_IIP.IZACTL1.bit.TRG = ImIipDefine_D_IM_IIP_RUNNING;
		IO_IIP.IZACTL2.bit.ABORT = ImIipDefine_D_IM_IIP_RUNNING;
		Ddim_Print(( "im_iip_sub_start: IZACTL1.bit.TRG = %u\n", IO_IIP.IZACTL1.bit.TRG ));
#endif //CO_DEBUG_ON_PC
	}

	im_iip_static_irq_enable( NULL,irq_mask );

	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return ImIipDefine_D_IM_IIP_OK;
}

/**
*	IIP SWTRG
*/
INT32 Im_IIP_Start_SWTRG( const EImIipUnitId unitId, const INT32 swtrg )
{
	return Im_IIP_LinkStart_SWTRG( unitId, swtrg, ImIipDefine_D_IM_IIP_ENABLE_OFF );
}

INT32 Im_IIP_LinkStart_SWTRG( const EImIipUnitId unitId, const INT32 swtrg, const UINT32 link_onoff )
{
	INT32							retval = ImIipDefine_D_IM_IIP_OK;
	volatile struct io_iip_uinftbl*	p_uinftbl;
	UINT32							loopcnt;
	UINT32							irq_mask;

#ifdef ImIipStruct_CO_PARAM_CHECK
	if( (swtrg != ImIipDefine_D_IM_IIP_SWTRG_ON) && (swtrg != ImIipDefine_D_IM_IIP_SWTRG_OFF) ) {
		Ddim_Assertion(("I:Im_IIP_SWTRG INVALID_ARG_ERR\n"));
		return ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
#endif


	Im_IIP_On_Pclk();
	ImIipDefine_IM_IIP_DSB();


	// Start IIP macro when IZACTL1.TRG == stop
	irq_mask = im_iip_static_irq_disable();

	if( IO_IIP.IZACTL1.bit.TRG == ImIipDefine_D_IM_IIP_STOPPED ) {
		im_iip_counter_on_lipclk(NULL);
		im_iip_struct_on_lclk(NULL);
		ImIipDefine_IM_IIP_DSB();

		for( loopcnt = 0; loopcnt < ImIipStruct_D_IM_IIP_CACHE_MAXNUM; loopcnt++ ) {
			IO_IIP.PDCCTL[loopcnt].bit.FLHALL = ImIipDefine_D_IM_IIP_FLUSH_IMGCACHE_START;
		}

		im_iip_counter_on_izarac_caxrac(NULL);

		ImIipDefine_IM_IIP_DSB();
		ImIipDefine_IM_IIP_WAIT_USEC( ImIipDefine_D_IM_IIP_SRAM_WAIT_USEC );

		IO_IIP.IZACTL1.bit.TRG = ImIipDefine_D_IM_IIP_START;

#ifdef CO_DEBUG_ON_PC
		IO_IIP.IZACTL1.bit.TRG = ImIipDefine_D_IM_IIP_RUNNING;
		IO_IIP.IZACTL2.bit.ABORT = ImIipDefine_D_IM_IIP_RUNNING;
#endif //CO_DEBUG_ON_PC

		ImIipDefine_IM_IIP_PRINT_PCDBG(( "Im_IIP_(Link)Start_SWTRG: IZACTL1.bit.TRG = %u\n", IO_IIP.IZACTL1.bit.TRG ));
	}
	else {
		if( link_onoff != ImIipDefine_D_IM_IIP_ENABLE_OFF ) {
			IO_IIP.IZACTL1.bit.TRG = ImIipDefine_D_IM_IIP_START;
#ifdef CO_DEBUG_ON_PC
			IO_IIP.IZACTL1.bit.TRG = ImIipDefine_D_IM_IIP_RUNNING;
#endif //CO_DEBUG_ON_PC

			ImIipDefine_IM_IIP_PRINT_PCDBG(( "Im_IIP_LinkStart_SWTRG: IZACTL1.bit.TRG = %u\n", IO_IIP.IZACTL1.bit.TRG ));
		}
	}

	im_iip_static_irq_enable(NULL, irq_mask );

	// Start Unit
	p_uinftbl = im_iip_sun_get_unitinftbl_regaddr( unitId );
	if( p_uinftbl == NULL ) {
		retval = ImIipDefine_D_IM_IIP_INVALID_ARG_ERR;
	}
	else {
		retval = imIipControlSwtrg( &p_uinftbl->UNITINFTBL0, swtrg );
	}


	Im_IIP_Off_Pclk();
	ImIipDefine_IM_IIP_DSB();

	return retval;
}

ULONG im_iip_sub_util_conv_pixid( const EImIipPixid pixid )
{
	switch( pixid ) {
		case ImIipStruct_E_IM_IIP_PIXID_0:
			return 0UL;
		case ImIipStruct_E_IM_IIP_PIXID_1:
			return 1UL;
		case ImIipStruct_E_IM_IIP_PIXID_2:
			return 2UL;
		case ImIipStruct_E_IM_IIP_PIXID_3:
			return 3UL;
		case ImIipStruct_E_IM_IIP_PIXID_4:
			return 4UL;
		case ImIipStruct_E_IM_IIP_PIXID_5:
			return 5UL;
		case ImIipStruct_E_IM_IIP_PIXID_6:
			return 6UL;
		case ImIipStruct_E_IM_IIP_PIXID_7:
			return 7UL;
		case ImIipStruct_E_IM_IIP_PIXID_8:
			return 8UL;
		case ImIipStruct_E_IM_IIP_PIXID_9:
			return 9UL;
		case ImIipStruct_E_IM_IIP_PIXID_10:
			return 10UL;
		case ImIipStruct_E_IM_IIP_PIXID_11:
			return 11UL;
		default:
			return (ULONG)ImIipStruct_E_IM_IIP_PIXID_INVALID;
	}
}

// Convert UnitID to PortID
ULONG im_iip_sub_util_conv_portid( const EImIipUnitId unitid )
{
	switch( unitid ) {
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD0:
			return E_IM_IIP_PARAM_PORTID_LD0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD1:
			return E_IM_IIP_PARAM_PORTID_LD1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD2:
			return E_IM_IIP_PARAM_PORTID_LD2;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD3:
			return E_IM_IIP_PARAM_PORTID_LD3;
		case ImIipStruct_E_IM_IIP_UNIT_ID_FLT:
			return E_IM_IIP_PARAM_PORTID_FLT_P0;	// Only port0
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN0:
			return E_IM_IIP_PARAM_PORTID_AFN0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN1:
			return E_IM_IIP_PARAM_PORTID_AFN1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN2:
			return E_IM_IIP_PARAM_PORTID_AFN2;
		case ImIipStruct_E_IM_IIP_UNIT_ID_FRECT0:
			return E_IM_IIP_PARAM_PORTID_FRECT0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_MON:
			return E_IM_IIP_PARAM_PORTID_NONE;		// Port not found
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL0:
			return E_IM_IIP_PARAM_PORTID_SL0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL1:
			return E_IM_IIP_PARAM_PORTID_SL1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL2:
			return E_IM_IIP_PARAM_PORTID_SL2;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL3:
			return E_IM_IIP_PARAM_PORTID_SL3;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL4:
			return E_IM_IIP_PARAM_PORTID_SL4;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL5:
			return E_IM_IIP_PARAM_PORTID_SL5;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL6:
			return E_IM_IIP_PARAM_PORTID_SL6;
		case ImIipStruct_E_IM_IIP_UNIT_ID_FRECT1:
			return E_IM_IIP_PARAM_PORTID_FRECT1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL7:
			return E_IM_IIP_PARAM_PORTID_SL7;
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL8:
			return E_IM_IIP_PARAM_PORTID_SL8;
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC0:
			return E_IM_IIP_PARAM_PORTID_CSC0;
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC1:
			return E_IM_IIP_PARAM_PORTID_CSC1;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LUT:
			return E_IM_IIP_PARAM_PORTID_LUT_P0;	// Only port0
		case ImIipStruct_E_IM_IIP_UNIT_ID_GPC:
			return E_IM_IIP_PARAM_PORTID_GPC_P0;	// Only port0
		case ImIipStruct_E_IM_IIP_UNIT_ID_BLEND0:
			return E_IM_IIP_PARAM_PORTID_BLEND0_P0;	// Only port0
		case ImIipStruct_E_IM_IIP_UNIT_ID_CFL0:
			return E_IM_IIP_PARAM_PORTID_CFL0_P0;	// Only port0
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC2:
			return E_IM_IIP_PARAM_PORTID_CSC2;
		case ImIipStruct_E_IM_IIP_UNIT_ID_CSC3:
			return E_IM_IIP_PARAM_PORTID_CSC3;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD4:
			return E_IM_IIP_PARAM_PORTID_LD4;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD5:
			return E_IM_IIP_PARAM_PORTID_LD5;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD6:
			return E_IM_IIP_PARAM_PORTID_LD6;
		case ImIipStruct_E_IM_IIP_UNIT_ID_LD7:
			return E_IM_IIP_PARAM_PORTID_LD7;
		case ImIipStruct_E_IM_IIP_UNIT_ID_AFN3:
			return E_IM_IIP_PARAM_PORTID_AFN3;
		case ImIipStruct_E_IM_IIP_UNIT_ID_BLEND1:
			return E_IM_IIP_PARAM_PORTID_BLEND1_P0;	// Only port0
		case ImIipStruct_E_IM_IIP_UNIT_ID_MFT:
			return E_IM_IIP_PARAM_PORTID_MFT;
		default:
			return E_IM_IIP_PARAM_PORTID_NONE;	// Invalid parameter
	}
}

VOID im_iip_sub_set_unitinftbl_param(ImIipDefine* self, TImIipUnitCfg* const unitinftbl_param, const EImIipUnitId id, const VOID* const addr, const ULLONG unitidBitmask )
{
	switch( id ) {
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL0:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL1:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL2:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL3:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL4:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL5:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL6:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL7:	// FALLTHROUGH
		case ImIipStruct_E_IM_IIP_UNIT_ID_SL8:
			unitinftbl_param->unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
			unitinftbl_param->chainEnable = ImIipDefine_D_IM_IIP_PLDUNIT_CHAIN_DISABLE;
			unitinftbl_param->unitParamAddr = (ULONG)addr;
			unitinftbl_param->loadUnitParamFlag = unitidBitmask;
			break;
		default:
			unitinftbl_param->unitCtrl = ImIipDefine_D_IM_IIP_HW_CTRL_SWTRG;
			unitinftbl_param->unitParamAddr = (ULONG)addr;
			break;
	}
}

VOID im_iip_sub_set_pixfmttbl_param( ImIipDefine* self,TImIipPixfmttbl* const pixfmttbl,
									    const TImIipUtilImgGbl* const gbl,
									    const UINT32 pixDepth,
									    const TImIipUtilAlphaInfo* const alpha )
{
	pixfmttbl->pixDepth = pixDepth;
	if( (gbl->alpha == ImIipDefine_D_IM_IIP_ALPHA_FALSE) || (alpha == NULL) ) {
		pixfmttbl->alpha = ImIipDefine_D_IM_IIP_ALPHA_FALSE;
		pixfmttbl->alphaDepth = ImIipStruct_E_IM_IIP_ADEPTH_8BITS;
		pixfmttbl->alphaSubsampling = ImIipDefine_D_IM_IIP_ALPHA_NO_SUBSAMP;
	}
	else {
		pixfmttbl->alpha = ImIipDefine_D_IM_IIP_ALPHA_TRUE;
		pixfmttbl->alphaDepth = alpha->alphaDepth;
		pixfmttbl->alphaSubsampling = alpha->alphaSubsampling;

		pixfmttbl->lineBytes.Alpha = gbl->lineBytes.Alpha;
		pixfmttbl->addr.Alpha = gbl->addr.Alpha;
		pixfmttbl->masterifAlpha = gbl->masterifAlpha;
	}
	pixfmttbl->frameType = gbl->frameType;
	pixfmttbl->pixFormat = gbl->pixFormat;
	pixfmttbl->chunkyColor.component0 = gbl->chunkyColor.component0;
	pixfmttbl->chunkyColor.component1 = gbl->chunkyColor.component1;
	pixfmttbl->chunkyColor.component2 = gbl->chunkyColor.component2;
	pixfmttbl->chunkyColor.component3 = gbl->chunkyColor.component3;
	pixfmttbl->signYG = gbl->signYG;
	pixfmttbl->signCbB = gbl->signCbB;
	pixfmttbl->signCrR = gbl->signCrR;
	pixfmttbl->signD3 = gbl->signD3;
	pixfmttbl->masterifYG = gbl->masterifYG;
	pixfmttbl->masterifCbB = gbl->masterifCbB;
	pixfmttbl->masterifCrR = gbl->masterifCrR;
	pixfmttbl->pixOutsideImg = ImIipDefine_D_IM_IIP_OUTSIDE_IMG_EDGE;
//	pixfmttbl->yGValOutsideImg;		// no use
//	pixfmttbl->cbBValOutsideImg;	// no use
//	pixfmttbl->crRValOutsideImg;	// no use
//	pixfmttbl->alphaValOutsideImg;	// no use
	pixfmttbl->width = gbl->width;
	pixfmttbl->lines = gbl->lines;
	pixfmttbl->lineBytes.yG = gbl->lineBytes.yG;
	pixfmttbl->lineBytes.cbB = gbl->lineBytes.cbB;
	pixfmttbl->lineBytes.crR = gbl->lineBytes.crR;
	pixfmttbl->addr.yG = gbl->addr.yG;
	pixfmttbl->addr.cbB = gbl->addr.cbB;
	pixfmttbl->addr.crR = gbl->addr.crR;
}

VOID im_iip_sub_set_phvsz_1d_sl( ImIipDefine* self,TImIipUtilPhvsz* const phvsz,
								    const TImIipUtilImgInt* const dst )
{
	UINT32						mod_sz;
	const TImIipUtilRectInt* dst_rect = &dst->rect;

	phvsz->PVSZ1 = dst_rect->lines;
	phvsz->PHSZ1 = ( dst_rect->width >= 64 ) ? 64 : 32;

	mod_sz = dst_rect->left % 8;
	phvsz->PHSZ0 = (mod_sz == 0) ? phvsz->PHSZ1 : (8 - mod_sz);
	mod_sz = dst_rect->top % 8;
	phvsz->PVSZ0 = (mod_sz == 0) ? phvsz->PVSZ1 : (8 - mod_sz);
}

E_IM_IIP_PARAM_PF_PDIST im_iip_sub_get_pf_pdist( const UINT32 pixDepth,
												    const EImIipFtype frameType,
												    const EImIipPfmt pixFormat,
												    const UINT32 alpha )
{
	if(
		(pixFormat == ImIipStruct_E_IM_IIP_PFMT_RGB565) ||
		(pixFormat == ImIipStruct_E_IM_IIP_PFMT_RGBA5551) ||
		(pixFormat == ImIipStruct_E_IM_IIP_PFMT_RGBA4444)
	   ) {
		return E_IM_IIP_PARAM_PF_PDIST_32PIX;
	}


	if( ImIipDefine_D_IM_IIP_PDEPTH_8BITS == pixDepth ) {

		if( pixFormat == ImIipStruct_E_IM_IIP_PFMT_CBCR ) {
			return E_IM_IIP_PARAM_PF_PDIST_32PIX;
		}

		if(
			((ImIipStruct_E_IM_IIP_PFMT_BAYER == pixFormat) && (ImIipDefine_D_IM_IIP_ALPHA_TRUE == alpha)) ||
			((ImIipStruct_E_IM_IIP_PFMT_PLANE == pixFormat) && (ImIipDefine_D_IM_IIP_ALPHA_TRUE == alpha))
			) {
			return E_IM_IIP_PARAM_PF_PDIST_32PIX;
		}

		if(
			(ImIipStruct_E_IM_IIP_PFMT_BAYER == pixFormat) ||
			(ImIipStruct_E_IM_IIP_PFMT_PLANE == pixFormat)
		   ) {
			return E_IM_IIP_PARAM_PF_PDIST_64PIX;
		}

		if( ImIipStruct_E_IM_IIP_PFMT_VIDEO == pixFormat ) {
			return E_IM_IIP_PARAM_PF_PDIST_64PIX;
		}

		if( ImIipStruct_E_IM_IIP_FTYPE_CHUNKY == frameType ) {
			if( ImIipStruct_E_IM_IIP_PFMT_YCC444 == pixFormat ) {
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

		if( pixFormat == ImIipStruct_E_IM_IIP_PFMT_CBCR ) {
			return E_IM_IIP_PARAM_PF_PDIST_16PIX;
		}

		if(
			((ImIipStruct_E_IM_IIP_PFMT_BAYER == pixFormat) && (ImIipDefine_D_IM_IIP_ALPHA_TRUE == alpha)) ||
			((ImIipStruct_E_IM_IIP_PFMT_PLANE == pixFormat) && (ImIipDefine_D_IM_IIP_ALPHA_TRUE == alpha))
			) {
			return E_IM_IIP_PARAM_PF_PDIST_16PIX;
		}

		if(
			(ImIipStruct_E_IM_IIP_PFMT_BAYER == pixFormat) ||
			(ImIipStruct_E_IM_IIP_PFMT_PLANE == pixFormat)
		   ) {
			return E_IM_IIP_PARAM_PF_PDIST_32PIX;
		}

		if( ImIipStruct_E_IM_IIP_PFMT_VIDEO == pixFormat ) {
			return E_IM_IIP_PARAM_PF_PDIST_32PIX;
		}

		if( ImIipStruct_E_IM_IIP_FTYPE_CHUNKY == frameType ) {
			if( ImIipStruct_E_IM_IIP_PFMT_YCC444 == pixFormat ) {
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
