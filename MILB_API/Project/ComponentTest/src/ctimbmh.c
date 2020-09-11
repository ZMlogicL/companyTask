/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImBmh类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include <string.h>
#include <stdlib.h>
#include "im_bmh.h"
#include "dd_top.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#include "jmlbmh.h"
#include "ctimbmh.h"
#include "ctimbmh1.h"
#include "ctimbmh2.h"
#include "ctimbmh3.h"
#include "ctimbmh4.h"
#include "ctimbmh5.h"
#include "ctimbmh6.h"
#include "ctimbmh7.h"
#include "ctimbmh8.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImBmh, ct_im_bmh);
#define CT_IM_BMH_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImBmhPrivate,CT_TYPE_IM_BMH))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#ifdef CO_MSG_PRINT_ON
#define CtImBmh_D_IM_BMH_RESULT(statement) result = statement
#else
#define CtImBmh_D_IM_BMH_RESULT
#endif

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// nothing special.

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// nothing special.

struct _CtImBmhPrivate
{
	kuint32 ctIdx1st;
	kuint32 ctIdx2nd;
	kuint32 ctIdx3rd;
	CtImBmh1 *bmh1;
	CtImBmh2 *bmh2;
	CtImBmh3 *bmh3;
	CtImBmh4 *bmh4;
	CtImBmh5 *bmh5;
	CtImBmh6 *bmh6;
	CtImBmh7 *bmh7;		
	CtImBmh8 *bmh8;
	DdimUserCustom* usercustom;
	kuchar loop0;
	kulong loop1;
	kulong loop2;
};

/*
 * DECLS
 */
static kint32 		ctImBmhRun1(CtImBmh *self);
static kint32 		ctImBmhRun2(CtImBmh *self);
static kint32 		ctImBmhRun3(CtImBmh *self);

static void ct_im_bmh_constructor(CtImBmh *self) 
{
	CtImBmhPrivate *priv = CT_IM_BMH_GET_PRIVATE(self);
	priv->bmh1 = ct_im_bmh1_new();
	priv->bmh2 = ct_im_bmh2_new();
	priv->bmh3 = ct_im_bmh3_new();
	priv->bmh4 = ct_im_bmh4_new();
	priv->bmh5 = ct_im_bmh5_new();
	priv->bmh6 = ct_im_bmh6_new();
	priv->bmh7 = ct_im_bmh7_new();
	priv->bmh8 = ct_im_bmh8_new();
	priv->usercustom = ddim_user_custom_new();	
	priv->loop0 = 0;
	priv->loop1 = 0;
	priv->loop2 = 0;

	// ddim_user_custom *duc = ddim_user_custom_new();
	// im_bmh *ib = im_bhm_new();
}

static void ct_im_bmh_destructor(CtImBmh *self) 
{
	CtImBmhPrivate *priv = CT_IM_BMH_GET_PRIVATE(self);
	if(priv->bmh1) {
		k_object_unref(priv->bmh1);
		priv->bmh1 = NULL;		
	}
	if(priv->bmh2) 
	{
		k_object_unref(priv->bmh2);
		priv->bmh2 = NULL;	
	}
	if(priv->bmh3) 
	{
		k_object_unref(priv->bmh3);
		priv->bmh3 = NULL;
	}
	if(priv->bmh4)
	 {
		k_object_unref(priv->bmh4);
		priv->bmh4 = NULL;
	}
	if(priv->bmh5) 
	{
		k_object_unref(priv->bmh5);
		priv->bmh5 = NULL;		
	}
	if(priv->bmh6) 
	{
		k_object_unref(priv->bmh6);
		priv->bmh6 = NULL;	
	}
	if(priv->bmh7) 
	{
		k_object_unref(priv->bmh7);
		priv->bmh7 = NULL;
	}
	if(priv->bmh8) 
	{
		k_object_unref(priv->bmh8);
		priv->bmh8 = NULL;
	}	
	if(priv->usercustom != NULL)
	{
		k_object_unref(priv->usercustom);
		priv->usercustom = NULL;			
	}			
}

/*
 * IMPL
 */
