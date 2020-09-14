/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y18series1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "imr2yclk.h"
#include "imr2yctrl3.h"
#include "imr2yctrl.h"
#include "ctimr2y18series1.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y18series1, ct_im_r2y_18series1)
#define CT_IM_R2Y_18SERIES1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y18series1Private, CT_TYPE_IM_R2Y_18SERIES1))


struct _CtImR2y18series1Private
{

};


/*
 * IMPL
 */
static void ct_im_r2y_18series1_constructor(CtImR2y18series1 *self)
{
	CtImR2y18series1Private *priv = CT_IM_R2Y_18SERIES1_GET_PRIVATE(self);
	self->imR2yCtrl3 = im_r2y_ctrl3_new();
	self->imR2yClk = im_r2y_clk_new();
	self->imR2yCtrl = im_r2y_ctrl_new();
}

static void ct_im_r2y_18series1_destructor(CtImR2y18series1 *self)
{
	CtImR2y18series1Private *priv = CT_IM_R2Y_18SERIES1_GET_PRIVATE(self);
	if(self->imR2yCtrl3){
				k_object_unref(self->imR2yCtrl3);
				self->imR2yCtrl3=NULL;
			}

			if(self->imR2yCtrl){
				k_object_unref(self->imR2yCtrl);
				self->imR2yCtrl3=NULL;
			}

			if(self->imR2yClk){
					k_object_unref(self->imR2yClk);
					self->imR2yClk=NULL;
				}
}


/*
 * PUBLIC
 */
