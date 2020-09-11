/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-08
*@author : aorongxing
*@brief : PalladiumTestR2yCom2
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 
*
*/

#include "ct_im_r2y.h"
#include "im_r2y.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "driver_common.h"
#include "palladium_test.h"
#include <string.h>
#include "palladiumtestr2ycom2.h"


K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestR2yCom2, palladium_test_r2y_com2)
#define PALLADIUM_TEST_R2Y_COM2_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
										PalladiumTestR2yCom2Private, PALLADIUM_TYPE_TEST_R2Y_COM2))


struct _PalladiumTestR2yCom2Private
{

};


static void palladium_test_r2y_com2_constructor(PalladiumTestR2yCom2 *self)
{
	PalladiumTestR2yCom2Private *priv = PALLADIUM_TEST_R2Y_COM2_GET_PRIVATE(self);
}

static void palladium_test_r2y_com2_destructor(PalladiumTestR2yCom2 *self)
{
	PalladiumTestR2yCom2Private *priv = PALLADIUM_TEST_R2Y_COM2_GET_PRIVATE(self);
}

// Input: RGB P12,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_33"
VOID pt_im_r2y_do_test_3_33( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_BAY_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_BAY_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_34"
VOID pt_im_r2y_do_test_3_34( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_BAY_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_BAY_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12,  Output: Y only U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_35"
VOID pt_im_r2y_do_test_3_35( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_BAY_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_BAY_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_36"
VOID pt_im_r2y_do_test_3_36( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_BAY_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_BAY_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP + D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U8,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_41"
VOID pt_im_r2y_do_test_3_41( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_42"
VOID pt_im_r2y_do_test_3_42( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));


#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_43"
VOID pt_im_r2y_do_test_3_43( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));


#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_44"
VOID pt_im_r2y_do_test_3_44( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));


#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_45"
VOID pt_im_r2y_do_test_3_45( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));


#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: Y only U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_46"
VOID pt_im_r2y_do_test_3_46( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));


#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U8,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_47"
VOID pt_im_r2y_do_test_3_47( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_48"
VOID pt_im_r2y_do_test_3_48( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_49"
VOID pt_im_r2y_do_test_3_49( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC444 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_50"
VOID pt_im_r2y_do_test_3_50( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC444_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC444_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_51"
VOID pt_im_r2y_do_test_3_51( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_52"
VOID pt_im_r2y_do_test_3_52( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC420 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_53"
VOID pt_im_r2y_do_test_3_53( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC420_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC420_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC420 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_54"
VOID pt_im_r2y_do_test_3_54( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC420_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC420_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC420 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_55"
VOID pt_im_r2y_do_test_3_55( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC420_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC420_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC444 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_56"
VOID pt_im_r2y_do_test_3_56( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC444_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC444_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_57"
VOID pt_im_r2y_do_test_3_57( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_58"
VOID pt_im_r2y_do_test_3_58( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_59"
VOID pt_im_r2y_do_test_3_59( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: Y only U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_60"
VOID pt_im_r2y_do_test_3_60( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_61"
VOID pt_im_r2y_do_test_3_61( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', (1280 * 960 * 2 * 3) );
	memset( (VOID*)(D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP + (1280 * 960 * 2 * 3)), '\xee', (1280 * 960 * 2)
			+ ( D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 256 ));
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, (1280 * 960 * 2 * 3) );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack(( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP + (1280 * 960 * 2 * 3)),
			D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES * 4 );
	Palladium_Set_Out_Localstack(( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP + (1280 * 960 * 2 * 3)
			+ (1280 * 960 * 2)), D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 256 );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_62"
VOID pt_im_r2y_do_test_3_62( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_63"
VOID pt_im_r2y_do_test_3_63( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}


// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_64"
VOID pt_im_r2y_do_test_3_64( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}


// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_65"
VOID pt_im_r2y_do_test_3_65( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}


// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_66"
VOID pt_im_r2y_do_test_3_66( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}



PalladiumTestR2yCom2* palladium_test_r2y_com2_new(void)
{
	PalladiumTestR2yCom2* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_R2Y_COM2, sizeof(PalladiumTestR2yCom2Private));

	return self;
}

PalladiumTestR2yCom2* palladium_test_r2y_com2_get(void)
{
	static PalladiumTestR2yCom2* self = NULL;

	if (!self) {
		self = k_object_new_with_private(PALLADIUM_TYPE_TEST_R2Y_COM2, sizeof(PalladiumTestR2yCom2Private));
	}

	return self;
}
