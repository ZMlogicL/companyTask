/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassd
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2yclassd.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yClassd, ct_im_r2y_classd)
#define CT_IM_R2Y_CLASSD_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yClassdPrivate, CT_TYPE_IM_R2Y_CLASSD))


struct _CtImR2yClassdPrivate
{

};


static void ct_im_r2y_classd_constructor(CtImR2yClassd *self)
{
	CtImR2yClassdPrivate *priv = CT_IM_R2Y_CLASSD_GET_PRIVATE(self);

	self->ctImR2yClassa=ct_im_r2y_classa_new();
	self->ctImR2y=ct_im_r2y_new();
	self->imR2y3=ct_im_r2y3_new();
	self->imR2y2=ct_im_r2y2_new();
	self->imR2yProc=ct_im_r2y_proc_new();
	self->imR2yClk=im_r2y_clk_new();
	self->imR2y=im_r2y_new();
	self->imR2yStat=im_r2y_stat_new();
}

static void ct_im_r2y_classd_destructor(CtImR2yClassd *self)
{
	CtImR2yClassdPrivate *priv = CT_IM_R2Y_CLASSD_GET_PRIVATE(self);
	if(self->ctImR2yClassa){
						k_object_unref(self->ctImR2yClassa);
						self->ctImR2yClassa=NULL;
					}
		if(self->ctImR2y){
							k_object_unref(self->ctImR2y);
							self->ctImR2y=NULL;
						}
		if(self->imR2y3){
							k_object_unref(self->imR2y3);
							self->imR2y3=NULL;
						}
		if(self->imR2y2){
							k_object_unref(self->imR2y2);
							self->imR2y2=NULL;
						}
		if(self->imR2yProc){
							k_object_unref(self->imR2yProc);
							self->imR2yProc=NULL;
						}
		if(self->imR2yClk){
							k_object_unref(self->imR2yClk);
							self->imR2yClk=NULL;
						}
		if(self->imR2y){
							k_object_unref(self->imR2y);
							self->imR2y=NULL;
						}
		if(self->imR2yStat){
									k_object_unref(self->imR2yStat);
									self->imR2yStat=NULL;
								}
}


#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_15: "
INT32 ct_im_r2y_classd_1_15(CtImR2yClassd*self, UCHAR pipeNo )
{
	TImR2yAxiYyrStat r2yAxiReadStat;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));


#ifdef CO_DEBUG_ON_PC
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		ioR2yP1.yych.yyraxsts.bit.yyrresp0 = 3;
		ioR2yP1.yych.yyraxsts.bit.yyrresp1 = 3;
		ioR2yP1.yych.yyraxsts.bit.yyrresp2 = 3;
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		ioR2yP2.yych.yyraxsts.bit.yyrresp0 = 3;
		ioR2yP2.yych.yyraxsts.bit.yyrresp1 = 3;
		ioR2yP2.yych.yyraxsts.bit.yyrresp2 = 3;
	}
#endif // CO_DEBUG_ON_PC
	memset( &r2yAxiReadStat, '\0', sizeof(r2yAxiReadStat) );
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_get_axi_read_stat(self->imR2y, pipeNo, &r2yAxiReadStat );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
	im_r2y_get_axi_read_stat(self->imR2y, pipeNo, &r2yAxiReadStat );

#endif
	Ddim_Print(( "yyrAxiStat[0] = %x\n", r2yAxiReadStat.yyrAxiStat[0] ));
	Ddim_Print(( "yyrAxiStat[1] = %x\n", r2yAxiReadStat.yyrAxiStat[1] ));
	Ddim_Print(( "yyrAxiStat[2] = %x\n", r2yAxiReadStat.yyrAxiStat[2] ));

#ifdef CO_DEBUG_ON_PC
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		ioR2yP1.yych.yyraxsts.bit.yyrresp0 = 0;
		ioR2yP1.yych.yyraxsts.bit.yyrresp1 = 0;
		ioR2yP1.yych.yyraxsts.bit.yyrresp2 = 0;
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		ioR2yP2.yych.yyraxsts.bit.yyrresp0 = 0;
		ioR2yP2.yych.yyraxsts.bit.yyrresp1 = 0;
		ioR2yP2.yych.yyraxsts.bit.yyrresp2 = 0;
	}
#endif // CO_DEBUG_ON_PC
	memset( &r2yAxiReadStat, '\0', sizeof(r2yAxiReadStat) );
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_get_axi_read_stat(self->imR2y, pipeNo, &r2yAxiReadStat );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
	im_r2y_get_axi_read_stat(self->imR2y, pipeNo, &r2yAxiReadStat );
