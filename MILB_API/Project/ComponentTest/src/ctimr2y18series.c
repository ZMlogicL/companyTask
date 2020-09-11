/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 梁正明
*@brief : CtImR2y18series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "imr2ystat.h"
#include "imr2yclk.h"
#include "imr2yedge.h"
#include "imr2yctrl3.h"
#include "ctimr2y18series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y18series, ct_im_r2y_18series)
#define CT_IM_R2Y_18SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y18seriesPrivate, CT_TYPE_IM_R2Y_18SERIES))


struct _CtImR2y18seriesPrivate
{

};


/*
 * IMPL
 */
static void ct_im_r2y_18series_constructor(CtImR2y18series *self)
{
	CtImR2y18seriesPrivate *priv = CT_IM_R2Y_18SERIES_GET_PRIVATE(self);
	self->imR2yEdge = im_r2y_edge_new();
	self->imR2yClk = im_r2y_clk_new();
	self->imR2yStat = im_r2y_stat_new();
	self->imR2yCtrl3 = im_r2y_ctrl3_new();
}

static void ct_im_r2y_18series_destructor(CtImR2y18series *self)
{
	CtImR2y18seriesPrivate *priv = CT_IM_R2Y_18SERIES_GET_PRIVATE(self);
			if(self->imR2yEdge){
				k_object_unref(self->imR2yEdge);
				self->imR2yEdge=NULL;
			}

			if(self->imR2yClk){
				k_object_unref(self->imR2yClk);
				self->imR2yClk=NULL;
			}

			if(self->imR2yStat){
					k_object_unref(self->imR2yStat);
					self->imR2yStat=NULL;
			}

			if(self->imR2yCtrl3){
								k_object_unref(self->imR2yCtrl3);
								self->imR2yCtrl3=NULL;
						}
}


/*
 * PUBLIC
 */
#undef 	CtImR2y18series_FUNC_NAME
#define 	CtImR2y18series_FUNC_NAME "ct_im_r2y_18series_0: "
kint32 ct_im_r2y_18series_0(CtImR2y18series *self, kuchar pipeNo)
{
	TImR2yCtrlEdgeDotNoise r2yCtrlEdgeDot[] =
		{
				// max
				[0] =
					{
							.hfEnable = 1,
							.mfEnable = 1,
							.hfPThreshold = 0x3FF,
							.hfMThreshold = 0x3FF,
							.hfPCoef = 8,
							.hfMCoef = 8,
							.mfPThreshold = 0x3FF,
							.mfMThreshold = 0x3FF,
							.mfPCoef = 8,
							.mfMCoef = 8,
					},
				// min
				[1] = {
							.hfEnable = 0,
							.mfEnable = 0,
							.hfPThreshold = 0,
							.hfMThreshold = 0,
							.hfPCoef = 0,
							.hfMCoef = 0,
							.mfPThreshold = 0,
							.mfMThreshold = 0,
							.mfPCoef = 0,
							.mfMCoef = 0,
						},
				// indvisual
				[2] =
						{
								.hfEnable = 1,
								.mfEnable = 1,
								.hfPThreshold = 0x11,
								.hfMThreshold = 0x12,
								.hfPCoef = 2,
								.hfMCoef = 3,
								.mfPThreshold = 0x13,
								.mfMThreshold = 0x14,
								.mfPCoef = 4,
								.mfMCoef = 5,
						},
		};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y18series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < (sizeof(r2yCtrlEdgeDot) / sizeof(r2yCtrlEdgeDot[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_edge_ctrl_dot_noise(self->imR2yEdge, pipeNo, &r2yCtrlEdgeDot[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdthw = 0x%x\n",
				ioR2yP1.fR2y.egdt.egdtctl.bit.egdthw));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdtmw = 0x%x\n",
				ioR2yP1.fR2y.egdt.egdtctl.bit.egdtmw));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdthwthp = 0x%x\n",
				ioR2yP1.fR2y.egdt.egdthwth.bit.egdthwthp));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdthwthm = 0x%x\n",
				ioR2yP1.fR2y.egdt.egdthwth.bit.egdthwthm));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdthwkp = 0x%x\n",
				ioR2yP1.fR2y.egdt.egdthwk.bit.egdthwkp));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdthwkm = 0x%x\n",
				ioR2yP1.fR2y.egdt.egdthwk.bit.egdthwkm));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdtmwthp = 0x%x\n",
				ioR2yP1.fR2y.egdt.egdtmwth.bit.egdtmwthp));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdtmwthm = 0x%x\n",
				ioR2yP1.fR2y.egdt.egdtmwth.bit.egdtmwthm));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdtmwkp = 0x%x\n",
				ioR2yP1.fR2y.egdt.egdtmwk.bit.egdtmwkp));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdtmwkm = 0x%x\n",
				ioR2yP1.fR2y.egdt.egdtmwk.bit.egdtmwkm));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdthw = 0x%x\n",
				ioR2yP2.fR2y.egdt.egdtctl.bit.egdthw));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdtmw = 0x%x\n",
				ioR2yP2.fR2y.egdt.egdtctl.bit.egdtmw));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdthwthp = 0x%x\n",
				ioR2yP2.fR2y.egdt.egdthwth.bit.egdthwthp));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdthwthm = 0x%x\n",
				ioR2yP2.fR2y.egdt.egdthwth.bit.egdthwthm));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdthwkp = 0x%x\n",
				ioR2yP2.fR2y.egdt.egdthwk.bit.egdthwkp));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdthwkm = 0x%x\n",
				ioR2yP2.fR2y.egdt.egdthwk.bit.egdthwkm));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdtmwthp = 0x%x\n",
				ioR2yP2.fR2y.egdt.egdtmwth.bit.egdtmwthp));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdtmwthm = 0x%x\n",
				ioR2yP2.fR2y.egdt.egdtmwth.bit.egdtmwthm));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdtmwkp = 0x%x\n",
				ioR2yP2.fR2y.egdt.egdtmwk.bit.egdtmwkp));
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "egdtmwkm = 0x%x\n",
				ioR2yP2.fR2y.egdt.egdtmwk.bit.egdtmwkm));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y18series_FUNC_NAME
