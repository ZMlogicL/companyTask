/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :luhongyin
*@brief               :CtAudioCaseFactory类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseFactory类
*@version 1.0.0
*
*/
// #include "ctaudiocase.h"
#include <string.h>
#include <stdlib.h>
#include "audio_if.h"
#include "dd_audio.h"
#include "dd_hdmac0.h"
#include "dd_top.h"
#include "dd_cache.h"
#include "dd_pdm.h"
#include "dd_gic.h"
#include "peripheral.h"

#include "ctaudiocaseone.h"
#include "ctaudiocasetwo.h"
#include "ctaudiocasethree.h"
#include "ctaudiocasefour.h"
#include "ctaudiocasefive.h"
#include "ctaudiocasesix.h"
#include "ctaudiocaseseven.h"
#include "ctaudiocaseeight.h"
#include "ctaudiocasenine.h"
#include "ctaudiocaseten.h"
#include "ctaudiocaseeleven.h"
#include "ctaudiocasetwelve.h"

#include "ctaudiocasefactory.h"

G_DEFINE_TYPE(CtAudioCaseFactory, ct_audio_case_factory, G_TYPE_OBJECT);
#define 	CT_AUDIO_CASE_FACTORY_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_AUDIO_CASE_FACTORY, CtAudioCaseFactoryPrivate))

struct _CtAudioCaseFactoryPrivate
{
	
};
/*
*DECLS
*/
static void ct_audio_case_factory_class_init(CtAudioCaseFactoryClass *klass);
static void ct_audio_case_factory_init(CtAudioCaseFactory *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
/*
 * IMPL
 */
static void ct_audio_case_factory_class_init(CtAudioCaseFactoryClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtAudioCaseFactoryPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_audio_case_factory_init(CtAudioCaseFactory *self)
{
	// CtAudioCaseFactory *self = CT_AUDIO_CASE_FACTORY(object);
    // CtAudioCaseFactoryPrivate *priv = CT_AUDIO_CASE_FACTORY_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_factory_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_factory_parent_class)->finalize(object);
}
/*
*PUBLIC
*/

AbsCtAudioCase* ct_audio_case_factory_create_case(CtAudioCaseFactory *self, AbsCtAudioCaseType type)
{
	AbsCtAudioCase *ret = NULL;
	switch(type)
	{
		case AbsCtAudioCase_EQUAL_ONE:
			ret = (AbsCtAudioCase*)ct_audio_case_one_new();
			break;
		case AbsCtAudioCase_EQUAL_TWO:
			ret = (AbsCtAudioCase*)ct_audio_case_two_new();
			break;
		case AbsCtAudioCase_EQUAL_THREE:
			ret = (AbsCtAudioCase*)ct_audio_case_three_new();
			break;
		case AbsCtAudioCase_EQUAL_FOUR:
			ret = (AbsCtAudioCase*)ct_audio_case_four_new();
			break;
		case AbsCtAudioCase_EQUAL_FIVE:
			ret = (AbsCtAudioCase*)ct_audio_case_five_new();
			break;
		case AbsCtAudioCase_EQUAL_SIX:
			ret = (AbsCtAudioCase*)ct_audio_case_six_new();
			break;
		case AbsCtAudioCase_EQUAL_SEVEN:
			ret = (AbsCtAudioCase*)ct_audio_case_seven_new();
			break;
		case AbsCtAudioCase_EQUAL_EIGHT:
			ret = (AbsCtAudioCase*)ct_audio_case_eight_new();
			break;
		case AbsCtAudioCase_EQUAL_NINE:
			ret = (AbsCtAudioCase*)ct_audio_case_nine_new();
			break;
		case AbsCtAudioCase_EQUAL_TEN:
			ret = (AbsCtAudioCase*)ct_audio_case_ten_new();
			break;
		case AbsCtAudioCase_EQUAL_ELEVEN:
			ret = (AbsCtAudioCase*)ct_audio_case_eleven_new();
			break;
		case AbsCtAudioCase_EQUAL_TWELVE:
			ret = (AbsCtAudioCase*)ct_audio_case_twelve_new();
			break;
		default: 
			DriverCommon_DDIM_PRINT(("ddaudio : ERROR command line\n"));
			break;
	}
	return ret;
}

CtAudioCaseFactory *ct_audio_case_factory_new(void)
{
	static CtAudioCaseFactory *self = NULL;
	if (!self) {
		self = CT_AUDIO_CASE_FACTORY(g_object_new(CT_TYPE_AUDIO_CASE_FACTORY, NULL));
	}
	return self;
}

