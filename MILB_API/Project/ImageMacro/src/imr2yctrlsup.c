/*
 * imr2yctrlsup.c
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
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

#include "imr2yctrlsup.h"
#include "imr2y.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yCtrlSup, im_r2y_ctrl_sup);
#define IM_R2Y_CTRL_SUP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yCtrlSupPrivate, IM_TYPE_R2Y_CTRL_SUP))

struct _ImR2yCtrlSupPrivate
{
	int a;
};


/*
*DECLS
*/
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
static void imR2ySetRdmaValBtcOffsetCtrl( kuint16 pipeNo, const TImR2yTcof* const r2y_ctrl_btc_offset );
static void imR2ySetRdmaValBtcTctCtrl( kuint16 pipeNo, const TImR2yTct* const r2y_ctrl_btc_tct );
static void imR2ySetRdmaValBtcTchsCtrl( kuint16 pipeNo, const TImR2yTchs* const r2y_ctrl_btc_tchs );
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


/*
*IMPL
*/
static void im_r2y_ctrl_sup_constructor(ImR2yCtrlSup *self)
{
	ImR2yCtrlSupPrivate *priv = IM_R2Y_CTRL_SUP_GET_PRIVATE(self);
}

static void im_r2y_ctrl_sup_destructor(ImR2yCtrlSup *self)
{
	ImR2yCtrlSupPrivate *priv = IM_R2Y_CTRL_SUP_GET_PRIVATE(self);
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON

static void imR2ySetRdmaValBtcOffsetCtrl( kuint16 pipeNo, const TImR2yTcof* const r2y_ctrl_btc_offset )
{
	RdmaBtcTcofVal btc_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_BTC_TCOF_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	imR2yUtils_SET_REG_SIGNED_A( btc_ctrl.TCOF, union io_r2y_tcof, TCOFR, r2y_ctrl_btc_offset->R );
	imR2yUtils_SET_REG_SIGNED_A( btc_ctrl.TCOF, union io_r2y_tcof, TCOFG, r2y_ctrl_btc_offset->G );
	imR2yUtils_SET_REG_SIGNED_A( btc_ctrl.TCOF, union io_r2y_tcof, TCOFB, r2y_ctrl_btc_offset->B );
	imR2yUtils_SET_REG_SIGNED_A( btc_ctrl.TCOF, union io_r2y_tcof, TCOFYB, r2y_ctrl_btc_offset->Yb );

	rdma_ctrl.transfer_byte = sizeof( RdmaBtcTcofVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&btc_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValBtcTctCtrl( kuint16 pipeNo, const TImR2yTct* const r2y_ctrl_btc_tct )
{
	RdmaBtcTctVal btc_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_BTC_TCT_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	btc_ctrl.TCTCTL.bit.TCTEN   = r2y_ctrl_btc_tct->tctEnable;
	btc_ctrl.TCTSTA.bit.TCTHSTA = r2y_ctrl_btc_tct->startX;
	btc_ctrl.TCTSTA.bit.TCTVSTA = r2y_ctrl_btc_tct->startY;
	btc_ctrl.TCTB.bit.TCTBHSIZ  = r2y_ctrl_btc_tct->blockHsiz;
	btc_ctrl.TCTB.bit.TCTBVSIZ  = r2y_ctrl_btc_tct->blockVsiz;
	btc_ctrl.TCTB.bit.TCTBHNUM  = r2y_ctrl_btc_tct->blockHnum;
	btc_ctrl.TCTB.bit.TCTBVNUM  = r2y_ctrl_btc_tct->blockVnum;

	rdma_ctrl.transfer_byte = sizeof( RdmaBtcTctVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&btc_ctrl;
	im_r2y_utils_start_rdma( im_r2y_utils_get(), &rdma_ctrl );
}

static void imR2ySetRdmaValBtcTchsCtrl( kuint16 pipeNo, const TImR2yTchs* const r2y_ctrl_btc_tchs )
{
	RdmaBtcTchsVal btc_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_BTC_TCHS_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	btc_ctrl.TCHSCTL.bit.TCHSEN    = r2y_ctrl_btc_tchs->histEnable;
	btc_ctrl.TCHSCTL.bit.TCHSHCYC  = r2y_ctrl_btc_tchs->samplingHcyc;
	btc_ctrl.TCHSCTL.bit.TCHSVCYC  = r2y_ctrl_btc_tchs->samplingVcyc;
	btc_ctrl.TCHSCTL.bit.TCHSRGBMD = r2y_ctrl_btc_tchs->histogramMode;
	btc_ctrl.TCHSCTL.bit.TCHSMN    = r2y_ctrl_btc_tchs->histMinusMode;
	btc_ctrl.TCHSSTA.bit.TCHSHSTA  = r2y_ctrl_btc_tchs->tchsWindow.imgTop;
	btc_ctrl.TCHSSTA.bit.TCHSVSTA  = r2y_ctrl_btc_tchs->tchsWindow.imgLeft;
	btc_ctrl.TCHSSIZ.bit.TCHSHSIZ  = r2y_ctrl_btc_tchs->tchsWindow.imgWidth;
	btc_ctrl.TCHSSIZ.bit.TCHSVSIZ  = r2y_ctrl_btc_tchs->tchsWindow.imgLines;

	rdma_ctrl.transfer_byte = sizeof( RdmaBtcTchsVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&btc_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE

/*
*PUBLIC
*/
void im_r2y_ctrl_sup_multi_axis(ImR2yCtrlSup *self, kuint16 pipeNo, const CtrlMultiAxis* const r2y_ctrl_multi_axis )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	// MCKA_0_00~MCKA_4_22
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaAK[0][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaAK[0][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaAK[0][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaAK[0][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaAK[0][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaAK[0][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaAK[0][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaAK[0][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaAK[0][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaAK[1][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaAK[1][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaAK[1][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaAK[1][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaAK[1][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaAK[1][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaAK[1][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaAK[1][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaAK[1][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaAK[2][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaAK[2][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaAK[2][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaAK[2][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaAK[2][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaAK[2][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaAK[2][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaAK[2][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaAK[2][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaAK[3][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaAK[3][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaAK[3][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaAK[3][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaAK[3][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaAK[3][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaAK[3][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaAK[3][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaAK[3][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaAK[4][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaAK[4][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaAK[4][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaAK[4][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaAK[4][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaAK[4][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaAK[4][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaAK[4][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaAK[4][2][2] );

		// MCKB_0_00~MCKB_4_22
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaBK[0][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaBK[0][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaBK[0][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaBK[0][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaBK[0][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaBK[0][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaBK[0][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaBK[0][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaBK[0][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaBK[1][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaBK[1][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaBK[1][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaBK[1][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaBK[1][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaBK[1][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaBK[1][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaBK[1][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaBK[1][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaBK[2][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaBK[2][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaBK[2][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaBK[2][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaBK[2][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaBK[2][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaBK[2][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaBK[2][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaBK[2][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaBK[3][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaBK[3][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaBK[3][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaBK[3][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaBK[3][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaBK[3][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaBK[3][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaBK[3][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaBK[3][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaBK[4][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaBK[4][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaBK[4][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaBK[4][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaBK[4][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaBK[4][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaBK[4][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaBK[4][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaBK[4][2][2] );

		// MCKC_0_00~MCKC_4_22
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaCK[0][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaCK[0][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaCK[0][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaCK[0][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaCK[0][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaCK[0][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaCK[0][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaCK[0][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaCK[0][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaCK[1][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaCK[1][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaCK[1][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaCK[1][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaCK[1][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaCK[1][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaCK[1][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaCK[1][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaCK[1][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaCK[2][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaCK[2][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaCK[2][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaCK[2][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaCK[2][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaCK[2][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaCK[2][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaCK[2][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaCK[2][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaCK[3][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaCK[3][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaCK[3][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaCK[3][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaCK[3][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaCK[3][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaCK[3][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaCK[3][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaCK[3][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaCK[4][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaCK[4][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaCK[4][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaCK[4][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaCK[4][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaCK[4][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaCK[4][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaCK[4][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaCK[4][2][2] );

			// MCKD_0_00~MCKD_4_22
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaDK[0][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaDK[0][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaDK[0][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaDK[0][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaDK[0][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaDK[0][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaDK[0][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaDK[0][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaDK[0][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaDK[1][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaDK[1][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaDK[1][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaDK[1][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaDK[1][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaDK[1][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaDK[1][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaDK[1][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaDK[1][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaDK[2][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaDK[2][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaDK[2][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaDK[2][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaDK[2][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaDK[2][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaDK[2][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaDK[2][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaDK[2][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaDK[3][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaDK[3][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaDK[3][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaDK[3][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaDK[3][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaDK[3][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaDK[3][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaDK[3][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaDK[3][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaDK[4][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaDK[4][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaDK[4][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaDK[4][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaDK[4][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaDK[4][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaDK[4][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaDK[4][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaDK[4][2][2] );

			// MCKE_0_00~MCKE_4_22
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaEK[0][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaEK[0][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaEK[0][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaEK[0][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaEK[0][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaEK[0][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaEK[0][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaEK[0][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaEK[0][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaEK[1][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaEK[1][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaEK[1][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaEK[1][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaEK[1][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaEK[1][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaEK[1][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaEK[1][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaEK[1][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaEK[2][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaEK[2][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaEK[2][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaEK[2][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaEK[2][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaEK[2][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaEK[2][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaEK[2][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaEK[2][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaEK[3][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaEK[3][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaEK[3][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaEK[3][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaEK[3][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaEK[3][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaEK[3][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaEK[3][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaEK[3][2][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaEK[4][0][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaEK[4][0][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaEK[4][0][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaEK[4][1][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaEK[4][1][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaEK[4][1][2] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaEK[4][2][0] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaEK[4][2][1] );
			imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaEK[4][2][2] );

}

#ifdef CO_DDIM_UTILITY_USE
#ifdef CO_R2Y_RDMA_ON

void im_r2y_ctrl_sup_set_rdma_val_multi_axis(ImR2yCtrlSup *self, CtrlRdmaMcycVal* mcyc_ctrl, kuint16 pipeNo, const CtrlMultiAxis* const r2y_ctrl_multi_axis )
{
	// MCYC10~MCYC22
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_0_0, r2y_ctrl_multi_axis->cycCoeff[0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_0_1, r2y_ctrl_multi_axis->cycCoeff[1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_0_2, r2y_ctrl_multi_axis->cycCoeff[2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_1_0, r2y_ctrl_multi_axis->cycCoeff[3] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_1_1, r2y_ctrl_multi_axis->cycCoeff[4] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_1_2, r2y_ctrl_multi_axis->cycCoeff[5] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_2_0, r2y_ctrl_multi_axis->cycCoeff[6] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_2_1, r2y_ctrl_multi_axis->cycCoeff[7] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_2_2, r2y_ctrl_multi_axis->cycCoeff[8] );

		// MCB1A~MCB4D
		mcyc_ctrl->MCB1AB.bit.MCB1A = r2y_ctrl_multi_axis->boundary[0];
		mcyc_ctrl->MCB1AB.bit.MCB1B = r2y_ctrl_multi_axis->boundary[1];
		mcyc_ctrl->MCB1CD.bit.MCB1C = r2y_ctrl_multi_axis->boundary[2];
		mcyc_ctrl->MCB1CD.bit.MCB1D = r2y_ctrl_multi_axis->boundary[3];
		mcyc_ctrl->MCB2AB.bit.MCB2A = r2y_ctrl_multi_axis->boundary[4];
		mcyc_ctrl->MCB2AB.bit.MCB2B = r2y_ctrl_multi_axis->boundary[5];
		mcyc_ctrl->MCB2CD.bit.MCB2C = r2y_ctrl_multi_axis->boundary[6];
		mcyc_ctrl->MCB2CD.bit.MCB2D = r2y_ctrl_multi_axis->boundary[7];
		mcyc_ctrl->MCB3AB.bit.MCB3A = r2y_ctrl_multi_axis->boundary[8];
		mcyc_ctrl->MCB3AB.bit.MCB3B = r2y_ctrl_multi_axis->boundary[9];
		mcyc_ctrl->MCB3CD.bit.MCB3C = r2y_ctrl_multi_axis->boundary[10];
		mcyc_ctrl->MCB3CD.bit.MCB3D = r2y_ctrl_multi_axis->boundary[11];
		mcyc_ctrl->MCB4AB.bit.MCB4A = r2y_ctrl_multi_axis->boundary[12];
		mcyc_ctrl->MCB4AB.bit.MCB4B = r2y_ctrl_multi_axis->boundary[13];
		mcyc_ctrl->MCB4CD.bit.MCB4C = r2y_ctrl_multi_axis->boundary[14];
		mcyc_ctrl->MCB4CD.bit.MCB4D = r2y_ctrl_multi_axis->boundary[15];

		// MCID1~MCID4
		mcyc_ctrl->MCID1.bit.MCID1A = r2y_ctrl_multi_axis->areaIndex[0][0];
		mcyc_ctrl->MCID1.bit.MCID1B = r2y_ctrl_multi_axis->areaIndex[0][1];
		mcyc_ctrl->MCID1.bit.MCID1C = r2y_ctrl_multi_axis->areaIndex[0][2];
		mcyc_ctrl->MCID1.bit.MCID1D = r2y_ctrl_multi_axis->areaIndex[0][3];
		mcyc_ctrl->MCID1.bit.MCID1E = r2y_ctrl_multi_axis->areaIndex[0][4];
		mcyc_ctrl->MCID2.bit.MCID2A = r2y_ctrl_multi_axis->areaIndex[1][0];
		mcyc_ctrl->MCID2.bit.MCID2B = r2y_ctrl_multi_axis->areaIndex[1][1];
		mcyc_ctrl->MCID2.bit.MCID2C = r2y_ctrl_multi_axis->areaIndex[1][2];
		mcyc_ctrl->MCID2.bit.MCID2D = r2y_ctrl_multi_axis->areaIndex[1][3];
		mcyc_ctrl->MCID2.bit.MCID2E = r2y_ctrl_multi_axis->areaIndex[1][4];
		mcyc_ctrl->MCID3.bit.MCID3A = r2y_ctrl_multi_axis->areaIndex[2][0];
		mcyc_ctrl->MCID3.bit.MCID3B = r2y_ctrl_multi_axis->areaIndex[2][1];
		mcyc_ctrl->MCID3.bit.MCID3C = r2y_ctrl_multi_axis->areaIndex[2][2];
		mcyc_ctrl->MCID3.bit.MCID3D = r2y_ctrl_multi_axis->areaIndex[2][3];
		mcyc_ctrl->MCID3.bit.MCID3E = r2y_ctrl_multi_axis->areaIndex[2][4];
		mcyc_ctrl->MCID4.bit.MCID4A = r2y_ctrl_multi_axis->areaIndex[3][0];
		mcyc_ctrl->MCID4.bit.MCID4B = r2y_ctrl_multi_axis->areaIndex[3][1];
		mcyc_ctrl->MCID4.bit.MCID4C = r2y_ctrl_multi_axis->areaIndex[3][2];
		mcyc_ctrl->MCID4.bit.MCID4D = r2y_ctrl_multi_axis->areaIndex[3][3];
		mcyc_ctrl->MCID4.bit.MCID4E = r2y_ctrl_multi_axis->areaIndex[3][4];

		// MCKA_0_00~MCKA_4_22
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaAK[0][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaAK[0][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaAK[0][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaAK[0][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaAK[0][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaAK[0][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaAK[0][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaAK[0][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaAK[0][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaAK[1][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaAK[1][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaAK[1][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaAK[1][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaAK[1][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaAK[1][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaAK[1][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaAK[1][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaAK[1][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaAK[2][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaAK[2][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaAK[2][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaAK[2][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaAK[2][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaAK[2][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaAK[2][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaAK[2][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaAK[2][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaAK[3][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaAK[3][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaAK[3][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaAK[3][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaAK[3][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaAK[3][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaAK[3][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaAK[3][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaAK[3][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaAK[4][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaAK[4][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaAK[4][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaAK[4][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaAK[4][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaAK[4][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaAK[4][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaAK[4][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaAK[4][2][2] );

		// MCKB_0_00~MCKB_4_22
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaBK[0][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaBK[0][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaBK[0][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaBK[0][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaBK[0][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaBK[0][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaBK[0][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaBK[0][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaBK[0][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaBK[1][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaBK[1][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaBK[1][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaBK[1][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaBK[1][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaBK[1][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaBK[1][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaBK[1][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaBK[1][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaBK[2][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaBK[2][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaBK[2][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaBK[2][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaBK[2][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaBK[2][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaBK[2][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaBK[2][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaBK[2][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaBK[3][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaBK[3][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaBK[3][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaBK[3][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaBK[3][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaBK[3][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaBK[3][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaBK[3][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaBK[3][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaBK[4][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaBK[4][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaBK[4][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaBK[4][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaBK[4][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaBK[4][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaBK[4][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaBK[4][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaBK[4][2][2] );

		// MCKC_0_00~MCKC_4_22
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaCK[0][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaCK[0][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaCK[0][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaCK[0][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaCK[0][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaCK[0][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaCK[0][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaCK[0][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaCK[0][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaCK[1][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaCK[1][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaCK[1][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaCK[1][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaCK[1][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaCK[1][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaCK[1][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaCK[1][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaCK[1][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaCK[2][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaCK[2][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaCK[2][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaCK[2][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaCK[2][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaCK[2][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaCK[2][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaCK[2][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaCK[2][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaCK[3][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaCK[3][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaCK[3][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaCK[3][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaCK[3][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaCK[3][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaCK[3][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaCK[3][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaCK[3][2][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaCK[4][0][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaCK[4][0][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaCK[4][0][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaCK[4][1][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaCK[4][1][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaCK[4][1][2] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaCK[4][2][0] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaCK[4][2][1] );
		imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaCK[4][2][2] );

}

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE

ImR2yCtrlSup *im_r2y_ctrl_sup_new(void)
{
	ImR2yCtrlSup* self = k_object_new_with_private(IM_TYPE_R2Y_CTRL_SUP,sizeof(ImR2yCtrlSupPrivate));
	return self;
}