#endif
	Ddim_Print(( "yyrAxiStat[0] = %x\n", r2yAxiReadStat.yyrAxiStat[0] ));
	Ddim_Print(( "yyrAxiStat[1] = %x\n", r2yAxiReadStat.yyrAxiStat[1] ));
	Ddim_Print(( "yyrAxiStat[2] = %x\n", r2yAxiReadStat.yyrAxiStat[2] ));

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_25: "
INT32 ct_im_r2y_classd_1_25( CtImR2yClassd*self,UCHAR pipeNo )
{
	UINT32 loopcnt1;
	UINT32 loopcnt2;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

#ifdef CO_MSG_PRINT_ON
	for( loopcnt1 = D_IM_R2Y_YYW_CH_0; loopcnt1 < D_IM_R2Y_YYW_CH_MAX; loopcnt1++ ) {
		for( loopcnt2 = D_IM_R2Y_YYW_BANK_0; loopcnt2 < D_IM_R2Y_YYW_BANK_MAX; loopcnt2++ ) {
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "##loop %u-%u\n", loopcnt1, loopcnt2 ));
			ercd = Im_R2Y_Set_OutBankIndex( pipeNo, loopcnt1, loopcnt2 );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
			im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIPE1\n" ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank0ps = %u\n", ioR2yP1.yyw.yywbank.bit.bank0ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank1ps = %u\n", ioR2yP1.yyw.yywbank.bit.bank1ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank2ps = %u\n", ioR2yP1.yyw.yywbank.bit.bank2ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bankaps = %u\n", ioR2yP1.yyw.yywbank.bit.bankaps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bankst  = %u\n", ioR2yP1.yyw.yywbank.bit.bankst ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIPE2\n" ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank0ps = %u\n", ioR2yP2.yyw.yywbank.bit.bank0ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank1ps = %u\n", ioR2yP2.yyw.yywbank.bit.bank1ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank2ps = %u\n", ioR2yP2.yyw.yywbank.bit.bank2ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bankaps = %u\n", ioR2yP2.yyw.yywbank.bit.bankaps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bankst  = %u\n", ioR2yP2.yyw.yywbank.bit.bankst ));
			im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
		}
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_26: "
INT32 ct_im_r2y_classd_1_26( CtImR2yClassd*self,UCHAR pipeNo )
{
	UINT32 loopcnt1;
	UINT32 loopcnt2;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	TImR2yOutbankInfo r2yAddr0;

	memset( &r2yAddr0, '\x0', sizeof(r2yAddr0) );
	r2yAddr0.bankInitialPosition = D_IM_R2Y_YYW_BANK_3;
	r2yAddr0.useBankNum = D_IM_R2Y_YYW_BANK_3;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrY = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrCb = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrCr = (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;

#ifdef CO_MSG_PRINT_ON
	for( loopcnt1 = D_IM_R2Y_YYW_CH_0; loopcnt1 < D_IM_R2Y_YYW_CH_MAX; loopcnt1++ ) {
		ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, loopcnt1, &r2yAddr0 );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

		for( loopcnt2 = D_IM_R2Y_YYW_BANK_0; loopcnt2 < D_IM_R2Y_YYW_BANK_MAX; loopcnt2++ ) {
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "##loop %u-%u\n", loopcnt1, loopcnt2 ));

#ifdef CO_DEBUG_ON_PC
			if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
				ioR2yP1.yyw.yywbank.bit.bank0sts = loopcnt2;
				ioR2yP1.yyw.yywbank.bit.bank1sts = loopcnt2;
				ioR2yP1.yyw.yywbank.bit.bank2sts = loopcnt2;
				ioR2yP1.yyw.yywbank.bit.bankasts = loopcnt2;
			}
			if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
				ioR2yP2.yyw.yywbank.bit.bank0sts = loopcnt2;
				ioR2yP2.yyw.yywbank.bit.bank1sts = loopcnt2;
				ioR2yP2.yyw.yywbank.bit.bank2sts = loopcnt2;
				ioR2yP2.yyw.yywbank.bit.bankasts = loopcnt2;
			}
