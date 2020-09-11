/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-04-20
*@author              :
*@brief               :snsnet
*@rely                :klib
*@function
*SNSFS文件系统，采用ETK-C语言编写
*设计的主要功能:
*@version
*1.0.0 2020年04月开始开发
*/
#include "ct_im_iip.h"
#include "im_iip.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "driver_common.h"
#include "palladium_test.h"
#include "jdsiip.h"
#include <string.h>
#include "palladiumtestiip1.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestIip1, palladium_test_iip1);

#define PALLADIUM_TEST_IIP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestIip1Private,PALLADIUM_TYPE_TEST_IIP1))
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "1_1_4"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "1_1_13"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "2_1_x"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "2_2_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "2_2_2"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "2_4_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "2_5_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "2_5_2"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "2_5_3"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "2_5_4"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "2_5_5"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "2_6_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "2_7_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "3_1_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "3_1_2"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "3_1_3"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "3_1_4"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "3_2_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "3_2_2"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "3_2_3"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "4_1_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "5_1_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "5_1_2"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "6_1_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "6_2_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "7_1_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "7_1_2"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "8_1_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "8_1_2"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "8_1_3"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "9_1_1"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "9_1_2"
#undef PalladiumTestIip1_TEST_NO
#define PalladiumTestIip1_TEST_NO "9_2_1"

