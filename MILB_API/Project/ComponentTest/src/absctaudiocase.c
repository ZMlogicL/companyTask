/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :AbsCtAudioCase类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、AbsCtAudioCase类
*@version 1.0.0
*
*/

#include "absctaudiocase.h"

K_TYPE_DEFINE_WITH_PRIVATE(AbsCtAudioCase, abs_ct_audio_case)
#define ABS_CT_AUDIO_CASE_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), \
		AbsCtAudioCasePrivate, ABS_TYPE_CT_AUDIO_CASE))

struct _AbsCtAudioCasePrivate
{
	
};
/*
*DECLS
*/
static void abs_ct_audio_case_constructor(AbsCtAudioCase *self);
static void abs_ct_audio_case_destructor(AbsCtAudioCase *self);

/*
 * IMPL
 */
static void abs_ct_audio_case_constructor(AbsCtAudioCase *self)
{
}

static void abs_ct_audio_case_destructor(AbsCtAudioCase *self)
{
}

/*
*PUBLIC
*/
void abs_ct_audio_case_do_with_args(AbsCtAudioCase *self, kint caseValue)
{
	if(self->doWithArgs)
	{
		self->doWithArgs(self, caseValue);
	}
}

void abs_ct_audio_case_do_no_args(AbsCtAudioCase *self, kchar *str)
{
	if(self->doNoArgs)
	{
		self->doNoArgs(self, str);
	}
}

AbsCtAudioCase *abs_ct_audio_case_new(void)
{
	AbsCtAudioCase *self = k_object_new(ABS_TYPE_CT_AUDIO_CASE);
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}

