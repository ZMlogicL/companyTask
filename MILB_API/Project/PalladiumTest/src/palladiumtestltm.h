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

#ifndef __PALLADIUM_TEST_LTM_H__
#define __PALLADIUM_TEST_LTM_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_LTM	(palladium_test_ltm_get_type())
#define PALLADIUM_TEST_LTMER(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestLtm)
#define PALLADIUM_IS_TEST_LTM(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_LTM)

typedef struct _PalladiumTestLtm		PalladiumTestLtm;
struct _PalladiumTestLtm
{
	KObject parent;
};


KConstType 										palladium_test_ltm_get_type(void);
PalladiumTestLtm* 							palladium_test_ltm_new(void);
VOID 													ptImLtmRbkRun( VOID );
VOID 													ptImLtmMapRun( VOID );
VOID 													ptImLtmMain( VOID );
VOID 													ptImLtmLtmRun( VOID );

#endif /* __PALLADIUM_TEST_LTM_H__ */

