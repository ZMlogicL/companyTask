/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-10
*@author : 刘嫚鶄
*@brief : PalladiumTestHdmi
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __PALLADIUM_TEST_HDMI_H__
#define __PALLADIUM_TEST_HDMI_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_HDMI                  (palladium_test_hdmi_get_type())
#define PALLADIUM_TEST_HDMI(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, PalladiumTestHdmi)) 
#define PALLADIUM_IS_TEST_HDMI(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PALLADIUM_TYPE_TEST_HDMI)) 

typedef struct _PalladiumTestHdmi PalladiumTestHdmi;
typedef struct _PalladiumTestHdmiPrivate PalladiumTestHdmiPrivate;

struct _PalladiumTestHdmi 
{
	KObject parent;
};

KConstType palladium_test_hdmi_get_type(void);
PalladiumTestHdmi* palladium_test_hdmi_new(void);

VOID 		pt_im_hdmi_main( VOID );

#endif /* __PALLADIUM_TEST_HDMI_H__ */
