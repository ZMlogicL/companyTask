/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-06-13
*@author              :
*@brief               :snsos
*@rely                :klib
*@function
*采用ETK-C语言抄写代码
*设计的主要功能:
*@version
*1.0.0 2020年06月开始开发
*/


#ifndef __PALLADIUM_TEST_MIPI_A_H_
#define __PALLADIUM_TEST_MIPI_A_H_

#include <klib.h>

#define PALLADIUM_TYPE_TEST_MIPI_A	(palladium_test_mipi_a_get_type())
#define PALLADIUM_TEST_MIPI_AER(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestMipiA)
#define PALLADIUM_IS_TEST_MIPI_A(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_MIPI_A)

typedef struct _PalladiumTestMipiA   PalladiumTestMipiA  ;
typedef struct _PalladiumTestMipiAPrivate		PalladiumTestMipiAPrivate;

struct _PalladiumTestMipiA{
	KObject parent;
};

KConstType 					palladium_test_mipi_a_get_type(void);
VOID 								palladium_test_mipi_a_pt_Im_mipi_main(PalladiumTestMipiA* self );
PalladiumTestMipiA* 	palladium_test_mipi_a_new(void);

#endif /* __PALLADIUM_TEST_MIPI_A_H_ */