#define 	CtImR2y18series_FUNC_NAME "ct_im_r2y_18series_1: "
kint32 ct_im_r2y_18series_1(CtImR2y18series *self, kuchar pipeNo)
{
	TImR2yCtrlMapscl r2yCtrlMapscl[] =
		{
			// max
			[0] =
				{
					.blockSizeh = 0x3FE,
					.blockSizeV = 0x3FF,
					.recipMultipliH = 0x3FFF,
					.recipMultipliShiftH = 6,
					.recipMultipliV = 0x3FFF,
					.recipMultipliShiftV = 6,
					.blockStartH = 0xF,
					.blockStartCoordH = 0x3FE,
					.blockStartV = 0xB,
					.blockStartCoordV = 0x3FF,
				},
			// min
			[1] =
				{
					.blockSizeh = 0x10,
					.blockSizeV = 0x10,
					.recipMultipliH = 0,
					.recipMultipliShiftH = 0,
					.recipMultipliV = 0,
					.recipMultipliShiftV = 0,
					.blockStartH = 0,
					.blockStartCoordH = 0,
					.blockStartV = 0,
					.blockStartCoordV = 0,
				},
			// min
			[2] =
				{
					.blockSizeh = 0x11,
					.blockSizeV = 0x22,
					.recipMultipliH = 0x33,
					.recipMultipliShiftH = 0x4,
					.recipMultipliV = 0x55,
					.recipMultipliShiftV = 0x6,
					.blockStartH = 0x7,
					.blockStartCoordH = 0x88,
					.blockStartV = 0x9,
					.blockStartCoordV = 0xAA,
				},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y18series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < (sizeof(r2yCtrlMapscl) / sizeof(r2yCtrlMapscl[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl3_map_scl(self->imR2yCtrl3, pipeNo, &r2yCtrlMapscl[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT(("egmpsizh = 0x%x\n", ioR2yP1.fR2y.mapscl.egmpsiz.bit.egmpsizh));
		DriverCommon_DDIM_PRINT(("egmpsizv = 0x%x\n", ioR2yP1.fR2y.mapscl.egmpsiz.bit.egmpsizv));
		DriverCommon_DDIM_PRINT(("egmpinvh = 0x%x\n", ioR2yP1.fR2y.mapscl.egmpsizhinv.bit.egmpinvh));
		DriverCommon_DDIM_PRINT(("egmpinvsfth = 0x%x\n", ioR2yP1.fR2y.mapscl.egmpsizhinv.bit.egmpinvsfth));
		DriverCommon_DDIM_PRINT(("egmpinvv = 0x%x\n", ioR2yP1.fR2y.mapscl.egmpsizvinv.bit.egmpinvv));
		DriverCommon_DDIM_PRINT(("egmpinvsftv = 0x%x\n", ioR2yP1.fR2y.mapscl.egmpsizvinv.bit.egmpinvsftv));
		DriverCommon_DDIM_PRINT(("egmpstabh = 0x%x\n", ioR2yP1.fR2y.mapscl.egmpstaph.bit.egmpstabh));
		DriverCommon_DDIM_PRINT(("egmpstach = 0x%x\n", ioR2yP1.fR2y.mapscl.egmpstaph.bit.egmpstach));
		DriverCommon_DDIM_PRINT(("egmpstabv = 0x%x\n", ioR2yP1.fR2y.mapscl.egmpstapv.bit.egmpstabv));
		DriverCommon_DDIM_PRINT(("egmpstacv = 0x%x\n", ioR2yP1.fR2y.mapscl.egmpstapv.bit.egmpstacv));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT(("egmpsizh = 0x%x\n", ioR2yP2.fR2y.mapscl.egmpsiz.bit.egmpsizh));
		DriverCommon_DDIM_PRINT(("egmpsizv = 0x%x\n", ioR2yP2.fR2y.mapscl.egmpsiz.bit.egmpsizv));
		DriverCommon_DDIM_PRINT(("egmpinvh = 0x%x\n", ioR2yP2.fR2y.mapscl.egmpsizhinv.bit.egmpinvh));
		DriverCommon_DDIM_PRINT(("egmpinvsfth = 0x%x\n", ioR2yP2.fR2y.mapscl.egmpsizhinv.bit.egmpinvsfth));
		DriverCommon_DDIM_PRINT(("egmpinvv = 0x%x\n", ioR2yP2.fR2y.mapscl.egmpsizvinv.bit.egmpinvv));
		DriverCommon_DDIM_PRINT(("egmpinvsftv = 0x%x\n", ioR2yP2.fR2y.mapscl.egmpsizvinv.bit.egmpinvsftv));
		DriverCommon_DDIM_PRINT(("egmpstabh = 0x%x\n", ioR2yP2.fR2y.mapscl.egmpstaph.bit.egmpstabh));
		DriverCommon_DDIM_PRINT(("egmpstach = 0x%x\n", ioR2yP2.fR2y.mapscl.egmpstaph.bit.egmpstach));
		DriverCommon_DDIM_PRINT(("egmpstabv = 0x%x\n", ioR2yP2.fR2y.mapscl.egmpstapv.bit.egmpstabv));
		DriverCommon_DDIM_PRINT(("egmpstacv = 0x%x\n", ioR2yP2.fR2y.mapscl.egmpstapv.bit.egmpstacv));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y18series_FUNC_NAME
#define	CtImR2y18series_FUNC_NAME "ct_im_r2y_18series_2: "
kint32 ct_im_r2y_18series_2(CtImR2y18series *self, kuchar pipeNo)
{
	kint32 ercd;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y18series_FUNC_NAME));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif
	ercd = im_r2y_ctrl3_set_map_scl_tbl_access_enable(self->imR2yCtrl3, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_OFF);
	DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif
	ercd = im_r2y_ctrl3_set_map_scl_tbl_access_enable(self->imR2yCtrl3, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_ON);
	DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif
	ercd = im_r2y_ctrl3_set_map_scl_tbl_access_enable(self->imR2yCtrl3, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
	DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif
	ercd = im_r2y_ctrl3_set_map_scl_tbl_access_enable(self->imR2yCtrl3, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
	DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "0x%x\n", ercd));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y18series_FUNC_NAME
#define 	CtImR2y18series_FUNC_NAME "ct_im_r2y_18series_3: "
kint32 ct_im_r2y_18series_3(CtImR2y18series *self, kuchar pipeNo)
{
	TImR2yCtrlEdgeBlend r2yCtrlEdgeBlend[] =
		{
			// max
			[0] =
				{
					.blendType = 1,
					.border =
						{
							0x3FF, 0x3FF, 0x3FF,
						},
					.alphaOffset =
						{
							0xFF, 0xFF, 0xFF, 0xFF,
						},
					.alphaGain =
						{
							0x1FF, 0x1FF, 0x1FF, 0x1FF,
						},
					.betaOffset =
						{
							0xFF, 0xFF, 0xFF, 0xFF,
						},
					.betaGain =
						{
							0x1FF, 0x1FF, 0x1FF, 0x1FF,
						},
					.levelClipP = 0x1FF,
					.levelClipM = 0x1FF,
				},
			// min
			[1] =
				{
					.blendType = 0,
					.border =
						{
							0, 0, 0,
						},
					.alphaOffset =
						{
							0, 0, 0, 0,
						},
					.alphaGain =
						{
							-0x200, -0x200, -0x200, -0x200,
						},
					.betaOffset =
						{
							0, 0, 0, 0,
						},
					.betaGain =
						{
							-0x200, -0x200, -0x200, -0x200,
						},
					.levelClipP = 0,
					.levelClipM = 0,
				},
			// indvisual
			[2] =
				{
					.blendType = 0x1,
					.border =
						{
							0x2, 0x3, 0x4,
						},
					.alphaOffset =
						{
							0x5, 0x6, 0x7, 0x8,
						},
					.alphaGain =
						{
							0x9, 0xA, 0xB, 0xC,
						},
					.betaOffset =
						{
							0xD, 0xE, 0xF, 0x10,
						},
					.betaGain =
						{
							0x11, 0x12, 0x13, 0x14,
						},
					.levelClipP = 0x15,
					.levelClipM = 0x16,
			},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y18series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < (sizeof(r2yCtrlEdgeBlend) / sizeof(r2yCtrlEdgeBlend[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_edge_ctrl_blend(self->imR2yEdge, pipeNo, &r2yCtrlEdgeBlend[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT(("egcmps = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpctl.bit.egcmps));
		DriverCommon_DDIM_PRINT(("egcmpbd1 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpbd.bit.egcmpbd1));
		DriverCommon_DDIM_PRINT(("egcmpbd2 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpbd.bit.egcmpbd2));
		DriverCommon_DDIM_PRINT(("egcmpbd3 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpbd.bit.egcmpbd3));
		DriverCommon_DDIM_PRINT(("egcmpalpof0 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpalpof.bit.egcmpalpof0));
		DriverCommon_DDIM_PRINT(("egcmpalpof1 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpalpof.bit.egcmpalpof1));
		DriverCommon_DDIM_PRINT(("egcmpalpof2 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpalpof.bit.egcmpalpof2));
		DriverCommon_DDIM_PRINT(("egcmpalpof3 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpalpof.bit.egcmpalpof3));
		DriverCommon_DDIM_PRINT(("egcmpalpga[0] = 0x%lx\n", ioR2yP1.fR2y.egcmp.egcmpalpga.word[0]));
		DriverCommon_DDIM_PRINT(("egcmpalpga[1] = 0x%lx\n", ioR2yP1.fR2y.egcmp.egcmpalpga.word[1]));
		DriverCommon_DDIM_PRINT(("egcmpalpga0 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpalpga.bit.egcmpalpga0));
		DriverCommon_DDIM_PRINT(("egcmpalpga1 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpalpga.bit.egcmpalpga1));
		DriverCommon_DDIM_PRINT(("egcmpalpga2 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpalpga.bit.egcmpalpga2));
		DriverCommon_DDIM_PRINT(("egcmpalpga3 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpalpga.bit.egcmpalpga3));
		DriverCommon_DDIM_PRINT(("egcmpbtaof0 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpbtaof.bit.egcmpbtaof0));
		DriverCommon_DDIM_PRINT(("egcmpbtaof1 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpbtaof.bit.egcmpbtaof1));
		DriverCommon_DDIM_PRINT(("egcmpbtaof2 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpbtaof.bit.egcmpbtaof2));
		DriverCommon_DDIM_PRINT(("egcmpbtaof3 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpbtaof.bit.egcmpbtaof3));
		DriverCommon_DDIM_PRINT(("egcmpbtaga[0] = 0x%lx\n", ioR2yP1.fR2y.egcmp.egcmpbtaga.word[0]));
		DriverCommon_DDIM_PRINT(("egcmpbtaga[1] = 0x%lx\n", ioR2yP1.fR2y.egcmp.egcmpbtaga.word[1]));
		DriverCommon_DDIM_PRINT(("egcmpbtaga0 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpbtaga.bit.egcmpbtaga0));
		DriverCommon_DDIM_PRINT(("egcmpbtaga1 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpbtaga.bit.egcmpbtaga1));
		DriverCommon_DDIM_PRINT(("egcmpbtaga2 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpbtaga.bit.egcmpbtaga2));
		DriverCommon_DDIM_PRINT(("egcmpbtaga3 = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpbtaga.bit.egcmpbtaga3));
		DriverCommon_DDIM_PRINT(("egcmpclpp = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpclp.bit.egcmpclpp));
		DriverCommon_DDIM_PRINT(("egcmpclpm = 0x%x\n",  ioR2yP1.fR2y.egcmp.egcmpclp.bit.egcmpclpm));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT(("egcmps = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpctl.bit.egcmps));
		DriverCommon_DDIM_PRINT(("egcmpbd1 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpbd.bit.egcmpbd1));
		DriverCommon_DDIM_PRINT(("egcmpbd2 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpbd.bit.egcmpbd2));
		DriverCommon_DDIM_PRINT(("egcmpbd3 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpbd.bit.egcmpbd3));
		DriverCommon_DDIM_PRINT(("egcmpalpof0 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpalpof.bit.egcmpalpof0));
		DriverCommon_DDIM_PRINT(("egcmpalpof1 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpalpof.bit.egcmpalpof1));
		DriverCommon_DDIM_PRINT(("egcmpalpof2 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpalpof.bit.egcmpalpof2));
		DriverCommon_DDIM_PRINT(("egcmpalpof3 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpalpof.bit.egcmpalpof3));
		DriverCommon_DDIM_PRINT(("egcmpalpga[0] = 0x%lx\n", ioR2yP2.fR2y.egcmp.egcmpalpga.word[0]));
		DriverCommon_DDIM_PRINT(("egcmpalpga[1] = 0x%lx\n", ioR2yP2.fR2y.egcmp.egcmpalpga.word[1]));
		DriverCommon_DDIM_PRINT(("egcmpalpga0 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpalpga.bit.egcmpalpga0));
		DriverCommon_DDIM_PRINT(("egcmpalpga1 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpalpga.bit.egcmpalpga1));
		DriverCommon_DDIM_PRINT(("egcmpalpga2 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpalpga.bit.egcmpalpga2));
		DriverCommon_DDIM_PRINT(("egcmpalpga3 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpalpga.bit.egcmpalpga3));
		DriverCommon_DDIM_PRINT(("egcmpbtaof0 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpbtaof.bit.egcmpbtaof0));
		DriverCommon_DDIM_PRINT(("egcmpbtaof1 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpbtaof.bit.egcmpbtaof1));
		DriverCommon_DDIM_PRINT(("egcmpbtaof2 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpbtaof.bit.egcmpbtaof2));
		DriverCommon_DDIM_PRINT(("egcmpbtaof3 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpbtaof.bit.egcmpbtaof3));
		DriverCommon_DDIM_PRINT(("egcmpbtaga[0] = 0x%lx\n", ioR2yP2.fR2y.egcmp.egcmpbtaga.word[0]));
		DriverCommon_DDIM_PRINT(("egcmpbtaga[1] = 0x%lx\n", ioR2yP2.fR2y.egcmp.egcmpbtaga.word[1]));
		DriverCommon_DDIM_PRINT(("egcmpbtaga0 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpbtaga.bit.egcmpbtaga0));
		DriverCommon_DDIM_PRINT(("egcmpbtaga1 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpbtaga.bit.egcmpbtaga1));
		DriverCommon_DDIM_PRINT(("egcmpbtaga2 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpbtaga.bit.egcmpbtaga2));
		DriverCommon_DDIM_PRINT(("egcmpbtaga3 = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpbtaga.bit.egcmpbtaga3));
		DriverCommon_DDIM_PRINT(("egcmpclpp = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpclp.bit.egcmpclpp));
		DriverCommon_DDIM_PRINT(("egcmpclpm = 0x%x\n",  ioR2yP2.fR2y.egcmp.egcmpclp.bit.egcmpclpm));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y18series_FUNC_NAME
#define 	CtImR2y18series_FUNC_NAME "ct_im_r2y_18series_4: "
kint32 ct_im_r2y_18series_4(CtImR2y18series *self, kuchar pipeNo)
{
	TImR2yCtrlCRefEdgeTextureAdjCommon r2yCtrlCRefEdgeTextureAdjCommon[] =
		{
			// max
			[0] =
				{
					.cbAFocus1Pos = 0x7F,
					.crAFocus1Pos = 0x7F,
					.cbAFocus2Pos = 0x7F,
					.crAFocus2Pos = 0x7F,
					.cbBFocus1Pos = 0x7F,
					.crBFocus1Pos = 0x7F,
					.cbBFocus2Pos = 0x7F,
					.crBFocus2Pos = 0x7F,
				},
			// min
			[1] =
				{
					.cbAFocus1Pos = -0x80,
					.crAFocus1Pos = -0x80,
					.cbAFocus2Pos = -0x80,
					.crAFocus2Pos = -0x80,
					.cbBFocus1Pos = -0x80,
					.crBFocus1Pos = -0x80,
					.cbBFocus2Pos = -0x80,
					.crBFocus2Pos = -0x80,
				},
			// indvisual
			[2] =
				{
					.cbAFocus1Pos = 0x1,
					.crAFocus1Pos = 0x2,
					.cbAFocus2Pos = 0x3,
					.crAFocus2Pos = 0x4,
					.cbBFocus1Pos = 0x5,
					.crBFocus1Pos = 0x6,
					.cbBFocus2Pos = 0x7,
					.crBFocus2Pos = 0x8,
				},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y18series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < (sizeof(r2yCtrlCRefEdgeTextureAdjCommon) \
			/ sizeof(r2yCtrlCRefEdgeTextureAdjCommon[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl3_cref_edge_texture_adj_common(self->imR2yCtrl3, pipeNo,
				&r2yCtrlCRefEdgeTextureAdjCommon[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT(("crvafx = 0x%lx\n", ioR2yP1.fR2y.crv.crvaf.word));
		DriverCommon_DDIM_PRINT(("crvafx1 = 0x%x\n",  ioR2yP1.fR2y.crv.crvaf.bit.crvafx1));
		DriverCommon_DDIM_PRINT(("crvafy1 = 0x%x\n",  ioR2yP1.fR2y.crv.crvaf.bit.crvafy1));
		DriverCommon_DDIM_PRINT(("crvafx2 = 0x%x\n",  ioR2yP1.fR2y.crv.crvaf.bit.crvafx2));
		DriverCommon_DDIM_PRINT(("crvafy2 = 0x%x\n",  ioR2yP1.fR2y.crv.crvaf.bit.crvafy2));
		DriverCommon_DDIM_PRINT(("crvbfx = 0x%lx\n", ioR2yP1.fR2y.crv.crvbf.word));
		DriverCommon_DDIM_PRINT(("crvbfx1 = 0x%x\n",  ioR2yP1.fR2y.crv.crvbf.bit.crvbfx1));
		DriverCommon_DDIM_PRINT(("crvbfy1 = 0x%x\n",  ioR2yP1.fR2y.crv.crvbf.bit.crvbfy1));
		DriverCommon_DDIM_PRINT(("crvbfx2 = 0x%x\n",  ioR2yP1.fR2y.crv.crvbf.bit.crvbfx2));
		DriverCommon_DDIM_PRINT(("crvbfy2 = 0x%x\n",  ioR2yP1.fR2y.crv.crvbf.bit.crvbfy2));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT(("crvafx = 0x%lx\n", ioR2yP2.fR2y.crv.crvaf.word));
		DriverCommon_DDIM_PRINT(("crvafx1 = 0x%x\n",  ioR2yP2.fR2y.crv.crvaf.bit.crvafx1));
		DriverCommon_DDIM_PRINT(("crvafy1 = 0x%x\n",  ioR2yP2.fR2y.crv.crvaf.bit.crvafy1));
		DriverCommon_DDIM_PRINT(("crvafx2 = 0x%x\n",  ioR2yP2.fR2y.crv.crvaf.bit.crvafx2));
		DriverCommon_DDIM_PRINT(("crvafy2 = 0x%x\n",  ioR2yP2.fR2y.crv.crvaf.bit.crvafy2));
		DriverCommon_DDIM_PRINT(("crvbfx = 0x%lx\n", ioR2yP2.fR2y.crv.crvbf.word));
		DriverCommon_DDIM_PRINT(("crvbfx1 = 0x%x\n",  ioR2yP2.fR2y.crv.crvbf.bit.crvbfx1));
		DriverCommon_DDIM_PRINT(("crvbfy1 = 0x%x\n",  ioR2yP2.fR2y.crv.crvbf.bit.crvbfy1));
		DriverCommon_DDIM_PRINT(("crvbfx2 = 0x%x\n",  ioR2yP2.fR2y.crv.crvbf.bit.crvbfx2));
		DriverCommon_DDIM_PRINT(("crvbfy2 = 0x%x\n",  ioR2yP2.fR2y.crv.crvbf.bit.crvbfy2));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y18series_FUNC_NAME
#define 	CtImR2y18series_FUNC_NAME "ct_im_r2y_18series_5: "
kint32 ct_im_r2y_18series_5(CtImR2y18series *self, kuchar pipeNo)
{
	TImR2yCtrlCRefEdgeAdj r2yCtrlCRefEdgeAdj[] =
		{
			// max
			[0] =
				{
					.areaAEnable = 1,
					.areaBEnable = 1,
					.mergeMethod = 2,
					.areaAScaleOffset =0xFF,
					.areaAScaleGain =
						{
							0x3FF, 0x3FF,
						},
					.areaAScaleBorder = 0x7F,
					.areaAScaleClipLo = 0xFF,
					.areaAScaleClipHi = 0xFF,
					.areaAYScaleGainP = 0xFF,
					.areaAYScaleGainM = 0xFF,
					.areaAYScaleBorder =
						{
							0xFF, 0xFF,
						},
					.areaAYScaleClipLo = 0x100,
					.areaAYScaleClipHi = 0x100,
					.areaBScaleOffset = 0xFF,
					.areaBScaleGain =
						{
							0x3FF, 0x3FF,
						},
					.areaBScaleBorder = 0x7F,
					.areaBScaleClipLo = 0xFF,
					.areaBScaleClipHi = 0xFF,
					.areaBYScaleGainP = 0xFF,
					.areaBYScaleGainM = 0xFF,
					.areaBYScaleBorder =
						{
							0xFF, 0xFF,
						},
					.areaBYScaleClipLo = 0x100,
					.areaBYScaleClipHi = 0x100,
					.levelClipP = 0x1FF,
					.levelClipM = 0x1FF,
				},
			// min
			[1] =
				{
					.areaAEnable = 0,
					.areaBEnable = 0,
					.mergeMethod = 0,
					.areaAScaleOffset =0,
					.areaAScaleGain =
						{
							-0x400, -0x400,
						},
					.areaAScaleBorder = 0,
					.areaAScaleClipLo = 0,
					.areaAScaleClipHi = 0,
					.areaAYScaleGainP = 0,
					.areaAYScaleGainM = 0,
					.areaAYScaleBorder =
						{
							0, 0,
						},
					.areaAYScaleClipLo = 0,
					.areaAYScaleClipHi = 0,
					.areaBScaleOffset = 0,
					.areaBScaleGain =
						{
							-0x400, -0x400,
						},
					.areaBScaleBorder = 0,
					.areaBScaleClipLo = 0,
					.areaBScaleClipHi = 0,
					.areaBYScaleGainP = 0,
					.areaBYScaleGainM = 0,
					.areaBYScaleBorder =
						{
							0, 0,
						},
					.areaBYScaleClipLo = 0,
					.areaBYScaleClipHi = 0,
					.levelClipP = 0,
					.levelClipM = 0,
				},
			// indvisual
			[2] =
				{
					.areaAEnable = 1,
					.areaBEnable = 1,
					.mergeMethod = 1,
					.areaAScaleOffset =0x10,
					.areaAScaleGain =
						{
							0x11, 0x12,
						},
					.areaAScaleBorder = 0x13,
					.areaAScaleClipLo = 0x14,
					.areaAScaleClipHi = 0x15,
					.areaAYScaleGainP = 0x16,
					.areaAYScaleGainM = 0x17,
					.areaAYScaleBorder =
						{
							0x18, 0x19,
						},
					.areaAYScaleClipLo = 0x1A,
					.areaAYScaleClipHi = 0x1B,
					.areaBScaleOffset = 0x1C,
					.areaBScaleGain =
						{
							0x1D, 0x1E,
						},
					.areaBScaleBorder = 0x1F,
					.areaBScaleClipLo = 0x20,
					.areaBScaleClipHi = 0x21,
					.areaBYScaleGainP = 0x22,
					.areaBYScaleGainM = 0x23,
					.areaBYScaleBorder =
						{
							0x24, 0x25,
						},
					.areaBYScaleClipLo = 0x26,
					.areaBYScaleClipHi = 0x27,
					.levelClipP = 0x28,
					.levelClipM = 0x29,
				},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y18series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < (sizeof(r2yCtrlCRefEdgeAdj) / sizeof(r2yCtrlCRefEdgeAdj[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl3_cref_edge_adj(self->imR2yCtrl3, pipeNo, &r2yCtrlCRefEdgeAdj[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y18series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT(("egcrae = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvctl.bit.egcrae));
		DriverCommon_DDIM_PRINT(("egcrbe = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvctl.bit.egcrbe));
		DriverCommon_DDIM_PRINT(("egcrvmrg = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvctl.bit.egcrvmrg));
		DriverCommon_DDIM_PRINT(("egcrvasclof1 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvasclof.bit.egcrvasclof1));
		DriverCommon_DDIM_PRINT(("egcrvasclga = 0x%lx\n", ioR2yP1.fR2y.egcrv.egcrvasclga.word));
		DriverCommon_DDIM_PRINT(("egcrvasclga0 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvasclga.bit.egcrvasclga0));
		DriverCommon_DDIM_PRINT(("egcrvasclga1 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvasclga.bit.egcrvasclga1));
		DriverCommon_DDIM_PRINT(("egcrvasclbd1 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvasclbd.bit.egcrvasclbd1));
		DriverCommon_DDIM_PRINT(("egcrvasclcpl = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvasclcp.bit.egcrvasclcpl));
		DriverCommon_DDIM_PRINT(("egcrvasclcph = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvasclcp.bit.egcrvasclcph));
		DriverCommon_DDIM_PRINT(("egyasclga0 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egyasclga.bit.egyasclga0));
		DriverCommon_DDIM_PRINT(("egyasclga1 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egyasclga.bit.egyasclga1));
		DriverCommon_DDIM_PRINT(("egyasclbd0 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egyasclbd.bit.egyasclbd0));
		DriverCommon_DDIM_PRINT(("egyasclbd1 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egyasclbd.bit.egyasclbd1));
		DriverCommon_DDIM_PRINT(("EGYASCLCLPL = 0x%x\n",  ioR2yP1.fR2y.egcrv.egyasclclp.bit.EGYASCLCLPL));
		DriverCommon_DDIM_PRINT(("egyasclclph = 0x%x\n",  ioR2yP1.fR2y.egcrv.egyasclclp.bit.egyasclclph));
		DriverCommon_DDIM_PRINT(("egcrvbsclof1 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvbsclof.bit.egcrvbsclof1));
		DriverCommon_DDIM_PRINT(("egcrvbsclga = 0x%lx\n", ioR2yP1.fR2y.egcrv.egcrvbsclga.word));
		DriverCommon_DDIM_PRINT(("egcrvbsclga0 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvbsclga.bit.egcrvbsclga0));
		DriverCommon_DDIM_PRINT(("egcrvbsclga1 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvbsclga.bit.egcrvbsclga1));
		DriverCommon_DDIM_PRINT(("egcrvbsclbd1 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvbsclbd.bit.egcrvbsclbd1));
		DriverCommon_DDIM_PRINT(("egcrvbsclcpl = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvbsclcp.bit.egcrvbsclcpl));
		DriverCommon_DDIM_PRINT(("egcrvbsclcph = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvbsclcp.bit.egcrvbsclcph));
		DriverCommon_DDIM_PRINT(("egybsclga0 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egybsclga.bit.egybsclga0));
		DriverCommon_DDIM_PRINT(("egybsclga1 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egybsclga.bit.egybsclga1));
		DriverCommon_DDIM_PRINT(("egybsclbd0 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egybsclbd.bit.egybsclbd0));
		DriverCommon_DDIM_PRINT(("egybsclbd1 = 0x%x\n",  ioR2yP1.fR2y.egcrv.egybsclbd.bit.egybsclbd1));
		DriverCommon_DDIM_PRINT(("egybsclclpl = 0x%x\n",  ioR2yP1.fR2y.egcrv.egybsclclp.bit.egybsclclpl));
		DriverCommon_DDIM_PRINT(("egybsclclph = 0x%x\n",  ioR2yP1.fR2y.egcrv.egybsclclp.bit.egybsclclph));
		DriverCommon_DDIM_PRINT(("egcrvclpp = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvclp.bit.egcrvclpp));
		DriverCommon_DDIM_PRINT(("egcrvclpm = 0x%x\n",  ioR2yP1.fR2y.egcrv.egcrvclp.bit.egcrvclpm));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT(("egcrae = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvctl.bit.egcrae));
		DriverCommon_DDIM_PRINT(("egcrbe = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvctl.bit.egcrbe));
		DriverCommon_DDIM_PRINT(("egcrvmrg = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvctl.bit.egcrvmrg));
		DriverCommon_DDIM_PRINT(("egcrvasclof1 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvasclof.bit.egcrvasclof1));
		DriverCommon_DDIM_PRINT(("egcrvasclga = 0x%lx\n", ioR2yP2.fR2y.egcrv.egcrvasclga.word));
		DriverCommon_DDIM_PRINT(("egcrvasclga0 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvasclga.bit.egcrvasclga0));
		DriverCommon_DDIM_PRINT(("egcrvasclga1 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvasclga.bit.egcrvasclga1));
		DriverCommon_DDIM_PRINT(("egcrvasclbd1 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvasclbd.bit.egcrvasclbd1));
		DriverCommon_DDIM_PRINT(("egcrvasclcpl = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvasclcp.bit.egcrvasclcpl));
		DriverCommon_DDIM_PRINT(("egcrvasclcph = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvasclcp.bit.egcrvasclcph));
		DriverCommon_DDIM_PRINT(("egyasclga0 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egyasclga.bit.egyasclga0));
		DriverCommon_DDIM_PRINT(("egyasclga1 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egyasclga.bit.egyasclga1));
		DriverCommon_DDIM_PRINT(("egyasclbd0 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egyasclbd.bit.egyasclbd0));
		DriverCommon_DDIM_PRINT(("egyasclbd1 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egyasclbd.bit.egyasclbd1));
		DriverCommon_DDIM_PRINT(("egyasclclpl = 0x%x\n",  ioR2yP2.fR2y.egcrv.egyasclclp.bit.egyasclclpl));
		DriverCommon_DDIM_PRINT(("egyasclclph = 0x%x\n",  ioR2yP2.fR2y.egcrv.egyasclclp.bit.egyasclclph));
		DriverCommon_DDIM_PRINT(("egcrvbsclof1 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvbsclof.bit.egcrvbsclof1));
		DriverCommon_DDIM_PRINT(("egcrvbsclga = 0x%lx\n", ioR2yP2.fR2y.egcrv.egcrvbsclga.word));
		DriverCommon_DDIM_PRINT(("egcrvbsclga0 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvbsclga.bit.egcrvbsclga0));
		DriverCommon_DDIM_PRINT(("egcrvbsclga1 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvbsclga.bit.egcrvbsclga1));
		DriverCommon_DDIM_PRINT(("egcrvbsclbd1 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvbsclbd.bit.egcrvbsclbd1));
		DriverCommon_DDIM_PRINT(("egcrvbsclcpl = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvbsclcp.bit.egcrvbsclcpl));
		DriverCommon_DDIM_PRINT(("egcrvbsclcph = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvbsclcp.bit.egcrvbsclcph));
		DriverCommon_DDIM_PRINT(("egybsclga0 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egybsclga.bit.egybsclga0));
		DriverCommon_DDIM_PRINT(("egybsclga1 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egybsclga.bit.egybsclga1));
		DriverCommon_DDIM_PRINT(("egybsclbd0 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egybsclbd.bit.egybsclbd0));
		DriverCommon_DDIM_PRINT(("egybsclbd1 = 0x%x\n",  ioR2yP2.fR2y.egcrv.egybsclbd.bit.egybsclbd1));
		DriverCommon_DDIM_PRINT(("egybsclclpl = 0x%x\n",  ioR2yP2.fR2y.egcrv.egybsclclp.bit.egybsclclpl));
		DriverCommon_DDIM_PRINT(("egybsclclph = 0x%x\n",  ioR2yP2.fR2y.egcrv.egybsclclp.bit.egybsclclph));
		DriverCommon_DDIM_PRINT(("egcrvclpp = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvclp.bit.egcrvclpp));
		DriverCommon_DDIM_PRINT(("egcrvclpm = 0x%x\n",  ioR2yP2.fR2y.egcrv.egcrvclp.bit.egcrvclpm));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

CtImR2y18series* ct_im_r2y_18series_new(void)
{
	CtImR2y18series* self = k_object_new_with_private(CT_TYPE_IM_R2Y_18SERIES, sizeof(CtImR2y18seriesPrivate));

	return self;
}
