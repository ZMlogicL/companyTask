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

#ifndef __PALLADIUM_TEST_HDMAC0_H__
#define __PALLADIUM_TEST_HDMAC0_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_HDMAC0	    (palladium_test_hdmac0_get_type())
#define PALLADIUM_TEST_HDMAC0(obj) 	      K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestHdmac0)
#define PALLADIUM_IS_TEST_HDMAC0(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_HDMAC0)

typedef struct _PalladiumTestHdmac0    PalladiumTestHdmac0;
typedef struct _PalladiumTestHdmac0Private    PalladiumTestHdmac0Private;

struct _PalladiumTestHdmac0{
  KObject parent;
};


KConstType 		                  palladium_test_hdmac0_get_type(void);
PalladiumTestHdmac0* 	palladium_test_hdmac0_new(void);

/*
 * PUBLIC
 */
void                                  palladium_test_hdmac0_dd_main(PalladiumTestHdmac0 *self);

#endif /* __PALLADIUM_TEST_HDMAC0_H__ */

