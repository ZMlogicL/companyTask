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


#include "kchiptop3.h"


K_TYPE_DEFINE_WITH_PRIVATE(KChiptop3, k_chiptop3);
#define K_CHIPTOP3_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KChiptop3Private, K_TYPE_CHIPTOP3))


struct _KChiptop3Private
{
	kint a;
};


volatile IoChiptop	ioChiptop	__attribute__((section(".CHIPTOP")));
/*
 * IMPL
 */
static void k_chiptop3_constructor(KChiptop3 *self)
{
	KChiptop3Private *priv = K_CHIPTOP3_GET_PRIVATE(self);

	priv->a = 0;
}

static void k_chiptop3_destructor(KChiptop3 *self)
{
	KChiptop3Private *priv = K_CHIPTOP3_GET_PRIVATE(self);

	priv->a = 0;
}
/**
 * PUBLIC
 */
KChiptop3 *k_chiptop3_new(void)
{
	KChiptop3* self = k_object_new_with_private(K_TYPE_CHIPTOP3,sizeof(KChiptop3Private));

	return self;
}
