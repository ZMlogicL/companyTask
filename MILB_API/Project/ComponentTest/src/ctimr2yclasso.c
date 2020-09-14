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

void ct_im_r2y_classo_1_54_temp3(CtImR2yClasso *self)
{
#ifdef CO_MSG_PRINT_ON
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[0][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl0.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[0][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl0.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[0][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl0.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl0.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl0.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl0.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl0.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl0.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_0_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl0.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[1][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl1.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[1][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl1.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[1][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl1.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl1.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl1.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl1.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl1.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl1.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_1_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl1.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[2][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl2.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[2][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl2.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[2][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl2.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl2.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl2.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl2.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl2.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl2.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_2_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl2.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[3][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl3.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[3][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl3.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[3][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl3.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl3.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl3.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl3.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl3.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl3.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_3_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl3.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[4][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl4.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[4][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl4.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcli[4][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcli.mcl4.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl4.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl4.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl4.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl4.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl4.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLI_4_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcli.mcl4.bit.mcl21 ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[0][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl0.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[0][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl0.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[0][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl0.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl0.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl0.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl0.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl0.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl0.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_0_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl0.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[1][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl1.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[1][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl1.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[1][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl1.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl1.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl1.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl1.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl1.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl1.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_1_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl1.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[2][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl2.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[2][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl2.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[2][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl2.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl2.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl2.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl2.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl2.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl2.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_2_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl2.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[3][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl3.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[3][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl3.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[3][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl3.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl3.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl3.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl3.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl3.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl3.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_3_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl3.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[4][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl4.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[4][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl4.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclj[4][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclj.mcl4.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl4.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl4.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl4.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl4.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl4.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLJ_4_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclj.mcl4.bit.mcl21 ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[0][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl0.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[0][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl0.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[0][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl0.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl0.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl0.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl0.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl0.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl0.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_0_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl0.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[1][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl1.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[1][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl1.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[1][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl1.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl1.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl1.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl1.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl1.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl1.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_1_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl1.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[2][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl2.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[2][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl2.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[2][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl2.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl2.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl2.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl2.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl2.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl2.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_2_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl2.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[3][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl3.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[3][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl3.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[3][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl3.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl3.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl3.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl3.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl3.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl3.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_3_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl3.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[4][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl4.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[4][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl4.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mclk[4][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mclk.mcl4.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl4.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl4.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl4.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl4.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl4.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLK_4_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mclk.mcl4.bit.mcl21 ));
	Ddim_Print(( "\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[0][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl0.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[0][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl0.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[0][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl0.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl0.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl0.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl0.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl0.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl0.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_0_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl0.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[1][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl1.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[1][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl1.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[1][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl1.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl1.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl1.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl1.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl1.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl1.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_1_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl1.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[2][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl2.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[2][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl2.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[2][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl2.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl2.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl2.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl2.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl2.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl2.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_2_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl2.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[3][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl3.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[3][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl3.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[3][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl3.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl3.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl3.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl3.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl3.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl3.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_3_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl3.bit.mcl21 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[4][0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl4.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[4][1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl4.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcll[4][2] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcll.mcl4.word[2] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_0_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl4.bit.mcl00 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_0_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl4.bit.mcl01 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_1_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl4.bit.mcl10 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_1_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl4.bit.mcl11 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_2_0 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl4.bit.mcl20 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "MCLL_4_2_1 = 0x%x\n", ioR2yP2.fR2y.mcc.mcll.mcl4.bit.mcl21 ));
	Ddim_Print(( "\n" ));

	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcycbalp   = 0x%x\n", ioR2yP2.fR2y.mcc.mcycbalp.bit.mcycbalp ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcycbga1  = 0x%x\n", ioR2yP2.fR2y.mcc.mcycbga.bit.mcycbga1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcycbga2  = 0x%x\n", ioR2yP2.fR2y.mcc.mcycbga.bit.mcycbga2 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcycbga3  = 0x%x\n", ioR2yP2.fR2y.mcc.mcycbga.bit.mcycbga3 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcycbga4  = 0x%x\n", ioR2yP2.fR2y.mcc.mcycbga.bit.mcycbga4 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcycbbd1  = 0x%x\n", ioR2yP2.fR2y.mcc.mcycbbd.bit.mcycbbd1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcycbbd2  = 0x%x\n", ioR2yP2.fR2y.mcc.mcycbbd.bit.mcycbbd2 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcycbbd3  = 0x%x\n", ioR2yP2.fR2y.mcc.mcycbbd.bit.mcycbbd3 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcycbbd4  = 0x%x\n", ioR2yP2.fR2y.mcc.mcycbbd.bit.mcycbbd4 ));
	Ddim_Print(( "\n" ));

	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabalp   = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabalp.bit.mcbabalp ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabof0  = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabof.bit.mcbabof0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabof1  = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabof.bit.mcbabof1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabof2  = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabof.bit.mcbabof2 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabof3  = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabof.bit.mcbabof3 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabga[0] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcbabga.word[0] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabga[1] = 0x%lx\n", ioR2yP2.fR2y.mcc.mcbabga.word[1] ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabga0  = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabga.bit.mcbabga0 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabga1  = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabga.bit.mcbabga1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabga2  = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabga.bit.mcbabga2 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabga3  = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabga.bit.mcbabga3 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabbd1  = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabbd.bit.mcbabbd1 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabbd2  = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabbd.bit.mcbabbd2 ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "mcbabbd3  = 0x%x\n", ioR2yP2.fR2y.mcc.mcbabbd.bit.mcbabbd3 ));
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
