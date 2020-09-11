/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-00
*@author              :王印斌
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

// #include "ct_im_cnr.h"
#include "im_cnr.h"
#include "dd_top.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#include "im_rdma.h"
#include "jdscnr.h"
#include "ctimcnr.h"
#include "ctimcnr1.h"
#include "ctimcnr2.h"
#include "ctimcnr3.h"
#include "ctimcnr4.h"
#include "ctimcnr5.h"
#include "ctimcnr6.h"
#include "ctimcnr7.h"
#include "ctimcnr8.h"
#include "ctimcnr9.h"
#include "ctimcnr10.h"
#include "ctimcnr11.h"
#include "ctimcnr12.h"
#include "ctimcnr13.h"
#include "ctimcnr14.h"

#include <string.h>
#include <stdlib.h>

G_DEFINE_TYPE(CtImCnr, ct_im_cnr, G_TYPE_OBJECT); 
#define CT_IM_CNR_GET_PRIVATE(o) (G_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_CNR, CtImCnrPrivate))

#define CtImCnr_M_16ROUNDUP(a)	((((a)+0x0F) >> 4) << 4)		/**< 16 byte alignment */

struct _CtImCnrPrivate
{
};

static void 	ctImCnrOflPrintDebugCsprEdgeTbl(UCHAR ch);
static void 	ctImCnrOtfPrintDebugCsprEdgeTbl(UCHAR ch);
static INT32 	ctImCnrRun1(CtImCnr* self, const UINT32 ctNo2nd);

static void ct_im_cnr_constructor(CtImCnr *self)
{
	// CtImCnrPrivate *priv = CT_IM_CNR_GET_PRIVATE(self);
}

static void ct_im_cnr_destructor(CtImCnr  *object)
{
}

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// nothing special.

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// nothing special.

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
UINT32 gCT_IM_CNR_In_Addr = CtImCnr_D_IM_CNR_TEST_IMG_SRC_ADDR;
UINT32 gCT_IM_CNR_Out_Addr = CtImCnr_D_IM_CNR_TEST_IMG_DST_ADDR;

/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
#ifdef CO_MSG_PRINT_ON
#define D_IM_CNR_RESULT(statement)		result = statement
#else
#define D_IM_CNR_RESULT
#endif

