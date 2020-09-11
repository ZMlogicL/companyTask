/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImIip2
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


// CT header
// C Standard header
#include <string.h>
#include <stdlib.h>

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif
#endif //CO_CT_IM_IIP_DISABLE

#include "ct_im_iip.h"
#include "ct_im_iip_b2y_frect_afn.h"
#include "ct_im_iip_afn.h"
#include "ct_im_iip_frect.h"
#include "ct_im_iip_lut.h"
#include "ct_im_iip_blend.h"
#include "ct_im_iip_csc.h"
#include "ct_im_iip_ld.h"
#include "ct_im_iip_flt.h"
#include "ct_im_iip_sl.h"
#include "ct_im_iip_mon.h"
#include "ct_im_iip_cfl.h"
#include "ct_im_iip_gpc.h"
#include "ct_im_iip_utility.h"
#include "ct_im_iip_mft.h"
// im_iip header
#include "im_iip.h"

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#include "palladium_test_common.h"
#endif
// ### REMOVE_RELEASE END

// Driver common header
#include "driver_common.h"
#include "ddim_user_custom.h"

// Clock Control
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif

// Memory barrier
#include "dd_arm.h"
// MILB register header
#include "jdsiip.h"
#include "ctimiip.h"
#include "ctimiip2.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIip2, ct_im_iip_2)
//#define CT_IM_IIP_2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIip2Private, CT_TYPE_IM_IIP_2))


struct _CtImIip2Private
{

};

#ifndef CO_CT_IM_IIP_DISABLE
extern T_CT_IM_IIP_AXI_PRINT_TBL g_ct_im_iip_axi_print_tbl[E_IM_IIP_AXI_ID_MAX];
#endif //CO_CT_IM_IIP_DISABLE


/*
*DECLS
*/
#ifndef CO_CT_IM_IIP_DISABLE
static VOID ct_im_iip_print_axictl( const E_IM_IIP_AXI_ID axiid );
#endif //CO_CT_IM_IIP_DISABLE

#ifndef CO_CT_IM_IIP_DISABLE
extern VOID Im_IIP_Print_DebugStatus( VOID );
#endif //CO_CT_IM_IIP_DISABLE


/**
 * IMPL
 */
//static void ct_im_iip_2_constructor(CtImIip2 *self)
//{
//	CtImIip2Private *priv = CT_IM_IIP_2_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_2_destructor(CtImIip2 *self)
//{
//	CtImIip2Private *priv = CT_IM_IIP_2_GET_PRIVATE(self);
//}

#ifndef CO_CT_IM_IIP_DISABLE
static VOID ct_im_iip_print_axictl( const E_IM_IIP_AXI_ID axiid )
{
	ULONG reg0 = 0;
	ULONG reg1 = 0;
	T_CT_IM_IIP_AXI_PRINT_TBL axi_tbl;

	axi_tbl = g_ct_im_iip_axi_print_tbl[axiid];

	if( axi_tbl.reg_addr0 == NULL ) {
		Ddim_Print(( "ct_im_iip_print_axictl: ERROR!!\n" ));
		return;
	}

	Im_IIP_On_Pclk();

	reg0 = *axi_tbl.reg_addr0;
	if( axi_tbl.reg_addr1 != NULL ) {
		reg1 = *axi_tbl.reg_addr1;
	}

	Ddim_Print(( "%s: 0x%lx 0x%lx\n", axi_tbl.axiname, reg0, reg1 ));

	Im_IIP_Off_Pclk();
}
#endif //CO_CT_IM_IIP_DISABLE


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
INT32 CT_Im_IIP_1_1_10( VOID )
{
	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	return CT_Im_IIP_1_1_9();
}

