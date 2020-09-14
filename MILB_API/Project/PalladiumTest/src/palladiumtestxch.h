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

#ifndef __PALLADIUM_TEST_XCH_H__
#define __PALLADIUM_TEST_XCH_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_XCH	(palladium_test_xch_get_type())
#define PALLADIUM_TEST_XCH(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestXch)
#define PALLADIUM_IS_TEST_XCH(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_XCH)

typedef struct _PalladiumTestXch PalladiumTestXch;
typedef struct _PalladiumTestXchPrivate PalladiumTestXchPrivate;

struct _PalladiumTestXch{
	KObject parent;
};

KConstType 								palladium_test_xch_get_type(void);
PalladiumTestXch* 					palladium_test_xch_new(void);

void 											palladium_test_xch_im_main( void );

#endif /* __PALLADIUM_TEST_XCH_H__ */

