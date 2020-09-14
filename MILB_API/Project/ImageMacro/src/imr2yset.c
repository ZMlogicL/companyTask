/*
 * imr2yset.c
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
*@author              :gonghaotian
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

#include "imr2yset.h"
#include "imr2yctrl2.h"

#include "imr2yctrl3.h"
#include "imr2yedge.h"
#include "imr2y.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2ySet, im_r2y_set);
#define IM_R2Y_SET_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2ySetPrivate, IM_TYPE_R2Y_SET))

struct _ImR2ySetPrivate
{
	int a;
};


/*
 * DECLS
 */
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON

static void imR2ySetRdmaValGammmaDiffTable( kuint16 pipeNo, kuint16 tbl_index, const ULLONG* const src_diff_tbl );
static void imR2ySetRdmaValGammmaFullTable( kuint16 pipeNo, kuint16 tbl_index, const kuint16* const src_full_tbl );
static void imR2ySetRdmaValHedgeScaleTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num );
static void imR2ySetRdmaValHedgeStepTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num );
static void imR2ySetRdmaValMedgeScaleTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num );
static void imR2ySetRdmaValMedgeStepTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num );
static void imR2ySetRdmaValLedgeScaleTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num );
static void imR2ySetRdmaValLedgeStepTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num );
static void imR2ySetRdmaValMapScaleTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num );

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
 * IMPL
 */
static void im_r2y_set_constructor(ImR2ySet *self)
{
	ImR2ySetPrivate *priv = IM_R2Y_SET_GET_PRIVATE(self);
}

static void im_r2y_set_destructor(ImR2ySet *self)
{
	ImR2ySetPrivate *priv = IM_R2Y_SET_GET_PRIVATE(self);
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON

static void imR2ySetRdmaValGammmaDiffTable( kuint16 pipeNo, kuint16 tbl_index, const ULLONG* const src_diff_tbl )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	switch( tbl_index ){
		case 1:		// R
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_GMRDF_Tbl_Addr[pipeNo]);
			break;
		case 2:		// G
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_GMGDF_Tbl_Addr[pipeNo]);
			break;
		case 3:		// B
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_GMBDF_Tbl_Addr[pipeNo]);
			break;
		case 4:		// Yb
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_GMYBDF_Tbl_Addr[pipeNo]);
			break;
//		case 0:		// RGB common
		default:
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_GMRGBDF_Tbl_Addr[pipeNo]);
			break;
	}

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaGmdfTblval );
	rdma_ctrl.reg_data_top_addr = (kulong)src_diff_tbl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValGammmaFullTable( kuint16 pipeNo, kuint16 tbl_index, const kuint16* const src_full_tbl )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	switch( tbl_index ){
		case 1:		// R
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_GMRFL_Tbl_Addr[pipeNo]);
			break;
		case 2:		// G
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_GMGFL_Tbl_Addr[pipeNo]);
			break;
		case 3:		// B
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_GMBFL_Tbl_Addr[pipeNo]);
			break;
		case 4:		// Yb
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_GMYBFL_Tbl_Addr[pipeNo]);
			break;
