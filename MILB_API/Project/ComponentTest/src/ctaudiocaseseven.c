/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseSeven类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseSeven类
*@version 1.0.0
*
*/

#include "ctaudiocaseseven.h"

G_DEFINE_TYPE(CtAudioCaseSeven, ct_audio_case_seven, G_TYPE_OBJECT);
#define 	CT_AUDIO_CASE_SEVEN_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_AUDIO_CASE_SEVEN, CtAudioCaseSevenPrivate))

struct _CtAudioCaseSevenPrivate
{
	
};

/*
*DECLS
*/
static void ct_audio_case_seven_class_init(CtAudioCaseSevenClass *klass);
static void ct_audio_case_seven_init(CtAudioCaseSeven *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue);

/*
 * IMPL
 */
static void ct_audio_case_seven_class_init(CtAudioCaseSevenClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtAudioCaseSevenPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_audio_case_seven_init(CtAudioCaseSeven *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_seven_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_seven_parent_class)->finalize(object);
}


//793-924
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue)
{
	gpointer temp = NULL;
	gpointer secondTemp = NULL;
	switch(caseValue)
	{
		case 793:
			ct_dd_audio_get_status_input_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 794:
			ct_dd_audio_get_status_input_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 795:
			ct_dd_audio_get_status_input_test(ct_dd_audio_get_new(&temp, 5));
			break;
		case 796:
			ct_dd_audio_start_output_test1(ct_dd_audio_start_new(&temp, 0));
			break;
		case 797:
			ct_dd_audio_start_output_test1(ct_dd_audio_start_new(&temp, 2));
			break;
		case 798:
			ct_dd_audio_start_output_test1(ct_dd_audio_start_new(&temp, 3));
			break;
		case 799:
			ct_dd_audio_start_output_test_multi(ct_dd_audio_start_new(&temp, 0));
			break;
		case 800:
			ct_dd_audio_start_output_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_stop_output_test(ct_dd_audio_stop_new(&secondTemp, 0));
			break;
		case 801:
			ct_dd_audio_start_output_test1(ct_dd_audio_start_new(&temp, 2));
			ct_dd_audio_stop_output_test(ct_dd_audio_stop_new(&secondTemp, 2));
			break;
		case 802:
			ct_dd_audio_start_output_test1(ct_dd_audio_start_new(&temp, 3));
			ct_dd_audio_stop_output_test(ct_dd_audio_stop_new(&secondTemp, 3));
			break;
		case 803:
			ct_dd_audio_start_output_test_multi(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_stop_output_test(ct_dd_audio_stop_new(&secondTemp, DdAudio_IF_CH0_CH1));
			break;
		case 804:
			ct_dd_audio_get_status_output_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 805:
			ct_dd_audio_get_status_output_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 806:
			ct_dd_audio_get_status_output_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 807:
			ct_dd_audio_get_status_output_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 808:
			ct_dd_audio_start_loop_back_test1(ct_dd_audio_start_new(&temp, 0));
			break;
		case 809:
			ct_dd_audio_start_loop_back_test1(ct_dd_audio_start_new(&temp, 2));
			break;
		case 810:
			ct_dd_audio_start_loop_back_test_multi(ct_dd_audio_start_new(&temp, 0));
			break;
		case 811:
			ct_dd_audio_start_loop_back_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_stop_loop_back_test(ct_dd_audio_stop_new(&secondTemp, 0));
			break;
		case 812:
			ct_dd_audio_start_loop_back_test1(ct_dd_audio_start_new(&temp, 2));
			ct_dd_audio_stop_loop_back_test(ct_dd_audio_stop_new(&secondTemp, 2));
			break;
		case 813:
			ct_dd_audio_start_loop_back_test_multi(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_stop_loop_back_test(ct_dd_audio_stop_new(&secondTemp, DdAudio_IF_CH0_CH1));
			break;
		case 814:
			ct_dd_audio_get_status_loop_back_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 815:
			ct_dd_audio_get_status_loop_back_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 816:
			ct_dd_audio_get_status_loop_back_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 817:
			ct_dd_audio_set_enable_fifo_full_dmain_test1(ct_dd_audio_set_new(&temp, 0));
			break;
		case 818:
			ct_dd_audio_set_enable_fifo_full_dmain_test2(ct_dd_audio_set_new(&temp, 0));
			break;
		case 819:
			ct_dd_audio_set_enable_fifo_full_dmain_test1(ct_dd_audio_set_new(&temp, 1));
			break;
		case 820:
			ct_dd_audio_set_enable_fifo_full_dmain_test2(ct_dd_audio_set_new(&temp, 1));
			break;
		case 821:
			ct_dd_audio_set_enable_fifo_full_dmain_test1(ct_dd_audio_set_new(&temp, 2));
			break;
		case 822:
			ct_dd_audio_set_enable_fifo_full_dmain_test2(ct_dd_audio_set_new(&temp, 2));
			break;
		case 823:
			ct_dd_audio_set_enable_fifo_full_dmain_test1(ct_dd_audio_set_new(&temp, 4));
			break;
		case 824:
			ct_dd_audio_set_enable_fifo_full_dmain_test2(ct_dd_audio_set_new(&temp, 4));
			break;
		case 825:
			ct_dd_audio_set_enable_fifo_full_dmain_test1(ct_dd_audio_set_new(&temp, 5));
			break;
		case 826:
			ct_dd_audio_set_enable_fifo_full_dmain_test2(ct_dd_audio_set_new(&temp, 5));
			break;
		case 827:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test1(ct_dd_audio_set_new(&temp, 0));
			break;
		case 828:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test2(ct_dd_audio_set_new(&temp, 0));
			break;
		case 829:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test1(ct_dd_audio_set_new(&temp, 1));
			break;
		case 830:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test2(ct_dd_audio_set_new(&temp, 1));
			break;
		case 831:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test1(ct_dd_audio_set_new(&temp, 2));
			break;
		case 832:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test2(ct_dd_audio_set_new(&temp, 2));
			break;
		case 833:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test1(ct_dd_audio_set_new(&temp, 3));
			break;
		case 834:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test2(ct_dd_audio_set_new(&temp, 3));
			break;
		case 835:
			ct_dd_audio_set_input_dmarequest_enable_test1(ct_dd_audio_set_new(&temp, 0));
			break;
		case 836:
			ct_dd_audio_set_input_dmarequest_enable_test2(ct_dd_audio_set_new(&temp, 0));
			break;
		case 837:
			ct_dd_audio_set_input_dmarequest_enable_test1(ct_dd_audio_set_new(&temp, 1));
			break;
		case 838:
			ct_dd_audio_set_input_dmarequest_enable_test2(ct_dd_audio_set_new(&temp, 1));
			break;
		case 839:
			ct_dd_audio_set_input_dmarequest_enable_test1(ct_dd_audio_set_new(&temp, 2));
			break;
		case 840:
			ct_dd_audio_set_input_dmarequest_enable_test2(ct_dd_audio_set_new(&temp, 2));
			break;
		case 841:
			ct_dd_audio_set_input_dmarequest_enable_test1(ct_dd_audio_set_new(&temp, 4));
			break;
		case 842:
			ct_dd_audio_set_input_dmarequest_enable_test2(ct_dd_audio_set_new(&temp, 4));
			break;
		case 843:
			ct_dd_audio_set_input_dmarequest_enable_test1(ct_dd_audio_set_new(&temp, 5));
			break;
		case 844:
			ct_dd_audio_set_input_dmarequest_enable_test2(ct_dd_audio_set_new(&temp, 5));
			break;
		case 845:
			ct_dd_audio_set_output_dmarequest_enable_test1(ct_dd_audio_set_new(&temp, 0));
			break;
		case 846:
			ct_dd_audio_set_output_dmarequest_enable_test2(ct_dd_audio_set_new(&temp, 0));
			break;
		case 847:
			ct_dd_audio_set_output_dmarequest_enable_test1(ct_dd_audio_set_new(&temp, 1));
			break;
		case 848:
			ct_dd_audio_set_output_dmarequest_enable_test2(ct_dd_audio_set_new(&temp, 1));
			break;
		case 849:
			ct_dd_audio_set_output_dmarequest_enable_test1(ct_dd_audio_set_new(&temp, 2));
			break;
		case 850:
			ct_dd_audio_set_output_dmarequest_enable_test2(ct_dd_audio_set_new(&temp, 2));
			break;
		case 851:
			ct_dd_audio_set_output_dmarequest_enable_test1(ct_dd_audio_set_new(&temp, 3));
			break;
		case 852:
			ct_dd_audio_set_output_dmarequest_enable_test2(ct_dd_audio_set_new(&temp, 3));
			break;
		case 853:
			ct_dd_audio_get_in_dmasample_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 854:
			ct_dd_audio_get_in_dmasample_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 855:
			ct_dd_audio_get_in_dmasample_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 856:
			ct_dd_audio_get_in_dmasample_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 857:
			ct_dd_audio_get_in_dmasample_test(ct_dd_audio_get_new(&temp, 5));
			break;
		case 858:
			ct_dd_audio_get_out_dmasample_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 859:
			ct_dd_audio_get_out_dmasample_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 860:
			ct_dd_audio_get_out_dmasample_test(ct_dd_audio_get_new(&temp, 2));
			break;
		case 861:
			ct_dd_audio_get_out_dmasample_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 862:
			ct_dd_audio_set_swaphw_auidlr_test1(ct_dd_audio_set_new(&temp, 0));
			break;
		case 863:
			ct_dd_audio_set_swaphw_auidlr_test2(ct_dd_audio_set_new(&temp, 0));
			break;
		case 864:
			ct_dd_audio_set_swaphw_auidlr_test3(ct_dd_audio_set_new(&temp, 0));
			break;
		case 865:
			ct_dd_audio_set_swaphw_auidlr_test1(ct_dd_audio_set_new(&temp, 1));
			break;
		case 866:
			ct_dd_audio_set_swaphw_auidlr_test2(ct_dd_audio_set_new(&temp, 1));
			break;
		case 867:
			ct_dd_audio_set_swaphw_auidlr_test3(ct_dd_audio_set_new(&temp, 1));
			break;
		case 868:
			ct_dd_audio_set_swaphw_auidlr_test1(ct_dd_audio_set_new(&temp, 2));
			break;
		case 869:
			ct_dd_audio_set_swaphw_auidlr_test2(ct_dd_audio_set_new(&temp, 2));
			break;
		case 870:
			ct_dd_audio_set_swaphw_auidlr_test3(ct_dd_audio_set_new(&temp, 2));
			break;
		case 871:
			ct_dd_audio_set_swaphw_auidlr_test1(ct_dd_audio_set_new(&temp, 4));
			break;
		case 872:
			ct_dd_audio_set_swaphw_auidlr_test2(ct_dd_audio_set_new(&temp, 4));
			break;
		case 873:
			ct_dd_audio_set_swaphw_auidlr_test3(ct_dd_audio_set_new(&temp, 4));
			break;
		case 874:
			ct_dd_audio_set_swaphw_auidlr_test1(ct_dd_audio_set_new(&temp, 5));
			break;
		case 875:
			ct_dd_audio_set_swaphw_auidlr_test2(ct_dd_audio_set_new(&temp, 5));
			break;
		case 876:
			ct_dd_audio_set_swaphw_auidlr_test3(ct_dd_audio_set_new(&temp, 5));
			break;
		case 877:
			ct_dd_audio_set_swapbyte_auidlr_test1(ct_dd_audio_set_new(&temp, 0));
			break;
		case 878:
			ct_dd_audio_set_swapbyte_auidlr_test2(ct_dd_audio_set_new(&temp, 0));
			break;
		case 879:
			ct_dd_audio_set_swapbyte_auidlr_test3(ct_dd_audio_set_new(&temp, 0));
			break;
		case 880:
			ct_dd_audio_set_swapbyte_auidlr_test1(ct_dd_audio_set_new(&temp, 1));
			break;
		case 881:
			ct_dd_audio_set_swapbyte_auidlr_test2(ct_dd_audio_set_new(&temp, 1));
			break;
		case 882:
			ct_dd_audio_set_swapbyte_auidlr_test3(ct_dd_audio_set_new(&temp, 1));
			break;
		case 883:
			ct_dd_audio_set_swapbyte_auidlr_test1(ct_dd_audio_set_new(&temp, 2));
			break;
		case 884:
			ct_dd_audio_set_swapbyte_auidlr_test2(ct_dd_audio_set_new(&temp, 2));
			break;
		case 885:
			ct_dd_audio_set_swapbyte_auidlr_test3(ct_dd_audio_set_new(&temp, 2));
			break;
		case 886:
			ct_dd_audio_set_swapbyte_auidlr_test1(ct_dd_audio_set_new(&temp, 4));
			break;
		case 887:
			ct_dd_audio_set_swapbyte_auidlr_test2(ct_dd_audio_set_new(&temp, 4));
			break;
		case 888:
			ct_dd_audio_set_swapbyte_auidlr_test3(ct_dd_audio_set_new(&temp, 4));
			break;
		case 889:
			ct_dd_audio_set_swapbyte_auidlr_test1(ct_dd_audio_set_new(&temp, 5));
			break;
		case 890:
			ct_dd_audio_set_swapbyte_auidlr_test2(ct_dd_audio_set_new(&temp, 5));
			break;
		case 891:
			ct_dd_audio_set_swapbyte_auidlr_test3(ct_dd_audio_set_new(&temp, 5));
			break;
		case 892:
			ct_dd_audio_set1_swaphw_auodlr_test1(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 893:
			ct_dd_audio_set1_swaphw_auodlr_test2(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 894:
			ct_dd_audio_set1_swaphw_auodlr_test3(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 895:
			ct_dd_audio_set1_swaphw_auodlr_test4(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 896:
			ct_dd_audio_set1_swaphw_auodlr_test1(ct_dd_audio_set1_new(&temp, 1));
			break;
		case 897:
			ct_dd_audio_set1_swaphw_auodlr_test2(ct_dd_audio_set1_new(&temp, 1));
			break;
		case 898:
			ct_dd_audio_set1_swaphw_auodlr_test3(ct_dd_audio_set1_new(&temp, 1));
			break;
		case 899:
			ct_dd_audio_set1_swaphw_auodlr_test4(ct_dd_audio_set1_new(&temp, 1));
			break;
		case 900:
			ct_dd_audio_set1_swaphw_auodlr_test1(ct_dd_audio_set1_new(&temp, 2));
			break;
		case 901:
			ct_dd_audio_set1_swaphw_auodlr_test2(ct_dd_audio_set1_new(&temp, 2));
			break;
		case 902:
			ct_dd_audio_set1_swaphw_auodlr_test3(ct_dd_audio_set1_new(&temp, 2));
			break;
		case 903:
			ct_dd_audio_set1_swaphw_auodlr_test4(ct_dd_audio_set1_new(&temp, 2));
			break;
		case 904:
			ct_dd_audio_set1_swaphw_auodlr_test1(ct_dd_audio_set1_new(&temp, 3));
			break;
		case 905:
			ct_dd_audio_set1_swaphw_auodlr_test2(ct_dd_audio_set1_new(&temp, 3));
			break;
		case 906:
			ct_dd_audio_set1_swaphw_auodlr_test3(ct_dd_audio_set1_new(&temp, 3));
			break;
		case 907:
			ct_dd_audio_set1_swapbyte_auodlr_test1(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 908:
			ct_dd_audio_set1_swapbyte_auodlr_test2(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 909:
			ct_dd_audio_set1_swapbyte_auodlr_test3(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 910:
			ct_dd_audio_set1_swapbyte_auodlr_test4(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 911:
			ct_dd_audio_set1_swapbyte_auodlr_test1(ct_dd_audio_set1_new(&temp, 1));
			break;
		case 912:
			ct_dd_audio_set1_swapbyte_auodlr_test2(ct_dd_audio_set1_new(&temp, 1));
			break;
		case 913:
			ct_dd_audio_set1_swapbyte_auodlr_test3(ct_dd_audio_set1_new(&temp, 1));
			break;
		case 914:
			ct_dd_audio_set1_swapbyte_auodlr_test4(ct_dd_audio_set1_new(&temp, 1));
			break;
		case 915:
			ct_dd_audio_set1_swapbyte_auodlr_test1(ct_dd_audio_set1_new(&temp, 2));
			break;
		case 916:
			ct_dd_audio_set1_swapbyte_auodlr_test2(ct_dd_audio_set1_new(&temp, 2));
			break;
		case 917:
			ct_dd_audio_set1_swapbyte_auodlr_test3(ct_dd_audio_set1_new(&temp, 2));
			break;
		case 918:
			ct_dd_audio_set1_swapbyte_auodlr_test4(ct_dd_audio_set1_new(&temp, 2));
			break;
		case 919:
			ct_dd_audio_set1_swapbyte_auodlr_test1(ct_dd_audio_set1_new(&temp, 3));
			break;
		case 920:
			ct_dd_audio_set1_swapbyte_auodlr_test2(ct_dd_audio_set1_new(&temp, 3));
			break;
		case 921:
			ct_dd_audio_set1_swapbyte_auodlr_test3(ct_dd_audio_set1_new(&temp, 3));
			break;
		case 922:
			ct_dd_audio_get_addr_reg_auidlr_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 923:
			ct_dd_audio_get_addr_reg_auidlr_test(ct_dd_audio_get_new(&temp, 1));
			break;
		case 924:
			ct_dd_audio_get_addr_reg_auidlr_test(ct_dd_audio_get_new(&temp, 2));
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

	if(secondTemp)
	{
		k_object_unref(secondTemp);
		secondTemp = NULL;
	}
}

/*
*PUBLIC
*/

CtAudioCaseSeven *ct_audio_case_seven_new(void)
{
	CtAudioCaseSeven *self = CT_AUDIO_CASE_SEVEN(g_object_new(CT_TYPE_AUDIO_CASE_SEVEN, NULL));
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}

