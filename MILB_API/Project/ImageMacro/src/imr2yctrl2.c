/*
 * imr2yctrl2.c
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
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

#include "imr2yctrl2.h"
#include "imr2y.h"
#include "imr2y2.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yCtrl2, im_r2y_ctrl2);
#define IM_R2Y_CTRL2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yCtrl2Private, IM_TYPE_R2Y_CTRL2))

struct _ImR2yCtrl2Private
{
	int a;
};


static VOID imR2ySetTctAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_tct_tbl_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetTctAccessEnable,
};

static VOID imR2ySetBtcHistogramAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_btc_histogram_tbl_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetBtcHistogramAccessEnable,
};

static VOID imR2ySetGammaTblAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_gamma_tbl_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetGammaTblAccessEnable,
};

static VOID imR2ySetGammaYbTblAccessEnable( UCHAR pipe_no, const UCHAR enable );
static volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE gim_r2y_gamma_yb_tbl_accen_ctrl = {
	.ctrl_cnt = { 0, 0 },
	.reg_set_func = imR2ySetGammaYbTblAccessEnable,
};


#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static VOID imR2ySetRdmaValWbClipCtrl( UCHAR pipe_no, const T_IM_R2Y_RGB_COLOR* const rgb_color );
static VOID imR2ySetRdmaValCc0MatrixCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_CC0* const r2y_ctrl_cc );
static VOID imR2ySetRdmaValCc0MatrixCoefficientCtrl( UCHAR pipe_no, const SHORT* const cc0k );
static VOID imR2ySetRdmaValGammaCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_GAMMA* const r2y_ctrl_gamma );
static VOID imR2ySetRdmaValCc1MatrixCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_CC1* const r2y_ctrl_cc );
static VOID imR2ySetRdmaValCc1MatrixCoefficientCtrl( UCHAR pipe_no, const SHORT* const cc1k );
static VOID imR2ySetRdmaValYcConvertCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_YCC* const r2y_ctrl_ycc );
static VOID imR2ySetRdmaValYnrCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_YNR* const r2y_ctrl_ynr );

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
*IMPL
*/
static void im_r2y_ctrl2_constructor(ImR2yCtrl2 *self)
{
	ImR2yCtrl2Private *priv = IM_R2Y_CTRL2_GET_PRIVATE(self);
}

static void im_r2y_ctrl2_destructor(ImR2yCtrl2 *self)
{
	ImR2yCtrl2Private *priv = IM_R2Y_CTRL2_GET_PRIVATE(self);
}

static VOID imR2ySetTctAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCTCTL.bit.TCTAEN = enable;
}

static VOID imR2ySetBtcHistogramAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHSCTL.bit.TCHAEN = enable;
}

static VOID imR2ySetGammaTblAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.GAM.GMCTL.bit.GMAEN = enable;
}

