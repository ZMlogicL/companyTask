/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y113series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "imr2yclk.h"
#include "ctimr2y113series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y113series, ct_im_r2y_113series)
#define CT_IM_R2Y_113SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2y113seriesPrivate, \
		CT_TYPE_IM_R2Y_113SERIES))


struct _CtImR2y113seriesPrivate
{

};


/*
 * IMPL
 */
static void ct_im_r2y_113series_constructor(CtImR2y113series *self)
{
	CtImR2y113seriesPrivate *priv = CT_IM_R2Y_113SERIES_GET_PRIVATE(self);
	self->imR2yClk = im_r2y_clk_new();
	self->imR2yCtrl2 = im_r2y_ctrl2_new();
	self->imR2yUtility = im_r2y_utility_new();
	self->imR2yUtility2 = im_r2y_utility2_new();
	self->imR2yUtility4 = im_r2y_utility4_new();
}

static void ct_im_r2y_113series_destructor(CtImR2y113series *self)
{
	CtImR2y113seriesPrivate *priv = CT_IM_R2Y_113SERIES_GET_PRIVATE(self);
			if(self->imR2yUtility2){
						k_object_unref(self->imR2yUtility2);
						self->imR2yUtility2=NULL;
			}

			if(self->imR2yCtrl2){
				k_object_unref(self->imR2yCtrl2);
				self->imR2yCtrl2=NULL;
			}

			if(self->imR2yUtility){
						k_object_unref(self->imR2yUtility);
						self->imR2yUtility=NULL;
					}

			if(self->imR2yClk){
					k_object_unref(self->imR2yClk);
					self->imR2yClk=NULL;
			}

			if(self->imR2yUtility4){
								k_object_unref(self->imR2yUtility4);
								self->imR2yUtility4=NULL;
						}
}


/*
 * PUBLIC
 */
