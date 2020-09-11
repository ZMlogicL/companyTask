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

#ifndef __ABS_CT_AUDIO_CASE_H__
#define __ABS_CT_AUDIO_CASE_H__
#include <string.h>
#include <stdlib.h>
#include <klib.h>
#include "audio_if.h"
#include "dd_audio.h"
#include "dd_hdmac0.h"
#include "dd_top.h"
#include "dd_cache.h"
#include "dd_pdm.h"
#include "dd_gic.h"
#include "peripheral.h"
#include "ctddaudio.h"
#include "ctddaudioint.h"
#include "ctddaudioctrl.h"
#include "ctddaudioctrl1.h"
#include "ctddaudioctrl2.h"
#include "ctddaudioctrl3.h"
#include "ctddaudioctrl4.h"
#include "ctddaudioctrl5.h"
#include "ctddaudioctrl6.h"
#include "ctddaudioctrl7.h"
#include "ctddaudioctrl8.h"
#include "ctddaudioctrl9.h"
#include "ctddaudioctrl10.h"
#include "ctddaudioget.h"
#include "ctddaudiostart.h"
#include "ctddaudiostop.h"
#include "ctddaudioset.h"
#include "ctddaudioset1.h"
#include "ctddaudioset2.h"
#include "ctddaudioset3.h"
#include "ctddaudiothree.h"
#include "ctddaudiothree1.h"
#include "ctddaudiothree2.h"
#include "ctddaudiothree3.h"
#include "ctddaudiothree4.h"
#include "ctddaudiothree5.h"
#include "ctddaudiothree6.h"
#include "ctddaudiothree7.h"
#include "ctddaudiothree8.h"
#include "ctddaudiothree9.h"
#include "ctddaudiothree10.h"
#include "ctddaudiothree11.h"
#include "ctddaudiothree12.h"
#include "ctddaudiothree13.h"
#include "ctddaudiothree14.h"
#include "ctddaudiothree15.h"
#include "ctddaudiothree16.h"
#include "ctddaudiofifo.h"
#include "ctddaudiofifo1.h"
#include "ctddaudiofifo2.h"
#include "ctddaudiofifo3.h"

#define ABS_TYPE_CT_AUDIO_CASE   (abs_ct_audio_case_get_type())
#define ABS_IS_CT_AUDIO_CASE(obj)    K_TYPE_CHECK_INSTANCE_TYPE(obj, AbsCtAudioCase)
#define ABS_CT_AUDIO_CASE(obj)     (K_TYPE_CHECK_INSTANCE_CAST(obj, AbsCtAudioCase))

typedef enum
{
	AbsCtAudioCase_EQUAL_DEFAULT,
	AbsCtAudioCase_EQUAL_ONE,
	AbsCtAudioCase_EQUAL_TWO,
	AbsCtAudioCase_EQUAL_THREE,
	AbsCtAudioCase_EQUAL_FOUR,
	AbsCtAudioCase_EQUAL_FIVE,
	AbsCtAudioCase_EQUAL_SIX,
	AbsCtAudioCase_EQUAL_SEVEN,
	AbsCtAudioCase_EQUAL_EIGHT,
	AbsCtAudioCase_EQUAL_NINE,
	AbsCtAudioCase_EQUAL_TEN,
	AbsCtAudioCase_EQUAL_ELEVEN,
	AbsCtAudioCase_EQUAL_TWELVE

}AbsCtAudioCaseType;


typedef struct 				_AbsCtAudioCase AbsCtAudioCase;
typedef struct 				_AbsCtAudioCasePrivate AbsCtAudioCasePrivate;

struct _AbsCtAudioCase
{
	KObject parent;
	void (*doWithArgs)(AbsCtAudioCase *self, kint caseValue);
	void (*doNoArgs)(AbsCtAudioCase *self, kchar *str);
};


KConstType		            	abs_ct_audio_case_get_type(void);
AbsCtAudioCase           *abs_ct_audio_case_new(void);

void 								abs_ct_audio_case_do_with_args(AbsCtAudioCase *self, kint caseValue);
void 								abs_ct_audio_case_do_no_args(AbsCtAudioCase *self, kchar *str);

#endif /* __K_CT_AUDIO_CASE_H__ */

