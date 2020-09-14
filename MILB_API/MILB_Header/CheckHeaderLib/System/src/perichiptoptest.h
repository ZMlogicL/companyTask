/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :郑蛘钊
*@brief             :perichiptoptest
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __PERI_CHIPTOP_TEST_H__
#define __PERI_CHIPTOP_TEST_H__


#include <klib.h>


#define PERI_TYPE_CHIPTOP_TEST	        (peri_chiptop_test_get_type())
#define PERI_CHIPTOP_TEST(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), PeriChiptopTest))
#define PERI_IS_CHIPTOP_TEST(obj)	    (K_TYPE_CHECK_INSTANCE_TYPE((obj), PERI_TYPE_CHIPTOP_TEST))


typedef struct _PeriChiptopTest	        PeriChiptopTest;
typedef struct _PeriChiptopTestPrivate	PeriChiptopTestPrivate;


struct  _PeriChiptopTest
{
	KObject parent;
};


KConstType	     peri_chiptop_test_get_type(void);
PeriChiptopTest* peri_chiptop_test_new(void);
void             peri_chiptop_test_peri_test(PeriChiptopTest *self);
void             peri_chiptop_test_chiptop_test(PeriChiptopTest *self);


#endif/*__PERI_CHIPTOP_TEST_H__*/
