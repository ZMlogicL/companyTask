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
	self->imR2yCtrl2=im_r2y_ctr2_new();
	self->imR2yClk=im_r2y_clk_new();
	self->imR2yCtrl=im_r2y_ctrl_new();
	self->imR2yStat=im_r2y_stat_new();
	self->imR2yEdge=im_r2y_edge_new();

}

static void ct_im_r2y_classh_destructor(CtImR2yClassh *self)
{
	CtImR2yClasshPrivate *priv = CT_IM_R2Y_CLASSH_GET_PRIVATE(self);
	if(self->imR2yCtrl2){
						k_object_unref(self->imR2yCtrl2);
						self->imR2yCtrl2=NULL;
					}
	if(self->imR2yClk){
						k_object_unref(self->imR2yClk);
						self->imR2yClk=NULL;
					}
	if(self->imR2yCtrl){
						k_object_unref(self->imR2yCtrl);
						self->imR2yCtrl=NULL;
					}
	if(self->imR2yStat){
						k_object_unref(self->imR2yStat);
						self->imR2yStat=NULL;
					}
	if(self->imR2yEdge){
						k_object_unref(self->imR2yEdge);
						self->imR2yEdge=NULL;
					}
}



#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_55: "
INT32 ct_im_r2y_classh_1_55(CtImR2yClassh *self, UCHAR pipeNo )
{
	TImR2yTcof r2yCtrlBtcOffset[] = {
		[0] = {	// max
			.r = 0x1FF,
			.g = 0x1FF,
			.b = 0x1FF,
			.yB = 0x1FF,
		},
		[1] = {	// min
			.r = -0x200,
			.g = -0x200,
			.b = -0x200,
			.yB = -0x200,
		},
		[2] = {	// indvisual
			.r = 0x10,
			.g = 0x20,
			.b = 0x30,
			.yB = 0x40,
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
		ercd = im_r2y_ctrl2_before_tone_offset(self->imR2yCtrl2, pipeNo, &r2yCtrlBtcOffset[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcof[0]   = 0x%lx\n", ioR2yP1.fR2y.btc.tcof.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcof[1]   = 0x%lx\n", ioR2yP1.fR2y.btc.tcof.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcofr     = 0x%x\n",  ioR2yP1.fR2y.btc.tcof.bit.tcofr ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcofg     = 0x%x\n",  ioR2yP1.fR2y.btc.tcof.bit.tcofg ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcofb     = 0x%x\n",  ioR2yP1.fR2y.btc.tcof.bit.tcofb ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcofyb    = 0x%x\n",  ioR2yP1.fR2y.btc.tcof.bit.tcofyb ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcof[0]   = 0x%lx\n", ioR2yP2.fR2y.btc.tcof.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcof[1]   = 0x%lx\n", ioR2yP2.fR2y.btc.tcof.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcofr     = 0x%x\n",  ioR2yP2.fR2y.btc.tcof.bit.tcofr ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcofg     = 0x%x\n",  ioR2yP2.fR2y.btc.tcof.bit.tcofg ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcofb     = 0x%x\n",  ioR2yP2.fR2y.btc.tcof.bit.tcofb ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "tcofyb    = 0x%x\n",  ioR2yP2.fR2y.btc.tcof.bit.tcofyb ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_56: "
INT32 ct_im_r2y_classh_1_56( CtImR2yClassh *self,UCHAR pipeNo )
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
		ercd = im_r2y_ctrl2_set_luminance_evaluation_tbl_access_enable(self->imR2yCtrl2, pipeNo, accessEnable[loopcnt], D_IM_R2Y_WAIT_ON );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCTAEN = %u\n", ioR2yP1.fR2y.btc.TCTCTL.bit.TCTAEN ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCTAEN = %u\n", ioR2yP2.fR2y.btc.TCTCTL.bit.TCTAEN ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_57: "
INT32 ct_im_r2y_classh_1_57( CtImR2yClassh *self,UCHAR pipeNo )
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
		ercd = im_r2y_ctrl2_set_btc_histogram_tbl_access_enable(self->imR2yCtrl2, pipeNo, accessEnable[loopcnt], D_IM_R2Y_WAIT_ON );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCHAEN = %u\n", ioR2yP1.fR2y.btc.TCHSCTL.bit.TCHAEN ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "TCHAEN = %u\n", ioR2yP2.fR2y.btc.TCHSCTL.bit.TCHAEN ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_58: "
INT32 ct_im_r2y_classh_1_58(CtImR2yClassh *self, UCHAR pipeNo )
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
		ercd = im_r2y_ctrl_tone(self->imR2yCtrl, pipeNo, &r2yCtrlTone[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "tcen     = 0x%x\n", ioR2yP1.fR2y.tc.tcctl.bit.tcen ));
		Ddim_Print(( "tcben   = 0x%x\n", ioR2yP1.fR2y.tc.tcctl.bit.tcben ));
		Ddim_Print(( "tcblen   = 0x%x\n", ioR2yP1.fR2y.tc.tcctl.bit.tcblen ));
		Ddim_Print(( "tcres    = 0x%x\n", ioR2yP1.fR2y.tc.tcctl.bit.tcres ));
		Ddim_Print(( "tctbl    = 0x%x\n", ioR2yP1.fR2y.tc.tcctl.bit.tctbl ));
		Ddim_Print(( "tcyout   = 0x%x\n", ioR2yP1.fR2y.tc.tcctl.bit.tcyout ));
		Ddim_Print(( "tcintbit = 0x%x\n", ioR2yP1.fR2y.tc.tcctl.bit.tcintbit ));
		Ddim_Print(( "tcblnd   = 0x%x\n", ioR2yP1.fR2y.tc.tcctl.bit.tcblnd ));
		Ddim_Print(( "tcyc00 = 0x%x\n", ioR2yP1.fR2y.tc.tcyc.bit.tcyc00 ));
		Ddim_Print(( "tcyc01 = 0x%x\n", ioR2yP1.fR2y.tc.tcyc.bit.tcyc01 ));
		Ddim_Print(( "tcyc02 = 0x%x\n", ioR2yP1.fR2y.tc.tcyc.bit.tcyc02 ));
		Ddim_Print(( "tcep0   = 0x%x\n", ioR2yP1.fR2y.tc.tcep.bit.tcep0 ));
		Ddim_Print(( "tcep1   = 0x%x\n", ioR2yP1.fR2y.tc.tcep.bit.tcep1 ));
		Ddim_Print(( "tcep2   = 0x%x\n", ioR2yP1.fR2y.tc.tcep.bit.tcep2 ));
		Ddim_Print(( "tcep3   = 0x%x\n", ioR2yP1.fR2y.tc.tcep.bit.tcep3 ));
		Ddim_Print(( "tcclprp  = 0x%x\n", ioR2yP1.fR2y.tc.tcclpr.bit.tcclprp ));
		Ddim_Print(( "tcclprm  = 0x%x\n", ioR2yP1.fR2y.tc.tcclpr.bit.tcclprm ));
		Ddim_Print(( "tcclpgp  = 0x%x\n", ioR2yP1.fR2y.tc.tcclpg.bit.tcclpgp ));
		Ddim_Print(( "tcclpgm  = 0x%x\n", ioR2yP1.fR2y.tc.tcclpg.bit.tcclpgm ));
		Ddim_Print(( "tcclpbp  = 0x%x\n", ioR2yP1.fR2y.tc.tcclpb.bit.tcclpbp ));
		Ddim_Print(( "tcclpbm  = 0x%x\n", ioR2yP1.fR2y.tc.tcclpb.bit.tcclpbm ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "tcen     = 0x%x\n", ioR2yP2.fR2y.tc.tcctl.bit.tcen ));
		Ddim_Print(( "tcben   = 0x%x\n", ioR2yP2.fR2y.tc.tcctl.bit.tcben ));
		Ddim_Print(( "tcblen   = 0x%x\n", ioR2yP2.fR2y.tc.tcctl.bit.tcblen ));
		Ddim_Print(( "tcres    = 0x%x\n", ioR2yP2.fR2y.tc.tcctl.bit.tcres ));
		Ddim_Print(( "tctbl    = 0x%x\n", ioR2yP2.fR2y.tc.tcctl.bit.tctbl ));
		Ddim_Print(( "tcyout   = 0x%x\n", ioR2yP2.fR2y.tc.tcctl.bit.tcyout ));
		Ddim_Print(( "tcintbit = 0x%x\n", ioR2yP2.fR2y.tc.tcctl.bit.tcintbit ));
		Ddim_Print(( "tcblnd   = 0x%x\n", ioR2yP2.fR2y.tc.tcctl.bit.tcblnd ));
		Ddim_Print(( "tcyc00 = 0x%x\n", ioR2yP2.fR2y.tc.tcyc.bit.tcyc00 ));
		Ddim_Print(( "tcyc01 = 0x%x\n", ioR2yP2.fR2y.tc.tcyc.bit.tcyc01 ));
		Ddim_Print(( "tcyc02 = 0x%x\n", ioR2yP2.fR2y.tc.tcyc.bit.tcyc02 ));
		Ddim_Print(( "tcep0   = 0x%x\n", ioR2yP2.fR2y.tc.tcep.bit.tcep0 ));
		Ddim_Print(( "tcep1   = 0x%x\n", ioR2yP2.fR2y.tc.tcep.bit.tcep1 ));
		Ddim_Print(( "tcep2   = 0x%x\n", ioR2yP2.fR2y.tc.tcep.bit.tcep2 ));
		Ddim_Print(( "tcep3   = 0x%x\n", ioR2yP2.fR2y.tc.tcep.bit.tcep3 ));
		Ddim_Print(( "tcclprp  = 0x%x\n", ioR2yP2.fR2y.tc.tcclpr.bit.tcclprp ));
		Ddim_Print(( "tcclprm  = 0x%x\n", ioR2yP2.fR2y.tc.tcclpr.bit.tcclprm ));
		Ddim_Print(( "tcclpgp  = 0x%x\n", ioR2yP2.fR2y.tc.tcclpg.bit.tcclpgp ));
		Ddim_Print(( "tcclpgm  = 0x%x\n", ioR2yP2.fR2y.tc.tcclpg.bit.tcclpgm ));
		Ddim_Print(( "tcclpbp  = 0x%x\n", ioR2yP2.fR2y.tc.tcclpb.bit.tcclpbp ));
		Ddim_Print(( "tcclpbm  = 0x%x\n", ioR2yP2.fR2y.tc.tcclpb.bit.tcclpbm ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_59: "
INT32 ct_im_r2y_classh_1_59(CtImR2yClassh *self, UCHAR pipeNo )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl_set_tone_control_tbl_access_enable(self->imR2yCtrl, pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl_set_tone_control_tbl_access_enable(self->imR2yCtrl, pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl_set_tone_control_tbl_access_enable(self->imR2yCtrl, pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl_set_tone_control_tbl_access_enable(self->imR2yCtrl, pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_60: "
INT32 ct_im_r2y_classh_1_60( CtImR2yClassh *self,UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	UCHAR tR2yEnable;
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		Ddim_Print(( "PIPE1\n" ));
		ioR2yP1.fR2y.CNTL.R2YFLAG.bit.TCACT = 0;
		ercd = im_r2y_ctrl_is_act_tone(self->imR2yCtrl, 0, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP1.fR2y.CNTL.R2YFLAG.bit.TCACT = 1;
		ercd = im_r2y_ctrl_is_act_tone(self->imR2yCtrl, 0, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP1.fR2y.CNTL.R2YFLAG.bit.TCACT = 0;
		ercd = im_r2y_ctrl_is_act_tone(self->imR2yCtrl, 0, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		Ddim_Print(( "PIPE2\n" ));
		ioR2yP2.fR2y.CNTL.R2YFLAG.bit.TCACT = 0;
		ercd = im_r2y_ctrl_is_act_tone(self->imR2yCtrl, 1, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP2.fR2y.CNTL.R2YFLAG.bit.TCACT = 1;
		ercd = im_r2y_ctrl_is_act_tone(self->imR2yCtrl, 1, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP2.fR2y.CNTL.R2YFLAG.bit.TCACT = 0;
		ercd = im_r2y_ctrl_is_act_tone(self->imR2yCtrl, 1, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_61: "
INT32 ct_im_r2y_classh_1_61( CtImR2yClassh *self,UCHAR pipeNo )
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
		ercd = im_r2y_ctrl2_gamma(self->imR2yCtrl2, pipeNo, &r2yCtrlGamma[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "gmen  = 0x%x\n", ioR2yP1.fR2y.gam.gmctl.bit.gmen ));
		Ddim_Print(( "gmmd  = 0x%x\n", ioR2yP1.fR2y.gam.gmctl.bit.gmmd ));
		Ddim_Print(( "gamsw = 0x%x\n", ioR2yP1.fR2y.gam.gmctl.bit.gamsw ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "gmen  = 0x%x\n", ioR2yP2.fR2y.gam.gmctl.bit.gmen ));
		Ddim_Print(( "gmmd  = 0x%x\n", ioR2yP2.fR2y.gam.gmctl.bit.gmmd ));
		Ddim_Print(( "gamsw = 0x%x\n", ioR2yP2.fR2y.gam.gmctl.bit.gamsw ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_62: "
INT32 ct_im_r2y_classh_1_62(CtImR2yClassh *self, UCHAR pipeNo )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl2_set_gamma_tbl_access_enable(self->imR2yCtrl2, pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_63: "
INT32 ct_im_r2y_classh_1_63( CtImR2yClassh *self,UCHAR pipeNo )
{
	INT32 ercd;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, D_IM_R2Y_ENABLE_ON, D_IM_R2Y_WAIT_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	ercd = im_r2y_ctrl2_set_gamma_yb_tbl_access_enable(self->imR2yCtrl2, pipeNo, D_IM_R2Y_ENABLE_OFF, D_IM_R2Y_WAIT_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_64: "
INT32 ct_im_r2y_classh_1_64( CtImR2yClassh *self,UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	UCHAR tR2yEnable;
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		Ddim_Print(( "PIPE1\n" ));
		ioR2yP1.fR2y.CNTL.R2YFLAG.bit.GAMACT = 0;
		ercd = im_r2y_ctrl2_is_act_gamma(self->imR2yCtrl2, pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP1.fR2y.CNTL.R2YFLAG.bit.GAMACT = 1;
		ercd = im_r2y_ctrl2_is_act_gamma(self->imR2yCtrl2, pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP1.fR2y.CNTL.R2YFLAG.bit.GAMACT = 0;
		ercd = im_r2y_ctrl2_is_act_gamma(self->imR2yCtrl2, pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		Ddim_Print(( "PIPE2\n" ));
		ioR2yP2.fR2y.CNTL.R2YFLAG.bit.GAMACT = 0;
		ercd = im_r2y_ctrl2_is_act_gamma(self->imR2yCtrl2, pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP2.fR2y.CNTL.R2YFLAG.bit.GAMACT = 1;
		ercd = im_r2y_ctrl2_is_act_gamma(self->imR2yCtrl2, pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
		ioR2yP2.fR2y.CNTL.R2YFLAG.bit.GAMACT = 0;
		ercd = im_r2y_ctrl2_is_act_gamma(self->imR2yCtrl2, pipeNo, &tR2yEnable );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%u\n", tR2yEnable ));
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_65: "
INT32 ct_im_r2y_classh_1_65(CtImR2yClassh *self, UCHAR pipeNo )
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
	ercd = im_r2y_ctrl2_cc1_matrix(self->imR2yCtrl2, pipeNo, &r2yCtrlCc[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1dp    = %u\n",    ioR2yP1.fR2y.cca1.cc1ctl.bit.cc1dp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[0]  = 0x%lx\n", ioR2yP1.fR2y.cca1.cc1k.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[1]  = 0x%lx\n", ioR2yP1.fR2y.cca1.cc1k.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[2]  = 0x%lx\n", ioR2yP1.fR2y.cca1.cc1k.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[3]  = 0x%lx\n", ioR2yP1.fR2y.cca1.cc1k.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[4]  = 0x%lx\n", ioR2yP1.fR2y.cca1.cc1k.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k00 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k00 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k01 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k01 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k02 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k02 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k10 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k10 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k11 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k11 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k12 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k12 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k20 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k20 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k21 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k21 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k22 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k22 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clprp = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1clpr.bit.cc1clprp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clprm = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1clpr.bit.cc1clprm ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clpgp = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1clpg.bit.cc1clpgp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clpgm = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1clpg.bit.cc1clpgm ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clpbp = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1clpb.bit.cc1clpbp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clpbm = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1clpb.bit.cc1clpbm ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1dp    = %u\n",    ioR2yP2.fR2y.cca1.cc1ctl.bit.cc1dp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[0]  = 0x%lx\n", ioR2yP2.fR2y.cca1.cc1k.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[1]  = 0x%lx\n", ioR2yP2.fR2y.cca1.cc1k.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[2]  = 0x%lx\n", ioR2yP2.fR2y.cca1.cc1k.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[3]  = 0x%lx\n", ioR2yP2.fR2y.cca1.cc1k.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[4]  = 0x%lx\n", ioR2yP2.fR2y.cca1.cc1k.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k00 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k00 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k01 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k01 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k02 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k02 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k10 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k10 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k11 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k11 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k12 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k12 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k20 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k20 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k21 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k21 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k22 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k22 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clprp = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1clpr.bit.cc1clprp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clprm = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1clpr.bit.cc1clprm ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clpgp = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1clpg.bit.cc1clpgp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clpgm = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1clpg.bit.cc1clpgm ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clpbp = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1clpb.bit.cc1clpbp ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1clpbm = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1clpb.bit.cc1clpbm ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_66: "
INT32 ct_im_r2y_classh_1_66(CtImR2yClassh *self, UCHAR pipeNo )
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
		ercd = im_r2y_ctrl2_set_cc1_matrix_coefficient(self->imR2yCtrl2, pipeNo, &r2yCc1k[loopcnt][0] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[0]  = 0x%lx\n", ioR2yP1.fR2y.cca1.cc1k.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[1]  = 0x%lx\n", ioR2yP1.fR2y.cca1.cc1k.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[2]  = 0x%lx\n", ioR2yP1.fR2y.cca1.cc1k.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[3]  = 0x%lx\n", ioR2yP1.fR2y.cca1.cc1k.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[4]  = 0x%lx\n", ioR2yP1.fR2y.cca1.cc1k.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k00 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k00 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k01 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k01 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k02 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k02 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k10 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k10 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k11 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k11 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k12 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k12 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k20 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k20 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k21 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k21 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k22 = 0x%x\n",  ioR2yP1.fR2y.cca1.cc1k.bit.cc1k22 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[0]  = 0x%lx\n", ioR2yP2.fR2y.cca1.cc1k.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[1]  = 0x%lx\n", ioR2yP2.fR2y.cca1.cc1k.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[2]  = 0x%lx\n", ioR2yP2.fR2y.cca1.cc1k.word[2] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[3]  = 0x%lx\n", ioR2yP2.fR2y.cca1.cc1k.word[3] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k[4]  = 0x%lx\n", ioR2yP2.fR2y.cca1.cc1k.word[4] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k00 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k00 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k01 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k01 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k02 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k02 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k10 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k10 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k11 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k11 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k12 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k12 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k20 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k20 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k21 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k21 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "cc1k22 = 0x%x\n",  ioR2yP2.fR2y.cca1.cc1k.bit.cc1k22 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_67: "
INT32 ct_im_r2y_classh_1_67(CtImR2yClassh *self, UCHAR pipeNo )
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
		ercd = im_r2y_ctrl2_yc_convert(self->imR2yCtrl2, pipeNo, &r2yCtrlYcc[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "yc[0]  = 0x%lx\n", ioR2yP1.fR2y.yc.yc.word[0] ));
		Ddim_Print(( "yc[1]  = 0x%lx\n", ioR2yP1.fR2y.yc.yc.word[1] ));
		Ddim_Print(( "yc[2]  = 0x%lx\n", ioR2yP1.fR2y.yc.yc.word[2] ));
		Ddim_Print(( "yc[3]  = 0x%lx\n", ioR2yP1.fR2y.yc.yc.word[3] ));
		Ddim_Print(( "yc[4]  = 0x%lx\n", ioR2yP1.fR2y.yc.yc.word[4] ));
		Ddim_Print(( "yc00 = 0x%x\n",  ioR2yP1.fR2y.yc.yc.bit.yc00 ));
		Ddim_Print(( "yc01 = 0x%x\n",  ioR2yP1.fR2y.yc.yc.bit.yc01 ));
		Ddim_Print(( "yc02 = 0x%x\n",  ioR2yP1.fR2y.yc.yc.bit.yc02 ));
		Ddim_Print(( "yc10 = 0x%x\n",  ioR2yP1.fR2y.yc.yc.bit.yc10 ));
		Ddim_Print(( "yc11 = 0x%x\n",  ioR2yP1.fR2y.yc.yc.bit.yc11 ));
		Ddim_Print(( "yc12 = 0x%x\n",  ioR2yP1.fR2y.yc.yc.bit.yc12 ));
		Ddim_Print(( "yc20 = 0x%x\n",  ioR2yP1.fR2y.yc.yc.bit.yc20 ));
		Ddim_Print(( "yc21 = 0x%x\n",  ioR2yP1.fR2y.yc.yc.bit.yc21 ));
		Ddim_Print(( "yc22 = 0x%x\n",  ioR2yP1.fR2y.yc.yc.bit.yc22 ));
		Ddim_Print(( "yyblnd = 0x%x\n",  ioR2yP1.fR2y.yc.yblend.bit.yyblnd ));
		Ddim_Print(( "ybblnd = 0x%x\n",  ioR2yP1.fR2y.yc.yblend.bit.ybblnd ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "yc[0]  = 0x%lx\n", ioR2yP2.fR2y.yc.yc.word[0] ));
		Ddim_Print(( "yc[1]  = 0x%lx\n", ioR2yP2.fR2y.yc.yc.word[1] ));
		Ddim_Print(( "yc[2]  = 0x%lx\n", ioR2yP2.fR2y.yc.yc.word[2] ));
		Ddim_Print(( "yc[3]  = 0x%lx\n", ioR2yP2.fR2y.yc.yc.word[3] ));
		Ddim_Print(( "yc[4]  = 0x%lx\n", ioR2yP2.fR2y.yc.yc.word[4] ));
		Ddim_Print(( "yc00 = 0x%x\n",  ioR2yP2.fR2y.yc.yc.bit.yc00 ));
		Ddim_Print(( "yc01 = 0x%x\n",  ioR2yP2.fR2y.yc.yc.bit.yc01 ));
		Ddim_Print(( "yc02 = 0x%x\n",  ioR2yP2.fR2y.yc.yc.bit.yc02 ));
		Ddim_Print(( "yc10 = 0x%x\n",  ioR2yP2.fR2y.yc.yc.bit.yc10 ));
		Ddim_Print(( "yc11 = 0x%x\n",  ioR2yP2.fR2y.yc.yc.bit.yc11 ));
		Ddim_Print(( "yc12 = 0x%x\n",  ioR2yP2.fR2y.yc.yc.bit.yc12 ));
		Ddim_Print(( "yc20 = 0x%x\n",  ioR2yP2.fR2y.yc.yc.bit.yc20 ));
		Ddim_Print(( "yc21 = 0x%x\n",  ioR2yP2.fR2y.yc.yc.bit.yc21 ));
		Ddim_Print(( "yc22 = 0x%x\n",  ioR2yP2.fR2y.yc.yc.bit.yc22 ));
		Ddim_Print(( "yyblnd = 0x%x\n",  ioR2yP2.fR2y.yc.yblend.bit.yyblnd ));
		Ddim_Print(( "ybblnd = 0x%x\n",  ioR2yP2.fR2y.yc.yblend.bit.ybblnd ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_68: "
INT32 ct_im_r2y_classh_1_68( CtImR2yClassh *self,UCHAR pipeNo )
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
		ercd = im_r2y_ctrl2_ynr(self->imR2yCtrl2, pipeNo, &r2yCtrlYnr[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrmd    = 0x%x\n",  ioR2yP1.fR2y.ynr.nrctl.bit.nrmd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrblend = 0x%x\n",  ioR2yP1.fR2y.ynr.nrctl.bit.nrblend ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrof0  = 0x%x\n",  ioR2yP1.fR2y.ynr.nrof.bit.nrof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrof1  = 0x%x\n",  ioR2yP1.fR2y.ynr.nrof.bit.nrof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrof2  = 0x%x\n",  ioR2yP1.fR2y.ynr.nrof.bit.nrof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrof3  = 0x%x\n",  ioR2yP1.fR2y.ynr.nrof.bit.nrof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga[0] = 0x%lx\n", ioR2yP1.fR2y.ynr.nrga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga[1] = 0x%lx\n", ioR2yP1.fR2y.ynr.nrga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga0  = 0x%x\n",  ioR2yP1.fR2y.ynr.nrga.bit.nrga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga1  = 0x%x\n",  ioR2yP1.fR2y.ynr.nrga.bit.nrga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga2  = 0x%x\n",  ioR2yP1.fR2y.ynr.nrga.bit.nrga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga3  = 0x%x\n",  ioR2yP1.fR2y.ynr.nrga.bit.nrga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrbd1  = 0x%x\n",  ioR2yP1.fR2y.ynr.nrbd.bit.nrbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrbd2  = 0x%x\n",  ioR2yP1.fR2y.ynr.nrbd.bit.nrbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrbd3  = 0x%x\n",  ioR2yP1.fR2y.ynr.nrbd.bit.nrbd3 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrmd    = 0x%x\n",  ioR2yP2.fR2y.ynr.nrctl.bit.nrmd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrblend = 0x%x\n",  ioR2yP2.fR2y.ynr.nrctl.bit.nrblend ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrof0  = 0x%x\n",  ioR2yP2.fR2y.ynr.nrof.bit.nrof0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrof1  = 0x%x\n",  ioR2yP2.fR2y.ynr.nrof.bit.nrof1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrof2  = 0x%x\n",  ioR2yP2.fR2y.ynr.nrof.bit.nrof2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrof3  = 0x%x\n",  ioR2yP2.fR2y.ynr.nrof.bit.nrof3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga[0] = 0x%lx\n", ioR2yP2.fR2y.ynr.nrga.word[0] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga[1] = 0x%lx\n", ioR2yP2.fR2y.ynr.nrga.word[1] ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga0  = 0x%x\n",  ioR2yP2.fR2y.ynr.nrga.bit.nrga0 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga1  = 0x%x\n",  ioR2yP2.fR2y.ynr.nrga.bit.nrga1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga2  = 0x%x\n",  ioR2yP2.fR2y.ynr.nrga.bit.nrga2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrga3  = 0x%x\n",  ioR2yP2.fR2y.ynr.nrga.bit.nrga3 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrbd1  = 0x%x\n",  ioR2yP2.fR2y.ynr.nrbd.bit.nrbd1 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrbd2  = 0x%x\n",  ioR2yP2.fR2y.ynr.nrbd.bit.nrbd2 ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "nrbd3  = 0x%x\n",  ioR2yP2.fR2y.ynr.nrbd.bit.nrbd3 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classh_1_69: "
INT32 ct_im_r2y_classh_1_69( CtImR2yClassh *self,UCHAR pipeNo )
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
		ercd = im_r2y_edge_noise_reduction(self->imR2yEdge, pipeNo, &r2yCtrlEdgeCmn[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egsmt     = 0x%x\n", ioR2yP1.fR2y.egsm.egsmctl.bit.egsmt ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egsmtth   = 0x%x\n", ioR2yP1.fR2y.egsm.egsmtt.bit.egsmtth ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egsmttxga = 0x%x\n", ioR2yP1.fR2y.egsm.egsmtt.bit.egsmttxga ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egsmt     = 0x%x\n", ioR2yP2.fR2y.egsm.egsmctl.bit.egsmt ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egsmtth   = 0x%x\n", ioR2yP2.fR2y.egsm.egsmtt.bit.egsmtth ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "egsmttxga = 0x%x\n", ioR2yP2.fR2y.egsm.egsmtt.bit.egsmttxga ));
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
