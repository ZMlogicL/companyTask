/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseTen类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、CtAudioCaseTen类
*@version 1.0.0
*
*/

#include "ctaudiocaseten.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtAudioCaseTen, ct_audio_case_ten)
#define CT_AUDIO_CASE_TEN_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), \
		CtAudioCaseTenPrivate, CT_TYPE_AUDIO_CASE_TEN))

struct _CtAudioCaseTenPrivate
{
	
};

/*
*DECLS
*/
static void ct_audio_case_ten_constructor(CtAudioCaseTen *self);
static void ct_audio_case_ten_destructor(CtAudioCaseTen *self);
static void doWithArgs_od(AbsCtAudioCase *self, kint caseValue);

/*
 * IMPL
 */
static void ct_audio_case_ten_constructor(CtAudioCaseTen *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void ct_audio_case_ten_destructor(CtAudioCaseTen *self)
{
	self = NULL;
}

//123-244
static void doWithArgs_od(AbsCtAudioCase *self, kint caseValue)
{
	kpointer temp = NULL;
	kpointer secondTemp = NULL;
	switch(caseValue)
	{
		case 123:
			ct_dd_audio_get_ctrl_i2scmmn_test2(ct_dd_audio_get_new(&temp, 0));
			break;
		case 124:
			ct_dd_audio_ctrl8_i2sin_test11(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 125:
			ct_dd_audio_ctrl8_i2sin_test11(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 126:
			ct_dd_audio_ctrl8_i2sin_test11(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 127:
			ct_dd_audio_ctrl8_i2sin_test11(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 128:
			ct_dd_audio_ctrl8_i2sin_test11(ct_dd_audio_ctrl8_new(&temp, 5));
			break;
		case 129:
			ct_dd_audio_ctrl8_i2sin_test1(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 130:
			ct_dd_audio_ctrl8_i2sin_test1(ct_dd_audio_ctrl8_new(&temp, 6));
			break;
		case 131:
			ct_dd_audio_ctrl8_i2sin_test12(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 132:
			ct_dd_audio_ctrl8_i2sin_test13(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 133:
			ct_dd_audio_ctrl8_i2sin_test14(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 134:
			ct_dd_audio_get_ctrl_i2sin_test1(ct_dd_audio_get_new(&temp, 3));
			break;
		case 135:
			ct_dd_audio_get_ctrl_i2sin_test1(ct_dd_audio_get_new(&temp, 6));
			break;
		case 136:
			ct_dd_audio_get_ctrl_i2sin_test2(ct_dd_audio_get_new(&temp, 0));
			break;
		case 137:
			ct_dd_audio_ctrl9_i2sout_test36(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 138:
			ct_dd_audio_ctrl9_i2sout_test37(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 139:
			ct_dd_audio_ctrl9_i2sout_test38(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 140:
			ct_dd_audio_ctrl9_i2sout_test39(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 141:
			ct_dd_audio_ctrl10_i2sout_test40(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 142:
			ct_dd_audio_ctrl9_i2sout_test36(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 143:
			ct_dd_audio_ctrl9_i2sout_test37(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 144:
			ct_dd_audio_ctrl9_i2sout_test38(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 145:
			ct_dd_audio_ctrl9_i2sout_test39(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 146:
			ct_dd_audio_ctrl10_i2sout_test40(ct_dd_audio_ctrl10_new(&temp, 1));
			break;
		case 147:
			ct_dd_audio_ctrl9_i2sout_test36(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 148:
			ct_dd_audio_ctrl9_i2sout_test37(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 149:
			ct_dd_audio_ctrl9_i2sout_test38(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 150:
			ct_dd_audio_ctrl9_i2sout_test39(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 151:
			ct_dd_audio_ctrl10_i2sout_test40(ct_dd_audio_ctrl10_new(&temp, 2));
			break;
		case 152:
			ct_dd_audio_ctrl9_i2sout_test36(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 153:
			ct_dd_audio_ctrl9_i2sout_test37(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 154:
			ct_dd_audio_ctrl9_i2sout_test38(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 155:
			ct_dd_audio_ctrl9_i2sout_test39(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 156:
			ct_dd_audio_ctrl10_i2sout_test40(ct_dd_audio_ctrl10_new(&temp, 3));
			break;
		case 157:
			ct_dd_audio_ctrl8_i2sout_test1(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 158:
			ct_dd_audio_ctrl10_i2sout_test41(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 159:
			ct_dd_audio_ctrl10_i2sout_test42(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 160:
			ct_dd_audio_ctrl10_i2sout_test43(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 161:
			ct_dd_audio_ctrl10_i2sout_test44(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 162:
			ct_dd_audio_get_ctrl_i2sout_test1(ct_dd_audio_get_new(&temp, 4));
			break;
		case 163:
			ct_dd_audio_get_ctrl_i2sout_test2(ct_dd_audio_get_new(&temp, 0));
			break;
		case 164:
			ct_dd_audio_ctrl10_dmain_test3(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 165:
			ct_dd_audio_ctrl10_dmain_test4(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 166:
			ct_dd_audio_ctrl10_dmain_test5(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 167:
			ct_dd_audio_ctrl10_dmain_test3(ct_dd_audio_ctrl10_new(&temp, 1));
			break;
		case 168:
			ct_dd_audio_ctrl10_dmain_test4(ct_dd_audio_ctrl10_new(&temp, 1));
			break;
		case 169:
			ct_dd_audio_ctrl10_dmain_test5(ct_dd_audio_ctrl10_new(&temp, 1));
			break;
		case 170:
			ct_dd_audio_ctrl10_dmain_test3(ct_dd_audio_ctrl10_new(&temp, 2));
			break;
		case 171:
			ct_dd_audio_ctrl10_dmain_test4(ct_dd_audio_ctrl10_new(&temp, 2));
			break;
		case 172:
			ct_dd_audio_ctrl10_dmain_test5(ct_dd_audio_ctrl10_new(&temp, 2));
			break;
		case 173:
			ct_dd_audio_ctrl10_dmain_test3(ct_dd_audio_ctrl10_new(&temp, 4));
			break;
		case 174:
			ct_dd_audio_ctrl10_dmain_test4(ct_dd_audio_ctrl10_new(&temp, 4));
			break;
		case 175:
			ct_dd_audio_ctrl10_dmain_test5(ct_dd_audio_ctrl10_new(&temp, 4));
			break;
		case 176:
			ct_dd_audio_ctrl10_dmain_test3(ct_dd_audio_ctrl10_new(&temp, 5));
			break;
		case 177:
			ct_dd_audio_ctrl10_dmain_test4(ct_dd_audio_ctrl10_new(&temp, 5));
			break;
		case 178:
			ct_dd_audio_ctrl10_dmain_test5(ct_dd_audio_ctrl10_new(&temp, 5));
			break;
		case 179:
			ct_dd_audio_ctrl10_dmain_test1(ct_dd_audio_ctrl10_new(&temp, 3));
			break;
		case 180:
			ct_dd_audio_ctrl10_dmain_test1(ct_dd_audio_ctrl10_new(&temp, 6));
			break;
		case 181:
			ct_dd_audio_ctrl10_dmain_test6(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 182:
			ct_dd_audio_ctrl10_dmain_test7(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 183:
			ct_dd_audio_get_ctrl_dmain_test1(ct_dd_audio_get_new(&temp, 3));
			break;
		case 184:
			ct_dd_audio_get_ctrl_dmain_test1(ct_dd_audio_get_new(&temp, 6));
			break;
		case 185:
			ct_dd_audio_get_ctrl_dmain_test2(ct_dd_audio_get_new(&temp, 0));
			break;
		case 186:
			ct_dd_audio_ctrl10_dmaout_test3(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 187:
			ct_dd_audio_ctrl10_dmaout_test4(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 188:
			ct_dd_audio_ctrl10_dmaout_test5(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 189:
			ct_dd_audio_ctrl10_dmaout_test3(ct_dd_audio_ctrl10_new(&temp, 1));
			break;
		case 190:
			ct_dd_audio_ctrl10_dmaout_test4(ct_dd_audio_ctrl10_new(&temp, 1));
			break;
		case 191:
			ct_dd_audio_ctrl10_dmaout_test5(ct_dd_audio_ctrl10_new(&temp, 1));
			break;
		case 192:
			ct_dd_audio_ctrl10_dmaout_test3(ct_dd_audio_ctrl10_new(&temp, 2));
			break;
		case 193:
			ct_dd_audio_ctrl10_dmaout_test4(ct_dd_audio_ctrl10_new(&temp, 2));
			break;
		case 194:
			ct_dd_audio_ctrl10_dmaout_test5(ct_dd_audio_ctrl10_new(&temp, 2));
			break;
		case 195:
			ct_dd_audio_ctrl10_dmaout_test3(ct_dd_audio_ctrl10_new(&temp, 3));
			break;
		case 196:
			ct_dd_audio_ctrl10_dmaout_test4(ct_dd_audio_ctrl10_new(&temp, 3));
			break;
		case 197:
			ct_dd_audio_ctrl10_dmaout_test5(ct_dd_audio_ctrl10_new(&temp, 3));
			break;
		case 198:
			ct_dd_audio_ctrl10_dmaout_test1(ct_dd_audio_ctrl10_new(&temp, 4));
			break;
		case 199:
			ct_dd_audio_ctrl10_dmaout_test6(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 200:
			ct_dd_audio_ctrl10_dmaout_test7(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 201:
			ct_dd_audio_get_ctrl_dmaout_test1(ct_dd_audio_get_new(&temp, 4));
			break;
		case 202:
			ct_dd_audio_get_ctrl_dmaout_test2(ct_dd_audio_get_new(&temp, 0));
			break;
		case 203:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_start_input_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, 0));
			break;
		case 204:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 2));
			ct_dd_audio_start_input_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, 2));
			break;
		case 205:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 4));
			ct_dd_audio_start_input_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, 4));
			break;
		case 206:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 5));
			ct_dd_audio_start_input_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, 5));
			break;
		case 207:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_start_input_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 208:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 4));
			ct_dd_audio_start_input_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, D_DD_AUDIO_IF_CH4_CH5));
			break;
		case 209:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 5));
			ct_dd_audio_start_input_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, D_DD_AUDIO_IF_CH4_CH5));
			break;
		case 210:
			ct_dd_audio_start_input_test2(ct_dd_audio_start_new(&temp, 3));
			break;
		case 211:
			ct_dd_audio_start_input_test2(ct_dd_audio_start_new(&temp, 6));
			break;
		case 212:
			ct_dd_audio_init_test(NULL);
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, 0));
			break;
		case 213:
			ct_dd_audio_init_test(NULL);
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, 2));
			break;
		case 214:
			ct_dd_audio_init_test(NULL);
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, 4));
			break;
		case 215:
			ct_dd_audio_init_test(NULL);
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, 5));
			break;
		case 216:
			ct_dd_audio_init_test(NULL);
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 217:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 218:
			ct_dd_audio_init_test(NULL);
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, D_DD_AUDIO_IF_CH4_CH5));
			break;
		case 219:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 4));
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, D_DD_AUDIO_IF_CH4_CH5));
			break;
		case 220:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 5));
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, D_DD_AUDIO_IF_CH4_CH5));
			break;
		case 221:
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, 3));
			break;
		case 222:
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, 6));
			break;
		case 223:
			ct_dd_audio_get_status_input_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 224:
			ct_dd_audio_get_status_input_test(ct_dd_audio_get_new(&temp, 6));
			break;
		case 225:
			ct_dd_audio_start_output_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_start_output_test2((CtDdAudioStart*)temp);
			break;
		case 226:
			ct_dd_audio_start_loop_back_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_start_output_test2((CtDdAudioStart*)temp);
			break;
		case 227:
			ct_dd_audio_start_output_test1(ct_dd_audio_start_new(&temp, 2));
			ct_dd_audio_start_output_test2((CtDdAudioStart*)temp);
			break;
		case 228:
			ct_dd_audio_start_loop_back_test1(ct_dd_audio_start_new(&temp, 2));
			ct_dd_audio_start_output_test2((CtDdAudioStart*)temp);
			break;
		case 229:
			ct_dd_audio_start_output_test1(ct_dd_audio_start_new(&temp, 3));
			ct_dd_audio_start_output_test2((CtDdAudioStart*)temp);
			break;
		case 230:
			ct_dd_audio_start_output_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_start_output_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 231:
			ct_dd_audio_start_loop_back_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_start_output_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 232:
			ct_dd_audio_start_output_test2(ct_dd_audio_start_new(&temp, 4));
			break;
		case 233:
			ct_dd_audio_stop_output_test(ct_dd_audio_stop_new(&secondTemp, 0));
			break;
		case 234:
			ct_dd_audio_stop_output_test(ct_dd_audio_stop_new(&secondTemp, 2));
			break;
		case 235:
			ct_dd_audio_stop_output_test(ct_dd_audio_stop_new(&secondTemp, 3));
			break;
		case 236:
			ct_dd_audio_stop_output_test(ct_dd_audio_stop_new(&secondTemp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 237:
			ct_dd_audio_start_output_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_stop_output_test(ct_dd_audio_stop_new(&secondTemp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 238:
			ct_dd_audio_stop_output_test(ct_dd_audio_stop_new(&secondTemp, 4));
			break;
		case 239:
			ct_dd_audio_get_status_output_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 240:
			ct_dd_audio_start_loop_back_test2(ct_dd_audio_start_new(&temp, 0));
			break;
		case 241:
			ct_dd_audio_start_loop_back_test3(ct_dd_audio_start_new(&temp, 0));
			break;
		case 242:
			ct_dd_audio_start_loop_back_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_start_loop_back_test2((CtDdAudioStart*)temp);
			break;
		case 243:
			ct_dd_audio_start_loop_back_test2(ct_dd_audio_start_new(&temp, 2));
			break;
		case 244:
			ct_dd_audio_start_loop_back_test3(ct_dd_audio_start_new(&temp, 2));
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

	if(secondTemp)
	{
		k_object_unref(secondTemp);
		secondTemp = NULL;
	}
}

/*
*PUBLIC
*/

CtAudioCaseTen *ct_audio_case_ten_new(void)
{
	CtAudioCaseTen *self = k_object_new(CT_TYPE_AUDIO_CASE_TEN);
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}

