/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree6类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE6_H_
#define __CT_DD_AUDIO_THREE6_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE6					(ct_dd_audio_three6_get_type())
#define CT_DD_AUDIO_THREE6(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree6))
#define CT_DD_AUDIO_THREE6_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE6, CtDdAudioThree6Class))
#define CT_IS_DD_AUDIO_THREE6(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE6))
#define CT_IS_DD_AUDIO_THREE6_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE6))
#define CT_DD_AUDIO_THREE6_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE6, CtDdAudioThree6Class))

typedef struct 			_CtDdAudioThree6 CtDdAudioThree6;
typedef struct 			_CtDdAudioThree6Class CtDdAudioThree6Class;
typedef struct 			_CtDdAudioThree6Private CtDdAudioThree6Private;

struct _CtDdAudioThree6
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree6Class
{
	GObjectClass parentclass;
};

GType			 					ct_dd_audio_three6_get_type(void);
CtDdAudioThree6		  *ct_dd_audio_three6_new(kpointer *temp, kuint8 ch);

void 								ct_dd_audio_three6_074(CtDdAudioThree6 *self);
void 								ct_dd_audio_three6_075(CtDdAudioThree6 *self);
void 								ct_dd_audio_three6_076(CtDdAudioThree6 *self);
void 								ct_dd_audio_3_077(CtDdAudioThree6 *self);
void 								ct_dd_audio_three6_078(CtDdAudioThree6 *self);
void 								ct_dd_audio_three6_079(CtDdAudioThree6 *self);
void								ct_dd_audio_three6_080(CtDdAudioThree6 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE6_H_ */
