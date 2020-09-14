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
#include "imr2yutils.h"
#include "imr2y2.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yCtrl2, im_r2y_ctrl2);
#define IM_R2Y_CTRL2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yCtrl2Private, IM_TYPE_R2Y_CTRL2))

struct _ImR2yCtrl2Private
{
	int a;
};


static void imR2ySetTctAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_tct_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetTctAccessEnable,
};

static void imR2ySetBtcHistogramAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_btc_histogram_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetBtcHistogramAccessEnable,
};

static void imR2ySetGammaTblAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_gamma_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetGammaTblAccessEnable,
};

static void imR2ySetGammaYbTblAccessEnable( kuint16 pipeNo, const kuint16 enable );
static volatile R2yAccessEnableManage gim_r2y_gamma_yb_tbl_accen_ctrl = {
	.ctrlCnt = { 0, 0 },
	.reg_set_func = imR2ySetGammaYbTblAccessEnable,
};


#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static void imR2ySetRdmaValWbClipCtrl( kuint16 pipeNo, const R2yRgbColor* const rgb_color );
static void imR2ySetRdmaValCc0MatrixCtrl( kuint16 pipeNo, const R2yCtrlCc0* const r2y_ctrl_cc );
static void imR2ySetRdmaValCc0MatrixCoefficientCtrl( kuint16 pipeNo, const kint16* const cc0k );
static void imR2ySetRdmaValGammaCtrl( kuint16 pipeNo, const ImR2yCtrlGamma* const r2y_ctrl_gamma );
static void imR2ySetRdmaValCc1MatrixCtrl( kuint16 pipeNo, const R2yCtrlCc1* const r2y_ctrl_cc );
static void imR2ySetRdmaValCc1MatrixCoefficientCtrl( kuint16 pipeNo, const kint16* const cc1k );
static void imR2ySetRdmaValYcConvertCtrl( kuint16 pipeNo, const R2yCtrlYcc* const r2y_ctrl_ycc );
static void imR2ySetRdmaValYnrCtrl( kuint16 pipeNo, const R2yCtrlYnr* const r2y_ctrl_ynr );

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

static void imR2ySetTctAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCTCTL.bit.TCTAEN = enable;
}

static void imR2ySetBtcHistogramAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHSCTL.bit.TCHAEN = enable;
}

static void imR2ySetGammaTblAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->F_R2Y.GAM.GMCTL.bit.GMAEN = enable;
}

