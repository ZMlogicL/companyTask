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
#include "palladiumtestcnr2.h"

K_TYPE_DEFINE_WITH_PRIVATE(PalladiumTestCnr2, palladium_test_cnr2);
#define PALLADIUM_TEST_CNR2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), PalladiumTestCnr2Private, PALLADIUM_TYPE_TEST_CNR2))


#undef  PalladiumTestCnr_D_IM_CNR_TEST_NO
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_1"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_2"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_3"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_4"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_5"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_6"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_7"
#define PalladiumTestCnr_D_IM_CNR_TEST_NO "2_8"

struct _PalladiumTestCnr2Private
{
	kint a;
};

static void palladium_test_cnr2_constructor(PalladiumTestCnr2* self)
{
	PalladiumTestCnr2Private* priv = PALLADIUM_TEST_CNR2_GET_PRIVATE(self);
priv->a = 0;
}

static void palladium_test_cnr2_destructor(PalladiumTestCnr2* self)
{
	PalladiumTestCnr2Private* priv = PALLADIUM_TEST_CNR2_GET_PRIVATE(self);
priv->a = 0;
}

void palladium_test_cnr2_im_ofl_2_1(PalladiumTestCnr2*self, kuchar ch )
{
	kint32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_CTRL_C sprCtrlC = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};
	T_IM_CNR_RDMA_DATA_CTRL_C	rdmactrlC;
	const  T_IM_CNR_RDMA_ADDR_CTRL_C*	cnrCtrlAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_Ctrl_C( ch, &cnrCtrlAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_Ctrl_C error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_Ctrl_C( &sprCtrlC, &rdmactrlC );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_Ctrl_C error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)cnrCtrlAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmactrlC;
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
		pt_im_cnr_ofl_cspr_reg_print( 0 );
		pt_im_cnr_ofl_cspr_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_cspr_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_otf_2_1(PalladiumTestCnr2*self, kuchar ch )
{
	kint32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_CTRL_C sprCtrlC = {
		.enable = E_IM_CNR_ONOFF_ENABLE,
		.mid_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
		.low_freq_nr = {
			.enable = E_IM_CNR_ONOFF_ENABLE,
			.h_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_y_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.h_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.v_c_threshold = {
				0xFF, 0xFF, 0xFF, 0xFF,
			},
			.y_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
			.c_threshold_scl_en = E_IM_CNR_ONOFF_DISABLE,
		},
	};
	T_IM_CNR_RDMA_DATA_CTRL_C	rdmactrlC;
	const  T_IM_CNR_RDMA_ADDR_CTRL_C*	cnrCtrlAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OTF_Ctrl_C( ch, &cnrCtrlAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_Ctrl_C error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_Ctrl_C( &sprCtrlC, &rdmactrlC );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_Ctrl_C error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)cnrCtrlAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmactrlC;
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
		pt_im_cnr_otf_cspr_reg_print( 0 );
		pt_im_cnr_otf_cspr_reg_print( 1 );
	}
	else{
		pt_im_cnr_otf_cspr_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_ofl_2_2(PalladiumTestCnr2*self, kuchar ch )
{
	kint32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_OFL_CTRL_Y			sprCtrlY = {
		.enable = E_IM_CNR_ONOFF_DISABLE,
		.threshold_type = E_IM_CNR_THRES_REGISTER,
		.level = E_IM_CNR_LEVEL_HIGH,
		.h_y_threshold = 0xFF,
		.v_y_threshold = 0xFF,
		.h_c_threshold = 0xFF,
		.v_c_threshold = 0xFF,
		.alpha_blend_ratio = 0x1F,
	};
	T_IM_CNR_RDMA_DATA_OFL_CTRL_Y	rdmactrlY;
	const  T_IM_CNR_RDMA_ADDR_OFL_CTRL_Y*	cnrCtrlAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_Ctrl_Y( ch, &cnrCtrlAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_Ctrl_Y error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_Ctrl_Y( &sprCtrlY, &rdmactrlY );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_Ctrl_Y error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)cnrCtrlAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmactrlY;
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
		pt_im_cnr_ofl_yspr_reg_print( 0 );
		pt_im_cnr_ofl_yspr_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_yspr_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_ofl_2_3(PalladiumTestCnr2*self, kuchar ch )
{
	kint32 ret;
	T_IM_RDMA_CTRL rdmaCtrl;
	T_IM_CNR_TABLE	ysprTable = {
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
	T_IM_CNR_RDMA_DATA_OFL_YSPR_TBL	rdmaYsprTbl;
	const  T_IM_CNR_RDMA_ADDR_OFL_YSPR_TBL*	ysprTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_YSPR_Table( ch, &ysprTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_YSPR_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_YSPR_Table( &ysprTable, &rdmaYsprTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_YSPR_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)ysprTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaYsprTbl;
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
		pt_im_cnr_ofl_yspr_tbl_reg_print( 0 );
		pt_im_cnr_ofl_yspr_tbl_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_yspr_tbl_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_ofl_2_4(PalladiumTestCnr2*self, kuchar ch )
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
	T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL	rdmaMidYTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL*	midYTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_Y_Table( ch, &midYTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table( &cnrTable, &rdmaMidYTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)midYTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaMidYTbl;
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
		pt_im_cnr_ofl_cspr_mid_y_reg_print( 0 );
		pt_im_cnr_ofl_cspr_mid_y_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_cspr_mid_y_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_otf_2_4(PalladiumTestCnr2*self, kuchar ch )
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
	T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL	rdmaMidYTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL*	midYTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_Y_Table( ch, &midYTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_Y_Table( &cnrTable, &rdmaMidYTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)midYTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaMidYTbl;
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
		pt_im_cnr_otf_cspr_mid_y_reg_print( 0 );
		pt_im_cnr_otf_cspr_mid_y_reg_print( 1 );
	}
	else{
		pt_im_cnr_otf_cspr_mid_y_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_ofl_2_5(PalladiumTestCnr2*self, kuchar ch )
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
	T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL	rdmaMidCcYTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL*	midCcYTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_Y_Table( ch, &midCcYTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_Y_Table( &cnrTable, &rdmaMidCcYTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)midCcYTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaMidCcYTbl;
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
		pt_im_cnr_ofl_cspr_mid_cc_y_reg_print( 0 );
		pt_im_cnr_ofl_cspr_mid_cc_y_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_cspr_mid_cc_y_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_otf_2_5(PalladiumTestCnr2*self, kuchar ch )
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
	T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL	rdmaMidCcYTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL*	midCcYTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_CC_Y_Table( ch, &midCcYTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_Y_Table( &cnrTable, &rdmaMidCcYTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)midCcYTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaMidCcYTbl;
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
		pt_im_cnr_otf_cspr_mid_cc_y_reg_print( 0 );
		pt_im_cnr_otf_cspr_mid_cc_y_reg_print( 1 );
	}
	else{
		pt_im_cnr_otf_cspr_mid_cc_y_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_ofl_2_6(PalladiumTestCnr2*self, kuchar ch )
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
	T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL	rdmaMidCcCTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL*	midCcCTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_C_Table( ch, &midCcCTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Mid_CC_C_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_C_Table( &cnrTable, &rdmaMidCcCTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_C_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)midCcCTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaMidCcCTbl;
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
		pt_im_cnr_ofl_cspr_mid_cc_c_reg_print( 0 );
		pt_im_cnr_ofl_cspr_mid_cc_c_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_cspr_mid_cc_c_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_otf_2_6(PalladiumTestCnr2*self, kuchar ch )
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
	T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL	rdmaMidCcCTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL*	midCcCTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_CC_C_Table( ch, &midCcCTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Mid_CC_C_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_C_Table( &cnrTable, &rdmaMidCcCTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_C_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)midCcCTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaMidCcCTbl;
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
		pt_im_cnr_otf_cspr_mid_cc_c_reg_print( 0 );
		pt_im_cnr_otf_cspr_mid_cc_c_reg_print( 1 );
	}
	else{
		pt_im_cnr_otf_cspr_mid_cc_c_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_ofl_2_7(PalladiumTestCnr2*self, kuchar ch )
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
	T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL	rdmaLowYTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL*	lowYTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_Y_Table( ch, &lowYTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Low_Y_Table( &cnrTable, &rdmaLowYTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Low_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)lowYTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaLowYTbl;
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
		pt_im_cnr_ofl_cspr_low_y_reg_print( 0 );
		pt_im_cnr_ofl_cspr_low_y_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_cspr_low_y_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_otf_2_7(PalladiumTestCnr2*self, kuchar ch )
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
	T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL	rdmaLowYTbl;
	const  T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL*	lowYTblAddr;
	ULONG	size;

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_Y_Table( ch, &lowYTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OTF_CSPR_Low_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OTF_CSPR_Low_Y_Table( &cnrTable, &rdmaLowYTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OTF_CSPR_Low_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	// タイマー起動
	Palladium_Timer( P_TIMER_ID_COMMON0, P_TIMER_START );

	rdmaCtrl.transfer_byte		= size;
	rdmaCtrl.reg_addr_tbl_addr	= (ULONG)lowYTblAddr;
	rdmaCtrl.reg_data_top_addr	= (ULONG)&rdmaLowYTbl;
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
		pt_im_cnr_otf_cspr_low_y_reg_print( 0 );
		pt_im_cnr_otf_cspr_low_y_reg_print( 1 );
	}
	else{
		pt_im_cnr_otf_cspr_low_y_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OTF test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

void palladium_test_cnr2_im_ofl_2_8(PalladiumTestCnr2*self, kuchar ch )
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

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " begin\n" ));

	ret = Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_Y_Table( ch, &lowCcYTblAddr, &size );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Get_RdmaAddr_OFL_CSPR_Low_CC_Y_Table error = 0x%x\n", ret ));
		return ;
	}

	ret = Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_Y_Table( &cnrTable, &rdmaLowCcYTbl );
	if( ret != D_DDIM_OK ) {
		Ddim_Print(("Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_Y_Table error = 0x%x\n", ret ));
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
		pt_im_cnr_ofl_cspr_low_cc_y_reg_print( 0 );
		pt_im_cnr_ofl_cspr_low_cc_y_reg_print( 1 );
	}
	else{
		pt_im_cnr_ofl_cspr_low_cc_y_reg_print( ch );
	}

	Ddim_Print(( "*** CNR OFL test " PalladiumTestCnr_D_IM_CNR_TEST_NO " end\n" ));
}

PalladiumTestCnr2* palladium_test_cnr2_new(void)
{
	PalladiumTestCnr2* self = k_object_new_with_private(PALLADIUM_TYPE_TEST_CNR2,sizeof(PalladiumTestCnr2Private));
	return self;
}
