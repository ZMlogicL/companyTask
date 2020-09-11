/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-10
*@author : 刘嫚鶄
*@brief : ImElaTestCase
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

#include "imelatestcase.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImElaTestCase, im_ela_test_case)
#define IM_ELA_TEST_CASE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImElaTestCasePrivate, IM_TYPE_ELA_TEST_CASE))

struct _ImElaTestCasePrivate
{

};

/*
 * DECLS
 */

static VOID ptImElaDoTest201( VOID );
static VOID ptImElaDoTest202( VOID );
static VOID ptImElaDoTest203( VOID );
static VOID ptImElaDoTest204( VOID );
static VOID ptImElaDoTest205( VOID );
static VOID ptImElaDoTest206( VOID );
static VOID ptImElaDoTest207( VOID );
static VOID ptImElaDoTest208( VOID );
static VOID ptImElaDoTest209( VOID );
static VOID ptImElaDoTest210( VOID );
static VOID ptImElaDoTest211( VOID );
static VOID ptImElaDoTest212( VOID );
static VOID ptImElaDoTest213( VOID );
static VOID ptImElaDoTest214( VOID );
static VOID ptImElaDoTest215( VOID );
static VOID ptImElaDoTest216( VOID );
static VOID ptImElaDoTest217( VOID );
static VOID ptImElaDoTest218( VOID );
static VOID ptImElaDoTest219( VOID );
static VOID ptImElaDoTest220( VOID );
static VOID ptImElaDoTest221( VOID );
static VOID ptImElaDoTest222( VOID );
static VOID ptImElaDoTest223( VOID );
static VOID ptImElaDoTest224( VOID );
static VOID ptImElaDoTest225( VOID );
static VOID ptImElaDoTest226( VOID );
static VOID ptImElaDoTest227( VOID );
static VOID ptImElaDoTest228( VOID );
static VOID ptImElaDoTest229( VOID );
static VOID ptImElaDoTest230( VOID );
static VOID ptImElaDoTest231( VOID );
static VOID ptImElaDoTest232( VOID );
static VOID ptImElaDoTest233( VOID );
static VOID ptImElaDoTest234( VOID );
static VOID ptImElaDoTest235( VOID );
static VOID ptImElaDoTest236( VOID );
static VOID ptImElaDoTest237( VOID );
static VOID ptImElaDoTest238( VOID );
static VOID ptImElaDoTest239( VOID );
static VOID ptImElaDoTest240( VOID );
static VOID ptImElaDoTest241( VOID );
static VOID ptImElaDoTest242( VOID );
static VOID ptImElaDoTest243( VOID );
static VOID ptImElaDoTest244( VOID );
static VOID ptImElaDoTest245( VOID );
static VOID ptImElaDoTest246( VOID );
static VOID ptImElaDoTest247( VOID );
static VOID ptImElaDoTest248( VOID );

static void im_ela_test_case_constructor(ImElaTestCase *self)
{
	ImElaTestCasePrivate *priv = IM_ELA_TEST_CASE_GET_PRIVATE(self);
}

static void im_ela_test_case_destructor(ImElaTestCase *self)
{
	ImElaTestCasePrivate *priv = IM_ELA_TEST_CASE_GET_PRIVATE(self);
}

/*
 * IMPL
 */

static VOID ptImElaDoTest201( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));

	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_12M );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest202( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}


static VOID ptImElaDoTest203( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}



