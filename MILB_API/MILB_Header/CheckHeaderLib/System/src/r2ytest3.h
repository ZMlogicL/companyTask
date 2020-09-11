/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :陈倩
*@brief             :r2ytest3
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


#ifndef __R2Y_TEST3_H__
#define __R2Y_TEST3_H__


#include <klib.h>


#define R2Y_TYPE_TEST3	(r2y_test3_get_type())
#define R2Y_TEST3(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), R2yTest3))
#define R2Y_IS_TEST3(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), R2yTest3))


typedef struct _R2yTest3	R2yTest3;
typedef struct _R2yTest3Private	R2yTest3Private;

struct  _R2yTest3
{
	KObject parent;
};


KConstType			r2y_test3_get_type(void);
R2yTest3*			r2y_test3_new(void);
void 					r2y_test3_r2y_test(R2yTest3 *self);

#endif/*__R2Y_TEST3_H__*/

