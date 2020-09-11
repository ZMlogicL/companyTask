/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : maoguangkun
*@brief : CtImIip4
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
#include "ctimiip4.h"


//K_TYPE_DEFINE_WITH_PRIVATE(CtImIip4, ct_im_iip_4)
//#define CT_IM_IIP_4_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImIip4Private, CT_TYPE_IM_IIP_4))


struct _CtImIip4Private
{

};


#ifndef CO_CT_IM_IIP_DISABLE
static VOID 		ct_im_iip_print_hist(volatile ULONG (*hist_addr)[D_IM_IIP_HIST_MAXCOUNTS]);
#endif //CO_CT_IM_IIP_DISABLE


/********
 * IMPL
 */
//static void ct_im_iip_4_constructor(CtImIip4 *self)
//{
//	CtImIip4Private *priv = CT_IM_IIP_4_GET_PRIVATE(self);
//}
//
//static void ct_im_iip_4_destructor(CtImIip4 *self)
//{
//	CtImIip4Private *priv = CT_IM_IIP_4_GET_PRIVATE(self);
//}

#ifndef CO_CT_IM_IIP_DISABLE
static VOID ct_im_iip_print_hist(volatile ULONG (*hist_addr)[D_IM_IIP_HIST_MAXCOUNTS])
{
	UINT32 loopcnt;
	UINT32 count;

	Im_IIP_On_Pclk();
	Im_IIP_On_Hclk();

	count = sizeof(*hist_addr) / sizeof((*hist_addr)[0]);
	for (loopcnt = 0; loopcnt < count; loopcnt++)
	{
		Ddim_Print(( "0x%lx ", (*hist_addr)[loopcnt] ));
		if ((loopcnt % 16) == 15)
		{
			Ddim_Print(( "\n" ));
		}
	}

	Im_IIP_Off_Hclk();
	Im_IIP_Off_Pclk();

	Ddim_Print(( "\n" ));
}
#endif //CO_CT_IM_IIP_DISABLE


/**********
 * PUBLIC
 */
