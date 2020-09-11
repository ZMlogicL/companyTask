/*
 * imr2yctrl4.c
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

#include "imr2yctrl4.h"
#include "imr2yctrlsup.h"
#include "imr2y.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yCtrl4, im_r2y_ctrl4);
#define IM_R2Y_CTRL4_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yCtrl4Private, IM_TYPE_R2Y_CTRL4))

struct _ImR2yCtrl4Private
{
	int a;
};



/*
*DECLS
*/


/*
*IMPL
*/
static void im_r2y_ctrl4_constructor(ImR2yCtrl4 *self)
{
	ImR2yCtrl4Private *priv = IM_R2Y_CTRL4_GET_PRIVATE(self);
}

static void im_r2y_ctrl4_destructor(ImR2yCtrl4 *self)
{
	ImR2yCtrl4Private *priv = IM_R2Y_CTRL4_GET_PRIVATE(self);
}


/*
*PUBLIC
*/
/* Multi Axis Control
 */
INT32 im_r2y_ctrl4_multi_axis(ImR2yCtrl4 *self, UCHAR pipe_no, const T_IM_R2Y_CTRL_MULTI_AXIS* const r2y_ctrl_multi_axis )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifndef CO_R2Y_RDMA_ON
	union io_r2y_mcid1 mcid1;
	union io_r2y_mcid2 mcid2;
	union io_r2y_mcid3 mcid3;
	union io_r2y_mcid4 mcid4;
#endif	// CO_R2Y_RDMA_ON

