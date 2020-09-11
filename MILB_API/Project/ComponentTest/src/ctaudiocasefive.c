/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseFive类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseFive类
*@version 1.0.0
*
*/

#include "ctaudiocasefive.h"

G_DEFINE_TYPE(CtAudioCaseFive, ct_audio_case_five, G_TYPE_OBJECT);
#define 	CT_AUDIO_CASE_FIVE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_AUDIO_CASE_FIVE, CtAudioCaseFivePrivate))

struct _CtAudioCaseFivePrivate
{
	
};

/*
*DECLS
*/
static void ct_audio_case_five_class_init(CtAudioCaseFiveClass *klass);
static void ct_audio_case_five_init(CtAudioCaseFive *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue);

/*
 * IMPL
 */
static void ct_audio_case_five_class_init(CtAudioCaseFiveClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtAudioCaseFivePrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_audio_case_five_init(CtAudioCaseFive *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_five_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_five_parent_class)->finalize(object);
}


//529-660
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue)
{
	gpointer temp = NULL;
	switch(caseValue)
	{
		case 529:
			ct_dd_audio_ctrl5_i2scmmn_test14(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 530:
			ct_dd_audio_ctrl5_i2scmmn_test15(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 531:
			ct_dd_audio_ctrl5_i2scmmn_test16(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 532:
			ct_dd_audio_ctrl5_i2scmmn_test17(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 533:
			ct_dd_audio_ctrl5_i2scmmn_test18(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 534:
			ct_dd_audio_ctrl5_i2scmmn_test19(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 535:
			ct_dd_audio_ctrl5_i2scmmn_test20(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 536:
			ct_dd_audio_ctrl5_i2scmmn_test21(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 537:
			ct_dd_audio_ctrl5_i2scmmn_test22(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 538:
			ct_dd_audio_ctrl6_i2scmmn_test23(ct_dd_audio_ctrl6_new(&temp, 5));
			break;
		case 539:
			ct_dd_audio_ctrl6_i2scmmn_test24(ct_dd_audio_ctrl6_new(&temp, 5));
			break;
		case 540:
			ct_dd_audio_ctrl6_i2scmmn_test25(ct_dd_audio_ctrl6_new(&temp, 5));
			break;
		case 541:
			ct_dd_audio_ctrl6_i2scmmn_test26(ct_dd_audio_ctrl6_new(&temp, 5));
			break;
		case 542:
			ct_dd_audio_ctrl6_i2scmmn_test27(ct_dd_audio_ctrl6_new(&temp, 5));
			break;
		case 543:
			ct_dd_audio_ctrl6_i2scmmn_test30(ct_dd_audio_ctrl6_new(&temp, 5));
			break;
		case 544:
			ct_dd_audio_ctrl6_i2scmmn_test31(ct_dd_audio_ctrl6_new(&temp, 5));
			break;
		case 545:
			ct_dd_audio_ctrl6_i2scmmn_test32(ct_dd_audio_ctrl6_new(&temp, 5));
			break;
		case 546:
			ct_dd_audio_ctrl7_i2scmmn_test35(ct_dd_audio_ctrl7_new(&temp, 5));
			break;
		case 547:
			ct_dd_audio_get_ctrl_i2scmmn_test1(ct_dd_audio_get_new(&temp, 0));
			break;
		case 548:
			ct_dd_audio_get_ctrl_i2scmmn_test1(ct_dd_audio_get_new(&temp, 1));
			break;
		case 549:
			ct_dd_audio_get_ctrl_i2scmmn_test1(ct_dd_audio_get_new(&temp, 2));
			break;
		case 550:
			ct_dd_audio_get_ctrl_i2scmmn_test1(ct_dd_audio_get_new(&temp, 3));
			break;
		case 551:
			ct_dd_audio_get_ctrl_i2scmmn_test1(ct_dd_audio_get_new(&temp, 4));
			break;
		case 552:
			ct_dd_audio_get_ctrl_i2scmmn_test1(ct_dd_audio_get_new(&temp, 5));
			break;
		case 553:
			ct_dd_audio_ctrl8_i2sin_test1(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 554:
			ct_dd_audio_ctrl8_i2sin_test2(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 555:
			ct_dd_audio_ctrl8_i2sin_test3(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 556:
			ct_dd_audio_ctrl8_i2sin_test4(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 557:
			ct_dd_audio_ctrl8_i2sin_test5(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 558:
			ct_dd_audio_ctrl8_i2sin_test6(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 559:
			ct_dd_audio_ctrl8_i2sin_test7(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 560:
			ct_dd_audio_ctrl8_i2sin_test8(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 561:
			ct_dd_audio_ctrl8_i2sin_test9(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 562:
			ct_dd_audio_ctrl8_i2sin_test10(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 563:
			ct_dd_audio_ctrl8_i2sin_test1(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 564:
			ct_dd_audio_ctrl8_i2sin_test2(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 565:
			ct_dd_audio_ctrl8_i2sin_test3(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 566:
			ct_dd_audio_ctrl8_i2sin_test4(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 567:
			ct_dd_audio_ctrl8_i2sin_test5(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 568:
			ct_dd_audio_ctrl8_i2sin_test6(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 569:
			ct_dd_audio_ctrl8_i2sin_test7(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 570:
			ct_dd_audio_ctrl8_i2sin_test8(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 571:
			ct_dd_audio_ctrl8_i2sin_test9(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 572:
			ct_dd_audio_ctrl8_i2sin_test10(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 573:
			ct_dd_audio_ctrl8_i2sin_test1(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 574:
			ct_dd_audio_ctrl8_i2sin_test2(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 575:
			ct_dd_audio_ctrl8_i2sin_test3(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 576:
			ct_dd_audio_ctrl8_i2sin_test4(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 577:
			ct_dd_audio_ctrl8_i2sin_test5(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 578:
			ct_dd_audio_ctrl8_i2sin_test6(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 579:
			ct_dd_audio_ctrl8_i2sin_test7(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 580:
			ct_dd_audio_ctrl8_i2sin_test8(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 581:
			ct_dd_audio_ctrl8_i2sin_test9(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 582:
			ct_dd_audio_ctrl8_i2sin_test10(ct_dd_audio_ctrl8_new(&temp, 2));
			break;
		case 583:
			ct_dd_audio_ctrl8_i2sin_test1(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 584:
			ct_dd_audio_ctrl8_i2sin_test2(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 585:
			ct_dd_audio_ctrl8_i2sin_test3(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 586:
			ct_dd_audio_ctrl8_i2sin_test4(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 587:
			ct_dd_audio_ctrl8_i2sin_test5(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 588:
			ct_dd_audio_ctrl8_i2sin_test6(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 589:
			ct_dd_audio_ctrl8_i2sin_test7(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 590:
			ct_dd_audio_ctrl8_i2sin_test8(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 591:
			ct_dd_audio_ctrl8_i2sin_test9(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 592:
			ct_dd_audio_ctrl8_i2sin_test10(ct_dd_audio_ctrl8_new(&temp, 4));
			break;
		case 593:
			ct_dd_audio_ctrl8_i2sin_test1(ct_dd_audio_ctrl8_new(&temp, 5));
			break;
		case 594:
			ct_dd_audio_ctrl8_i2sin_test2(ct_dd_audio_ctrl8_new(&temp, 5));
			break;
		case 595:
			ct_dd_audio_ctrl8_i2sin_test3(ct_dd_audio_ctrl8_new(&temp, 5));
			break;
		case 596:
			ct_dd_audio_ctrl8_i2sin_test4(ct_dd_audio_ctrl8_new(&temp, 5));
			break;
		case 597:
			ct_dd_audio_ctrl8_i2sin_test5(ct_dd_audio_ctrl8_new(&temp, 5));
			break;
		case 598:
			ct_dd_audio_ctrl8_i2sin_test6(ct_dd_audio_ctrl8_new(&temp, 5));
			break;
		case 599:
			ct_dd_audio_ctrl8_i2sin_test7(ct_dd_audio_ctrl8_new(&temp, 5));
			break;
		case 600:
			ct_dd_audio_ctrl8_i2sin_test8(ct_dd_audio_ctrl8_new(&temp, 5));
			break;
		case 601:
			ct_dd_audio_ctrl8_i2sin_test9(ct_dd_audio_ctrl8_new(&temp, 5));
			break;
		case 602:
			ct_dd_audio_ctrl8_i2sin_test10(ct_dd_audio_ctrl8_new(&temp, 5));
			break;
		case 603:
			ct_dd_audio_get_ctrl_i2sin_test1(ct_dd_audio_get_new(&temp, 0));
			break;
		case 604:
			ct_dd_audio_get_ctrl_i2sin_test1(ct_dd_audio_get_new(&temp, 1));
			break;
		case 605:
			ct_dd_audio_get_ctrl_i2sin_test1(ct_dd_audio_get_new(&temp, 2));
			break;
		case 606:
			ct_dd_audio_get_ctrl_i2sin_test1(ct_dd_audio_get_new(&temp, 4));
			break;
		case 607:
			ct_dd_audio_get_ctrl_i2sin_test1(ct_dd_audio_get_new(&temp, 5));
			break;
		case 608:
			ct_dd_audio_ctrl8_i2sout_test1(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 609:
			ct_dd_audio_ctrl8_i2sout_test2(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 610:
			ct_dd_audio_ctrl8_i2sout_test3(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 611:
			ct_dd_audio_ctrl8_i2sout_test4(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 612:
			ct_dd_audio_ctrl8_i2sout_test5(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 613:
			ct_dd_audio_ctrl8_i2sout_test6(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 614:
			ct_dd_audio_ctrl8_i2sout_test7(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 615:
			ct_dd_audio_ctrl8_i2sout_test8(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 616:
			ct_dd_audio_ctrl8_i2sout_test9(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 617:
			ct_dd_audio_ctrl8_i2sout_test10(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 618:
			ct_dd_audio_ctrl8_i2sout_test11(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 619:
			ct_dd_audio_ctrl8_i2sout_test12(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 620:
			ct_dd_audio_ctrl8_i2sout_test13(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 621:
			ct_dd_audio_ctrl8_i2sout_test14(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 622:
			ct_dd_audio_ctrl8_i2sout_test15(ct_dd_audio_ctrl8_new(&temp, 0));
			break;
		case 623:
			ct_dd_audio_ctrl9_i2sout_test16(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 624:
			ct_dd_audio_ctrl9_i2sout_test17(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 625:
			ct_dd_audio_ctrl9_i2sout_test18(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 626:
			ct_dd_audio_ctrl9_i2sout_test19(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 627:
			ct_dd_audio_ctrl9_i2sout_test20(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 628:
			ct_dd_audio_ctrl9_i2sout_test21(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 629:
			ct_dd_audio_ctrl9_i2sout_test22(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 630:
			ct_dd_audio_ctrl9_i2sout_test23(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 631:
			ct_dd_audio_ctrl9_i2sout_test24(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 632:
			ct_dd_audio_ctrl9_i2sout_test25(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 633:
			ct_dd_audio_ctrl9_i2sout_test26(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 634:
			ct_dd_audio_ctrl9_i2sout_test27(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 635:
			ct_dd_audio_ctrl9_i2sout_test28(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 636:
			ct_dd_audio_ctrl9_i2sout_test29(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 637:
			ct_dd_audio_ctrl9_i2sout_test30(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 638:
			ct_dd_audio_ctrl9_i2sout_test31(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 639:
			ct_dd_audio_ctrl9_i2sout_test32(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 640:
			ct_dd_audio_ctrl9_i2sout_test33(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 641:
			ct_dd_audio_ctrl9_i2sout_test34(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 642:
			ct_dd_audio_ctrl9_i2sout_test35(ct_dd_audio_ctrl9_new(&temp, 0));
			break;
		case 643:
			ct_dd_audio_ctrl8_i2sout_test1(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 644:
			ct_dd_audio_ctrl8_i2sout_test2(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 645:
			ct_dd_audio_ctrl8_i2sout_test3(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 646:
			ct_dd_audio_ctrl8_i2sout_test4(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 647:
			ct_dd_audio_ctrl8_i2sout_test5(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 648:
			ct_dd_audio_ctrl8_i2sout_test6(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 649:
			ct_dd_audio_ctrl8_i2sout_test7(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 650:
			ct_dd_audio_ctrl8_i2sout_test8(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 651:
			ct_dd_audio_ctrl8_i2sout_test9(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 652:
			ct_dd_audio_ctrl8_i2sout_test10(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 653:
			ct_dd_audio_ctrl8_i2sout_test11(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 654:
			ct_dd_audio_ctrl8_i2sout_test12(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 655:
			ct_dd_audio_ctrl8_i2sout_test13(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 656:
			ct_dd_audio_ctrl8_i2sout_test14(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 657:
			ct_dd_audio_ctrl8_i2sout_test15(ct_dd_audio_ctrl8_new(&temp, 1));
			break;
		case 658:
			ct_dd_audio_ctrl9_i2sout_test16(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 659:
			ct_dd_audio_ctrl9_i2sout_test17(ct_dd_audio_ctrl9_new(&temp, 1));
			break;
		case 660:
			ct_dd_audio_ctrl9_i2sout_test18(ct_dd_audio_ctrl9_new(&temp, 1));
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

CtAudioCaseFive *ct_audio_case_five_new(void)
{
	CtAudioCaseFive *self = CT_AUDIO_CASE_FIVE(g_object_new(CT_TYPE_AUDIO_CASE_FIVE, NULL));
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}

