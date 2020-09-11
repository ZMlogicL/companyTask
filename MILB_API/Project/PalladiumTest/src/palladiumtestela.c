/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-10
*@author : 刘嫚鶄
*@brief : PalladiumTestEla
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

#include "ct_im_ela.h"
#include "im_ela.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "driver_common.h"
#include "palladium_test.h"
#include <string.h>

#include "palladiumtestela.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestEla, palladium_test_ela)
#define PALLADIUM_TEST_ELA_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), PalladiumTestElaPrivate, PALLADIUM_TYPE_TEST_ELA))

struct _PalladiumTestElaPrivate
{

};

/*
 * DECLS
 */

static VOID ptImElaEnableGic( VOID );
static VOID ptImElaStartClock( VOID );


static void palladium_test_ela_constructor(PalladiumTestEla *self)
{
//	PalladiumTestElaPrivate *priv = PALLADIUM_TEST_ELA_GET_PRIVATE(self);
}

static void palladium_test_ela_destructor(PalladiumTestEla *self)
{
//	PalladiumTestElaPrivate *priv = PALLADIUM_TEST_ELA_GET_PRIVATE(self);
}

/*
 * IMPL
 */

static VOID ptImElaEnableGic( VOID )
{
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT, 1, D_DD_GIC_PRI30, 1 );		// cpu=0, intid=118, enable, pri=30
	Dd_GIC_Ctrl( E_DD_GIC_INTID_ELA_UNIT_INT,  1, D_DD_GIC_PRI30, 1 );		// int enable
}

static VOID ptImElaStartClock( VOID )
{
	UCHAR im_ela_pclk_ctrl_cnt = 0;
	UCHAR im_ela_clk_ctrl_cnt = 0;
	UCHAR im_ela_iclk_ctrl_cnt = 0;
	Dd_Top_Start_Clock( (UCHAR*)&im_ela_pclk_ctrl_cnt, D_IM_ELA_PCLK_REG_ADDR, ~D_IM_ELA_PCLK_REG_BIT );
	Dd_Top_Start_Clock( (UCHAR*)&im_ela_iclk_ctrl_cnt, D_IM_ELA_ICLK_REG_ADDR, ~D_IM_ELA_ICLK_REG_BIT );
	Dd_Top_Start_Clock( (UCHAR*)&im_ela_clk_ctrl_cnt, D_IM_ELA_CLK_REG_ADDR, ~D_IM_ELA_CLK_REG_BIT );
}

VOID pt_im_ela_main( VOID )
{
	UCHAR			type1;

	// 開始...
	Ddim_Print(( "****** ELA begin Pt_Im_ELA_Main\n" ));

	// タイマー初期化
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// テストパラメータ取得
	type1	= gDDIM_Info.com._6a;
	im_ela_test_case_choose_case(im_ela_test_case_new(),type1);

	Ddim_Print(( "*** ELA begin Im_ELA_Init\n" ));
	Im_ELA_Init();
	Ddim_Print(( "*** ELA end Im_ELA_Init\n" ));

	ptImElaEnableGic();
	ptImElaStartClock();

	// タイマーログ出力
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );

#if 0
	Ddim_Print(( "\n" ));
	Ddim_Print(( "(CLKSEL-B)\n" ));
	Ddim_Print(( "ELACLK[0] = %d\n", Dd_Top_Get_CLKSEL_ELA0CLK() ));
	Ddim_Print(( "ELACLK[1] = %d\n", Dd_Top_Get_CLKSEL_ELA1CLK() ));
	Ddim_Print(( "(CLKSTOP-F)\n" ));
	Ddim_Print(( "ELACK[0] = %d\n", Dd_Top_Get_CLKSTOP_ELA0CK() ));
	Ddim_Print(( "ELACK[1] = %d\n", Dd_Top_Get_CLKSTOP_ELA1CK() ));
	Ddim_Print(( "ELAAP[0] = %d\n", Dd_Top_Get_CLKSTOP_ELA0AP() ));
	Ddim_Print(( "ELAAP[1] = %d\n", Dd_Top_Get_CLKSTOP_ELA1AP() ));
	Ddim_Print(( "ELAAX[0] = %d\n", Dd_Top_Get_CLKSTOP_ELA0AX() ));
	Ddim_Print(( "ELAAX[1] = %d\n", Dd_Top_Get_CLKSTOP_ELA1AX() ));
	Ddim_Print(( "****** ELA end Pt_Im_ELA_Main\n" ));
#endif
	// テスト強制終了処理
	Palladium_Force_Stop();
}

PalladiumTestEla* palladium_test_ela_new(void)
{
	PalladiumTestEla* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_ELA, sizeof(PalladiumTestElaPrivate));

	return self;
}

