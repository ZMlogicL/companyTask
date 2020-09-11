/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-04-20
*@author              :
*@brief               :snsnet网络协议栈
*@rely                :klib
*@function
*SNSNET，采用ETK-C语言编写
*设计的主要功能:
*@version
*1.0.0 2020年04月开始开发
*/

#ifndef __PALLADIUM_TEST_LTM1_H__
#define __PALLADIUM_TEST_LTM1_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_LTM1	(palladium_test_ltm1_get_type())
#define PALLADIUM_TEST_LTM1(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestLtm1)
#define PALLADIUM_IS_TEST_LTM1(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_LTM1)

typedef struct _PalladiumTestLtm1		PalladiumTestLtm1;
struct _PalladiumTestLtm1
{
	KObject parent;
};



KConstType 												palladium_test_ltm1_get_type(void);
PalladiumTestLtm1* 									palladium_test_ltm1_new(void);
VOID 															palladium_test_ltm1_enable_gic( VOID );
VOID 															palladium_test_ltm1_start_clock( VOID );
VOID 															palladium_test_ltm1_rbk_run1( const UINT32 type2 );
VOID 															palladium_test_ltm1_rbk_run2( const UINT32 type2 );
VOID 															palladium_test_ltm1_rbk_run3( const UINT32 type2 );
VOID 															palladium_test_ltm1_map_run1( const UINT32 type2 );
VOID 															palladium_test_ltm1_rbk_run9( const UINT32 type1 );
VOID 															palladium_test_ltm1_map_run2( const UINT32 type2 );
VOID 															palladium_test_ltm1_map_do_test_31( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID 															palladium_test_ltm1_map_do_test_32( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );

#endif /* __PALLADIUM_TEST_LTM_1_H__ */