static void ctImCnrOflPrintDebugCsprEdgeTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("CESCLBD_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_1));
		Ddim_Print(("CESCLBD_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_2));
		Ddim_Print(("CESCLBD_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_3));
		Ddim_Print(("CESCLBD_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_4));
		Ddim_Print(("CESCLBD_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLBD.CESCLBD2.bit.CESCLBD_5));

		Ddim_Print(("CESCLOF_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_0));
		Ddim_Print(("CESCLOF_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_1));
		Ddim_Print(("CESCLOF_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_2));
		Ddim_Print(("CESCLOF_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_3));
		Ddim_Print(("CESCLOF_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_4));
		Ddim_Print(("CESCLOF_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_5));

		Ddim_Print(("CESCLGA_0 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLGA.CESCLGA1.bit.CESCLGA_0));
		Ddim_Print(("CESCLGA_1 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLGA.CESCLGA1.bit.CESCLGA_1));
		Ddim_Print(("CESCLGA_2 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLGA.CESCLGA1.bit.CESCLGA_2));
		Ddim_Print(("CESCLGA_3 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLGA.CESCLGA1.bit.CESCLGA_3));
		Ddim_Print(("CESCLGA_4 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLGA.CESCLGA2.bit.CESCLGA_4));
		Ddim_Print(("CESCLGA_5 = 0x%x\n", io_cnr(loop)->OFL_CSPR_REG.CESCLGA.CESCLGA2.bit.CESCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

static void ctImCnrOtfPrintDebugCsprEdgeTbl(UCHAR ch)
{
	UCHAR loop, loopSta, loopEnd;

	Im_CNR_On_Pclk(ch);

	ct_im_cnr_get_loop_cnt(ch, &loopSta, &loopEnd);

	for(loop = loopSta; loop <= loopEnd; loop++){
		Ddim_Print(("ch[%d]\n",           loop));
		Ddim_Print(("CESCLBD_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_1));
		Ddim_Print(("CESCLBD_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_2));
		Ddim_Print(("CESCLBD_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_3));
		Ddim_Print(("CESCLBD_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLBD.CESCLBD1.bit.CESCLBD_4));
		Ddim_Print(("CESCLBD_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLBD.CESCLBD2.bit.CESCLBD_5));

		Ddim_Print(("CESCLOF_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_0));
		Ddim_Print(("CESCLOF_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_1));
		Ddim_Print(("CESCLOF_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_2));
		Ddim_Print(("CESCLOF_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLOF.CESCLOF1.bit.CESCLOF_3));
		Ddim_Print(("CESCLOF_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_4));
		Ddim_Print(("CESCLOF_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLOF.CESCLOF2.bit.CESCLOF_5));

		Ddim_Print(("CESCLGA_0 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLGA.CESCLGA1.bit.CESCLGA_0));
		Ddim_Print(("CESCLGA_1 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLGA.CESCLGA1.bit.CESCLGA_1));
		Ddim_Print(("CESCLGA_2 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLGA.CESCLGA1.bit.CESCLGA_2));
		Ddim_Print(("CESCLGA_3 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLGA.CESCLGA1.bit.CESCLGA_3));
		Ddim_Print(("CESCLGA_4 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLGA.CESCLGA2.bit.CESCLGA_4));
		Ddim_Print(("CESCLGA_5 = 0x%x\n", io_cnr(loop)->OTF_CSPR_REG.CESCLGA.CESCLGA2.bit.CESCLGA_5));
	}

	Im_CNR_Off_Pclk(ch);
}

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/

#ifdef CO_CNR_DEBUG
extern void Im_CNR_Print_ClockStatus(void);
#endif

static INT32 ctImCnrRun1(CtImCnr* self, const UINT32 ctNo2nd)
{
	CtImCnr1 *ctim1 = ct_im_cnr1_new();
	ctim1->ch1 = self->ctId;
	CtImCnr2 *ctim2 = ct_im_cnr2_new();
	ctim2->ch2 = self->ctId;
	CtImCnr3 *ctim3 = ct_im_cnr3_new();
	ctim3->ch3 = self->ctId;
	CtImCnr4 *ctim4 = ct_im_cnr4_new();
	ctim4->ch4 = self->ctId;
	CtImCnr5 *ctim5 = ct_im_cnr5_new();
	ctim5->ch5 = self->ctId;
	CtImCnr13 *ctim13 = ct_im_cnr13_new();
	ctim13->ch13 = self->ctId;	

	Ddim_Print(("ctImCnrRun1 ctNo2nd = 0x%x ctNo3rd = 0x%x\n", ctNo2nd, self->ctId));
	switch(ctNo2nd) {
		// Test-1-1
		case 1:
			return ct_im_cnr_ofl_1_1(ctim1);

		// Test-1-2
		case 2:
			return ct_im_cnr_ofl_1_2(ctim1);

		// Test-1-3
		case 3:
			return ct_im_cnr_ofl_1_3(ctim1);

		// Test-1-4
		case 4:
			return ct_im_cnr_ofl_1_4(ctim1);

		// Test-1-5
		case 5:
			return ct_im_cnr_ofl_1_5(ctim13);

		// Test-1-6
		case 6:
			return ct_im_cnr_ofl_1_6(ctim13);

		// Test-1-7
		case 7:
			return ct_im_cnr_ofl_1_7(ctim13);

		// Test-1-8
		case 8:
			return ct_im_cnr_ofl_1_8(ctim13);

		// Test-1-9
		case 9:
			return ct_im_cnr_ofl_1_9(ctim13);

		// Test-1-10
		case 10:
			return ct_im_cnr_ofl_1_10(ctim13);

		// Test-1-11
		case 11:
			return ct_im_cnr_ofl_1_11(ctim13);

		// Test-1-12
		case 12:
			return ct_im_cnr_ofl_1_12(ctim13);

		// Test-1-13
		case 13:
			return ct_im_cnr_ofl_1_13(ctim2);

		// Test-1-14
		case 14:
			return ct_im_cnr_ofl_1_14(ctim2);

		// Test-1-15
		case 15:
			return ct_im_cnr_ofl_1_15(ctim2);

		// Test-1-16
		case 16:
			return ct_im_cnr_ofl_1_16(ctim3);

		// Test-1-17
		case 17:
			return ct_im_cnr_ofl_1_17(ctim2);

		// Test-1-18
		case 18:
			return ct_im_cnr_ofl_1_18(ctim3);

		// Test-1-19
		case 19:
			return ct_im_cnr_ofl_1_19(ctim3);

		// Test-1-20
		case 20:
			return ct_im_cnr_ofl_1_20(ctim4);

		// Test-1-21
		case 21:
			return ct_im_cnr_ofl_1_21(ctim3);

		// Test-1-22
		case 22:
			return ct_im_cnr_ofl_1_22(ctim3);

		// Test-1-23
		case 23:
			return ct_im_cnr_ofl_1_23(ctim2);

		// Test-1-24
		case 24:
			return ct_im_cnr_ofl_1_24(ctim2);

		// Test-1-25
		case 25:
			return ct_im_cnr_ofl_1_25(ctim4);

		// Test-1-26
		case 26:
			return ct_im_cnr_ofl_1_26(ctim4);

		// Test-1-27
		case 27:
			return ct_im_cnr_ofl_1_27(ctim5);


// test RDMA
		// Test-1-30
		case 30:
			return ct_im_cnr_ofl_1_30(ctim2);
		// Test-1-31
		case 31:
			return ct_im_cnr_ofl_1_31(ctim5);
		// Test-1-32
		case 32:
			return ct_im_cnr_ofl_1_32(ctim2);
		// Test-1-33
		case 33:
			return ct_im_cnr_ofl_1_33(ctim3);
		// Test-1-34
		case 34:
			return ct_im_cnr_ofl_1_34(ctim3);
		// Test-1-35
		case 35:
			return ct_im_cnr_ofl_1_35(ctim4);
		// Test-1-36
		case 36:
			return ct_im_cnr_ofl_1_36(ctim4);
		// Test-1-37
		case 37:
			return ct_im_cnr_ofl_1_37(ctim5);
		// Test-1-38
		case 38:
			return ct_im_cnr_ofl_1_38(ctim5);
		// Test-1-39
		case 39:
			return ct_im_cnr_ofl_1_39(ctim5);
		// Test-1-40
		case 40:
			return ct_im_cnr_ofl_1_40(ctim5);
		// Test-1-41
		case 41:
			return ct_im_cnr_ofl_1_41(ctim5);
		// Test-1-42
		case 42:
			return ct_im_cnr_ofl_1_42(ctim5);
		// Test-1-43
		case 43:
			return ct_im_cnr_ofl_1_43(ctim5);
		// Test-1-44
		case 44:
			return ct_im_cnr_ofl_1_44(ctim5);
		// Test-1-45
		case 45:
			return ct_im_cnr_ofl_1_45(ctim5);
		// Test-1-46
		case 46:
			return ct_im_cnr_ofl_1_46(ctim5);
		// Test-1-47
		case 47:
			return ct_im_cnr_ofl_1_47(ctim5);
		// Test-1-48
		case 48:
			return ct_im_cnr_ofl_1_48(ctim5);
		// Test-1-49
		case 49:
			return ct_im_cnr_ofl_1_49(ctim5);
		// Test-1-50
		case 50:
			return ct_im_cnr_ofl_1_50(ctim5);
		// Test-1-51
		case 51:
			return ct_im_cnr_ofl_1_51(ctim5);
		// Test-1-52
		case 52:
			return ct_im_cnr_ofl_1_52(ctim1);
		// Test-1-53
		case 53:
			return ct_im_cnr_ofl_1_53(ctim1);
		// Test-1-54
		case 54:
			return ct_im_cnr_ofl_1_54(ctim2);
		// Test-1-55
		case 55:
			return ct_im_cnr_ofl_1_55(ctim3);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	k_object_unref(ctim1);
	k_object_unref(ctim2);
	k_object_unref(ctim3);
	k_object_unref(ctim4);
	k_object_unref(ctim5);
	k_object_unref(ctim13);

	return D_DDIM_INPUT_PARAM_ERROR;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_10: "
INT32 ct_im_cnr_6_10(CtImCnr* self)
{
	UCHAR ch = self->ctId;
	INT32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_TABLE	cnrTable = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0xFF,
		.of1 = 0xFF,
		.of2 = 0xFF,
		.of3 = 0xFF,
		.of4 = 0xFF,
		.of5 = 0xFF,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL	rdmaEdgeTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL*	C_EDGE_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Edge_Table(ch, &C_EDGE_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Edge_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Edge_Table(&cnrTable, &rdmaEdgeTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Edge_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_EDGE_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaEdgeTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOflPrintDebugCsprEdgeTbl(0);
		ctImCnrOflPrintDebugCsprEdgeTbl(1);
	}
	else{
		ctImCnrOflPrintDebugCsprEdgeTbl(ch);
	}

	return D_DDIM_OK;
}

#undef D_IM_CNR_FUNC_NAME
#define D_IM_CNR_FUNC_NAME "ct_im_cnr_6_21: "
INT32 ct_im_cnr_6_21(CtImCnr* self)
{
	UCHAR ch = self->ctId;
	INT32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_TABLE	cnrTable = {
		.bd1 = 0xFF,
		.bd2 = 0xFF,
		.bd3 = 0xFF,
		.bd4 = 0xFF,
		.bd5 = 0xFF,
		.of0 = 0xFF,
		.of1 = 0xFF,
		.of2 = 0xFF,
		.of3 = 0xFF,
		.of4 = 0xFF,
		.of5 = 0xFF,
		.gain0 = 0x7F,
		.gain1 = 0x7F,
		.gain2 = 0x7F,
		.gain3 = 0x7F,
		.gain4 = 0x7F,
		.gain5 = 0x7F,
	};
	T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL	rdmaEdgeTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL*	C_EDGE_TBL_ADDR;
	ULONG	size;

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Edge_Table(ch, &C_EDGE_TBL_ADDR, &size);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Edge_Table error = 0x%x\n", ret));
		return ret;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Edge_Table(&cnrTable, &rdmaEdgeTbl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Edge_Table error = 0x%x\n", ret));
		return ret;
	}

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)C_EDGE_TBL_ADDR;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaEdgeTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync(D_DDIM_WAIT_END_TIME, &rdmaCtrl);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret));
		return ret;
	}

	if(ch == D_IM_CNR_CH_2){
		ctImCnrOtfPrintDebugCsprEdgeTbl(0);
		ctImCnrOtfPrintDebugCsprEdgeTbl(1);
	}
	else{
		ctImCnrOtfPrintDebugCsprEdgeTbl(ch);
	}

	return D_DDIM_OK;
}

static INT32 ctImCnrRun6(CtImCnr* self, const UINT32 ctNo2nd)
{
	CtImCnr2 *ctim2 = ct_im_cnr2_new();
	ctim2->ch2 = self->ctId;
	CtImCnr3 *ctim3 = ct_im_cnr3_new();
	ctim3->ch3 = self->ctId;
	CtImCnr4 *ctim4 = ct_im_cnr4_new();
	ctim4->ch4 = self->ctId;
	CtImCnr5 *ctim5 = ct_im_cnr5_new();
	ctim5->ch5 = self->ctId;
	CtImCnr7 *ctim7 = ct_im_cnr7_new();
	ctim7->ch7 = self->ctId;
	CtImCnr8 *ctim8 = ct_im_cnr8_new();
	ctim8->ch8 = self->ctId;
	CtImCnr9 *ctim9 = ct_im_cnr9_new();
	ctim9->ch9 = self->ctId;
	CtImCnr10 *ctim10 = ct_im_cnr10_new();
	ctim10->ch10 = self->ctId;
	CtImCnr13 *ctim13 = ct_im_cnr13_new();
	ctim13->ch13 = self->ctId;

	Ddim_Print(("ctImCnrRun6 ctNo2nd = 0x%x, ctNo3rd = 0x%x\n", ctNo2nd, self->ctId));
	switch(ctNo2nd) {
		// Test-6-1
		case 1:
			return ct_im_cnr_6_1(ctim13);

		// Test-6-2
		case 2:
			return ct_im_cnr_6_2(ctim2);

		// Test-6-3
		case 3:
			return ct_im_cnr_6_3(ctim4);

		// Test-6-4
		case 4:
			return ct_im_cnr_6_4(ctim2);

		// Test-6-5
		case 5:
			return ct_im_cnr_6_5(ctim2);

		// Test-6-6
		case 6:
			return ct_im_cnr_6_6(ctim3);

		// Test-6-7
		case 7:
			return ct_im_cnr_6_7(ctim2);

		// Test-6-8
		case 8:
			return ct_im_cnr_6_8(ctim3);

		// Test-6-9
		case 9:
			return ct_im_cnr_6_9(ctim3);

		// Test-6-10
		case 10:
			return ct_im_cnr_6_10(self);

		// Test-6-11
		case 11:
			return ct_im_cnr_6_11(ctim5);

		// Test-6-12
		case 12:
			return ct_im_cnr_6_12(ctim4);

		// Test-6-13
		case 13:
			return ct_im_cnr_6_13(ctim4);

		// Test-6-14
		case 14:
			return ct_im_cnr_6_14(ctim7);

		// Test-6-15
		case 15:
			return ct_im_cnr_6_15(ctim7);

		// Test-6-16
		case 16:
			return ct_im_cnr_6_16(ctim8);

		// Test-6-17
		case 17:
			return ct_im_cnr_6_17(ctim8);

		// Test-6-18
		case 18:
			return ct_im_cnr_6_18(ctim8);

		// Test-6-19
		case 19:
			return ct_im_cnr_6_19(ctim8);

		// Test-6-20
		case 20:
			return ct_im_cnr_6_20(ctim9);

		// Test-6-21
		case 21:
			return ct_im_cnr_6_21(self);

		// Test-6-22
		case 22:
			return ct_im_cnr_6_22(ctim10);

		// Test-6-23
		case 23:
			return ct_im_cnr_6_23(ctim9);

		// Test-6-24
		case 24:
			return ct_im_cnr_6_24(ctim9);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	k_object_unref(ctim2);
	k_object_unref(ctim3);
	k_object_unref(ctim4);
	k_object_unref(ctim5);
	k_object_unref(ctim7);
	k_object_unref(ctim8);
	k_object_unref(ctim9);
	k_object_unref(ctim10);
	k_object_unref(ctim13);

	return D_DDIM_INPUT_PARAM_ERROR;
}

void ct_im_cnr_run(CtImCnr* self, const UINT32 ctIdx1st, const UINT32 ctIdx2nd)
{
#ifdef CO_MSG_PRINT_ON
	INT32 result = D_DDIM_INPUT_PARAM_ERROR;
#endif
	static BOOL S_IS_INIT = 0;

	Ddim_Print(("ct_im_cnr_run(%u, %u, %u) Begin\n", ctIdx1st, ctIdx2nd, self->ctId));

	if(S_IS_INIT == 0) {
#ifdef CO_DEBUG_ON_PC
		memset((void*)&IO_CNR1, '\0', sizeof(IO_CNR1));
//		Dd_Top_Set_CLKSTOP_CNR1AP(1);
//		Dd_Top_Set_CLKSTOP_CNR1AX(1);
//		Dd_Top_Set_CLKSTOP_CNR1CK(1);
#endif // CO_DEBUG_ON_PC

		Ddim_Print(("Im_CNR_OFL_Init() Begin\n"));
		Im_CNR_OFL_Init(self->ctId);

#ifndef CO_DEBUG_ON_PC
//		memset((void *)CtImCnr_D_IM_CNR_TEST_IMG_SRC_ADDR, '\0', CtImCnr_D_IM_CNR_TEST_IMG_SRC_BYTES);
//		memset((void *)CtImCnr_D_IM_CNR_TEST_IMG_DST_ADDR, '\0', CtImCnr_D_IM_CNR_TEST_IMG_DST_BYTES);
#endif // CO_DEBUG_ON_PC

		Ddim_Print(("Im_CNR_OFL_Init() End\n"));
		Ddim_Print(("Im_CNR_OTF_Init() Begin\n"));
		Im_CNR_OTF_Init(self->ctId);

#ifndef CO_DEBUG_ON_PC
//		memset((void *)CtImCnr_D_IM_CNR_TEST_IMG_SRC_ADDR, '\0', CtImCnr_D_IM_CNR_TEST_IMG_SRC_BYTES);
//		memset((void *)CtImCnr_D_IM_CNR_TEST_IMG_DST_ADDR, '\0', CtImCnr_D_IM_CNR_TEST_IMG_DST_BYTES);
#endif // CO_DEBUG_ON_PC

		Ddim_Print(("Im_CNR_OTF_Init() End\n"));
		S_IS_INIT = 1;
	}

#ifdef CO_CNR_DEBUG
	Im_CNR_Print_ClockStatus();
#endif
	Ddim_Print(("ct_im_cnr_run ctIdx1st = 0x%x ctNo2nd = 0x%x ctNo3rd = 0x%x\n", ctIdx1st, ctIdx2nd, self->ctId));

	CtImCnr6 *ctim6 = ct_im_cnr6_new();
	ctim6->ch6 = self->ctId;
	CtImCnr11 *ctim11 =	ct_im_cnr11_new();
	ctim11->ch11 = self->ctId;
	CtImCnr12 *ctim12 =	ct_im_cnr12_new();
	CtImCnr14 *ctim14 =	ct_im_cnr14_new();
	ctim14->ch14 = self->ctId;

	switch(ctIdx1st) {
		case 1:
			D_IM_CNR_RESULT(ctImCnrRun1(self, ctIdx2nd));
			break;

		case 2:
			D_IM_CNR_RESULT(ct_im_cnr_run_2(ctim6, ctIdx2nd));
			break;

		case 3:
			D_IM_CNR_RESULT(ct_im_cnr_run_3(ctim11, ctIdx2nd, ctim6));
			break;

		case 4:
			D_IM_CNR_RESULT(ct_im_cnr_run_4( ctim14, ctIdx2nd));
			break;

		case 5:
			D_IM_CNR_RESULT(ct_im_cnr_run_5(ctim12, ctIdx2nd));
			break;

		case 6:
			D_IM_CNR_RESULT(ctImCnrRun6(self, ctIdx2nd));
			break;

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	k_object_unref(ctim6);
	k_object_unref(ctim11);
	k_object_unref(ctim12);
	k_object_unref(ctim14);

#ifdef CO_MSG_PRINT_ON
	Ddim_Print(("result = 0x%x\n", result));
#endif

#ifdef CO_CNR_DEBUG
	Im_CNR_Print_ClockStatus();
#endif

	Ddim_Print(("ct_im_cnr_run(%u, %u, %u) End\n", ctIdx1st, ctIdx2nd, self->ctId));

	return;
}

void ct_im_cnr_main(INT32 argc, CHAR** argv)
{
	CtImCnr* self = ct_im_cnr_new();
	self->ctId = (UINT32)atoi((const char*)argv[3]);

	if(argc < 3) {
		Ddim_Print(("ct_im_cnr_main: parameter error.\n"));
		return;
	}

	ct_im_cnr_run(self, (UINT32)atoi((const char*)argv[1]),
				   	(UINT32)atoi((const char*)argv[2]));
	k_object_unref(self);					   
}

void ct_im_cnr_get_loop_cnt(UCHAR ch, UCHAR* sta, UCHAR* end)
{
	switch(ch){
		case 0:
			*sta = 0;
			*end = 0;
			break;
		case 1:
			*sta = 1;
			*end = 1;
			break;
		default:
			*sta = 0;
			*end = 1;
			break;
	}
}

CtImCnr* ct_im_cnr_new(void)
{
	CtImCnr* self = g_object_new(CT_TYPE_IM_CNR, NULL);
	return self;
}