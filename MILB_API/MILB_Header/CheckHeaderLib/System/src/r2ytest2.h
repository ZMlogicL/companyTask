/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :陈倩
*@brief             :r2ytest2
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


#ifndef __R2Y_TEST2_H__
#define __R2Y_TEST2_H__


#include <klib.h>


#define R2Y_TYPE_TEST2	(r2y_test2_get_type())
#define R2Y_TEST2(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), R2yTest2))
#define R2Y_IS_TEST2(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), R2yTest2))


typedef struct _R2yTest2	R2yTest2;
typedef struct _R2yTest2Private	R2yTest2Private;

struct  _R2yTest2
{
	KObject parent;
};


KConstType			r2y_test2_get_type(void);
R2yTest2*			r2y_test2_new(void);
void 					r2y_test2_r2y_test(R2yTest2 *self);

#endif/*__R2Y_TEST2_H__*/

