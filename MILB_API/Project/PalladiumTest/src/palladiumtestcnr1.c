/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :郭江龙
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
#include <string.h>
#include "ddim_user_custom.h"
#include "palladium_test.h"
#include "palladium_test_common.h"
#include "palladium_test_interrupt.h"
//#include "_timer.h"
#include "dd_gic.h"
#include "dd_top.h"
#include "im_cnr.h"
#include "im_rdma.h"
#include "jdscnr.h"
#include "palladiumtestcnr1.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestCnr1, palladium_test_cnr1);
#define PALLADIUM_TEST_CNR1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), PalladiumTestCnr1Private, PALLADIUM_TYPE_TEST_CNR1))

#undef  PalladiumTestCnr_D_IM_CNR_TEST_NO
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_8"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_9"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_10"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_11"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_12"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_13"

struct _PalladiumTestCnr1Private
{
	kint a;
};

static void palladium_test_cnr1_constructor(PalladiumTestCnr1* self)
{
	PalladiumTestCnr1Private* priv = PALLADIUM_TEST_CNR1_GET_PRIVATE(self);
priv->a = 0;
}

static void palladium_test_cnr1_destructor(PalladiumTestCnr1* self)
{
	PalladiumTestCnr1Private* priv = PALLADIUM_TEST_CNR1_GET_PRIVATE(self);
priv->a = 0;
}

