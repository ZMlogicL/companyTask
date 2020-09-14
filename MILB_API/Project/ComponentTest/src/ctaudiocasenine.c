/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseNine类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseNine类
*@version 1.0.0
*
*/

#include "ctaudiocasenine.h"

G_DEFINE_TYPE(CtAudioCaseNine, ct_audio_case_nine, G_TYPE_OBJECT);
#define CT_AUDIO_CASE_NINE_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_AUDIO_CASE_NINE, CtAudioCaseNinePrivate))

struct _CtAudioCaseNinePrivate
{
};

/*
*DECLS
*/
static void ct_audio_case_nine_class_init(CtAudioCaseNineClass *klass);
static void ct_audio_case_nine_init(CtAudioCaseNine *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue);

/*
 * IMPL
 */
static void ct_audio_case_nine_class_init(CtAudioCaseNineClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtAudioCaseNinePrivate));
}

static void ct_audio_case_nine_init(CtAudioCaseNine *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void dispose_od(GObject *object)
{
	CtAudioCaseNine *self = (CtAudioCaseNine*)object;
}

static void finalize_od(GObject *object)
{
	CtAudioCaseNine *self = (CtAudioCaseNine*)object;
}

//1-122
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue)
{
	gpointer temp =NULL;
	switch(caseValue)
	{
		case 1:
			ct_dd_audio_input_open_test1(ct_dd_audio_new(&temp, 3));
			break;
		case 2:
			ct_dd_audio_input_open_test1(ct_dd_audio_new(&temp, 6));
			break;
		case 3:
			ct_dd_audio_input_open_test4(ct_dd_audio_new(&temp, 0));
			break;
		case 4:
			ct_dd_audio_output_open_test1(ct_dd_audio_new(&temp, 4));
			break;
		case 5:
			ct_dd_audio_output_open_test4(ct_dd_audio_new(&temp, 0));
			break;
		case 6:
			ct_dd_audio_input_close_test(ct_dd_audio_new(&temp, 3));
			break;
		case 7:
			ct_dd_audio_input_close_test(ct_dd_audio_new(&temp, 6));
			break;
		case 8:
			ct_dd_audio_output_close_test(ct_dd_audio_new(&temp, 4));
			break;
		case 9:
			ct_dd_audio_int_handler_test1(ct_dd_audio_int_new(&temp, 6));
			break;
		case 10:
			ct_dd_audio_reset_test(ct_dd_audio_new(&temp, 6));
			break;
		case 11:
			ct_dd_audio_ctrl_common_test1(ct_dd_audio_ctrl_new(&temp, 6));
			break;
		case 12:
			ct_dd_audio_ctrl_common_test6(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 13:
			ct_dd_audio_ctrl_common_test7(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 14:
			ct_dd_audio_ctrl_common_test8(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 15:
			ct_dd_audio_ctrl_common_test9(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 16:
			ct_dd_audio_ctrl_common_test10(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 17:
			ct_dd_audio_ctrl_common_test11(ct_dd_audio_ctrl_new(&temp, 0));
			break;
		case 18:
			ct_dd_audio_get_ctrl_common_test1(ct_dd_audio_get_new(&temp, 6));
			break;
		case 19:
			ct_dd_audio_get_ctrl_common_test2(ct_dd_audio_get_new(&temp, 0));
			break;
		case 20:
			ct_dd_audio_ctrl1_input_test15(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 21:
			ct_dd_audio_ctrl1_input_test16(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 22:
			ct_dd_audio_ctrl1_input_test17(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 23:
			ct_dd_audio_ctrl1_input_test18(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 24:
			ct_dd_audio_ctrl1_input_test15(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 25:
			ct_dd_audio_ctrl1_input_test16(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 26:
			ct_dd_audio_ctrl1_input_test17(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 27:
			ct_dd_audio_ctrl1_input_test18(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 28:
			ct_dd_audio_ctrl1_input_test15(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 29:
			ct_dd_audio_ctrl1_input_test16(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 30:
			ct_dd_audio_ctrl1_input_test17(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 31:
			ct_dd_audio_ctrl1_input_test18(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 32:
			ct_dd_audio_ctrl1_input_test15(ct_dd_audio_ctrl1_new(&temp, 4));
			break;
		case 33:
			ct_dd_audio_ctrl1_input_test16(ct_dd_audio_ctrl1_new(&temp, 4));
			break;
		case 34:
			ct_dd_audio_ctrl1_input_test17(ct_dd_audio_ctrl1_new(&temp, 4));
			break;
		case 35:
			ct_dd_audio_ctrl1_input_test18(ct_dd_audio_ctrl1_new(&temp, 4));
			break;
		case 36:
			ct_dd_audio_ctrl1_input_test15(ct_dd_audio_ctrl1_new(&temp, 5));
			break;
		case 37:
			ct_dd_audio_ctrl1_input_test16(ct_dd_audio_ctrl1_new(&temp, 5));
			break;
		case 38:
			ct_dd_audio_ctrl1_input_test17(ct_dd_audio_ctrl1_new(&temp, 5));
			break;
		case 39:
			ct_dd_audio_ctrl1_input_test18(ct_dd_audio_ctrl1_new(&temp, 5));
			break;
		case 40:
			ct_dd_audio_ctrl_input_test1(ct_dd_audio_ctrl_new(&temp, 3));
			break;
		case 41:
			ct_dd_audio_ctrl_input_test1(ct_dd_audio_ctrl_new(&temp, 6));
			break;
		case 42:
			ct_dd_audio_ctrl1_input_test19(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 43:
			ct_dd_audio_ctrl1_input_test20(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 44:
			ct_dd_audio_ctrl1_input_test21(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 45:
			ct_dd_audio_ctrl1_input_test22(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 46:
			ct_dd_audio_ctrl1_input_test23(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 47:
			ct_dd_audio_get_ctrl_input_test1(ct_dd_audio_get_new(&temp, 3));
			break;
		case 48:
			ct_dd_audio_get_ctrl_input_test1(ct_dd_audio_get_new(&temp, 6));
			break;
		case 49:
			ct_dd_audio_get_ctrl_input_test2(ct_dd_audio_get_new(&temp, 0));
			break;
		case 50:
			ct_dd_audio_ctrl3_output_test29(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 51:
			ct_dd_audio_ctrl3_output_test30(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 52:
			ct_dd_audio_ctrl3_output_test31(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 53:
			ct_dd_audio_ctrl3_output_test32(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 54:
			ct_dd_audio_ctrl4_output_test33(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 55:
			ct_dd_audio_ctrl4_output_test34(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 56:
			ct_dd_audio_ctrl4_output_test35(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 57:
			ct_dd_audio_ctrl4_output_test36(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 58:
			ct_dd_audio_ctrl4_output_test37(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 59:
			ct_dd_audio_ctrl4_output_test38(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 60:
			ct_dd_audio_ctrl3_output_test29(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 61:
			ct_dd_audio_ctrl3_output_test30(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 62:
			ct_dd_audio_ctrl3_output_test31(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 63:
			ct_dd_audio_ctrl3_output_test32(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 64:
			ct_dd_audio_ctrl4_output_test33(ct_dd_audio_ctrl4_new(&temp, 1));
			break;
		case 65:
			ct_dd_audio_ctrl4_output_test34(ct_dd_audio_ctrl4_new(&temp, 1));
			break;
		case 66:
			ct_dd_audio_ctrl4_output_test35(ct_dd_audio_ctrl4_new(&temp, 1));
			break;
		case 67:
			ct_dd_audio_ctrl4_output_test36(ct_dd_audio_ctrl4_new(&temp, 1));
			break;
		case 68:
			ct_dd_audio_ctrl4_output_test37(ct_dd_audio_ctrl4_new(&temp, 1));
			break;
		case 69:
			ct_dd_audio_ctrl4_output_test38(ct_dd_audio_ctrl4_new(&temp, 1));
			break;
		case 70:
			ct_dd_audio_ctrl3_output_test29(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 71:
			ct_dd_audio_ctrl3_output_test30(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 72:
			ct_dd_audio_ctrl3_output_test31(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 73:
			ct_dd_audio_ctrl3_output_test32(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 74:
			ct_dd_audio_ctrl4_output_test33(ct_dd_audio_ctrl4_new(&temp, 2));
			break;
		case 75:
			ct_dd_audio_ctrl4_output_test34(ct_dd_audio_ctrl4_new(&temp, 2));
			break;
		case 76:
			ct_dd_audio_ctrl4_output_test35(ct_dd_audio_ctrl4_new(&temp, 2));
			break;
		case 77:
			ct_dd_audio_ctrl4_output_test36(ct_dd_audio_ctrl4_new(&temp, 2));
			break;
		case 78:
			ct_dd_audio_ctrl4_output_test37(ct_dd_audio_ctrl4_new(&temp, 2));
			break;
		case 79:
			ct_dd_audio_ctrl4_output_test38(ct_dd_audio_ctrl4_new(&temp, 2));
			break;
		case 80:
			ct_dd_audio_ctrl3_output_test29(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 81:
			ct_dd_audio_ctrl3_output_test30(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 82:
			ct_dd_audio_ctrl3_output_test31(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 83:
			ct_dd_audio_ctrl3_output_test32(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 84:
			ct_dd_audio_ctrl4_output_test33(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 85:
			ct_dd_audio_ctrl4_output_test34(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 86:
			ct_dd_audio_ctrl4_output_test35(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 87:
			ct_dd_audio_ctrl4_output_test36(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 88:
			ct_dd_audio_ctrl4_output_test37(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 89:
			ct_dd_audio_ctrl4_output_test38(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 90:
			ct_dd_audio_ctrl1_output_test1(ct_dd_audio_ctrl1_new(&temp, 4));
			break;
		case 91:
			ct_dd_audio_ctrl4_output_test39(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 92:
			ct_dd_audio_ctrl4_output_test40(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 93:
			ct_dd_audio_ctrl4_output_test41(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 94:
			ct_dd_audio_ctrl4_output_test42(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 95:
			ct_dd_audio_ctrl4_output_test43(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 96:
			ct_dd_audio_ctrl4_output_test44(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 97:
			ct_dd_audio_ctrl4_output_test45(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 98:
			ct_dd_audio_get_ctrl_output_test1(ct_dd_audio_get_new(&temp, 4));
			break;
		case 99:
			ct_dd_audio_get_ctrl_output_test2(ct_dd_audio_get_new(&temp, 0));
			break;
		case 100:
			ct_dd_audio_ctrl7_i2scmmn_test38(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 101:
			ct_dd_audio_ctrl7_i2scmmn_test39(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 102:
			ct_dd_audio_ctrl7_i2scmmn_test40(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 103:
			ct_dd_audio_ctrl7_i2scmmn_test41(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 104:
			ct_dd_audio_ctrl7_i2scmmn_test38(ct_dd_audio_ctrl7_new(&temp, 2));
			break;
		case 105:
			ct_dd_audio_ctrl7_i2scmmn_test39(ct_dd_audio_ctrl7_new(&temp, 2));
			break;
		case 106:
			ct_dd_audio_ctrl7_i2scmmn_test40(ct_dd_audio_ctrl7_new(&temp, 2));
			break;
		case 107:
			ct_dd_audio_ctrl7_i2scmmn_test41(ct_dd_audio_ctrl7_new(&temp, 2));
			break;
		case 108:
			ct_dd_audio_ctrl7_i2scmmn_test39(ct_dd_audio_ctrl7_new(&temp, 2));
			break;
		case 109:
			ct_dd_audio_ctrl7_i2scmmn_test41(ct_dd_audio_ctrl7_new(&temp, 3));
			break;
		case 110:
			ct_dd_audio_ctrl7_i2scmmn_test38(ct_dd_audio_ctrl7_new(&temp, 4));
			break;
		case 111:
			ct_dd_audio_ctrl7_i2scmmn_test40(ct_dd_audio_ctrl7_new(&temp, 4));
			break;
		case 112:
			ct_dd_audio_ctrl7_i2scmmn_test38(ct_dd_audio_ctrl7_new(&temp, 5));
			break;
		case 113:
			ct_dd_audio_ctrl7_i2scmmn_test40(ct_dd_audio_ctrl7_new(&temp, 5));
			break;
		case 114:
			ct_dd_audio_ctrl4_i2scmmn_test1(ct_dd_audio_ctrl4_new(&temp, 6));
			break;
		case 115:
			ct_dd_audio_ctrl7_i2scmmn_test42(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 116:
			ct_dd_audio_ctrl7_i2scmmn_test43(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 117:
			ct_dd_audio_ctrl7_i2scmmn_test44(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 118:
			ct_dd_audio_ctrl7_i2scmmn_test45(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 119:
			ct_dd_audio_ctrl7_i2scmmn_test46(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 120:
			ct_dd_audio_ctrl7_i2scmmn_test47(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 121:
			ct_dd_audio_ctrl7_i2scmmn_test48(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 122:
			ct_dd_audio_get_ctrl_i2scmmn_test1(ct_dd_audio_get_new(&temp, 6));
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


/*
*PUBLIC
*/

CtAudioCaseNine *ct_audio_case_nine_new(void)
{
	CtAudioCaseNine *self = g_object_new(CT_TYPE_AUDIO_CASE_NINE, NULL);
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}

