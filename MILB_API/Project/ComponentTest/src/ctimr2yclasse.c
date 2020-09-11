/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClasse
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2yclasse.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yClasse, ct_im_r2y_classe)
#define CT_IM_R2Y_CLASSE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yClassePrivate, CT_TYPE_IM_R2Y_CLASSE))


struct _CtImR2yClassePrivate
{

};


static void ct_im_r2y_classe_constructor(CtImR2yClasse *self)
{
	CtImR2yClassePrivate *priv = CT_IM_R2Y_CLASSE_GET_PRIVATE(self);
}

static void ct_im_r2y_classe_destructor(CtImR2yClasse *self)
{
	CtImR2yClassePrivate *priv = CT_IM_R2Y_CLASSE_GET_PRIVATE(self);
}


#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classe_1_37: "
INT32 ct_im_r2y_classe_1_37( CtImR2yClasse *self,UCHAR pipeNo )
{
	TImR2yCtrlTrimming r2yCtrlTrimming[] = {
		[0] = {	// max
			.trimmingEnable = 1,
			.trimWindow = {
				.imgLeft = 2262,
				.imgWidth = 2360,
				.imgTop = 8886,
				.imgLines = 8960,
			},
		},
		[1] = {	// min
			.trimmingEnable = 0,
			.trimWindow = {
				.imgLeft = 0,
				.imgWidth = 0,
				.imgTop = 0,
				.imgLines = 0,
			},
		},
	};
	UINT32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
	const char dumpMsg0[] = D_IM_R2Y_FUNC_NAME "0x%x\n";
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlTrimming) / sizeof(r2yCtrlTrimming[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));
		ercd = im_r2y3_ctrl_trimming(self->imR2y3, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yCtrlTrimming[loopcnt] );
		Ddim_Print(( dumpMsg0, ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "TRM0EN   = %u\n", ioR2yP1.yyw.yyw0md.bit.TRM0EN ));
		Ddim_Print(( "TRM0HSTA = %u\n", ioR2yP1.yyw.TRM0H.bit.TRM0HSTA ));
		Ddim_Print(( "TRM0HSIZ = %u\n", ioR2yP1.yyw.TRM0H.bit.TRM0HSIZ ));
		Ddim_Print(( "TRM0VSTA = %u\n", ioR2yP1.yyw.TRM0V.bit.TRM0VSTA ));
		Ddim_Print(( "TRM0VSIZ = %u\n", ioR2yP1.yyw.TRM0V.bit.TRM0VSIZ ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "TRM0EN   = %u\n", ioR2yP2.yyw.yyw0md.bit.TRM0EN ));
		Ddim_Print(( "TRM0HSTA = %u\n", ioR2yP2.yyw.TRM0H.bit.TRM0HSTA ));
		Ddim_Print(( "TRM0HSIZ = %u\n", ioR2yP2.yyw.TRM0H.bit.TRM0HSIZ ));
		Ddim_Print(( "TRM0VSTA = %u\n", ioR2yP2.yyw.TRM0V.bit.TRM0VSTA ));
		Ddim_Print(( "TRM0VSIZ = %u\n", ioR2yP2.yyw.TRM0V.bit.TRM0VSIZ ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
		ercd = im_r2y3_ctrl_trimming(self->imR2y3, pipeNo, D_IM_R2Y_YYW_CH_1, &r2yCtrlTrimming[loopcnt] );
		Ddim_Print(( dumpMsg0, ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "TRM1EN   = %u\n", ioR2yP1.yyw.YYW1MD.bit.TRM1EN ));
		Ddim_Print(( "TRM1HSTA = %u\n", ioR2yP1.yyw.TRM1H.bit.TRM1HSTA ));
		Ddim_Print(( "TRM1HSIZ = %u\n", ioR2yP1.yyw.TRM1H.bit.TRM1HSIZ ));
		Ddim_Print(( "TRM1VSTA = %u\n", ioR2yP1.yyw.TRM1V.bit.TRM1VSTA ));
		Ddim_Print(( "TRM1VSIZ = %u\n", ioR2yP1.yyw.TRM1V.bit.TRM1VSIZ ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "TRM1EN   = %u\n", ioR2yP2.yyw.YYW1MD.bit.TRM1EN ));
		Ddim_Print(( "TRM1HSTA = %u\n", ioR2yP2.yyw.TRM1H.bit.TRM1HSTA ));
		Ddim_Print(( "TRM1HSIZ = %u\n", ioR2yP2.yyw.TRM1H.bit.TRM1HSIZ ));
		Ddim_Print(( "TRM1VSTA = %u\n", ioR2yP2.yyw.TRM1V.bit.TRM1VSTA ));
		Ddim_Print(( "TRM1VSIZ = %u\n", ioR2yP2.yyw.TRM1V.bit.TRM1VSIZ ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
		ercd = im_r2y3_ctrl_trimming(self->imR2y3, pipeNo, D_IM_R2Y_YYW_CH_2, &r2yCtrlTrimming[loopcnt] );
		Ddim_Print(( dumpMsg0, ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "TRM2EN   = %u\n", ioR2yP1.yyw.YYW2MD.bit.TRM2EN ));
		Ddim_Print(( "TRM2HSTA = %u\n", ioR2yP1.yyw.TRM2H.bit.TRM2HSTA ));
		Ddim_Print(( "TRM2HSIZ = %u\n", ioR2yP1.yyw.TRM2H.bit.TRM2HSIZ ));
		Ddim_Print(( "TRM2VSTA = %u\n", ioR2yP1.yyw.TRM2V.bit.TRM2VSTA ));
		Ddim_Print(( "TRM2VSIZ = %u\n", ioR2yP1.yyw.TRM2V.bit.TRM2VSIZ ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "TRM2EN   = %u\n", ioR2yP2.yyw.YYW2MD.bit.TRM2EN ));
		Ddim_Print(( "TRM2HSTA = %u\n", ioR2yP2.yyw.TRM2H.bit.TRM2HSTA ));
		Ddim_Print(( "TRM2HSIZ = %u\n", ioR2yP2.yyw.TRM2H.bit.TRM2HSIZ ));
		Ddim_Print(( "TRM2VSTA = %u\n", ioR2yP2.yyw.TRM2V.bit.TRM2VSTA ));
		Ddim_Print(( "TRM2VSIZ = %u\n", ioR2yP2.yyw.TRM2V.bit.TRM2VSIZ ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classe_1_38: "
INT32 ct_im_r2y_classe_1_38( CtImR2yClasse *self,UCHAR pipeNo )
{
	T_IM_R2Y_CTRL_TRIMMING_EXT r2yCtrlTrimming[] = {
		[0] = {	// max
			.trimmingEnableB = 1,
			.trimmingEnableC = 1,
			.trimWindowB = {
				.imgLeft = 2262,
				.imgWidth = 2360,
				.imgTop = 8886,
				.imgLines = 8960,
			},
			.trimWindowC = {
				.imgLeft = 2262,
				.imgWidth = 2360,
				.imgTop = 8886,
				.imgLines = 8960,
			},
		},
		[1] = {	// min
			.trimmingEnableB = 0,
			.trimmingEnableC = 0,
			.trimWindowB = {
				.imgTop = 0,
				.imgWidth = 0,
				.imgLeft = 0,
				.imgLines = 0,
			},
			.trimWindowC = {
				.imgTop = 0,
				.imgWidth = 0,
				.imgLeft = 0,
				.imgLines = 0,
			},
		},
	};
	UINT32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
	const char dumpMsg0[] = D_IM_R2Y_FUNC_NAME "0x%x\n";
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlTrimming) / sizeof(r2yCtrlTrimming[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));
		ercd = im_r2y3_ctrl_trimming_external(self->imR2y3, pipeNo, &r2yCtrlTrimming[loopcnt] );
		Ddim_Print(( dumpMsg0, ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "TRMBEN   = %u\n", ioR2yP1.yyw.yyw0md.bit.TRMBEN ));
		Ddim_Print(( "TRMBHSTA = %u\n", ioR2yP1.yyw.TRMBH.bit.TRMBHSTA ));
		Ddim_Print(( "TRMBHSIZ = %u\n", ioR2yP1.yyw.TRMBH.bit.TRMBHSIZ ));
		Ddim_Print(( "TRMBVSTA = %u\n", ioR2yP1.yyw.TRMBV.bit.TRMBVSTA ));
		Ddim_Print(( "TRMBVSIZ = %u\n", ioR2yP1.yyw.TRMBV.bit.TRMBVSIZ ));
		Ddim_Print(( "TRMCEN   = %u\n", ioR2yP1.yyw.yyw0md.bit.TRMCEN ));
		Ddim_Print(( "TRMCHSTA = %u\n", ioR2yP1.yyw.TRMCH.bit.TRMCHSTA ));
		Ddim_Print(( "TRMCHSIZ = %u\n", ioR2yP1.yyw.TRMCH.bit.TRMCHSIZ ));
		Ddim_Print(( "TRMCVSTA = %u\n", ioR2yP1.yyw.TRMCV.bit.TRMCVSTA ));
		Ddim_Print(( "TRMCVSIZ = %u\n", ioR2yP1.yyw.TRMCV.bit.TRMCVSIZ ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "TRMBEN   = %u\n", ioR2yP2.yyw.yyw0md.bit.TRMBEN ));
		Ddim_Print(( "TRMBHSTA = %u\n", ioR2yP2.yyw.TRMBH.bit.TRMBHSTA ));
		Ddim_Print(( "TRMBHSIZ = %u\n", ioR2yP2.yyw.TRMBH.bit.TRMBHSIZ ));
		Ddim_Print(( "TRMBVSTA = %u\n", ioR2yP2.yyw.TRMBV.bit.TRMBVSTA ));
		Ddim_Print(( "TRMBVSIZ = %u\n", ioR2yP2.yyw.TRMBV.bit.TRMBVSIZ ));
		Ddim_Print(( "TRMCEN   = %u\n", ioR2yP2.yyw.yyw0md.bit.TRMCEN ));
		Ddim_Print(( "TRMCHSTA = %u\n", ioR2yP2.yyw.TRMCH.bit.TRMCHSTA ));
		Ddim_Print(( "TRMCHSIZ = %u\n", ioR2yP2.yyw.TRMCH.bit.TRMCHSIZ ));
		Ddim_Print(( "TRMCVSTA = %u\n", ioR2yP2.yyw.TRMCV.bit.TRMCVSTA ));
		Ddim_Print(( "TRMCVSIZ = %u\n", ioR2yP2.yyw.TRMCV.bit.TRMCVSIZ ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classe_1_39: "
INT32 ct_im_r2y_classe_1_39( CtImR2yClasse *self,UCHAR pipeNo )
{
	TImR2yCtrlHistogram r2yCtrlHist[] = {
		[0] = {	// max
			.enable = 1,
			.yywNo = 1,
			.samplingPitch = 3,
			.histogramArea = {
				.imgLeft = 2262,
				.imgWidth = 2360,
				.imgTop = 8886,
				.imgLines = 8960,
			},
		},
		[1] = {	// min
			.enable = 0,
			.yywNo = 0,
			.samplingPitch = 0,
			.histogramArea = {
				.imgLeft = 0,
				.imgWidth = 96,
				.imgTop = 0,
				.imgLines = 72,
			},
		},
		[2] = {	// indivisual
			.enable = 1,
			.yywNo = 1,
			.samplingPitch = 2,
			.histogramArea = {
				.imgLeft = 960,
				.imgWidth = 1280,
				.imgTop = 720,
				.imgLines = 960,
			},
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
	UINT32 loopcnt;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlHist) / sizeof(r2yCtrlHist[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		ercd = im_r2y3_ctrl_histogram(self->imR2y3, pipeNo, &r2yCtrlHist[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTEN   = %u\n",   ioR2yP1.yyw.hstmd.bit.HSTEN ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTSEL  = %u\n",   ioR2yP1.yyw.hstmd.bit.HSTSEL ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIT_M   = %u\n",   ioR2yP1.yyw.hstmd.bit.PIT_M ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTHSTA = 0x%x\n", ioR2yP1.yyw.HSTH.bit.HSTHSTA ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTHSIZ = 0x%x\n", ioR2yP1.yyw.HSTH.bit.HSTHSIZ ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTVSTA = 0x%x\n", ioR2yP1.yyw.HSTV.bit.HSTVSTA ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTVSIZ = 0x%x\n", ioR2yP1.yyw.HSTV.bit.HSTVSIZ ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTEN   = %u\n",   ioR2yP2.yyw.hstmd.bit.HSTEN ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTSEL  = %u\n",   ioR2yP2.yyw.hstmd.bit.HSTSEL ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIT_M   = %u\n",   ioR2yP2.yyw.hstmd.bit.PIT_M ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTHSTA = 0x%x\n", ioR2yP2.yyw.HSTH.bit.HSTHSTA ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTHSIZ = 0x%x\n", ioR2yP2.yyw.HSTH.bit.HSTHSIZ ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTVSTA = 0x%x\n", ioR2yP2.yyw.HSTV.bit.HSTVSTA ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTVSIZ = 0x%x\n", ioR2yP2.yyw.HSTV.bit.HSTVSIZ ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
	}
#endif


	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classe_1_40: "
INT32 ct_im_r2y_classe_1_40( CtImR2yClasse *self,UCHAR pipeNo )
{
	TImR2yHistogramStat status;
	TImR2yHistogramAddr dstAddr;
	USHORT yBuf[D_IM_R2Y_TABLE_MAX_HISTOGRAM];
	UINT32 loopcnt;
	UINT32 loopcnt2;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < 4; loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		switch( loopcnt ) {
			default:
//			case 0:	// max
				if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
					ioR2yP1.yyw.hstmd.bit.yhsovf = 1;
					ioR2yP1.yyw.hstmd.bit.hststs = 0;
					for( loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt2++ ) {
						ioR2yTblP1.hsty.hword[loopcnt2] = 0x7FFF;
					}
				}
				if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
					ioR2yP2.yyw.hstmd.bit.yhsovf = 1;
					ioR2yP2.yyw.hstmd.bit.hststs = 0;
					for( loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt2++ ) {
						ioR2yTblP2.hsty.hword[loopcnt2] = 0x7FFF;
					}
				}
				break;
			case 1:	// min
				if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
					ioR2yP1.yyw.hstmd.bit.yhsovf = 0;
					ioR2yP1.yyw.hstmd.bit.hststs = 0;
					for( loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt2++ ) {
						ioR2yTblP1.hsty.hword[loopcnt2] = 0;
					}
				}
				if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
					ioR2yP2.yyw.hstmd.bit.yhsovf = 0;
					ioR2yP2.yyw.hstmd.bit.hststs = 0;
					for( loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt2++ ) {
						ioR2yTblP2.hsty.hword[loopcnt2] = 0;
					}
				}
				break;
			case 2:	// indvisual
				if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
					ioR2yP1.yyw.hstmd.bit.yhsovf = 1;
					ioR2yP1.yyw.hstmd.bit.hststs = 0;
					for( loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt2++ ) {
						ioR2yTblP1.hsty.hword[loopcnt2] = loopcnt2 +1;
					}
				}
				if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
					ioR2yP2.yyw.hstmd.bit.yhsovf = 1;
					ioR2yP2.yyw.hstmd.bit.hststs = 0;
					for( loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt2++ ) {
						ioR2yTblP2.hsty.hword[loopcnt2] = loopcnt2 +1;
					}
				}
				break;
			case 3:	// hststs=1(busy)
				if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
					ioR2yP1.yyw.hstmd.bit.yhsovf = 1;
					ioR2yP1.yyw.hstmd.bit.hststs = 1;
					for( loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt2++ ) {
						ioR2yTblP1.hsty.hword[loopcnt2] = 0x7FFF;
					}
				}
				if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
					ioR2yP2.yyw.hstmd.bit.yhsovf = 1;
					ioR2yP2.yyw.hstmd.bit.hststs = 1;
					for( loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt2++ ) {
						ioR2yTblP2.hsty.hword[loopcnt2] = 0x7FFF;
					}
				}
				break;
		}


#ifdef CO_MSG_PRINT_ON
		dstAddr.yBuf = yBuf;
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
			Ddim_Print(( "PIPE1\n" ));
			memset( yBuf, '\0', sizeof(yBuf) );
			ercd = im_r2y3_get_histogram(self->imR2y3, 0, &status, &dstAddr );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "y_overflow     = %u\n", status.y_overflow ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "running_status = %u\n", status.running_status ));

			for( loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt2++ ) {
				Ddim_Print(( "yBuf[%3u] = 0x%x ", loopcnt2, yBuf[loopcnt2] ));
				if( (loopcnt2 % 4) == 3 ) {
					Ddim_Print(( "\n" ));
				}
			}
		}
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
			Ddim_Print(( "PIPE2\n" ));
			memset( yBuf, '\0', sizeof(yBuf) );
			ercd = im_r2y3_get_histogram(self->imR2y3, 1, &status, &dstAddr );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "y_overflow     = %u\n", status.y_overflow ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "running_status = %u\n", status.running_status ));

			for( loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_HISTOGRAM; loopcnt2++ ) {
				Ddim_Print(( "yBuf[%3u] = 0x%x ", loopcnt2, yBuf[loopcnt2] ));
				if( (loopcnt2 % 4) == 3 ) {
					Ddim_Print(( "\n" ));
				}
			}
		}
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classe_1_41: "
INT32 ct_im_r2y_classe_1_41( CtImR2yClasse *self,UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y3_set_histogram_access_enable(self->imR2y3, pipeNo, 1, 1 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTAEN = %u\n", ioR2yP1.R2Y_CMN.RAMAEN.bit.HSTAEN ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTAEN = %u\n", ioR2yP2.R2Y_CMN.RAMAEN.bit.HSTAEN ));
	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
	ercd = im_r2y3_set_histogram_access_enable(self->imR2y3, pipeNo, 0, 0 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTAEN = %u\n", ioR2yP1.R2Y_CMN.RAMAEN.bit.HSTAEN ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "HSTAEN = %u\n", ioR2yP2.R2Y_CMN.RAMAEN.bit.HSTAEN ));
	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classe_1_42: "
INT32 ct_im_r2y_classe_1_42( CtImR2yClasse *self,UCHAR pipeNo )
{
	TImR2yColorExtract r2yColorExtract[] = {
		[0] = {	// max
			.extractEnable = 1,
			.refAxisX = 0xFF,
			.refAxisY = 0xFF,
		},
		[1] = {	// min
			.extractEnable = 0,
			.refAxisX = -0x1,
			.refAxisY = -0x1,
		},
		[2] = {	// indvisual
			.extractEnable = 0,
			.refAxisX = 0xFD,
			.refAxisY = 0xFE,
		},
	};
	UINT32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yColorExtract) / sizeof(r2yColorExtract[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y3_set_color_extract(self->imR2y3, pipeNo, &r2yColorExtract[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCEEN = %u\n",   ioR2yP1.yyw.PCEMD.bit.PCEEN ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCEX  = 0x%x\n", ioR2yP1.yyw.PCEXY.bit.PCEX ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCEY  = 0x%x\n", ioR2yP1.yyw.PCEXY.bit.PCEY ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCEEN = %u\n",   ioR2yP2.yyw.PCEMD.bit.PCEEN ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCEX  = 0x%x\n", ioR2yP2.yyw.PCEXY.bit.PCEX ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCEY  = 0x%x\n", ioR2yP2.yyw.PCEXY.bit.PCEY ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classe_1_43: "
INT32 ct_im_r2y_classe_1_43( CtImR2yClasse *self,UCHAR pipeNo )
{
	TImR2yChromaScale r2yChromaScale[] = {
		[0] = {	// max
			.chromaOffset = 0xFF,
			.chromaGain = 0x3FF,
		},
		[1] = {	// min
			.chromaOffset = 0,
			.chromaGain = 0,
		},
		[2] = {	// indvisual
			.chromaOffset = 1,
			.chromaGain = 2,
		},
	};
	UINT32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yChromaScale) / sizeof(r2yChromaScale[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y3_set_chroma(self->imR2y3, pipeNo, &r2yChromaScale[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCECOF = 0x%x\n", ioR2yP1.yyw.PCEC.bit.PCECOF ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCECGA = 0x%x\n", ioR2yP1.yyw.PCEC.bit.PCECGA ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCECOF = 0x%x\n", ioR2yP2.yyw.PCEC.bit.PCECOF ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCECGA = 0x%x\n", ioR2yP2.yyw.PCEC.bit.PCECGA ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classe_1_44: "
INT32 ct_im_r2y_classe_1_44(CtImR2yClasse *self, UCHAR pipeNo )
{
	TImR2yHueScale r2yHueScale[] = {
		[0] = {	// max
			.hueOffset = 0xFF,
			.hueGain = 0x3FF,
		},
		[1] = {	// min
			.hueOffset = 0,
			.hueGain = 0,
		},
		[2] = {	// indvisual
			.hueOffset = 1,
			.hueGain = 2,
		},
	};
	UINT32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yHueScale) / sizeof(r2yHueScale[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y3_set_hue(self->imR2y3, pipeNo, &r2yHueScale[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCEHOF = 0x%x\n", ioR2yP1.yyw.PCEH.bit.PCEHOF ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCEHGA = 0x%x\n", ioR2yP1.yyw.PCEH.bit.PCEHGA ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCEHOF = 0x%x\n", ioR2yP2.yyw.PCEH.bit.PCEHOF ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "PCEHGA = 0x%x\n", ioR2yP2.yyw.PCEH.bit.PCEHGA ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classe_1_45: "
INT32 ct_im_r2y_classe_1_45( CtImR2yClasse *self,UCHAR pipeNo )
{
	TImR2yPostRexize0Param r2yPostResize0[] = {
		[0] = {	// max
			.edgeEnable = 1,
			.gradationEnable = 1,
			.hpfK = { 0x3FF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F },
			.strength = 8,
			.coringPOffset = { 0xFF, 0xFF, 0xFF, 0xFF },
			.coringPGain = { 0x7F, 0x7F, 0x7F, 0x7F },
			.coringPDorder = { 0xFF, 0xFF, 0xFF },
			.coringMOffset = { 0xFF, 0xFF, 0xFF, 0xFF },
			.coringMGain = { 0x7F, 0x7F, 0x7F, 0x7F },
			.coringMBorder = { 0xFF, 0xFF, 0xFF },
			.scaleReductCoef = 0x3F,
			.scalePOffset = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
			.scalePGain = { 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF },
			.scalePDorder = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
			.scaleMOffset = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
			.scaleMGain = { 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF },
			.scaleMBorder = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
			.gradationPOffset = { 0x7F, 0x7F, 0x7F, 0x7F, 0x7F },
			.gradationPGain = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
			.gradationPDorder = { 0x7F, 0x7F, 0x7F, 0x7F },
			.gradationMOffset = { 0x7F, 0x7F, 0x7F, 0x7F, 0x7F },
			.gradationMGain = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
			.gradationMBorder = { 0x7F, 0x7F, 0x7F, 0x7F },
			.levelClipPOffset = { 0x7F, 0x7F, 0x7F },
			.levelClipPGain = { 0x7F, 0x7F, 0x7F },
			.levelClipPDorder = { 0xFF, 0xFF },
			.levelClipMOffset = { 0x7F, 0x7F, 0x7F },
			.levelClipMGain = { 0x7F, 0x7F, 0x7F },
			.levelClipMBorder = { 0xFF, 0xFF },
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
			.coringMGain = { 0x44, 0x55, 0x66, 0x77 },
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
			.gradationMOffset = { 0x54, 0x43, 0x32, 0x21, 0x10 },
			.gradationMGain = { 0x20, 0x30, 0x40, 0x50, 0x60 },
			.gradationMBorder = { 0x76, 0x65, 0x54, 0x43 },
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

	for( loopcnt = 0; loopcnt < (sizeof(r2yPostResize0) / sizeof(r2yPostResize0[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_proc_ctrl_post_resize_edge0(self->imR2yProc, pipeNo, &r2yPostResize0[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0en        = 0x%x\n",  ioR2yP1.yyw.ee0ctl.bit.ee0en ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tc        = 0x%x\n",  ioR2yP1.yyw.ee0ctl.bit.ee0tc ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk[0]   = 0x%lx\n", ioR2yP1.yyw.ee0hpfk.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk[1]   = 0x%lx\n", ioR2yP1.yyw.ee0hpfk.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk0     = 0x%x\n",  ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk1     = 0x%x\n",  ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk2     = 0x%x\n",  ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk3     = 0x%x\n",  ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk4     = 0x%x\n",  ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk5     = 0x%x\n",  ioR2yP1.yyw.ee0hpfk.bit.ee0hpfk5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0nrlv      = 0x%x\n",  ioR2yP1.yyw.ee0nrlv.bit.ee0nrlv ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpof0  = 0x%x\n",  ioR2yP1.yyw.ee0corpof.bit.ee0corpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpof1  = 0x%x\n",  ioR2yP1.yyw.ee0corpof.bit.ee0corpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpof2  = 0x%x\n",  ioR2yP1.yyw.ee0corpof.bit.ee0corpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpof3  = 0x%x\n",  ioR2yP1.yyw.ee0corpof.bit.ee0corpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpga    = 0x%lx\n", ioR2yP1.yyw.ee0corpga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpga0  = 0x%x\n",  ioR2yP1.yyw.ee0corpga.bit.ee0corpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpga1  = 0x%x\n",  ioR2yP1.yyw.ee0corpga.bit.ee0corpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpga2  = 0x%x\n",  ioR2yP1.yyw.ee0corpga.bit.ee0corpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpga3  = 0x%x\n",  ioR2yP1.yyw.ee0corpga.bit.ee0corpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpbd1  = 0x%x\n",  ioR2yP1.yyw.ee0corpbd.bit.ee0corpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpbd2  = 0x%x\n",  ioR2yP1.yyw.ee0corpbd.bit.ee0corpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpbd3  = 0x%x\n",  ioR2yP1.yyw.ee0corpbd.bit.ee0corpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormof0  = 0x%x\n",  ioR2yP1.yyw.ee0cormof.bit.ee0cormof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormof1  = 0x%x\n",  ioR2yP1.yyw.ee0cormof.bit.ee0cormof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormof2  = 0x%x\n",  ioR2yP1.yyw.ee0cormof.bit.ee0cormof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormof3  = 0x%x\n",  ioR2yP1.yyw.ee0cormof.bit.ee0cormof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormga    = 0x%lx\n", ioR2yP1.yyw.ee0cormga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormga0  = 0x%x\n",  ioR2yP1.yyw.ee0cormga.bit.ee0cormga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormga1  = 0x%x\n",  ioR2yP1.yyw.ee0cormga.bit.ee0cormga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormga2  = 0x%x\n",  ioR2yP1.yyw.ee0cormga.bit.ee0cormga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormga3  = 0x%x\n",  ioR2yP1.yyw.ee0cormga.bit.ee0cormga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormbd1  = 0x%x\n",  ioR2yP1.yyw.ee0cormbd.bit.ee0cormbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormbd2  = 0x%x\n",  ioR2yP1.yyw.ee0cormbd.bit.ee0cormbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormbd3  = 0x%x\n",  ioR2yP1.yyw.ee0cormbd.bit.ee0cormbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclsup    = 0x%x\n",  ioR2yP1.yyw.ee0sclsup.bit.ee0sclsup ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof0  = 0x%x\n",  ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof1  = 0x%x\n",  ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof2  = 0x%x\n",  ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof3  = 0x%x\n",  ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof4  = 0x%x\n",  ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof5  = 0x%x\n",  ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof6  = 0x%x\n",  ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof7  = 0x%x\n",  ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof8  = 0x%x\n",  ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof9  = 0x%x\n",  ioR2yP1.yyw.ee0sclpof.bit.ee0sclpof9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga[0] = 0x%lx\n", ioR2yP1.yyw.ee0sclpga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga[1] = 0x%lx\n", ioR2yP1.yyw.ee0sclpga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga[2] = 0x%lx\n", ioR2yP1.yyw.ee0sclpga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga[3] = 0x%lx\n", ioR2yP1.yyw.ee0sclpga.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga[4] = 0x%lx\n", ioR2yP1.yyw.ee0sclpga.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga0  = 0x%x\n",  ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga1  = 0x%x\n",  ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga2  = 0x%x\n",  ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga3  = 0x%x\n",  ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga4  = 0x%x\n",  ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga5  = 0x%x\n",  ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga6  = 0x%x\n",  ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga7  = 0x%x\n",  ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga8  = 0x%x\n",  ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga9  = 0x%x\n",  ioR2yP1.yyw.ee0sclpga.bit.ee0sclpga9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd1  = 0x%x\n",  ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd2  = 0x%x\n",  ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd3  = 0x%x\n",  ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd4  = 0x%x\n",  ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd5  = 0x%x\n",  ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd6  = 0x%x\n",  ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd7  = 0x%x\n",  ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd8  = 0x%x\n",  ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd9  = 0x%x\n",  ioR2yP1.yyw.ee0sclpbd.bit.ee0sclpbd9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof0  = 0x%x\n",  ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof1  = 0x%x\n",  ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof2  = 0x%x\n",  ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof3  = 0x%x\n",  ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof4  = 0x%x\n",  ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof5  = 0x%x\n",  ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof6  = 0x%x\n",  ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof7  = 0x%x\n",  ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof8  = 0x%x\n",  ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof9  = 0x%x\n",  ioR2yP1.yyw.ee0sclmof.bit.ee0sclmof9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga[0] = 0x%lx\n", ioR2yP1.yyw.ee0sclmga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga[1] = 0x%lx\n", ioR2yP1.yyw.ee0sclmga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga[2] = 0x%lx\n", ioR2yP1.yyw.ee0sclmga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga[3] = 0x%lx\n", ioR2yP1.yyw.ee0sclmga.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga[4] = 0x%lx\n", ioR2yP1.yyw.ee0sclmga.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga0  = 0x%x\n",  ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga1  = 0x%x\n",  ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga2  = 0x%x\n",  ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga3  = 0x%x\n",  ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga4  = 0x%x\n",  ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga5  = 0x%x\n",  ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga6  = 0x%x\n",  ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga7  = 0x%x\n",  ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga8  = 0x%x\n",  ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga9  = 0x%x\n",  ioR2yP1.yyw.ee0sclmga.bit.ee0sclmga9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd1  = 0x%x\n",  ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd2  = 0x%x\n",  ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd3  = 0x%x\n",  ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd4  = 0x%x\n",  ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd5  = 0x%x\n",  ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd6  = 0x%x\n",  ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd7  = 0x%x\n",  ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd8  = 0x%x\n",  ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd9  = 0x%x\n",  ioR2yP1.yyw.ee0sclmbd.bit.ee0sclmbd9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpof0  = 0x%x\n",  ioR2yP1.yyw.ee0tonpof.bit.ee0tonpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpof1  = 0x%x\n",  ioR2yP1.yyw.ee0tonpof.bit.ee0tonpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpof2  = 0x%x\n",  ioR2yP1.yyw.ee0tonpof.bit.ee0tonpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpof3  = 0x%x\n",  ioR2yP1.yyw.ee0tonpof.bit.ee0tonpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpof4  = 0x%x\n",  ioR2yP1.yyw.ee0tonpof.bit.ee0tonpof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga[0] = 0x%lx\n", ioR2yP1.yyw.ee0tonpga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga[1] = 0x%lx\n", ioR2yP1.yyw.ee0tonpga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga[2] = 0x%lx\n", ioR2yP1.yyw.ee0tonpga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga0  = 0x%x\n",  ioR2yP1.yyw.ee0tonpga.bit.ee0tonpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga1  = 0x%x\n",  ioR2yP1.yyw.ee0tonpga.bit.ee0tonpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga2  = 0x%x\n",  ioR2yP1.yyw.ee0tonpga.bit.ee0tonpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga3  = 0x%x\n",  ioR2yP1.yyw.ee0tonpga.bit.ee0tonpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga4  = 0x%x\n",  ioR2yP1.yyw.ee0tonpga.bit.ee0tonpga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpbd1  = 0x%x\n",  ioR2yP1.yyw.ee0tonpbd.bit.ee0tonpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpbd2  = 0x%x\n",  ioR2yP1.yyw.ee0tonpbd.bit.ee0tonpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpbd3  = 0x%x\n",  ioR2yP1.yyw.ee0tonpbd.bit.ee0tonpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpbd4  = 0x%x\n",  ioR2yP1.yyw.ee0tonpbd.bit.ee0tonpbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmof0  = 0x%x\n",  ioR2yP1.yyw.ee0tonmof.bit.ee0tonmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmof1  = 0x%x\n",  ioR2yP1.yyw.ee0tonmof.bit.ee0tonmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmof2  = 0x%x\n",  ioR2yP1.yyw.ee0tonmof.bit.ee0tonmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmof3  = 0x%x\n",  ioR2yP1.yyw.ee0tonmof.bit.ee0tonmof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmof4  = 0x%x\n",  ioR2yP1.yyw.ee0tonmof.bit.ee0tonmof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga[0] = 0x%lx\n", ioR2yP1.yyw.ee0tonmga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga[1] = 0x%lx\n", ioR2yP1.yyw.ee0tonmga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga[2] = 0x%lx\n", ioR2yP1.yyw.ee0tonmga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga0  = 0x%x\n",  ioR2yP1.yyw.ee0tonmga.bit.ee0tonmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga1  = 0x%x\n",  ioR2yP1.yyw.ee0tonmga.bit.ee0tonmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga2  = 0x%x\n",  ioR2yP1.yyw.ee0tonmga.bit.ee0tonmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga3  = 0x%x\n",  ioR2yP1.yyw.ee0tonmga.bit.ee0tonmga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga4  = 0x%x\n",  ioR2yP1.yyw.ee0tonmga.bit.ee0tonmga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmbd1  = 0x%x\n",  ioR2yP1.yyw.ee0tonmbd.bit.ee0tonmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmbd2  = 0x%x\n",  ioR2yP1.yyw.ee0tonmbd.bit.ee0tonmbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmbd3  = 0x%x\n",  ioR2yP1.yyw.ee0tonmbd.bit.ee0tonmbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmbd4  = 0x%x\n",  ioR2yP1.yyw.ee0tonmbd.bit.ee0tonmbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppof0  = 0x%x\n",  ioR2yP1.yyw.ee0clppof.bit.ee0clppof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppof1  = 0x%x\n",  ioR2yP1.yyw.ee0clppof.bit.ee0clppof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppof2  = 0x%x\n",  ioR2yP1.yyw.ee0clppof.bit.ee0clppof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppga    = 0x%lx\n", ioR2yP1.yyw.ee0clppga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppga0  = 0x%x\n",  ioR2yP1.yyw.ee0clppga.bit.ee0clppga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppga1  = 0x%x\n",  ioR2yP1.yyw.ee0clppga.bit.ee0clppga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppga2  = 0x%x\n",  ioR2yP1.yyw.ee0clppga.bit.ee0clppga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppbd1  = 0x%x\n",  ioR2yP1.yyw.EE0CLPPBD.bit.ee0clppbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPPBD_2  = 0x%x\n",  ioR2yP1.yyw.EE0CLPPBD.bit.EE0CLPPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMOF_0  = 0x%x\n",  ioR2yP1.yyw.EE0CLPMOF.bit.EE0CLPMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMOF_1  = 0x%x\n",  ioR2yP1.yyw.EE0CLPMOF.bit.EE0CLPMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMOF_2  = 0x%x\n",  ioR2yP1.yyw.EE0CLPMOF.bit.EE0CLPMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMGA    = 0x%lx\n", ioR2yP1.yyw.EE0CLPMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMGA_0  = 0x%x\n",  ioR2yP1.yyw.EE0CLPMGA.bit.EE0CLPMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMGA_1  = 0x%x\n",  ioR2yP1.yyw.EE0CLPMGA.bit.EE0CLPMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMGA_2  = 0x%x\n",  ioR2yP1.yyw.EE0CLPMGA.bit.EE0CLPMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMBD_1  = 0x%x\n",  ioR2yP1.yyw.EE0CLPMBD.bit.EE0CLPMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMBD_2  = 0x%x\n",  ioR2yP1.yyw.EE0CLPMBD.bit.EE0CLPMBD_2 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0en        = 0x%x\n",  ioR2yP2.yyw.ee0ctl.bit.ee0en ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tc        = 0x%x\n",  ioR2yP2.yyw.ee0ctl.bit.ee0tc ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk[0]   = 0x%lx\n", ioR2yP2.yyw.ee0hpfk.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk[1]   = 0x%lx\n", ioR2yP2.yyw.ee0hpfk.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk0     = 0x%x\n",  ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk1     = 0x%x\n",  ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk2     = 0x%x\n",  ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk3     = 0x%x\n",  ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk4     = 0x%x\n",  ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0hpfk5     = 0x%x\n",  ioR2yP2.yyw.ee0hpfk.bit.ee0hpfk5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0nrlv      = 0x%x\n",  ioR2yP2.yyw.ee0nrlv.bit.ee0nrlv ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpof0  = 0x%x\n",  ioR2yP2.yyw.ee0corpof.bit.ee0corpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpof1  = 0x%x\n",  ioR2yP2.yyw.ee0corpof.bit.ee0corpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpof2  = 0x%x\n",  ioR2yP2.yyw.ee0corpof.bit.ee0corpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpof3  = 0x%x\n",  ioR2yP2.yyw.ee0corpof.bit.ee0corpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpga    = 0x%lx\n", ioR2yP2.yyw.ee0corpga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpga0  = 0x%x\n",  ioR2yP2.yyw.ee0corpga.bit.ee0corpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpga1  = 0x%x\n",  ioR2yP2.yyw.ee0corpga.bit.ee0corpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpga2  = 0x%x\n",  ioR2yP2.yyw.ee0corpga.bit.ee0corpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpga3  = 0x%x\n",  ioR2yP2.yyw.ee0corpga.bit.ee0corpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpbd1  = 0x%x\n",  ioR2yP2.yyw.ee0corpbd.bit.ee0corpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpbd2  = 0x%x\n",  ioR2yP2.yyw.ee0corpbd.bit.ee0corpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0corpbd3  = 0x%x\n",  ioR2yP2.yyw.ee0corpbd.bit.ee0corpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormof0  = 0x%x\n",  ioR2yP2.yyw.ee0cormof.bit.ee0cormof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormof1  = 0x%x\n",  ioR2yP2.yyw.ee0cormof.bit.ee0cormof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormof2  = 0x%x\n",  ioR2yP2.yyw.ee0cormof.bit.ee0cormof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormof3  = 0x%x\n",  ioR2yP2.yyw.ee0cormof.bit.ee0cormof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormga    = 0x%lx\n", ioR2yP2.yyw.ee0cormga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormga0  = 0x%x\n",  ioR2yP2.yyw.ee0cormga.bit.ee0cormga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormga1  = 0x%x\n",  ioR2yP2.yyw.ee0cormga.bit.ee0cormga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormga2  = 0x%x\n",  ioR2yP2.yyw.ee0cormga.bit.ee0cormga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormga3  = 0x%x\n",  ioR2yP2.yyw.ee0cormga.bit.ee0cormga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormbd1  = 0x%x\n",  ioR2yP2.yyw.ee0cormbd.bit.ee0cormbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormbd2  = 0x%x\n",  ioR2yP2.yyw.ee0cormbd.bit.ee0cormbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0cormbd3  = 0x%x\n",  ioR2yP2.yyw.ee0cormbd.bit.ee0cormbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclsup    = 0x%x\n",  ioR2yP2.yyw.ee0sclsup.bit.ee0sclsup ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof0  = 0x%x\n",  ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof1  = 0x%x\n",  ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof2  = 0x%x\n",  ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof3  = 0x%x\n",  ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof4  = 0x%x\n",  ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof5  = 0x%x\n",  ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof6  = 0x%x\n",  ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof7  = 0x%x\n",  ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof8  = 0x%x\n",  ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpof9  = 0x%x\n",  ioR2yP2.yyw.ee0sclpof.bit.ee0sclpof9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga[0] = 0x%lx\n", ioR2yP2.yyw.ee0sclpga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga[1] = 0x%lx\n", ioR2yP2.yyw.ee0sclpga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga[2] = 0x%lx\n", ioR2yP2.yyw.ee0sclpga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga[3] = 0x%lx\n", ioR2yP2.yyw.ee0sclpga.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga[4] = 0x%lx\n", ioR2yP2.yyw.ee0sclpga.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga0  = 0x%x\n",  ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga1  = 0x%x\n",  ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga2  = 0x%x\n",  ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga3  = 0x%x\n",  ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga4  = 0x%x\n",  ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga5  = 0x%x\n",  ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga6  = 0x%x\n",  ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga7  = 0x%x\n",  ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga8  = 0x%x\n",  ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpga9  = 0x%x\n",  ioR2yP2.yyw.ee0sclpga.bit.ee0sclpga9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd1  = 0x%x\n",  ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd2  = 0x%x\n",  ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd3  = 0x%x\n",  ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd4  = 0x%x\n",  ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd5  = 0x%x\n",  ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd6  = 0x%x\n",  ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd7  = 0x%x\n",  ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd8  = 0x%x\n",  ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclpbd9  = 0x%x\n",  ioR2yP2.yyw.ee0sclpbd.bit.ee0sclpbd9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof0  = 0x%x\n",  ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof1  = 0x%x\n",  ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof2  = 0x%x\n",  ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof3  = 0x%x\n",  ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof4  = 0x%x\n",  ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof5  = 0x%x\n",  ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof6  = 0x%x\n",  ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof7  = 0x%x\n",  ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof8  = 0x%x\n",  ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmof9  = 0x%x\n",  ioR2yP2.yyw.ee0sclmof.bit.ee0sclmof9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga[0] = 0x%lx\n", ioR2yP2.yyw.ee0sclmga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga[1] = 0x%lx\n", ioR2yP2.yyw.ee0sclmga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga[2] = 0x%lx\n", ioR2yP2.yyw.ee0sclmga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga[3] = 0x%lx\n", ioR2yP2.yyw.ee0sclmga.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga[4] = 0x%lx\n", ioR2yP2.yyw.ee0sclmga.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga0  = 0x%x\n",  ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga1  = 0x%x\n",  ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga2  = 0x%x\n",  ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga3  = 0x%x\n",  ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga4  = 0x%x\n",  ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga5  = 0x%x\n",  ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga6  = 0x%x\n",  ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga7  = 0x%x\n",  ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga8  = 0x%x\n",  ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmga9  = 0x%x\n",  ioR2yP2.yyw.ee0sclmga.bit.ee0sclmga9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd1  = 0x%x\n",  ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd2  = 0x%x\n",  ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd3  = 0x%x\n",  ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd4  = 0x%x\n",  ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd5  = 0x%x\n",  ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd5 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd6  = 0x%x\n",  ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd6 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd7  = 0x%x\n",  ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd7 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd8  = 0x%x\n",  ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd8 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0sclmbd9  = 0x%x\n",  ioR2yP2.yyw.ee0sclmbd.bit.ee0sclmbd9 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpof0  = 0x%x\n",  ioR2yP2.yyw.ee0tonpof.bit.ee0tonpof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpof1  = 0x%x\n",  ioR2yP2.yyw.ee0tonpof.bit.ee0tonpof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpof2  = 0x%x\n",  ioR2yP2.yyw.ee0tonpof.bit.ee0tonpof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpof3  = 0x%x\n",  ioR2yP2.yyw.ee0tonpof.bit.ee0tonpof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpof4  = 0x%x\n",  ioR2yP2.yyw.ee0tonpof.bit.ee0tonpof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga[0] = 0x%lx\n", ioR2yP2.yyw.ee0tonpga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga[1] = 0x%lx\n", ioR2yP2.yyw.ee0tonpga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga[2] = 0x%lx\n", ioR2yP2.yyw.ee0tonpga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga0  = 0x%x\n",  ioR2yP2.yyw.ee0tonpga.bit.ee0tonpga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga1  = 0x%x\n",  ioR2yP2.yyw.ee0tonpga.bit.ee0tonpga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga2  = 0x%x\n",  ioR2yP2.yyw.ee0tonpga.bit.ee0tonpga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga3  = 0x%x\n",  ioR2yP2.yyw.ee0tonpga.bit.ee0tonpga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpga4  = 0x%x\n",  ioR2yP2.yyw.ee0tonpga.bit.ee0tonpga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpbd1  = 0x%x\n",  ioR2yP2.yyw.ee0tonpbd.bit.ee0tonpbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpbd2  = 0x%x\n",  ioR2yP2.yyw.ee0tonpbd.bit.ee0tonpbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpbd3  = 0x%x\n",  ioR2yP2.yyw.ee0tonpbd.bit.ee0tonpbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonpbd4  = 0x%x\n",  ioR2yP2.yyw.ee0tonpbd.bit.ee0tonpbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmof0  = 0x%x\n",  ioR2yP2.yyw.ee0tonmof.bit.ee0tonmof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmof1  = 0x%x\n",  ioR2yP2.yyw.ee0tonmof.bit.ee0tonmof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmof2  = 0x%x\n",  ioR2yP2.yyw.ee0tonmof.bit.ee0tonmof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmof3  = 0x%x\n",  ioR2yP2.yyw.ee0tonmof.bit.ee0tonmof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmof4  = 0x%x\n",  ioR2yP2.yyw.ee0tonmof.bit.ee0tonmof4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga[0] = 0x%lx\n", ioR2yP2.yyw.ee0tonmga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga[1] = 0x%lx\n", ioR2yP2.yyw.ee0tonmga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga[2] = 0x%lx\n", ioR2yP2.yyw.ee0tonmga.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga0  = 0x%x\n",  ioR2yP2.yyw.ee0tonmga.bit.ee0tonmga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga1  = 0x%x\n",  ioR2yP2.yyw.ee0tonmga.bit.ee0tonmga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga2  = 0x%x\n",  ioR2yP2.yyw.ee0tonmga.bit.ee0tonmga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga3  = 0x%x\n",  ioR2yP2.yyw.ee0tonmga.bit.ee0tonmga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmga4  = 0x%x\n",  ioR2yP2.yyw.ee0tonmga.bit.ee0tonmga4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmbd1  = 0x%x\n",  ioR2yP2.yyw.ee0tonmbd.bit.ee0tonmbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmbd2  = 0x%x\n",  ioR2yP2.yyw.ee0tonmbd.bit.ee0tonmbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmbd3  = 0x%x\n",  ioR2yP2.yyw.ee0tonmbd.bit.ee0tonmbd3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0tonmbd4  = 0x%x\n",  ioR2yP2.yyw.ee0tonmbd.bit.ee0tonmbd4 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppof0  = 0x%x\n",  ioR2yP2.yyw.ee0clppof.bit.ee0clppof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppof1  = 0x%x\n",  ioR2yP2.yyw.ee0clppof.bit.ee0clppof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppof2  = 0x%x\n",  ioR2yP2.yyw.ee0clppof.bit.ee0clppof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppga    = 0x%lx\n", ioR2yP2.yyw.ee0clppga.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppga0  = 0x%x\n",  ioR2yP2.yyw.ee0clppga.bit.ee0clppga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppga1  = 0x%x\n",  ioR2yP2.yyw.ee0clppga.bit.ee0clppga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppga2  = 0x%x\n",  ioR2yP2.yyw.ee0clppga.bit.ee0clppga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ee0clppbd1  = 0x%x\n",  ioR2yP2.yyw.EE0CLPPBD.bit.ee0clppbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPPBD_2  = 0x%x\n",  ioR2yP2.yyw.EE0CLPPBD.bit.EE0CLPPBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMOF_0  = 0x%x\n",  ioR2yP2.yyw.EE0CLPMOF.bit.EE0CLPMOF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMOF_1  = 0x%x\n",  ioR2yP2.yyw.EE0CLPMOF.bit.EE0CLPMOF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMOF_2  = 0x%x\n",  ioR2yP2.yyw.EE0CLPMOF.bit.EE0CLPMOF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMGA    = 0x%lx\n", ioR2yP2.yyw.EE0CLPMGA.word ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMGA_0  = 0x%x\n",  ioR2yP2.yyw.EE0CLPMGA.bit.EE0CLPMGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMGA_1  = 0x%x\n",  ioR2yP2.yyw.EE0CLPMGA.bit.EE0CLPMGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMGA_2  = 0x%x\n",  ioR2yP2.yyw.EE0CLPMGA.bit.EE0CLPMGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMBD_1  = 0x%x\n",  ioR2yP2.yyw.EE0CLPMBD.bit.EE0CLPMBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EE0CLPMBD_2  = 0x%x\n",  ioR2yP2.yyw.EE0CLPMBD.bit.EE0CLPMBD_2 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

CtImR2yClasse* ct_im_r2y_classe_new(void)
{
	CtImR2yClasse* self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSE, sizeof(CtImR2yClassePrivate));

	return self;
}

CtImR2yClasse* ct_im_r2y_classe_get(void)
{
	static CtImR2yClasse* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSE, sizeof(CtImR2yClassePrivate));
	}

	return self;
}
