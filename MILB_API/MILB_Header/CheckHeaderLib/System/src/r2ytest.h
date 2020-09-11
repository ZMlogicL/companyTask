/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :陈倩
*@brief             :r2ytest
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*3、
*4、
*5、
*@version
*
*/


#ifndef __R2Y_TEST_H__
#define __R2Y_TEST_H__


#include <klib.h>


#define R2Y_TYPE_TEST	(r2y_test_get_type())
#define R2Y_TEST(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), R2yTest))
#define R2Y_IS_TEST(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), R2yTest))


typedef struct _R2yTest	R2yTest;
typedef struct _R2yTestPrivate	R2yTestPrivate;

struct  _R2yTest
{
	KObject parent;
};


KConstType		r2y_test_get_type(void);
R2yTest*			r2y_test_new(void);
void 				r2y_test(R2yTest *self);

#endif/*__R2Y_TEST_H__*/

