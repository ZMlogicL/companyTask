/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :luhongyin
*@brief               :CtAudioCaseThree类
*@rely                :glib
*@function
*
*设计的主要功能:
*1、CtAudioCaseThree类
*@version 1.0.0
*
*/

#include "ctaudiocasethree.h"

G_DEFINE_TYPE(CtAudioCaseThree, ct_audio_case_three, G_TYPE_OBJECT);
#define CT_AUDIO_CASE_THREE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), \
			CT_TYPE_AUDIO_CASE_THREE, CtAudioCaseThreePrivate))

struct _CtAudioCaseThreePrivate
{
	
};

/*
*DECLS
*/
static void ct_audio_case_three_class_init(CtAudioCaseThreeClass *klass);
static void ct_audio_case_three_init(CtAudioCaseThree *self);
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue);

/*
 * IMPL
 */
static void ct_audio_case_three_class_init(CtAudioCaseThreeClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	g_type_class_add_private(klass, sizeof(CtAudioCaseThreePrivate));
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
}

static void ct_audio_case_three_init(CtAudioCaseThree *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_three_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	G_OBJECT_CLASS(ct_audio_case_three_parent_class)->finalize(object);
}

//265-396
static void doWithArgs_od(AbsCtAudioCase *self, gint caseValue)
{
	gpointer temp = NULL;
	switch(caseValue)
	{
		case 265:
			ct_dd_audio_get_ctrl_input_test1(ct_dd_audio_get_new(&temp, 1));
			break;
		case 266:
			ct_dd_audio_get_ctrl_input_test1(ct_dd_audio_get_new(&temp, 2));
			break;
		case 267:
			ct_dd_audio_get_ctrl_input_test1(ct_dd_audio_get_new(&temp, 4));
			break;
		case 268:
			ct_dd_audio_get_ctrl_input_test1(ct_dd_audio_get_new(&temp, 5));
			break;
		case 269:
			ct_dd_audio_ctrl1_output_test1(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 270:
			ct_dd_audio_ctrl1_output_test2(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 271:
			ct_dd_audio_ctrl1_output_test3(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 272:
			ct_dd_audio_ctrl1_output_test4(ct_dd_audio_ctrl1_new(&temp, 0));
			break;
		case 273:
			ct_dd_audio_ctrl2_output_test5(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 274:
			ct_dd_audio_ctrl2_output_test6(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 275:
			ct_dd_audio_ctrl2_output_test7(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 276:
			ct_dd_audio_ctrl2_output_test8(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 277:
			ct_dd_audio_ctrl2_output_test9(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 278:
			ct_dd_audio_ctrl2_output_test10(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 279:
			ct_dd_audio_ctrl2_output_test11(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 280:
			ct_dd_audio_ctrl2_output_test12(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 281:
			ct_dd_audio_ctrl2_output_test13(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 282:
			ct_dd_audio_ctrl2_output_test14(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 283:
			ct_dd_audio_ctrl2_output_test15(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 284:
			ct_dd_audio_ctrl2_output_test16(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 285:
			ct_dd_audio_ctrl2_output_test17(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 286:
			ct_dd_audio_ctrl2_output_test18(ct_dd_audio_ctrl2_new(&temp, 0));
			break;
		case 287:
			ct_dd_audio_ctrl3_output_test19(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 288:
			ct_dd_audio_ctrl3_output_test20(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 289:
			ct_dd_audio_ctrl3_output_test21(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 290:
			ct_dd_audio_ctrl3_output_test22(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 291:
			ct_dd_audio_ctrl3_output_test23(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 292:
			ct_dd_audio_ctrl3_output_test24(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 293:
			ct_dd_audio_ctrl3_output_test25(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 294:
			ct_dd_audio_ctrl3_output_test26(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 295:
			ct_dd_audio_ctrl3_output_test27(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 296:
			ct_dd_audio_ctrl3_output_test28(ct_dd_audio_ctrl3_new(&temp, 0));
			break;
		case 297:
			ct_dd_audio_ctrl1_output_test1(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 298:
			ct_dd_audio_ctrl1_output_test2(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 299:
			ct_dd_audio_ctrl1_output_test3(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 300:
			ct_dd_audio_ctrl1_output_test4(ct_dd_audio_ctrl1_new(&temp, 1));
			break;
		case 301:
			ct_dd_audio_ctrl2_output_test5(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 302:
			ct_dd_audio_ctrl2_output_test6(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 303:
			ct_dd_audio_ctrl2_output_test7(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 304:
			ct_dd_audio_ctrl2_output_test8(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 305:
			ct_dd_audio_ctrl2_output_test9(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 306:
			ct_dd_audio_ctrl2_output_test10(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 307:
			ct_dd_audio_ctrl2_output_test11(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 308:
			ct_dd_audio_ctrl2_output_test12(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 309:
			ct_dd_audio_ctrl2_output_test13(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 310:
			ct_dd_audio_ctrl2_output_test14(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 311:
			ct_dd_audio_ctrl2_output_test15(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 312:
			ct_dd_audio_ctrl2_output_test16(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 313:
			ct_dd_audio_ctrl2_output_test17(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 314:
			ct_dd_audio_ctrl2_output_test18(ct_dd_audio_ctrl2_new(&temp, 1));
			break;
		case 315:
			ct_dd_audio_ctrl3_output_test19(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 316:
			ct_dd_audio_ctrl3_output_test20(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 317:
			ct_dd_audio_ctrl3_output_test21(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 318:
			ct_dd_audio_ctrl3_output_test22(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 319:
			ct_dd_audio_ctrl3_output_test23(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 320:
			ct_dd_audio_ctrl3_output_test24(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 321:
			ct_dd_audio_ctrl3_output_test25(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 322:
			ct_dd_audio_ctrl3_output_test26(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 323:
			ct_dd_audio_ctrl3_output_test27(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 324:
			ct_dd_audio_ctrl3_output_test28(ct_dd_audio_ctrl3_new(&temp, 1));
			break;
		case 325:
			ct_dd_audio_ctrl1_output_test1(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 326:
			ct_dd_audio_ctrl1_output_test2(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 327:
			ct_dd_audio_ctrl1_output_test3(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 328:
			ct_dd_audio_ctrl1_output_test4(ct_dd_audio_ctrl1_new(&temp, 2));
			break;
		case 329:
			ct_dd_audio_ctrl2_output_test5(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 330:
			ct_dd_audio_ctrl2_output_test6(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 331:
			ct_dd_audio_ctrl2_output_test7(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 332:
			ct_dd_audio_ctrl2_output_test8(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 333:
			ct_dd_audio_ctrl2_output_test9(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 334:
			ct_dd_audio_ctrl2_output_test10(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 335:
			ct_dd_audio_ctrl2_output_test11(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 336:
			ct_dd_audio_ctrl2_output_test12(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 337:
			ct_dd_audio_ctrl2_output_test13(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 338:
			ct_dd_audio_ctrl2_output_test14(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 339:
			ct_dd_audio_ctrl2_output_test15(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 340:
			ct_dd_audio_ctrl2_output_test16(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 341:
			ct_dd_audio_ctrl2_output_test17(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 342:
			ct_dd_audio_ctrl2_output_test18(ct_dd_audio_ctrl2_new(&temp, 2));
			break;
		case 343:
			ct_dd_audio_ctrl3_output_test19(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 344:
			ct_dd_audio_ctrl3_output_test20(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 345:
			ct_dd_audio_ctrl3_output_test21(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 346:
			ct_dd_audio_ctrl3_output_test22(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 347:
			ct_dd_audio_ctrl3_output_test23(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 348:
			ct_dd_audio_ctrl3_output_test24(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 349:
			ct_dd_audio_ctrl3_output_test25(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 350:
			ct_dd_audio_ctrl3_output_test26(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 351:
			ct_dd_audio_ctrl3_output_test27(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 352:
			ct_dd_audio_ctrl3_output_test28(ct_dd_audio_ctrl3_new(&temp, 2));
			break;
		case 353:
			ct_dd_audio_ctrl1_output_test1(ct_dd_audio_ctrl1_new(&temp, 3));
			break;
		case 354:
			ct_dd_audio_ctrl1_output_test2(ct_dd_audio_ctrl1_new(&temp, 3));
			break;
		case 355:
			ct_dd_audio_ctrl1_output_test3(ct_dd_audio_ctrl1_new(&temp, 3));
			break;
		case 356:
			ct_dd_audio_ctrl1_output_test4(ct_dd_audio_ctrl1_new(&temp, 3));
			break;
		case 357:
			ct_dd_audio_ctrl2_output_test5(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 358:
			ct_dd_audio_ctrl2_output_test6(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 359:
			ct_dd_audio_ctrl2_output_test7(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 360:
			ct_dd_audio_ctrl2_output_test8(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 361:
			ct_dd_audio_ctrl2_output_test9(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 362:
			ct_dd_audio_ctrl2_output_test10(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 363:
			ct_dd_audio_ctrl2_output_test11(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 364:
			ct_dd_audio_ctrl2_output_test12(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 365:
			ct_dd_audio_ctrl2_output_test13(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 366:
			ct_dd_audio_ctrl2_output_test14(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 367:
			ct_dd_audio_ctrl2_output_test15(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 368:
			ct_dd_audio_ctrl2_output_test16(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 369:
			ct_dd_audio_ctrl2_output_test17(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 370:
			ct_dd_audio_ctrl2_output_test18(ct_dd_audio_ctrl2_new(&temp, 3));
			break;
		case 371:
			ct_dd_audio_ctrl3_output_test19(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 372:
			ct_dd_audio_ctrl3_output_test20(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 373:
			ct_dd_audio_ctrl3_output_test21(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 374:
			ct_dd_audio_ctrl3_output_test22(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 375:
			ct_dd_audio_ctrl3_output_test23(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 376:
			ct_dd_audio_ctrl3_output_test24(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 377:
			ct_dd_audio_ctrl3_output_test25(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 378:
			ct_dd_audio_ctrl3_output_test26(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 379:
			ct_dd_audio_ctrl3_output_test27(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 380:
			ct_dd_audio_ctrl3_output_test28(ct_dd_audio_ctrl3_new(&temp, 3));
			break;
		case 381:
			ct_dd_audio_get_ctrl_output_test1(ct_dd_audio_get_new(&temp, 0));
			break;
		case 382:
			ct_dd_audio_get_ctrl_output_test1(ct_dd_audio_get_new(&temp, 1));
			break;
		case 383:
			ct_dd_audio_get_ctrl_output_test1(ct_dd_audio_get_new(&temp, 2));
			break;
		case 384:
			ct_dd_audio_get_ctrl_output_test1(ct_dd_audio_get_new(&temp, 3));
			break;
		case 385:
			ct_dd_audio_ctrl4_i2scmmn_test1(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 386:
			ct_dd_audio_ctrl4_i2scmmn_test2(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 387:
			ct_dd_audio_ctrl4_i2scmmn_test3(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 388:
			ct_dd_audio_ctrl4_i2scmmn_test4(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 389:
			ct_dd_audio_ctrl4_i2scmmn_test5(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 390:
			ct_dd_audio_ctrl4_i2scmmn_test6(ct_dd_audio_ctrl4_new(&temp, 0));
			break;
		case 391:
			ct_dd_audio_ctrl5_i2scmmn_test7(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 392:
			ct_dd_audio_ctrl5_i2scmmn_test8(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 393:
			ct_dd_audio_ctrl5_i2scmmn_test9(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 394:
			ct_dd_audio_ctrl5_i2scmmn_test10(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 395:
			ct_dd_audio_ctrl5_i2scmmn_test11(ct_dd_audio_ctrl5_new(&temp, 0));
			break;
		case 396:
			ct_dd_audio_ctrl5_i2scmmn_test12(ct_dd_audio_ctrl5_new(&temp, 0));
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

CtAudioCaseThree *ct_audio_case_three_new(void)
{
	CtAudioCaseThree *self = CT_AUDIO_CASE_THREE(g_object_new(CT_TYPE_AUDIO_CASE_THREE, NULL));
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}