void  palladium_test_cnr1_im_otf_2_8(PalladiumTestCnr1* self, kuchar ch )
{
	kint32 ret;
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
	T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL	rdmaLowCcYTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL*	lowCcYTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_CC_Y_Table( ch, &lowCcYTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_CC_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_Y_Table( &cnrTable, &rdmaLowCcYTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)lowCcYTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaLowCcYTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_WAIT_END_TIME, &rdmaCtrl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret ));
		return ;
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	if( ch == D_IM_CNR_CH_2 ){
		pt_im_cnr_otf_cspr_low_cc_y_reg_print( 0 );
		pt_im_cnr_otf_cspr_low_cc_y_reg_print( 1 );
	}
	else{
		pt_im_cnr_otf_cspr_low_cc_y_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void  palladium_test_cnr1_im_ofl_2_9(PalladiumTestCnr1* self, kuchar ch )
{
	kint32 ret;
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
	T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL	rdmaLowCcCTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL*	lowCcCTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_C_Table( ch, &lowCcCTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_C_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_C_Table( &cnrTable, &rdmaLowCcCTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_C_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)lowCcCTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaLowCcCTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_WAIT_END_TIME, &rdmaCtrl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret ));
		return ;
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	if( ch == D_IM_CNR_CH_2 ){
		pt_im_cnr_ofl_cspr_low_cc_c_reg_print( 0 );
		pt_im_cnr_ofl_cspr_low_cc_c_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_cspr_low_cc_c_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void  palladium_test_cnr1_im_otf_2_9(PalladiumTestCnr1* self, kuchar ch )
{
	kint32 ret;
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
	T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL	rdmaLowCcCTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL*	lowCcCTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_CC_C_Table( ch, &lowCcCTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_CC_C_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_C_Table( &cnrTable, &rdmaLowCcCTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_C_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)lowCcCTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaLowCcCTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_WAIT_END_TIME, &rdmaCtrl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret ));
		return ;
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	if( ch == D_IM_CNR_CH_2 ){
		pt_im_cnr_otf_cspr_low_cc_c_reg_print( 0 );
		pt_im_cnr_otf_cspr_low_cc_c_reg_print( 1 );
	}
	else{
		pt_im_cnr_otf_cspr_low_cc_c_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void  palladium_test_cnr1_im_ofl_2_10(PalladiumTestCnr1* self, kuchar ch )
{
	kint32 ret;
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
	const  T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL*	edgeTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Edge_Table( ch, &edgeTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Edge_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Edge_Table( &cnrTable, &rdmaEdgeTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Edge_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)edgeTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaEdgeTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_WAIT_END_TIME, &rdmaCtrl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret ));
		return ;
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	if( ch == D_IM_CNR_CH_2 ){
		pt_im_cnr_ofl_cspr_edge_reg_print( 0 );
		pt_im_cnr_ofl_cspr_edge_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_cspr_edge_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void  palladium_test_cnr1_im_otf_2_10(PalladiumTestCnr1* self, kuchar ch )
{
	kint32 ret;
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
	const  T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL*	edgeTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Edge_Table( ch, &edgeTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Edge_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Edge_Table( &cnrTable, &rdmaEdgeTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Edge_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)edgeTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaEdgeTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_WAIT_END_TIME, &rdmaCtrl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret ));
		return ;
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	if( ch == D_IM_CNR_CH_2 ){
		pt_im_cnr_otf_cspr_edge_reg_print( 0 );
		pt_im_cnr_otf_cspr_edge_reg_print( 1 );
	}
	else{
		pt_im_cnr_otf_cspr_edge_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void  palladium_test_cnr1_im_ofl_2_11(PalladiumTestCnr1* self, kuchar ch )
{
	kint32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_HUE_SPEC_TABLE	sprCsprHue = {
		.cd_cb = 0xFF,
		.cd_cr = 0xFF,
		.k_cb = 0x3FF,
		.k_cr = 0x3FF,
		.bd1 = 0x7FF,
		.bd2 = 0x7FF,
		.bd3 = 0x7FF,
		.bd4 = 0x7FF,
		.bd5 = 0x7FF,
		.of0 = 0x100,
		.of1 = 0x100,
		.of2 = 0x100,
		.of3 = 0x100,
		.of4 = 0x100,
		.of5 = 0x100,
		.gain0 = 0x07FF,
		.gain1 = 0x07FF,
		.gain2 = 0x07FF,
		.gain3 = 0x07FF,
		.gain4 = 0x07FF,
		.gain5 = 0x07FF
	};
	T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL	rdmaHueTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL*	hueTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Hue_Spec_Table( ch, &hueTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Hue_Spec_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Hue_Spec_Table( &sprCsprHue, &rdmaHueTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Hue_Spec_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)hueTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaHueTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_WAIT_END_TIME, &rdmaCtrl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret ));
		return ;
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	if( ch == D_IM_CNR_CH_2 ){
		pt_im_cnr_ofl_cspr_hue_reg_print( 0 );
		pt_im_cnr_ofl_cspr_hue_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_cspr_hue_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void  palladium_test_cnr1_im_otf_2_11(PalladiumTestCnr1* self, kuchar ch )
{
	kint32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_HUE_SPEC_TABLE	sprCsprHue = {
		.cd_cb = 0xFF,
		.cd_cr = 0xFF,
		.k_cb = 0x3FF,
		.k_cr = 0x3FF,
		.bd1 = 0x7FF,
		.bd2 = 0x7FF,
		.bd3 = 0x7FF,
		.bd4 = 0x7FF,
		.bd5 = 0x7FF,
		.of0 = 0x100,
		.of1 = 0x100,
		.of2 = 0x100,
		.of3 = 0x100,
		.of4 = 0x100,
		.of5 = 0x100,
		.gain0 = 0x07FF,
		.gain1 = 0x07FF,
		.gain2 = 0x07FF,
		.gain3 = 0x07FF,
		.gain4 = 0x07FF,
		.gain5 = 0x07FF
	};
	T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL	rdmaHueTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL*	hueTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Hue_Spec_Table( ch, &hueTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Hue_Spec_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Hue_Spec_Table( &sprCsprHue, &rdmaHueTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Hue_Spec_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)hueTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaHueTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_WAIT_END_TIME, &rdmaCtrl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret ));
		return ;
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	if( ch == D_IM_CNR_CH_2 ){
		pt_im_cnr_otf_cspr_hue_reg_print( 0 );
		pt_im_cnr_otf_cspr_hue_reg_print( 1 );
	}
	else{
		pt_im_cnr_otf_cspr_hue_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void  palladium_test_cnr1_im_ofl_2_12(PalladiumTestCnr1* self, kuchar ch )
{
	kint32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_CTRL_CC_SRC_DST	csprSprsCc = {
		.enable = (E_IM_CNR_ONOFF)1,
		.cb_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		},
		.cr_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		}
	};
	T_IM_CNR_RDMA_DATA_SPRS_CC_TBL	rdmaSprsTbl;
	const  T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL*	sprsTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRS_CC_Table( ch, &sprsTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRS_CC_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_SPRS_CC_Table( &csprSprsCc, &rdmaSprsTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_SPRS_CC_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)sprsTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaSprsTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_WAIT_END_TIME, &rdmaCtrl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret ));
		return ;
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	if( ch == D_IM_CNR_CH_2 ){
		pt_im_cnr_ofl_cspr_sprs_reg_print( 0 );
		pt_im_cnr_ofl_cspr_sprs_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_cspr_sprs_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void  palladium_test_cnr1_im_otf_2_12(PalladiumTestCnr1* self, kuchar ch )
{
	kint32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_CTRL_CC_SRC_DST	csprSprsCc = {
		.enable = (E_IM_CNR_ONOFF)1,
		.cb_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		},
		.cr_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		}
	};
	T_IM_CNR_RDMA_DATA_SPRS_CC_TBL	rdmaSprsTbl;
	const  T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL*	sprsTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRS_CC_Table( ch, &sprsTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRS_CC_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_SPRS_CC_Table( &csprSprsCc, &rdmaSprsTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_SPRS_CC_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)sprsTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaSprsTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_WAIT_END_TIME, &rdmaCtrl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret ));
		return ;
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	if( ch == D_IM_CNR_CH_2 ){
		pt_im_cnr_otf_cspr_sprs_reg_print( 0 );
		pt_im_cnr_otf_cspr_sprs_reg_print( 1 );
	}
	else{
		pt_im_cnr_otf_cspr_sprs_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void  palladium_test_cnr1_im_ofl_2_13(PalladiumTestCnr1* self, kuchar ch )
{
	kint32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_CTRL_CC_SRC_DST	csprSprdCc = {
		.enable = (E_IM_CNR_ONOFF)1,
		.cb_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		},
		.cr_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		}
	};
	T_IM_CNR_RDMA_DATA_SPRD_CC_TBL	rdmaSprdTbl;
	const  T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL*	sprdTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRD_CC_Table( ch, &sprdTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_SPRD_CC_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_SPRD_CC_Table( &csprSprdCc, &rdmaSprdTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_SPRD_CC_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)sprdTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaSprdTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_WAIT_END_TIME, &rdmaCtrl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret ));
		return ;
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	if( ch == D_IM_CNR_CH_2 ){
		pt_im_cnr_ofl_cspr_sprd_reg_print( 0 );
		pt_im_cnr_ofl_cspr_sprd_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_cspr_sprd_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void  palladium_test_cnr1_im_otf_2_13(PalladiumTestCnr1* self, kuchar ch )
{
	kint32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_CTRL_CC_SRC_DST	csprSprdCc = {
		.enable = (E_IM_CNR_ONOFF)1,
		.cb_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		},
		.cr_table = {
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
			.gain0 = 0x07FF,
			.gain1 = 0x07FF,
			.gain2 = 0x07FF,
			.gain3 = 0x07FF,
			.gain4 = 0x07FF,
			.gain5 = 0x07FF
		}
	};
	T_IM_CNR_RDMA_DATA_SPRD_CC_TBL	rdmaSprdTbl;
	const  T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL*	sprdTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRD_CC_Table( ch, &sprdTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_SPRD_CC_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_SPRD_CC_Table( &csprSprdCc, &rdmaSprdTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_SPRD_CC_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)sprdTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaSprdTbl;
	rdmaCtrl.req_threshold		= E_IM_RDMA_PRCH_CNT_NOLIMIT;
	rdmaCtrl.int_mode			= E_IM_RDMA_INT_MODE_AND_ERR;
	rdmaCtrl.pCallBack			= NULL;
	ret = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_WAIT_END_TIME, &rdmaCtrl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Ctrl error = 0x%x\n", ret ));
		return ;
	}

	// タイマー停止
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_END );

	// 出力ダンプ
	if( ch == D_IM_CNR_CH_2 ){
		pt_im_cnr_otf_cspr_sprd_reg_print( 0 );
		pt_im_cnr_otf_cspr_sprd_reg_print( 1 );
	}
	else{
		pt_im_cnr_otf_cspr_sprd_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void  palladium_test_cnr1_im_run_5(PalladiumTestCnr1* self, const kuint32 type1 )
{
	kuchar			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			pt_im_cnr_ofl_1_1(0);
			break;
		case 2:
			pt_im_cnr_ofl_1_1(0);
			pt_im_cnr_ofl_1_2(0);
			break;
		case 3:
			pt_im_cnr_ofl_1_1(0);
			pt_im_cnr_ofl_1_3(0);
			break;
		case 4:
			pt_im_cnr_ofl_1_1(1);
			break;
		case 5:
			pt_im_cnr_ofl_1_1(1);
			pt_im_cnr_ofl_1_2(1);
			break;
		case 6:
			pt_im_cnr_ofl_1_1(1);
			pt_im_cnr_ofl_1_3(1);
			break;
		case 7:
			pt_im_cnr_otf_1_1(0);
			break;
		case 8:
			pt_im_cnr_otf_1_1(0);
			pt_im_cnr_otf_1_2(0);
			break;
		case 9:
			pt_im_cnr_otf_1_1(0);
			pt_im_cnr_otf_1_3(0);
			break;
		case 10:
			pt_im_cnr_otf_1_1(1);
			break;
		case 11:
			pt_im_cnr_otf_1_1(1);
			pt_im_cnr_otf_1_2(1);
			break;
		case 12:
			pt_im_cnr_otf_1_1(1);
			pt_im_cnr_otf_1_3(1);
			break;

		default:
			Ddim_Print(("*** CNR test skip\n" ));
			break;
	}
}

void  palladium_test_cnr1_im_run_6(PalladiumTestCnr1* self, const kuint32 type1 )
{
	kuchar			type2;

	type2	= gDDIM_Info.com._6b;

	switch( type2 ) {
		case 1:
			// Ctrl_C (OFL)
			pt_im_cnr_ofl_2_1(0);
			pt_im_cnr_ofl_2_1(1);
			pt_im_cnr_ofl_2_1(2);
			break;
		case 2:
			// Ctrl_Y (OFL)
			pt_im_cnr_ofl_2_2(0);
			pt_im_cnr_ofl_2_2(1);
			pt_im_cnr_ofl_2_2(2);
			break;
		case 3:
			// YSPR Table (OFL)
			pt_im_cnr_ofl_2_3(0);
			pt_im_cnr_ofl_2_3(1);
			pt_im_cnr_ofl_2_3(2);
			break;
		case 4:
			// CSPR Mid-Y Table (OFL)
			pt_im_cnr_ofl_2_4(0);
			pt_im_cnr_ofl_2_4(1);
			pt_im_cnr_ofl_2_4(2);
			break;
		case 5:
			// CSPR Mid-CC-Y Table (OFL)
			pt_im_cnr_ofl_2_5(0);
			pt_im_cnr_ofl_2_5(1);
			pt_im_cnr_ofl_2_5(2);
			break;
		case 6:
			// CSPR Mid-CC-C Table (OFL)
			pt_im_cnr_ofl_2_6(0);
			pt_im_cnr_ofl_2_6(1);
			pt_im_cnr_ofl_2_6(2);
			break;
		case 7:
			// CSPR Low-Y Table (OFL)
			pt_im_cnr_ofl_2_7(0);
			pt_im_cnr_ofl_2_7(1);
			pt_im_cnr_ofl_2_7(2);
			break;
		case 8:
			// CSPR Low-CC-Y Table (OFL)
			pt_im_cnr_ofl_2_8(0);
			pt_im_cnr_ofl_2_8(1);
			pt_im_cnr_ofl_2_8(2);
			break;
		case 9:
			// CSPR Low-CC-C Table (OFL)
			pt_im_cnr_ofl_2_9(0);
			pt_im_cnr_ofl_2_9(1);
			pt_im_cnr_ofl_2_9(2);
			break;
		case 10:
			// CSPR Edge Specified Table (OFL)
			pt_im_cnr_ofl_2_10(0);
			pt_im_cnr_ofl_2_10(1);
			pt_im_cnr_ofl_2_10(2);
			break;
		case 11:
			// CSPR Hue Specified Table (OFL)
			pt_im_cnr_ofl_2_11(0);
			pt_im_cnr_ofl_2_11(1);
			pt_im_cnr_ofl_2_11(2);
			break;
		case 12:
			// CSPR SPRS_CC Table (OFL)
			pt_im_cnr_ofl_2_12(0);
			pt_im_cnr_ofl_2_12(1);
			pt_im_cnr_ofl_2_12(2);
			break;
		case 13:
			// CSPR SPRD_CC Table (OFL)
			pt_im_cnr_ofl_2_13(0);
			pt_im_cnr_ofl_2_13(1);
			pt_im_cnr_ofl_2_13(2);
			break;
		case 14:
			// Ctrl_C (OTF)
			pt_im_cnr_otf_2_1(0);
			pt_im_cnr_otf_2_1(1);
			pt_im_cnr_otf_2_1(2);
			break;
		case 15:
			// CSPR Mid-Y Table (OTF)
			pt_im_cnr_otf_2_4(0);
			pt_im_cnr_otf_2_4(1);
			pt_im_cnr_otf_2_4(2);
			break;
		case 16:
			// CSPR Mid-CC-Y Table (OTF)
			pt_im_cnr_otf_2_5(0);
			pt_im_cnr_otf_2_5(1);
			pt_im_cnr_otf_2_5(2);
			break;
		case 17:
			// CSPR Mid-CC-C Table (OTF)
			pt_im_cnr_otf_2_6(0);
			pt_im_cnr_otf_2_6(1);
			pt_im_cnr_otf_2_6(2);
			break;
		case 18:
			// CSPR Low-Y Table (OTF)
			pt_im_cnr_otf_2_7(0);
			pt_im_cnr_otf_2_7(1);
			pt_im_cnr_otf_2_7(2);
			break;
		case 19:
			// CSPR Low-CC-Y Table (OTF)
			pt_im_cnr_otf_2_8(0);
			pt_im_cnr_otf_2_8(1);
			pt_im_cnr_otf_2_8(2);
			break;
		case 20:
			// CSPR Low-CC-C Table (OTF)
			pt_im_cnr_otf_2_9(0);
			pt_im_cnr_otf_2_9(1);
			pt_im_cnr_otf_2_9(2);
			break;
		case 21:
			// CSPR Edge Specified Table (OTF)
			pt_im_cnr_otf_2_10(0);
			pt_im_cnr_otf_2_10(1);
			pt_im_cnr_otf_2_10(2);
			break;
		case 22:
			// CSPR Hue Specified Table (OTF)
			pt_im_cnr_otf_2_11(0);
			pt_im_cnr_otf_2_11(1);
			pt_im_cnr_otf_2_11(2);
			break;
		case 23:
			// CSPR SPRS_CC Table (OTF)
			pt_im_cnr_otf_2_12(0);
			pt_im_cnr_otf_2_12(1);
			pt_im_cnr_otf_2_12(2);
			break;
		case 24:
			// CSPR SPRD_CC Table (OTF)
			pt_im_cnr_otf_2_13(0);
			pt_im_cnr_otf_2_13(1);
			pt_im_cnr_otf_2_13(2);
			break;

		default:
			Ddim_Print(("*** CNR test skip\n" ));
			break;
	}
}

PalladiumTestCnr1* palladium_test_cnr1_new(void)
{
	PalladiumTestCnr1* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_CNR1,sizeof(PalladiumTestCnr1Private));
	return self;
}
