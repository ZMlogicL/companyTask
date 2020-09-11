/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :刘杰
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

#ifndef __PALLADIUM_TEST_SHDR_H__
#define __PALLADIUM_TEST_SHDR_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_SHDR	    (palladium_test_shdr_get_type())
#define PALLADIUM_TEST_SHDR(obj) 	    K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestShdr)
#define PALLADIUM_IS_TEST_SHDR(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_SHDR)

typedef struct _PalladiumTestShdr    PalladiumTestShdr;
typedef struct _PalladiumTestShdrPrivate    PalladiumTestShdrPrivate;

struct _PalladiumTestShdr{
  KObject parent;
};


KConstType 		            palladium_test_shdr_get_type(void);
PalladiumTestShdr* 	palladium_test_shdr_new(void);

/*
 * PUBLIC
 */
void palladium_test_shdr_im_main( void );

#endif /* __PALLADIUM_TEST_SHDR_H__ */