#ifdef CO_PARAM_CHECK
	if( r2y_ctrl_multi_axis == NULL ) {
		Ddim_Assertion(("im_r2y_ctrl4_multi_axis error. r2y_ctrl_multi_axis = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y_ctrl4_multi_axis error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

#ifdef CO_R2Y_RDMA_ON
	im_r2y_ctrl5_set_rdma_val_multi_axis(im_r2y_ctrl5_new(), pipe_no, r2y_ctrl_multi_axis );
#else	// CO_R2Y_RDMA_ON
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	// MCYC10~MCYC22
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYC, union io_r2y_mcyc, MCYC_0_0, r2y_ctrl_multi_axis->cyc_coeff[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYC, union io_r2y_mcyc, MCYC_0_1, r2y_ctrl_multi_axis->cyc_coeff[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYC, union io_r2y_mcyc, MCYC_0_2, r2y_ctrl_multi_axis->cyc_coeff[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYC, union io_r2y_mcyc, MCYC_1_0, r2y_ctrl_multi_axis->cyc_coeff[3] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYC, union io_r2y_mcyc, MCYC_1_1, r2y_ctrl_multi_axis->cyc_coeff[4] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYC, union io_r2y_mcyc, MCYC_1_2, r2y_ctrl_multi_axis->cyc_coeff[5] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYC, union io_r2y_mcyc, MCYC_2_0, r2y_ctrl_multi_axis->cyc_coeff[6] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYC, union io_r2y_mcyc, MCYC_2_1, r2y_ctrl_multi_axis->cyc_coeff[7] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYC, union io_r2y_mcyc, MCYC_2_2, r2y_ctrl_multi_axis->cyc_coeff[8] );

	// MCB1A~MCB4D
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB1AB.bit.MCB1A = r2y_ctrl_multi_axis->boundary[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB1AB.bit.MCB1B = r2y_ctrl_multi_axis->boundary[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB1CD.bit.MCB1C = r2y_ctrl_multi_axis->boundary[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB1CD.bit.MCB1D = r2y_ctrl_multi_axis->boundary[3];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB2AB.bit.MCB2A = r2y_ctrl_multi_axis->boundary[4];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB2AB.bit.MCB2B = r2y_ctrl_multi_axis->boundary[5];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB2CD.bit.MCB2C = r2y_ctrl_multi_axis->boundary[6];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB2CD.bit.MCB2D = r2y_ctrl_multi_axis->boundary[7];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB3AB.bit.MCB3A = r2y_ctrl_multi_axis->boundary[8];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB3AB.bit.MCB3B = r2y_ctrl_multi_axis->boundary[9];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB3CD.bit.MCB3C = r2y_ctrl_multi_axis->boundary[10];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB3CD.bit.MCB3D = r2y_ctrl_multi_axis->boundary[11];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB4AB.bit.MCB4A = r2y_ctrl_multi_axis->boundary[12];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB4AB.bit.MCB4B = r2y_ctrl_multi_axis->boundary[13];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB4CD.bit.MCB4C = r2y_ctrl_multi_axis->boundary[14];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCB4CD.bit.MCB4D = r2y_ctrl_multi_axis->boundary[15];

	// MCID1~MCID4
	mcid1.word = 0UL;
	mcid2.word = 0UL;
	mcid3.word = 0UL;
	mcid4.word = 0UL;
	mcid1.bit.MCID1A = r2y_ctrl_multi_axis->area_index[0][0];
	mcid1.bit.MCID1B = r2y_ctrl_multi_axis->area_index[0][1];
	mcid1.bit.MCID1C = r2y_ctrl_multi_axis->area_index[0][2];
	mcid1.bit.MCID1D = r2y_ctrl_multi_axis->area_index[0][3];
	mcid1.bit.MCID1E = r2y_ctrl_multi_axis->area_index[0][4];
	mcid2.bit.MCID2A = r2y_ctrl_multi_axis->area_index[1][0];
	mcid2.bit.MCID2B = r2y_ctrl_multi_axis->area_index[1][1];
	mcid2.bit.MCID2C = r2y_ctrl_multi_axis->area_index[1][2];
	mcid2.bit.MCID2D = r2y_ctrl_multi_axis->area_index[1][3];
	mcid2.bit.MCID2E = r2y_ctrl_multi_axis->area_index[1][4];
	mcid3.bit.MCID3A = r2y_ctrl_multi_axis->area_index[2][0];
	mcid3.bit.MCID3B = r2y_ctrl_multi_axis->area_index[2][1];
	mcid3.bit.MCID3C = r2y_ctrl_multi_axis->area_index[2][2];
	mcid3.bit.MCID3D = r2y_ctrl_multi_axis->area_index[2][3];
	mcid3.bit.MCID3E = r2y_ctrl_multi_axis->area_index[2][4];
	mcid4.bit.MCID4A = r2y_ctrl_multi_axis->area_index[3][0];
	mcid4.bit.MCID4B = r2y_ctrl_multi_axis->area_index[3][1];
	mcid4.bit.MCID4C = r2y_ctrl_multi_axis->area_index[3][2];
	mcid4.bit.MCID4D = r2y_ctrl_multi_axis->area_index[3][3];
	mcid4.bit.MCID4E = r2y_ctrl_multi_axis->area_index[3][4];

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCID1.word = mcid1.word;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCID2.word = mcid2.word;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCID3.word = mcid3.word;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCID4.word = mcid4.word;

	//TODO 抽出
	im_r2y_ctrl_sup_multi_axis(im_r2y_ctrl_sup_new(), pipe_no, r2y_ctrl_multi_axis);

	// MCKF_0_00~MCKF_4_22
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_f_k[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_f_k[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_f_k[0][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_f_k[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_f_k[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_f_k[0][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_f_k[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_f_k[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_f_k[0][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_f_k[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_f_k[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_f_k[1][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_f_k[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_f_k[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_f_k[1][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_f_k[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_f_k[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_f_k[1][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_f_k[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_f_k[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_f_k[2][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_f_k[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_f_k[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_f_k[2][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_f_k[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_f_k[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_f_k[2][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_f_k[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_f_k[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_f_k[3][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_f_k[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_f_k[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_f_k[3][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_f_k[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_f_k[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_f_k[3][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_f_k[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_f_k[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_f_k[4][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_f_k[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_f_k[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_f_k[4][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_f_k[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_f_k[4][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKF.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_f_k[4][2][2] );

	// MCKG_0_00~MCKG_4_22
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_g_k[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_g_k[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_g_k[0][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_g_k[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_g_k[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_g_k[0][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_g_k[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_g_k[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_g_k[0][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_g_k[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_g_k[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_g_k[1][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_g_k[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_g_k[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_g_k[1][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_g_k[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_g_k[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_g_k[1][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_g_k[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_g_k[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_g_k[2][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_g_k[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_g_k[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_g_k[2][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_g_k[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_g_k[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_g_k[2][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_g_k[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_g_k[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_g_k[3][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_g_k[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_g_k[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_g_k[3][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_g_k[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_g_k[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_g_k[3][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_g_k[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_g_k[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_g_k[4][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_g_k[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_g_k[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_g_k[4][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_g_k[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_g_k[4][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKG.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_g_k[4][2][2] );

	// MCKH_0_00~MCKH_4_22
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_h_k[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_h_k[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_h_k[0][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_h_k[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_h_k[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_h_k[0][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_h_k[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_h_k[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_h_k[0][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_h_k[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_h_k[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_h_k[1][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_h_k[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_h_k[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_h_k[1][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_h_k[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_h_k[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_h_k[1][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_h_k[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_h_k[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_h_k[2][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_h_k[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_h_k[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_h_k[2][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_h_k[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_h_k[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_h_k[2][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_h_k[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_h_k[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_h_k[3][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_h_k[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_h_k[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_h_k[3][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_h_k[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_h_k[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_h_k[3][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_h_k[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_h_k[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_h_k[4][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_h_k[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_h_k[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_h_k[4][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_h_k[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_h_k[4][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKH.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_h_k[4][2][2] );

	// MCKI_0_00~MCKI_4_22
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_i_k[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_i_k[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_i_k[0][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_i_k[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_i_k[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_i_k[0][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_i_k[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_i_k[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_i_k[0][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_i_k[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_i_k[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_i_k[1][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_i_k[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_i_k[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_i_k[1][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_i_k[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_i_k[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_i_k[1][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_i_k[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_i_k[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_i_k[2][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_i_k[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_i_k[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_i_k[2][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_i_k[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_i_k[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_i_k[2][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_i_k[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_i_k[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_i_k[3][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_i_k[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_i_k[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_i_k[3][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_i_k[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_i_k[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_i_k[3][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_i_k[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_i_k[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_i_k[4][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_i_k[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_i_k[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_i_k[4][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_i_k[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_i_k[4][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKI.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_i_k[4][2][2] );

	// MCKJ_0_00~MCKJ_4_22
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_j_k[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_j_k[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_j_k[0][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_j_k[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_j_k[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_j_k[0][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_j_k[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_j_k[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_j_k[0][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_j_k[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_j_k[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_j_k[1][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_j_k[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_j_k[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_j_k[1][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_j_k[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_j_k[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_j_k[1][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_j_k[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_j_k[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_j_k[2][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_j_k[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_j_k[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_j_k[2][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_j_k[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_j_k[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_j_k[2][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_j_k[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_j_k[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_j_k[3][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_j_k[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_j_k[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_j_k[3][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_j_k[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_j_k[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_j_k[3][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_j_k[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_j_k[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_j_k[4][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_j_k[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_j_k[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_j_k[4][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_j_k[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_j_k[4][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKJ.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_j_k[4][2][2] );

	// MCKK_0_00~MCKK_4_22
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_k_k[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_k_k[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_k_k[0][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_k_k[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_k_k[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_k_k[0][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_k_k[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_k_k[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_k_k[0][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_k_k[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_k_k[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_k_k[1][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_k_k[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_k_k[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_k_k[1][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_k_k[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_k_k[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_k_k[1][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_k_k[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_k_k[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_k_k[2][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_k_k[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_k_k[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_k_k[2][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_k_k[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_k_k[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_k_k[2][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_k_k[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_k_k[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_k_k[3][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_k_k[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_k_k[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_k_k[3][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_k_k[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_k_k[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_k_k[3][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_k_k[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_k_k[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_k_k[4][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_k_k[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_k_k[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_k_k[4][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_k_k[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_k_k[4][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKK.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_k_k[4][2][2] );

	// MCKL_0_00~MCKL_4_22
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_0, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_l_k[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_0, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_l_k[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_0, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_l_k[0][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_0, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_l_k[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_0, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_l_k[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_0, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_l_k[0][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_0, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_l_k[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_0, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_l_k[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_0, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_l_k[0][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_1, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_l_k[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_1, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_l_k[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_1, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_l_k[1][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_1, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_l_k[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_1, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_l_k[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_1, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_l_k[1][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_1, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_l_k[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_1, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_l_k[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_1, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_l_k[1][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_2, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_l_k[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_2, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_l_k[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_2, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_l_k[2][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_2, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_l_k[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_2, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_l_k[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_2, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_l_k[2][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_2, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_l_k[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_2, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_l_k[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_2, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_l_k[2][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_3, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_l_k[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_3, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_l_k[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_3, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_l_k[3][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_3, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_l_k[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_3, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_l_k[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_3, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_l_k[3][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_3, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_l_k[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_3, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_l_k[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_3, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_l_k[3][2][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_4, union io_r2y_mck_x, MCK_0_0, r2y_ctrl_multi_axis->area_l_k[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_4, union io_r2y_mck_x, MCK_0_1, r2y_ctrl_multi_axis->area_l_k[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_4, union io_r2y_mck_x, MCK_0_2, r2y_ctrl_multi_axis->area_l_k[4][0][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_4, union io_r2y_mck_x, MCK_1_0, r2y_ctrl_multi_axis->area_l_k[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_4, union io_r2y_mck_x, MCK_1_1, r2y_ctrl_multi_axis->area_l_k[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_4, union io_r2y_mck_x, MCK_1_2, r2y_ctrl_multi_axis->area_l_k[4][1][2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_4, union io_r2y_mck_x, MCK_2_0, r2y_ctrl_multi_axis->area_l_k[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_4, union io_r2y_mck_x, MCK_2_1, r2y_ctrl_multi_axis->area_l_k[4][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCKL.MCK_4, union io_r2y_mck_x, MCK_2_2, r2y_ctrl_multi_axis->area_l_k[4][2][2] );

	// MCLA_0_00~MCLA_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_a_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_a_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_a_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_a_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_a_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_a_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_a_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_a_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_a_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_a_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_a_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_a_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_a_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_a_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_a_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_a_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_a_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_a_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_a_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_a_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_a_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_a_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_a_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_a_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_a_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_a_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_a_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_a_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_a_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLA.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_a_l[4][2][1] );

	// MCLB_0_00~MCLB_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_b_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_b_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_b_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_b_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_b_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_b_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_b_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_b_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_b_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_b_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_b_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_b_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_b_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_b_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_b_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_b_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_b_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_b_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_b_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_b_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_b_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_b_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_b_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_b_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_b_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_b_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_b_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_b_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_b_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLB.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_b_l[4][2][1] );

	// MCLC_0_00~MCLC_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_c_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_c_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_c_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_c_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_c_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_c_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_c_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_c_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_c_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_c_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_c_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_c_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_c_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_c_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_c_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_c_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_c_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_c_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_c_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_c_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_c_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_c_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_c_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_c_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_c_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_c_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_c_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_c_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_c_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLC.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_c_l[4][2][1] );

	// MCLD_0_00~MCLD_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_d_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_d_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_d_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_d_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_d_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_d_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_d_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_d_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_d_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_d_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_d_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_d_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_d_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_d_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_d_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_d_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_d_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_d_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_d_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_d_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_d_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_d_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_d_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_d_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_d_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_d_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_d_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_d_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_d_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLD.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_d_l[4][2][1] );

	// MCLE_0_00~MCLE_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_e_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_e_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_e_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_e_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_e_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_e_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_e_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_e_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_e_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_e_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_e_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_e_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_e_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_e_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_e_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_e_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_e_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_e_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_e_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_e_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_e_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_e_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_e_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_e_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_e_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_e_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_e_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_e_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_e_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLE.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_e_l[4][2][1] );

	// MCLF_0_00~MCLF_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_f_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_f_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_f_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_f_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_f_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_f_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_f_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_f_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_f_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_f_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_f_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_f_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_f_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_f_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_f_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_f_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_f_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_f_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_f_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_f_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_f_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_f_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_f_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_f_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_f_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_f_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_f_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_f_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_f_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLF.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_f_l[4][2][1] );

	// MCLG_0_00~MCLG_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_g_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_g_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_g_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_g_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_g_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_g_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_g_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_g_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_g_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_g_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_g_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_g_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_g_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_g_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_g_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_g_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_g_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_g_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_g_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_g_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_g_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_g_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_g_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_g_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_g_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_g_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_g_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_g_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_g_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLG.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_g_l[4][2][1] );

	// MCLH_0_00~MCLH_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_h_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_h_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_h_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_h_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_h_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_h_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_h_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_h_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_h_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_h_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_h_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_h_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_h_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_h_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_h_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_h_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_h_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_h_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_h_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_h_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_h_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_h_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_h_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_h_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_h_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_h_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_h_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_h_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_h_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLH.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_h_l[4][2][1] );

	// MCLI_0_00~MCLI_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_i_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_i_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_i_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_i_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_i_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_i_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_i_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_i_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_i_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_i_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_i_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_i_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_i_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_i_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_i_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_i_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_i_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_i_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_i_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_i_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_i_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_i_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_i_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_i_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_i_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_i_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_i_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_i_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_i_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLI.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_i_l[4][2][1] );

	// MCLJ_0_00~MCLJ_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_j_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_j_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_j_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_j_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_j_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_j_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_j_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_j_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_j_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_j_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_j_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_j_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_j_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_j_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_j_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_j_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_j_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_j_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_j_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_j_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_j_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_j_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_j_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_j_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_j_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_j_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_j_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_j_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_j_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLJ.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_j_l[4][2][1] );

	// MCLK_0_00~MCLK_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_k_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_k_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_k_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_k_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_k_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_k_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_k_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_k_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_k_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_k_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_k_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_k_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_k_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_k_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_k_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_k_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_k_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_k_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_k_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_k_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_k_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_k_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_k_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_k_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_k_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_k_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_k_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_k_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_k_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLK.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_k_l[4][2][1] );

	// MCLL_0_00~MCLL_4_21
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_0, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_l_l[0][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_0, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_l_l[0][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_0, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_l_l[0][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_0, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_l_l[0][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_0, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_l_l[0][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_0, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_l_l[0][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_1, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_l_l[1][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_1, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_l_l[1][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_1, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_l_l[1][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_1, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_l_l[1][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_1, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_l_l[1][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_1, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_l_l[1][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_2, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_l_l[2][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_2, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_l_l[2][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_2, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_l_l[2][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_2, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_l_l[2][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_2, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_l_l[2][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_2, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_l_l[2][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_3, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_l_l[3][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_3, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_l_l[3][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_3, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_l_l[3][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_3, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_l_l[3][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_3, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_l_l[3][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_3, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_l_l[3][2][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_4, union io_r2y_mcl_x, MCL_0_0, r2y_ctrl_multi_axis->area_l_l[4][0][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_4, union io_r2y_mcl_x, MCL_0_1, r2y_ctrl_multi_axis->area_l_l[4][0][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_4, union io_r2y_mcl_x, MCL_1_0, r2y_ctrl_multi_axis->area_l_l[4][1][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_4, union io_r2y_mcl_x, MCL_1_1, r2y_ctrl_multi_axis->area_l_l[4][1][1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_4, union io_r2y_mcl_x, MCL_2_0, r2y_ctrl_multi_axis->area_l_l[4][2][0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCLL.MCL_4, union io_r2y_mcl_x, MCL_2_1, r2y_ctrl_multi_axis->area_l_l[4][2][1] );

	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYCBALP.bit.MCYCBALP = r2y_ctrl_multi_axis->cyc_alpha_blend;
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_1, r2y_ctrl_multi_axis->cyc_blend_gain[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_2, r2y_ctrl_multi_axis->cyc_blend_gain[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_3, r2y_ctrl_multi_axis->cyc_blend_gain[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYCBGA, union io_r2y_mcycbga, MCYCBGA_4, r2y_ctrl_multi_axis->cyc_blend_gain[3] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYCBBD.bit.MCYCBBD_1 = r2y_ctrl_multi_axis->cyc_blend_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYCBBD.bit.MCYCBBD_2 = r2y_ctrl_multi_axis->cyc_blend_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYCBBD.bit.MCYCBBD_3 = r2y_ctrl_multi_axis->cyc_blend_border[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCYCBBD.bit.MCYCBBD_4 = r2y_ctrl_multi_axis->cyc_blend_border[3];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABALP.bit.MCBABALP = r2y_ctrl_multi_axis->cba_alpha_blend;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABOF.bit.MCBABOF_0 = r2y_ctrl_multi_axis->cba_blend_offset[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABOF.bit.MCBABOF_1 = r2y_ctrl_multi_axis->cba_blend_offset[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABOF.bit.MCBABOF_2 = r2y_ctrl_multi_axis->cba_blend_offset[2];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABOF.bit.MCBABOF_3 = r2y_ctrl_multi_axis->cba_blend_offset[3];
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABGA, union io_r2y_mcbabga, MCBABGA_0, r2y_ctrl_multi_axis->cba_blend_gain[0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABGA, union io_r2y_mcbabga, MCBABGA_1, r2y_ctrl_multi_axis->cba_blend_gain[1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABGA, union io_r2y_mcbabga, MCBABGA_2, r2y_ctrl_multi_axis->cba_blend_gain[2] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABGA, union io_r2y_mcbabga, MCBABGA_3, r2y_ctrl_multi_axis->cba_blend_gain[3] );
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABBD.bit.MCBABBD_1 = r2y_ctrl_multi_axis->cba_blend_border[0];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABBD.bit.MCBABBD_2 = r2y_ctrl_multi_axis->cba_blend_border[1];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->F_R2Y.MCC.MCBABBD.bit.MCBABBD_3 = r2y_ctrl_multi_axis->cba_blend_border[2];
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
#endif	// CO_R2Y_RDMA_ON

	return D_DDIM_OK;
}


ImR2yCtrl4 *im_r2y_ctrl4_new(void)
{
	ImR2yCtrl4* self = k_object_new_with_private(IM_TYPE_R2Y_CTRL4,sizeof(ImR2yCtrl4Private));
	return self;
}
