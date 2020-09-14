/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassf
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2yclassf.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yClassf, ct_im_r2y_classf)
#define CT_IM_R2Y_CLASSF_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yClassfPrivate, CT_TYPE_IM_R2Y_CLASSF))


struct _CtImR2yClassfPrivate
{

};


static void ct_im_r2y_classf_constructor(CtImR2yClassf *self)
{
	CtImR2yClassfPrivate *priv = CT_IM_R2Y_CLASSF_GET_PRIVATE(self);



	ImR2yCtrl2*imR2yCtrl2;
	self->imR2yClk=im_r2y_clk_new();
	self->imR2y3=ct_im_r2y3_new();
	self->imR2yCtrl=im_r2y_ctrl_new();
	self->imR2yCtrl2=im_r2y_ctrl2_new();
}

static void ct_im_r2y_classf_destructor(CtImR2yClassf *self)
{
	CtImR2yClassfPrivate *priv = CT_IM_R2Y_CLASSF_GET_PRIVATE(self);
	if(self->imR2yClk){
						k_object_unref(self->imR2yClk);
						self->imR2yClk=NULL;
					}
	if(self->imR2y3){
						k_object_unref(self->imR2y3);
						self->imR2y3=NULL;
					}
	if(self->imR2yCtrl){
						k_object_unref(self->imR2yCtrl);
						self->imR2yCtrl=NULL;
					}
	if(self->imR2yCtrl2){
						k_object_unref(self->imR2yCtrl2);
						self->imR2yCtrl2=NULL;
					}
}



