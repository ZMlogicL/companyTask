/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtDdAudioThree15类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*/

#ifndef __CT_DD_AUDIO_THREE15_H_
#define __CT_DD_AUDIO_THREE15_H_

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE15					(ct_dd_audio_three15_get_type())
#define CT_DD_AUDIO_THREE15(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree15))
#define CT_DD_AUDIO_THREE15_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE15, CtDdAudioThree15Class))
#define CT_IS_DD_AUDIO_THREE15(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE15))
#define CT_IS_DD_AUDIO_THREE15_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE15))
#define CT_DD_AUDIO_THREE15_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE15, CtDdAudioThree15Class))

typedef struct 			_CtDdAudioThree15 CtDdAudioThree15;
typedef struct 			_CtDdAudioThree15Class CtDdAudioThree15Class;
typedef struct 			_CtDdAudioThree15Private CtDdAudioThree15Private;

struct _CtDdAudioThree15
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThree15Class
{
	GObjectClass parentclass;
};

GType			 				ct_dd_audio_three15_get_type(void);
CtDdAudioThree15  *ct_dd_audio_three15_new(kpointer *temp, kuint8 ch);

void 							ct_dd_audio_three15_126(CtDdAudioThree15 *self);
void 							ct_dd_audio_three15_127(CtDdAudioThree15 *self);
void 							ct_dd_audio_three15_128(CtDdAudioThree15 *self);
void 							ct_dd_audio_three15_129(CtDdAudioThree15 *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE15_H_ */
