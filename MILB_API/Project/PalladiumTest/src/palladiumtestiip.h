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

#ifndef __PALLADIUM_TEST_IIP_H__
#define __PALLADIUM_TEST_IIP_H__

#include <klib.h>
#include "ddim_typedef.h"

#define PALLADIUM_TYPE_TEST_IIP	(palladium_test_iip_get_type())
#define PALLADIUM_TEST_IIP(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestIip)
#define PALLADIUM_IS_TEST_IIP(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_IIP)

typedef struct	_PalladiumTestIip 					PalladiumTestIip;
typedef struct  _PalladiumTestIipPrivate		PalladiumTestIipPrivate;

struct	_PalladiumTestIip{
	KObject parent;
};

KConstType 			palladium_test_iip_get_type(void);


#ifdef __cplusplus
extern "C" {
#endif
VOID 						palladium_test_iip_Pt_Im_IIP_Main( PalladiumTestIip* self );
#ifdef __cplusplus
}
#endif

PalladiumTestIip* 	palladium_test_iip_new(void);
#endif /* __PALLADIUM_TEST_IIP_H__ */

