/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseTwelve类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、CtAudioCaseTwelve类
*@version 1.0.0
*/

#include "ctaudiocasetwelve.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtAudioCaseTwelve, ct_audio_case_twelve)
#define CT_AUDIO_CASE_TWELVE_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), \
		CtAudioCaseTwelvePrivate, CT_TYPE_AUDIO_CASE_TWELVE))

#define CtAudioCaseTwelve_CtDdAudio_CT_DD_Audio_WORK_AREA	(0x7C000000)

struct _CtAudioCaseTwelvePrivate
{
	
};
/*
*DECLS
*/
static void ct_audio_case_twelve_constructor(CtAudioCaseTwelve *self);
static void ct_audio_case_twelve_destructor(CtAudioCaseTwelve *self);
static void doWithArgs_od(AbsCtAudioCase* self, kint caseValue);
static void doNoArgs_od(AbsCtAudioCase* self, kchar* str);

/*
 * IMPL
 */
static void ct_audio_case_twelve_constructor(CtAudioCaseTwelve *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = doNoArgs_od;
}

static void ct_audio_case_twelve_destructor(CtAudioCaseTwelve *self)
{
	self = NULL;
}

<<<<<<< .mine
static void doWithArgs_od(AbsCtAudioCase* self, kint caseValue)
=======
static void doWithArgs_od(AbsCtAudioCase *self, int caseValue)
>>>>>>> .r6812
{
	kpointer temp = NULL;
	switch(caseValue)
	{
		case 0:
			ct_dd_audio_three_reg_rw(ct_dd_audio_three_new(temp, 0));
			break;
		case 1:
			ct_dd_audio_three_input_open_close(ct_dd_audio_three_new(temp, 0));
			break;
		case 2:
			ct_dd_audio_three_input_open_close(ct_dd_audio_three_new(temp, 1));
			break;
		case 3:
			ct_dd_audio_three_input_open_close(ct_dd_audio_three_new(temp, 2));
			break;
		case 4:
			ct_dd_audio_three_input_open_close(ct_dd_audio_three_new(temp, 4));
			break;
		case 5:
			ct_dd_audio_three_input_open_close(ct_dd_audio_three_new(temp, 5));
			break;
		case 6:
			ct_dd_audio_three_output_open_close(ct_dd_audio_three_new(temp, 0));
			break;
		case 7:
			ct_dd_audio_three_output_open_close(ct_dd_audio_three_new(temp, 1));
			break;
		case 8:
			ct_dd_audio_three_output_open_close(ct_dd_audio_three_new(temp, 2));
			break;
		case 9:
			ct_dd_audio_three_output_open_close(ct_dd_audio_three_new(temp, 3));
			break;
		case 10:
			ct_dd_audio_three_init(ct_dd_audio_three_new(temp, 0));
			break;
		case 11:
			ct_dd_audio_three_init(ct_dd_audio_three_new(temp, 1));
			break;
		case 12:
			ct_dd_audio_three_init(ct_dd_audio_three_new(temp, 2));
			break;
		case 13:
			ct_dd_audio_three_init(ct_dd_audio_three_new(temp, 3));
			break;
		case 14:
			ct_dd_audio_three_init(ct_dd_audio_three_new(temp, 4));
			break;
		case 15:
			ct_dd_audio_three_init(ct_dd_audio_three_new(temp, 5));
			break;
		case 16:
			ct_dd_audio_three_update_input_setting(ct_dd_audio_three_new(temp, 0));
			break;
		case 17:
			ct_dd_audio_three_update_input_setting(ct_dd_audio_three_new(temp, 1));
			break;
		case 18:
			ct_dd_audio_three_update_input_setting(ct_dd_audio_three_new(temp, 2));
			break;
		case 19:
			ct_dd_audio_three_update_input_setting(ct_dd_audio_three_new(temp, 4));
			break;
		case 20:
			ct_dd_audio_three_update_input_setting(ct_dd_audio_three_new(temp, 5));
			break;
		case 21:
			ct_dd_audio_three_update_output_setting(ct_dd_audio_three_new(temp, 0));
			break;
		case 22:
			ct_dd_audio_three_update_output_setting(ct_dd_audio_three_new(temp, 1));
			break;
		case 23:
			ct_dd_audio_three_update_output_setting(ct_dd_audio_three_new(temp, 2));
			break;
		case 24:
			ct_dd_audio_three_update_output_setting(ct_dd_audio_three_new(temp, 3));
			break;
		case 25:
			ct_dd_audio_three_reset_input_status(ct_dd_audio_three_new(temp, 0));
			break;
		case 26:
			ct_dd_audio_three_reset_input_status(ct_dd_audio_three_new(temp, 1));
			break;
		case 27:
			ct_dd_audio_three_reset_input_status(ct_dd_audio_three_new(temp, 2));
			break;
		case 28:
			ct_dd_audio_three_reset_input_status(ct_dd_audio_three_new(temp, 4));
			break;
		case 29:
			ct_dd_audio_three_reset_input_status(ct_dd_audio_three_new(temp, 3));
			break;
		case 30:
			ct_dd_audio_three_reset_output_status(ct_dd_audio_three_new(temp, 0));
			break;
		case 31:
			ct_dd_audio_three_reset_output_status(ct_dd_audio_three_new(temp, 1));
			break;
		case 32:
			ct_dd_audio_three_reset_output_status(ct_dd_audio_three_new(temp, 2));
			break;
		case 33:
			ct_dd_audio_three_reset_output_status(ct_dd_audio_three_new(temp, 3));
			break;
		case 34:
			ct_dd_audio_three_start_stop_input(ct_dd_audio_three_new(temp, 0));
			break;
		case 35:
			ct_dd_audio_three_start_stop_input(ct_dd_audio_three_new(temp, 2));
			break;
		case 36:
			ct_dd_audio_three_start_stop_input(ct_dd_audio_three_new(temp, 4));
			break;
		case 37:
			ct_dd_audio_three_start_stop_input(ct_dd_audio_three_new(temp, 5));
			break;
		case 38:
			ct_dd_audio_three_start_stop_output(ct_dd_audio_three_new(temp, 0));
			break;
		case 39:
			ct_dd_audio_three_start_stop_output(ct_dd_audio_three_new(temp, 2));
			break;
		case 40:
			ct_dd_audio_three_start_stop_output(ct_dd_audio_three_new(temp, 3));
			break;
		case 41:
			ct_dd_audio_three_041(ct_dd_audio_three_new(temp, 0));
			break;
		case 42:
			ct_dd_audio_three1_042(ct_dd_audio_three1_new(temp,0));
			break;
		case 43:
			ct_dd_audio_three1_043(ct_dd_audio_three1_new(temp,0));
			break;
		case 44:
			ct_dd_audio_three1_044(ct_dd_audio_three1_new(temp,0));
			break;
		case 45:
			ct_dd_audio_three1_045(ct_dd_audio_three1_new(temp,0));
			break;
		case 46:
			ct_dd_audio_three1_046(ct_dd_audio_three1_new(temp,0));
			break;
		case 47:
			ct_dd_audio_three1_047(ct_dd_audio_three1_new(temp,0));
			break;
		case 48:
			ct_dd_audio_three2_048(ct_dd_audio_three2_new(temp, 0));
			break;
		case 49:
			ct_dd_audio_three2_049(ct_dd_audio_three2_new(temp, 0));
			break;
		case 50:
			ct_dd_audio_three2_050(ct_dd_audio_three2_new(temp, 0));
			break;
		case 51:
			ct_dd_audio_three2_051(ct_dd_audio_three2_new(temp, 0));
			break;
		case 52:
			ct_dd_audio_three2_052(ct_dd_audio_three2_new(temp, 0));
			break;
		case 53:
			ct_dd_audio_three3_053(ct_dd_audio_three3_new(temp,0));
			break;
		case 54:
			ct_dd_audio_three3_054(ct_dd_audio_three3_new(temp,0));
			break;
		case 55:
			ct_dd_audio_three3_055(ct_dd_audio_three3_new(temp,0));
			break;
		case 56:
			ct_dd_audio_three3_056(ct_dd_audio_three3_new(temp,0));
			break;
		case 57:
			ct_dd_audio_trhee3_057(ct_dd_audio_three3_new(temp,0));
			break;
		case 58:
			ct_dd_audio_three3_058(ct_dd_audio_three3_new(temp,0));
			break;
		case 59:
			ct_dd_audio_three3_059(ct_dd_audio_three3_new(temp,0));
			break;
		case 60:
			ct_dd_audio_three4_060(ct_dd_audio_three4_new(temp, 0));
			break;
		case 61:
			ct_dd_audio_three4_061(ct_dd_audio_three4_new(temp, 0));
			break;
		case 62:
			ct_dd_audio_three4_062(ct_dd_audio_three4_new(temp, 0));
			break;
		case 63:
			ct_dd_audio_three4_063(ct_dd_audio_three4_new(temp, 0));
			break;
		case 64:
			ct_dd_audio_three4_064(ct_dd_audio_three4_new(temp, 0));
			break;
		case 65:
			ct_dd_audio_three4_065(ct_dd_audio_three4_new(temp, 0));
			break;
		case 66:
			ct_dd_audio_three4_066(ct_dd_audio_three4_new(temp, 0));
			break;
		case 67:
			ct_dd_audio_three5_067(ct_dd_audio_three5_new(temp, 0));
			break;
		case 68:
			ct_dd_audio_three5_068(ct_dd_audio_three5_new(temp, 0));
			break;
		case 69:
			ct_dd_audio_three5_069(ct_dd_audio_three5_new(temp, 0));
			break;
		case 70:
			ct_dd_audio_three5_070(ct_dd_audio_three5_new(temp, 0));
			break;
		case 71:
			ct_dd_audio_three5_071(ct_dd_audio_three5_new(temp, 0));
			break;
		case 72:
			ct_dd_audio_three5_072(ct_dd_audio_three5_new(temp, 0));
			break;
		case 73:
			ct_dd_audio_three5_073(ct_dd_audio_three5_new(temp, 0));
			break;
		case 74:
			ct_dd_audio_three6_074(ct_dd_audio_three6_new(temp, 0));
			break;
		case 75:
			ct_dd_audio_three6_075(ct_dd_audio_three6_new(temp, 0));
			break;
		case 76:
			ct_dd_audio_three6_076(ct_dd_audio_three6_new(temp, 0));
			break;
		case 77:
			ct_dd_audio_3_077(ct_dd_audio_three6_new(temp, 0));
			break;
		case 78:
			ct_dd_audio_three6_078(ct_dd_audio_three6_new(temp, 0));
			break;
		case 79:
			ct_dd_audio_three6_079(ct_dd_audio_three6_new(temp, 0));
			break;
		case 80:
			ct_dd_audio_three6_080(ct_dd_audio_three6_new(temp, 0));
			break;
		case 81:
			ct_dd_audio_three7_081(ct_dd_audio_three7_new(temp, 0));
			break;
		case 82:
			ct_dd_audio_three7_082(ct_dd_audio_three7_new(temp, 0));
			break;
		case 83:
			ct_dd_audio_three7_083(ct_dd_audio_three7_new(temp, 0));
			break;
		case 84:
			ct_dd_audio_three7_084(ct_dd_audio_three7_new(temp, 0));
			break;
		case 85:
			ct_dd_audio_three7_085(ct_dd_audio_three7_new(temp, 0));
			break;
		case 86:
			ct_dd_audio_three7_086(ct_dd_audio_three7_new(temp, 0));
			break;
		case 87:
			ct_dd_audio_three7_087(ct_dd_audio_three7_new(temp, 0));
			break;
		case 88:
			ct_dd_audio_three8_088(ct_dd_audio_three8_new(temp, 0));
			break;
		case 89:
			ct_dd_audio_three8_089(ct_dd_audio_three8_new(temp, 4));
			break;
		case 90:
			ct_dd_audio_three8_090(ct_dd_audio_three8_new(temp, 0));
			break;
		case 91:
			ct_dd_audio_three8_091(ct_dd_audio_three8_new(temp, 0));
			break;
		case 92:
			ct_dd_audio_three8_092(ct_dd_audio_three8_new(temp, 0));
			break;
		case 93:
			ct_dd_audio_three8_093(ct_dd_audio_three8_new(temp, 0));
			break;
		case 94:
			ct_dd_audio_three9_094(ct_dd_audio_three9_new(temp, 0));
			break;
		case 95:
			ct_dd_audio_three9_095(ct_dd_audio_three9_new(temp, 0));
			break;
		case 96:
			ct_dd_audio_three9_096(ct_dd_audio_three9_new(temp, 0));
			break;
		case 97:
			ct_dd_audio_three9_097(ct_dd_audio_three9_new(temp, 0));
			break;
		case 98:
			ct_dd_audio_three9_098(ct_dd_audio_three9_new(temp, 0));
			break;
		case 99:
			ct_dd_audio_three10_099(ct_dd_audio_three10_new(temp, 0));
			break;
		case 100:
			ct_dd_audio_three10_100(ct_dd_audio_three10_new(temp, 0));
			break;
		case 101:
			ct_dd_audio_three10_101(ct_dd_audio_three10_new(temp, 0));
			break;
		case 102:
			ct_dd_audio_three10_102(ct_dd_audio_three10_new(temp, 0));
			break;
		case 103:
			ct_dd_audio_three10_103(ct_dd_audio_three10_new(temp, 0));
			break;
		case 104:
			ct_dd_audio_three11_104(ct_dd_audio_three11_new(temp, 0));
			break;
		case 105:
			ct_dd_audio_three11_105(ct_dd_audio_three11_new(temp, 0));
			break;
		case 106:
			ct_dd_audio_three11_106(ct_dd_audio_three11_new(temp, 0));
			break;
		case 107:
			ct_dd_audio_three11_107(ct_dd_audio_three11_new(temp, 0));
			break;
		case 108:
			ct_dd_audio_three11_108(ct_dd_audio_three11_new(temp, 0));
			break;
		case 109:
			ct_dd_audio_three12_109(ct_dd_audio_three12_new(temp, 0));
			break;
		case 110:
			ct_dd_audio_three12_110(ct_dd_audio_three12_new(temp, 0));
			break;
		case 111:
			ct_dd_audio_three12_111(ct_dd_audio_three12_new(temp, 0));
			break;
		case 112:
			ct_dd_audio_three12_112(ct_dd_audio_three12_new(temp, 0));
			break;
		case 113:
			ct_dd_audio_three13_113(ct_dd_audio_three13_new(temp, 0));
			break;
		case 114:
			ct_dd_audio_three13_114(ct_dd_audio_three13_new(temp, 0));
			break;
		case 115:
			ct_dd_audio_three13_115(ct_dd_audio_three13_new(temp, 0));
			break;
		case 116:
			ct_dd_audio_three13_116(ct_dd_audio_three13_new(temp, 0));
			break;
		case 117:
			ct_dd_audio_three13_117(ct_dd_audio_three13_new(temp, 0));
			break;
		case 118:
			ct_dd_audio_three13_118(ct_dd_audio_three13_new(temp, 0));
			break;
		case 119:
			ct_dd_audio_three13_119(ct_dd_audio_three13_new(temp, 0));
			break;
		case 120:
			ct_dd_audio_three13_120(ct_dd_audio_three13_new(temp, 0));
			break;
		case 121:
			ct_dd_audio_three14_121(ct_dd_audio_three14_new(temp, 0));
			break;
		case 122:
			ct_dd_audio_three14_122(ct_dd_audio_three14_new(temp, 0));
			break;
		case 123:
			ct_dd_audio_three14_123(ct_dd_audio_three14_new(temp, 0));
			break;
		case 124:
			ct_dd_audio_three14_124(ct_dd_audio_three14_new(temp, 0));
			break;
		case 125:
			ct_dd_audio_three14_125(ct_dd_audio_three14_new(temp, 0));
			break;
		case 126:
			ct_dd_audio_three15_126(ct_dd_audio_three15_new(temp, 0));
			break;
		case 127:
			ct_dd_audio_three15_127(ct_dd_audio_three15_new(temp, 0));
			break;
		case 128:
			ct_dd_audio_three15_128(ct_dd_audio_three15_new(temp, 0));
			break;
		case 129:
			ct_dd_audio_three15_129(ct_dd_audio_three15_new(temp, 0));
			break;
		case 130:
			ct_dd_audio_3_130(ct_dd_audio_three16_new(temp, 5));
			break;
		case 131:
			ct_dd_audio_3_131(ct_dd_audio_three16_new(temp, 0));
			break;
		default :
			Ddim_Print(("ddaudio : ERROR command line\n"));
			break;
	}
	if(temp)
	{
		k_object_unref(temp);
		temp = NULL;
	}
}

