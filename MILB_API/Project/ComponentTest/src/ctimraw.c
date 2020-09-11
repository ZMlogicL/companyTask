/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈元
*@brief : CtImRaw
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include <stdlib.h>
#include <string.h>

#include "jdsraw.h"
#include "im_raw.h"
#include "driver_common.h"
#include "ctimrawconfig.h"
#include "ctimrawvarify.h"
#include "ctimrawtest1.h"
#include "ctimrawtest2.h"
#include "ctimraw.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImRaw, ct_im_raw)
#define CT_IM_RAW_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImRawPrivate, CT_TYPE_IM_RAW))


struct _CtImRawPrivate
{
	CtImRawConfig *ctImRawConfig;
	CtImRawVarify *ctImRawVarify;
	CtImRawTest1 *ctImRawTest1;
	CtImRawTest2 *ctImRawTest2;
	kint32 retval;
	Test2Val test2Val;
};


/********
 * IMPL
 */
static void ct_im_raw_constructor(CtImRaw *self)
{
	CtImRawPrivate *priv = CT_IM_RAW_GET_PRIVATE(self);

	priv->ctImRawConfig = ct_im_raw_config_new();
	priv->ctImRawVarify = ct_im_raw_varify_new();
	priv->ctImRawTest1 = ct_im_raw_test1_new();
	priv->ctImRawTest2 = ct_im_raw_test2_new();
}

static void ct_im_raw_destructor(CtImRaw *self)
{
//	CtImRawPrivate *priv = CT_IM_RAW_GET_PRIVATE(self);
}


/********
 * PUBLIC
 */
kuint32 ct_im_raw_get_enc_size(CtImRaw* self)
{
	CtImRawPrivate *priv = CT_IM_RAW_GET_PRIVATE(self);

	return ct_im_raw_config_get_enc_byte(priv->ctImRawConfig);
}

