/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :于孟孟
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#include "checkheadermaindefs.h"


K_TYPE_DEFINE_WITH_PRIVATE(IntErnals, int_ernals);
#define INT_ERNALS_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), IntErnalsPrivate, INT_TYPE_ERNALS))


struct _IntErnalsPrivate
{
	int a;
};
/*
 * IMPL
 */
static void int_ernals_constructor(IntErnals *self)
{
	IntErnalsPrivate *priv = INT_ERNALS_GET_PRIVATE(self);
}

static void int_ernals_destructor(IntErnals *self)
{
	IntErnalsPrivate *priv = INT_ERNALS_GET_PRIVATE(self);
}
/*
 * PUBLIC
 */
IntErnals *int_ernals_new(void)
{
	IntErnals* self = k_object_new_with_private(INT_TYPE_ERNALS,sizeof(IntErnalsPrivate));

	return self;
}
