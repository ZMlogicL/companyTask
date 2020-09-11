/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :郭江龙
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __PALLADIUM_TEST_CNR_H__
#define __PALLADIUM_TEST_CNR_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_CNR		    (palladium_test_cnr_get_type())
#define PALLADIUM_TEST_CNR(obj)		    (K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestCnr))
#define PALLADIUM_IS_TEST_CNR(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_CNR))

typedef struct 				_PalladiumTestCnr PalladiumTestCnr;
typedef struct 				_PalladiumTestCnrPrivate PalladiumTestCnrPrivate;

struct _PalladiumTestCnr {
	KObject parent;
};

KConstType 		    palladium_test_cnr_get_type(void);

void                                 palladium_test_cnr_im_main(void);
PalladiumTestCnr*       palladium_test_cnr_new(void);

#endif /* __PALLADIUM_TEST_CNR_H__ */
