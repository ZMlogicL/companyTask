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

#ifndef __PALLADIUM_TEST_CNR1_H__
#define __PALLADIUM_TEST_CNR1_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_CNR1		    (palladium_test_cnr1_get_type())
#define PALLADIUM_TEST_CNR1(obj)		        (K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestCnr1))
#define PALLADIUM_IS_TEST_CNR1(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_CNR1))

typedef struct 				_PalladiumTestCnr1 PalladiumTestCnr1;
typedef struct 				_PalladiumTestCnr1Private PalladiumTestCnr1Private;

struct _PalladiumTestCnr1 {
	KObject parent;
};

KConstType 		    palladium_test_cnr1_get_type(void);

void                                palladium_test_cnr1_im_otf_2_8(PalladiumTestCnr1* self, kuchar ch );
void                                palladium_test_cnr1_im_ofl_2_9(PalladiumTestCnr1* self, kuchar ch );
void                                palladium_test_cnr1_im_otf_2_9(PalladiumTestCnr1* self, kuchar ch );
void                                palladium_test_cnr1_im_ofl_2_10(PalladiumTestCnr1* self, kuchar ch );
void                                palladium_test_cnr1_im_ofl_2_11(PalladiumTestCnr1* self, kuchar ch );
void                                palladium_test_cnr1_im_otf_2_11(PalladiumTestCnr1* self, kuchar ch );
void                                palladium_test_cnr1_im_ofl_2_12(PalladiumTestCnr1* self, kuchar ch );
void                                palladium_test_cnr1_im_otf_2_12(PalladiumTestCnr1* self, kuchar ch );
void                                palladium_test_cnr1_im_ofl_2_13(PalladiumTestCnr1* self, kuchar ch );
void                                palladium_test_cnr1_im_run_5( PalladiumTestCnr1* self,const kuint32 type1 );
void                                palladium_test_cnr1_im_run_6( PalladiumTestCnr* self,const kuint32 type1 );
PalladiumTestCnr1*	   palladium_test_cnr1_new(void);

#endif /* __PALLADIUM_TEST_CNR1_H__ */
