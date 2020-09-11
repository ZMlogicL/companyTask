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


#include "kchiptop1.h"


K_TYPE_DEFINE_WITH_PRIVATE(KChiptop1, k_chiptop1);
#define K_CHIPTOP1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KChiptop1Private, K_TYPE_CHIPTOP1))


struct _KChiptop1Private
{
	kint a;
};
/*
 * IMPL
 */
static void k_chiptop1_constructor(KChiptop1 *self)
{
	KChiptop1Private *priv = K_CHIPTOP1_GET_PRIVATE(self);

	priv->a = 0;
}

static void k_chiptop1_destructor(KChiptop1 *self)
{
	KChiptop1Private *priv = K_CHIPTOP1_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
KChiptop1 *k_chiptop1_new(void)
{
	KChiptop1* self = k_object_new_with_private(K_TYPE_CHIPTOP1,sizeof(KChiptop1Private));

	return self;
}
