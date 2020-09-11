/*
 * imr2yctrl5.c
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

#include "imr2yctrl5.h"
#include "imr2yutils.h"
#include "imr2y.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yCtrl5, im_r2y_ctrl5);
#define IM_R2Y_CTRL5_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yCtrl5Private, IM_TYPE_R2Y_CTRL5))

struct _ImR2yCtrl5Private
{
	int a;
};

/*
*DECLS
*/

/*
*IMPL
*/
static void im_r2y_ctrl5_constructor(ImR2yCtrl5 *self)
{
	ImR2yCtrl5Private *priv = IM_R2Y_CTRL5_GET_PRIVATE(self);
}

static void im_r2y_ctrl5_destructor(ImR2yCtrl5 *self)
{
	ImR2yCtrl5Private *priv = IM_R2Y_CTRL5_GET_PRIVATE(self);
}


/*
*PUBLIC
*/
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
VOID im_r2y_ctrl5_set_rdma_val_multi_axis(ImR2yCtrl5 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_MULTI_AXIS* const r2y_ctrl_multi_axis )
{
	T_IM_R2Y_CTRL_RDMA_MCYC_VAL mcyc_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(gIM_R2Y_MCYC_Addr[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	im_r2y_ctrl_sup_set_rdma_val_multi_axis(&mcyc_ctrl, pipe_no, r2y_ctrl_multi_axis);
	// MCKD_0_00~MCKD_4_22
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_d_k[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_d_k[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_d_k[0][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_d_k[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_d_k[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_d_k[0][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_d_k[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_d_k[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_d_k[0][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_d_k[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_d_k[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_d_k[1][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_d_k[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_d_k[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_d_k[1][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_d_k[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_d_k[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_d_k[1][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_d_k[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_d_k[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_d_k[2][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_d_k[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_d_k[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_d_k[2][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_d_k[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_d_k[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_d_k[2][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_d_k[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_d_k[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_d_k[3][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_d_k[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_d_k[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_d_k[3][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_d_k[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_d_k[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_d_k[3][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_d_k[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_d_k[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_d_k[4][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_d_k[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_d_k[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_d_k[4][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_d_k[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_d_k[4][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_d_k[4][2][2] );

	// MCKE_0_00~MCKE_4_22
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_e_k[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_e_k[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_e_k[0][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_e_k[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_e_k[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_e_k[0][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_e_k[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_e_k[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_e_k[0][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_e_k[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_e_k[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_e_k[1][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_e_k[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_e_k[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_e_k[1][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_e_k[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_e_k[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_e_k[1][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_e_k[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_e_k[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_e_k[2][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_e_k[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_e_k[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_e_k[2][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_e_k[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_e_k[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_e_k[2][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_e_k[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_e_k[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_e_k[3][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_e_k[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_e_k[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_e_k[3][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_e_k[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_e_k[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_e_k[3][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_e_k[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_e_k[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_e_k[4][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_e_k[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_e_k[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_e_k[4][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_e_k[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_e_k[4][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_e_k[4][2][2] );

	// MCKF_0_00~MCKF_4_22
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_f_k[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_f_k[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_f_k[0][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_f_k[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_f_k[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_f_k[0][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_f_k[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_f_k[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_f_k[0][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_f_k[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_f_k[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_f_k[1][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_f_k[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_f_k[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_f_k[1][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_f_k[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_f_k[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_f_k[1][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_f_k[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_f_k[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_f_k[2][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_f_k[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_f_k[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_f_k[2][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_f_k[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_f_k[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_f_k[2][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_f_k[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_f_k[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_f_k[3][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_f_k[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_f_k[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_f_k[3][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_f_k[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_f_k[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_f_k[3][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_f_k[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_f_k[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_f_k[4][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_f_k[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_f_k[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_f_k[4][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_f_k[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_f_k[4][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_f_k[4][2][2] );

	// MCKG_0_00~MCKG_4_22
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_g_k[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_g_k[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_g_k[0][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_g_k[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_g_k[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_g_k[0][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_g_k[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_g_k[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_g_k[0][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_g_k[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_g_k[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_g_k[1][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_g_k[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_g_k[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_g_k[1][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_g_k[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_g_k[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_g_k[1][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_g_k[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_g_k[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_g_k[2][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_g_k[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_g_k[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_g_k[2][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_g_k[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_g_k[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_g_k[2][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_g_k[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_g_k[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_g_k[3][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_g_k[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_g_k[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_g_k[3][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_g_k[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_g_k[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_g_k[3][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_g_k[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_g_k[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_g_k[4][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_g_k[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_g_k[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_g_k[4][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_g_k[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_g_k[4][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_g_k[4][2][2] );

	// MCKH_0_00~MCKH_4_22
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_h_k[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_h_k[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_h_k[0][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_h_k[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_h_k[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_h_k[0][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_h_k[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_h_k[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_h_k[0][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_h_k[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_h_k[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_h_k[1][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_h_k[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_h_k[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_h_k[1][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_h_k[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_h_k[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_h_k[1][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_h_k[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_h_k[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_h_k[2][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_h_k[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_h_k[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_h_k[2][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_h_k[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_h_k[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_h_k[2][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_h_k[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_h_k[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_h_k[3][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_h_k[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_h_k[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_h_k[3][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_h_k[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_h_k[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_h_k[3][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_h_k[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_h_k[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_h_k[4][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_h_k[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_h_k[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_h_k[4][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_h_k[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_h_k[4][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_h_k[4][2][2] );

	// MCKI_0_00~MCKI_4_22
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_i_k[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_i_k[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_i_k[0][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_i_k[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_i_k[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_i_k[0][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_i_k[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_i_k[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_i_k[0][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_i_k[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_i_k[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_i_k[1][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_i_k[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_i_k[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_i_k[1][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_i_k[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_i_k[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_i_k[1][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_i_k[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_i_k[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_i_k[2][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_i_k[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_i_k[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_i_k[2][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_i_k[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_i_k[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_i_k[2][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_i_k[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_i_k[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_i_k[3][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_i_k[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_i_k[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_i_k[3][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_i_k[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_i_k[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_i_k[3][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_i_k[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_i_k[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_i_k[4][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_i_k[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_i_k[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_i_k[4][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_i_k[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_i_k[4][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_i_k[4][2][2] );

	// MCKJ_0_00~MCKJ_4_22
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_j_k[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_j_k[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_j_k[0][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_j_k[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_j_k[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_j_k[0][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_j_k[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_j_k[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_j_k[0][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_j_k[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_j_k[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_j_k[1][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_j_k[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_j_k[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_j_k[1][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_j_k[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_j_k[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_j_k[1][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_j_k[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_j_k[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_j_k[2][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_j_k[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_j_k[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_j_k[2][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_j_k[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_j_k[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_j_k[2][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_j_k[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_j_k[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_j_k[3][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_j_k[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_j_k[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_j_k[3][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_j_k[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_j_k[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_j_k[3][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_j_k[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_j_k[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_j_k[4][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_j_k[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_j_k[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_j_k[4][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_j_k[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_j_k[4][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_j_k[4][2][2] );

	// MCKK_0_00~MCKK_4_22
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_k_k[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_k_k[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_k_k[0][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_k_k[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_k_k[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_k_k[0][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_k_k[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_k_k[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_k_k[0][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_k_k[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_k_k[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_k_k[1][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_k_k[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_k_k[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_k_k[1][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_k_k[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_k_k[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_k_k[1][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_k_k[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_k_k[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_k_k[2][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_k_k[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_k_k[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_k_k[2][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_k_k[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_k_k[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_k_k[2][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_k_k[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_k_k[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_k_k[3][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_k_k[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_k_k[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_k_k[3][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_k_k[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_k_k[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_k_k[3][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_k_k[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_k_k[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_k_k[4][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_k_k[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_k_k[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_k_k[4][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_k_k[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_k_k[4][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_k_k[4][2][2] );

	// MCKL_0_00~MCKL_4_22
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_l_k[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_l_k[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_l_k[0][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_l_k[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_l_k[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_l_k[0][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_l_k[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_l_k[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_l_k[0][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_l_k[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_l_k[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_l_k[1][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_l_k[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_l_k[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_l_k[1][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_l_k[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_l_k[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_l_k[1][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_l_k[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_l_k[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_l_k[2][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_l_k[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_l_k[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_l_k[2][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_l_k[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_l_k[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_l_k[2][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_l_k[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_l_k[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_l_k[3][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_l_k[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_l_k[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_l_k[3][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_l_k[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_l_k[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_l_k[3][2][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_l_k[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_l_k[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_l_k[4][0][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_l_k[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_l_k[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_l_k[4][1][2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_l_k[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_l_k[4][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_l_k[4][2][2] );

	// MCLA_0_00~MCLA_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_a_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_a_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_a_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_a_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_a_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_a_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_a_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_a_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_a_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_a_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_a_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_a_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_a_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_a_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_a_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_a_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_a_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_a_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_a_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_a_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_a_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_a_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_a_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_a_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_a_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_a_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_a_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_a_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_a_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_a_l[4][2][1] );

	// MCLB_0_00~MCLB_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_b_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_b_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_b_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_b_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_b_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_b_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_b_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_b_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_b_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_b_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_b_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_b_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_b_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_b_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_b_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_b_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_b_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_b_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_b_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_b_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_b_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_b_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_b_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_b_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_b_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_b_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_b_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_b_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_b_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_b_l[4][2][1] );

	// MCLC_0_00~MCLC_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_c_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_c_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_c_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_c_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_c_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_c_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_c_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_c_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_c_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_c_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_c_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_c_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_c_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_c_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_c_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_c_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_c_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_c_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_c_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_c_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_c_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_c_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_c_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_c_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_c_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_c_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_c_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_c_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_c_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_c_l[4][2][1] );

	// MCLD_0_00~MCLD_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_d_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_d_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_d_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_d_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_d_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_d_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_d_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_d_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_d_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_d_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_d_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_d_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_d_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_d_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_d_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_d_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_d_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_d_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_d_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_d_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_d_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_d_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_d_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_d_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_d_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_d_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_d_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_d_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_d_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_d_l[4][2][1] );

	// MCLE_0_00~MCLE_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_e_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_e_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_e_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_e_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_e_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_e_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_e_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_e_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_e_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_e_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_e_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_e_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_e_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_e_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_e_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_e_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_e_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_e_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_e_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_e_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_e_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_e_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_e_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_e_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_e_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_e_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_e_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_e_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_e_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_e_l[4][2][1] );

	// MCLF_0_00~MCLF_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_f_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_f_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_f_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_f_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_f_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_f_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_f_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_f_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_f_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_f_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_f_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_f_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_f_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_f_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_f_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_f_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_f_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_f_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_f_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_f_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_f_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_f_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_f_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_f_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_f_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_f_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_f_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_f_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_f_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_f_l[4][2][1] );

	// MCLG_0_00~MCLG_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_g_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_g_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_g_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_g_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_g_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_g_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_g_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_g_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_g_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_g_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_g_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_g_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_g_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_g_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_g_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_g_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_g_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_g_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_g_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_g_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_g_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_g_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_g_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_g_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_g_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_g_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_g_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_g_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_g_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_g_l[4][2][1] );

	// MCLH_0_00~MCLH_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_h_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_h_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_h_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_h_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_h_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_h_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_h_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_h_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_h_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_h_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_h_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_h_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_h_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_h_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_h_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_h_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_h_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_h_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_h_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_h_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_h_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_h_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_h_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_h_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_h_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_h_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_h_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_h_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_h_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_h_l[4][2][1] );

	// MCLI_0_00~MCLI_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_i_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_i_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_i_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_i_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_i_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_i_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_i_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_i_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_i_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_i_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_i_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_i_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_i_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_i_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_i_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_i_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_i_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_i_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_i_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_i_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_i_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_i_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_i_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_i_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_i_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_i_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_i_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_i_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_i_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_i_l[4][2][1] );

	// MCLJ_0_00~MCLJ_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_j_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_j_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_j_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_j_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_j_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_j_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_j_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_j_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_j_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_j_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_j_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_j_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_j_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_j_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_j_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_j_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_j_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_j_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_j_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_j_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_j_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_j_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_j_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_j_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_j_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_j_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_j_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_j_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_j_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_j_l[4][2][1] );

	// MCLK_0_00~MCLK_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_k_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_k_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_k_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_k_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_k_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_k_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_k_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_k_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_k_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_k_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_k_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_k_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_k_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_k_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_k_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_k_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_k_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_k_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_k_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_k_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_k_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_k_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_k_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_k_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_k_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_k_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_k_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_k_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_k_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_k_l[4][2][1] );

	// MCLL_0_00~MCLL_4_21
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_l_l[0][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_l_l[0][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_l_l[0][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_l_l[0][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_l_l[0][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_l_l[0][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_l_l[1][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_l_l[1][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_l_l[1][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_l_l[1][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_l_l[1][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_l_l[1][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_l_l[2][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_l_l[2][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_l_l[2][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_l_l[2][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_l_l[2][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_l_l[2][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_l_l[3][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_l_l[3][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_l_l[3][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_l_l[3][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_l_l[3][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_l_l[3][2][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_l_l[4][0][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_l_l[4][0][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_l_l[4][1][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_l_l[4][1][1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_l_l[4][2][0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_l_l[4][2][1] );

	mcyc_ctrl.MCYCBALP.bit.MCYCBALP = r2y_ctrl_multi_axis->cyc_alpha_blend;
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_1, r2y_ctrl_multi_axis->cyc_blend_gain[0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_2, r2y_ctrl_multi_axis->cyc_blend_gain[1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_3, r2y_ctrl_multi_axis->cyc_blend_gain[2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_4, r2y_ctrl_multi_axis->cyc_blend_gain[3] );
	mcyc_ctrl.MCYCBBD.bit.MCYCBBD_1 = r2y_ctrl_multi_axis->cyc_blend_border[0];
	mcyc_ctrl.MCYCBBD.bit.MCYCBBD_2 = r2y_ctrl_multi_axis->cyc_blend_border[1];
	mcyc_ctrl.MCBABALP.bit.MCBABALP = r2y_ctrl_multi_axis->cba_alpha_blend;
	mcyc_ctrl.MCBABOF.bit.MCBABOF_0 = r2y_ctrl_multi_axis->cba_blend_offset[0];
	mcyc_ctrl.MCBABOF.bit.MCBABOF_1 = r2y_ctrl_multi_axis->cba_blend_offset[1];
	mcyc_ctrl.MCBABOF.bit.MCBABOF_2 = r2y_ctrl_multi_axis->cba_blend_offset[2];
	mcyc_ctrl.MCBABOF.bit.MCBABOF_3 = r2y_ctrl_multi_axis->cba_blend_offset[3];
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCBABGA, union io_r2y_mcbabga, MCBABGA_0, r2y_ctrl_multi_axis->cba_blend_gain[0] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCBABGA, union io_r2y_mcbabga, MCBABGA_1, r2y_ctrl_multi_axis->cba_blend_gain[1] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCBABGA, union io_r2y_mcbabga, MCBABGA_2, r2y_ctrl_multi_axis->cba_blend_gain[2] );
	im_r2y_set_reg_signed_a( mcyc_ctrl.MCBABGA, union io_r2y_mcbabga, MCBABGA_3, r2y_ctrl_multi_axis->cba_blend_gain[3] );
	mcyc_ctrl.MCBABBD.bit.MCBABBD_1 = r2y_ctrl_multi_axis->cba_blend_border[0];
	mcyc_ctrl.MCBABBD.bit.MCBABBD_2 = r2y_ctrl_multi_axis->cba_blend_border[1];
	mcyc_ctrl.MCBABBD.bit.MCBABBD_3 = r2y_ctrl_multi_axis->cba_blend_border[2];

	rdma_ctrl.transfer_byte = sizeof( T_IM_R2Y_CTRL_RDMA_MCYC_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&mcyc_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE

ImR2yCtrl5 *im_r2y_ctrl5_new(void)
{
	ImR2yCtrl5* self = k_object_new_with_private(IM_TYPE_R2Y_CTRL5,sizeof(ImR2yCtrl5Private));
	return self;
}
