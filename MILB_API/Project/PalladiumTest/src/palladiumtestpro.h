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

#ifndef __PALLADIUM_TEST_PRO_H__
#define __PALLADIUM_TEST_PRO_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_PRO	(palladium_test_pro_get_type())
#define PALLADIUM_TEST_PRO(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestPro)
#define PALLADIUM_IS_TEST_PRO(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_PRO)

typedef struct 				_PalladiumTestPro PalladiumTestPro;

struct _PalladiumTestPro{
	KObject parent;
};

KConstType 				palladium_test_pro_get_type(void);
PalladiumTestPro* 	palladium_test_pro_new(void);
void 							palladium_test_pro_main( void );

#endif /* __PALLADIUM_TEST_PRO_H__ */

