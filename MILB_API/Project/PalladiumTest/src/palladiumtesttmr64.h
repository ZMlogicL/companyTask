/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-08
*@author : aorongxing
*@brief : PalladiumTestTmr64
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 
*
*/


#ifndef __PALLADIUM_TEST_TMR64_H__
#define __PALLADIUM_TEST_TMR64_H__


#include <klib.h>


#define PALLADIUM_TYPE_TEST_TMR64                  (palladium_test_tmr64_get_type())
#define PALLADIUM_TEST_TMR64(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, PalladiumTestTmr64)) 
#define PALLADIUM_IS_TEST_TMR64(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PALLADIUM_TYPE_TEST_TMR64)) 


typedef struct _PalladiumTestTmr64 PalladiumTestTmr64;
typedef struct _PalladiumTestTmr64Private PalladiumTestTmr64Private;

struct _PalladiumTestTmr64 
{
	KObject parent;
};


KConstType 					palladium_test_tmr64_get_type(void);
PalladiumTestTmr64* 	palladium_test_tmr64_new(void);

void 								palladium_test_tmr64_pt_dd_main(PalladiumTestTmr64* self);

#endif /* __PALLADIUM_TEST_TMR64_H__ */