static kint32 ctImBmhRun1(CtImBmh *self)
{
	CtImBmhPrivate *priv = CT_IM_BMH_GET_PRIVATE(self);
	priv->bmh1->channelNo = priv->ctIdx3rd;
	priv->bmh2->channelNo = priv->ctIdx3rd;	
	priv->bmh3->channelNo = priv->ctIdx3rd;	

	switch(priv->ctIdx2nd){
		// Test-1-1
		case 1:
			return ct_im_bmh1_1_1(priv->bmh1);

		// Test-1-2
		case 2:
			return ct_im_bmh1_1_2(priv->bmh1);

		// Test-1-3
		case 3:
			return ct_im_bmh1_1_3(priv->bmh1);

		// Test-1-4
		case 4:
			return ct_im_bmh1_1_4(priv->bmh1);

		// Test-1-5
		case 5:
			return ct_im_bmh1_1_5(priv->bmh1);

		// Test-1-6
		case 6:
			return ct_im_bmh1_1_6(priv->bmh1);

		// Test-1-7
		case 7:
			return ct_im_bmh1_1_7(priv->bmh1);

		// Test-1-8
		case 8:
			return ct_im_bmh1_1_8(priv->bmh1);

		// Test-1-9
		case 9:
			return ct_im_bmh1_1_9(priv->bmh1);

		// Test-1-10
		case 10:
			return ct_im_bmh1_1_10(priv->bmh1);

		// Test-1-11
		case 11:
			return ct_im_bmh1_1_11(priv->bmh1);

		// Test-1-12
		case 12:
			return ct_im_bmh1_1_12(priv->bmh1);

		// Test-1-13
		case 13:
			return ct_im_bmh1_1_13(priv->bmh1);

		// Test-1-14
		case 14:
			return ct_im_bmh1_1_14(priv->bmh1);

		// Test-1-15
		case 15:
			return ct_im_bmh1_1_15(priv->bmh1);

		// Test-1-16
		case 16:
			return ct_im_bmh1_1_16(priv->bmh1);

		// Test-1-17
		case 17:
			return ct_im_bmh1_1_17(priv->bmh1);

		// Test-1-18
		case 18:
			return ct_im_bmh2_1_18(priv->bmh2);

		// Test-1-19
		case 19:
			return ct_im_bmh2_1_19(priv->bmh2);

		// Test-1-20
		case 20:
			return ct_im_bmh2_1_20(priv->bmh2);

		// Test-1-21
		case 21:
			return ct_im_bmh2_1_21(priv->bmh2);

		// Test-1-22
		case 22:
			return ct_im_bmh2_1_22(priv->bmh2);

		// Test-1-23
		case 23:
			return ct_im_bmh2_1_23(priv->bmh2);

		// Test-1-24
		case 24:
			return ct_im_bmh2_1_24(priv->bmh2);

		// Test-1-25
		case 25:
			return ct_im_bmh2_1_25(priv->bmh2);

		// Test-1-26
		case 26:
			return ct_im_bmh2_1_26(priv->bmh2);

		// Test-1-27
		case 27:
			return ct_im_bmh2_1_27(priv->bmh2);

		// Test-1-28
		case 28:
			return ct_im_bmh2_1_28(priv->bmh2);

		// Test-1-29
		case 29:
			return ct_im_bmh2_1_29(priv->bmh2);

		// Test-1-30
		case 30:
			return ct_im_bmh2_1_30(priv->bmh2);

		// Test-1-31
		case 31:
			return ct_im_bmh2_1_31(priv->bmh2);

		// Test-1-32
		case 32:
			return ct_im_bmh2_1_32(priv->bmh2);

		// Test-1-33
		case 33:
			return ct_im_bmh2_1_33(priv->bmh2);

		// Test-1-34
		case 34:
			return ct_im_bmh3_1_34(priv->bmh3);

		// Test-1-35
		case 35:
			return ct_im_bmh3_1_35(priv->bmh3);

		// Test-1-36
		case 36:
			return ct_im_bmh3_1_36(priv->bmh3);

		// Test-1-37
		case 37:
			return ct_im_bmh3_1_37(priv->bmh3);

		// Test-1-38
		case 38:
			return ct_im_bmh3_1_38(priv->bmh3);

		// Test-1-39
		case 39:
			return ct_im_bmh3_1_39(priv->bmh3);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}
	return D_DDIM_INPUT_PARAM_ERROR;
}

