/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassh
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2yclassh.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yClassh, ct_im_r2y_classh)
#define CT_IM_R2Y_CLASSH_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yClasshPrivate, CT_TYPE_IM_R2Y_CLASSH))


struct _CtImR2yClasshPrivate
{

};


static void ct_im_r2y_classh_constructor(CtImR2yClassh *self)
{
	CtImR2yClasshPrivate *priv = CT_IM_R2Y_CLASSH_GET_PRIVATE(self);
}

static void ct_im_r2y_classh_destructor(CtImR2yClassh *self)
{
	CtImR2yClasshPrivate *priv = CT_IM_R2Y_CLASSH_GET_PRIVATE(self);
}



#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_55: "
INT32 ct_im_r2y_classh_1_55( UCHAR pipeNo )
{
	TImR2yTcof r2yCtrlBtcOffset[] = {
		[0] = {	// max
			.R = 0x1FF,
			.G = 0x1FF,
			.B = 0x1FF,
			.Yb = 0x1FF,
		},
		[1] = {	// min
			.R = -0x200,
			.G = -0x200,
			.B = -0x200,
			.Yb = -0x200,
		},
		[2] = {	// indvisual
			.R = 0x10,
			.G = 0x20,
			.B = 0x30,
			.Yb = 0x40,
		}
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlBtcOffset) / sizeof(r2yCtrlBtcOffset[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_R2Y_Ctrl_BeforeTone_Offset( pipeNo, &r2yCtrlBtcOffset[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOF[0]   = 0x%lx\n", ioR2yP1.F_R2Y.BTC.TCOF.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOF[1]   = 0x%lx\n", ioR2yP1.F_R2Y.BTC.TCOF.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOFR     = 0x%x\n",  ioR2yP1.F_R2Y.BTC.TCOF.bit.TCOFR ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOFG     = 0x%x\n",  ioR2yP1.F_R2Y.BTC.TCOF.bit.TCOFG ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOFB     = 0x%x\n",  ioR2yP1.F_R2Y.BTC.TCOF.bit.TCOFB ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOFYB    = 0x%x\n",  ioR2yP1.F_R2Y.BTC.TCOF.bit.TCOFYB ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOF[0]   = 0x%lx\n", ioR2yP2.F_R2Y.BTC.TCOF.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOF[1]   = 0x%lx\n", ioR2yP2.F_R2Y.BTC.TCOF.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOFR     = 0x%x\n",  ioR2yP2.F_R2Y.BTC.TCOF.bit.TCOFR ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOFG     = 0x%x\n",  ioR2yP2.F_R2Y.BTC.TCOF.bit.TCOFG ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOFB     = 0x%x\n",  ioR2yP2.F_R2Y.BTC.TCOF.bit.TCOFB ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCOFYB    = 0x%x\n",  ioR2yP2.F_R2Y.BTC.TCOF.bit.TCOFYB ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_56: "
INT32 ct_im_r2y_classh_1_56( UCHAR pipeNo )
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
		ercd = Im_R2Y_Set_LuminanceEvaluationTblAccessEnable( pipeNo, accessEnable[loopcnt], D_IM_R2Y_WAIT_ON );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCTAEN = %u\n", ioR2yP1.F_R2Y.BTC.TCTCTL.bit.TCTAEN ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCTAEN = %u\n", ioR2yP2.F_R2Y.BTC.TCTCTL.bit.TCTAEN ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_57: "
INT32 ct_im_r2y_classh_1_57( UCHAR pipeNo )
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
		ercd = Im_R2Y_Set_BTC_HistogramTblAccessEnable( pipeNo, accessEnable[loopcnt], D_IM_R2Y_WAIT_ON );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCHAEN = %u\n", ioR2yP1.F_R2Y.BTC.TCHSCTL.bit.TCHAEN ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCHAEN = %u\n", ioR2yP2.F_R2Y.BTC.TCHSCTL.bit.TCHAEN ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_58: "
INT32 ct_im_r2y_classh_1_58( UCHAR pipeNo )
{
	TImR2yCtrlTone r2yCtrlTone[] = {
		[0] = {	// max
			.toneEnable = 1,
			.toneYbEnable = 1,
			.tableBlendEnable = 1,
			.tableResol = 2,
			.tableSelect = 3,
			.ytcOut = 1,
			.intBit = 3,
			.tableBlendRatio = 0x1F,
			.ycMatrix = {
				0xFF, 0xFF, 0xFF,
			},
			.tableEndp = {
				0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
			},
			.clipPR = 0xFFF,
			.clipMR = 0xFFF,
			.clipPG = 0xFFF,
			.clipMG = 0xFFF,
			.clipPB = 0xFFF,
			.clipMB = 0xFFF,
		},
		[1] = {	// min
			.toneEnable = 0,
			.toneYbEnable = 0,
			.tableBlendEnable = 0,
			.tableResol = 0,
			.tableSelect = 0,
			.ytcOut = 0,
			.intBit = 0,
			.tableBlendRatio = 0,
			.ycMatrix = {
				0, 0, 0,
			},
			.tableEndp = {
				0, 0, 0, 0,
			},
			.clipPR = 0,
			.clipMR = 0,
			.clipPG = 0,
			.clipMG = 0,
			.clipPB = 0,
			.clipMB = 0,
		},
		[2] = {	// indvisual
			.toneEnable = 0x0,
			.toneYbEnable = 0x1,
			.tableBlendEnable = 0x1,
			.tableResol = 0x1,
			.tableSelect = 0x2,
			.ytcOut = 1,
			.intBit = 1,
			.tableBlendRatio = 0x10,
			.ycMatrix = {
				0x4, 0x5, 0x6,
			},
			.tableEndp = {
				0x7, 0x8, 0x9, 0xA,
			},
			.clipPR = 0xB,
			.clipMR = 0xC,
			.clipPG = 0xD,
			.clipMG = 0xE,
			.clipPB = 0xF,
			.clipMB = 0x10,
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlTone) / sizeof(r2yCtrlTone[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_R2Y_Ctrl_Tone( pipeNo, &r2yCtrlTone[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "TCEN     = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCTL.bit.TCEN ));
		Ddim_Print(( "TCYBEN   = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCTL.bit.TCYBEN ));
		Ddim_Print(( "TCBLEN   = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCTL.bit.TCBLEN ));
		Ddim_Print(( "TCRES    = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCTL.bit.TCRES ));
		Ddim_Print(( "TCTBL    = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCTL.bit.TCTBL ));
		Ddim_Print(( "TCYOUT   = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCTL.bit.TCYOUT ));
		Ddim_Print(( "TCINTBIT = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCTL.bit.TCINTBIT ));
		Ddim_Print(( "TCBLND   = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCTL.bit.TCBLND ));
		Ddim_Print(( "TCYC_0_0 = 0x%x\n", ioR2yP1.F_R2Y.TC.TCYC.bit.TCYC_0_0 ));
		Ddim_Print(( "TCYC_0_1 = 0x%x\n", ioR2yP1.F_R2Y.TC.TCYC.bit.TCYC_0_1 ));
		Ddim_Print(( "TCYC_0_2 = 0x%x\n", ioR2yP1.F_R2Y.TC.TCYC.bit.TCYC_0_2 ));
		Ddim_Print(( "TCEP_0   = 0x%x\n", ioR2yP1.F_R2Y.TC.TCEP.bit.TCEP_0 ));
		Ddim_Print(( "TCEP_1   = 0x%x\n", ioR2yP1.F_R2Y.TC.TCEP.bit.TCEP_1 ));
		Ddim_Print(( "TCEP_2   = 0x%x\n", ioR2yP1.F_R2Y.TC.TCEP.bit.TCEP_2 ));
		Ddim_Print(( "TCEP_3   = 0x%x\n", ioR2yP1.F_R2Y.TC.TCEP.bit.TCEP_3 ));
		Ddim_Print(( "TCCLPRP  = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCLPR.bit.TCCLPRP ));
		Ddim_Print(( "TCCLPRM  = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCLPR.bit.TCCLPRM ));
		Ddim_Print(( "TCCLPGP  = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCLPG.bit.TCCLPGP ));
		Ddim_Print(( "TCCLPGM  = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCLPG.bit.TCCLPGM ));
		Ddim_Print(( "TCCLPBP  = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCLPB.bit.TCCLPBP ));
		Ddim_Print(( "TCCLPBM  = 0x%x\n", ioR2yP1.F_R2Y.TC.TCCLPB.bit.TCCLPBM ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "TCEN     = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCTL.bit.TCEN ));
		Ddim_Print(( "TCYBEN   = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCTL.bit.TCYBEN ));
		Ddim_Print(( "TCBLEN   = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCTL.bit.TCBLEN ));
		Ddim_Print(( "TCRES    = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCTL.bit.TCRES ));
		Ddim_Print(( "TCTBL    = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCTL.bit.TCTBL ));
		Ddim_Print(( "TCYOUT   = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCTL.bit.TCYOUT ));
		Ddim_Print(( "TCINTBIT = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCTL.bit.TCINTBIT ));
		Ddim_Print(( "TCBLND   = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCTL.bit.TCBLND ));
		Ddim_Print(( "TCYC_0_0 = 0x%x\n", ioR2yP2.F_R2Y.TC.TCYC.bit.TCYC_0_0 ));
		Ddim_Print(( "TCYC_0_1 = 0x%x\n", ioR2yP2.F_R2Y.TC.TCYC.bit.TCYC_0_1 ));
		Ddim_Print(( "TCYC_0_2 = 0x%x\n", ioR2yP2.F_R2Y.TC.TCYC.bit.TCYC_0_2 ));
		Ddim_Print(( "TCEP_0   = 0x%x\n", ioR2yP2.F_R2Y.TC.TCEP.bit.TCEP_0 ));
		Ddim_Print(( "TCEP_1   = 0x%x\n", ioR2yP2.F_R2Y.TC.TCEP.bit.TCEP_1 ));
		Ddim_Print(( "TCEP_2   = 0x%x\n", ioR2yP2.F_R2Y.TC.TCEP.bit.TCEP_2 ));
		Ddim_Print(( "TCEP_3   = 0x%x\n", ioR2yP2.F_R2Y.TC.TCEP.bit.TCEP_3 ));
		Ddim_Print(( "TCCLPRP  = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCLPR.bit.TCCLPRP ));
		Ddim_Print(( "TCCLPRM  = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCLPR.bit.TCCLPRM ));
		Ddim_Print(( "TCCLPGP  = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCLPG.bit.TCCLPGP ));
		Ddim_Print(( "TCCLPGM  = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCLPG.bit.TCCLPGM ));
		Ddim_Print(( "TCCLPBP  = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCLPB.bit.TCCLPBP ));
		Ddim_Print(( "TCCLPBM  = 0x%x\n", ioR2yP2.F_R2Y.TC.TCCLPB.bit.TCCLPBM ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_59: "
INT32 ct_im_r2y_classh_1_59( UCHAR pipeNo )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_ToneControlTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_ToneControlTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_ToneControlTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_ToneControlTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_60: "
INT32 ct_im_r2y_classh_1_60( UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	UCHAR tR2yEnable;
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		Ddim_Print(( "PIPE1\n" ));
		ioR2yP1.F_R2Y.CNTL.R2YFLAG.bit.TCACT = 0;
		ercd = Im_R2Y_Is_Act_Tone( 0, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP1.F_R2Y.CNTL.R2YFLAG.bit.TCACT = 1;
		ercd = Im_R2Y_Is_Act_Tone( 0, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP1.F_R2Y.CNTL.R2YFLAG.bit.TCACT = 0;
		ercd = Im_R2Y_Is_Act_Tone( 0, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		Ddim_Print(( "PIPE2\n" ));
		ioR2yP2.F_R2Y.CNTL.R2YFLAG.bit.TCACT = 0;
		ercd = Im_R2Y_Is_Act_Tone( 1, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP2.F_R2Y.CNTL.R2YFLAG.bit.TCACT = 1;
		ercd = Im_R2Y_Is_Act_Tone( 1, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP2.F_R2Y.CNTL.R2YFLAG.bit.TCACT = 0;
		ercd = Im_R2Y_Is_Act_Tone( 1, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_61: "
INT32 ct_im_r2y_classh_1_61( UCHAR pipeNo )
{
	TImR2yCtrlGamma r2yCtrlGamma[] = {
		[0] = {	// max
			.gammaEnable = 1,
			.gammaMode = 1,
			.gammaYbTblSimul = 1,
		},
		[1] = {	// min
			.gammaEnable = 0,
			.gammaMode = 0,
			.gammaYbTblSimul = 0,
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlGamma) / sizeof(r2yCtrlGamma[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_R2Y_Ctrl_Gamma( pipeNo, &r2yCtrlGamma[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "GMEN  = 0x%x\n", ioR2yP1.F_R2Y.GAM.GMCTL.bit.GMEN ));
		Ddim_Print(( "GMMD  = 0x%x\n", ioR2yP1.F_R2Y.GAM.GMCTL.bit.GMMD ));
		Ddim_Print(( "GAMSW = 0x%x\n", ioR2yP1.F_R2Y.GAM.GMCTL.bit.GAMSW ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "GMEN  = 0x%x\n", ioR2yP2.F_R2Y.GAM.GMCTL.bit.GMEN ));
		Ddim_Print(( "GMMD  = 0x%x\n", ioR2yP2.F_R2Y.GAM.GMCTL.bit.GMMD ));
		Ddim_Print(( "GAMSW = 0x%x\n", ioR2yP2.F_R2Y.GAM.GMCTL.bit.GAMSW ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_62: "
INT32 ct_im_r2y_classh_1_62( UCHAR pipeNo )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_GammaTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_GammaTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_GammaTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_GammaTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_63: "
INT32 ct_im_r2y_classh_1_63( UCHAR pipeNo )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_GammaYbTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_GammaYbTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_GammaYbTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = Im_R2Y_Set_GammaYbTblAccessEnable( pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_64: "
INT32 ct_im_r2y_classh_1_64( UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	UCHAR tR2yEnable;
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		Ddim_Print(( "PIPE1\n" ));
		ioR2yP1.F_R2Y.CNTL.R2YFLAG.bit.GAMACT = 0;
		ercd = Im_R2Y_Is_Act_Gamma( pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP1.F_R2Y.CNTL.R2YFLAG.bit.GAMACT = 1;
		ercd = Im_R2Y_Is_Act_Gamma( pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP1.F_R2Y.CNTL.R2YFLAG.bit.GAMACT = 0;
		ercd = Im_R2Y_Is_Act_Gamma( pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		Ddim_Print(( "PIPE2\n" ));
		ioR2yP2.F_R2Y.CNTL.R2YFLAG.bit.GAMACT = 0;
		ercd = Im_R2Y_Is_Act_Gamma( pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP2.F_R2Y.CNTL.R2YFLAG.bit.GAMACT = 1;
		ercd = Im_R2Y_Is_Act_Gamma( pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP2.F_R2Y.CNTL.R2YFLAG.bit.GAMACT = 0;
		ercd = Im_R2Y_Is_Act_Gamma( pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_65: "
INT32 ct_im_r2y_classh_1_65( UCHAR pipeNo )
{
	TImR2yCtrlCc1 r2yCtrlCc[] = {
		[0] = {	// max
			.posiDec = 3,
			.ccMatrix = {
				{ 0x7FF, 0x7FF, 0x7FF },
				{ 0x7FF, 0x7FF, 0x7FF },
				{ 0x7FF, 0x7FF, 0x7FF },
			},
			.clipPR = 0xFFF,
			.clipMR = 0xFFF,
			.clipPG = 0xFFF,
			.clipMG = 0xFFF,
			.clipPB = 0xFFF,
			.clipMB = 0xFFF,
		},
		[1] = {	// min
			.posiDec = 0,
			.ccMatrix = {
				{ -0x800, -0x800, -0x800 },
				{ -0x800, -0x800, -0x800 },
				{ -0x800, -0x800, -0x800 },
			},
			.clipPR = 0,
			.clipMR = 0,
			.clipPG = 0,
			.clipMG = 0,
			.clipPB = 0,
			.clipMB = 0,
		},
		[2] = {	// indvisual
			.posiDec = 0,
			.ccMatrix = {
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 },
			},
			.clipPR = 10,
			.clipMR = 11,
			.clipPG = 12,
			.clipMG = 13,
			.clipPB = 14,
			.clipMB = 15,
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
	ercd = Im_R2Y_Ctrl_CC1_Matrix( pipeNo, &r2yCtrlCc[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1DP    = %u\n",    ioR2yP1.F_R2Y.CCA1.CC1CTL.bit.CC1DP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[0]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA1.CC1K.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[1]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA1.CC1K.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[2]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA1.CC1K.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[3]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA1.CC1K.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[4]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA1.CC1K.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_0 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_0_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_1 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_0_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_2 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_0_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_0 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_1_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_1 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_1_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_2 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_1_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_0 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_2_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_1 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_2_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_2 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_2_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPRP = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1CLPR.bit.CC1CLPRP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPRM = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1CLPR.bit.CC1CLPRM ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPGP = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1CLPG.bit.CC1CLPGP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPGM = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1CLPG.bit.CC1CLPGM ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPBP = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1CLPB.bit.CC1CLPBP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPBM = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1CLPB.bit.CC1CLPBM ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1DP    = %u\n",    ioR2yP2.F_R2Y.CCA1.CC1CTL.bit.CC1DP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[0]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA1.CC1K.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[1]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA1.CC1K.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[2]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA1.CC1K.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[3]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA1.CC1K.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[4]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA1.CC1K.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_0 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_0_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_1 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_0_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_2 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_0_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_0 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_1_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_1 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_1_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_2 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_1_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_0 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_2_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_1 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_2_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_2 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_2_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPRP = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1CLPR.bit.CC1CLPRP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPRM = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1CLPR.bit.CC1CLPRM ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPGP = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1CLPG.bit.CC1CLPGP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPGM = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1CLPG.bit.CC1CLPGM ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPBP = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1CLPB.bit.CC1CLPBP ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1CLPBM = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1CLPB.bit.CC1CLPBM ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_66: "
INT32 ct_im_r2y_classh_1_66( UCHAR pipeNo )
{
	SHORT r2yCc1k[3][9] = {
		{	// max
			0x7FF, 0x7FF, 0x7FF , 0x7FF, 0x7FF, 0x7FF , 0x7FF, 0x7FF, 0x7FF,
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

	for( loopcnt = 0; loopcnt < (sizeof(r2yCc1k) / sizeof(r2yCc1k[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_R2Y_Set_CC1_Matrix_Coefficient( pipeNo, &r2yCc1k[loopcnt][0] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[0]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA1.CC1K.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[1]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA1.CC1K.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[2]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA1.CC1K.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[3]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA1.CC1K.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[4]  = 0x%lx\n", ioR2yP1.F_R2Y.CCA1.CC1K.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_0 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_0_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_1 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_0_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_2 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_0_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_0 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_1_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_1 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_1_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_2 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_1_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_0 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_2_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_1 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_2_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_2 = 0x%x\n",  ioR2yP1.F_R2Y.CCA1.CC1K.bit.CC1K_2_2 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[0]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA1.CC1K.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[1]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA1.CC1K.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[2]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA1.CC1K.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[3]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA1.CC1K.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K[4]  = 0x%lx\n", ioR2yP2.F_R2Y.CCA1.CC1K.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_0 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_0_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_1 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_0_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_0_2 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_0_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_0 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_1_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_1 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_1_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_1_2 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_1_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_0 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_2_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_1 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_2_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "CC1K_2_2 = 0x%x\n",  ioR2yP2.F_R2Y.CCA1.CC1K.bit.CC1K_2_2 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_67: "
INT32 ct_im_r2y_classh_1_67( UCHAR pipeNo )
{
	TImR2yCtrlYcc r2yCtrlYcc[] = {
		[0] = {	// max
			.ycCoeff = {
				{ 0xFF, 0xFF, 0xFF, },
				{ 0xFF, 0xFF, 0xFF, },
				{ 0xFF, 0xFF, 0xFF, },
			},
			.yBlendRatio = 0x3F,
			.ybBlendRatio = 0x3F,
		},
		[1] = {	// min
			.ycCoeff = {
				{ -0x100, -0x100, -0x100, },
				{ -0x100, -0x100, -0x100, },
				{ -0x100, -0x100, -0x100, },
			},
			.yBlendRatio = 0,
			.ybBlendRatio = 0,
		},
		[2] = {	// indvisual
			.ycCoeff = {
				{ 0x1, 0x2, 0x3, },
				{ 0x4, 0x5, 0x6, },
				{ 0x7, 0x8, 0x9, },
			},
			.yBlendRatio = 0xA,
			.ybBlendRatio = 0xB,
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlYcc) / sizeof(r2yCtrlYcc[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_R2Y_Ctrl_Yc_Convert( pipeNo, &r2yCtrlYcc[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "YC[0]  = 0x%lx\n", ioR2yP1.F_R2Y.YC.YC.word[0] ));
		Ddim_Print(( "YC[1]  = 0x%lx\n", ioR2yP1.F_R2Y.YC.YC.word[1] ));
		Ddim_Print(( "YC[2]  = 0x%lx\n", ioR2yP1.F_R2Y.YC.YC.word[2] ));
		Ddim_Print(( "YC[3]  = 0x%lx\n", ioR2yP1.F_R2Y.YC.YC.word[3] ));
		Ddim_Print(( "YC[4]  = 0x%lx\n", ioR2yP1.F_R2Y.YC.YC.word[4] ));
		Ddim_Print(( "YC_0_0 = 0x%x\n",  ioR2yP1.F_R2Y.YC.YC.bit.YC_0_0 ));
		Ddim_Print(( "YC_0_1 = 0x%x\n",  ioR2yP1.F_R2Y.YC.YC.bit.YC_0_1 ));
		Ddim_Print(( "YC_0_2 = 0x%x\n",  ioR2yP1.F_R2Y.YC.YC.bit.YC_0_2 ));
		Ddim_Print(( "YC_1_0 = 0x%x\n",  ioR2yP1.F_R2Y.YC.YC.bit.YC_1_0 ));
		Ddim_Print(( "YC_1_1 = 0x%x\n",  ioR2yP1.F_R2Y.YC.YC.bit.YC_1_1 ));
		Ddim_Print(( "YC_1_2 = 0x%x\n",  ioR2yP1.F_R2Y.YC.YC.bit.YC_1_2 ));
		Ddim_Print(( "YC_2_0 = 0x%x\n",  ioR2yP1.F_R2Y.YC.YC.bit.YC_2_0 ));
		Ddim_Print(( "YC_2_1 = 0x%x\n",  ioR2yP1.F_R2Y.YC.YC.bit.YC_2_1 ));
		Ddim_Print(( "YC_2_2 = 0x%x\n",  ioR2yP1.F_R2Y.YC.YC.bit.YC_2_2 ));
		Ddim_Print(( "YYBLND = 0x%x\n",  ioR2yP1.F_R2Y.YC.YBLEND.bit.YYBLND ));
		Ddim_Print(( "YBBLND = 0x%x\n",  ioR2yP1.F_R2Y.YC.YBLEND.bit.YBBLND ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "YC[0]  = 0x%lx\n", ioR2yP2.F_R2Y.YC.YC.word[0] ));
		Ddim_Print(( "YC[1]  = 0x%lx\n", ioR2yP2.F_R2Y.YC.YC.word[1] ));
		Ddim_Print(( "YC[2]  = 0x%lx\n", ioR2yP2.F_R2Y.YC.YC.word[2] ));
		Ddim_Print(( "YC[3]  = 0x%lx\n", ioR2yP2.F_R2Y.YC.YC.word[3] ));
		Ddim_Print(( "YC[4]  = 0x%lx\n", ioR2yP2.F_R2Y.YC.YC.word[4] ));
		Ddim_Print(( "YC_0_0 = 0x%x\n",  ioR2yP2.F_R2Y.YC.YC.bit.YC_0_0 ));
		Ddim_Print(( "YC_0_1 = 0x%x\n",  ioR2yP2.F_R2Y.YC.YC.bit.YC_0_1 ));
		Ddim_Print(( "YC_0_2 = 0x%x\n",  ioR2yP2.F_R2Y.YC.YC.bit.YC_0_2 ));
		Ddim_Print(( "YC_1_0 = 0x%x\n",  ioR2yP2.F_R2Y.YC.YC.bit.YC_1_0 ));
		Ddim_Print(( "YC_1_1 = 0x%x\n",  ioR2yP2.F_R2Y.YC.YC.bit.YC_1_1 ));
		Ddim_Print(( "YC_1_2 = 0x%x\n",  ioR2yP2.F_R2Y.YC.YC.bit.YC_1_2 ));
		Ddim_Print(( "YC_2_0 = 0x%x\n",  ioR2yP2.F_R2Y.YC.YC.bit.YC_2_0 ));
		Ddim_Print(( "YC_2_1 = 0x%x\n",  ioR2yP2.F_R2Y.YC.YC.bit.YC_2_1 ));
		Ddim_Print(( "YC_2_2 = 0x%x\n",  ioR2yP2.F_R2Y.YC.YC.bit.YC_2_2 ));
		Ddim_Print(( "YYBLND = 0x%x\n",  ioR2yP2.F_R2Y.YC.YBLEND.bit.YYBLND ));
		Ddim_Print(( "YBBLND = 0x%x\n",  ioR2yP2.F_R2Y.YC.YBLEND.bit.YBBLND ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_68: "
INT32 ct_im_r2y_classh_1_68( UCHAR pipeNo )
{
	TImR2yCtrlYnr r2yCtrlYnr[] = {
		[0] = {	// max
			.nrMode = 3,
			.blendRatio = 7,
			.offset = {
				0x3FF, 0x3FF, 0x3FF, 0x3FF,
			},
			.gain = {
				0x3FF, 0x3FF, 0x3FF, 0x3FF,
			},
			.border = {
				0x3FF, 0x3FF, 0x3FF,
			},
		},
		[1] = {	// min
			.nrMode = 0,
			.blendRatio = 0,
			.offset = {
				0, 0, 0, 0,
			},
			.gain = {
				-0x400, -0x400, -0x400, -0x400,
			},
			.border = {
				0, 0, 0,
			},
		},
		[2] = {	// indvisual
			.nrMode = 1,
			.blendRatio = 2,
			.offset = {
				3, 4, 5, 6,
			},
			.gain = {
				7, 8, 9, 10,
			},
			.border = {
				11, 12, 13,
			},
		},
	};
	UINT32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlYnr) / sizeof(r2yCtrlYnr[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_R2Y_Ctrl_Ynr( pipeNo, &r2yCtrlYnr[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRMD    = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NRCTL.bit.NRMD ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRBLEND = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NRCTL.bit.NRBLEND ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NROF_0  = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NROF.bit.NROF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NROF_1  = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NROF.bit.NROF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NROF_2  = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NROF.bit.NROF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NROF_3  = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NROF.bit.NROF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA[0] = 0x%lx\n", ioR2yP1.F_R2Y.YNR.NRGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA[1] = 0x%lx\n", ioR2yP1.F_R2Y.YNR.NRGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA_0  = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NRGA.bit.NRGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA_1  = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NRGA.bit.NRGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA_2  = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NRGA.bit.NRGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA_3  = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NRGA.bit.NRGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRBD_1  = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NRBD.bit.NRBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRBD_2  = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NRBD.bit.NRBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRBD_3  = 0x%x\n",  ioR2yP1.F_R2Y.YNR.NRBD.bit.NRBD_3 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRMD    = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NRCTL.bit.NRMD ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRBLEND = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NRCTL.bit.NRBLEND ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NROF_0  = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NROF.bit.NROF_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NROF_1  = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NROF.bit.NROF_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NROF_2  = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NROF.bit.NROF_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NROF_3  = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NROF.bit.NROF_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA[0] = 0x%lx\n", ioR2yP2.F_R2Y.YNR.NRGA.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA[1] = 0x%lx\n", ioR2yP2.F_R2Y.YNR.NRGA.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA_0  = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NRGA.bit.NRGA_0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA_1  = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NRGA.bit.NRGA_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA_2  = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NRGA.bit.NRGA_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRGA_3  = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NRGA.bit.NRGA_3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRBD_1  = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NRBD.bit.NRBD_1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRBD_2  = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NRBD.bit.NRBD_2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "NRBD_3  = 0x%x\n",  ioR2yP2.F_R2Y.YNR.NRBD.bit.NRBD_3 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_69: "
INT32 ct_im_r2y_classh_1_69( UCHAR pipeNo )
{
	TImR2yCtrlEdgeCmn r2yCtrlEdgeCmn[] = {
		[0] = {	// max
			.reductionMode = 1,
			.threshold = 0xFFF,
			.textureGain = 0x3F,
		},
		[1] = {	// min
			.reductionMode = 0,
			.threshold = 0,
			.textureGain = 0,
		},
		[2] = {	// indvisual
			.reductionMode = 1,
			.threshold = 0x400,
			.textureGain = 0x22,
		},
	};
	UINT32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlEdgeCmn) / sizeof(r2yCtrlEdgeCmn[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_R2Y_Ctrl_Edge_NoiseReduction( pipeNo, &r2yCtrlEdgeCmn[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGSMT     = 0x%x\n", ioR2yP1.F_R2Y.EGSM.EGSMCTL.bit.EGSMT ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGSMTTH   = 0x%x\n", ioR2yP1.F_R2Y.EGSM.EGSMTT.bit.EGSMTTH ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGSMTTXGA = 0x%x\n", ioR2yP1.F_R2Y.EGSM.EGSMTT.bit.EGSMTTXGA ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGSMT     = 0x%x\n", ioR2yP2.F_R2Y.EGSM.EGSMCTL.bit.EGSMT ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGSMTTH   = 0x%x\n", ioR2yP2.F_R2Y.EGSM.EGSMTT.bit.EGSMTTH ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "EGSMTTXGA = 0x%x\n", ioR2yP2.F_R2Y.EGSM.EGSMTT.bit.EGSMTTXGA ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}


CtImR2yClassh* ct_im_r2y_classh_new(void)
{
	CtImR2yClassh* self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSH, sizeof(CtImR2yClasshPrivate));

	return self;
}

CtImR2yClassh* ct_im_r2y_classh_get(void)
{
	static CtImR2yClassh* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSH, sizeof(CtImR2yClasshPrivate));
	}

	return self;
}