static VOID ptImElaDoTest204( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest205( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest206( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_12M );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest207( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest208( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}


static VOID ptImElaDoTest209( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}


static VOID ptImElaDoTest210( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest211( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest212( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest213( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest214( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest215( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}


static VOID ptImElaDoTest216( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}


static VOID ptImElaDoTest217( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest218( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, S_SDRAM_ELA_NOISE_SUPPRESS );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}


static VOID ptImElaDoTest219( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, (1152 * 628 * 16) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, (S_SDRAM_ELA_OUT_BAYER / 2) );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest220( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, (1152 * 628 * 16) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, (S_SDRAM_ELA_OUT_BAYER / 2) );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}


static VOID ptImElaDoTest221( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, (1152 * 628 * 16) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest222( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );	// 長波長ノイズ抑制データ
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, (1152 * 628 * 16) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest223( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest224( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	memset((VOID*)S_SDRAM_ELA_ADR_NOISE_SUPPRESS, 0xFF, 4);
	memset((VOID*)S_SDRAM_ELA_ADR_EXTRACT_NOISE, 0xAA, 4);
	memset((VOID*)S_SDRAM_ELA_ADR_OUT_BAYER, 0x55, 4);
	DDIM_User_L1l2cache_Clean_Flush_All();
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest225( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest226( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}


static VOID ptImElaDoTest227( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest228( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest229( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest230( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest231( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, (4480 * 2492));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest232( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, (4480 * 2492));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}


static VOID ptImElaDoTest233( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest234( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}



static VOID ptImElaDoTest235( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, (640*480*2) );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest236( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, (640*480*2) );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest237( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest238( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest239( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest240( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}


static VOID ptImElaDoTest241( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest242( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest243( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, (640*480) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, (640*480) );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest244( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, (640*480) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, (640*480) );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest245( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest246( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest247( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

static VOID ptImElaDoTest248( VOID )
{
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " begin\n" ));
	Palladium_Set_In_Localstack( S_SDRAM_ELA_ADR_IN_BAYER, S_SDRAM_ELA_SIZ_4K2K );
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* ELA begin CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	D_IM_ELA_CT_FUNC();
	Ddim_Print(( "* ELA end CT_Im_Ela_" D_IM_ELA_TEST_NO "\n" ));
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_NOISE_SUPPRESS, (4480 * 2492) );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_EXTRACT_NOISE, S_SDRAM_ELA_EXTRACT_NOISE );
	Palladium_Set_Out_Localstack( S_SDRAM_ELA_ADR_OUT_BAYER, S_SDRAM_ELA_OUT_BAYER );
	Ddim_Print(( "*** ELA test " D_IM_ELA_TEST_NO " end\n" ));
}

void im_ela_test_case_choose_case(ImElaTestCase*self,UCHAR type1)
{
	switch( type1 ) {
		case 1:
			ptImElaDoTest201();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 2:
			ptImElaDoTest202();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 3:
			ptImElaDoTest203();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 4:
			ptImElaDoTest204();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 5:
			ptImElaDoTest205();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 6:
			ptImElaDoTest206();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 7:
			ptImElaDoTest207();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 8:
			ptImElaDoTest208();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 9:
			ptImElaDoTest209();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 10:
			ptImElaDoTest210();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 11:
			ptImElaDoTest211();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 12:
			ptImElaDoTest212();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 13:
			ptImElaDoTest213();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 14:
			ptImElaDoTest214();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 15:
			ptImElaDoTest215();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 16:
			ptImElaDoTest216();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 17:
			ptImElaDoTest217();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 18:
			ptImElaDoTest218();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 19:
			ptImElaDoTest219();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 20:
			ptImElaDoTest220();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 21:
			ptImElaDoTest221();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 22:
			ptImElaDoTest222();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 23:
			ptImElaDoTest223();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 24:
			ptImElaDoTest224();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 25:
			ptImElaDoTest225();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 26:
			ptImElaDoTest226();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 27:
			ptImElaDoTest227();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 28:
			ptImElaDoTest228();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 29:
			ptImElaDoTest229();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 30:
			ptImElaDoTest230();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 31:
			ptImElaDoTest231();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 32:
			ptImElaDoTest232();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 33:
			ptImElaDoTest233();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 34:
			ptImElaDoTest234();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;im_ela_test_case_choose_case
		case 35:
			ptImElaDoTest235();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 36:
			ptImElaDoTest236();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 37:
			ptImElaDoTest237();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 38:
			ptImElaDoTest238();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 39:
			ptImElaDoTest239();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 40:
			ptImElaDoTest240();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 41:
			ptImElaDoTest241();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 42:
			ptImElaDoTest242();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 43:
			ptImElaDoTest243();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 44:
			ptImElaDoTest244();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 45:
			ptImElaDoTest245();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 46:
			ptImElaDoTest246();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 47:
			ptImElaDoTest247();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		case 48:
			ptImElaDoTest248();
			Ddim_Print(( "\n" ));
			CT_Im_Ela_Reg_Print();
			break;
		default:
			Ddim_Print(("*** ELA test skip\n" ));
			break;
	}
}

ImElaTestCase* im_ela_test_case_new(void)
{
	ImElaTestCase* self = k_object_new_with_private(IM_TYPE_ELA_TEST_CASE, sizeof(ImElaTestCasePrivate));

	return self;
}
