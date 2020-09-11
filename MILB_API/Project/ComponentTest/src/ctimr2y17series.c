/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y17series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


// #include "jdsr2yf2e.h" 需要的变量
#include "imr2y.h"
#include "imr2yedge.h"
#include "imr2ystat.h"
#include "imr2yclk.h"
#include "jdsr2yf2e.h"
#include "ctimr2ytool.h"
#include "ctimr2y17series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y17series, ct_im_r2y_17series)
#define CT_IM_R2Y_17SERIES_GET_PRIVATE(o) \
	(K_OBJECT_GET_PRIVATE ((o), CtImR2y17seriesPrivate, CT_TYPE_IM_R2Y_17SERIES))


struct _CtImR2y17seriesPrivate
{

};


/*
 * IMPL
 */
static void ct_im_r2y_17series_constructor(CtImR2y17series *self)
{
	CtImR2y17seriesPrivate *priv = CT_IM_R2Y_17SERIES_GET_PRIVATE(self);
	self->imR2yStat = im_r2y_stat_new();
	self->imR2yEdge = im_r2y_edge_new();
	self->imR2yClk = im_r2y_clk_new();
}

static void ct_im_r2y_17series_destructor(CtImR2y17series *self)
{
	CtImR2y17seriesPrivate *priv = CT_IM_R2Y_17SERIES_GET_PRIVATE(self);
	if(self->imR2yStat){
			k_object_unref(self->imR2yStat);
			self->imR2yStat=NULL;
		}

		if(self->imR2yEdge){
			k_object_unref(self->imR2yEdge);
			self->imR2yEdge=NULL;
		}

		if(self->imR2yClk){
				k_object_unref(self->imR2yClk);
				self->imR2yClk=NULL;
			}
}


/*
 * PUBLIC
 */
#undef 	CtImR2y17series_FUNC_NAME
#define 	CtImR2y17series_FUNC_NAME "ct_im_r2y_17series_4: "
kint32 ct_im_r2y_17series_4(CtImR2y17series *self, kuchar pipeNo)
{
	kint32 ercd;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y17series_FUNC_NAME));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_medium_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo,
			ImR2y_ENABLE_ON, ImR2y_WAIT_OFF);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_medium_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo,
			ImR2y_ENABLE_OFF, ImR2y_WAIT_ON);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_medium_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo,
			ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_medium_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo,
			ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y17series_FUNC_NAME
#define 	CtImR2y17series_FUNC_NAME "ct_im_r2y_17series_5: "
kint32 ct_im_r2y_17series_5(CtImR2y17series *self, kuchar pipeNo)
{
	kint32 ercd;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y17series_FUNC_NAME));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_medium_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo,
			ImR2y_ENABLE_ON, ImR2y_WAIT_OFF);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_medium_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo,
			ImR2y_ENABLE_OFF, ImR2y_WAIT_ON);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_medium_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo,
			ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_medium_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo,
			ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y17series_FUNC_NAME
