/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseOne类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseOne类
*@version 1.0.0
*
*/
#include "ctaudiocasefactory.h"
#include "ctaudiocaseone.h"

G_DEFINE_TYPE(CtAudioCaseOne, ct_audio_case_one, G_TYPE_OBJECT);
#define 	CT_AUDIO_CASE_ONE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_AUDIO_CASE_ONE, CtAudioCaseOnePrivate))

#define CtAudioCaseOne_EXCEPTION -1

struct _CtAudioCaseOnePrivate
{
	
};

/*
*DECLS
*/
static void ct_audio_case_one_class_init(CtAudioCaseOneClass *klass);
static void ct_audio_case_one_init(CtAudioCaseOne *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue);
/*
 * IMPL
 */
static void ct_audio_case_one_constructor(CtAudioCaseOne *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void ct_audio_case_one_destructor(CtAudioCaseOne *self)
{
	self = NULL;
}

static void ct_audio_case_one_class_init(CtAudioCaseOneClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtAudioCaseOnePrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_audio_case_one_init(CtAudioCaseOne *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_one_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_one_parent_class)->finalize(object);
}

//1 - 132
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue)
{
	gpointer temp = NULL;
	switch(caseValue)
	{
		case 1:
			ct_dd_audio_input_open_test1(ct_dd_audio_new(&temp, 0));
			break;
		case 2:
			ct_dd_audio_input_open_test2(ct_dd_audio_new(&temp, 0));
			break;
		case 3:
			ct_dd_audio_input_open_test3(ct_dd_audio_new(&temp, 0));
			break;
		case 4:
			ct_dd_audio_input_open_test1(ct_dd_audio_new(&temp, 1));
			break;
		case 5:
			ct_dd_audio_input_open_test2(ct_dd_audio_new(&temp, 1));
			break;
			break;
		case 6:
			ct_dd_audio_input_open_test3(ct_dd_audio_new(&temp, 1));
			break;
		case 7:
			ct_dd_audio_input_open_test1(ct_dd_audio_new(&temp, 2));
			break;
		case 8:
			ct_dd_audio_input_open_test2(ct_dd_audio_new(&temp, 2));
			break;
			break;
		case 9:
			ct_dd_audio_input_open_test3(ct_dd_audio_new(&temp, 2));
			break;
		case 10:
			ct_dd_audio_input_open_test1(ct_dd_audio_new(&temp, 4));
			break;
		case 11:
			ct_dd_audio_input_open_test2(ct_dd_audio_new(&temp, 4));
			break;
			break;
		case 12:
			ct_dd_audio_input_open_test3(ct_dd_audio_new(&temp, 4));
			break;
		case 13:
			ct_dd_audio_input_open_test1(ct_dd_audio_new(&temp, 5));
			break;
		case 14:
			ct_dd_audio_input_open_test2(ct_dd_audio_new(&temp, 5));
			break;
			break;
		case 15:
			ct_dd_audio_input_open_test3(ct_dd_audio_new(&temp, 5));
			break;
		case 16:
			ct_dd_audio_output_open_test1(ct_dd_audio_new(&temp, 0));
			break;
		case 17:
			ct_dd_audio_output_open_test2(ct_dd_audio_new(&temp, 0));
			break;
		case 18:
			ct_dd_audio_output_open_test3(ct_dd_audio_new(&temp, 0));
			break;
		case 19:
			ct_dd_audio_output_open_test1(ct_dd_audio_new(&temp, 1));
			break;
		case 20:
			ct_dd_audio_output_open_test2(ct_dd_audio_new(&temp, 0));
			break;
		case 21:
			ct_dd_audio_output_open_test3(ct_dd_audio_new(&temp, 1));
			break;
		case 22:
			ct_dd_audio_output_open_test1(ct_dd_audio_new(&temp, 2));
			break;
		case 23:
			ct_dd_audio_output_open_test2(ct_dd_audio_new(&temp, 0));
			break;
		case 24:
			ct_dd_audio_output_open_test3(ct_dd_audio_new(&temp, 2));
			break;
		case 25:
			ct_dd_audio_output_open_test1(ct_dd_audio_new(&temp, 3));
			break;
		case 26:
			ct_dd_audio_output_open_test2(ct_dd_audio_new(&temp, 0));
			break;
		case 27:
			ct_dd_audio_output_open_test3(ct_dd_audio_new(&temp, 3));
			break;
		case 28:
			ct_dd_audio_input_close_test(ct_dd_audio_new(&temp, 0));
			break;
		case 29:
			ct_dd_audio_input_close_test(ct_dd_audio_new(&temp, 1));
			break;
		case 30:
			ct_dd_audio_input_close_test(ct_dd_audio_new(&temp, 2));
			break;
		case 31:
			ct_dd_audio_input_close_test(ct_dd_audio_new(&temp, 4));
			break;
		case 32:
			ct_dd_audio_input_close_test(ct_dd_audio_new(&temp, 5));
			break;
		case 33:
			ct_dd_audio_output_close_test(ct_dd_audio_new(&temp, 0));
			break;
		case 34:
			ct_dd_audio_output_close_test(ct_dd_audio_new(&temp, 1));
			break;
		case 35:
			ct_dd_audio_output_close_test(ct_dd_audio_new(&temp, 2));
			break;
		case 36:
			ct_dd_audio_output_close_test(ct_dd_audio_new(&temp, 3));
			break;
		case 37:
			ct_dd_audio_int_handler_test1(ct_dd_audio_int_new(&temp, 0));
			break;
		case 38:
			ct_dd_audio_int_handler_test2(ct_dd_audio_int_new(&temp, 0));
			break;
		case 39:
			ct_dd_audio_int_handler_test3(ct_dd_audio_int_new(&temp, 0));
			break;
		case 40:
			ct_dd_audio_int_handler_test4(ct_dd_audio_int_new(&temp, 0));
			break;
		case 41:
			ct_dd_audio_int_handler_test5(ct_dd_audio_int_new(&temp, 0));
			break;
		case 42:
			ct_dd_audio_int_handler_test6(ct_dd_audio_int_new(&temp, 0));
			break;
		case 43:
			ct_dd_audio_int_handler_test7(ct_dd_audio_int_new(&temp, 0));
			break;
		case 44:
			ct_dd_audio_int_handler_test8(ct_dd_audio_int_new(&temp, 0));
			break;
		case 45:
			ct_dd_audio_int_handler_test9(ct_dd_audio_int_new(&temp, 0));
			break;
		case 46:
			ct_dd_audio_int_handler_test10(ct_dd_audio_int_new(&temp, 0));
			break;
		case 47:
			ct_dd_audio_int_handler_test11(ct_dd_audio_int_new(&temp, 0));
			break;
		case 48:
			ct_dd_audio_int_handler_test12(ct_dd_audio_int_new(&temp, 0));
			break;
		case 49:
			ct_dd_audio_int_handler_test13(ct_dd_audio_int_new(&temp, 0));
			break;
		case 50:
			ct_dd_audio_int_handler_test14(ct_dd_audio_int_new(&temp, 0));
			break;
		case 51:
			ct_dd_audio_int_handler_test15(ct_dd_audio_int_new(&temp, 0));
			break;
		case 52:
			ct_dd_audio_int_handler_test16(ct_dd_audio_int_new(&temp, 0));
			break;
		case 53:
			ct_dd_audio_int_handler_test17(ct_dd_audio_int_new(&temp, 0));
			break;
		case 54:
			ct_dd_audio_int_handler_test18(ct_dd_audio_int_new(&temp, 0));
			break;
		case 55:
			ct_dd_audio_int_handler_test19(ct_dd_audio_int_new(&temp, 0));
			break;
		case 56:
			ct_dd_audio_int_handler_test1(ct_dd_audio_int_new(&temp, 1));
			break;
		case 57:
			ct_dd_audio_int_handler_test2(ct_dd_audio_int_new(&temp, 1));
			break;
		case 58:
			ct_dd_audio_int_handler_test3(ct_dd_audio_int_new(&temp, 1));
			break;
		case 59:
			ct_dd_audio_int_handler_test4(ct_dd_audio_int_new(&temp, 1));
			break;
		case 60:
			ct_dd_audio_int_handler_test5(ct_dd_audio_int_new(&temp, 1));
			break;
		case 61:
			ct_dd_audio_int_handler_test6(ct_dd_audio_int_new(&temp, 1));
			break;
		case 62:
			ct_dd_audio_int_handler_test7(ct_dd_audio_int_new(&temp, 1));
			break;
		case 63:
			ct_dd_audio_int_handler_test8(ct_dd_audio_int_new(&temp, 1));
			break;
		case 64:
			ct_dd_audio_int_handler_test9(ct_dd_audio_int_new(&temp, 1));
			break;
		case 65:
			ct_dd_audio_int_handler_test10(ct_dd_audio_int_new(&temp, 1));
			break;
		case 66:
			ct_dd_audio_int_handler_test11(ct_dd_audio_int_new(&temp, 1));
			break;
		case 67:
			ct_dd_audio_int_handler_test12(ct_dd_audio_int_new(&temp, 1));
			break;
		case 68:
			ct_dd_audio_int_handler_test13(ct_dd_audio_int_new(&temp, 1));
			break;
		case 69:
			ct_dd_audio_int_handler_test14(ct_dd_audio_int_new(&temp, 1));
			break;
		case 70:
			ct_dd_audio_int_handler_test15(ct_dd_audio_int_new(&temp, 1));
			break;
		case 71:
			ct_dd_audio_int_handler_test16(ct_dd_audio_int_new(&temp, 1));
			break;
		case 72:
			ct_dd_audio_int_handler_test17(ct_dd_audio_int_new(&temp, 1));
			break;
		case 73:
			ct_dd_audio_int_handler_test18(ct_dd_audio_int_new(&temp, 1));
			break;
		case 74:
			ct_dd_audio_int_handler_test19(ct_dd_audio_int_new(&temp, 1));
			break;
		case 75:
			ct_dd_audio_int_handler_test1(ct_dd_audio_int_new(&temp, 2));
			break;
		case 76:
			ct_dd_audio_int_handler_test2(ct_dd_audio_int_new(&temp, 2));
			break;
		case 77:
			ct_dd_audio_int_handler_test3(ct_dd_audio_int_new(&temp, 2));
			break;
		case 78:
			ct_dd_audio_int_handler_test4(ct_dd_audio_int_new(&temp, 2));
			break;
		case 79:
			ct_dd_audio_int_handler_test5(ct_dd_audio_int_new(&temp, 2));
			break;
		case 80:
			ct_dd_audio_int_handler_test6(ct_dd_audio_int_new(&temp, 2));
			break;
		case 81:
			ct_dd_audio_int_handler_test7(ct_dd_audio_int_new(&temp, 2));
			break;
		case 82:
			ct_dd_audio_int_handler_test8(ct_dd_audio_int_new(&temp, 2));
			break;
		case 83:
			ct_dd_audio_int_handler_test9(ct_dd_audio_int_new(&temp, 2));
			break;
		case 84:
			ct_dd_audio_int_handler_test10(ct_dd_audio_int_new(&temp, 2));
			break;
		case 85:
			ct_dd_audio_int_handler_test11(ct_dd_audio_int_new(&temp, 2));
			break;
		case 86:
			ct_dd_audio_int_handler_test12(ct_dd_audio_int_new(&temp, 2));
			break;
		case 87:
			ct_dd_audio_int_handler_test13(ct_dd_audio_int_new(&temp, 2));
			break;
		case 88:
			ct_dd_audio_int_handler_test14(ct_dd_audio_int_new(&temp, 2));
			break;
		case 89:
			ct_dd_audio_int_handler_test15(ct_dd_audio_int_new(&temp, 2));
			break;
		case 90:
			ct_dd_audio_int_handler_test16(ct_dd_audio_int_new(&temp, 2));
			break;
		case 91:
			ct_dd_audio_int_handler_test17(ct_dd_audio_int_new(&temp, 2));
			break;
		case 92:
			ct_dd_audio_int_handler_test18(ct_dd_audio_int_new(&temp, 2));
			break;
		case 93:
			ct_dd_audio_int_handler_test19(ct_dd_audio_int_new(&temp, 2));
			break;
		case 94:
			ct_dd_audio_int_handler_test1(ct_dd_audio_int_new(&temp, 3));
			break;
		case 95:
			ct_dd_audio_int_handler_test2(ct_dd_audio_int_new(&temp, 3));
			break;
		case 96:
			ct_dd_audio_int_handler_test3(ct_dd_audio_int_new(&temp, 3));
			break;
		case 97:
			ct_dd_audio_int_handler_test4(ct_dd_audio_int_new(&temp, 3));
			break;
		case 98:
			ct_dd_audio_int_handler_test5(ct_dd_audio_int_new(&temp, 3));
			break;
		case 99:
			ct_dd_audio_int_handler_test6(ct_dd_audio_int_new(&temp, 3));
			break;
		case 100:
			ct_dd_audio_int_handler_test7(ct_dd_audio_int_new(&temp, 3));
			break;
		case 101:
			ct_dd_audio_int_handler_test8(ct_dd_audio_int_new(&temp, 3));
			break;
		case 102:
			ct_dd_audio_int_handler_test9(ct_dd_audio_int_new(&temp, 3));
			break;
		case 103:
			ct_dd_audio_int_handler_test10(ct_dd_audio_int_new(&temp, 3));
			break;
		case 104:
			ct_dd_audio_int_handler_test11(ct_dd_audio_int_new(&temp, 3));
			break;
		case 105:
			ct_dd_audio_int_handler_test12(ct_dd_audio_int_new(&temp, 3));
			break;
		case 106:
			ct_dd_audio_int_handler_test13(ct_dd_audio_int_new(&temp, 3));
			break;
		case 107:
			ct_dd_audio_int_handler_test14(ct_dd_audio_int_new(&temp, 3));
			break;
		case 108:
			ct_dd_audio_int_handler_test15(ct_dd_audio_int_new(&temp, 3));
			break;
		case 109:
			ct_dd_audio_int_handler_test16(ct_dd_audio_int_new(&temp, 3));
			break;
		case 110:
			ct_dd_audio_int_handler_test17(ct_dd_audio_int_new(&temp, 3));
			break;
		case 111:
			ct_dd_audio_int_handler_test18(ct_dd_audio_int_new(&temp, 3));
			break;
		case 112:
			ct_dd_audio_int_handler_test19(ct_dd_audio_int_new(&temp, 3));
			break;
		case 113:
			ct_dd_audio_int_handler_test1(ct_dd_audio_int_new(&temp, 4));
			break;
		case 114:
			ct_dd_audio_int_handler_test2(ct_dd_audio_int_new(&temp, 4));
			break;
		case 115:
			ct_dd_audio_int_handler_test3(ct_dd_audio_int_new(&temp, 4));
			break;
		case 116:
			ct_dd_audio_int_handler_test4(ct_dd_audio_int_new(&temp, 4));
			break;
		case 117:
			ct_dd_audio_int_handler_test5(ct_dd_audio_int_new(&temp, 4));
			break;
		case 118:
			ct_dd_audio_int_handler_test6(ct_dd_audio_int_new(&temp, 4));
			break;
		case 119:
			ct_dd_audio_int_handler_test7(ct_dd_audio_int_new(&temp, 4));
			break;
		case 120:
			ct_dd_audio_int_handler_test8(ct_dd_audio_int_new(&temp, 4));
			break;
		case 121:
			ct_dd_audio_int_handler_test9(ct_dd_audio_int_new(&temp, 4));
			break;
		case 122:
			ct_dd_audio_int_handler_test10(ct_dd_audio_int_new(&temp, 4));
			break;
		case 123:
			ct_dd_audio_int_handler_test11(ct_dd_audio_int_new(&temp, 4));
			break;
		case 124:
			ct_dd_audio_int_handler_test12(ct_dd_audio_int_new(&temp, 4));
			break;
		case 125:
			ct_dd_audio_int_handler_test13(ct_dd_audio_int_new(&temp, 4));
			break;
		case 126:
			ct_dd_audio_int_handler_test14(ct_dd_audio_int_new(&temp, 4));
			break;
		case 127:
			ct_dd_audio_int_handler_test15(ct_dd_audio_int_new(&temp, 4));
			break;
		case 128:
			ct_dd_audio_int_handler_test16(ct_dd_audio_int_new(&temp, 4));
			break;
		case 129:
			ct_dd_audio_int_handler_test17(ct_dd_audio_int_new(&temp, 4));
			break;
		case 130:
			ct_dd_audio_int_handler_test18(ct_dd_audio_int_new(&temp, 4));
			break;
		case 131:
			ct_dd_audio_int_handler_test19(ct_dd_audio_int_new(&temp, 4));
			break;
		case 132:
			ct_dd_audio_int_handler_test1(ct_dd_audio_int_new(&temp, 5));
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
/*
 *
 * @brief		Command processing of dd_audio_if.h
 * @param[in]	gint32 argc
 * @param[in]	CHAR** argv
 * @return		None
 * @note		Command processing of MBch.
 * @attention	None
 */

void ct_dd_audio_one_if_main(gint argc, kchar** argv)
{
//	ct_dd_audio_set_gpio(NULL);
	
	Dd_CACHE_L1_Clean_Flush_Dcache_All();
	Dd_CACHE_L2_Clean_Flush_Dcache_All();
	AbsCtAudioCaseType caseTestType = AbsCtAudioCase_EQUAL_DEFAULT;
	gint caseNum = CtAudioCaseOne_EXCEPTION;

	if(atoi(argv[1]) == 1) {
		switch (atoi(argv[2]))
		caseNum = atoi(argv[2]);
		
		if(caseNum >= 1 && caseNum <= 132)
		{
			caseTestType = AbsCtAudioCase_EQUAL_ONE;
		}else if(caseNum >= 132 && caseNum <= 264)
		{
			caseTestType = AbsCtAudioCase_EQUAL_TWO;
		}else if(caseNum >= 265 && caseNum <= 396)
		{
			caseTestType = AbsCtAudioCase_EQUAL_THREE;
		}else if(caseNum >= 397 && caseNum <= 528)
		{
			caseTestType = AbsCtAudioCase_EQUAL_FOUR;
		}else if(caseNum >= 529 && caseNum <= 660)
		{
			caseTestType = AbsCtAudioCase_EQUAL_FIVE;
		}else if(caseNum >= 661 && caseNum <= 792)
		{	
			caseTestType = AbsCtAudioCase_EQUAL_SIX;
		}else if(caseNum >= 793 && caseNum <= 924)
		{
			caseTestType = AbsCtAudioCase_EQUAL_SEVEN;
		}else if(caseNum >= 925 && caseNum <= 1056)
		{
			caseTestType = AbsCtAudioCase_EQUAL_EIGHT;
		}else
		{
			DriverCommon_DDIM_PRINT(("ddaudio : ERROR command line\n"));
		}
	}
	else if(atoi(argv[1]) == 2) {
		caseNum = atoi(argv[2]);
		if(caseNum >= 1 && caseNum <= 122)
		{
			caseTestType = AbsCtAudioCase_EQUAL_NINE;
		}else if(caseNum >= 123 && caseNum <= 244)
		{
			caseTestType = AbsCtAudioCase_EQUAL_TEN;
		}else if(caseNum >= 245 && caseNum <= 367)
		{
			caseTestType = AbsCtAudioCase_EQUAL_ELEVEN;
		}else
		{
			DriverCommon_DDIM_PRINT(("ddaudio : ERROR command line\n"));
		}
	}
	else if(atoi(argv[1]) == 3) {
		caseNum = atoi(argv[2]);
		if(caseNum >= 1 && caseNum <= 131)
		{
			caseTestType = AbsCtAudioCase_EQUAL_TWELVE;
		}else
		{
			DriverCommon_DDIM_PRINT(("ddaudio : ERROR command line\n"));
		}
	}else if(2 == argc)
	{
		caseTestType = AbsCtAudioCase_EQUAL_TWELVE;
	}
	else {
		DriverCommon_DDIM_PRINT(("ddaudio : ERROR command line\n"));
	}

	if(caseTestType != AbsCtAudioCase_EQUAL_DEFAULT)
	{
		AbsCtAudioCase* executeCase = ct_audio_case_factory_create_case(ct_audio_case_factory_new(), caseTestType);
		//判断是字符还是整数:
		if(caseNum == CtAudioCaseOne_EXCEPTION)
		{
			abs_ct_audio_case_do_no_args(executeCase, argv[argc-1]);
		}else
		{
			abs_ct_audio_case_do_with_args(executeCase, caseNum);
		}
		k_object_unref(executeCase);
	}

	Dd_CACHE_L1_Clean_Flush_Dcache_All();
	Dd_CACHE_L2_Clean_Flush_Dcache_All();
}

CtAudioCaseOne *ct_audio_case_one_new(void)
{
	CtAudioCaseOne *self = CT_AUDIO_CASE_ONE(g_object_new(CT_TYPE_AUDIO_CASE_ONE, NULL));
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}

