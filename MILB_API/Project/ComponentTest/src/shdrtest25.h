/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : maoguangkun
*@brief : ShdrTest25
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __SHDR_TEST2_5_H__
#define __SHDR_TEST2_5_H__


#include <klib.h>

#include "ctimshdrerr.h"


#define SHDR_TYPE_TEST2_5                  (shdr_test2_5_get_type())
#define SHDR_TEST2_5(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ShdrTest25)) 
#define SHDR_IS_TEST2_5(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, SHDR_TYPE_TEST2_5)) 


typedef struct _ShdrTest25 ShdrTest25;
typedef struct _ShdrTest25Private ShdrTest25Private;


struct _ShdrTest25 
{
	KObject parent;
};


KConstType					shdr_test2_5_get_type(void);
ShdrTest25*				shdr_test2_5_get(void);

VOID 							ct_im_shdr_test2_5(ShdrTest25* self);
VOID							ct_im_shdr_test2_5_test(ShdrTest25* self, TImShdrParam* shdr_param);

#endif /* __SHDR_TEST2_5_H__ */
