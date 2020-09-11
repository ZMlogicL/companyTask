/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : maoguangkun
*@brief : ShdrTest21
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __SHDR_TEST2_1_H__
#define __SHDR_TEST2_1_H__


#include <klib.h>

#include "shdrtest23.h"


#define SHDR_TYPE_TEST2_1                  (shdr_test2_1_get_type())
#define SHDR_TEST2_1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ShdrTest21)) 
#define SHDR_IS_TEST2_1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, SHDR_TYPE_TEST2_1)) 


typedef struct _ShdrTest21 ShdrTest21;
typedef struct _ShdrTest21Private ShdrTest21Private;


struct _ShdrTest21 
{
	KObject parent;
};


KConstType 		shdr_test2_1_get_type(void);
ShdrTest21* 		shdr_test2_1_get(void);

VOID 					ct_im_shdr_test2_1(ShdrTest21* self);

#endif /* __SHDR_TEST2_1_H__ */