#undef 	CtImR2y113series_FUNC_NAME
#define 	CtImR2y113series_FUNC_NAME "ct_im_r2y_113series_0: "
kint32 ct_im_r2y_113series_0(CtImR2y113series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEgwsclTblAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y113series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility4_get_rdma_addr_egwscl_table(self->imR2yUtility4, pipeNo, 0, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEgwsclTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "address High[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility4_get_rdma_addr_egwscl_table(self->imR2yUtility4, pipeNo, 1, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEgwsclTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "address Medium[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility4_get_rdma_addr_egwscl_table(self->imR2yUtility4, pipeNo, 2, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEgwsclTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "address Low[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y113series_FUNC_NAME
#define 	CtImR2y113series_FUNC_NAME "ct_im_r2y_113series_1: "
kint32 ct_im_r2y_113series_1(CtImR2y113series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEgwtonTblAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y113series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility2_get_rdma_addr_egwton_table(self->imR2yUtility2, pipeNo, 0, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEgwtonTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "address High[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility2_get_rdma_addr_egwton_table(self->imR2yUtility2, pipeNo, 1, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEgwtonTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "address Meduim[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility2_get_rdma_addr_egwton_table(self->imR2yUtility2, pipeNo, 2, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEgwtonTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "address Low[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y113series_FUNC_NAME
#define 	CtImR2y113series_FUNC_NAME "ct_im_r2y_113series_2: "
kint32 ct_im_r2y_113series_2(CtImR2y113series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEgmpsclTblAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y113series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility2_get_rdma_addr_egmpscl_table(self->imR2yUtility2, pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEgmpsclTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y113series_FUNC_NAME
#define 	CtImR2y113series_FUNC_NAME "ct_im_r2y_113series_3: "
kint32 ct_im_r2y_113series_3(CtImR2y113series *self, kuchar pipeNo)
{
	TImR2yRightsideOffset r2yCtrlOfsByte[] =
	{
		// max
		[0] =
			{
				.offsetByte[0] = 0x0FFE,
				.offsetByte[1] = 0x0FFE,
				.offsetByte[2] = 0x0FFE,
				.offsetByte[3] = 0x0FFE,
			},
		// min
		[1] =
			{
				.offsetByte[0] = 0,
				.offsetByte[1] = 0,
				.offsetByte[2] = 0,
				.offsetByte[3] = 0,
			},
		// indvisual
		[2] =
			{
				.offsetByte[0] = 0x0100,
				.offsetByte[1] = 0x0200,
				.offsetByte[2] = 0x0300,
				.offsetByte[3] = 0x0400,
			},
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	if(pipeNo == D_IM_R2Y_PIPE12){
		return D_DDIM_OK;
	}
	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y113series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < (sizeof(r2yCtrlOfsByte) / sizeof(r2yCtrlOfsByte[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("* *%u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = Im_R2Y_Set_RightSide_Offset(pipeNo, D_IM_R2Y_YYW_CH_0, &r2yCtrlOfsByte[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT(("yyw0ofsx0 = 0x%x\n", ioR2yP1.yyw.yyw0ofsx.bit.yyw0ofsx0));
		DriverCommon_DDIM_PRINT(("yyw0ofsx1 = 0x%x\n", ioR2yP1.yyw.yyw0ofsx.bit.yyw0ofsx1));
		DriverCommon_DDIM_PRINT(("yyw0ofsx2 = 0x%x\n", ioR2yP1.yyw.yyw0ofsx.bit.yyw0ofsx2));
		DriverCommon_DDIM_PRINT(("yyw0ofsx3 = 0x%x\n", ioR2yP1.yyw.yyw0ofsx.bit.yyw0ofsx3));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT(("yyw0ofsx0 = 0x%x\n", ioR2yP2.yyw.yyw0ofsx.bit.yyw0ofsx0));
		DriverCommon_DDIM_PRINT(("yyw0ofsx1 = 0x%x\n", ioR2yP2.yyw.yyw0ofsx.bit.yyw0ofsx1));
		DriverCommon_DDIM_PRINT(("yyw0ofsx2 = 0x%x\n", ioR2yP2.yyw.yyw0ofsx.bit.yyw0ofsx2));
		DriverCommon_DDIM_PRINT(("yyw0ofsx3 = 0x%x\n", ioR2yP2.yyw.yyw0ofsx.bit.yyw0ofsx3));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
		ercd = Im_R2Y_Set_RightSide_Offset(pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yCtrlOfsByte[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT(("yywaofsx0 = 0x%x\n", ioR2yP1.yyw.yywaofsx.bit.yywaofsx0));
		DriverCommon_DDIM_PRINT(("yywaofsx1 = 0x%x\n", ioR2yP1.yyw.yywaofsx.bit.yywaofsx1));
		DriverCommon_DDIM_PRINT(("yywaofsx2 = 0x%x\n", ioR2yP1.yyw.yywaofsx.bit.yywaofsx2));
		DriverCommon_DDIM_PRINT(("yywaofsx3 = 0x%x\n", ioR2yP1.yyw.yywaofsx.bit.yywaofsx3));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT(("yywaofsx0 = 0x%x\n", ioR2yP2.yyw.yywaofsx.bit.yywaofsx0));
		DriverCommon_DDIM_PRINT(("yywaofsx1 = 0x%x\n", ioR2yP2.yyw.yywaofsx.bit.yywaofsx1));
		DriverCommon_DDIM_PRINT(("yywaofsx2 = 0x%x\n", ioR2yP2.yyw.yywaofsx.bit.yywaofsx2));
		DriverCommon_DDIM_PRINT(("yywaofsx3 = 0x%x\n", ioR2yP2.yyw.yywaofsx.bit.yywaofsx3));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y113series_FUNC_NAME
#define 	CtImR2y113series_FUNC_NAME "ct_im_r2y_113series_4: "
kint32 ct_im_r2y_113series_4(CtImR2y113series *self, kuchar pipeNo)
{
	TImR2yTct r2yCtrlBtcTct[] =
		{
			// max
			[0] =
				{
					.tctEnable = 1,
					.startX = 0xFFE,
					.startY = 0x3FFF,
					.blockHsiz = 0x80,
					.blockVsiz = 0x80,
					.blockHnum = 0x28,
					.blockVnum = 0x1E,
				},
			// min
			[1] =
				{
					.tctEnable = 0,
					.startX = 0,
					.startY = 0,
					.blockHsiz = 8,
					.blockVsiz = 4,
					.blockHnum = 2,
					.blockVnum = 2,
				},
			// indvisual
			[2] =
				{
					.tctEnable = 1,
					.startX = 0x100,
					.startY = 0x200,
					.blockHsiz = 0x30,
					.blockVsiz = 0x40,
					.blockHnum = 0x20,
					.blockVnum = 0x10,
				}
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y113series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < (sizeof(r2yCtrlBtcTct) / sizeof(r2yCtrlBtcTct[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl2_before_tone_tct(self->imR2yCtrl2, pipeNo, &r2yCtrlBtcTct[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tcten = 0x%x\n", ioR2yP1.fR2y.btc.tctctl.bit.tcten));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tcthsta = 0x%x\n", ioR2yP1.fR2y.btc.tctsta.bit.tcthsta));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tctvsta = 0x%x\n", ioR2yP1.fR2y.btc.tctsta.bit.tctvsta));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tctbhsiz = 0x%x\n", ioR2yP1.fR2y.btc.tctb.bit.tctbhsiz));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tctbvsiz = 0x%x\n", ioR2yP1.fR2y.btc.tctb.bit.tctbvsiz));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tctbhnum = 0x%x\n", ioR2yP1.fR2y.btc.tctb.bit.tctbhnum));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tctbvnum = 0x%x\n", ioR2yP1.fR2y.btc.tctb.bit.tctbvnum));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tcten = 0x%x\n", ioR2yP2.fR2y.btc.tctctl.bit.tcten));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tcthsta = 0x%x\n", ioR2yP2.fR2y.btc.tctsta.bit.tcthsta));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tctvsta = 0x%x\n", ioR2yP2.fR2y.btc.tctsta.bit.tctvsta));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tctbhsiz = 0x%x\n", ioR2yP2.fR2y.btc.tctb.bit.tctbhsiz));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tctbvsiz = 0x%x\n", ioR2yP2.fR2y.btc.tctb.bit.tctbvsiz));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tctbhnum = 0x%x\n", ioR2yP2.fR2y.btc.tctb.bit.tctbhnum));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tctbvnum = 0x%x\n", ioR2yP2.fR2y.btc.tctb.bit.tctbvnum));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y113series_FUNC_NAME
#define 	CtImR2y113series_FUNC_NAME "ct_im_r2y_113series_5: "
kint32 ct_im_r2y_113series_5(CtImR2y113series *self, kuchar pipeNo)
{
	TImR2yTchs r2yCtrlBtcTchs[] =
		{
			// max
			[0] =
				{
					.histEnable = 1,
					.samplingHcyc = 2,
					.samplingVcyc = 4,
					.histogramMode = 4,
					.histMinusMode = 1,
					.tchsWindow =
						{
							.imgTop = 0x3FFF,
							.imgLeft = 0xFFF,
							.imgWidth = 0x938,
							.imgLines = 0x2260,
						},
			},
			// min
			[1] =
				{
					.histEnable = 0,
					.samplingHcyc = 0,
					.samplingVcyc = 0,
					.histogramMode = 0,
					.histMinusMode = 0,
					.tchsWindow =
						{
							.imgTop = 0,
							.imgLeft = 0,
							.imgWidth = 2,
							.imgLines = 1,
						},
			},
			// indvisual
			[2] =
				{
					.histEnable = 1,
					.samplingHcyc = 1,
					.samplingVcyc = 3,
					.histogramMode = 2,
					.histMinusMode = 1,
					.tchsWindow =
						{
							.imgTop = 0x10,
							.imgLeft = 0x20,
							.imgWidth = 0x400,
							.imgLines = 0x1000,
						},
			}
	};
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y113series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < (sizeof(r2yCtrlBtcTchs) / sizeof(r2yCtrlBtcTchs[0])); loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl2_before_tone_tchs(self->imR2yCtrl2, pipeNo, &r2yCtrlBtcTchs[loopcnt]);
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo);
		DriverCommon_DDIM_PRINT(("PIPE1\n"));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsen = 0x%x\n",
				ioR2yP1.fR2y.btc.tchsctl.bit.tchsen));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "ttchshcyc = 0x%x\n",
				ioR2yP1.fR2y.btc.tchsctl.bit.ttchshcyc));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsvcyc = 0x%x\n",
				ioR2yP1.fR2y.btc.tchsctl.bit.tchsvcyc));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsrgbmd = 0x%x\n",
				ioR2yP1.fR2y.btc.tchsctl.bit.tchsrgbmd));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsmn = 0x%x\n",
				ioR2yP1.fR2y.btc.tchsctl.bit.tchsmn));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchshsta = 0x%x\n",
				ioR2yP1.fR2y.btc.tchssta.bit.tchshsta));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsvsta = 0x%x\n",
				ioR2yP1.fR2y.btc.tchssta.bit.tchsvsta));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchshsiz = 0x%x\n",
				ioR2yP1.fR2y.btc.tchssiz.bit.tchshsiz));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsvsiz = 0x%x\n",
				ioR2yP1.fR2y.btc.tchssiz.bit.tchsvsiz));
		DriverCommon_DDIM_PRINT(("PIPE2\n"));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsen = 0x%x\n",
				ioR2yP2.fR2y.btc.tchsctl.bit.tchsen));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "ttchshcyc = 0x%x\n",
				ioR2yP2.fR2y.btc.tchsctl.bit.ttchshcyc));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsvcyc = 0x%x\n",
				ioR2yP2.fR2y.btc.tchsctl.bit.tchsvcyc));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsrgbmd = 0x%x\n",
				ioR2yP2.fR2y.btc.tchsctl.bit.tchsrgbmd));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsmn = 0x%x\n",
				ioR2yP2.fR2y.btc.tchsctl.bit.tchsmn));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchshsta = 0x%x\n",
				ioR2yP2.fR2y.btc.tchssta.bit.tchshsta));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsvsta = 0x%x\n",
				ioR2yP2.fR2y.btc.tchssta.bit.tchsvsta));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchshsiz = 0x%x\n",
				ioR2yP2.fR2y.btc.tchssiz.bit.tchshsiz));
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "tchsvsiz = 0x%x\n",
				ioR2yP2.fR2y.btc.tchssiz.bit.tchsvsiz));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y113series_FUNC_NAME
#define 	CtImR2y113series_FUNC_NAME "ct_im_r2y_113series_6: "
kint32 ct_im_r2y_113series_6(CtImR2y113series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaBtcTctAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y113series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility_get_rdma_addr_before_tone_tct_cntl(self->imR2yUtility, pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaBtcTctAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y113series_FUNC_NAME
#define 	CtImR2y113series_FUNC_NAME "ct_im_r2y_113series_7: "
kint32 ct_im_r2y_113series_7(CtImR2y113series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaBtcTchsAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y113series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility_get_rdma_addr_before_tone_tchs_cntl(self->imR2yUtility, pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaBtcTchsAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y113series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

CtImR2y113series *ct_im_r2y_113series_new(void)
{
	CtImR2y113series *self = k_object_new_with_private(CT_TYPE_IM_R2Y_113SERIES, sizeof(CtImR2y113seriesPrivate));

	return self;
}