static kint32 ctImBmhRun2(CtImBmh *self)
{
	CtImBmhPrivate *priv = CT_IM_BMH_GET_PRIVATE(self);		
	switch(priv->ctIdx2nd){
		// Test-2-1
		case 1:
			return ct_im_bmh4_2_1(priv->bmh4);

		// Test-2-2
		case 2:
			return ct_im_bmh4_2_2(priv->bmh4);

		// Test-2-3
		case 3:
			return ct_im_bmh4_2_3(priv->bmh4);

		// Test-2-4
		case 4:
			return ct_im_bmh4_2_4(priv->bmh4);

		// Test-2-5
		case 5:
			return ct_im_bmh4_2_5(priv->bmh4);

		// Test-2-6
		case 6:
			return ct_im_bmh4_2_6(priv->bmh4);

		// Test-2-7
		case 7:
			return ct_im_bmh4_2_7(priv->bmh4);

		// Test-2-8
		case 8:
			return ct_im_bmh4_2_8(priv->bmh4);

		// Test-2-9
		case 9:
			return ct_im_bmh4_2_9(priv->bmh4);

		// Test-2-10
		case 10:
			return ct_im_bmh4_2_10(priv->bmh4);

		// Test-2-11
		case 11:
			return ct_im_bmh4_2_11(priv->bmh4);

		// Test-2-12
		case 12:
			return ct_im_bmh4_2_12(priv->bmh4);

		// Test-2-13
		case 13:
			return ct_im_bmh4_2_13(priv->bmh4);

		// Test-2-14
		case 14:
			return ct_im_bmh4_2_14(priv->bmh4);

		// Test-2-15
		case 15:
			return ct_im_bmh4_2_15(priv->bmh4);

		// Test-2-16
		case 16:
			return ct_im_bmh4_2_16(priv->bmh4);

		// Test-2-17
		case 17:
			return ct_im_bmh4_2_17(priv->bmh4);

		// Test-2-18
		case 18:
			return ct_im_bmh4_2_18(priv->bmh4);

		// Test-2-19
		case 19:
			return ct_im_bmh4_2_19(priv->bmh4);

		// Test-2-20
		case 20:
			return ct_im_bmh4_2_20(priv->bmh4);

		// Test-2-21
		case 21:
			return ct_im_bmh4_2_21(priv->bmh4);

		// Test-2-22
		case 22:
			return ct_im_bmh4_2_22(priv->bmh4);

		// Test-2-23
		case 23:
			return ct_im_bmh4_2_23(priv->bmh4);

		// Test-2-24
		case 24:
			return ct_im_bmh4_2_24(priv->bmh4);

		// Test-2-25
		case 25:
			return ct_im_bmh4_2_25(priv->bmh4);

		// Test-2-26
		case 26:
			return ct_im_bmh4_2_26(priv->bmh4);

		// Test-2-27
		case 27:
			return ct_im_bmh4_2_27(priv->bmh4);

		// Test-2-28
		case 28:
			return ct_im_bmh4_2_28(priv->bmh4);

		// Test-2-29
		case 29:
			return ct_im_bmh4_2_29(priv->bmh4);

		// Test-2-30
		case 30:
			return ct_im_bmh4_2_30(priv->bmh4);

		// Test-2-31
		case 31:
			return ct_im_bmh4_2_31(priv->bmh4);

		// Test-2-32
		case 32:
			return ct_im_bmh4_2_32(priv->bmh4);

		// Test-2-33
		case 33:
			return ct_im_bmh4_2_33(priv->bmh4);

		// Test-2-34
		case 34:
			return ct_im_bmh4_2_34(priv->bmh4);

		// Test-2-35
		case 35:
			return ct_im_bmh4_2_35(priv->bmh4);

		// Test-2-36
		case 36:
			return ct_im_bmh4_2_36(priv->bmh4);

		// Test-2-37
		case 37:
			return ct_im_bmh4_2_37(priv->bmh4);

		// Test-2-38
		case 38:
			return ct_im_bmh4_2_38(priv->bmh4);

		// Test-2-39
		case 39:
			return ct_im_bmh4_2_39(priv->bmh4);

		// Test-2-40
		case 40:
			return ct_im_bmh4_2_40(priv->bmh4);

		// Test-2-41
		case 41:
			return ct_im_bmh4_2_41(priv->bmh4);

		// Test-2-42
		case 42:
			return ct_im_bmh4_2_42(priv->bmh4);

		// Test-2-43
		case 43:
			return ct_im_bmh4_2_43(priv->bmh4);

		// Test-2-44
		case 44:
			return ct_im_bmh4_2_44(priv->bmh4);

		// Test-2-45
		case 45:
			return ct_im_bmh4_2_45(priv->bmh4);

		// Test-2-46
		case 46:
			return ct_im_bmh4_2_46(priv->bmh4);

		// Test-2-47
		case 47:
			return ct_im_bmh4_2_47(priv->bmh4);

		// Test-2-48
		case 48:
			return ct_im_bmh4_2_48(priv->bmh4);

		// Test-2-49
		case 49:
			return ct_im_bmh4_2_49(priv->bmh4);

		// Test-2-50
		case 50:
			return ct_im_bmh4_2_50(priv->bmh4);

		// Test-2-51
		case 51:
			return ct_im_bmh4_2_51(priv->bmh4);

		// Test-2-52
		case 52:
			return ct_im_bmh4_2_52(priv->bmh4);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}
	return D_DDIM_INPUT_PARAM_ERROR;
}

