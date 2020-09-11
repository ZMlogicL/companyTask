/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :陈倩
*@brief             :r2ytest1
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


#ifndef __R2Y_TEST1_H__
#define __R2Y_TEST1_H__


#include <klib.h>


#define R2Y_TYPE_TEST1	(r2y_test1_get_type())
#define R2Y_TEST1(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), R2yTest1))
#define R2Y_IS_TEST1(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), R2yTest1))


typedef struct _R2yTest1	R2yTest1;
typedef struct _R2yTest1Private	R2yTest1Private;

struct  _R2yTest1
{
	KObject parent;
};


KConstType			r2y_test1_get_type(void);
R2yTest1*			r2y_test1_new(void);
void 					r2y_test1_r2y_test(R2yTest1 *self);

#endif/*__R2Y_TEST1_H__*/

