/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseEight类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、CtAudioCaseEight类
*@version 1.0.0
*
*/

#include "ctaudiocaseeight.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtAudioCaseEight, ct_audio_case_eight)
#define CT_AUDIO_CASE_EIGHT_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), \
		CtAudioCaseEightPrivate, CT_TYPE_AUDIO_CASE_EIGHT))

struct _CtAudioCaseEightPrivate
{
	
};
/*
*DECLS
*/
static void ct_audio_case_eight_constructor(CtAudioCaseEight *self);
static void ct_audio_case_eight_destructor(CtAudioCaseEight *self);
static void doWithArgs_od(AbsCtAudioCase *self, kint caseValue);

/*
 * IMPL
 */
static void ct_audio_case_eight_constructor(CtAudioCaseEight *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void ct_audio_case_eight_destructor(CtAudioCaseEight *self)
{
	self =NULL;
}

//925-1056
static void doWithArgs_od(AbsCtAudioCase *self, kint caseValue)
{
	kpointer temp = NULL;
	switch(caseValue)
	{
		case 925:
			ct_dd_audio_get_addr_reg_auidlr_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 926:
			ct_dd_audio_get_addr_reg_auidlr_test(ct_dd_audio_get_new(&temp, 5));
			break;
		case 927:
			ct_dd_audio_get_addr_reg_auodlr_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 928:
			ct_dd_audio_get_addr_reg_auodlr_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 929:
			ct_dd_audio_get_addr_reg_auodlr_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 930:
			ct_dd_audio_get_addr_reg_auodlr_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 931:
			ct_dd_audio_get_addr_reg_auidl_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 932:
			ct_dd_audio_get_addr_reg_auidl_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 933:
			ct_dd_audio_get_addr_reg_auidl_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 934:
			ct_dd_audio_get_addr_reg_auidl_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 935:
			ct_dd_audio_get_addr_reg_auidl_test(ct_dd_audio_get_new(&temp, 5));
			break;
		case 936:
			ct_dd_audio_get_addr_reg_auidr_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 937:
			ct_dd_audio_get_addr_reg_auidr_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 938:
			ct_dd_audio_get_addr_reg_auidr_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 939:
			ct_dd_audio_get_addr_reg_auidr_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 940:
			ct_dd_audio_get_addr_reg_auidr_test(ct_dd_audio_get_new(&temp, 5));
			break;
		case 941:
			ct_dd_audio_get_addr_reg_auodl_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 942:
			ct_dd_audio_get_addr_reg_auodl_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 943:
			ct_dd_audio_get_addr_reg_auodl_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 944:
			ct_dd_audio_get_addr_reg_auodl_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 945:
			ct_dd_audio_get_addr_reg_auodr_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 946:
			ct_dd_audio_get_addr_reg_auodr_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 947:
			ct_dd_audio_get_addr_reg_auodr_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 948:
			ct_dd_audio_get_addr_reg_auodr_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 949:
			ct_dd_audio_get_addr_reg_auiddmapt_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 950:
			ct_dd_audio_get_addr_reg_auiddmapt_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 951:
			ct_dd_audio_get_addr_reg_auiddmapt_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 952:
			ct_dd_audio_get_addr_reg_auiddmapt_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 953:
			ct_dd_audio_get_addr_reg_auiddmapt_test(ct_dd_audio_get_new(&temp, 5));
			break;
		case 954:
			ct_dd_audio_get_addr_reg_auoddmapt_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 955:
			ct_dd_audio_get_addr_reg_auoddmapt_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 956:
			ct_dd_audio_get_addr_reg_auoddmapt_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 957:
			ct_dd_audio_get_addr_reg_auoddmapt_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 958:
			ct_dd_audio_set2_enable_input_intr_test1(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 959:
			ct_dd_audio_set2_enable_input_intr_test2(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 960:
			ct_dd_audio_set2_enable_input_intr_test3(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 961:
			ct_dd_audio_set2_enable_input_intr_test4(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 962:
			ct_dd_audio_set2_enable_input_intr_test5(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 963:
			ct_dd_audio_set2_enable_input_intr_test6(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 964:
			ct_dd_audio_set2_enable_input_intr_test7(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 965:
			ct_dd_audio_set2_enable_input_intr_test8(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 966:
			ct_dd_audio_set2_enable_input_intr_test1(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 967:
			ct_dd_audio_set2_enable_input_intr_test2(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 968:
			ct_dd_audio_set2_enable_input_intr_test3(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 969:
			ct_dd_audio_set2_enable_input_intr_test4(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 970:
			ct_dd_audio_set2_enable_input_intr_test5(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 971:
			ct_dd_audio_set2_enable_input_intr_test6(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 972:
			ct_dd_audio_set2_enable_input_intr_test7(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 973:
			ct_dd_audio_set2_enable_input_intr_test8(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 974:
			ct_dd_audio_set2_enable_input_intr_test1(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 975:
			ct_dd_audio_set2_enable_input_intr_test2(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 976:
			ct_dd_audio_set2_enable_input_intr_test3(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 977:
			ct_dd_audio_set2_enable_input_intr_test4(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 978:
			ct_dd_audio_set2_enable_input_intr_test5(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 979:
			ct_dd_audio_set2_enable_input_intr_test6(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 980:
			ct_dd_audio_set2_enable_input_intr_test7(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 981:
			ct_dd_audio_set2_enable_input_intr_test8(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 982:
			ct_dd_audio_set2_enable_input_intr_test1(ct_dd_audio_set2_new(&temp, 4));
			break;
		case 983:
			ct_dd_audio_set2_enable_input_intr_test2(ct_dd_audio_set2_new(&temp, 4));
			break;
		case 984:
			ct_dd_audio_set2_enable_input_intr_test3(ct_dd_audio_set2_new(&temp, 4));
			break;
		case 985:
			ct_dd_audio_set2_enable_input_intr_test4(ct_dd_audio_set2_new(&temp, 4));
			break;
		case 986:
			ct_dd_audio_set2_enable_input_intr_test5(ct_dd_audio_set2_new(&temp, 4));
			break;
		case 987:
			ct_dd_audio_set2_enable_input_intr_test6(ct_dd_audio_set2_new(&temp, 4));
			break;
		case 988:
			ct_dd_audio_set2_enable_input_intr_test7(ct_dd_audio_set2_new(&temp, 4));
			break;
		case 989:
			ct_dd_audio_set2_enable_input_intr_test8(ct_dd_audio_set2_new(&temp, 4));
			break;
		case 990:
			ct_dd_audio_set2_enable_input_intr_test1(ct_dd_audio_set2_new(&temp, 5));
			break;
		case 991:
			ct_dd_audio_set2_enable_input_intr_test2(ct_dd_audio_set2_new(&temp, 5));
			break;
		case 992:
			ct_dd_audio_set2_enable_input_intr_test3(ct_dd_audio_set2_new(&temp, 5));
			break;
		case 993:
			ct_dd_audio_set2_enable_input_intr_test4(ct_dd_audio_set2_new(&temp, 5));
			break;
		case 994:
			ct_dd_audio_set2_enable_input_intr_test5(ct_dd_audio_set2_new(&temp, 5));
			break;
		case 995:
			ct_dd_audio_set2_enable_input_intr_test6(ct_dd_audio_set2_new(&temp, 5));
			break;
		case 996:
			ct_dd_audio_set2_enable_input_intr_test7(ct_dd_audio_set2_new(&temp, 5));
			break;
		case 997:
			ct_dd_audio_set2_enable_input_intr_test8(ct_dd_audio_set2_new(&temp, 5));
			break;
		case 998:
			ct_dd_audio_set2_enable_output_intr_test1(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 999:
			ct_dd_audio_set2_enable_output_intr_test2(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 1000:
			ct_dd_audio_set2_enable_output_intr_test3(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 1001:
			ct_dd_audio_set2_enable_output_intr_test4(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 1002:
			ct_dd_audio_set2_enable_output_intr_test5(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 1003:
			ct_dd_audio_set2_enable_output_intr_test6(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 1004:
			ct_dd_audio_set2_enable_output_intr_test7(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 1005:
			ct_dd_audio_set2_enable_output_intr_test8(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 1006:
			ct_dd_audio_set2_enable_output_intr_test1(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 1007:
			ct_dd_audio_set2_enable_output_intr_test2(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 1008:
			ct_dd_audio_set2_enable_output_intr_test3(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 1009:
			ct_dd_audio_set2_enable_output_intr_test4(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 1010:
			ct_dd_audio_set2_enable_output_intr_test5(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 1011:
			ct_dd_audio_set2_enable_output_intr_test6(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 1012:
			ct_dd_audio_set2_enable_output_intr_test7(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 1013:
			ct_dd_audio_set2_enable_output_intr_test8(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 1014:
			ct_dd_audio_set2_enable_output_intr_test1(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 1015:
			ct_dd_audio_set2_enable_output_intr_test2(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 1016:
			ct_dd_audio_set2_enable_output_intr_test3(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 1017:
			ct_dd_audio_set2_enable_output_intr_test4(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 1018:
			ct_dd_audio_set2_enable_output_intr_test5(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 1019:
			ct_dd_audio_set2_enable_output_intr_test6(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 1020:
			ct_dd_audio_set2_enable_output_intr_test7(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 1021:
			ct_dd_audio_set2_enable_output_intr_test8(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 1022:
			ct_dd_audio_set2_enable_output_intr_test1(ct_dd_audio_set2_new(&temp, 3));
			break;
		case 1023:
			ct_dd_audio_set2_enable_output_intr_test2(ct_dd_audio_set2_new(&temp, 3));
			break;
		case 1024:
			ct_dd_audio_set2_enable_output_intr_test3(ct_dd_audio_set2_new(&temp, 3));
			break;
		case 1025:
			ct_dd_audio_set2_enable_output_intr_test4(ct_dd_audio_set2_new(&temp, 3));
			break;
		case 1026:
			ct_dd_audio_set2_enable_output_intr_test5(ct_dd_audio_set2_new(&temp, 3));
			break;
		case 1027:
			ct_dd_audio_set2_enable_output_intr_test6(ct_dd_audio_set2_new(&temp, 3));
			break;
		case 1028:
			ct_dd_audio_set2_enable_output_intr_test7(ct_dd_audio_set2_new(&temp, 3));
			break;
		case 1029:
			ct_dd_audio_set2_enable_output_intr_test8(ct_dd_audio_set2_new(&temp, 3));
			break;
		case 1030:
			ct_dd_audio_set3_enable_in_over_flow_intr_test1(ct_dd_audio_set3_new(&temp, 0));
			break;
		case 1031:
			ct_dd_audio_set3_enable_in_over_flow_intr_test2(ct_dd_audio_set3_new(&temp, 0));
			break;
		case 1032:
			ct_dd_audio_set3_enable_in_over_flow_intr_test1(ct_dd_audio_set3_new(&temp, 1));
			break;
		case 1033:
			ct_dd_audio_set3_enable_in_over_flow_intr_test2(ct_dd_audio_set3_new(&temp, 1));
			break;
		case 1034:
			ct_dd_audio_set3_enable_in_over_flow_intr_test1(ct_dd_audio_set3_new(&temp, 2));
			break;
		case 1035:
			ct_dd_audio_set3_enable_in_over_flow_intr_test2(ct_dd_audio_set3_new(&temp, 2));
			break;
		case 1036:
			ct_dd_audio_set3_enable_in_over_flow_intr_test1(ct_dd_audio_set3_new(&temp, 4));
			break;
		case 1037:
			ct_dd_audio_set3_enable_in_over_flow_intr_test2(ct_dd_audio_set3_new(&temp, 4));
			break;
		case 1038:
			ct_dd_audio_set3_enable_in_over_flow_intr_test1(ct_dd_audio_set3_new(&temp, 5));
			break;
		case 1039:
			ct_dd_audio_set3_enable_in_over_flow_intr_test2(ct_dd_audio_set3_new(&temp, 5));
			break;
		case 1040:
			ct_dd_audio_set3_enable_out_under_flow_intr_test1(ct_dd_audio_set3_new(&temp, 0));
			break;
		case 1041:
			ct_dd_audio_set3_enable_out_under_flow_intr_test2(ct_dd_audio_set3_new(&temp, 0));
			break;
		case 1042:
			ct_dd_audio_set3_enable_out_under_flow_intr_test1(ct_dd_audio_set3_new(&temp, 1));
			break;
		case 1043:
			ct_dd_audio_set3_enable_out_under_flow_intr_test2(ct_dd_audio_set3_new(&temp, 1));
			break;
		case 1044:
			ct_dd_audio_set3_enable_out_under_flow_intr_test1(ct_dd_audio_set3_new(&temp, 2));
			break;
		case 1045:
			ct_dd_audio_set3_enable_out_under_flow_intr_test2(ct_dd_audio_set3_new(&temp, 2));
			break;
		case 1046:
			ct_dd_audio_set3_enable_out_under_flow_intr_test1(ct_dd_audio_set3_new(&temp, 3));
			break;
		case 1047:
			ct_dd_audio_set3_enable_out_under_flow_intr_test2(ct_dd_audio_set3_new(&temp, 3));
			break;
		case 1048:
			ct_dd_audio_get_input_fifo_status_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 1049:
			ct_dd_audio_get_input_fifo_status_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 1050:
			ct_dd_audio_get_input_fifo_status_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 1051:
			ct_dd_audio_get_input_fifo_status_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 1052:
			ct_dd_audio_get_input_fifo_status_test(ct_dd_audio_get_new(&temp, 5));
			break;
		case 1053:
			ct_dd_audio_get_output_fifo_status_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 1054:
			ct_dd_audio_get_output_fifo_status_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 1055:
			ct_dd_audio_get_output_fifo_status_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 1056:
			ct_dd_audio_get_output_fifo_status_test(ct_dd_audio_get_new(&temp, 3));
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

CtAudioCaseEight *ct_audio_case_eight_new(void)
{
	CtAudioCaseEight *self = k_object_new(CT_TYPE_AUDIO_CASE_EIGHT);
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}