#undef 	CtImR2y18series1_FUNC_NAME
#define 	CtImR2y18series1_FUNC_NAME "ct_im_r2y_18series1_6: "
kint32 ct_im_r2y_18series1_6(CtImR2y18series1 *self, kuchar pipeNo)
{
	TImR2yCtrlCRefYbBlend r2yCtrlCRefYbBlend[] =
		{
			// max
			[0] =
				{
					.areaAEnable = 1,
					.areaBEnable = 1,
					.areaAOffset = 0xFF,
					.areaAGain =
						{
							0x3FF, 0x3FF,
						},
					.areaABorder = 0x7F,
					.areaAScaleClipLo = 0x80,
					.areaAScaleClipHi = 0x80,
					.areaACorrectGainP = 0xFF,
					.areaACorrectGainM = 0xFF,
					.areaACorrectBorder =
						{
							0xFF, 0xFF,
						},
					.areaACorrectClipLo = 0x80,
					.areaACorrectClipHi = 0x80,
					.areaBOffset = 0xFF,
					.areaBGain =
						{
							0x3FF, 0x3FF,
						},
					.areaBBorder = 0x7F,
					.areaBScaleClipLo = 0x80,
					.areaBScaleClipHi = 0x80,
					.areaBCorrectGainP = 0xFF,
					.areaBCorrectGainM = 0xFF,
					.areaBCorrectBorder =
						{
							0xFF, 0xFF,
						},
					.areaBCorrectClipLo = 0x80,
					.areaBCorrectClipHi = 0x80,
				},
			// min
			[1] =
				{
					.areaAEnable = 0,
					.areaBEnable = 0,
					.areaAOffset = 0,
					.areaAGain =
						{
							-0x400, -0x400,
						},
					.areaABorder = 0,
					.areaAScaleClipLo = 0,
					.areaAScaleClipHi = 0,
					.areaACorrectGainP = 0,
					.areaACorrectGainM = 0,
					.areaACorrectBorder =
						{
							0, 0,
						},
					.areaACorrectClipLo = 0,
					.areaACorrectClipHi = 0,
					.areaBOffset = 0,
					.areaBGain =
						{
							-0x400, -0x400,
						},
					.areaBBorder = 0,
					.areaBScaleClipLo = 0,
					.areaBScaleClipHi = 0,
					.areaBCorrectGainP = 0,
					.areaBCorrectGainM = 0,
					.areaBCorrectBorder =
						{
							0, 0,
						},
					.areaBCorrectClipLo = 0,
					.areaBCorrectClipHi = 0,
				},
			// indvisual
			[2] =
				{
					.areaAEnable = 1,
					.areaBEnable = 1,
					.areaAOffset = 0x1,
					.areaAGain =
						{
							0x2, 0x3,
						},
					.areaABorder = 0x4,
					.areaAScaleClipLo = 0x5,
					.areaAScaleClipHi = 0x6,
					.areaACorrectGainP = 0x7,
					.areaACorrectGainM = 0x8,
					.areaACorrectBorder =
						{
							0x9, 0xA,
						},
					.areaACorrectClipLo = 0xB,
					.areaACorrectClipHi = 0xC,
					.areaBOffset = 0xD,
					.areaBGain =
						{
							0xE, 0xF,
						},
					.areaBBorder = 0x10,
					.areaBScaleClipLo = 0x11,
					.areaBScaleClipHi = 0x12,
					.areaBCorrectGainP = 0x13,
					.areaBCorrectGainM = 0x14,
					.areaBCorrectBorder =
						{
							0x15, 0x16,
						},
					.areaBCorrectClipLo = 0x17,
					.areaBCorrectClipHi = 0x18,
			},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y18series1_FUNC_NAME));
	for(loopcnt = 0; loopcnt < (sizeof(r2yCtrlCRefYbBlend) / sizeof(r2yCtrlCRefYbBlend[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl3_cref_yb_blend(self->imR2yCtrl3, pipeNo, &r2yCtrlCRefYbBlend[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y18series1_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT(("ybcrae = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvctl.bit.ybcrae));
		DriverCommon_DDIM_PRINT(("ybcrbe = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvctl.bit.ybcrbe));
		DriverCommon_DDIM_PRINT(("ybcrvaalpof1 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvaalpof.bit.ybcrvaalpof1));
		DriverCommon_DDIM_PRINT(("ybcrvaalpga = 0x%lx\n", ioR2yP1.fR2y.ybcrv.ybcrvaalpga.word));
		DriverCommon_DDIM_PRINT(("ybcrvaalpga0 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvaalpga.bit.ybcrvaalpga0));
		DriverCommon_DDIM_PRINT(("ybcrvaalpga1 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvaalpga.bit.ybcrvaalpga1));
		DriverCommon_DDIM_PRINT(("ybcrvaalpbd1 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvaalpbd.bit.ybcrvaalpbd1));
		DriverCommon_DDIM_PRINT(("ybcrvaalpcpl = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvaalpcp.bit.ybcrvaalpcpl));
		DriverCommon_DDIM_PRINT(("ybcrvaalpcph = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvaalpcp.bit.ybcrvaalpcph));
		DriverCommon_DDIM_PRINT(("ybyaalpga0 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybyaalpga.bit.ybyaalpga0));
		DriverCommon_DDIM_PRINT(("ybyaalpga1 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybyaalpga.bit.ybyaalpga1));
		DriverCommon_DDIM_PRINT(("ybyaalpbd0 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybyaalpbd.bit.ybyaalpbd0));
		DriverCommon_DDIM_PRINT(("ybyaalpbd1 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybyaalpbd.bit.ybyaalpbd1));
		DriverCommon_DDIM_PRINT(("ybyaalpclpl = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybyaalpclp.bit.ybyaalpclpl));
		DriverCommon_DDIM_PRINT(("ybyaalpclph = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybyaalpclp.bit.ybyaalpclph));
		DriverCommon_DDIM_PRINT(("ybcrvbalpof1 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvbalpof.bit.ybcrvbalpof1));
		DriverCommon_DDIM_PRINT(("ybcrvbalpga = 0x%lx\n", ioR2yP1.fR2y.ybcrv.ybcrvbalpga.word));
		DriverCommon_DDIM_PRINT(("ybcrvbalpga0 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvbalpga.bit.ybcrvbalpga0));
		DriverCommon_DDIM_PRINT(("ybcrvbalpga1 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvbalpga.bit.ybcrvbalpga1));
		DriverCommon_DDIM_PRINT(("ybcrvbalpbd1 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvbalpbd.bit.ybcrvbalpbd1));
		DriverCommon_DDIM_PRINT(("ybcrvbalpcpl = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvbalpcp.bit.ybcrvbalpcpl));
		DriverCommon_DDIM_PRINT(("ybcrvbalpcph = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybcrvbalpcp.bit.ybcrvbalpcph));
		DriverCommon_DDIM_PRINT(("ybybalpga0 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybybalpga.bit.ybybalpga0));
		DriverCommon_DDIM_PRINT(("ybybalpga1 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybybalpga.bit.ybybalpga1));
		DriverCommon_DDIM_PRINT(("ybybalpbd0 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybybalpbd.bit.ybybalpbd0));
		DriverCommon_DDIM_PRINT(("ybybalpbd1 = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybybalpbd.bit.ybybalpbd1));
		DriverCommon_DDIM_PRINT(("ybybalpclpl = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybybalpclp.bit.ybybalpclpl));
		DriverCommon_DDIM_PRINT(("ybybalpclph = 0x%x\n",  ioR2yP1.fR2y.ybcrv.ybybalpclp.bit.ybybalpclph));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT(("ybcrae = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvctl.bit.ybcrae));
		DriverCommon_DDIM_PRINT(("ybcrbe = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvctl.bit.ybcrbe));
		DriverCommon_DDIM_PRINT(("ybcrvaalpof1 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvaalpof.bit.ybcrvaalpof1));
		DriverCommon_DDIM_PRINT(("ybcrvaalpga = 0x%lx\n", ioR2yP2.fR2y.ybcrv.ybcrvaalpga.word));
		DriverCommon_DDIM_PRINT(("ybcrvaalpga0 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvaalpga.bit.ybcrvaalpga0));
		DriverCommon_DDIM_PRINT(("ybcrvaalpga1 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvaalpga.bit.ybcrvaalpga1));
		DriverCommon_DDIM_PRINT(("ybcrvaalpbd1 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvaalpbd.bit.ybcrvaalpbd1));
		DriverCommon_DDIM_PRINT(("ybcrvaalpcpl = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvaalpcp.bit.ybcrvaalpcpl));
		DriverCommon_DDIM_PRINT(("ybcrvaalpcph = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvaalpcp.bit.ybcrvaalpcph));
		DriverCommon_DDIM_PRINT(("ybyaalpga0 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybyaalpga.bit.ybyaalpga0));
		DriverCommon_DDIM_PRINT(("ybyaalpga1 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybyaalpga.bit.ybyaalpga1));
		DriverCommon_DDIM_PRINT(("ybyaalpbd0 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybyaalpbd.bit.ybyaalpbd0));
		DriverCommon_DDIM_PRINT(("ybyaalpbd1 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybyaalpbd.bit.ybyaalpbd1));
		DriverCommon_DDIM_PRINT(("ybyaalpclpl = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybyaalpclp.bit.ybyaalpclpl));
		DriverCommon_DDIM_PRINT(("ybyaalpclph = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybyaalpclp.bit.ybyaalpclph));
		DriverCommon_DDIM_PRINT(("ybcrvbalpof1 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvbalpof.bit.ybcrvbalpof1));
		DriverCommon_DDIM_PRINT(("ybcrvbalpga = 0x%lx\n", ioR2yP2.fR2y.ybcrv.ybcrvbalpga.word));
		DriverCommon_DDIM_PRINT(("ybcrvbalpga0 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvbalpga.bit.ybcrvbalpga0));
		DriverCommon_DDIM_PRINT(("ybcrvbalpga1 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvbalpga.bit.ybcrvbalpga1));
		DriverCommon_DDIM_PRINT(("ybcrvbalpbd1 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvbalpbd.bit.ybcrvbalpbd1));
		DriverCommon_DDIM_PRINT(("ybcrvbalpcpl = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvbalpcp.bit.ybcrvbalpcpl));
		DriverCommon_DDIM_PRINT(("ybcrvbalpcph = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybcrvbalpcp.bit.ybcrvbalpcph));
		DriverCommon_DDIM_PRINT(("ybybalpga0 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybybalpga.bit.ybybalpga0));
		DriverCommon_DDIM_PRINT(("ybybalpga1 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybybalpga.bit.ybybalpga1));
		DriverCommon_DDIM_PRINT(("ybybalpbd0 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybybalpbd.bit.ybybalpbd0));
		DriverCommon_DDIM_PRINT(("ybybalpbd1 = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybybalpbd.bit.ybybalpbd1));
		DriverCommon_DDIM_PRINT(("ybybalpclpl = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybybalpclp.bit.ybybalpclpl));
		DriverCommon_DDIM_PRINT(("ybybalpclph = 0x%x\n",  ioR2yP2.fR2y.ybcrv.ybybalpclp.bit.ybybalpclph));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y18series1_FUNC_NAME
#define 	CtImR2y18series1_FUNC_NAME "ct_im_r2y_18series1_7: "
kint32 ct_im_r2y_18series1_7(CtImR2y18series1 *self, kuchar pipeNo)
{
	TImR2yCtrlClpf r2yCtrlClpf[] =
		{
			// max
			[0] =
				{
					.clpfEnable = 1,
					.interlockBlendEnable = 1,
					.lpfK =
						{
							0xFF, 0xFF, 0xFF,
							0xFF, 0xFF, 0xFF,
							0xFF, 0xFF, 0xFF,
						},
					.lpfIbOffset =
						{
							0x80, 0x80, 0x80, 0x80,
						},
					.lpfIbGain =
						{
							0x1FF, 0x1FF, 0x1FF, 0x1FF,
						},
					.lpfIbBorder =
						{
							0x3FF, 0x3FF, 0x3FF,
						},
				},
			// min
			[1] =
				{
					.clpfEnable = 0,
					.interlockBlendEnable = 0,
					.lpfK =
						{
							-0x100, -0x100, -0x100,
							-0x100, -0x100, -0x100,
							-0x100, -0x100, -0x100,
						},
					.lpfIbOffset =
						{
							0, 0, 0, 0,
						},
					.lpfIbGain =
						{
							-0x200, -0x200, -0x200, -0x200,
						},
					.lpfIbBorder =
						{
							0, 0, 0,
						},
				},
			// indvisual
			[2] =
				{
					.clpfEnable = 0,
					.interlockBlendEnable = 0x1,
					.lpfK =
						{
							0x2, 0x3, 0x4,
							0x5, 0x6, 0x7,
							0x8, 0x9, 0xA,
						},
					.lpfIbOffset =
						{
							0xB, 0xC, 0xD, 0xE,
						},
					.lpfIbGain =
						{
							0xF, 0x10, 0x11, 0x12,
						},
					.lpfIbBorder =
						{
							0x13, 0x14, 0x15,
						},
				},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y18series1_FUNC_NAME));
	for(loopcnt = 0; loopcnt < (sizeof(r2yCtrlClpf) / sizeof(r2yCtrlClpf[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl3_color_nr(self->imR2yCtrl3, pipeNo, &r2yCtrlClpf[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y18series1_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT(("clpfen = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfctl.bit.clpfen));
		DriverCommon_DDIM_PRINT(("clpfya = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfctl.bit.clpfya));
		DriverCommon_DDIM_PRINT(("clpfk[0] = 0x%lx\n", ioR2yP1.fR2y.clpf.clpfk.word[0]));
		DriverCommon_DDIM_PRINT(("clpfk[1] = 0x%lx\n", ioR2yP1.fR2y.clpf.clpfk.word[1]));
		DriverCommon_DDIM_PRINT(("clpfk[2] = 0x%lx\n", ioR2yP1.fR2y.clpf.clpfk.word[2]));
		DriverCommon_DDIM_PRINT(("clpfk[3] = 0x%lx\n", ioR2yP1.fR2y.clpf.clpfk.word[3]));
		DriverCommon_DDIM_PRINT(("clpfk[4] = 0x%lx\n", ioR2yP1.fR2y.clpf.clpfk.word[4]));
		DriverCommon_DDIM_PRINT(("clpfk0 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfk.bit.clpfk0));
		DriverCommon_DDIM_PRINT(("clpfk1 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfk.bit.clpfk1));
		DriverCommon_DDIM_PRINT(("clpfk2 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfk.bit.clpfk2));
		DriverCommon_DDIM_PRINT(("clpfk3 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfk.bit.clpfk3));
		DriverCommon_DDIM_PRINT(("clpfk4 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfk.bit.clpfk4));
		DriverCommon_DDIM_PRINT(("clpfk5 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfk.bit.clpfk5));
		DriverCommon_DDIM_PRINT(("clpfk6 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfk.bit.clpfk6));
		DriverCommon_DDIM_PRINT(("clpfk7 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfk.bit.clpfk7));
		DriverCommon_DDIM_PRINT(("clpfk8 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfk.bit.clpfk8));
		DriverCommon_DDIM_PRINT(("clpfof0 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfof.bit.clpfof0));
		DriverCommon_DDIM_PRINT(("clpfof1 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfof.bit.clpfof1));
		DriverCommon_DDIM_PRINT(("clpfof2 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfof.bit.clpfof2));
		DriverCommon_DDIM_PRINT(("clpfof3 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfof.bit.clpfof3));
		DriverCommon_DDIM_PRINT(("clpfga[0] = 0x%lx\n", ioR2yP1.fR2y.clpf.clpfga.word[0]));
		DriverCommon_DDIM_PRINT(("clpfga[1] = 0x%lx\n", ioR2yP1.fR2y.clpf.clpfga.word[1]));
		DriverCommon_DDIM_PRINT(("clpfga0 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfga.bit.clpfga0));
		DriverCommon_DDIM_PRINT(("clpfga1 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfga.bit.clpfga1));
		DriverCommon_DDIM_PRINT(("clpfga2 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfga.bit.clpfga2));
		DriverCommon_DDIM_PRINT(("clpfga3 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfga.bit.clpfga3));
		DriverCommon_DDIM_PRINT(("clpfbd1 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfbd.bit.clpfbd1));
		DriverCommon_DDIM_PRINT(("clpfbd2 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfbd.bit.clpfbd2));
		DriverCommon_DDIM_PRINT(("clpfbd3 = 0x%x\n",  ioR2yP1.fR2y.clpf.clpfbd.bit.clpfbd3));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT(("clpfen = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfctl.bit.clpfen));
		DriverCommon_DDIM_PRINT(("clpfya = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfctl.bit.clpfya));
		DriverCommon_DDIM_PRINT(("clpfk[0] = 0x%lx\n", ioR2yP2.fR2y.clpf.clpfk.word[0]));
		DriverCommon_DDIM_PRINT(("clpfk[1] = 0x%lx\n", ioR2yP2.fR2y.clpf.clpfk.word[1]));
		DriverCommon_DDIM_PRINT(("clpfk[2] = 0x%lx\n", ioR2yP2.fR2y.clpf.clpfk.word[2]));
		DriverCommon_DDIM_PRINT(("clpfk[3] = 0x%lx\n", ioR2yP2.fR2y.clpf.clpfk.word[3]));
		DriverCommon_DDIM_PRINT(("clpfk[4] = 0x%lx\n", ioR2yP2.fR2y.clpf.clpfk.word[4]));
		DriverCommon_DDIM_PRINT(("clpfk0 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfk.bit.clpfk0));
		DriverCommon_DDIM_PRINT(("clpfk1 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfk.bit.clpfk1));
		DriverCommon_DDIM_PRINT(("clpfk2 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfk.bit.clpfk2));
		DriverCommon_DDIM_PRINT(("clpfk3 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfk.bit.clpfk3));
		DriverCommon_DDIM_PRINT(("clpfk4 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfk.bit.clpfk4));
		DriverCommon_DDIM_PRINT(("clpfk5 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfk.bit.clpfk5));
		DriverCommon_DDIM_PRINT(("clpfk6 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfk.bit.clpfk6));
		DriverCommon_DDIM_PRINT(("clpfk7 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfk.bit.clpfk7));
		DriverCommon_DDIM_PRINT(("clpfk8 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfk.bit.clpfk8));
		DriverCommon_DDIM_PRINT(("clpfof0 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfof.bit.clpfof0));
		DriverCommon_DDIM_PRINT(("clpfof1 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfof.bit.clpfof1));
		DriverCommon_DDIM_PRINT(("clpfof2 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfof.bit.clpfof2));
		DriverCommon_DDIM_PRINT(("clpfof3 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfof.bit.clpfof3));
		DriverCommon_DDIM_PRINT(("clpfga[0] = 0x%lx\n", ioR2yP2.fR2y.clpf.clpfga.word[0]));
		DriverCommon_DDIM_PRINT(("clpfga[1] = 0x%lx\n", ioR2yP2.fR2y.clpf.clpfga.word[1]));
		DriverCommon_DDIM_PRINT(("clpfga0 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfga.bit.clpfga0));
		DriverCommon_DDIM_PRINT(("clpfga1 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfga.bit.clpfga1));
		DriverCommon_DDIM_PRINT(("clpfga2 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfga.bit.clpfga2));
		DriverCommon_DDIM_PRINT(("clpfga3 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfga.bit.clpfga3));
		DriverCommon_DDIM_PRINT(("clpfbd1 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfbd.bit.clpfbd1));
		DriverCommon_DDIM_PRINT(("clpfbd2 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfbd.bit.clpfbd2));
		DriverCommon_DDIM_PRINT(("clpfbd3 = 0x%x\n",  ioR2yP2.fR2y.clpf.clpfbd.bit.clpfbd3));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y18series1_FUNC_NAME
#define 	CtImR2y18series1_FUNC_NAME "ct_im_r2y_18series1_8: "
kint32 ct_im_r2y_18series1_8(CtImR2y18series1 *self, kuchar pipeNo)
{
	TImR2yCtrlCs r2yCtrlCs[] =
		{
			// max
			[0] = {
				.csyEnable = 1,
				.csyMixRatio = 0x8,
				.csySelectTable = 1,
				.csyOffset =
					{
						0x3FF, 0x3FF, 0x3FF, 0x3FF,
					},
				.csyGain =
					{
						0x3FF, 0x3FF, 0x3FF, 0x3FF,
					},
				.csyBorder =
					{
						0x3FF, 0x3FF, 0x3FF,
					},
				.yRevEnable = 1,
				.cRevEnable = 1,
				.cFixedEnable = 1,
				.cbFixed = 0x1FF,
				.crFixed = 0x1FF,
				.yOffset = 0x3FF,
				.cbOffset = 0x3FF,
				.crOffset = 0x3FF,
			},
		// min
		[1] =
			{
				.csyEnable = 0,
				.csyMixRatio = 0,
				.csySelectTable = 0,
				.csyOffset =
					{
						0, 0, 0, 0,
					},
				.csyGain =
					{
						-0x400, -0x400, -0x400, -0x400,
					},
				.csyBorder =
					{
						0, 0, 0,
					},
				.yRevEnable = 0,
				.cRevEnable = 0,
				.cFixedEnable = 0,
				.cbFixed = -0x200,
				.crFixed = -0x200,
				.yOffset = -0x400,
				.cbOffset = -0x400,
				.crOffset = -0x400,
			},
		// indvisual
		[2] =
			{
				.csyEnable = 0,
				.csyMixRatio = 1,
				.csySelectTable = 0,
				.csyOffset =
					{
						0x3, 0x4, 0x5, 0x6,
					},
				.csyGain =
					{
						0x7, 0x8, 0x9, 0xA,
					},
				.csyBorder =
					{
						0xB, 0xC, 0xD,
					},
				.yRevEnable = 1,
				.cRevEnable = 0,
				.cFixedEnable = 1,
				.cbFixed = 0xE,
				.crFixed = 0xF,
				.yOffset = 0x10,
				.cbOffset = 0x11,
				.crOffset = 0x12,
			},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y18series1_FUNC_NAME));
	for(loopcnt = 0; loopcnt < (sizeof(r2yCtrlCs) / sizeof(r2yCtrlCs[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl3_chroma_suppress(self->imR2yCtrl3, pipeNo, &r2yCtrlCs[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y18series1_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT(("csyen = 0x%x\n",  ioR2yP1.fR2y.csp.csyctl.bit.csyen));
		DriverCommon_DDIM_PRINT(("csyky = 0x%x\n",  ioR2yP1.fR2y.csp.csyctl.bit.csyky));
		DriverCommon_DDIM_PRINT(("csytbl = 0x%x\n",  ioR2yP1.fR2y.csp.csyctl.bit.csytbl));
		DriverCommon_DDIM_PRINT(("csyof0 = 0x%x\n",  ioR2yP1.fR2y.csp.csyof.bit.csyof0));
		DriverCommon_DDIM_PRINT(("csyof1 = 0x%x\n",  ioR2yP1.fR2y.csp.csyof.bit.csyof1));
		DriverCommon_DDIM_PRINT(("csyof2 = 0x%x\n",  ioR2yP1.fR2y.csp.csyof.bit.csyof2));
		DriverCommon_DDIM_PRINT(("csyof3 = 0x%x\n",  ioR2yP1.fR2y.csp.csyof.bit.csyof3));
		DriverCommon_DDIM_PRINT(("csyga[0] = 0x%lx\n", ioR2yP1.fR2y.csp.csyga.word[0]));
		DriverCommon_DDIM_PRINT(("csyga[1] = 0x%lx\n", ioR2yP1.fR2y.csp.csyga.word[1]));
		DriverCommon_DDIM_PRINT(("csyga0 = 0x%x\n",  ioR2yP1.fR2y.csp.csyga.bit.csyga0));
		DriverCommon_DDIM_PRINT(("csyga1 = 0x%x\n",  ioR2yP1.fR2y.csp.csyga.bit.csyga1));
		DriverCommon_DDIM_PRINT(("csyga2 = 0x%x\n",  ioR2yP1.fR2y.csp.csyga.bit.csyga2));
		DriverCommon_DDIM_PRINT(("csyga3 = 0x%x\n",  ioR2yP1.fR2y.csp.csyga.bit.csyga3));
		DriverCommon_DDIM_PRINT(("csybd1 = 0x%x\n",  ioR2yP1.fR2y.csp.csybd.bit.csybd1));
		DriverCommon_DDIM_PRINT(("csybd2 = 0x%x\n",  ioR2yP1.fR2y.csp.csybd.bit.csybd2));
		DriverCommon_DDIM_PRINT(("csybd3 = 0x%x\n",  ioR2yP1.fR2y.csp.csybd.bit.csybd3));
		DriverCommon_DDIM_PRINT(("yrv = 0x%x\n",  ioR2yP1.fR2y.csp.ycrvfx.bit.yrv));
		DriverCommon_DDIM_PRINT(("crv = 0x%x\n",  ioR2yP1.fR2y.csp.ycrvfx.bit.crv));
		DriverCommon_DDIM_PRINT(("cfixen = 0x%x\n",  ioR2yP1.fR2y.csp.ycrvfx.bit.cfixen));
		DriverCommon_DDIM_PRINT(("cfix = 0x%lx\n", ioR2yP1.fR2y.csp.cfix.word));
		DriverCommon_DDIM_PRINT(("cfixb = 0x%x\n",  ioR2yP1.fR2y.csp.cfix.bit.cfixb));
		DriverCommon_DDIM_PRINT(("cfixr = 0x%x\n",  ioR2yP1.fR2y.csp.cfix.bit.cfixr));
		DriverCommon_DDIM_PRINT(("ycof[0] = 0x%lx\n", ioR2yP1.fR2y.csp.ycof.word[0]));
		DriverCommon_DDIM_PRINT(("ycof[1] = 0x%lx\n", ioR2yP1.fR2y.csp.ycof.word[1]));
		DriverCommon_DDIM_PRINT(("yof = 0x%x\n",  ioR2yP1.fR2y.csp.ycof.bit.yof));
		DriverCommon_DDIM_PRINT(("cofb = 0x%x\n",  ioR2yP1.fR2y.csp.ycof.bit.cofb));
		DriverCommon_DDIM_PRINT(("cofr = 0x%x\n",  ioR2yP1.fR2y.csp.ycof.bit.cofr));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT(("csyen = 0x%x\n",  ioR2yP2.fR2y.csp.csyctl.bit.csyen));
		DriverCommon_DDIM_PRINT(("csyky = 0x%x\n",  ioR2yP2.fR2y.csp.csyctl.bit.csyky));
		DriverCommon_DDIM_PRINT(("csytbl = 0x%x\n",  ioR2yP2.fR2y.csp.csyctl.bit.csytbl));
		DriverCommon_DDIM_PRINT(("csyof0 = 0x%x\n",  ioR2yP2.fR2y.csp.csyof.bit.csyof0));
		DriverCommon_DDIM_PRINT(("csyof1 = 0x%x\n",  ioR2yP2.fR2y.csp.csyof.bit.csyof1));
		DriverCommon_DDIM_PRINT(("csyof2 = 0x%x\n",  ioR2yP2.fR2y.csp.csyof.bit.csyof2));
		DriverCommon_DDIM_PRINT(("csyof3 = 0x%x\n",  ioR2yP2.fR2y.csp.csyof.bit.csyof3));
		DriverCommon_DDIM_PRINT(("csyga[0] = 0x%lx\n", ioR2yP2.fR2y.csp.csyga.word[0]));
		DriverCommon_DDIM_PRINT(("csyga[1] = 0x%lx\n", ioR2yP2.fR2y.csp.csyga.word[1]));
		DriverCommon_DDIM_PRINT(("csyga0 = 0x%x\n",  ioR2yP2.fR2y.csp.csyga.bit.csyga0));
		DriverCommon_DDIM_PRINT(("csyga1 = 0x%x\n",  ioR2yP2.fR2y.csp.csyga.bit.csyga1));
		DriverCommon_DDIM_PRINT(("csyga2 = 0x%x\n",  ioR2yP2.fR2y.csp.csyga.bit.csyga2));
		DriverCommon_DDIM_PRINT(("csyga3 = 0x%x\n",  ioR2yP2.fR2y.csp.csyga.bit.csyga3));
		DriverCommon_DDIM_PRINT(("csybd1 = 0x%x\n",  ioR2yP2.fR2y.csp.csybd.bit.csybd1));
		DriverCommon_DDIM_PRINT(("csybd2 = 0x%x\n",  ioR2yP2.fR2y.csp.csybd.bit.csybd2));
		DriverCommon_DDIM_PRINT(("csybd3 = 0x%x\n",  ioR2yP2.fR2y.csp.csybd.bit.csybd3));
		DriverCommon_DDIM_PRINT(("yrv = 0x%x\n",  ioR2yP2.fR2y.csp.ycrvfx.bit.yrv));
		DriverCommon_DDIM_PRINT(("crv = 0x%x\n",  ioR2yP2.fR2y.csp.ycrvfx.bit.crv));
		DriverCommon_DDIM_PRINT(("cfixen = 0x%x\n",  ioR2yP2.fR2y.csp.ycrvfx.bit.cfixen));
		DriverCommon_DDIM_PRINT(("cfix = 0x%lx\n", ioR2yP2.fR2y.csp.cfix.word));
		DriverCommon_DDIM_PRINT(("cfixb = 0x%x\n",  ioR2yP2.fR2y.csp.cfix.bit.cfixb));
		DriverCommon_DDIM_PRINT(("cfixr = 0x%x\n",  ioR2yP2.fR2y.csp.cfix.bit.cfixr));
		DriverCommon_DDIM_PRINT(("ycof[0] = 0x%lx\n", ioR2yP2.fR2y.csp.ycof.word[0]));
		DriverCommon_DDIM_PRINT(("ycof[1] = 0x%lx\n", ioR2yP2.fR2y.csp.ycof.word[1]));
		DriverCommon_DDIM_PRINT(("yof = 0x%x\n",  ioR2yP2.fR2y.csp.ycof.bit.yof));
		DriverCommon_DDIM_PRINT(("cofb = 0x%x\n",  ioR2yP2.fR2y.csp.ycof.bit.cofb));
		DriverCommon_DDIM_PRINT(("cofr = 0x%x\n",  ioR2yP2.fR2y.csp.ycof.bit.cofr));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y18series1_FUNC_NAME
#define 	CtImR2y18series1_FUNC_NAME "ct_im_r2y_18series1_9: "
kint32 ct_im_r2y_18series1_9(CtImR2y18series1 *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y189
	{
		kushort srcTbl[D_IM_R2Y_TABLE_MAX_TONE];
	};
	struct TCtImR2y189 tblBody;
	struct TCtImR2y189* tbl = &tblBody;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y189
	{
		kushort srcTbl[D_IM_R2Y_TABLE_MAX_TONE];
	}* tbl = (struct TCtImR2y189*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //"CO_DEBUG_ON_PC
	kuint32 loopcnt;
	kuint32 loopcnt2;
	kuint32 loopcnt3;
	union UCtImR2y189
	{
		kulong	word;
		struct
		{
			kulong	tc0	:15;
			kulong		:1;
			kulong	tc1	:15;
			kulong		:1;
		}bit;
	} wordConv =
		{
			.bit.tc0 = 0,
			.bit.tc1 = 0,
		};
	kulong regVal;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y18series1_FUNC_NAME));
	for(loopcnt = 0; loopcnt < 3; loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
		switch(loopcnt) {
		// max
			default:
				//		case 0:
				// check: set max value
				for(loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_TONE; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0x7FFF;
				}
				break;
			case 1:
				// check: min max value
				for(loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_TONE; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0;
				}
				break;
			case 2:
				// check: set indvisual value
				for(loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_TONE; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = D_IM_R2Y_TABLE_MAX_TONE - loopcnt2;
				}
				break;
		}
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl3_set_tone_control_table(self->imR2yCtrl3, pipeNo, tbl->srcTbl, 0, D_IM_R2Y_TABLE_MAX_TONE);
		DriverCommon_DDIM_PRINT((CtImR2y18series1_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_set_tone_control_tbl_access_enable(self->imR2yCtrl, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_TONE; loopcnt2 += 2) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP1.tc.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if (loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.tc0;
					} else {
						regVal = wordConv.bit.tc1;
					}
					//	DriverCommon_DDIM_PRINT(("[%u], 0x%x, 0x%x, 0x%lx\n", loopcnt3, regVal,
					//tbl->srcTbl[loopcnt3], wordConv.word));
					if (regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt3));
					}
				}
			}
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_TONE; loopcnt2 += 2) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP2.tc.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.tc0;
					} else {
						regVal = wordConv.bit.tc1;
					}
					//	DriverCommon_DDIM_PRINT(("[%u], 0x%x, 0x%x, 0x%lx\n", loopcnt3,
					//	regVal, tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT(("[%u] unmatch\n", loopcnt3));
					}
				}
			}
		}
		im_r2y_set_tone_control_tbl_access_enable(self->imR2yCtrl, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

CtImR2y18series1* ct_im_r2y_18series1_new(void)
{
	CtImR2y18series1* self = k_object_new_with_private(CT_TYPE_IM_R2Y_18SERIES1, sizeof(CtImR2y18series1Private));

	return self;
}