#define 	CtImR2y17series_FUNC_NAME "ct_im_r2y_17series_6: "
kint32 ct_im_r2y_17series_6(CtImR2y17series *self, kuchar pipeNo)
{
	TImR2yCtrlLedge r2yCtrlLedge[] =
		{
				// max
				[0] =
					{
							.edgeEnable = 1,
							.scaleEnable = 1,
							.tableClipSelect = 1,
							.scaleTableResol = 2,
							.scaleTableSelect = 3,
							.gradationTableResol = 2,
							.gradationTableSelect = 3,
							.hpfK =
								{
										0x3FF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, },
							.corpOffset =
								{
										0x3FF, 0x3FF, 0x3FF, 0x3FF, },
							.corpGain =
								{
										0x7F, 0x7F, 0x7F, 0x7F, },
							.corpBorder =
								{
										0x3FF, 0x3FF, 0x3FF, },
							.cormOffset =
								{
										0x3FF, 0x3FF, 0x3FF, 0x3FF, },
							.cormGain =
								{
										0x7F, 0x7F, 0x7F, 0x7F, },
							.cormBorder =
								{
										0x3FF, 0x3FF, 0x3FF, },
							.supScl = 0x3F,
							.levelClipPOffset =
								{
										0x1FF, 0x1FF, 0x1FF, },
							.levelClipPGain =
								{
										0x7F, 0x7F, 0x7F, },
							.levelClipPBorder =
								{
										0x3FF, 0x3FF, },
							.levelClipMOffset =
								{
										0x1FF, 0x1FF, 0x1FF, },
							.levelClipMGain =
								{
										0x7F, 0x7F, 0x7F, },
							.levelClipMBorder =
								{
										0x3FF, 0x3FF, }, },
				// min
				[1] =
					{
							.edgeEnable = 0,
							.scaleEnable = 0,
							.tableClipSelect = 0,
							.scaleTableResol = 0,
							.scaleTableSelect = 0,
							.gradationTableResol = 0,
							.gradationTableSelect = 0,
							.hpfK =
								{
										0, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, },
							.corpOffset =
								{
										0, 0, 0, 0, },
							.corpGain =
								{
										-0x80, -0x80, -0x80, -0x80, },
							.corpBorder =
								{
										0, 0, 0, },
							.cormOffset =
								{
										0, 0, 0, 0, },
							.cormGain =
								{
										-0x80, -0x80, -0x80, -0x80, },
							.cormBorder =
								{
										0, 0, 0, },
							.supScl = 0,
							.levelClipPOffset =
								{
									0, 0, 0, },
							.levelClipPGain =
								{
									-0x80, -0x80, -0x80, },
							.levelClipPBorder =
								{
										0, 0, },
							.levelClipMOffset =
								{
										0, 0, 0, },
							.levelClipMGain =
								{
										-0x80, -0x80, -0x80, },
							.levelClipMBorder =
								{
										0, 0, }, },
				// indvisual
				[2] =
					{
							.edgeEnable = 1,
							.scaleEnable = 0,
							.tableClipSelect = 0,
							.scaleTableResol = 1,
							.scaleTableSelect = 1,
							.gradationTableResol = 1,
							.gradationTableSelect = 1,
							.hpfK =
								{
									0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, },
							.corpOffset =
								{
									0xB, 0xC, 0xD, 0xE, },
							.corpGain =
								{
									0xF, 0x10, 0x11, 0x12, },
							.corpBorder =
								{
									0x13, 0x14, 0x15, },
							.cormOffset =
								{
									0x16, 0x17, 0x18, 0x19, },
							.cormGain =
								{
									0x1A, 0x1B, 0x1C, 0x1D, },
							.cormBorder =
								{
									0x1E, 0x1F, 0x20, },
							.supScl = 0x21,
							.levelClipPOffset =
								{
									0x22, 0x23, 0x24, },
							.levelClipPGain =
								{
									0x25, 0x26, 0x27, },
							.levelClipPBorder =
								{
									0x28, 0x29, },
							.levelClipMOffset =
								{
									0x2A, 0x2B, 0x2C, },
							.levelClipMGain =
								{
									0x2D, 0x2E, 0x2F, },
							.levelClipMBorder =
								{
									0x30, 0x31, }, },
		};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint loopcnt;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y17series_FUNC_NAME));
	for (loopcnt = 0; loopcnt < (sizeof(r2yCtrlLedge) / sizeof(r2yCtrlLedge[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_edge_ctrl_low_edge(self->imR2yEdge, pipeNo, &r2yCtrlLedge[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwen = %u\n",
				ioR2yP1.fR2y.eglw.eglwctl.bit.eglwen));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwmp = %u\n",
				ioR2yP1.fR2y.eglw.eglwctl.bit.eglwmp));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwtc = %u\n",
				ioR2yP1.fR2y.eglw.eglwctl.bit.eglwtc));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwsclres = %u\n",
				ioR2yP1.fR2y.eglw.eglwctl.bit.eglwsclres));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwscltbl = %u\n",
				ioR2yP1.fR2y.eglw.eglwctl.bit.eglwscltbl));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwtcres = %u\n",
				ioR2yP1.fR2y.eglw.eglwctl.bit.eglwtcres));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwtctbl = %u\n",
				ioR2yP1.fR2y.eglw.eglwctl.bit.eglwtctbl));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk[0] = 0x%lx\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.word[0]));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk[1] = 0x%lx\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.word[1]));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk[2] = 0x%lx\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.word[2]));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk0 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.bit.eglwhpfk0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.bit.eglwhpfk1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.bit.eglwhpfk2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk3 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.bit.eglwhpfk3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk4 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.bit.eglwhpfk4));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk5 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.bit.eglwhpfk5));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk6 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.bit.eglwhpfk6));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk7 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.bit.eglwhpfk7));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk8 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.bit.eglwhpfk8));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk9 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwhpfk.bit.eglwhpfk9));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpof0 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcorpof.bit.eglwcorpof0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpof1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcorpof.bit.eglwcorpof1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpof2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcorpof.bit.eglwcorpof2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpof3 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcorpof.bit.eglwcorpof3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpga = 0x%lx\n",
				ioR2yP1.fR2y.eglw.eglwcorpga.word));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpga0 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcorpga.bit.eglwcorpga0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpga1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcorpga.bit.eglwcorpga1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpga2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcorpga.bit.eglwcorpga2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpga3 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcorpga.bit.eglwcorpga3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpbd1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcorpbd.bit.eglwcorpbd1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpbd2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcorpbd.bit.eglwcorpbd2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpbd3 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcorpbd.bit.eglwcorpbd3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormof0 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcormof.bit.eglwcormof0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormof1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcormof.bit.eglwcormof1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormof2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcormof.bit.eglwcormof2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormof3 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcormof.bit.eglwcormof3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormga = 0x%lx\n",
				ioR2yP1.fR2y.eglw.eglwcormga.word));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormga0 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcormga.bit.eglwcormga0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormga1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcormga.bit.eglwcormga1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormga2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcormga.bit.eglwcormga2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormga3 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcormga.bit.eglwcormga3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormbd1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcormbd.bit.eglwcormbd1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormbd2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcormbd.bit.eglwcormbd2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormbd3 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwcormbd.bit.eglwcormbd3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwsclsup = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwsclsup.bit.eglwsclsup));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppof0 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclppof.bit.eglwclppof0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppof1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclppof.bit.eglwclppof1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppof2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclppof.bit.eglwclppof2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppga = 0x%lx\n",
				ioR2yP1.fR2y.eglw.eglwclppga.word));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppga0 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclppga.bit.eglwclppga0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppga1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclppga.bit.eglwclppga1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppga2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclppga.bit.eglwclppga2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppbd1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclppbd.bit.eglwclppbd1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppbd2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclppbd.bit.eglwclppbd2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmof0 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclpmof.bit.eglwclpmof0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmof1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclpmof.bit.eglwclpmof1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmof2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclpmof.bit.eglwclpmof2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmga = 0x%lx\n",
				ioR2yP1.fR2y.eglw.eglwclpmga.word));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmga0 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclpmga.bit.eglwclpmga0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmga1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclpmga.bit.eglwclpmga1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmga2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclpmga.bit.eglwclpmga2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmbd1 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclpmbd.bit.eglwclpmbd1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmbd2 = 0x%x\n",
				ioR2yP1.fR2y.eglw.eglwclpmbd.bit.eglwclpmbd2));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwen = %u\n",
				ioR2yP2.fR2y.eglw.eglwctl.bit.eglwen));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwmp = %u\n",
				ioR2yP2.fR2y.eglw.eglwctl.bit.eglwmp));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwtc = %u\n",
				ioR2yP2.fR2y.eglw.eglwctl.bit.eglwtc));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwsclres = %u\n",
				ioR2yP2.fR2y.eglw.eglwctl.bit.eglwsclres));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwscltbl = %u\n",
				ioR2yP2.fR2y.eglw.eglwctl.bit.eglwscltbl));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwtcres = %u\n",
				ioR2yP2.fR2y.eglw.eglwctl.bit.eglwtcres));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "EGLWTCTB = %u\n",
				ioR2yP2.fR2y.eglw.eglwctl.bit.eglwtctbl));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk[0] = 0x%lx\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.word[0]));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk[1] = 0x%lx\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.word[1]));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk[2] = 0x%lx\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.word[2]));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk0 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.bit.eglwhpfk0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.bit.eglwhpfk1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.bit.eglwhpfk2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk3 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.bit.eglwhpfk3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk4 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.bit.eglwhpfk4));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk5 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.bit.eglwhpfk5));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk6 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.bit.eglwhpfk6));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk7 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.bit.eglwhpfk7));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk8 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.bit.eglwhpfk8));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwhpfk9 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwhpfk.bit.eglwhpfk9));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpof0 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcorpof.bit.eglwcorpof0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpof1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcorpof.bit.eglwcorpof1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpof2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcorpof.bit.eglwcorpof2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpof3 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcorpof.bit.eglwcorpof3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpga = 0x%lx\n",
				ioR2yP2.fR2y.eglw.eglwcorpga.word));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpga0 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcorpga.bit.eglwcorpga0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpga1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcorpga.bit.eglwcorpga1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpga2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcorpga.bit.eglwcorpga2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpga3 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcorpga.bit.eglwcorpga3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpbd1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcorpbd.bit.eglwcorpbd1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcorpbd2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcorpbd.bit.eglwcorpbd2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "EGLWCORPBD_3 = 0x%x\n",
				ioR2yP2.fR2y.eglw.EGLWCORPBD.bit.EGLWCORPBD_3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormof0 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcormof.bit.eglwcormof0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormof1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcormof.bit.eglwcormof1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormof2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcormof.bit.eglwcormof2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormof3 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcormof.bit.eglwcormof3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormga = 0x%lx\n",
				ioR2yP2.fR2y.eglw.eglwcormga.word));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormga0 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcormga.bit.eglwcormga0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormga1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcormga.bit.eglwcormga1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormga2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcormga.bit.eglwcormga2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormga3 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcormga.bit.eglwcormga3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormbd1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcormbd.bit.eglwcormbd1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormbd2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcormbd.bit.eglwcormbd2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwcormbd3 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwcormbd.bit.eglwcormbd3));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwsclsup = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwsclsup.bit.eglwsclsup));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppof0 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclppof.bit.eglwclppof0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppof1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclppof.bit.eglwclppof1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppof2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclppof.bit.eglwclppof2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppga = 0x%lx\n",
				ioR2yP2.fR2y.eglw.eglwclppga.word));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppga0 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclppga.bit.eglwclppga0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppga1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclppga.bit.eglwclppga1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppga2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclppga.bit.eglwclppga2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppbd1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclppbd.bit.eglwclppbd1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclppbd2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclppbd.bit.eglwclppbd2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmof0 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclpmof.bit.eglwclpmof0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmof1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclpmof.bit.eglwclpmof1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmof2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclpmof.bit.eglwclpmof2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmga = 0x%lx\n",
				ioR2yP2.fR2y.eglw.eglwclpmga.word));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmga0 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclpmga.bit.eglwclpmga0));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmga1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclpmga.bit.eglwclpmga1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmga2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclpmga.bit.eglwclpmga2));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmbd1 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclpmbd.bit.eglwclpmbd1));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "eglwclpmbd2 = 0x%x\n",
				ioR2yP2.fR2y.eglw.eglwclpmbd.bit.eglwclpmbd2));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y17series_FUNC_NAME