#endif //CO_DEBUG_ON_PC

			ercd = Im_R2Y_Inc_OutBankIndex( pipeNo, loopcnt1 );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
			im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIPE1\n" ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank0ps = %u\n", ioR2yP1.yyw.yywbank.bit.bank0ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank1ps = %u\n", ioR2yP1.yyw.yywbank.bit.bank1ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank2ps = %u\n", ioR2yP1.yyw.yywbank.bit.bank2ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bankaps = %u\n", ioR2yP1.yyw.yywbank.bit.bankaps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bankst  = %u\n", ioR2yP1.yyw.yywbank.bit.bankst ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIPE2\n" ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank0ps = %u\n", ioR2yP2.yyw.yywbank.bit.bank0ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank1ps = %u\n", ioR2yP2.yyw.yywbank.bit.bank1ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bank2ps = %u\n", ioR2yP2.yyw.yywbank.bit.bank2ps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bankaps = %u\n", ioR2yP2.yyw.yywbank.bit.bankaps ));
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "bankst  = %u\n", ioR2yP2.yyw.yywbank.bit.bankst ));
			im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
		}
	}
#endif


	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_27: "
INT32 ct_im_r2y_classd_1_27( CtImR2yClassd*self,UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif


#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Set_YywParamHold( pipeNo, D_IM_R2Y_ENABLE_ON );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIPE1\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "WKPPRM = %u\n", ioR2yP1.yyw.yywkpp.bit.yywkpp ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIPE2\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "WKPPRM = %u\n", ioR2yP2.yyw.yywkpp.bit.yywkpp ));
	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
	ercd = Im_R2Y_Set_YywParamHold( pipeNo, D_IM_R2Y_ENABLE_OFF );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIPE1\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "WKPPRM = %u\n", ioR2yP1.yyw.yywkpp.bit.yywkpp ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "PIPE2\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "WKPPRM = %u\n", ioR2yP2.yyw.yywkpp.bit.yywkpp ));
	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_28: "
INT32 ct_im_r2y_classd_1_28( CtImR2yClassd*self,UCHAR pipeNo )
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yCtrlSdramInput r2yCtrlSdramIn = gct_im_r2y_ctrl_sdram_in_base;
	TImR2yResizeRect r2yResizeRectParam;
	TImR2yInaddrInfo r2yInAddr = {
		.rgb.addrR = (VOID*)0x10000000,		// R
		.rgb.addrG = (VOID*)0x20000000,		// G
		.rgb.addrB = (VOID*)0x30000000,		// B
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	memset( &r2yResizeRectParam, '\x0', sizeof(r2yResizeRectParam) );

	r2yResizeRectParam.inputSize.imgTop = 375;
	r2yResizeRectParam.inputSize.imgLeft = 500;
	r2yResizeRectParam.inputSize.imgWidth = 2000 - r2yResizeRectParam.inputSize.imgLeft *2;
	r2yResizeRectParam.inputSize.imgLines = 1500 - r2yResizeRectParam.inputSize.imgTop *2;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywWidth = 2000;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines = 1500;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y] = 0x1000;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CB] = 0x2000;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywWidth = 1000;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywLines = 750;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y] = 0x3000;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CB] = 0x4000;

#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));

	ercd = im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));

	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));

	ercd = im_r2y_set_in_addr_info(self->imR2y, pipeNo, &r2yInAddr );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl );
	im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &r2yCtrlSdramIn );
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &gct_im_r2y_ctrl_sdram_in_base );
	im_r2y_set_in_addr_info(self->imR2y, pipeNo, &r2yInAddr );
