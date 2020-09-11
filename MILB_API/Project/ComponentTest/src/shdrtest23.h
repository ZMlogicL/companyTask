/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : maoguangkun
*@brief : ShdrTest23
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __SHDR_TEST2_3_H__
#define __SHDR_TEST2_3_H__


#include <klib.h>

#include "shdrtest25.h"


#define SHDR_TYPE_TEST2_3                  (shdr_test2_3_get_type())
#define SHDR_TEST2_3(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ShdrTest23)) 
#define SHDR_IS_TEST2_3(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, SHDR_TYPE_TEST2_3)) 


typedef struct _ShdrTest23 ShdrTest23;
typedef struct _ShdrTest23Private ShdrTest23Private;


struct _ShdrTest23 
{
	KObject parent;
};


KConstType 			shdr_test2_3_get_type(void);
ShdrTest23*			shdr_test2_3_get(void);

VOID 						ct_im_shdr_test2_3(ShdrTest23* self);
VOID 						ct_im_shdr_tset2_3_lineint_callback(ShdrTest23* self);
VOID 						ct_im_shdr_tset2_3_callback(ShdrTest23* self);

#endif /* __SHDR_TEST2_3_H__ */
