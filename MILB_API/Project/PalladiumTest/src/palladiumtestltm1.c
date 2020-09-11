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



typedef struct _PalladiumTestLtm1Private		PalladiumTestLtm1Private;
struct _PalladiumTestLtm1Private
{
	int a;
};

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestLtm1, palladium_test_ltm1)
#define PALLADIUM_TEST_LTM1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), PalladiumTestLtm1Private,PALLADIUM_TYPE_TEST_LTM1))
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
#define D_IM_LTM1_CLK_REG_BIT		D_DD_TOP_LTM1CK_BIT
#define D_IM_LTM1_HCLK_REG_BIT		D_DD_TOP_LTM1AH_BIT
#define D_IM_LTM1_PCLK_REG_BIT		D_DD_TOP_LTM1AP_BIT
#define D_IM_LTM1_ACLK_REG_BIT		D_DD_TOP_LTM1AX_BIT

#define D_IM_LTM2_RBKCLK_REG_BIT	D_DD_TOP_LTMRBK2CK_BIT
#define D_IM_LTM2_CLK_REG_BIT		D_DD_TOP_LTM2CK_BIT
#define D_IM_LTM2_HCLK_REG_BIT		D_DD_TOP_LTM2AH_BIT
#define D_IM_LTM2_PCLK_REG_BIT		D_DD_TOP_LTM2AP_BIT
#define D_IM_LTM2_ACLK_REG_BIT		D_DD_TOP_LTM2AX_BIT

#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "1_1"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "1_9"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "2_1"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "2_7"
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
#define D_IM_LTM_TEST_NO "3_16"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_18"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "1_1"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "1_8"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "1_15"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "2_1"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "2_10"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "9_"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_1"
#undef D_IM_LTM_TEST_NO
#define D_IM_LTM_TEST_NO "3_2"