static kint32 ctImBmhRun3(CtImBmh *self)
{
	CtImBmhPrivate *priv = CT_IM_BMH_GET_PRIVATE(self);
	priv->bmh5->channelNo = priv->ctIdx3rd;	
	priv->bmh6->channelNo = priv->ctIdx3rd;	
	priv->bmh7->channelNo = priv->ctIdx3rd;				
	priv->bmh8->channelNo = priv->ctIdx3rd;	
	ddim_user_custom_l1l2cache_clean_flush_all(priv->usercustom);

	switch(priv->ctIdx2nd){
		// Test-3-1
		case 1:
			return ct_im_bmh5_3_1(priv->bmh5);

		// Test-3-2
		case 2:
			return ct_im_bmh5_3_2(priv->bmh5);

		// Test-3-3
		case 3:
			return ct_im_bmh5_3_3(priv->bmh5);

		// Test-3-4
		case 4:
			return ct_im_bmh5_3_4(priv->bmh5);

		// Test-3-5
		case 5:
			return ct_im_bmh5_3_5(priv->bmh5);

		// Test-3-6
		case 6:
			return ct_im_bmh5_3_6(priv->bmh5);

		// Test-3-7
		case 7:
			return ct_im_bmh5_3_7(priv->bmh5);

		// Test-3-8
		case 8:
			return ct_im_bmh5_3_8(priv->bmh5);

		// Test-3-9
		case 9:
			return ct_im_bmh5_3_9(priv->bmh5);

		// Test-3-10
		case 10:
			return ct_im_bmh5_3_10(priv->bmh5);

		// Test-3-11
		case 11:
			return ct_im_bmh6_3_11(priv->bmh6);

		// Test-3-12
		case 12:
			return ct_im_bmh6_3_12(priv->bmh6);

		// Test-3-13
		case 13:
			return ct_im_bmh6_3_13(priv->bmh6);

		// Test-3-14
		case 14:
			return ct_im_bmh6_3_14(priv->bmh6);

		// Test-3-15
		case 15:
			return ct_im_bmh6_3_15(priv->bmh6);

		// Test-3-16
		case 16:
			return ct_im_bmh6_3_16(priv->bmh6);

		// Test-3-17
		case 17:
			return ct_im_bmh6_3_17(priv->bmh6);

		// Test-3-18
		case 18:
			return ct_im_bmh6_3_18(priv->bmh6);

		// Test-3-19
		case 19:
			return ct_im_bmh6_3_19(priv->bmh6);

		// Test-3-20
		case 20:
			return ct_im_bmh6_3_20(priv->bmh6);

		// Test-3-21
		case 21:
			return ct_im_bmh6_3_21(priv->bmh6);

		// Test-3-22
		case 22:
			return ct_im_bmh6_3_22(priv->bmh6);

		// Test-3-23
		case 23:
			return ct_im_bmh7_3_23(priv->bmh7);

		// Test-3-24
		case 24:
			return ct_im_bmh7_3_24(priv->bmh7);

		// Test-3-25
		case 25:
			return ct_im_bmh7_3_25(priv->bmh7);

		// Test-3-26
		case 26:
			return ct_im_bmh7_3_26(priv->bmh7);

		// Test-3-27
		case 27:
			return ct_im_bmh7_3_27(priv->bmh7);

		// Test-3-28
		case 28:
			return ct_im_bmh7_3_28(priv->bmh7);

		// Test-3-29
		case 29:
			return ct_im_bmh7_3_29(priv->bmh7);

		// Test-3-30
		case 30:
			return ct_im_bmh7_3_30(priv->bmh7);

		// Test-3-31
		case 31:
			return ct_im_bmh7_3_31(priv->bmh7);

		// Test-3-32
		case 32:
			return ct_im_bmh8_3_32(priv->bmh8);

		// Test-3-33
		case 33:
			return ct_im_bmh8_3_33(priv->bmh8);

		// Test-3-34
		case 34:
			return ct_im_bmh8_3_34(priv->bmh8);

		// Test-3-35
		case 35:
			return ct_im_bmh8_3_35(priv->bmh8);

		// Test-3-36
		case 36:
			return ct_im_bmh8_3_36(priv->bmh8);

		// Test-3-37
		case 37:
			return ct_im_bmh8_3_37(priv->bmh8);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}
	return D_DDIM_INPUT_PARAM_ERROR;
}

