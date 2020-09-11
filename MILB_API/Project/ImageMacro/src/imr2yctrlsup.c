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
static VOID imR2ySetRdmaValBtcOffsetCtrl( UCHAR pipe_no, const T_IM_R2Y_TCOF* const r2y_ctrl_btc_offset );
static VOID imR2ySetRdmaValBtcTctCtrl( UCHAR pipe_no, const T_IM_R2Y_TCT* const r2y_ctrl_btc_tct );
static VOID imR2ySetRdmaValBtcTchsCtrl( UCHAR pipe_no, const T_IM_R2Y_TCHS* const r2y_ctrl_btc_tchs );
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

static VOID imR2ySetRdmaValBtcOffsetCtrl( UCHAR pipe_no, const T_IM_R2Y_TCOF* const r2y_ctrl_btc_offset )
{
	T_IM_R2Y_CTRL_RDMA_BTC_TCOF_VAL btc_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_BTC_TCOF_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	im_r2y_set_reg_signed_a( btc_ctrl.TCOF, union io_r2y_tcof, TCOFR, r2y_ctrl_btc_offset->R );
	im_r2y_set_reg_signed_a( btc_ctrl.TCOF, union io_r2y_tcof, TCOFG, r2y_ctrl_btc_offset->G );
	im_r2y_set_reg_signed_a( btc_ctrl.TCOF, union io_r2y_tcof, TCOFB, r2y_ctrl_btc_offset->B );
	im_r2y_set_reg_signed_a( btc_ctrl.TCOF, union io_r2y_tcof, TCOFYB, r2y_ctrl_btc_offset->Yb );

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_BTC_TCOF_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&btc_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValBtcTctCtrl( UCHAR pipe_no, const T_IM_R2Y_TCT* const r2y_ctrl_btc_tct )
{
	T_IM_R2Y_CTRL_RDMA_BTC_TCT_VAL btc_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_BTC_TCT_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	btc_ctrl.TCTCTL.bit.TCTEN   = r2y_ctrl_btc_tct->tct_enable;
	btc_ctrl.TCTSTA.bit.TCTHSTA = r2y_ctrl_btc_tct->start_x;
	btc_ctrl.TCTSTA.bit.TCTVSTA = r2y_ctrl_btc_tct->start_y;
	btc_ctrl.TCTB.bit.TCTBHSIZ  = r2y_ctrl_btc_tct->block_hsiz;
	btc_ctrl.TCTB.bit.TCTBVSIZ  = r2y_ctrl_btc_tct->block_vsiz;
	btc_ctrl.TCTB.bit.TCTBHNUM  = r2y_ctrl_btc_tct->block_hnum;
	btc_ctrl.TCTB.bit.TCTBVNUM  = r2y_ctrl_btc_tct->block_vnum;

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_BTC_TCT_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&btc_ctrl;
	im_r2y_utils_start_rdma( im_r2y_utils_get(), &rdma_ctrl );
}

static VOID imR2ySetRdmaValBtcTchsCtrl( UCHAR pipe_no, const T_IM_R2Y_TCHS* const r2y_ctrl_btc_tchs )
{
	T_IM_R2Y_CTRL_RDMA_BTC_TCHS_VAL btc_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_BTC_TCHS_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	btc_ctrl.TCHSCTL.bit.TCHSEN    = r2y_ctrl_btc_tchs->hist_enable;
	btc_ctrl.TCHSCTL.bit.TCHSHCYC  = r2y_ctrl_btc_tchs->sampling_hcyc;
	btc_ctrl.TCHSCTL.bit.TCHSVCYC  = r2y_ctrl_btc_tchs->sampling_vcyc;
	btc_ctrl.TCHSCTL.bit.TCHSRGBMD = r2y_ctrl_btc_tchs->histogram_mode;
	btc_ctrl.TCHSCTL.bit.TCHSMN    = r2y_ctrl_btc_tchs->hist_minus_mode;
	btc_ctrl.TCHSSTA.bit.TCHSHSTA  = r2y_ctrl_btc_tchs->tchs_window.img_top;
	btc_ctrl.TCHSSTA.bit.TCHSVSTA  = r2y_ctrl_btc_tchs->tchs_window.img_left;
	btc_ctrl.TCHSSIZ.bit.TCHSHSIZ  = r2y_ctrl_btc_tchs->tchs_window.img_width;
	btc_ctrl.TCHSSIZ.bit.TCHSVSIZ  = r2y_ctrl_btc_tchs->tchs_window.img_lines;

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_BTC_TCHS_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&btc_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE

/*
*PUBLIC
*/
void im_r2y_ctrl_sup_multi_axis(ImR2yCtrlSup *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_MULTI_AXIS* const r2y_ctrl_multi_axis )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	// MCKA_0_00~MCKA_4_22
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_a_k[0][0][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_a_k[0][0][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_a_k[0][0][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_a_k[0][1][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_a_k[0][1][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_a_k[0][1][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_a_k[0][2][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_a_k[0][2][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_a_k[0][2][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_a_k[1][0][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_a_k[1][0][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_a_k[1][0][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_a_k[1][1][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_a_k[1][1][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_a_k[1][1][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_a_k[1][2][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_a_k[1][2][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_a_k[1][2][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_a_k[2][0][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_a_k[2][0][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_a_k[2][0][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_a_k[2][1][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_a_k[2][1][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_a_k[2][1][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_a_k[2][2][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_a_k[2][2][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_a_k[2][2][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_a_k[3][0][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_a_k[3][0][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_a_k[3][0][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_a_k[3][1][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_a_k[3][1][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_a_k[3][1][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_a_k[3][2][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_a_k[3][2][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_a_k[3][2][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_a_k[4][0][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_a_k[4][0][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_a_k[4][0][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_a_k[4][1][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_a_k[4][1][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_a_k[4][1][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_a_k[4][2][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_a_k[4][2][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKA.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_a_k[4][2][2] );

		// MCKB_0_00~MCKB_4_22
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_b_k[0][0][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_b_k[0][0][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_b_k[0][0][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_b_k[0][1][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_b_k[0][1][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_b_k[0][1][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_b_k[0][2][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_b_k[0][2][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_b_k[0][2][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_b_k[1][0][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_b_k[1][0][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_b_k[1][0][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_b_k[1][1][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_b_k[1][1][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_b_k[1][1][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_b_k[1][2][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_b_k[1][2][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_b_k[1][2][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_b_k[2][0][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_b_k[2][0][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_b_k[2][0][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_b_k[2][1][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_b_k[2][1][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_b_k[2][1][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_b_k[2][2][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_b_k[2][2][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_b_k[2][2][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_b_k[3][0][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_b_k[3][0][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_b_k[3][0][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_b_k[3][1][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_b_k[3][1][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_b_k[3][1][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_b_k[3][2][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_b_k[3][2][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_b_k[3][2][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_b_k[4][0][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_b_k[4][0][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_b_k[4][0][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_b_k[4][1][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_b_k[4][1][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_b_k[4][1][2] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_b_k[4][2][0] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_b_k[4][2][1] );
		im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKB.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_b_k[4][2][2] );

		// MCKC_0_00~MCKC_4_22
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_c_k[0][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_c_k[0][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_c_k[0][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_c_k[0][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_c_k[0][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_c_k[0][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_c_k[0][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_c_k[0][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_c_k[0][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_c_k[1][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_c_k[1][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_c_k[1][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_c_k[1][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_c_k[1][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_c_k[1][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_c_k[1][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_c_k[1][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_c_k[1][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_c_k[2][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_c_k[2][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_c_k[2][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_c_k[2][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_c_k[2][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_c_k[2][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_c_k[2][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_c_k[2][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_c_k[2][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_c_k[3][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_c_k[3][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_c_k[3][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_c_k[3][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_c_k[3][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_c_k[3][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_c_k[3][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_c_k[3][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_c_k[3][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_c_k[4][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_c_k[4][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_c_k[4][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_c_k[4][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_c_k[4][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_c_k[4][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_c_k[4][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_c_k[4][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKC.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_c_k[4][2][2] );

			// MCKD_0_00~MCKD_4_22
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_d_k[0][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_d_k[0][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_d_k[0][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_d_k[0][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_d_k[0][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_d_k[0][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_d_k[0][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_d_k[0][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_d_k[0][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_d_k[1][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_d_k[1][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_d_k[1][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_d_k[1][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_d_k[1][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_d_k[1][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_d_k[1][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_d_k[1][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_d_k[1][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_d_k[2][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_d_k[2][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_d_k[2][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_d_k[2][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_d_k[2][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_d_k[2][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_d_k[2][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_d_k[2][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_d_k[2][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_d_k[3][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_d_k[3][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_d_k[3][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_d_k[3][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_d_k[3][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_d_k[3][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_d_k[3][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_d_k[3][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_d_k[3][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_d_k[4][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_d_k[4][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_d_k[4][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_d_k[4][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_d_k[4][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_d_k[4][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_d_k[4][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_d_k[4][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_d_k[4][2][2] );

			// MCKE_0_00~MCKE_4_22
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_e_k[0][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_e_k[0][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_e_k[0][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_e_k[0][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_e_k[0][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_e_k[0][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_e_k[0][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_e_k[0][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_e_k[0][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_e_k[1][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_e_k[1][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_e_k[1][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_e_k[1][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_e_k[1][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_e_k[1][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_e_k[1][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_e_k[1][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_e_k[1][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_e_k[2][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_e_k[2][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_e_k[2][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_e_k[2][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_e_k[2][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_e_k[2][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_e_k[2][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_e_k[2][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_e_k[2][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_e_k[3][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_e_k[3][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_e_k[3][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_e_k[3][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_e_k[3][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_e_k[3][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_e_k[3][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_e_k[3][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_e_k[3][2][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_e_k[4][0][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_e_k[4][0][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_e_k[4][0][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_e_k[4][1][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_e_k[4][1][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_e_k[4][1][2] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_e_k[4][2][0] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_e_k[4][2][1] );
			im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_e_k[4][2][2] );

}

#ifdef CO_DDIM_UTILITY_USE
#ifdef CO_R2Y_RDMA_ON

VOID im_r2y_ctrl_sup_set_rdma_val_multi_axis(ImR2yCtrlSup *self, T_IM_R2Y_CTRL_RDMA_MCYC_VAL* mcyc_ctrl, UCHAR pipe_no, const T_IM_R2Y_CTRL_MULTI_AXIS* const r2y_ctrl_multi_axis )
{
	// MCYC10~MCYC22
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_0_0, r2y_ctrl_multi_axis->cyc_coeff[0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_0_1, r2y_ctrl_multi_axis->cyc_coeff[1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_0_2, r2y_ctrl_multi_axis->cyc_coeff[2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_1_0, r2y_ctrl_multi_axis->cyc_coeff[3] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_1_1, r2y_ctrl_multi_axis->cyc_coeff[4] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_1_2, r2y_ctrl_multi_axis->cyc_coeff[5] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_2_0, r2y_ctrl_multi_axis->cyc_coeff[6] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_2_1, r2y_ctrl_multi_axis->cyc_coeff[7] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCYC, union io_r2y_mcyc, MCYC_2_2, r2y_ctrl_multi_axis->cyc_coeff[8] );

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
		mcyc_ctrl->MCID1.bit.MCID1A = r2y_ctrl_multi_axis->area_index[0][0];
		mcyc_ctrl->MCID1.bit.MCID1B = r2y_ctrl_multi_axis->area_index[0][1];
		mcyc_ctrl->MCID1.bit.MCID1C = r2y_ctrl_multi_axis->area_index[0][2];
		mcyc_ctrl->MCID1.bit.MCID1D = r2y_ctrl_multi_axis->area_index[0][3];
		mcyc_ctrl->MCID1.bit.MCID1E = r2y_ctrl_multi_axis->area_index[0][4];
		mcyc_ctrl->MCID2.bit.MCID2A = r2y_ctrl_multi_axis->area_index[1][0];
		mcyc_ctrl->MCID2.bit.MCID2B = r2y_ctrl_multi_axis->area_index[1][1];
		mcyc_ctrl->MCID2.bit.MCID2C = r2y_ctrl_multi_axis->area_index[1][2];
		mcyc_ctrl->MCID2.bit.MCID2D = r2y_ctrl_multi_axis->area_index[1][3];
		mcyc_ctrl->MCID2.bit.MCID2E = r2y_ctrl_multi_axis->area_index[1][4];
		mcyc_ctrl->MCID3.bit.MCID3A = r2y_ctrl_multi_axis->area_index[2][0];
		mcyc_ctrl->MCID3.bit.MCID3B = r2y_ctrl_multi_axis->area_index[2][1];
		mcyc_ctrl->MCID3.bit.MCID3C = r2y_ctrl_multi_axis->area_index[2][2];
		mcyc_ctrl->MCID3.bit.MCID3D = r2y_ctrl_multi_axis->area_index[2][3];
		mcyc_ctrl->MCID3.bit.MCID3E = r2y_ctrl_multi_axis->area_index[2][4];
		mcyc_ctrl->MCID4.bit.MCID4A = r2y_ctrl_multi_axis->area_index[3][0];
		mcyc_ctrl->MCID4.bit.MCID4B = r2y_ctrl_multi_axis->area_index[3][1];
		mcyc_ctrl->MCID4.bit.MCID4C = r2y_ctrl_multi_axis->area_index[3][2];
		mcyc_ctrl->MCID4.bit.MCID4D = r2y_ctrl_multi_axis->area_index[3][3];
		mcyc_ctrl->MCID4.bit.MCID4E = r2y_ctrl_multi_axis->area_index[3][4];

		// MCKA_0_00~MCKA_4_22
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_a_k[0][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_a_k[0][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_a_k[0][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_a_k[0][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_a_k[0][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_a_k[0][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_a_k[0][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_a_k[0][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_a_k[0][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_a_k[1][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_a_k[1][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_a_k[1][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_a_k[1][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_a_k[1][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_a_k[1][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_a_k[1][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_a_k[1][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_a_k[1][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_a_k[2][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_a_k[2][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_a_k[2][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_a_k[2][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_a_k[2][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_a_k[2][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_a_k[2][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_a_k[2][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_a_k[2][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_a_k[3][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_a_k[3][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_a_k[3][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_a_k[3][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_a_k[3][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_a_k[3][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_a_k[3][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_a_k[3][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_a_k[3][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_a_k[4][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_a_k[4][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_a_k[4][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_a_k[4][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_a_k[4][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_a_k[4][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_a_k[4][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_a_k[4][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKA.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_a_k[4][2][2] );

		// MCKB_0_00~MCKB_4_22
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_b_k[0][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_b_k[0][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_b_k[0][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_b_k[0][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_b_k[0][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_b_k[0][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_b_k[0][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_b_k[0][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_b_k[0][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_b_k[1][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_b_k[1][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_b_k[1][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_b_k[1][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_b_k[1][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_b_k[1][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_b_k[1][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_b_k[1][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_b_k[1][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_b_k[2][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_b_k[2][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_b_k[2][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_b_k[2][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_b_k[2][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_b_k[2][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_b_k[2][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_b_k[2][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_b_k[2][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_b_k[3][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_b_k[3][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_b_k[3][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_b_k[3][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_b_k[3][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_b_k[3][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_b_k[3][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_b_k[3][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_b_k[3][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_b_k[4][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_b_k[4][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_b_k[4][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_b_k[4][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_b_k[4][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_b_k[4][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_b_k[4][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_b_k[4][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKB.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_b_k[4][2][2] );

		// MCKC_0_00~MCKC_4_22
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_c_k[0][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_c_k[0][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_c_k[0][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_c_k[0][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_c_k[0][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_c_k[0][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_c_k[0][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_c_k[0][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_c_k[0][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_c_k[1][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_c_k[1][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_c_k[1][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_c_k[1][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_c_k[1][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_c_k[1][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_c_k[1][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_c_k[1][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_c_k[1][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_c_k[2][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_c_k[2][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_c_k[2][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_c_k[2][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_c_k[2][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_c_k[2][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_c_k[2][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_c_k[2][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_c_k[2][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_c_k[3][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_c_k[3][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_c_k[3][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_c_k[3][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_c_k[3][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_c_k[3][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_c_k[3][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_c_k[3][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_c_k[3][2][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_c_k[4][0][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_c_k[4][0][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_c_k[4][0][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_c_k[4][1][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_c_k[4][1][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_c_k[4][1][2] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_c_k[4][2][0] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_c_k[4][2][1] );
		im_r2y_set_reg_signed_a( mcyc_ctrl->MCKC.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_c_k[4][2][2] );

}

#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE

ImR2yCtrlSup *im_r2y_ctrl_sup_new(void)
{
	ImR2yCtrlSup* self = k_object_new_with_private(IM_TYPE_R2Y_CTRL_SUP,sizeof(ImR2yCtrlSupPrivate));
	return self;
}