INT32 CT_Im_IIP_1_1_12( VOID )
{
	T_IM_IIP_CTRL_AXI		axicfg;
	E_IM_IIP_AXI_ID			axiid;
	INT32					ercd;
	ULLONG					unit_bitmask = 0xFFFFFFFFFFFFFFFFull;


	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	memset( &axicfg, '\0', sizeof(axicfg) );
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		Ddim_Print(( "** AXIID: %u\n", axiid ));

		// check result=0x0C000001
		ercd = Im_IIP_Ctrl_AXI( axiid, NULL );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		// check register max value
		axicfg.trans_req_ctrl = 3;
		axicfg.cache_type = 0xF;
		axicfg.protection_type = 7;
		ercd = Im_IIP_Ctrl_AXI( axiid, &axicfg );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_axictl( axiid );

		// check register min value
		axicfg.trans_req_ctrl = 0;
		axicfg.cache_type = 0;
		axicfg.protection_type = 0;
		ercd = Im_IIP_Ctrl_AXI( axiid, &axicfg );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_axictl( axiid );
	}

	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_13( VOID )
{
	T_IM_IIP_CTRL_AXI		axicfg_max;
	T_IM_IIP_CTRL_AXI		axicfg_min;
	T_IM_IIP_CTRL_AXI_ALL	axicfgall;
	E_IM_IIP_AXI_ID			axiid;
	INT32					ercd;
	UINT32					unit_bitmask = 0xFFFFFFFF;


	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));


	memset( &axicfg_max, '\0', sizeof(axicfg_max) );
	axicfg_max.trans_req_ctrl = 3;
	axicfg_max.cache_type = 0xF;
	axicfg_max.protection_type = 7;

	memset( &axicfg_min, '\0', sizeof(axicfg_min) );
	axicfg_min.trans_req_ctrl = 0;
	axicfg_min.cache_type = 0;
	axicfg_min.protection_type = 0;


	Ddim_Print(( "** imgcache0\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.imgcache0 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.imgcache0 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** imgcache1\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.imgcache1 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.imgcache1 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** imgcache2\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.imgcache2 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.imgcache2 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** dp\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.dp = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.dp = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** afn0\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.afn0 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.afn0 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** afn1\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.afn1 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.afn1 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** afn2\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.afn2 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.afn2 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** afn3\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.afn3 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.afn3 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** frect0\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.frect0 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.frect0 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** frect1\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.frect1 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.frect1 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** gpc\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.gpc = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.gpc = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** sl0\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl0 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl0 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** sl1\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl1 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl1 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** sl2\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl2 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl2 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** sl3\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl3 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl3 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** sl4\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl4 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl4 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** sl5\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl5 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl5 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** sl6\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl6 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl6 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** sl7\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl7 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl7 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	Ddim_Print(( "** sl8\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl8 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.sl8 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}



	Ddim_Print(( "** all\n" ));
	// check register max value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.imgcache0 = &axicfg_max;
	axicfgall.imgcache1 = &axicfg_max;
	axicfgall.imgcache2 = &axicfg_max;
	axicfgall.dp = &axicfg_max;
	axicfgall.afn0 = &axicfg_max;
	axicfgall.afn1 = &axicfg_max;
	axicfgall.afn2 = &axicfg_max;
	axicfgall.afn3 = &axicfg_max;
	axicfgall.frect0 = &axicfg_max;
	axicfgall.frect1 = &axicfg_max;
	axicfgall.gpc = &axicfg_max;
	axicfgall.sl0 = &axicfg_max;
	axicfgall.sl1 = &axicfg_max;
	axicfgall.sl2 = &axicfg_max;
	axicfgall.sl3 = &axicfg_max;
	axicfgall.sl4 = &axicfg_max;
	axicfgall.sl5 = &axicfg_max;
	axicfgall.sl6 = &axicfg_max;
	axicfgall.sl7 = &axicfg_max;
	axicfgall.sl8 = &axicfg_max;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}
	// check register min value
	memset( &axicfgall, '\0', sizeof(axicfgall) );
	axicfgall.imgcache0 = &axicfg_min;
	axicfgall.imgcache1 = &axicfg_min;
	axicfgall.imgcache2 = &axicfg_min;
	axicfgall.dp = &axicfg_min;
	axicfgall.afn0 = &axicfg_min;
	axicfgall.afn1 = &axicfg_min;
	axicfgall.afn2 = &axicfg_min;
	axicfgall.afn3 = &axicfg_min;
	axicfgall.frect0 = &axicfg_min;
	axicfgall.frect1 = &axicfg_min;
	axicfgall.gpc = &axicfg_min;
	axicfgall.sl0 = &axicfg_min;
	axicfgall.sl1 = &axicfg_min;
	axicfgall.sl2 = &axicfg_min;
	axicfgall.sl3 = &axicfg_min;
	axicfgall.sl4 = &axicfg_min;
	axicfgall.sl5 = &axicfg_min;
	axicfgall.sl6 = &axicfg_min;
	axicfgall.sl7 = &axicfg_min;
	axicfgall.sl8 = &axicfg_min;
	ercd = Im_IIP_Ctrl_AXI_ALL( &axicfgall );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	for( axiid = E_IM_IIP_AXI_ID_TOP; axiid < E_IM_IIP_AXI_ID_MAX; axiid++ ) {
		ct_im_iip_print_axictl( axiid );
	}


	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_14( VOID )
{
	T_IM_IIP_CTRL_BASE		basecfg;
	INT32					ercd;
	UINT32					unit_bitmask = 0xFFFFFFFF;


	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));


	memset( &basecfg, '\0', sizeof(basecfg) );