/*
 * PUBLIC
 */
void ct_im_bmh_print_debug_sadr(CtImBmh *self)
{
	CtImBmhPrivate *priv = CT_IM_BMH_GET_PRIVATE(self);

	for(priv->loop0 = 0; priv->loop0 < 2; priv->loop0++){
		Ddim_Print(("IO_BMH[%d]\n", priv->loop0));
		for(priv->loop1 = 0; priv->loop1 < 2; priv->loop1++){
			for(priv->loop2 = 0; priv->loop2 < 128; priv->loop2++){
				Ddim_Print(("[%lu][%lu] = 0x%lx\n", priv->loop1, priv->loop2,
						IO_BMH[priv->loop0].SADR.word[priv->loop1][priv->loop2]));
			}
		}
	}
}

void ct_im_bmh_run(CtImBmh *self)
{
	CtImBmhPrivate *priv = CT_IM_BMH_GET_PRIVATE(self);
	
#ifdef CO_MSG_PRINT_ON
	kint32 result = D_DDIM_INPUT_PARAM_ERROR;
#endif
	static BOOL is_init = 0;

	Ddim_Print(("ct_im_bmh_run(%u, %u, %u) Begin\n", priv->ctIdx1st, priv->ctIdx2nd, priv->ctIdx3rd));

	if(is_init == 0){
#ifdef CO_DEBUG_ON_PC
		memset((kpointer)&IO_BMH, '\0', sizeof(IO_BMH));
//		Dd_Top_Set_CLKSTOP14_BMHAX(1);
//		Dd_Top_Set_CLKSTOP14_BMHCK(1);
#endif // CO_DEBUG_ON_PC

		if(!((priv->ctIdx1st == 1) && (priv->ctIdx2nd == 1))){
			Ddim_Print(("Im_BMH_Init() Begin\n"));
			Im_BMH_Init(0);
			Im_BMH_Init(1);

			Ddim_Print(("Im_BMH_Init() End\n"));
			is_init = 1;
		}
	}

#ifdef CO_BMH_DEBUG
	Im_BMH_Print_ClockStatus();
#endif

	switch(priv->ctIdx1st){
		case 1:
			CtImBmh_D_IM_BMH_RESULT(ctImBmhRun1(self));
			break;

		case 2:
			CtImBmh_D_IM_BMH_RESULT(ctImBmhRun2(self));
			break;

		case 3:
			CtImBmh_D_IM_BMH_RESULT(ctImBmhRun3(self));
			break;

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}


#ifdef CO_MSG_PRINT_ON
	Ddim_Print(("result = 0x%x\n", result));
#endif

#ifdef CO_BMH_DEBUG
	Im_BMH_Print_ClockStatus();
#endif

	Ddim_Print(("ct_im_bmh_run(%u, %u, %u) End\n", priv->ctIdx1st, priv->ctIdx2nd, priv->ctIdx3rd));

	return;
}

void ct_im_bmh_main(CtImBmh *self, kint32 argc, kchar** argv)//线程
{
	CtImBmhPrivate *priv = CT_IM_BMH_GET_PRIVATE(self);

//	/* 线程创建，klib找不到etk_init */
//	etk_init(&argc, &argv);
//	int i;

//	/*	执行程序，线程开始操作*/
//	for(i=0;i<3;i++){
//		Ddim_Print(("ct_im_bmh_main: parameter error.\n"));
//		return;
//	}

	if(argc < 3){
		Ddim_Print(("ct_im_bmh_main: parameter error.\n"));
		return;
	}

	priv->ctIdx1st = (kuint32)atoi((const char*)argv[1]);
	priv->ctIdx2nd = (kuint32)atoi((const char*)argv[2]);
	priv->ctIdx3rd = (kuint32)atoi((const char*)argv[3]);

	ct_im_bmh_run(self);

//	/*	返回线程*/
//    etk_main();
//   	return 0;
}

/*
 * 此函数用于创建对象
 * @     
 * @return:
 */
CtImBmh* ct_im_bmh_new(void) 
{
    CtImBmh *self = k_object_new_with_private(CT_TYPE_IM_BMH, sizeof(CtImBmhPrivate));
    return self;
}
