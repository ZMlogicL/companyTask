/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-09
*@author : 刘嫚鶄
*@brief : PalladiumTestMe
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __PALLADIUM_TEST_ME_H__
#define __PALLADIUM_TEST_ME_H__


#include <klib.h>


#define PALLADIUM_TYPE_TEST_ME                  (palladium_test_me_get_type())
#define PALLADIUM_TEST_ME(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, PalladiumTestMe)) 
#define PALLADIUM_IS_TEST_ME(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PALLADIUM_TYPE_TEST_ME)) 


typedef struct _PalladiumTestMe PalladiumTestMe;
typedef struct _PalladiumTestMePrivate PalladiumTestMePrivate;

struct _PalladiumTestMe 
{
	KObject parent;
};

KConstType palladium_test_me_get_type(void);
PalladiumTestMe* palladium_test_me_new(void);

/*
 * PUBLIC
 */

void pt_im_me_main(PalladiumTestMe *self );

#endif /* __PALLADIUM_TEST_ME_H__ */
