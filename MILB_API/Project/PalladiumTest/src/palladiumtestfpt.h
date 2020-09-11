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

#ifndef __PALLADIUM_TEST_FPT_H__
#define __PALLADIUM_TEST_FPT_H__

#include <klib.h>

#define PALLADIUM_TYPE_TEST_FPT	(palladium_test_fpt_get_type())
#define PALLADIUM_TEST_FPT(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestFpt)
#define PALLADIUM_IS_TEST_FPT(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_FPT)

typedef struct 				_PalladiumTestFpt PalladiumTestFpt;
typedef struct 				_PalladiumTestFptPrivate		PalladiumTestFptPrivate;
struct _PalladiumTestFpt {
	KObject parent;
};


KConstType 			palladium_test_fpt_get_type(void);
PalladiumTestFpt* 	palladium_test_fpt_new(void);

VOID 						palladium_test_fpt_pt_im_fpt_main( VOID );

#endif /* __PALLADIUM_TEST_FPT_H__ */

