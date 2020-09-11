/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseFour类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseFour类
*@version 1.0.0
*
*/

#include "ctaudiocasefour.h"

G_DEFINE_TYPE(CtAudioCaseFour, ct_audio_case_four, G_TYPE_OBJECT);
#define 	CT_AUDIO_CASE_FOUR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
				CT_TYPE_AUDIO_CASE_FOUR, CtAudioCaseFourPrivate))

struct _CtAudioCaseFourPrivate
{
	
};

/*
*DECLS
*/
static void ct_audio_case_four_class_init(CtAudioCaseFourClass *klass);
static void ct_audio_case_four_init(CtAudioCaseFour *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue);

/*
 * IMPL
 */
static void ct_audio_case_four_class_init(CtAudioCaseFourClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtAudioCaseFourPrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_audio_case_four_init(CtAudioCaseFour *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_four_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_four_parent_class)->finalize(object);
}

//397-528
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue)
{
	gpointer temp = NULL;
	switch(caseValue)
	{
		case 397:
			ct_dd_audio_ctrl5_i2scmmn_test13(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 398:
			ct_dd_audio_ctrl5_i2scmmn_test14(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 399:
			ct_dd_audio_ctrl5_i2scmmn_test15(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 400:
			ct_dd_audio_ctrl5_i2scmmn_test16(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 401:
			ct_dd_audio_ctrl5_i2scmmn_test17(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 402:
			ct_dd_audio_ctrl5_i2scmmn_test18(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 403:
			ct_dd_audio_ctrl5_i2scmmn_test19(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 404:
			ct_dd_audio_ctrl5_i2scmmn_test20(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 405:
			ct_dd_audio_ctrl5_i2scmmn_test21(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 406:
			ct_dd_audio_ctrl5_i2scmmn_test22(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 407:
			ct_dd_audio_ctrl6_i2scmmn_test23(ct_dd_audio_ctrl6_new(&temp, 0));
			break;
		case 408:
			ct_dd_audio_ctrl6_i2scmmn_test24(ct_dd_audio_ctrl6_new(&temp, 0));
			break;
		case 409:
			ct_dd_audio_ctrl6_i2scmmn_test25(ct_dd_audio_ctrl6_new(&temp, 0));
			break;
		case 410:
			ct_dd_audio_ctrl6_i2scmmn_test26(ct_dd_audio_ctrl6_new(&temp, 0));
			break;
		case 411:
			ct_dd_audio_ctrl6_i2scmmn_test27(ct_dd_audio_ctrl6_new(&temp, 0));
			break;
		case 412:
			ct_dd_audio_ctrl6_i2scmmn_test28(ct_dd_audio_ctrl6_new(&temp, 0));
			break;
		case 413:
			ct_dd_audio_ctrl6_i2scmmn_test29(ct_dd_audio_ctrl6_new(&temp, 0));
			break;
		case 414:
			ct_dd_audio_ctrl6_i2scmmn_test30(ct_dd_audio_ctrl6_new(&temp, 0));
			break;
		case 415:
			ct_dd_audio_ctrl6_i2scmmn_test31(ct_dd_audio_ctrl6_new(&temp, 0));
			break;
		case 416:
			ct_dd_audio_ctrl6_i2scmmn_test32(ct_dd_audio_ctrl6_new(&temp, 0));
			break;
		case 417:
			ct_dd_audio_ctrl6_i2scmmn_test33(ct_dd_audio_ctrl6_new(&temp, 0));
			break;
		case 418:
			ct_dd_audio_ctrl7_i2scmmn_test34(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 419:
			ct_dd_audio_ctrl7_i2scmmn_test35(ct_dd_audio_ctrl7_new(&temp, 0));
			break;
		case 420:
			ct_dd_audio_ctrl6_i2scmmn_test25(ct_dd_audio_ctrl6_new(&temp, 1));
			break;
		case 421:
			ct_dd_audio_get_ctrl_i2scmmn_test1(ct_dd_audio_get_new(&temp, 2));
			break;
		case 422:
			ct_dd_audio_ctrl4_i2scmmn_test2(ct_dd_audio_ctrl4_new(&temp, 2));
			break;
		case 423:
			ct_dd_audio_ctrl4_i2scmmn_test3(ct_dd_audio_ctrl4_new(&temp, 2));
			break;
		case 424:
			ct_dd_audio_ctrl4_i2scmmn_test4(ct_dd_audio_ctrl4_new(&temp, 2));
			break;
		case 425:
			ct_dd_audio_ctrl4_i2scmmn_test5(ct_dd_audio_ctrl4_new(&temp, 2));
			break;
		case 426:
			ct_dd_audio_ctrl4_i2scmmn_test6(ct_dd_audio_ctrl4_new(&temp, 2));
			break;
		case 427:
			ct_dd_audio_ctrl5_i2scmmn_test7(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 428:
			ct_dd_audio_ctrl5_i2scmmn_test8(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 429:
			ct_dd_audio_ctrl5_i2scmmn_test9(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 430:
			ct_dd_audio_ctrl5_i2scmmn_test10(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 431:
			ct_dd_audio_ctrl5_i2scmmn_test11(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 432:
			ct_dd_audio_ctrl5_i2scmmn_test12(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 433:
			ct_dd_audio_ctrl5_i2scmmn_test13(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 434:
			ct_dd_audio_ctrl5_i2scmmn_test14(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 435:
			ct_dd_audio_ctrl5_i2scmmn_test15(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 436:
			ct_dd_audio_ctrl5_i2scmmn_test16(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 437:
			ct_dd_audio_ctrl5_i2scmmn_test17(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 438:
			ct_dd_audio_ctrl5_i2scmmn_test18(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 439:
			ct_dd_audio_ctrl5_i2scmmn_test19(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 440:
			ct_dd_audio_ctrl5_i2scmmn_test20(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 441:
			ct_dd_audio_ctrl5_i2scmmn_test21(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 442:
			ct_dd_audio_ctrl5_i2scmmn_test22(ct_dd_audio_ctrl5_new(&temp, 2));
			break;
		case 443:
			ct_dd_audio_ctrl6_i2scmmn_test23(ct_dd_audio_ctrl6_new(&temp, 2));
			break;
		case 444:
			ct_dd_audio_ctrl6_i2scmmn_test24(ct_dd_audio_ctrl6_new(&temp, 2));
			break;
		case 445:
			ct_dd_audio_ctrl6_i2scmmn_test25(ct_dd_audio_ctrl6_new(&temp, 2));
			break;
		case 446:
			ct_dd_audio_ctrl6_i2scmmn_test26(ct_dd_audio_ctrl6_new(&temp, 2));
			break;
		case 447:
			ct_dd_audio_ctrl6_i2scmmn_test27(ct_dd_audio_ctrl6_new(&temp, 2));
			break;
		case 448:
			ct_dd_audio_ctrl6_i2scmmn_test28(ct_dd_audio_ctrl6_new(&temp, 2));
			break;
		case 449:
			ct_dd_audio_ctrl6_i2scmmn_test29(ct_dd_audio_ctrl6_new(&temp, 2));
			break;
		case 450:
			ct_dd_audio_ctrl6_i2scmmn_test30(ct_dd_audio_ctrl6_new(&temp, 2));
			break;
		case 451:
			ct_dd_audio_ctrl6_i2scmmn_test31(ct_dd_audio_ctrl6_new(&temp, 2));
			break;
		case 452:
			ct_dd_audio_ctrl6_i2scmmn_test32(ct_dd_audio_ctrl6_new(&temp, 2));
			break;
		case 453:
			ct_dd_audio_ctrl6_i2scmmn_test33(ct_dd_audio_ctrl6_new(&temp, 2));
			break;
		case 454:
			ct_dd_audio_ctrl7_i2scmmn_test34(ct_dd_audio_ctrl7_new(&temp, 2));
			break;
		case 455:
			ct_dd_audio_ctrl7_i2scmmn_test35(ct_dd_audio_ctrl7_new(&temp, 2));
			break;
		case 456:
			ct_dd_audio_ctrl4_i2scmmn_test1(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 457:
			ct_dd_audio_ctrl4_i2scmmn_test2(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 458:
			ct_dd_audio_ctrl4_i2scmmn_test3(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 459:
			ct_dd_audio_ctrl4_i2scmmn_test4(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 460:
			ct_dd_audio_ctrl4_i2scmmn_test5(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 461:
			ct_dd_audio_ctrl4_i2scmmn_test6(ct_dd_audio_ctrl4_new(&temp, 3));
			break;
		case 462:
			ct_dd_audio_ctrl5_i2scmmn_test7(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 463:
			ct_dd_audio_ctrl5_i2scmmn_test8(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 464:
			ct_dd_audio_ctrl5_i2scmmn_test9(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 465:
			ct_dd_audio_ctrl5_i2scmmn_test10(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 466:
			ct_dd_audio_ctrl5_i2scmmn_test11(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 467:
			ct_dd_audio_ctrl5_i2scmmn_test12(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 468:
			ct_dd_audio_ctrl5_i2scmmn_test13(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 469:
			ct_dd_audio_ctrl5_i2scmmn_test14(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 470:
			ct_dd_audio_ctrl5_i2scmmn_test15(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 471:
			ct_dd_audio_ctrl5_i2scmmn_test16(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 472:
			ct_dd_audio_ctrl5_i2scmmn_test17(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 473:
			ct_dd_audio_ctrl5_i2scmmn_test18(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 474:
			ct_dd_audio_ctrl5_i2scmmn_test19(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 475:
			ct_dd_audio_ctrl5_i2scmmn_test20(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 476:
			ct_dd_audio_ctrl5_i2scmmn_test21(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 477:
			ct_dd_audio_ctrl5_i2scmmn_test22(ct_dd_audio_ctrl5_new(&temp, 3));
			break;
		case 478:
			ct_dd_audio_ctrl6_i2scmmn_test23(ct_dd_audio_ctrl6_new(&temp, 3));
			break;
		case 479:
			ct_dd_audio_ctrl6_i2scmmn_test24(ct_dd_audio_ctrl6_new(&temp, 3));
			break;
		case 480:
			ct_dd_audio_ctrl6_i2scmmn_test25(ct_dd_audio_ctrl6_new(&temp, 3));
			break;
		case 481:
			ct_dd_audio_ctrl6_i2scmmn_test26(ct_dd_audio_ctrl6_new(&temp, 3));
			break;
		case 482:
			ct_dd_audio_ctrl6_i2scmmn_test28(ct_dd_audio_ctrl6_new(&temp, 3));
			break;
		case 483:
			ct_dd_audio_ctrl6_i2scmmn_test30(ct_dd_audio_ctrl6_new(&temp, 3));
			break;
		case 484:
			ct_dd_audio_ctrl6_i2scmmn_test31(ct_dd_audio_ctrl6_new(&temp, 3));
			break;
		case 485:
			ct_dd_audio_ctrl6_i2scmmn_test33(ct_dd_audio_ctrl6_new(&temp, 3));
			break;
		case 486:
			ct_dd_audio_ctrl7_i2scmmn_test35(ct_dd_audio_ctrl7_new(&temp, 3));
			break;
		case 487:
			ct_dd_audio_ctrl7_i2scmmn_test36(ct_dd_audio_ctrl7_new(&temp, 4));
			break;
		case 488:
			ct_dd_audio_ctrl7_i2scmmn_test37(ct_dd_audio_ctrl7_new(&temp, 4));
			break;
		case 489:
			ct_dd_audio_ctrl4_i2scmmn_test3(ct_dd_audio_ctrl4_new(&temp, 4));
			break;
		case 490:
			ct_dd_audio_ctrl4_i2scmmn_test4(ct_dd_audio_ctrl4_new(&temp, 4));
			break;
		case 491:
			ct_dd_audio_ctrl4_i2scmmn_test5(ct_dd_audio_ctrl4_new(&temp, 4));
			break;
		case 492:
			ct_dd_audio_ctrl5_i2scmmn_test7(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 493:
			ct_dd_audio_ctrl5_i2scmmn_test8(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 494:
			ct_dd_audio_ctrl5_i2scmmn_test9(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 495:
			ct_dd_audio_ctrl5_i2scmmn_test10(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 496:
			ct_dd_audio_ctrl5_i2scmmn_test11(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 497:
			ct_dd_audio_ctrl5_i2scmmn_test12(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 498:
			ct_dd_audio_ctrl5_i2scmmn_test13(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 499:
			ct_dd_audio_ctrl5_i2scmmn_test14(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 500:
			ct_dd_audio_ctrl5_i2scmmn_test15(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 501:
			ct_dd_audio_ctrl5_i2scmmn_test16(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 502:
			ct_dd_audio_ctrl5_i2scmmn_test17(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 503:
			ct_dd_audio_ctrl5_i2scmmn_test18(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 504:
			ct_dd_audio_ctrl5_i2scmmn_test19(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 505:
			ct_dd_audio_ctrl5_i2scmmn_test20(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 506:
			ct_dd_audio_ctrl5_i2scmmn_test21(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 507:
			ct_dd_audio_ctrl5_i2scmmn_test22(ct_dd_audio_ctrl5_new(&temp, 4));
			break;
		case 508:
			ct_dd_audio_ctrl6_i2scmmn_test23(ct_dd_audio_ctrl6_new(&temp, 4));
			break;
		case 509:
			ct_dd_audio_ctrl6_i2scmmn_test24(ct_dd_audio_ctrl6_new(&temp, 4));
			break;
		case 510:
			ct_dd_audio_ctrl6_i2scmmn_test25(ct_dd_audio_ctrl6_new(&temp, 4));
			break;
		case 511:
			ct_dd_audio_ctrl6_i2scmmn_test26(ct_dd_audio_ctrl6_new(&temp, 4));
			break;
		case 512:
			ct_dd_audio_ctrl6_i2scmmn_test27(ct_dd_audio_ctrl6_new(&temp, 4));
			break;
		case 513:
			ct_dd_audio_ctrl6_i2scmmn_test30(ct_dd_audio_ctrl6_new(&temp, 4));
			break;
		case 514:
			ct_dd_audio_ctrl6_i2scmmn_test31(ct_dd_audio_ctrl6_new(&temp, 4));
			break;
		case 515:
			ct_dd_audio_ctrl6_i2scmmn_test32(ct_dd_audio_ctrl6_new(&temp, 4));
			break;
		case 516:
			ct_dd_audio_ctrl7_i2scmmn_test35(ct_dd_audio_ctrl7_new(&temp, 4));
			break;
		case 517:
			ct_dd_audio_ctrl7_i2scmmn_test36(ct_dd_audio_ctrl7_new(&temp, 5));
			break;
		case 518:
			ct_dd_audio_ctrl7_i2scmmn_test37(ct_dd_audio_ctrl7_new(&temp, 5));
			break;
		case 519:
			ct_dd_audio_ctrl4_i2scmmn_test3(ct_dd_audio_ctrl4_new(&temp, 5));
			break;
		case 520:
			ct_dd_audio_ctrl4_i2scmmn_test4(ct_dd_audio_ctrl4_new(&temp, 5));
			break;
		case 521:
			ct_dd_audio_ctrl4_i2scmmn_test5(ct_dd_audio_ctrl4_new(&temp, 5));
			break;
		case 522:
			ct_dd_audio_ctrl5_i2scmmn_test7(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 523:
			ct_dd_audio_ctrl5_i2scmmn_test8(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 524:
			ct_dd_audio_ctrl5_i2scmmn_test9(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 525:
			ct_dd_audio_ctrl5_i2scmmn_test10(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 526:
			ct_dd_audio_ctrl5_i2scmmn_test11(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 527:
			ct_dd_audio_ctrl5_i2scmmn_test12(ct_dd_audio_ctrl5_new(&temp, 5));
			break;
		case 528:
			ct_dd_audio_ctrl5_i2scmmn_test13(ct_dd_audio_ctrl5_new(&temp, 5));
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

CtAudioCaseFour *ct_audio_case_four_new(void)
{
	CtAudioCaseFour *self = CT_AUDIO_CASE_FOUR(g_object_new(CT_TYPE_AUDIO_CASE_FOUR, NULL));
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}

