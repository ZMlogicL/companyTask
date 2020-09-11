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
}

static void ct_im_r2y_classf_destructor(CtImR2yClassf *self)
{
	CtImR2yClassfPrivate *priv = CT_IM_R2Y_CLASSF_GET_PRIVATE(self);
}



#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_46: "
INT32 ct_im_r2y_classf_1_46( UCHAR pipeNo )
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
		ercd = Im_R2Y_Ctrl_PostResizeEdge1( pipeNo, &r2yPostResize1[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1EN        = 0x%x\n",  ioR2yP1.yyw.EE1CTL.bit.EE1EN ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TC        = 0x%x\n",  ioR2yP1.yyw.EE1CTL.bit.EE1TC ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK[0]   = 0x%lx\n", ioR2yP1.yyw.EE1HPFK.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK[1]   = 0x%lx\n", ioR2yP1.yyw.EE1HPFK.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK0     = 0x%x\n",  ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK1     = 0x%x\n",  ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK2     = 0x%x\n",  ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK3     = 0x%x\n",  ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK4     = 0x%x\n",  ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK5     = 0x%x\n",  ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1NRLV      = 0x%x\n",  ioR2yP1.yyw.EE1NRLV.bit.EE1NRLV ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPOF_0  = 0x%x\n",  ioR2yP1.yyw.EE1CORPOF.bit.EE1CORPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPOF_1  = 0x%x\n",  ioR2yP1.yyw.EE1CORPOF.bit.EE1CORPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPOF_2  = 0x%x\n",  ioR2yP1.yyw.EE1CORPOF.bit.EE1CORPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPOF_3  = 0x%x\n",  ioR2yP1.yyw.EE1CORPOF.bit.EE1CORPOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPGA    = 0x%lx\n", ioR2yP1.yyw.EE1CORPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPGA_0  = 0x%x\n",  ioR2yP1.yyw.EE1CORPGA.bit.EE1CORPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPGA_1  = 0x%x\n",  ioR2yP1.yyw.EE1CORPGA.bit.EE1CORPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPGA_2  = 0x%x\n",  ioR2yP1.yyw.EE1CORPGA.bit.EE1CORPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPGA_3  = 0x%x\n",  ioR2yP1.yyw.EE1CORPGA.bit.EE1CORPGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPBD_1  = 0x%x\n",  ioR2yP1.yyw.EE1CORPBD.bit.EE1CORPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPBD_2  = 0x%x\n",  ioR2yP1.yyw.EE1CORPBD.bit.EE1CORPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPBD_3  = 0x%x\n",  ioR2yP1.yyw.EE1CORPBD.bit.EE1CORPBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMOF_0  = 0x%x\n",  ioR2yP1.yyw.EE1CORMOF.bit.EE1CORMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMOF_1  = 0x%x\n",  ioR2yP1.yyw.EE1CORMOF.bit.EE1CORMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMOF_2  = 0x%x\n",  ioR2yP1.yyw.EE1CORMOF.bit.EE1CORMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMOF_3  = 0x%x\n",  ioR2yP1.yyw.EE1CORMOF.bit.EE1CORMOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMGA    = 0x%lx\n", ioR2yP1.yyw.EE1CORMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMGA_0  = 0x%x\n",  ioR2yP1.yyw.EE1CORMGA.bit.EE1CORMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMGA_1  = 0x%x\n",  ioR2yP1.yyw.EE1CORMGA.bit.EE1CORMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMGA_2  = 0x%x\n",  ioR2yP1.yyw.EE1CORMGA.bit.EE1CORMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMGA_3  = 0x%x\n",  ioR2yP1.yyw.EE1CORMGA.bit.EE1CORMGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMBD_1  = 0x%x\n",  ioR2yP1.yyw.EE1CORMBD.bit.EE1CORMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMBD_2  = 0x%x\n",  ioR2yP1.yyw.EE1CORMBD.bit.EE1CORMBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMBD_3  = 0x%x\n",  ioR2yP1.yyw.EE1CORMBD.bit.EE1CORMBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLSUP    = 0x%x\n",  ioR2yP1.yyw.EE1SCLSUP.bit.EE1SCLSUP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_0  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_1  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_2  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_3  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_4  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_5  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_6  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_7  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_8  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_9  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA[0] = 0x%lx\n", ioR2yP1.yyw.EE1SCLPGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA[1] = 0x%lx\n", ioR2yP1.yyw.EE1SCLPGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA[2] = 0x%lx\n", ioR2yP1.yyw.EE1SCLPGA.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA[3] = 0x%lx\n", ioR2yP1.yyw.EE1SCLPGA.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA[4] = 0x%lx\n", ioR2yP1.yyw.EE1SCLPGA.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_0  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_1  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_2  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_3  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_4  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_5  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_6  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_7  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_8  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_9  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_1  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_2  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_3  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_4  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_5  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_6  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_7  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_8  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_9  = 0x%x\n",  ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_0  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_1  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_2  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_3  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_4  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_5  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_6  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_7  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_8  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_9  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA[0] = 0x%lx\n", ioR2yP1.yyw.EE1SCLMGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA[1] = 0x%lx\n", ioR2yP1.yyw.EE1SCLMGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA[2] = 0x%lx\n", ioR2yP1.yyw.EE1SCLMGA.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA[3] = 0x%lx\n", ioR2yP1.yyw.EE1SCLMGA.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA[4] = 0x%lx\n", ioR2yP1.yyw.EE1SCLMGA.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_0  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_1  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_2  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_3  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_4  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_5  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_6  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_7  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_8  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_9  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_1  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_2  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_3  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_4  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_5  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_6  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_7  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_8  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_9  = 0x%x\n",  ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPOF_0  = 0x%x\n",  ioR2yP1.yyw.EE1TONPOF.bit.EE1TONPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPOF_1  = 0x%x\n",  ioR2yP1.yyw.EE1TONPOF.bit.EE1TONPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPOF_2  = 0x%x\n",  ioR2yP1.yyw.EE1TONPOF.bit.EE1TONPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPOF_3  = 0x%x\n",  ioR2yP1.yyw.EE1TONPOF.bit.EE1TONPOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPOF_4  = 0x%x\n",  ioR2yP1.yyw.EE1TONPOF.bit.EE1TONPOF_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA[0] = 0x%lx\n", ioR2yP1.yyw.EE1TONPGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA[1] = 0x%lx\n", ioR2yP1.yyw.EE1TONPGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA[2] = 0x%lx\n", ioR2yP1.yyw.EE1TONPGA.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA_0  = 0x%x\n",  ioR2yP1.yyw.EE1TONPGA.bit.EE1TONPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA_1  = 0x%x\n",  ioR2yP1.yyw.EE1TONPGA.bit.EE1TONPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA_2  = 0x%x\n",  ioR2yP1.yyw.EE1TONPGA.bit.EE1TONPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA_3  = 0x%x\n",  ioR2yP1.yyw.EE1TONPGA.bit.EE1TONPGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA_4  = 0x%x\n",  ioR2yP1.yyw.EE1TONPGA.bit.EE1TONPGA_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPBD_1  = 0x%x\n",  ioR2yP1.yyw.EE1TONPBD.bit.EE1TONPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPBD_2  = 0x%x\n",  ioR2yP1.yyw.EE1TONPBD.bit.EE1TONPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPBD_3  = 0x%x\n",  ioR2yP1.yyw.EE1TONPBD.bit.EE1TONPBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPBD_4  = 0x%x\n",  ioR2yP1.yyw.EE1TONPBD.bit.EE1TONPBD_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMOF_0  = 0x%x\n",  ioR2yP1.yyw.EE1TONMOF.bit.EE1TONMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMOF_1  = 0x%x\n",  ioR2yP1.yyw.EE1TONMOF.bit.EE1TONMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMOF_2  = 0x%x\n",  ioR2yP1.yyw.EE1TONMOF.bit.EE1TONMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMOF_3  = 0x%x\n",  ioR2yP1.yyw.EE1TONMOF.bit.EE1TONMOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMOF_4  = 0x%x\n",  ioR2yP1.yyw.EE1TONMOF.bit.EE1TONMOF_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA[0] = 0x%lx\n", ioR2yP1.yyw.EE1TONMGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA[1] = 0x%lx\n", ioR2yP1.yyw.EE1TONMGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA[2] = 0x%lx\n", ioR2yP1.yyw.EE1TONMGA.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA_0  = 0x%x\n",  ioR2yP1.yyw.EE1TONMGA.bit.EE1TONMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA_1  = 0x%x\n",  ioR2yP1.yyw.EE1TONMGA.bit.EE1TONMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA_2  = 0x%x\n",  ioR2yP1.yyw.EE1TONMGA.bit.EE1TONMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA_3  = 0x%x\n",  ioR2yP1.yyw.EE1TONMGA.bit.EE1TONMGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA_4  = 0x%x\n",  ioR2yP1.yyw.EE1TONMGA.bit.EE1TONMGA_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMBD_1  = 0x%x\n",  ioR2yP1.yyw.EE1TONMBD.bit.EE1TONMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMBD_2  = 0x%x\n",  ioR2yP1.yyw.EE1TONMBD.bit.EE1TONMBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMBD_3  = 0x%x\n",  ioR2yP1.yyw.EE1TONMBD.bit.EE1TONMBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMBD_4  = 0x%x\n",  ioR2yP1.yyw.EE1TONMBD.bit.EE1TONMBD_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPOF_0  = 0x%x\n",  ioR2yP1.yyw.EE1CLPPOF.bit.EE1CLPPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPOF_1  = 0x%x\n",  ioR2yP1.yyw.EE1CLPPOF.bit.EE1CLPPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPOF_2  = 0x%x\n",  ioR2yP1.yyw.EE1CLPPOF.bit.EE1CLPPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPGA    = 0x%lx\n", ioR2yP1.yyw.EE1CLPPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPGA_0  = 0x%x\n",  ioR2yP1.yyw.EE1CLPPGA.bit.EE1CLPPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPGA_1  = 0x%x\n",  ioR2yP1.yyw.EE1CLPPGA.bit.EE1CLPPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPGA_2  = 0x%x\n",  ioR2yP1.yyw.EE1CLPPGA.bit.EE1CLPPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPBD_1  = 0x%x\n",  ioR2yP1.yyw.EE1CLPPBD.bit.EE1CLPPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPBD_2  = 0x%x\n",  ioR2yP1.yyw.EE1CLPPBD.bit.EE1CLPPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMOF_0  = 0x%x\n",  ioR2yP1.yyw.EE1CLPMOF.bit.EE1CLPMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMOF_1  = 0x%x\n",  ioR2yP1.yyw.EE1CLPMOF.bit.EE1CLPMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMOF_2  = 0x%x\n",  ioR2yP1.yyw.EE1CLPMOF.bit.EE1CLPMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMGA    = 0x%lx\n", ioR2yP1.yyw.EE1CLPMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMGA_0  = 0x%x\n",  ioR2yP1.yyw.EE1CLPMGA.bit.EE1CLPMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMGA_1  = 0x%x\n",  ioR2yP1.yyw.EE1CLPMGA.bit.EE1CLPMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMGA_2  = 0x%x\n",  ioR2yP1.yyw.EE1CLPMGA.bit.EE1CLPMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMBD_1  = 0x%x\n",  ioR2yP1.yyw.EE1CLPMBD.bit.EE1CLPMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMBD_2  = 0x%x\n",  ioR2yP1.yyw.EE1CLPMBD.bit.EE1CLPMBD_2 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1EN        = 0x%x\n",  ioR2yP2.yyw.EE1CTL.bit.EE1EN ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TC        = 0x%x\n",  ioR2yP2.yyw.EE1CTL.bit.EE1TC ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK[0]   = 0x%lx\n", ioR2yP2.yyw.EE1HPFK.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK[1]   = 0x%lx\n", ioR2yP2.yyw.EE1HPFK.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK0     = 0x%x\n",  ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK1     = 0x%x\n",  ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK2     = 0x%x\n",  ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK3     = 0x%x\n",  ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK4     = 0x%x\n",  ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1HPFK5     = 0x%x\n",  ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1NRLV      = 0x%x\n",  ioR2yP2.yyw.EE1NRLV.bit.EE1NRLV ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPOF_0  = 0x%x\n",  ioR2yP2.yyw.EE1CORPOF.bit.EE1CORPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPOF_1  = 0x%x\n",  ioR2yP2.yyw.EE1CORPOF.bit.EE1CORPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPOF_2  = 0x%x\n",  ioR2yP2.yyw.EE1CORPOF.bit.EE1CORPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPOF_3  = 0x%x\n",  ioR2yP2.yyw.EE1CORPOF.bit.EE1CORPOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPGA    = 0x%lx\n", ioR2yP2.yyw.EE1CORPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPGA_0  = 0x%x\n",  ioR2yP2.yyw.EE1CORPGA.bit.EE1CORPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPGA_1  = 0x%x\n",  ioR2yP2.yyw.EE1CORPGA.bit.EE1CORPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPGA_2  = 0x%x\n",  ioR2yP2.yyw.EE1CORPGA.bit.EE1CORPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPGA_3  = 0x%x\n",  ioR2yP2.yyw.EE1CORPGA.bit.EE1CORPGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPBD_1  = 0x%x\n",  ioR2yP2.yyw.EE1CORPBD.bit.EE1CORPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPBD_2  = 0x%x\n",  ioR2yP2.yyw.EE1CORPBD.bit.EE1CORPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORPBD_3  = 0x%x\n",  ioR2yP2.yyw.EE1CORPBD.bit.EE1CORPBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMOF_0  = 0x%x\n",  ioR2yP2.yyw.EE1CORMOF.bit.EE1CORMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMOF_1  = 0x%x\n",  ioR2yP2.yyw.EE1CORMOF.bit.EE1CORMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMOF_2  = 0x%x\n",  ioR2yP2.yyw.EE1CORMOF.bit.EE1CORMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMOF_3  = 0x%x\n",  ioR2yP2.yyw.EE1CORMOF.bit.EE1CORMOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMGA    = 0x%lx\n", ioR2yP2.yyw.EE1CORMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMGA_0  = 0x%x\n",  ioR2yP2.yyw.EE1CORMGA.bit.EE1CORMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMGA_1  = 0x%x\n",  ioR2yP2.yyw.EE1CORMGA.bit.EE1CORMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMGA_2  = 0x%x\n",  ioR2yP2.yyw.EE1CORMGA.bit.EE1CORMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMGA_3  = 0x%x\n",  ioR2yP2.yyw.EE1CORMGA.bit.EE1CORMGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMBD_1  = 0x%x\n",  ioR2yP2.yyw.EE1CORMBD.bit.EE1CORMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMBD_2  = 0x%x\n",  ioR2yP2.yyw.EE1CORMBD.bit.EE1CORMBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CORMBD_3  = 0x%x\n",  ioR2yP2.yyw.EE1CORMBD.bit.EE1CORMBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLSUP    = 0x%x\n",  ioR2yP2.yyw.EE1SCLSUP.bit.EE1SCLSUP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_0  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_1  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_2  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_3  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_4  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_5  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_6  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_7  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_8  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPOF_9  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA[0] = 0x%lx\n", ioR2yP2.yyw.EE1SCLPGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA[1] = 0x%lx\n", ioR2yP2.yyw.EE1SCLPGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA[2] = 0x%lx\n", ioR2yP2.yyw.EE1SCLPGA.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA[3] = 0x%lx\n", ioR2yP2.yyw.EE1SCLPGA.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA[4] = 0x%lx\n", ioR2yP2.yyw.EE1SCLPGA.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_0  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_1  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_2  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_3  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_4  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_5  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_6  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_7  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_8  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPGA_9  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_1  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_2  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_3  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_4  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_5  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_6  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_7  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_8  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLPBD_9  = 0x%x\n",  ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_0  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_1  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_2  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_3  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_4  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_5  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_6  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_7  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_8  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMOF_9  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA[0] = 0x%lx\n", ioR2yP2.yyw.EE1SCLMGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA[1] = 0x%lx\n", ioR2yP2.yyw.EE1SCLMGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA[2] = 0x%lx\n", ioR2yP2.yyw.EE1SCLMGA.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA[3] = 0x%lx\n", ioR2yP2.yyw.EE1SCLMGA.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA[4] = 0x%lx\n", ioR2yP2.yyw.EE1SCLMGA.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_0  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_1  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_2  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_3  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_4  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_5  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_6  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_7  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_8  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMGA_9  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_1  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_2  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_3  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_4  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_5  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_6  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_7  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_8  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1SCLMBD_9  = 0x%x\n",  ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPOF_0  = 0x%x\n",  ioR2yP2.yyw.EE1TONPOF.bit.EE1TONPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPOF_1  = 0x%x\n",  ioR2yP2.yyw.EE1TONPOF.bit.EE1TONPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPOF_2  = 0x%x\n",  ioR2yP2.yyw.EE1TONPOF.bit.EE1TONPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPOF_3  = 0x%x\n",  ioR2yP2.yyw.EE1TONPOF.bit.EE1TONPOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPOF_4  = 0x%x\n",  ioR2yP2.yyw.EE1TONPOF.bit.EE1TONPOF_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA[0] = 0x%lx\n", ioR2yP2.yyw.EE1TONPGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA[1] = 0x%lx\n", ioR2yP2.yyw.EE1TONPGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA[2] = 0x%lx\n", ioR2yP2.yyw.EE1TONPGA.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA_0  = 0x%x\n",  ioR2yP2.yyw.EE1TONPGA.bit.EE1TONPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA_1  = 0x%x\n",  ioR2yP2.yyw.EE1TONPGA.bit.EE1TONPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA_2  = 0x%x\n",  ioR2yP2.yyw.EE1TONPGA.bit.EE1TONPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA_3  = 0x%x\n",  ioR2yP2.yyw.EE1TONPGA.bit.EE1TONPGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPGA_4  = 0x%x\n",  ioR2yP2.yyw.EE1TONPGA.bit.EE1TONPGA_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPBD_1  = 0x%x\n",  ioR2yP2.yyw.EE1TONPBD.bit.EE1TONPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPBD_2  = 0x%x\n",  ioR2yP2.yyw.EE1TONPBD.bit.EE1TONPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPBD_3  = 0x%x\n",  ioR2yP2.yyw.EE1TONPBD.bit.EE1TONPBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONPBD_4  = 0x%x\n",  ioR2yP2.yyw.EE1TONPBD.bit.EE1TONPBD_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMOF_0  = 0x%x\n",  ioR2yP2.yyw.EE1TONMOF.bit.EE1TONMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMOF_1  = 0x%x\n",  ioR2yP2.yyw.EE1TONMOF.bit.EE1TONMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMOF_2  = 0x%x\n",  ioR2yP2.yyw.EE1TONMOF.bit.EE1TONMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMOF_3  = 0x%x\n",  ioR2yP2.yyw.EE1TONMOF.bit.EE1TONMOF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMOF_4  = 0x%x\n",  ioR2yP2.yyw.EE1TONMOF.bit.EE1TONMOF_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA[0] = 0x%lx\n", ioR2yP2.yyw.EE1TONMGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA[1] = 0x%lx\n", ioR2yP2.yyw.EE1TONMGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA[2] = 0x%lx\n", ioR2yP2.yyw.EE1TONMGA.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA_0  = 0x%x\n",  ioR2yP2.yyw.EE1TONMGA.bit.EE1TONMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA_1  = 0x%x\n",  ioR2yP2.yyw.EE1TONMGA.bit.EE1TONMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA_2  = 0x%x\n",  ioR2yP2.yyw.EE1TONMGA.bit.EE1TONMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA_3  = 0x%x\n",  ioR2yP2.yyw.EE1TONMGA.bit.EE1TONMGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMGA_4  = 0x%x\n",  ioR2yP2.yyw.EE1TONMGA.bit.EE1TONMGA_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMBD_1  = 0x%x\n",  ioR2yP2.yyw.EE1TONMBD.bit.EE1TONMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMBD_2  = 0x%x\n",  ioR2yP2.yyw.EE1TONMBD.bit.EE1TONMBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMBD_3  = 0x%x\n",  ioR2yP2.yyw.EE1TONMBD.bit.EE1TONMBD_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1TONMBD_4  = 0x%x\n",  ioR2yP2.yyw.EE1TONMBD.bit.EE1TONMBD_4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPOF_0  = 0x%x\n",  ioR2yP2.yyw.EE1CLPPOF.bit.EE1CLPPOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPOF_1  = 0x%x\n",  ioR2yP2.yyw.EE1CLPPOF.bit.EE1CLPPOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPOF_2  = 0x%x\n",  ioR2yP2.yyw.EE1CLPPOF.bit.EE1CLPPOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPGA    = 0x%lx\n", ioR2yP2.yyw.EE1CLPPGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPGA_0  = 0x%x\n",  ioR2yP2.yyw.EE1CLPPGA.bit.EE1CLPPGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPGA_1  = 0x%x\n",  ioR2yP2.yyw.EE1CLPPGA.bit.EE1CLPPGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPGA_2  = 0x%x\n",  ioR2yP2.yyw.EE1CLPPGA.bit.EE1CLPPGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPBD_1  = 0x%x\n",  ioR2yP2.yyw.EE1CLPPBD.bit.EE1CLPPBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPPBD_2  = 0x%x\n",  ioR2yP2.yyw.EE1CLPPBD.bit.EE1CLPPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMOF_0  = 0x%x\n",  ioR2yP2.yyw.EE1CLPMOF.bit.EE1CLPMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMOF_1  = 0x%x\n",  ioR2yP2.yyw.EE1CLPMOF.bit.EE1CLPMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMOF_2  = 0x%x\n",  ioR2yP2.yyw.EE1CLPMOF.bit.EE1CLPMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMGA    = 0x%lx\n", ioR2yP2.yyw.EE1CLPMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMGA_0  = 0x%x\n",  ioR2yP2.yyw.EE1CLPMGA.bit.EE1CLPMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMGA_1  = 0x%x\n",  ioR2yP2.yyw.EE1CLPMGA.bit.EE1CLPMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMGA_2  = 0x%x\n",  ioR2yP2.yyw.EE1CLPMGA.bit.EE1CLPMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMBD_1  = 0x%x\n",  ioR2yP2.yyw.EE1CLPMBD.bit.EE1CLPMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE1CLPMBD_2  = 0x%x\n",  ioR2yP2.yyw.EE1CLPMBD.bit.EE1CLPMBD_2 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_47: "
INT32 ct_im_r2y_classf_1_47( UCHAR pipeNo )
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
			ercd = Im_R2Y_Set_RGBDeknee_Table( pipeNo, loopcnt2, tbl->srcTbl );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
			Im_R2Y_On_Hclk( pipeNo );
			Im_R2Y_Set_RGBDekneeAccessEnable( pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
			switch( loopcnt2 ) {
				default:
//				case E_R2Y_DKN_RGBTBL_R:
					if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loopcnt3++ ) {
							if( ioR2yTblP1.DKNTBLR.hword[loopcnt3] != tbl->srcTbl[loopcnt3] ) {
								Ddim_Print(( errmsg, loopcnt2, loopcnt3 ));
							}
						}
					}
					if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
						for( loopcnt3 = 0; loopcnt3 < D_IM_R2Y_TABLE_MAX_RGB_DEKNEE; loopcnt3++ ) {
							if( ioR2yTblP2.DKNTBLR.hword[loopcnt3] != tbl->srcTbl[loopcnt3] ) {
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
			Im_R2Y_Set_RGBDekneeAccessEnable( pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
			Im_R2Y_Off_Hclk( pipeNo );
#else
			Im_R2Y_Set_RGBDeknee_Table( pipeNo, loopcnt2, tbl->srcTbl );
#endif
		}
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_48: "
INT32 ct_im_r2y_classf_1_48( UCHAR pipeNo )
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
		ercd = Im_R2Y_Set_RGBDekneeAccessEnable( pipeNo, accessEnable[loopcnt], D_IM_R2Y_WAIT_ON );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "YYRAEN_RGB_DEKNEE = %u\n", ioR2yP1.R2Y_CMN.RAMAEN.bit.YYRAEN_RGB_DEKNEE ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "YYRAEN_RGB_DEKNEE = %u\n", ioR2yP2.R2Y_CMN.RAMAEN.bit.YYRAEN_RGB_DEKNEE ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_49: "
INT32 ct_im_r2y_classf_1_49( UCHAR pipeNo )
{
	TImR2yOfs ofs[] = {
		[0] = {	// max
			.R = 0x1FF,
			.G = 0x1FF,
			.B = 0x1FF,
		},
		[1] = {	// min
			.R = -512,
			.G = -512,
			.B = -512,
		},
		[2] = {	// indvisual
			.R = 10,
			.G = 20,
			.B = 30,
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
		ercd = Im_R2Y_Set_Offset( pipeNo, &ofs[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "OFST[0] = 0x%lx\n", ioR2yP1.F_R2Y.OFG.OFST.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "OFST[1] = 0x%lx\n", ioR2yP1.F_R2Y.OFG.OFST.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "OFSTR   = 0x%x\n",  ioR2yP1.F_R2Y.OFG.OFST.bit.OFSTR ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "OFSTG   = 0x%x\n",  ioR2yP1.F_R2Y.OFG.OFST.bit.OFSTG ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "OFSTB   = 0x%x\n",  ioR2yP1.F_R2Y.OFG.OFST.bit.OFSTB ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "OFST[0] = 0x%lx\n", ioR2yP2.F_R2Y.OFG.OFST.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "OFST[1] = 0x%lx\n", ioR2yP2.F_R2Y.OFG.OFST.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "OFSTR   = 0x%x\n",  ioR2yP2.F_R2Y.OFG.OFST.bit.OFSTR ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "OFSTG   = 0x%x\n",  ioR2yP2.F_R2Y.OFG.OFST.bit.OFSTG ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "OFSTB   = 0x%x\n",  ioR2yP2.F_R2Y.OFG.OFST.bit.OFSTB ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_50: "
INT32 ct_im_r2y_classf_1_50( UCHAR pipeNo )
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
		ercd = Im_R2Y_Set_WB_Gain( pipeNo, &r2yRgbColor[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBGAR = 0x%x\n", ioR2yP1.F_R2Y.OFG.WBGAR.bit.WBGAR ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBGAG = 0x%x\n", ioR2yP1.F_R2Y.OFG.WBGAR.bit.WBGAG ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBGAB = 0x%x\n", ioR2yP1.F_R2Y.OFG.WBGAR.bit.WBGAB ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBGAR = 0x%x\n", ioR2yP2.F_R2Y.OFG.WBGAR.bit.WBGAR ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBGAG = 0x%x\n", ioR2yP2.F_R2Y.OFG.WBGAR.bit.WBGAG ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBGAB = 0x%x\n", ioR2yP2.F_R2Y.OFG.WBGAR.bit.WBGAB ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_51: "
INT32 ct_im_r2y_classf_1_51( UCHAR pipeNo )
{
	TImR2yRgbColor r2yRgbColor[] = {
		[0] = {	// max
			.R = 0xFFF,
			.G = 0xFFF,
			.B = 0xFFF,
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
		ercd = Im_R2Y_Set_WB_Clip_Level( pipeNo, &r2yRgbColor[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBLVR = 0x%x\n", ioR2yP1.F_R2Y.OFG.WBLV.bit.WBLVR ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBLVG = 0x%x\n", ioR2yP1.F_R2Y.OFG.WBLV.bit.WBLVG ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBLVB = 0x%x\n", ioR2yP1.F_R2Y.OFG.WBLV.bit.WBLVB ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBLVR = 0x%x\n", ioR2yP2.F_R2Y.OFG.WBLV.bit.WBLVR ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBLVG = 0x%x\n", ioR2yP2.F_R2Y.OFG.WBLV.bit.WBLVG ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "WBLVB = 0x%x\n", ioR2yP2.F_R2Y.OFG.WBLV.bit.WBLVB ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_52: "
INT32 ct_im_r2y_classf_1_52( UCHAR pipeNo )
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
	ercd = Im_R2Y_Ctrl_CC0_Matrix( pipeNo, &r2yCtrlCc[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0DP     = %u\n",    ioR2yP1.F_R2Y.CCA0.CC0CTL.bit.CC0DP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[0]   = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0K.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[1]   = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0K.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[2]   = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0K.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[3]   = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0K.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[4]   = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0K.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_0  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_0_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_1  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_0_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_2  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_0_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_0  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_1_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_1  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_1_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_2  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_1_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_0  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_2_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_1  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_2_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_2  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_2_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_0  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_1  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_2  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA[0] = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0YBGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA[1] = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0YBGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_0  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0YBGA.bit.CC0YBGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_1  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0YBGA.bit.CC0YBGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_2  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0YBGA.bit.CC0YBGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBBD_1  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0YBBD.bit.CC0YBBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBBD_2  = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0YBBD.bit.CC0YBBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYC_0    = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CCYC.bit.CCYC_0_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYC_1    = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CCYC.bit.CCYC_0_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYC_2    = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CCYC.bit.CCYC_0_2 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0DP     = %u\n",    ioR2yP2.F_R2Y.CCA0.CC0CTL.bit.CC0DP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[0]   = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0K.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[1]   = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0K.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[2]   = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0K.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[3]   = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0K.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[4]   = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0K.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_0  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_0_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_1  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_0_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_2  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_0_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_0  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_1_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_1  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_1_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_2  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_1_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_0  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_2_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_1  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_2_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_2  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_2_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_0  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_1  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBOF_2  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0YBOF.bit.CC0YBOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA[0] = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0YBGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA[1] = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0YBGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_0  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0YBGA.bit.CC0YBGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_1  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0YBGA.bit.CC0YBGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBGA_2  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0YBGA.bit.CC0YBGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBBD_1  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0YBBD.bit.CC0YBBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYBBD_2  = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0YBBD.bit.CC0YBBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYC_0    = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CCYC.bit.CCYC_0_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYC_1    = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CCYC.bit.CCYC_0_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CCYC_2    = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CCYC.bit.CCYC_0_2 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classf_1_53: "
INT32 ct_im_r2y_classf_1_53( UCHAR pipeNo )
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
		ercd = Im_R2Y_Set_CC0_Matrix_Coefficient( pipeNo, &r2yCc0k[loopcnt][0] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[0]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0K.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[1]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0K.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[2]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0K.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[3]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0K.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[4]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA0.CC0K.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_0 = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_0_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_1 = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_0_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_2 = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_0_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_0 = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_1_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_1 = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_1_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_2 = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_1_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_0 = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_2_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_1 = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_2_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_2 = 0x%x\n",  ioR2yP1.F_R2Y.CCA0.CC0K.bit.CC0K_2_2 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[0]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0K.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[1]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0K.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[2]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0K.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[3]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0K.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K[4]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA0.CC0K.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_0 = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_0_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_1 = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_0_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_0_2 = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_0_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_0 = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_1_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_1 = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_1_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_1_2 = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_1_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_0 = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_2_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_1 = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_2_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC0K_2_2 = 0x%x\n",  ioR2yP2.F_R2Y.CCA0.CC0K.bit.CC0K_2_2 ));
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
