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

#include <string.h>
#include "ct_im_b2r.h"
#include "ct_im_ltm.h"
#include "im_ltm.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "driver_common.h"
#include "palladium_test.h"
#include "palladiumtestltm1.h"
#include "palladiumtestltm.h"


typedef struct _PalladiumTestLtmPrivate		PalladiumTestLtmPrivate;
struct _PalladiumTestLtmPrivate
{
	int a;
};

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestLtm, palladium_test_ltm)
#define PALLADIUM_TEST_LTM_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestLtmPrivate,PALLADIUM_TYPE_TEST_LTM))
#define D_IM_LTM1_RBKCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())
#define D_IM_LTM1_CLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP11())
#define D_IM_LTM1_HCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP11())
#define D_IM_LTM1_PCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP11())
#define D_IM_LTM1_ACLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP11())

#define D_IM_LTM2_RBKCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())
#define D_IM_LTM2_CLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP13())
#define D_IM_LTM2_HCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP13())
#define D_IM_LTM2_PCLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP13())
#define D_IM_LTM2_ACLK_REG_ADDR		(&Dd_Top_Get_CLKSTOP13())

#define D_IM_LTM1_RBKCLK_REG_BIT	D_DD_TOP_LTMRBK1CK_BIT
#define D_IM_LTM1_CLK_REG_BIT			D_DD_TOP_LTM1CK_BIT
#define D_IM_LTM1_HCLK_REG_BIT		D_DD_TOP_LTM1AH_BIT
#define D_IM_LTM1_PCLK_REG_BIT		D_DD_TOP_LTM1AP_BIT
#define D_IM_LTM1_ACLK_REG_BIT		D_DD_TOP_LTM1AX_BIT

#define D_IM_LTM2_RBKCLK_REG_BIT	D_DD_TOP_LTMRBK2CK_BIT
#define D_IM_LTM2_CLK_REG_BIT			D_DD_TOP_LTM2CK_BIT
#define D_IM_LTM2_HCLK_REG_BIT		D_DD_TOP_LTM2AH_BIT
#define D_IM_LTM2_PCLK_REG_BIT		D_DD_TOP_LTM2AP_BIT
#define D_IM_LTM2_ACLK_REG_BIT		D_DD_TOP_LTM2AX_BIT

#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_3"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_4"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_5"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_6"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_7"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_8"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_9"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_10"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_11"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_12"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "9_"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "1_1"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "1_9"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "1_18"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "2_1"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "2_8"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "2_15"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_1"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_2"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_3"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_4"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_5"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_6"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_7"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_8"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_9"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_10"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_11"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_12"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_13"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_14"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_15"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "9_"