#if 0	// B2Y Link not support
	basecfg.b2y_link = 1;
#endif	// B2Y Link not support
	basecfg.enable_interrupt_flag = 0
		| D_IM_IIP_INT_FACTOR_IZAEND
		| D_IM_IIP_INT_FACTOR_AXIERR
		| D_IM_IIP_INT_FACTOR_SL0END
		| D_IM_IIP_INT_FACTOR_SL1END
		| D_IM_IIP_INT_FACTOR_SL2END
		| D_IM_IIP_INT_FACTOR_SL3END
		| D_IM_IIP_INT_FACTOR_SL4END
		| D_IM_IIP_INT_FACTOR_SL5END
		| D_IM_IIP_INT_FACTOR_SL6END
		| D_IM_IIP_INT_FACTOR_SL7END
		| D_IM_IIP_INT_FACTOR_SL8END
		| D_IM_IIP_INT_FACTOR_SL0_LINEEND
		| D_IM_IIP_INT_FACTOR_SL1_LINEEND
		| D_IM_IIP_INT_FACTOR_SL2_LINEEND
		| D_IM_IIP_INT_FACTOR_SL3_LINEEND
		| D_IM_IIP_INT_FACTOR_SL4_LINEEND
		| D_IM_IIP_INT_FACTOR_SL5_LINEEND
		| D_IM_IIP_INT_FACTOR_SL6_LINEEND
		| D_IM_IIP_INT_FACTOR_SL7_LINEEND
		| D_IM_IIP_INT_FACTOR_SL8_LINEEND
#if 0	// IMG-SRAM not support
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN0
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN1
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN2
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN3
		| D_IM_IIP_INT_FACTOR_RINGFULL_FRECT0
		| D_IM_IIP_INT_FACTOR_RINGFULL_FRECT1
		| D_IM_IIP_INT_FACTOR_RINGFULL_FLT
