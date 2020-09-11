/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition Watchdog Timer I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#include "kwdog.h"

K_TYPE_DEFINE_WITH_PRIVATE(KWdog, k_wdog);
#define K_WDOG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KWdogPrivate, K_TYPE_WDOG))

struct _KWdogPrivate
{

};

volatile IoWdog ioWdog __attribute__((section(".WDOG")));
/**
 *IMPL
 */
static void k_wdog_constructor(KWdog *self)
{
//	KWdogPrivate *priv = K_WDOG_GET_PRIVATE(self);
}

static void k_wdog_destructor(KWdog *self)
{
//	KWdogPrivate *priv = K_WDOG_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KWdog* k_wdog_new(void)
{
    KWdog* self = k_object_new_with_private(K_TYPE_WDOG, sizeof(KWdogPrivate));
    return self;
}