static VOID 												ptImLtmRbkDoTest11( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 												ptImLtmRbkDoTest19( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 												ptImLtmRbkDoTest21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 												ptImLtmRbkDoTest27( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 												ptImLtmRbkDoTest31( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest32( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest33( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest34( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest35( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest36( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest37( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest38( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest39( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest310( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest311( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest312( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest313( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest314( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest315( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest316( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmRbkDoTest318( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
static VOID 												ptImLtmMapDoTest11( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 												ptImLtmMapDoTest18( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 												ptImLtmMapDoTest115( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 												ptImLtmMapDoTest21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );
static VOID 												ptImLtmMapDoTest210( const UINT32 ctIdx1st, const UINT32 ctIdx2nd );


static void palladium_test_ltm1_constructor(PalladiumTestLtm1 *self)
{
	PalladiumTestLtm1Private *priv = PALLADIUM_TEST_LTM1_GET_PRIVATE(self);
	priv -> a = 0;
}

static void palladium_test_ltm1_destructor(PalladiumTestLtm1 *self)
{
	PalladiumTestLtm1Private *priv = PALLADIUM_TEST_LTM1_GET_PRIVATE(self);
	priv -> a = 0;
}

static VOID ptImLtmRbkDoTest11( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		1, 2, 3, 4, 5, 6, 7, 8,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_RBK_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest19( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		9, 10, 11, 12, 13, 14, 16, 17,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_RBK_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		1, 2, 3, 4, 5, 6,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_RBK_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest27( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		7, 8, 9, 10, 11, 12, 13,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_RBK_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest31( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest32( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest33( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest34( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest35( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest36( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP / 16 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP / 16 );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest37( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP / 64 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP / 64 );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest38( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest39( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest310( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest311( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest312( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest313( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest314( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest315( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_BAY_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP / 4 );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest316( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, '\xee', (D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH + 2) * 3 / 2 * (D_IM_LTM_RBK_SRC_IMG_PIXS_LINES + 2) );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_UP );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_BAY_ADDR_TOP, (D_IM_LTM_RBK_SRC_IMG_PIXS_WIDTH + 2) * 3 / 2 * (D_IM_LTM_RBK_SRC_IMG_PIXS_LINES + 2) );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_UP );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmRbkDoTest318( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " begin\n" ));

#if 0
	// ��o�̓G���A��Fill
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, '\xee', D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );
	memset( (VOID*)D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, '\xee', D_IM_LTM_RBK_DST_IMG_BYTES_P );
#endif

	// ��̓f�[�^
	Palladium_Set_In_Localstack( D_IM_LTM_RBK_IMG_MEM_IN_R_ADDR_TOP, D_IM_LTM_RBK_SRC_IMG_RGB_BYTES );

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_RBK_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// �o�̓_���v
	Palladium_Set_Out_Localstack( D_IM_LTM_RBK_IMG_MEM_OUT_RGB_ADDR_TOP, D_IM_LTM_RBK_DST_IMG_BYTES_P );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest11( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		1, 2, 3, 4, 5, 6, 7,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_MAP_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest18( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		8, 9, 10, 11, 12, 13,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_MAP_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest115( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		15, 16, 17, 18, 19, 20, 21,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_MAP_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_MAP_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

static VOID ptImLtmMapDoTest210( const UINT32 ctIdx1st, const UINT32 ctIdx2nd )
{
	static const UCHAR	no2ndTbl[] = {
		10, 11, 12, 13, 14, 15, 16, 17,
	};
	UINT32				loopcnt;

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	for( loopcnt = 0; loopcnt < (sizeof(no2ndTbl) / sizeof(no2ndTbl[0])); loopcnt++ ) {
		Ddim_Print(( "=-=-=-=-\n" ));
		Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
		CT_Im_LTM_MAP_Run( ctIdx1st, no2ndTbl[loopcnt], 0 );
		Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_%u_%u\n", ctIdx1st, no2ndTbl[loopcnt] ));
	}

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

VOID palladium_test_ltm1_enable_gic( VOID )
{
//	Dd_GIC_Init();
	Dd_GIC_Ctrl( E_DD_GIC_INTID_TIMER_CH0_INT,    1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=118, enable, pri=30
	Dd_GIC_Ctrl( E_DD_GIC_INTID_LTM_UNIT1_INT,    1, D_DD_GIC_PRI30, 1 );		// int enable
	Dd_GIC_Ctrl( E_DD_GIC_INTID_LTM_UNIT2_INT,    1, D_DD_GIC_PRI30, 1 );		// int enable

	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT1_INT,    1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=217, enable, pri=30 SRO_UNIT1_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT1_VD_INT, 1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=218, enable, pri=30 SRO_UNIT1_VD_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT1_HD_INT, 1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=219, enable, pri=30 SRO_UNIT1_HD_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT2_INT,    1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=220, enable, pri=30 SRO_UNIT2_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT2_VD_INT, 1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=221, enable, pri=30 SRO_UNIT2_VD_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_SRO_UNIT2_HD_INT, 1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=222, enable, pri=30 SRO_UNIT2_HD_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2R_UNIT1_INT,    1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=233, enable, pri=30 B2R_UNIT1_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_B2R_UNIT2_INT,    1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=234, enable, pri=30 B2R_UNIT2_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_R2Y_UNIT1_INT,    1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=237, enable, pri=30 R2Y_UNIT1_INT
	Dd_GIC_Ctrl( E_DD_GIC_INTID_R2Y_UNIT2_INT,    1, D_DD_GIC_PRI30, 1 );		//cpu=0, intid=238, enable, pri=30 R2Y_UNIT2_INT
}

VOID palladium_test_ltm1_start_clock( VOID )
{
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_PCLOCK) || defined(CO_ACT_HCLOCK)
#else
	UCHAR imLtm1RbkclkCtrlCnt = 0;
	UCHAR imLtm1ClkCtrlCnt    = 0;
	UCHAR imLtm1HclkCtrlCnt   = 0;
	UCHAR imLtm1PclkCtrlCnt   = 0;
	UCHAR imLtm1IclkCtrlCnt   = 0;
	UCHAR imLtm2RbkclkCtrlCnt = 0;
	UCHAR imLtm2ClkCtrlCnt    = 0;
	UCHAR imLtm2HclkCtrlCnt   = 0;
	UCHAR imLtm2PclkCtrlCnt   = 0;
	UCHAR imLtm2IclkCtrlCnt   = 0;

	Dd_Top_Start_Clock( &imLtm1PclkCtrlCnt,    D_IM_LTM1_PCLK_REG_ADDR,    ~D_IM_LTM1_PCLK_REG_BIT   );
	Dd_Top_Start_Clock( &imLtm1HclkCtrlCnt,    D_IM_LTM1_HCLK_REG_ADDR,    ~D_IM_LTM1_HCLK_REG_BIT   );
	Dd_Top_Start_Clock( &imLtm1IclkCtrlCnt,    D_IM_LTM1_ACLK_REG_ADDR,    ~D_IM_LTM1_ACLK_REG_BIT   );
	Dd_Top_Start_Clock( &imLtm1ClkCtrlCnt,     D_IM_LTM1_CLK_REG_ADDR,     ~D_IM_LTM1_CLK_REG_BIT    );
	Dd_Top_Start_Clock( &imLtm1RbkclkCtrlCnt,  D_IM_LTM1_RBKCLK_REG_ADDR,  ~D_IM_LTM1_RBKCLK_REG_BIT );

	Dd_Top_Start_Clock( &imLtm2PclkCtrlCnt,    D_IM_LTM2_PCLK_REG_ADDR,    ~D_IM_LTM2_PCLK_REG_BIT   );
	Dd_Top_Start_Clock( &imLtm2HclkCtrlCnt,    D_IM_LTM2_HCLK_REG_ADDR,    ~D_IM_LTM2_HCLK_REG_BIT   );
	Dd_Top_Start_Clock( &imLtm2IclkCtrlCnt,    D_IM_LTM2_ACLK_REG_ADDR,    ~D_IM_LTM2_ACLK_REG_BIT   );
	Dd_Top_Start_Clock( &imLtm2ClkCtrlCnt,     D_IM_LTM2_CLK_REG_ADDR,     ~D_IM_LTM2_CLK_REG_BIT    );
	Dd_Top_Start_Clock( &imLtm2RbkclkCtrlCnt,  D_IM_LTM2_RBKCLK_REG_ADDR,  ~D_IM_LTM2_RBKCLK_REG_BIT );
#endif
}

VOID palladium_test_ltm1_rbk_run1( const UINT32 type2 )
{
	UCHAR			type3;

	type3	= gDDIM_Info.com._6c;

	switch( type3 ) {
		case 1:
			ptImLtmRbkDoTest11( type2, type3 );
			break;
		case 9:
			ptImLtmRbkDoTest19( type2, type3 );
			break;
		default:
			Ddim_Print(("*** LTM RBK test skip\n" ));
			break;
	}
}

VOID palladium_test_ltm1_rbk_run2( const UINT32 type2 )
{
	UCHAR			type3;

	type3	= gDDIM_Info.com._6c;

	switch( type3 ) {
		case 1:
			ptImLtmRbkDoTest21( type2, type3 );
			break;
		case 7:
			ptImLtmRbkDoTest27( type2, type3 );
			break;
		default:
			Ddim_Print(("*** LTM RBK test skip\n" ));
			break;
	}
}

VOID palladium_test_ltm1_rbk_run3( const UINT32 type2 )
{
	UCHAR			type3;
	UCHAR			type4;

	type3	= gDDIM_Info.com._6c;
	type4	= gDDIM_Info.com._6d;

	switch( type3 ) {
		case 1:
			ptImLtmRbkDoTest31( type2, type3, type4 );
			break;
		case 2:
			ptImLtmRbkDoTest32( type2, type3, type4 );
			break;
		case 3:
			ptImLtmRbkDoTest33( type2, type3, type4 );
			break;
		case 4:
			ptImLtmRbkDoTest34( type2, type3, type4 );
			break;
		case 5:
			ptImLtmRbkDoTest35( type2, type3, type4 );
			break;
		case 6:
			ptImLtmRbkDoTest36( type2, type3, type4 );
			break;
		case 7:
			ptImLtmRbkDoTest37( type2, type3, type4 );
			break;
		case 8:
			ptImLtmRbkDoTest38( type2, type3, type4 );
			break;
		case 9:
			ptImLtmRbkDoTest39( type2, type3, type4 );
			break;
		case 10:
			ptImLtmRbkDoTest310( type2, type3, type4 );
			break;
		case 11:
			ptImLtmRbkDoTest311( type2, type3, type4 );
			break;
		case 12:
			ptImLtmRbkDoTest312( type2, type3, type4 );
			break;
		case 13:
			ptImLtmRbkDoTest313( type2, type3, type4 );
			break;
		case 14:
			ptImLtmRbkDoTest314( type2, type3, type4 );
			break;
		case 15:
			ptImLtmRbkDoTest315( type2, type3, type4 );
			break;
		case 16:
			ptImLtmRbkDoTest316( type2, type3, type4 );
			break;
		case 18:
			ptImLtmRbkDoTest318( type2, type3, type4 );
			break;
		default:
			Ddim_Print(("*** LTM RBK test skip\n" ));
			break;
	}
}

VOID palladium_test_ltm1_map_run1( const UINT32 type2 )
{
	UCHAR			type3;

	type3	= gDDIM_Info.com._6c;

	switch( type3 ) {
		case 1:
			ptImLtmMapDoTest11( type2, type3 );
			break;
		case 8:
			ptImLtmMapDoTest18( type2, type3 );
			break;
		case 15:
			ptImLtmMapDoTest115( type2, type3 );
			break;
		default:
			Ddim_Print(("*** LTM MAP test skip\n" ));
			break;
	}
}

VOID palladium_test_ltm1_rbk_run9( const UINT32 type1 )
{
	UCHAR			type2;

	type2	= gDDIM_Info.com._6c;

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO "%u begin\n", type2 ));


	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "=-=-=-=-\n" ));
	Ddim_Print(( "* LTM RBK begin CT_Im_Ltm_Rbk_1_%u\n", type2 ));
	CT_Im_LTM_RBK_Run( 1, type2, 0 );
	Ddim_Print(( "* LTM RBK end CT_Im_Ltm_Rbk_1_%u\n", type2 ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM RBK test " D_IM_LTM_TEST_NO "%u end\n", type2 ));
}

VOID palladium_test_ltm1_map_run2( const UINT32 type2 )
{
	UCHAR			type3;

	type3	= gDDIM_Info.com._6c;

	switch( type3 ) {
		case 1:
			ptImLtmMapDoTest21( type2, type3 );
			break;
		case 10:
			ptImLtmMapDoTest210( type2, type3 );
			break;
		default:
			Ddim_Print(("*** LTM MAP test skip\n" ));
			break;
	}
}

VOID palladium_test_ltm1_map_do_test_31( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
{
	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " begin\n" ));

	// �^�C�}�[�N��
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	// �e�X�g�R�[�h�N��
	Ddim_Print(( "* LTM MAP begin CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));
	CT_Im_LTM_MAP_Run( ctIdx1st, ctIdx2nd, ctIdx3rd );
	Ddim_Print(( "* LTM MAP end CT_Im_Ltm_Map_" D_IM_LTM_TEST_NO "\n" ));

	// �^�C�}�[��~
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	Ddim_Print(( "*** LTM MAP test " D_IM_LTM_TEST_NO " end\n" ));
}

VOID palladium_test_ltm1_map_do_test_32( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd )
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

PalladiumTestLtm1* palladium_test_ltm1_new(void)
{
	PalladiumTestLtm1 *self = k_object_new_with_private(PALLADIUM_TYPE_TEST_LTM1, sizeof(PalladiumTestLtm1Private));
	return self;
}
