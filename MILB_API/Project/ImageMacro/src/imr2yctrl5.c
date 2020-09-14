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
void im_r2y_ctrl5_set_rdma_val_multi_axis(ImR2yCtrl5 *self, kuint16 pipeNo, const CtrlMultiAxis* const r2y_ctrl_multi_axis )
{
	CtrlRdmaMcycVal mcyc_ctrl;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (kulong)&(gIM_R2Y_MCYC_Addr[pipeNo]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	im_r2y_ctrl_sup_set_rdma_val_multi_axis(&mcyc_ctrl, pipeNo, r2y_ctrl_multi_axis);
	// MCKD_0_00~MCKD_4_22
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaDK[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaDK[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaDK[0][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaDK[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaDK[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaDK[0][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaDK[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaDK[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaDK[0][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaDK[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaDK[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaDK[1][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaDK[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaDK[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaDK[1][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaDK[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaDK[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaDK[1][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaDK[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaDK[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaDK[2][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaDK[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaDK[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaDK[2][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaDK[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaDK[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaDK[2][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaDK[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaDK[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaDK[3][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaDK[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaDK[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaDK[3][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaDK[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaDK[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaDK[3][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaDK[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaDK[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaDK[4][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaDK[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaDK[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaDK[4][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaDK[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaDK[4][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKD.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaDK[4][2][2] );

	// MCKE_0_00~MCKE_4_22
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaEK[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaEK[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaEK[0][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaEK[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaEK[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaEK[0][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaEK[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaEK[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaEK[0][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaEK[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaEK[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaEK[1][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaEK[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaEK[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaEK[1][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaEK[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaEK[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaEK[1][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaEK[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaEK[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaEK[2][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaEK[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaEK[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaEK[2][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaEK[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaEK[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaEK[2][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaEK[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaEK[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaEK[3][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaEK[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaEK[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaEK[3][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaEK[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaEK[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaEK[3][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaEK[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaEK[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaEK[4][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaEK[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaEK[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaEK[4][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaEK[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaEK[4][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKE.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaEK[4][2][2] );

	// MCKF_0_00~MCKF_4_22
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaFK[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaFK[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaFK[0][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaFK[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaFK[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaFK[0][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaFK[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaFK[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaFK[0][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaFK[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaFK[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaFK[1][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaFK[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaFK[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaFK[1][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaFK[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaFK[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaFK[1][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaFK[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaFK[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaFK[2][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaFK[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaFK[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaFK[2][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaFK[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaFK[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaFK[2][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaFK[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaFK[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaFK[3][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaFK[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaFK[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaFK[3][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaFK[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaFK[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaFK[3][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaFK[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaFK[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaFK[4][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaFK[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaFK[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaFK[4][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaFK[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaFK[4][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKF.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaFK[4][2][2] );

	// MCKG_0_00~MCKG_4_22
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaGK[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaGK[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaGK[0][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaGK[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaGK[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaGK[0][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaGK[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaGK[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaGK[0][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaGK[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaGK[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaGK[1][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaGK[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaGK[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaGK[1][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaGK[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaGK[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaGK[1][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaGK[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaGK[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaGK[2][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaGK[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaGK[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaGK[2][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaGK[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaGK[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaGK[2][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaGK[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaGK[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaGK[3][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaGK[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaGK[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaGK[3][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaGK[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaGK[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaGK[3][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaGK[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaGK[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaGK[4][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaGK[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaGK[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaGK[4][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaGK[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaGK[4][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKG.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaGK[4][2][2] );

	// MCKH_0_00~MCKH_4_22
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaHK[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaHK[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaHK[0][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaHK[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaHK[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaHK[0][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaHK[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaHK[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaHK[0][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaHK[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaHK[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaHK[1][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaHK[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaHK[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaHK[1][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaHK[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaHK[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaHK[1][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaHK[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaHK[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaHK[2][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaHK[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaHK[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaHK[2][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaHK[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaHK[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaHK[2][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaHK[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaHK[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaHK[3][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaHK[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaHK[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaHK[3][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaHK[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaHK[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaHK[3][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaHK[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaHK[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaHK[4][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaHK[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaHK[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaHK[4][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaHK[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaHK[4][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKH.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaHK[4][2][2] );

	// MCKI_0_00~MCKI_4_22
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaIK[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaIK[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaIK[0][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaIK[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaIK[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaIK[0][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaIK[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaIK[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaIK[0][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaIK[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaIK[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaIK[1][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaIK[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaIK[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaIK[1][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaIK[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaIK[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaIK[1][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaIK[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaIK[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaIK[2][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaIK[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaIK[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaIK[2][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaIK[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaIK[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaIK[2][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaIK[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaIK[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaIK[3][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaIK[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaIK[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaIK[3][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaIK[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaIK[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaIK[3][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaIK[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaIK[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaIK[4][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaIK[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaIK[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaIK[4][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaIK[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaIK[4][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKI.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaIK[4][2][2] );

	// MCKJ_0_00~MCKJ_4_22
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaJK[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaJK[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaJK[0][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaJK[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaJK[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaJK[0][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaJK[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaJK[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaJK[0][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaJK[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaJK[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaJK[1][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaJK[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaJK[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaJK[1][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaJK[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaJK[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaJK[1][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaJK[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaJK[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaJK[2][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaJK[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaJK[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaJK[2][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaJK[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaJK[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaJK[2][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaJK[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaJK[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaJK[3][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaJK[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaJK[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaJK[3][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaJK[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaJK[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaJK[3][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaJK[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaJK[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaJK[4][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaJK[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaJK[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaJK[4][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaJK[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaJK[4][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKJ.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaJK[4][2][2] );

	// MCKK_0_00~MCKK_4_22
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaKK[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaKK[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaKK[0][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaKK[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaKK[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaKK[0][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaKK[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaKK[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaKK[0][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaKK[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaKK[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaKK[1][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaKK[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaKK[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaKK[1][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaKK[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaKK[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaKK[1][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaKK[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaKK[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaKK[2][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaKK[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaKK[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaKK[2][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaKK[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaKK[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaKK[2][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaKK[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaKK[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaKK[3][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaKK[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaKK[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaKK[3][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaKK[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaKK[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaKK[3][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaKK[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaKK[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaKK[4][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaKK[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaKK[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaKK[4][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaKK[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaKK[4][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKK.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaKK[4][2][2] );

	// MCKL_0_00~MCKL_4_22
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaLK[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaLK[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaLK[0][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaLK[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaLK[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaLK[0][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaLK[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaLK[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaLK[0][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaLK[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaLK[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaLK[1][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaLK[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaLK[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaLK[1][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaLK[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaLK[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaLK[1][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaLK[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaLK[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaLK[2][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaLK[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaLK[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaLK[2][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaLK[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaLK[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaLK[2][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaLK[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaLK[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaLK[3][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaLK[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaLK[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaLK[3][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaLK[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaLK[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaLK[3][2][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->areaLK[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->areaLK[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->areaLK[4][0][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->areaLK[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->areaLK[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->areaLK[4][1][2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->areaLK[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->areaLK[4][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCKL.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->areaLK[4][2][2] );

	// MCLA_0_00~MCLA_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaAL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaAL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaAL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaAL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaAL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaAL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaAL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaAL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaAL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaAL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaAL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaAL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaAL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaAL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaAL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaAL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaAL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaAL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaAL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaAL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaAL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaAL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaAL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaAL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaAL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaAL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaAL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaAL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaAL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLA.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaAL[4][2][1] );

	// MCLB_0_00~MCLB_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaBL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaBL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaBL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaBL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaBL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaBL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaBL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaBL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaBL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaBL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaBL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaBL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaBL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaBL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaBL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaBL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaBL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaBL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaBL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaBL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaBL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaBL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaBL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaBL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaBL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaBL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaBL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaBL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaBL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLB.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaBL[4][2][1] );

	// MCLC_0_00~MCLC_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaCL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaCL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaCL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaCL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaCL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaCL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaCL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaCL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaCL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaCL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaCL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaCL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaCL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaCL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaCL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaCL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaCL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaCL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaCL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaCL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaCL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaCL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaCL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaCL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaCL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaCL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaCL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaCL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaCL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLC.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaCL[4][2][1] );

	// MCLD_0_00~MCLD_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaDL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaDL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaDL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaDL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaDL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaDL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaDL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaDL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaDL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaDL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaDL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaDL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaDL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaDL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaDL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaDL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaDL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaDL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaDL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaDL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaDL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaDL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaDL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaDL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaDL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaDL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaDL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaDL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaDL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLD.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaDL[4][2][1] );

	// MCLE_0_00~MCLE_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaEL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaEL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaEL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaEL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaEL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaEL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaEL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaEL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaEL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaEL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaEL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaEL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaEL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaEL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaEL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaEL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaEL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaEL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaEL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaEL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaEL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaEL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaEL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaEL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaEL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaEL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaEL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaEL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaEL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLE.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaEL[4][2][1] );

	// MCLF_0_00~MCLF_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaFL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaFL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaFL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaFL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaFL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaFL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaFL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaFL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaFL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaFL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaFL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaFL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaFL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaFL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaFL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaFL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaFL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaFL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaFL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaFL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaFL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaFL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaFL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaFL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaFL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaFL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaFL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaFL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaFL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLF.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaFL[4][2][1] );

	// MCLG_0_00~MCLG_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaGL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaGL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaGL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaGL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaGL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaGL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaGL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaGL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaGL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaGL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaGL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaGL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaGL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaGL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaGL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaGL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaGL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaGL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaGL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaGL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaGL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaGL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaGL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaGL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaGL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaGL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaGL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaGL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaGL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLG.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaGL[4][2][1] );

	// MCLH_0_00~MCLH_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaHL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaHL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaHL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaHL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaHL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaHL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaHL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaHL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaHL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaHL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaHL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaHL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaHL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaHL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaHL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaHL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaHL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaHL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaHL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaHL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaHL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaHL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaHL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaHL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaHL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaHL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaHL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaHL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaHL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLH.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaHL[4][2][1] );

	// MCLI_0_00~MCLI_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaIL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaIL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaIL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaIL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaIL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaIL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaIL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaIL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaIL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaIL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaIL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaIL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaIL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaIL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaIL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaIL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaIL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaIL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaIL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaIL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaIL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaIL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaIL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaIL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaIL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaIL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaIL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaIL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaIL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLI.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaIL[4][2][1] );

	// MCLJ_0_00~MCLJ_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaJL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaJL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaJL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaJL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaJL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaJL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaJL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaJL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaJL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaJL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaJL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaJL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaJL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaJL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaJL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaJL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaJL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaJL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaJL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaJL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaJL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaJL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaJL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaJL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaJL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaJL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaJL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaJL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaJL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaJL[4][2][1] );

	// MCLK_0_00~MCLK_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaKL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaKL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaKL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaKL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaKL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaKL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaKL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaKL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaKL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaKL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaKL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaKL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaKL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaKL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaKL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaKL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaKL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaKL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaKL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaKL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaKL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaKL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaKL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaKL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaKL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaKL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaKL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaKL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaKL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLK.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaKL[4][2][1] );

	// MCLL_0_00~MCLL_4_21
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaLL[0][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaLL[0][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaLL[0][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaLL[0][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaLL[0][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaLL[0][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaLL[1][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaLL[1][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaLL[1][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaLL[1][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaLL[1][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaLL[1][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaLL[2][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaLL[2][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaLL[2][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaLL[2][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaLL[2][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaLL[2][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaLL[3][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaLL[3][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaLL[3][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaLL[3][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaLL[3][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaLL[3][2][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->areaLL[4][0][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->areaLL[4][0][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->areaLL[4][1][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->areaLL[4][1][1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->areaLL[4][2][0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCLL.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->areaLL[4][2][1] );

	mcyc_ctrl.MCYCBALP.bit.MCYCBALP = r2y_ctrl_multi_axis->cycAlphaBlend;
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_1, r2y_ctrl_multi_axis->cycBlendGain[0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_2, r2y_ctrl_multi_axis->cycBlendGain[1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_3, r2y_ctrl_multi_axis->cycBlendGain[2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_4, r2y_ctrl_multi_axis->cycBlendGain[3] );
	mcyc_ctrl.MCYCBBD.bit.MCYCBBD_1 = r2y_ctrl_multi_axis->cycBlendBorder[0];
	mcyc_ctrl.MCYCBBD.bit.MCYCBBD_2 = r2y_ctrl_multi_axis->cycBlendBorder[1];
	mcyc_ctrl.MCBABALP.bit.MCBABALP = r2y_ctrl_multi_axis->cbaAlphaBlend;
	mcyc_ctrl.MCBABOF.bit.MCBABOF_0 = r2y_ctrl_multi_axis->cbaBlendOffset[0];
	mcyc_ctrl.MCBABOF.bit.MCBABOF_1 = r2y_ctrl_multi_axis->cbaBlendOffset[1];
	mcyc_ctrl.MCBABOF.bit.MCBABOF_2 = r2y_ctrl_multi_axis->cbaBlendOffset[2];
	mcyc_ctrl.MCBABOF.bit.MCBABOF_3 = r2y_ctrl_multi_axis->cbaBlendOffset[3];
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCBABGA, union io_r2y_mcbabga, MCBABGA_0, r2y_ctrl_multi_axis->cbaBlendGain[0] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCBABGA, union io_r2y_mcbabga, MCBABGA_1, r2y_ctrl_multi_axis->cbaBlendGain[1] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCBABGA, union io_r2y_mcbabga, MCBABGA_2, r2y_ctrl_multi_axis->cbaBlendGain[2] );
	imR2yUtils_SET_REG_SIGNED_A( mcyc_ctrl.MCBABGA, union io_r2y_mcbabga, MCBABGA_3, r2y_ctrl_multi_axis->cbaBlendGain[3] );
	mcyc_ctrl.MCBABBD.bit.MCBABBD_1 = r2y_ctrl_multi_axis->cbaBlendBorder[0];
	mcyc_ctrl.MCBABBD.bit.MCBABBD_2 = r2y_ctrl_multi_axis->cbaBlendBorder[1];
	mcyc_ctrl.MCBABBD.bit.MCBABBD_3 = r2y_ctrl_multi_axis->cbaBlendBorder[2];

	rdma_ctrl.transfer_byte = sizeof( CtrlRdmaMcycVal );
	rdma_ctrl.reg_data_top_addr = (kulong)&mcyc_ctrl;
	im_r2y_utils_start_rdma(im_r2y_utils_get(), &rdma_ctrl );
}
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE

ImR2yCtrl5 *im_r2y_ctrl5_new(void)
{
	ImR2yCtrl5* self = k_object_new_with_private(IM_TYPE_R2Y_CTRL5,sizeof(ImR2yCtrl5Private));
	return self;
}