// Test Code Main
void ct_im_raw_main(CtImRaw* self, int argc, char** argv)
{
	CtImRawPrivate *priv = CT_IM_RAW_GET_PRIVATE(self);
	kuint32 testNum0;
	kuint32 testNum1;

#if 0
#ifndef CO_DEBUG_ON_PC
	// Data area value all crear!!!
	ct_im_raw_config_clear(priv->ctImRawConfig);
#endif	// CO_DEBUG_ON_PC
#endif

	Ddim_Print(("ct_im_raw_main Start\n"));

	ct_im_raw_config_init_param(priv->ctImRawConfig);
//	Ddim_Print(("init param OK\n"));
	priv->retval = ct_im_raw_varify_test_init(priv->ctImRawVarify);

//	Ddim_Print(("test init OK\n"));

	testNum0 = (kuint32)atoi((const char*)argv[1]);
	testNum1 = (kuint32)atoi((const char*)argv[2]);

	switch (testNum0) {
		// PC simulator
		case 1:
			switch (testNum1) {
				// Open/Close(pol_sem)
				case 0:
					Ddim_Print(("raw test1_0 Start\n"));
					priv->retval = ct_im_raw_test1_0(priv->ctImRawTest1);
					Ddim_Print(("raw test1_0 End\n"));
					break;
				// Open/Close(twai_sem)
				case 1:
					Ddim_Print(("raw test1_1 Start\n"));
					priv->retval = ct_im_raw_test1_1(priv->ctImRawTest1);
					Ddim_Print(("raw test1_1 End\n"));
					break;
				// Open/Close(parameter error)
				case 2:
					Ddim_Print(("raw test1_2 Start\n"));
					priv->retval = ct_im_raw_test1_2(priv->ctImRawTest1);
					Ddim_Print(("raw test1_2 End\n"));
					break;
				// Ctrl_CodeTbl(normal end)
				case 3:
					Ddim_Print(("raw test1_3 Start\n"));
					priv->retval = ct_im_raw_test1_3(priv->ctImRawTest1);
					Ddim_Print(("raw test1_3 End\n"));
					break;
				// Ctrl_CodeTbl(parameter error)
				case 4:
					Ddim_Print(("raw test1_4 Start\n"));
					priv->retval = ct_im_raw_test1_4(priv->ctImRawTest1);
					Ddim_Print(("raw test1_4 End\n"));
					break;
				// Ctrl_CodeTbl(macro busy)
				case 5:
					Ddim_Print(("raw test1_5 Start\n"));
					priv->retval = ct_im_raw_test1_5(priv->ctImRawTest1);
					Ddim_Print(("raw test1_5 End\n"));
					break;
				// Ctrl_Enc(normal end)
				case 6:
					Ddim_Print(("raw test1_6 Start\n"));
					priv->retval = ct_im_raw_test1_6(priv->ctImRawTest1);
					Ddim_Print(("raw test1_6 End\n"));
					break;
				// Ctrl_Enc(parameter error)
				case 7:
					Ddim_Print(("raw test1_7 Start\n"));
					priv->retval = ct_im_raw_test1_7(priv->ctImRawTest1);
					Ddim_Print(("raw test1_7 End\n"));
					break;
				// Ctrl_Enc(macro busy)
				case 8:
					Ddim_Print(("raw test1_8 Start\n"));
					priv->retval = ct_im_raw_test1_8(priv->ctImRawTest1);
					Ddim_Print(("raw test1_8 End\n"));
					break;
				// Ctrl_Dec(normal end)
				case 9:
					Ddim_Print(("raw test1_9 Start\n"));
					priv->retval = ct_im_raw_test1_9(priv->ctImRawTest1);
					Ddim_Print(("raw test1_9 End\n"));
					break;
				// Ctrl_Dec(parameter error)
				case 10:
					Ddim_Print(("raw test1_10 Start\n"));
					priv->retval = ct_im_raw_test1_10(priv->ctImRawTest1);
					Ddim_Print(("raw test1_10 End\n"));
					break;
				// Ctrl_Dec(macro busy)
				case 11:
					Ddim_Print(("raw test1_11 Start\n"));
					priv->retval = ct_im_raw_test1_11(priv->ctImRawTest1);
					Ddim_Print(("raw test1_11 End\n"));
					break;
				// _Start(normal end)
				case 12:
					Ddim_Print(("raw test1_12 Start\n"));
					priv->retval = ct_im_raw_test1_12(priv->ctImRawTest1);
					Ddim_Print(("raw test1_12 End\n"));
					break;
				// _Start(system error)
				case 13:
					Ddim_Print(("raw test1_13 Start\n"));
					priv->retval = ct_im_raw_test1_13(priv->ctImRawTest1);
					Ddim_Print(("raw test1_13 End\n"));
					break;
				// _Start(macro busy)
				case 14:
					Ddim_Print(("raw test1_14 Start\n"));
					priv->retval = ct_im_raw_test1_14(priv->ctImRawTest1);
					Ddim_Print(("raw test1_14 End\n"));
					break;
				// Wait_End_Enc(normal end)
				case 15:
					Ddim_Print(("raw test1_15 Start\n"));
					priv->retval = ct_im_raw_test1_15(priv->ctImRawTest1);
					Ddim_Print(("raw test1_15 End\n"));
					break;
				// Wait_End_Enc(parameter error)
				case 16:
					Ddim_Print(("raw test1_16 Start\n"));
					priv->retval = ct_im_raw_test1_16(priv->ctImRawTest1);
					Ddim_Print(("raw test1_16 End\n"));
					break;
				// Wait_End_Enc(system error)
				case 17:
					Ddim_Print(("raw test1_17 Start\n"));
					priv->retval = ct_im_raw_test1_17(priv->ctImRawTest1);
					Ddim_Print(("raw test1_17 End\n"));
					break;
				// Wait_End_Enc(R_AXI error)
				case 18:
					Ddim_Print(("raw test1_18 Start\n"));
					priv->retval = ct_im_raw_test1_18(priv->ctImRawTest1);
					Ddim_Print(("raw test1_18 End\n"));
					break;
				// Wait_End_Enc(W_AXI error)
				case 19:
					Ddim_Print(("raw test1_19 Start\n"));
					priv->retval = ct_im_raw_test1_19(priv->ctImRawTest1);
					Ddim_Print(("raw test1_19 End\n"));
					break;
				// Wait_End_Enc(force stop)
				case 20:
					Ddim_Print(("raw test1_20 Start\n"));
					priv->retval = ct_im_raw_test1_20(priv->ctImRawTest1);
					Ddim_Print(("raw test1_20 End\n"));
					break;
				// Wait_End_Dec(normal end)
				case 21:
					Ddim_Print(("raw test1_21 Start\n"));
					priv->retval = ct_im_raw_test1_21(priv->ctImRawTest1);
					Ddim_Print(("raw test1_21 End\n"));
					break;
				// Wait_End_Dec(parameter error)
				case 22:
					Ddim_Print(("raw test1_22 Start\n"));
					priv->retval = ct_im_raw_test1_22(priv->ctImRawTest1);
					Ddim_Print(("raw test1_22 End\n"));
					break;
				// Wait_End_Dec(system error)
				case 23:
					Ddim_Print(("raw test1_23 Start\n"));
					priv->retval = ct_im_raw_test1_23(priv->ctImRawTest1);
					Ddim_Print(("raw test1_23 End\n"));
					break;
				// Wait_End_Dec(R_AXI error)
				case 24:
					Ddim_Print(("raw test1_24 Start\n"));
					priv->retval = ct_im_raw_test1_24(priv->ctImRawTest1);
					Ddim_Print(("raw test1_24 End\n"));
					break;
				// Wait_End_Dec(W_AXI error)
				case 25:
					Ddim_Print(("raw test1_25 Start\n"));
					priv->retval = ct_im_raw_test1_25(priv->ctImRawTest1);
					Ddim_Print(("raw test1_25 End\n"));
					break;
				// Wait_End_Dec(force stop)
				case 26:
					Ddim_Print(("raw test1_26 Start\n"));
					priv->retval = ct_im_raw_test1_26(priv->ctImRawTest1);
					Ddim_Print(("raw test1_26 End\n"));
					break;
#if 0	// 1-20(Wait_End_Enc(force stop))�Ŏ��{�ς�
				// Stop(normal end)
				case 27:
					Ddim_Print(("raw test1_27 Start\n"));
					priv->retval = ct_im_raw_test1_27();
					Ddim_Print(("raw test1_27 End\n"));
					break;
#endif	// 1-20(Wait_End_Enc(force stop))�Ŏ��{�ς�
				// Stop(system error)
				case 28:
					Ddim_Print(("raw test1_28 Start\n"));
					priv->retval = ct_im_raw_test1_28(priv->ctImRawTest1);
					Ddim_Print(("raw test1_28 End\n"));
					break;
#if 0	// �m�F�̂��悤���Ȃ�
				// Stop(macro busy)
				case 29:
					Ddim_Print(("raw test1_29 Start\n"));
					priv->retval = ct_im_raw_test1_29();
					Ddim_Print(("raw test1_29 End\n"));
					break;
#endif	// �m�F�̂��悤���Ȃ�
				// Get_AXI_Status(normal end)
				case 30:
					Ddim_Print(("raw test1_30 Start\n"));
					priv->retval = ct_im_raw_test1_30(priv->ctImRawTest1);
					Ddim_Print(("raw test1_30 End\n"));
					break;
				// Get_AXI_Status(parameter error)
				case 31:
					Ddim_Print(("raw test1_31 Start\n"));
					priv->retval = ct_im_raw_test1_31(priv->ctImRawTest1);
					Ddim_Print(("raw test1_31 End\n"));
					break;
				// Int_Handler(normal end)
				case 32:
					Ddim_Print(("raw test1_32 Start\n"));
					priv->retval = ct_im_raw_test1_32(priv->ctImRawTest1);
					Ddim_Print(("raw test1_32 End\n"));
					break;
				// Int_Handler(R_AXI error)
				case 33:
					Ddim_Print(("raw test1_33 Start\n"));
					priv->retval = ct_im_raw_test1_33(priv->ctImRawTest1);
					Ddim_Print(("raw test1_33 End\n"));
					break;
				// Int_Handler(W_AXI error)
				case 34:
					Ddim_Print(("raw test1_34 Start\n"));
					priv->retval = ct_im_raw_test1_34(priv->ctImRawTest1);
					Ddim_Print(("raw test1_34 End\n"));
					break;
				default:
					Ddim_Print(("IMRAW NO COMMAND\n"));
					return;
			}
			break;
		// Palladium
		case 2:
			switch(testNum1){
				case 0:
					Ddim_Print(("raw test2_0 Start\n"));
					priv->retval = ct_im_raw_test2_0(priv->ctImRawTest2);
					Ddim_Print(("raw test2_0 End\n"));
					break;
				case 1:
					Ddim_Print(("raw test2_1 Start\n"));
					priv->retval = ct_im_raw_test2_1(priv->ctImRawTest2);
					Ddim_Print(("raw test2_1 End\n"));
					ct_im_raw_varify_dump_reg(priv->ctImRawVarify);
					break;
				case 2:
					Ddim_Print(("raw test2_2 Start\n"));
					priv->retval = ct_im_raw_test2_2(priv->ctImRawTest2, 0);
					Ddim_Print(("raw test2_2 End\n"));

					ct_im_raw_varify_dump_reg(priv->ctImRawVarify);
					break;
				case 3:
					Ddim_Print(("raw test2_3 Start\n"));
					priv->retval = ct_im_raw_test2_3(priv->ctImRawTest2);
					Ddim_Print(("raw test2_3 End\n"));

					ct_im_raw_varify_dump_reg(priv->ctImRawVarify);
					break;
				case 4:
		#ifndef D_CT_IM_RAW_PT_TEST
		//			ct_im_raw_load_8bit_image();
		#endif
					Ddim_Print(("raw test2_4 Start\n"));
					priv->retval = ct_im_raw_test2_4(priv->ctImRawTest2);
					Ddim_Print(("raw test2_4 End\n"));

					ct_im_raw_varify_dump_reg(priv->ctImRawVarify);
					break;
				case 5:
		#ifndef D_CT_IM_RAW_PT_TEST
		//			ct_im_raw_load_8bit_image();
		#endif
					Ddim_Print(("raw test2_5 Start\n"));
					priv->retval = ct_im_raw_test2_5(priv->ctImRawTest2);
					Ddim_Print(("raw test2_5 End\n"));

					ct_im_raw_varify_dump_reg(priv->ctImRawVarify);
					break;
				case 6:
					Ddim_Print(("raw test2_6 Start\n"));
					priv->retval = ct_im_raw_test2_6(priv->ctImRawTest2);
					Ddim_Print(("raw test2_6 End\n"));
					break;
				case 7:
					Ddim_Print(("raw test2_7 Start\n"));
					priv->retval = ct_im_raw_test2_7(priv->ctImRawTest2);
					Ddim_Print(("raw test2_7 End\n"));
					break;
				case 8:
					Ddim_Print(("raw test2_8 Start\n"));
					priv->retval = ct_im_raw_test2_8(priv->ctImRawTest2);
					Ddim_Print(("raw test2_8 End\n"));
					break;
				case 9:
					Ddim_Print(("raw test2_9 Start\n"));
					priv->retval = ct_im_raw_test2_9(priv->ctImRawTest2);
					Ddim_Print(("raw test2_9 End\n"));
					break;
				case 10:
					Ddim_Print(("raw test2_10 Start\n"));
					priv->retval = ct_im_raw_test2_10(priv->ctImRawTest2);
					Ddim_Print(("raw test2_10 End\n"));
					break;
				case 11:
					Ddim_Print(("raw test2_11 Start\n"));
					priv->retval = ct_im_raw_test2_11(priv->ctImRawTest2);
					Ddim_Print(("raw test2_11 End\n"));

					ct_im_raw_varify_dump_reg(priv->ctImRawVarify);
					break;
				case 13:
					Ddim_Print(("raw test2_13 Start\n"));
					priv->retval = ct_im_raw_test2_2(priv->ctImRawTest2, 1);
					Ddim_Print(("raw test2_13 End\n"));
					break;
				case 14:
					Ddim_Print(("raw test2_14 Start\n"));
					priv->test2Val.test2Val1 = (kuint32)atoi((const char*)argv[2]);
					priv->test2Val.test2Val2 = (kuint32)atoi((const char*)argv[3]);
					priv->test2Val.test2Val3 = (kuint32)atoi((const char*)argv[4]);
					priv->test2Val.test2Val4 = (kuint32)atoi((const char*)argv[5]);
					priv->test2Val.test2Val5 = (kuint32)atoi((const char*)argv[6]);
					priv->test2Val.test2Val6 = (kuint32)atoi((const char*)argv[7]);
					priv->test2Val.test2Val7 = (kuint32)atoi((const char*)argv[8]);
					priv->test2Val.test2Val8 = (kuint32)atoi((const char*)argv[9]);
					priv->retval = ct_im_raw_test2_14(priv->ctImRawTest2, priv->test2Val);
					Ddim_Print(("raw test2_14 End\n"));
					break;
				default:
					Ddim_Print(("IMRAW NO COMMAND\n"));
					return;
			}
			break;
		default:
			Ddim_Print(("IMRAW NO COMMAND\n"));
			return;
	}

#ifndef D_CT_IM_RAW_PT_TEST
	if (priv->retval) {
		Ddim_Print(("IMRAW COMMAND ERROR\n"));
//		DDIM_User_Dly_Tsk(1000);
//		while(1);
	} else {
		Ddim_Print(("IMRAW COMMAND OK\n"));
	}
#else
	if (priv->retval) {
		Ddim_Print(("IMRAW COMMAND ERROR\n"));
	} else {
		Ddim_Print(("IMRAW COMMAND OK\n"));
	}
#endif

	return;
}

