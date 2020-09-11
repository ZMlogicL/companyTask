/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-09
*@author : 刘嫚鶄
*@brief : PalladiumTestMe
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

#include "im_me.h"
#include "ct_im_me.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "driver_common.h"
#include "palladium_test.h"

#include "palladiumtestme.h"


K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestMe, palladium_test_me)
#define PALLADIUM_TEST_ME_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), PalladiumTestMePrivate, PALLADIUM_TYPE_TEST_ME))

#define D_PT_ME_CMD_LEN			(20)

static char* gCmd_Argv[ D_PT_ME_CMD_LEN ];

struct _PalladiumTestMePrivate
{

};

/*
 * DECLS
 */

static VOID   ptImMeEnableGic( VOID );
static VOID   ptImMeStartClock( VOID );
static void    ptImMeExecuteCmd( int cmdArgc, char* cmdArgv );

static void palladium_test_me_constructor(PalladiumTestMe *self)
{
//	PalladiumTestMePrivate *priv = PALLADIUM_TEST_ME_GET_PRIVATE(self);
}

static void palladium_test_me_destructor(PalladiumTestMe *self)
{
//	PalladiumTestMePrivate *priv = PALLADIUM_TEST_ME_GET_PRIVATE(self);
}

/*
 * IMPL
 */

static VOID ptImMeEnableGic( VOID )
{
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT, 1, D_DD_GIC_PRI30, 1 );		// cpu=0, intid=118, enable, pri=30
	Dd_GIC_Ctrl( E_DD_GIC_INTID_ME_INT,        1, D_DD_GIC_PRI30, 1 );		// int enable
}

static VOID ptImMeStartClock( VOID )
{
	kuchar imMePclkCtrlCnt = 0;
	kuchar imMeClkCtrlCnt = 0;
	kuchar imMeIclkCtrlCnt = 0;

	Dd_Top_Start_Clock( (kuchar*)&imMePclkCtrlCnt, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_MEAP_BIT );
	Dd_Top_Start_Clock( (kuchar*)&imMeIclkCtrlCnt, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_MEAX_BIT );
	Dd_Top_Start_Clock( (kuchar*)&imMeClkCtrlCnt, &Dd_Top_Get_CLKSTOP7(), ~D_DD_TOP_MECK_BIT );
}

static void ptImMeExecuteCmd( int cmdArgc, char* cmdArgv )
{
	kint32 j;
	kint32 cmdPos = 0;

	for( j = 0; j < cmdArgc; j++ ) {
		gCmd_Argv[ j ] = ( cmdArgv + ( cmdPos * D_PT_ME_CMD_LEN ) );
		cmdPos++;
	}

	ct_im_me_main( cmdArgc, gCmd_Argv );
}


void pt_im_me_main(PalladiumTestMe *self )
{
	UINT32	testno;

	// 開始...
	DriverCommon_DDIM_PRINT(( "****** ME begin Pt_Im_ME_Main\n" ));

	// タイマー初期化
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// テストパラメータ取得
	testno	= gDDIM_Info.com._6a;

	DriverCommon_DDIM_PRINT(( "****** Palladium Test %d begin\n", testno ));

	ptImMeEnableGic();
	ptImMeStartClock();

	while( 1 ) {

		if ( testno == 1 ) {
			// 入力データ.
			Palladium_Set_In_Localstack( D_IM_ME_IMG_MEM_IN_YCC_REF_ADDR_TOP, D_IM_ME_IMG_MEM_4K2K_YCC_REF_U8_BYTES );
			Palladium_Set_In_Localstack( D_IM_ME_IMG_MEM_IN_YCC_STD_ADDR_TOP, D_IM_ME_IMG_MEM_4K2K_YCC_STD_U8_BYTES );

			// タイマー起動.
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

			// テストコード起動.
			char test_argv1[][ D_PT_ME_CMD_LEN ] = { "imme", "2", "1" };
			ptImMeExecuteCmd((sizeof(test_argv1) / D_PT_ME_CMD_LEN), (char*)test_argv1);

			// タイマー停止.
			Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

			// 出力ダンプ
			Palladium_Set_Out_Localstack( D_IM_ME_IMG_MEM_OUT_HEVC_ADDR_TOP,      D_IM_ME_IMG_MEM_HEVC_U8_BYTES );
		}
		else {
			DriverCommon_DDIM_PRINT(("*** RS Parameter Error\n" ));
		}

		break;
	}

	// タイマーログ出力
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );

	DriverCommon_DDIM_PRINT(( "****** Palladium Test %d end\n", testno ));

	// Force stop
	Palladium_Force_Stop();
}

PalladiumTestMe* palladium_test_me_new(void)
{
	PalladiumTestMe* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_ME, sizeof(PalladiumTestMePrivate));

	return self;
}

