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
#include "palladium_test_iip.h"
#include "ct_im_iip.h"
#include "im_iip.h"
//#include "im_b2y.h"
#include "dd_gic.h"
#include "dd_top.h"

#include "driver_common.h"
#include "palladium_test.h"

#include "jdsiip.h"

#include <string.h>
#include "palladiumtestiip1.h"
#include "palladiumtestiip.h"


K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestIip, palladium_test_iip);

#define PALLADIUM_TEST_IIP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestIipPrivate,PALLADIUM_TYPE_TEST_IIP))
#define PalladiumTestIip_IM_IIP_CLK_REG_ADDR	(&PalladiumTestIip_Top_Get_CLKSTOP3())
#define PalladiumTestIip_IM_IIP_HCLK_REG_ADDR	(&PalladiumTestIip_Top_Get_CLKSTOP3())
#define PalladiumTestIip_IM_IIP_PCLK_REG_ADDR	(&PalladiumTestIip_Top_Get_CLKSTOP3())
#define PalladiumTestIip_IM_IIP_ICLK_REG_ADDR	(&PalladiumTestIip_Top_Get_CLKSTOP3())
#define PalladiumTestIip_IM_B2Y_CLK_REG_ADDR	(&PalladiumTestIip_Top_Get_CLKSTOP11())
#define PalladiumTestIip_IM_B2Y_HCLK_REG_ADDR	(&PalladiumTestIip_Top_Get_CLKSTOP11())
#define PalladiumTestIip_IM_B2Y_PCLK_REG_ADDR	(&PalladiumTestIip_Top_Get_CLKSTOP11())
#define PalladiumTestIip_IM_B2Y_ICLK_REG_ADDR	(&PalladiumTestIip_Top_Get_CLKSTOP11())

#define PalladiumTestIip_IM_IIP_CLK_REG_BIT	PalladiumTestIip_DD_TOP_IIPCK_BIT
#define PalladiumTestIip_IM_IIP_PCLK_REG_BIT	PalladiumTestIip_DD_TOP_IIPAP_BIT
#define PalladiumTestIip_IM_IIP_HCLK_REG_BIT	PalladiumTestIip_DD_TOP_IIPAH_BIT
#define PalladiumTestIip_IM_IIP_ICLK_REG_BIT	PalladiumTestIip_DD_TOP_IIPAX_BIT
#define PalladiumTestIip_IM_B2Y_CLK_REG_BIT	PalladiumTestIip_DD_TOP_R2Y1CK_BIT	// bit4
#define PalladiumTestIip_IM_B2Y_HCLK_REG_BIT	PalladiumTestIip_DD_TOP_R2Y1AH_BIT	// bit5
#define PalladiumTestIip_IM_B2Y_PCLK_REG_BIT	PalladiumTestIip_DD_TOP_R2Y1AP_BIT	// bit6
#define PalladiumTestIip_IM_B2Y_ICLK_REG_BIT	PalladiumTestIip_DD_TOP_R2Y1AX_BIT	// bit7

#define PalladiumTestIip_PT_IM_IIP_IMG_SRAM_ADDR0	(0x30000000UL)
#define PalladiumTestIip_PT_IM_IIP_IMG_SRAM_ADDR1	(0x34000000UL)
#define PalladiumTestIip_PT_IM_IIP_IMG_SRAM_ADDR2	(0x38000000UL)
#define PalladiumTestIip_PT_IM_IIP_IMG_SRAM_ADDR3	(0x3C000000UL)

#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "9_3_1"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "10_1_1"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "10_1_2"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "11_1_1"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "11_1_2"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "12_1_1"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "12_1_2"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "13_1_1"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "13_1_2"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "13_1_3"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "13_1_4"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "13_1_5"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "13_1_6"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "13_1_7"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "13_1_8"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_1_1"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_1_2"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_1_3"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_1_4"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_2_1"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_2_2"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_3_1"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_3_2"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_4_1"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_4_2"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_4_3"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "14_4_4"
#undef PalladiumTestIip_IM_IIP_TEST_NO
#define PalladiumTestIip_IM_IIP_TEST_NO "15_1_1"

struct _PalladiumTestIipPrivate
{
		kint a;
};

static const kchar S_ERRMSG_SKIP[] = "*** IIP test skip %u-%u-%u\n";