static void doNoArgs_od(AbsCtAudioCase *self, kchar* str)
{
	kpointer temp = NULL;
	if( !strcmp(str, "hdmi") ) {
		ct_dd_audio_3_hdmi(ct_dd_audio_three16_new(temp, 3));
	}
	else if( !strcmp(str, "rec_monitor0_n") ) {
		ct_dd_audio_fifo_monitor_rec0_n(ct_dd_audio_fifo_new(temp, 0));
	}
	else if( !strcmp(str, "rec_monitor0") ) {
		ct_dd_audio_fifo_monitor_rec0(ct_dd_audio_fifo_new(temp, 0));
	}
	else if( !strcmp(str, "rec_monitor0_s") ) {
		ct_dd_audio_fifo_monitor_rec0_slave(ct_dd_audio_fifo_new(temp, 0));
	}
	else if( !strcmp(str, "rec_monitor1") ) {
		ct_dd_audio_fifo_monitor_rec1(ct_dd_audio_fifo_new(temp, 0));
	}
	else if( !strcmp(str, "rec_monitor1_s") ) {
		ct_dd_audio_fifo_monitor_rec1_slave(ct_dd_audio_fifo_new(temp, 0));
	}
	else if( !strcmp(str, "rec_monitor2_n") ) {
		ct_dd_audio_fifo_monitor_rec2_n(ct_dd_audio_fifo_new(temp, 0));
	}
	else if( !strcmp(str, "rec_monitor2") ) {
		ct_dd_audio_fifo_monitor_rec2(ct_dd_audio_fifo_new(temp, 0));
	}
	else if( !strcmp(str, "rec_monitor2_s") ) {
		ct_dd_audio_fifo1_monitor_rec2_slave(ct_dd_audio_fifo1_new(temp, 0));
	}
	else if( !strcmp(str, "rec_monitor3_n") ) {
		ct_dd_audio_fifo1_monitor_rec3_n(ct_dd_audio_fifo1_new(temp, 0));
	}
	else if( !strcmp(str, "rec_monitor3") ) {
		ct_dd_audio_fifo1_monitor_rec3(ct_dd_audio_fifo1_new(temp, 0));
	}
	else if( !strcmp(str, "rec_monitor3_s") ) {
		ct_dd_audio_fifo1_monitor_rec3_slave(ct_dd_audio_fifo1_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor0_n") ) {
		ct_dd_audio_fifo1_monitor_play0_n(ct_dd_audio_fifo1_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor0") ) {
		ct_dd_audio_fifo1_monitor_play0(ct_dd_audio_fifo1_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor0_s") ) {
		ct_dd_audio_fifo1_monitor_play0_slave(ct_dd_audio_fifo1_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor1") ) {
		ct_dd_audio_fifo2_monitor_play1(ct_dd_audio_fifo2_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor1_s") ) {
		ct_dd_audio_fifo2_monitor_play1_slave(ct_dd_audio_fifo2_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor2_n") ) {
		ct_dd_audio_fifo2_monitor_play2_n(ct_dd_audio_fifo2_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor2") ) {
		ct_dd_audio_fifo2_monitor_play2(ct_dd_audio_fifo2_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor2_s") ) {
		ct_dd_audio_fifo2_monitor_play2_slave(ct_dd_audio_fifo2_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor3_n") ) {
		ct_dd_audio_fifo2_monitor_play3_n(ct_dd_audio_fifo2_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor3") ) {
		ct_dd_audio_fifo2_monitor_play3(ct_dd_audio_fifo2_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor3_s") ) {
		ct_dd_audio_fifo2_monitor_play3_slave(ct_dd_audio_fifo2_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor0_d2") ) {
		ct_dd_audio_fifo3_monitor_play0_D2(ct_dd_audio_fifo3_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor1_d2") ) {
		ct_dd_audio_fifo3_monitor_play1_D2(ct_dd_audio_fifo3_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor2_d2") ) {
		ct_dd_audio_fifo3_monitor_play2_D2(ct_dd_audio_fifo3_new(temp, 0));
	}
	else if( !strcmp(str, "play_monitor3_d2") ) {
		ct_dd_audio_fifo3_monitor_play3_D2(ct_dd_audio_fifo3_new(temp, 0));
	}
	else if( !strcmp(str, "bitshift") ) {
		ct_dd_audio_fifo3_bit_shift((kuint16*)CtAudioCaseTwelve_CtDdAudio_CT_DD_Audio_WORK_AREA , 0x1000000);
	}
	else if( !strcmp(str, "pdm_sync") ) {
		ct_dd_audio_fifo3_sync_pdm();
	}else {
		Ddim_Print(("ddaudio : ERROR command line\n"));
	}

	if(temp)
	{
		k_object_unref(temp);
		temp = NULL;
	}
}

CtAudioCaseTwelve *ct_audio_case_twelve_new(void)
{
	CtAudioCaseTwelve *self = k_object_new(CT_TYPE_AUDIO_CASE_TWELVE);
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}

