/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date               :2020-09-03
*@author           :luhongyin
*@brief              :CtDdAudio类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_DD_AUDIO_H__
#define __CT_DD_AUDIO_H__
// #include <glib-object.h>
#include "./../../../../fj/glib/src/gobject.h"
G_BEGIN_DECLS

#define CT_TYPE_DD_AUDIO			   			(ct_dd_audio_get_type ())
#define CT_DD_AUDIO(widget)		   			(G_TYPE_CHECK_INSTANCE_CAST ((widget), CT_TYPE_DD_AUDIO, CtDdAudio))
#define CT_DD_AUDIO_CLASS(klass)	  		(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_DD_AUDIO, CtDdAudioClass))
#define CT_IS_DD_AUDIO(widget)	   			(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_DD_AUDIO))
#define CT_IS_DD_AUDIO_CLASS(klass)  	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_DD_AUDIO))
#define CT_DD_AUDIO_GET_CLASS(obj)   	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_DD_AUDIO, CtDdAudioClass))
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define CtDdAudio_CT_DD_Audio_WORK_AREA		(0x7C000000)
#define CtDdAudio_CT_DD_Audio_WORK_AREA2	(0x7D000000)

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/

#define CtDdAudio_CT_DD_AUDIO_ASSERT(_a) \
    {\
        if (! _a) {\
            DriverCommon_DDIM_PRINT(("%d: CtDdAudio_CT_DD_AUDIO_ASSERT: TestCaseError(0x%08x)\n", \
            __LINE__, _a));\
            ct_dd_audio_do_test_ng_countup(NULL);\
        } else {\
            ct_dd_audio_do_test_ok_countup(NULL);\
        }\
    }

#define CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS(_a, _b) \
    {\
        if (_a != _b) {\
            DriverCommon_DDIM_PRINT(("%d: CtDdAudio_CT_DD_AUDIO_ASSERT_EQUALS: TestCaseError(0x%08x, 0x%08x)\n", \
            __LINE__, _a, _b));\
            ct_dd_audio_do_test_ng_countup(NULL);\
        } else {\
            ct_dd_audio_do_test_ok_countup(NULL);\
        }\
    }

#define CtDdAudio_CT_DD_AUDIO_TEST_ASSERT_NOT_EQUALS(_a, _b) \
    {\
        if (_a == _b) {\
            DriverCommon_DDIM_PRINT(("%d: CtDdAudio_CT_DD_AUDIO_TEST_ASSERT_NOT_EQUALS: TestCaseError(0x%08x, 0x%08x)\n", \
            __LINE__, _a, _b));\
            ct_dd_audio_do_test_ng_countup(NULL);\
        } else {\
            ct_dd_audio_do_test_ok_countup(NULL);\
        }\
    }


typedef struct _CtDdAudio         		CtDdAudio;
typedef struct _CtDdAudioClass    	CtDdAudioClass;
typedef struct _CtDdAudioPrivate  	CtDdAudioPrivate;

struct _CtDdAudio
{
	GObject parent;
	guint8 ch;
};

struct _CtDdAudioClass
{
	GObjectClass parentclass;
};

GType           			ct_dd_audio_get_type (void);
CtDdAudio 			  *ct_dd_audio_new(gpointer *temp, guint8 ch);

void 						ct_dd_audio_test_init(CtDdAudio *self);
void 						ct_dd_audio_test_fin(CtDdAudio *self, const kchar* testName);
void 						ct_dd_audio_do_test_ng_countup(CtDdAudio *self);
void 						ct_dd_audio_do_test_ok_countup(CtDdAudio *self);
void 						ct_dd_audio_reg_init(CtDdAudio *self);
void 						ct_dd_audio_set_gpio( CtDdAudio *self );
void 						ct_dd_audio_input_open_test1( CtDdAudio *self );
void 						ct_dd_audio_input_open_test2( CtDdAudio *self );
void 						ct_dd_audio_input_open_test3( CtDdAudio *self );
void 						ct_dd_audio_input_open_test4( CtDdAudio *self );
void 						ct_dd_audio_input_open_test5( CtDdAudio *self );
void 						ct_dd_audio_output_open_test1( CtDdAudio *self );
void 						ct_dd_audio_output_open_test2( CtDdAudio *self );
void 						ct_dd_audio_output_open_test3( CtDdAudio *self );
void 						ct_dd_audio_output_open_test4( CtDdAudio *self );
void 						ct_dd_audio_output_open_test5( CtDdAudio *self );
void 						ct_dd_audio_input_close_test( CtDdAudio *self );
void 						ct_dd_audio_output_close_test( CtDdAudio *self );
void 						ct_dd_audio_init_test( CtDdAudio *self );
void 						ct_dd_audio_reset_test( CtDdAudio *self );

G_END_DECLS
#endif /* __CT_DD_AUDIO_H_ */
