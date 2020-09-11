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

#ifndef __PALLADIUM_TEST_SDRAMC_H__
#define __PALLADIUM_TEST_SDRAMC_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_SDRAMC	(palladium_test_sdramc_get_type())
#define PALLADIUM_TEST_SDRAMC(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestSdramc)
#define PALLADIUM_IS_TEST_SDRAMC(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_SDRAMC)

typedef struct 				_PalladiumTestSdramc PalladiumTestSdramc;
typedef struct 				_PalladiumTestSdramcPrivate PalladiumTestSdramcPrivate;

struct _PalladiumTestSdramc {
	KObject parent;
};

KConstType 						palladium_test_sdramc_get_type(void);
PalladiumTestSdramc* 	palladium_test_sdramc_new(void);

void 									palladium_test_sdramc_im_sdramc_main( void );

#endif /* __PALLADIUM_TEST_SDRAMC_H__ */

