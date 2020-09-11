/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImIip3
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
#include "ctimiip3.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIip3, ct_im_iip_3)
//#define CT_IM_IIP_3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIip3Private, CT_TYPE_IM_IIP_3))


struct _CtImIip3Private
{

};


/********
 * IMPL
 */
//static void ct_im_iip_3_constructor(CtImIip3 *self)
//{
//	CtImIip3Private *priv = CT_IM_IIP_3_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_3_destructor(CtImIip3 *self)
//{
//	CtImIip3Private *priv = CT_IM_IIP_3_GET_PRIVATE(self);
//}


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
INT32 CT_Im_IIP_1_1_17( VOID)
{
	UINT32 enable_interrupt_flag;
	INT32 ercd;
	UINT32 loopcnt;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
	UINT32 int_factor_array[] = { ( D_IM_IIP_INT_FACTOR_SL0_LINEEND | D_IM_IIP_INT_FACTOR_SL1_LINEEND | D_IM_IIP_INT_FACTOR_SL2_LINEEND | D_IM_IIP_INT_FACTOR_SL3_LINEEND | D_IM_IIP_INT_FACTOR_SL4_LINEEND | D_IM_IIP_INT_FACTOR_SL5_LINEEND | D_IM_IIP_INT_FACTOR_SL6_LINEEND | D_IM_IIP_INT_FACTOR_SL7_LINEEND | D_IM_IIP_INT_FACTOR_SL8_LINEEND),
	D_IM_IIP_INT_FACTOR_SL0_LINEEND,
	D_IM_IIP_INT_FACTOR_SL1_LINEEND,
	D_IM_IIP_INT_FACTOR_SL2_LINEEND,
	D_IM_IIP_INT_FACTOR_SL3_LINEEND,
	D_IM_IIP_INT_FACTOR_SL4_LINEEND,
	D_IM_IIP_INT_FACTOR_SL5_LINEEND,
	D_IM_IIP_INT_FACTOR_SL6_LINEEND,
	D_IM_IIP_INT_FACTOR_SL7_LINEEND,
	D_IM_IIP_INT_FACTOR_SL8_LINEEND, };

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG(unit_bitmask, 0, 0, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	for (loopcnt = 0; loopcnt < (sizeof(int_factor_array) / sizeof(int_factor_array[0])); loopcnt++)
	{
		enable_interrupt_flag = int_factor_array[loopcnt];

		Ddim_Print(( D_IM_IIP_FUNC_NAME "** flag bit = 0x%x\n", enable_interrupt_flag ));

		// check register max value
		ercd = Im_IIP_Set_SLIntLines(enable_interrupt_flag, 0x3FFFFFFF);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_base();

		// check register min value
		ercd = Im_IIP_Set_SLIntLines(enable_interrupt_flag, 0);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		ct_im_iip_print_base();
	}

	ercd = Im_IIP_Close_SWTRG(unit_bitmask, 0, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_19( VOID)
{
	INT32 ercd;
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	CHAR clk_dump_msg[] = "PCLK=%u ICLK=%u CLK=%u\n";
#endif
	CHAR clk_dump_msg1[] = "TRG=%u ABORT=%u\n";
	CHAR clk_dump_msg2[] = "IZARAC=%u CA1RAC=%u CA2RAC=%u\n";

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	// check: result = 0x0
	ercd = Im_IIP_Open(100);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	// !!! Need set Unit and Pixid parameter when physical or emnulator using.

	Ddim_Print(( "** Start test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Start();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 3
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 1
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 0 0
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	Ddim_Print(( "** Re-Start test\n" ));
	// check: result = 0x0C000100
	ercd = Im_IIP_Start();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 3
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 1
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 0 0
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	Ddim_Print(( "** Stop test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Stop( D_IM_IIP_STOP);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 2
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 0
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 1 1
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	Ddim_Print(( "** Aobrt test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Start();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	// check: result = 0x0
	ercd = Im_IIP_Stop( D_IM_IIP_ABORT);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 2
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 0
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 1 1
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	// check: result = 0x0
	ercd = Im_IIP_Close();
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_20( VOID)
{
	INT32 ercd;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	CHAR clk_dump_msg[] = "PCLK=%u ICLK=%u CLK=%u\n";
#endif
	CHAR clk_dump_msg1[] = "TRG=%u ABORT=%u\n";
	CHAR clk_dump_msg2[] = "IZARAC=%u CA1RAC=%u CA2RAC=%u\n";

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	// check: result = 0x0
	ercd = Im_IIP_Open_SWTRG(unit_bitmask, 0, 0, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	// !!! Need set Unit and Pixid parameter when physical or emnulator using.

	Ddim_Print(( "** Start test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_LinkStart_SWTRG(E_IM_IIP_UNIT_ID_SL2, D_IM_IIP_SWTRG_ON, D_IM_IIP_ENABLE_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 3
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 1
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 0 0
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif
	Im_IIP_On_Pclk();
	Ddim_Print(( "UNITINF TRG = %u\n", IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.SWTRG ));
	Im_IIP_Off_Pclk();

	Ddim_Print(( "** Start test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_LinkStart_SWTRG(E_IM_IIP_UNIT_ID_SL3, D_IM_IIP_SWTRG_ON, D_IM_IIP_ENABLE_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 3
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 1
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 0 0
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif
	Im_IIP_On_Pclk();
	Ddim_Print(( "UNITINF TRG = %u\n", IO_IIP.UNITINFTBL_SL3.UNITINFTBL0.bit.SWTRG ));
	Im_IIP_Off_Pclk();

	Ddim_Print(( "** Start test\n" ));
	// check: result = 0x0C000001
	ercd = Im_IIP_LinkStart_SWTRG(E_IM_IIP_UNIT_ID_MAX, D_IM_IIP_SWTRG_ON, D_IM_IIP_ENABLE_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Ddim_Print(( "** Close test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Close_SWTRG(0xFFFFull, 0, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 3
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 1
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 0 0
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	Ddim_Print(( "** Close test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Close_SWTRG(0xFFFFFFFFFFFF0000ull, 0, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 2
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 0
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 1 1
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_21( VOID)
{
	INT32 ercd;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	CHAR clk_dump_msg[] = "PCLK=%u ICLK=%u CLK=%u\n";
#endif
	CHAR clk_dump_msg1[] = "TRG=%u ABORT=%u\n";
	CHAR clk_dump_msg2[] = "IZARAC=%u CA1RAC=%u CA2RAC=%u\n";

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	// check: result = 0x0
	ercd = Im_IIP_Open_SWTRG(unit_bitmask, 0, 0, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	// !!! Need set Unit and Pixid parameter when physical or emnulator using.

	Ddim_Print(( "** Start test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Start_SWTRG(E_IM_IIP_UNIT_ID_SL2, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 3
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 1
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 0 0
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif
	Im_IIP_On_Pclk();
	Ddim_Print(( "UNITINF TRG = %u\n", IO_IIP.UNITINFTBL_SL2.UNITINFTBL0.bit.SWTRG ));
	Im_IIP_Off_Pclk();

	Ddim_Print(( "** Start test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Start_SWTRG(E_IM_IIP_UNIT_ID_SL3, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 3
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 1
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 0 0
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif
	Im_IIP_On_Pclk();
	Ddim_Print(( "UNITINF TRG = %u\n", IO_IIP.UNITINFTBL_SL3.UNITINFTBL0.bit.SWTRG ));
	Im_IIP_Off_Pclk();

	Ddim_Print(( "** Start test\n" ));
	// check: result = 0x0C000001
	ercd = Im_IIP_Start_SWTRG(E_IM_IIP_UNIT_ID_MAX, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Ddim_Print(( "** Close test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Close_SWTRG(0xFFFFull, 0, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 3
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 1
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 0 0
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	Ddim_Print(( "** Close test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Close_SWTRG(0xFFFFFFFFFFFF0000ull, 0, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 2
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 0
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 1 1 1
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_22( VOID)
{
	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	return CT_Im_IIP_1_1_19();
}
#endif //CO_CT_IM_IIP_DISABLE

CtImIip3* ct_im_iip_3_get(void)
{
	static CtImIip3* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_3, sizeof(CtImIip3Private));
	}

	return self;
}
