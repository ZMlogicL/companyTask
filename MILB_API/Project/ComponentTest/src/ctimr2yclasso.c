/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-02
 *@author : THH
 *@brief : CtImR2yClasso
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */

#include "ctimr2yclasso.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yClasso, ct_im_r2y_classo)
#define CT_IM_R2Y_CLASSO_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yClassoPrivate, CT_TYPE_IM_R2Y_CLASSO))

struct _CtImR2yClassoPrivate
{

};

static void ct_im_r2y_classo_constructor(CtImR2yClasso *self)
{
	CtImR2yClassoPrivate *priv = CT_IM_R2Y_CLASSO_GET_PRIVATE(self);
}

static void ct_im_r2y_classo_destructor(CtImR2yClasso *self)
{
	CtImR2yClassoPrivate *priv = CT_IM_R2Y_CLASSO_GET_PRIVATE(self);
}

void ct_im_r2y_classo_1_54_temp3()
{
#ifdef CO_MSG_PRINT_ON
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[0][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_0.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[0][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_0.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[0][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_0.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_0.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_0.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_0.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_0.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_0.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_0.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[1][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_1.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[1][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_1.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[1][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_1.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_1.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_1.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_1.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_1.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_1.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_1.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[2][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_2.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[2][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_2.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[2][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_2.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_2.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_2.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_2.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_2.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_2.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_2.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[3][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_3.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[3][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_3.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[3][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_3.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_3.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_3.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_3.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_3.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_3.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_3.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[4][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_4.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[4][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_4.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI[4][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_4.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_4.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_4.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_4.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_4.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_4.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLI.MCL_4.bit.MCL_2_1 ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[0][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_0.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[0][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_0.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[0][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_0.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_0.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_0.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_0.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_0.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_0.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_0.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[1][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_1.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[1][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_1.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[1][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_1.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_1.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_1.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_1.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_1.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_1.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_1.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[2][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_2.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[2][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_2.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[2][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_2.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_2.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_2.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_2.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_2.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_2.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_2.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[3][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_3.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[3][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_3.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[3][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_3.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_3.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_3.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_3.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_3.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_3.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_3.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[4][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_4.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[4][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_4.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ[4][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_4.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_4.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_4.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_4.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_4.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_4.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLJ.MCL_4.bit.MCL_2_1 ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[0][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_0.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[0][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_0.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[0][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_0.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_0.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_0.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_0.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_0.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_0.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_0.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[1][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_1.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[1][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_1.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[1][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_1.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_1.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_1.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_1.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_1.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_1.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_1.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[2][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_2.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[2][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_2.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[2][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_2.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_2.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_2.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_2.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_2.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_2.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_2.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[3][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_3.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[3][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_3.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[3][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_3.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_3.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_3.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_3.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_3.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_3.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_3.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[4][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_4.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[4][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_4.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK[4][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_4.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_4.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_4.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_4.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_4.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_4.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLK.MCL_4.bit.MCL_2_1 ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[0][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_0.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[0][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_0.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[0][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_0.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_0.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_0.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_0.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_0.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_0.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_0.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[1][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_1.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[1][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_1.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[1][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_1.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_1.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_1.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_1.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_1.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_1.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_1.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[2][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_2.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[2][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_2.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[2][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_2.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_2.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_2.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_2.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_2.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_2.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_2.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[3][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_3.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[3][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_3.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[3][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_3.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_3.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_3.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_3.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_3.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_3.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_3.bit.MCL_2_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[4][0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_4.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[4][1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_4.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL[4][2] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_4.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_0_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_4.bit.MCL_0_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_0_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_4.bit.MCL_0_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_1_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_4.bit.MCL_1_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_1_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_4.bit.MCL_1_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_2_0 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_4.bit.MCL_2_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_2_1 = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCLL.MCL_4.bit.MCL_2_1 ));
	Ddim_Print(( "\n" ));

	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCYCBALP   = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCYCBALP.bit.MCYCBALP ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCYCBGA_1  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCYCBGA.bit.MCYCBGA_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCYCBGA_2  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCYCBGA.bit.MCYCBGA_2 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCYCBGA_3  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCYCBGA.bit.MCYCBGA_3 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCYCBGA_4  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCYCBGA.bit.MCYCBGA_4 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCYCBBD_1  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCYCBBD.bit.MCYCBBD_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCYCBBD_2  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCYCBBD.bit.MCYCBBD_2 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCYCBBD_3  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCYCBBD.bit.MCYCBBD_3 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCYCBBD_4  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCYCBBD.bit.MCYCBBD_4 ));
	Ddim_Print(( "\n" ));

	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABALP   = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABALP.bit.MCBABALP ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABOF_0  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABOF.bit.MCBABOF_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABOF_1  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABOF.bit.MCBABOF_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABOF_2  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABOF.bit.MCBABOF_2 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABOF_3  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABOF.bit.MCBABOF_3 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABGA[0] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCBABGA.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABGA[1] = 0x%lx\n", ioR2yP2.F_R2Y.MCC.MCBABGA.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABGA_0  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABGA.bit.MCBABGA_0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABGA_1  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABGA.bit.MCBABGA_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABGA_2  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABGA.bit.MCBABGA_2 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABGA_3  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABGA.bit.MCBABGA_3 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABBD_1  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABBD.bit.MCBABBD_1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABBD_2  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABBD.bit.MCBABBD_2 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCBABBD_3  = 0x%x\n", ioR2yP2.F_R2Y.MCC.MCBABBD.bit.MCBABBD_3 ));
	Ddim_Print(( "\n" ));

#endif

}

CtImR2yClasso* ct_im_r2y_classo_new(void)
{
	CtImR2yClasso* self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSO, sizeof(CtImR2yClassoPrivate));

	return self;
}

CtImR2yClasso* ct_im_r2y_classo_get(void)
{
	static CtImR2yClasso* self = NULL;

	if(!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSO, sizeof(CtImR2yClassoPrivate));
	}

	return self;
}