static void imR2ySetGammaYbTblAccessEnable( kuint16 pipeNo, const kuint16 enable )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	gImIoR2yRegPtr[pipeNo]->F_R2Y.GAM.GMCTL.bit.GMYAEN = enable;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static void imR2ySetRdmaValWbClipCtrl( kuint16 pipeNo, const R2yRgbColor* const rgb_color )
{
	RdmaWbClipVal wb_clip_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_WB_CLIP_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	wb_clip_ctrl.WBLV.bit.WBLVR = rgb_color->R;
	wb_clip_ctrl.WBLV.bit.WBLVG = rgb_color->G;
	wb_clip_ctrl.WBLV.bit.WBLVB = rgb_color->B;

	rdma_ctrl.transfer_byte = sizeof( RdmaWbClipVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&wb_clip_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValCc0MatrixCtrl( kuint16 pipeNo, const R2yCtrlCc0* const r2y_ctrl_cc )
{
	CtrlRdmaCc0Val cc0_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_CC0_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	cc0_ctrl.CC0CTL.bit.CC0DP = r2y_ctrl_cc->posiDec;
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_0_0, r2y_ctrl_cc->ccMatrix[0][0] );
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_0_1, r2y_ctrl_cc->ccMatrix[0][1] );
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_0_2, r2y_ctrl_cc->ccMatrix[0][2] );
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_1_0, r2y_ctrl_cc->ccMatrix[1][0] );
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_1_1, r2y_ctrl_cc->ccMatrix[1][1] );
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_1_2, r2y_ctrl_cc->ccMatrix[1][2] );
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_2_0, r2y_ctrl_cc->ccMatrix[2][0] );
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_2_1, r2y_ctrl_cc->ccMatrix[2][1] );
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0K, union io_r2y_cc0k, CC0K_2_2, r2y_ctrl_cc->ccMatrix[2][2] );
	cc0_ctrl.CC0YBOF.bit.CC0YBOF_0 = r2y_ctrl_cc->cybof[0];
	cc0_ctrl.CC0YBOF.bit.CC0YBOF_1 = r2y_ctrl_cc->cybof[1];
	cc0_ctrl.CC0YBOF.bit.CC0YBOF_2 = r2y_ctrl_cc->cybof[2];
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_0, r2y_ctrl_cc->cybga[0] );
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_1, r2y_ctrl_cc->cybga[1] );
	imR2yUtils_SET_REG_SIGNED_A( cc0_ctrl.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_2, r2y_ctrl_cc->cybga[2] );
	cc0_ctrl.CC0YBBD.bit.CC0YBBD_1 = r2y_ctrl_cc->cybbd[0];
	cc0_ctrl.CC0YBBD.bit.CC0YBBD_2 = r2y_ctrl_cc->cybbd[1];
	cc0_ctrl.CCYC.bit.CCYC_0_0 = r2y_ctrl_cc->cyc[0];
	cc0_ctrl.CCYC.bit.CCYC_0_1 = r2y_ctrl_cc->cyc[1];
	cc0_ctrl.CCYC.bit.CCYC_0_2 = r2y_ctrl_cc->cyc[2];

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaCc0Val );
	rdma_ctrl.reg_data_top_addr = (kulong)&cc0_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValCc0MatrixCoefficientCtrl( kuint16 pipeNo, const kint16* const cc0k )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_CC0_COEF_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = sizeof( RdmaCc0CoefVal );
	rdma_ctrl.reg_data_top_addr = (kulong)cc0k;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValGammaCtrl( kuint16 pipeNo, const ImR2yCtrlGamma* const r2y_ctrl_gamma )
{
	CtrlRdmaGammaVal gamma_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_GAMMA_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	gamma_ctrl.GMCTL.bit.GMEN  = r2y_ctrl_gamma->gammaEnable;
	gamma_ctrl.GMCTL.bit.GMMD  = r2y_ctrl_gamma->gammaMode;
	gamma_ctrl.GMCTL.bit.GAMSW = r2y_ctrl_gamma->gammaYbTblSimul;

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaGammaVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&gamma_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValCc1MatrixCtrl( kuint16 pipeNo, const R2yCtrlCc1* const r2y_ctrl_cc )
{
	CtrlRdmaCc1Val cc1_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_CC1_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	cc1_ctrl.CC1CTL.bit.CC1DP = r2y_ctrl_cc->posiDec;
	imR2yUtils_SET_REG_SIGNED_A( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_0_0, r2y_ctrl_cc->ccMatrix[0][0] );
	imR2yUtils_SET_REG_SIGNED_A( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_0_1, r2y_ctrl_cc->ccMatrix[0][1] );
	imR2yUtils_SET_REG_SIGNED_A( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_0_2, r2y_ctrl_cc->ccMatrix[0][2] );
	imR2yUtils_SET_REG_SIGNED_A( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_1_0, r2y_ctrl_cc->ccMatrix[1][0] );
	imR2yUtils_SET_REG_SIGNED_A( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_1_1, r2y_ctrl_cc->ccMatrix[1][1] );
	imR2yUtils_SET_REG_SIGNED_A( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_1_2, r2y_ctrl_cc->ccMatrix[1][2] );
	imR2yUtils_SET_REG_SIGNED_A( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_2_0, r2y_ctrl_cc->ccMatrix[2][0] );
	imR2yUtils_SET_REG_SIGNED_A( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_2_1, r2y_ctrl_cc->ccMatrix[2][1] );
	imR2yUtils_SET_REG_SIGNED_A( cc1_ctrl.CC1K, union io_r2y_cc1k, CC1K_2_2, r2y_ctrl_cc->ccMatrix[2][2] );

	cc1_ctrl.CC1CLPR.bit.CC1CLPRP = r2y_ctrl_cc->clipPR;
	cc1_ctrl.CC1CLPR.bit.CC1CLPRM = r2y_ctrl_cc->clipMR;
	cc1_ctrl.CC1CLPG.bit.CC1CLPGP = r2y_ctrl_cc->clipPG;
	cc1_ctrl.CC1CLPG.bit.CC1CLPGM = r2y_ctrl_cc->clipMG;
	cc1_ctrl.CC1CLPB.bit.CC1CLPBP = r2y_ctrl_cc->clipPB;
	cc1_ctrl.CC1CLPB.bit.CC1CLPBM = r2y_ctrl_cc->clipMB;

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaCc1Val );
	rdma_ctrl.reg_data_top_addr = (kulong)&cc1_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValCc1MatrixCoefficientCtrl( kuint16 pipeNo, const kint16* const cc1k )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_CC1_COEF_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = sizeof( RdmaCc1CoefVal );
	rdma_ctrl.reg_data_top_addr = (kulong)cc1k;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValYcConvertCtrl( kuint16 pipeNo, const R2yCtrlYcc* const r2y_ctrl_ycc )
{
	CtrlRdmaYccVal ycc_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_YCC_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	imR2yUtils_SET_REG_SIGNED_A( ycc_ctrl.YC, union io_r2y_yc, YC_0_0, r2y_ctrl_ycc->ycCoeff[0][0] );
	imR2yUtils_SET_REG_SIGNED_A( ycc_ctrl.YC, union io_r2y_yc, YC_0_1, r2y_ctrl_ycc->ycCoeff[0][1] );
	imR2yUtils_SET_REG_SIGNED_A( ycc_ctrl.YC, union io_r2y_yc, YC_0_2, r2y_ctrl_ycc->ycCoeff[0][2] );
	imR2yUtils_SET_REG_SIGNED_A( ycc_ctrl.YC, union io_r2y_yc, YC_1_0, r2y_ctrl_ycc->ycCoeff[1][0] );
	imR2yUtils_SET_REG_SIGNED_A( ycc_ctrl.YC, union io_r2y_yc, YC_1_1, r2y_ctrl_ycc->ycCoeff[1][1] );
	imR2yUtils_SET_REG_SIGNED_A( ycc_ctrl.YC, union io_r2y_yc, YC_1_2, r2y_ctrl_ycc->ycCoeff[1][2] );
	imR2yUtils_SET_REG_SIGNED_A( ycc_ctrl.YC, union io_r2y_yc, YC_2_0, r2y_ctrl_ycc->ycCoeff[2][0] );
	imR2yUtils_SET_REG_SIGNED_A( ycc_ctrl.YC, union io_r2y_yc, YC_2_1, r2y_ctrl_ycc->ycCoeff[2][1] );
	imR2yUtils_SET_REG_SIGNED_A( ycc_ctrl.YC, union io_r2y_yc, YC_2_2, r2y_ctrl_ycc->ycCoeff[2][2] );
	ycc_ctrl.YBLEND.bit.YYBLND = r2y_ctrl_ycc->yBlendRatio;
	ycc_ctrl.YBLEND.bit.YBBLND = r2y_ctrl_ycc->ybBlendRatio;

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaYccVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&ycc_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValYnrCtrl( kuint16 pipeNo, const R2yCtrlYnr* const r2y_ctrl_ynr )
{
	CtrlRdmaYnrVal ynr_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_YNR_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	ynr_ctrl.NRCTL.bit.NRMD    = r2y_ctrl_ynr->nrMode;
	ynr_ctrl.NRCTL.bit.NRBLEND = r2y_ctrl_ynr->blendRatio;
	ynr_ctrl.NROF.bit.NROF_0   = r2y_ctrl_ynr->offset[0];
	ynr_ctrl.NROF.bit.NROF_1   = r2y_ctrl_ynr->offset[1];
	ynr_ctrl.NROF.bit.NROF_2   = r2y_ctrl_ynr->offset[2];
	ynr_ctrl.NROF.bit.NROF_3   = r2y_ctrl_ynr->offset[3];
	imR2yUtils_SET_REG_SIGNED_A( ynr_ctrl.NRGA, union io_r2y_nrga, NRGA_0, r2y_ctrl_ynr->gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( ynr_ctrl.NRGA, union io_r2y_nrga, NRGA_1, r2y_ctrl_ynr->gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( ynr_ctrl.NRGA, union io_r2y_nrga, NRGA_2, r2y_ctrl_ynr->gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( ynr_ctrl.NRGA, union io_r2y_nrga, NRGA_3, r2y_ctrl_ynr->gain[3] );
	ynr_ctrl.NRBD.bit.NRBD_1 = r2y_ctrl_ynr->border[0];
	ynr_ctrl.NRBD.bit.NRBD_2 = r2y_ctrl_ynr->border[1];
	ynr_ctrl.NRBD.bit.NRBD_3 = r2y_ctrl_ynr->border[2];

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaYnrVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&ynr_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}


#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
*PUBLIC
*/
/* WB Gain control
 */
INT32 im_r2y_ctrl2_set_wb_gain(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yRgbColor* const rgb_color )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(rgb_color == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_set_wb_gain error. rgb_color = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_wb_gain error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.OFG.WBGAR.bit.WBGAR = rgb_color->R;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.OFG.WBGAR.bit.WBGAG = rgb_color->G;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.OFG.WBGAR.bit.WBGAB = rgb_color->B;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* WB Clip Level control
 */
INT32 im_r2y_ctrl2_set_wb_clip_level(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yRgbColor* const rgb_color )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(rgb_color == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_set_wb_clip_level error. rgb_color = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_wb_clip_level error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValWbClipCtrl( pipeNo, rgb_color );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.OFG.WBLV.bit.WBLVR = rgb_color->R;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.OFG.WBLV.bit.WBLVG = rgb_color->G;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.OFG.WBLV.bit.WBLVB = rgb_color->B;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* CC0 Matrix Control
 */
INT32 im_r2y_ctrl2_cc0_matrix(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yCtrlCc0* const r2y_ctrl_cc )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_cc == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_cc0_matrix error. r2y_ctrl_cc = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_cc0_matrix error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValCc0MatrixCtrl( pipeNo, r2y_ctrl_cc );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0CTL.bit.CC0DP = r2y_ctrl_cc->posiDec;
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_0, r2y_ctrl_cc->ccMatrix[0][0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_1, r2y_ctrl_cc->ccMatrix[0][1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_2, r2y_ctrl_cc->ccMatrix[0][2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_0, r2y_ctrl_cc->ccMatrix[1][0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_1, r2y_ctrl_cc->ccMatrix[1][1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_2, r2y_ctrl_cc->ccMatrix[1][2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_0, r2y_ctrl_cc->ccMatrix[2][0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_1, r2y_ctrl_cc->ccMatrix[2][1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_2, r2y_ctrl_cc->ccMatrix[2][2] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_0 = r2y_ctrl_cc->cybof[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_1 = r2y_ctrl_cc->cybof[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_2 = r2y_ctrl_cc->cybof[2];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_0, r2y_ctrl_cc->cybga[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_1, r2y_ctrl_cc->cybga[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0YBGA, union io_r2y_cc0ybga, CC0YBGA_2, r2y_ctrl_cc->cybga[2] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0YBBD.bit.CC0YBBD_1 = r2y_ctrl_cc->cybbd[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0YBBD.bit.CC0YBBD_2 = r2y_ctrl_cc->cybbd[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CCYC.bit.CCYC_0_0 = r2y_ctrl_cc->cyc[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CCYC.bit.CCYC_0_1 = r2y_ctrl_cc->cyc[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CCYC.bit.CCYC_0_2 = r2y_ctrl_cc->cyc[2];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set CC0 Matrix coefficient
 */
INT32 im_r2y_ctrl2_set_cc0_matrix_coefficient(ImR2yCtrl2 *self, kuint16 pipeNo, const kint16* const cc0k )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(cc0k == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_set_cc0_matrix_coefficient error. cc0k = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_cc0_matrix_coefficient error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValCc0MatrixCoefficientCtrl( pipeNo, cc0k );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_0, cc0k[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_1, cc0k[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_0_2, cc0k[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_0, cc0k[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_1, cc0k[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_1_2, cc0k[5] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_0, cc0k[6] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_1, cc0k[7] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA0.CC0K, union io_r2y_cc0k, CC0K_2_2, cc0k[8] );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* RGB Offset before TC control
 */
INT32 im_r2y_ctrl2_before_tone_offset(ImR2yCtrl2 *self, kuint16 pipeNo, const TImR2yTcof* const r2y_ctrl_btc_offset )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_btc_offset == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl2_before_tone_offset error. r2y_ctrl_btc_offset = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_before_tone_offset error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	im_r2y_set_rdma_val_btc_ctrl_offset( pipeNo, r2y_ctrl_btc_offset );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCOF, union io_r2y_tcof, TCOFR, r2y_ctrl_btc_offset->R );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCOF, union io_r2y_tcof, TCOFG, r2y_ctrl_btc_offset->G );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCOF, union io_r2y_tcof, TCOFB, r2y_ctrl_btc_offset->B );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCOF, union io_r2y_tcof, TCOFYB, r2y_ctrl_btc_offset->Yb );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Luminance Evaluation before TC control
 */
INT32 im_r2y_ctrl2_before_tone_tct(ImR2yCtrl2 *self, kuint16 pipeNo, const TImR2yTct* const r2y_ctrl_btc_tct )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_btc_tct == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl2_before_tone_tct error. r2y_ctrl_btc_tct = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_before_tone_tct error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	im_r2y_set_rdma_val_btc_ctrl_tct( pipeNo, r2y_ctrl_btc_tct );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCTCTL.bit.TCTEN   = r2y_ctrl_btc_tct->tctEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCTSTA.bit.TCTHSTA = r2y_ctrl_btc_tct->startX;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCTSTA.bit.TCTVSTA = r2y_ctrl_btc_tct->startY;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCTB.bit.TCTBHSIZ  = r2y_ctrl_btc_tct->blockHsiz;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCTB.bit.TCTBVSIZ  = r2y_ctrl_btc_tct->blockVsiz;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCTB.bit.TCTBHNUM  = r2y_ctrl_btc_tct->blockHnum;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCTB.bit.TCTBVNUM  = r2y_ctrl_btc_tct->blockVnum;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Histogram before TC control
 */
INT32 im_r2y_ctrl2_before_tone_tchs(ImR2yCtrl2 *self, kuint16 pipeNo, const TImR2yTchs* const r2y_ctrl_btc_tchs )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_btc_tchs == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl2_before_tone_tchs error. r2y_ctrl_btc_tchs = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_before_tone_tchs error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	im_r2y_set_rdma_val_btc_ctrl_tchs( pipeNo, r2y_ctrl_btc_tchs );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHSCTL.bit.TCHSEN    = r2y_ctrl_btc_tchs->histEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHSCTL.bit.TCHSHCYC  = r2y_ctrl_btc_tchs->samplingHcyc;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHSCTL.bit.TCHSVCYC  = r2y_ctrl_btc_tchs->samplingVcyc;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHSCTL.bit.TCHSRGBMD = r2y_ctrl_btc_tchs->histogramMode;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHSCTL.bit.TCHSMN    = r2y_ctrl_btc_tchs->histMinusMode;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHSSTA.bit.TCHSHSTA  = r2y_ctrl_btc_tchs->tchsWindow.imgLeft;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHSSTA.bit.TCHSVSTA  = r2y_ctrl_btc_tchs->tchsWindow.imgTop;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHSSIZ.bit.TCHSHSIZ  = r2y_ctrl_btc_tchs->tchsWindow.imgWidth;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.BTC.TCHSSIZ.bit.TCHSVSIZ  = r2y_ctrl_btc_tchs->tchsWindow.imgLines;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set Luminance evaluation table access enable
 */
INT32 im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(ImR2yCtrl2 *self, kuint16 pipeNo, kuint16 tctEnable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_tct_tbl_accen_ctrl,
									 tctEnable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Set BTC histogram table access enable
 */
INT32 im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(ImR2yCtrl2 *self, kuint16 pipeNo, kuint16 histEnable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_btc_histogram_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_btc_histogram_tbl_accen_ctrl,
									 histEnable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "Im_R2Y_Set_BTCHistogramTblAccessEnable error. Macro busy\n" )
									 );
}

/* Gamma Correction control
 */
INT32 im_r2y_ctrl2_gamma(ImR2yCtrl2 *self, kuint16 pipeNo, const ImR2yCtrlGamma* const r2y_ctrl_gamma )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_gamma == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl2_gamma error. r2y_ctrl_gamma = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}

	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_gamma error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValGammaCtrl( pipeNo, r2y_ctrl_gamma );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.GAM.GMCTL.bit.GMEN  = r2y_ctrl_gamma->gammaEnable;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.GAM.GMCTL.bit.GMMD  = r2y_ctrl_gamma->gammaMode;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.GAM.GMCTL.bit.GAMSW = r2y_ctrl_gamma->gammaYbTblSimul;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set Gamma table access enable
 */
INT32 im_r2y_ctrl2_set_gamma_tbl_access_enable(ImR2yCtrl2 *self, kuint16 pipeNo, kuint16 acc_enable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_gamma_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_gamma_tbl_accen_ctrl,
									 acc_enable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y_ctrl2_set_gamma_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Set Gamma Yb table access enable
 */
INT32 im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(ImR2yCtrl2 *self, kuint16 pipeNo, kuint16 acc_enable, kuint16 wait_enable )
{
#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_gamma_yb_tbl_access_enable error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	return im_r2y_set_access_enable(im_r2y2_new(), pipeNo,
									 &gim_r2y_gamma_yb_tbl_accen_ctrl,
									 acc_enable,
									 wait_enable,
									 ImR2yUtils_ASSETION_MSG( "im_r2y_ctrl2_set_gamma_yb_tbl_access_enable error. Macro busy\n" )
									 );
}

/* Is Gamma Control active
 */
INT32 im_r2y_ctrl2_is_act_gamma(ImR2yCtrl2 *self, kuint16 pipeNo, kuint16* const active_status )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_is_act_gamma error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	*active_status = (gImIoR2yRegPtr[pipeNo]->F_R2Y.CNTL.R2YFLAG.bit.GAMACT != 0)?(ImR2yCtrl_ENABLE_ON):(ImR2yCtrl_ENABLE_OFF);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return D_DDIM_OK;
}

/* CC1 Matrix Control
 */
INT32 im_r2y_ctrl2_cc1_matrix(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yCtrlCc1* const r2y_ctrl_cc )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_cc == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_cc1_matrix error. r2y_ctrl_cc = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_cc1_matrix error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValCc1MatrixCtrl( pipeNo, r2y_ctrl_cc );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1CTL.bit.CC1DP = r2y_ctrl_cc->posiDec;
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_0, r2y_ctrl_cc->ccMatrix[0][0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_1, r2y_ctrl_cc->ccMatrix[0][1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_2, r2y_ctrl_cc->ccMatrix[0][2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_0, r2y_ctrl_cc->ccMatrix[1][0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_1, r2y_ctrl_cc->ccMatrix[1][1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_2, r2y_ctrl_cc->ccMatrix[1][2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_0, r2y_ctrl_cc->ccMatrix[2][0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_1, r2y_ctrl_cc->ccMatrix[2][1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_2, r2y_ctrl_cc->ccMatrix[2][2] );

	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1CLPR.bit.CC1CLPRP = r2y_ctrl_cc->clipPR;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1CLPR.bit.CC1CLPRM = r2y_ctrl_cc->clipMR;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1CLPG.bit.CC1CLPGP = r2y_ctrl_cc->clipPG;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1CLPG.bit.CC1CLPGM = r2y_ctrl_cc->clipMG;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1CLPB.bit.CC1CLPBP = r2y_ctrl_cc->clipPB;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1CLPB.bit.CC1CLPBM = r2y_ctrl_cc->clipMB;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Set CC1 Matrix coefficient
 */
INT32 im_r2y_ctrl2_set_cc1_matrix_coefficient(ImR2yCtrl2 *self, kuint16 pipeNo, const kint16* const cc1k )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(cc1k == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_set_cc1_matrix_coefficient error. cc1k = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_set_cc1_matrix_coefficient error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValCc1MatrixCoefficientCtrl( pipeNo, cc1k );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_0, cc1k[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_1, cc1k[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_0_2, cc1k[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_0, cc1k[3] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_1, cc1k[4] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_1_2, cc1k[5] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_0, cc1k[6] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_1, cc1k[7] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.CCA1.CC1K, union io_r2y_cc1k, CC1K_2_2, cc1k[8] );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* YC Convert control
 */
INT32 im_r2y_ctrl2_yc_convert(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yCtrlYcc* const r2y_ctrl_ycc )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_ycc == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_yc_convert error. r2y_ctrl_ycc = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_yc_convert error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValYcConvertCtrl( pipeNo, r2y_ctrl_ycc );
#else	// CO_R2Y_RDMA_ON
	// It sets it to the register at once.
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YC.YC, union io_r2y_yc, YC_0_0, r2y_ctrl_ycc->ycCoeff[0][0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YC.YC, union io_r2y_yc, YC_0_1, r2y_ctrl_ycc->ycCoeff[0][1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YC.YC, union io_r2y_yc, YC_0_2, r2y_ctrl_ycc->ycCoeff[0][2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YC.YC, union io_r2y_yc, YC_1_0, r2y_ctrl_ycc->ycCoeff[1][0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YC.YC, union io_r2y_yc, YC_1_1, r2y_ctrl_ycc->ycCoeff[1][1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YC.YC, union io_r2y_yc, YC_1_2, r2y_ctrl_ycc->ycCoeff[1][2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YC.YC, union io_r2y_yc, YC_2_0, r2y_ctrl_ycc->ycCoeff[2][0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YC.YC, union io_r2y_yc, YC_2_1, r2y_ctrl_ycc->ycCoeff[2][1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YC.YC, union io_r2y_yc, YC_2_2, r2y_ctrl_ycc->ycCoeff[2][2] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YC.YBLEND.bit.YYBLND = r2y_ctrl_ycc->yBlendRatio;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YC.YBLEND.bit.YBBLND = r2y_ctrl_ycc->ybBlendRatio;
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}

/* Y(Luminance) Noise Reduction control
 */
INT32 im_r2y_ctrl2_ynr(ImR2yCtrl2 *self, kuint16 pipeNo, const R2yCtrlYnr* const r2y_ctrl_ynr )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_ctrl_ynr == NULL) {
		Ddim_Assertion(("im_r2y_ctrl2_ynr error. r2y_ctrl_ynr = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl2_ynr error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	imR2ySetRdmaValYnrCtrl( pipeNo, r2y_ctrl_ynr );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NRCTL.bit.NRMD    = r2y_ctrl_ynr->nrMode;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NRCTL.bit.NRBLEND = r2y_ctrl_ynr->blendRatio;
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NROF.bit.NROF_0   = r2y_ctrl_ynr->offset[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NROF.bit.NROF_1   = r2y_ctrl_ynr->offset[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NROF.bit.NROF_2   = r2y_ctrl_ynr->offset[2];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NROF.bit.NROF_3   = r2y_ctrl_ynr->offset[3];
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NRGA, union io_r2y_nrga, NRGA_0, r2y_ctrl_ynr->gain[0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NRGA, union io_r2y_nrga, NRGA_1, r2y_ctrl_ynr->gain[1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NRGA, union io_r2y_nrga, NRGA_2, r2y_ctrl_ynr->gain[2] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NRGA, union io_r2y_nrga, NRGA_3, r2y_ctrl_ynr->gain[3] );
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NRBD.bit.NRBD_1 = r2y_ctrl_ynr->border[0];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NRBD.bit.NRBD_2 = r2y_ctrl_ynr->border[1];
	gImIoR2yRegPtr[pipeNo]->F_R2Y.YNR.NRBD.bit.NRBD_3 = r2y_ctrl_ynr->border[2];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}


ImR2yCtrl2 *im_r2y_ctrl2_new(void)
{
	ImR2yCtrl2* self = k_object_new_with_private(IM_TYPE_R2Y_CTRL2,sizeof(ImR2yCtrl2Private));
	return self;
}
