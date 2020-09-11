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

#ifndef __PALLADIUM_TEST_CNR2_H__
#define __PALLADIUM_TEST_CNR2_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_CNR2		    (palladium_test_cnr2_get_type())
#define PALLADIUM_TEST_CNR2(obj)		        (K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestCnr2))
#define PALLADIUM_IS_TEST_CNR2(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_CNR2))

typedef struct 				_PalladiumTestCnr2 PalladiumTestCnr2;
typedef struct 				_PalladiumTestCnr2Private PalladiumTestCnr2Private;

struct _PalladiumTestCnr2 {
	KObject parent;
};

KConstType 		    palladium_test_cnr2_get_type(void);

void                                         palladium_test_cnr2_im_ofl_2_1(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_otf_2_1(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_ofl_2_2(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_ofl_2_3(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_ofl_2_4(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_otf_2_4(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_ofl_2_5(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_otf_2_5(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_ofl_2_6(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_otf_2_6(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_ofl_2_7(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_otf_2_7(PalladiumTestCnr2*self, kuchar ch );
void                                         palladium_test_cnr2_im_ofl_2_8(PalladiumTestCnr2*self, kuchar ch );
PalladiumTestCnr2*		        palladium_test_cnr2_new(void);

#endif /* __PALLADIUM_TEST_CNR2_H__ */