#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_46: "
INT32 ct_im_r2y_classf_1_46(CtImR2yClassf *self, UCHAR pipeNo )
{
	TImR2yPostResize1Param r2yPostResize1[] = {
		[0] = {	// max
			.edgeEnable = 1,
			.gradationEnable = 1,
			.hpfK = { 0x3FF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F },
			.strength = 8,
			.coringPOffset = { 0x3FC, 0x3FC, 0x3FC, 0x3FC },
			.coringPGain = { 0x7F, 0x7F, 0x7F, 0x7F },
			.coringPDorder = { 0x3FC, 0x3FC, 0x3FC },
			.coringMOffset = { 0x3FC, 0x3FC, 0x3FC, 0x3FC },
			.coringMGain = { 0x7F, 0x7F, 0x7F, 0x7F },
			.coringMBorder = { 0x3FC, 0x3FC, 0x3FC },
			.scaleReductCoef = 0x3F,
			.scalePOffset = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
			.scalePGain = { 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF },
			.scalePDorder = { 0x3FC, 0x3FC, 0x3FC, 0x3FC, 0x3FC, 0x3FC, 0x3FC, 0x3FC, 0x3FC },
			.scaleMOffset = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
			.scaleMGain = { 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF },
			.scaleMBorder = { 0x3FC, 0x3FC, 0x3FC, 0x3FC, 0x3FC, 0x3FC, 0x3FC, 0x3FC, 0x3FC },
			.gradationPOffset = { 0x1FC, 0x1FC, 0x1FC, 0x1FC, 0x1FC },
			.gradationPGain = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
			.gradationPDorder = { 0x1FC, 0x1FC, 0x1FC, 0x1FC },
			.gradationMOffset = { 0x1FC, 0x1FC, 0x1FC, 0x1FC, 0x1FC },
			.gradationMGain = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
			.gradationMBorder = { 0x1FC, 0x1FC, 0x1FC, 0x1FC },
			.levelClipPOffset = { 0x1FC, 0x1FC, 0x1FC },
			.levelClipPGain = { 0x7F, 0x7F, 0x7F },
			.levelClipPDorder = { 0x3FC, 0x3FC },
			.levelClipMOffset = { 0x1FC, 0x1FC, 0x1FC },
			.levelClipMGain = { 0x7F, 0x7F, 0x7F },
			.levelClipMBorder = { 0x3FC, 0x3FC },
		},
		[1] = {	// min
			.edgeEnable = 0,
			.gradationEnable = 0,
			.hpfK = { 0, -128, -128, -128, -128, -128 },
			.strength = 0,
			.coringPOffset = { 0, 0, 0, 0 },
			.coringPGain = { -128, -128, -128, -128 },
			.coringPDorder = { 0, 0, 0 },
			.coringMOffset = { 0, 0, 0, 0 },
			.coringMGain = { -128, -128, -128, -128 },
			.coringMBorder = { 0, 0, 0 },
			.scaleReductCoef = 0,
			.scalePOffset = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			.scalePGain = { -4096, -4096, -4096, -4096, -4096, -4096, -4096, -4096, -4096, -4096 },
			.scalePDorder = { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			.scaleMOffset = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			.scaleMGain = { -4096, -4096, -4096, -4096, -4096, -4096, -4096, -4096, -4096, -4096 },
			.scaleMBorder = { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			.gradationPOffset = { 0, 0, 0, 0, 0 },
			.gradationPGain = { -256, -256, -256, -256, -256 },
			.gradationPDorder = { 0, 0, 0, 0 },
			.gradationMOffset = { 0, 0, 0, 0, 0 },
			.gradationMGain = { -256, -256, -256, -256, -256 },
			.gradationMBorder = { 0, 0, 0, 0 },
			.levelClipPOffset = { 0, 0, 0 },
			.levelClipPGain = { -128, -128, -128 },
			.levelClipPDorder = { 0, 0 },
			.levelClipMOffset = { 0, 0, 0 },
			.levelClipMGain = { -128, -128, -128 },
			.levelClipMBorder = { 0, 0 },
		},
		[2] = {	// indvisual
			.edgeEnable = 1,
			.gradationEnable = 1,
			.hpfK = { 0x1FF, 0x1F, 0x2F, 0x3F, 0x4F, 0x5F },
			.strength = 1,
			.coringPOffset = { 0x10, 0x20, 0x30, 0x40 },
			.coringPGain = { 0x11, 0x22, 0x33, 0x44 },
			.coringPDorder = { 0x12, 0x23, 0x34 },
			.coringMOffset = { 0x50, 0x60, 0x70, 0x80 },
			.coringMGain = { 0x55, 0x66, 0x77, 0x88 },
			.coringMBorder = { 0x45, 0x56, 0x67 },
			.scaleReductCoef = 0x20,
			.scalePOffset = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0 },
			.scalePGain = { 0x100, 0x200, 0x300, 0x400, 0x500, 0x600, 0x700, 0x800, 0x900, 0xA00 },
			.scalePDorder = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 },
			.scaleMOffset = { 0x18, 0x28, 0x38, 0x48, 0x58, 0x68, 0x78, 0x88, 0x98, 0xA8 },
			.scaleMGain = { 0x111, 0x222, 0x333, 0x444, 0x555, 0x666, 0x777, 0x888, 0x999, 0xAAA },
			.scaleMBorder = { 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0 },
			.gradationPOffset = { 0x11, 0x22, 0x33, 0x44, 0x55 },
			.gradationPGain = { 0x10, 0x20, 0x30, 0x40, 0x50 },
			.gradationPDorder = { 0x1A, 0x2A, 0x3A, 0x4A },
			.gradationMOffset = { 0x66, 0x77, 0x88, 0x98, 0xA8 },
			.gradationMGain = { 0x20, 0x30, 0x40, 0x50, 0x60 },
			.gradationMBorder = { 0x70, 0x80, 0x90, 0xA0 },
			.levelClipPOffset = { 0x40, 0x50, 0x60 },
			.levelClipPGain = { 0x11, 0x22, 0x33 },
			.levelClipPDorder = { 0x48, 0x58 },
			.levelClipMOffset = { 0x10, 0x20, 0x30 },
			.levelClipMGain = { 0x44, 0x55, 0x66 },
			.levelClipMBorder = { 0x1F, 0x2F },
		},
	};
	UINT32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yPostResize1) / sizeof(r2yPostResize1[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl_post_resize_edge1(self->imR2yCtrl, pipeNo, &r2yPostResize1[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1en        = 0x%x\n",  ioR2yP1.yyw.ee1ctl.bit.ee1en ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tc        = 0x%x\n",  ioR2yP1.yyw.ee1ctl.bit.ee1tc ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk[0]   = 0x%lx\n", ioR2yP1.yyw.ee1hpfk.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk[1]   = 0x%lx\n", ioR2yP1.yyw.ee1hpfk.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk0     = 0x%x\n",  ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk1     = 0x%x\n",  ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk2     = 0x%x\n",  ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk3     = 0x%x\n",  ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk4     = 0x%x\n",  ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk5     = 0x%x\n",  ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1nrlv      = 0x%x\n",  ioR2yP1.yyw.ee1nrlv.bit.ee1nrlv ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpof0  = 0x%x\n",  ioR2yP1.yyw.ee1corpof.bit.ee1corpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpof1  = 0x%x\n",  ioR2yP1.yyw.ee1corpof.bit.ee1corpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpof2  = 0x%x\n",  ioR2yP1.yyw.ee1corpof.bit.ee1corpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpof3  = 0x%x\n",  ioR2yP1.yyw.ee1corpof.bit.ee1corpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpga    = 0x%lx\n", ioR2yP1.yyw.ee1corpga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpga0  = 0x%x\n",  ioR2yP1.yyw.ee1corpga.bit.ee1corpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpga1  = 0x%x\n",  ioR2yP1.yyw.ee1corpga.bit.ee1corpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpga2  = 0x%x\n",  ioR2yP1.yyw.ee1corpga.bit.ee1corpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpga3  = 0x%x\n",  ioR2yP1.yyw.ee1corpga.bit.ee1corpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpbd1  = 0x%x\n",  ioR2yP1.yyw.ee1corpbd.bit.ee1corpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpbd2  = 0x%x\n",  ioR2yP1.yyw.ee1corpbd.bit.ee1corpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpbd3  = 0x%x\n",  ioR2yP1.yyw.ee1corpbd.bit.ee1corpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormof0  = 0x%x\n",  ioR2yP1.yyw.ee1cormof.bit.ee1cormof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormof1  = 0x%x\n",  ioR2yP1.yyw.ee1cormof.bit.ee1cormof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormof2  = 0x%x\n",  ioR2yP1.yyw.ee1cormof.bit.ee1cormof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormof3  = 0x%x\n",  ioR2yP1.yyw.ee1cormof.bit.ee1cormof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormga    = 0x%lx\n", ioR2yP1.yyw.ee1cormga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormga0  = 0x%x\n",  ioR2yP1.yyw.ee1cormga.bit.ee1cormga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormga1  = 0x%x\n",  ioR2yP1.yyw.ee1cormga.bit.ee1cormga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormga2  = 0x%x\n",  ioR2yP1.yyw.ee1cormga.bit.ee1cormga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormga3  = 0x%x\n",  ioR2yP1.yyw.ee1cormga.bit.ee1cormga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormbd1  = 0x%x\n",  ioR2yP1.yyw.ee1cormbd.bit.ee1cormbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormbd2  = 0x%x\n",  ioR2yP1.yyw.ee1cormbd.bit.ee1cormbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormbd3  = 0x%x\n",  ioR2yP1.yyw.ee1cormbd.bit.ee1cormbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclsup    = 0x%x\n",  ioR2yP1.yyw.ee1sclsup.bit.ee1sclsup ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof0  = 0x%x\n",  ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof1  = 0x%x\n",  ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof2  = 0x%x\n",  ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof3  = 0x%x\n",  ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof4  = 0x%x\n",  ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof5  = 0x%x\n",  ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof6  = 0x%x\n",  ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof7  = 0x%x\n",  ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof8  = 0x%x\n",  ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof9  = 0x%x\n",  ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga[0] = 0x%lx\n", ioR2yP1.yyw.ee1sclpga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga[1] = 0x%lx\n", ioR2yP1.yyw.ee1sclpga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga[2] = 0x%lx\n", ioR2yP1.yyw.ee1sclpga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga[3] = 0x%lx\n", ioR2yP1.yyw.ee1sclpga.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga[4] = 0x%lx\n", ioR2yP1.yyw.ee1sclpga.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga0  = 0x%x\n",  ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga1  = 0x%x\n",  ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga2  = 0x%x\n",  ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga3  = 0x%x\n",  ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga4  = 0x%x\n",  ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga5  = 0x%x\n",  ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga6  = 0x%x\n",  ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga7  = 0x%x\n",  ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga8  = 0x%x\n",  ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga9  = 0x%x\n",  ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd1  = 0x%x\n",  ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd2  = 0x%x\n",  ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd3  = 0x%x\n",  ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd4  = 0x%x\n",  ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd5  = 0x%x\n",  ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd6  = 0x%x\n",  ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd7  = 0x%x\n",  ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd8  = 0x%x\n",  ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd9  = 0x%x\n",  ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof0  = 0x%x\n",  ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof1  = 0x%x\n",  ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof2  = 0x%x\n",  ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof3  = 0x%x\n",  ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof4  = 0x%x\n",  ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof5  = 0x%x\n",  ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof6  = 0x%x\n",  ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof7  = 0x%x\n",  ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof8  = 0x%x\n",  ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof9  = 0x%x\n",  ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga[0] = 0x%lx\n", ioR2yP1.yyw.ee1sclmga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga[1] = 0x%lx\n", ioR2yP1.yyw.ee1sclmga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga[2] = 0x%lx\n", ioR2yP1.yyw.ee1sclmga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga[3] = 0x%lx\n", ioR2yP1.yyw.ee1sclmga.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga[4] = 0x%lx\n", ioR2yP1.yyw.ee1sclmga.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga0  = 0x%x\n",  ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga1  = 0x%x\n",  ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga2  = 0x%x\n",  ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga3  = 0x%x\n",  ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga4  = 0x%x\n",  ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga5  = 0x%x\n",  ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga6  = 0x%x\n",  ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga7  = 0x%x\n",  ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga8  = 0x%x\n",  ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga9  = 0x%x\n",  ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd1  = 0x%x\n",  ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd2  = 0x%x\n",  ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd3  = 0x%x\n",  ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd4  = 0x%x\n",  ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd5  = 0x%x\n",  ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd6  = 0x%x\n",  ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd7  = 0x%x\n",  ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd8  = 0x%x\n",  ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd9  = 0x%x\n",  ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpof0  = 0x%x\n",  ioR2yP1.yyw.ee1tonpof.bit.ee1tonpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpof1  = 0x%x\n",  ioR2yP1.yyw.ee1tonpof.bit.ee1tonpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpof2  = 0x%x\n",  ioR2yP1.yyw.ee1tonpof.bit.ee1tonpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpof3  = 0x%x\n",  ioR2yP1.yyw.ee1tonpof.bit.ee1tonpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpof4  = 0x%x\n",  ioR2yP1.yyw.ee1tonpof.bit.ee1tonpof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga[0] = 0x%lx\n", ioR2yP1.yyw.ee1tonpga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga[1] = 0x%lx\n", ioR2yP1.yyw.ee1tonpga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga[2] = 0x%lx\n", ioR2yP1.yyw.ee1tonpga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga0  = 0x%x\n",  ioR2yP1.yyw.ee1tonpga.bit.ee1tonpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga1  = 0x%x\n",  ioR2yP1.yyw.ee1tonpga.bit.ee1tonpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga2  = 0x%x\n",  ioR2yP1.yyw.ee1tonpga.bit.ee1tonpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga3  = 0x%x\n",  ioR2yP1.yyw.ee1tonpga.bit.ee1tonpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga4  = 0x%x\n",  ioR2yP1.yyw.ee1tonpga.bit.ee1tonpga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpbd1  = 0x%x\n",  ioR2yP1.yyw.ee1tonpbd.bit.ee1tonpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpbd2  = 0x%x\n",  ioR2yP1.yyw.ee1tonpbd.bit.ee1tonpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpbd3  = 0x%x\n",  ioR2yP1.yyw.ee1tonpbd.bit.ee1tonpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpbd4  = 0x%x\n",  ioR2yP1.yyw.ee1tonpbd.bit.ee1tonpbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmof0  = 0x%x\n",  ioR2yP1.yyw.ee1tonmof.bit.ee1tonmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmof1  = 0x%x\n",  ioR2yP1.yyw.ee1tonmof.bit.ee1tonmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmof2  = 0x%x\n",  ioR2yP1.yyw.ee1tonmof.bit.ee1tonmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmof3  = 0x%x\n",  ioR2yP1.yyw.ee1tonmof.bit.ee1tonmof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmof4  = 0x%x\n",  ioR2yP1.yyw.ee1tonmof.bit.ee1tonmof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga[0] = 0x%lx\n", ioR2yP1.yyw.ee1tonmga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga[1] = 0x%lx\n", ioR2yP1.yyw.ee1tonmga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga[2] = 0x%lx\n", ioR2yP1.yyw.ee1tonmga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga0  = 0x%x\n",  ioR2yP1.yyw.ee1tonmga.bit.ee1tonmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga1  = 0x%x\n",  ioR2yP1.yyw.ee1tonmga.bit.ee1tonmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga2  = 0x%x\n",  ioR2yP1.yyw.ee1tonmga.bit.ee1tonmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga3  = 0x%x\n",  ioR2yP1.yyw.ee1tonmga.bit.ee1tonmga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga4  = 0x%x\n",  ioR2yP1.yyw.ee1tonmga.bit.ee1tonmga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmbd1  = 0x%x\n",  ioR2yP1.yyw.ee1tonmbd.bit.ee1tonmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmbd2  = 0x%x\n",  ioR2yP1.yyw.ee1tonmbd.bit.ee1tonmbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmbd3  = 0x%x\n",  ioR2yP1.yyw.ee1tonmbd.bit.ee1tonmbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmbd4  = 0x%x\n",  ioR2yP1.yyw.ee1tonmbd.bit.ee1tonmbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppof0  = 0x%x\n",  ioR2yP1.yyw.ee1clppof.bit.ee1clppof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppof1  = 0x%x\n",  ioR2yP1.yyw.ee1clppof.bit.ee1clppof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppof2  = 0x%x\n",  ioR2yP1.yyw.ee1clppof.bit.ee1clppof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppga    = 0x%lx\n", ioR2yP1.yyw.ee1clppga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppga0  = 0x%x\n",  ioR2yP1.yyw.ee1clppga.bit.ee1clppga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppga1  = 0x%x\n",  ioR2yP1.yyw.ee1clppga.bit.ee1clppga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppga2  = 0x%x\n",  ioR2yP1.yyw.ee1clppga.bit.ee1clppga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppbd1  = 0x%x\n",  ioR2yP1.yyw.ee1clppbd.bit.ee1clppbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppbd2  = 0x%x\n",  ioR2yP1.yyw.ee1clppbd.bit.ee1clppbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmof0  = 0x%x\n",  ioR2yP1.yyw.ee1clpmof.bit.ee1clpmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmof1  = 0x%x\n",  ioR2yP1.yyw.ee1clpmof.bit.ee1clpmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmof2  = 0x%x\n",  ioR2yP1.yyw.ee1clpmof.bit.ee1clpmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmga    = 0x%lx\n", ioR2yP1.yyw.ee1clpmga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmga0  = 0x%x\n",  ioR2yP1.yyw.ee1clpmga.bit.ee1clpmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmga1  = 0x%x\n",  ioR2yP1.yyw.ee1clpmga.bit.ee1clpmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmga2  = 0x%x\n",  ioR2yP1.yyw.ee1clpmga.bit.ee1clpmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmbd1  = 0x%x\n",  ioR2yP1.yyw.ee1clpmbd.bit.ee1clpmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmbd2  = 0x%x\n",  ioR2yP1.yyw.ee1clpmbd.bit.ee1clpmbd2 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1en        = 0x%x\n",  ioR2yP2.yyw.ee1ctl.bit.ee1en ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tc        = 0x%x\n",  ioR2yP2.yyw.ee1ctl.bit.ee1tc ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk[0]   = 0x%lx\n", ioR2yP2.yyw.ee1hpfk.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk[1]   = 0x%lx\n", ioR2yP2.yyw.ee1hpfk.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk0     = 0x%x\n",  ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk1     = 0x%x\n",  ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk2     = 0x%x\n",  ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk3     = 0x%x\n",  ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk4     = 0x%x\n",  ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1hpfk5     = 0x%x\n",  ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1nrlv      = 0x%x\n",  ioR2yP2.yyw.ee1nrlv.bit.ee1nrlv ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpof0  = 0x%x\n",  ioR2yP2.yyw.ee1corpof.bit.ee1corpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpof1  = 0x%x\n",  ioR2yP2.yyw.ee1corpof.bit.ee1corpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpof2  = 0x%x\n",  ioR2yP2.yyw.ee1corpof.bit.ee1corpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpof3  = 0x%x\n",  ioR2yP2.yyw.ee1corpof.bit.ee1corpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpga    = 0x%lx\n", ioR2yP2.yyw.ee1corpga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpga0  = 0x%x\n",  ioR2yP2.yyw.ee1corpga.bit.ee1corpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpga1  = 0x%x\n",  ioR2yP2.yyw.ee1corpga.bit.ee1corpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpga2  = 0x%x\n",  ioR2yP2.yyw.ee1corpga.bit.ee1corpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpga3  = 0x%x\n",  ioR2yP2.yyw.ee1corpga.bit.ee1corpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpbd1  = 0x%x\n",  ioR2yP2.yyw.ee1corpbd.bit.ee1corpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpbd2  = 0x%x\n",  ioR2yP2.yyw.ee1corpbd.bit.ee1corpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1corpbd3  = 0x%x\n",  ioR2yP2.yyw.ee1corpbd.bit.ee1corpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormof0  = 0x%x\n",  ioR2yP2.yyw.ee1cormof.bit.ee1cormof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormof1  = 0x%x\n",  ioR2yP2.yyw.ee1cormof.bit.ee1cormof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormof2  = 0x%x\n",  ioR2yP2.yyw.ee1cormof.bit.ee1cormof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormof3  = 0x%x\n",  ioR2yP2.yyw.ee1cormof.bit.ee1cormof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormga    = 0x%lx\n", ioR2yP2.yyw.ee1cormga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormga0  = 0x%x\n",  ioR2yP2.yyw.ee1cormga.bit.ee1cormga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormga1  = 0x%x\n",  ioR2yP2.yyw.ee1cormga.bit.ee1cormga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormga2  = 0x%x\n",  ioR2yP2.yyw.ee1cormga.bit.ee1cormga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormga3  = 0x%x\n",  ioR2yP2.yyw.ee1cormga.bit.ee1cormga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormbd1  = 0x%x\n",  ioR2yP2.yyw.ee1cormbd.bit.ee1cormbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormbd2  = 0x%x\n",  ioR2yP2.yyw.ee1cormbd.bit.ee1cormbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1cormbd3  = 0x%x\n",  ioR2yP2.yyw.ee1cormbd.bit.ee1cormbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclsup    = 0x%x\n",  ioR2yP2.yyw.ee1sclsup.bit.ee1sclsup ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof0  = 0x%x\n",  ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof1  = 0x%x\n",  ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof2  = 0x%x\n",  ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof3  = 0x%x\n",  ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof4  = 0x%x\n",  ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof5  = 0x%x\n",  ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof6  = 0x%x\n",  ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof7  = 0x%x\n",  ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof8  = 0x%x\n",  ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpof9  = 0x%x\n",  ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga[0] = 0x%lx\n", ioR2yP2.yyw.ee1sclpga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga[1] = 0x%lx\n", ioR2yP2.yyw.ee1sclpga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga[2] = 0x%lx\n", ioR2yP2.yyw.ee1sclpga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga[3] = 0x%lx\n", ioR2yP2.yyw.ee1sclpga.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga[4] = 0x%lx\n", ioR2yP2.yyw.ee1sclpga.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga0  = 0x%x\n",  ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga1  = 0x%x\n",  ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga2  = 0x%x\n",  ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga3  = 0x%x\n",  ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga4  = 0x%x\n",  ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga5  = 0x%x\n",  ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga6  = 0x%x\n",  ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga7  = 0x%x\n",  ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga8  = 0x%x\n",  ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpga9  = 0x%x\n",  ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd1  = 0x%x\n",  ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd2  = 0x%x\n",  ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd3  = 0x%x\n",  ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd4  = 0x%x\n",  ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd5  = 0x%x\n",  ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd6  = 0x%x\n",  ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd7  = 0x%x\n",  ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd8  = 0x%x\n",  ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclpbd9  = 0x%x\n",  ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof0  = 0x%x\n",  ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof1  = 0x%x\n",  ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof2  = 0x%x\n",  ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof3  = 0x%x\n",  ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof4  = 0x%x\n",  ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof5  = 0x%x\n",  ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof6  = 0x%x\n",  ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof7  = 0x%x\n",  ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof8  = 0x%x\n",  ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmof9  = 0x%x\n",  ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga[0] = 0x%lx\n", ioR2yP2.yyw.ee1sclmga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga[1] = 0x%lx\n", ioR2yP2.yyw.ee1sclmga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga[2] = 0x%lx\n", ioR2yP2.yyw.ee1sclmga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga[3] = 0x%lx\n", ioR2yP2.yyw.ee1sclmga.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga[4] = 0x%lx\n", ioR2yP2.yyw.ee1sclmga.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga0  = 0x%x\n",  ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga1  = 0x%x\n",  ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga2  = 0x%x\n",  ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga3  = 0x%x\n",  ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga4  = 0x%x\n",  ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga5  = 0x%x\n",  ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga6  = 0x%x\n",  ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga7  = 0x%x\n",  ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga8  = 0x%x\n",  ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmga9  = 0x%x\n",  ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd1  = 0x%x\n",  ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd2  = 0x%x\n",  ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd3  = 0x%x\n",  ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd4  = 0x%x\n",  ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd5  = 0x%x\n",  ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd6  = 0x%x\n",  ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd7  = 0x%x\n",  ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd8  = 0x%x\n",  ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1sclmbd9  = 0x%x\n",  ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpof0  = 0x%x\n",  ioR2yP2.yyw.ee1tonpof.bit.ee1tonpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpof1  = 0x%x\n",  ioR2yP2.yyw.ee1tonpof.bit.ee1tonpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpof2  = 0x%x\n",  ioR2yP2.yyw.ee1tonpof.bit.ee1tonpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpof3  = 0x%x\n",  ioR2yP2.yyw.ee1tonpof.bit.ee1tonpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpof4  = 0x%x\n",  ioR2yP2.yyw.ee1tonpof.bit.ee1tonpof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga[0] = 0x%lx\n", ioR2yP2.yyw.ee1tonpga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga[1] = 0x%lx\n", ioR2yP2.yyw.ee1tonpga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga[2] = 0x%lx\n", ioR2yP2.yyw.ee1tonpga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga0  = 0x%x\n",  ioR2yP2.yyw.ee1tonpga.bit.ee1tonpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga1  = 0x%x\n",  ioR2yP2.yyw.ee1tonpga.bit.ee1tonpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga2  = 0x%x\n",  ioR2yP2.yyw.ee1tonpga.bit.ee1tonpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga3  = 0x%x\n",  ioR2yP2.yyw.ee1tonpga.bit.ee1tonpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpga4  = 0x%x\n",  ioR2yP2.yyw.ee1tonpga.bit.ee1tonpga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpbd1  = 0x%x\n",  ioR2yP2.yyw.ee1tonpbd.bit.ee1tonpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpbd2  = 0x%x\n",  ioR2yP2.yyw.ee1tonpbd.bit.ee1tonpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpbd3  = 0x%x\n",  ioR2yP2.yyw.ee1tonpbd.bit.ee1tonpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonpbd4  = 0x%x\n",  ioR2yP2.yyw.ee1tonpbd.bit.ee1tonpbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmof0  = 0x%x\n",  ioR2yP2.yyw.ee1tonmof.bit.ee1tonmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmof1  = 0x%x\n",  ioR2yP2.yyw.ee1tonmof.bit.ee1tonmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmof2  = 0x%x\n",  ioR2yP2.yyw.ee1tonmof.bit.ee1tonmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmof3  = 0x%x\n",  ioR2yP2.yyw.ee1tonmof.bit.ee1tonmof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmof4  = 0x%x\n",  ioR2yP2.yyw.ee1tonmof.bit.ee1tonmof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga[0] = 0x%lx\n", ioR2yP2.yyw.ee1tonmga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga[1] = 0x%lx\n", ioR2yP2.yyw.ee1tonmga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga[2] = 0x%lx\n", ioR2yP2.yyw.ee1tonmga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga0  = 0x%x\n",  ioR2yP2.yyw.ee1tonmga.bit.ee1tonmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga1  = 0x%x\n",  ioR2yP2.yyw.ee1tonmga.bit.ee1tonmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga2  = 0x%x\n",  ioR2yP2.yyw.ee1tonmga.bit.ee1tonmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga3  = 0x%x\n",  ioR2yP2.yyw.ee1tonmga.bit.ee1tonmga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmga4  = 0x%x\n",  ioR2yP2.yyw.ee1tonmga.bit.ee1tonmga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmbd1  = 0x%x\n",  ioR2yP2.yyw.ee1tonmbd.bit.ee1tonmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmbd2  = 0x%x\n",  ioR2yP2.yyw.ee1tonmbd.bit.ee1tonmbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmbd3  = 0x%x\n",  ioR2yP2.yyw.ee1tonmbd.bit.ee1tonmbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1tonmbd4  = 0x%x\n",  ioR2yP2.yyw.ee1tonmbd.bit.ee1tonmbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppof0  = 0x%x\n",  ioR2yP2.yyw.ee1clppof.bit.ee1clppof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppof1  = 0x%x\n",  ioR2yP2.yyw.ee1clppof.bit.ee1clppof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppof2  = 0x%x\n",  ioR2yP2.yyw.ee1clppof.bit.ee1clppof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppga    = 0x%lx\n", ioR2yP2.yyw.ee1clppga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppga0  = 0x%x\n",  ioR2yP2.yyw.ee1clppga.bit.ee1clppga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppga1  = 0x%x\n",  ioR2yP2.yyw.ee1clppga.bit.ee1clppga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppga2  = 0x%x\n",  ioR2yP2.yyw.ee1clppga.bit.ee1clppga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppbd1  = 0x%x\n",  ioR2yP2.yyw.ee1clppbd.bit.ee1clppbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clppbd2  = 0x%x\n",  ioR2yP2.yyw.ee1clppbd.bit.ee1clppbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmof0  = 0x%x\n",  ioR2yP2.yyw.ee1clpmof.bit.ee1clpmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmof1  = 0x%x\n",  ioR2yP2.yyw.ee1clpmof.bit.ee1clpmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmof2  = 0x%x\n",  ioR2yP2.yyw.ee1clpmof.bit.ee1clpmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmga    = 0x%lx\n", ioR2yP2.yyw.ee1clpmga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmga0  = 0x%x\n",  ioR2yP2.yyw.ee1clpmga.bit.ee1clpmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmga1  = 0x%x\n",  ioR2yP2.yyw.ee1clpmga.bit.ee1clpmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmga2  = 0x%x\n",  ioR2yP2.yyw.ee1clpmga.bit.ee1clpmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmbd1  = 0x%x\n",  ioR2yP2.yyw.ee1clpmbd.bit.ee1clpmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee1clpmbd2  = 0x%x\n",  ioR2yP2.yyw.ee1clpmbd.bit.ee1clpmbd2 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_47: "
INT32 ct_im_r2y_classf_1_47( CtImR2yClassf *self,UCHAR pipeNo )
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y147 {
		USHORT srcTbl[D_IM_R2Y_TABLE_MAX_RGB_DEKNEE];
	};
	struct TCtImR2y147 tblBody;
	struct TCtImR2y147* tbl = &tblBody;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y147 {
		USHORT srcTbl[D_IM_R2Y_TABLE_MAX_RGB_DEKNEE];
	}* tbl = (struct TCtImR2y147*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	UINT32				loopcnt;
	ER2yDknRgbtbl	loopcnt2;
	UINT32				loopcnt3;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	const char errmsg[] = "%u[%u] unmatch\n";

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < 3; loopcnt++ ) {
		switch( loopcnt ) {
			default:	// max
//			case 0:
				for( loopcnt3 = 0; loopcnt3 < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loopcnt3++ ) {
					tbl->srcTbl[loopcnt3] = 0xFFF;
				}
				break;
			case 1:	// min
				for( loopcnt3 = 0; loopcnt3 < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loopcnt3++ ) {
					tbl->srcTbl[loopcnt3] = 0;
				}
				break;
			case 2:	// indvisual
				for( loopcnt3 = 0; loopcnt3 < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loopcnt3++ ) {
					tbl->srcTbl[loopcnt3] = 0xFFF - loopcnt3;
				}
				break;
		}

		for( loopcnt2 = (ER2yDknRgbtbl)0; loopcnt2 < E_R2Y_DKN_RGBTBL_MAX; loopcnt2++ ) {
			Ddim_Print(( "** %u - %u\n", loopcnt, loopcnt2 ));


#ifdef CO_MSG_PRINT_ON
			ercd = im_r2y3_set_rgb_deknee_table(self->imR2y3, pipeNo, loopcnt2, tbl->srcTbl );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
			Im_R2Y_On_Hclk( pipeNo );
			im_r2y3_set_rgb_deknee_access_enable(self->imR2y3, pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
			switch( loopcnt2 ) {
				default:
//				case E_R2Y_DKN_RGBTBL_R:
					if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loopcnt3++ ) {
							if( ioR2yTblP1.dkntblr.hword[loopcnt3] != tbl->srcTbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loopcnt3++ ) {
							if( ioR2yTblP2.dkntblr.hword[loopcnt3] != tbl->srcTbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					break;
				case E_R2Y_DKN_RGBTBL_G:
					if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loopcnt3++ ) {
							if( ioR2yTblP1.DKNTBLG.hword[loopcnt3] != tbl->srcTbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loopcnt3++ ) {
							if( ioR2yTblP2.DKNTBLG.hword[loopcnt3] != tbl->srcTbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					break;
				case E_R2Y_DKN_RGBTBL_B:
					if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loopcnt3++ ) {
							if( ioR2yTblP1.DKNTBLB.hword[loopcnt3] != tbl->srcTbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loopcnt3++ ) {
							if( ioR2yTblP2.DKNTBLB.hword[loopcnt3] != tbl->srcTbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					break;
			}
			im_r2y3_set_rgb_deknee_access_enable(self->imR2y3, pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
			Im_R2Y_Off_Hclk( pipeNo );
#else
			im_r2y3_set_rgb_deknee_table(self->imR2y3, pipeNo, loopcnt2, tbl->srcTbl );
#endif
		}
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_48: "
INT32 ct_im_r2y_classf_1_48(CtImR2yClassf *self, UCHAR pipeNo )
{
	UCHAR accessEnable[] = {
		[0] = 1,	// max
		[1] = 0,	// min
	};
	UINT32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(accessEnable) / sizeof(accessEnable[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y3_set_rgb_deknee_access_enable(self->imR2y3, pipeNo, accessEnable[loopcnt], D_IM_R2Y_WAIT_ON );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "YyraenRgbDeknee = %u\n", ioR2yP1.R2yCmn.ramaen.bit.YyraenRgbDeknee ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "YyraenRgbDeknee = %u\n", ioR2yP2.R2yCmn.ramaen.bit.YyraenRgbDeknee ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_49: "
INT32 ct_im_r2y_classf_1_49(CtImR2yClassf *self, UCHAR pipeNo )
{
	TImR2yOfs ofs[] = {
		[0] = {	// max
			.r = 0x1FF,
			.g = 0x1FF,
			.b = 0x1FF,
		},
		[1] = {	// min
			.r = -512,
			.g = -512,
			.b = -512,
		},
		[2] = {	// indvisual
			.r = 10,
			.g = 20,
			.b = 30,
		},
	};
	UINT32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(ofs) / sizeof(ofs[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl_set_offset(self->imR2yCtrl, pipeNo, &ofs[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ofst[0] = 0x%lx\n", ioR2yP1.fR2y.ofg.ofst.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ofst[1] = 0x%lx\n", ioR2yP1.fR2y.ofg.ofst.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ofstr   = 0x%x\n",  ioR2yP1.fR2y.ofg.ofst.bit.ofstr ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ofstg   = 0x%x\n",  ioR2yP1.fR2y.ofg.ofst.bit.ofstg ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ofstb   = 0x%x\n",  ioR2yP1.fR2y.ofg.ofst.bit.ofstb ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ofst[0] = 0x%lx\n", ioR2yP2.fR2y.ofg.ofst.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ofst[1] = 0x%lx\n", ioR2yP2.fR2y.ofg.ofst.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ofstr   = 0x%x\n",  ioR2yP2.fR2y.ofg.ofst.bit.ofstr ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ofstg   = 0x%x\n",  ioR2yP2.fR2y.ofg.ofst.bit.ofstg ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ofstb   = 0x%x\n",  ioR2yP2.fR2y.ofg.ofst.bit.ofstb ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_50: "
INT32 ct_im_r2y_classf_1_50( CtImR2yClassf *self,UCHAR pipeNo )
{
	TImR2yRgbColor r2yRgbColor[] = {
		[0] = {	// max
			.R = 0x7FF,
			.G = 0x7FF,
			.B = 0x7FF,
		},
		[1] = {	// min
			.R = 0,
			.G = 0,
			.B = 0,
		},
		[2] = {	// indvisual
			.R = 1,
			.G = 2,
			.B = 3,
		}
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < (sizeof(r2yRgbColor) / sizeof(r2yRgbColor[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl2_set_wb_gain(self->imR2yCtrl2, pipeNo, &r2yRgbColor[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wbgar = 0x%x\n", ioR2yP1.fR2y.ofg.wbgar.bit.wbgar ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wbgag = 0x%x\n", ioR2yP1.fR2y.ofg.wbgar.bit.wbgag ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wbgab = 0x%x\n", ioR2yP1.fR2y.ofg.wbgar.bit.wbgab ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wbgar = 0x%x\n", ioR2yP2.fR2y.ofg.wbgar.bit.wbgar ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wbgag = 0x%x\n", ioR2yP2.fR2y.ofg.wbgar.bit.wbgag ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wbgab = 0x%x\n", ioR2yP2.fR2y.ofg.wbgar.bit.wbgab ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_51: "
INT32 ct_im_r2y_classf_1_51( CtImR2yClassf *self,UCHAR pipeNo )
{
	TImR2yRgbColor r2yRgbColor[] = {
		[0] = {	// max
			.r = 0xFFF,
			.g = 0xFFF,
			.b = 0xFFF,
		},
		[1] = {	// min
			.r = 0,
			.g = 0,
			.b = 0,
		},
		[2] = {	// indvisual
			.r = 1,
			.g = 2,
			.b = 3,
		}
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yRgbColor) / sizeof(r2yRgbColor[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl2_set_wb_clip_level(self->imR2yCtrl2, pipeNo, &r2yRgbColor[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wblvr = 0x%x\n", ioR2yP1.fR2y.ofg.wblv.bit.wblvr ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wblvg = 0x%x\n", ioR2yP1.fR2y.ofg.wblv.bit.wblvg ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wblvb = 0x%x\n", ioR2yP1.fR2y.ofg.wblv.bit.wblvb ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wblvr = 0x%x\n", ioR2yP2.fR2y.ofg.wblv.bit.wblvr ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wblvg = 0x%x\n", ioR2yP2.fR2y.ofg.wblv.bit.wblvg ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "wblvb = 0x%x\n", ioR2yP2.fR2y.ofg.wblv.bit.wblvb ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_52: "
INT32 ct_im_r2y_classf_1_52( CtImR2yClassf *self,UCHAR pipeNo )
{
	TImR2yCtrlCc0 r2yCtrlCc[] = {
		[0] = {	// max
			.posiDec = 3,
			.ccMatrix = {
				{ 0x7FF, 0x7FF, 0x7FF },
				{ 0x7FF, 0x7FF, 0x7FF },
				{ 0x7FF, 0x7FF, 0x7FF },
			},
			.cybof = {
				0x7FF, 0x7FF, 0x7FF,
			},
			.cybga = {
				0xFF, 0xFF, 0xFF,
			},
			.cybbd = {
				0xFFF, 0xFFF,
			},
			.cyc = {
				0xFF, 0xFF, 0xFF,
			},
		},
		[1] = {	// min
			.posiDec = 0,
			.ccMatrix = {
				{ -0x800, -0x800, -0x800 },
				{ -0x800, -0x800, -0x800 },
				{ -0x800, -0x800, -0x800 },
			},
			.cybof = {
				0, 0, 0,
			},
			.cybga = {
				-0x100, -0x100, -0x100,
			},
			.cybbd = {
				0, 0,
			},
			.cyc = {
				0, 0, 0,
			},
		},
		[2] = {	// indvisual
			.posiDec = 0,
			.ccMatrix = {
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 },
			},
			.cybof = {
				10, 11, 12,
			},
			.cybga = {
				13, 14, 15,
			},
			.cybbd = {
				16, 17,
			},
			.cyc = {
				18, 19, 20,
			},
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));



	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlCc) / sizeof(r2yCtrlCc[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl2_cc0_matrix(self->imR2yCtrl2, pipeNo, &r2yCtrlCc[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0dp     = %u\n",    ioR2yP1.fR2y.cca0.cc0ctl.bit.cc0dp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[0]   = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0k.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[1]   = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0k.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[2]   = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0k.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[3]   = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0k.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[4]   = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0k.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k00  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k00 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k01  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k01 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k02  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k02 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k10  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k10 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k11  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k11 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k12  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k12 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k20  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k20 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k21  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k21 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k22  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k22 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_0  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0ybof.bit.cc0ybof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_1  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0ybof.bit.cc0ybof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_2  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0ybof.bit.cc0ybof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA[0] = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0ybga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA[1] = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0ybga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_0  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0ybga.bit.cc0ybga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_1  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0ybga.bit.cc0ybga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_2  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0ybga.bit.cc0ybga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBBD_1  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0ybbd.bit.cc0ybbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBBD_2  = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0ybbd.bit.cc0ybbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ccyc0    = 0x%x\n",  ioR2yP1.fR2y.cca0.CCYC.bit.ccyc00 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCyc1    = 0x%x\n",  ioR2yP1.fR2y.cca0.CCYC.bit.ccyc01 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCyc2    = 0x%x\n",  ioR2yP1.fR2y.cca0.CCYC.bit.ccyc02 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0dp     = %u\n",    ioR2yP2.fR2y.cca0.cc0ctl.bit.cc0dp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[0]   = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0k.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[1]   = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0k.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[2]   = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0k.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[3]   = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0k.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[4]   = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0k.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k00  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k00 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k01  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k01 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k02  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k02 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k10  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k10 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k11  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k11 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k12  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k12 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k20  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k20 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k21  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k21 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k22  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k22 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_0  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0ybof.bit.cc0ybof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_1  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0ybof.bit.cc0ybof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_2  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0ybof.bit.cc0ybof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA[0] = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0ybga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA[1] = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0ybga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_0  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0ybga.bit.cc0ybga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_1  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0ybga.bit.cc0ybga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_2  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0ybga.bit.cc0ybga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBBD_1  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0ybbd.bit.cc0ybbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBBD_2  = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0ybbd.bit.cc0ybbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ccyc0    = 0x%x\n",  ioR2yP2.fR2y.cca0.CCYC.bit.ccyc00 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCyc1    = 0x%x\n",  ioR2yP2.fR2y.cca0.CCYC.bit.ccyc01 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCyc2    = 0x%x\n",  ioR2yP2.fR2y.cca0.CCYC.bit.ccyc02 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_53: "
INT32 ct_im_r2y_classf_1_53( CtImR2yClassf *self,UCHAR pipeNo )
{
	SHORT r2yCc0k[3][9] = {
		{	// max
			0x7FF, 0x7FF, 0x7FF, 0x7FF, 0x7FF, 0x7FF, 0x7FF, 0x7FF, 0x7FF,
		},
		{	// min
			-0x800, -0x800, -0x800, -0x800, -0x800, -0x800, -0x800, -0x800, -0x800,
		},
		{	// indvisual
			1, 2, 3, 4, 5, 6, 7, 8, 9,
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yCc0k) / sizeof(r2yCc0k[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl2_set_cc0_matrix_coefficient(self->imR2yCtrl2, pipeNo, &r2yCc0k[loopcnt][0] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[0]  = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0k.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[1]  = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0k.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[2]  = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0k.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[3]  = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0k.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[4]  = 0x%lx\n", ioR2yP1.fR2y.cca0.cc0k.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k00 = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k00 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k01 = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k01 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k02 = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k02 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k10 = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k10 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k11 = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k11 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k12 = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k12 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k20 = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k20 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k21 = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k21 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k22 = 0x%x\n",  ioR2yP1.fR2y.cca0.cc0k.bit.cc0k22 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[0]  = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0k.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[1]  = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0k.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[2]  = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0k.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[3]  = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0k.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k[4]  = 0x%lx\n", ioR2yP2.fR2y.cca0.cc0k.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k00 = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k00 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k01 = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k01 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k02 = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k02 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k10 = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k10 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k11 = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k11 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k12 = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k12 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k20 = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k20 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k21 = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k21 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc0k22 = 0x%x\n",  ioR2yP2.fR2y.cca0.cc0k.bit.cc0k22 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

CtImR2yClassf* ct_im_r2y_classf_new(void)
{
	CtImR2yClassf* self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSF, sizeof(CtImR2yClassfPrivate));

	return self;
}

CtImR2yClassf* ct_im_r2y_classf_get(void)
{
	static CtImR2yClassf* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSF, sizeof(CtImR2yClassfPrivate));
	}

	return self;
}