#ifndef CO_CT_IM_IIP_DISABLE
INT32 CT_Im_IIP_1_1_23( VOID)
{
	INT32 ercd;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	CHAR clk_dump_msg[] = "PCLK=%u ICLK=%u CLK=%u\n";
#endif
	CHAR clk_dump_msg1[] = "TRG=%u ABORT=%u\n";
	CHAR clk_dump_msg2[] = "IZARAC=%u CA1RAC=%u CA2RAC=%u\n";
	UINT32 wait_factor_2 = 0;
	UINT32 wait_factor_3 = 0;
	UINT32 wait_factor_6 = 0;

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

	ercd = Im_IIP_Set_Interrupt( D_IM_IIP_INT_FACTOR_SL5END | D_IM_IIP_INT_FACTOR_SL0END | D_IM_IIP_INT_FACTOR_SL8END, 1);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	ct_im_iip_print_base();

	Ddim_Print(( "** Start test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Start_SWTRG(E_IM_IIP_UNIT_ID_SL0, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 3
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 1
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 0 0 0
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif
	Im_IIP_On_Pclk();
	Ddim_Print(( "UNITINF TRG = %u\n", IO_IIP.UNITINFTBL_SL0.UNITINFTBL0.bit.SWTRG ));
	Im_IIP_Off_Pclk();

	Ddim_Print(( "** Start test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Start_SWTRG(E_IM_IIP_UNIT_ID_SL5, D_IM_IIP_SWTRG_ON);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Im_IIP_On_Pclk();
	// check: value is 3
	Ddim_Print(( clk_dump_msg1, IO_IIP.IZACTL1.bit.TRG, IO_IIP.IZACTL2.bit.ABORT ));
	// check: value is 1
	Ddim_Print(( clk_dump_msg2, IO_IIP.ACESEN0.bit.IZARAC, IO_IIP.ACESEN0.bit.CA1RAC, IO_IIP.ACESEN0.bit.CA2RAC ));
	Im_IIP_Off_Pclk();
	// check: value is 0 0 0
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
	Ddim_Print(( clk_dump_msg, Dd_Top_Get_CLKSTOP3_IIPAP(), Dd_Top_Get_CLKSTOP3_IIPAX(), Dd_Top_Get_CLKSTOP3_IIPCK() ));
#endif
	Im_IIP_On_Pclk();
	Ddim_Print(( "UNITINF TRG = %u\n", IO_IIP.UNITINFTBL_SL5.UNITINFTBL0.bit.SWTRG ));
	Im_IIP_Off_Pclk();

#ifdef CO_DEBUG_ON_PC
	IO_IIP.INTIZ1.bit.__SL0FF = 1;
	IO_IIP.INTIZ1.bit.__SL5FF = 1;
	IO_IIP.INTIZ1.bit.__SL0MF = 1;
	Im_IIP_Int_Handler();
#endif // CO_DEBUG_ON_PC

	Ddim_Print(( "** WaitEnd test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Wait_End(&wait_factor_3, D_IM_IIP_INT_FACTOR_SL5END, D_IM_IIP_AND_WAIT, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x wait_factor_3 = 0x%x\n", ercd, wait_factor_3 ));

	Ddim_Print(( "** WaitEnd test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Wait_End(&wait_factor_2, D_IM_IIP_INT_FACTOR_SL0END, D_IM_IIP_AND_WAIT, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x wait_factor_2 = 0x%x\n", ercd, wait_factor_2 ));

	Ddim_Print(( "** WaitEnd test\n" ));
	// check: result = 0x0C000013
	ercd = Im_IIP_Wait_End(&wait_factor_6, D_IM_IIP_INT_FACTOR_SL0END, D_IM_IIP_AND_WAIT, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x wait_factor_6 = 0x%x\n", ercd, wait_factor_6 ));

	Ddim_Print(( "** WaitEnd test\n" ));
	// check: result = 0x0C000013
	ercd = Im_IIP_Wait_End(&wait_factor_2, D_IM_IIP_INT_FACTOR_SL0_LINEEND, D_IM_IIP_AND_WAIT, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x wait_factor_2 = 0x%x\n", ercd, wait_factor_2 ));

	ercd = Im_IIP_Set_Interrupt( D_IM_IIP_INT_FACTOR_SL0_LINEEND, 1);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
#ifdef CO_DEBUG_ON_PC
	Im_IIP_Int_Handler();
#endif // CO_DEBUG_ON_PC

	Ddim_Print(( "** WaitEnd test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Wait_End(&wait_factor_2, D_IM_IIP_INT_FACTOR_SL0_LINEEND, D_IM_IIP_AND_WAIT, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x wait_factor_2 = 0x%x\n", ercd, wait_factor_2 ));
	ct_im_iip_print_base();

	Ddim_Print(( "** Close test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Close_SWTRG( D_IM_IIP_PARAM_PLDUNIT_SL0, 0, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	ct_im_iip_print_base();

	Ddim_Print(( "** Close test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Close_SWTRG( D_IM_IIP_PARAM_PLDUNIT_SL5, 0, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	ct_im_iip_print_base();

	Ddim_Print(( "** Close test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Close_SWTRG(0xFFFFull & ~(D_IM_IIP_PARAM_PLDUNIT_SL0 | D_IM_IIP_PARAM_PLDUNIT_SL5), 0, 0);
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
	ct_im_iip_print_base();

	Ddim_Print(( "** Close test\n" ));
	// check: result = 0x0
	ercd = Im_IIP_Close_SWTRG(0xFFFFFFFFFFFF0000ull & ~(D_IM_IIP_PARAM_PLDUNIT_SL0 | D_IM_IIP_PARAM_PLDUNIT_SL5), 0, 0);
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
	ct_im_iip_print_base();

	return D_DDIM_OK;
}

INT32 CT_Im_IIP_1_1_24( VOID)
{
	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	return CT_Im_IIP_1_1_23();
}

INT32 CT_Im_IIP_1_1_25( VOID)
{
	INT32 ercd;
	UINT32 loopcnt;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
	UINT32 param_tbl_idx;
	UINT32 hist_resol_max;
	struct
	{
		E_IM_IIP_OPEN_RES res_bitmask;
		UINT32 hist_type_idx;
		volatile ULONG (*hist_array)[D_IM_IIP_HIST_MAXCOUNTS];		// Pointer of HISTGRAM array.
		UCHAR clear_hist_func_param[4];
	} param_tbl[] = { [0] = { .res_bitmask = E_IM_IIP_OPEN_RES_HIST_0, .hist_type_idx = 0, .hist_array = &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[0], .clear_hist_func_param = { D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF }, }, [1] = { .res_bitmask = E_IM_IIP_OPEN_RES_HIST_1, .hist_type_idx = 1, .hist_array = &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[1], .clear_hist_func_param = { D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF }, }, [2] = { .res_bitmask = E_IM_IIP_OPEN_RES_HIST_2, .hist_type_idx = 2, .hist_array = &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[2], .clear_hist_func_param = { D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_OFF }, }, [3] = { .res_bitmask = E_IM_IIP_OPEN_RES_HIST_3, .hist_type_idx = 3, .hist_array = &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[3], .clear_hist_func_param = { D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_ON }, }, };

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG(unit_bitmask, 0, 0, 1000);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	for (param_tbl_idx = 0; param_tbl_idx < (sizeof(param_tbl) / sizeof(param_tbl[0])); param_tbl_idx++)
	{
		Ddim_Print(( "** hist[%u]\n", param_tbl[param_tbl_idx].hist_type_idx ));

		hist_resol_max = sizeof((*param_tbl[param_tbl_idx].hist_array)) / sizeof((*param_tbl[param_tbl_idx].hist_array)[0]);

		ercd = Im_IIP_Set_AccessEnable(param_tbl[param_tbl_idx].res_bitmask, 1);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		Im_IIP_On_Pclk();
		Im_IIP_On_Hclk();
		for (loopcnt = 0; loopcnt < hist_resol_max; loopcnt++)
		{
			(*param_tbl[param_tbl_idx].hist_array)[loopcnt] = 0xFFFFFFul;
		}
		Im_IIP_Off_Hclk();
		Im_IIP_Off_Pclk();

#ifdef CO_DEBUG_ON_PC
		// check result = 0x0C000100
		IO_IIP.AHBSTS.bit.HISSTS = 1;
		ercd = Im_IIP_Clear_HISTGRAM(
				param_tbl[param_tbl_idx].clear_hist_func_param[0],
				param_tbl[param_tbl_idx].clear_hist_func_param[1],
				param_tbl[param_tbl_idx].clear_hist_func_param[2],
				param_tbl[param_tbl_idx].clear_hist_func_param[3]
		);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		IO_IIP.AHBSTS.bit.HISSTS = 0;
#endif //CO_DEBUG_ON_PC

		// check histgram value = 0xFFFFFF
		ct_im_iip_print_hist(param_tbl[param_tbl_idx].hist_array);

		// check histgram value = 0
		ercd = Im_IIP_Clear_HISTGRAM(param_tbl[param_tbl_idx].clear_hist_func_param[0], param_tbl[param_tbl_idx].clear_hist_func_param[1], param_tbl[param_tbl_idx].clear_hist_func_param[2], param_tbl[param_tbl_idx].clear_hist_func_param[3]);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		ct_im_iip_print_hist(param_tbl[param_tbl_idx].hist_array);

		ercd = Im_IIP_Set_AccessEnable(param_tbl[param_tbl_idx].res_bitmask, 0);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	}

	//
	// MONINIT
	//
	Ddim_Print(( "** moninit\n" ));

	ercd = Im_IIP_Set_AccessEnable(E_IM_IIP_OPEN_RES_HIST_0 | E_IM_IIP_OPEN_RES_HIST_1 | E_IM_IIP_OPEN_RES_HIST_2 | E_IM_IIP_OPEN_RES_HIST_3, 1);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

#ifdef CO_DEBUG_ON_PC
	// check result = 0x0C000100
	IO_IIP.AHBSTS.bit.HISSTS = 1;
	ercd = Im_IIP_Clear_HISTGRAM( D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	IO_IIP.AHBSTS.bit.HISSTS = 0;

	Ddim_Print(( "MONINIT = 0x%x\n", IO_IIP.MONINIT.bit.INIT ));

	// check clear monitor1 register
	IO_IIP.MONINIT.bit.INIT = 0;
	ercd = Im_IIP_Clear_HISTGRAM( D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_ON );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Ddim_Print(( "MONINIT = 0x%x\n", IO_IIP.MONINIT.bit.INIT ));
	IO_IIP.MONINIT.bit.INIT = 0;
#endif //CO_DEBUG_ON_PC

	ercd = Im_IIP_Set_AccessEnable(E_IM_IIP_OPEN_RES_HIST_0 | E_IM_IIP_OPEN_RES_HIST_1 | E_IM_IIP_OPEN_RES_HIST_2 | E_IM_IIP_OPEN_RES_HIST_3, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	ercd = Im_IIP_Close_SWTRG(unit_bitmask, 0, 0);
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}

#ifdef CO_CT_IM_IIP_ENABLE_1_1_26
INT32 CT_Im_IIP_1_1_26( VOID )
{
	INT32 ercd;
	UINT32 loopcnt;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;
	static volatile ULONG g_ct_im_iip_hist_buf[D_IM_IIP_HIST_MAXCOUNTS];
	UINT32 param_tbl_idx;
	UINT32 hist_resol_max;
	struct
	{
		E_IM_IIP_OPEN_RES res_bitmask;
		UINT32 hist_type_idx;
		volatile ULONG (*hist_array)[D_IM_IIP_HIST_MAXCOUNTS];		// Pointer of HISTGRAM array.
		UCHAR clear_hist_func_param[4];
		volatile ULONG* get_hist_func_param[4];
	}param_tbl[] =
	{
		[0] =
		{
			.res_bitmask = E_IM_IIP_OPEN_RES_HIST_0,
			.hist_type_idx = 0,
			.hist_array = &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[0],
			.clear_hist_func_param =
			{	D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF},
			.get_hist_func_param =
			{	g_ct_im_iip_hist_buf, NULL, NULL, NULL},
		},
		[1] =
		{
			.res_bitmask = E_IM_IIP_OPEN_RES_HIST_1,
			.hist_type_idx = 1,
			.hist_array = &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[1],
			.clear_hist_func_param =
			{	D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF},
			.get_hist_func_param =
			{	NULL, g_ct_im_iip_hist_buf, NULL, NULL},
		},
		[2] =
		{
			.res_bitmask = E_IM_IIP_OPEN_RES_HIST_2,
			.hist_type_idx = 2,
			.hist_array = &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[2],
			.clear_hist_func_param =
			{	D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_ON, D_IM_IIP_ENABLE_OFF},
			.get_hist_func_param =
			{	NULL, NULL, g_ct_im_iip_hist_buf, NULL},
		},
		[3] =
		{
			.res_bitmask = E_IM_IIP_OPEN_RES_HIST_3,
			.hist_type_idx = 3,
			.hist_array = &IO_IIP_TBL.HISTGRAM.HISTGRAM.word[3],
			.clear_hist_func_param =
			{	D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_OFF, D_IM_IIP_ENABLE_ON},
			.get_hist_func_param =
			{	NULL, NULL, NULL, g_ct_im_iip_hist_buf},
		},
	};

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	for( param_tbl_idx = 0; param_tbl_idx < (sizeof(param_tbl) / sizeof(param_tbl[0])); param_tbl_idx++ )
	{
		Ddim_Print(( "** hist[%u]\n", param_tbl[param_tbl_idx].hist_type_idx ));

		ercd = Im_IIP_Set_AccessEnable( param_tbl[param_tbl_idx].res_bitmask, 1 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		hist_resol_max = sizeof((*param_tbl[param_tbl_idx].hist_array)) / sizeof((*param_tbl[param_tbl_idx].hist_array)[0]);

		Im_IIP_On_Pclk();
		Im_IIP_On_Hclk();
		for( loopcnt = 0; loopcnt < hist_resol_max; loopcnt++ )
		{
			(*param_tbl[param_tbl_idx].hist_array)[loopcnt] = 0xFFFFFFul;
		}
		Im_IIP_Off_Hclk();
		Im_IIP_Off_Pclk();

#ifdef CO_DEBUG_ON_PC
		// check result = 0x0C000100
		IO_IIP.AHBSTS.bit.HISSTS = 1;
		ercd = Im_IIP_Get_HISTGRAM(
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[0],
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[1],
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[2],
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[3]
		);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
		IO_IIP.AHBSTS.bit.HISSTS = 0;
#endif //CO_DEBUG_ON_PC

		// check get histgram = 0xFFFFFF
		ercd = Im_IIP_Get_HISTGRAM(
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[0],
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[1],
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[2],
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[3]
		);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		ct_im_iip_print_hist( &g_ct_im_iip_hist_buf );

		// check result = 0x0
		ercd = Im_IIP_Clear_HISTGRAM(
				param_tbl[param_tbl_idx].clear_hist_func_param[0],
				param_tbl[param_tbl_idx].clear_hist_func_param[1],
				param_tbl[param_tbl_idx].clear_hist_func_param[2],
				param_tbl[param_tbl_idx].clear_hist_func_param[3]
		);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		// check get histgram = 0
		ercd = Im_IIP_Get_HISTGRAM(
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[0],
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[1],
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[2],
				(ULONG*)param_tbl[param_tbl_idx].get_hist_func_param[3]
		);
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

		ct_im_iip_print_hist( &g_ct_im_iip_hist_buf );

		ercd = Im_IIP_Set_AccessEnable( param_tbl[param_tbl_idx].res_bitmask, 0 );
		Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));
	}

	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_CT_IM_IIP_ENABLE_1_1_26

#ifdef CO_DEBUG_ON_PC
INT32 CT_Im_IIP_1_1_27( VOID )
{
	INT32 ercd;
	UCHAR histmax;
	ULLONG unit_bitmask = 0xFFFFFFFFFFFFFFFFull;

	Ddim_Print(( D_IM_IIP_FUNC_NAME "\n" ));

	ercd = Im_IIP_Open_SWTRG( unit_bitmask, 0, 0, 1000 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	Ddim_Print(( "** HISTMAX0\n" ));
	IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_0 = 0xFF;

	// check get HISTMAX0
	ercd = Im_IIP_Get_HISTMAX( &histmax, NULL, NULL, NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x histmax=0x%x\n", ercd, histmax ));

	IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_0 = 0;

	// check get HISTMAX0
	ercd = Im_IIP_Get_HISTMAX( &histmax, NULL, NULL, NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x histmax=0x%x\n", ercd, histmax ));

	Ddim_Print(( "** HISTMAX1\n" ));
	IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_1 = 0xFF;

	// check get HISTMAX1
	ercd = Im_IIP_Get_HISTMAX( NULL, &histmax, NULL, NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x histmax=0x%x\n", ercd, histmax ));

	IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_1 = 0;

	// check get HISTMAX1
	ercd = Im_IIP_Get_HISTMAX( NULL, &histmax, NULL, NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x histmax=0x%x\n", ercd, histmax ));

	Ddim_Print(( "** HISTMAX2\n" ));
	IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_2 = 0xFF;

	// check get HISTMAX2
	ercd = Im_IIP_Get_HISTMAX( NULL, NULL, &histmax, NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x histmax=0x%x\n", ercd, histmax ));

	IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_2 = 0;

	// check get HISTMAX2
	ercd = Im_IIP_Get_HISTMAX( NULL, NULL, &histmax, NULL );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x histmax=0x%x\n", ercd, histmax ));

	Ddim_Print(( "** HISTMAX3\n" ));
	IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_3 = 0xFF;

	// check get HISTMAX3
	ercd = Im_IIP_Get_HISTMAX( NULL, NULL, NULL, &histmax );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x histmax=0x%x\n", ercd, histmax ));

	IO_IIP.HISTMAX.HISTMAX1.bit.HISTMAX_3 = 0;

	// check get HISTMAX3
	ercd = Im_IIP_Get_HISTMAX( NULL, NULL, NULL, &histmax );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x histmax=0x%x\n", ercd, histmax ));

	ercd = Im_IIP_Close_SWTRG( unit_bitmask, 0, 0 );
	Ddim_Print(( D_IM_IIP_FUNC_NAME "result = 0x%x\n", ercd ));

	return D_DDIM_OK;
}
#endif //CO_DEBUG_ON_PC
#endif //CO_CT_IM_IIP_DISABLE

CtImIip4* ct_im_iip_4_get(void)
{
	static CtImIip4* self = NULL;

	if (!self) {
//		self = k_object_new_with_private(CT_TYPE_IM_IIP_4, sizeof(CtImIip4Private));
	}

	return self;
}
