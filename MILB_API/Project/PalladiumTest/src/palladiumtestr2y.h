/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-08
*@author : aorongxing
*@brief : PalladiumTestR2y
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 
*
*/


#ifndef __PALLADIUM_TEST_R2Y_H__
#define __PALLADIUM_TEST_R2Y_H__


#include <klib.h>


#define PALLADIUM_TYPE_TEST_R2Y                  (palladium_test_r2y_get_type())
#define PALLADIUM_TEST_R2Y(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, PalladiumTestR2y)) 
#define PALLADIUM_IS_TEST_R2Y(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PALLADIUM_TYPE_TEST_R2Y)) 


typedef struct _PalladiumTestR2y PalladiumTestR2y;
typedef struct _PalladiumTestR2yPrivate PalladiumTestR2yPrivate;

struct _PalladiumTestR2y 
{
	KObject parent;
};


KConstType 				palladium_test_r2y_get_type(void);
PalladiumTestR2y* 	palladium_test_r2y_new(void);

void 							palladium_test_r2y_main(PalladiumTestR2y* self);

#endif /* __PALLADIUM_TEST_R2Y_H__ */