static VOID ptImIipDoTest931( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipRun93( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1011( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1012( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest101( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1111( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1112( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipRun111( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1211( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1212( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipRun121( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1311( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1312( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1313( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1314( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1315( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1316( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1317( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1318( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipRun131( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1411( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1412( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1413( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1414( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipRun141( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1421( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1422( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipRun142( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1431( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1432( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipRun143( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1441( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1442( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1443( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1444( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipRun144( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipDoTest1511( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );
static VOID ptImIipRun151( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd );

static void palladiumTestIipConstructor(PalladiumTestIip *self)
{
	PalladiumTestIipPrivate *priv = PALLADIUM_TEST_IIP_GET_PRIVATE(self);
	priv->a = 0;
}

static void palladiumTestIipDestructor(PalladiumTestIip *self)
{
	PalladiumTestIipPrivate *priv = PALLADIUM_TEST_IIP_GET_PRIVATE(self);
		priv->a = 0;
}

static VOID ptImIipDoTest931( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RGBA5551_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_RGBA5551_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipRun93( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	switch( ctNo3nd ) {
		case 1:
			ptImIipDoTest931( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		default:
			Ddim_Print(( S_ERRMSG_SKIP, ctNo1st, ctNo2nd, ctNo3nd ));
			break;
	}
}

static VOID ptImIipDoTest1011( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RGB565_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_RGB565_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_RGB565_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1012( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_"PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC420_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest101( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	switch( ctNo3nd ) {
		case 1:
			ptImIipDoTest1011( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 2:
			ptImIipDoTest1012( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		default:
			Ddim_Print(( S_ERRMSG_SKIP, ctNo1st, ctNo2nd, ctNo3nd ));
			break;
	}
}

static VOID ptImIipDoTest1111( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1112( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U16_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U16_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipRun111( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	switch( ctNo3nd ) {
		case 1:
			ptImIipDoTest1111( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 2:
			ptImIipDoTest1112( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		default:
			Ddim_Print(( S_ERRMSG_SKIP, ctNo1st, ctNo2nd, ctNo3nd ));
			break;
	}
}

static VOID ptImIipDoTest1211( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1212( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipRun121( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	switch( ctNo3nd ) {
		case 1:
			ptImIipDoTest1211( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 2:
			ptImIipDoTest1212( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		default:
			Ddim_Print(( S_ERRMSG_SKIP, ctNo1st, ctNo2nd, ctNo3nd ));
			break;
	}
}

static VOID ptImIipDoTest1311( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1312( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1313( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_YCC420_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_YCC420_U8_A, D_IM_IIP_VGA_YCC420_U8_A_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1314( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_1_10_YCC420_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_VGA_1_10_YCC420_U8_A, D_IM_IIP_VGA_1_10_YCC420_U8_A_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_1_10_YCC420_U8_BYTES );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_VGA_1_10_YCC420_U8_A, D_IM_IIP_VGA_1_10_YCC420_U8_A_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1315( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RIBERY_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_YCC420_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_YCC420_U8_A, D_IM_IIP_VGA_YCC420_U8_A_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_RIBERY_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1316( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RIBERY_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_1_10_YCC420_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_VGA_1_10_YCC420_U8_A, D_IM_IIP_VGA_1_10_YCC420_U8_A_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RIBERY_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1317( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_FULLHD_YCC422_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_FULLHD_1_10_YCC420_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_FULLHD_1_10_YCC420_U8_A, D_IM_IIP_FULLHD_1_10_YCC420_U8_A_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_FULLHD_YCC422_U8_BYTES );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_FULLHD_1_10_YCC420_U8_BYTES );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_FULLHD_1_10_YCC420_U8_A, D_IM_IIP_FULLHD_1_10_YCC420_U8_A_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1318( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_FULLHD_RIBERY_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_FULLHD_1_10_YCC420_U8_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_FULLHD_1_10_YCC420_U8_A, D_IM_IIP_FULLHD_1_10_YCC420_U8_A_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_FULLHD_RIBERY_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipRun131( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	switch( ctNo3nd ) {
		case 1:
			ptImIipDoTest1311( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 2:
			ptImIipDoTest1312( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 3:
			ptImIipDoTest1313( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 4:
			ptImIipDoTest1314( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 5:
			ptImIipDoTest1315( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 6:
			ptImIipDoTest1316( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 7:
			ptImIipDoTest1317( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 8:
			ptImIipDoTest1318( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		default:
			Ddim_Print(( S_ERRMSG_SKIP, ctNo1st, ctNo2nd, ctNo3nd ));
			break;
	}
}

static VOID ptImIipDoTest1411( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_2_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1412( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_2_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1413( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_HD_4_3_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1414( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U16_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U16_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipRun141( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	switch( ctNo3nd ) {
		case 1:
			ptImIipDoTest1411( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 2:
			ptImIipDoTest1412( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 3:
			ptImIipDoTest1413( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 4:
			ptImIipDoTest1414( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		default:
			Ddim_Print(( S_ERRMSG_SKIP, ctNo1st, ctNo2nd, ctNo3nd ));
			break;
	}
}

static VOID ptImIipDoTest1421( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RGBA4444_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_RGBA4444_BYTES );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_2_TOP, D_IM_IIP_VGA_RGBA4444_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1422( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, 320 *2 *240 );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, 320 *2 *240 );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipRun142( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	switch( ctNo3nd ) {
		case 1:
			ptImIipDoTest1421( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 2:
			ptImIipDoTest1422( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		default:
			Ddim_Print(( S_ERRMSG_SKIP, ctNo1st, ctNo2nd, ctNo3nd ));
			break;
	}
}

static VOID ptImIipDoTest1431( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1432( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U12_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U12_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipRun143( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	switch( ctNo3nd ) {
		case 1:
			ptImIipDoTest1431( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 2:
			ptImIipDoTest1432( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		default:
			Ddim_Print(( S_ERRMSG_SKIP, ctNo1st, ctNo2nd, ctNo3nd ));
			break;
	}
}

static VOID ptImIipDoTest1441( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, (D_IM_IIP_VGA_YCC422_U8_BYTES + D_IM_IIP_VGA_YCC422_U8_A_BYTES) );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1442( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_RGBA8888_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_RGBA8888_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_RGBA8888_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1443( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC444_U16_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_YCC444_U16_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC444_U16_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipDoTest1444( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U16_BYTES + D_IM_IIP_VGA_YCC422_U16_A_BYTES );
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_4_TOP, D_IM_IIP_VGA_YCC422_U16_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U16_BYTES + D_IM_IIP_VGA_YCC422_U16_A_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipRun144( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	switch( ctNo3nd ) {
		case 1:
			ptImIipDoTest1441( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 2:
			ptImIipDoTest1442( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 3:
			ptImIipDoTest1443( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		case 4:
			ptImIipDoTest1444( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		default:
			Ddim_Print(( S_ERRMSG_SKIP, ctNo1st, ctNo2nd, ctNo3nd ));
			break;
	}
}

static VOID ptImIipDoTest1511( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( D_IM_IIP_IMG_MEM_ADDR_0_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* IIP begin CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	CT_Im_IIP_Run( ctNo1st, ctNo2nd, ctNo3nd );
	Ddim_Print(( "* IIP end CT_Im_Iip_" PalladiumTestIip_IM_IIP_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( D_IM_IIP_IMG_MEM_ADDR_1_TOP, D_IM_IIP_VGA_YCC422_U8_BYTES );
	Ddim_Print(( "*** IIP test " PalladiumTestIip_IM_IIP_TEST_NO " end\n" ));
}

static VOID ptImIipRun151( kuchar const ctNo1st, kuchar const ctNo2nd, kuchar const ctNo3nd )
{
switch( ctNo3nd ) {
		case 1:
			ptImIipDoTest1511( ctNo1st, ctNo2nd, ctNo3nd );
			break;
		default:
			Ddim_Print(( S_ERRMSG_SKIP, ctNo1st, ctNo2nd, ctNo3nd ));
			break;
	}
}

VOID palladium_test_iip_Pt_Im_IIP_Main( PalladiumTestIip* self )
{
	kuchar			type1;
	kuchar			type2;
	kuchar			type3;
	kint32			ercd;
	Ddim_Print(( "****** IIP begin palladium_test_iip_Pt_Im_IIP_Main\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	type1	= gDDIM_Info.com._6a;
	type2	= gDDIM_Info.com._6b;
	type3	= gDDIM_Info.com._6c;
	Ddim_Print(( "*** IIP begin Im_IIP_Init\n" ));
#ifdef CO_DEBUG_ON_PC
	memset( (VOID*)&IO_IIP, '\0', sizeof(IO_IIP) );
	IO_IIP.IZACTL1.bit.TRG = 2;
	IO_IIP.IZACTL2.bit.ABORT = 2;
	Dd_Top_Set_CLKSTOP3_IIPAP( 1 );
	Dd_Top_Set_CLKSTOP3_IIPAH( 1 );
	Dd_Top_Set_CLKSTOP3_IIPAX( 1 );
	Dd_Top_Set_CLKSTOP3_IIPCK( 1 );
#endif // CO_DEBUG_ON_PC
	ercd = Im_IIP_Init();
	if( ercd != D_IM_IIP_OK ) {
		Ddim_Print(( "Im_IIP_Init() error 0x%x\n", ercd ));

		Palladium_Force_Stop();

		return;
	}
	Ddim_Print(( "*** IIP end Im_IIP_Init\n" ));

	palladium_test_iip1_pt_im_iip_enable_gic(NULL);
	palladium_test_iip1_pt_im_iip_start_clock(NULL);

	switch( type1 ) {
		case 1:
			switch( type2 ) {
				case 1:
					palladium_test_iip1_pt_im_iip_run_1_1(NULL, type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 2:
			switch( type2 ) {
				case 1:
					palladium_test_iip1_pt_im_iip_run_2_1( NULL, type1, type2, type3 );
					break;
				case 2:
					palladium_test_iip1_pt_im_iip_run_2_2(NULL,  type1, type2, type3 );
					break;
				case 4:
					palladium_test_iip1_pt_im_iip_run_2_4(NULL,  type1, type2, type3 );
					break;
				case 5:
					palladium_test_iip1_pt_im_iip_run_2_5( NULL, type1, type2, type3 );
					break;
				case 6:
					palladium_test_iip1_pt_im_iip_run_2_6( NULL, type1, type2, type3 );
					break;
				case 7:
					palladium_test_iip1_pt_im_iip_run_2_7( NULL, type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 3:
			switch( type2 ) {
				case 1:
					palladium_test_iip1_pt_im_iip_run_3_1(NULL,  type1, type2, type3 );
					break;
				case 2:
					palladium_test_iip1_pt_im_iip_run_3_2( NULL, type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 4:
			switch( type2 ) {
				case 1:
					palladium_test_iip1_pt_im_iip_run_4_1( NULL, type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 5:
			switch( type2 ) {
				case 1:
					palladium_test_iip1_pt_im_iip_run_5_1(NULL,  type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 6:
			switch( type2 ) {
				case 1:
					palladium_test_iip1_pt_im_iip_run_6_1(NULL,  type1, type2, type3 );
					break;
				case 2:
					palladium_test_iip1_pt_im_iip_run_6_2( NULL,type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 7:
			switch( type2 ) {
				case 1:
					palladium_test_iip1_pt_im_iip_run_7_1(NULL, type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 8:
			switch( type2 ) {
				case 1:
					palladium_test_iip1_pt_im_iip_run_8_1( NULL,type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 9:
			switch( type2 ) {
				case 1:
					palladium_test_iip1_pt_im_iip_run_9_1(NULL, type1, type2, type3 );
					break;
				case 2:
					palladium_test_iip1_pt_im_iip_run_9_2( NULL,type1, type2, type3 );
					break;
				case 3:
					ptImIipRun93( type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 10:
			switch( type2 ) {
				case 1:
					ptImIipDoTest101( type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 11:
			switch( type2 ) {
				case 1:
					ptImIipRun111( type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 12:
			switch( type2 ) {
				case 1:
					ptImIipRun121( type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 13:
			switch( type2 ) {
				case 1:
					ptImIipRun131( type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 14:
			switch( type2 ) {
				case 1:
					ptImIipRun141( type1, type2, type3 );
					break;
				case 2:
					ptImIipRun142( type1, type2, type3 );
					break;
				case 3:
					ptImIipRun143( type1, type2, type3 );
					break;
				case 4:
					ptImIipRun144( type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		case 15:
			switch( type2 ) {
				case 1:
					ptImIipRun151( type1, type2, type3 );
					break;
				default:
					Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
					break;
			}
			break;
		default:
			Ddim_Print(( S_ERRMSG_SKIP, type1, type2, type3 ));
			break;
	}
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );
	Ddim_Print(( "****** IIP end palladium_test_iip_Pt_Im_IIP_Main\n" ));
	Palladium_Force_Stop();
}

PalladiumTestIip* palladium_test_iip_new(void)
{
	PalladiumTestIip *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_IIP,sizeof(PalladiumTestIipPrivate));
	return self;
}
