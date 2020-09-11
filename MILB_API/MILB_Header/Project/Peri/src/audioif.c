/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-04
*@author            :陈倩
*@brief             :audioif
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*3、
*4、
*5、
*@version
*
*/


#include "audioif.h"


K_TYPE_DEFINE_WITH_PRIVATE(AudioIf, audio_if);
#define AUDIO_IF_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), AudioIfPrivate, AUDIO_TYPE_IF))


struct  _AudioIfPrivate
{

};


volatile IoAudio ioAudio __attribute__((section(".AUDIO")));
/**
 DECLS
*/
/**
 IMPL
*/
static void audio_if_constructor(AudioIf *self)
{
//	AudioIfPrivate *priv = AUDIO_IF_GET_PRIVATE(self);
}

static void audio_if_destructor(AudioIf *self)
{
//	AudioIfPrivate *priv = AUDIO_IF_GET_PRIVATE(self);
}
/**
 PUBLIC
*/
AudioIf* audio_if_new(void)
{
	AudioIf* self = k_object_new_with_private(AUDIO_TYPE_IF, sizeof(AudioIfPrivate));
	return self;
}

