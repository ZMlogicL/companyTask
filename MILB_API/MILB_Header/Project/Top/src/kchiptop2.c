/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :申雨
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


#include "kchiptop2.h"


K_TYPE_DEFINE_WITH_PRIVATE(KChiptop2, k_chiptop2);
#define K_CHIPTOP2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KChiptop2Private, K_TYPE_CHIPTOP2))


struct _KChiptop2Private
{
	kint a;
};
/*
 * IMPL
 */
static void k_chiptop2_constructor(KChiptop2 *self)
{
	KChiptop2Private *priv = K_CHIPTOP2_GET_PRIVATE(self);

	priv->a = 0;
}

static void k_chiptop2_destructor(KChiptop2 *self)
{
	KChiptop2Private *priv = K_CHIPTOP2_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
KChiptop2 *k_chiptop2_new(void)
{
	KChiptop2* self = k_object_new_with_private(K_TYPE_CHIPTOP2,sizeof(KChiptop2Private));

	return self;
}
