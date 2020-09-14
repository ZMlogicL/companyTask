/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :AbsCtAudioCase类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、AbsCtAudioCase类
*@version 1.0.0
*
*/


#include "absctaudiocase.h"

G_DEFINE_TYPE(AbsCtAudioCase, abs_ct_audio_case, G_TYPE_OBJECT);
#define ABS_CT_AUDIO_CASE_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),ABS_TYPE_CT_AUDIO_CASE, AbsCtAudioCasePrivate))

struct _AbsCtAudioCasePrivate
{
};
/*
*DECLS
*/
static void abs_ct_audio_case_class_init(AbsCtAudioCaseClass *klass);
static void abs_ct_audio_case_init(AbsCtAudioCase *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
/*
 * IMPL
 */
static void abs_ct_audio_case_class_init(AbsCtAudioCaseClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(AbsCtAudioCasePrivate));
}

static void abs_ct_audio_case_init(AbsCtAudioCase *self)
{
}

static void dispose_od(GObject *object)
{
	AbsCtAudioCase *self = (AbsCtAudioCase*)object;
}

static void finalize_od(GObject *object)
{
	AbsCtAudioCase *self = (AbsCtAudioCase*)object;
}

/*
*PUBLIC
*/
void abs_ct_audio_case_do_with_args(AbsCtAudioCase *self, gint caseValue)
{
	if(self->doWithArgs)
	{
		self->doWithArgs(self, caseValue);
	}
}

void abs_ct_audio_case_do_no_args(AbsCtAudioCase *self, gchar *str)
{
	if(self->doNoArgs)
	{
		self->doNoArgs(self, str);
	}
}

AbsCtAudioCase *abs_ct_audio_case_new(void)
{
	AbsCtAudioCase *self = g_object_new(ABS_TYPE_CT_AUDIO_CASE, NULL);
	if (!self)
	{
		return NULL;
	}
	return self;
}