static VOID imIipRun114( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipRun1113( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest221( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest222(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest241(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest251( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest252( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest253( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest254(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest255(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest261( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest271(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest311(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest312(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest313(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest314(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest321( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest322( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest323( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest411( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest511( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest512( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest611( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest621(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest711( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest712( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest811( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest812( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static VOID imIipDoTest813(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static  VOID imIipDoTest911( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static  VOID imIipDoTest912(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
static  VOID imIipDoTest921(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );

struct _PalladiumTestIip1Private
{
		kint a;
};

static void palladium_test_iip1_constructor(PalladiumTestIip1 *self)
{
	PalladiumTestIip1Private *priv = PALLADIUM_TEST_IIP1_GET_PRIVATE(self);
	priv->a = 0;
}

static void palladium_test_iip1_destructor(PalladiumTestIip1 *self)
{
	PalladiumTestIip1Private *priv = PALLADIUM_TEST_IIP1_GET_PRIVATE(self);
		priv->a = 0;
}

static VOID imIipRun114( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	static const kuchar	S_NO_3RD_TBL[] = {
		4, // 5 same as 4
	};
	kuint32				loopcnt;
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	for( loopcnt = 0; loopcnt < (sizeof(S_NO_3RD_TBL) / sizeof(S_NO_3RD_TBL[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* IIP begin CT_Im_Iip_%u_%u_%u\n", ctNo1st, ctNo2st, S_NO_3RD_TBL[loopcnt] ));
		CT_Im_IIP_Run( ctNo1st, ctNo2st, S_NO_3RD_TBL[loopcnt] );
		Ddim_Print(( "* IIP end CT_Im_Iip_%u_%u_%u\n", ctNo1st, ctNo2st, S_NO_3RD_TBL[loopcnt] ));
	}

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipRun1113( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	static const kuchar	S_NO_3RD_TBL[] = {
		13, 16, 17, 18, 35, 36, 39, 40, // 41 same as 39
	};
	kuint32				loopcnt;

	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	for( loopcnt = 0; loopcnt < (sizeof(S_NO_3RD_TBL) / sizeof(S_NO_3RD_TBL[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* IIP begin CT_Im_Iip_%u_%u_%u\n", ctNo1st, ctNo2st, S_NO_3RD_TBL[loopcnt] ));
		CT_Im_IIP_Run( ctNo1st, ctNo2st, S_NO_3RD_TBL[loopcnt] );
		Ddim_Print(( "* IIP end CT_Im_Iip_%u_%u_%u\n", ctNo1st, ctNo2st, S_NO_3RD_TBL[loopcnt] ));
	}
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest221( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest222(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest241(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest251( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RAW16BIT_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_2_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
#ifndef CO_DEBUG_ON_PC
	memcpy( (VOID*)D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_Y,  (VOID*)D_PT_IM_IIP_IMG_SRAM_ADDR0, D_IM_IIP_VGA_YCC422_U8_BYTES );	// Copy Y
	DDIM_User_L1l2cache_Clean_Addr( D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_Y, D_IM_IIP_VGA_YCC422_U8_BYTES );
	memcpy( (VOID*)D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C, (VOID*)D_PT_IM_IIP_IMG_SRAM_ADDR1, D_IM_IIP_VGA_YCC422_U8_BYTES );	// Copy CbCr
	DDIM_User_L1l2cache_Clean_Addr( D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C, D_IM_IIP_VGA_YCC422_U8_BYTES /2 );
#endif
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest252( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_FULLHD_YCC420_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_2_TOP, D_IM_IIP_FULLHD_YCC420_U8_BYTES );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_FULLHD_YCC420_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest253( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_FULLHD_VIS_YCC420_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_2_TOP, D_IM_IIP_FULLHD_YCC420_U8_BYTES );	// afn
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_FULLHD_YCC420_U8_BYTES );	// frect0
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_3_TOP, D_IM_IIP_FULLHD_YCC420_U8_BYTES );	// frect1
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest254(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_FULLHD_VIS_YCC420_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_2_TOP, D_IM_IIP_FULLHD_YCC420_U8_BYTES );	// afn
#ifndef CO_DEBUG_ON_PC
	memcpy( (VOID*)D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_Y,  (VOID*)D_PT_IM_IIP_IMG_SRAM_ADDR0, 0x40000 );	// Copy Y 256kB
	DDIM_User_L1l2cache_Clean_Addr( D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_Y, 0x40000 );
	memcpy( (VOID*)D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C, (VOID*)D_PT_IM_IIP_IMG_SRAM_ADDR1, 0x20000 );	// Copy CbCr 128kB
	DDIM_User_L1l2cache_Clean_Addr( D_IM_IIP_IMG_MEM_ADDR_4_YCC422_U8_C, 0x20000 );
#endif
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest255(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_FULLHD_YCC420_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_2_TOP, D_IM_IIP_FULLHD_YCC420_U8_BYTES );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_FULLHD_YCC420_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest261( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, 65536 );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest271(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest311(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
#if 1
#ifndef CO_DEBUG_ON_PC
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_0_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_1_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
#endif //CO_DEBUG_ON_PC
#endif
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest312(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
#if 0
#ifndef CO_DEBUG_ON_PC
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_0_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_1_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
#endif //CO_DEBUG_ON_PC
#endif
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest313( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
#if 0
#ifndef CO_DEBUG_ON_PC
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_0_TOP, '\xee', D_IM_IIP_VGA_PLANE14BIT_BYTES );
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_1_TOP, '\xee', D_IM_IIP_VGA_PLANE14BIT_BYTES );
#endif //CO_DEBUG_ON_PC
#endif
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_PLANE14BIT_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_PLANE14BIT_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest314(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
#if 1
#ifndef CO_DEBUG_ON_PC
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_0_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_1_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
	DDIM_User_L1l2cache_Clean_Addr( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	DDIM_User_L1l2cache_Clean_Addr( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
#endif //CO_DEBUG_ON_PC
#endif
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest321( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_FULLHD_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_16_9_RIBERY_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest322( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_FULLHD_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_HD_16_9_RIBERY_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest323( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_FULLHD_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_FULLHD_RIBERY_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest411( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
#if 0
#ifndef CO_DEBUG_ON_PC
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_0_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_1_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
#endif //CO_DEBUG_ON_PC
#endif
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest511( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
#if 0
#ifndef CO_DEBUG_ON_PC
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_0_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_1_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
#endif //CO_DEBUG_ON_PC
#endif
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest512( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
#if 0
#ifndef CO_DEBUG_ON_PC
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_0_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_1_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
#endif //CO_DEBUG_ON_PC
#endif
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest611( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));

#if 0
#ifndef CO_DEBUG_ON_PC
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_0_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_4_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_1_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
#endif //CO_DEBUG_ON_PC
#endif
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest621(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U16_BYTES + D_IM_IIP_VGA_YCC422_U16_A_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_YCC422_U16_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U16_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest711( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
#if 0
#ifndef CO_DEBUG_ON_PC
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_0_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_1_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
#endif //CO_DEBUG_ON_PC
#endif
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest712( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
#if 0
#ifndef CO_DEBUG_ON_PC
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_0_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
	memset( (VOID*)D_IM_IIP_IMG_MEM_ADDR_1_TOP, '\xee', D_IM_IIP_VGA_YCC422_U8_BYTES );
#endif //CO_DEBUG_ON_PC
#endif
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest811( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RGBA4444_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_RGBA4444_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest812( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RGBA4444_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_RGBA4444_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static VOID imIipDoTest813(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static  VOID imIipDoTest911( kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static  VOID imIipDoTest912(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RAW12BIT_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_RAW12BIT_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

static  VOID imIipDoTest921(kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RGBA8888_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_RGBA8888_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2st, ctNo3st );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip1_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_RGBA8888_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

VOID palladium_test_iip1_pt_im_iip_start_clock( PalladiumTestIip1* self )
{
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_PCLOCK) || defined(CO_ACT_HCLOCK)
#else
	kuchar imIipClkCtrlCnt = 0;
	kuchar imIipHclkCtrlCnt = 0;
	kuchar imIipPclkCtrlCnt = 0;
	kuchar imIipIclkCtrlCnt = 0;
	kuchar imB2yClkCtrlCnt = 0;
	kuchar imB2yHclkCtrlCnt = 0;
	kuchar imB2yPclkCtrlCnt = 0;
	kuchar imB2yIclkCtrlCnt = 0;

	Dd_Top_Start_Clock( &imIipPclkCtrlCnt, D_IM_IIP_PCLK_REG_ADDR, ~D_IM_IIP_PCLK_REG_BIT );
	Dd_Top_Start_Clock( &imIipHclkCtrlCnt, D_IM_IIP_HCLK_REG_ADDR, ~D_IM_IIP_HCLK_REG_BIT );
	Dd_Top_Start_Clock( &imIipIclkCtrlCnt, D_IM_IIP_ICLK_REG_ADDR, ~D_IM_IIP_ICLK_REG_BIT );
	Dd_Top_Start_Clock( &imIipClkCtrlCnt,  D_IM_IIP_CLK_REG_ADDR,  ~D_IM_IIP_CLK_REG_BIT );

	Dd_Top_Start_Clock( &imB2yPclkCtrlCnt, D_IM_B2Y_PCLK_REG_ADDR, ~D_IM_B2Y_PCLK_REG_BIT );
	Dd_Top_Start_Clock( &imB2yHclkCtrlCnt, D_IM_B2Y_HCLK_REG_ADDR, ~D_IM_B2Y_HCLK_REG_BIT );
	Dd_Top_Start_Clock( &imB2yIclkCtrlCnt, D_IM_B2Y_ICLK_REG_ADDR, ~D_IM_B2Y_ICLK_REG_BIT );
	Dd_Top_Start_Clock( &imB2yClkCtrlCnt,  D_IM_B2Y_CLK_REG_ADDR,  ~D_IM_B2Y_CLK_REG_BIT );
#endif
}

VOID palladium_test_iip1_pt_im_iip_enable_gic( PalladiumTestIip1* self )
{
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT, 1, D_DD_GIC_PRI30, 1 );		// cpu=0, intid=118, enable, pri=30
	Dd_GIC_Ctrl( E_DD_GIC_INTID_IIP_INT,       1, D_DD_GIC_PRI30, 1 );		// int enable
}

VOID palladium_test_iip1_pt_im_iip_run_1_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 4:
			imIipRun114(ctNo1st, ctNo2st, ctNo3st );
			break;
		case 13:
			imIipRun1113( ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_2_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	static const kuchar	S_NO_3RD_TBL[] = {
		1, 2, 3,
	};
	kuint32				loopcnt;
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " begin\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	for( loopcnt = 0; loopcnt < (sizeof(S_NO_3RD_TBL) / sizeof(S_NO_3RD_TBL[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* IIP begin CT_Im_Iip_%u_%u_%u\n", ctNo1st, ctNo2st, S_NO_3RD_TBL[loopcnt] ));
		CT_Im_IIP_Run( ctNo1st, ctNo2st, S_NO_3RD_TBL[loopcnt] );
		Ddim_Print(( "* IIP end CT_Im_Iip_%u_%u_%u\n", ctNo1st, ctNo2st, S_NO_3RD_TBL[loopcnt] ));
	}
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Ddim_Print(( "*** IIP test " PalladiumTestIip1_TEST_NO " end\n" ));
}

VOID palladium_test_iip1_pt_im_iip_run_2_2( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest221(ctNo1st, ctNo2st, ctNo3st );
			break;
		case 2:
			imIipDoTest222( ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_2_4( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest241(ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_2_5( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
//	Im_B2Y_Init();

	switch( ctNo3st ) {
		case 1:
			imIipDoTest251(ctNo1st, ctNo2st, ctNo3st );
			break;
		case 2:
			imIipDoTest252(ctNo1st, ctNo2st, ctNo3st );
			break;
		case 3:
			imIipDoTest253(ctNo1st, ctNo2st, ctNo3st );
			break;
		case 4:
			imIipDoTest254(ctNo1st, ctNo2st, ctNo3st );
			break;
		case 5:
			imIipDoTest255( ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_2_6( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest261( ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_2_7(PalladiumTestIip1* self , kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest271(ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_3_1( PalladiumTestIip1* self , kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest311( ctNo1st, ctNo2st, ctNo3st );
			break;
		case 2:
			imIipDoTest312( ctNo1st, ctNo2st, ctNo3st );
			break;
		case 3:
			imIipDoTest313(ctNo1st, ctNo2st, ctNo3st );
			break;
		case 4:
			imIipDoTest314( ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_3_2( PalladiumTestIip1* self , kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest321(ctNo1st, ctNo2st, ctNo3st );
			break;
		case 2:
			imIipDoTest322(ctNo1st, ctNo2st, ctNo3st );
			break;
		case 3:
			imIipDoTest323( ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_4_1(PalladiumTestIip1* self , kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest411( ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}

}

VOID palladium_test_palladium_test_pt_im_iip_run_5_1(PalladiumTestIip1* self , kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest511(  ctNo1st, ctNo2st, ctNo3st );
			break;
		case 2:
			imIipDoTest512(  ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_6_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest611( ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_6_2(PalladiumTestIip1* self , kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest621(  ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_7_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest711( ctNo1st, ctNo2st, ctNo3st );
			break;
		case 2:
			imIipDoTest712(  ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_8_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest811( ctNo1st, ctNo2st, ctNo3st );
			break;
		case 2:
			imIipDoTest812( ctNo1st, ctNo2st, ctNo3st );
			break;
		case 3:
			imIipDoTest813( ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_9_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest911(  ctNo1st, ctNo2st, ctNo3st );
			break;
		case 2:
			imIipDoTest912(  ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

VOID palladium_test_iip1_pt_im_iip_run_9_2( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st )
{
	switch( ctNo3st ) {
		case 1:
			imIipDoTest921(ctNo1st, ctNo2st, ctNo3st );
			break;
		default:
			Ddim_Print(( errmsg_skip, ctNo1st, ctNo2st, ctNo3st ));
			break;
	}
}

PalladiumTestIip* palladium_test_iip1_new(void)
{
	PalladiumTestIip1 *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_IIP1,sizeof(PalladiumTestIip1Private));
	return self;
}
