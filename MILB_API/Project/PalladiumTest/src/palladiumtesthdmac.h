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

#ifndef __PALLADIUM_TEST_HDMAC_H__
#define __PALLADIUM_TEST_HDMAC_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_HDMAC	    (palladium_test_hdmac_get_type())
#define PALLADIUM_TEST_HDMAC(obj)       	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestHdmac)
#define PALLADIUM_IS_TEST_HDMAC(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_HDMAC)

typedef struct _PalladiumTestHdmac   PalladiumTestHdmac;
typedef struct _PalladiumTestHdmacPrivate   PalladiumTestHdmacPrivate;

struct _PalladiumTestHdmac{
  KObject parent;
};


KConstType 		                palladium_test_hdmac_get_type(void);
PalladiumTestHdmac* 	palladium_test_hdmac_new(void);

/*
 * PUBLIC
 */
void                                palladium_test_hdmac_dd_main( void );

#endif /* __PALLADIUM_TEST_HDMAC_H__ */