#endif	// IMG-SRAM not support
		;
	basecfg.sl0_interrupt_lines = 0x3FFF;
	basecfg.sl1_interrupt_lines = 0x3FFF;
	basecfg.sl2_interrupt_lines = 0x3FFF;
	basecfg.sl3_interrupt_lines = 0x3FFF;
	basecfg.sl4_interrupt_lines = 0x3FFF;
	basecfg.sl5_interrupt_lines = 0x3FFF;
	basecfg.sl6_interrupt_lines = 0x3FFF;
	basecfg.sl7_interrupt_lines = 0x3FFF;
	basecfg.sl8_interrupt_lines = 0x3FFF;
	basecfg.int_handler = (T_IM_IIP_CALLBACK)0xFFFFFFFF;
	basecfg.cache_flush_ctrl[0] = 1;
	basecfg.cache_flush_ctrl[1] = 1;
	basecfg.cache_flush_ctrl[2] = 1;
	basecfg.ext_bit_ctrl_less_8bits[0] = 1;
	basecfg.ext_bit_ctrl_less_8bits[1] = 1;
	basecfg.ext_bit_ctrl_less_8bits[2] = 1;


	// check result = 0x0C000001
	ercd = Im_IIP_Ctrl_Base( NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check register max value
	ercd = Im_IIP_Ctrl_Base( &basecfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	ct_im_iip_print_base();

	// check register min value
	memset( &basecfg, '\0', sizeof(basecfg) );
	ercd = Im_IIP_Ctrl_Base( &basecfg );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	ct_im_iip_print_base();

	Im_IIP_Print_DebugStatus();


	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_15( VOID )
{
	UINT32	enable_interrupt_flag;
	INT32	ercd;
	UINT32	unit_bitmask = 0xFFFFFFFF;


	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));


	enable_interrupt_flag = 0
		| D_IM_IIP_INT_FACTOR_IZAEND
		| D_IM_IIP_INT_FACTOR_AXIERR
		| D_IM_IIP_INT_FACTOR_SL0END
		| D_IM_IIP_INT_FACTOR_SL1END
		| D_IM_IIP_INT_FACTOR_SL2END
		| D_IM_IIP_INT_FACTOR_SL3END
		| D_IM_IIP_INT_FACTOR_SL4END
		| D_IM_IIP_INT_FACTOR_SL5END
		| D_IM_IIP_INT_FACTOR_SL6END
		| D_IM_IIP_INT_FACTOR_SL7END
		| D_IM_IIP_INT_FACTOR_SL8END
		| D_IM_IIP_INT_FACTOR_SL0_LINEEND
		| D_IM_IIP_INT_FACTOR_SL1_LINEEND
		| D_IM_IIP_INT_FACTOR_SL2_LINEEND
		| D_IM_IIP_INT_FACTOR_SL3_LINEEND
		| D_IM_IIP_INT_FACTOR_SL4_LINEEND
		| D_IM_IIP_INT_FACTOR_SL5_LINEEND
		| D_IM_IIP_INT_FACTOR_SL6_LINEEND
		| D_IM_IIP_INT_FACTOR_SL7_LINEEND
		| D_IM_IIP_INT_FACTOR_SL8_LINEEND
#if 0	// INTIZ2/INTEN2 delete
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN0
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN1
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN2
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN3
		| D_IM_IIP_INT_FACTOR_RINGFULL_FRECT0
		| D_IM_IIP_INT_FACTOR_RINGFULL_FRECT1
		| D_IM_IIP_INT_FACTOR_RINGFULL_FLT
#endif	// INTIZ2/INTEN2 delete
		;


	// check register max value
	ercd = Im_IIP_Set_Interrupt( enable_interrupt_flag, 1 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	ct_im_iip_print_base();

	// check register min value
	ercd = Im_IIP_Set_Interrupt( enable_interrupt_flag, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	ct_im_iip_print_base();


	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_16( VOID )
{
	UINT32	enable_interrupt_flag;
	INT32	ercd;
	UINT32	loopcnt;
	ULLONG	unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
	UINT32 int_factor_array[] = {
		( D_IM_IIP_INT_FACTOR_IZAEND
		| D_IM_IIP_INT_FACTOR_AXIERR
		| D_IM_IIP_INT_FACTOR_SL0END
		| D_IM_IIP_INT_FACTOR_SL1END
		| D_IM_IIP_INT_FACTOR_SL2END
		| D_IM_IIP_INT_FACTOR_SL3END
		| D_IM_IIP_INT_FACTOR_SL4END
		| D_IM_IIP_INT_FACTOR_SL5END
		| D_IM_IIP_INT_FACTOR_SL6END
		| D_IM_IIP_INT_FACTOR_SL7END
		| D_IM_IIP_INT_FACTOR_SL8END
		| D_IM_IIP_INT_FACTOR_SL0_LINEEND
		| D_IM_IIP_INT_FACTOR_SL1_LINEEND
		| D_IM_IIP_INT_FACTOR_SL2_LINEEND
		| D_IM_IIP_INT_FACTOR_SL3_LINEEND
		| D_IM_IIP_INT_FACTOR_SL4_LINEEND
		| D_IM_IIP_INT_FACTOR_SL5_LINEEND
		| D_IM_IIP_INT_FACTOR_SL6_LINEEND
		| D_IM_IIP_INT_FACTOR_SL7_LINEEND
		| D_IM_IIP_INT_FACTOR_SL8_LINEEND
#if 0	// INTIZ2/INTEN2 delete
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN0
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN1
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN2
		| D_IM_IIP_INT_FACTOR_RINGFULL_AFN3
		| D_IM_IIP_INT_FACTOR_RINGFULL_FRECT0
		| D_IM_IIP_INT_FACTOR_RINGFULL_FRECT1
		| D_IM_IIP_INT_FACTOR_RINGFULL_FLT
#endif	// INTIZ2/INTEN2 delete
		 ),
		D_IM_IIP_INT_FACTOR_IZAEND,
		D_IM_IIP_INT_FACTOR_AXIERR,
		D_IM_IIP_INT_FACTOR_SL0END,
		D_IM_IIP_INT_FACTOR_SL1END,
		D_IM_IIP_INT_FACTOR_SL2END,
		D_IM_IIP_INT_FACTOR_SL3END,
		D_IM_IIP_INT_FACTOR_SL4END,
		D_IM_IIP_INT_FACTOR_SL5END,
		D_IM_IIP_INT_FACTOR_SL6END,
		D_IM_IIP_INT_FACTOR_SL7END,
		D_IM_IIP_INT_FACTOR_SL8END,
		D_IM_IIP_INT_FACTOR_SL0_LINEEND,
		D_IM_IIP_INT_FACTOR_SL1_LINEEND,
		D_IM_IIP_INT_FACTOR_SL2_LINEEND,
		D_IM_IIP_INT_FACTOR_SL3_LINEEND,
		D_IM_IIP_INT_FACTOR_SL4_LINEEND,
		D_IM_IIP_INT_FACTOR_SL5_LINEEND,
		D_IM_IIP_INT_FACTOR_SL6_LINEEND,
		D_IM_IIP_INT_FACTOR_SL7_LINEEND,
		D_IM_IIP_INT_FACTOR_SL8_LINEEND,
#if 0	// INTIZ2/INTEN2 delete
		D_IM_IIP_INT_FACTOR_RINGFULL_AFN0,
		D_IM_IIP_INT_FACTOR_RINGFULL_AFN1,
		D_IM_IIP_INT_FACTOR_RINGFULL_AFN2,
		D_IM_IIP_INT_FACTOR_RINGFULL_AFN3,
		D_IM_IIP_INT_FACTOR_RINGFULL_FRECT0,
		D_IM_IIP_INT_FACTOR_RINGFULL_FRECT1,
		D_IM_IIP_INT_FACTOR_RINGFULL_FLT,
#endif	// INTIZ2/INTEN2 delete
	};


	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));


	for( loopcnt = 0; loopcnt < (sizeof(int_factor_array) / sizeof(int_factor_array[0])); loopcnt++ ) {
		enable_interrupt_flag = int_factor_array[loopcnt];

		Ddim_Print(( D_IM_IIP_FUNC_NAME "** flag bit = 0x%x\n", enable_interrupt_flag ));

		// check register max value
		ercd = Im_IIP_Set_IntHandler( enable_interrupt_flag, (T_IM_IIP_CALLBACK)0xFFFFFFFF );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_base();
		Im_IIP_Print_DebugStatus();

		// check register min value
		ercd = Im_IIP_Set_IntHandler( enable_interrupt_flag, (T_IM_IIP_CALLBACK)0 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_base();
		Im_IIP_Print_DebugStatus();

		DDIM_User_Dly_Tsk( 300 );		// Wait for UART output.
	}


	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_CT_IM_IIP_DISABLE

CtImIip2* ct_im_iip_2_get(void)
{
	static CtImIip2* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_2, sizeof(CtImIip2Private));
	}

	return self;
}