//		case 0:		// RGB common
		default:
			rdma_ctrl.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_GMRGBFL_Tbl_Addr[pipeNo]);
			break;
	}

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaGmflTblval );
	rdma_ctrl.reg_data_top_addr = (kulong)src_full_tbl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValHedgeScaleTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGHWSCL_Tbl_Addr[pipeNo].EGWSCL[write_ofs_num / 4]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = array_num / 4;
	rdma_ctrl.reg_data_top_addr = (kulong)src_tbl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValHedgeStepTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGHWTON_Tbl_Addr[pipeNo].EGWTON[write_ofs_num / 2]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = array_num / 2;
	rdma_ctrl.reg_data_top_addr = (kulong)src_tbl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValMedgeScaleTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGMWSCL_Tbl_Addr[pipeNo].EGWSCL[write_ofs_num / 4]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = array_num / 4;
	rdma_ctrl.reg_data_top_addr = (kulong)src_tbl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValMedgeStepTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGMWTON_Tbl_Addr[pipeNo].EGWTON[write_ofs_num / 2]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = array_num / 2;
	rdma_ctrl.reg_data_top_addr = (kulong)src_tbl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValLedgeScaleTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGLWSCL_Tbl_Addr[pipeNo].EGWSCL[write_ofs_num / 4]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = array_num / 4;
	rdma_ctrl.reg_data_top_addr = (kulong)src_tbl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValLedgeStepTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGLWTON_Tbl_Addr[pipeNo].EGWTON[write_ofs_num / 2]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = array_num / 2;
	rdma_ctrl.reg_data_top_addr = (kulong)src_tbl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValMapScaleTable( kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_EGMPSCL_Tbl_Addr[pipeNo].EGMPSCL[write_ofs_num / 2]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = array_num / 2;
	rdma_ctrl.reg_data_top_addr = (kulong)src_tbl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
 * PUBLIC
 */
/* Set Gamma Table
 */
INT32 im_r2y_set_gamma_table(ImR2ySet *self, kuint16 pipeNo, kuint16 tbl_index, const kuint16* const src_full_tbl, const ULLONG* const src_diff_tbl )
{
	volatile kuint16* dst_full_table = NULL;
	volatile ULLONG* dst_diff_table = NULL;
	UINT32 loopcnt;
	kuint16 loop_sta, loop_end;
	INT32 ercd;
	INT32 ercd2;
	kuint16 act_status;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(src_full_tbl == NULL) {
		Ddim_Assertion(("im_r2y_set_gamma_table error. src_full_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if(src_diff_tbl == NULL) {
		Ddim_Assertion(("im_r2y_set_gamma_table error. src_diff_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( tbl_index > 4 ){
		Ddim_Assertion(("im_r2y_set_gamma_table error. tbl_index > 4\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_gamma_table error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loopcnt = loop_sta; loopcnt <= loop_end; loopcnt++ ){
		im_r2y_ctrl2_is_act_gamma(im_r2y_ctrl2_new(),  loopcnt, &act_status );
		if( act_status != ImR2yCtrl_ENABLE_OFF ) {
			return ImR2yUtils_MACRO_BUSY;
		}
	}

	ercd = im_r2y_ctrl2_set_gamma_tbl_access_enable(im_r2y_ctrl2_new(),  pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
	if( ercd != D_DDIM_OK ) {
		return ercd;
	}
	while( 1 ) {
		switch (tbl_index) {
			case 0:	// RGB common
				dst_full_table = gImIoR2yTblPtr[pipeNo]->GMRGBFL.hword;
				dst_diff_table = gImIoR2yTblPtr[pipeNo]->GMRGBDF.dword;
				break;
			case 1:	// R-Gamma
				dst_full_table = gImIoR2yTblPtr[pipeNo]->GMRFL.hword;
				dst_diff_table = gImIoR2yTblPtr[pipeNo]->GMRDF.dword;
				break;
			case 2:	// G-Gamma
				dst_full_table = gImIoR2yTblPtr[pipeNo]->GMGFL.hword;
				dst_diff_table = gImIoR2yTblPtr[pipeNo]->GMGDF.dword;
				break;
			case 3:	// B-Gamma
				dst_full_table = gImIoR2yTblPtr[pipeNo]->GMBFL.hword;
				dst_diff_table = gImIoR2yTblPtr[pipeNo]->GMBDF.dword;
				break;
			case 4:	// Yb-Gamma
				dst_full_table = gImIoR2yTblPtr[pipeNo]->GMYBFL.hword;
				dst_diff_table = gImIoR2yTblPtr[pipeNo]->GMYBDF.dword;
				break;
			default:
				ercd = ImR2yUtils_PARAM_ERROR;
				break;
		}
		if( ercd != D_DDIM_OK ) {
			break;
		}

		// for PG-Relief
		if( (dst_full_table == NULL) || (dst_diff_table == NULL) ) {
			break;
		}

		ercd = im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(im_r2y_ctrl2_new(),  pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValGammmaDiffTable( pipeNo, tbl_index, src_diff_tbl );
		imR2ySetRdmaValGammmaFullTable( pipeNo, tbl_index, src_full_tbl );
#else	// CO_R2Y_RDMA_ON
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );
		for( loopcnt = 0; loopcnt < ImR2yCtrl_TABLE_MAX_GAMMA; loopcnt++ ) {
			dst_full_table[loopcnt] = src_full_tbl[loopcnt];
			dst_diff_table[loopcnt] = src_diff_tbl[loopcnt];
		}
		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(im_r2y_ctrl2_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}
		break;
	}

	ercd2 = im_r2y_ctrl2_set_gamma_tbl_access_enable(im_r2y_ctrl2_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
	if( ercd2 != D_DDIM_OK ) {
		return ercd2;
	}

	return ercd;
}

/* Set High Edge emphasis scaling Table
 */
INT32 im_r2y_set_high_edge_scale_table(ImR2ySet *self, kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	UINT32 loop_cnt;
	kuint16 loop_sta, loop_end;
	INT32 ercd;
	kuint16 act_status;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

	// Start status check in R2Y core part
#ifdef CO_PARAM_CHECK
	if(src_tbl == NULL) {
		Ddim_Assertion(("im_r2y_set_high_edge_scale_table error. src_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( (write_ofs_num + array_num) > ImR2yCtrl_TABLE_MAX_EDGE_SCALE_HI ) {
		Ddim_Assertion(("im_r2y_set_high_edge_scale_table error. write_ofs_num + array_num > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_high_edge_scale_table error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_r2y_edge_is_act_post_filter(im_r2y_edge_new(),  loop_cnt, &act_status );
		if( act_status != ImR2yCtrl_ENABLE_OFF ) {
			return ImR2yUtils_MACRO_BUSY;
		}
	}

	while( 1 ) {
		ercd = im_r2y_edge_set_high_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValHedgeScaleTable( pipeNo, src_tbl, write_ofs_num, array_num );
#else	// CO_R2Y_RDMA_ON
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

		for( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			gImIoR2yTblPtr[pipeNo]->EGHWSCL.byte[write_ofs_num + loop_cnt] = src_tbl[loop_cnt];
		}

		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y_edge_set_high_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	return ercd;
}

/* Set High Edge emphasis stepping Table
 */
INT32 im_r2y_set_high_edge_step_table(ImR2ySet *self, kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	UINT32 loop_cnt;
	kuint16 loop_sta, loop_end;
	INT32 ercd;
	kuint16 act_status;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

	// Start status check in R2Y core part
#ifdef CO_PARAM_CHECK
	if(src_tbl == NULL) {
		Ddim_Assertion(("im_r2y_set_high_edge_step_table error. src_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( (write_ofs_num + array_num) > ImR2yCtrl_TABLE_MAX_EDGE_TC_HI ) {
		Ddim_Assertion(("im_r2y_set_high_edge_step_table error. write_ofs_num + array_num > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_high_edge_step_table error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_r2y_edge_is_act_post_filter(im_r2y_edge_new(),  loop_cnt, &act_status );
		if( act_status != ImR2yCtrl_ENABLE_OFF ) {
			return ImR2yUtils_MACRO_BUSY;
		}
	}

	while( 1 ) {
		ercd = im_r2y_edge_set_high_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValHedgeStepTable( pipeNo, src_tbl, write_ofs_num, array_num );
#else	// CO_R2Y_RDMA_ON
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

		for( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			gImIoR2yTblPtr[pipeNo]->EGHWTON.hword[write_ofs_num + loop_cnt] = src_tbl[loop_cnt];
		}

		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y_edge_set_high_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	return ercd;
}

/* Set Medium Edge emphasis scaling Table
 */
INT32 im_r2y_set_medium_edge_scale_table(ImR2ySet *self, kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	UINT32 loop_cnt;
	kuint16 loop_sta, loop_end;
	INT32 ercd;
	kuint16 act_status;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

	// Start status check in R2Y core part
#ifdef CO_PARAM_CHECK
	if(src_tbl == NULL) {
		Ddim_Assertion(("im_r2y_set_medium_edge_scale_table error. src_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( (write_ofs_num + array_num) > ImR2yCtrl_TABLE_MAX_EDGE_SCALE_MEDIUM ) {
		Ddim_Assertion(("im_r2y_set_medium_edge_scale_table error. write_ofs_num + array_num > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_medium_edge_scale_table error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_r2y_edge_is_act_post_filter(im_r2y_edge_new(),  loop_cnt, &act_status );
		if( act_status != ImR2yCtrl_ENABLE_OFF ) {
			return ImR2yUtils_MACRO_BUSY;
		}
	}

	while( 1 ) {
		ercd = im_r2y_edge_set_medium_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValMedgeScaleTable( pipeNo, src_tbl, write_ofs_num, array_num );
#else	// CO_R2Y_RDMA_ON
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

		for( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			gImIoR2yTblPtr[pipeNo]->EGMWSCL.byte[write_ofs_num + loop_cnt] = src_tbl[loop_cnt];
		}

		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y_edge_set_medium_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	return ercd;
}

/* Set Medium Edge emphasis stepping Table
 */
INT32 im_r2y_set_medium_edge_step_table(ImR2ySet *self, kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	UINT32 loop_cnt;
	kuint16 loop_sta, loop_end;
	INT32 ercd;
	kuint16 act_status;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

	// Start status check in R2Y core part
#ifdef CO_PARAM_CHECK
	if(src_tbl == NULL) {
		Ddim_Assertion(("im_r2y_set_medium_edge_step_table error. src_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( (write_ofs_num + array_num) > ImR2yCtrl_TABLE_MAX_EDGE_TC_MEDIUM ) {
		Ddim_Assertion(("im_r2y_set_medium_edge_step_table error. write_ofs_num + array_num > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_medium_edge_step_table error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_r2y_edge_is_act_post_filter(im_r2y_edge_new(),  loop_cnt, &act_status );
		if( act_status != ImR2yCtrl_ENABLE_OFF ) {
			return ImR2yUtils_MACRO_BUSY;
		}
	}

	while( 1 ) {
		ercd = im_r2y_edge_set_medium_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValMedgeStepTable( pipeNo, src_tbl, write_ofs_num, array_num );
#else	// CO_R2Y_RDMA_ON
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

		for( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			gImIoR2yTblPtr[pipeNo]->EGMWTON.hword[write_ofs_num + loop_cnt] = src_tbl[loop_cnt];
		}

		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y_edge_set_medium_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	return ercd;
}

/* Set Low Edge emphasis scaling Table
 */
INT32 im_r2y_set_low_edge_scale_table(ImR2ySet *self, kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	UINT32 loop_cnt;
	kuint16 loop_sta, loop_end;
	INT32 ercd;
	kuint16 act_status;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

	// Start status check in R2Y core part
#ifdef CO_PARAM_CHECK
	if(src_tbl == NULL) {
		Ddim_Assertion(("im_r2y_set_low_edge_scale_table error. src_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( (write_ofs_num + array_num) > ImR2yCtrl_TABLE_MAX_EDGE_SCALE_LO ) {
		Ddim_Assertion(("im_r2y_set_low_edge_scale_table error. write_ofs_num + array_num > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_low_edge_scale_table error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_r2y_edge_is_act_post_filter(im_r2y_edge_new(),  loop_cnt, &act_status );
		if( act_status != ImR2yCtrl_ENABLE_OFF ) {
			return ImR2yUtils_MACRO_BUSY;
		}
	}

	while( 1 ) {
		ercd = im_r2y_edge_set_low_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValLedgeScaleTable( pipeNo, src_tbl, write_ofs_num, array_num );
#else	// CO_R2Y_RDMA_ON
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

		for( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			gImIoR2yTblPtr[pipeNo]->EGLWSCL.byte[write_ofs_num + loop_cnt] = src_tbl[loop_cnt];
		}

		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y_edge_set_low_edge_scl_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	return ercd;
}

/* Set Low Edge emphasis stepping Table
 */
INT32 im_r2y_set_low_edge_step_table(ImR2ySet *self, kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	UINT32 loop_cnt;
	kuint16 loop_sta, loop_end;
	INT32 ercd;
	kuint16 act_status;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

	// Start status check in R2Y core part
#ifdef CO_PARAM_CHECK
	if(src_tbl == NULL) {
		Ddim_Assertion(("im_r2y_set_low_edge_step_table error. src_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( (write_ofs_num + array_num) > ImR2yCtrl_TABLE_MAX_EDGE_TC_LO ) {
		Ddim_Assertion(("im_r2y_set_low_edge_step_table error. write_ofs_num + array_num > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_low_edge_step_table error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_r2y_edge_is_act_post_filter(im_r2y_edge_new(),  loop_cnt, &act_status );
		if( act_status != ImR2yCtrl_ENABLE_OFF ) {
			return ImR2yUtils_MACRO_BUSY;
		}
	}

	while( 1 ) {
		ercd = im_r2y_edge_set_low_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValLedgeStepTable( pipeNo, src_tbl, write_ofs_num, array_num );
#else	// CO_R2Y_RDMA_ON
		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

		for( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			gImIoR2yTblPtr[pipeNo]->EGLWTON.hword[write_ofs_num + loop_cnt] = src_tbl[loop_cnt];
		}

		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y_edge_set_low_edge_step_tbl_access_enable(im_r2y_edge_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	return ercd;
}

/* Set Map Scale Table
 */
INT32 im_r2y_set_map_scl_table(ImR2ySet *self, kuint16 pipeNo, const kuint16* const src_tbl, kuint16 write_ofs_num, kuint16 array_num )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y_sram** gImIoR2yTblPtr = im_r2y_utils_get_io_tbl(imR2yUtils);

#ifndef CO_R2Y_RDMA_ON
	volatile kuint16* dst_table;
#endif	// CO_R2Y_RDMA_ON
	UINT32 loop_cnt;
	kuint16 loop_sta, loop_end;
	INT32 ercd;
	kuint16 act_status;

	// Start status check in R2Y core part
#ifdef CO_PARAM_CHECK
	if(src_tbl == NULL) {
		Ddim_Assertion(("im_r2y_set_map_scl_table error. src_tbl = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( (write_ofs_num + array_num) > ImR2yCtrl_TABLE_MAX_MAPSCL ) {
		Ddim_Assertion(("im_r2y_set_map_scl_table error. write_ofs_num + array_num > MAX\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_set_map_scl_table error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_r2y_edge_is_act_post_filter(im_r2y_edge_new(),  loop_cnt, &act_status );
		if( act_status != ImR2yCtrl_ENABLE_OFF ) {
			return ImR2yUtils_MACRO_BUSY;
		}
	}

	while( 1 ) {
		ercd = im_r2y_ctrl3_set_map_scl_tbl_access_enable(im_r2y_ctrl3_new(),  pipeNo, ImR2yCtrl_ENABLE_ON, ImR2yCtrl_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_R2Y_RDMA_ON
		imR2ySetRdmaValMapScaleTable( pipeNo, src_tbl, write_ofs_num, array_num );
#else	// CO_R2Y_RDMA_ON
		dst_table = gImIoR2yTblPtr[pipeNo]->EGMPSCL.hword[0];

		im_r2y_clk_on_hclk(im_r2y_clk_new(),  pipeNo );

		for( loop_cnt = 0; loop_cnt < array_num; loop_cnt++ ) {
			dst_table[write_ofs_num + loop_cnt] = src_tbl[loop_cnt];
		}

		im_r2y_clk_off_hclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

		ercd = im_r2y_ctrl3_set_map_scl_tbl_access_enable(im_r2y_ctrl3_new(),  pipeNo, ImR2yCtrl_ENABLE_OFF, ImR2yCtrl_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	return ercd;
}

ImR2ySet *im_r2y_set_new(void)
{
	ImR2ySet* self = k_object_new_with_private(IM_TYPE_R2Y_SET,sizeof(ImR2ySetPrivate));
	return self;
}
