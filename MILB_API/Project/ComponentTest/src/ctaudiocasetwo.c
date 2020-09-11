/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseTwo类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseTwo类
*@version 1.0.0
*
*/

#include "ctaudiocasetwo.h"

G_DEFINE_TYPE(CtAudioCaseTwo, ct_audio_case_two, G_TYPE_OBJECT);
#define CT_AUDIO_CASE_TWO_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
		CT_TYPE_AUDIO_CASE_TWO, CtAudioCaseTwoPrivate))

struct _CtAudioCaseTwoPrivate
{
	
};
/*
*DECLS
*/
static void ct_audio_case_two_class_init(CtAudioCaseTwoClass *klass);
static void ct_audio_case_two_init(CtAudioCaseTwo *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue);
/*
 * IMPL
 */
static void ct_audio_case_two_class_init(CtAudioCaseTwoClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtAudioCaseTwoPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_audio_case_two_init(CtAudioCaseTwo *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_two_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_two_parent_class)->finalize(object);
}

//133-264
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue)
{
	gpointer temp = NULL;
	switch(caseValue)
	{
		case 133:
			ct_dd_audio_int_handler_test2(ct_dd_audio_int_new(&temp, 5));
			break;
		case 134:
			ct_dd_audio_int_handler_test3(ct_dd_audio_int_new(&temp, 5));
			break;
		case 135:
			ct_dd_audio_int_handler_test4(ct_dd_audio_int_new(&temp, 5));
			break;
		case 136:
			ct_dd_audio_int_handler_test5(ct_dd_audio_int_new(&temp, 5));
			break;
		case 137:
			ct_dd_audio_int_handler_test6(ct_dd_audio_int_new(&temp, 5));
			break;
		case 138:
			ct_dd_audio_int_handler_test7(ct_dd_audio_int_new(&temp, 5));
			break;
		case 139:
			ct_dd_audio_int_handler_test8(ct_dd_audio_int_new(&temp, 5));
			break;
		case 140:
			ct_dd_audio_int_handler_test9(ct_dd_audio_int_new(&temp, 5));
			break;
		case 141:
			ct_dd_audio_int_handler_test10(ct_dd_audio_int_new(&temp, 5));
			break;
		case 142:
			ct_dd_audio_int_handler_test11(ct_dd_audio_int_new(&temp, 5));
			break;
		case 143:
			ct_dd_audio_int_handler_test12(ct_dd_audio_int_new(&temp, 5));
			break;
		case 144:
			ct_dd_audio_int_handler_test13(ct_dd_audio_int_new(&temp, 5));
			break;
		case 145:
			ct_dd_audio_int_handler_test14(ct_dd_audio_int_new(&temp, 5));
			break;
		case 146:
			ct_dd_audio_int_handler_test15(ct_dd_audio_int_new(&temp, 5));
			break;
		case 147:
			ct_dd_audio_int_handler_test16(ct_dd_audio_int_new(&temp, 5));
			break;
		case 148:
			ct_dd_audio_int_handler_test17(ct_dd_audio_int_new(&temp, 5));
			break;
		case 149:
			ct_dd_audio_int_handler_test18(ct_dd_audio_int_new(&temp, 5));
			break;
		case 150:
			ct_dd_audio_int_handler_test19(ct_dd_audio_int_new(&temp, 5));
			break;
		case 151:
			ct_dd_audio_init_test(NULL);
			break;
		case 152:
			ct_dd_audio_reset_test(ct_dd_audio_new(&temp, 0));
			break;
		case 153:
			ct_dd_audio_reset_test(ct_dd_audio_new(&temp, 1));
			break;
		case 154:
			ct_dd_audio_reset_test(ct_dd_audio_new(&temp, 2));
			break;
		case 155:
			ct_dd_audio_reset_test(ct_dd_audio_new(&temp, 3));
			break;
		case 156:
			ct_dd_audio_reset_test(ct_dd_audio_new(&temp, 4));
			break;
		case 157:
			ct_dd_audio_reset_test(ct_dd_audio_new(&temp, 5));
			break;
		case 158:
			ct_dd_audio_ctrl_common_test1(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 159:
			ct_dd_audio_ctrl_common_test2(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 160:
			ct_dd_audio_ctrl_common_test3(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 161:
			ct_dd_audio_ctrl_common_test4(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 162:
			ct_dd_audio_ctrl_common_test5(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 163:
			ct_dd_audio_ctrl_common_test1(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 164:
			ct_dd_audio_ctrl_common_test2(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 165:
			ct_dd_audio_ctrl_common_test3(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 166:
			ct_dd_audio_ctrl_common_test4(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 167:
			ct_dd_audio_ctrl_common_test5(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 168:
			ct_dd_audio_ctrl_common_test1(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 169:
			ct_dd_audio_ctrl_common_test2(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 170:
			ct_dd_audio_ctrl_common_test3(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 171:
			ct_dd_audio_ctrl_common_test4(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 172:
			ct_dd_audio_ctrl_common_test5(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 173:
			ct_dd_audio_ctrl_common_test1(ct_dd_audio_ctrl_new(&temp, 3));
			break;
		case 174:
			ct_dd_audio_ctrl_common_test2(ct_dd_audio_ctrl_new(&temp, 3));
			break;
		case 175:
			ct_dd_audio_ctrl_common_test3(ct_dd_audio_ctrl_new(&temp, 3));
			break;
		case 176:
			ct_dd_audio_ctrl_common_test4(ct_dd_audio_ctrl_new(&temp, 3));
			break;
		case 177:
			ct_dd_audio_ctrl_common_test5(ct_dd_audio_ctrl_new(&temp, 3));
			break;
		case 178:
			ct_dd_audio_ctrl_common_test1(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 179:
			ct_dd_audio_ctrl_common_test2(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 180:
			ct_dd_audio_ctrl_common_test3(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 181:
			ct_dd_audio_ctrl_common_test4(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 182:
			ct_dd_audio_ctrl_common_test5(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 183:
			ct_dd_audio_ctrl_common_test1(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 184:
			ct_dd_audio_ctrl_common_test2(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 185:
			ct_dd_audio_ctrl_common_test3(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 186:
			ct_dd_audio_ctrl_common_test4(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 187:
			ct_dd_audio_ctrl_common_test5(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 188:
			ct_dd_audio_get_ctrl_common_test1(ct_dd_audio_get_new(&temp, 0));
			break;
		case 189:
			ct_dd_audio_get_ctrl_common_test1(ct_dd_audio_get_new(&temp, 1));
			break;
		case 190:
			ct_dd_audio_get_ctrl_common_test1(ct_dd_audio_get_new(&temp, 2));
			break;
		case 191:
			ct_dd_audio_get_ctrl_common_test1(ct_dd_audio_get_new(&temp, 3));
			break;
		case 192:
			ct_dd_audio_get_ctrl_common_test1(ct_dd_audio_get_new(&temp, 4));
			break;
		case 193:
			ct_dd_audio_get_ctrl_common_test1(ct_dd_audio_get_new(&temp, 5));
			break;
		case 194:
			ct_dd_audio_ctrl_input_test1(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 195:
			ct_dd_audio_ctrl_input_test2(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 196:
			ct_dd_audio_ctrl_input_test3(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 197:
			ct_dd_audio_ctrl_input_test4(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 198:
			ct_dd_audio_ctrl_input_test5(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 199:
			ct_dd_audio_ctrl_input_test6(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 200:
			ct_dd_audio_ctrl_input_test7(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 201:
			ct_dd_audio_ctrl_input_test8(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 202:
			ct_dd_audio_ctrl_input_test9(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 203:
			ct_dd_audio_ctrl_input_test10(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 204:
			ct_dd_audio_ctrl1_input_test11(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 205:
			ct_dd_audio_ctrl1_input_test12(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 206:
			ct_dd_audio_ctrl1_input_test13(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 207:
			ct_dd_audio_ctrl1_input_test14(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 208:
			ct_dd_audio_ctrl_input_test1(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 209:
			ct_dd_audio_ctrl_input_test2(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 210:
			ct_dd_audio_ctrl_input_test3(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 211:
			ct_dd_audio_ctrl_input_test4(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 212:
			ct_dd_audio_ctrl_input_test5(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 213:
			ct_dd_audio_ctrl_input_test6(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 214:
			ct_dd_audio_ctrl_input_test7(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 215:
			ct_dd_audio_ctrl_input_test8(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 216:
			ct_dd_audio_ctrl_input_test9(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 217:
			ct_dd_audio_ctrl_input_test10(ct_dd_audio_ctrl_new(&temp, 1));
			break;
		case 218:
			ct_dd_audio_ctrl1_input_test11(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 219:
			ct_dd_audio_ctrl1_input_test12(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 220:
			ct_dd_audio_ctrl1_input_test13(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 221:
			ct_dd_audio_ctrl1_input_test14(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 222:
			ct_dd_audio_ctrl_input_test1(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 223:
			ct_dd_audio_ctrl_input_test2(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 224:
			ct_dd_audio_ctrl_input_test3(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 225:
			ct_dd_audio_ctrl_input_test4(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 226:
			ct_dd_audio_ctrl_input_test5(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 227:
			ct_dd_audio_ctrl_input_test6(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 228:
			ct_dd_audio_ctrl_input_test7(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 229:
			ct_dd_audio_ctrl_input_test8(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 230:
			ct_dd_audio_ctrl_input_test9(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 231:
			ct_dd_audio_ctrl_input_test10(ct_dd_audio_ctrl_new(&temp, 2));
			break;
		case 232:
			ct_dd_audio_ctrl1_input_test11(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 233:
			ct_dd_audio_ctrl1_input_test12(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 234:
			ct_dd_audio_ctrl1_input_test13(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 235:
			ct_dd_audio_ctrl1_input_test14(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 236:
			ct_dd_audio_ctrl_input_test1(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 237:
			ct_dd_audio_ctrl_input_test2(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 238:
			ct_dd_audio_ctrl_input_test3(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 239:
			ct_dd_audio_ctrl_input_test4(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 240:
			ct_dd_audio_ctrl_input_test5(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 241:
			ct_dd_audio_ctrl_input_test6(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 242:
			ct_dd_audio_ctrl_input_test7(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 243:
			ct_dd_audio_ctrl_input_test8(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 244:
			ct_dd_audio_ctrl_input_test9(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 245:
			ct_dd_audio_ctrl_input_test10(ct_dd_audio_ctrl_new(&temp, 4));
			break;
		case 246:
			ct_dd_audio_ctrl1_input_test11(ct_dd_audio_ctrl1_new(&temp, 4));
			break;
		case 247:
			ct_dd_audio_ctrl1_input_test12(ct_dd_audio_ctrl1_new(&temp, 4));
			break;
		case 248:
			ct_dd_audio_ctrl1_input_test13(ct_dd_audio_ctrl1_new(&temp, 4));
			break;
		case 249:
			ct_dd_audio_ctrl1_input_test14(ct_dd_audio_ctrl1_new(&temp, 4));
			break;
		case 250:
			ct_dd_audio_ctrl_input_test1(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 251:
			ct_dd_audio_ctrl_input_test2(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 252:
			ct_dd_audio_ctrl_input_test3(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 253:
			ct_dd_audio_ctrl_input_test4(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 254:
			ct_dd_audio_ctrl_input_test5(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 255:
			ct_dd_audio_ctrl_input_test6(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 256:
			ct_dd_audio_ctrl_input_test7(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 257:
			ct_dd_audio_ctrl_input_test8(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 258:
			ct_dd_audio_ctrl_input_test9(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 259:
			ct_dd_audio_ctrl_input_test10(ct_dd_audio_ctrl_new(&temp, 5));
			break;
		case 260:
			ct_dd_audio_ctrl1_input_test11(ct_dd_audio_ctrl1_new(&temp, 5));
			break;
		case 261:
			ct_dd_audio_ctrl1_input_test12(ct_dd_audio_ctrl1_new(&temp, 5));
			break;
		case 262:
			ct_dd_audio_ctrl1_input_test13(ct_dd_audio_ctrl1_new(&temp, 5));
			break;
		case 263:
			ct_dd_audio_ctrl1_input_test14(ct_dd_audio_ctrl1_new(&temp, 5));
			break;
		case 264:
			ct_dd_audio_get_ctrl_input_test1(ct_dd_audio_get_new(&temp, 0));
			break;
		default :
			DriverCommon_DDIM_PRINT(("ddaudio : ERROR command line\n"));
			break;
	}
	if(temp)
	{
		k_object_unref(temp);
		temp = NULL;
	}
}

/*
*PUBLIC
*/

CtAudioCaseTwo *ct_audio_case_two_new(void)
{
	CtAudioCaseTwo *self = CT_AUDIO_CASE_TWO(g_object_new(CT_TYPE_AUDIO_CASE_TWO, NULL));
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}