// Test Code Main
void ct_im_raw_main_pc(CtImRaw* self, int argc, char** argv)
{
	CtImRawPrivate *priv = CT_IM_RAW_GET_PRIVATE(self);


	Ddim_Print(("RAW Test 2_0\n"));
	priv->retval = ct_im_raw_test2_0(priv->ctImRawTest2);
	ct_im_raw_varify_ret_print(priv->ctImRawVarify, priv->retval);
	Ddim_Print(("RAW Test 2_1\n"));
	priv->retval = ct_im_raw_varify_test_init(priv->ctImRawVarify);
	ct_im_raw_varify_dump_reg(priv->ctImRawVarify);
	ct_im_raw_varify_ret_print(priv->ctImRawVarify, priv->retval);

	Ddim_Print(("RAW Test 2_10\n"));
	priv->retval = ct_im_raw_test2_10(priv->ctImRawTest2);
	ct_im_raw_varify_ret_print(priv->ctImRawVarify, priv->retval);
	Ddim_Print(("RAW Test 2_11\n"));
	priv->retval = ct_im_raw_test2_11(priv->ctImRawTest2);
	ct_im_raw_varify_ret_print(priv->ctImRawVarify, priv->retval);
	Ddim_Print(("RAW Test 2_12\n"));
	priv->retval = ct_im_raw_test2_12(priv->ctImRawTest2);
	ct_im_raw_varify_ret_print(priv->ctImRawVarify, priv->retval);

	return;
}

CtImRaw* ct_im_raw_new(void)
{
	CtImRaw* self = k_object_new_with_private(CT_TYPE_IM_RAW, sizeof(CtImRawPrivate));

	return self;
}