#endif

	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg();

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_29: "
INT32 ct_im_r2y_classd_1_29( CtImR2yClassd*self,UCHAR pipeNo )
{
	UINT32					loopcnt;
	TImR2yCtrl			r2yCtrl = gctImR2yCtrlBase;
	T_IM_R2Y_RESIZE_PITCH	r2yResizePitch[] = {
		[0] = {	// max
			.inputSize.imgTop = 0,
			.inputSize.imgLeft = 0,
			.inputSize.imgWidth = 2360,
			.inputSize.imgLines = 8960,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputXStartPos = 0xFFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputXPitch = 0xFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputYStartPos = 0xFFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputYPitch = 0xFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_0] = -65536,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_1] = -65536,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputXStartPos = 0xFFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputXPitch = 0xFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputYStartPos = 0xFFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputYPitch = 0xFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_0] = -65536,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_1] = -65536,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputXStartPos = 0xFFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputXPitch = 0xFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputYStartPos = 0xFFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputYPitch = 0xFFFF,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputGlobalW[D_IM_R2Y_PORT_0] = -65536,
			.outputPitch[D_IM_R2Y_YYW_CH_0A].outputGlobalW[D_IM_R2Y_PORT_0] = -65536,
		},
		[1] = {	// min
			.inputSize.imgTop = 0,
			.inputSize.imgLeft = 0,
			.inputSize.imgWidth = 0,
			.inputSize.imgLines = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputXStartPos = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputXPitch = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputYStartPos = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputYPitch = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y] = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CB] = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputXStartPos = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputXPitch = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputYStartPos = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputYPitch = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y] = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CB] = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputXStartPos = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputXPitch = 0x4000,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputYStartPos = 0,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputYPitch = 0x4000,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputGlobalW[D_IM_R2Y_PORT_Y] = 0,
		},
		[2] = {	// ind
			.inputSize.imgTop = 0,
			.inputSize.imgLeft = 0,
			.inputSize.imgWidth = 1000,
			.inputSize.imgLines = 750,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputXStartPos = 1,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputXPitch = 0x4000 / 2,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputYStartPos = 2,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputYPitch = 0x4000 / 4,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y] = 4000,
			.outputPitch[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CB] = 2000,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputXStartPos = 3,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputXPitch = 0x4000 / 8,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputYStartPos = 4,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputYPitch = 0x4000 / 16,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y] = 1000,
			.outputPitch[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CB] = 500,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputXStartPos = 5,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputXPitch = 0x4000 * 2,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputYStartPos = 6,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputYPitch = 0x4000 * 3,
			.outputPitch[D_IM_R2Y_YYW_CH_2].outputGlobalW[D_IM_R2Y_PORT_Y] = 3000,
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < (sizeof(r2yResizePitch) / sizeof(r2yResizePitch[0])); loopcnt++ ) {
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "## %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

		ercd = im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gct_im_r2y_ctrl_sdram_in_base );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

		ercd = Im_r2y_set_resize_pitch(self->imR2y, pipeNo, &r2yResizePitch[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#else
		im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl );
		im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gct_im_r2y_ctrl_sdram_in_base );
		Im_r2y_set_resize_pitch(self->imR2y, pipeNo, &r2yResizePitch );
#endif

		ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
		ct_im_r2y_classa_print_resize_rect_reg();