static VOID imR2ySetGammaYbTblAccessEnable( UCHAR pipe_no, const UCHAR enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.GAM.GMCTL.bit.GMYAEN = enable;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static VOID imR2ySetRdmaValWbClipCtrl( UCHAR pipe_no, const T_IM_R2Y_RGB_COLOR* const rgb_color )
{
	T_IM_R2Y_CTRL_RDMA_WB_CLIP_VAL wb_clip_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_WB_CLIP_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	wb_clip_ctrl.WBLV.bit.WBLVR = rgb_color->R;
	wb_clip_ctrl.WBLV.bit.WBLVG = rgb_color->G;
	wb_clip_ctrl.WBLV.bit.WBLVB = rgb_color->B;

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_WB_CLIP_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&wb_clip_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValCc0MatrixCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_CC0* const r2y_ctrl_cc )
{
	T_IM_R2Y_CTRL_RDMA_CC0_VAL cc0_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_CC0_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	cc0_ctrl.CC0CTL.bit.CC0DP = r2y_ctrl_cc->posi_dec;
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_0_0, r2y_ctrl_cc->cc_matrix[0][0] );
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_0_1, r2y_ctrl_cc->cc_matrix[0][1] );
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_0_2, r2y_ctrl_cc->cc_matrix[0][2] );
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_1_0, r2y_ctrl_cc->cc_matrix[1][0] );
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_1_1, r2y_ctrl_cc->cc_matrix[1][1] );
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_1_2, r2y_ctrl_cc->cc_matrix[1][2] );
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_2_0, r2y_ctrl_cc->cc_matrix[2][0] );
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_2_1, r2y_ctrl_cc->cc_matrix[2][1] );
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_2_2, r2y_ctrl_cc->cc_matrix[2][2] );
	cc0_ctrl.CC0YBOF.bit.CC0YBOF_0 = r2y_ctrl_cc->cybof[0];
	cc0_ctrl.CC0YBOF.bit.CC0YBOF_1 = r2y_ctrl_cc->cybof[1];
	cc0_ctrl.CC0YBOF.bit.CC0YBOF_2 = r2y_ctrl_cc->cybof[2];
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_0, r2y_ctrl_cc->cybga[0] );
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_1, r2y_ctrl_cc->cybga[1] );
	im_r2y_set_reg_signed_a( cc0_ctrl.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_2, r2y_ctrl_cc->cybga[2] );
	cc0_ctrl.CC0YBBD.bit.CC0YBBD_1 = r2y_ctrl_cc->cybbd[0];
	cc0_ctrl.CC0YBBD.bit.CC0YBBD_2 = r2y_ctrl_cc->cybbd[1];
	cc0_ctrl.CCYC.bit.CCYC_0_0 = r2y_ctrl_cc->cyc[0];
	cc0_ctrl.CCYC.bit.CCYC_0_1 = r2y_ctrl_cc->cyc[1];
	cc0_ctrl.CCYC.bit.CCYC_0_2 = r2y_ctrl_cc->cyc[2];

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_CC0_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&cc0_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValCc0MatrixCoefficientCtrl( UCHAR pipe_no, const SHORT* const cc0k )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_CC0_COEF_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_CC0_COEF_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)cc0k;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValGammaCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_GAMMA* const r2y_ctrl_gamma )
{
	T_IM_R2Y_CTRL_RDMA_GAMMA_VAL gamma_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_GAMMA_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	gamma_ctrl.GMCTL.bit.GMEN  = r2y_ctrl_gamma->gamma_enable;
	gamma_ctrl.GMCTL.bit.GMMD  = r2y_ctrl_gamma->gamma_mode;
	gamma_ctrl.GMCTL.bit.GAMSW = r2y_ctrl_gamma->gamma_yb_tbl_simul;

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_GAMMA_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&gamma_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValCc1MatrixCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_CC1* const r2y_ctrl_cc )
{
	T_IM_R2Y_CTRL_RDMA_CC1_VAL cc1_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_CC1_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	cc1_ctrl.CC1CTL.bit.CC1DP = r2y_ctrl_cc->posi_dec;
	im_r2y_set_reg_signed_a( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_0_0, r2y_ctrl_cc->cc_matrix[0][0] );
	im_r2y_set_reg_signed_a( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_0_1, r2y_ctrl_cc->cc_matrix[0][1] );
	im_r2y_set_reg_signed_a( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_0_2, r2y_ctrl_cc->cc_matrix[0][2] );
	im_r2y_set_reg_signed_a( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_1_0, r2y_ctrl_cc->cc_matrix[1][0] );
	im_r2y_set_reg_signed_a( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_1_1, r2y_ctrl_cc->cc_matrix[1][1] );
	im_r2y_set_reg_signed_a( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_1_2, r2y_ctrl_cc->cc_matrix[1][2] );
	im_r2y_set_reg_signed_a( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_2_0, r2y_ctrl_cc->cc_matrix[2][0] );
	im_r2y_set_reg_signed_a( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_2_1, r2y_ctrl_cc->cc_matrix[2][1] );
	im_r2y_set_reg_signed_a( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_2_2, r2y_ctrl_cc->cc_matrix[2][2] );

	cc1_ctrl.CC1CLPR.bit.CC1CLPRP = r2y_ctrl_cc->clip_p_r;
	cc1_ctrl.CC1CLPR.bit.CC1CLPRM = r2y_ctrl_cc->clip_m_r;
	cc1_ctrl.CC1CLPG.bit.CC1CLPGP = r2y_ctrl_cc->clip_p_g;
	cc1_ctrl.CC1CLPG.bit.CC1CLPGM = r2y_ctrl_cc->clip_m_g;
	cc1_ctrl.CC1CLPB.bit.CC1CLPBP = r2y_ctrl_cc->clip_p_b;
	cc1_ctrl.CC1CLPB.bit.CC1CLPBM = r2y_ctrl_cc->clip_m_b;

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_CC1_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&cc1_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValCc1MatrixCoefficientCtrl( UCHAR pipe_no, const SHORT* const cc1k )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_CC1_COEF_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_CC1_COEF_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)cc1k;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValYcConvertCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_YCC* const r2y_ctrl_ycc )
{
	T_IM_R2Y_CTRL_RDMA_YCC_VAL ycc_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_YCC_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	im_r2y_set_reg_signed_a( ycc_ctrl.YC, union io_r2y_yc, YC_0_0, r2y_ctrl_ycc->yc_coeff[0][0] );
	im_r2y_set_reg_signed_a( ycc_ctrl.YC, union io_r2y_yc, YC_0_1, r2y_ctrl_ycc->yc_coeff[0][1] );
	im_r2y_set_reg_signed_a( ycc_ctrl.YC, union io_r2y_yc, YC_0_2, r2y_ctrl_ycc->yc_coeff[0][2] );
	im_r2y_set_reg_signed_a( ycc_ctrl.YC, union io_r2y_yc, YC_1_0, r2y_ctrl_ycc->yc_coeff[1][0] );
	im_r2y_set_reg_signed_a( ycc_ctrl.YC, union io_r2y_yc, YC_1_1, r2y_ctrl_ycc->yc_coeff[1][1] );
	im_r2y_set_reg_signed_a( ycc_ctrl.YC, union io_r2y_yc, YC_1_2, r2y_ctrl_ycc->yc_coeff[1][2] );
	im_r2y_set_reg_signed_a( ycc_ctrl.YC, union io_r2y_yc, YC_2_0, r2y_ctrl_ycc->yc_coeff[2][0] );
	im_r2y_set_reg_signed_a( ycc_ctrl.YC, union io_r2y_yc, YC_2_1, r2y_ctrl_ycc->yc_coeff[2][1] );
	im_r2y_set_reg_signed_a( ycc_ctrl.YC, union io_r2y_yc, YC_2_2, r2y_ctrl_ycc->yc_coeff[2][2] );
	ycc_ctrl.YBLEND.bit.YYBLND = r2y_ctrl_ycc->y_blend_ratio;
	ycc_ctrl.YBLEND.bit.YBBLND = r2y_ctrl_ycc->yb_blend_ratio;

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_YCC_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&ycc_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValYnrCtrl( UCHAR pipe_no, const T_IM_R2Y_CTRL_YNR* const r2y_ctrl_ynr )
{
	T_IM_R2Y_CTRL_RDMA_YNR_VAL ynr_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_YNR_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	ynr_ctrl.NRCTL.bit.NRMD    = r2y_ctrl_ynr->nr_mode;
	ynr_ctrl.NRCTL.bit.NRBLEND = r2y_ctrl_ynr->blend_ratio;
	ynr_ctrl.NROF.bit.NROF_0   = r2y_ctrl_ynr->offset[0];
	ynr_ctrl.NROF.bit.NROF_1   = r2y_ctrl_ynr->offset[1];
	ynr_ctrl.NROF.bit.NROF_2   = r2y_ctrl_ynr->offset[2];
	ynr_ctrl.NROF.bit.NROF_3   = r2y_ctrl_ynr->offset[3];
	im_r2y_set_reg_signed_a( ynr_ctrl.NRGA, union io_r2y_nrga, NRGA_0, r2y_ctrl_ynr->gain[0] );
	im_r2y_set_reg_signed_a( ynr_ctrl.NRGA, union io_r2y_nrga, NRGA_1, r2y_ctrl_ynr->gain[1] );
	im_r2y_set_reg_signed_a( ynr_ctrl.NRGA, union io_r2y_nrga, NRGA_2, r2y_ctrl_ynr->gain[2] );
	im_r2y_set_reg_signed_a( ynr_ctrl.NRGA, union io_r2y_nrga, NRGA_3, r2y_ctrl_ynr->gain[3] );
	ynr_ctrl.NRBD.bit.NRBD_1 = r2y_ctrl_ynr->border[0];
	ynr_ctrl.NRBD.bit.NRBD_2 = r2y_ctrl_ynr->border[1];
	ynr_ctrl.NRBD.bit.NRBD_3 = r2y_ctrl_ynr->border[2];

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_YNR_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&ynr_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}


#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
*PUBLIC
*/
/* WB Gain control
 */
INT32 im_r2y_ctrl2_set_wb_gain(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_RGB_COLOR* const rgb_color )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(rgb_color == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_set_wb_gain error. rgb_color = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_wb_gain error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.OFG.WBGAR.bit.WBGAR = rgb_color->R;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.OFG.WBGAR.bit.WBGAG = rgb_color->G;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.OFG.WBGAR.bit.WBGAB = rgb_color->B;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* WB Clip Level control
 */
INT32 im_r2y_ctrl2_set_wb_clip_level(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_RGB_COLOR* const rgb_color )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(rgb_color == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_set_wb_clip_level error. rgb_color = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_wb_clip_level error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValWbClipCtrl( pipe_no, rgb_color );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.OFG.WBLV.bit.WBLVR = rgb_color->R;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.OFG.WBLV.bit.WBLVG = rgb_color->G;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.OFG.WBLV.bit.WBLVB = rgb_color->B;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* CC0 Matrix Control
 */
INT32 im_r2y_ctrl2_cc0_matrix(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_CC0* const r2y_ctrl_cc )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_cc == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_cc0_matrix error. r2y_ctrl_cc = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_cc0_matrix error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValCc0MatrixCtrl( pipe_no, r2y_ctrl_cc );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0CTL.bit.CC0DP = r2y_ctrl_cc->posi_dec;
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_0, r2y_ctrl_cc->cc_matrix[0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_1, r2y_ctrl_cc->cc_matrix[0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_2, r2y_ctrl_cc->cc_matrix[0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_0, r2y_ctrl_cc->cc_matrix[1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_1, r2y_ctrl_cc->cc_matrix[1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_2, r2y_ctrl_cc->cc_matrix[1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_0, r2y_ctrl_cc->cc_matrix[2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_1, r2y_ctrl_cc->cc_matrix[2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_2, r2y_ctrl_cc->cc_matrix[2][2] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_0 = r2y_ctrl_cc->cybof[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_1 = r2y_ctrl_cc->cybof[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_2 = r2y_ctrl_cc->cybof[2];
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_0, r2y_ctrl_cc->cybga[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_1, r2y_ctrl_cc->cybga[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_2, r2y_ctrl_cc->cybga[2] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0YBBD.bit.CC0YBBD_1 = r2y_ctrl_cc->cybbd[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0YBBD.bit.CC0YBBD_2 = r2y_ctrl_cc->cybbd[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CCYC.bit.CCYC_0_0 = r2y_ctrl_cc->cyc[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CCYC.bit.CCYC_0_1 = r2y_ctrl_cc->cyc[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CCYC.bit.CCYC_0_2 = r2y_ctrl_cc->cyc[2];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set CC0 Matrix coefficient
 */
INT32 im_r2y_ctrl2_set_cc0_matrix_coefficient(ImR2yCtrl2 *self, UCHAR pipe_no, const SHORT* const cc0k )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(cc0k == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_set_cc0_matrix_coefficient error. cc0k = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_cc0_matrix_coefficient error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValCc0MatrixCoefficientCtrl( pipe_no, cc0k );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_0, cc0k[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_1, cc0k[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_2, cc0k[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_0, cc0k[3] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_1, cc0k[4] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_2, cc0k[5] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_0, cc0k[6] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_1, cc0k[7] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_2, cc0k[8] );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* RGB Offset before TC control
 */
INT32 im_r2y_ctrl2_before_tone_offset(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_TCOF* const r2y_ctrl_btc_offset )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_btc_offset == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl2_before_tone_offset error. r2y_ctrl_btc_offset = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_before_tone_offset error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	im_r2y_set_rdma_val_btc_ctrl_offset( pipe_no, r2y_ctrl_btc_offset );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCOF, union io_r2y_tcof, TCOFR, r2y_ctrl_btc_offset->R );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCOF, union io_r2y_tcof, TCOFG, r2y_ctrl_btc_offset->G );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCOF, union io_r2y_tcof, TCOFB, r2y_ctrl_btc_offset->B );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCOF, union io_r2y_tcof, TCOFYB, r2y_ctrl_btc_offset->Yb );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Luminance Evaluation before TC control
 */
INT32 im_r2y_ctrl2_before_tone_tct(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_TCT* const r2y_ctrl_btc_tct )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_btc_tct == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl2_before_tone_tct error. r2y_ctrl_btc_tct = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_before_tone_tct error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	im_r2y_set_rdma_val_btc_ctrl_tct( pipe_no, r2y_ctrl_btc_tct );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCTCTL.bit.TCTEN   = r2y_ctrl_btc_tct->tct_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCTSTA.bit.TCTHSTA = r2y_ctrl_btc_tct->start_x;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCTSTA.bit.TCTVSTA = r2y_ctrl_btc_tct->start_y;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCTB.bit.TCTBHSIZ  = r2y_ctrl_btc_tct->block_hsiz;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCTB.bit.TCTBVSIZ  = r2y_ctrl_btc_tct->block_vsiz;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCTB.bit.TCTBHNUM  = r2y_ctrl_btc_tct->block_hnum;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCTB.bit.TCTBVNUM  = r2y_ctrl_btc_tct->block_vnum;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Histogram before TC control
 */
INT32 im_r2y_ctrl2_before_tone_tchs(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_TCHS* const r2y_ctrl_btc_tchs )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_btc_tchs == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl2_before_tone_tchs error. r2y_ctrl_btc_tchs = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_before_tone_tchs error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	im_r2y_set_rdma_val_btc_ctrl_tchs( pipe_no, r2y_ctrl_btc_tchs );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHSCTL.bit.TCHSEN    = r2y_ctrl_btc_tchs->hist_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHSCTL.bit.TCHSHCYC  = r2y_ctrl_btc_tchs->sampling_hcyc;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHSCTL.bit.TCHSVCYC  = r2y_ctrl_btc_tchs->sampling_vcyc;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHSCTL.bit.TCHSRGBMD = r2y_ctrl_btc_tchs->histogram_mode;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHSCTL.bit.TCHSMN    = r2y_ctrl_btc_tchs->hist_minus_mode;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHSSTA.bit.TCHSHSTA  = r2y_ctrl_btc_tchs->tchs_window.img_left;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHSSTA.bit.TCHSVSTA  = r2y_ctrl_btc_tchs->tchs_window.img_top;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHSSIZ.bit.TCHSHSIZ  = r2y_ctrl_btc_tchs->tchs_window.img_width;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.BTC.TCHSSIZ.bit.TCHSVSIZ  = r2y_ctrl_btc_tchs->tchs_window.img_lines;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set Luminance evaluation table access enable
 */
INT32 im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(ImR2yCtrl2 *self, UCHAR pipe_no, UCHAR tct_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_tct_tbl_accen_ctrl,
									 tct_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Set BTC histogram table access enable
 */
INT32 im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(ImR2yCtrl2 *self, UCHAR pipe_no, UCHAR hist_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_btc_histogram_tbl_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_btc_histogram_tbl_accen_ctrl,
									 hist_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "Im_R2Y_Set_BTCHistogramTblAccessEnable error. Macro busy\n" )
									 );
}

/* Gamma Correction control
 */
INT32 im_r2y_ctrl2_gamma(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_GAMMA* const r2y_ctrl_gamma )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_gamma == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl2_gamma error. r2y_ctrl_gamma = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}

	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_gamma error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValGammaCtrl( pipe_no, r2y_ctrl_gamma );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.GAM.GMCTL.bit.GMEN  = r2y_ctrl_gamma->gamma_enable;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.GAM.GMCTL.bit.GMMD  = r2y_ctrl_gamma->gamma_mode;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.GAM.GMCTL.bit.GAMSW = r2y_ctrl_gamma->gamma_yb_tbl_simul;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set Gamma table access enable
 */
INT32 im_r2y_ctrl2_set_gamma_tbl_access_enable(ImR2yCtrl2 *self, UCHAR pipe_no, UCHAR acc_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_gamma_tbl_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_gamma_tbl_accen_ctrl,
									 acc_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y_ctrl2_set_gamma_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Set Gamma Yb table access enable
 */
INT32 im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(ImR2yCtrl2 *self, UCHAR pipe_no, UCHAR acc_enable, UCHAR wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_gamma_yb_tbl_access_enable error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipe_no,
									 &gim_r2y_gamma_yb_tbl_accen_ctrl,
									 acc_enable,
									 wait_enable,
									 M_IM_R2Y_ASSETION_MSG( "im_r2y_ctrl2_set_gamma_yb_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Is Gamma Control active
 */
INT32 im_r2y_ctrl2_is_act_gamma(ImR2yCtrl2 *self, UCHAR pipe_no, UCHAR* const active_status )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_is_act_gamma error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	*active_status = (gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CNTL.R2YFLAG.bit.GAMACT != 0)?(D_IM_R2Y_ENABLE_ON):(D_IM_R2Y_ENABLE_OFF);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return D_DDIM_OK;
}

/* CC1 Matrix Control
 */
INT32 im_r2y_ctrl2_cc1_matrix(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_CC1* const r2y_ctrl_cc )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_cc == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_cc1_matrix error. r2y_ctrl_cc = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_cc1_matrix error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValCc1MatrixCtrl( pipe_no, r2y_ctrl_cc );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1CTL.bit.CC1DP = r2y_ctrl_cc->posi_dec;
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_0, r2y_ctrl_cc->cc_matrix[0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_1, r2y_ctrl_cc->cc_matrix[0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_2, r2y_ctrl_cc->cc_matrix[0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_0, r2y_ctrl_cc->cc_matrix[1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_1, r2y_ctrl_cc->cc_matrix[1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_2, r2y_ctrl_cc->cc_matrix[1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_0, r2y_ctrl_cc->cc_matrix[2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_1, r2y_ctrl_cc->cc_matrix[2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_2, r2y_ctrl_cc->cc_matrix[2][2] );

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1CLPR.bit.CC1CLPRP = r2y_ctrl_cc->clip_p_r;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1CLPR.bit.CC1CLPRM = r2y_ctrl_cc->clip_m_r;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1CLPG.bit.CC1CLPGP = r2y_ctrl_cc->clip_p_g;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1CLPG.bit.CC1CLPGM = r2y_ctrl_cc->clip_m_g;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1CLPB.bit.CC1CLPBP = r2y_ctrl_cc->clip_p_b;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1CLPB.bit.CC1CLPBM = r2y_ctrl_cc->clip_m_b;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set CC1 Matrix coefficient
 */
INT32 im_r2y_ctrl2_set_cc1_matrix_coefficient(ImR2yCtrl2 *self, UCHAR pipe_no, const SHORT* const cc1k )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(cc1k == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_set_cc1_matrix_coefficient error. cc1k = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_cc1_matrix_coefficient error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValCc1MatrixCoefficientCtrl( pipe_no, cc1k );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_0, cc1k[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_1, cc1k[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_2, cc1k[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_0, cc1k[3] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_1, cc1k[4] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_2, cc1k[5] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_0, cc1k[6] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_1, cc1k[7] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_2, cc1k[8] );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* YC Convert control
 */
INT32 im_r2y_ctrl2_yc_convert(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_YCC* const r2y_ctrl_ycc )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_ycc == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_yc_convert error. r2y_ctrl_ycc = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_yc_convert error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValYcConvertCtrl( pipe_no, r2y_ctrl_ycc );
#else	// CO_R2Y_RDMA_ON
	// It sets it to the register at once.
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YC.YC, union io_r2y_yc, YC_0_0, r2y_ctrl_ycc->yc_coeff[0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YC.YC, union io_r2y_yc, YC_0_1, r2y_ctrl_ycc->yc_coeff[0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YC.YC, union io_r2y_yc, YC_0_2, r2y_ctrl_ycc->yc_coeff[0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YC.YC, union io_r2y_yc, YC_1_0, r2y_ctrl_ycc->yc_coeff[1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YC.YC, union io_r2y_yc, YC_1_1, r2y_ctrl_ycc->yc_coeff[1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YC.YC, union io_r2y_yc, YC_1_2, r2y_ctrl_ycc->yc_coeff[1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YC.YC, union io_r2y_yc, YC_2_0, r2y_ctrl_ycc->yc_coeff[2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YC.YC, union io_r2y_yc, YC_2_1, r2y_ctrl_ycc->yc_coeff[2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YC.YC, union io_r2y_yc, YC_2_2, r2y_ctrl_ycc->yc_coeff[2][2] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YC.YBLEND.bit.YYBLND = r2y_ctrl_ycc->y_blend_ratio;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YC.YBLEND.bit.YBBLND = r2y_ctrl_ycc->yb_blend_ratio;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Y(Luminance) Noise Reduction control
 */
INT32 im_r2y_ctrl2_ynr(ImR2yCtrl2 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_YNR* const r2y_ctrl_ynr )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_ynr == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_ynr error. r2y_ctrl_ynr = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_ynr error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValYnrCtrl( pipe_no, r2y_ctrl_ynr );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NRCTL.bit.NRMD    = r2y_ctrl_ynr->nr_mode;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NRCTL.bit.NRBLEND = r2y_ctrl_ynr->blend_ratio;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NROF.bit.NROF_0   = r2y_ctrl_ynr->offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NROF.bit.NROF_1   = r2y_ctrl_ynr->offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NROF.bit.NROF_2   = r2y_ctrl_ynr->offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NROF.bit.NROF_3   = r2y_ctrl_ynr->offset[3];
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NRGA, union io_r2y_nrga, NRGA_0, r2y_ctrl_ynr->gain[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NRGA, union io_r2y_nrga, NRGA_1, r2y_ctrl_ynr->gain[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NRGA, union io_r2y_nrga, NRGA_2, r2y_ctrl_ynr->gain[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NRGA, union io_r2y_nrga, NRGA_3, r2y_ctrl_ynr->gain[3] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NRBD.bit.NRBD_1 = r2y_ctrl_ynr->border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NRBD.bit.NRBD_2 = r2y_ctrl_ynr->border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.YNR.NRBD.bit.NRBD_3 = r2y_ctrl_ynr->border[2];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}


ImR2yCtrl2 *im_r2y_ctrl2_new(void)
{
	ImR2yCtrl2* self = k_object_new_with_private(IM_TYPE_R2Y_CTRL2,sizeof(ImR2yCtrl2Private));
	return self;
}
