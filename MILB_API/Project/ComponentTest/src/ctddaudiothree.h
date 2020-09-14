/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :zhaoxin
*@brief               :CtDdAudioThree类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_THREE_H_
#define __CT_DD_AUDIO_THREE_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO_THREE					(ct_dd_audio_three_get_type())
#define CT_DD_AUDIO_THREE(obj)					(G_TYPE_CHECK_INSTANCE_CAST (obj, CtDdAudioThree))
#define CT_DD_AUDIO_THREE_CLASS(klass)					(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO_THREE, CtDdAudioThreeClass))
#define CT_IS_DD_AUDIO_THREE(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_DD_AUDIO_THREE))
#define CT_IS_DD_AUDIO_THREE_CLASS(klass)					(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO_THREE))
#define CT_DD_AUDIO_THREE_GET_CLASS(obj)					(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO_THREE, CtDdAudioThreeClass))

typedef struct 			_CtDdAudioThree CtDdAudioThree;
typedef struct 			_CtDdAudioThreeClass CtDdAudioThreeClass;
typedef struct 			_CtDdAudioThreePrivate CtDdAudioThreePrivate;

struct _CtDdAudioThree
{
	KObject parent;
	kuint8 ch;
};

struct _CtDdAudioThreeClass
{
	GObjectClass parentclass;
};

GType			 			ct_dd_audio_three_get_type(void);
CtDdAudioThree  *ct_dd_audio_three_new(kpointer *temp, kuint8 ch);

void 						ct_dd_audio_three_reg_rw(CtDdAudioThree *self);
void 						ct_dd_audio_three_input_open_close(CtDdAudioThree *self);
void 						ct_dd_audio_three_output_open_close(CtDdAudioThree *self);
void 						ct_dd_audio_three_init(CtDdAudioThree *self);
void 						ct_dd_audio_three_update_input_setting(CtDdAudioThree *self);
void 						ct_dd_audio_three_update_output_setting(CtDdAudioThree *self);
void 						ct_dd_audio_three_reset_input_status(CtDdAudioThree *self);
void 						ct_dd_audio_three_reset_output_status(CtDdAudioThree *self);
void 						ct_dd_audio_three_start_stop_input(CtDdAudioThree *self);
void 						ct_dd_audio_three_start_stop_output(CtDdAudioThree *self);
void 						ct_dd_audio_three_041(CtDdAudioThree *self);

G_END_DECLS

#endif /* __CT_DD_AUDIO_THREE_H_ */