#ifdef IM_R2Y_STATUS_PRINT
		im_r2y_stat_print_status(self->imR2yStat);
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_30: "
INT32 ct_im_r2y_classd_1_30(CtImR2yClassd*self, UCHAR pipeNo )
{
	TImR2yResizeParam r2yResizeParam;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;
	UCHAR loopcnt2, loopsta, loopend;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	ct_im_r2y_get_loop_val(self->ctImR2y, pipeNo, &loopsta, &loopend );

	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

		switch( loopcnt ) {
			default:
//			case 0:
				ercd = ct_im_r2y_classd_1_28( pipeNo );
				if( ercd != D_DDIM_OK ) {
					return ercd;
				}
				break;
			case 1:
				ercd = ct_im_r2y_classd_1_29( pipeNo );
				if( ercd != D_DDIM_OK ) {
					return ercd;
				}
				break;
		}

		for( loopcnt2 = loopsta; loopcnt2 <= loopend; loopcnt2++ ){
#ifdef CO_MSG_PRINT_ON
			ercd = im_r2y2_get_resize_param(self->imR2y2, loopcnt2, &r2yResizeParam );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));

			Ddim_Print(( "PIPE%d\n", loopcnt2+1 ));
			Ddim_Print(( "resize_select = %u\n", r2yResizeParam.resize_select ));
			switch( r2yResizeParam.resize_select ) {
				case 1:
					Ddim_Print(( "imgTop              = %u\n", r2yResizeParam.r2yResizeRect.inputSize.imgTop ));
					Ddim_Print(( "imgLeft             = %u\n", r2yResizeParam.r2yResizeRect.inputSize.imgLeft ));
					Ddim_Print(( "imgWidth            = %u\n", r2yResizeParam.r2yResizeRect.inputSize.imgWidth ));
					Ddim_Print(( "imgLines            = %u\n", r2yResizeParam.r2yResizeRect.inputSize.imgLines ));
					Ddim_Print(( "0 yywWidth          = %u\n", r2yResizeParam.r2yResizeRect.outputSize[D_IM_R2Y_YYW_CH_0].yywWidth ));
					Ddim_Print(( "0 yywLines          = %u\n", r2yResizeParam.r2yResizeRect.outputSize[D_IM_R2Y_YYW_CH_0].yywLines ));
					Ddim_Print(( "0 outputGlobalW 0  = %u\n", r2yResizeParam.r2yResizeRect.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y] ));
					Ddim_Print(( "0 outputGlobalW 1  = %u\n", r2yResizeParam.r2yResizeRect.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CB] ));
					Ddim_Print(( "1 yywWidth          = %u\n", r2yResizeParam.r2yResizeRect.outputSize[D_IM_R2Y_YYW_CH_1].yywWidth ));
					Ddim_Print(( "1 yywLines          = %u\n", r2yResizeParam.r2yResizeRect.outputSize[D_IM_R2Y_YYW_CH_1].yywLines ));
					Ddim_Print(( "1 outputGlobalW 0  = %u\n", r2yResizeParam.r2yResizeRect.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y] ));
					Ddim_Print(( "1 outputGlobalW 1  = %u\n", r2yResizeParam.r2yResizeRect.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CB] ));
					break;
				case 2:
					Ddim_Print(( "imgTop              = %u\n", r2yResizeParam.r2yResizePitch.inputSize.imgTop ));
					Ddim_Print(( "imgLeft             = %u\n", r2yResizeParam.r2yResizePitch.inputSize.imgLeft ));
					Ddim_Print(( "imgWidth            = %u\n", r2yResizeParam.r2yResizePitch.inputSize.imgWidth ));
					Ddim_Print(( "imgLines            = %u\n", r2yResizeParam.r2yResizePitch.inputSize.imgLines ));
					Ddim_Print(( "0 outputXStartPos = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_0].outputXStartPos ));
					Ddim_Print(( "0 outputXPitch     = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_0].outputXPitch ));
					Ddim_Print(( "0 outputYStartPos = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_0].outputYStartPos ));
					Ddim_Print(( "0 outputYPitch     = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_0].outputYPitch ));
					Ddim_Print(( "0 outputGlobalW 0  = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y] ));
					Ddim_Print(( "0 outputGlobalW 1  = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CB] ));
					Ddim_Print(( "1 outputXStartPos = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_1].outputXStartPos ));
					Ddim_Print(( "1 outputXPitch     = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_1].outputXPitch ));
					Ddim_Print(( "1 outputYStartPos = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_1].outputYStartPos ));
					Ddim_Print(( "1 outputYPitch     = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_1].outputYPitch ));
					Ddim_Print(( "1 outputGlobalW 0  = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y] ));
					Ddim_Print(( "1 outputGlobalW 1  = %u\n", r2yResizeParam.r2yResizePitch.outputPitch[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CB] ));
					break;
			}

#else
			im_r2y2_get_resize_param(self->imR2y2, loopcnt2, &r2yResizeParam );
#endif
		}
	}

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_31: "
INT32 ct_im_r2y_classd_1_31( CtImR2yClassd*self,UCHAR pipeNo )
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yResizeRect r2yResizeRectParam;
	TImR2yInaddrInfo r2yInAddr;
	TImR2yOutbankInfo r2yAddr0;
	TImR2yOutbankInfo r2yAddr1;
	TImR2yOutbankInfo r2yAddr2;
	TImR2yOutbankInfo r2yAddr0a;
	TImR2yOutaddrInfo outAddrInfo;
	UINT32 loopcnt;
	UCHAR bankIndex;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
	const char dumpmsg[] = "%d idx=%u addr y=0x%05lx cb=0x%05lx cr=0x%05lx\n";
#endif

	r2yCtrl.outputMode0a = D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_32_SP;

	r2yResizeRectParam.inputSize.imgTop = 0;
	r2yResizeRectParam.inputSize.imgLeft = 0;
	r2yResizeRectParam.inputSize.imgWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH;
	r2yResizeRectParam.inputSize.imgLines = D_IM_R2Y_SRC_IMG_PIXS_LINES;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CB] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_C;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywWidth = 320;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywLines = 240;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CB] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_C;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;

	r2yInAddr.rgb.addrR = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_R_ADDR_TOP;
	r2yInAddr.rgb.addrG = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_G_ADDR_TOP;
	r2yInAddr.rgb.addrB = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_B_ADDR_TOP;

	memset( &r2yAddr0, '\x0', sizeof(r2yAddr0) );
	r2yAddr0.bankInitialPosition = D_IM_R2Y_YYW_BANK_3;
	r2yAddr0.useBankNum = D_IM_R2Y_YYW_BANK_3;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY = (VOID*)0x100;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb = (VOID*)0x200;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCr = (VOID*)0x300;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrY = (VOID*)0x400;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrCb = (VOID*)0x500;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrCr = (VOID*)0x600;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrY = (VOID*)0x700;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrCb = (VOID*)0x800;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrCr = (VOID*)0x900;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrY = (VOID*)0xa00;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrCb = (VOID*)0xb00;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrCr = (VOID*)0xc00;

	memset( &r2yAddr1, '\x0', sizeof(r2yAddr1) );
	r2yAddr1.bankInitialPosition = D_IM_R2Y_YYW_BANK_3;
	r2yAddr1.useBankNum = D_IM_R2Y_YYW_BANK_3;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY = (VOID*)0x1100;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb = (VOID*)0x1200;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCr = (VOID*)0x1300;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrY = (VOID*)0x1400;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrCb = (VOID*)0x1500;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrCr = (VOID*)0x1600;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrY = (VOID*)0x1700;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrCb = (VOID*)0x1800;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrCr = (VOID*)0x1900;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrY = (VOID*)0x1a00;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrCb = (VOID*)0x1b00;
	r2yAddr1.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrCr = (VOID*)0x1c00;

	memset( &r2yAddr2, '\x0', sizeof(r2yAddr2) );
	r2yAddr2.bankInitialPosition = D_IM_R2Y_YYW_BANK_3;
	r2yAddr2.useBankNum = D_IM_R2Y_YYW_BANK_3;
	r2yAddr2.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY = (VOID*)0x2100;
	r2yAddr2.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrY = (VOID*)0x2200;
	r2yAddr2.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrY = (VOID*)0x2300;
	r2yAddr2.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrY = (VOID*)0x2400;

	memset( &r2yAddr0a, '\x0', sizeof(r2yAddr0a) );
	r2yAddr0a.bankInitialPosition = D_IM_R2Y_YYW_BANK_3;
	r2yAddr0a.useBankNum = D_IM_R2Y_YYW_BANK_3;
	r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY = (VOID*)0x3100;
	r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb = (VOID*)0x3200;
	r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrY = (VOID*)0x3300;
	r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrCb = (VOID*)0x3400;
	r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrY = (VOID*)0x3500;
	r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrCb = (VOID*)0x3600;
	r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrY = (VOID*)0x3700;
	r2yAddr0a.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrCb = (VOID*)0x3800;

#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gct_im_r2y_ctrl_sdram_in_base );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_set_in_addr_info(self->imR2y, pipeNo, &r2yInAddr );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr1 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr2 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0a );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl );
	im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gct_im_r2y_ctrl_sdram_in_base );
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam );
	im_r2y_set_in_addr_info(self->imR2y, pipeNo, &r2yInAddr );
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0 );
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr1 );
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr2 );
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0a );
#endif

	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", 0 ));

#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "Status\n" ));
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	for( loopcnt = 0; loopcnt < D_IM_R2Y_YYW_BANK_MAX; loopcnt++ ) {
#ifdef D_IM_R2Y_DEBUG_ON_PC
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
			gIM_R2Y_macro_fake_finish[0] = 1;
		}
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
			gIM_R2Y_macro_fake_finish[1] = 1;
		}
#endif
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "R2Y Start\n" ));


#ifdef CO_MSG_PRINT_ON
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "loopcnt = %u\n", loopcnt ));
		ercd = Im_R2Y_Start( pipeNo );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#else
		Im_R2Y_Start( pipeNo );
#endif

#ifdef D_IM_R2Y_DEBUG_ON_PC
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
			gIM_R2Y_macro_fake_finish[0] = 0;
		}
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
			gIM_R2Y_macro_fake_finish[1] = 0;
		}
#endif

		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
			flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
		}
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
			flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
		}

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_proc_wait_end(self->imR2yProc, NULL, flgptn, 60 );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
			ercd = im_r2y3_get_latest_out_addr(self->imR2y3, 0, D_IM_R2Y_YYW_CH_0, &bankIndex, &outAddrInfo );
			Ddim_Print(( dumpmsg,
						ercd,
						bankIndex,
						(ULONG)outAddrInfo.ycc.addrY,
						(ULONG)outAddrInfo.ycc.addrCb,
						(ULONG)outAddrInfo.ycc.addrCr
						));
			ercd = im_r2y3_get_latest_out_addr(self->imR2y3, 0, D_IM_R2Y_YYW_CH_1, &bankIndex, &outAddrInfo );
			Ddim_Print(( dumpmsg,
						ercd,
						bankIndex,
						(ULONG)outAddrInfo.ycc.addrY,
						(ULONG)outAddrInfo.ycc.addrCb,
						(ULONG)outAddrInfo.ycc.addrCr
						));
			ercd = im_r2y3_get_latest_out_addr(self->imR2y3, 0, D_IM_R2Y_YYW_CH_2, &bankIndex, &outAddrInfo );
			Ddim_Print(( dumpmsg,
						ercd,
						bankIndex,
						(ULONG)outAddrInfo.ycc.addrY,
						(ULONG)outAddrInfo.ycc.addrCb,
						(ULONG)outAddrInfo.ycc.addrCr
						));
			ercd = im_r2y3_get_latest_out_addr(self->imR2y3, 0, D_IM_R2Y_YYW_CH_0A, &bankIndex, &outAddrInfo );
			Ddim_Print(( dumpmsg,
						ercd,
						bankIndex,
						(ULONG)outAddrInfo.ycc.addrY,
						(ULONG)outAddrInfo.ycc.addrCb,
						(ULONG)outAddrInfo.ycc.addrCr
						));
		}
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
			ercd = im_r2y3_get_latest_out_addr(self->imR2y3, 1, D_IM_R2Y_YYW_CH_0, &bankIndex, &outAddrInfo );
			Ddim_Print(( dumpmsg,
						ercd,
						bankIndex,
						(ULONG)outAddrInfo.ycc.addrY,
						(ULONG)outAddrInfo.ycc.addrCb,
						(ULONG)outAddrInfo.ycc.addrCr
						));
			ercd = im_r2y3_get_latest_out_addr(self->imR2y3, 1, D_IM_R2Y_YYW_CH_1, &bankIndex, &outAddrInfo );
			Ddim_Print(( dumpmsg,
						ercd,
						bankIndex,
						(ULONG)outAddrInfo.ycc.addrY,
						(ULONG)outAddrInfo.ycc.addrCb,
						(ULONG)outAddrInfo.ycc.addrCr
						));
			ercd = im_r2y3_get_latest_out_addr(self->imR2y3, 1, D_IM_R2Y_YYW_CH_2, &bankIndex, &outAddrInfo );
			Ddim_Print(( dumpmsg,
						ercd,
						bankIndex,
						(ULONG)outAddrInfo.ycc.addrY,
						(ULONG)outAddrInfo.ycc.addrCb,
						(ULONG)outAddrInfo.ycc.addrCr
						));
			ercd = im_r2y3_get_latest_out_addr(self->imR2y3, 1, D_IM_R2Y_YYW_CH_0A, &bankIndex, &outAddrInfo );
			Ddim_Print(( dumpmsg,
						ercd,
						bankIndex,
						(ULONG)outAddrInfo.ycc.addrY,
						(ULONG)outAddrInfo.ycc.addrCb,
						(ULONG)outAddrInfo.ycc.addrCr
						));
		}

		ercd = Im_R2Y_Stop( pipeNo );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#else
		im_r2y_proc_wait_end(self->imR2yProc, NULL, flgptn, 60 );
		im_r2y_get_out_bank_index(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &bankIndex );
		im_r2y_get_out_bank_index(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_1, &bankIndex );
		Im_R2Y_Stop( pipeNo );
