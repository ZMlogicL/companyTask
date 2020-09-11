/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassi
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2yclassi.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yClassi, ct_im_r2y_classi)
#define CT_IM_R2Y_CLASSI_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yClassiPrivate, CT_TYPE_IM_R2Y_CLASSI))


struct _CtImR2yClassiPrivate
{

};


static void ct_im_r2y_classi_constructor(CtImR2yClassi *self)
{
	CtImR2yClassiPrivate *priv = CT_IM_R2Y_CLASSI_GET_PRIVATE(self);
}

static void ct_im_r2y_classi_destructor(CtImR2yClassi *self)
{
	CtImR2yClassiPrivate *priv = CT_IM_R2Y_CLASSI_GET_PRIVATE(self);
}



#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classi_1_70: "
INT32 ct_im_r2y_classi_1_70( UCHAR pipeNo )
{
	TImR2yCtrlHedge r2yCtrlHedge[] = {
		[0] = {	// max
			.edgeEnable = 1,
			.scaleEnable = 1,
			.tableClipSelect = 1,
			.scaleTableResol = 2,
			.scaleTableSelect = 3,
			.gradationTableResol = 2,
			.gradationTableSelect = 3,
			.nrLevel = 0x8,
			.hpfK = {
				0x3FF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
			},
			.corpOffset = {
				0x3FF, 0x3FF, 0x3FF, 0x3FF,
			},
			.corpGain = {
				0x7F, 0x7F, 0x7F, 0x7F,
			},
			.corpBorder = {
				0x3FF, 0x3FF, 0x3FF,
			},
			.cormOffset = {
				0x3FF, 0x3FF, 0x3FF, 0x3FF,
			},
			.cormGain = {
				0x7F, 0x7F, 0x7F, 0x7F,
			},
			.cormBorder = {
				0x3FF, 0x3FF, 0x3FF,
			},
			.supScl = 0x3F,
			.levelClipPOffset = {
				0x1FF, 0x1FF, 0x1FF,
			},
			.levelClipPGain = {
				0x7F, 0x7F, 0x7F,
			},
			.levelClipPDorder = {
				0x3FF, 0x3FF,
			},
			.levelClipMOffset = {
				0x1FF, 0x1FF, 0x1FF,
			},
			.levelClipMGain = {
				0x7F, 0x7F, 0x7F,
			},
			.levelClipMBorder = {
				0x3FF, 0x3FF,
			},
		},
		[1] = {	// min
			.edgeEnable = 0,
			.scaleEnable = 0,
			.tableClipSelect = 0,
			.scaleTableResol = 0,
			.scaleTableSelect = 0,
			.gradationTableResol = 0,
			.gradationTableSelect = 0,
			.nrLevel = 0,
			.hpfK = {
				0, -0x80, -0x80, -0x80, -0x80, -0x80,
			},
			.corpOffset = {
				0, 0, 0, 0,
			},
			.corpGain = {
				-0x80, -0x80, -0x80, -0x80,
			},
			.corpBorder = {
				0, 0, 0,
			},
			.cormOffset = {
				0, 0, 0, 0,
			},
			.cormGain = {
				-0x80, -0x80, -0x80, -0x80,
			},
			.cormBorder = {
				0, 0, 0,
			},
			.supScl = 0,
			.levelClipPOffset = {
				0, 0, 0,
			},
			.levelClipPGain = {
				-0x80, -0x80, -0x80,
			},
			.levelClipPDorder = {
				0, 0,
			},
			.levelClipMOffset = {
				0, 0, 0,
			},
			.levelClipMGain = {
				-0x80, -0x80, -0x80,
			},
			.levelClipMBorder = {
				0, 0,
			},
		},
		[2] = {	// indvisual
			.edgeEnable = 1,
			.scaleEnable = 0,
			.tableClipSelect = 0,
			.scaleTableResol = 1,
			.scaleTableSelect = 1,
			.gradationTableResol = 1,
			.gradationTableSelect = 1,
			.nrLevel = 2,
			.hpfK = {
				1, 2, 3, 4, 5, 6,
			},
			.corpOffset = {
				7, 8, 9, 10,
			},
			.corpGain = {
				11, 12, 13, 14,
			},
			.corpBorder = {
				15, 16, 17,
			},
			.cormOffset = {
				18, 19, 20, 21,
			},
			.cormGain = {
				22, 23, 24, 25,
			},
			.cormBorder = {
				26, 27, 28,
			},
			.supScl = 29,
			.levelClipPOffset = {
				30, 31, 32,
			},
			.levelClipPGain = {
				33, 34, 35,
			},
			.levelClipPDorder = {
				36, 37,
			},
			.levelClipMOffset = {
				38, 39, 40,
			},
			.levelClipMGain = {
				41, 42, 43,
			},
			.levelClipMBorder = {
				44, 45,
			},
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlHedge) / sizeof(r2yCtrlHedge[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_R2Y_Ctrl_HighEdge( pipeNo, &r2yCtrlHedge[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWEN       = %u\n",    ioR2yP1.F_R2Y.EGHW.EGHWCTL.bit.EGHWEN ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWMP       = %u\n",    ioR2yP1.F_R2Y.EGHW.EGHWCTL.bit.EGHWMP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWTC       = %u\n",    ioR2yP1.F_R2Y.EGHW.EGHWCTL.bit.EGHWTC ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWSCLRES   = %u\n",    ioR2yP1.F_R2Y.EGHW.EGHWCTL.bit.EGHWSCLRES ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWSCLTBL   = %u\n",    ioR2yP1.F_R2Y.EGHW.EGHWCTL.bit.EGHWSCLTBL ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWTCRES    = %u\n",    ioR2yP1.F_R2Y.EGHW.EGHWCTL.bit.EGHWTCRES ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWTCTBL    = %u\n",    ioR2yP1.F_R2Y.EGHW.EGHWCTL.bit.EGHWTCTBL ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWNRLV     = %u\n",    ioR2yP1.F_R2Y.EGHW.EGHWCTL.bit.EGHWNRLV ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK[0]  = 0x%lx\n", ioR2yP1.F_R2Y.EGHW.EGHWHPFK.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK[1]  = 0x%lx\n", ioR2yP1.F_R2Y.EGHW.EGHWHPFK.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK0    = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK1    = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK2    = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK3    = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK4    = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK5    = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPOF_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPOF_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPOF_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPOF_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPGA   = 0x%lx\n", ioR2yP1.F_R2Y.EGHW.EGHWCORPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPGA_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORPGA.bit.EGHWCORPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPGA_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORPGA.bit.EGHWCORPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPGA_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORPGA.bit.EGHWCORPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPGA_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORPGA.bit.EGHWCORPGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPBD_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPBD_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPBD_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMOF_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMOF_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMOF_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMOF_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMGA   = 0x%lx\n", ioR2yP1.F_R2Y.EGHW.EGHWCORMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMGA_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORMGA.bit.EGHWCORMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMGA_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORMGA.bit.EGHWCORMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMGA_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORMGA.bit.EGHWCORMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMGA_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORMGA.bit.EGHWCORMGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMBD_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMBD_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMBD_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWSCLSUP   = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWSCLSUP.bit.EGHWSCLSUP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPOF_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPOF_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPOF_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPGA   = 0x%lx\n", ioR2yP1.F_R2Y.EGHW.EGHWCLPPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPGA_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPPGA.bit.EGHWCLPPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPGA_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPPGA.bit.EGHWCLPPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPGA_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPPGA.bit.EGHWCLPPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPBD_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPPBD.bit.EGHWCLPPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPBD_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPPBD.bit.EGHWCLPPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMOF_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMOF_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMOF_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMGA   = 0x%lx\n", ioR2yP1.F_R2Y.EGHW.EGHWCLPMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMGA_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPMGA.bit.EGHWCLPMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMGA_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPMGA.bit.EGHWCLPMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMGA_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPMGA.bit.EGHWCLPMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMBD_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPMBD.bit.EGHWCLPMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMBD_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGHW.EGHWCLPMBD.bit.EGHWCLPMBD_2 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWEN       = %u\n",    ioR2yP2.F_R2Y.EGHW.EGHWCTL.bit.EGHWEN ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWMP       = %u\n",    ioR2yP2.F_R2Y.EGHW.EGHWCTL.bit.EGHWMP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWTC       = %u\n",    ioR2yP2.F_R2Y.EGHW.EGHWCTL.bit.EGHWTC ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWSCLRES   = %u\n",    ioR2yP2.F_R2Y.EGHW.EGHWCTL.bit.EGHWSCLRES ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWSCLTBL   = %u\n",    ioR2yP2.F_R2Y.EGHW.EGHWCTL.bit.EGHWSCLTBL ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWTCRES    = %u\n",    ioR2yP2.F_R2Y.EGHW.EGHWCTL.bit.EGHWTCRES ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWTCTBL    = %u\n",    ioR2yP2.F_R2Y.EGHW.EGHWCTL.bit.EGHWTCTBL ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWNRLV     = %u\n",    ioR2yP2.F_R2Y.EGHW.EGHWCTL.bit.EGHWNRLV ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK[0]  = 0x%lx\n", ioR2yP2.F_R2Y.EGHW.EGHWHPFK.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK[1]  = 0x%lx\n", ioR2yP2.F_R2Y.EGHW.EGHWHPFK.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK0    = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK1    = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK2    = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK3    = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK4    = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWHPFK5    = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWHPFK.bit.EGHWHPFK5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPOF_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPOF_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPOF_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPOF_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORPOF.bit.EGHWCORPOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPGA   = 0x%lx\n", ioR2yP2.F_R2Y.EGHW.EGHWCORPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPGA_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORPGA.bit.EGHWCORPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPGA_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORPGA.bit.EGHWCORPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPGA_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORPGA.bit.EGHWCORPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPGA_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORPGA.bit.EGHWCORPGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPBD_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPBD_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORPBD_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORPBD.bit.EGHWCORPBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMOF_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMOF_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMOF_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMOF_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORMOF.bit.EGHWCORMOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMGA   = 0x%lx\n", ioR2yP2.F_R2Y.EGHW.EGHWCORMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMGA_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORMGA.bit.EGHWCORMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMGA_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORMGA.bit.EGHWCORMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMGA_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORMGA.bit.EGHWCORMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMGA_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORMGA.bit.EGHWCORMGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMBD_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMBD_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCORMBD_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCORMBD.bit.EGHWCORMBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWSCLSUP   = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWSCLSUP.bit.EGHWSCLSUP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPOF_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPOF_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPOF_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPPOF.bit.EGHWCLPPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPGA   = 0x%lx\n", ioR2yP2.F_R2Y.EGHW.EGHWCLPPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPGA_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPPGA.bit.EGHWCLPPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPGA_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPPGA.bit.EGHWCLPPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPGA_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPPGA.bit.EGHWCLPPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPBD_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPPBD.bit.EGHWCLPPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPPBD_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPPBD.bit.EGHWCLPPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMOF_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMOF_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMOF_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPMOF.bit.EGHWCLPMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMGA   = 0x%lx\n", ioR2yP2.F_R2Y.EGHW.EGHWCLPMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMGA_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPMGA.bit.EGHWCLPMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMGA_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPMGA.bit.EGHWCLPMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMGA_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPMGA.bit.EGHWCLPMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMBD_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPMBD.bit.EGHWCLPMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGHWCLPMBD_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGHW.EGHWCLPMBD.bit.EGHWCLPMBD_2 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classi_1_71: "
INT32 ct_im_r2y_classi_1_71( UCHAR pipeNo )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_HighEdgeSclTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_HighEdgeSclTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_HighEdgeSclTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_HighEdgeSclTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classi_1_72: "
INT32 ct_im_r2y_classi_1_72( UCHAR pipeNo )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_HighEdgeStepTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_HighEdgeStepTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_HighEdgeStepTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_HighEdgeStepTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classi_1_73: "
INT32 ct_im_r2y_classi_1_73( UCHAR pipeNo )
{
	TImR2yCtrlMedge r2yCtrlMedge[] = {
		[0] = {	// max
			.edgeEnable = 1,
			.scaleEnable = 1,
			.tableClipSelect = 1,
			.scaleTableResol = 2,
			.scaleTableSelect = 3,
			.gradationTableResol = 2,
			.gradationTableSelect = 3,
			.nrLevel = 0x8,
			.hpfK = {
				0x3FF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
			},
			.corpOffset = {
				0x3FF, 0x3FF, 0x3FF, 0x3FF,
			},
			.corpGain = {
				0x7F, 0x7F, 0x7F, 0x7F,
			},
			.corpBorder = {
				0x3FF, 0x3FF, 0x3FF,
			},
			.cormOffset = {
				0x3FF, 0x3FF, 0x3FF, 0x3FF,
			},
			.cormGain = {
				0x7F, 0x7F, 0x7F, 0x7F,
			},
			.cormBorder = {
				0x3FF, 0x3FF, 0x3FF,
			},
			.supScl = 0x3F,
			.levelClipPOffset = {
				0x1FF, 0x1FF, 0x1FF,
			},
			.levelClipPGain = {
				0x7F, 0x7F, 0x7F,
			},
			.levelClipPDorder = {
				0x3FF, 0x3FF,
			},
			.levelClipMOffset = {
				0x1FF, 0x1FF, 0x1FF,
			},
			.levelClipMGain = {
				0x7F, 0x7F, 0x7F,
			},
			.levelClipMBorder = {
				0x3FF, 0x3FF,
			},
		},
		[1] = {	// min
			.edgeEnable = 0,
			.scaleEnable = 0,
			.tableClipSelect = 0,
			.scaleTableResol = 0,
			.scaleTableSelect = 0,
			.gradationTableResol = 0,
			.gradationTableSelect = 0,
			.nrLevel = 0,
			.hpfK = {
				0, -0x80, -0x80, -0x80, -0x80, -0x80,
			},
			.corpOffset = {
				0, 0, 0, 0,
			},
			.corpGain = {
				-0x80, -0x80, -0x80, -0x80,
			},
			.corpBorder = {
				0, 0, 0,
			},
			.cormOffset = {
				0, 0, 0, 0,
			},
			.cormGain = {
				-0x80, -0x80, -0x80, -0x80,
			},
			.cormBorder = {
				0, 0, 0,
			},
			.supScl = 0,
			.levelClipPOffset = {
				0, 0, 0,
			},
			.levelClipPGain = {
				-0x80, -0x80, -0x80,
			},
			.levelClipPDorder = {
				0, 0,
			},
			.levelClipMOffset = {
				0, 0, 0,
			},
			.levelClipMGain = {
				-0x80, -0x80, -0x80,
			},
			.levelClipMBorder = {
				0, 0,
			},
		},
		[2] = {	// indvisual
			.edgeEnable = 1,
			.scaleEnable = 0,
			.tableClipSelect = 0,
			.scaleTableResol = 1,
			.scaleTableSelect = 1,
			.gradationTableResol = 1,
			.gradationTableSelect = 1,
			.nrLevel = 2,
			.hpfK = {
				1, 2, 3, 4, 5, 6,
			},
			.corpOffset = {
				7, 8, 9, 10,
			},
			.corpGain = {
				11, 12, 13, 14,
			},
			.corpBorder = {
				15, 16, 17,
			},
			.cormOffset = {
				18, 19, 20, 21,
			},
			.cormGain = {
				22, 23, 24, 25,
			},
			.cormBorder = {
				26, 27, 28,
			},
			.supScl = 29,
			.levelClipPOffset = {
				30, 31, 32,
			},
			.levelClipPGain = {
				33, 34, 35,
			},
			.levelClipPDorder = {
				36, 37,
			},
			.levelClipMOffset = {
				38, 39, 40,
			},
			.levelClipMGain = {
				41, 42, 43,
			},
			.levelClipMBorder = {
				44, 45,
			},
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlMedge) / sizeof(r2yCtrlMedge[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_R2Y_Ctrl_MediumEdge( pipeNo, &r2yCtrlMedge[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWEN       = %u\n",    ioR2yP1.F_R2Y.EGMW.EGMWCTL.bit.EGMWEN ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWMP       = %u\n",    ioR2yP1.F_R2Y.EGMW.EGMWCTL.bit.EGMWMP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWTC       = %u\n",    ioR2yP1.F_R2Y.EGMW.EGMWCTL.bit.EGMWTC ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWSCLRES   = %u\n",    ioR2yP1.F_R2Y.EGMW.EGMWCTL.bit.EGMWSCLRES ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWSCLTBL   = %u\n",    ioR2yP1.F_R2Y.EGMW.EGMWCTL.bit.EGMWSCLTBL ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWTCRES    = %u\n",    ioR2yP1.F_R2Y.EGMW.EGMWCTL.bit.EGMWTCRES ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWTCTBL    = %u\n",    ioR2yP1.F_R2Y.EGMW.EGMWCTL.bit.EGMWTCTBL ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWNRLV     = %u\n",    ioR2yP1.F_R2Y.EGMW.EGMWCTL.bit.EGMWNRLV ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK[0]  = 0x%lx\n", ioR2yP1.F_R2Y.EGMW.EGMWHPFK.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK[1]  = 0x%lx\n", ioR2yP1.F_R2Y.EGMW.EGMWHPFK.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK0    = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK1    = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK2    = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK3    = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK4    = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK5    = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPOF_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPOF_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPOF_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPOF_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPGA   = 0x%lx\n", ioR2yP1.F_R2Y.EGMW.EGMWCORPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPGA_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORPGA.bit.EGMWCORPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPGA_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORPGA.bit.EGMWCORPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPGA_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORPGA.bit.EGMWCORPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPGA_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORPGA.bit.EGMWCORPGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPBD_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPBD_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPBD_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMOF_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMOF_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMOF_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMOF_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMGA   = 0x%lx\n", ioR2yP1.F_R2Y.EGMW.EGMWCORMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMGA_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORMGA.bit.EGMWCORMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMGA_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORMGA.bit.EGMWCORMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMGA_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORMGA.bit.EGMWCORMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMGA_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORMGA.bit.EGMWCORMGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMBD_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMBD_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMBD_3 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWSCLSUP   = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWSCLSUP.bit.EGMWSCLSUP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPOF_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPOF_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPOF_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPGA   = 0x%lx\n", ioR2yP1.F_R2Y.EGMW.EGMWCLPPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPGA_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPPGA.bit.EGMWCLPPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPGA_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPPGA.bit.EGMWCLPPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPGA_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPPGA.bit.EGMWCLPPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPBD_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPPBD.bit.EGMWCLPPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPBD_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPPBD.bit.EGMWCLPPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMOF_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMOF_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMOF_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMGA   = 0x%lx\n", ioR2yP1.F_R2Y.EGMW.EGMWCLPMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMGA_0 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPMGA.bit.EGMWCLPMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMGA_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPMGA.bit.EGMWCLPMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMGA_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPMGA.bit.EGMWCLPMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMBD_1 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPMBD.bit.EGMWCLPMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMBD_2 = 0x%x\n",  ioR2yP1.F_R2Y.EGMW.EGMWCLPMBD.bit.EGMWCLPMBD_2 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWEN       = %u\n",    ioR2yP2.F_R2Y.EGMW.EGMWCTL.bit.EGMWEN ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWMP       = %u\n",    ioR2yP2.F_R2Y.EGMW.EGMWCTL.bit.EGMWMP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWTC       = %u\n",    ioR2yP2.F_R2Y.EGMW.EGMWCTL.bit.EGMWTC ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWSCLRES   = %u\n",    ioR2yP2.F_R2Y.EGMW.EGMWCTL.bit.EGMWSCLRES ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWSCLTBL   = %u\n",    ioR2yP2.F_R2Y.EGMW.EGMWCTL.bit.EGMWSCLTBL ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWTCRES    = %u\n",    ioR2yP2.F_R2Y.EGMW.EGMWCTL.bit.EGMWTCRES ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWTCTBL    = %u\n",    ioR2yP2.F_R2Y.EGMW.EGMWCTL.bit.EGMWTCTBL ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWNRLV     = %u\n",    ioR2yP2.F_R2Y.EGMW.EGMWCTL.bit.EGMWNRLV ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK[0]  = 0x%lx\n", ioR2yP2.F_R2Y.EGMW.EGMWHPFK.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK[1]  = 0x%lx\n", ioR2yP2.F_R2Y.EGMW.EGMWHPFK.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK0    = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK1    = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK2    = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK3    = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK4    = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWHPFK5    = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWHPFK.bit.EGMWHPFK5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPOF_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPOF_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPOF_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPOF_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORPOF.bit.EGMWCORPOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPGA   = 0x%lx\n", ioR2yP2.F_R2Y.EGMW.EGMWCORPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPGA_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORPGA.bit.EGMWCORPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPGA_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORPGA.bit.EGMWCORPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPGA_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORPGA.bit.EGMWCORPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPGA_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORPGA.bit.EGMWCORPGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPBD_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPBD_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORPBD_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORPBD.bit.EGMWCORPBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMOF_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMOF_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMOF_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMOF_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORMOF.bit.EGMWCORMOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMGA   = 0x%lx\n", ioR2yP2.F_R2Y.EGMW.EGMWCORMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMGA_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORMGA.bit.EGMWCORMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMGA_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORMGA.bit.EGMWCORMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMGA_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORMGA.bit.EGMWCORMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMGA_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORMGA.bit.EGMWCORMGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMBD_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMBD_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCORMBD_3 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCORMBD.bit.EGMWCORMBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWSCLSUP   = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWSCLSUP.bit.EGMWSCLSUP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPOF_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPOF_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPOF_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPPOF.bit.EGMWCLPPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPGA   = 0x%lx\n", ioR2yP2.F_R2Y.EGMW.EGMWCLPPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPGA_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPPGA.bit.EGMWCLPPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPGA_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPPGA.bit.EGMWCLPPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPGA_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPPGA.bit.EGMWCLPPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPBD_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPPBD.bit.EGMWCLPPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPPBD_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPPBD.bit.EGMWCLPPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMOF_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMOF_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMOF_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPMOF.bit.EGMWCLPMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMGA   = 0x%lx\n", ioR2yP2.F_R2Y.EGMW.EGMWCLPMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMGA_0 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPMGA.bit.EGMWCLPMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMGA_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPMGA.bit.EGMWCLPMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMGA_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPMGA.bit.EGMWCLPMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMBD_1 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPMBD.bit.EGMWCLPMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGMWCLPMBD_2 = 0x%x\n",  ioR2yP2.F_R2Y.EGMW.EGMWCLPMBD.bit.EGMWCLPMBD_2 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}


CtImR2yClassi* ct_im_r2y_classi_new(void)
{
	CtImR2yClassi* self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSI, sizeof(CtImR2yClassiPrivate));

	return self;
}

CtImR2yClassi* ct_im_r2y_classi_get(void)
{
	static CtImR2yClassi* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSI, sizeof(CtImR2yClassiPrivate));
	}

	return self;
}