static VOID 										ptImLtmMapDoTest33( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmMapDoTest34( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmMapDoTest35( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmMapDoTest36( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmMapDoTest37( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmMapDoTest38( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmMapDoTest39( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmMapDoTest310( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmMapDoTest311( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmMapDoTest312( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmMapRun3( const UINT32 type2 );
static VOID 										ptImLtmMapRun9( const UINT32 type1 );
static VOID 										ptImLtmLtmDoTest11( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 										ptImLtmLtmDoTest19( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 										ptImLtmLtmDoTest118( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 										ptImLtmLtmRun1( const UINT32 type2 );
static VOID 										ptImLtmLtmDoTest21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 										ptImLtmLtmDoTest28( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 										ptImLtmLtmDoTest215( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 										ptImLtmLtmRun2( const UINT32 type2 );
static VOID 										ptImLtmLtmDoTest31( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest32( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest33( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest34( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest35( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest36( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest37( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest38( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest39( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest310( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest311( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest312( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest313( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest314( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmDoTest315( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 										ptImLtmLtmRun3( const UINT32 type2 );
static VOID 										ptImLtmLtmRun9( const UINT32 type1 );



static void palladium_test_ltm_constructor(PalladiumTestLtm *self)
{
	PalladiumTestLtmPrivate *priv = PALLADIUM_TEST_LTM_GET_PRIVATE(self);
	priv -> a = 0;
}

static void palladium_test_ltm_destructor(PalladiumTestLtm *self)
{
	PalladiumTestLtmPrivate *priv = PALLADIUM_TEST_LTM_GET_PRIVATE(self);
	priv -> a = 0;
}

static VOID ptImLtmMapDoTest33( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_LTM_MAP_SRC_IMG_BYTES_P );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_LTM_MAP_SRC_IMG_BYTES_P );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_MAP_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest34( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_LTM_MAP_SRC_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_LTM_MAP_SRC_IMG_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_MAP_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest35( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_LTM_MAP_SRC_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_LTM_MAP_SRC_IMG_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_MAP_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest36( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_LTM_MAP_SRC_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_LTM_MAP_SRC_IMG_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_MAP_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest37( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_LTM_MAP_SRC_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_LTM_MAP_SRC_IMG_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_MAP_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest38( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_LTM_MAP_SRC_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_LTM_MAP_SRC_IMG_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_MAP_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest39( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_LTM_MAP_SRC_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_LTM_MAP_SRC_IMG_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_MAP_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest310( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_LTM_MAP_SRC_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_LTM_MAP_SRC_IMG_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_MAP_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest311( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP,   '\xee', D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP  );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_UP  );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_MAP_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest312( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, '\xee', D_IM_LTM_MAP_SRC_IMG_BYTES_UP );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_P );
	memset( (VOID*)D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, '\xee', D_IM_LTM_MAP_DST_IMG_BYTES_P );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_MAP_IMG_MEM_IN_RGB_ADDR_TOP, D_IM_LTM_MAP_SRC_IMG_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_MAP_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YP_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_P );
	Palladium_Set_Out_Localstack( D_IM_LTM_MAP_IMG_MEM_OUT_YN_ADDR_TOP, D_IM_LTM_MAP_DST_IMG_BYTES_P );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapRun3( const UINT32 type2 )
{
	UCHAR			type3;
	UCHAR			type4;

	type3	= gDDIM_Info.com._6c;
	type4	= gDDIM_Info.com._6d;

	switch( type3 ) {
		case 1:
			palladium_test_ltm1_map_do_test_31( type2, type3, type4 );
			break;
		case 2:
			palladium_test_ltm1_map_do_test_32( type2, type3, type4 );
			break;
		case 3:
			ptImLtmMapDoTest33( type2, type3, type4 );
			break;
		case 4:
			ptImLtmMapDoTest34( type2, type3, type4 );
			break;
		case 5:
			ptImLtmMapDoTest35( type2, type3, type4 );
			break;
		case 6:
			ptImLtmMapDoTest36( type2, type3, type4 );
			break;
		case 7:
			ptImLtmMapDoTest37( type2, type3, type4 );
			break;
		case 8:
			ptImLtmMapDoTest38( type2, type3, type4 );
			break;
		case 9:
			ptImLtmMapDoTest39( type2, type3, type4 );
			break;
		case 10:
			ptImLtmMapDoTest310( type2, type3, type4 );
			break;
		case 11:
			ptImLtmMapDoTest311( type2, type3, type4 );
			break;
		case 12:
			ptImLtmMapDoTest312( type2, type3, type4 );
			break;
		default:
			Ddim_Print(("*** LTM MAP test skip\n" ));
			break;
	}
}

static VOID ptImLtmMapRun9( const UINT32 type1 )
{
	UCHAR			type2;

	type2	= gDDIM_Info.com._6c;

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO "%u begin\n", type2 ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "=-=-=-=-\n" ));
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_1_%u\n", type2 ));
	CT_Im_LTM_MAP_Run( 1, type2, 0 );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_1_%u\n", type2 ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO "%u end\n", type2 ));
}

static VOID ptImLtmLtmDoTest11( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		1, 2, 3, 4, 5, 6, 7, 8,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_LTM_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest19( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		9, 10, 11, 12, 13, 14, 15, 16,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_LTM_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest118( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		18, 19, 20, 21, 22, 23, 24, 25,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_LTM_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmRun1( const UINT32 type2 )
{
	UCHAR			type3;

	type3	= gDDIM_Info.com._6c;

	switch( type3 ) {
		case 1:
			ptImLtmLtmDoTest11( type2, type3 );
			break;
		case 9:
			ptImLtmLtmDoTest19( type2, type3 );
			break;
		case 18:
			ptImLtmLtmDoTest118( type2, type3 );
			break;
		default:
			Ddim_Print(("*** LTM LTM test skip\n" ));
			break;
	}
}

static VOID ptImLtmLtmDoTest21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		1, 2, 3, 4, 5, 6, 7,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_LTM_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest28( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		8, 9, 10, 11, 12, 13, 14,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_LTM_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest215( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		15, 16, 17, 18, 19, 20, 21,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_LTM_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmRun2( const UINT32 type2 )
{
	UCHAR			type3;

	type3	= gDDIM_Info.com._6c;

	switch( type3 ) {
		case 1:
			ptImLtmLtmDoTest21( type2, type3 );
			break;
		case 8:
			ptImLtmLtmDoTest28( type2, type3 );
			break;
		case 15:
			ptImLtmLtmDoTest215( type2, type3 );
			break;
		default:
			Ddim_Print(("*** LTM LTM test skip\n" ));
			break;
	}
}

static VOID ptImLtmLtmDoTest31( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest32( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest33( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_P );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_P );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_P );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_P );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest34( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest35( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest36( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest37( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest38( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest39( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest310( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest311( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest312( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest313( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  '\xee', D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_P );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_R_ADDR_TOP,  D_IM_LTM_LTM_SRC_IMG_RGB_BYTES );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_P );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest314( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP,    '\xee', D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_16BIT_NONPACK );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP,    D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_16BIT_NONPACK );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_R_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmDoTest315( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP,    '\xee', D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_16BIT_NONPACK );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, '\xee', D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	memset( (VOID*)D_IM_LTM_LTM_IMG_MEM_OUT_Y_ADDR_TOP, '\xee', D_IM_LTM_LTM_DST_IMG_BYTES_YCC );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_B2R_IMG_MEM_IN_BAY_ADDR_TOP,    D_IM_B2R_SRC_IMG_GLOBAL_WIDTH_BAY_16BIT_NONPACK );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YP_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );
	Palladium_Set_In_Localstack( D_IM_LTM_LTM_IMG_MEM_IN_YN_ADDR_TOP, D_IM_LTM_LTM_SRC_IMG_MAP_BYTES_UP );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_LTM_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_LTM_IMG_MEM_OUT_Y_ADDR_TOP, D_IM_LTM_LTM_DST_IMG_BYTES_YCC );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmLtmRun3( const UINT32 type2 )
{
	UCHAR			type3;
	UCHAR			type4;

	type3	= gDDIM_Info.com._6c;
	type4	= gDDIM_Info.com._6d;

	switch( type3 ) {
		case 1:
			ptImLtmLtmDoTest31( type2, type3, type4 );
			break;
		case 2:
			ptImLtmLtmDoTest32( type2, type3, type4 );
			break;
		case 3:
			ptImLtmLtmDoTest33( type2, type3, type4 );
			break;
		case 4:
			ptImLtmLtmDoTest34( type2, type3, type4 );
			break;
		case 5:
			ptImLtmLtmDoTest35( type2, type3, type4 );
			break;
		case 6:
			ptImLtmLtmDoTest36( type2, type3, type4 );
			break;
		case 7:
			ptImLtmLtmDoTest37( type2, type3, type4 );
			break;
		case 8:
			ptImLtmLtmDoTest38( type2, type3, type4 );
			break;
		case 9:
			ptImLtmLtmDoTest39( type2, type3, type4 );
			break;
		case 10:
			ptImLtmLtmDoTest310( type2, type3, type4 );
			break;
		case 11:
			ptImLtmLtmDoTest311( type2, type3, type4 );
			break;
		case 12:
			ptImLtmLtmDoTest312( type2, type3, type4 );
			break;
		case 13:
			ptImLtmLtmDoTest313( type2, type3, type4 );
			break;
		case 14:
			ptImLtmLtmDoTest314( type2, type3, type4 );
			break;
		case 15:
			ptImLtmLtmDoTest315( type2, type3, type4 );
			break;
		default:
			Ddim_Print(("*** LTM LTM test skip\n" ));
			break;
	}
}

static VOID ptImLtmLtmRun9( const UINT32 type1 )
{
	UCHAR			type2;

	type2	= gDDIM_Info.com._6c;

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO "%u begin\n", type2 ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "=-=-=-=-\n" ));
	Ddim_Print(( "* LTM LTM begin CT_Im_Ltm_Ltm_1_%u\n", type2 ));
	CT_Im_LTM_LTM_Run( 1, type2, 0 );
	Ddim_Print(( "* LTM LTM end CT_Im_Ltm_Ltm_1_%u\n", type2 ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM LTM test " D_IM_LTM_TEST_NO "%u end\n", type2 ));
}

VOID ptImLtmRbkRun( VOID )
{
	UCHAR			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			palladium_test_ltm1_rbk_run1( type2 );
			break;
		case 2:
			palladium_test_ltm1_rbk_run2( type2 );
			break;
		case 3:
			palladium_test_ltm1_rbk_run3( type2 );
			break;
		case 9:
			palladium_test_ltm1_rbk_run9( type2 );
			break;
		default:
			Ddim_Print(("*** LTM RBK test skip\n" ));
			break;
	}
}

VOID ptImLtmMapRun( VOID )
{
	UCHAR			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			palladium_test_ltm1_map_run1( type2 );
			break;
		case 2:
			palladium_test_ltm1_map_run2( type2 );
			break;
		case 3:
			ptImLtmMapRun3( type2 );
			break;
		case 9:
			ptImLtmMapRun9( type2 );
			break;
		default:
			Ddim_Print(("*** LTM MAP test skip\n" ));
			break;
	}
}

VOID ptImLtmMain( VOID )
{
	UCHAR			type1;

	// �J�n...
	Ddim_Print(( "****** LTM begin ptImLtmMain\n" ));

	// �^�C�}�[����
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_INIT );

	// �e�X�g�p�����[�^�擾
	type1	= gDDIM_Info.com._6a;

	Dd_Top_Set_CLKSTOP11_LTM1CK( 1 );
	Dd_Top_Set_CLKSEL4_LTM1CLK( 0 );	// 300MHz
	Dd_Top_Set_CLKSTOP11_LTM1CK( 0 );
	Dd_Top_Set_CLKSTOP13_LTM2CK( 1 );
	Dd_Top_Set_CLKSEL6_LTM2CLK( 0 );	// 300MHz
	Dd_Top_Set_CLKSTOP13_LTM2CK( 0 );


	Ddim_Print(( "*** LTM begin Im_LTM_Init\n" ));
	Im_LTM_Init_All_Block( D_IM_LTM_PIPE12 );
	Ddim_Print(( "*** LTM end Im_LTM_Init\n" ));

	palladium_test_ltm1_enable_gic();
	palladium_test_ltm1_start_clock();

	switch( type1 ) {
		case 1:
			ptImLtmRbkRun();
			break;
		case 2:
			ptImLtmMapRun();
			break;
		case 3:
			ptImLtmLtmRun();
			break;
		default:
			Ddim_Print(("*** LTM test skip\n" ));
			break;
	}

	// �^�C�}�[���O�o��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_PRINT );


	Ddim_Print(( "(CLKSEL-4)\n" ));
	Ddim_Print(( "LTM1CLK = %d\n", Dd_Top_Get_CLKSEL4_LTM1CLK() ));
	Ddim_Print(( "(CLKSEL-5)\n" ));
	Ddim_Print(( "LTMRBK1CLK = %d\n", Dd_Top_Get_CLKSEL5_LTMRBK1CLK() ));
	Ddim_Print(( "(CLKSTOP-10)\n" ));
	Ddim_Print(( "LTMRBK1CK = %d\n", Dd_Top_Get_CLKSTOP10_LTMRBK1CK() ));
	Ddim_Print(( "(CLKSTOP-11)\n" ));
	Ddim_Print(( "LTM1CK = %d\n", Dd_Top_Get_CLKSTOP11_LTM1CK() ));
	Ddim_Print(( "LTM1AP = %d\n", Dd_Top_Get_CLKSTOP11_LTM1AP() ));
	Ddim_Print(( "LTM1AH = %d\n", Dd_Top_Get_CLKSTOP11_LTM1AH() ));
	Ddim_Print(( "LTM1AX = %d\n", Dd_Top_Get_CLKSTOP11_LTM1AX() ));
	Ddim_Print(( "(CLKSEL-6)\n" ));
	Ddim_Print(( "LTM2CLK = %d\n", Dd_Top_Get_CLKSEL6_LTM2CLK() ));
	Ddim_Print(( "(CLKSEL-7)\n" ));
	Ddim_Print(( "LTMRBK2CLK = %d\n", Dd_Top_Get_CLKSEL7_LTMRBK2CLK() ));
	Ddim_Print(( "(CLKSTOP-12)\n" ));
	Ddim_Print(( "LTMRBK2CK = %d\n", Dd_Top_Get_CLKSTOP12_LTMRBK2CK() ));
	Ddim_Print(( "(CLKSTOP-13)\n" ));
	Ddim_Print(( "LTM2CK = %d\n", Dd_Top_Get_CLKSTOP13_LTM2CK() ));
	Ddim_Print(( "LTM2AP = %d\n", Dd_Top_Get_CLKSTOP13_LTM2AP() ));
	Ddim_Print(( "LTM2AH = %d\n", Dd_Top_Get_CLKSTOP13_LTM2AH() ));
	Ddim_Print(( "LTM2AX = %d\n", Dd_Top_Get_CLKSTOP13_LTM2AX() ));
	Ddim_Print(( "****** LTM end ptImLtmMain\n" ));

	// �e�X�g�����I������
	Palladium_Force_Stop();
}

VOID ptImLtmLtmRun( VOID )
{
	UCHAR			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			ptImLtmLtmRun1( type2 );
			break;
		case 2:
			ptImLtmLtmRun2( type2 );
			break;
		case 3:
			ptImLtmLtmRun3( type2 );
			break;
		case 9:
			ptImLtmLtmRun9( type2 );
			break;
		default:
			Ddim_Print(("*** LTM LTM test skip\n" ));
			break;
	}
}

PalladiumTestLtm* palladium_test_ltm_new(void)
{
	PalladiumTestLtm *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_LTM, sizeof(PalladiumTestLtmPrivate));
	return self;
}
