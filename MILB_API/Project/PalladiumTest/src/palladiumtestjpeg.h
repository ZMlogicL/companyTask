/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-04-20
*@author              :
*@brief               :snsnet网络协议栈
*@rely                :klib
*@function
*SNSNET，采用ETK-C语言编写
*设计的主要功能:
*@version
*1.0.0 2020年04月开始开发
*/

#ifndef __PALLADIUM_TEST_JPEG_H__
#define __PALLADIUM_TEST_JPEG_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_JPEG			(palladium_test_jpeg_get_type())
#define PALLADIUM_TEST_JPEG(obj) 		K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestJpeg)
#define PALLADIUM_IS_TEST_JPEG(obj) 		K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_JPEG)

typedef struct _PalladiumTestJpeg PalladiumTestJpeg;
typedef struct _PalladiumTestJpegPrivate PalladiumTestJpegPrivate;

struct _PalladiumTestJpeg{
	KObject parent;
};

KConstType 								palladium_test_jpeg_get_type(void);
PalladiumTestJpeg* 					palladium_test_jpeg_new(void);

//Pt_Im_JPEG_Main
void 											palladium_test_jpeg_main( void );

#endif /* __PALLADIUM_TEST_JPEG_H__ */

