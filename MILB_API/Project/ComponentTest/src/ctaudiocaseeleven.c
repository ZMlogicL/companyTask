/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :zhaoxin
*@brief               :CtAudioCaseEleven类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、CtAudioCaseEleven类
*@version 1.0.0
*
*/

#include "ctaudiocaseeleven.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtAudioCaseEleven, ct_audio_case_eleven)
#define CT_AUDIO_CASE_ELEVEN_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), \
		CtAudioCaseElevenPrivate, CT_TYPE_AUDIO_CASE_ELEVEN))

struct _CtAudioCaseElevenPrivate
{
	
};

/*
*DECLS
*/
static void ct_audio_case_eleven_constructor(CtAudioCaseEleven *self);
static void ct_audio_case_eleven_destructor(CtAudioCaseEleven *self);
static void doWithArgs_od(AbsCtAudioCase *self, kint caseValue);

/*
 * IMPL
 */
static void ct_audio_case_eleven_constructor(CtAudioCaseEleven *self)
{
	((AbsCtAudioCase*)self)->doWithArgs = doWithArgs_od;
	((AbsCtAudioCase*)self)->doNoArgs = NULL;
}

static void ct_audio_case_eleven_destructor(CtAudioCaseEleven *self)
{
	self = NULL;
}

//245-367
static void doWithArgs_od(AbsCtAudioCase *self, kint caseValue)
{
	kpointer temp = NULL;
	kpointer secondTemp = NULL;
	switch(caseValue)
	{
		case 245:
			ct_dd_audio_start_loop_back_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_start_loop_back_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, 2));
			break;
		case 246:
			ct_dd_audio_start_loop_back_test2(ct_dd_audio_start_new(&temp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 247:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_start_loop_back_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 248:
			ct_dd_audio_start_loop_back_test_multi(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_start_loop_back_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 249:
			ct_dd_audio_start_loop_back_test_multi(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_stop_loop_back_test(ct_dd_audio_stop_new(&secondTemp, 0));
			ct_dd_audio_start_loop_back_test2(ct_dd_audio_start_set_ch((CtDdAudioStart*)temp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 250:
			ct_dd_audio_start_input_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_start_loop_back_test_multi2((CtDdAudioStart*)temp);
			break;
		case 251:
			ct_dd_audio_start_loop_back_test2(ct_dd_audio_start_new(&temp, 3));
			break;
		case 252:
			ct_dd_audio_stop_loop_back_test(ct_dd_audio_stop_new(&secondTemp, 0));
			break;
		case 253:
			ct_dd_audio_stop_loop_back_test(ct_dd_audio_stop_new(&secondTemp, 2));
			break;
		case 254:
			ct_dd_audio_stop_loop_back_test(ct_dd_audio_stop_new(&secondTemp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 255:
			ct_dd_audio_start_loop_back_test1(ct_dd_audio_start_new(&temp, 0));
			ct_dd_audio_stop_loop_back_test(ct_dd_audio_stop_new(&secondTemp, D_DD_AUDIO_IF_CH0_CH1));
			break;
		case 256:
			ct_dd_audio_stop_loop_back_test(ct_dd_audio_stop_new(&secondTemp, 3));
			break;
		case 257:
			ct_dd_audio_get_status_loop_back_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 258:
			ct_dd_audio_set_enable_fifo_full_dmain_test3(ct_dd_audio_set_new(&temp, 0));
			break;
		case 259:
			ct_dd_audio_set_enable_fifo_full_dmain_test3(ct_dd_audio_set_new(&temp, 1));
			break;
		case 260:
			ct_dd_audio_set_enable_fifo_full_dmain_test3(ct_dd_audio_set_new(&temp, 2));
			break;
		case 261:
			ct_dd_audio_set_enable_fifo_full_dmain_test3(ct_dd_audio_set_new(&temp, 4));
			break;
		case 262:
			ct_dd_audio_set_enable_fifo_full_dmain_test3(ct_dd_audio_set_new(&temp, 5));
			break;
		case 263:
			ct_dd_audio_set_enable_fifo_full_dmain_test4(ct_dd_audio_set_new(&temp, 3));
			break;
		case 264:
			ct_dd_audio_set_enable_fifo_full_dmain_test4(ct_dd_audio_set_new(&temp, 6));
			break;
		case 265:
			ct_dd_audio_set_enable_fifo_full_dmain_test5(ct_dd_audio_set_new(&temp, 0));
			break;
		case 266:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test3(ct_dd_audio_set_new(&temp, 0));
			break;
		case 267:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test3(ct_dd_audio_set_new(&temp, 1));
			break;
		case 268:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test3(ct_dd_audio_set_new(&temp, 2));
			break;
		case 269:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test3(ct_dd_audio_set_new(&temp, 3));
			break;
		case 270:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test4(ct_dd_audio_set_new(&temp, 4));
			break;
		case 271:
			ct_dd_audio_set_enable_fifo_empty_dma_out_test5(ct_dd_audio_set_new(&temp, 0));
			break;
		case 272:
			ct_dd_audio_set_input_dmarequest_enable_test3(ct_dd_audio_set_new(&temp, 0));
			break;
		case 273:
			ct_dd_audio_set_input_dmarequest_enable_test3(ct_dd_audio_set_new(&temp, 1));
			break;
		case 274:
			ct_dd_audio_set_input_dmarequest_enable_test3(ct_dd_audio_set_new(&temp, 2));
			break;
		case 275:
			ct_dd_audio_set_input_dmarequest_enable_test3(ct_dd_audio_set_new(&temp, 4));
			break;
		case 276:
			ct_dd_audio_set_input_dmarequest_enable_test3(ct_dd_audio_set_new(&temp, 5));
			break;
		case 277:
			ct_dd_audio_set_input_dmarequest_enable_test4(ct_dd_audio_set_new(&temp, 3));
			break;
		case 278:
			ct_dd_audio_set_input_dmarequest_enable_test4(ct_dd_audio_set_new(&temp, 6));
			break;
		case 279:
			ct_dd_audio_set_input_dmarequest_enable_test5(ct_dd_audio_set_new(&temp, 0));
			break;
		case 280:
			ct_dd_audio_set_output_dmarequest_enable_test3(ct_dd_audio_set_new(&temp, 0));
			break;
		case 281:
			ct_dd_audio_set_output_dmarequest_enable_test3(ct_dd_audio_set_new(&temp, 1));
			break;
		case 282:
			ct_dd_audio_set_output_dmarequest_enable_test3(ct_dd_audio_set_new(&temp, 2));
			break;
		case 283:
			ct_dd_audio_set_output_dmarequest_enable_test3(ct_dd_audio_set_new(&temp, 3));
			break;
		case 284:
			ct_dd_audio_set_output_dmarequest_enable_test4(ct_dd_audio_set_new(&temp, 4));
			break;
		case 285:
			ct_dd_audio_set_output_dmarequest_enable_test5(ct_dd_audio_set_new(&temp, 0));
			break;
		case 286:
			ct_dd_audio_get_in_dmasample_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 287:
			ct_dd_audio_get_in_dmasample_test(ct_dd_audio_get_new(&temp, 6));
			break;
		case 288:
			ct_dd_audio_get_out_dmasample_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 289:
			ct_dd_audio_set_swaphw_auidlr_test4(ct_dd_audio_set_new(&temp, 0));
			break;
		case 290:
			ct_dd_audio_set_swaphw_auidlr_test4(ct_dd_audio_set_new(&temp, 1));
			break;
		case 291:
			ct_dd_audio_set_swaphw_auidlr_test4(ct_dd_audio_set_new(&temp, 2));
			break;
		case 292:
			ct_dd_audio_set_swaphw_auidlr_test4(ct_dd_audio_set_new(&temp, 4));
			break;
		case 293:
			ct_dd_audio_set_swaphw_auidlr_test4(ct_dd_audio_set_new(&temp, 5));
			break;
		case 294:
			ct_dd_audio_set_swaphw_auidlr_test5(ct_dd_audio_set_new(&temp, 3));
			break;
		case 295:
			ct_dd_audio_set_swaphw_auidlr_test5(ct_dd_audio_set_new(&temp, 6));
			break;
		case 296:
			ct_dd_audio_set_swaphw_auidlr_test6(ct_dd_audio_set_new(&temp, 0));
			break;
		case 297:
			ct_dd_audio_set_swapbyte_auidlr_test4(ct_dd_audio_set_new(&temp, 0));
			break;
		case 298:
			ct_dd_audio_set_swapbyte_auidlr_test4(ct_dd_audio_set_new(&temp, 1));
			break;
		case 299:
			ct_dd_audio_set_swapbyte_auidlr_test4(ct_dd_audio_set_new(&temp, 2));
			break;
		case 300:
			ct_dd_audio_set_swapbyte_auidlr_test4(ct_dd_audio_set_new(&temp, 4));
			break;
		case 301:
			ct_dd_audio_set_swapbyte_auidlr_test4(ct_dd_audio_set_new(&temp, 5));
			break;
		case 302:
			ct_dd_audio_set_swapbyte_auidlr_test5(ct_dd_audio_set_new(&temp, 3));
			break;
		case 303:
			ct_dd_audio_set_swapbyte_auidlr_test5(ct_dd_audio_set_new(&temp, 6));
			break;
		case 304:
			ct_dd_audio_set_swapbyte_auidlr_test6(ct_dd_audio_set_new(&temp, 0));
			break;
		case 305:
			ct_dd_audio_set1_swaphw_auodlr_test5(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 306:
			ct_dd_audio_set1_swaphw_auodlr_test6(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 307:
			ct_dd_audio_set1_swaphw_auodlr_test5(ct_dd_audio_set1_new(&temp, 1));
			break;
		case 308:
			ct_dd_audio_set1_swaphw_auodlr_test6(ct_dd_audio_set1_new(&temp, 1));
			break;
		case 309:
			ct_dd_audio_set1_swaphw_auodlr_test5(ct_dd_audio_set1_new(&temp, 2));
			break;
		case 310:
			ct_dd_audio_set1_swaphw_auodlr_test6(ct_dd_audio_set1_new(&temp, 2));
			break;
		case 311:
			ct_dd_audio_set1_swaphw_auodlr_test5(ct_dd_audio_set1_new(&temp, 3));
			break;
		case 312:
			ct_dd_audio_set1_swaphw_auodlr_test7(ct_dd_audio_set1_new(&temp, 4));
			break;
		case 313:
			ct_dd_audio_set1_swaphw_auodlr_test8(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 314:
			ct_dd_audio_set1_swapbyte_auodlr_test5(ct_dd_audio_set1_new(&temp, 0));
			break;
		case 315:
			ct_dd_audio_set2_swapbyte_auodlr_test6(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 316:
			ct_dd_audio_set1_swapbyte_auodlr_test5(ct_dd_audio_set1_new(&temp, 1));
			break;
		case 317:
			ct_dd_audio_set2_swapbyte_auodlr_test6(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 318:
			ct_dd_audio_set1_swapbyte_auodlr_test5(ct_dd_audio_set1_new(&temp, 2));
			break;
		case 319:
			ct_dd_audio_set2_swapbyte_auodlr_test6(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 320:
			ct_dd_audio_set1_swapbyte_auodlr_test5(ct_dd_audio_set1_new(&temp, 3));
			break;
		case 321:
			ct_dd_audio_set2_swapbyte_auodlr_test7(ct_dd_audio_set2_new(&temp, 4));
			break;
		case 322:
			ct_dd_audio_set2_swapbyte_auodlr_test8(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 323:
			ct_dd_audio_get_addr_reg_auidlr_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 324:
			ct_dd_audio_get_addr_reg_auidlr_test(ct_dd_audio_get_new(&temp, 6));
			break;
		case 325:
			ct_dd_audio_get_addr_reg_auodlr_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 326:
			ct_dd_audio_get_addr_reg_auidl_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 327:
			ct_dd_audio_get_addr_reg_auidl_test(ct_dd_audio_get_new(&temp, 6));
			break;
		case 328:
			ct_dd_audio_get_addr_reg_auidr_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 329:
			ct_dd_audio_get_addr_reg_auidr_test(ct_dd_audio_get_new(&temp, 6));
			break;
		case 330:
			ct_dd_audio_get_addr_reg_auodl_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 331:
			ct_dd_audio_get_addr_reg_auodr_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 332:
			ct_dd_audio_get_addr_reg_auiddmapt_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 333:
			ct_dd_audio_get_addr_reg_auiddmapt_test(ct_dd_audio_get_new(&temp, 6));
			break;
		case 334:
			ct_dd_audio_get_addr_reg_auoddmapt_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 335:
			ct_dd_audio_set2_enable_input_intr_test9(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 336:
			ct_dd_audio_set2_enable_input_intr_test10(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 337:
			ct_dd_audio_set2_enable_input_intr_test9(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 338:
			ct_dd_audio_set2_enable_input_intr_test10(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 339:
			ct_dd_audio_set2_enable_input_intr_test9(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 340:
			ct_dd_audio_set2_enable_input_intr_test10(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 341:
			ct_dd_audio_set2_enable_input_intr_test9(ct_dd_audio_set2_new(&temp, 4));
			break;
		case 342:
			ct_dd_audio_set2_enable_input_intr_test10(ct_dd_audio_set2_new(&temp, 4));
			break;
		case 343:
			ct_dd_audio_set2_enable_input_intr_test9(ct_dd_audio_set2_new(&temp, 5));
			break;
		case 344:
			ct_dd_audio_set2_enable_input_intr_test10(ct_dd_audio_set2_new(&temp, 5));
			break;
		case 345:
			ct_dd_audio_set2_enable_input_intr_test11(ct_dd_audio_set2_new(&temp, 3));
			break;
		case 346:
			ct_dd_audio_set2_enable_input_intr_test11(ct_dd_audio_set2_new(&temp, 6));
			break;
		case 347:
			ct_dd_audio_set2_enable_input_intr_test12(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 348:
			ct_dd_audio_set2_enable_output_intr_test9(ct_dd_audio_set2_new(&temp, 0));
			break;
		case 349:
			ct_dd_audio_set3_enable_output_intr_test10(ct_dd_audio_set3_new(&temp, 0));
			break;
		case 350:
			ct_dd_audio_set2_enable_output_intr_test9(ct_dd_audio_set2_new(&temp, 1));
			break;
		case 351:
			ct_dd_audio_set3_enable_output_intr_test10(ct_dd_audio_set3_new(&temp, 1));
			break;
		case 352:
			ct_dd_audio_set2_enable_output_intr_test9(ct_dd_audio_set2_new(&temp, 2));
			break;
		case 353:
			ct_dd_audio_set3_enable_output_intr_test10(ct_dd_audio_set3_new(&temp, 2));
			break;
		case 354:
			ct_dd_audio_set2_enable_output_intr_test9(ct_dd_audio_set2_new(&temp, 3));
			break;
		case 355:
			ct_dd_audio_set3_enable_output_intr_test10(ct_dd_audio_set3_new(&temp, 3));
			break;
		case 356:
			ct_dd_audio_set3_enable_output_intr_test11(ct_dd_audio_set3_new(&temp, 4));
			break;
		case 357:
			ct_dd_audio_set3_enable_output_intr_test12(ct_dd_audio_set3_new(&temp, 0));
			break;
		case 358:
			ct_dd_audio_set3_enable_in_over_flow_intr_test3(ct_dd_audio_set3_new(&temp, 3));
			break;
		case 359:
			ct_dd_audio_set3_enable_in_over_flow_intr_test3(ct_dd_audio_set3_new(&temp, 6));
			break;
		case 360:
			ct_dd_audio_set3_enable_in_over_flow_intr_test4(ct_dd_audio_set3_new(&temp, 0));
			break;
		case 361:
			ct_dd_audio_set3_enable_out_under_flow_intr_test3(ct_dd_audio_set3_new(&temp, 4));
			break;
		case 362:
			ct_dd_audio_set3_enable_out_under_flow_intr_test4(ct_dd_audio_set3_new(&temp, 0));
			break;
		case 363:
			ct_dd_audio_get_input_fifo_status_test(ct_dd_audio_get_new(&temp, 3));
			break;
		case 364:
			ct_dd_audio_get_input_fifo_status_test(ct_dd_audio_get_new(&temp, 6));
			break;
		case 365:
			ct_dd_audio_get_output_fifo_status_test(ct_dd_audio_get_new(&temp, 4));
			break;
		case 366:
			ct_dd_audio_input_open_test5(ct_dd_audio_new(&temp, 0));
			break;
		case 367:
			ct_dd_audio_output_open_test5(ct_dd_audio_new(&temp, 0));
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
	}
}

/*
*PUBLIC
*/

CtAudioCaseEleven *ct_audio_case_eleven_new(void)
{
	CtAudioCaseEleven *self = k_object_new(CT_TYPE_AUDIO_CASE_ELEVEN);
	if (K_UNLIKELY(!self))
	{
		return NULL;
	}
	return self;
}



