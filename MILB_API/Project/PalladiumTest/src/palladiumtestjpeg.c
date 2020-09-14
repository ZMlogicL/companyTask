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


#include "palladiumtestjpeg.h"
#include "ddim_user_custom.h"
#include "palladium_test_common.h"
#include "palladium_test.h"
#include "dd_gic.h"
#include "dd_top.h"

#include "ct_im_jpeg.h"
#include "im_jpeg.h"

K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(PalladiumTestJpeg, palladium_test_jpeg,K_TYPE_OBJECT)
#define PALLADIUM_TEST_JPEG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestJpegPrivate,PALLADIUM_TYPE_TEST_JPEG))

#define PalladiumTestJpeg_CLKSTOP_REG_ADDR		(&Dd_Top_Get_CLKSTOP3())

#define PalladiumTestJpeg_CLK_ON				(0x00200000)	// bit[21:22]=10.
#define PalladiumTestJpeg_HCLK_ON				(0x02000000)	// bit[25:24]=10.
#define PalladiumTestJpeg_ICLK_ON				(0x08000000)	// bit[27:26]=10.

struct _PalladiumTestJpegPrivate
{
	kuchar clkCtrlCnt;
	kuchar hclkCtrlCnt;
	kuchar iclkCtrlCnt;
};

/*
 * DECLS
 */

static void 		ptImJpegEncEnableGic( void );
static void 		ptImJpegEncStartClock(PalladiumTestJpeg *self );

/*
 * IMPL
 */

static void palladium_test_jpeg_constructor(PalladiumTestJpeg *self)
{
	PalladiumTestJpegPrivate *priv = PALLADIUM_TEST_JPEG_GET_PRIVATE(self);
	priv -> clkCtrlCnt = 0;
	priv -> hclkCtrlCnt = 0;
	priv -> iclkCtrlCnt = 0;
}

static void palladium_test_jpeg_destructor(PalladiumTestJpeg *self)
{
}

static void ptImJpegEncEnableGic( void )
{
	dd_gic_ctrl( EDdGicIntid_JPEG_INT, 1, D_DD_GIC_PRI30, 1);		// int enable
}

static void ptImJpegEncStartClock(PalladiumTestJpeg *self )
{
	PalladiumTestJpegPrivate *priv = PALLADIUM_TEST_JPEG_GET_PRIVATE(self);
	dd_top_start_clock( &priv ->clkCtrlCnt,  PalladiumTestJpeg_CLKSTOP_REG_ADDR, PalladiumTestJpeg_CLK_ON );
	dd_top_start_clock( &priv ->hclkCtrlCnt, PalladiumTestJpeg_CLKSTOP_REG_ADDR, PalladiumTestJpeg_HCLK_ON );
	dd_top_start_clock( &priv ->iclkCtrlCnt, PalladiumTestJpeg_CLKSTOP_REG_ADDR, PalladiumTestJpeg_ICLK_ON );
}

/*
 * PUBULIC
 */

/**
 * @brief		Test code
 * @param		void
 * @return		void
 * @note		None
 * @attention	None
 */
void palladium_test_jpeg_main(PalladiumTestJpeg *self)
{
	kuint32	param1;
	kuint32	param2;
	kuint32	param3;

	// 開始...
	Ddim_Print(( "****** Palladium JPEG Test : palladium_test_jpeg_main\n" ));

	// タイマー初期化
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// テストパラメータ取得
	param1	= gDdimInfo.com._6a;
	param2	= gDdimInfo.com._6b;
	param3	= gDdimInfo.com._6c;

	ptImJpegEncEnableGic();
	ptImJpegEncStartClock(self);

	// タイマー起動
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// TEST処理実行
	if (param1 == 1) {
		Ct_Im_Jpeg_Run_1(param2, param3);
	}
	else if (param1 == 2) {
		Ct_Im_Jpeg_Run_2(param2, param3);
	}
	else {
		Ddim_Print(("input parameter error\n"));
	}

	// タイマー停止
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// タイマーログ出力
	palladium_test_timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );

	Ddim_Print(( "****** Palladium JPEG Test end\n" ));

	// Force stop
	palladium_test_force_stop();
}


PalladiumTestJpeg* palladium_test_jpeg_new(void)
{
	PalladiumTestJpeg *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_JPEG, sizeof(PalladiumTestJpegPrivate));
	return self;
}
