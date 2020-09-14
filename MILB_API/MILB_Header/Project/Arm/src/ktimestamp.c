/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :Definition Timestamp Generator I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#include "ktimestamp.h"


K_TYPE_DEFINE_WITH_PRIVATE(KTimestamp, k_timestamp);

#define K_TIMESTAMP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), KTimestampPrivate, K_TYPE_TIMESTAMP))


struct _KTimestampPrivate
{

};


volatile IoTimestamp ioTimestamp __attribute__((section(".TIMESTAMP")));
/**
 *IMPL
 */
static void k_timestamp_constructor(KTimestamp *self)
{
//	KTimestampPrivate *priv = K_TIMESTAMP_GET_PRIVATE(self);
}

static void k_timestamp_destructor(KTimestamp *self)
{
//	KTimestampPrivate *priv = K_TIMESTAMP_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
KTimestamp* k_timestamp_new(void)
{
    KTimestamp* self = k_object_new_with_private(K_TYPE_TIMESTAMP, sizeof(KTimestampPrivate));
    return self;
}