#define 	CtImR2y17series_FUNC_NAME "ct_im_r2y_17series_7: "
kint32 ct_im_r2y_17series_7(CtImR2y17series *self, kuchar pipeNo)
{
	kint32 ercd;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y17series_FUNC_NAME));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_low_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_OFF);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_low_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_ON);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_low_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_low_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y17series_FUNC_NAME
#define 	CtImR2y17series_FUNC_NAME "ct_im_r2y_17series_8: "
kint32 ct_im_r2y_17series_8(CtImR2y17series *self, kuchar pipeNo)
{
	kint32 ercd;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y17series_FUNC_NAME));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_low_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_OFF);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_low_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_ON);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_low_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif
	ercd = im_r2y_edge_set_low_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
	DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStatself->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y17series_FUNC_NAME
#define 	CtImR2y17series_FUNC_NAME "ct_im_r2y_17series_9: "
kint32 ct_im_r2y_17series_9(CtImR2y17series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kuchar tR2yEnable;
	kint32 ercd;
#endif

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y17series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	if (CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		ioR2yP1.fR2y.cntl.r2yflag.bit.ycfact = 0;
		ercd = im_r2y_edge_is_act_post_filter(self->imR2yEdge, pipeNo, &tR2yEnable);
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "%u\n", tR2yEnable));
		ioR2yP1.fR2y.cntl.r2yflag.bit.ycfact = 1;
		ercd = im_r2y_edge_is_act_post_filter(self->imR2yEdge, pipeNo, &tR2yEnable);
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "%u\n", tR2yEnable));
		ioR2yP1.fR2y.cntl.r2yflag.bit.ycfact = 0;
		ercd = im_r2y_edge_is_act_post_filter(self->imR2yEdge, pipeNo, &tR2yEnable);
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "%u\n", tR2yEnable));
	}
	if (CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		ioR2yP2.fR2y.cntl.r2yflag.bit.ycfact = 0;
		ercd = im_r2y_edge_is_act_post_filter(self->imR2yEdge, pipeNo, &tR2yEnable);
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "%u\n", tR2yEnable));
		ioR2yP2.fR2y.cntl.r2yflag.bit.ycfact = 1;
		ercd = im_r2y_edge_is_act_post_filter(self->imR2yEdge, pipeNo, &tR2yEnable);
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "%u\n", tR2yEnable));
		ioR2yP2.fR2y.cntl.r2yflag.bit.ycfact = 0;
		ercd = im_r2y_edge_is_act_post_filter(self->imR2yEdge, pipeNo, &tR2yEnable);
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "0x%x\n", ercd));
		DriverCommon_DDIM_PRINT((CtImR2y17series_FUNC_NAME "%u\n", tR2yEnable));
	}
#endif

	return D_DDIM_OK; //需改
}

CtImR2y17series* ct_im_r2y_17series_new(void)
{
	CtImR2y17series* self = k_object_new_with_private(CT_TYPE_IM_R2Y_17SERIES, sizeof(CtImR2y17seriesPrivate));

	return self;
}
