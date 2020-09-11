/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-10
*@author : 周云飞
*@brief : PalladiumTestRaw
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

#ifndef __PALLADIUM_TEST_RAW_H__
#define __PALLADIUM_TEST_RAW_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_RAW                  (palladium_test_raw_get_type())
#define PALLADIUM_TEST_RAW(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, PalladiumTestRaw)) 
#define PALLADIUM_IS_TEST_RAW(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PALLADIUM_TYPE_TEST_RAW)) 

typedef struct _PalladiumTestRaw PalladiumTestRaw;
typedef struct _PalladiumTestRawPrivate PalladiumTestRawPrivate;

struct _PalladiumTestRaw 
{
	KObject parent;
};

KConstType 					palladium_test_raw_get_type(void);
PalladiumTestRaw* 		palladium_test_raw_new(void);

/*
 * PUBLIC
 */

VOID  								pt_im_raw_main( VOID );

#endif /* __PALLADIUM_TEST_RAW_H__ */
