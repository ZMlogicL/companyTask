/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-08
*@author : aorongxing
*@brief : PalladiumTestR2yCom
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
#include "palladiumtestr2ycom.h"


K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestR2yCom, palladium_test_r2y_com)
#define PALLADIUM_TEST_R2Y_COM_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
										PalladiumTestR2yComPrivate, PALLADIUM_TYPE_TEST_R2Y_COM))


struct _PalladiumTestR2yComPrivate
{

};


static void palladium_test_r2y_com_constructor(PalladiumTestR2yCom *self)
{
	PalladiumTestR2yComPrivate *priv = PALLADIUM_TEST_R2Y_COM_GET_PRIVATE(self);
}

static void palladium_test_r2y_com_destructor(PalladiumTestR2yCom *self)
{
	PalladiumTestR2yComPrivate *priv = PALLADIUM_TEST_R2Y_COM_GET_PRIVATE(self);
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_1"
VOID pt_im_r2y_do_test_3_1( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));


#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12(for B2R 16bit non-packed raw),  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_2"
VOID pt_im_r2y_do_test_3_2( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
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
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT2_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12(for LTM 16bit non-packed raw),  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_3"
VOID pt_im_r2y_do_test_3_3( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
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
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT2_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_4"
VOID pt_im_r2y_do_test_3_4( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
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

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_5"
VOID pt_im_r2y_do_test_3_5( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
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
#define D_IM_R2Y_TEST_NO "3_6"
VOID pt_im_r2y_do_test_3_6( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
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
#define D_IM_R2Y_TEST_NO "3_12"
VOID pt_im_r2y_do_test_3_12( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
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
#define D_IM_R2Y_TEST_NO "3_13"
VOID pt_im_r2y_do_test_3_13( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
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

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U16,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_14"
VOID pt_im_r2y_do_test_3_14( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	// ��̓f�[�^
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
#define D_IM_R2Y_TEST_NO "3_15"
VOID pt_im_r2y_do_test_3_15( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
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
#define D_IM_R2Y_TEST_NO "3_16"
VOID pt_im_r2y_do_test_3_16( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
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
#define D_IM_R2Y_TEST_NO "3_17"
VOID pt_im_r2y_do_test_3_17( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', (1280 * 960 * 2 * 3) );
	memset( (VOID*)( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP + (1280 * 960 * 2 * 3)), '\xee', (1280 * 960 * 2) + ( D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 256 ));
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

// Input: RGB U16,  Output: Y only U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_18"
VOID pt_im_r2y_do_test_3_18( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES
			+ D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U16_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP_1, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U8,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_19"
VOID pt_im_r2y_do_test_3_19( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U8,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_20"
VOID pt_im_r2y_do_test_3_20( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U8,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_21"
VOID pt_im_r2y_do_test_3_21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U8,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_22"
VOID pt_im_r2y_do_test_3_22( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U8,  Output: Y only U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_23"
VOID pt_im_r2y_do_test_3_23( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );

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
#define D_IM_R2Y_TEST_NO "3_24"
VOID pt_im_r2y_do_test_3_24( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', (1280 * 960 * 2)
			+ ( D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 256 ));
#endif

	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES * 4 );
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP + (1280 * 960 * 2),
			D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 256 );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB U8,  Output: Y only U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_25"
VOID pt_im_r2y_do_test_3_25( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES
			+ D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP_1, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_26"
VOID pt_im_r2y_do_test_3_26( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
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

// Input: RGB P12,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_27"
VOID pt_im_r2y_do_test_3_27( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );

	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_28"
VOID pt_im_r2y_do_test_3_28( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_29"
VOID pt_im_r2y_do_test_3_29( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12,  Output: Y only U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_30"
VOID pt_im_r2y_do_test_3_30( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_U8_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12,  Output: YCC422 U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_31"
VOID pt_im_r2y_do_test_3_31( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', (1280 * 960 * 3 / 2 * 3) );
	memset( (VOID*)(D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP + (1280 * 960 * 3 / 2 * 3)), '\xee', (1280 * 960 * 2)
			+ ( D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 256 ));
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, (1280 * 960 * 3 / 2 * 3));

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack(( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP + (1280 * 960 * 3 / 2 * 3)),
			D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES * 4 );
	Palladium_Set_Out_Localstack(( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP + (1280 * 960 * 3 / 2 * 3)
			+ (1280 * 960 * 2)), D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 256 );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}

// Input: RGB P12,  Output: Y only U8
#undef D_IM_R2Y_TEST_NO
#define D_IM_R2Y_TEST_NO "3_32"
VOID pt_im_r2y_do_test_3_32( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );
	memset( (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, '\xee', D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES
			+ D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_R2Y_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_R2Y_IMG_MEM_IN_RGB_P12_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* R2Y begin CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));
	CT_Im_R2Y_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* R2Y end CT_Im_R2y_" D_IM_R2Y_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC_ADDR_TOP, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES );
	Palladium_Set_Out_Localstack( D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP_1, D_IM_R2Y_IMG_MEM_OUT_YCC422_BYTES / 2 );

	Ddim_Print(( "*** R2Y test " D_IM_R2Y_TEST_NO " end\n" ));
}


PalladiumTestR2yCom* palladium_test_r2y_com_new(void)
{
	PalladiumTestR2yCom* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_R2Y_COM, sizeof(PalladiumTestR2yComPrivate));

	return self;
}

PalladiumTestR2yCom* palladium_test_r2y_com_get(void)
{
	static PalladiumTestR2yCom* self = NULL;

	if (!self) {
		self = k_object_new_with_private(PALLADIUM_TYPE_TEST_R2Y_COM, sizeof(PalladiumTestR2yComPrivate));
	}

	return self;
}
