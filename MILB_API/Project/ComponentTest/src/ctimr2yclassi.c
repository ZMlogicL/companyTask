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
	self->imR2yClk=im_r2y_clk_new();
	self->imR2yEdge=im_r2y_edge_new();
}

static void ct_im_r2y_classi_destructor(CtImR2yClassi *self)
{
	CtImR2yClassiPrivate *priv = CT_IM_R2Y_CLASSI_GET_PRIVATE(self);
	if(self->imR2yClk){
						k_object_unref(self->imR2yClk);
						self->imR2yClk=NULL;
					}
	if(self->imR2yEdge){
						k_object_unref(self->imR2yEdge);
						self->imR2yEdge=NULL;
					}
}



#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classi_1_70: "
INT32 ct_im_r2y_classi_1_70( CtImR2yClassi *self,UCHAR pipeNo )
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
		ercd = im_r2y_edge_ctrl_high_edge(self->imR2yEdge, pipeNo, &r2yCtrlHedge[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwen       = %u\n",    ioR2yP1.fR2y.eghw.eghwctl.bit.eghwen ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwmp       = %u\n",    ioR2yP1.fR2y.eghw.eghwctl.bit.eghwmp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwtc       = %u\n",    ioR2yP1.fR2y.eghw.eghwctl.bit.eghwtc ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwsclres   = %u\n",    ioR2yP1.fR2y.eghw.eghwctl.bit.eghwsclres ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwscltbl   = %u\n",    ioR2yP1.fR2y.eghw.eghwctl.bit.eghwscltbl ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwtcres    = %u\n",    ioR2yP1.fR2y.eghw.eghwctl.bit.eghwtcres ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwtctbl    = %u\n",    ioR2yP1.fR2y.eghw.eghwctl.bit.eghwtctbl ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwnrlv     = %u\n",    ioR2yP1.fR2y.eghw.eghwctl.bit.eghwnrlv ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk[0]  = 0x%lx\n", ioR2yP1.fR2y.eghw.eghwhpfk.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk[1]  = 0x%lx\n", ioR2yP1.fR2y.eghw.eghwhpfk.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk0    = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwhpfk.bit.eghwhpfk0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk1    = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwhpfk.bit.eghwhpfk1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk2    = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwhpfk.bit.eghwhpfk2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk3    = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwhpfk.bit.eghwhpfk3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk4    = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwhpfk.bit.eghwhpfk4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk5    = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwhpfk.bit.eghwhpfk5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpof0 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcorpof.bit.eghwcorpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpof1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcorpof.bit.eghwcorpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpof2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcorpof.bit.eghwcorpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpof3 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcorpof.bit.eghwcorpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpga   = 0x%lx\n", ioR2yP1.fR2y.eghw.eghwcorpga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpga0 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcorpga.bit.eghwcorpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpga1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcorpga.bit.eghwcorpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpga2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcorpga.bit.eghwcorpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpga3 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcorpga.bit.eghwcorpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpbd1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcorpbd.bit.eghwcorpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpbd2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcorpbd.bit.eghwcorpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpbd3 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcorpbd.bit.eghwcorpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormof0 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcormof.bit.eghwcormof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormof1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcormof.bit.eghwcormof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormof2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcormof.bit.eghwcormof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormof3 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcormof.bit.eghwcormof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormga   = 0x%lx\n", ioR2yP1.fR2y.eghw.eghwcormga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormga0 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcormga.bit.eghwcormga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormga1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcormga.bit.eghwcormga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormga2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcormga.bit.eghwcormga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormga3 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcormga.bit.eghwcormga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormbd1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcormbd.bit.eghwcormbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormbd2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcormbd.bit.eghwcormbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormbd3 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwcormbd.bit.eghwcormbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwsclsup   = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwsclsup.bit.eghwsclsup ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppof0 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclppof.bit.eghwclppof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppof1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclppof.bit.eghwclppof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppof2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclppof.bit.eghwclppof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppga   = 0x%lx\n", ioR2yP1.fR2y.eghw.eghwclppga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppga0 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclppga.bit.eghwclppga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppga1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclppga.bit.eghwclppga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppga2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclppga.bit.eghwclppga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppbd1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclppbd.bit.eghwclppbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppbd2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclppbd.bit.eghwclppbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmof0 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclpmof.bit.eghwclpmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmof1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclpmof.bit.eghwclpmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmof2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclpmof.bit.eghwclpmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmga   = 0x%lx\n", ioR2yP1.fR2y.eghw.eghwclpmga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmga0 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclpmga.bit.eghwclpmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmga1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclpmga.bit.eghwclpmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmga2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclpmga.bit.eghwclpmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmbd1 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclpmbd.bit.eghwclpmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmbd2 = 0x%x\n",  ioR2yP1.fR2y.eghw.eghwclpmbd.bit.eghwclpmbd2 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwen       = %u\n",    ioR2yP2.fR2y.eghw.eghwctl.bit.eghwen ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwmp       = %u\n",    ioR2yP2.fR2y.eghw.eghwctl.bit.eghwmp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwtc       = %u\n",    ioR2yP2.fR2y.eghw.eghwctl.bit.eghwtc ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwsclres   = %u\n",    ioR2yP2.fR2y.eghw.eghwctl.bit.eghwsclres ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwscltbl   = %u\n",    ioR2yP2.fR2y.eghw.eghwctl.bit.eghwscltbl ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwtcres    = %u\n",    ioR2yP2.fR2y.eghw.eghwctl.bit.eghwtcres ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwtctbl    = %u\n",    ioR2yP2.fR2y.eghw.eghwctl.bit.eghwtctbl ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwnrlv     = %u\n",    ioR2yP2.fR2y.eghw.eghwctl.bit.eghwnrlv ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk[0]  = 0x%lx\n", ioR2yP2.fR2y.eghw.eghwhpfk.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk[1]  = 0x%lx\n", ioR2yP2.fR2y.eghw.eghwhpfk.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk0    = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwhpfk.bit.eghwhpfk0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk1    = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwhpfk.bit.eghwhpfk1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk2    = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwhpfk.bit.eghwhpfk2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk3    = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwhpfk.bit.eghwhpfk3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk4    = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwhpfk.bit.eghwhpfk4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwhpfk5    = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwhpfk.bit.eghwhpfk5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpof0 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcorpof.bit.eghwcorpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpof1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcorpof.bit.eghwcorpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpof2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcorpof.bit.eghwcorpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpof3 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcorpof.bit.eghwcorpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpga   = 0x%lx\n", ioR2yP2.fR2y.eghw.eghwcorpga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpga0 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcorpga.bit.eghwcorpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpga1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcorpga.bit.eghwcorpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpga2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcorpga.bit.eghwcorpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpga3 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcorpga.bit.eghwcorpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpbd1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcorpbd.bit.eghwcorpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpbd2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcorpbd.bit.eghwcorpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcorpbd3 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcorpbd.bit.eghwcorpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormof0 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcormof.bit.eghwcormof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormof1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcormof.bit.eghwcormof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormof2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcormof.bit.eghwcormof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormof3 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcormof.bit.eghwcormof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormga   = 0x%lx\n", ioR2yP2.fR2y.eghw.eghwcormga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormga0 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcormga.bit.eghwcormga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormga1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcormga.bit.eghwcormga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormga2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcormga.bit.eghwcormga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormga3 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcormga.bit.eghwcormga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormbd1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcormbd.bit.eghwcormbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormbd2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcormbd.bit.eghwcormbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwcormbd3 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwcormbd.bit.eghwcormbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwsclsup   = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwsclsup.bit.eghwsclsup ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppof0 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclppof.bit.eghwclppof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppof1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclppof.bit.eghwclppof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppof2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclppof.bit.eghwclppof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppga   = 0x%lx\n", ioR2yP2.fR2y.eghw.eghwclppga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppga0 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclppga.bit.eghwclppga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppga1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclppga.bit.eghwclppga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppga2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclppga.bit.eghwclppga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppbd1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclppbd.bit.eghwclppbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclppbd2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclppbd.bit.eghwclppbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmof0 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclpmof.bit.eghwclpmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmof1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclpmof.bit.eghwclpmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmof2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclpmof.bit.eghwclpmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmga   = 0x%lx\n", ioR2yP2.fR2y.eghw.eghwclpmga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmga0 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclpmga.bit.eghwclpmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmga1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclpmga.bit.eghwclpmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmga2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclpmga.bit.eghwclpmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmbd1 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclpmbd.bit.eghwclpmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "eghwclpmbd2 = 0x%x\n",  ioR2yP2.fR2y.eghw.eghwclpmbd.bit.eghwclpmbd2 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classi_1_71: "
INT32 ct_im_r2y_classi_1_71(CtImR2yClassi *self, UCHAR pipeNo )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_edge_set_high_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_edge_set_high_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_edge_set_high_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_edge_set_high_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classi_1_72: "
INT32 ct_im_r2y_classi_1_72( CtImR2yClassi *self,UCHAR pipeNo )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_edge_set_high_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_edge_set_high_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_edge_set_high_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_edge_set_high_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classi_1_73: "
INT32 ct_im_r2y_classi_1_73( CtImR2yClassi *self,UCHAR pipeNo )
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
		ercd = im_r2y_edge_ctrl_medium_edge(self->imR2yEdge, pipeNo, &r2yCtrlMedge[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwen       = %u\n",    ioR2yP1.fR2y.egmw.egmwctl.bit.egmwen ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwmp       = %u\n",    ioR2yP1.fR2y.egmw.egmwctl.bit.egmwmp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwtc       = %u\n",    ioR2yP1.fR2y.egmw.egmwctl.bit.egmwtc ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwsclres   = %u\n",    ioR2yP1.fR2y.egmw.egmwctl.bit.egmwsclres ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwscltbl   = %u\n",    ioR2yP1.fR2y.egmw.egmwctl.bit.egmwscltbl ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwtcres    = %u\n",    ioR2yP1.fR2y.egmw.egmwctl.bit.egmwtcres ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwtctbl    = %u\n",    ioR2yP1.fR2y.egmw.egmwctl.bit.egmwtctbl ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwnrlv     = %u\n",    ioR2yP1.fR2y.egmw.egmwctl.bit.egmwnrlv ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk[0]  = 0x%lx\n", ioR2yP1.fR2y.egmw.egmwhpfk.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk[1]  = 0x%lx\n", ioR2yP1.fR2y.egmw.egmwhpfk.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk0    = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwhpfk.bit.egmwhpfk0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk1    = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwhpfk.bit.egmwhpfk1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk2    = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwhpfk.bit.egmwhpfk2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk3    = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwhpfk.bit.egmwhpfk3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk4    = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwhpfk.bit.egmwhpfk4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk5    = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwhpfk.bit.egmwhpfk5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpof0 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcorpof.bit.egmwcorpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpof1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcorpof.bit.egmwcorpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpof2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcorpof.bit.egmwcorpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpof3 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcorpof.bit.egmwcorpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpga   = 0x%lx\n", ioR2yP1.fR2y.egmw.egmwcorpga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpga0 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcorpga.bit.egmwcorpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpga1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcorpga.bit.egmwcorpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpga2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcorpga.bit.egmwcorpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpga3 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcorpga.bit.egmwcorpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpbd1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcorpbd.bit.egmwcorpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpbd2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcorpbd.bit.egmwcorpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpbd3 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcorpbd.bit.egmwcorpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormof0 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcormof.bit.egmwcormof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormof1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcormof.bit.egmwcormof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormof2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcormof.bit.egmwcormof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormof3 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcormof.bit.egmwcormof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormga   = 0x%lx\n", ioR2yP1.fR2y.egmw.egmwcormga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormga0 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcormga.bit.egmwcormga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormga1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcormga.bit.egmwcormga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormga2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcormga.bit.egmwcormga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormga3 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcormga.bit.egmwcormga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormbd1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcormbd.bit.egmwcormbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormbd2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcormbd.bit.egmwcormbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormbd3 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwcormbd.bit.egmwcormbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwsclsup   = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwsclsup.bit.egmwsclsup ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppof0 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclppof.bit.egmwclppof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppof1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclppof.bit.egmwclppof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppof2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclppof.bit.egmwclppof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppga   = 0x%lx\n", ioR2yP1.fR2y.egmw.egmwclppga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppga0 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclppga.bit.egmwclppga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppga1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclppga.bit.egmwclppga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppga2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclppga.bit.egmwclppga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppbd1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclppbd.bit.egmwclppbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppbd2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclppbd.bit.egmwclppbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmof0 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclpmof.bit.egmwclpmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmof1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclpmof.bit.egmwclpmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmof2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclpmof.bit.egmwclpmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmga   = 0x%lx\n", ioR2yP1.fR2y.egmw.egmwclpmga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmga0 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclpmga.bit.egmwclpmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmga1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclpmga.bit.egmwclpmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmga2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclpmga.bit.egmwclpmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmbd1 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclpmbd.bit.egmwclpmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmbd2 = 0x%x\n",  ioR2yP1.fR2y.egmw.egmwclpmbd.bit.egmwclpmbd2 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwen       = %u\n",    ioR2yP2.fR2y.egmw.egmwctl.bit.egmwen ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwmp       = %u\n",    ioR2yP2.fR2y.egmw.egmwctl.bit.egmwmp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwtc       = %u\n",    ioR2yP2.fR2y.egmw.egmwctl.bit.egmwtc ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwsclres   = %u\n",    ioR2yP2.fR2y.egmw.egmwctl.bit.egmwsclres ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwscltbl   = %u\n",    ioR2yP2.fR2y.egmw.egmwctl.bit.egmwscltbl ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwtcres    = %u\n",    ioR2yP2.fR2y.egmw.egmwctl.bit.egmwtcres ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwtctbl    = %u\n",    ioR2yP2.fR2y.egmw.egmwctl.bit.egmwtctbl ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwnrlv     = %u\n",    ioR2yP2.fR2y.egmw.egmwctl.bit.egmwnrlv ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk[0]  = 0x%lx\n", ioR2yP2.fR2y.egmw.egmwhpfk.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk[1]  = 0x%lx\n", ioR2yP2.fR2y.egmw.egmwhpfk.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk0    = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwhpfk.bit.egmwhpfk0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk1    = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwhpfk.bit.egmwhpfk1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk2    = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwhpfk.bit.egmwhpfk2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk3    = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwhpfk.bit.egmwhpfk3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk4    = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwhpfk.bit.egmwhpfk4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwhpfk5    = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwhpfk.bit.egmwhpfk5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpof0 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcorpof.bit.egmwcorpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpof1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcorpof.bit.egmwcorpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpof2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcorpof.bit.egmwcorpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpof3 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcorpof.bit.egmwcorpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpga   = 0x%lx\n", ioR2yP2.fR2y.egmw.egmwcorpga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpga0 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcorpga.bit.egmwcorpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpga1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcorpga.bit.egmwcorpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpga2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcorpga.bit.egmwcorpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpga3 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcorpga.bit.egmwcorpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpbd1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcorpbd.bit.egmwcorpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpbd2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcorpbd.bit.egmwcorpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcorpbd3 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcorpbd.bit.egmwcorpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormof0 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcormof.bit.egmwcormof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormof1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcormof.bit.egmwcormof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormof2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcormof.bit.egmwcormof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormof3 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcormof.bit.egmwcormof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormga   = 0x%lx\n", ioR2yP2.fR2y.egmw.egmwcormga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormga0 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcormga.bit.egmwcormga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormga1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcormga.bit.egmwcormga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormga2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcormga.bit.egmwcormga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormga3 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcormga.bit.egmwcormga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormbd1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcormbd.bit.egmwcormbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormbd2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcormbd.bit.egmwcormbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwcormbd3 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwcormbd.bit.egmwcormbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwsclsup   = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwsclsup.bit.egmwsclsup ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppof0 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclppof.bit.egmwclppof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppof1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclppof.bit.egmwclppof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppof2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclppof.bit.egmwclppof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppga   = 0x%lx\n", ioR2yP2.fR2y.egmw.egmwclppga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppga0 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclppga.bit.egmwclppga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppga1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclppga.bit.egmwclppga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppga2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclppga.bit.egmwclppga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppbd1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclppbd.bit.egmwclppbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclppbd2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclppbd.bit.egmwclppbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmof0 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclpmof.bit.egmwclpmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmof1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclpmof.bit.egmwclpmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmof2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclpmof.bit.egmwclpmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmga   = 0x%lx\n", ioR2yP2.fR2y.egmw.egmwclpmga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmga0 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclpmga.bit.egmwclpmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmga1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclpmga.bit.egmwclpmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmga2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclpmga.bit.egmwclpmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmbd1 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclpmbd.bit.egmwclpmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egmwclpmbd2 = 0x%x\n",  ioR2yP2.fR2y.egmw.egmwclpmbd.bit.egmwclpmbd2 ));
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
