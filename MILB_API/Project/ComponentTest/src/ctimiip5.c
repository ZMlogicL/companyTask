/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip5
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
//#include "ct_im_iip_frect.h"
#include "ctimiipfrect.h"
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
#include "ctimiip5.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIip5, ct_im_iip_5)
//#define CT_IM_IIP_5_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIip5Private, CT_TYPE_IM_IIP_5))


struct _CtImIip5Private
{

};


/*
*DECLS
*/
#ifndef CO_CT_IM_IIP_DISABLE
#ifdef CO_DEBUG_ON_PC
static 		 VOID ct_im_iip_print_mon( const T_IM_IIP_MON const mon[4] );
#endif //CO_DEBUG_ON_PC
#endif //CO_CT_IM_IIP_DISABLE


/********
 * IMPL
 */
//static void ct_im_iip_5_constructor(CtImIip5 *self)
//{
//	CtImIip5Private *priv = CT_IM_IIP_5_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_5_destructor(CtImIip5 *self)
//{
//	CtImIip5Private *priv = CT_IM_IIP_5_GET_PRIVATE(self);
//}

#ifndef CO_CT_IM_IIP_DISABLE
#ifdef CO_DEBUG_ON_PC
static VOID ct_im_iip_print_mon( const T_IM_IIP_MON const mon[4] )
{
	UINT32 loopcnt;

	for( loopcnt = 0; loopcnt < 4; loopcnt++ )
	{
		Ddim_Print(( "pos_x = 0x%04x pos_y = 0x%04x value = 0x%04x(%d)\n", mon[loopcnt].pos_x, mon[loopcnt].pos_y, mon[loopcnt].value, mon[loopcnt].value ));
	}
}
#endif //CO_DEBUG_ON_PC
#endif //CO_CT_IM_IIP_DISABLE


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
#ifdef CO_DEBUG_ON_PC
INT32 CT_Im_IIP_1_1_28( VOID )
{
	INT32 ercd;
	UINT32 loopcnt;
	T_IM_IIP_MAXMON mon;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	for( loopcnt = 0; loopcnt < (sizeof(mon.max) / sizeof(mon.max[0])); loopcnt++ )
	{
		IO_IIP.MAXMON[loopcnt].bit.HPOINTMAX = 0x3FFF;
		IO_IIP.MAXMON[loopcnt].bit.VPOINTMAX = 0;
		IO_IIP.MAXMON[loopcnt].bit.MAXVAL = -0x4000;

		// check get MAXMON
		ercd = Im_IIP_Get_MAXMON( &mon );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_mon( mon.max );

		IO_IIP.MAXMON[loopcnt].bit.HPOINTMAX = 0;
		IO_IIP.MAXMON[loopcnt].bit.VPOINTMAX = 0x3FFF;
		IO_IIP.MAXMON[loopcnt].bit.MAXVAL = 0x3FFF;

		// check get MAXMON
		ercd = Im_IIP_Get_MAXMON( &mon );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_mon( mon.max );
	}

	// check result = 0x0C000001
	ercd = Im_IIP_Get_MAXMON( NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 CT_Im_IIP_1_1_29( VOID )
{
	INT32 ercd;
	UINT32 loopcnt;
	T_IM_IIP_MINMON mon;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	for( loopcnt = 0; loopcnt < (sizeof(mon.min) / sizeof(mon.min[0])); loopcnt++ )
	{
		IO_IIP.MINMON[loopcnt].bit.HPOINTMIN = 0x3FFF;
		IO_IIP.MINMON[loopcnt].bit.VPOINTMIN = 0;
		IO_IIP.MINMON[loopcnt].bit.MINVAL = -0x4000;

		// check get MINMON
		ercd = Im_IIP_Get_MINMON( &mon );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_mon( mon.min );

		IO_IIP.MINMON[loopcnt].bit.HPOINTMIN = 0;
		IO_IIP.MINMON[loopcnt].bit.VPOINTMIN = 0x3FFF;
		IO_IIP.MINMON[loopcnt].bit.MINVAL = 0x3FFF;

		// check get MINMON
		ercd = Im_IIP_Get_MINMON( &mon );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_mon( mon.min );
	}

	// check result = 0x0C000001
	ercd = Im_IIP_Get_MINMON( NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 CT_Im_IIP_1_1_30( VOID )
{
	INT32 ercd;
	UINT32 loopcnt;
	T_IM_IIP_ADDMON mon;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	for( loopcnt = 0; loopcnt < (sizeof(mon.add) / sizeof(mon.add[0])); loopcnt++ )
	{
		IO_IIP.ADDMON[loopcnt].bit.HPOINTADD = 0x3FFF;
		IO_IIP.ADDMON[loopcnt].bit.VPOINTADD = 0;
		IO_IIP.ADDMON[loopcnt].bit.ADDVAL = -0x4000;

		// check get ADDMON
		ercd = Im_IIP_Get_ADDMON( &mon );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_mon( mon.add );

		IO_IIP.ADDMON[loopcnt].bit.HPOINTADD = 0;
		IO_IIP.ADDMON[loopcnt].bit.VPOINTADD = 0x3FFF;
		IO_IIP.ADDMON[loopcnt].bit.ADDVAL = 0x3FFF;

		// check get ADDMON
		ercd = Im_IIP_Get_ADDMON( &mon );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_mon( mon.add );
	}

	// check result = 0x0C000001
	ercd = Im_IIP_Get_ADDMON( NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 CT_Im_IIP_1_1_31( VOID )
{
	INT32 ercd;
	E_IM_IIP_CACHE_CH loopcnt;
	T_IM_IIP_ACCESS_INFO info;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
	static const CHAR dump_msg[] = "acc=0x%08lx miss=0x%08lx\n";

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	for( loopcnt = E_IM_IIP_CACHE_CH_0; loopcnt < E_IM_IIP_CACHE_CH_MAX; loopcnt++ )
	{
		IO_IIP.PDCRAC[loopcnt].bit.PDCRAC = 0xFFFFFFFF;
		IO_IIP.PDCRMC[loopcnt].bit.PDCRMC = 0;

		ercd = Im_IIP_Get_ImgCache_Access_Info( loopcnt, &info );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		Ddim_Print(( dump_msg, info.real_access_counter, info.real_miss_counter ));

		IO_IIP.PDCRAC[loopcnt].bit.PDCRAC = 0;
		IO_IIP.PDCRMC[loopcnt].bit.PDCRMC = 0xFFFFFFFF;

		ercd = Im_IIP_Get_ImgCache_Access_Info( loopcnt, &info );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		Ddim_Print(( dump_msg, info.real_access_counter, info.real_miss_counter ));

		IO_IIP.PDCRAC[loopcnt].bit.PDCRAC = 0;
		IO_IIP.PDCRMC[loopcnt].bit.PDCRMC = 0;

		ercd = Im_IIP_Get_ImgCache_Access_Info( loopcnt, &info );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		Ddim_Print(( dump_msg, info.real_access_counter, info.real_miss_counter ));
	}

	// check result = 0x0C000001
	ercd = Im_IIP_Get_ImgCache_Access_Info( E_IM_IIP_CACHE_CH_MAX, &info );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check result = 0x0C000001
	ercd = Im_IIP_Get_ImgCache_Access_Info( E_IM_IIP_CACHE_CH_0, NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 CT_Im_IIP_1_1_32( VOID )
{
	INT32 ercd;
	T_IM_IIP_AXI_STATUS sts;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
	static const CHAR dump_msg[] = "read=0x%08lx write=0x%08lx\n";

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	IO_IIP.AXRSTS.word = 0xFFFFFFFFul;
	IO_IIP.AXWSTS.word = 0;

	ercd = Im_IIP_Get_AXI_Status( &sts );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	Ddim_Print(( dump_msg, sts.read_channel_status, sts.write_channel_status ));

	IO_IIP.AXRSTS.word = 0;
	IO_IIP.AXWSTS.word = 0xFFFFFFFFul;

	ercd = Im_IIP_Get_AXI_Status( &sts );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	Ddim_Print(( dump_msg, sts.read_channel_status, sts.write_channel_status ));

	ercd = Im_IIP_Get_AXI_Status( NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 CT_Im_IIP_1_1_33( VOID )
{
	INT32 ercd;
	UINT32 sl_status;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
	static const CHAR dump_msg[] = "sl_stat=0x%u\n";

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	IO_IIP.IZACTL1.bit.SLALE = 1;

	ercd = Im_IIP_Get_SL_Status( &sl_status );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	Ddim_Print(( dump_msg, sl_status ));

	IO_IIP.IZACTL1.bit.SLALE = 0;

	ercd = Im_IIP_Get_SL_Status( &sl_status );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	Ddim_Print(( dump_msg, sl_status ));

	ercd = Im_IIP_Get_SL_Status( NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_DEBUG_ON_PC

INT32 CT_Im_IIP_1_1_35( VOID)
{
	INT32 ercd;
	UINT32 loopcnt;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
	static const CHAR dump_msg[] = "accen0=0x%08lx\n";
	UINT32 accen_bitmask[] = { E_IM_IIP_OPEN_RES_LUT_A | E_IM_IIP_OPEN_RES_LUT_B | E_IM_IIP_OPEN_RES_LUT_C | E_IM_IIP_OPEN_RES_LUT_D | E_IM_IIP_OPEN_RES_LUT_E | E_IM_IIP_OPEN_RES_LUT_F | E_IM_IIP_OPEN_RES_HIST_0 | E_IM_IIP_OPEN_RES_HIST_1 | E_IM_IIP_OPEN_RES_HIST_2 | E_IM_IIP_OPEN_RES_HIST_3 | E_IM_IIP_OPEN_RES_CACHE1 | E_IM_IIP_OPEN_RES_CACHE2, E_IM_IIP_OPEN_RES_LUT_A, E_IM_IIP_OPEN_RES_LUT_B, E_IM_IIP_OPEN_RES_LUT_C, E_IM_IIP_OPEN_RES_LUT_D, E_IM_IIP_OPEN_RES_LUT_E, E_IM_IIP_OPEN_RES_LUT_F, E_IM_IIP_OPEN_RES_HIST_0, E_IM_IIP_OPEN_RES_HIST_1, E_IM_IIP_OPEN_RES_HIST_2, E_IM_IIP_OPEN_RES_HIST_3, E_IM_IIP_OPEN_RES_CACHE1, E_IM_IIP_OPEN_RES_CACHE2, };

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG(unit_bitmask, 0, 0, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	for (loopcnt = 0; loopcnt < (sizeof(accen_bitmask) / sizeof(accen_bitmask[0])); loopcnt++)
	{
		Ddim_Print(( "** bitmask = 0x%x\n", accen_bitmask[loopcnt] ));

		ercd = Im_IIP_Set_AccessEnable(accen_bitmask[loopcnt], 1);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		Im_IIP_On_Pclk();
		Ddim_Print(( dump_msg, IO_IIP.ACESEN0.word ));
		Im_IIP_Off_Pclk();

		ercd = Im_IIP_Set_AccessEnable(accen_bitmask[loopcnt], 0);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		Im_IIP_On_Pclk();
		Ddim_Print(( dump_msg, IO_IIP.ACESEN0.word ));
		Im_IIP_Off_Pclk();
	}

	ercd = Im_IIP_Close_SWTRG(unit_bitmask, 0, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_36( VOID)
{
	INT32 ercd;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
//	static const CHAR		dump_msg[] = "LKEN=%u\n";

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG(unit_bitmask, 0, 0, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

#if 0	// B2Y Link not support
	ercd = Im_IIP_Set_B2YLinkEnable( 1 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	Im_IIP_On_Pclk();
	Ddim_Print(( dump_msg, IO_IIP.IZACTL1.bit.LKEN ));
	Im_IIP_Off_Pclk();

	ercd = Im_IIP_Set_B2YLinkEnable( 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	Im_IIP_On_Pclk();
	Ddim_Print(( dump_msg, IO_IIP.IZACTL1.bit.LKEN ));
	Im_IIP_Off_Pclk();
#endif	// B2Y Link not support

	ercd = Im_IIP_Close_SWTRG(unit_bitmask, 0, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

#ifdef CO_DEBUG_ON_PC
INT32 CT_Im_IIP_1_1_37( VOID )
{
	INT32 ercd;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
	static const CHAR dump_msg1[] = "B2Y=0x%x AFN0=0x%x AFN1=0x%x AFN2=0x%x AFN3=0x%x FR0=0x%x FR1=0x%x\n";
	static const CHAR dump_msg2[] = "LD0=0x%x LD1=0x%x LD2=0x%x LD3=0x%x LD4=0x%x LD5=0x%x LD6=0x%x FLT=0x%x\n";
	T_IM_IIP_GENLINE genline;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	IO_IIP.GENLINE.GENLINE1.bit.B2Y_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE1.bit.AFN0_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE1.bit.AFN1_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE1.bit.AFN2_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE2.bit.AFN3_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE2.bit.FR0_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE2.bit.FR1_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE2.bit.LD0_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE3.bit.LD1_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE3.bit.LD2_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE3.bit.LD3_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE3.bit.LD4_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE4.bit.LD5_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE4.bit.LD6_OUTLINENO = 0x3FFF;
	IO_IIP.GENLINE.GENLINE4.bit.FLT_OUTLINENO = 0x3FFF;

	ercd = Im_IIP_Get_Genline( &genline );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	Ddim_Print(( dump_msg1,
					genline.b2y_outlineno,
					genline.afn_outlineno[0],
					genline.afn_outlineno[1],
					genline.afn_outlineno[2],
					genline.afn_outlineno[3],
					genline.frect_outlineno[0],
					genline.frect_outlineno[1]
			));
	Ddim_Print(( dump_msg2,
					genline.ld_outlineno[0],
					genline.ld_outlineno[1],
					genline.ld_outlineno[2],
					genline.ld_outlineno[3],
					genline.ld_outlineno[4],
					genline.ld_outlineno[5],
					genline.ld_outlineno[6],
					genline.flt_outlineno
			));

	IO_IIP.GENLINE.GENLINE1.bit.B2Y_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE1.bit.AFN0_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE1.bit.AFN1_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE1.bit.AFN2_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE2.bit.AFN3_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE2.bit.FR0_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE2.bit.FR1_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE2.bit.LD0_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE3.bit.LD1_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE3.bit.LD2_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE3.bit.LD3_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE3.bit.LD4_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE4.bit.LD5_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE4.bit.LD6_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE4.bit.FLT_OUTLINENO = 0;

	ercd = Im_IIP_Get_Genline( &genline );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	Ddim_Print(( dump_msg1,
					genline.b2y_outlineno,
					genline.afn_outlineno[0],
					genline.afn_outlineno[1],
					genline.afn_outlineno[2],
					genline.afn_outlineno[3],
					genline.frect_outlineno[0],
					genline.frect_outlineno[1]
			));
	Ddim_Print(( dump_msg2,
					genline.ld_outlineno[0],
					genline.ld_outlineno[1],
					genline.ld_outlineno[2],
					genline.ld_outlineno[3],
					genline.ld_outlineno[4],
					genline.ld_outlineno[5],
					genline.ld_outlineno[6],
					genline.flt_outlineno
			));

	IO_IIP.GENLINE.GENLINE1.bit.B2Y_OUTLINENO = 0;
	IO_IIP.GENLINE.GENLINE1.bit.AFN0_OUTLINENO = 1;
	IO_IIP.GENLINE.GENLINE1.bit.AFN1_OUTLINENO = 2;
	IO_IIP.GENLINE.GENLINE1.bit.AFN2_OUTLINENO = 3;
	IO_IIP.GENLINE.GENLINE2.bit.AFN3_OUTLINENO = 4;
	IO_IIP.GENLINE.GENLINE2.bit.FR0_OUTLINENO = 5;
	IO_IIP.GENLINE.GENLINE2.bit.FR1_OUTLINENO = 6;
	IO_IIP.GENLINE.GENLINE2.bit.LD0_OUTLINENO = 7;
	IO_IIP.GENLINE.GENLINE3.bit.LD1_OUTLINENO = 8;
	IO_IIP.GENLINE.GENLINE3.bit.LD2_OUTLINENO = 9;
	IO_IIP.GENLINE.GENLINE3.bit.LD3_OUTLINENO = 10;
	IO_IIP.GENLINE.GENLINE3.bit.LD4_OUTLINENO = 11;
	IO_IIP.GENLINE.GENLINE4.bit.LD5_OUTLINENO = 12;
	IO_IIP.GENLINE.GENLINE4.bit.LD6_OUTLINENO = 13;
	IO_IIP.GENLINE.GENLINE4.bit.FLT_OUTLINENO = 14;

	ercd = Im_IIP_Get_Genline( &genline );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	Ddim_Print(( dump_msg1,
					genline.b2y_outlineno,
					genline.afn_outlineno[0],
					genline.afn_outlineno[1],
					genline.afn_outlineno[2],
					genline.afn_outlineno[3],
					genline.frect_outlineno[0],
					genline.frect_outlineno[1]
			));
	Ddim_Print(( dump_msg2,
					genline.ld_outlineno[0],
					genline.ld_outlineno[1],
					genline.ld_outlineno[2],
					genline.ld_outlineno[3],
					genline.ld_outlineno[4],
					genline.ld_outlineno[5],
					genline.ld_outlineno[6],
					genline.flt_outlineno
			));

	// check: result = 0x0C000001
	ercd = Im_IIP_Get_Genline( NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
INT32 CT_Im_IIP_1_1_38( VOID )
{
	INT32 ercd;
	UINT32 loopcnt;
	UINT32 loopcnt2;
	struct
	{
		ULONG dtout_mon_lo;
		ULONG dtout_mon_hi;
		ULONG wait_mon_lo;
		ULONG wait_mon_hi;
		ULONG pdc_dtout_mon_0;
		ULONG pdc_dtout_mon_1;
		ULONG pdc_dtout_mon_2;
		ULONG pdc_rdy_mon_0;
		ULONG pdc_rdy_mon_1;
		ULONG pdc_rdy_mon_2;
	}param_tbl[] =
	{
		[0] =
		{
			.dtout_mon_lo = 0xFFFFFFFFul,
			.dtout_mon_hi = 0xFFFFFFFFul,
			.wait_mon_lo = 0xFFFFFFFFul,
			.wait_mon_hi = 0xFFFFFFFFul,
			.pdc_dtout_mon_0 = 0x7FFFul,
			.pdc_dtout_mon_1 = 0x7FFFul,
			.pdc_dtout_mon_2 = 0x7FFFul,
			.pdc_rdy_mon_0 = 0x7FFFul,
			.pdc_rdy_mon_1 = 0x7FFFul,
			.pdc_rdy_mon_2 = 0x7FFFul,
		},
		[1] =
		{
			.dtout_mon_lo = 0,
			.dtout_mon_hi = 0,
			.wait_mon_lo = 0,
			.wait_mon_hi = 0,
			.pdc_dtout_mon_0 = 0,
			.pdc_dtout_mon_1 = 0,
			.pdc_dtout_mon_2 = 0,
			.pdc_rdy_mon_0 = 0,
			.pdc_rdy_mon_1 = 0,
			.pdc_rdy_mon_2 = 0,
		},
		[2] =
		{
			.dtout_mon_lo = 1,
			.dtout_mon_hi = 2,
			.wait_mon_lo = 3,
			.wait_mon_hi = 4,
			.pdc_dtout_mon_0 = 5,
			.pdc_dtout_mon_1 = 6,
			.pdc_dtout_mon_2 = 7,
			.pdc_rdy_mon_0 = 8,
			.pdc_rdy_mon_1 = 9,
			.pdc_rdy_mon_2 = 10,
		},
	};
	T_IM_IIP_DEBUG_MONITOR monitor_val;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	for( loopcnt = 0; loopcnt < (sizeof(param_tbl) / sizeof(param_tbl[0])); loopcnt++ )
	{
		Ddim_Print(( "** param%u\n", loopcnt ));

		IO_IIP.DTOUT_MON.bit.DTOUT_MON_LO = param_tbl[loopcnt].dtout_mon_lo;
		IO_IIP.DTOUT_MON.bit.DTOUT_MON_HI = param_tbl[loopcnt].dtout_mon_hi;
		IO_IIP.WAIT_MON.bit.WAIT_MON_LO = param_tbl[loopcnt].wait_mon_lo;
		IO_IIP.WAIT_MON.bit.WAIT_MON_HI = param_tbl[loopcnt].wait_mon_hi;
		IO_IIP.PDC_DTOUT_MON.PDC_DTOUT_MON1.bit.PDC_DTOUT_MON_0 = param_tbl[loopcnt].pdc_dtout_mon_0;
		IO_IIP.PDC_DTOUT_MON.PDC_DTOUT_MON1.bit.PDC_DTOUT_MON_1 = param_tbl[loopcnt].pdc_dtout_mon_1;
		IO_IIP.PDC_DTOUT_MON.PDC_DTOUT_MON2.bit.PDC_DTOUT_MON_2 = param_tbl[loopcnt].pdc_dtout_mon_2;
		IO_IIP.PDC_RDY_MON.PDC_RDY_MON1.bit.PDC_RDY_MON_0 = param_tbl[loopcnt].pdc_rdy_mon_0;
		IO_IIP.PDC_RDY_MON.PDC_RDY_MON1.bit.PDC_RDY_MON_1 = param_tbl[loopcnt].pdc_rdy_mon_1;
		IO_IIP.PDC_RDY_MON.PDC_RDY_MON2.bit.PDC_RDY_MON_2 = param_tbl[loopcnt].pdc_rdy_mon_2;

		ercd = Im_IIP_Get_Debug_Monitor( &monitor_val );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		Ddim_Print(( "data_out_port = 0x%llx\n", monitor_val.data_out_port ));
		Ddim_Print(( "waiting_port = 0x%llx\n", monitor_val.waiting_port ));
		for( loopcnt2 = 0; loopcnt2 < D_IM_IIP_CACHE_MAXNUM; loopcnt2++ )
		{
			Ddim_Print(( "imgcache_data_out[%u] = 0x%x\n", loopcnt2, monitor_val.imgcache_data_out[loopcnt2] ));
		}
		for( loopcnt2 = 0; loopcnt2 < D_IM_IIP_CACHE_MAXNUM; loopcnt2++ )
		{
			Ddim_Print(( "imgcache_ready[%u] = 0x%x\n", loopcnt2, monitor_val.imgcache_ready[loopcnt2] ));
		}
	}

	return D_DDIM_OK;
}
#endif //CO_DEBUG_ON_PC
#endif //CO_CT_IM_IIP_DISABLE

CtImIip5* ct_im_iip_5_get(void)
{
	static CtImIip5* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_5, sizeof(CtImIip5Private));
	}

	return self;
}
