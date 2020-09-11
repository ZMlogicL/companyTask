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

#ifndef __PALLADIUM_TEST_TMR32_H__
#define __PALLADIUM_TEST_TMR32_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_TMR32	(palladium_test_tmr32_get_type())
#define PALLADIUM_TEST_TMR32(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestTmr32)
#define PALLADIUM_IS_TEST_TMR32(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_TMR32)

typedef struct 				_PalladiumTestTmr32 PalladiumTestTmr32;
typedef struct 				_PalladiumTestTmr32Private		PalladiumTestTmr32Private;

struct _PalladiumTestTmr32 {
	KObject parent;
};

KConstType 					palladium_test_tmr32_get_type(void);
PalladiumTestTmr32* 	palladium_test_tmr32_new(void);

void 								palladium_test_tmr32_pt_dd_tmr32_main(void);

#endif /* __PALLADIUM_TEST_TMR32_H__ */

