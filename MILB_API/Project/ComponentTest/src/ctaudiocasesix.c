/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseSix类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseSix类
*@version 1.0.0
*
*/

#include "ctaudiocasesix.h"

G_DEFINE_TYPE(CtAudioCaseSix, ct_audio_case_six, G_TYPE_OBJECT);
#define 	CT_AUDIO_CASE_SIX_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_AUDIO_CASE_SIX, CtAudioCaseSixPrivate))

struct _CtAudioCaseSixPrivate
{
	
};

/*
*DECLS
*/
static void ct_audio_case_six_class_init(CtAudioCaseSixClass *klass);
static void ct_audio_case_six_init(CtAudioCaseSix *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue);

/*
 * IMPL
 */
static void ct_audio_case_six_class_init(CtAudioCaseSixClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtAudioCaseSixPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_audio_case_six_init(CtAudioCaseSix *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_six_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_six_parent_class)->finalize(object);
}


//661-792
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue)
{
	gpointer temp = NULL;
	gpointer secondTemp = NULL;
	switch(caseValue)
	{
		case 661:
			ct_dd_audio_ctrl9_i2sout_test19(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 662:
			ct_dd_audio_ctrl9_i2sout_test20(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 663:
			ct_dd_audio_ctrl9_i2sout_test21(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 664:
			ct_dd_audio_ctrl9_i2sout_test22(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 665:
			ct_dd_audio_ctrl9_i2sout_test23(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 666:
			ct_dd_audio_ctrl9_i2sout_test24(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 667:
			ct_dd_audio_ctrl9_i2sout_test25(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 668:
			ct_dd_audio_ctrl9_i2sout_test26(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 669:
			ct_dd_audio_ctrl9_i2sout_test27(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 670:
			ct_dd_audio_ctrl9_i2sout_test28(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 671:
			ct_dd_audio_ctrl9_i2sout_test29(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 672:
			ct_dd_audio_ctrl9_i2sout_test30(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 673:
			ct_dd_audio_ctrl9_i2sout_test31(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 674:
			ct_dd_audio_ctrl9_i2sout_test32(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 675:
			ct_dd_audio_ctrl9_i2sout_test33(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 676:
			ct_dd_audio_ctrl9_i2sout_test34(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 677:
			ct_dd_audio_ctrl9_i2sout_test35(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 678:
			ct_dd_audio_ctrl8_i2sout_test1(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 679:
			ct_dd_audio_ctrl8_i2sout_test2(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 680:
			ct_dd_audio_ctrl8_i2sout_test3(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 681:
			ct_dd_audio_ctrl8_i2sout_test4(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 682:
			ct_dd_audio_ctrl8_i2sout_test5(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 683:
			ct_dd_audio_ctrl8_i2sout_test6(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 684:
			ct_dd_audio_ctrl8_i2sout_test7(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 685:
			ct_dd_audio_ctrl8_i2sout_test8(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 686:
			ct_dd_audio_ctrl8_i2sout_test9(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 687:
			ct_dd_audio_ctrl8_i2sout_test10(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 688:
			ct_dd_audio_ctrl8_i2sout_test11(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 689:
			ct_dd_audio_ctrl8_i2sout_test12(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 690:
			ct_dd_audio_ctrl8_i2sout_test13(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 691:
			ct_dd_audio_ctrl8_i2sout_test14(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 692:
			ct_dd_audio_ctrl8_i2sout_test15(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 693:
			ct_dd_audio_ctrl9_i2sout_test16(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 694:
			ct_dd_audio_ctrl9_i2sout_test17(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 695:
			ct_dd_audio_ctrl9_i2sout_test18(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 696:
			ct_dd_audio_ctrl9_i2sout_test19(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 697:
			ct_dd_audio_ctrl9_i2sout_test20(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 698:
			ct_dd_audio_ctrl9_i2sout_test21(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 699:
			ct_dd_audio_ctrl9_i2sout_test22(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 700:
			ct_dd_audio_ctrl9_i2sout_test23(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 701:
			ct_dd_audio_ctrl9_i2sout_test24(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 702:
			ct_dd_audio_ctrl9_i2sout_test25(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 703:
			ct_dd_audio_ctrl9_i2sout_test26(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 704:
			ct_dd_audio_ctrl9_i2sout_test27(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 705:
			ct_dd_audio_ctrl9_i2sout_test28(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 706:
			ct_dd_audio_ctrl9_i2sout_test29(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 707:
			ct_dd_audio_ctrl9_i2sout_test30(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 708:
			ct_dd_audio_ctrl9_i2sout_test31(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 709:
			ct_dd_audio_ctrl9_i2sout_test32(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 710:
			ct_dd_audio_ctrl9_i2sout_test33(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 711:
			ct_dd_audio_ctrl9_i2sout_test34(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 712:
			ct_dd_audio_ctrl9_i2sout_test35(ct_dd_audio_ctrl9_new(&temp, 2));
			break;
		case 713:
			ct_dd_audio_ctrl8_i2sout_test1(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 714:
			ct_dd_audio_ctrl8_i2sout_test2(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 715:
			ct_dd_audio_ctrl8_i2sout_test3(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 716:
			ct_dd_audio_ctrl8_i2sout_test4(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 717:
			ct_dd_audio_ctrl8_i2sout_test5(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 718:
			ct_dd_audio_ctrl8_i2sout_test6(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 719:
			ct_dd_audio_ctrl8_i2sout_test7(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 720:
			ct_dd_audio_ctrl8_i2sout_test8(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 721:
			ct_dd_audio_ctrl8_i2sout_test9(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 722:
			ct_dd_audio_ctrl8_i2sout_test10(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 723:
			ct_dd_audio_ctrl8_i2sout_test11(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 724:
			ct_dd_audio_ctrl8_i2sout_test12(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 725:
			ct_dd_audio_ctrl8_i2sout_test13(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 726:
			ct_dd_audio_ctrl8_i2sout_test14(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 727:
			ct_dd_audio_ctrl8_i2sout_test15(ct_dd_audio_ctrl8_new(&temp, 3));
			break;
		case 728:
			ct_dd_audio_ctrl9_i2sout_test16(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 729:
			ct_dd_audio_ctrl9_i2sout_test17(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 730:
			ct_dd_audio_ctrl9_i2sout_test18(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 731:
			ct_dd_audio_ctrl9_i2sout_test19(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 732:
			ct_dd_audio_ctrl9_i2sout_test20(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 733:
			ct_dd_audio_ctrl9_i2sout_test21(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 734:
			ct_dd_audio_ctrl9_i2sout_test22(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 735:
			ct_dd_audio_ctrl9_i2sout_test23(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 736:
			ct_dd_audio_ctrl9_i2sout_test24(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 737:
			ct_dd_audio_ctrl9_i2sout_test25(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 738:
			ct_dd_audio_ctrl9_i2sout_test26(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 739:
			ct_dd_audio_ctrl9_i2sout_test27(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 740:
			ct_dd_audio_ctrl9_i2sout_test28(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 741:
			ct_dd_audio_ctrl9_i2sout_test29(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 742:
			ct_dd_audio_ctrl9_i2sout_test30(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 743:
			ct_dd_audio_ctrl9_i2sout_test31(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 744:
			ct_dd_audio_ctrl9_i2sout_test32(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 745:
			ct_dd_audio_ctrl9_i2sout_test33(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 746:
			ct_dd_audio_ctrl9_i2sout_test34(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 747:
			ct_dd_audio_ctrl9_i2sout_test35(ct_dd_audio_ctrl9_new(&temp, 3));
			break;
		case 748:
			ct_dd_audio_get_ctrl_i2sout_test1(ct_dd_audio_get_new(&temp, 0));
			break;
		case 749:
			ct_dd_audio_get_ctrl_i2sout_test1(ct_dd_audio_get_new(&temp, 1));
			break;
		case 750:
			ct_dd_audio_get_ctrl_i2sout_test1(ct_dd_audio_get_new(&temp, 2));
			break;
		case 751:
			ct_dd_audio_get_ctrl_i2sout_test1(ct_dd_audio_get_new(&temp, 3));
			break;
		case 752:
			ct_dd_audio_ctrl10_dmain_test1(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 753:
			ct_dd_audio_ctrl10_dmain_test2(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 754:
			ct_dd_audio_ctrl10_dmain_test1(ct_dd_audio_ctrl10_new(&temp, 1));
			break;
		case 755:
			ct_dd_audio_ctrl10_dmain_test2(ct_dd_audio_ctrl10_new(&temp, 1));
			break;
		case 756:
			ct_dd_audio_ctrl10_dmain_test1(ct_dd_audio_ctrl10_new(&temp, 2));
			break;
		case 757:
			ct_dd_audio_ctrl10_dmain_test2(ct_dd_audio_ctrl10_new(&temp, 2));
			break;
		case 758:
			ct_dd_audio_ctrl10_dmain_test1(ct_dd_audio_ctrl10_new(&temp, 4));
			break;
		case 759:
			ct_dd_audio_ctrl10_dmain_test2(ct_dd_audio_ctrl10_new(&temp, 4));
			break;
		case 760:
			ct_dd_audio_ctrl10_dmain_test1(ct_dd_audio_ctrl10_new(&temp, 5));
			break;
		case 761:
			ct_dd_audio_ctrl10_dmain_test2(ct_dd_audio_ctrl10_new(&temp, 5));
			break;
		case 762:
			ct_dd_audio_get_ctrl_dmain_test1(ct_dd_audio_get_new(&temp, 0));
			break;
		case 763:
			ct_dd_audio_get_ctrl_dmain_test1(ct_dd_audio_get_new(&temp, 1));
			break;
		case 764:
			ct_dd_audio_get_ctrl_dmain_test1(ct_dd_audio_get_new(&temp, 2));
			break;
		case 765:
			ct_dd_audio_get_ctrl_dmain_test1(ct_dd_audio_get_new(&temp, 4));
			break;
		case 766:
			ct_dd_audio_get_ctrl_dmain_test1(ct_dd_audio_get_new(&temp, 5));
			break;
		case 767:
			ct_dd_audio_ctrl10_dmaout_test1(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 768:
			ct_dd_audio_ctrl10_dmaout_test2(ct_dd_audio_ctrl10_new(&temp, 0));
			break;
		case 769:
			ct_dd_audio_ctrl10_dmaout_test1(ct_dd_audio_ctrl10_new(&temp, 1));
			break;
		case 770:
			ct_dd_audio_ctrl10_dmaout_test2(ct_dd_audio_ctrl10_new(&temp, 1));
			break;
		case 771:
			ct_dd_audio_ctrl10_dmaout_test1(ct_dd_audio_ctrl10_new(&temp, 2));
			break;
		case 772:
			ct_dd_audio_ctrl10_dmaout_test2(ct_dd_audio_ctrl10_new(&temp, 2));
			break;
		case 773:
			ct_dd_audio_ctrl10_dmaout_test1(ct_dd_audio_ctrl10_new(&temp, 3));
			break;
		case 774:
			ct_dd_audio_ctrl10_dmaout_test2(ct_dd_audio_ctrl10_new(&temp, 3));
			break;
		case 775:
			ct_dd_audio_get_ctrl_dmaout_test1(ct_dd_audio_get_new(&temp, 0));
			break;
		case 776:
			ct_dd_audio_get_ctrl_dmaout_test1(ct_dd_audio_get_new(&temp, 1));
			break;
		case 777:
			ct_dd_audio_get_ctrl_dmaout_test1(ct_dd_audio_get_new(&temp, 2));
			break;
		case 778:
			ct_dd_audio_get_ctrl_dmaout_test1(ct_dd_audio_get_new(&temp, 3));
			break;
		case 779:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 0));
			break;
		case 780:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 2));
			break;
		case 781:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 4));
			break;
		case 782:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 5));
			break;
		case 783:
			ct_dd_audio_start_input_test_multi01(ct_dd_audio_start_new(&temp, 0));
			break;
		case 784:
			ct_dd_audio_start_input_test_multi45(ct_dd_audio_start_new(&temp, 0));
			break;
		case 785:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, 0));
			break;
		case 786:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 2));
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, 2));
			break;
		case 787:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 4));
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, 4));
			break;
		case 788:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 5));
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, 5));
			break;
		case 789:
			ct_dd_audio_start_input_test_multi01(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, DdAudio_IF_CH0_CH1));
			break;
		case 790:
			ct_dd_audio_start_input_test_multi45(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_stop_input_test(ct_dd_audio_stop_new(&secondTemp, D_DD_AUDIO_IF_CH4_CH5));
			break;
		case 791:
			ct_dd_audio_get_status_input_test(ct_dd_audio_get_new(&temp, 0));
			break;
		case 792:
			ct_dd_audio_get_status_input_test(ct_dd_audio_get_new(&temp, 1));
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

CtAudioCaseSix *ct_audio_case_six_new(void)
{
	CtAudioCaseSix *self = CT_AUDIO_CASE_SIX(g_object_new(CT_TYPE_AUDIO_CASE_SIX, NULL));
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}