#endif

#ifdef IM_R2Y_STATUS_PRINT
//		im_r2y_stat_print_status(self->imR2yStat);
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_32: "
INT32 ct_im_r2y_classd_1_32( CtImR2yClassd*self,UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
	const char msgDump1[] = D_IM_R2Y_FUNC_NAME "extben = %u\n";
	const char msg_dump2[] = D_IM_R2Y_FUNC_NAME "extcen = %u\n";
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_set_externalIf_output(self->imR2y3, pipeNo, 1, 1 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( msgDump1, ioR2yP1.yyw.yyw0md.bit.extben ));
	Ddim_Print(( msg_dump2, ioR2yP1.yyw.yyw0md.bit.extcen ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( msgDump1, ioR2yP2.yyw.yyw0md.bit.extben ));
	Ddim_Print(( msg_dump2, ioR2yP2.yyw.yyw0md.bit.extcen ));
	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
	ercd = im_r2y_set_externalIf_output(self->imR2y3, pipeNo, 0, 0 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( msgDump1, ioR2yP1.yyw.yyw0md.bit.extben ));
	Ddim_Print(( msg_dump2, ioR2yP1.yyw.yyw0md.bit.extcen ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( msgDump1, ioR2yP2.yyw.yyw0md.bit.extben ));
	Ddim_Print(( msg_dump2, ioR2yP2.yyw.yyw0md.bit.extcen ));
	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
	ercd = im_r2y_set_externalIf_output(self->imR2y3, pipeNo, 0, 1 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( msgDump1, ioR2yP1.yyw.yyw0md.bit.extben ));
	Ddim_Print(( msg_dump2, ioR2yP1.yyw.yyw0md.bit.extcen ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( msgDump1, ioR2yP2.yyw.yyw0md.bit.extben ));
	Ddim_Print(( msg_dump2, ioR2yP2.yyw.yyw0md.bit.extcen ));
	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
	ercd = im_r2y_set_externalIf_output(self->imR2y3, pipeNo, 1, 0 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( msgDump1, ioR2yP1.yyw.yyw0md.bit.extben ));
	Ddim_Print(( msg_dump2, ioR2yP1.yyw.yyw0md.bit.extcen ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( msgDump1, ioR2yP2.yyw.yyw0md.bit.extben ));
	Ddim_Print(( msg_dump2, ioR2yP2.yyw.yyw0md.bit.extcen ));
	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_33: "
INT32 ct_im_r2y_classd_1_33( CtImR2yClassd*self,UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
	const char msgDump1[] = D_IM_R2Y_FUNC_NAME "extben = %u extcen = %u\n";
	UCHAR ipuEn, cnrEn;
	UCHAR loopcnt, loopsta, loopend;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ct_im_r2y_get_loop_val(self->ctImR2y, pipeNo, &loopsta, &loopend );

	for( loopcnt = loopsta; loopcnt <= loopend; loopcnt++ ){
		ercd = im_r2y_set_externalIf_output(self->imR2y3, loopcnt, 1, 1 );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		ercd = im_r2y_get_externalIf_output(self->imR2y3, loopcnt, &ipuEn, &cnrEn );
		Ddim_Print(( msgDump1, ipuEn, cnrEn ));
		ercd = im_r2y_set_externalIf_output(self->imR2y3, loopcnt, 0, 0 );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		ercd = im_r2y_get_externalIf_output(self->imR2y3, loopcnt, &ipuEn, &cnrEn );
		Ddim_Print(( msgDump1, ipuEn, cnrEn ));
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_34: "
INT32 ct_im_r2y_classd_1_34( CtImR2yClassd*self,UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Set_FrameStop( pipeNo, 1 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "frmstp = %u\n", ioR2yP1.yyr.dinctl.bit.frmstp ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "frmstp = %u\n", ioR2yP2.yyr.dinctl.bit.frmstp ));
	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
	ercd = Im_R2Y_Set_FrameStop( pipeNo, 0 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "frmstp = %u\n", ioR2yP1.yyr.dinctl.bit.frmstp ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "frmstp = %u\n", ioR2yP2.yyr.dinctl.bit.frmstp ));
	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_35: "
INT32 ct_im_r2y_classd_1_35( CtImR2yClassd*self,UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
	BOOL busyState;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 3;
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
		ercd = Im_R2Y_Get_YyrBusy( 0, &busyState );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "busy = %u\n", busyState ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		ioR2yP1.yyr.yyrtrg.bit.yyrtrg = 2;
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
		ercd = Im_R2Y_Get_YyrBusy( 0, &busyState );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "busy = %u\n", busyState ));
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		ioR2yP2.yyr.yyrtrg.bit.yyrtrg = 3;
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
		ercd = Im_R2Y_Get_YyrBusy( 1, &busyState );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "busy = %u\n", busyState ));
		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		ioR2yP2.yyr.yyrtrg.bit.yyrtrg = 2;
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
		ercd = Im_R2Y_Get_YyrBusy( 1, &busyState );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "busy = %u\n", busyState ));
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classd_1_36: "
INT32 ct_im_r2y_classd_1_36( CtImR2yClassd*self,UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
	USHORT ringPixs;
#endif
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	r2yCtrl.ycfBypass  = 0;
	r2yCtrl.ycfPadding = 0;

	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		ercd = im_r2y3_get_h_ring_pixs(self->imR2y3, 0, &ringPixs );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ring = %u\n", ringPixs ));
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		ercd = im_r2y3_get_h_ring_pixs(self->imR2y3, 1, &ringPixs );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ring = %u\n", ringPixs ));
	}

	r2yCtrl.ycfBypass  = 1;
	r2yCtrl.ycfPadding = 0;

	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		ercd = im_r2y3_get_h_ring_pixs(self->imR2y3, 0, &ringPixs );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ring = %u\n", ringPixs ));
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		ercd = im_r2y3_get_h_ring_pixs(self->imR2y3, 1, &ringPixs );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "ring = %u\n", ringPixs ));
	}
#endif

	return D_DDIM_OK;
}

CtImR2yClassd* ct_im_r2y_classd_new(void)
{
	CtImR2yClassd* self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSD, sizeof(CtImR2yClassdPrivate));

	return self;
}

CtImR2yClassd* ct_im_r2y_classd_get(void)
{
	static CtImR2yClassd* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSD, sizeof(CtImR2yClassdPrivate));
	}

	return self;
}
